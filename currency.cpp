#include "currency.h"
#include <qdebug.h>

currency::currency(QString name, int multiplier, QString code, double exchange) : QObject(parent)
{
    this->nazwa=name;
    this->mnoznik=multiplier;
    this->kod=code;
    this->kurs=exchange;
    qDebug() << "Tworzenie obiektu" << nazwa;
}
