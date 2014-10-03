#include "AdminBackend.h"

AdminBackend::AdminBackend(QObject *parent) :
    QObject(parent)
{
}

QString AdminBackend::getTree()
{
    QString retString = "import QtQuick 2.2\n\
            ListModel {\n\
                    id: treemodel\n\
                    ListElement {\n\
                        text: \"Servers\"\n\
                        %1\n\
                    }\n\
                }\n";

    if(!servers_.size())
            return retString.arg("");
    else{
        QString s = "elements: [";
        for(uint i = 0; i < servers_.size(); i++){
            QString str = "ListElement\n {\nproperty int sid:%4\ntext:\"%1\";\ncolor:%3;\n%2\n},";
            Server * serv = servers_.GetServer(i);
            QString temp = getTreeBranch(serv->servs);

            str = str.arg(serv->name).arg(temp).arg(colorToString(serv->color)).arg(serv->sid);
            s.append(str);
        }
        s = s.replace(s.size()-1, 1, "]");

        return retString.arg(s);
    }

}

void AdminBackend::saveBranchState(int id, bool expanded)
{
    QMap<int, bool>::iterator i = treeState_.find(id);
    if(i != treeState_.end() ) {
        i.value() = expanded;
        ++i;
    }
    else
        treeState_.insert(id,expanded);
}

bool AdminBackend::getBranchState(int id)
{
    return treeState_.value(id, false);
}

QString AdminBackend::itemClicked(const QString &name)
{
    return name+" clicked.";
}

QString AdminBackend::itemDoubleClicked(const QString &name)
{
    return name+" double clicked.";
}

ushort AdminBackend::validateHostParam(const QString &name, const QString &ip, ushort port)
{
    ushort ret = 0;
    if(name.isEmpty())
        ret |= 1;
    if((ip == "000.000.000.000") || (ip == "255.255.255.255"))
        ret |= 2;
    if(!ip.contains(QRegExp("^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$")))
        ret |= 2;
    if(port <= 1024)
        ret |= 4;
    return ret;
}


void AdminBackend::addServer(const QString &name, const QString &ip, const QString &port, QColor color)
{
//    Server *serv = new Server();
//    serv->name = name;
//    serv->ip = ip;
//    serv->port = port.toInt()
//    serv->color = color;

    //проверка, подключение, плучение типа и вместо типа создаем указатели
    //на сервисы

//    QVector<Service *> *servces = new QVector<Service *>(getService());
//    serv->servs = servces;

    servers_.AddServer(ip, port.toInt(), name, color);
}

void AdminBackend::removeServer(int &id)
{
    servers_.DelServer(id);
}



//QVector<Service *> AdminBackend::getService()
//{

//}

QString AdminBackend::getTreeBranch(QVector<Service *> *serv)
{
    if(serv){
        QString retStr = "elements:[";
        for(int i = 0; i < serv->size(); i++){
            QString str = "ListElement\n {\nproperty int sid:%3\ntext:\"%1\";\n%2\n},";
            str = str.arg(serv->at(i)->name).arg(getTreeBranch(serv->at(i)->servs)).arg(serv->at(i)->sid);
            retStr.append(str);
        }

        return retStr.replace(retStr.size()-1, 1, "]");
    }
    else{
        return "";
    }
}

//QString AdminBackend::getTreeBranch(QVector<Server> *serv) const
//{
//    if(serv->size()){
//        QString retStr = "elements:[%1]";
//        foreach (Server srv, serv) {
//            QString str = "ListElement {text:%1;%2;}";
////            str = str.arg(srv.name).arg(getTreeBranch(srv.servs));
//        }
//        return retStr;
//    }
//    else{
//        return "";
//    }
//}
