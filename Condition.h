#pragma once
#include "MutexLock.h"
#include "noncopyable.h"
#include <pthread.h>
#include <errno.h>
#include <cstdint>
#include <time.h>

class Condition: noncopyable
{
public:
    explicit Condition(MutexLock &mutex_):
        mutex(mutex_)
    {
        pthread_cond_init(&cond, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&cond);
    }
    void wait() 
    {
        pthread_cond_wait(&cond, mutex.get());
    }
    void notify()
    {
        pthread_cond_signal(&cond);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&cond);
    }
    void waitForSecond(int seconds)
    {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        //return  pthread_cond_timedwait(&cond, mutex.get(), &abstime) == ETIMEDOUT;
        return;
    }
private:
    MutexLock &mutex;
    pthread_cond_t cond;
};