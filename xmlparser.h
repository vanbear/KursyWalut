#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QtWidgets>
#include <iostream>
#include <QDebug>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject *parent = 0);

    bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);

signals:

public slots:
};

#endif // XMLPARSER_H
