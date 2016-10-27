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

class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = 0);

    void doDownload();

signals:

public slots:
    void ReplyFinished (QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADER_H
