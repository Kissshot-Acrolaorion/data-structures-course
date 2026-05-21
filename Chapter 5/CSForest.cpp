#include<bits/stdc++.h>
using namespace std;
 
template<class T>
struct node{
    T data;
    node* child;
    node* sibling;
    node(T data):data(data),child(nullptr),sibling(nullptr){}
    node():data(T()),child(nullptr),sibling(nullptr){}
};

template<class T>
class CSForest{
private:
    node<T>* root;
    node<T>* findNode(node<T>* current, T value);

public:
    CSForest():root(nullptr){}
    bool insert(T parent, T child);
    
};
template<class T>
node<T>* CSForest<T>::findNode(node<T>* current, T value)
{
    if(current==nullptr) return nullptr;
    if(current->data==value) return current;

    node<T> *found=findNode(current->child,value);

    if(found!=nullptr) return found;
    return findNode(current->sibling,value);
}

template<class T>
bool CSForest<T>::insert(T parent, T child)
{
    if(root==nullptr)
    {
        root=new node<T>(parent);
        root->child=new node<T>(child);
        return 1;
    }
    node<T>* parentNode=findNode(root, parent);
    if(parentNode==nullptr) return 0;
    
    node<T>* newChild=new node<T>(child);
    if(parentNode->child==nullptr)
        parentNode->child=newChild;
    else 
    {
        node<T>* sibling=parentNode->child;
        while(sibling->sibling!=nullptr)
            sibling=sibling->sibling;
        sibling->sibling=newChild;
    }
    return 1;
}

