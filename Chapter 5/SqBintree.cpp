#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    T data;
    int left,right;
    Node():data(0),left(-1),right(-1){}
    
};
template<class T>
class SqBinTree{
    private:
        Node<T>* tree;
        int root,MaxSize;
        int pre_in(vector<T> pre,vector<T> in,int step);
        int post_in(vector<T> post,vector<T> in,int step);

    public:
        SqBinTree():root(-1),MaxSize(1e4) {tree=new Node<T>[MaxSize];}
        SqBinTree(int maxsize):root(-1),MaxSize(maxsize) {tree=new Node<T>[MaxSize];}        
        void InitSqBinTree(){MaxSize=1e4,root=-1,tree=new Node<T>[MaxSize];}
        void InitSqBinTree(int maxsize){MaxSize=maxsize,root=-1,tree=new Node<T>[MaxSize];}

        void AddSqBinTree(int idx,T data);
        void AddSqBinTree(int idx,T data,int left,int right);
        void CreateSqBinTree_pre_in(vector<T> pre,vector<T> in){root=pre_in(pre,in,0);}
        void CreateSqBinTree_post_in(vector<T> post,vector<T> in){root=post_in(post,in,0);}
        vector<T> PreOrder();
        vector<T> InOrder();
        vector<T> PostOrder();
        vector<T> LevelOrder();

        void PreOrder(int u,vector<T>& res);
        void InOrder(int u,vector<T>& res);
        void PostOrder(int u,vector<T>& res);
};
template<class T>
int SqBinTree<T>::pre_in(vector<T> pre,vector<T> in,int step)
{
    if(pre.empty()) return -1;
    Node<T>* newnode=new Node<T>();
    int root_idx=-1;
    for(size_t i=0;i<in.size();i++)
    {
        if(in[i]==pre[0])
        {
            root_idx=i;break;
        }
    }

    newnode->data=pre[0];
    newnode->left=SqBinTree<T>::pre_in(vector<T>(pre.begin()+1,pre.begin()+1+root_idx),vector<T>(in.begin(),in.begin()+root_idx),2*step+1);
    newnode->right=SqBinTree<T>::pre_in(vector<T>(pre.begin()+1+root_idx,pre.end()),vector<T>(in.begin()+root_idx+1,in.end()),2*step+2);
    tree[step]=*newnode;
    return step;
}
template<class T>
int SqBinTree<T>::post_in(vector<T> post,vector<T> in,int step)
{
    if(post.empty()) return -1;
    Node<T>* newnode=new Node<T>();
    int root_idx=-1;
    for(size_t i=0;i<in.size();i++)
    {
        if(in[i]==post.back())
        {
            root_idx=i;break;
        }
    }
   
    newnode->data=post.back();
    newnode->left=SqBinTree<T>::post_in(vector<T>(post.begin(),post.begin()+root_idx),vector<T>(in.begin(),in.begin()+root_idx),2*step+1);
    newnode->right=SqBinTree<T>::post_in(vector<T>(post.begin()+root_idx,post.end()-1),vector<T>(in.begin()+root_idx+1,in.end()),2*step+2);
    tree[step]=*newnode;
    return step;
}

template<class T>
void SqBinTree<T>::AddSqBinTree(int idx,T data,int left,int right)
{
    if(root==-1) root=0;
    tree[idx].data=data;
    tree[idx].left=left;
    tree[idx].right=right;
}
template<class T>
void SqBinTree<T>::AddSqBinTree(int idx,T data)
{
    if(root==-1) root=0;
    tree[idx].data=data;
    tree[idx].left=-1;
    tree[idx].right=-1;
}

template<class T>
vector<T> SqBinTree<T>::PreOrder()
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
vector<T> SqBinTree<T>::InOrder()
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
vector<T> SqBinTree<T>::PostOrder()
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
vector<T> SqBinTree<T>::LevelOrder()
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
void SqBinTree<T>::PreOrder(int u,vector<T>& res)
{
    if(u==-1) return;
    res.push_back(tree[u].data);
    PreOrder(tree[u].left,res);
    PreOrder(tree[u].right,res);
}

template<class T>
void SqBinTree<T>::InOrder(int u,vector<T>& res)
{
    if(u==-1) return;                   
    InOrder(tree[u].left,res);
    res.push_back(tree[u].data);
    InOrder(tree[u].right,res);
}

template<class T>
void SqBinTree<T>::PostOrder(int u,vector<T>& res)
{
    if(u==-1) return;
    PostOrder(tree[u].left,res);
    PostOrder(tree[u].right,res);
    res.push_back(tree[u].data);
}