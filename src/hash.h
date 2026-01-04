#pragma once
#include<vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

vector<string> words;
int createWordList()
{
  ifstream a("reformatted.txt");
  string word;
  while(!a.eof())
  {
    a>>word;
    words.push_back(word);
  }
  sort(words.begin(),words.end());
  words.erase(unique(words.begin(),words.end()),words.end());
  return words.size();
  //for(auto& word:words)cout<<word<<' ';
}

int binarySearch(string& word)
{
  int high=words.size()-1;
  int low=0;
  while(high>=low)
  {
    int mid=low+(high-low)/2;
    if(word==words[mid])return mid;
    else if(word>words[mid])low=mid+1;
    else high=mid-1;
  }
  cout<<"\n<not in dictionary>\n";
  return 0;
}

int hashToken(string& s)
{
 return binarySearch(s);
}

string dehashToken(int index)
{
 return words.at(index);
}