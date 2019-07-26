//先搞了一个MutexLock封装mutex操作，封装成lock，unlock，get操作
//之后用MutexLockGuard封装MutexLock的方法，起保护作用
#pragma once
#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>

class MutexLock: noncopyable
{
public:
    MutexLock() 
    {
        pthread_mutex_init(&mutex, NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_t* get()
    {
        return &mutex;
    }
private:
    pthread_mutex_t mutex;

//友元类不受访问权限影响
private:
    friend class Contition;
};

class MutexLockGuard: noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex_):
    mutex(mutex_)
    {
        mutex.lock();
    }
    ~MutexLockGuard()
    {
        mutex.unlock();
    }
private:
    MutexLock &mutex;
};