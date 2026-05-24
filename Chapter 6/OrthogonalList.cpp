#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int v;
    int w;
    Edge* hlink;
    Edge* vlink;
    Edge(int v,int w):v(v),w(w),hlink(nullptr),vlink(nullptr){}
};
struct Plot{
    int w;
    Edge* hlink;
    Edge* vlink;
};
class OrthogonalList{
private:
    int n;
    vector<Plot*> plots;
public:
    OrthogonalList(int n):n(n),plots(vector<Plot*>(n,nullptr)){}
    ~OrthogonalList();
    void AddEdge(int u,int v,int w);
    void RemoveEdge(int u,int v);
    int GetWeight(int u,int v);
};
OrthogonalList::~OrthogonalList()
{
    for(int i=0;i<n;i++)
    {
        Edge* cur=plots[i]->hlink;
        while(cur)
        {
            Edge* tmp=cur;
            cur=cur->hlink;
            delete tmp;
        }
    }
    for(int j=0;j<n;j++)
    {
        Edge* cur=plots[j]->vlink;
        while(cur)
        {
            Edge* tmp=cur;
            cur=cur->vlink;
            delete tmp;
        }
    }
    for(int i=0;i<n;i++)
        delete plots[i];
}
void OrthogonalList::AddEdge(int u,int v,int w)
{
    Edge* newEdge=new Edge(v,w);
    newEdge->hlink=plots[u]->hlink;
    plots[u]->hlink=newEdge;
    newEdge->vlink=plots[v]->vlink;
    plots[v]->vlink=newEdge;
}
void OrthogonalList::RemoveEdge(int u,int v)
{
    Edge* cur=plots[u]->hlink;
    Edge* prev=nullptr;
    while(cur)
    {
        if(cur->v==v)
        {
            if(prev)
                prev->hlink=cur->hlink;
            else
                plots[u]->hlink=cur->hlink;
            delete cur;
            break;
        }
        prev=cur;
        cur=cur->hlink;
    }
    cur=plots[v]->vlink;
    prev=nullptr;
    while(cur)
    {
        if(cur->v==u)
        {
            if(prev)
                prev->vlink=cur->vlink;
            else
                plots[v]->vlink=cur->vlink;
            delete cur;
            break;
        }
        prev=cur;
        cur=cur->vlink;
    }
}
int OrthogonalList::GetWeight(int u,int v)
{
    for(Edge* e=plots[u]->hlink;e;e=e->hlink)
    {
        if(e->v==v)
            return e->w;
    }
    return INF;
}
