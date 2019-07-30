//先搞了一个MutexLock封装mutex操作，封装成lock，unlock，get操作
//之后用MutexLockGuard封装MutexLock的方法，起保护作用，类出了作用域之后析构时自动unlock mutex，更保险
#pragma once
#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>

class MutexLock: noncopyable
{
public:
    MutexLock() // 默认构造函数
    {
        pthread_mutex_init(&mutex, NULL);
    }
    ~MutexLock() //析构函数
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    void lock() // 加锁
    {
        pthread_mutex_lock(&mutex);
    }
    void unlock() // 解锁
    {
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_t* get() // 获取互斥量
    {
        return &mutex;
    }
private:
    pthread_mutex_t mutex; // 私有变量：互斥量

//友元类不受访问权限影响
private:
    friend class Contition; // 条件变量访问MutexLock类不受权限约束
};

class MutexLockGuard: noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex_): // 构造函数，防止隐式转换的发生
    mutex(mutex_)
    {
        mutex.lock(); // 对mutex加锁
    }
    ~MutexLockGuard()
    {
        mutex.unlock(); // 析构式自动解锁
    }
private:
    MutexLock &mutex; // 私有成员变量：MutexLock mutex
};