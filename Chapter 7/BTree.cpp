#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    vector<T> keys;
    vector<Node<T>*> child;
    int num;
    int isleaf;

    Node():keys(),child(),num(0),isleaf(1){}
};

template<class T>
class BTree{
private:
    Node<T>* root;
    vector<T> arr;
    int Order;
    
    void SplitChild(Node<T>* parent,int idx);
    void InsertNonFull(Node<T>* u, T data);
    
public:
    BTree():Order(2),root(nullptr){}
    BTree(int order):Order(order),root(nullptr){}
    BTree(vector<T> arr,int order):Order(order),root(nullptr),arr(arr){}
    
    bool Insert(T data);
    bool Remove(T data); 
    bool Search(T data);
    
};

template<class T>
void BTree<T>::SplitChild(Node<T>* parent,int idx)
{
    Node<T>* child = parent->child[idx];
    Node<T>* newchild = new Node<T>();
    newchild->isleaf = child->isleaf;
    newchild->num = Order-1;

    for(int i=0;i<Order-1;i++)
        newchild->keys.push_back(child->keys[i+Order]);

    if(!child->isleaf)
        for(int i=0;i<Order;i++)
            newchild->child.push_back(child->child[i+Order]);
        
    child->num = Order-1;

    parent->child.insert(parent->child.begin()+idx+1,newchild);
    parent->keys.insert(parent->keys.begin()+idx,child->keys[Order-1]);
    parent->num++;
}

template<class T>
void BTree<T>::InsertNonFull(Node<T>* u, T data)
{
    int i = u->num-1;
    if(u->isleaf)
    {
        u->keys.push_back(data);
        while(i>=0 && u->keys[i]>data)
        {
            swap(u->keys[i],u->keys[i+1]);
            i--;
        }
        u->num++;
    }
    else
    {
        while(i>=0 && u->keys[i]>data)
            i--;
        i++;
        if(u->child[i]->num == 2*Order-1)
        {
            SplitChild(u,i);
            if(u->keys[i]<data)
                i++;
        }
        InsertNonFull(u->child[i],data);
    }
}

template<class T>
bool BTree<T>::Insert(T data)
{
    if(root == nullptr)
    {
        root = new Node<T>();
        root->keys.push_back(data);
        root->num++;
        return true;
    }
    if(SearchNode(root,data))
        return false;
    if(root->num == 2*Order-1)
    {
        Node<T>* newroot = new Node<T>();
        newroot->isleaf = 0;
        newroot->child.push_back(root);
        SplitChild(newroot,0);
        InsertNonFull(newroot,data);
        root = newroot;
    }
    else
        InsertNonFull(root,data);
    return true;
}

template<class T>
bool BTree<T>::Search(T data)
{
    int i = 0;
    while(i<root->num && data>root->keys[i])
        i++;
    if(i<root->num && root->keys[i] == data)
        return true;
    if(root->isleaf)
        return false;
    return Search(root->child[i],data);
}