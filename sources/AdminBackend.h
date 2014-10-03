#ifndef ADMINBACKEND_H
#define ADMINBACKEND_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "Common.h"
#include "ServerList.h"
//#include "Sessions.h"


class AdminBackend : public QObject
{
    Q_OBJECT



public:
    explicit AdminBackend(QObject *parent = 0);
    Q_INVOKABLE QString getTree();

    Q_INVOKABLE void saveBranchState(int id, bool expanded);
    Q_INVOKABLE bool getBranchState(int id);

    //=====¬озможно стоит методы эти переделать под sid:
    Q_INVOKABLE QString itemClicked(const QString &name);
    Q_INVOKABLE QString itemDoubleClicked(const QString &name);
    //=====end

    Q_INVOKABLE ushort validateHostParam(const QString &name,const QString &ip, ushort port);

    Settings cfg() const{     return cfg_;    }
    void setCfg(const Settings &cfg){
        cfg_ = cfg;
    }
    void setCfg(const QString &lang, const QString &cdTbl, ushort dbglvl, bool dlask, bool inferrsrv ){
        cfg_.lang = lang;
        cfg_.cdTbl = cdTbl;
        cfg_.dbglvl = dbglvl;
        cfg_.dlask = dlask;
        cfg_.inferrsrv = inferrsrv;
    }

signals:

public slots:
    void addServer(const QString &name, const QString &ip, const QString &port, QColor color);
    void removeServer(int &id);

private:
    Settings cfg_;
    ServerList servers_;
    QMap<int, bool> treeState_;

//    Sessions sessions_;


//    QVector<Service *> getService();
//    QString getTreeBranch(QVector<Server> *serv) const;

    QString getTreeBranch(QVector<Service *> *serv);
    QString colorToString(QColor color){
        QString str = "\"#%1%2%3\"";
        QString r = QString("").setNum(color.red(),16);
        QString g = QString("").setNum(color.green(),16);
        QString b = QString("").setNum(color.blue(),16);
        if(r.size()<2)
            r.prepend("0");
        if(g.size()<2)
            g.prepend("0");
        if(b.size()<2)
            b.prepend("0");
        return str.arg(r).arg(g).arg(b);
    }

};

#endif // ADMINBACKEND_H

