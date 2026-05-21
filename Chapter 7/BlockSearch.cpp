#include<bits/stdc++.h>
using namespace std;

template<class T>
class BlockSearch{
private:
    vector<T> data;
    int blockSize;
    vector<pair<int, int>> idx_table;
    int SqSearchBlock(int target,int &comparisons);
    int BinSearchBlock(int target,int &comparisons);

public:
    BlockSearch(vector<T> d,int blockSize):data(d),blockSize(blockSize){}
    void BuildIndex();
    int Search(int target, int& comparisons, int method=0);
};

template<class T>
int BlockSearch<T>::SqSearchBlock(int target,int &comparisons)
{
    for(int i=0;i<idx_table.size();i++)
    {
        comparisons++;
        if(idx_table[i].first>=target)
            return i;
    }
    return -1;
}

template<class T>
int BlockSearch<T>::BinSearchBlock(int target,int &comparisons)
{

    int l=0, r=idx_table.size()-1;
    while(l<=r)
    {
        int mid=(l+r)/2;
        comparisons++;
        if(idx_table[mid].first>=target)
            r=mid-1;
        else
            l=mid+1;
    }

    if(l>=idx_table.size()) return -1;
    return l;
}

template<class T>
void BlockSearch<T>::BuildIndex()
{   
    for(int i=0;i<data.size();i+=blockSize)
    {
        int end=min(i+blockSize,(int)data.size());
        int tmax=*max_element(data.begin()+i, data.begin()+end);
        idx_table.push_back({tmax,i});
    }
}

template<class T>
int BlockSearch<T>::Search(int target,int& comparisons,int method)
{
    int BlockIdx;
    if(method==0)
        BlockIdx=SqSearchBlock(target,comparisons);
    else
        BlockIdx=BinSearchBlock(target,comparisons);
        
    if(BlockIdx==-1) return -1;
    
    int start=idx_table[BlockIdx].second;
    int end=min(start+blockSize,(int)data.size());
    
    for(int i=start;i<end;i++)
    {
        comparisons++;
        if(data[i]==target)
            return i;
    }
    return -1;
}