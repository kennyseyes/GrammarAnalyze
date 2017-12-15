#ifndef TABLEM_H
#define TABLEM_H

#include <QWidget>
#include <method2core.h>

namespace Ui {
class tableM;
}

class tableM : public QWidget
{
    Q_OBJECT

public:
    explicit tableM(QWidget *parent = 0);
    ~tableM();

    void setTablehead(method2Core* h);
    void initialize();

private:
    Ui::tableM *ui;
    method2Core *tablehead;
};

#endif // TABLEM_H
