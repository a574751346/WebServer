//本文件定义了CurrentThread命名空间，在其中定义了一些【线程名字】和【线程id】等相关【变量及获取方法】
//关于__builtin_expect的用法
//https://www.cnblogs.com/li-hao/archive/2012/02/06/2340094.html
#pragma once
#include <stdint.h>

namespace CurrentThread
{
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;
    void cacheTid();
    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString()
    {
        return t_tidString;
    }

    inline int tidStringLength()
    {
        return t_tidStringLength;
    }

    inline const char* name()
    {
        return t_threadName;
    }
}