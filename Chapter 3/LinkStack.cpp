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
class LinkStack{
private:
    node<T> *top;
public:
    LinkStack(){top=nullptr;}
    void InitStack(){top=nullptr;}
    void DestroyStack(){Clear();}
    ~LinkStack(){Clear();}

    bool Empty(){return top==nullptr;}
    int Length();
    void Clear();
    T Top();
    bool Push(T e);
    bool Pop();

};
template<class T>
int LinkStack<T>::Length()
{
    int count=0;
    for(node<T>* p=top;p!=nullptr;p=p->next) count++;
    return count;
}

template<class T>
void LinkStack<T>::Clear()
{
    node<T> *p=top;
    node<T>* q;
    while(p!=nullptr)
    {
        q=p->next;
        delete p;
        p=q;
    }
    InitStack();
}

template<class T>
T LinkStack<T>::Top()
{
    if(Empty()) return T();
    return top->data;
}

template<class T>
bool LinkStack<T>::Push(T e)
{
    node<T>* p=new node<T>(e);
    p->next=top;
    top=p;
    return 1;
}

template<class T>
bool LinkStack<T>::Pop()
{
    if(Empty()) return 0;
    node<T>* p=top;
    top=top->next;
    delete p;
    return 1;
}

signed main()
{
    int b,n;
    cin>>b>>n;
    LinkStack<int> s;
    while(n)
    {
        s.Push(n%b);
        n/=b;
    }
    while(!s.Empty()) cout<<s.Top(),s.Pop();
    return 0;
}