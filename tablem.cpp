#include "tablem.h"
#include "ui_tablem.h"
#include <QStringList>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>

tableM::tableM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tableM)
{
    ui->setupUi(this);
}

tableM::~tableM()
{
    delete ui;
}

void tableM::setTablehead(method2Core* h)
{
    tablehead=h;
}

void tableM::initialize()
{
    qDebug()<<tablehead;
    ui->table->setColumnCount(tablehead->gettermN()+1);
    ui->table->setRowCount(tablehead->getnonN()+1+tablehead->getrec().size());

    QStringList non;
    QStringList term;

    node* temp=tablehead->getTerm();//设置终结符

    term.append(QString::fromStdString(""));
    while (temp->next!=NULL) {
        temp=temp->next;
        term.append(QString::fromStdString(temp->s));
        //qDebug()<<QString::fromStdString(temp->s);
    }
    term.append(QString::fromStdString("$"));
    ui->table->setHorizontalHeaderLabels(term);

    non.append(QString::fromStdString(tablehead->getStart()));
    temp=tablehead->getNonterm();
    while (temp->next!=NULL) {
        temp=temp->next;
        non.append(QString::fromStdString(temp->s));
    }
  //  non.append(QString::fromStdString(temp->s));

    for(string s:tablehead->getrec())
    {
        non.append(QString::fromStdString(s+"'"));
    }
    ui->table->setVerticalHeaderLabels(non);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //derec
    QString s="";
    for (node* p:tablehead->getprod2())
    {
        temp=p;
        while (temp->next!=NULL) {
            temp=temp->next;
            if(temp->s=="\\0")
                s+="ε";
            else
            s+=QString::fromStdString(temp->s);
        }

        ui->derec->addItem(s);
        s="";
    }

}
