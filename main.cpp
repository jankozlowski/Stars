#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtPlugin>
//Q_IMPORT_PLUGIN(qjpeg)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
