#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H
#include <SortChain.h>
#include<ChainNode.h>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
//����ɢ����
//class ChainNode;
//class SortChain;
class ChainHashTable
{
    public:
        ChainHashTable(int divisor = 26){//��ʼ��ɢ�б��Ͱ��
            D = divisor;
            ht = new SortChain[D];
        };
        ~ChainHashTable(){delete[] ht;}
        bool Search(const string &k,string&e)const{//
           char fWord = k[0];
           int i;
           i = (fWord-'a')%D;//�õ�����ĸ��Ͱ��
           // const char* firstWord = k. substr(0,1).c_str();
            return ht[i].Search(k,e);//�õ���i��ascii����˼�ȥa��ascii�벢ȡ��D�������õ�Ҫ�ҵĵ�����ɢ���е�λ��
        }
        ChainHashTable &Insert(const string &e){
            char fWord = e[0];
            int i;
            i = (fWord-'a')%D;//�õ�����ĸ��Ͱ��
            ht[i].DistinctInsert(e);//�õ���i��ascii����˼�ȥa��ascii�벢ȡ��D�������õ�Ҫ�ҵĵ�����ɢ���е�λ��
            return *this;
        }
        ChainHashTable &Delete(const string &k,string &e){
            char fWord = k[0];
            int i;
            i = (fWord-'a')%D;//�õ�����ĸ��Ͱ��
            ht[i].Delete(k,e);//�õ���i��ascii����˼�ȥa��ascii�벢ȡ��D�������õ�Ҫ�ҵĵ�����ɢ���е�λ��
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
            //cdataָҪ���Ҽ���ǰ��ĵ��ʣ�bdataΪ�����ĵ���,same���������ж��Ƿ���ͬ,����һ����ĸ��ͬ��same= false
            bool similarity = true;//�Ƿ�����
            int diff = 0;//��ͬ����ĸ����
            int bi=0,ci=0;//biָ��bdata����ĸ��ciָ��cdata
            if((cdata.length()-bdata.length())<2||(cdata.length()-bdata.length())>-2){
                //���������ʵĳ������С�ڵ���yiʱ�������ʲſ������ơ���������
                if(cdata.length() == bdata.length()){//����������ʳ������
                    for(int j = 0; j<cdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//���������������ĸ����ͬ��diff+1����diff>1ʱ����ֱ���˳�ѭ������������
                                diff++;
                                //same = false;
                            }
                            if(diff>1){similarity = false;
                            }
                            ci++;//ָ�붼��һָ���һ����ĸ
                            bi++;
                        }
                    }
                    if(diff==0){
                        cout<<"��ͬ";
                    }
                    return similarity;
                }
                else if(cdata.length()<bdata.length()){//������鵥�ʳ�1ʱ
                    for(int j = 0; j<bdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//���ֲ���ͬ��ĸʱ��biָ�����һλ��ci++���䣬��ȥ��bdata�ж���Ĳ���ͬ��һλ�Ƚ�
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
                else if(cdata.length()>bdata.length()){//������鵥�ʶ�ʱ
                    for(int j = 0; j<cdata.length();j++){
                        if(similarity){
                            if(cdata[ci]!=bdata[bi]){//���ֲ���ͬ��ĸʱ��ciָ�����һλ��bi���䣬��ȥ��cdata�ж���Ĳ���ͬ��һλ�Ƚ�
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
            //same = true;//same�жϵ����Ƿ��ڴʵ���
            cout<<bChecked+"���Ƶĵ����У�"<<endl;
            for(int i =0; i<D;i++){
                current = ht[i].first;
                col = i;
                while(current){
                   check = isSimilar(bChecked,current->data);//�ж��Ƿ�����
                   if(check){
                        cout<<"("<<col<<","<<row<<"):"<<current->data<<";   ";
                        count++;
                        }
                   current= current->link;
                   row++;
                    }
            }
            if(count==0){
                cout<<"û����ͬ�ĵ���"<<endl;
            }else cout<<"��"<<count<<"�����Ƶ���"<<endl;

        }

        void Check(){
            bool Iscontinue = true;//�ж��Ƿ��ٴμ��
            char y;
            string bsearch;//
            while(Iscontinue){
                cout<<"������������ĵ���"<<endl;
                cin>>bsearch;
                SpellCheck(bsearch);
                cout<<"�����밴Yֹͣ����밴N"<<endl;
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
        string dictionary[1000];//�ֵ䵥��
        char black = ' ' ;//�ո�
        int ends = 0, nums = 0;//endsָ��result����ĸ��numsָ�򵥴ʵĸ���
        string line;
        string result="";
        ifstream in(".\\test.txt");
        if(in){
            while(getline(in,line)){
                result+=line;
//cout<<result<<endl;
/*||result[ends]==','||result[ends]==';'||
                    result[ends]=='��'||result[ends]=='��'||result[ends]=='.'||result=='��'*/
                while(result[ends]){
                    if(result[ends] == black){//�����ո�ends����һλ������Ŀ��һ
                        nums++;
                        ends++;
                    }
                    else{
                        dictionary[nums]+=result[ends++];//û��������¼����ַ���ends��һ
                    }
                }
            }
        }else{
        cout<<"no such file"<<endl;
        }
         for(int i = 0;i<nums;i++){
            Insert(dictionary[i]);//���뵥�ʽ����ֵ�
        }
        cout<<"�ֵ佨�����"<<endl;
        Output();//����ֵ�
        return *this;
        }
    protected:

    private:
        int D;
        //bool same;
        SortChain *ht;
};

#endif // CHAINHASHTABLE_H
