#include "sensor_set.h"
#include "private.h"

#include <library/cpp/yt/assert/assert.h>

#include <library/cpp/monlib/metrics/summary_snapshot.h>

namespace NYT::NProfiling {

using namespace NYTree;

////////////////////////////////////////////////////////////////////////////////

const static auto& Logger = SolomonLogger;

////////////////////////////////////////////////////////////////////////////////

TSensorSet::TSensorSet(TSensorOptions options, i64 iteration, int windowSize, int gridFactor)
    : Options_(options)
    , GridFactor_(gridFactor)
    , CountersCube_{windowSize, iteration}
    , TimeCountersCube_{windowSize, iteration}
    , GaugesCube_{windowSize, iteration}
    , SummariesCube_{windowSize, iteration}
    , TimersCube_{windowSize, iteration}
    , HistogramsCube_{windowSize, iteration}
    , GaugeHistogramsCube_{windowSize, iteration}
{ }

bool TSensorSet::IsEmpty() const
{
    return Counters_.empty() &&
        Gauges_.empty() &&
        Summaries_.empty() &&
        Timers_.empty() &&
        Histograms_.empty() &&
        GaugeHistograms_.empty();
}

void TSensorSet::Profile(const TProfiler &profiler)
{
    CubeSize_ = profiler.Gauge("/cube_size");
    SensorsEmitted_ = profiler.Gauge("/sensors_emitted");
}

void TSensorSet::ValidateOptions(TSensorOptions options)
{
    if (!Options_.IsCompatibleWith(options)) {
        OnError(TError("Conflicting sensor settings")
            << TErrorAttribute("current", ToString(Options_))
            << TErrorAttribute("provided", ToString(options)));
    }
}

void TSensorSet::AddCounter(TCounterStatePtr counter)
{
    InitializeType(ESensorType::Counter);
    CountersCube_.AddAll(counter->TagIds, counter->Projections);
    Counters_.emplace(std::move(counter));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddGauge(TGaugeStatePtr gauge)
{
    InitializeType(ESensorType::Gauge);
    GaugesCube_.AddAll(gauge->TagIds, gauge->Projections);
    Gauges_.emplace(std::move(gauge));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddSummary(TSummaryStatePtr summary)
{
    InitializeType(ESensorType::Summary);
    SummariesCube_.AddAll(summary->TagIds, summary->Projections);
    Summaries_.emplace(std::move(summary));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddTimerSummary(TTimerSummaryStatePtr timer)
{
    InitializeType(ESensorType::Timer);
    TimersCube_.AddAll(timer->TagIds, timer->Projections);
    Timers_.emplace(std::move(timer));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddTimeCounter(TTimeCounterStatePtr counter)
{
    InitializeType(ESensorType::TimeCounter);
    TimeCountersCube_.AddAll(counter->TagIds, counter->Projections);
    TimeCounters_.emplace(std::move(counter));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddHistogram(THistogramStatePtr histogram)
{
    InitializeType(ESensorType::Histogram);
    HistogramsCube_.AddAll(histogram->TagIds, histogram->Projections);
    Histograms_.emplace(std::move(histogram));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::AddGaugeHistogram(THistogramStatePtr histogram)
{
    InitializeType(ESensorType::GaugeHistogram);
    GaugeHistogramsCube_.AddAll(histogram->TagIds, histogram->Projections);
    GaugeHistograms_.emplace(std::move(histogram));
    CubeSize_.Update(GetCubeSize());
}

void TSensorSet::RenameDynamicTag(const TDynamicTagPtr& dynamicTag, TTagId newTag)
{
    auto doRename = [&] (auto& cube, const auto& sensors) {
        for (const auto& sensor : sensors) {
            for (auto [tag, index] : sensor->Projections.DynamicTags()) {
                if (tag == dynamicTag) {
                    cube.RemoveAll(sensor->TagIds, sensor->Projections);
                    sensor->TagIds[index] = newTag;
                    cube.AddAll(sensor->TagIds, sensor->Projections);
                }
            }
        }
    };

    doRename(CountersCube_, Counters_);
    doRename(GaugesCube_, Gauges_);
    doRename(SummariesCube_, Summaries_);
    doRename(TimersCube_, Timers_);
    doRename(HistogramsCube_, Histograms_);
    doRename(GaugeHistogramsCube_, GaugeHistograms_);
}

int TSensorSet::Collect()
{
    int count = 0;

    auto collect = [&] (auto& set, auto& cube, auto doRead) {
        using TElement = typename std::remove_reference_t<decltype(set)>::key_type;

        std::deque<TElement> toRemove;

        cube.StartIteration();
        for (const auto& counter : set) {
            auto [value, ok] = doRead(counter);
            if (!ok) {
                toRemove.push_back(counter);
                continue;
            }

            if (Options_.Sparse && IsZeroValue(value)) {
                continue;
            }

            counter->Projections.Range(counter->TagIds, [&, value=value] (auto tags) {
                cube.Update(std::move(tags), value);
            });
        }
        cube.FinishIteration();

        for (const auto& removed : toRemove) {
            cube.RemoveAll(removed->TagIds, removed->Projections);
            set.erase(removed);
        }

        count += cube.GetProjections().size();
    };

    collect(Counters_, CountersCube_, [] (auto counter) -> std::pair<i64, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {0, false};
        }

        try {
            auto value = counter->Reader();

            auto delta = value - counter->LastValue;
            counter->LastValue = value;
            return {delta, true};
        } catch (const std::exception& ex) {
            YT_LOG_ERROR(ex, "Counter read failed");
            return {0, false};
        }
    });

    collect(TimeCounters_, TimeCountersCube_, [] (auto counter) -> std::pair<TDuration, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {TDuration::Zero(), false};
        }

        auto value = owner->GetValue();

        auto delta = value - counter->LastValue;
        counter->LastValue = value;
        return {delta, true};
    });

    collect(Gauges_, GaugesCube_, [] (auto counter) -> std::pair<double, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {0, false};
        }

        try {
            auto value = counter->Reader();

            return {value, true};
        } catch (const std::exception& ex) {
            YT_LOG_ERROR(ex, "Gauge read failed");
            return {0, false};
        }
    });

    collect(Summaries_, SummariesCube_, [] (auto counter) -> std::pair<TSummarySnapshot<double>, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {{}, false};
        }

        auto value = owner->GetSummaryAndReset();
        return {value, true};
    });

    collect(Timers_, TimersCube_, [] (auto counter) -> std::pair<TSummarySnapshot<TDuration>, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {{}, false};
        }

        auto value = owner->GetSummaryAndReset();
        return {value, true};
    });

    collect(Histograms_, HistogramsCube_, [] (auto counter) -> std::pair<THistogramSnapshot, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {{}, false};
        }

        auto value = owner->GetSnapshot();
        owner->Reset();
        return {value, true};
    });

    collect(GaugeHistograms_, GaugeHistogramsCube_, [] (auto counter) -> std::pair<TGaugeHistogramSnapshot, bool> {
        auto owner = counter->Owner.Lock();
        if (!owner) {
            return {{}, false};
        }

        auto value = owner->GetSnapshot();
        return {value, true};
    });

    return count;
}

void TSensorSet::ReadSensors(
    const TString& name,
    const TReadOptions& options,
    TTagWriter* tagWriter,
    ::NMonitoring::IMetricConsumer* consumer) const
{
    if (!Error_.IsOK()) {
        return;
    }

    auto readOptions = options;
    readOptions.Sparse = Options_.Sparse;
    readOptions.Global = Options_.Global;
    readOptions.DisableSensorsRename = Options_.DisableSensorsRename;
    readOptions.DisableDefault = Options_.DisableDefault;

    int sensorsEmitted = 0;

    sensorsEmitted += CountersCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += TimeCountersCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += GaugesCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += SummariesCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += TimersCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += HistogramsCube_.ReadSensors(name, readOptions, tagWriter, consumer);
    sensorsEmitted += GaugeHistogramsCube_.ReadSensors(name, readOptions, tagWriter, consumer);

    SensorsEmitted_.Update(sensorsEmitted);
}

int TSensorSet::ReadSensorValues(
    const TTagIdList& tagIds,
    int index,
    const TReadOptions& options,
    const TTagRegistry& tagRegistry,
    TFluentAny fluent) const
{
    if (!Error_.IsOK()) {
        THROW_ERROR_EXCEPTION("Broken sensor")
            << Error_;
    }

    int valuesRead = 0;
    valuesRead += CountersCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += TimeCountersCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += GaugesCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += SummariesCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += TimersCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += HistogramsCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);
    valuesRead += GaugeHistogramsCube_.ReadSensorValues(tagIds, index, options, tagRegistry, fluent);

    return valuesRead;
}

int TSensorSet::GetGridFactor() const
{
    return GridFactor_;
}

int TSensorSet::GetObjectCount() const
{
    return Counters_.size() +
        TimeCounters_.size() +
        Gauges_.size() +
        Summaries_.size() +
        Timers_.size() +
        Histograms_.size() +
        GaugeHistograms_.size();
}

int TSensorSet::GetCubeSize() const
{
    return CountersCube_.GetSize() +
        TimeCountersCube_.GetSize() +
        GaugesCube_.GetSize() +
        SummariesCube_.GetSize() +
        TimersCube_.GetSize() +
        HistogramsCube_.GetSize() +
        GaugeHistogramsCube_.GetSize();
}

const TError& TSensorSet::GetError() const
{
    return Error_;
}

std::optional<ESensorType> TSensorSet::GetType() const
{
    return Type_;
}

void TSensorSet::OnError(TError error)
{
    if (Error_.IsOK()) {
        Error_ = std::move(error);
    }
}

void TSensorSet::InitializeType(ESensorType type)
{
    if (Options_.DisableProjections) {
        return;
    }

    if (Type_ && *Type_ != type) {
        OnError(TError("Conflicting sensor types")
            << TErrorAttribute("expected", *Type_)
            << TErrorAttribute("provided", type));
    }

    if (!Type_) {
        Type_ = type;
    }
}

void TSensorSet::DumpCube(NProto::TCube *cube) const
{
    cube->set_sparse(Options_.Sparse);
    cube->set_global(Options_.Global);
    cube->set_disable_default(Options_.DisableDefault);
    cube->set_disable_sensors_rename(Options_.DisableSensorsRename);

    CountersCube_.DumpCube(cube);
    TimeCountersCube_.DumpCube(cube);
    GaugesCube_.DumpCube(cube);
    SummariesCube_.DumpCube(cube);
    TimersCube_.DumpCube(cube);
    HistogramsCube_.DumpCube(cube);
    GaugeHistogramsCube_.DumpCube(cube);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NProfiling
