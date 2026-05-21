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
    Node* next;
    Node(int key,T value):key(key),value(value),next(nullptr){}
    Node():key(0),value(T()),next(nullptr){}
    
};
template<class T>
class LinkHashTable{
private:
    vector<Node<T>*> table;
    int MaxSize;
    int Hash(int key);
    string OP;

public:
    LinkHashTable(int size,string op):table(size,nullptr),MaxSize(size),OP(op){}
    LinkHashTable():table(10000,nullptr),MaxSize(10000),OP("Remaind"){}

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
    int Hkey=Hash(key);
    Node<T>* newnode=new Node<T>(key,value);
    
    if(table[Hkey]==nullptr)
        table[Hkey]=newnode;
    else
    {
        Node<T>* cur=table[Hkey];
        newnode->next=cur;
        table[Hkey]=newnode;
    }
}

template<class T>
bool LinkHashTable<T>::Remove(int key)
{
    int Hkey=Hash(key);
    Node<T>* cur=table[Hkey];
    Node<T>* pre=nullptr;
    while(cur!=nullptr)
    {
        if(cur->key==key)
        {
            if(pre==nullptr)
                table[Hkey]=cur->next;
            else
                pre->next=cur->next;
            delete cur;
            return 1;
        }
        pre=cur;
        cur=cur->next;
    }
    return 0;
}

template<class T>
T LinkHashTable<T>::Search(int key)
{
    int Hkey=Hash(key);
    Node<T>* cur=table[Hkey];
    while(cur!=nullptr)
    {
        if(cur->key==key)
            return cur->value;
        cur=cur->next;
    }
    return T();
}
