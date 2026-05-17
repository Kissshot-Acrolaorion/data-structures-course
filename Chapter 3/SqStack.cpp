#include<bits/stdc++.h>
using namespace std;

template<class T>
class SqStack{
private:
    T *data;
    int top, MaxSize;
public:
    SqStack():top(-1),MaxSize(1e4){data=new T[MaxSize];}
    SqStack(int maxsize):top(-1),MaxSize(maxsize){data=new T[MaxSize];}
    void InitStack(){top=-1,MaxSize=1e4,data=new T[MaxSize];}
    void InitStack(int maxsize){top=-1,MaxSize=maxsize,data=new T[MaxSize];}
    void DestroyStack(){delete []data;}
    ~SqStack(){delete []data;}

    bool Empty(){return top==-1;}
    int Length(){return top+1;}
    void Clear(){InitStack(MaxSize);}
    T Top();
    bool Push(T e);
    bool Pop();

};
template<class T>
T SqStack<T>::Top()
{
    if(Empty()) return T();
    return data[top];
}
template<class T>
bool SqStack<T>::Push(T e)
{
    if(top==MaxSize-1) return 0;
    data[++top]=e; return 1;
}
template<class T>
bool SqStack<T>::Pop()
{
    if(Empty()) return 0;
    top--; return 1;
}

