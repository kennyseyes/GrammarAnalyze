#include "input.h"
#include "ui_input.h"
#include <QDebug>
#include<QPushButton>
#include <QButtonGroup>

#include <QLabel>
using namespace std;

QButtonGroup *bg;
QVBoxLayout *lay1;
int cnt;

input::input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
    connect(ui->return_2,SIGNAL(clicked(bool)),this,SLOT(close()));
    ui->widget->hide();
    bg=new QButtonGroup;
}

input::~input()
{
    delete ui;
}

void input::on_return_2_clicked()
{
}

void input::on_submit_clicked()
{
    delete lay1;
    QList<QLabel*> lbls = ui->symbols->findChildren<QLabel*>();
    foreach (QLabel* lb, lbls) {   delete lb;  }
    QList<QPushButton*> btns = ui->symbols->findChildren<QPushButton*>();
    foreach (QPushButton* btn, btns) {   delete btn;  }

    qDebug()<<ui->start->text()<<"\n"<<ui->terminator->text()<<"\n"<<ui->nonterminator->text();
    lay1=new QVBoxLayout();

    QPushButton *to=new QPushButton;
    to->setText("→");
    to->setFixedSize(40,40);
    lay1->addWidget(to);
    bg->addButton(to,0);

    QLabel *startl=new QLabel;
    startl->setText("起始符：");
    startl->setMaximumHeight(40);
    QLabel *nontl=new QLabel;
    nontl->setText("非终结符：");
    nontl->setMaximumHeight(40);
    QLabel *terml=new QLabel;
    terml->setText("终结符：");
    terml->setMaximumHeight(40);

    //起始符
    lay1->addWidget(startl);
    string s=ui->start->text().toStdString();
    for(int i=0;i<s.length();i++)
    {
        if(i==s.length()-1 && s[i]!=' ')
            m->setStart(s);
        else if(s[i]==' ')
            m->setStart(s.substr(0,i));
    }
    QPushButton *b=new QPushButton;
    connect(b,SIGNAL(clicked(bool)),this,SLOT(showch()));
    b->setText(QString::fromStdString(m->getStart()));
    b->setFixedSize(40,40);
    bg->addButton(b,1);
    lay1->addWidget(b);
    cnt=2;

    //非终结符
    lay1->addWidget(nontl);
    string nont=ui->nonterminator->text().toStdString();
    int start=0,end=0;
    for(int i=0;i<nont.length();i++)
    {
        if(nont[i]==' ')
        {
            end=i;
            node *n=new node;
            n->s=nont.substr(start,end-start);
            n->next=NULL;
            m->setNonterm(n);
            start=i+1;end=i+1;
            QPushButton *b=new QPushButton;
            connect(b,SIGNAL(clicked(bool)),this,SLOT(showch()));
            b->setText(QString::fromStdString(n->s));
            b->setFixedSize(40,40);
            bg->addButton(b,cnt);
            cnt++;
            lay1->addWidget(b);
        }
        end++;
    }
    node *n=new node;
    n->s=nont.substr(start,end-start+1);
    n->next=NULL;
    m->setNonterm(n);
    QPushButton *b1=new QPushButton;
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(showch()));
    b1->setText(QString::fromStdString(n->s));
    b1->setFixedSize(40,40);
    bg->addButton(b1,cnt);
    cnt++;
    lay1->addWidget(b1);



    //终结符
    lay1->addWidget(terml);
    string term=ui->terminator->text().toStdString();
    start=0,end=0;
    for(int i=0;i<term.length();i++)
    {
        if(term[i]==' ')
        {
            end=i;
            node *n=new node;
            n->s=term.substr(start,end-start);
            n->next=NULL;
            m->setNonterm(n);
            start=i+1;end=i+1;
            QPushButton *b=new QPushButton;
            connect(b,SIGNAL(clicked(bool)),this,SLOT(showch()));
            if(n->s!="\\0")
                b->setText(QString::fromStdString(n->s));
            else
                b->setText(QString::fromStdString("ε"));
            b->setFixedSize(40,40);
            bg->addButton(b,cnt);
            cnt++;
            lay1->addWidget(b);
        }
        end++;
    }
    node *n2=new node;
    n2->s=term.substr(start,end-start+1);
    n2->next=NULL;
    m->setNonterm(n2);
    QPushButton *b2=new QPushButton;
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(showch()));
    if(n2->s!="\\0")
        b2->setText(QString::fromStdString(n2->s));
    else
        b2->setText(QString::fromStdString("ε"));
    b2->setFixedSize(40,40);
    bg->addButton(b1,cnt);
    cnt=0;
    lay1->addWidget(b2);


    ui->widget->show();
    ui->symbols->setLayout(lay1);
}




