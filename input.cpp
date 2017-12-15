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
    //connect(ui->ok,SIGNAL(clicked(bool)),this,SLOT(sendtable()));
    ui->widget->hide();
    bg=new QButtonGroup;
    connect( bg, SIGNAL(buttonClicked (int)), this, SLOT(buttonJudge(int)) );
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
    ui->showPro->clear();
    ui->chanshengshi->clear();

    lay1=new QVBoxLayout();

    QPushButton *to=new QPushButton;
    to->setText("->");
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
    for(int i=0;i<s.length();i++)//设置起始符
    {
        if(i==s.length()-1 && s[i]!=' ')
            m->setStart(s);
        else if(s[i]==' ')
            m->setStart(s.substr(0,i));
    }
    QPushButton *b=new QPushButton;
    b->setText(QString::fromStdString(m->getStart()));
    b->setFixedSize(40,40);
    bg->addButton(b,1);
    lay1->addWidget(b);
    cnt=2;

    //非终结符
    m->deleteNonterm();
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
            m->setNonterm(n);//设置非终结符
            start=i+1;end=i+1;
            QPushButton *b=new QPushButton;
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
    m->setNonterm(n);//设置非终结符
    QPushButton *b1=new QPushButton;
    b1->setText(QString::fromStdString(n->s));
    b1->setFixedSize(40,40);
    bg->addButton(b1,cnt);
    cnt++;
    lay1->addWidget(b1);



    //终结符
    m->deleteTerm();
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
            m->setTerm(n);//设置终结符
            start=i+1;end=i+1;
            QPushButton *b=new QPushButton;
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
    m->setTerm(n2);//设置终结符
    QPushButton *b2=new QPushButton;
    if(n2->s!="\\0")
        b2->setText(QString::fromStdString(n2->s));
    else
        b2->setText(QString::fromStdString("ε"));
    b2->setFixedSize(40,40);
    bg->addButton(b2,cnt);
    cnt=0;
    lay1->addWidget(b2);


    ui->widget->show();
    ui->symbols->setLayout(lay1);

//    qDebug()<<"起始符："<<QString::fromStdString( m->getStart())<<"非终结符：";
//    node *nont2=m->getNonterm();
//    node *t=nont2;
//    while(t->next!=NULL && nont2->next!=NULL)
//    {
//        t=t->next;
//        qDebug()<<QString::fromStdString(t->s);
//    }
//    qDebug()<<"终结符";
//    node *term2=m->getTerm();
//    t=term2;
//    while (t->next!=NULL && term2->next!=NULL) {
//        t=t->next;
//        qDebug()<<QString::fromStdString(t->s);
//    }
}


void input::buttonJudge(int n)
{
    ui->showPro->setText(ui->showPro->text()+bg->button(n)->text()+' ');
}

void input::on_pushButton_clicked()
{
    ui->showPro->clear();
}

void input::on_ok_2_clicked()
{
    if(ui->showPro->text()!="")
        ui->chanshengshi->addItem(ui->showPro->text());
    ui->showPro->clear();
}

void input::on_pushButton_3_clicked()
{
    if(ui->chanshengshi->currentItem()!=Q_NULLPTR)
    {
        QListWidgetItem * item = ui->chanshengshi->takeItem(ui->chanshengshi->currentRow());
        delete item;
    }
}

void input::on_ok_clicked()
{
    t=new tableM;
    t->setTablehead(m);
    t->initialize();

    node* temp;
    int row=0;
    int i1=0,i2=0;//判断首尾
    string word;
    node* s;
    m->setprodN(ui->chanshengshi->count());
    //设置产生式，以链表方式存储到prod中
    while (row<ui->chanshengshi->count())
    {
        s=new node;
        s->next=NULL;
        temp=s;
        while (i2<ui->chanshengshi->item(row)->text().length())
        {
            if(ui->chanshengshi->item(row)->text()[i2]==' ')//遇到空格存储
            {
                word=ui->chanshengshi->item(row)->text().toStdString().substr(i1,i2-i1);
                temp->next=new node;
                temp=temp->next;
                temp->next=NULL;
                temp->s=word;

                i1=i2+1;
                i2=i1;
            }
            else
                i2++;
        }
        m->setProd(s->next,row);

        row++;
        i1=0;i2=0;
    }

/////////////////////
//    node*  wow=m->getProd();
//    node* test=wow;
//    while(test->next!=NULL)
//    {
//        qDebug()<<QString::fromStdString(test->s);
//        test=test->next;
//    }

    //测试产生式
//    qDebug()<<m->getprodN();
//    node* h=m->getprodA();
//    node *temp1;
//    for(int i=0;i<m->getprodN();i++)
//    {
//        qDebug()<<"no."<<i;
//        temp1=&h[i];
//        while (temp1->next!=NULL) {
//            temp1=temp1->next;
//            qDebug()<<" "<<QString::fromStdString(temp1->s);
//        }
//    }
//////////////////////

    //消除直接左递归
    qDebug()<<"消除左递归";
    m->distroyRec();

    //求first集
    t->show();

}
