/*==============================================================================
// File:    SocketCmd.cpp
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   10.04.13
// Read license.txt for more informations.
//============================================================================*/
//		Сокетное подключение управления сервером.
//=============================================================================

#include  "SocketCmd.h"
//====== Ошибки сетевых подключений.
#define	 ERXN_NO_ERR			(0)		//
#define	 ERXN_DISCONNECT_REMOTE	(1)		// Отключение клиента.
#define	 ERXN_DISABLE_RECONNECT	(2)		//
#define	 ERXN_HEADER_KEY		(3)		//
#define	 ERXN_HEADER_SIZE		(4)		//
#define	 ERXN_HEADER			(5)		//
#define	 ERXN_SEND_ERROR		(6)		//
#define	 ERXN_RECV_ERROR		(7)		//
#define	 ERXN_TIMEOUT			(8)		//
#define	 ERXN_WAIT_CONNECT		(9)		//
#define	 ERXN_DISCONNECT		(10)	//
#define	 ERXN_CREATE_ERR		(11)	//
#define	 ERXN_OPT_ERR			(12)	//
#define	 ERXN_INTERNAL1			(13)	//
#define	 ERXN_INTERNAL2			(14)	//
#define	 ERXN_INTERNAL3			(15)	//
#define	 ERXN_INTERNAL4			(16)	//
//#define	 ERXN_INTERNAL5		(17)	//

//======
#define	 NTIME_RECONNECT		(2000)	// Период попыток пересоединений.

//======
SocketCmd::SocketCmd(const QString &host, unsigned short port) : XThread("SocketCmd"), recv_buf_size(TCP_CMD_LEN_MAX),
                                    recv_buf(0L), last_act(0), timer_period(60),
                                    nStat(LSTAT_DISCONNECT), socket_fd(-1), host_name(host), port_(port)
{
	thread_done = true;
	SafeStartThread();		// Запуск процесса с ожиданием и контролем.
}

//======
SocketCmd::~SocketCmd(void)
{
	Disconnect();

	thread_done = false;
	SafeStopThread();		// Остановка процесса с ожиданием и контролем.

//	addr = 0L;
	delete	host_name;
	host_name = 0L;
}

//======
retErr	SocketCmd::Disconnect(void)
{
  	delete 	addr;
    addr = 0L;
	delete	host_name;
	host_name = 0L;
    socket->close();
	return	NO_ERR;
}


//======
void  SocketCmd::PrintErrInfo(int errn)
{
	if		(!errn)		return;
	if		(errn == ERXN_WAIT_CONNECT)	return;

	if		(errn == ERXN_DISCONNECT)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket disconnect"));
	else if	(errn == ERXN_DISCONNECT_REMOTE)	PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket disconnect remote"));
	else if	(errn == ERXN_DISABLE_RECONNECT)	PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket remote disable reconnect"));
	else if	(errn == ERXN_TIMEOUT)				PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket timeout wait header"));
	else if	(errn == ERXN_SEND_ERROR)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket send error: %d  (%s)"), errno,  strerror(errno));
	else if	(errn == ERXN_OPT_ERR)				PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket error setsockopt: (%s)"), strerror(errno));
	else if	(errn == ERXN_CREATE_ERR)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket create error : (%s)"), errno,  strerror(errno));
	else if	(errn == ERXN_RECV_ERROR)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket recv error: %d  (%s)"), errno,  strerror(errno));
	else if	(errn == ERXN_HEADER_KEY)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket receive invalid header key"));
	else if	(errn == ERXN_HEADER_SIZE)			PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket receive invalid header size"));
	else if	(errn == ERXN_HEADER)				PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket receive invalid header"));
//	else if	(errn == ERXN_WAIT_CONNECT)			PrintLog(0, QT_TRANSLATE_NOOP("","Socket wait connect"));
    else										PrintLog(0, QT_TRANSLATE_NOOP("","TCP socket disconnect internal error %d"), errn);
}

//======
retErr	SocketCmd::Connect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
//    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    //	Clear(ERXN_NO_ERR);

    socket->connectToHost(host_name, port_);
    if(!socket->waitForConnected(5000))
    {
            return ERR_SOCKET_OPEN;
    }

    nStat     = LSTAT_RESOLVED;
	return	NO_ERR;
}



//======
retErr	 SocketCmd::SocketWriteData(const QByteArray &buf)
{

    if(socket->write(buf) == -1)
        return -1;

	return	NO_ERR;
}

//======
QByteArray  SocketCmd::SocketReadData()
{
    return socket->readAll();

}



//=============================================================================
//=============================================================================
//======  Процесс - обработчик событий объектов.
void  SocketCmd::run(void)
{
//	fd_set	fds;
//	int		rcod, fd, cnt, nds;
//	time_ms ntime, ctime;
//	time_ms	last_event = Xtime();	// Время последнего вызова события таймаута.

    Connect();
	//====== Цикл обработки событий от сокетов.
	while	(thread_done)
    {

	}
}

//=============================================================================
