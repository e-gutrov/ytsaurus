#include "thread_pool.h"
#include "notify_manager.h"
#include "single_queue_scheduler_thread.h"
#include "private.h"
#include "profiling_helpers.h"
#include "thread_pool_detail.h"

#include <yt/yt/core/actions/invoker_detail.h>

#include <yt/yt/core/misc/finally.h>

#include <yt/yt/core/ypath/token.h>

namespace NYT::NConcurrency {

using namespace NProfiling;
using namespace NYPath;
using namespace NYTree;

////////////////////////////////////////////////////////////////////////////////

// This routines could be placed in TThreadPool class but it causes a circular ref.
class TInvokerQueueAdapter
    : public TMpmcInvokerQueue
    , public TNotifyManager
{
public:
    TInvokerQueueAdapter(
        TIntrusivePtr<NThreading::TEventCount> callbackEventCount,
        const TTagSet& counterTagSet,
        const TDuration pollingPeriod)
        : TMpmcInvokerQueue(callbackEventCount, counterTagSet)
        , TNotifyManager(callbackEventCount, counterTagSet, pollingPeriod)
    { }

    TClosure OnExecute(TEnqueuedAction* action, bool fetchNext, std::function<bool()> isStopping)
    {
        while (true) {
            int activeThreadDelta = !action->Finished ? -1 : 0;
            TMpmcInvokerQueue::EndExecute(action);

            auto cookie = GetEventCount()->PrepareWait();
            auto minEnqueuedAt = ResetMinEnqueuedAt();

            TClosure callback;
            if (fetchNext) {
                callback = TMpmcInvokerQueue::BeginExecute(action);

                if (callback) {
                    YT_ASSERT(action->EnqueuedAt > 0);
                    minEnqueuedAt = action->EnqueuedAt;
                    activeThreadDelta += 1;
                }
            }

            YT_VERIFY(activeThreadDelta <= 1 && activeThreadDelta >= -1);
            if (activeThreadDelta != 0) {
                auto activeThreads = ActiveThreads_.fetch_add(activeThreadDelta) + activeThreadDelta;
                YT_VERIFY(activeThreads >= 0 && activeThreads <= TThreadPoolBase::MaxThreadCount);
            }

            if (callback || isStopping()) {
                CancelWait();

                NotifyAfterFetch(GetCpuInstant(), minEnqueuedAt);
                return callback;
            }

            Wait(cookie, isStopping);
        }
    }

    void Invoke(TClosure callback) override
    {
        auto cpuInstant = TMpmcInvokerQueue::EnqueueCallback(
            std::move(callback),
            /*profilingTag*/ 0,
            /*profilerTag*/ nullptr);

        NotifyFromInvoke(cpuInstant, ActiveThreads_.load() == 0);
    }

    void Invoke(TMutableRange<TClosure> callbacks) override
    {
        auto cpuInstant = TMpmcInvokerQueue::EnqueueCallbacks(callbacks);
        NotifyFromInvoke(cpuInstant, ActiveThreads_.load() == 0);
    }

private:
    std::atomic<int> ActiveThreads_ = 0;
};

class TThreadPoolThread
    : public TSchedulerThread
{
public:
    TThreadPoolThread(
        TIntrusivePtr<TInvokerQueueAdapter> queue,
        TIntrusivePtr<NThreading::TEventCount> callbackEventCount,
        const TString& threadGroupName,
        const TString& threadName,
        EThreadPriority threadPriority)
        : TSchedulerThread(
            callbackEventCount,
            threadGroupName,
            threadName,
            threadPriority,
            /*shutdownPriority*/ 0)
        , Queue_(std::move(queue))
    { }

protected:
    const TIntrusivePtr<TInvokerQueueAdapter> Queue_;
    TEnqueuedAction CurrentAction_;

    TClosure OnExecute() override
    {
        bool fetchNext = !TSchedulerThread::IsStopping() || TSchedulerThread::GracefulStop_;

        return Queue_->OnExecute(&CurrentAction_, fetchNext, [&] {
            return TSchedulerThread::IsStopping();
        });
    }

    TClosure BeginExecute() override
    {
        Y_UNREACHABLE();
    }

    void EndExecute() override
    {
        Y_UNREACHABLE();
    }
};

class TThreadPool
    : public IThreadPool
    , public TThreadPoolBase
{
public:
    TThreadPool(
        int threadCount,
        const TString& threadNamePrefix,
        EThreadPriority threadPriority,
        const TDuration pollingPeriod)
        : TThreadPoolBase(threadNamePrefix, threadPriority)
        , Queue_(New<TInvokerQueueAdapter>(
            CallbackEventCount_,
            GetThreadTags(ThreadNamePrefix_),
            pollingPeriod))
        , Invoker_(Queue_)
    {
        Configure(threadCount);
    }

    ~TThreadPool()
    {
        Shutdown();
    }

    const IInvokerPtr& GetInvoker() override
    {
        EnsureStarted();
        return Invoker_;
    }

    void Configure(int threadCount) override
    {
        TThreadPoolBase::Configure(threadCount);
    }

    int GetThreadCount() override
    {
        return TThreadPoolBase::GetThreadCount();
    }

    void Shutdown() override
    {
        TThreadPoolBase::Shutdown();
    }

private:
    const TIntrusivePtr<NThreading::TEventCount> CallbackEventCount_ = New<NThreading::TEventCount>();
    const TIntrusivePtr<TInvokerQueueAdapter> Queue_;
    const IInvokerPtr Invoker_;

    void DoShutdown() override
    {
        Queue_->Shutdown();
        TThreadPoolBase::DoShutdown();
    }

    TClosure MakeFinalizerCallback() override
    {
        return BIND_NO_PROPAGATE([queue = Queue_, callback = TThreadPoolBase::MakeFinalizerCallback()] {
            callback();
            queue->DrainConsumer();
        });
    }

    TSchedulerThreadBasePtr SpawnThread(int index) override
    {
        return New<TThreadPoolThread>(
            Queue_,
            CallbackEventCount_,
            ThreadNamePrefix_,
            MakeThreadName(index),
            ThreadPriority_);
    }
};

////////////////////////////////////////////////////////////////////////////////

IThreadPoolPtr CreateThreadPool(
    int threadCount,
    const TString& threadNamePrefix,
    EThreadPriority threadPriority,
    const TDuration pollingPeriod)
{
    return New<TThreadPool>(threadCount, threadNamePrefix, threadPriority, pollingPeriod);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NConcurrency
