#ifndef SESSIONS_H
#define SESSIONS_H

#include <QObject>
#include "Structs.h"
#include "SocketCmd.h"



class Sessions : public QObject
{
    Q_OBJECT
public:
    explicit Sessions(QObject *parent = 0);

    bool isCorrServer(void){    return true;    }
    QVector<Service*> getServices(const QString &host_name, unsigned short port );
    SocketCmd *newSessions(const QString &host_name, unsigned short port);
    SocketCmd *findSess(const QString &host_name, unsigned short port);

signals:

public slots:

private:
    QVector<SocketCmd> oSock_;

};

#endif // SESSIONS_H
