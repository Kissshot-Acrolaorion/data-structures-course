#include<bits/stdc++.h>
using namespace std;

template<class T>
void StraightInsertSort(vector<T>& arr)
{
    int n=arr.size();
    int i,j;
    for(i=1;i<n;i++)
    {
        T key=arr[i];
        for(j=i-1;j>=0&&arr[j]>key;j--)
            arr[j+1]=arr[j];
        arr[j+1]=key;
    }
}

template<class T>
void BinaryInsertSort(vector<T>& arr)
{
    int n=arr.size();
    int i,j;
    for(i=1;i<n;i++)
    {
        T key=arr[i];
        int l=0,r=i-1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(arr[mid]>key)
                r=mid-1;
            else
                l=mid+1;
        }
        for(j=i-1;j>=l;j--)
            arr[j+1]=arr[j];
        arr[l]=key;
    }
}

template<class T>
void ShellSort(vector<T>& arr,int gap)
{
    int n=arr.size();
    for(int gap=n/2;gap>0;gap/=2)
    {
        for(int i=gap;i<n;i++)
        {
            T key=arr[i];
            int j;
            for(j=i-gap;j>=0&&arr[j]>key;j-=gap)
                arr[j+gap]=arr[j];
            arr[j+gap]=key;
        }
    }
}