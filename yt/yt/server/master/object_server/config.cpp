#include "config.h"

#include <yt/yt/core/ytree/request_complexity_limiter.h>

namespace NYT::NObjectServer {

using namespace NYTree;

////////////////////////////////////////////////////////////////////////////////

void TMutationIdempotizerConfig::Register(TRegistrar registrar)
{
    registrar.Parameter("enabled", &TThis::Enabled)
        .Default(true);
    registrar.Parameter("expiration_time", &TThis::ExpirationTime)
        .Default(TDuration::Minutes(5));
    registrar.Parameter("expiration_check_period", &TThis::ExpirationCheckPeriod)
        .Default(TDuration::Seconds(10));
    registrar.Parameter("max_expired_mutation_id_removals_per_commit", &TThis::MaxExpiredMutationIdRemovalsPerCommit)
        .Default(50000);
}

DEFINE_REFCOUNTED_TYPE(TMutationIdempotizerConfig)

////////////////////////////////////////////////////////////////////////////////

void TDynamicObjectManagerConfig::Register(TRegistrar registrar)
{
    registrar.Parameter("max_weight_per_gc_sweep", &TThis::MaxWeightPerGCSweep)
        .Default(100000);
    registrar.Parameter("gc_sweep_period", &TThis::GCSweepPeriod)
        .Default(TDuration::MilliSeconds(1000));
    registrar.Parameter("object_removal_cells_sync_period", &TThis::ObjectRemovalCellsSyncPeriod)
        .Default(TDuration::MilliSeconds(100));
    registrar.Parameter("mutation_idempotizer", &TThis::MutationIdempotizer)
        .DefaultNew();
    registrar.Parameter("reserved_attributes", &TThis::ReservedAttributes)
        .Default();
    registrar.Parameter("yson_string_intern_length_threshold", &TThis::YsonStringInternLengthThreshold)
        .Default(DefaultYsonStringInternLengthThreshold)
        .InRange(DefaultYsonStringInternLengthThreshold, 1_GB);
    registrar.Parameter("profiling_period", &TThis::ProfilingPeriod)
        .Default(DefaultProfilingPeriod);
}

DEFINE_REFCOUNTED_TYPE(TDynamicObjectManagerConfig)

////////////////////////////////////////////////////////////////////////////////

void TObjectServiceConfig::Register(TRegistrar registrar)
{
    registrar.Parameter("yield_timeout", &TThis::YieldTimeout)
        .Default(TDuration::MilliSeconds(10));

    registrar.Parameter("sticky_user_error_expire_time", &TThis::StickyUserErrorExpireTime)
        .Default(TDuration::Seconds(1));

    registrar.Parameter("cross_cell_sync_delay", &TThis::CrossCellSyncDelay)
        .Default(TDuration::MilliSeconds(10));

    registrar.Parameter("timeout_backoff_lead_time", &TThis::TimeoutBackoffLeadTime)
        .Default(TDuration::Seconds(3));
    registrar.Parameter("default_execute_timeout", &TThis::DefaultExecuteTimeout)
        .Default(TDuration::Seconds(30));
    registrar.Parameter("forwarded_request_timeout_reserve", &TThis::ForwardedRequestTimeoutReserve)
        .Default(TDuration::Seconds(3));

    registrar.Parameter("master_cache", &TThis::MasterCache)
        .DefaultNew();

    registrar.Parameter("enable_local_read_executor", &TThis::EnableLocalReadExecutor)
        .Default(false);
    registrar.Parameter("enable_local_read_busy_wait", &TThis::EnableLocalReadBusyWait)
        .Default(true);
}

DEFINE_REFCOUNTED_TYPE(TObjectServiceConfig)

////////////////////////////////////////////////////////////////////////////////

void TReadRequestComplexityLimitsConfig::RegisterParameters(
    TRegistrar registrar,
    const TReadRequestComplexity& defaults)
{
    registrar.Parameter("node_count", &TThis::NodeCount)
        .Default(defaults.NodeCount);
    registrar.Parameter("result_size", &TThis::ResultSize)
        .Default(defaults.ResultSize);
};

void TReadRequestComplexityLimitsConfig::ToReadRequestComplexity(TReadRequestComplexity& limits) const
{
    limits.NodeCount = NodeCount;
    limits.ResultSize = ResultSize;
}

void TDefaultReadRequestComplexityLimitsConfig::Register(TRegistrar registrar)
{
    RegisterParameters(
        registrar,
        TReadRequestComplexity(/*nodeCount*/ 100'000, /*resultSize*/ 50'000'000));
}

void TMaxReadRequestComplexityLimitsConfig::Register(TRegistrar registrar)
{
    RegisterParameters(
        registrar,
        TReadRequestComplexity(/*nodeCount*/ 1'000'000, /*resultSize*/ 5000000000ULL));
}

////////////////////////////////////////////////////////////////////////////////

void TDynamicObjectServiceConfig::Register(TRegistrar registrar)
{
    registrar.Parameter("enable_two_level_cache", &TThis::EnableTwoLevelCache)
        .Default(true);
    registrar.Parameter("enable_local_read_executor", &TThis::EnableLocalReadExecutor)
        .Default(false);
    registrar.Parameter("local_read_worker_count", &TThis::LocalReadWorkerCount)
        .GreaterThan(0)
        .Default(4);
    registrar.Parameter("schedule_reply_retry_backoff", &TThis::ScheduleReplyRetryBackoff)
        .Default(TDuration::MilliSeconds(100));

    registrar.Parameter("local_read_executor_quantum_duration", &TThis::LocalReadExecutorQuantumDuration)
        .Default(TDuration::MilliSeconds(10));

    registrar.Parameter("process_sessions_period", &TThis::ProcessSessionsPeriod)
        .Default(TDuration::MilliSeconds(10));

    registrar.Parameter("default_read_request_complexity_limits", &TThis::DefaultReadRequestComlexityLimits)
        .DefaultCtor([] { return New<TDefaultReadRequestComplexityLimitsConfig>(); });

    registrar.Parameter("max_read_request_complexity_limits", &TThis::MaxReadRequestComplexityLimits)
        .DefaultCtor([] { return New<TMaxReadRequestComplexityLimitsConfig>(); });
}

DEFINE_REFCOUNTED_TYPE(TDynamicObjectServiceConfig)

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NObjectServer
