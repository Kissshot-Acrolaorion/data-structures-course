#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    T data;
    Node<T>* left,*right;
    int ltag,rtag;
    Node():data(0),left(nullptr),right(nullptr),ltag(0),rtag(0){}
    Node(T data):data(data),left(nullptr),right(nullptr),ltag(0),rtag(0){}   
};

template<class T>
class TreadBinTree{
    private:
        Node<T>* root;
        string OP;
        Node<T>* pre_in(vector<T> pre,vector<T> in);
        Node<T>* post_in(vector<T> post,vector<T> in);
        void InTread(Node<T>* u,Node<T>*& pre);
        void PreTread(Node<T>* u,Node<T>*& pre);
        void PostTread(Node<T>* u,Node<T>*& pre);

    public:
        TreadBinTree(string op="in"):root(nullptr),OP(op){}
        void InitTreadBinTree(string op="in"){root=nullptr,OP=op;}

        void CreateLinkBinTree_pre_in(vector<T> pre,vector<T> in);
        void CreateLinkBinTree_post_in(vector<T> post,vector<T> in);

        vector<T> Order();
        vector<T> PreOrder();
        vector<T> InOrder();
        vector<T> PostOrder();
        
};

template<class T>
vector<T> TreadBinTree<T>::Order()
{
    if(OP=="pre") return PreOrder();
    else if(OP=="in") return InOrder();
    else if(OP=="post") return PostOrder();
    return vector<T>();
}

template<class T>
void TreadBinTree<T>::CreateLinkBinTree_pre_in(vector<T> pre,vector<T> in)
{
    root=pre_in(pre,in);
    Node<T>* preNode = nullptr;
    if(OP=="pre") PreTread(root,preNode);
    else if(OP=="in") InTread(root,preNode);
    else if(OP=="post") PostTread(root,preNode);
}

template<class T>
void TreadBinTree<T>::CreateLinkBinTree_post_in(vector<T> post,vector<T> in)
{
    root=post_in(post,in);
    Node<T>* preNode = nullptr;
    if(OP=="pre") PreTread(root,preNode);
    else if(OP=="in") InTread(root,preNode);
    else if(OP=="post") PostTread(root,preNode);
}

template<class T>
Node<T>* TreadBinTree<T>::pre_in(vector<T> pre,vector<T> in)
{
    if(pre.empty()||in.empty()) return nullptr;
    int root_idx=find(in.begin(),in.end(),pre[0])-in.begin();
    Node<T>* node=new Node<T>(pre[0]);
    node->left = pre_in(vector<T>(pre.begin()+1,pre.begin()+1+root_idx),vector<T>(in.begin(),in.begin()+root_idx));
    node->right = pre_in(vector<T>(pre.begin()+1+root_idx,pre.end()),vector<T>(in.begin()+root_idx+1,in.end()));
    return node;
}

template<class T>
Node<T>* TreadBinTree<T>::post_in(vector<T> post,vector<T> in)
{
    if(post.empty()||in.empty()) return nullptr;
    int root_idx=find(in.begin(),in.end(),post.back())-in.begin();
    Node<T>* node=new Node<T>(post.back());
    node->left = post_in(vector<T>(post.begin(),post.begin()+root_idx),vector<T>(in.begin(),in.begin()+root_idx));
    node->right = post_in(vector<T>(post.begin()+root_idx,post.end()-1),vector<T>(in.begin()+root_idx+1,in.end()));
    return node;
}

template<class T>
void TreadBinTree<T>::InTread(Node<T>* u,Node<T>*& pre)
{
    if(u==nullptr) return;
    InTread(u->left,pre);
    
    if(u->left==nullptr)
        u->ltag=1,u->left=pre;
    else
        u->ltag=0;
    
    if(pre!=nullptr&&pre->right==nullptr)
        pre->rtag=1,pre->right=u;
    else if(pre!=nullptr)
        pre->rtag=0;
    
    pre=u;
    InTread(u->right,pre);
}

template<class T>
void TreadBinTree<T>::PreTread(Node<T>* u,Node<T>*& pre)
{
    if(u==nullptr) return;
    
    if(u->left==nullptr)
        u->ltag=1,u->left=pre;
    else
        u->ltag=0;
    
    if(pre!=nullptr && pre->right==nullptr)
        pre->rtag=1,pre->right=u;
    else if(pre!=nullptr)
        pre->rtag=0;
    
    pre=u;
    
    if(u->ltag==0) PreTread(u->left,pre);
    if(u->rtag==0) PreTread(u->right,pre);
}

template<class T>
void TreadBinTree<T>::PostTread(Node<T>* u,Node<T>*& pre)
{
    if(u==nullptr) return;
    
    PostTread(u->left,pre);
    PostTread(u->right,pre);
    
    if(u->left==nullptr)
        u->ltag=1,u->left=pre;
    else
        u->ltag=0;
    
    if(pre!=nullptr&&pre->right==nullptr)
        pre->rtag=1,pre->right=u;
    else if(pre!=nullptr)
        pre->rtag=0;

    pre=u;
}

template<class T>
vector<T> TreadBinTree<T>::InOrder()
{
    vector<T> res;
    if(root==nullptr) return res;
    
    Node<T> *u=root;
    while(u!=nullptr)
    {
        while(u->ltag==0&&u->left!=nullptr)
            u=u->left;
        
        res.push_back(u->data);
        
        while(u->rtag==1&&u->right!=nullptr)
        {
            u=u->right;
            res.push_back(u->data);
        }    
        u=u->right;
    }
    return res;
}

template<class T>
vector<T> TreadBinTree<T>::PreOrder()
{
    vector<T> res;
    if(root==nullptr) return res;
    
    Node<T> *u=root;
    while(u!=nullptr)
    {
        res.push_back(u->data);
        
        if(u->ltag==0&&u->left!=nullptr)
            u=u->left;
        else
            u=u->right;
    }
    return res;
}

// 后序线索二叉树的后序遍历较为复杂,弃坑
template<class T>
vector<T> TreadBinTree<T>::PostOrder()
{
    vector<T> res;
    if(root==nullptr) return res;
    
    stack<Node<T>*> st;
    st.push(root);
    
    while(!st.empty()) 
    {
        Node<T> *u=st.top();st.pop();
        res.push_back(u->data);
        
        if(u->ltag==0) 
            st.push(u->left);
        if(u->rtag==0) 
            st.push(u->right);
    }
    reverse(res.begin(),res.end());
    
    return res;
}