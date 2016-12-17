#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "currency.h"
#include <QLabel>

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
    QLabel* m_statusLeft = new QLabel("", this);
    QLabel* m_statusMiddle = new QLabel("", this);
    QLabel* m_statusRight = new QLabel("", this);



public slots:
    void XMLParse();
    void changeStatus(const QString txt);

private slots:
    void on_Button_Przelicz_clicked();
    void on_Button_switch_clicked();

    void on_comboBox_CurrencySelect1_currentIndexChanged(const QString &arg1);
    void on_comboBox_CurrencySelect2_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
