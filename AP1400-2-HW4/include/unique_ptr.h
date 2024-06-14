#pragma once

template<typename T>
class UniquePtr
{
public:
    UniquePtr();
    UniquePtr(T* ptr);
    UniquePtr(const UniquePtr<T>& other) = delete;
    ~UniquePtr();

    void operator=(const UniquePtr<T>& other) = delete;
    operator bool() const;
    T* get();
    T operator*();
    T* operator->();
    void reset();
    void reset(T* nptr);
    T* release();
private:
    T* ptr = nullptr;
};

template<typename T>
UniquePtr<T>::UniquePtr() : ptr(nullptr)
{}
template<typename T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr(ptr)
{}
template<typename T>
UniquePtr<T>::~UniquePtr()
{
    reset();
}

template<typename T>
T* UniquePtr<T>::get()
{
    return ptr;
}
template<typename T>
UniquePtr<T>::operator bool() const
{
    return ptr != nullptr;
}
template<typename T>
T UniquePtr<T>::operator*()
{
    return (*ptr);
}
template<typename T>
T* UniquePtr<T>::operator->()
{

    return (ptr);
}
template<typename T>
void UniquePtr<T>::reset()
{
    delete ptr;
    ptr = nullptr;
}
template<typename T>
void UniquePtr<T>::reset(T* nptr)
{
    reset();
    ptr = nptr;
}
template<typename T>
T* UniquePtr<T>::release()
{
    T* rptr = ptr;
    ptr     = nullptr;
    return rptr;
}



template<typename T,typename ...Args >
static UniquePtr<T> make_unique(Args... args)
{
    return new T(args...);
}






