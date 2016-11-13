#include "currency.h"
#include <qdebug.h>

currency::currency(QObject *parent, QString name, int multiplier, QString code, int exchange) : QObject(parent)
{
    qDebug() << "Tworzenie obiektu" << name;
}

QString GetName()
{

}

int GetMultiplier()
{

}

QString GetCode()
{

}

int GetExchange()
{

}
