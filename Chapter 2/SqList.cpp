#include<bits/stdc++.h>
using namespace std;

template<class T>
class SqList{
private:
	T* data;
    int MaxSize,Length;
public:
	SqList():MaxSize(1e4),Length(0){data=new T[MaxSize];}
	SqList(int maxsize,int length):MaxSize(maxsize),Length(length){data=new T[MaxSize];}
	void InitList(){MaxSize=1e4,Length=0,data=new T[MaxSize];}
	void InitList(int maxsize,int length){MaxSize=maxsize,Length=length,data=new T[MaxSize];}
	
	int LocateElem(T e); 
	T GetElem(int idx);

	bool ListInsert(int idx,T e);

	bool ListDelete(int idx,T& e); 

	int GetLength(){return Length;}
	bool Empty(){return Length==0;}
	void PrintList();
	void DestroyList(){delete[] data;}
	 
};
template<class T>
int SqList<T>::LocateElem(T e)
{
	for(int i=0;i<Length;i++)
		if(e==data[i])
			return i+1;
	return 0;
}
template<class T>
T SqList<T>::GetElem(int idx)
{
	if(idx<1||idx>Length)
		return T();
	return data[idx-1];
}
template<class T>
bool SqList<T>::ListInsert(int idx,T e)
{
	if(idx<1||idx>Length+1)
		return 0;
	if(Length>=MaxSize)
		return 0;
	for(int i=Length;i>=idx;i--)
		data[i]=data[i-1];
	data[idx-1]=e;
	Length++;
	return 1;
}
template<class T>
bool SqList<T>::ListDelete(int idx,T& e)
{
	if(idx<1||idx>Length)
		return 0;
	e=data[idx-1];
	for(int i=idx;i<Length;i++)
		data[i-1]=data[i];
	Length--;
	return 1;
}
template<class T>
void SqList<T>::PrintList()
{
	for(int i=0;i<Length;i++)
	{
		cout<<data[i];
		i!=Length-1?cout<<" ":cout<<endl;
	}
}


void Test1()
{
    SqList<int> list;
    
    // Test insertion
    cout << "Testing insertion of 1, 2, 3 into the list:" << endl;
    list.ListInsert(1, 1);
    list.ListInsert(2, 2);
    list.ListInsert(3, 3);
    list.PrintList();
    
    cout << "Current length: " << list.GetLength() << endl;
    cout << "The 2nd element is: " << list.GetElem(2) << endl;
    cout << "The position of element 3 is: " << list.LocateElem(3) << endl;
    
    int deletedElem;
    if (list.ListDelete(2, deletedElem)) 
        cout << "Deleted the 2nd element: " << deletedElem << endl;         
    cout << "The list after deletion:" << endl;
    list.PrintList();

    list.DestroyList();
}

void  Test2()
{
    SqList<string> list;
    
    cout << "\n--- Test 2: string type ---" << endl;
    cout << "Testing insertion of 'apple', 'banana', 'cherry' into the list:" << endl;
    list.ListInsert(1, "apple");
    list.ListInsert(2, "banana");
    list.ListInsert(3, "cherry");
    list.PrintList();
    
    cout << "Current length: " << list.GetLength() << endl;
    cout << "The 2nd element is: " << list.GetElem(2) << endl;
    cout << "The position of 'cherry' is: " << list.LocateElem("cherry") << endl;
    
    string deletedElem;
    if (list.ListDelete(2, deletedElem))
        cout << "Deleted the 2nd element: " << deletedElem << endl;
    cout << "The list after deletion:" << endl;
    list.PrintList();
    
    list.DestroyList();
}
signed main()
{
    Test1();
    Test2();
    return 0;
}
