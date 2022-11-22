
#include<iostream>
#include<memory>
using namespace std;

// weak_ptr：
//    1,临时所有权，当某个对象只有存在时才需要被访问，
//      而且随时可能被他人删除时，可以用weak_ptr来跟踪该对象。
//    2,打破shared_ptr所管理对象组成的循环引用，weak_ptr并不增加引用计数。


template<typename T>
class WeakPtr {
private:
    T* ptr;

public:
    template<typename Y>
    friend class WeakPtr;


    WeakPtr() : ptr(nullptr) {}

    WeakPtr(const WeakPtr& other) {
        ptr = other.ptr;
    }

    template<typename Y>
    WeakPtr(const std::WeakPtr<Y>& r) {
        ptr = r.ptr;
    }

    template<typename Y>
    WeakPtr(const std::SharedPtr<Y>& r) {}


    WeakPtr(WeakPtr&& other) {}
    
    template<typename Y>
    WeakPtr(WeakPtr<Y>&& other) {}

    ~WeakPtr() {}

    void reset() {}

    void swap(WeakPtr& r) {}

    long use_count() {}

    bool expiread() {}
};