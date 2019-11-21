#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bridge.h"
#include <QMainWindow>
#include <vector>

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
    void messageHandle(QString key, QString content);
    void functionHandle(QString key);

private:
    Ui::MainWindow *ui;
    Bridge *bridge;
    vector<QWidget*> widgeArray;
    void setWidgeState(bool usable);

};
#endif // MAINWINDOW_H
