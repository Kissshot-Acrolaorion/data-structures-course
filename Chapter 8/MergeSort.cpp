#include<bits/stdc++.h>
using namespace std;

template<class T>
void MergeSort(vector<T>& arr,int l,int r)
{
    if(l>=r) return;
    int mid=(l+r)>>1;

    MergeSort(arr,l,mid);
    MergeSort(arr,mid+1,r);

    vector<T> tmp(r-l+1);
    int i=l,j=mid+1,k=0;

    while(i<=mid&&j<=r)
        tmp[k++]=arr[i]<=arr[j]?arr[i++]:arr[j++];

    while(i<=mid) tmp[k++]=arr[i++];
    while(j<=r) tmp[k++]=arr[j++];
    
    for(i=l;i<=r;i++)
        arr[i]=tmp[i-l];
}

void Print(vector<int>& arr)
{
    for(int i=0;i<arr.size();i++)
    {
        cout<<arr[i];
        i==arr.size()-1?cout<<endl:cout<<" ";
    }
}
