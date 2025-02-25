#include "operation_controller_impl.h"
#include "bootstrap.h"
#include "controller_agent_tracker.h"
#include "helpers.h"
#include "node_manager.h"
#include "private.h"
#include "scheduler.h"

#include <yt/yt/server/lib/exec_node/public.h>

#include <yt/yt/server/lib/controller_agent/helpers.h>

#include <yt/yt/server/lib/scheduler/config.h>
#include <yt/yt/server/lib/scheduler/experiments.h>
#include <yt/yt/server/lib/scheduler/helpers.h>

#include <yt/yt/ytlib/api/native/client.h>
#include <yt/yt/ytlib/api/native/connection.h>

#include <yt/yt/ytlib/controller_agent/job_prober_service_proxy.h>

#include <yt/yt/ytlib/job_proxy/public.h>

namespace NYT::NScheduler {

using namespace NConcurrency;
using namespace NRpc;
using namespace NYson;
using namespace NYTree;
using namespace NControllerAgent;

using NYT::FromProto;
using NYT::ToProto;

////////////////////////////////////////////////////////////////////////////////

namespace {

bool IsAgentFailureError(const TError& error)
{
    if (IsChannelFailureError(error)) {
        return true;
    }
    auto code = error.GetCode();
    return code == NYT::EErrorCode::Timeout;
}

bool IsAgentDisconnectionError(const TError& error)
{
    return error.FindMatching(NObjectClient::EErrorCode::PrerequisiteCheckFailed).has_value();
}

} // namespace

////////////////////////////////////////////////////////////////////////////////

TOperationControllerImpl::TOperationControllerImpl(
    TBootstrap* bootstrap,
    TSchedulerConfigPtr config,
    const TOperationPtr& operation)
    : Bootstrap_(bootstrap)
    , Config_(std::move(config))
    , OperationId_(operation->GetId())
    , PreemptionMode_(operation->Spec()->PreemptionMode)
    , Logger(SchedulerLogger.WithTag("OperationId: %v", OperationId_))
    , ControllerRuntimeData_(New<TControllerRuntimeData>())
{ }


void TOperationControllerImpl::AssignAgent(const TControllerAgentPtr& agent, TControllerEpoch epoch)
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    auto guard = Guard(SpinLock_);

    YT_VERIFY(!IncarnationId_);
    IncarnationId_ = agent->GetIncarnationId();
    Agent_ = agent;

    ControllerAgentTrackerProxy_ = std::make_unique<TControllerAgentServiceProxy>(agent->GetChannel());
    ControllerAgentJobProberProxy_ = std::make_unique<TJobProberServiceProxy>(agent->GetChannel());

    Epoch_.store(epoch);

    JobEventsOutbox_ = agent->GetJobEventsOutbox();
    OperationEventsOutbox_ = agent->GetOperationEventsOutbox();
    ScheduleJobRequestsOutbox_ = agent->GetScheduleJobRequestsOutbox();
}

bool TOperationControllerImpl::RevokeAgent()
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    auto guard = Guard(SpinLock_);

    if (!IncarnationId_) {
        return false;
    }

    PendingInitializeResult_ = TPromise<TOperationControllerInitializeResult>();
    PendingPrepareResult_ = TPromise<TOperationControllerPrepareResult>();
    PendingMaterializeResult_ = TPromise<TOperationControllerMaterializeResult>();
    PendingReviveResult_ = TPromise<TOperationControllerReviveResult>();
    PendingCommitResult_ = TPromise<TOperationControllerCommitResult>();

    ControllerAgentTrackerProxy_.reset();
    ControllerAgentJobProberProxy_.reset();

    IncarnationId_ = {};
    Agent_.Reset();

    YT_LOG_INFO("Agent revoked for operation");

    return true;
}

TControllerAgentPtr TOperationControllerImpl::FindAgent() const
{
    VERIFY_THREAD_AFFINITY_ANY();

    return Agent_.Lock();
}

TControllerEpoch TOperationControllerImpl::GetEpoch() const
{
    return Epoch_.load();
}

TFuture<TOperationControllerInitializeResult> TOperationControllerImpl::Initialize(const std::optional<TOperationTransactions>& transactions)
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto agent = Agent_.Lock();
    if (!agent) {
        throw TFiberCanceledException();
    }

    YT_VERIFY(!PendingInitializeResult_);
    PendingInitializeResult_ = NewPromise<TOperationControllerInitializeResult>();

    auto req = ControllerAgentTrackerProxy_->InitializeOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->SetTimeout(Config_->ControllerAgentTracker->LightRpcTimeout);
    if (transactions) {
        req->set_clean(false);
        ToProto(req->mutable_transaction_ids(), *transactions);
    } else {
        req->set_clean(true);
    }
    InvokeAgent<TControllerAgentServiceProxy::TRspInitializeOperation>(req).Subscribe(
        BIND([
            this,
            this_ = MakeStrong(this)
        ] (const TErrorOr<TControllerAgentServiceProxy::TRspInitializeOperationPtr>& rspOrError) {
            if (!IncarnationId_) {
                // Operation agent was revoked.
                return;
            }
            if (!rspOrError.IsOK()) {
                OnInitializationFinished(static_cast<TError>(rspOrError));
                return;
            }

            auto rsp = rspOrError.Value();
            if (rsp->has_result()) {
                TOperationControllerInitializeResult result;
                FromProto(
                    &result,
                    rsp->result(),
                    OperationId_,
                    Bootstrap_,
                    Config_->OperationTransactionPingPeriod);

                OnInitializationFinished(result);
            }
        })
        .Via(agent->GetCancelableInvoker()));

    return PendingInitializeResult_;
}

TFuture<TOperationControllerPrepareResult> TOperationControllerImpl::Prepare()
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto agent = Agent_.Lock();
    if (!agent) {
        throw TFiberCanceledException();
    }

    YT_VERIFY(!PendingPrepareResult_);
    PendingPrepareResult_ = NewPromise<TOperationControllerPrepareResult>();

    auto req = ControllerAgentTrackerProxy_->PrepareOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->SetTimeout(Config_->ControllerAgentTracker->LightRpcTimeout);
    InvokeAgent<TControllerAgentServiceProxy::TRspPrepareOperation>(req).Subscribe(
        BIND([
            this,
            this_ = MakeStrong(this)
        ] (const TErrorOr<TControllerAgentServiceProxy::TRspPrepareOperationPtr>& rspOrError) {
            if (!IncarnationId_) {
                // Operation agent was revoked.
                return;
            }
            if (!rspOrError.IsOK()) {
                OnPreparationFinished(static_cast<TError>(rspOrError));
                return;
            }

            auto rsp = rspOrError.Value();
            if (rsp->has_result()) {
                OnPreparationFinished(FromProto<TOperationControllerPrepareResult>(rsp->result()));
            }
        })
        .Via(agent->GetCancelableInvoker()));

    return PendingPrepareResult_;
}

TFuture<TOperationControllerMaterializeResult> TOperationControllerImpl::Materialize()
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto agent = Agent_.Lock();
    if (!agent) {
        throw TFiberCanceledException();
    }

    YT_VERIFY(!PendingMaterializeResult_);
    PendingMaterializeResult_ = NewPromise<TOperationControllerMaterializeResult>();

    auto req = ControllerAgentTrackerProxy_->MaterializeOperation();
    req->SetTimeout(Config_->ControllerAgentTracker->LightRpcTimeout);
    ToProto(req->mutable_operation_id(), OperationId_);
    InvokeAgent<TControllerAgentServiceProxy::TRspMaterializeOperation>(req).Subscribe(
        BIND([
            this,
            this_ = MakeStrong(this)
        ] (const TErrorOr<TControllerAgentServiceProxy::TRspMaterializeOperationPtr>& rspOrError) {
            if (!IncarnationId_) {
                // Operation agent was revoked.
                return;
            }
            if (!rspOrError.IsOK()) {
                OnMaterializationFinished(static_cast<TError>(rspOrError));
                return;
            }

            auto rsp = rspOrError.Value();
            if (rsp->has_result()) {
                OnMaterializationFinished(FromProto<TOperationControllerMaterializeResult>(rsp->result()));
            }
        })
        .Via(agent->GetCancelableInvoker()));

    return PendingMaterializeResult_;
}

TFuture<TOperationControllerReviveResult> TOperationControllerImpl::Revive()
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto agent = Agent_.Lock();
    if (!agent) {
        throw TFiberCanceledException();
    }

    YT_VERIFY(!PendingReviveResult_);
    PendingReviveResult_ = NewPromise<TOperationControllerReviveResult>();

    auto req = ControllerAgentTrackerProxy_->ReviveOperation();
    req->SetTimeout(Config_->ControllerAgentTracker->LightRpcTimeout);
    ToProto(req->mutable_operation_id(), OperationId_);
    InvokeAgent<TControllerAgentServiceProxy::TRspReviveOperation>(req).Subscribe(
        BIND([
            this,
            this_ = MakeStrong(this),
            operationId = OperationId_,
            incarnationId = agent->GetIncarnationId(),
            preemptionMode = PreemptionMode_
        ] (const TErrorOr<TControllerAgentServiceProxy::TRspReviveOperationPtr>& rspOrError) {
            if (!IncarnationId_) {
                // Operation agent was revoked.
                return;
            }
            if (!rspOrError.IsOK()) {
                OnRevivalFinished(static_cast<TError>(rspOrError));
                return;
            }

            auto rsp = rspOrError.Value();
            if (rsp->has_result()) {
                TOperationControllerReviveResult result;
                FromProto(
                    &result,
                    rsp->result(),
                    operationId,
                    incarnationId,
                    preemptionMode);

                OnRevivalFinished(result);
            }
        })
        .Via(agent->GetCancelableInvoker()));

    return PendingReviveResult_;
}

TFuture<TOperationControllerCommitResult> TOperationControllerImpl::Commit()
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto agent = Agent_.Lock();
    if (!agent) {
        throw TFiberCanceledException();
    }

    YT_VERIFY(!PendingCommitResult_);
    PendingCommitResult_ = NewPromise<TOperationControllerCommitResult>();

    auto req = ControllerAgentTrackerProxy_->CommitOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->SetTimeout(Config_->ControllerAgentTracker->LightRpcTimeout);
    InvokeAgent<TControllerAgentServiceProxy::TRspCommitOperation>(req).Subscribe(
        BIND([
            this,
            this_ = MakeStrong(this)
        ] (const TErrorOr<TControllerAgentServiceProxy::TRspCommitOperationPtr>& rspOrError) {
            if (!IncarnationId_) {
                // Operation agent was revoked.
                return;
            }
            if (!rspOrError.IsOK()) {
                OnCommitFinished(static_cast<TError>(rspOrError));
                return;
            }

            auto rsp = rspOrError.Value();
            if (rsp->has_result()) {
                OnCommitFinished(FromProto<TOperationControllerCommitResult>(rsp->result()));
            }
        })
        .Via(agent->GetCancelableInvoker()));

    return PendingCommitResult_;
}

TFuture<void> TOperationControllerImpl::Terminate(EOperationState finalState)
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    YT_LOG_INFO("Terminating operation controller");

    if (!IncarnationId_) {
        YT_LOG_INFO("Operation has no agent assigned; terminate request ignored");
        return VoidFuture;
    }

    YT_VERIFY(finalState == EOperationState::Aborted || finalState == EOperationState::Failed);
    EControllerState controllerFinalState = finalState == EOperationState::Aborted
        ? EControllerState::Aborted
        : EControllerState::Failed;

    auto req = ControllerAgentTrackerProxy_->TerminateOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->set_controller_final_state(static_cast<int>(controllerFinalState));
    req->SetTimeout(Config_->ControllerAgentTracker->HeavyRpcTimeout);
    return InvokeAgent<TControllerAgentServiceProxy::TRspTerminateOperation>(req).As<void>();
}

TFuture<void> TOperationControllerImpl::Complete()
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    YT_VERIFY(IncarnationId_);

    auto req = ControllerAgentTrackerProxy_->CompleteOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->SetTimeout(Config_->ControllerAgentTracker->HeavyRpcTimeout);
    return InvokeAgent<TControllerAgentServiceProxy::TRspCompleteOperation>(req).As<void>();
}

TFuture<void> TOperationControllerImpl::Register(const TOperationPtr& operation)
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    auto agent = Agent_.Lock();
    // Called synchronously just after assinging agent.
    YT_VERIFY(agent);

    YT_LOG_DEBUG("Registering operation at agent (AgentId: %v, OperationId: %v)",
        agent->GetId(),
        operation->GetId());

    TControllerAgentServiceProxy proxy(agent->GetChannel());
    auto req = proxy.RegisterOperation();
    req->SetTimeout(Config_->ControllerAgentTracker->HeavyRpcTimeout);

    auto* descriptor = req->mutable_operation_descriptor();
    ToProto(descriptor->mutable_operation_id(), operation->GetId());
    descriptor->set_operation_type(static_cast<int>(operation->GetType()));
    descriptor->set_spec(operation->GetSpecString().ToString());
    descriptor->set_experiment_assignments(ConvertToYsonString(operation->ExperimentAssignments()).ToString());
    descriptor->set_start_time(ToProto<ui64>(operation->GetStartTime()));
    descriptor->set_authenticated_user(operation->GetAuthenticatedUser());
    if (operation->GetSecureVault()) {
        descriptor->set_secure_vault(ConvertToYsonString(operation->GetSecureVault()).ToString());
    }
    descriptor->set_acl(ConvertToYsonString(operation->GetRuntimeParameters()->Acl).ToString());
    ToProto(descriptor->mutable_pool_tree_controller_settings_map(), operation->PoolTreeControllerSettingsMap());
    ToProto(descriptor->mutable_user_transaction_id(), operation->GetUserTransactionId());
    descriptor->set_controller_epoch(operation->ControllerEpoch());

    return InvokeAgent<TControllerAgentServiceProxy::TRspRegisterOperation>(req).As<void>();
}

TFuture<TOperationControllerUnregisterResult> TOperationControllerImpl::Unregister()
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    if (!IncarnationId_) {
        YT_LOG_INFO("Operation has no agent assigned; unregister request ignored");
        return MakeFuture<TOperationControllerUnregisterResult>({});
    }

    YT_LOG_INFO("Unregistering operation controller");

    auto req = ControllerAgentTrackerProxy_->UnregisterOperation();
    ToProto(req->mutable_operation_id(), OperationId_);
    req->SetTimeout(Config_->ControllerAgentTracker->HeavyRpcTimeout);
    return InvokeAgent<TControllerAgentServiceProxy::TRspUnregisterOperation>(req).Apply(
        BIND([] (const TControllerAgentServiceProxy::TRspUnregisterOperationPtr& rsp) {
            return TOperationControllerUnregisterResult{FromProto<TOperationJobMetrics>(rsp->residual_job_metrics())};
        }));
}

TFuture<void> TOperationControllerImpl::UpdateRuntimeParameters(TOperationRuntimeParametersUpdatePtr update)
{
    VERIFY_THREAD_AFFINITY(ControlThread);
    if (!IncarnationId_) {
        return VoidFuture;
    }

    auto req = ControllerAgentTrackerProxy_->UpdateOperationRuntimeParameters();
    ToProto(req->mutable_operation_id(), OperationId_);
    ToProto(req->mutable_parameters(), ConvertToYsonString(update).ToString());
    req->SetTimeout(Config_->ControllerAgentTracker->HeavyRpcTimeout);
    return InvokeAgent<TControllerAgentServiceProxy::TRspUpdateOperationRuntimeParameters>(req).As<void>();
}

void TOperationControllerImpl::OnJobFinished(
    const TJobPtr& job)
{
    VERIFY_THREAD_AFFINITY_ANY();

    if (ShouldSkipJobEvent(job)) {
        return;
    }

    TFinishedJobSummary eventSummary{
        .OperationId = OperationId_,
        .Id = job->GetId(),
        .FinishTime = TInstant::Now(),
    };

    auto result = EnqueueJobEvent(std::move(eventSummary));
    YT_LOG_TRACE("Job finish notification %v (JobId: %v)",
        result ? "enqueued" : "dropped",
        job->GetId());
}

void TOperationControllerImpl::OnJobAborted(
    TJobId jobId,
    const TError& error,
    bool scheduled,
    std::optional<EAbortReason> abortReason,
    TControllerEpoch jobEpoch)
{
    VERIFY_THREAD_AFFINITY_ANY();

    if (ShouldSkipJobEvent(jobId, jobEpoch)) {
        return;
    }

    TAbortedBySchedulerJobSummary eventSummary{
        .OperationId = OperationId_,
        .Id = jobId,
        .FinishTime = TInstant::Now(),
        .AbortReason = abortReason,
        .Error = error.Truncate(),
        .Scheduled = scheduled,
    };

    auto result = EnqueueJobEvent(std::move(eventSummary));
    YT_LOG_TRACE("%v abort notification %v (JobId: %v)",
        scheduled ? "Job" : "Nonscheduled job",
        result ? "enqueued" : "dropped",
        jobId);
}

void TOperationControllerImpl::OnJobAborted(
    const TJobPtr& job,
    const TError& error,
    bool scheduled,
    std::optional<EAbortReason> abortReason)
{
    VERIFY_THREAD_AFFINITY_ANY();

    OnJobAborted(job->GetId(), error, scheduled, abortReason, job->GetControllerEpoch());
}

void TOperationControllerImpl::OnNonscheduledJobAborted(
    TJobId jobId,
    EAbortReason abortReason,
    TControllerEpoch jobEpoch)
{
    VERIFY_THREAD_AFFINITY_ANY();

    OnJobAborted(jobId, TError{}, false, abortReason, jobEpoch);
}

TFuture<void> TOperationControllerImpl::AbandonJob(TOperationId operationId, TJobId jobId)
{
    VERIFY_THREAD_AFFINITY_ANY();

    auto agent = Agent_.Lock();
    if (!agent) {
        THROW_ERROR_EXCEPTION(
            NScheduler::EErrorCode::AgentRevoked,
            "agent that has hosted operation %v is revoked", operationId);
    }

    auto request = ControllerAgentJobProberProxy_->AbandonJob();
    ToProto(request->mutable_incarnation_id(), agent->GetIncarnationId());
    ToProto(request->mutable_operation_id(), operationId);
    ToProto(request->mutable_job_id(), jobId);

    return request->Invoke().As<void>();
}

void TOperationControllerImpl::OnInitializationFinished(const TErrorOr<TOperationControllerInitializeResult>& resultOrError)
{
    YT_VERIFY(PendingInitializeResult_);

    if (resultOrError.IsOK()) {
        YT_LOG_DEBUG("Successful initialization result received");
    } else {
        YT_LOG_DEBUG(resultOrError, "Unsuccessful initialization result received");
        ProcessControllerAgentError(resultOrError);
    }

    PendingInitializeResult_.TrySet(resultOrError);
}

void TOperationControllerImpl::OnPreparationFinished(const TErrorOr<TOperationControllerPrepareResult>& resultOrError)
{
    YT_VERIFY(PendingPrepareResult_);

    if (resultOrError.IsOK()) {
        YT_LOG_DEBUG("Successful preparation result received");
    } else {
        YT_LOG_DEBUG(resultOrError, "Unsuccessful preparation result received");
        ProcessControllerAgentError(resultOrError);
    }

    PendingPrepareResult_.TrySet(resultOrError);
}

void TOperationControllerImpl::OnMaterializationFinished(const TErrorOr<TOperationControllerMaterializeResult>& resultOrError)
{
    YT_VERIFY(PendingMaterializeResult_);

    if (resultOrError.IsOK()) {
        auto materializeResult = resultOrError.Value();

        ControllerRuntimeData_->SetNeededResources(materializeResult.InitialNeededResources);
        ControllerRuntimeData_->MinNeededJobResources() = materializeResult.InitialMinNeededJobResources;

        YT_LOG_DEBUG("Successful materialization result received ("
            "Suspend: %v, InitialNeededResources: %v, InitialAggregatedMinNeededResources: %v)",
            materializeResult.Suspend,
            FormatResources(materializeResult.InitialNeededResources),
            FormatResources(materializeResult.InitialAggregatedMinNeededResources));
    } else {
        YT_LOG_DEBUG(resultOrError, "Unsuccessful materialization result received");
        ProcessControllerAgentError(resultOrError);
    }

    PendingMaterializeResult_.TrySet(resultOrError);
}

void TOperationControllerImpl::OnRevivalFinished(const TErrorOr<TOperationControllerReviveResult>& resultOrError)
{
    YT_VERIFY(PendingReviveResult_);

    if (resultOrError.IsOK()) {
        auto result = resultOrError.Value();

        // NB(eshcherbin): ControllerRuntimeData is used to pass NeededResources to MaterializeOperation().
        ControllerRuntimeData_->SetNeededResources(result.NeededResources);
        ControllerRuntimeData_->MinNeededJobResources() = result.MinNeededJobResources;

        YT_LOG_DEBUG(
            "Successful revival result received "
            "(RevivedFromSnapshot: %v, ControlJobLifetimeAtScheduler: %v, RevivedJobCount: %v, RevivedBannedTreeIds: %v, NeededResources: %v)",
            result.RevivedFromSnapshot,
            result.ControlJobLifetimeAtScheduler,
            result.RevivedJobs.size(),
            result.RevivedBannedTreeIds,
            FormatResources(result.NeededResources));
    } else {
        YT_LOG_DEBUG(resultOrError, "Unsuccessful revival result received");
        ProcessControllerAgentError(resultOrError);
    }

    PendingReviveResult_.TrySet(resultOrError);
}

void TOperationControllerImpl::OnCommitFinished(const TErrorOr<TOperationControllerCommitResult>& resultOrError)
{
    YT_VERIFY(PendingCommitResult_);

    if (resultOrError.IsOK()) {
        YT_LOG_DEBUG("Successful commit result received");
    } else {
        YT_LOG_DEBUG(resultOrError, "Unsuccessful commit result received");
        ProcessControllerAgentError(resultOrError);
    }

    PendingCommitResult_.TrySet(resultOrError);
}

void TOperationControllerImpl::SetControllerRuntimeData(const TControllerRuntimeDataPtr& controllerData)
{
    ControllerRuntimeData_ = controllerData;
}

TFuture<void> TOperationControllerImpl::GetFullHeartbeatProcessed()
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    auto agent = Agent_.Lock();
    if (!agent) {
        return VoidFuture;
    }
    return agent->GetFullHeartbeatProcessed();
}

TFuture<TControllerScheduleJobResultPtr> TOperationControllerImpl::ScheduleJob(
    const ISchedulingContextPtr& context,
    const TJobResources& jobLimits,
    const TString& treeId,
    const TString& poolPath,
    const TFairShareStrategyTreeConfigPtr& treeConfig)
{
    VERIFY_THREAD_AFFINITY_ANY();

    auto nodeId = context->GetNodeDescriptor().Id;
    auto cellTag = Bootstrap_->GetClient()->GetNativeConnection()->GetPrimaryMasterCellTag();
    auto jobId = GenerateJobId(cellTag, nodeId);

    const auto& nodeManager = Bootstrap_->GetScheduler()->GetNodeManager();
    const auto shardId = nodeManager->GetNodeShardId(nodeId);
    const auto& nodeShard = nodeManager->GetNodeShards()[shardId];

    if (!nodeShard->IsOperationRegistered(OperationId_)) {
        YT_LOG_DEBUG("Job schedule request cannot be served since operation is not registered at node shard (JobId: %v)",
            jobId);

        auto result = New<TControllerScheduleJobResult>();
        result->RecordFail(NControllerAgent::EScheduleJobFailReason::OperationNotRunning);
        return MakeFuture(std::move(result));
    }

    if (nodeShard->AreNewJobsForbiddenForOperation(OperationId_)) {
        YT_LOG_DEBUG("Job schedule request cannot be served since new jobs are forbidden for operation (JobId: %v)",
            jobId);

        auto result = New<TControllerScheduleJobResult>();
        result->RecordFail(NControllerAgent::EScheduleJobFailReason::NewJobsForbidden);
        return MakeFuture(std::move(result));
    }

    auto request = std::make_unique<TScheduleJobRequest>();
    request->OperationId = OperationId_;
    request->JobId = jobId;
    request->JobResourceLimits = jobLimits;
    request->TreeId = treeId;
    request->PoolPath = poolPath;
    request->NodeId = nodeId;
    request->NodeResourceLimits = context->ResourceLimits();
    request->NodeDiskResources = context->DiskResources();
    request->Spec.WaitingJobTimeout = treeConfig->WaitingJobTimeout;

    TIncarnationId incarnationId;
    {
        auto guard = Guard(SpinLock_);
        if (!IncarnationId_) {
            guard.Release();

            YT_LOG_DEBUG("Job schedule request cannot be served since no agent is assigned (JobId: %v)",
                jobId);

            auto result = New<TControllerScheduleJobResult>();
            result->RecordFail(EScheduleJobFailReason::NoAgentAssigned);

            return MakeFuture(result);
        }

        incarnationId = IncarnationId_;
        ScheduleJobRequestsOutbox_->Enqueue(std::move(request));
    }

    YT_LOG_TRACE("Job schedule request enqueued (JobId: %v, NodeAddress: %v)",
        jobId,
        context->GetNodeDescriptor().Address);

    return nodeShard->BeginScheduleJob(incarnationId, OperationId_, jobId);
}

void TOperationControllerImpl::UpdateMinNeededJobResources()
{
    VERIFY_THREAD_AFFINITY_ANY();

    EnqueueOperationEvent({
        ESchedulerToAgentOperationEventType::UpdateMinNeededJobResources,
        OperationId_
    });
    YT_LOG_DEBUG("Min needed job resources update request enqueued");
}

TCompositeNeededResources TOperationControllerImpl::GetNeededResources() const
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    return ControllerRuntimeData_->GetNeededResources();
}

TJobResourcesWithQuotaList TOperationControllerImpl::GetMinNeededJobResources() const
{
    VERIFY_THREAD_AFFINITY(ControlThread);

    return ControllerRuntimeData_->MinNeededJobResources();
}

EPreemptionMode TOperationControllerImpl::GetPreemptionMode() const
{
    return PreemptionMode_;
}

bool TOperationControllerImpl::ShouldSkipJobEvent(TJobId jobId, TControllerEpoch jobEpoch) const
{
    auto currentEpoch = Epoch_.load();
    if (jobEpoch != currentEpoch) {
        YT_LOG_DEBUG("Job abort notification skipped since controller epoch mismatch (JobId: %v, JobEpoch: %v, CurrentEpoch: %v)",
            jobId,
            jobEpoch,
            currentEpoch);
        return true;
    }
    return false;
}

bool TOperationControllerImpl::ShouldSkipJobEvent(const TJobPtr& job) const
{
    return ShouldSkipJobEvent(job->GetId(), job->GetControllerEpoch());
}

template <class TEvent>
bool TOperationControllerImpl::EnqueueJobEvent(TEvent&& event)
{
    auto guard = Guard(SpinLock_);
    if (IncarnationId_) {
        JobEventsOutbox_->Enqueue(TSchedulerToAgentJobEvent{std::move(event)});
        return true;
    } else {
        // All job notifications must be dropped after agent disconnection.
        // Job revival machinery will reconsider this event further.
        return false;
    }
}

void TOperationControllerImpl::EnqueueOperationEvent(TSchedulerToAgentOperationEvent&& event)
{
    YT_VERIFY(IncarnationId_);
    OperationEventsOutbox_->Enqueue(std::move(event));
}

void TOperationControllerImpl::EnqueueScheduleJobRequest(TScheduleJobRequestPtr&& event)
{
    YT_VERIFY(IncarnationId_);
    ScheduleJobRequestsOutbox_->Enqueue(std::move(event));
}

void TOperationControllerImpl::ProcessControllerAgentError(const TError& error)
{
    if (IsAgentDisconnectionError(error)) {
        auto agent = Agent_.Lock();
        if (!agent) {
            throw TFiberCanceledException();
        }
        const auto& agentTracker = Bootstrap_->GetControllerAgentTracker();
        agentTracker->HandleAgentFailure(agent, error);
    }
}

template <class TResponse, class TRequest>
TFuture<TIntrusivePtr<TResponse>> TOperationControllerImpl::InvokeAgent(
    const TIntrusivePtr<TRequest>& request)
{
    auto agent = Agent_.Lock();
    if (!agent) {
        throw NConcurrency::TFiberCanceledException();
    }
    auto method = request->GetMethod();

    YT_LOG_DEBUG("Sending request to agent (AgentId: %v, IncarnationId: %v, OperationId: %v, Method: %v)",
        agent->GetId(),
        agent->GetIncarnationId(),
        OperationId_,
        method);

    ToProto(request->mutable_incarnation_id(), agent->GetIncarnationId());

    return request->Invoke().Apply(BIND([
        agent,
        method,
        operationId=OperationId_,
        Logger=Logger,
        agentTracker=Bootstrap_->GetControllerAgentTracker()
    ] (const TErrorOr<TIntrusivePtr<TResponse>>& rspOrError) {
        YT_LOG_DEBUG(rspOrError, "Agent response received (AgentId: %v, OperationId: %v, Method: %v)",
            agent->GetId(),
            operationId,
            method);
        if (IsAgentFailureError(rspOrError) || IsAgentDisconnectionError(rspOrError)) {
            agentTracker->HandleAgentFailure(agent, rspOrError);
            // Unregistration should happen before actions that subscribed on this result.
            return rspOrError.ValueOrThrow();
        } else if (rspOrError.GetCode() == NControllerAgent::EErrorCode::AgentCallFailed) {
            YT_VERIFY(rspOrError.InnerErrors().size() == 1);
            THROW_ERROR rspOrError.InnerErrors()[0];
        } else {
            return rspOrError.ValueOrThrow();
        }
    }));
}

std::pair<NApi::ITransactionPtr, TString> TOperationControllerImpl::GetIntermediateMediumTransaction()
{
    return {nullptr, {}};
}

void TOperationControllerImpl::UpdateIntermediateMediumUsage(i64 /*usage*/)
{
    YT_UNIMPLEMENTED();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NScheduler
