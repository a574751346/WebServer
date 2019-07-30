//监控多个线程数量变化
#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count):
    mutex_(),
    condition_(mutex_),
    count_(count_)
{

}

void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);
    while (count_ > 0) {
        condition_.wait();
    }
}

void CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0) {
        condition_.notifyAll();
    }
}