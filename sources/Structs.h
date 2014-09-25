#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QColor>
#include <QVector>

struct Service{
    QString name;
    // возможно здесь будет еще тип сервиса
    QVector<Service*> *servs;
};

struct Server{
    QString name;
    QString ip;
    unsigned short port;
    QColor color;
    QVector<Service*> *servs;
    //Другие параметры
};

struct Settings{
    QString lang;
    QString cdTbl;
    unsigned short dbglvl;
    bool dlask;
    bool inferrsrv;
};


#endif // SERVER_H
