#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    T data;
    int left,right;
    Node():data(0),left(-1),right(-1){}
    
};
template<class T>
class SqBintree{
    private:
        Node<T>* tree;
        int root,MaxSize;

    public:
        SqBintree():root(-1),MaxSize(1e4) {tree=new Node<T>[MaxSize];}
        SqBintree(int maxsize):root(-1),MaxSize(maxsize) {tree=new Node<T>[MaxSize];}        
        void InitSqBintree(){MaxSize=1e4,root=-1,tree=new Node<T>[MaxSize];}
        void InitSqBintree(int maxsize){MaxSize=maxsize,root=-1,tree=new Node<T>[MaxSize];}

        void CreateSqBintree(int idx,T data);
        void CreateSqBintree(int idx,T data,int left,int right);

        vector<T> PreOrder();
        vector<T> InOrder();
        vector<T> PostOrder();
        vector<T> LevelOrder();

        void PreOrder(int u,vector<T>& res);
        void InOrder(int u,vector<T>& res);
        void PostOrder(int u,vector<T>& res);
};

template<class T>
void SqBintree<T>::CreateSqBintree(int idx,T data,int left,int right)
{
    if(root==-1) root=0;
    tree[idx].data=data;
    tree[idx].left=left;
    tree[idx].right=right;
}
template<class T>
void SqBintree<T>::CreateSqBintree(int idx,T data)
{
    if(root==-1) root=0;
    tree[idx].data=data;
    tree[idx].left=-1;
    tree[idx].right=-1;
}

template<class T>
vector<T> SqBintree<T>::PreOrder()
{
    vector<T> res;
    stack<int> s;
    if(root==-1) return res;
    s.push(root);
    while(!s.empty())
    {
        int u=s.top();s.pop();
        res.push_back(tree[u].data);
        if(tree[u].right!=-1) s.push(tree[u].right);
        if(tree[u].left!=-1) s.push(tree[u].left);
    }
    return res;
}

template<class T>
vector<T> SqBintree<T>::InOrder()
{
    vector<T> res;
    stack<int> s;
    int u=root;
    while(u!=-1||!s.empty())
    {
        while(u!=-1)
        {
            s.push(u);
            u=tree[u].left;
        }
        u=s.top();s.pop();
        res.push_back(tree[u].data);
        u=tree[u].right;
    }
    return res;
}   
template<class T>
vector<T> SqBintree<T>::PostOrder()
{
    vector<T> res;
    stack<int> s;
    if(root==-1) return res;
    s.push(root);
    while(!s.empty())
    {
        int u=s.top();s.pop();
        res.push_back(tree[u].data);
        if(tree[u].left!=-1) s.push(tree[u].left);
        if(tree[u].right!=-1) s.push(tree[u].right);
    }
    reverse(res.begin(),res.end());
    return res;
}

template<class T>
vector<T> SqBintree<T>::LevelOrder()
{
    vector<T> res;
    queue<int> q;
    if(root==-1) return res;
    q.push(root);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        res.push_back(tree[u].data);
        if(tree[u].left!=-1) q.push(tree[u].left);
        if(tree[u].right!=-1) q.push(tree[u].right);
    }
    return res;
}

template<class T>
void SqBintree<T>::PreOrder(int u,vector<T>& res)
{
    if(u==-1) return;
    res.push_back(tree[u].data);
    PreOrder(tree[u].left,res);
    PreOrder(tree[u].right,res);
}

template<class T>
void SqBintree<T>::InOrder(int u,vector<T>& res)
{
    if(u==-1) return;
    InOrder(tree[u].left,res);
    res.push_back(tree[u].data);
    InOrder(tree[u].right,res);
}

template<class T>
void SqBintree<T>::PostOrder(int u,vector<T>& res)
{
    if(u==-1) return;
    PostOrder(tree[u].left,res);
    PostOrder(tree[u].right,res);
    res.push_back(tree[u].data);
}
