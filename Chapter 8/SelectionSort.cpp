#include<bits/stdc++.h>
using namespace std;

template<class T>
void SimpleSelectionSort(vector<T>& arr)
{
    int n=arr.size();
    for(int i=0;i<n-1;i++)
    {
        int minx=i;
        for(int j=i+1;j<n;j++)
            if(arr[j]<arr[minx])
                minx=j;
        swap(arr[i],arr[minx]);
    }
}
template<class T>
void HeapSort(vector<T>& arr)
{
    for(int i=arr.size()/2-1;i>=0;i--)
    {
        int u=i;
        while(2*u+1<arr.size())
        {
            int v=2*u+1;
            if(v+1<arr.size()&&arr[v+1]>arr[v]) v++;
            if(arr[u]>=arr[v]) break;
            swap(arr[u],arr[v]);
            u=v;
        }
    }
    for(int i=arr.size()-1;i>0;i--)
    {
        swap(arr[0],arr[i]);
        int u=0;
        while(2*u+1<i)
        {
            int v=2*u+1;
            if(v+1<i&&arr[v+1]>arr[v]) v++;
            if(arr[u]>=arr[v]) break;
            swap(arr[u],arr[v]);
            u=v;
        }
    }
}