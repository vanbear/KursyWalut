#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H

#include <QObject>

class XmlStreamReader : public QObject
{
    Q_OBJECT
public:
    explicit XmlStreamReader(QObject *parent = 0);
    bool readFile(const QString &filename);

private:
    void readPozycja

signals:

public slots:
};

#endif // XMLSTREAMREADER_H
