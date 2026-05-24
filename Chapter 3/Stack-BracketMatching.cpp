#include <iostream>
#include <string>
using namespace std;
template<class T>
class Stack{
public:
    T *st;
    int top;
    Stack():top(-1),st(new T[100000]){}
    ~Stack() {delete[] st;}
    void Push(T x){st[++top]=x;}
    void Pop(){top--;}
    T Top(){return st[top];}
    bool Empty(){return top==-1;}
};

bool isValid(string s) 
{
    Stack<char> st;
    for(char c:s)
    {
        if(c=='('||c=='{'||c=='[') st.Push(c);
        else if(c==')'||c=='}'||c==']')
        {
            if(st.Empty()) return false;
            char top=st.Top();
            if((c==')'&&top=='(')||(c=='}'&&top=='{')||(c==']'&&top=='[')) st.Pop();
            else 
                return false;
        }
    }
    return st.Empty();
}