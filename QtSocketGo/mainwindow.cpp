#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //forbid to use all function before qt connect with go
    widgeArray.push_back(ui->sendBtn);
    widgeArray.push_back(ui->stopBtn);
    widgeArray.push_back(ui->sendInput);
    widgeArray.push_back(ui->textEdit);
    widgeArray.push_back(ui->startBtn);
    setWidgeState(false);

    //start wait for socket connection
    bridge = new Bridge();
    int suc = bridge->start();
    if (suc>=0){
        connect(bridge, SIGNAL(getMsg(QString, QString)), this, SLOT(messageHandle(QString, QString)));
        connect(bridge, SIGNAL(sendSignal(QString)), this, SLOT(functionHandle(QString)));
        setWidgeState(true);
    }else{
        QMessageBox::warning(this, "Error", "Fail when listen at localhost:4747!");
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete bridge;
}

void MainWindow::on_stopBtn_clicked(){
    return;
}

void MainWindow::on_startBtn_clicked(){
   return;
}

//messageHandle handle the data or message get from go
void MainWindow::messageHandle(QString key, QString content){
    if (key=="show"){
        ui->textEdit->setHtml(content);
    }
}

//functionHandle is a interface for bridge to controll mainwindow
void MainWindow::functionHandle(QString key){
   if(key=="disconnect"){
       setWidgeState(false);
   }
}

//setWidgeState set widge in mainwindow enable or disable
void MainWindow::setWidgeState(bool usable){
    for(uint i=0; i<widgeArray.size(); i++){
        widgeArray[i]->setEnabled(usable);
    }
}
