#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stars.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void akcje();
    void menusy();

private:
    Ui::MainWindow *ui;

    QMenu *plikmenu,*opcjemenu, *pomocmenu;
    QAction *nowy,*zapisz,*zakoncz, *wsc, *op, *porada;
    Stars *one;


signals:

public slots:
    void nowe();
    void save();
    void oProgramie();
    void porad();


};

#endif // MAINWINDOW_H
