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

    Server* GetServer(unsigned short index);
//    QVector<Server *> GetServerList();
    const QString GetName(unsigned short index) const;
    retErr	SetName(unsigned short index, const QString &name);
    retErr	DelServer(const QString & host_name, unsigned short port);
    retErr 	AddServer(const QString & host_name, unsigned short port, const QString & info_name);
    int		FindServer(const QString & host_name, unsigned short port) const;
    unsigned int size(){    return hosts_.size();    }
    //======
    const char * GetElementName(void) const;		//
//	retErr 	Save(TiXmlElement * pxml) const;		// Сохранение в XML структуру.
//	retErr 	Load(TiXmlElement * pxml);				// Чтение из XML структуры.

signals:

public slots:

private:
    QVector<Server *> hosts_;

};

#endif // SERVERLIST_H
