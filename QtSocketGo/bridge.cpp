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
           emit sendSignal("connect_success");
           connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(SocketReadData()));
           connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(SocketDisconect()));
    }
    return;
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
    if(key.find("@")!=key.npos){
        QMessageBox::warning(this, "Error", "Unexpect key!");
        return;
    }
    QString content = QString(data->toString());
    content.replace("#", "^#");
    string package = key + "@" + content.toStdString() + "\\#";
    if(int(package.length()*sizeof(char))>this->MTU){
        QMessageBox::warning(this, "Error", "Sending data overflow!");
        return;
    }
    qDebug()<<package.c_str();
    tcpSocket->write(package.c_str(), sizeof(char)*package.length());
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
             delete []buffer;
             return;
         }
         QString key = qs.left(idx);
         QString content = qs.right(qs.length()-idx-1);
         content.replace("^#", "#");
         if (!content.endsWith("\\#")){
             qDebug()<<"Receive data not end with '\\#'!";
             if (!content.contains("\\#")){
                 delete []buffer;
                 return;
             }
             int tidx = content.lastIndexOf("\\#");
             content = content.left(tidx);
         }else{
             content = content.left(content.length()-2);
         }
         qDebug()<<"Receive data: "<<key <<"     "<<content<<endl;
         emit getMsg(key, content);
    } else {
           qDebug()<<"FAIL!"<<endl;
           QMessageBox::warning(this, "Error", "Receive message fail!");
    }
    delete []buffer;
    return;
}










