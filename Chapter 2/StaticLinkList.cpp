#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
    T data;
    int link;
    node(T x):data(x),link(-1){}
    node():data(T()),link(-1){}
};

template<class T>
class StaticLinkList{
private:
    node<T>* data;
    int MaxSize,Length;
    int head;
public:
    StaticLinkList():MaxSize(1e4),Length(0),head(-1){data=new node<T>[MaxSize];}
    StaticLinkList(int maxsize,int length):MaxSize(maxsize),Length(length),head(-1){data=new node<T>[MaxSize];}
    void InitList(){MaxSize=1e4,Length=0,head=-1,data=new node<T>[MaxSize];}
    void InitList(int maxsize,int length){MaxSize=maxsize,Length=length,head=-1,data=new node<T>[MaxSize];}
    
    bool HeadInsert(T e);
    bool TailInsert(T e);
    bool Insert(int idx,T e);
    
    bool Delete(int idx,T& e);

    int LocateElem(T e);
    T GetElem(int idx);

    int GetLength(){return Length;}
    bool Empty(){return Length==0;}
    void PrintList();
    void DestroyList(){delete[] data,InitList();}
    ~StaticLinkList(){DestroyList();}
};
template<class T>
bool StaticLinkList<T>::HeadInsert(T e)
{
    if(Length>=MaxSize)
        return 0;
    data[Length].data=e;
    data[Length].link=head;
    head=Length;
    Length++;
    return 1;
}

template<class T>
bool StaticLinkList<T>::TailInsert(T e)
{
    if(Length>=MaxSize)
        return 0;
    
    data[Length].data=e;
    data[Length].link=-1;
    
    if(head==-1)
    {
        head=Length;
        Length++;
        return 1;
    }
    int thead=head;
    while(data[thead].link!=-1)
        thead=data[thead].link;
    data[thead].link=Length;
    Length++;
    return 1;
}
template<class T>
bool StaticLinkList<T>::Insert(int idx,T e)
{
    if(idx<1||idx>Length+1)
        return 0;
    if(Length>=MaxSize)
        return 0;
    if(idx==1)
        return HeadInsert(e);
 
    data[Length].data=e;
    int thead=head;
    for(int i=1;i<idx-1&&thead!=-1;i++)
        thead=data[thead].link;
    data[Length].link=data[thead].link;
    data[thead].link=Length;
    Length++;
    return 1;
}

template<class T>
bool StaticLinkList<T>::Delete(int idx,T& e)
{
    if(idx<1||idx>Length)
        return 0;
    int p=head;
    if(idx==1)
    {
        e=data[p].data;
        head=data[p].link;
        Length--;
        return 1;
    }
    for(int i=1;i<idx-1&&p!=-1;i++)
        p=data[p].link;
    
    int q=data[p].link;
    e=data[q].data;
    data[p].link=data[q].link;
    Length--;
    return 1;
}

template<class T>
int StaticLinkList<T>::LocateElem(T e)
{
    int p=head;
    for(int i=1;i<=Length&&p!=-1;i++)
    {
        if(data[p].data==e)
            return i;
        p=data[p].link;
    }
    return 0;
}

template<class T>
T StaticLinkList<T>::GetElem(int idx)
{
    if(idx<1||idx>Length)
        return T();
    int p=head;
    for(int i=1;i<idx&&p!=-1;i++)
        p=data[p].link;
    return data[p].data;
}

template<class T>
void StaticLinkList<T>::PrintList()
{
    int p=head;
    int idx=0;
    while(p!=-1&&idx<Length)
    {
        cout<<data[p].data;
        p=data[p].link;
        if(idx<Length-1) 
            cout<<" ";
        idx++;
    }
    cout<<endl;
}