#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>

#include <QFile>
#include <QDebug>

#include "mainwindow.h"
class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = 0);

    void doDownload();

signals:
    void DownloadFinished();
    void GotStatus(QString txt);

public slots:
    void ReplyFinished (QNetworkReply *reply);


private:
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
