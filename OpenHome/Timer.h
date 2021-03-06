#ifndef HEADER_TIMER
#define HEADER_TIMER

#include <OpenHome/Private/Standard.h>
#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Private/Queue.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Functor.h>

namespace OpenHome {

class Time
{
public:
    static TUint Now();
    static TBool IsBeforeOrAt(TUint aQuestionableTime, TUint aTime);
    static TBool IsAfter(TUint aQuestionableTime, TUint aTime);
    static TBool IsInPastOrNow(TUint aTime);
    static TBool IsInFuture(TUint aTime);
    static TInt TimeToWaitFor(TUint aTime);
};

class QueueSortedEntryTimer : public QueueSortedEntry
{
    friend class TimerManager;
protected:
    TUint iTime;  // Absolute (milliseconds from startup)
};

class Timer : public QueueSortedEntryTimer
{
    friend class TimerManager;
public:
    Timer(Functor aFunctor);
    void FireIn(TUint aTime); // Relative (milliseconds from now)
    void FireAt(TUint aTime); // Absolute (at specified millisecond)
    void Cancel();
    ~Timer();
    static TBool IsInManagerThread();
private:
    Functor iFunctor;
};

class TimerManager : public QueueSorted<Timer>
{
    friend class Timer;
public:
    TimerManager();
    void Stop();
    ~TimerManager();
    void CallbackLock();
    void CallbackUnlock();
private:
    void Run();
    void Fire();
    OpenHome::Thread* Thread() const;
    virtual void HeadChanged(QueueSortedEntry& aEntry);
    virtual TInt Compare(QueueSortedEntry& aEntry1, QueueSortedEntry& aEntry2);
private:
    QueueSortedEntryTimer iNow;
    Mutex iMutexNow;
    TBool iRemoving;
    ThreadFunctor* iThread;
    Semaphore iSemaphore;
    Mutex iMutex;
    TUint iNextTimer;
    TBool iStop;
    Semaphore iStopped;
    Mutex iCallbackMutex;
    OpenHome::Thread* iThreadHandle;
};

} // namespace OpenHome

#endif // HEADER_TIMER
