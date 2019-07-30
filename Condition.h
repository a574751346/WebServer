// pthread_cond_wait(&cond, &mutex)为什么要传入一个mutex互斥量？
// 首先理解下pthread_cond_wait的操作
// 1. 将mutex解锁
// 2. 阻塞等待cond条件
// 3. 将mutex加锁
// 其次，也是最重要的！！要理解如何使用pthread_cond_signal
// 1. 将mutex加锁
// 2. 更改while判断条件
// 3. 将mutex解锁
// 4. pthread_cond_signal
// 总结下为啥要这样做
// 个人理解时为了同步 wait 和 signal/broadcast 之间的顺序，使得wait的线程之后能够被唤醒

// ------------------------------------------------------------------------------

// Condition类封装了pthread_cond_t的一系列操作
// 构造函数 对应 初始化 pthread_cond_init
// 析构函数 对应 销毁 pthread_cond_destroy
// wait()成员函数 对应 pthread_cond_wait
// notify == signal ; notifyAll == broadcast

// ------------------------------------------------------------------------------

// struct timespec abstime; 
// https://blog.csdn.net/liu44235/article/details/37692635
// 获取纳秒精度的时间，使用clock_gettime(clock_id, struct timespec*)
// struct timeval xxxx;
// 获取微秒精度的时间，使用 int gettimeofday(struct timeval*, struct timezone *tz); 

// ------------------------------------------------------------------------------

#pragma once
#include "MutexLock.h"
#include "noncopyable.h"
#include <pthread.h>
#include <errno.h>
#include <cstdint>
#include <time.h>

class Condition: noncopyable // 不可拷贝类
{
public:
    explicit Condition(MutexLock &mutex_): // 使用一个MutexLock类来初始化Condition类
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
    void waitForSeconds(int seconds)
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