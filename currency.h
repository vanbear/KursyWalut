#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>

class currency : public QObject
{
    Q_OBJECT
public:
    currency(QString name = "non", int multiplier = 0, QString code = "NON", double exchange = 0);
    ~currency();

    QString nazwa;
    int mnoznik;
    QString kod;
    double kurs;

signals:

public slots:
};

#endif // CURRENCY_H
