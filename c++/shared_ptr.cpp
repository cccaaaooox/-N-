#include<iostream>
using namespace std;


class shared_count {
private:
    long count;
public:
    shared_count() : count(1) {}
    long getCount() {return count;}
    void addCount() {count++;}
    long reduceCount() {return --count;}
};

template<typename T>
class SharedPtr {
private:
    T* ptr;
    shared_count* sharedCount;
public:

    template<typename U>
    friend class smart_ptr;

    // 资源获取，并设置引用计数
    SharedPtr(T* p) : ptr(p) {
        sharedCount = new shared_count;
    }

    // 在引用计数为0时进行资源释放
    ~SharedPtr() {
        if (!sharedCount.reduceCount()) {
            delete ptr;
            delete sharedCount;
            ptr = sharedCount = nullptr;
            
        }
    }

    // 拷贝构造
    SharedPtr(const SharedPtr& sp) {
        ptr = sp.ptr;
        if (ptr) {
            sp.sharedCount->addCount();
            sharedCount = sp.sharedCount;
        }
    }

    // 拷贝赋值
    SharedPtr& operator=(SharedPtr sp) {
        sp.sawp(*this);
        return *this;
    }

    // 移动拷贝构造 ？ 可有可无
    // 移动赋值 ？可有可无
    template<typename U>
    SharedPtr(const SharedPtr<U>& other)
    {
        ptr = other.ptr;
        if (ptr) {
            other.sharedCount->addCount();
            sharedCount = other.sharedCount;
        }
    }

    template<typename U>
    SharedPtr(SharedPtr<U>&& other) 
    {
        ptr = other.ptr;
        if (ptr) {
            sharedCount = other.sharedCount;
            other.ptr = nullptr;
        }
    }

    template<typename U>
    SharedPtr(const SharedPtr<U>& other, T* p)
    {
        ptr = p;
        if (ptr) {
            other.sharedCount->addCount();
            sharedCount = other.sharedCount;
        }
    }

    T* get() {return ptr;}
    T& operator*() {return *ptr;}
    T* operator->() {return ptr;}
    operator bool() {return ptr;} 

    long use_count() {
        if (ptr) {
            return sharedCount->getCount();
        }
        return 0;
    }


private:
    void swap(SharedPtr& sp) {
        using std::sawp;
        swap(sp.ptr, ptr);
        swap(sp.sharedCount, sharedCount);
    }

};


template<typename T, typename U>
SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U>& other)
{
    T* ptr = dynamic_cast<T*>(other.get());
    return SharedPtr<T>(other, ptr); 
}

template<typename T, typename U>
SharedPtr<T> static_pointer_cast(const SharedPtr<U>& other)
{
    T* ptr = static_cast<T*>(other.get());
    return SharedPtr<T>(other, ptr); 
}

template<typename T, typename U>
SharedPtr<T> reinterpret_pointer_cast(const SharedPtr<U>& other)
{
    T* ptr = reinterpret_cast<T*>(other.get());
    return SharedPtr<T>(other, ptr); 
}

template<typename T, typename U>
SharedPtr<T> const_pointer_cast(const SharedPtr<U>& other)
{
    T* ptr = const_cast<T*>(other.get());
    return SharedPtr<T>(other, ptr); 
}