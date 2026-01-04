#pragma once
#include <fstream>
#include <iostream>
using namespace std;
struct Matrix
{
    long double** mat;
    int row;
    int col;
    Matrix(int row,int col):row{row},col{col}
    {
        mat=new long double*[row];
        for(int i=0;i<row;i++)mat[i]=new long double[col];
    }
    Matrix(Matrix& a)
    {
        row=a.row;
        col=a.col;
        mat=new long double*[row];
        for(int i=0;i<row;i++)mat[i]=new long double[col];
        for(int i=0;i<row;i++)
           for(int j=0;j<col;j++)
               mat[i][j]=a.mat[i][j];
    }
    ~Matrix()
    {
      for(int i=0;i<row;i++)
      {
        delete[] mat[i];
      }
      delete[] mat;
    }

    void display()
    {
        ofstream chain("chain.txt");
        chain<<row<<' '<<col<<'\n';
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                chain<<mat[i][j]<<' ';
            }
            chain<<'\n';
        }
    }

    void clear()
    {
        for(int i=0;i<row;i++)
           for(int j=0;j<col;j++)
             mat[i][j]=0;
    }
    void clean()
    {
        for(int i=0;i<row;i++)
           for(int j=0;j<col;j++)
              mat[i][j]=max(mat[i][j],(long double)1e-6);
    }
};

Matrix& operator*(Matrix& a,Matrix& b)
{
 if(a.col!=b.row)return a;
 Matrix* c=new Matrix(a.row,b.col);
 for(int i=0;i<c->row;i++)
 {
    for(int j=0;j<c->col;j++)
    {
        long double sum=0;
        for(int k=0;k<a.row;k++)
        {
            sum+=a.mat[i][k]*b.mat[k][j];
        }
        c->mat[i][j]=sum;
    }
 }

 #ifdef DEBUG
 cout<<"Result of [0,0] after multiplication:"<<c->mat[0][0]<<endl;
 #endif
 
 return *c;
}


void operator*=(Matrix& a,Matrix& b)
{
  a=a*b;
}

Matrix& operator^(Matrix& a,int pow)
{
    Matrix* b=new Matrix(a);
    for(int i=1;i<pow;i++)*b*=a;
    return *b;
}

