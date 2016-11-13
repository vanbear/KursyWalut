#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>

class currency : public QObject
{
    Q_OBJECT
public:
    explicit currency(QObject *parent = 0, QString name = "non", int multiplier = 0, QString code = "NON", int exchange = 0);

    QString GetName();
    int GetMultiplier();
    QString GetCode();
    int GetExchange();

signals:

public slots:
};

#endif // CURRENCY_H
