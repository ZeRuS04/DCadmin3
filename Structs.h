#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QColor>
#include <QVector>

struct Service{
    QString name;
    // �������� ����� ����� ��� ��� �������
    QVector<Service*> *servs;
};

struct Server{
    QString name;
    QString ip;
    unsigned short port;
    QColor color;
    QVector<Service*> *servs;
    //������ ���������
};

struct Settings{
    QString lang;
    QString cdTbl;
    unsigned short dbglvl;
    bool dlask;
    bool inferrsrv;
};


#endif // SERVER_H
