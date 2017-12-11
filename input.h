#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <method2core.h>
#include <cctype>
#include <QPushButton>
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

private:
    Ui::input *ui;
    method2Core *m=new method2Core;
};

#endif // INPUT_H
