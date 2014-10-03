#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QObject>
#include <QVector>
#include "Common.h"


class ServerList : public QObject
{
    Q_OBJECT
public:
    explicit ServerList(QObject *parent = 0);

//    QVector<Server *> GetServerList();
    const QString GetName(ushort index) const;
    retErr	SetName(ushort index, const QString &name);
    retErr	DelServer(const QString & host_name, ushort port);
    retErr  DelServer(int id);

    retErr 	AddServer(const QString & host_name, ushort port, const QString & info_name, QColor color);

    Server* GetServer(uint index);
    Server* GetServer(int id);
    int FindServer(const QString & host_name, ushort port);
    int FindServer(int id);
    int     getServerID(/*const QString & host_name, ushort port*/);
//    SID     getServiceID();

    uint size(){    return hosts_.size();    }
    //======
    const char * GetElementName(void) const;		//
//    retErr 	Save(TiXmlElement * pxml) const;		// Сохранение в XML структуру.
//    retErr 	Load(TiXmlElement * pxml);				// Чтение из XML структуры.

signals:

public slots:

private:
    QVector<Service *> *getService();

    QVector<Server *> hosts_;

};

#endif // SERVERLIST_H
