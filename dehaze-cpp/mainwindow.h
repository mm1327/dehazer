#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <haze.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void test();
private:
    Ui::MainWindow *ui;
    Haze haze;
};

#endif // MAINWINDOW_H
