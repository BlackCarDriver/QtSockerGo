#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("QT and Go socket demo");
    w.setFixedSize(440,320);

    w.show();
    return a.exec();
}
