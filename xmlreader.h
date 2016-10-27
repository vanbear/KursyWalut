#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = 0);

signals:

public slots:
};

#endif // XMLREADER_H