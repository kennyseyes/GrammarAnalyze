#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <input.h>
#include <tablem.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_custom_clicked();

    void on_default_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
