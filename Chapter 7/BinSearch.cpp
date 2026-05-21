#include<bits/stdc++.h>
using namespace std;

template<class T>
int BinSearch(vector<T> arr,int target)
{
    int l=0,r=arr.size()-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(arr[mid]==target) 
            return mid;
        else if(arr[mid]>target) 
            r=mid-1;
        else 
            l=mid+1;
    }
    return -1;
}
