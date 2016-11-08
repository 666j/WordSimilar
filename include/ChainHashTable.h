#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H
#include <SortChain.h>
#include<ChainNode.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
//链表散列类
//class ChainNode;
//class SortChain;
class ChainHashTable
{
    public:
        ChainHashTable(int divisor = 26){//初始化散列表的桶数
            D = divisor;
            ht = new SortChain[D];
        };
        ~ChainHashTable(){delete[] ht;}
        bool Search(const string &k,string&e)const{//
           char fWord = k[0];
           int i;
           i = (fWord-'a')%D;//得到首字母的桶号
           // const char* firstWord = k. substr(0,1).c_str();
            return ht[i].Search(k,e);//得到的i是ascii码因此减去a的ascii码并取与D的余数得到要找的单词在散列中的位置
        }
        ChainHashTable &Insert(const string &e){
            char fWord = e[0];
            int i;
            i = (fWord-'a')%D;//得到首字母的桶号
            ht[i].DistinctInsert(e);//得到的i是ascii码因此减去a的ascii码并取与D的余数得到要找的单词在散列中的位置
            return *this;
        }
        ChainHashTable &Delete(const string &k,string &e){
            char fWord = k[0];
            int i;
            i = (fWord-'a')%D;//得到首字母的桶号
            ht[i].Delete(k,e);//得到的i是ascii码因此减去a的ascii码并取与D的余数得到要找的单词在散列中的位置
            return *this;
        }
        void Output()const{
            for(int i =0;i<D;i++){
                    cout<<i<<"->";
                    ht[i].Output();
                    cout<<endl;
                    if(i<25)
                    cout<<"|"<<endl;
            }
        }
        bool isSimilar(string cdata,string bdata){
            //cdata指要查找即当前输的单词，bdata为被检查的单词,same变量用来判断是否相同,若有一个字母不同则same= false
            bool similarity = true;//是否相似
            int diff = 0;//不同的字母个数
            int bi=0,ci=0;//bi指向bdata的字母。ci指向cdata
            if((cdata.length()-bdata.length())<2||(cdata.length()-bdata.length())>-2){
                //当两个单词的长度相差小于等于yi时两个单词才可能相似。否则不相似
                if(cdata.length() == bdata.length()){//如果两个单词长度相等
                    for(int j = 0; j<cdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//如果两个单词有字母不相同，diff+1，当diff>1时，则直接退出循环不可能相似
                                diff++;
                                //same = false;
                            }
                            if(diff>1){similarity = false;
                            }
                            ci++;//指针都加一指向后一个字母
                            bi++;
                        }
                    }
                    if(diff==0){
                        cout<<"相同";
                    }
                    return similarity;
                }
                else if(cdata.length()<bdata.length()){//当被检查单词长1时
                    for(int j = 0; j<bdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//出现不相同字母时，bi指针后移一位，ci++不变，即去掉bdata中多出的不相同的一位比较
                                diff++;
                                bi++;
                            }else{
                                bi++;
                                ci++;
                            }
                            if(diff>1){similarity = false;
                            }
                        }
                    }
                    return similarity;
                }
                else if(cdata.length()>bdata.length()){//当被检查单词短时
                    for(int j = 0; j<cdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//出现不相同字母时，ci指针后移一位，bi不变，即去掉cdata中多出的不相同的一位比较
                                diff++;
                                ci++;
                               // same = false;
                            }else{
                                bi++;
                                ci++;
                            }
                             if(diff>1){similarity = false;
                            }
                        }
                    }
                    return similarity;
                }
            }else{
                return false;
            }
        }
        void SpellCheck(string bChecked){
            ChainNode *current;
            bool check= true;
            int count = 0;
            int col=0,row=0;
            //same = true;//same判断单词是否在词典中
            cout<<bChecked+"相似的单词有："<<endl;
            for(int i =0; i<D;i++){
                current = ht[i].first;
                col = i;
                while(current){
                   check = isSimilar(bChecked,current->data);//判断是否相似
                   if(check){
                        cout<<"("<<col<<","<<row<<"):"<<current->data<<";   ";
                        count++;
                        }
                   current= current->link;
                   row++;
                    }
            }
            if(count==0){
                cout<<"没有相同的单词"<<endl;
            }else cout<<"共"<<count<<"个相似单词"<<endl;

        }

        void Check(){
            bool Iscontinue = true;//判断是否再次检查
            char y;
            string bsearch;//
            while(Iscontinue){
                cout<<"请输入你想检查的单词"<<endl;
                cin>>bsearch;
                SpellCheck(bsearch);
                cout<<"继续请按Y停止检查请按N"<<endl;
                cin>>y;
                if(y=='N'){
                    Iscontinue = false;
                }else if(y=='Y'){
                    Iscontinue =true;
                }else{Iscontinue = false;}
                cout<<endl;
            }
        }
    ChainHashTable& Build_Dictionary(){
        string dictionary[1000];//字典单词
        char black = ' ' ;//空格
        int ends = 0, nums = 0;//ends指向result的字母，nums指向单词的个数
        string line;
        string result="";
        ifstream in(".\\test.txt");
        if(in){
            while(getline(in,line)){
                result+=line;
//cout<<result<<endl;
/*||result[ends]==','||result[ends]==';'||
                    result[ends]=='，'||result[ends]=='；'||result[ends]=='.'||result=='。'*/
                while(result[ends]){
                    if(result[ends] == black){//遇到空格ends右移一位单词数目加一
                        nums++;
                        ends++;
                    }
                    else{
                        dictionary[nums]+=result[ends++];//没有遇到空录入该字符，ends加一
                    }
                }
            }
        }else{
        cout<<"no such file"<<endl;
        }
         for(int i = 0;i<nums;i++){
            Insert(dictionary[i]);//插入单词建立字典
        }
        cout<<"字典建立完成"<<endl;
        Output();//输出字典
        return *this;
        }
    protected:

    private:
        int D;
        //bool same;
        SortChain *ht;
};

#endif // CHAINHASHTABLE_H
