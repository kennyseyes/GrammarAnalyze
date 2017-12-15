#ifndef METHOD2CORE_H
#define METHOD2CORE_H
#include <iostream>
#include <vector>

using namespace std;

typedef struct node{
    string s;
    node* next=NULL;
    node* first=NULL;
    node* follow=NULL;
    bool trans=0;
}node;


class method2Core
{
public:
    method2Core();
    void setStart(string s);
    string getStart();
    void setNonterm(node* s);
    void deleteNonterm();
    node* getNonterm();
    void setTerm(node* s);
    void deleteTerm();
    node* getTerm();
    void setProd(node* s,int i);
    void deleteProd();
    int getnonN();
    int gettermN();
    node* getprodA();//返回产生式数组
    void setprodN(int n);
    int getprodN();
    void setFirst();//设置first集
    void distroyRec();//消除直接左递归
    vector<node*> getprod2();
    vector<string> getrec();//得到新加入的非终结符
    vector<node*> getnontAll();

private:
    string start;//起始符
    node* nonterminator;//指向非终结符链表首地址的指针
    int nonN;
    node* terminator;//指向终结符链表首地址的指针
    int termN;
    int prodN;//产生式数量
    node* prodA;//产生式链表数组
    vector<node*> prod2;//消除左递归后的产生式
    vector<string> rec;//存在左递归的起始符
    vector<node*> nontAll;//所有的非终结符
};

#endif // METHOD2CORE_H
