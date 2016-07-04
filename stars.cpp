#include "stars.h"
#include <string>
#include <cmath>
#include <QGridLayout>
#include <QApplication>

Stars::Stars(QWidget *parent) :
    QWidget(parent)
{
    warunek=false;

    QGridLayout * layout = new QGridLayout();
    QGridLayout * layout1 = new QGridLayout();

    QLabel *info1 = new QLabel(tr("Wpisz okres dla jakiego chcesz wyświetlić informacje:"),this);
    QLabel *info2 = new QLabel(tr("Wybierz miasto lub podaj własną lokalizacje:"),this);
    QLabel *start = new QLabel(tr("Początek okresu:"),this);
    QLabel *end = new QLabel(tr("Koniec okresu:"),this);
    QLabel *szer = new QLabel(tr("Szerokość:"),this);
    QLabel *dlug = new QLabel(tr("Długość:"),this);
    QLabel *strefa = new QLabel(tr("Strefa czasowa:"),this);
    QLabel *minus12 = new QLabel(tr("-12"),this);
    QLabel *plus12 = new QLabel(tr("12"),this);
    number = new QLabel(tr("0"),this);

    QFontMetrics metrics(QApplication::font());

    sday = new QLineEdit(tr("29"),this);
    sday->setMinimumWidth((metrics.width("99")));
    smonth = new QLineEdit(tr("11"),this);
    smonth->setMinimumWidth((metrics.width("99")));
    syear = new QLineEdit(tr("2012"),this);
    syear->setMinimumWidth((metrics.width("9999")));
    kday = new QLineEdit(tr("21"),this);
    kday->setMinimumWidth((metrics.width("99")));
    kmonth = new QLineEdit(tr("12"),this);
    kmonth->setMinimumWidth((metrics.width("99")));
    kyear = new QLineEdit(tr("2012"),this);
    kyear->setMinimumWidth((metrics.width("9999")));

    szerokosc = new QLineEdit(tr(""),this);
    dlugosc = new QLineEdit(tr(""),this);
    rezultat = new QTextEdit(tr(""),this);
    rezultat->append(tr("Rezultat"));
    rezultat->setReadOnly(true);
    rezultat->setAlignment(Qt::AlignCenter);
    rezultat->setMinimumWidth(300);

    miasta[0] = new QRadioButton(tr("Gdańsk"), this);
    miasta[1] = new QRadioButton(tr("Warszawa"), this);
    miasta[2] = new QRadioButton(tr("Nowy York"), this);
    miasta[3] = new QRadioButton(tr("Sydney"), this);
    miasta[4] = new QRadioButton(tr("Montreal"), this);
    miasta[5] = new QRadioButton(tr("Shanghai"), this);
    miasta[6] = new QRadioButton(tr("Jerusalem"), this);
    miasta[7] = new QRadioButton(tr("Tokio"), this);
    miasta[8] = new QRadioButton(tr("Moskwa"), this);
    miasta[9] = new QRadioButton(tr("Własna:"),this);

    strefy = new QSlider(Qt::Horizontal,this);
    strefy->setMinimum(-12);
    strefy->setMaximum(12);

    oblicz = new QPushButton(tr("Oblicz"),this);
    oblicz->setStatusTip(tr("Wyświetl wyniki"));

    czasy = new QCheckBox(tr("Uwzglednij czas letni oraz zimowy (UE)"),this);

    QSpacerItem *puste_pole = new QSpacerItem(20,10);

    QGridLayout * layout2 = new QGridLayout();
    layout2->addWidget(sday,0,0);
    layout2->addWidget(smonth,0,1);
    layout2->addWidget(syear,0,2);
    layout2->addItem(puste_pole,0,3);
    layout2->addWidget(kday,0,4);
    layout2->addWidget(kmonth,0,5);
    layout2->addWidget(kyear,0,6);

    layout1->addWidget(info1,0,0,1,4,Qt::AlignCenter);
    layout1->addWidget(start,1,0,1,2,Qt::AlignLeft);
    layout1->addWidget(end,1,2,1,2,Qt::AlignRight);
    layout1->addLayout(layout2,2,0,1,4);
    layout1->addWidget(info2,3,0,1,4,Qt::AlignCenter);

    layout1->addWidget(miasta[0],4,0);
    layout1->addWidget(miasta[1],4,1);
    layout1->addWidget(miasta[3],5,0);
    layout1->addWidget(miasta[4],5,1);
    layout1->addWidget(miasta[6],6,0);
    layout1->addWidget(miasta[7],6,1);

    QVBoxLayout *prawe_miasta = new QVBoxLayout;
    prawe_miasta->addWidget(miasta[2]);
    prawe_miasta->addWidget(miasta[5]);
    prawe_miasta->addWidget(miasta[8]);

    layout1->addLayout(prawe_miasta,4,2,3,1,Qt::AlignRight);

    layout1->addWidget(szer,7,0,Qt::AlignCenter);
    layout1->addWidget(miasta[9],7,1);
    layout1->addWidget(dlug,7,2,Qt::AlignCenter);
    layout1->addWidget(szerokosc,8,0);
    layout1->addWidget(dlugosc,8,2);
    layout1->addWidget(czasy,9,0,1,4,Qt::AlignCenter);

    QGridLayout * layout3 = new QGridLayout();
    layout3->addWidget(strefa,0,1,Qt::AlignCenter);

    layout3->addWidget(minus12,1,0);
    layout3->addWidget(strefy,1,1);
    layout3->addWidget(plus12,1,3);
    layout3->addWidget(number,3,1, Qt::AlignCenter);

    layout1->addLayout(layout3,10,0,2,2);
    layout1->addWidget(oblicz,10,2,2,1);

    layout->addLayout(layout1,0,0);
    layout->addWidget(rezultat,0,1);

    this->setLayout(layout);
    this->show();

    mapper = new QSignalMapper(this);
    mapper2 = new QSignalMapper(this);
    mapper3 = new QSignalMapper(this);


    QString geograficzneSzerokosci[10] = {"54.37","52.25","40.75","-33.53","45.52","31.25","31.49","35.70","55.75",""};
    QString geograficzneDlugosci[10] = {"18.63","21.00","-74.00","151.06","-73.58","121.50","35.30","139.76","37.50",""};
    int strefyczasowe[10] ={ 1, 1, -6, 9, -5, 8, 2, 8, 4, 0 };
    QByteArray arrayDlugosc[10];
    QByteArray arraySzerokosc[10];
    const char* zdanie[10];
    const char* zdanie2[10];

    for(int a=0; a<10; a++){
        arrayDlugosc[a] = geograficzneDlugosci[a].toUtf8();
        zdanie[a] = arrayDlugosc[a].constData();
        mapper->setMapping(miasta[a], tr(zdanie[a]));
        connect(miasta[a], SIGNAL(clicked()),mapper, SLOT(map()));
        mapper3->setMapping(miasta[a], strefyczasowe[a]);
        connect(miasta[a],SIGNAL(clicked()),mapper3, SLOT(map()));
    }

    for(int a=0; a<10; a++){
        arraySzerokosc[a] = geograficzneSzerokosci[a].toUtf8();
        zdanie2[a] = arraySzerokosc[a].constData();
        mapper2->setMapping(miasta[a], tr(zdanie2[a]));
        connect(miasta[a], SIGNAL(clicked()),mapper2, SLOT(map()));
    }


    connect(mapper, SIGNAL(mapped(QString)), dlugosc, SLOT(setText(QString)));
    connect(mapper2, SIGNAL(mapped(QString)), szerokosc, SLOT(setText(QString)));
    connect(mapper3, SIGNAL(mapped(int)), this, SLOT(ustawLabel(int)));
    connect(mapper3, SIGNAL(mapped(int)), this, SLOT(ustawSlider(int)));

    connect(strefy, SIGNAL(valueChanged(int)), this,SLOT(ustawLabel(int)));
    connect(szerokosc, SIGNAL(selectionChanged()),this,SLOT(ustawWlasny()));
    connect(dlugosc, SIGNAL(selectionChanged()), this, SLOT(ustawWlasny()));
    connect(oblicz,SIGNAL(clicked()),this,SLOT(obliczenia()));

}

void Stars::ustawLabel(int a){
    number->setNum(a);
}

void Stars::ustawSlider(int a){
    strefy->setValue(a);
}

void Stars::ustawWlasny(){
    miasta[9]->setChecked(true);
    ustawSlider(0);
}

void Stars::clearall(){
    syear->clear();
    smonth->clear();
    sday->clear();
    kyear->clear();
    kmonth->clear();
    kday->clear();
    szerokosc->clear();
    dlugosc->clear();
    rezultat->clear();
    rezultat->setAlignment(Qt::AlignCenter);
    rezultat->append(tr("Rezultat"));
}

void Stars::obslugaBlad(QString title, QString tresc){
    QMessageBox *poradnik = new QMessageBox();
    QByteArray array;
    array = title.toUtf8();
    const char *tytul=array.constData();
    poradnik->setWindowTitle(tr(tytul));
    QByteArray array2;
    array2 = tresc.toUtf8();
    const char *content=array2.constData();
    poradnik->setWindowTitle(tr(tytul));
    poradnik->setText(tr(content));
    poradnik->setIcon(QMessageBox::Warning);
    poradnik->setStandardButtons(QMessageBox::Ok);
    poradnik->show();
}

void Stars::bledy(){

    int sdzien = sday->text().toInt();
    int smiesiac =  smonth->text().toInt();
    int srok = syear->text().toInt();
    int kdzien = kday->text().toInt();
    int kmiesiac =  kmonth->text().toInt();
    int krok =  kyear->text().toInt();


    if(syear->text() == "" || smonth->text() == "" || sday->text() == "" || kyear->text() == ""  || kmonth->text() == "" || kday->text() == "" || szerokosc->text() == "" || dlugosc->text() == "")
        throw 1;
    if(srok>krok || (srok==krok && smiesiac>kmiesiac) || (srok==krok && smiesiac==kmiesiac && sdzien>kdzien))
        throw 2;
    if(!(syear->text()).toInt() || !(smonth->text()).toInt() || !(sday->text()).toInt() || !(kyear->text()).toInt() || !(kmonth->text()).toInt() || !(kday->text()).toInt() || !(szerokosc->text()).toDouble() || !(dlugosc->text()).toDouble())
        throw 3;
    if(szerokosc->text().toDouble()<-90 || szerokosc->text().toDouble()>90)
        throw 4;
    if(dlugosc->text().toDouble()<-180 || dlugosc->text().toDouble()>180)
        throw 5;
    if(srok<-4713 || krok<-4713)
        throw 6;
    if(smiesiac<1 || smiesiac>12 || kmiesiac<1 || kmiesiac>12)
        throw 7;
    int liczba_dni[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,28,31,30,31,30,31,31,30,31,30,31}};
    if(srok % 4 == 0)
        liczba_dni[0][1]=29;
    if(krok % 4 == 0)
        liczba_dni[1][1]=29;
    if(sdzien<1 || sdzien>liczba_dni[0][smiesiac-1] || kdzien<1 || kdzien>liczba_dni[1][kmiesiac-1])
        throw 8;
}

void Stars::stopka(){
    rezultat->clear();
    rezultat->setAlignment(Qt::AlignCenter);
    rezultat->append(tr("Wschód i Zachód Słońca"));
    rezultat->append(tr("_______________________\n"));

    rezultat->append(tr("      Data                  Wschód           Zachód\n\n"));
}

int Stars::zmianaCzasu(int dzien, int miesiac, int rok){

    int z,e;

    if (miesiac==3 || miesiac==10){
        if(miesiac<3){
            z=rok-1;
            e=0;
        }
        else{
            z=rok;
            e=2;
        }

    int day=(((23*miesiac)/9) + dzien + 4 + rok + (z/4) - (z/100) + (z/400) - e) % 7;
    return day;
    }
    return 666;
}

void Stars::wschodslonca(int DzienPoczatkowy, int MiesiacPoczatkowy, int RokPoczatkowy){

    double Szerokosc = (szerokosc->text()).toDouble();
    double Dlugosc = (dlugosc->text()).toDouble();
    double Wysokosc = -0.833;

    double Julianski, Stulecie, L, G, O, F, E, A, C, Wschod, Zachod, minW, minZ;
    int WynikWschod, WynikZachod;

    int czas = 0;

    if(czasy->isChecked()){
        int day;
        day=zmianaCzasu(DzienPoczatkowy,MiesiacPoczatkowy,RokPoczatkowy);
        if(day==0){
            if(DzienPoczatkowy+7>31){
                warunek=!warunek;
            }
        }
        if(warunek==true)
            czas=1;
    }


    Julianski = 367*RokPoczatkowy-floor((double)(7*(RokPoczatkowy+floor(((double)(MiesiacPoczatkowy+9)/12)))/4))+floor((double)(275*MiesiacPoczatkowy/9))+DzienPoczatkowy-730531.5;
    Stulecie = Julianski/36525;
    L = fmod((4.8949504201433+628.331969753199*Stulecie),6.28318530718);
    G = fmod((6.2400408+628.3019501*Stulecie),6.28318530718);
    O = 0.409093-0.0002269*Stulecie;
    F = 0.033423*sin(G)+0.00034907*sin(2*G);
    E = 0.0430398*sin(2*(L+F))-0.00092502*sin(4*(L+F))-F;
    A = asin((sin(O))*(sin(L+F)));
    C = (sin(0.017453293*Wysokosc)-sin(0.017453293*Szerokosc)*sin(A))/(cos(0.017453293*Szerokosc)*cos(A));
    Wschod = (M_PI-(E+0.017453293*Dlugosc+acos(C)))*57.29577951/15;
    Zachod = (M_PI-(E+0.017453293*Dlugosc+(-1)*acos(C)))*57.29577951/15;

    minW=round((Wschod - floor(Wschod)) * 60);
    minZ=round((Zachod - floor(Zachod)) * 60);
    WynikWschod=int(floor(Wschod)+strefy->sliderPosition()+czas);
    WynikZachod=int(floor(Zachod)+strefy->sliderPosition()+czas);

    if(WynikWschod<0)
        WynikWschod=24+WynikWschod;
    else if(WynikWschod>=24)
        WynikWschod=WynikWschod-24;
    if(WynikZachod<0)
        WynikZachod=24+WynikZachod;
    else if(WynikZachod>=24)
        WynikZachod=WynikZachod-24;

   if(QString::number(DzienPoczatkowy).length()==1)
       rezultat->insertPlainText("  ");
   rezultat->insertPlainText(QString::number(DzienPoczatkowy));
   rezultat->insertPlainText(".");
   if(QString::number(MiesiacPoczatkowy).length()==1)
         rezultat->insertPlainText("0");
   rezultat->insertPlainText(QString::number(MiesiacPoczatkowy));
   rezultat->insertPlainText(".");
   rezultat->insertPlainText(QString::number(RokPoczatkowy));
   rezultat->insertPlainText("               ");
   rezultat->insertPlainText(QString::number(WynikWschod));
   rezultat->insertPlainText(":");
   if(minW<10)
       rezultat->insertPlainText("0");
   rezultat->insertPlainText(QString::number(minW));
   rezultat->insertPlainText("               ");
   rezultat->insertPlainText(QString::number(WynikZachod));
   rezultat->insertPlainText(":");
   if(minZ<10)
       rezultat->insertPlainText("0");
   rezultat->insertPlainText(QString::number(minZ));
   rezultat->append("");

}

void Stars::kalendarz(bool prawda, int &dni){

    int DzienPoczatkowy = (sday->text()).toInt();
    int MiesiacPoczatkowy = (smonth->text()).toInt();
    int RokPoczatkowy = (syear->text()).toInt();
    int DzienKoncowy = (kday->text()).toInt();
    int MiesiacKoncowy = (kmonth->text()).toInt();
    int RokKoncowy = (kyear->text()).toInt();

    int a=0;
    int LiczbaDni;


        while(DzienPoczatkowy!=DzienKoncowy || MiesiacPoczatkowy!=MiesiacKoncowy || RokPoczatkowy!=RokKoncowy){
            if(a==1){
                MiesiacPoczatkowy = 1;
                DzienPoczatkowy = 1;
            }
            while(MiesiacPoczatkowy<=13){
                if(MiesiacPoczatkowy==13){
                    RokPoczatkowy = RokPoczatkowy +1;
                    break;
                }

                if(MiesiacPoczatkowy == 1 || MiesiacPoczatkowy == 3 || MiesiacPoczatkowy == 5 || MiesiacPoczatkowy == 7 || MiesiacPoczatkowy == 8 || MiesiacPoczatkowy == 10 || MiesiacPoczatkowy == 12)
                    LiczbaDni=31;
                else if(MiesiacPoczatkowy == 4 || MiesiacPoczatkowy == 6 || MiesiacPoczatkowy == 9 || MiesiacPoczatkowy == 11)
                    LiczbaDni=30;
                else{
                    if(RokPoczatkowy % 4 == 0)
                        LiczbaDni=29;
                    else
                        LiczbaDni=28;
                }

                if(DzienPoczatkowy==DzienKoncowy && MiesiacPoczatkowy==MiesiacKoncowy && RokPoczatkowy!=RokKoncowy){
                    DzienPoczatkowy=DzienPoczatkowy+1;
                    a=2;
                }
                if(DzienPoczatkowy==DzienKoncowy && MiesiacPoczatkowy==MiesiacKoncowy)
                    break;
                if(a==1)
                    DzienPoczatkowy = 1;

                while (DzienPoczatkowy<=LiczbaDni+1){
                    a=1;
                    if(DzienPoczatkowy == LiczbaDni+1){
                        MiesiacPoczatkowy = MiesiacPoczatkowy + 1;
                        break;
                    }
                    if(prawda==true){
                        wschodslonca(DzienPoczatkowy,MiesiacPoczatkowy,RokPoczatkowy);
                        if(progress->wasCanceled())
                            return;
                        progress->setValue(dni);

                    }
                    if(DzienPoczatkowy==DzienKoncowy && MiesiacPoczatkowy==MiesiacKoncowy)
                        break;
                    DzienPoczatkowy = DzienPoczatkowy+1;
                    dni++;
                }
            }
        }

    if(a==0 && prawda==true)
        wschodslonca(DzienPoczatkowy,MiesiacPoczatkowy,RokPoczatkowy);

}

void Stars::obliczenia(){

    stopka();
    if(czasy->isChecked()){
    warunekPoczatkowy((sday->text()).toInt(), (smonth->text()).toInt());
    }
    int dni = 0;
    int &days = dni;
    try{
    bledy();
    kalendarz(false, days);
    progress = new QProgressDialog(tr("Obliczanie wschodów i zachodów słonca"), "Anuluj",0,dni);
    progress->setWindowModality(Qt::WindowModal);
    dni=0;
    progress->show();
    connect(progress, SIGNAL(canceled()), this, SLOT(cancel()));
    kalendarz(true, days);
    progress->close();
    }
    catch(int e){
        if(e==1)
            obslugaBlad(tr("Brak wartości"), tr("Wszystkie pola muszą być wypełnione."));
        else if(e==2)
            obslugaBlad(tr("Zły okres"), tr("Końcowy okres nie może być mniejszy od początkowego."));
        else if(e==3)
            obslugaBlad(tr("Litera"), tr("W podanych polach nie może być liter."));
        else if(e==4)
            obslugaBlad(tr("Nieodpowiednia Szerokość"), tr("Szerokość geograficzna powinna mieścić się w przedziale od -180 do 180."));
        else if(e==5)
            obslugaBlad(tr("Nieodpowiednia Długość"), tr("Długość geograficzna powinna mieścić się w przedziale od -90 do 90."));
        else if(e==6)
            obslugaBlad(tr("Nieodpowiednia Rok"), tr("Rok początkowy oraz końcowy nie nie może być wcześniejszy niż 4713 lat p.n.e."));
        else if(e==7)
            obslugaBlad(tr("Nieodpowiednia Miesiąc"), tr("Miesiąc początkowy oraz końcowy musi mieścić się w przedziale od 1 do 12."));
        else if(e==8)
            obslugaBlad(tr("Nieodpowiednia Dzień"), tr("Dzień początkowy oraz końcowy musi odzwierciedlać prawdziwą liczbę dni w miesiącu."));
        else
            obslugaBlad(tr("Nieznany błąd"),tr("Powstał nieznany błąd."));
    }
}

void Stars::warunekPoczatkowy(int dzien, int miesiac){
    if(miesiac>3 && miesiac<10)
        warunek=true;
    else if(miesiac==3 && dzien>=24){
    int liczba = 31-dzien;
    int day=zmianaCzasu(dzien, miesiac, (syear->text()).toInt());
    if (day==0)
        day=7;
    if((day+liczba)<7)
            warunek=true;
    else
            warunek=false;
    }
    else if(miesiac==10 && dzien>=24){
        int liczba = 31-dzien;
        int day=zmianaCzasu(dzien, miesiac, (syear->text()).toInt());
        if (day==0)
            day=7;
        if((day+liczba)<7)
                warunek=false;
        else
                warunek=true;
    }

}



