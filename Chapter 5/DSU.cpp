#include<bits/stdc++.h>
using namespace std;

class DSU{
private:
    int *data;
    int MaxSize;
    int *cnt;
public:
    DSU():MaxSize(1e4){data=new int[MaxSize]; cnt=new int[MaxSize];}
    DSU(int maxsize):MaxSize(maxsize){data=new int[MaxSize]; cnt=new int[MaxSize];}
    void InitDSU(){MaxSize=1e4,data=new int[MaxSize]; cnt=new int[MaxSize];}
    void InitDSU(int maxsize){MaxSize=maxsize,data=new int[MaxSize]; cnt=new int[MaxSize];}
    void DestroyDSU(){delete []data; delete []cnt;}
    ~DSU(){delete []data; delete []cnt;}

    void Initailize(){for(int i=0;i<MaxSize;i++) data[i]=-1, cnt[i]=1;}
    int Find(int x) {return data[x]=(data[x]<0?x:Find(data[x]));}
    int Size(int x){return cnt[Find(x)];}
    bool Union(int x,int y);
    
};

bool DSU::Union(int x,int y)
{
    int fx=Find(x), fy=Find(y);
    if(fx==fy) return 0;
    if(data[fx]>data[fy]) swap(fx,fy);
    data[fx]+=data[fy];
    cnt[fx]+=cnt[fy];
    data[fy]=fx;
    return 1;
}