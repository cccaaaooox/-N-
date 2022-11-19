#include<iostream>
using namespace std;


template<typename T>
class UniquePtr {
private:
    T* ptr;
public:
    // 构造函数获取资源
    UniquePtr(T* p = nullptr) : ptr(p) {}

    // 移动构造函数 - 实现资源的权限转移
    UniquePtr(UniquePtr&& up)
    {
        // up的资源释放给this
        ptr = up.release();
    }

    // 移动赋值函数 - 实现资源的权限转移，
    // 注意返回值是左值引用，可以实现连等功能
    // 参数是拷贝的对象
    UniquePtr& operator=(UniquePtr rhs) 
    {
        // 交换实现
        ths.swap(*this);
        return *this;
    }

    // 类似指针的操作
    T& operator*() {return *ptr;}
    T* operator->() {return ptr;}

    // 注意opertor bool没有返回值
    operator bool() {return ptr;}

    // 实现父子类之间的继承关系
    // 实现强制类型转化

    // 析构函数
    ~UniquePtr() {
        // 释放资源
        delete ptr;
        ptr = nullptr;
    }

    // get：返回普通指针的接口
    T* get() {return ptr;}

    // release：实现资源释放的接口
    T* release() 
    {
        T* tmp = ptr;
        delete ptr;
        ptr = nullptr;
        return tmp;
    }
private:
    // 实现资源交换
    void swap(UniquePtr&& up)
    {
        std::swap(up.ptr, ptr);
    }
private:
    // 拷贝构造函数，赋值构造函数 - 禁止拷贝，拒绝多个对象管理同一个资源
    UniquePtr(const UniquePtr& up) = delete;
    UniquePtr& operator=(const UniquePtr& up) = delete;
};