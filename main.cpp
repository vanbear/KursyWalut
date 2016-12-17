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

    //Pobierz plik XML
    downloader dwnldr;
    dwnldr.connect(&dwnldr, SIGNAL(DownloadFinished()), &w, SLOT(XMLParse()));
    dwnldr.doDownload();

    dwnldr.connect(&dwnldr, SIGNAL(GotStatus(QString)), &w, SLOT(changeStatus(QString)));

    return a.exec();
}
