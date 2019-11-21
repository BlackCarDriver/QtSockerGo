#include "bridge.h"
#include "datastruct.h"
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
        return -1;
    }else{
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
    qDebug()<<"read, length is "<<res<<endl;
    if( strlen(buffer) > 0) {
         qs = buffer;
         int idx = qs.indexOf("@");
         if (idx < 0 ){
             qDebug()<<"Error: no @ in receive data!"<<endl;
             return;
         }
         QString key = qs.left(idx);
         QString content = qs.right(qs.length()-idx-1);
         qDebug()<<"Receive data: "<<key <<"     "<<content<<endl;
         emit getMsg(key, content);
    } else {
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
    sendSignal("disconnect");
}

//disconnect initiative
void Bridge::disconnect(){
    this->SocketDisconect();
}

//send data to client
//key defined the function and can't contain char '@'
void Bridge::sendMessage(string key, DataStruct *data){
    if(key.find("@")!=0){
        QMessageBox::warning(this, "Error", "Unexpect key!");
        exit(1);
    }
    string package = key + "@" + data->toString();
    if(int(package.length()*sizeof(char))>this->MTU){
        QMessageBox::warning(this, "Error", "Sending data overflow!");
        exit(1);
    }
    tcpSocket->write(package.c_str(), sizeof(char)*package.length());
}












