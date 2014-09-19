#include "ServerList.h"

ServerList::ServerList(QObject *parent) :
    QObject(parent)
{
}

Server* ServerList::GetServer(unsigned short index)
{
    if 	(index >= hosts_.size())	return 	0L;

    Server * serv = hosts_.at(index);
    return 	serv;
}

//QVector<Server *> ServerList::GetServerList()
//{
//    return hosts_;
//}

//======
const QString ServerList::GetName(unsigned short index) const
{
    if 	(index >= hosts_.size())	return 	0L;

    return 	hosts_.at(index)->name;
}

//======
retErr 	ServerList::SetName(unsigned short index, const QString &name)
{
    if 	(index >= hosts_.size())	return 	0L;
    hosts_.at(index)->name = name;
    return 	NO_ERR;
}

//======
retErr 	ServerList::DelServer(const QString & host_name, unsigned short port)
{
    int i = 0;
    foreach( Server *host, hosts_){
        if ((host->ip == host_name) &&(host->port = port))
            hosts_.removeAt(i);
        i++;
    }

    return 	NO_ERR;
}

//======
int 	ServerList::FindServer(const QString & host_name, unsigned short port) const
{
    int		i = 0;

    foreach( Server *host, hosts_){
        if ((host->ip == host_name) &&(host->port = port))
            return i;
        i++;
    }

    return	-1;
}

//======
retErr 	ServerList::AddServer(const QString & host_name, unsigned short port, const QString & info_name)
{
    QString host_name_port = host_name + ":" +QString("").setNum(port);
    retErr rcod = ValidateHostName(host_name_port);
    if	(rcod)	return	rcod;

    unsigned short i;
    char	naddr[512];
    xstrcpy(naddr, host_name_port.toLocal8Bit().data());

//    ====== �������� ���������� ����-�����.
    if	((port < 1) || !naddr[0])		return	ERR_NET_PORT_NUMBER;

    i = strlen(naddr);
    naddr[i] = ':';
    xstrnum(naddr + i + 1, (unsigned short)port);

    //====== �������� ������ �� �������.
    if	(FindServer(host_name, port) >= 0)			return  ERR_SERVER_ALREADY_EXIST;

    Server *s = new Server();
    s->name = info_name;
    s->ip = host_name;
    s->port = port;
    s->color = QColor("black"); // ��������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!<<<<<<<<<<<<
    hosts_.push_back(s);
    return 	0;
}

//=============================================================================
//======
const char * ServerList::GetElementName(void) const
{
    return  "Servers";
}

//====== ���������� � XML ���������.
//retErr 	ServerList::Save(TiXmlElement * pxml) const
//{
//	int  i;
//	TiXmlElement * item_xml;

//	for (i=0; i < hosts.size(); ++i)
//	{
//		item_xml = new TiXmlElement("Server");
//		item_xml->SetAttribute("host", (const char *)hosts.at(i).toLocal8Bit());
//		if	(!names.at(i).isEmpty())	item_xml->SetAttribute("name", (const char *)names.at(i).toLocal8Bit());
//		pxml->LinkEndChild(item_xml);
//	}

//	return 0;
//}

////====== ������ �� XML ���������.
//retErr 	ServerList::Load(TiXmlElement * pxml)
//{
//	hosts.clear();
//	names.clear();

//	pxml = pxml->FirstChildElement("Server");
//	while	(pxml)
//	{
//		AddServer(pxml->Attribute("host"), pxml->Attribute("name"));
//		pxml = pxml->NextSiblingElement("Server");
//	}

//	return 0;
//}

//=============================================================================
