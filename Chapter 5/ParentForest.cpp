#include<bits/stdc++.h>
using namespace std;

template<class T>
struct node{
    T data;
    int parent;
    node():data(0),parent(-1){}
    node(T data):data(data),parent(-1){}
};

template<class T>
class ParentForest{
private:
    node<T> *data;
    int MaxSize;
public:
    ParentForest():MaxSize(1e4){data=new node<T>[MaxSize];}
    ParentForest(int maxsize):MaxSize(maxsize){data=new node<T>[MaxSize];}
    void InitParentForest(){MaxSize=1e4,data=new node<T>[MaxSize];}
    void InitParentForest(int maxsize){MaxSize=maxsize,data=new node<T>[MaxSize];}
    void DestroyParentForest(){delete []data;}
    ~ParentForest(){delete []data;}

    T getNode(int id){return data[id].data;}
    int getParent(int id){return data[id].parent;}
    void setParent(int id, int parent){data[id].parent=parent;}
    void setValue(int id, T value){data[id].data=value;}
    void setNode(int id, T value, int parent=-1){data[id].data=value; data[id].parent=parent;}
    int getRoot(int id)
    {
        if(data[id].parent==-1) return id;
        return data[id].parent=getRoot(data[id].parent);
    }
};
