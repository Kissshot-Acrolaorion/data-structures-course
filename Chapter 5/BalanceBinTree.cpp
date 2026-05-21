#include<bits/stdc++.h>
using namespace std;

template<class T>
struct Node{
    T data;
    Node* left;
    Node* right;
    int height;
    Node(T data):data(data),left(nullptr),right(nullptr),height(0){}
    Node():data(T()),left(nullptr),right(nullptr),height(0){}
};

template<class T>
class BalanceBinTree{
private:
    Node<T>* root;
    int GetHeight(Node<T>* u){return u==nullptr?-1:u->height;}
    int GetBalanceFactor(Node<T>* u){return GetHeight(u->left)-GetHeight(u->right);}
    void Update(Node<T>* u){u->height=max(GetHeight(u->left),GetHeight(u->right))+1;}
    
    Node<T>* RightRotate(Node<T>* y);
    Node<T>* LeftRotate(Node<T>* x);

    Node<T>* InsertNode(Node<T>* u, T data);
    Node<T>* RemoveNode(Node<T>* u, T data);

    Node<T>* FindMin(Node<T>* u);

public:
    BalanceBinTree():root(nullptr){}
    void InitBalanceBinTree(){root=nullptr;}

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
Node<T>* BalanceBinTree<T>::RightRotate(Node<T>* y)
{
    //原理：以y为根的子树进行右旋，y的左子树x成为新的根，x的右子树T2成为y的左子树
    Node<T>* x=y->left;
    Node<T>* T2=x->right;
    
    x->right=y;
    y->left=T2;
    
    Update(y);
    Update(x);
    
    return x;
}

template<class T>
Node<T>* BalanceBinTree<T>::LeftRotate(Node<T>* x)
{
    //原理：以x为根的子树进行左旋，x的右子树y成为新的根，y的左子树T2成为x的右子树
    Node<T>* y=x->right;
    Node<T>* T2=y->left;
    
    y->left=x;
    x->right=T2;
    
    Update(x);
    Update(y);
    
    return y;
}

template<class T>
Node<T>* BalanceBinTree<T>::FindMin(Node<T>* u)
{
    while(u->left!=nullptr)
        u=u->left;
    return u;
}

template<class T>
Node<T>* BalanceBinTree<T>::InsertNode(Node<T>* u, T data)
{
    if(u==nullptr)
        return new Node<T>(data);
    
    if(data<u->data)
        u->left=InsertNode(u->left,data);
    else if(data>u->data)
        u->right=InsertNode(u->right,data);
    else
        return u;
    
    Update(u);
    
    int bf=GetBalanceFactor(u);
    
    if(bf>1&&data<u->left->data)
        return RightRotate(u);
    
    if(bf<-1&&data>u->right->data)
        return LeftRotate(u);
    
    if(bf>1&&data>u->left->data)
    {
        u->left=LeftRotate(u->left);
        return RightRotate(u);
    }
    
    if(bf<-1&&data<u->right->data)
    {
        u->right=RightRotate(u->right);
        return LeftRotate(u);
    }
    return u;
}

template<class T>
Node<T>* BalanceBinTree<T>::RemoveNode(Node<T>* u, T data)
{
    if(u==nullptr)
        return nullptr;
    
    if(data < u->data)
        u->left=RemoveNode(u->left, data);
    else if(data > u->data)
        u->right=RemoveNode(u->right, data);
    else
    {
        if(u->left==nullptr||u->right==nullptr)
        {
            Node<T>* temp=u->left?u->left:u->right;
            if(temp==nullptr)
            {
                temp=u;
                u=nullptr;
            }
            else
                *u=*temp;
            delete temp;
        }
        else
        {
            Node<T>* temp=FindMin(u->right);
            u->data=temp->data;
            u->right=RemoveNode(u->right, temp->data);
        }
    }
    
    if(u==nullptr)
        return nullptr;
    
    Update(u);
    
    int bf=GetBalanceFactor(u);
    
    if(bf>1&&GetBalanceFactor(u->left)>=0)
        return RightRotate(u);
    
    if(bf>1&&GetBalanceFactor(u->left)<0)
    {
        u->left=LeftRotate(u->left);
        return RightRotate(u);
    }
    
    if(bf<-1&&GetBalanceFactor(u->right)<=0)
        return LeftRotate(u);
    
    if(bf<-1&&GetBalanceFactor(u->right)>0)
    {
        u->right=RightRotate(u->right);
        return LeftRotate(u);
    }
    
    return u;
}

template<class T>
bool BalanceBinTree<T>::Check(T data)
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
bool BalanceBinTree<T>::Insert(T data)
{
    if(Check(data)) return 0;
    root=InsertNode(root, data);
    return 1;
}

template<class T>
bool BalanceBinTree<T>::Remove(T data)
{
    if(!Check(data)) return 0;
    root=RemoveNode(root, data);
    return 1;
}

template<class T>
vector<T> BalanceBinTree<T>::PreOrder()
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
vector<T> BalanceBinTree<T>::InOrder()
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
vector<T> BalanceBinTree<T>::PostOrder()
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
vector<T> BalanceBinTree<T>::LevelOrder()
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
void BalanceBinTree<T>::PreOrder(Node<T>* u,vector<T>& res)
{    if(u==nullptr) return;
    res.push_back(u->data);
    PreOrder(u->left,res);
    PreOrder(u->right,res);
}

template<class T>
void BalanceBinTree<T>::InOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    InOrder(u->left,res);
    res.push_back(u->data);
    InOrder(u->right,res);
}

template<class T>
void BalanceBinTree<T>::PostOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    PostOrder(u->left,res);
    PostOrder(u->right,res);
    res.push_back(u->data);
}