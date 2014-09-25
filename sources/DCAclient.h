/*==============================================================================
// File:    DCAclient.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   30.05.2013
// Read license.txt for more informations.
//============================================================================*/

#ifndef  SOCKET_CMD_H
#define  SOCKET_CMD_H

#include  <QtCore/QObject>
#include  "TCPsocketCmd.h"
#include  "DCApack.h"

class  DCAclientSess;
class  DCAclientRoot;
class  TreeItem;
class  ItemPageInfo;
class  VarInfo;

//======
class DCAclient : public QObject, public TCPsocketCmd
{
	Q_OBJECT
  public:
	DCAclient(QObject * parent, DCAclientRoot  * root);
	~DCAclient(void);
	
  public slots:	
	void 	SendEvent(unsigned short iframe, unsigned short event, unsigned short row, unsigned short col);
	void 	SendEvent(unsigned short iframe, const char * data, unsigned short lenght);
	void	SendData(IIDX iframe, IIDX index, dval_type type, const char * data, unsigned short lenght);
	void	ChangesApply(const VarInfo * var, unsigned short row, const char * data, unsigned short lenght);

  signals:
//	void	EvUpdateTree(void);					// 	
	void	EvConnected(void);					//
	void	EvDisconnected(void);				//
	void	EvReconnect(void);					//
	void	EvSetSyslog(const QString &);		//
	void	UpdateValues(IIDX iframe, IIDX index, enum dval_type dtype, char * data, unsigned short dlen);
	void	GetNextUpdate(IIDX * iframe, IIDX * index, enum dval_type * dtype, time_ms ntime);

  protected:
	retErr	EventDisableReconnect(void);		
	retErr	EventIncomingPack(dsa_header * hd);	// Событие получение нового пакета.	
	retErr	EventConnected(void);				// Событие подключения к серверу.
	retErr	EventReconnect(void);				//
	retErr	EventDisconnected(void);			// Событие отключения от сервера.
	retErr	EventTimer(void);					//
	bool	event(QEvent * e);					// События после очереди событий.	

  private:
  friend DCAclientSess;
	bool  PeriodicUpdate(time_ms ntime);		// Пеиодическое обновления состояния переменных.

	DCAclientRoot * root;
	DCAclientSess * sess;
};

#endif   // SOCKET_CMD_H
//==============================================================================


