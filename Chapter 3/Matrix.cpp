#include<bits/stdc++.h>
using namespace std;    

template<class T>
class Matrix{
private:
    int row,col;
    T **data;
public:
    Matrix():row(0),col(0),data(nullptr){}
    Matrix(int r,int c):row(r),col(c){data=new T*[row];for(int i=0;i<row;i++) data[i]=new T[col]();}
    Matrix(const Matrix &m);
    void InitMatrix(int r,int c){row=r;col=c;data=new T*[row];for(int i=0;i<row;i++) data[i]=new T[col]();}
    void InitMatrix(){row=0;col=0;data=nullptr;}
    void DestroyMatrix(){for(int i=0;i<row;i++) delete[] data[i];delete[] data;InitMatrix();}
    void Clear(){DestroyMatrix();}
    ~Matrix(){DestroyMatrix();}
    
    void Copy(const Matrix &m);
    void set(int r, int c, T val){data[r][c]=val;}
    T get(int r, int c){return data[r][c];}

    Matrix<T> operator+(const T &scalar);
    Matrix<T> operator+(const Matrix &m);

    Matrix<T> operator*(const T &scalar);
    Matrix<T> operator*(const Matrix &m);

    Matrix<T> Transpose();
    Matrix<T> Negation();
    Matrix<T> Dot(const Matrix &m);
    void PrintMatrix();
};

template<class T>
Matrix<T>::Matrix(const Matrix &m)
{
    row=m.row;col=m.col;
    data=new T*[row];
    for(int i=0;i<row;i++)
    {
        data[i]=new T[col];
        for(int j=0;j<col;j++)
            data[i][j]=m.data[i][j];
    }
}

template<class T>
void Matrix<T>::Copy(const Matrix &m)
{
    DestroyMatrix();
    row=m.row;col=m.col;
    data=new T*[row];
    for(int i=0;i<row;i++)
    {
        data[i]=new T[col];
        for(int j=0;j<col;j++)
            data[i][j]=m.data[i][j];
    }
}

template<class T>
Matrix<T> Matrix<T>::operator+(const T &scalar)
{
    Matrix<T> res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.data[i][j]=data[i][j]+scalar;
    return res;
}
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix &m)
{
    if(row!=m.row || col!=m.col) return Matrix<T>();
    Matrix<T> res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.data[i][j]=data[i][j]+m.data[i][j];
    return res;
}
template<class T>
Matrix<T> Matrix<T>::operator*(const T &scalar)
{
    Matrix<T> res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.data[i][j]=data[i][j]*scalar;
    return res;
}
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix &m)
{
    Matrix<T> res(row,m.col);
    for(int i=0;i<row;i++)
        for(int j=0;j<m.col;j++)
            res.data[i][j]+=data[i][j]*m.data[i][j];
    return res;
}
template<class T>
Matrix<T> Matrix<T>::Transpose()
{
    Matrix<T> res(col,row);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.data[j][i]=data[i][j];
    return res;
}

template<class T>
Matrix<T> Matrix<T>::Negation()
{
    Matrix<T>  res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.data[i][j]=-data[i][j];
    return res;
}

template<class T>
Matrix<T> Matrix<T>::Dot(const Matrix &m)
{
    if(col!=m.row) return Matrix<T>();
    Matrix<T> res(row,m.col);
    for(int i=0;i<row;i++)
        for(int j=0;j<m.col;j++)
            for(int k=0;k<col;k++)
                res.data[i][j]+=data[i][k]*m.data[k][j];
    return res;
}
template<class T>
void Matrix<T>::PrintMatrix()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<data[i][j];
            if(j!=col-1) cout<<" ";
        }
        cout<<endl;
    }
}