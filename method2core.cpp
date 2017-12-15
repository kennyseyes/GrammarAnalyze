#include "method2core.h"
#include <QDebug>

method2Core::method2Core()
{
    nonterminator=new node;
    nonterminator->next=NULL;
    nonterminator->first=NULL;
    nonterminator->follow=NULL;
    terminator=new node;
    terminator->next=NULL;
    terminator->first=NULL;
    terminator->follow=NULL;
    termN=1;
    nonN=0;
    prodA=NULL;
    prodN=0;
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
    s->next=NULL;
    node* temp=nonterminator;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    nonN++;

    temp->next=s;
}

node* method2Core::getNonterm(){   return nonterminator;   }

void method2Core::setTerm(node* s)
{
    s->next=NULL;
    node* temp=terminator;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=s;
    termN++;
}
node* method2Core::getTerm(){  return terminator;  }

void method2Core::setProd(node* s,int i)
{
    prodA[i].next=s;
}

void method2Core::deleteNonterm()
{
    node *f=nonterminator->next;
    nonterminator->next=NULL;
    node *e;
    while (f!=NULL) {
        e=f->next;
        delete f;
        f=e;
    }
}

void method2Core::deleteTerm()
{
    node *f=terminator->next;
    terminator->next=NULL;
    node *e;
    while (f!=NULL) {
        e=f->next;
        delete f;
        f=e;
    }
}

void method2Core::deleteProd()
{
    if(prodA!=NULL)
    {
        for(int i=0;i<prodN;i++)
        {
            node *f=prodA[i].next;
            prodA[i].next=NULL;
            node *e;
            while (f!=NULL) {
                e=f->next;
                delete f;
                f=e;
            }
        }
        delete []prodA;
    }


}

int method2Core::getnonN()
{
    return nonN;
}

int method2Core::gettermN()
{
    return termN;
}

void method2Core::setprodN(int n)
{
    prodN=n;
    prodA=new node[n];
    for(int i=0;i<n;i++)
    {
        prodA[i].next=NULL;
        prodA[i].first=NULL;
        prodA[i].follow=NULL;
    }

}

node* method2Core::getprodA()
{
    return prodA;
}

vector<node*> method2Core::getprod2()
{
    return prod2;
}

int method2Core::getprodN()
{
    return prodN;
}


void method2Core::distroyRec()
{
    string s;//用于存储有左递归的非终结符
    string s1;//用于存储新增非终结符
    node *temp,*newprod,*n;//新产生式
    node *savepoint,*stemp,*ptr1,*ptr2;//用于拷贝产生式
    for (int i=0;i<prodN;i++ )
    {
        if(prodA[i].next->s==prodA[i].next->next->next->s && prodA[i].trans==0)//如果有左递归且没有被处理过
        {
            s=prodA[i].next->s;
            vector<string>::iterator result = find( rec.begin( ), rec.end( ),s);//如果处理的起始符没有在rec中，则加入rec
            if ( result == rec.end() ) //没找到
                rec.push_back(s);

            s1=s+"'";

            prodA[i].trans=1;
            newprod=new node;
            newprod->next=NULL;
            newprod->first=NULL;
            newprod->follow=NULL;

            n=new node;
            n->next=NULL;
            n->first=NULL;
            n->follow=NULL;
            n->s=s1;
            // setNonterm(n);
            newprod->next=n;
            temp=newprod->next;

            n=new node;
            n->next=NULL;
            n->first=NULL;
            n->follow=NULL;
            n->s="->";
            temp->next=n;
            temp=temp->next;


            //例：E->E+T，stemp存储+T, newprod存储 E'->+TE'
            savepoint=prodA[i].next->next->next->next;//复制产生式,
            ptr1=savepoint;
            stemp=new node;
            stemp->s=ptr1->s;
            ptr2=stemp;
            while (ptr1->next!=NULL) {
                ptr1=ptr1->next;
                n=new node;
                n->next=NULL;
                n->first=NULL;
                n->follow=NULL;
                n->s=ptr1->s;
                ptr2->next=n;
                ptr2=ptr2->next;
            }

            temp->next=stemp;
            while (temp->next!=NULL) {
                temp=temp->next;
            }

            n=new node;
            n->next=NULL;
            n->first=NULL;
            n->follow=NULL;
            n->s=s1;
            temp->next=n;
            prod2.push_back(newprod);


        }
        else//不存在左递归
        {
            vector<string>::iterator result = find( rec.begin(), rec.end(),prodA[i].next->s); //查找目前产生式的起始符是否含有左递归
            if ( result == rec.end() ) //没找到需要变更的式子
            {
                prod2.push_back(&prodA[i]);

            }

            else //找到
            {
                newprod=new node;
                newprod->next=NULL;
                newprod->first=NULL;
                newprod->follow=NULL;

                ptr1=prodA[i].next;
                stemp=new node;
                stemp->s=ptr1->s;
                ptr2=stemp;
                while (ptr1->next!=NULL) {
                    ptr1=ptr1->next;
                    n=new node;
                    n->next=NULL;
                    n->first=NULL;
                    n->follow=NULL;
                    n->s=ptr1->s;
                    ptr2->next=n;
                    ptr2=ptr2->next;
                }
                newprod->next=stemp;

                temp=newprod;
                while (temp->next!=NULL) {
                    temp=temp->next;
                }

                n=new node;
                n->next=NULL;
                n->first=NULL;
                n->follow=NULL;
                n->s=prodA[i].next->s+"'";
                temp->next=n;
                prod2.push_back(newprod);

            }
        }
    }

    //将所有的非终结符加入nontAll中
    n=new node;
    n->s=start;
    n->first=new node;
    nontAll.push_back(n);
    for(string s:rec)
    {
        n=new node;
        n->first=new node;
        n->s=s+"'";
        nontAll.push_back(n);
    }
    temp=nonterminator;
    while (temp->next!=NULL) {
        temp=temp->next;
        n=new node;
        n->first=new node;
        n->s=temp->s;
        nontAll.push_back(n);
    }

    //检测是否有出口
    node *escape;
    bool out=0;

    for(node *nt:nontAll)//对于每一个非终结符
    {
        temp=nonterminator;
        while (temp->next!=NULL) {//如果是原来的非终结符不用处理
            temp=temp->next;
            if(temp->s==nt->s)
                continue;
        }
        if(nt->s==start)
            continue;
        out=0;
        for(node *p:prod2)//在产生式中找nt开始的
        {

            if(nt->s==p->next->s)//如果是nt开始的
            {
                while(p->next!=NULL && !out)//往后找直到找到一个终结符
                {
                    p=p->next;
                    temp=terminator;
                    while (temp->next!=NULL && !out) {
                        temp=temp->next;
                        if(p->s==temp->s)//如果找到了一个终结符
                            out=1;
                    }
                }
            }
            if(out)
                break;
        }
        if(!out)//如果没有出口，填入起始符->\0,顺便将ε加入first集
        {
            n=new node;
            n->s="\\0";
            nt->first->next=n;

            escape=new node;
            temp=escape;

            n=new node;
            n->s=nt->s+"'";
            n->first=NULL;
            n->follow=NULL;
            n->next=NULL;
            temp->next=n;
            temp=temp->next;

            n=new node;
            n->s="->";
            n->first=NULL;
            n->follow=NULL;
            n->next=NULL;
            temp->next=n;
            temp=temp->next;

            n=new node;
            n->s="\\0";
            n->first=NULL;
            n->follow=NULL;
            n->next=NULL;
            temp->next=n;

            prod2.push_back(escape);
        }
    }



}

void method2Core::setFirst()//设置first集，设置每个产生式的first集
{
    string f;
    node* temp,*newnode,*ptr,*ptr1;
    bool found;//标志位
    for(node* n:prod2)//对于每一个产生式
    {
        n->next->first=new node;
        f=n->next->next->next->s;
        found=0;
        //判断产生式是否能直接找到终结符
        temp=terminator;
        while (temp->next!=NULL && !found)
        {
            temp=temp->next;
            //如果是终结符，直接加入first集
            if(temp->s==f)
            {
                //添加到非终结符
                for(node* n1:nontAll)
                {
                    if(n1->s==n->next->s)
                    {
                        newnode=new node;
                        newnode->s=f;
                        ptr=n1->first;
                        while (ptr->next!=NULL) {
                            ptr=ptr->next;
                        }
                        ptr->next=newnode;
                        break;
                    }
                }

                //添加到产生式
                n->next->first=new node;
                ptr=n->next->first;

                while(ptr->next!=NULL)
                    ptr=ptr->next;

                newnode=new node;
                newnode->s=f;

                ptr->next=newnode;
                found=1;
            }
        }

        //判断产生式通过非终结符找到的first非终结符
        if(!found)
        {
            ptr=n->next->next->next;//ptr存储目前正在检查的符号
            while (ptr!=NULL && !found) {
                //先将产生式中第一个符号加到first
                newnode=new node;
                newnode->s=f;//暂时设为这个非终结符，后通过寻找这个非终结符的first集进行操作
                ptr1=n->next->first;
                while(ptr1->next!=NULL)
                    ptr1=ptr1->next;
                ptr1=newnode;

                //检查是否有空串(ptr.s)
                for(node* n1:nontAll)
                {
                    if(n1->s==ptr->s)
                    {
                        if(n1->first->next->s=="\\0")//有空串，将下一个符号也加入first
                        {
                            ptr=ptr->next;
                            newnode=new node;
                            newnode->s=ptr->s;
                            temp=n1->first;
                            while (temp->next!=NULL) {
                                temp=temp->next;
                            }
                            temp->next=newnode;
                        }


                    }
                }
            }

        }

    }

}

vector<node*> method2Core::getnontAll()
{
    return nontAll;
}

vector<string> method2Core::getrec()
{
    return rec;
}
