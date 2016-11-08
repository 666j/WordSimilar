#ifndef SORTCHAIN_H
#define SORTCHAIN_H
#include <ChainNode.h>
//#include<ChainHashTable.h>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

//class ChainHashTable;
class SortChain
{
    //friend ChainHashTable;
    public:
        SortChain();
         ~SortChain();
        int Length()const;
        bool isEmpty()const{return first == 0;}
        bool Search(const string &k,string &e)const;
        SortChain &Insert(const string & x);
        SortChain &DistinctInsert(const string &e);
        SortChain &Delete(const string &k,string&e);
        void Output()const;
        public:
         ChainNode *first;
};


#endif // SORTCHAIN_H
