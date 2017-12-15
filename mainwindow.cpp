#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <method2core.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_custom_clicked()
{
    input *i=new input;
    i->show();
    method2Core *m=new method2Core;

}

void MainWindow::on_default_2_clicked()
{
    method2Core *m=new method2Core;
    tableM *t=new tableM;
//    string terms[7]={"+","-","*","/","(",")","num"};
//    string nonts[2]={"T","F"};
//    string prods[8]={"E -> E + T ","E -> E - T ","E -> T ","T -> T * F ","T -> T / F ","T -> F ","F -> ( E ) ","F -> num "};
    string terms[3]={"+","*","num"};
    string nonts[2]={"T","F"};
    string prods[3]={"E -> E + T ","T -> T * F ","F -> num "};
    m->setStart("E");
    node* n;
    for (string term:terms)
    {
        n=new node;
        n->next=NULL;
        n->first=NULL;
        n->follow=NULL;
        n->s=term;
        qDebug()<<QString::fromStdString(term);
        m->setTerm(n);
    }

    for (string nont:nonts)
    {
        n=new node;
        n->next=NULL;
        n->first=NULL;
        n->follow=NULL;
        n->s=nont;
        qDebug()<<QString::fromStdString(nont);
        m->setNonterm(n);
    }
   // m->setprodN(8);
    m->setprodN(3);
    //添加产生式
    int row=0,i1=0,i2=0;
    string word;
    node* temp;
    for(string prod:prods)
    {
        n=new node;
        n->next=NULL;
        n->first=NULL;
        n->follow=NULL;
        temp=n;
        while (i2<prod.length())
        {
            if(prod.at(i2)==' ')//遇到空格存储
            {
                word=prod.substr(i1,i2-i1);
                temp->next=new node;
                temp=temp->next;
                temp->next=NULL;
                temp->first=NULL;
                temp->follow=NULL;
                temp->s=word;

                i1=i2+1;
                i2=i1;
            }
            else
                i2++;
        }
        m->setProd(n->next,row);

        row++;
        i1=0;i2=0;
    }

//    node* h=m->getprodA();
//        node *temp1;
//    for(int i=0;i<8;i++)
//        {
//            qDebug()<<"no."<<i;
//            temp1=&h[i];
//            while (temp1->next!=NULL) {
//                temp1=temp1->next;
//                qDebug()<<" "<<QString::fromStdString(temp1->s);
//            }
//        }

    qDebug()<<"消除左递归";
    m->distroyRec();


    //设置first集
    m->setFirst();

    qDebug()<<"first集";

    for(node* n:m->getnontAll())
    {
        qDebug()<<QString::fromStdString( n->s)<<":";
        temp=n->first;
        while (temp->next!=NULL) {
            temp=temp->next;
           qDebug()<<QString::fromStdString(temp->s);
        }
    }

    t->setTablehead(m);
    t->initialize();
    t->show();
}
