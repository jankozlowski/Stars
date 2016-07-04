#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stars.h"
#include <ctime>
#include <QMessageBox>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Stars"));
    akcje();
    menusy();
    statusBar()->showMessage(tr(""));
    removeToolBar(ui->mainToolBar);
    one = new Stars;
    setCentralWidget(one);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::akcje(){
    nowy = new QAction(tr("Nowy"),this);
    nowy->setShortcut(QKeySequence::New);
    nowy->setStatusTip(tr("Czyści caly formularz"));
    connect(nowy,SIGNAL(triggered()),this,SLOT(nowe()));

    zapisz = new QAction(tr("Zapisz"),this);
    zapisz->setShortcut(QKeySequence::Save);
    zapisz->setStatusTip(tr("Zapisz wynik do pliku"));
    connect(zapisz,SIGNAL(triggered()),this,SLOT(save()));

    zakoncz = new QAction(tr("Wyjdz"),this);
    zakoncz->setShortcut(QKeySequence(tr("Ctrl+Q")));
    zakoncz->setStatusTip(tr("Wyjdz z programu"));
    connect(zakoncz,SIGNAL(triggered()), qApp, SLOT(quit()));

    op = new QAction(tr("O Programie"),this);
    op->setShortcut(QKeySequence::HelpContents);
    op->setStatusTip(tr("Informacje o programie"));
    connect(op,SIGNAL(triggered()),this,SLOT(oProgramie()));

    porada = new QAction(tr("Porada dnia"),this);
    porada->setShortcut(QKeySequence(tr("Ctrl+h")));
    porada->setStatusTip(tr("Wyświetla losową poradę"));
    connect(porada,SIGNAL(triggered()),this,SLOT(porad()));

    wsc = new QAction(tr("Wschód/Zachód"),this);
}

void MainWindow::menusy(){

    plikmenu = menuBar()->addMenu(tr("Plik"));
    plikmenu -> addAction(nowy);
    plikmenu -> addAction(zapisz);
    plikmenu -> addAction(zakoncz);

    opcjemenu = menuBar()->addMenu(tr("Opcje"));
    opcjemenu ->addAction(wsc);

    pomocmenu = menuBar()->addMenu((tr("Pomoc")));
    pomocmenu -> addAction(op);
    pomocmenu -> addAction(porada);

}

void MainWindow::nowe(){
    one->clearall();
}

void MainWindow::save(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Zapisz wyniki"), "",
        tr("All Files (*.*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, tr("Błąd zapisu"),tr("NIe udało się otworzyć pliku"));
            return;
        }

        QTextStream out(&file);
        out << one->rezultat->toPlainText();
    }
}

void MainWindow::oProgramie(){
    QWidget *programie = new QWidget();
    programie->setWindowTitle(tr("O programie"));
    programie->setFixedSize(485, 180);

    QLabel *fullMoon= new QLabel(programie);
    fullMoon->setPixmap(QPixmap("FullMoon.jpg"));
    fullMoon->setGeometry(5,-50,250,250);
    QPushButton *OK = new QPushButton("OK",programie);
    OK->setGeometry(400,150,80,25);
    QLabel *version = new QLabel(tr("Stars 1.0"),programie);
    version->setGeometry(285,10,80,15);
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    version->setFont(font);
    QLabel *opis = new QLabel(tr("Program umożliwa wyliczenie wschodów i zachodów słonca\ndla dowolnej daty w dowolnym miejscu na ziemi.\n\n"
                              "Autor: Jan Kozłowski\n\nTelefon: 514393032\n\nE-mail: jankozlowsk@gmail.com"),programie);
    opis->setGeometry(170,30,400,125);

    programie->show();
    connect(OK, SIGNAL(clicked()),programie,SLOT(close()));
}

void MainWindow::porad(){

    srand(time(0));
    QMessageBox *poradnik = new QMessageBox();
    poradnik->setWindowTitle(tr("Porada na dziś"));
    poradnik->setFixedSize(485, 180);
    QString porady[] = {tr("Szacunkiem dla przeszłośći jest praca w przyszłości."),tr("Odważni nie żyją wiecznie, ostrożni nie zyją wcale."),
                        tr("Gdybym tak był, gdzie chciałbym być, to byłbym tam, gdzie nie ma mnie, lecz tu, gdzie jestem, muszę być, nie mogę być zaś tam, gdzie chce."),
                        tr("Zbyt wiele przeszłości, za mało terażniejszośći, żadnej przyszłości."), tr("Wiedzę możemy przejąć od innych, ale mądrości musimy nauczyć się sami."),
                        tr("Nic na tym świecie nie stoi Ci na przeszkodzie, poza Twoim własnym przekonaniem, że coś Ci przeszkadza."),
                        tr("Wolność jest jak powietrze na szczycie góry. I jedno, i drugie nie do zniesienia dla słabych."),
                        tr("Wolność myśli jest przede wszystkim wolnością błądzenia."),
                        tr("Gdy język potrafi już tylko narzekać i krytykować, oznacza to, że chore jest serce."),
                        tr("Idż swoją drogą, a ludzie niech mówią, co chcą."), tr("Nikogo nie możesz zmusić do tego aby cię kochał, ale to co możesz zrobić to być kim kogo warto kochać."),
                        tr("Lepszy w wolności kąsek byle jaki niż w niewoli przysmaki."), tr("Jeżli jedna osoba coś potrafi, każda może się tego nauczyć."),
                        tr("Dobrze, że nie ma człowieka bez wad, bo taki człowiek nie miałby też przyjaciół."), tr("Przyażń zawsze jest pożyteczna, a miłość często szkodliwa."),
                        tr("Nigdy nie pozwól, by szkoła staneła na drodze Twojej edukacji."), tr("Drogi wcale nie muszą dokąść prowadzić. Muszą się tylko gdzieś zaczynać."),
                        tr("W gruncie rzeczy ważniejsze jest aby mieć cel niż żeby go osiągnąc."), tr("Nie idż za tłumem bo nigdzie nie dojdziesz."),
                        tr("Nie przestawaj się uśmiechać. Uśmiech jest mową duszy, gdy słowa nic nie pomogą, Uśmiech serce poruszy."),
                        tr("Nigdy nie porównuj się do gorszych od siebie bo będziesz stawał się coraz gorszy."), tr("Każdy cel jest możliwy do osiągnięcia, jeśli w to uwierzysz."),
                        tr("Nigdy nie kłóć się z głupkiem. Znizy cię do swojego poziomu i pokona doświadczeniem."),
                        tr("Co dostane za pieniądze Zdrowie? Nie tylko lekarzy. Wiarę? Nie tylko księży. Miłość Nie tylko chętne kobiety. Przyjażń Nie tylko towarzystwo. Dom? Nie tylko budynek."),
                        tr("Błąd jest przywilejem filozofów, tylko głupcy nie mylą się nigdy."), tr("Działanie jest najlepszym lekarstwem na rozpacz."),
                        tr("Nie ma porażek - tylko informacje zwrotne - lekcje, które uczą nas życia i pozwalają uniknąć gorszych błędów w przyszłości."),
                        tr("Sokrates zapytany przez swojego ucznia w kwestii tego czy się zenić odpowiedział: Cokolwiek wybierzesz i tak będziesz żałować."),
                        tr("Ci którzy odrzucają wolność dla bezpieczeństwa, nie zasługują ani na jedno ani na drugie."), tr("Uśmiech kosztuje mniej niż elektryczność i daje więcej światła.")};
    int fate=rand()%((sizeof porady)/(sizeof porady[0]));
    poradnik->setText(porady[fate]);
    poradnik->setIcon(QMessageBox::Information);
    poradnik->setStandardButtons(QMessageBox::Ok);

    poradnik->show();


}
