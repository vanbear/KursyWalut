#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QDebug>
#include <QWidget>
#include <QTest>
#include "currency.h"
#include <QPixmap>
#include <QShortcut>
#include <QFileInfo>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/flags/img/flags/undefined.jpg");
    ui->label_showPic1->setPixmap(pix);
    ui->label_showPic2->setPixmap(pix);

    //ustawianie rozmiaru okna
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    this->statusBar()->setSizeGripEnabled(false);

    m_statusLeft->setStyleSheet("QLabel { color : white; }");
    m_statusMiddle->setStyleSheet("QLabel { color : white; }");
    m_statusRight->setStyleSheet("QLabel { color : white; }");

    double x = this->geometry().width();
    double statuswidth=x/3;

    m_statusLeft->setFixedWidth(statuswidth);
    m_statusMiddle->setFixedWidth(statuswidth);
    m_statusRight->setFixedWidth(statuswidth);
    statusBar()->addPermanentWidget(m_statusLeft, 1);
    statusBar()->addPermanentWidget(m_statusMiddle, 1);
    statusBar()->addPermanentWidget(m_statusRight, 2);

    //ustawianie cienia na tekście
    QList<QLabel*> label_list_;
    QList<QGraphicsDropShadowEffect*> shadow_list_;
    label_list_.append(ui->label_CurrenyName1);
    label_list_.append(ui->label_CurrenyName2);
    label_list_.append(ui->label_ShowResults);
    label_list_.append(ui->label_ShowResults_small);
    label_list_.append(ui->label_2);

    foreach(QLabel *lbl, label_list_) {
        shadow_list_.append(new QGraphicsDropShadowEffect);
        shadow_list_.back()->setBlurRadius(0);
        shadow_list_.back()->setColor(QColor("#000000"));
        shadow_list_.back()->setOffset(2,2);
        lbl->setGraphicsEffect(shadow_list_.back());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeStatus(QString txt)
{
    this->m_statusRight->setText(txt);
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
    QFile file("LastA.xml");

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

        QDomNode data = root.elementsByTagName("data_publikacji").at(0);
        if (data.isElement())
        {
            QString data_publikacji = data.toElement().text();
            m_statusLeft->setText("Dane z dnia: "+data_publikacji);
        }

        QDomNode numer = root.elementsByTagName("numer_tabeli").at(0);
        if (data.isElement())
        {
            QString numer_tabeli = numer.toElement().text();
            m_statusMiddle->setText("Numer tabeli: "+numer_tabeli);
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
    int i1 = ui->comboBox_CurrencySelect1->currentIndex();
    int i2 = ui->comboBox_CurrencySelect2->currentIndex();

    if (i1>=0 and i2>=0 )
    {
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

        QString tekst = QString::number(wpisana_wartosc,'f',3)+" "+kod1+" = "+QString::number(wynik,'f',3)+" "+kod2;
        QString tekst2 = "1 "+kod1+" = "+QString::number(wynik2,'f',3)+" "+kod2;

        ui->label_ShowResults->setText(tekst);
        ui->label_ShowResults_small->setText(tekst2);
        ui->label_ShowResults->setWordWrap(true);

        qDebug() << "Wybrano " << nazwa1 << "kurs: " << kurs1 << " i " << nazwa2 << "kurs: " << kurs2;
     }
    else
    {
        ui->label_ShowResults->setText("Nie wybrałeś walut do przeliczenia");
        ui->label_ShowResults_small->setText("Prawdopodobnie nie udało się pobrać pliku z danymi.");
    }

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

void MainWindow::on_comboBox_CurrencySelect1_currentIndexChanged(const QString &arg1)
{
    // wybrane waluty
    QString kod = arg1;

    //zmiana obrazków
    QString path=":/flags/img/flags/"+kod+".png";

    QFileInfo info(path);
    QPixmap pix(":/flags/img/flags/undefined.png");

    if (info.exists())
        ui->label_showPic1->setPixmap(path);
    else
        ui->label_showPic1->setPixmap(pix);

    //zmiana napisów
    currency* waluta = waluty.value(arg1);
    QString nazwa = waluta->nazwa;
    ui->label_CurrenyName1->setText(nazwa);


}

void MainWindow::on_comboBox_CurrencySelect2_currentIndexChanged(const QString &arg1)
{
    // wybrane waluty
    QString kod = arg1;

    //zmiana obrazków
    QString path=":/flags/img/flags/"+kod+".png";

    QFileInfo info(path);
    QPixmap pix(":/flags/img/flags/undefined.png");

    if (info.exists())
        ui->label_showPic2->setPixmap(path);
    else
        ui->label_showPic2->setPixmap(pix);

    //zmiana napisów
    currency* waluta = waluty.value(arg1);
    QString nazwa = waluta->nazwa;
    ui->label_CurrenyName2->setText(nazwa);
}

