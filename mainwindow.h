#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "currency.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMap<QString, currency*> waluty;

public slots:
    void XMLParse();

private slots:
    void on_Button_Przelicz_clicked();

    void on_Button_switch_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
