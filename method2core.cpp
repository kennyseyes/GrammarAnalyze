#include "method2core.h"

method2Core::method2Core()
{
    nonterminator=new node;
    nonterminator->next=NULL;
    terminator=new node;
    terminator->next=NULL;
    production=new node;
    production->next=NULL;
}

void method2Core::setStart(string s)
{
    start=s;
}

string method2Core::getStart()
{
    return start;
}

void method2Core::setNonterm(node* s)
{
    node* temp=nonterminator;
    while(temp->next!=NULL)
        temp=temp->next;

    temp->next=s;
}

node* method2Core::getNonterm(){   return nonterminator;   }

void method2Core::setTerm(node* s)
{
    node* temp=terminator;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=s;
}
node* method2Core::getTerm(){  return terminator;  }

void method2Core::setProd(node* s)
{
    node* temp=production;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=s;
}
node* method2Core::getProd(){  return production;  }
