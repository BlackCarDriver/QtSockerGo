#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    bridge = new Bridge();
    int suc = bridge->start();
    if (suc>=0){
        ui->startBtn->setDisabled(true);
    }else{
        QMessageBox::warning(this, "Error", "Fail when listen at localhost:4747!");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_stopBtn_clicked(){
    qDebug()<<"Disconnect!"<<endl;
    bridge->disconnect();
    ui->startBtn->setDisabled(false);
    ui->stopBtn->setDisabled(true);
}

void MainWindow::on_startBtn_clicked(){
    if(bridge->Isconnected){
        return;
    }
    int suc = bridge->start();
    if (suc){
        QMessageBox::information(this, "Msg", "Lanugh Success!");
        ui->startBtn->setDisabled(true);
        ui->stopBtn->setDisabled(false);
    }else{
        QMessageBox::warning(this, "Msg", "Lanugh Fail!");
    }
}
