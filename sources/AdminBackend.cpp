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
            QString str = "ListElement\n {\ntext:\"%1\";\ncolor:%3;\n%2\n},";
            Server * serv = servers_.GetServer(i);
            QString temp = getTreeBranch(serv->servs);
            str = str.arg(servers_.GetServer(i)->name).arg(temp).arg(colorToString(servers_.GetServer(i)->color));
            s.append(str);
        }
        s = s.replace(s.size()-1, 1, "]");

        return retString.arg(s);
    }

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

    servers_.AddServer(ip, port.toInt(), name);
}



//QVector<Service *> AdminBackend::getService()
//{

//}

QString AdminBackend::getTreeBranch(QVector<Service *> *serv)
{
    if(serv){
        QString retStr = "elements:[";
        for(int i = 0; i < serv->size(); i++){
            QString str = "ListElement\n {\ntext:\"%1\";\n%2\n},";
            str = str.arg(serv->at(i)->name).arg(getTreeBranch(serv->at(i)->servs));
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
