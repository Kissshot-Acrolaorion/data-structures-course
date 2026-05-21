#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define pq priority_queue
template<class T>
struct Node{
    T data;
    Node* left,*right;
    Node():data(0),left(nullptr),right(nullptr){}

};

template<class T>
class HuffmanTree{
private:
    Node<T>* root;  
    string GetCode(Node<T>* u,T target,string path);
public:
    HuffmanTree():root(nullptr){}
    void BuildHuffmanTree(vector<T>& data,vector<int>& freq);

    void PreOrder(Node<T>* u,vector<T>& res);
    void InOrder(Node<T>* u,vector<T>& res);
    void PostOrder(Node<T>* u,vector<T>& res);

    vector<T> PreOrder();
    vector<T> InOrder();
    vector<T> PostOrder();
    vector<T> LevelOrder();

    string Code(T target){return GetCode(root,target,"");}
    
};
template<class T>
string HuffmanTree<T>::GetCode(Node<T>* u,T target,string path)
{
    if(u==nullptr) return "";
    if(u->data==target) return path;
    
    string left=GetCode(u->left,target,path+"0");
    if(left!="") return left;
    return GetCode(u->right,target,path+"1");
}

template<class T>
void HuffmanTree<T>::BuildHuffmanTree(vector<T>& data,vector<int>& freq)
{
    auto cmp=[](Node<T>* a,Node<T>* b){return a->data>b->data;};
    pq<Node<T>*,vector<Node<T>*>,decltype(cmp)> pq(cmp);
    for(int i=0;i<data.size();i++)
    {
        Node<T>* node=new Node<T>();
        node->data=freq[i];
        pq.push(node);
    }
    while(pq.size()>1)
    {
        Node<T>* left=pq.top();pq.pop();
        Node<T>* right=pq.top();pq.pop();
        Node<T>* parent=new Node<T>();
        parent->data=left->data+right->data;
        parent->left=left;
        parent->right=right;
        pq.push(parent);
    }
    root=pq.top();
}

template<class T>
vector<T> HuffmanTree<T>::PreOrder()
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
vector<T> HuffmanTree<T>::InOrder()
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
vector<T> HuffmanTree<T>::PostOrder()
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
vector<T> HuffmanTree<T>::LevelOrder()
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
void HuffmanTree<T>::PreOrder(Node<T>* u,vector<T>& res)
{    if(u==nullptr) return;
    res.push_back(u->data);
    PreOrder(u->left,res);
    PreOrder(u->right,res);
}

template<class T>
void HuffmanTree<T>::InOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    InOrder(u->left,res);
    res.push_back(u->data);
    InOrder(u->right,res);
}
template<class T>
void HuffmanTree<T>::PostOrder(Node<T>* u,vector<T>& res)
{
    if(u==nullptr) return;
    PostOrder(u->left,res);
    PostOrder(u->right,res);
    res.push_back(u->data);
}
