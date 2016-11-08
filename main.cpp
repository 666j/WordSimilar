#include <SortChain.h>
#include <ChainNode.h>
#include <iostream>
#include<string>
#include<ChainHashTable.h>
#include<fstream>
using namespace std;
int main()
{
    ChainHashTable cht;
    cht.Build_Dictionary();//½¨Á¢×Öµä
    cht.Check();

    return 0;
}
