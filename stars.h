#ifndef STARS_H
#define STARS_H

#include <QtGui>
#include <QWidget>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QProgressDialog>
#include <QCheckBox>
#include <QMessageBox>
#include <QLineEdit>

class Stars : public QWidget
{
    Q_OBJECT
public:
    explicit Stars(QWidget *parent = 0);
    void stopka();
    void clearall();
    void bledy();
    void warunekPoczatkowy(int dzien, int miesiac);
    int zmianaCzasu(int dzien, int miesiac, int rok);
    void obslugaBlad(QString title, QString tresc);
    void kalendarz(bool prawda, int &dni);
    void wschodslonca(int DzienPoczatkowy, int MiesiacPoczatkowy, int RokPoczatkowy);
    double round(double liczba) { return liczba < 0.0 ? ceil(liczba - 0.5) : floor(liczba + 0.5);}
    QTextEdit *rezultat;

private:
    QLineEdit *syear, *smonth, *sday, *kyear, *kmonth, *kday, *szerokosc, *dlugosc;
    QRadioButton *miasta[10];
    QSlider *strefy;
    QPushButton *oblicz;
    QSignalMapper *mapper, *mapper2, *mapper3;
    QLabel *number;
    QProgressDialog *progress;
    QCheckBox *czasy;
    bool warunek;

signals:

public slots:
    void ustawLabel(int);
    void ustawSlider(int);
    void obliczenia();
    void ustawWlasny();




};

#endif // STARS_H
