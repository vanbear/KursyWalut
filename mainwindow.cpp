#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QDebug>
#include <QWidget>
#include <QTest>
#include "currency.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::XMLParse()
{

    //najpierw trzeba zrobić Nasze Polskie Złote, których nie ma w pliku, który będziemy parsować
    QString nazwa = "polski złoty";
    QString kod = "PLN";
    currency* pl = new currency(nazwa,1,kod,1.);

    //i teraz wrzucamy początkowe dane do tych struktur
    waluty.insert(kod,pl);


    //Otwórz plik XML
    QDomDocument document;
    QFile file("D:/LastA.xml");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Nie znaleziono pliku";
        }
        else
        {
            if(!document.setContent(&file))
            {
                qDebug() << "Plik jest chyba popsutyyy";
            }
            file.close();
        }

        // Główny znacznik
        QDomElement root = document.firstChildElement();

        QDomNodeList pozycje = root.elementsByTagName("pozycja");
        for(int i = 0; i < pozycje.count(); i++)
        {
            QDomNode znacznik_pozycje = pozycje.at(i);
            if (znacznik_pozycje.isElement())
            {
                // dana pozycja
                QDomElement pozycja = znacznik_pozycje.toElement();
                // pobieranie danych ze znaczników z danej pozycji
                QString nazwa_waluty = pozycja.elementsByTagName("nazwa_waluty").at(0).toElement().text();
                int przelicznik = pozycja.elementsByTagName("przelicznik").at(0).toElement().text().toInt();
                QString kod_waluty = pozycja.elementsByTagName("kod_waluty").at(0).toElement().text();
                double kurs_sredni = pozycja.elementsByTagName("kurs_sredni").at(0).toElement().text().replace(",",".").toDouble();
                qDebug() << "Pozycja "<< i << ":" << nazwa_waluty << "Przelicznik:" << przelicznik << "Kod" << kod_waluty << "Kurs średni:" << kurs_sredni;
                currency* obj = new currency(nazwa_waluty,przelicznik,kod_waluty,kurs_sredni);
                waluty.insert(kod_waluty,obj);
            }
        }
  qDebug() << "Reading finished";

  qDebug() << waluty;
  qDebug() << waluty.keys();
  ui->comboBox_CurrencySelect1->addItems(waluty.keys());
  ui->comboBox_CurrencySelect2->addItems(waluty.keys());

}

void MainWindow::on_Button_Przelicz_clicked()
{

    // wybrane waluty
    QString wybrany_kod1 = ui->comboBox_CurrencySelect1->currentText();
    QString wybrany_kod2 = ui->comboBox_CurrencySelect2->currentText();

    //pobieranie danych z obiektów
    currency* waluta1 = waluty.value(wybrany_kod1);
    QString nazwa1 = waluta1->nazwa;
    QString kod1 = waluta1->kod;
    int mnoznik1 = waluta1->mnoznik;
    double kurs1 = waluta1->kurs;
    kurs1 = kurs1/mnoznik1;

    currency* waluta2 = waluty.value(wybrany_kod2);
    QString nazwa2 = waluta2->nazwa;
    QString kod2 = waluta2->kod;
    int mnoznik2 = waluta2->mnoznik;
    double kurs2 = waluta2->kurs;
    kurs2 = kurs2/mnoznik2;

    // sprawdzanie wpisanej wartosci
    double wpisana_wartosc = ui->LineEdit_AmountInput1->text().replace(",",".").toDouble();
    if (!wpisana_wartosc) wpisana_wartosc = 1; // jeżeli użytkownik nic nie wpisze to ustala wartość na 1

    double wynik = wpisana_wartosc*(kurs1/kurs2);
    double wynik2 = kurs1/kurs2;

    QString tekst = QString::number(wpisana_wartosc,'f',2)+" "+kod1+" = "+QString::number(wynik,'f',2)+" "+kod2;
    QString tekst2 = "1 "+kod1+" = "+QString::number(wynik2,'f',2)+" "+kod2;

    ui->label_ShowResults->setText(tekst);
    ui->label_ShowResults_small->setText(tekst2);
    ui->label_ShowResults->setWordWrap(true);

    qDebug() << "Wybrano " << nazwa1 << "kurs: " << kurs1 << " i " << nazwa2 << "kurs: " << kurs2;

    //wyświetlanie nazw walut

   ui->label_CurrenyName1->setText(nazwa1);
   ui->label_CurrenyName2->setText(nazwa2);


}

void MainWindow::on_Button_switch_clicked()
{
    QString selected1 = ui->comboBox_CurrencySelect1->currentText();
    QString selected2 = ui->comboBox_CurrencySelect2->currentText();
    int index1 = ui->comboBox_CurrencySelect1->findText(selected1);
    int index2 = ui->comboBox_CurrencySelect2->findText(selected2);
    qDebug() << "Zamiana miejsc, indeksy:" << index1 << ", " << index2;

    ui->comboBox_CurrencySelect1->setCurrentIndex(index2);
    ui->comboBox_CurrencySelect2->setCurrentIndex(index1);
}
