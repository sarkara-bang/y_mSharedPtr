//
// Created by sarkara on 2023/9/12.
//
#ifndef Y_MSHAREDPTR_Y_SHARED_PTR_H
#define Y_MSHAREDPTR_Y_SHARED_PTR_H

#include <iostream>
#include <memory>
using namespace std;

template<class T>
class CySharedPtr{
private:
    T* ptr = nullptr;
    unsigned int* ref_count = nullptr;
public:
    //默认构造函数
    CySharedPtr():ptr(nullptr),ref_count(nullptr){}
    //以T类型对象初始化的构造函数
    CySharedPtr(T* t):ptr(t),ref_count(new unsigned int (1)){}

    //拷贝构造函数
    CySharedPtr(CySharedPtr &rv){
        ptr = rv.ptr;
        ref_count = rv.ref_count;
        if(ref_count != nullptr){
            *(ref_count)++;
        }
   }
    //重载拷贝赋值运算符
    CySharedPtr& operator=(CySharedPtr &rv){
        //先处理自赋值情况
        if(rv.ptr == ptr){
            return *this;
        }
        //处理左值内部维护的指针
        if(*(this->ref_count) <= 1){
            delete this->ptr;
            delete this->ref_count;
        }else{
            (this->ref_count)--;
        }
        //拷贝右值的内容
        this->ptr = rv.ptr;
        this->ref_count = rv.ref_count;
        if(this->ptr != nullptr){
            *(this->ref_count)++;
        }

        return *this;
    }

    //提供重写的swap函数
    void swap(CySharedPtr& other){
        std::swap(this->ptr,other.ptr);
        std::swap(this->ref_count,other.ref_count);
    }
    //移动构造函数
    CySharedPtr(CySharedPtr &&rv):ptr(nullptr),ref_count(nullptr){
        swap(this,rv);
    }
    //重载移动赋值运算符
    CySharedPtr& operator=(CySharedPtr &&rv){
        //利用移动构造函数创建一个临时的智能指针
        //临时对象销毁后原引用计数-1
        CySharedPtr(std::move(rv)).swap(*this);
        return *this;
    }

    //一些工具函数或运算符
    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    T* get() {
        return ptr;
    }

    size_t use_count() {
        return *ref_count;
    }

    //析构函数销毁该智能指针
    ~CySharedPtr(){
        if(ref_count == nullptr){
            return;
        }
        (*ref_count)--;
        if(*ref_count > 0){
            return;
        }

        if(ptr != nullptr){
            delete ptr;
        }
        delete ref_count;
    }
};

#endif //Y_MSHAREDPTR_Y_SHARED_PTR_H