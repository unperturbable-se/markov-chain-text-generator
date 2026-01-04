#include <fstream>
#include<iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "matrix.h"
#include "hash.h"
using namespace std;

int reformatText()
{
 ifstream a("train.txt");
 ofstream b("reformatted.txt");
 char letter=' ';
 int i=0;
 while(!a.eof())
 {
   if(letter=='\n')b<<letter;
   while(letter=='\n')
   {
     letter=a.get();
   }
    if(letter==' ')b<<letter;
    else if(letter>='a'&&letter<='z')b<<letter;
    else if(letter>='A'&&letter<='Z')b<<char(letter+32);
    letter=a.get();
 }

 return 0;
}

void getValues(Matrix& matrix)
{
    ifstream f{"reformatted.txt"};
    string word;
    f>>word;
    int previousToken=hashToken(word);
    int nextToken=0;
    while(!f.eof())
    {
          //cout<<"debug(loop start)\n";
          f>>word;
          nextToken=hashToken(word);
          matrix.mat[previousToken][nextToken]++;
          previousToken=nextToken;
          //cout<<"running(debug(loop end)\n";
    }
}
void collectData()
{
        int size=createWordList();
        Matrix markovChain(size,size);
        markovChain.clear();
        getValues(markovChain);
        markovChain.display();
}

int main()
{
   cout<<"Formatting text...\n";
   reformatText();
   cout<<"Creating markov chain...\n";
   collectData();
   return 0;
}