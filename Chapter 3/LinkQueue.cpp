#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct node{
    T data;
    node *next;
    node(T e):data(e), next(nullptr){}
    node():data(T()), next(nullptr){}
};

template<class T>
class LinkQueue{
private:
    node<T> *front;
    node<T> *rear;
public:
    LinkQueue(){front=rear=nullptr;}
    void InitQueue(){front=rear=nullptr;}
    void DestroyQueue(){Clear();}
    ~LinkQueue(){Clear();}

    bool Empty(){return front==nullptr;}
    int Length();
    void Clear();
    T Front();
    bool Push(T e);
    bool Pop();

};
template<class T>
int LinkQueue<T>::Length()
{
    int count=0;
    for(node<T>* p=front;p!=nullptr;p=p->next) count++;
    return count;
}

template<class T>
void LinkQueue<T>::Clear()
{
    node<T> *p=front;
    node<T> *q;
    while(p!=nullptr)
    {
        q=p->next;
        delete p;
        p=q;
    }
    InitQueue();
}

template<class T>
T LinkQueue<T>::Front()
{
    if(Empty()) return T();
    return front->data;
}

template<class T>
bool LinkQueue<T>::Push(T e)
{
    node<T>* p=new node<T>(e);
    if(Empty())
        front=rear=p;
    else
    {
        rear->next=p;
        rear=p;
    }
    return 1;
}

template<class T>
bool LinkQueue<T>::Pop()
{
    if(Empty()) return 0;
    node<T>* p=front;
    front=front->next;
    delete p;
    return 1;
}
