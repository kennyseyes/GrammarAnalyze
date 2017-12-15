#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <method2core.h>
#include <cctype>
#include <QPushButton>
#include <tablem.h>
namespace Ui {
class input;
}

class input : public QWidget
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = 0);

    ~input();

private slots:
    void on_return_2_clicked();

    void on_submit_clicked();

    void buttonJudge(int);
    void on_pushButton_clicked();

    void on_ok_2_clicked();

    void on_pushButton_3_clicked();

    void on_ok_clicked();

private:
    Ui::input *ui;
    method2Core *m=new method2Core;
    tableM *t;
};

#endif // INPUT_H
