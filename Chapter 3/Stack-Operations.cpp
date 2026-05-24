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
double GetNum(string s)
{
    double ans=0;
    for(char c:s)
    {
        if(c>='0'&&c<='9') ans=ans*10+c-'0';
        else if(c=='.')
        {
            double t=1;
            for(int i=s.find('.')+1;i<s.size();i++)
            {
                t/=10;
                ans+=(s[i]-'0')*t;
            }
            break;
        }
    }
    return ans;
}
int GetPriority(char c)
{
    if(c=='+'||c=='-') return 1;
    else if(c=='*'||c=='/') return 2;
    else return 0;
}
string GetPost(string s) 
{
    string ans;
    Stack<char> st;
    for (int i=0;i<s.size();i++)
    {   
        
        if((s[i]>='0'&&s[i]<='9')||s[i]=='.')
        {
            int j=i;
            while(j<s.size()&&(s[j]>='0'&&s[j]<='9'||s[j]=='.')) j++;
            ans+=s.substr(i,j-i)+' ';
            i=j-1;
        }
        else if(s[i]=='(') st.Push(s[i]);
        else if(s[i]==')')
        {
            while(!st.Empty()&&st.Top()!='(')
            {
                ans+=st.Top();
                st.Pop();
            }
            st.Pop();
        }
        else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
        {
            
            while(!st.Empty()&&GetPriority(st.Top())>=GetPriority(s[i]))
            {
                ans+=st.Top();
                st.Pop();
            }
            st.Push(s[i]);
        }
    } 
    while(!st.Empty())
    {
        ans+=st.Top();
        st.Pop();
    }
    //cout<<ans<<endl;
    return ans;
}
double GetAns(string s)
{
    Stack<double> st;
    for(int i=0;i<s.size();i++)
    {
        if((s[i]>='0'&&s[i]<='9')||s[i]=='.')
        {
            int j=i;
            while(j<s.size()&&(s[j]>='0'&&s[j]<='9'||s[j]=='.')) j++;
            st.Push(GetNum(s.substr(i,j-i)));
            i=j-1;
        }
        else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
        {
            double b=st.Top(); st.Pop();
            double a=st.Top(); st.Pop();
           
            if(s[i]=='+') st.Push(a+b);
            else if(s[i]=='-') st.Push(a-b);
            else if(s[i]=='*') st.Push(a*b);
            else if(s[i]=='/') st.Push(a/b);
        }
    }
    return st.Top();
}
