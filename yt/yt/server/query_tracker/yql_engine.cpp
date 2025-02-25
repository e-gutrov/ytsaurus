#include "yql_engine.h"

#include "config.h"
#include "handler_base.h"

#include <yt/yt/ytlib/query_tracker_client/records/query.record.h>

#include <yt/yt/ytlib/api/native/client.h>
#include <yt/yt/ytlib/api/native/connection.h>

#include <yt/yt/ytlib/yql_client/yql_service_proxy.h>

#include <yt/yt/core/ytree/convert.h>
#include <yt/yt/core/ytree/attributes.h>

#include <yt/yt/core/rpc/public.h>

namespace NYT::NQueryTracker {

using namespace NQueryTrackerClient;
using namespace NApi;
using namespace NYPath;
using namespace NHiveClient;
using namespace NYTree;
using namespace NRpc;
using namespace NYqlClient;
using namespace NYqlClient::NProto;
using namespace NYson;

///////////////////////////////////////////////////////////////////////////////

class TYqlSettings
    : public TYsonStruct
{
public:
    TString Stage;

    REGISTER_YSON_STRUCT(TYqlSettings);

    static void Register(TRegistrar registrar)
    {
        registrar.Parameter("stage", &TThis::Stage)
            .Default("production");
    }
};

DEFINE_REFCOUNTED_TYPE(TYqlSettings);
DECLARE_REFCOUNTED_CLASS(TYqlSettings);

///////////////////////////////////////////////////////////////////////////////

class TYqlQueryHandler
    : public TQueryHandlerBase
{
public:
    TYqlQueryHandler(
        const NApi::IClientPtr& stateClient,
        const NYPath::TYPath& stateRoot,
        const TEngineConfigBasePtr& config,
        const NQueryTrackerClient::NRecords::TActiveQuery& activeQuery,
        const NApi::NNative::IConnectionPtr& connection)
        : TQueryHandlerBase(stateClient, stateRoot, config, activeQuery)
        , Query_(activeQuery.Query)
        , Connection_(connection)
        , Settings_(ConvertTo<TYqlSettingsPtr>(SettingsNode_))
    { }

    void Start() override
    {
        YT_LOG_DEBUG("Starting YQL query (Stage: %v)", Settings_->Stage);

        TYqlServiceProxy proxy(Connection_->GetYqlAgentChannelOrThrow(Settings_->Stage));
        auto req = proxy.StartQuery();
        auto* yqlRequest = req->mutable_yql_request();
        req->set_row_count_limit(Config_->RowCountLimit);
        yqlRequest->set_query(Query_);
        req->set_build_rowsets(true);
        AsyncQueryResult_  = req->Invoke();
        AsyncQueryResult_.Subscribe(BIND(&TYqlQueryHandler::OnYqlResponse, MakeWeak(this)).Via(GetCurrentInvoker()));
    }

    void Abort() override
    {
        // Nothing smarter than that for now.
        AsyncQueryResult_.Cancel(TError("Query aborted"));
    }

    void Detach() override
    {
        // Nothing smarter than that for now.
        AsyncQueryResult_.Cancel(TError("Query detached"));
    }

private:
    TString Query_;
    NApi::NNative::IConnectionPtr Connection_;
    TYqlSettingsPtr Settings_;

    TFuture<TTypedClientResponse<TRspStartQuery>::TResult> AsyncQueryResult_;

    void OnYqlResponse(const TErrorOr<TTypedClientResponse<TRspStartQuery>::TResult>& rspOrError)
    {
        if (rspOrError.FindMatching(NYT::EErrorCode::Canceled)) {
            return;
        }
        if (!rspOrError.IsOK()) {
            OnQueryFailed(rspOrError);
            return;
        }
        const auto& rsp = rspOrError.Value();
        auto optionalPlan = rsp->yql_response().has_plan() ? std::make_optional(TYsonString(rsp->yql_response().plan())) : std::nullopt;
        auto optionalStatistics = rsp->yql_response().has_statistics() ? std::make_optional(TYsonString(rsp->yql_response().statistics())) : std::nullopt;
        auto optionalTaskInfo = rsp->yql_response().has_task_info() ? std::make_optional(TYsonString(rsp->yql_response().task_info())) : std::nullopt;
        auto progress = BuildYsonStringFluently()
            .BeginMap()
                .OptionalItem("yql_plan", optionalPlan)
                .OptionalItem("yql_statistics", optionalStatistics)
                .OptionalItem("yql_task_info", optionalTaskInfo)
            .EndMap();
        OnProgress(progress);
        std::vector<TErrorOr<TSharedRef>> wireRowsetOrErrors;
        for (int index = 0; index < rsp->rowset_errors_size(); ++index) {
            auto error = FromProto<TError>(rsp->rowset_errors()[index]);
            if (error.IsOK()) {
                wireRowsetOrErrors.push_back(rsp->Attachments()[index]);
            } else {
                wireRowsetOrErrors.push_back(error);
            }
        }
        OnQueryCompletedWire(wireRowsetOrErrors);
    }
};

class TYqlEngine
    : public IQueryEngine
{
public:
    TYqlEngine(IClientPtr stateClient, TYPath stateRoot)
        : StateClient_(std::move(stateClient))
        , StateRoot_(std::move(stateRoot))
    { }

    IQueryHandlerPtr StartOrAttachQuery(NRecords::TActiveQuery activeQuery) override
    {
        return New<TYqlQueryHandler>(
            StateClient_,
            StateRoot_,
            Config_,
            activeQuery,
            DynamicPointerCast<NNative::IConnection>(StateClient_->GetConnection()));
    }

    void OnDynamicConfigChanged(const TEngineConfigBasePtr& config) override
    {
        Config_ = config;
    }

private:
    const IClientPtr StateClient_;
    const TYPath StateRoot_;
    TEngineConfigBasePtr Config_;
    TClusterDirectoryPtr ClusterDirectory_;
};

IQueryEnginePtr CreateYqlEngine(const IClientPtr& stateClient, const TYPath& stateRoot)
{
    return New<TYqlEngine>(stateClient, stateRoot);
}

///////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NQueryClient
