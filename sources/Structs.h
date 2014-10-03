#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include "Common.h"
#include <QColor>
#include <QVector>

struct Service{
    int sid;    // Servce ID, определ€ющий тип сервиса
    QString name;

    QVector<Service*> *servs;
};

struct Server{
    int sid;        // Server ID, определ€ющий тип сервера
    QString name;
    QString ip;
    ushort port;
    QColor color;
    QVector<Service*> *servs;
    //ƒругие параметры
};

struct Settings{
    QString lang;
    QString cdTbl;
    ushort dbglvl;
    bool dlask;
    bool inferrsrv;
};


#endif // SERVER_H
