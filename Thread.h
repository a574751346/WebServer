//包装了线程类
#pragma once
#if __linux
#include <sys/syscall.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>       // Or something like it. 
#endif
#include "noncopyable.h"
#include "CountDownLatch.h"
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <unistd.h>

class Thread: noncopyable
{
public:
    typedef std::function<void ()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const std::string& name = std::string());
    ~Thread();
    void start();
    int join();
    bool started() const {return started_;}
    pid_t tid() const {return tid_;}
    const std::string& name() const {return name_;}
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;
};