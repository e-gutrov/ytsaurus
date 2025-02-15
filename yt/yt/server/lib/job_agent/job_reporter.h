#pragma once

#include <yt/yt/server/lib/job_agent/public.h>

#include <yt/yt/ytlib/table_client/public.h>
#include <yt/yt/ytlib/api/native/public.h>

#include <yt/yt/client/api/public.h>
#include <yt/yt/client/api/operation_archive_schema.h>

#include <yt/yt/core/yson/string.h>

#include <optional>

namespace NYT::NJobAgent {

////////////////////////////////////////////////////////////////////////////////

//! Periodically reports job statistics to the dynamic table.
class TJobReporter
    : public TRefCounted
{
public:
    TJobReporter(
        TJobReporterConfigPtr reporterConfig,
        const NApi::NNative::IConnectionPtr& connection,
        std::optional<TString> localAddress = {});

    ~TJobReporter();

    void HandleJobReport(TJobReport&& statistics);
    void SetOperationArchiveVersion(int version);
    int ExtractWriteFailuresCount();
    bool GetQueueIsTooLarge();

    // For updates by original config changes (CA).
    void UpdateConfig(const TJobReporterConfigPtr& config);

    // For updates by dynamic config patch (Node).
    void OnDynamicConfigChanged(
        const TJobReporterDynamicConfigPtr& oldConfig,
        const TJobReporterDynamicConfigPtr& newConfig);

private:
    class TImpl;
    const TIntrusivePtr<TImpl> Impl_;
};

DEFINE_REFCOUNTED_TYPE(TJobReporter)

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NJobAgent
