#ifndef QTSOCKET_H
#define QTSOCKET_H

#include <QTcpSocket>

class QtSocket : public QTcpSocket{
    Q_OBJECT

public:
    QtSocket(qintptr handle, QObject *parent = nullptr);

signals:
    void MsReadyRead(QtSocket *);
    void MsStateChanged(QtSocket *, int);

};

#endif // QTSOCKET_H
