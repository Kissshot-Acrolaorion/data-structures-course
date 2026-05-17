#include <iostream>
using namespace std;

template<class T>
class ShareStack{
private:
    int top1,top2;
    int MaxSize;
    T* data;
public:
    ShareStack() : top1(-1),top2(10000),MaxSize(10000){data=new T[MaxSize];}
    ShareStack(int maxsize) : top1(-1),top2(maxsize),MaxSize(maxsize){data=new T[MaxSize];}
    void InitStack(){top1=-1;top2=MaxSize;data=new T[MaxSize];}
    void InitStack(int maxsize){top1=-1;top2=maxsize;MaxSize=maxsize;data=new T[MaxSize];}
    ~ShareStack(){delete []data;}
    void DestroyStack(){delete []data;}

    void Clear1(){top1=-1;}
    void Clear2(){top2=MaxSize;}
    bool Empty1(){return top1==-1;}
    bool Empty2(){return top2==MaxSize;}
    int Length1(){return top1+1;}
    int Length2(){return MaxSize-top2;}
    T Top1();
    T Top2();
    bool Push1(T e);
    bool Push2(T e);
    bool Pop1();
    bool Pop2();
};

template<class T>
T ShareStack<T>::Top1()
{
    if(Empty1()) return T();
    return data[top1];
}
template<class T>
T ShareStack<T>::Top2()
{
    if(Empty2()) return T();
    return data[top2];
}
template<class T>
bool ShareStack<T>::Push1(T e)
{
    if(1==top2-top1) return 0;
    data[++top1]=e; return 1;
}
template<class T>
bool ShareStack<T>::Push2(T e)
{
    if(1==top2-top1) return 0;
    data[--top2]=e; return 1;
}
template<class T>
bool ShareStack<T>::Pop1()
{
    if(Empty1()) return 0;
    top1--; return 1;
}
template<class T>
bool ShareStack<T>::Pop2()
{
    if(Empty2()) return 0;
    top2++; return 1;
}