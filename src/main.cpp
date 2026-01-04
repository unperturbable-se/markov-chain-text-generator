#define DEBUG 1
#include <iostream>
#include <fstream>
#include <sstream>
#include "matrix.h"
#include "hash.h"
#define size 7716
using namespace std;

void extractFromFile(Matrix*& markovChain) //error 
{
    ifstream f{"chain.txt"};
    int row;
    int col;
    f>>row>>col;
    int i=0;
    int temp{};
    markovChain=new Matrix(row,col);
    for(int i=0;i<row;i++)
       {
        for(int j=0;j<col;j++)
           {
             f>>temp;
             markovChain->mat[i][j]=temp;
           }
       }
}

void createProbabilities(Matrix& matrix)
{
    for(int i=0;i<matrix.row;i++)
    {
        long double sum=0;
        for(int j=0;j<matrix.col;j++)
           sum+=matrix.mat[i][j];
        if(sum==0)continue;
        for(int j=0;j<size;j++)
           matrix.mat[i][j]=matrix.mat[i][j]/sum;
    }
    matrix.clean();
}

Matrix* ExtractProbabilityVector(string token,Matrix& markovChain)
{
    int index=hashToken(token);
    Matrix* vec=new Matrix(1,size);
    for(int i=0;i<size;i++)
    vec->mat[0][i]=markovChain.mat[index][i];   
    return vec;
}

void predictText(string token,int n,Matrix& markovChain)
{
    Matrix a=*ExtractProbabilityVector(token,markovChain);
    string display=" ";
    for(int i=0;i<n;i++)
    {
    cout<<display<<' ';
    //cout<<' '<<a.mat[0][0]<<endl;
    int maxIndex=0;
    long double maxProb=a.mat[0][0];
    for(int i=1;i<size;i++)
        if(a.mat[0][i]>maxProb)
           {
            maxProb=a.mat[0][i];
            maxIndex=i;
           }
    display=dehashToken(maxIndex);
    a=a*markovChain;
    }
}

void predictText1(string token,int n,Matrix& markovChain)
{
    Matrix a=*ExtractProbabilityVector(token,markovChain);
    string display=" ";
    for(int i=0;i<n;i++)
    {
    cout<<display<<' ';
    int maxIndex=0;
    long double maxProb=a.mat[0][0];
    for(int i=1;i<size;i++)
        if(a.mat[0][i]>maxProb)
           {
            maxProb=a.mat[0][i];
            maxIndex=i;
           }
    token=dehashToken(maxIndex);
    a=*ExtractProbabilityVector(token,markovChain);
    display=token;
    }
}


int main()
{
    Matrix* markovChain;
    cout<<"Extracting contents from file.......\n";
    extractFromFile(markovChain);
    createWordList();
    createProbabilities(*markovChain);
    cout<<"Input:";
    string input;
    while(true)
    {
      cin>>input;
      predictText1(input,2,*markovChain);
    }
    return 0;
}