#include<bits/stdc++.h>
using namespace std;

template<class T>
void BubbleSort(vector<T>& arr)
{
    int n=arr.size();
    for(int i=0;i<n-1;i++)
    {
        bool f=0;
        for(int j=0;j<n-1-i;j++)
            if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]),f=1;
        if(!f) break;
    }
}
template<class T>
void QuickSort(vector<T>& arr,int l,int r)
{
    if(l>=r) return;
    int p=arr[l],i=l,j=r;
    while(i<j)
    {
        while(i<j&&arr[j]>=p) j--;
        if(i<j) arr[i++]=arr[j];
        while(i<j&&arr[i]<=p) i++;
        if(i<j) arr[j--]=arr[i];
    }
    arr[i]=p;
    QuickSort(arr,l,i);
    QuickSort(arr,i+1,r);
}

void Print(vector<int>& arr)
{
    for(int i=0;i<arr.size();i++)
    {
        cout<<arr[i];
        i==arr.size()-1?cout<<endl:cout<<" ";
    }
}
