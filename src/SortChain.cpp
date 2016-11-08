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
    //������������Ԫ�ط�����
    //���û���ҵ��ͷ���false
    ChainNode *current = first;
    //����ѭ�����ҵ���k��Ԫ��
    while(current && current->data != k){
        current = current->link;
    }
    //�����Ƿ�ƥ��
    if(current!=NULL){
        if(current->data == k){//���ƥ��
            e = current->data;
            return true;
        }else{
            cout<<"error";
            return false;//û��ƥ��
        }
    }
    return false;//������������û��ƥ��

}

SortChain& SortChain::Insert(const string& x){
    ChainNode *temp = new ChainNode;
    temp->data = x;
    temp->link = first;
    first = temp;
    return *this;

}


SortChain& SortChain::Delete(const string & k,string  &e){
    //ɾ���ȼ���k��Ԫ��
    //��Ҫɾ����Ԫ�ط���e��
    //���û��ƥ�����׳��쳣��
    ChainNode *p = first,*tp=0;//tpΪp����һ���ڵ㣻
    //Ѱ��ƥ��k��Ԫ��
    for(;p&&p->data<k;tp = p,p=p->link);
    //�����Ƿ�ƥ��
    if(p&&p->data==k){
        //��һ��һ��ƥ���Ԫ��
        e = p->data;//�������ݣ�
        //���������Ƴ�
        if(tp){
            tp->link = p->link;
            }else first = p->link;//���p�ǵ�һ���ڵ�
        delete p;
        return *this;
        }

        cout<<"û���ҵ�ƥ��Ԫ��,Ӧ���׳��쳣"<<endl;//BadInput�쳣
}


SortChain &SortChain::DistinctInsert(const string &e){
    //�����ǰ������û����ͬ��ֵe�������e��
    //������ظ����׳��쳣
    ChainNode *p=first, *tp = 0;//tpΪp����һ�����
    //�ƶ�tpʹe���Բ��뵽tp����
    for(;p&&p->data!=e;tp = p,p=p->link);//p->data<e����=e����
    //����Ƿ��ظ�
    if(p&&p->data == e)
        {
            return *this;

        }//throw BadInput;
    //û���ظ��Ļ������½�㣻
    else{
        ChainNode *q = new ChainNode;
        q->data = e;
        //��tp�������ڵ㣻
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
