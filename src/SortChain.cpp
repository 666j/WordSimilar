#include "SortChain.h"
#include <ChainNode.h>
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

class ChainNode;
SortChain::SortChain(){
    first=0;
}

SortChain::~SortChain()
{
    //dtor
    ChainNode *next;
    while(first){
        next = first->link;
        delete first;
        first = next;
    }
}

int SortChain::Length()const{
    ChainNode*current = first;
    int length = 0;
    while(current){
        length++;
        current = current->link;
    }
    return length;
}

bool SortChain::Search(const string& k,string& e)const{
    //将符合条件的元素放在中
    //如果没有找到就返回false
    ChainNode *current = first;
    //遍历循环查找等于k的元素
    while(current && current->data != k){
        current = current->link;
    }
    //核验是否匹配
    if(current!=NULL){
        if(current->data == k){//如果匹配
            e = current->data;
            return true;
        }else{
            cout<<"error";
            return false;//没有匹配
        }
    }
    return false;//遍历结束，且没有匹配

}

SortChain& SortChain::Insert(const string& x){
    ChainNode *temp = new ChainNode;
    temp->data = x;
    temp->link = first;
    first = temp;
    return *this;

}


SortChain& SortChain::Delete(const string & k,string  &e){
    //删除等价于k的元素
    //将要删除的元素放在e中
    //如果没有匹配则抛出异常；
    ChainNode *p = first,*tp=0;//tp为p的上一个节点；
    //寻找匹配k的元素
    for(;p&&p->data<k;tp = p,p=p->link);
    //核验是否匹配
    if(p&&p->data==k){
        //找一个一个匹配的元素
        e = p->data;//保存数据；
        //从链表中移除
        if(tp){
            tp->link = p->link;
            }else first = p->link;//如果p是第一个节点
        delete p;
        return *this;
        }

        cout<<"没有找到匹配元素,应该抛出异常"<<endl;//BadInput异常
}


SortChain &SortChain::DistinctInsert(const string &e){
    //如果当前链表中没有相同的值e，则插入e；
    //如果有重复则抛出异常
    ChainNode *p=first, *tp = 0;//tp为p的上一个结点
    //移动tp使e可以插入到tp后面
    for(;p&&p->data!=e;tp = p,p=p->link);//p->data<e或者=e待定
    //检查是否重复
    if(p&&p->data == e)
        {
            return *this;

        }//throw BadInput;
    //没有重复的话建立新结点；
    else{
        ChainNode *q = new ChainNode;
        q->data = e;
        //在tp后面插入节点；
        q->link = p;
        if(tp)tp->link = q;
        else first = q;
    }
    return *this;
}
    void SortChain::Output()const{
        ChainNode *current = first;
        if(!current){
            cout<<"NULL";
        }
        else{
            for(;current;current=current->link){
                if(current->link)
                 cout<<current->data<<" ->";
                else{
                    cout<<current->data;
                }
            }
        }

    }
