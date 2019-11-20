#include "bridge.h"
#include<QDebug>
#include<QMessageBox>

using namespace std;

Bridge::Bridge(QWidget *parent):QWidget(parent){
    tcpServer = new QTcpServer();
    tcpSocket = new QTcpSocket();
    Isconnected = false;
}

//start to listen at localhost
int Bridge::start(){
    if(!tcpServer->listen(QHostAddress::LocalHost, ListenAt)) {
        qDebug()<<"Error! Listen fail!"<<endl;
        return -1;
    }else{
        qDebug()<<"Server now is listening at port "<<ListenAt<<endl;
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(MakeSocketConnection()));
        return 0;
    }
}

//update a tcp connection to socket
void Bridge::MakeSocketConnection(){
    qDebug()<<"Someone connect!"<<endl;
    tcpSocket = tcpServer->nextPendingConnection();
    if(!tcpSocket){
           QMessageBox::warning(this, "Msg", "Connect Fail!");

    } else {
           Isconnected = true;
           QMessageBox::information(this, "Msg", "Connect success!");
           connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(SocketReadData()));
           connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(SocketDisconect()));
    }
    return;
}

//read data from socket connection
void Bridge::SocketReadData(){
    char *buffer = new char[MTU+1];
    QString qs = "";
    long long res = tcpSocket->read(buffer, MTU);
    qDebug()<<"result is "<<res<<endl;
    if( strlen(buffer) > 0) {
          qs = buffer;
          qDebug()<<"Success!"<<endl;
          QMessageBox::information(this, "Information", qs);
          tcpSocket->write("OK\n", sizeof("OK\n"));
    }else{
            qDebug()<<"FAIL!"<<endl;
           QMessageBox::warning(this, "Error", "Receive message fail!");
    }
    delete []buffer;
}

//socket connection break
void Bridge::SocketDisconect(){
    QMessageBox::warning(this,"Inof","The connect is Close!");
    this->Isconnected = false;
    tcpSocket->close();
    tcpServer->close();
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));
}

//disconnect initiative
void Bridge::disconnect(){
    this->SocketDisconect();
}
