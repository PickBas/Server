#include <QCoreApplication>
#include <QString>
#include "QtServer.h"

int get_port(char **argv){
    QString port_str(argv[1]);
    if(!port_str.toInt()){
        qDebug() << "Wrong input!\n";
        QCoreApplication::quit();
    }
    return port_str.toInt();
}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    QtServer server(nullptr);
    qint16 port = get_port(argv);
    if (!server.start_server(port)){
        qDebug() << "Error: " << server.errorString();
        return 1;
    }
    qDebug() << "Server started...";
    return a.exec();
}
