#include "ServerList.h"

ServerList::ServerList(QObject *parent) :
    QObject(parent)
{
}


//======
const QString ServerList::GetName(ushort index) const
{
    if 	(index >= hosts_.size())	return 	0L;

    return 	hosts_.at(index)->name;
}

//======
retErr 	ServerList::SetName(ushort index, const QString &name)
{
    if 	(index >= hosts_.size())	return 	0L;
    hosts_.at(index)->name = name;
    return 	NO_ERR;
}

//======
retErr 	ServerList::DelServer(const QString & host_name, ushort port)
{
    int i = 0;
    foreach( Server *host, hosts_){
        if ((host->ip == host_name) &&(host->port = port)){
            hosts_.removeAt(i);
        }
        i++;
    }

    return 	NO_ERR;
}

retErr ServerList::DelServer(int id)
{
    int i = 0;
    foreach( Server *host, hosts_){
        if (host->sid == id)
            hosts_.removeAt(i);
        i++;
    }
    return 	NO_ERR;
}

//======
Server* ServerList::GetServer(uint index)
{
    if(index >= hosts_.size()) return NULL;
    Server * serv = hosts_.at(index);
    return 	serv;
}

Server* ServerList::GetServer(int id)
{
    int index = FindServer(id);
    if(index == -1) return NULL;
    Server * serv = hosts_.at(index);
    return 	serv;
}

int ServerList::FindServer(const QString & host_name, ushort port)
{
    int		i = 0;

    foreach( Server *host, hosts_){
        if ((host->ip == host_name) &&(host->port = port))
            return i;
        i++;
    }

    return	-1;
}


int ServerList::FindServer(int id)
{
    int		i = 0;

    foreach( Server *host, hosts_){
        if (host->sid == id)
            return i;
        i++;
    }

    return	-1;
}

int ServerList::getServerID(/*const QString &host_name, ushort port*/)
{
    return rand()+1; //====================Исправить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//======
retErr 	ServerList::AddServer(const QString & host_name, ushort port, const QString & info_name, QColor color)
{
//    QString host_name_port = host_name + ":" +QString("").setNum(port);


    //====== Проверим список на повторы.
    if	(FindServer(host_name, port) >= 0)			return  ERR_SERVER_ALREADY_EXIST;

    Server *s = new Server();
    s->sid =  getServerID(); //Получаем SID
    if(s->sid == 0){ //Если сид = 0 - сервера не существует(либо не верный порт);
        delete s;
        return ERR_SERVER_NOT_EXIST;
    }


    s->name = info_name;
    s->ip = host_name;
    s->port = port;
    s->color = color;
    s->servs = getService();
    hosts_.push_back(s);
    return 	0;
}

//=============================================================================
//======
const char * ServerList::GetElementName(void) const
{
    return  "Servers";
}

QVector<Service *> *ServerList::getService()
{

//======Получение сервисов по Протоколу.======

    //==========Временная тестовая заглушка
    QVector<Service *> *ret = new  QVector<Service *>;

    Service *serv1 = new Service();
    serv1->sid = 1;
    serv1->name = "Service 1";
    ret->push_front(serv1);

    Service *serv2 = new Service();
    serv2->sid = 2;
    serv2->name = "Service 2";
    QVector<Service*> *s2 = new QVector<Service*>;

    Service *serv21 = new Service();
    serv21->sid = 21;
    serv21->name = "Service 2.1";

    Service *serv22 = new Service();
    serv22->sid = 22;
    serv22->name = "Service 2.2";
    Service *serv221 = new Service();
    serv221->sid = 221;
    serv221->name = "Service 2.2.1";
    QVector<Service*> *s22 = new QVector<Service*>;
    s22->push_front(serv221);

    serv22->servs = s22;

    Service *serv23 = new Service();
    serv23->sid = 23;
    serv23->name = "Service 2.3";

    s2->push_front(serv21);
    s2->push_front(serv22);
    s2->push_front(serv23);

    serv2->servs = s2;
    ret->push_front(serv2);

    Service *serv3 = new Service();
    serv3->sid = 3;
    serv3->name = "Service 3";
//    serv1.servs = NULL; //Здесь должна быть рекурсия.
    ret->push_front(serv3);
    //=========Временная тестовая заглушка end
    return ret;
}

////====== Сохранение в XML структуру.
//retErr 	ServerList::Save(TiXmlElement * pxml) const
//{
//    int  i;
//    TiXmlElement * item_xml;

//    for (i=0; i < hosts.size(); ++i)
//    {
//        item_xml = new TiXmlElement("Server");
//        item_xml->SetAttribute("host", (const char *)hosts.at(i).toLocal8Bit());
//        if	(!names.at(i).isEmpty())	item_xml->SetAttribute("name", (const char *)names.at(i).toLocal8Bit());
//        pxml->LinkEndChild(item_xml);
//    }

//    return 0;
//}

//////====== Чтение из XML структуры.
//retErr 	ServerList::Load(TiXmlElement * pxml)
//{
//    hosts.clear();
//    names.clear();

//    pxml = pxml->FirstChildElement("Server");
//    while	(pxml)
//    {
//        AddServer(pxml->Attribute("host"), pxml->Attribute("name"));
//        pxml = pxml->NextSiblingElement("Server");
//    }

//    return 0;
//}

////=============================================================================
