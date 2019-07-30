//定义不可拷贝类型
//只放开了默认构造函数和默认析构函数
//将拷贝构造函数和赋值运算符设为private
#pragma once

class noncopyable
{
protected:
    noncopyable() {} // 默认构造函数
    ~noncopyable() {} // 默认析构函数
private:
    noncopyable(const noncopyable&); // 拷贝构造函数
    const noncopyable& operator=(const noncopyable&); // 赋值运算符
};