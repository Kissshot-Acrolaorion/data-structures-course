#include<bits/stdc++.h>
using namespace std;

template<class T>
class SqQueue{
private:
    T *data;
    int front,rear;
    int MaxSize;
public:
    SqQueue(int maxsize=10000):front(0),rear(0),MaxSize(maxsize){data=new T[MaxSize];}
    void InitQueue(){front=rear=0,MaxSize=1e4;data=new T[MaxSize];}
    void InitQueue(int maxsize){front=rear=0,MaxSize=maxsize;data=new T[MaxSize];}
    void DestroyQueue(){delete []data;}
    ~SqQueue(){delete []data;}

    bool Empty(){return front==rear;}
    int Length(){return (rear-front+MaxSize)%MaxSize;}
    void Clear(){InitQueue(MaxSize);}
    T Front();
    bool Push(T e);
    bool Pop();
};
template<class T>
T SqQueue<T>::Front()
{
    if(Empty()) return T();
    return data[front];
}
template<class T>
bool SqQueue<T>::Push(T e)
{
    if((rear+1)%MaxSize==front) return 0;
    data[rear]=e; rear=(rear+1)%MaxSize; return 1;
}
template<class T>
bool SqQueue<T>::Pop()
{
    if(Empty()) return 0;
    front=(front+1)%MaxSize; return 1;
}