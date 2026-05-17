#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
	T data;
	node* prior;
	node* next;
	node(T x):data(x),prior(this),next(this){}
	node():data(T()),prior(this),next(this){} 
};

template<class T>
class CDLinkList{
private:
    node<T>* head;
    node<T>* tail;
    int Length;
public:
    CDLinkList():head(nullptr),tail(nullptr),Length(0){}
    CDLinkList(int length):head(nullptr),tail(nullptr),Length(length){}
    void InitList(){head=nullptr,tail=nullptr,Length=0;}
    void InitList(int length){head=nullptr,tail=nullptr,Length=length;}

    bool HeadInsert(T e);
    bool TailInsert(T e);
    bool Insert(int idx,T e);

	bool Delete(int idx,T& e);

    int LocateElem(T e);
    T GetElem(int idx);

    int GetLength(){return Length;}
    bool Empty(){return Length==0;}
    void PrintList();
    void DestroyList();
};

template<class T>
bool CDLinkList<T>::HeadInsert(T e)
{
    node<T>* newnode=new node<T>(e);
    if(head==nullptr)
    {
        head=newnode;
        tail=newnode;
        Length++;
        return 1;
    }
    newnode->next=head;
    newnode->prior=tail;
    head->prior=newnode;
    tail->next=newnode;
    head=newnode;
    Length++;
    return 1;
}

template<class T>
bool CDLinkList<T>::TailInsert(T e)
{
    node<T>* newnode=new node<T>(e);
    if(head==nullptr)
    {
        head=newnode;
        tail=newnode;
        Length++;
        return 1;
    }
    newnode->prior=tail;
    newnode->next=head;
    tail->next=newnode;
    head->prior=newnode;
    tail=newnode;
    Length++;
    return 1;
}

template<class T>
bool CDLinkList<T>::Insert(int idx,T e)
{
    node<T>* newnode=new node<T>(e);
    if(idx<1||idx>Length+1)
        return 0;
    if(idx==1)
        return HeadInsert(e);
    if(idx==Length+1)
        return TailInsert(e);
    node<T>* p=head;
    for(int i=1;i<idx-1&&p!=nullptr;i++)
        p=p->next;
    newnode->next=p->next;
    newnode->prior=p;
    p->next->prior=newnode;
    p->next=newnode;
    Length++;
    return 1;
}

template<class T>
bool CDLinkList<T>::Delete(int idx,T& e)
{
    if(idx<1||idx>Length)
        return 0;
    node<T>* p=head;
    if(idx==1)
    {
        e=p->data;
        if(Length==1)
        {
            head=nullptr;
            tail=nullptr;
        }
        else
        {
            head=p->next;
            head->prior=tail;
            tail->next=head;
        }
        delete p;
        Length--;
        return 1;
    }
    for(int i=1;i<idx-1&&p!=nullptr;i++)
        p=p->next;
    
    node<T>* q=p->next;
    e=q->data;
    p->next=q->next;
    q->next->prior=p;
    if(q==tail)
        tail=p;
    delete q;
    Length--;
    
    return 1;
}
template<class T>
int CDLinkList<T>::LocateElem(T e)
{
    node<T>* p=head;
    for(int i=1;i<=Length&&p!=nullptr;i++)
    {
        if(p->data==e)
            return i;
        p=p->next;
    }
    return 0;
}
template<class T>
T CDLinkList<T>::GetElem(int idx)
{
    if(idx<1||idx>Length)
        return T();
    node<T>* p=head;
    for(int i=1;i<idx&&p!=nullptr;i++)
        p=p->next;
    return p->data;
}
template<class T>
void CDLinkList<T>::PrintList()
{
    node<T>* p=head;
    int idx=0;
    while(p!=nullptr&&idx<Length)
    {
        cout<<p->data;
        p=p->next;
        if(idx<Length-1) 
            cout<<" ";
        idx++;
    }
    cout<<endl;
}
template<class T>
void CDLinkList<T>::DestroyList()
{
    node<T>* p=head;
    for(int i=0; i<Length; i++)
    {
        node<T>* q=p;
        p=p->next;
        delete q;
    }
    InitList();
}
