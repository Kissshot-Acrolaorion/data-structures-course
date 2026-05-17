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
	~SqList(){delete[] data;}
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