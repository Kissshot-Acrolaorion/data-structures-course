#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

class AdjMatrix{
private:
    int n;
    int **adj;
    void DFS(int u,bool *vis,vector<int> &res);
    void BFS(int u,bool *vis,vector<int> &res);
public:
    AdjMatrix(int n);
    ~AdjMatrix();
    void AddEdge(int u,int v,int w){adj[u][v]=w;}
    void RemoveEdge(int u,int v){adj[u][v]=INF;}
    int GetWeight(int u,int v){return adj[u][v];}
    void print();
    vector<int> DFSTraverse();
    vector<int> BFSTraverse();
    
};

void AdjMatrix::BFS(int u,bool *vis,vector<int> &res)
{
    queue<int> q;
    q.push(u);
    vis[u]=true;
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        res.push_back(cur);
        for(int v=0;v<n;v++)
        {
            if(adj[cur][v]!=INF&&!vis[v])
            {
                q.push(v);
                vis[v]=true;
            }
        }
    }
}

vector<int> AdjMatrix::BFSTraverse()
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


void AdjMatrix::DFS(int u,bool *vis,vector<int> &res)
{
    vis[u]=true;
    res.push_back(u);
    for(int v=0;v<n;v++)
    {
        if(adj[u][v]!=INF&&!vis[v])
            DFS(v,vis,res);
    }
}


vector<int> AdjMatrix::DFSTraverse()
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


AdjMatrix::AdjMatrix(int n)
{
    this->n=n;
    adj=new int*[n];
    for(int i=0;i<n;i++)
    {
        adj[i]=new int[n];
        for(int j=0;j<n;j++)
            adj[i][j]=INF;
    }
}

AdjMatrix::~AdjMatrix()
{
    for(int i=0;i<n;i++)
        delete[] adj[i];
    delete[] adj;
}

void AdjMatrix::print()
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(adj[i][j]==INF)
                cout<<"INF";
            else
                cout<<adj[i][j];
            j==n-1?cout<<endl:cout<<" ";
        }
       
    }
}
