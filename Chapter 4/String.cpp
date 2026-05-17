#include<bits/stdc++.h>
using namespace std;

void copy(char *dest, const char *src)
{
    while(*src)
        *dest++ = *src++;
    *dest = '\0';
}
bool compare(char *s1,char *s2)
{
    while(*s1&&*s2&&*s1==*s2)
        s1++,s2++;
    if(*s1==*s2)
        return 0;
    else if(*s1<*s2)
        return -1;
    else
        return 1;
}

class String{
private:
    char *str;
    int len;
public:
    String(){str = nullptr; len=0;}
    String(char *s):len(strlen(s)) {str=new char[len+1];copy(str,s);}
    void InitString(){str=nullptr; len=0;}
    void InitString(char *s){len=strlen(s);str=new char[len+1];copy(str,s);}
    void DestroyString() {delete[] str;str=nullptr;len=0;}
    ~String(){ delete[] str;}

    void Assign(char *s){DestroyString(); InitString(s);}
    void Copy(String &s){DestroyString(); InitString(s.str);}

    int Length(){return len;}
    bool Empty(){return len==0;}
    void Clear(){DestroyString();}

    int Compare(String &s){return compare(str,s.str);}
    void Concat(String &s1);
    String SubString(int pos,int len);
    char Index(int idx){return str[idx-1];}
    int Find(String &s);
    void Print(){cout<<str<<endl;}
};
void String::Concat(String &s1)
{
    char *tstr=new char[len+s1.len+1];
    copy(tstr,this->str);
    copy(tstr+len,s1.str);
    delete[] str;
    str=tstr;
    len=len+s1.len;
}
String String::SubString(int pos, int len)
{
    if(pos<1||pos>this->len||len<0||pos+len-1>this->len)
        return String();

    char *substr=new char[len+1];
    for(int i=0;i<len;i++)
        substr[i]=str[pos+i-1];
    substr[len]='\0';
    String s(substr);
    delete[] substr;
    return s;
}
// KMP algorithm
int String::Find(String &s)
{
    vector<int> Next(s.len,-1);
    for(int i=1,j=-1;i<s.len;i++)
    {
        while(j>=0&&s.str[j+1]!=s.str[i])
            j=Next[j];
        if(s.str[j+1]==s.str[i])
            j++;
        Next[i]=j;
    }
    for(int i=0,j=-1;i<len;i++)
    {
        while(j>=0&&s.str[j+1]!=str[i])
            j=Next[j];
        if(s.str[j+1]==str[i])
            j++;
        if(j==s.len-1)
            return i-s.len+2;
    }
    return 0;
}