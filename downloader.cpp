#include <QCoreApplication>

#include "downloader.h"

downloader::downloader(QObject *parent) : QObject(parent)
{

}

void downloader::doDownload()
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("http://www.nbp.pl/kursy/xml/LastA.xml")));
}

void downloader::ReplyFinished (QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug() << "Nie udało się pobrać pliku!";
    }
    else
    {
        qDebug( )<< "Pobrano plik";
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();

        QFile *file = new QFile("D:/LastA.xml");
        if (file->open(QFile::WriteOnly))
        {
            qDebug( )<< "Zapis start" << file->fileName();
            file->write(reply->readAll());
            file->flush();
            file->close();
            qDebug( )<< "Zapis stop";
        }
        delete file;
    }
    emit DownloadFinished();


}
