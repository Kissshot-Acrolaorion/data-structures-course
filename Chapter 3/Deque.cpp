#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
	T data;
	node* prior;
	node* next;
	node(T x):data(x),prior(nullptr),next(nullptr){}
	node():data(T()),prior(nullptr),next(nullptr){} 
};

template<class T>
class Deque{
private:
    node<T>* head;
    node<T>* tail;
public:
    Deque():head(nullptr),tail(nullptr){}
    void InitDeque(){head=tail=nullptr;}
    void DestroyDeque();
    ~Deque(){DestroyDeque();}

    bool Empty(){return head==nullptr;}
    int Length();
    void Clear(){DestroyDeque();}
    T Front();
    T Back();
    bool PushFront(T e);
    bool PushBack(T e);
    bool PopFront();
    bool PopBack();
};
template<class T>
int Deque<T>::Length()
{
    int count=0;
    for(node<T>* p=head;p!=nullptr;p=p->next) count++;
    return count;
}

template<class T>
T Deque<T>::Front()
{
    if(Empty()) return T();
    return head->data;
}
template<class T>
T Deque<T>::Back()
{
    if(Empty()) return T();
    return tail->data;
}
template<class T>
bool Deque<T>::PushFront(T e)
{
    node<T>* newnode=new node<T>(e);
    if(Empty())
    {
        head=tail=newnode;
        return 1;
    }
    newnode->next=head;
    head->prior=newnode;
    head=newnode;
    return 1;
}
template<class T>
bool Deque<T>::PushBack(T e)
{
    node<T>* newnode=new node<T>(e);
    if(Empty())
    {
        head=tail=newnode;
        return 1;
    }
    tail->next=newnode;
    newnode->prior=tail;
    tail=newnode;
    return 1;
}
template<class T>
bool Deque<T>::PopFront()
{
    if(Empty()) return 0;
    node<T>* p=head;
    head=head->next;
    if(head!=nullptr)
        head->prior=nullptr;
    else
        tail=nullptr;
    delete p;
    return 1;
}
template<class T>
bool Deque<T>::PopBack()
{
    if(Empty()) return 0;
    node<T>* p=tail;
    tail=tail->prior;
    if(tail!=nullptr)
        tail->next=nullptr;
    else
        head=nullptr;
    delete p;
    return 1;
}
template<class T>
void Deque<T>::DestroyDeque()
{
    node<T>* p=head;
    while(p!=nullptr)
    {
        node<T>* q=p;
        p=p->next;
        delete q;
    }
    head=tail=nullptr;
}
