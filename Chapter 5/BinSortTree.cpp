#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    T data;
    Node* left;
    Node* right;
    Node(T data):data(data),left(nullptr),right(nullptr){}
    Node():data(T()),left(nullptr),right(nullptr){}
};

template<class T>
class BinSortTree{
private:
    Node<T>* root;
public:
    BinSortTree():root(nullptr){}
    void InitBST(){root=nullptr;}

    bool Check(T data);
    bool Insert(T data);
    bool Remove(T data);

    vector<T> PreOrder();
    vector<T> InOrder();
    vector<T> PostOrder();
    vector<T> LevelOrder();

    void PreOrder(Node<T>* u,vector<T>& res);
    void InOrder(Node<T>* u,vector<T>& res);
    void PostOrder(Node<T>* u,vector<T>& res);
};

template<class T>
bool BinSortTree<T>::Check(T data)
{
    Node<T>* tnode=root;
    while(tnode!=nullptr)
    {
        if(tnode->data==data)
            return 1;
        else if(tnode->data>data)
            tnode=tnode->left;
        else
            tnode=tnode->right;
    }
    return 0;
}

template<class T>
bool BinSortTree<T>::Insert(T data)
{
    if(root==nullptr)
    {
        root=new Node<T>(data);
        return 1;
    }
    Node<T>* tnode=root;
    while(tnode!=nullptr)
    {
        if(tnode->data==data)
            return 0;
        else if(tnode->data>data)
        {
            if(tnode->left==nullptr)
            {
                tnode->left=new Node<T>(data);
                return 1;
            }
            tnode=tnode->left;
        }
        else
        {
            if(tnode->right==nullptr)
            {
                tnode->right=new Node<T>(data);
                return 1;
            }
            tnode=tnode->right;
        }
    }
    return 0;
}
template<class T>
bool BinSortTree<T>::Remove(T data)
{
    Node<T>* tnode=root;
    Node<T>* parent=nullptr;
    while(tnode!=nullptr)
    {
        if(tnode->data==data)
            break;
        else if(tnode->data>data)
            parent=tnode,tnode=tnode->left;

        else
            parent=tnode,tnode=tnode->right;
    }
    if(tnode==nullptr)
        return 0;

    if(tnode->left==nullptr&&tnode->right==nullptr)
    {
        if(parent==nullptr)
            root=nullptr;
        else if(parent->left==tnode)
            parent->left=nullptr;
        else
            parent->right=nullptr;
    }
    else if(tnode->left!=nullptr&&tnode->right!=nullptr)
    {
        Node<T>* snode=tnode->right;
        Node<T>* sparent=tnode;
        while(snode->left!=nullptr)
        {
            sparent=snode;
            snode=snode->left;
        }
        tnode->data=snode->data;
        if(sparent->left==snode)
            sparent->left=snode->right;
        else
            sparent->right=snode->right;
        tnode = snode;
    }
    else
    {
        Node<T>* child=(tnode->left!=nullptr)?tnode->left:tnode->right;
        if(parent==nullptr)
            root=child;
        else if(parent->left==tnode)
            parent->left=child;
        else
            parent->right=child;
    }
    delete tnode;
    return 1;
}

template<class T>
vector<T> BinSortTree<T>::PreOrder()
{
    vector<T> res;
    stack<Node<T>*> s;
    if(root==nullptr) return res;
    s.push(root);
    while(!s.empty())
    {
        Node<T>* u=s.top();s.pop();
        res.push_back(u->data);
        if(u->right!=nullptr) s.push(u->right);
        if(u->left!=nullptr) s.push(u->left);
    }
    return res;
}
template<class T>
vector<T> BinSortTree<T>::InOrder()
{
    vector<T> res;
    stack<Node<T>*> s;
    Node<T>* u=root;
    while(u!=nullptr||!s.empty())
    {
        while(u!=nullptr)
        {
            s.push(u);
            u=u->left;
        }
        u=s.top();s.pop();
        res.push_back(u->data);
        u=u->right;
    }
    return res;
}
template<class T>
vector<T> BinSortTree<T>::PostOrder()
{
    vector<T> res;
    stack<Node<T>*> s;
    if(root==nullptr) return res;
    s.push(root);
    while(!s.empty())
    {
        Node<T>* u=s.top();s.pop();
        res.push_back(u->data);
        if(u->left!=nullptr) s.push(u->left);
        if(u->right!=nullptr) s.push(u->right);
    }
    reverse(res.begin(),res.end());
    return res;
}
template<class T>
vector<T> BinSortTree<T>::LevelOrder()
{
    vector<T> res;
    queue<Node<T>*> q;
    if(root==nullptr) return res;
    q.push(root);
    while(!q.empty())
    {
        Node<T>* u=q.front();q.pop();
        res.push_back(u->data);
        if(u->left!=nullptr) q.push(u->left);
        if(u->right!=nullptr) q.push(u->right);
    }
    return res;
}

template<class T>
void BinSortTree<T>::PreOrder(Node<T>* u,vector<T>& res)
{    if(u==nullptr) return;
    res.push_back(u->data);
    PreOrder(u->left,res);
    PreOrder(u->right,res);
}

template<class T>
void BinSortTree<T>::InOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    InOrder(u->left,res);
    res.push_back(u->data);
    InOrder(u->right,res);
}
template<class T>
void BinSortTree<T>::PostOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    PostOrder(u->left,res);
    PostOrder(u->right,res);
    res.push_back(u->data);
}