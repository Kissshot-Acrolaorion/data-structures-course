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
class DLinkList{
private:
	node<T>* head;
    int Length;
public:
	DLinkList():head(nullptr),Length(0){}
    DLinkList(int length):head(nullptr),Length(length){}
    void InitList(){head=nullptr,Length=0;}
    void InitList(int length){head=nullptr,Length=length;}

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
bool DLinkList<T>::HeadInsert(T e)
{
	node<T>* newnode=new node<T>(e);
	if(head==nullptr)
	{
		head=newnode;
		Length++;
		return 1;
	}
	newnode->next=head;
	head->prior=newnode;
	head=newnode;
	Length++;
	return 1;
}
template<class T>
bool DLinkList<T>::TailInsert(T e)
{
	node<T>* newnode=new node<T>(e);
	if(head==nullptr)
	{
		head=newnode;
		Length++;
		return 1;
	}
	node<T>* p=head;
	while(p->next!=nullptr)
		p=p->next;
	p->next=newnode;
	newnode->prior=p;
	Length++;
	return 1;
}
template<class T>
bool DLinkList<T>::Insert(int idx,T e)
{
	if(idx<1||idx>Length+1)
		return 0;
	if(idx==1)
		return HeadInsert(e);
	if(idx==Length+1)
		return TailInsert(e);

	node<T>* newnode=new node<T>(e);
	node<T>* p=head;
	for(int i=1;i<idx-1&&p!=nullptr;i++)
		p=p->next;
	
	newnode->next=p->next;
	p->next->prior=newnode;
	p->next=newnode;
	newnode->prior=p;
	Length++;
	return 1;
}

template<class T>
bool DLinkList<T>::Delete(int idx,T& e)
{
	if(idx<1||idx>Length)
		return 0;
	node<T>* p=head;
	if(idx==1)
	{
		e=p->data;
		head=p->next;
		if(head!=nullptr)
			head->prior=nullptr;
		delete p;
		Length--;
		return 1;
	}
	for(int i=1;i<idx&&p!=nullptr;i++)
		p=p->next;
	e=p->data;
	p->prior->next=p->next;
	if(p->next!=nullptr)
		p->next->prior=p->prior;
	delete p;
	Length--;
	return 1;
}
template<class T>
int DLinkList<T>::LocateElem(T e)
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
T DLinkList<T>::GetElem(int idx)
{
	if(idx<1||idx>Length)
		return T();
	node<T>* p=head;
	for(int i=1;i<idx&&p!=nullptr;i++)
		p=p->next;
	return p->data;
}
template<class T>
void DLinkList<T>::PrintList()
{
	node<T>* p=head;
	while(p!=nullptr)
	{
		cout<<p->data;
		if(p->next!=nullptr)
			cout<<" ";
		p=p->next;
	}
	cout<<endl;
}
template<class T>
void DLinkList<T>::DestroyList()
{
	node<T>* p=head;
	while(p!=nullptr)
	{
		node<T>* q=p;
		p=p->next;
		delete q;
	}
	head=nullptr;
	Length=0;
}
