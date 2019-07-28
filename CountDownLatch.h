#pragma once
#include "MutexLock.h"
#include "Condition.h"
#include "noncopyable.h"

class CountDownLatch: noncopyable
{
public:
    explicit CountDownLatch(int count_);
    void wait();
    void countDown();
private:
    mutable MutexLock mutex;
    Condition condition;
    int count;
};