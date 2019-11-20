#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bridge.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stopBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;
    Bridge *bridge;
};
#endif // MAINWINDOW_H