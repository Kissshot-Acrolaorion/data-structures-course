#include<bits/stdc++.h>

template<class T>
int SqSearch(vector<T> arr,int target)
{
    for(size_t i=0;i<arr.size();i++)
        if(arr[i]==target) return i;
    return -1;
}


