#include "Sessions.h"

Sessions::Sessions(QObject *parent) :
    QObject(parent)
{
}

QVector<Service *> Sessions::getServices(const QString &host_name, unsigned short port)
{
    SocketCmd *ses = findSess(host_name, port);
    QByteArray sendData;
//    ses->SocketWriteData()


}

SocketCmd* Sessions::newSessions(const QString &host_name, unsigned short port)
{
    SocketCmd *ses = new SocketCmd(host_name, port);
    oSock_.push_front(*ses);
    return &ses;
}

SocketCmd* Sessions::findSess(const QString &host_name, unsigned short port)
{
    if(oSock_.isEmpty()){
         return newSessions(host_name, port);
    }
    for(int i = 0; i < oSock_.size(); i++){
        if((oSock_.at(i).Host() == host_name) && (oSock_.at(i).Port()== port))
            return &oSock_.at(i);
    }
    return newSessions(host_name, port);

}
