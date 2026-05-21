#include<bits/stdc++.h>
using namespace std;

void RadixSort(vector<int>& arr)
{
    int n=arr.size();
    vector<int> buckets[10];

    for(int exp=1;exp<=1e9;exp*=10)
    {
        for(int i=0;i<n;i++)
            buckets[arr[i]/exp%10].push_back(arr[i]);
        int idx=0;
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<buckets[i].size();j++)
                arr[idx++]=buckets[i][j];
            buckets[i].clear();
        }
    }
}
