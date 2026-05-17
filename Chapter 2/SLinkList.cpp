#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
    T data;
    node* next;

    node(T x):data(x),next(nullptr){}
    node():data(T()),next(nullptr){}
};

template<class T>
class SLinkList{
private:
    node<T>* head;
    int Length;
public:
    SLinkList():head(nullptr),Length(0){}
    SLinkList(int length):head(nullptr),Length(length){}
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
bool SLinkList<T>::HeadInsert(T e)
{
    node<T>* newNode=new node<T>(e);
    if (head==nullptr)
    {
        head=newNode;
        Length++;
        return 1;
    }
    
    newNode->next=head;
    head=newNode;
    Length++;
    
    return 1;
}

template<class T>
bool SLinkList<T>::TailInsert(T e)
{
    node<T>* newNode=new node<T>(e);
    if(head==nullptr)
    {
        head=newNode;
        Length++;
        return 1;
    }
    node<T>* p=head;
    while(p->next!=nullptr)
        p=p->next;
    p->next=newNode;
    Length++;
    
    return 1;
}

template<class T>
bool SLinkList<T>::Insert(int idx,T e)
{
    if(idx<1||idx>Length+1)
        return 0;
    if(idx==1)
        return HeadInsert(e);
    
    node<T>* newNode=new node<T>(e);
    node<T>* p=head;
    for(int i=1;i<idx-1&&p!=nullptr;i++)
        p=p->next;
    newNode->next=p->next;
    p->next=newNode;
    Length++;
    return 1;
}

template<class T>
bool SLinkList<T>::Delete(int idx,T& e)
{
    if(idx<1||idx>Length)
        return 0;
    node<T>* p=head;
    if(idx==1)
	{
		e=p->data;
		head=p->next;
		delete p;
		Length--;
		return 1;
	} 
	for(int i=1;i<idx-1&&p!=nullptr;i++)
        p=p->next;
    
    node<T>* q=p->next;
    e=q->data;
    p->next=q->next;
    delete q;
    Length--;
    
    return 1;
}

template<class T>
int SLinkList<T>::LocateElem(T e)
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
void SLinkList<T>::PrintList()
{
    node<T>* p=head;
    while(p!=nullptr)
    {
        cout<<p->data;
        p=p->next;
        if(p!=nullptr) 
            cout<<" ";
    }
    cout << endl;
}

template<class T>
void SLinkList<T>::DestroyList()
{
    node<T>* p=head;
    while(p!=nullptr)
    {
        node<T>* q=p;
        p=p->next;
        delete q;
    }
    InitList();
}

void Test1()
{
    cout << "--- Test 1: HeadInsert and TailInsert Test ---" << endl;
    SLinkList<int> list;
    for (int i = 1; i <= 3; i++) {
        list.HeadInsert(i); // After insertion: 3 2 1
    }

    for (int i = 4; i <= 6; i++) {
        list.TailInsert(i); // After insertion: 3 2 1 4 5 6
    }
    cout << "Current list elements: ";
    list.PrintList();
    cout << "List length: " << list.GetLength() << endl;
    cout << "Position of element 4: " << list.LocateElem(4) << endl;
    list.DestroyList();
}

void Test2()
{
    cout << "\n--- Test 2: Insert and Delete Test ---" << endl;
    SLinkList<int> list;
    list.TailInsert(10);
    list.TailInsert(30);
    list.TailInsert(50);
    
    list.Insert(2, 20); // Becomes 10 20 30 50
    list.Insert(4, 40); // Becomes 10 20 30 40 50
    cout << "List after insertion: ";
    list.PrintList();
    
    int e;
    if (list.Delete(3, e)) {
        cout << "Successfully deleted the 3rd element: " << e << endl;
    }
    cout << "List after deletion: ";
    list.PrintList();
    list.DestroyList();
}

void Test3()
{
    cout << "\n--- Test 3: String List Test ---" << endl;
    SLinkList<string> list;
    list.TailInsert("Hello");
    list.TailInsert("World");
    list.TailInsert("C++");
    
    list.Insert(2, "Beautiful");
    cout << "List after string insertions: ";
    list.PrintList();
    
    string e;
    if (list.Delete(3, e)) {
        cout << "Successfully deleted the 3rd element: " << e << endl;
    }
    cout << "List after deletion: ";
    list.PrintList();
    cout << "Position of 'C++': " << list.LocateElem("C++") << endl;
    list.DestroyList();
}
signed main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}