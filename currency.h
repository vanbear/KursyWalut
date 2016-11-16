#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>

class currency : public QObject
{
    Q_OBJECT
public:
    currency(std::string name = "non", int multiplier = 0, std::string code = "NON", double exchange = 0);

    std::string nazwa;
    int mnoznik;
    std::string kod;
    double kurs;

signals:

public slots:
};

#endif // CURRENCY_H
