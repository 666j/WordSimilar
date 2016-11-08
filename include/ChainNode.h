#ifndef CHAINNODE_H
#define CHAINNODE_H
#include<SortChain.h>
//#include<ChainHashTable.h>
#include<stdlib.h>
#include<string>
using namespace std;

class SortChain;
//class ChainHashTable;
class ChainNode
{
    friend SortChain;
    //friend ChainHashTable;
    private:
        public:
        string data;
        ChainNode *link;
};

#endif // CHAINNODE_H
