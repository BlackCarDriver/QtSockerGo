#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //forbid to use all function before qt connect with go
    widgeArray.push_back(ui->sendBtn);
    widgeArray.push_back(ui->sendInput);
    widgeArray.push_back(ui->textEdit);
    setWidgeState(false);

    //start wait for socket connection
    bridge = new Bridge();
    int suc = bridge->start();
    if (suc>=0){
        connect(bridge, SIGNAL(getMsg(QString, QString)), this, SLOT(messageHandle(QString, QString)));
        connect(bridge, SIGNAL(sendSignal(QString)), this, SLOT(functionHandle(QString)));
    }else{
        QMessageBox::warning(this, "Error", "Fail when listen at localhost:4747!");
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete bridge;
}

//setWidgeState set widge in mainwindow enable or disable
void MainWindow::setWidgeState(bool usable){
    for(uint i=0; i<widgeArray.size(); i++){
        widgeArray[i]->setEnabled(usable);
    }
}

//send inputbox content to go client
void MainWindow::on_sendBtn_clicked(){
    simpleStr* data = new(simpleStr);
    QString inputtext = ui->sendInput->toPlainText();
    data->init(inputtext);
    bridge->sendMessage("msg", data);
    delete data;
}

//functionHandle is a interface for bridge to controll mainwindow
void MainWindow::functionHandle(QString key){
   if(key=="connect_success"){
       setWidgeState(true);
   } else if(key=="disconnect"){
       setWidgeState(false);
   } else {
       QMessageBox::warning(this, "warn", "Unknow Signal: "+ key);
   }
}


//messageHandle handle the data or message get from go
void MainWindow::messageHandle(QString key, QString content){
    if (key=="msg"){
        ui->textEdit->append(content);
    }else if(key=="show") {
        ui->textEdit->setText(content);
    }
}
