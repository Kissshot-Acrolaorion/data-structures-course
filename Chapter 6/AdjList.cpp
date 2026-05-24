#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define pq priority_queue
#define PII pair<int,int>
struct Edge{
    int v;
    int w;
    Edge* next;
    Edge(int v,int w):v(v),w(w),next(nullptr){}
};

class AdjList{
private:
    int n;
    vector<Edge*> adj;
    void DFS(int u,bool *vis,vector<int> &res);
    void BFS(int u,bool *vis,vector<int> &res);
    void DijkstraDist(int s,vector<int> &dist,vector<int> &prev);
    void FloydDist(vector<vector<int>> &dist);
    
public:
    AdjList(int n):n(n),adj(vector<Edge*>(n,nullptr)){}
    ~AdjList();
    void AddEdge(int u,int v,int w);
    void RemoveEdge(int u,int v);
    int GetWeight(int u,int v);
    vector<int> DFSTraverse();
    vector<int> BFSTraverse();
    void print();

    void Dijkstra(int st,int ed);
    void Floyd(int st,int ed);
    void Prim();
    void Kruskal();
    vector<int> TopologicalSort();
};

void AdjList::print()
{
    for(int i=0;i<n;i++)
    {
        cout<<i<<": ";
        for(Edge* e=adj[i];e;e=e->next)
            cout<<"("<<e->v<<","<<e->w<<") ";
        cout<<endl;
    }
}

int AdjList::GetWeight(int u,int v)
{
    for(Edge* e=adj[u];e;e=e->next)
    {
        if(e->v==v)
            return e->w;
    }
    return INF;
}


AdjList::~AdjList()
{
    for(int i=0;i<n;i++)
    {
        Edge* cur=adj[i];
        while(cur)
        {
            Edge* tmp=cur;
            cur=cur->next;
            delete tmp;
        }
    }
}

void AdjList::AddEdge(int u,int v,int w)
{
    Edge* newEdge=new Edge(v,w);
    newEdge->next=adj[u];
    adj[u]=newEdge;
}


void AdjList::RemoveEdge(int u,int v)
{
    Edge* cur=adj[u];
    Edge* prev=nullptr;
    while(cur)
    {
        if(cur->v==v)
        {
            if(prev)
                prev->next=cur->next;
            else
                adj[u]=cur->next;
            delete cur;
            return;
        }
        prev=cur;
        cur=cur->next;
    }
}


void AdjList::BFS(int u,bool *vis,vector<int> &res)
{
    queue<int> q;
    q.push(u);
    vis[u]=true;
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        res.push_back(cur);
        for(Edge* e=adj[cur];e;e=e->next)
        {
            if(!vis[e->v])
            {
                q.push(e->v);
                vis[e->v]=true;
            }
        }
    }
}

vector<int> AdjList::BFSTraverse()
{
    bool *vis=new bool[n];
    memset(vis,false,sizeof(bool)*n);
    vector<int> res;
    for(int i=0;i<n;i++)
    {
        if(!vis[i])
            BFS(i,vis,res);
    }
    delete[] vis;
    return res;
}


void AdjList::DFS(int u,bool *vis,vector<int> &res)
{
    vis[u]=true;
    res.push_back(u);
    for(Edge* e=adj[u];e;e=e->next)
    {
        if(!vis[e->v])
            DFS(e->v,vis,res);
    }
}

vector<int> AdjList::DFSTraverse()
{
    bool *vis=new bool[n];
    memset(vis,false,sizeof(bool)*n);
    vector<int> res;
    for(int i=0;i<n;i++)
    {
        if(!vis[i])
            DFS(i,vis,res);
    }
    delete[] vis;
    return res;
}

void AdjList::DijkstraDist(int s,vector<int> &dist,vector<int> &prev)
{
    dist.assign(n,INF);
    prev.assign(n,-1);
    dist[s]=0;
    pq<PII,vector<PII>,greater<PII>> pq;
    pq.push({0,s});
    while(!pq.empty())
    {
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])
            continue;
        for(Edge* e=adj[u];e;e=e->next)
        {
            int v=e->v,w=e->w;
            if(dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                prev[v]=u;
                pq.push({dist[v],v});
            }
        }
    }
}
void AdjList::Dijkstra(int st,int ed)
{
    vector<int> dist;
    vector<int> prev,path;
    DijkstraDist(st,dist,prev);
    for(int v=ed;v!=-1;v=prev[v])
        path.push_back(v);
    reverse(path.begin(),path.end());

    if(dist[ed]==INF)
        cout<<"No path from "<<st<<" to "<<ed<<endl;
    else
    {
        cout<<"Shortest path from "<<st<<" to "<<ed<<": ";
        for(int i=0;i<path.size();i++)
        {
            cout<<path[i];
            i!=path.size()-1?cout<<" -> ":cout<<endl;
        }
    }
}
void AdjList::FloydDist(vector<vector<int>> &dist)
{
    dist.assign(n,vector<int>(n,INF));
    for(int i=0;i<n;i++)
        dist[i][i]=0;
    for(int u=0;u<n;u++)
    {
        for(Edge* e=adj[u];e;e=e->next)
        {
            int v=e->v,w=e->w;
            dist[u][v]=w;
        }
    }
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist[i][k]!=INF&&dist[k][j]!=INF&&dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
}
void AdjList::Floyd(int st,int ed)
{
    vector<vector<int>> dist;
    FloydDist(dist);
    if(dist[st][ed]==INF)
        cout<<"No path from "<<st<<" to "<<ed<<endl;
    else
        cout<<"Shortest distance from "<<st<<" to "<<ed<<" is "<<dist[st][ed]<<endl;
}

vector<int> AdjList::TopologicalSort()
{
    vector<int> inDegree(n,0);
    for(int u=0;u<n;u++)
    {
        for(Edge* e=adj[u];e;e=e->next)
            inDegree[e->v]++;
    }
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        if(inDegree[i]==0)
            q.push(i);
    }

    vector<int> topoOrder;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        topoOrder.push_back(u);
        for(Edge* e=adj[u];e;e=e->next)
        {
            int v=e->v;
            inDegree[v]--;
            if(inDegree[v]==0)
                q.push(v);
        }
    }
    if(topoOrder.size()!=n)
        return vector<int>();
    return topoOrder;
}
