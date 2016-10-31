#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QDebug>
#include <QWidget>
#include <QTest>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::XMLParse()
{
    //Otwórz plik XML
    QDomDocument document;
    QFile file("D:/LastA.xml");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Nie znaleziono pliku";
        }
        else
        {
            if(!document.setContent(&file))
            {
                qDebug() << "Plik jest chyba popsutyyy";
            }
            file.close();
        }

        // Główny znacznik
        QDomElement root = document.firstChildElement();

        QDomNodeList pozycje = root.elementsByTagName("pozycja");
        for(int i = 0; i < pozycje.count(); i++)
        {
            QDomNode znacznik_pozycje = pozycje.at(i);
            if (znacznik_pozycje.isElement())
            {
                // dana pozycja
                QDomElement pozycja = znacznik_pozycje.toElement();
                // pobieranie danych ze znaczników z danej pozycji
                QString nazwa_waluty = pozycja.elementsByTagName("nazwa_waluty").at(0).toElement().text();
                int przelicznik = pozycja.elementsByTagName("przelicznik").at(0).toElement().text().toInt();
                QString kod_waluty = pozycja.elementsByTagName("kod_waluty").at(0).toElement().text();
                double kurs_sredni = pozycja.elementsByTagName("kurs_sredni").at(0).toElement().text().replace(",",".").toDouble();
                qDebug() << "Pozycja "<< i << ":" << nazwa_waluty << "Przelicznik:" << przelicznik << "Kod" << kod_waluty << "Kurs średni:" << kurs_sredni;

            }
        }
  qDebug() << "Reading finished";
}
