#include "downloader.h"
#include "mainwindow.h"
#include <QApplication>
#include <QtXml>
#include <QDebug>
#include <QWidget>
#include <QTest>
#include "currency.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QString nazwa = "polski złoty";
    QString kod = "PLN";
    currency* pl = new currency(nazwa,1,kod,1.);
    QMap<QString, currency> waluty;
    waluty.insert(kod,pl);

    //Pobierz plik XML
    downloader dwnldr;
    dwnldr.connect(&dwnldr, SIGNAL(DownloadFinished()), &w, SLOT(XMLParse()));
    dwnldr.doDownload();

    return a.exec();
}
