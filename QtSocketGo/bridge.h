#ifndef BRIDGE_H
#define BRIDGE_H
#include <QDialog>
#include <QTcpServer>
#include <QtNetwork>
#include <QMainWindow>

/*
 bridge is the tool to connect qt and go ;
*/

class Bridge : public QWidget{
     Q_OBJECT
public:
    Bridge(QWidget *parent = nullptr);
    virtual ~Bridge(){}
    void disconnect();
    bool Isconnected;
    int start();

private slots:
     void MakeSocketConnection();
     void SocketReadData();
     void SocketDisconect();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    const quint16 ListenAt = 4747;
    const int MTU = 1024 * 100;
};

#endif // BRIDGE_H
