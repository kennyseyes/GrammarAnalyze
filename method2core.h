#ifndef METHOD2CORE_H
#define METHOD2CORE_H
#include <iostream>

using namespace std;

typedef struct node{
    string s;
    node* next;
}node;

class method2Core
{
public:
    method2Core();
    void setStart(string s);
    string getStart();
    void setNonterm(node* s);
    node* getNonterm();
    void setTerm(node* s);
    node* getTerm();
    void setProd(node* s);
    node* getProd();

private:
    string start;//起始符
    node* nonterminator;//指向非终结符链表首地址的指针
    node* terminator;//指向终结符链表首地址的指针
    node* production;//产生式链表
};

#endif // METHOD2CORE_H
