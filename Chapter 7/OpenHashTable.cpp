#include<bits/stdc++.h>
using namespace std;

int DirectAddressing(int key,int a,int b)
{
    return (a*key+b);
}
int RemaindAddressing(int key,int tableSize)
{
    return key%tableSize;
}
int MidSquareAddressing(int key,int midnum) 
{
    long long square = (long long)key*key;
    
    for(int i=0;i<midnum/2;i++) 
        square/=10;
    
    int mid=square%(int)pow(10, midnum);
    
    return mid;
}

template<class T>
struct Node{
    int key;
    T value;
    bool used;
    Node(int key,T value):key(key),value(value),used(true){}
    Node():key(0),value(T()),used(false){}
};

template<class T>
class LinkHashTable{
private:
    vector<Node<T>> table;
    int MaxSize;
    int Hash(int key);
    string OP,PROBE;
    int Hash2(int key) { return RemaindAddressing(key, MaxSize - 1) + 1; }
    void LinearInsert(int key,T value);
    void SquareInsert(int key,T value);
    void DoubleInsert(int key,T value);
    bool LinearRemove(int key);
    bool SquareRemove(int key);
    bool DoubleRemove(int key);

    T LinearSearch(int key);
    T SquareSearch(int key);
    T DoubleSearch(int key);

public:
    LinkHashTable(int size,string op,string probe):table(size),MaxSize(size),OP(op),PROBE(probe){}
    LinkHashTable():table(10000),MaxSize(10000),OP("Remaind"),PROBE("Linear"){}
    
    void Insert(int key,T value);
    bool Remove(int key);
    T Search(int key);
};

template<class T>
int LinkHashTable<T>::Hash(int key)
{
    if(OP == "Direct")
        return DirectAddressing(key,1,0)%MaxSize;
    else if(OP == "Remaind")
        return RemaindAddressing(key,MaxSize);
    else if(OP == "MidSquare")
        return MidSquareAddressing(key,4)%MaxSize;
    return -1;
}

template<class T>
void LinkHashTable<T>::Insert(int key,T value)
{
    if(PROBE == "Linear")
        LinearInsert(key,value);
    else if(PROBE == "Square")
        SquareInsert(key,value);
    else if(PROBE == "Double")
        DoubleInsert(key,value);
}

template<class T>
bool LinkHashTable<T>::Remove(int key)
{
    if(PROBE == "Linear")
        return LinearRemove(key);
    else if(PROBE == "Square")
        return SquareRemove(key);
    else if(PROBE == "Double")
        return DoubleRemove(key);
    return false;
}

template<class T>
T LinkHashTable<T>::Search(int key)
{
    if(PROBE == "Linear")
        return LinearSearch(key);
    else if(PROBE == "Square")
        return SquareSearch(key);
    else if(PROBE == "Double")
        return DoubleSearch(key);
    return T();
}

template<class T>
void LinkHashTable<T>::LinearInsert(int key,T value)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].value=value;
            return;
        }
        idx=(idx+1)%MaxSize;
        if(idx==Hkey)
            return;
    }
    table[idx]=Node<T>(key,value);
}

template<class T>
void LinkHashTable<T>::SquareInsert(int key,T value)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int d=1,f=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].value=value;
            return;
        }
        idx=(Hkey+f*d*d)%MaxSize;
        f=-f;
        if(f>0) d++;
        if(idx==Hkey)
            return;
    }
    table[idx]=Node<T>(key,value);
}

template<class T>
void LinkHashTable<T>::DoubleInsert(int key,T value)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int idx2=Hash2(key);
    int d=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].value=value;
            return;
        }
        idx=(Hkey+d*idx2)%MaxSize;
        d++;
        if(idx==Hkey)
            return;
    }
    table[idx]=Node<T>(key,value);
}

template<class T>
T LinkHashTable<T>::LinearSearch(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    while(table[idx].used)
    {
        if(table[idx].key==key)
            return table[idx].value;
        idx=(idx+1)%MaxSize;
        if(idx==Hkey)
            return T();
    }
    return T();
}

template<class T>
T LinkHashTable<T>::SquareSearch(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int d=1,f=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
            return table[idx].value;
        idx=(Hkey+f*d*d)%MaxSize;
        f=-f;
        if(f>0) d++;
        if(idx==Hkey)
            return T();
    }
    return T();
}

template<class T>
T LinkHashTable<T>::DoubleSearch(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int idx2=Hash2(key);
    int d=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
            return table[idx].value;
        idx=(Hkey+d*idx2)%MaxSize;
        d++;
        if(idx==Hkey)
            return T();
    }
    return T();
}

template<class T>
bool LinkHashTable<T>::LinearRemove(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].used=false;
            return true;
        }
        idx=(idx+1)%MaxSize;
        if(idx==Hkey)
            return false;
    }
    return false;
}

template<class T>
bool LinkHashTable<T>::SquareRemove(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int d=1,f=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].used=false;
            return true;
        }
        idx=(Hkey+f*d*d)%MaxSize;
        f=-f;
        if(f>0) d++;
        if(idx==Hkey)
            return false;
    }
    return false;
}

template<class T>
bool LinkHashTable<T>::DoubleRemove(int key)
{
    int Hkey=Hash(key);
    int idx=Hkey;
    int idx2=Hash2(key);
    int d=1;
    while(table[idx].used)
    {
        if(table[idx].key==key)
        {
            table[idx].used=false;
            return true;
        }
        idx=(Hkey+d*idx2)%MaxSize;
        d++;
        if(idx==Hkey)
            return false;
    }
    return false;
}
