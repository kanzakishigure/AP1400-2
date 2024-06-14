#pragma once
#include <bits/c++config.h>
#include <cstddef>
template<typename T>
class SharedPtr
{
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr<T>& other);
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr<T>& other);
         operator bool() const;
    T*   get();
    T    operator* () const;
    T*   operator->() const;
    void reset();
    void reset(T* nptr);
    T*   release();
    std::size_t use_count();

private:
    T*           ptr       = nullptr;
    std::size_t* ref_count = nullptr;
};
template<typename T>
SharedPtr<T>::SharedPtr()
:ptr(nullptr)
{
    ref_count = new std::size_t(1);
}
template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
:ptr(ptr)
{
    ref_count = new std::size_t(1);
}
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
    
    ptr = other.ptr ;
    ref_count = other.ref_count;
    *ref_count = *ref_count +1;
}
template<typename T>
SharedPtr<T>::~SharedPtr()
{
    ptr = nullptr;
    *ref_count = *ref_count -1;
    if((*ref_count)<=0)
    {
        delete  ptr;
        delete ref_count;
    }
}
template<typename T>
SharedPtr<T>&  SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if(&other == this)
    {
        return *this;
    }
    (*other.ref_count)+=1;
    reset();
    ptr = other.ptr ;
    ref_count = other.ref_count;
}
template<typename T>
SharedPtr<T>::operator bool() const
{
    return ptr!=nullptr;
}
template<typename T>
T* SharedPtr<T>::get()
{
    return  ptr;
}
template<typename T>
T SharedPtr<T>::operator*() const
{
    return *ptr;
}
template<typename T>
T* SharedPtr<T>::operator->() const
{
    return ptr;
}
template<typename T>
void SharedPtr<T>::reset()
{
    ptr = nullptr;
    *ref_count = *ref_count -1;
    if((*ref_count)<=0)
    {
        *ref_count = 0;
        delete  ptr;
    }
}
template<typename T>
void SharedPtr<T>::reset(T* nptr)
{
    reset();
    ptr = nptr;
    ref_count = new std::size_t(1);
    
}
template<typename T>
T* SharedPtr<T>::release()
{
    return ptr;
}
template<typename T>
std::size_t  SharedPtr<T>::use_count()
{
    return *ref_count;
}
template<typename T, typename... Args>
static SharedPtr<T> make_shared(Args... args)
{
    return new T(args...);
}

