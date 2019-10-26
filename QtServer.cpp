#include "QtServer.h"

QtServer::QtServer(QObject *parent) : QTcpServer(parent){}

bool QtServer::start_server(qint16 port){
    return listen(QHostAddress::Any, port);
}

void QtServer::incomingConnection(qintptr handle){
    auto socket = new QtSocket(handle, this);
    sockets << socket;

    for (auto i : sockets){
        QTextStream text(i);
        text << "Server connected with: " << handle;
        i->flush();
    }
    connect(socket, &QtSocket::MsReadyRead, this, [&] (QtSocket *soc){
        qDebug() << "Ready read...\n";
        QTextStream t(soc);
        auto text = t.readAll();

        for(auto i : sockets){
            QTextStream m(i);
            m << text;
            i->flush();
        }
    });

    connect(socket, &QtSocket::MsStateChanged, [&] (QtSocket *soc, int st){
       if (st == QTcpSocket::UnconnectedState){
           qDebug() << "Unconnected State with handle: " << soc->socketDescriptor();
           sockets.removeOne(soc);
           for (auto i : sockets){
               QTextStream t(i);
               t << "Server: " << soc->socketDescriptor() << "disconnected";
               i->flush();
           }
       }
    });
}


