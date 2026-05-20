#include<bits/stdc++.h>
using namespace std;


template<class T>
struct Node{
    T data;
    Node* left,*right;
    Node():data(0),left(nullptr),right(nullptr){}

};
template<class T>
class LinkBintree{
private:
    Node<T>* root;
    Node<T>* pre_in(vector<T> pre,vector<T> in);
    Node<T>* post_in(vector<T> post,vector<T> in);

public:
    LinkBintree():root(nullptr){}
    LinkBintree(Node<T>* r):root(r){}
    void InitLinkBintree(){root=nullptr;}
    void InitLinkBintree(Node<T>* r){root=r;}

    void CreateLinkBintree_pre_in(vector<T> pre,vector<T> in) {root=pre_in(pre,in);}
    void CreateLinkBintree_post_in(vector<T> post,vector<T> in) {root=post_in(post,in);}
    
    vector<T> PreOrder();
    vector<T> InOrder();
    vector<T> PostOrder();
    vector<T> LevelOrder();

    void PreOrder(Node<T>* u,vector<T>& res);
    void InOrder(Node<T>* u,vector<T>& res);
    void PostOrder(Node<T>* u,vector<T>& res);

};


template<class T>
Node<T>* LinkBintree<T>::pre_in(vector<T> pre,vector<T> in)
{
    if(pre.empty()||in.empty()) return nullptr;
    int root_idx=find(in.begin(),in.end(),pre[0])-in.begin();
    Node<T>* node=new Node<T>();
    node->data=pre[0];
    node->left = LinkBintree<T>::pre_in(vector<T>(pre.begin()+1,pre.begin()+1+root_idx),vector<T>(in.begin(),in.begin()+root_idx));
    node->right = LinkBintree<T>::pre_in(vector<T>(pre.begin()+1+root_idx,pre.end()),vector<T>(in.begin()+root_idx+1,in.end()));
    return node;
}

template<class T>
Node<T>* LinkBintree<T>::post_in(vector<T> post,vector<T> in)
{
    if(post.empty()||in.empty()) return nullptr;
    int root_idx=find(in.begin(),in.end(),post.back())-in.begin();
    Node<T>* node=new Node<T>();
    node->data=post.back();
    node->left = LinkBintree<T>::post_in(vector<T>(post.begin(),post.begin()+root_idx),vector<T>(in.begin(),in.begin()+root_idx));
    node->right = LinkBintree<T>::post_in(vector<T>(post.begin()+root_idx,post.end()-1),vector<T>(in.begin()+root_idx+1,in.end()));
    return node;
}

template<class T>
vector<T> LinkBintree<T>::PreOrder()
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
vector<T> LinkBintree<T>::InOrder()
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
vector<T> LinkBintree<T>::PostOrder()
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
vector<T> LinkBintree<T>::LevelOrder()
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
void LinkBintree<T>::PreOrder(Node<T>* u,vector<T>& res)
{    if(u==nullptr) return;
    res.push_back(u->data);
    PreOrder(u->left,res);
    PreOrder(u->right,res);
}

template<class T>
void LinkBintree<T>::InOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    InOrder(u->left,res);
    res.push_back(u->data);
    InOrder(u->right,res);
}
template<class T>
void LinkBintree<T>::PostOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    PostOrder(u->left,res);
    PostOrder(u->right,res);
    res.push_back(u->data);
}
