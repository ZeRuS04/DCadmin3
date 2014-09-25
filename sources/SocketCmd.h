/*==============================================================================
// File:    TCPsocketCmd.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   10.04.13
// Read license.txt for more informations.
//============================================================================*/
//		Сокетное подключение управления сервером.
//=============================================================================

#ifndef  TCP_SOCKET_CMD
#define  TCP_SOCKET_CMD

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QStack>
#include  "Common.h"
#include  "XThread.h"

//======
#define		LSTAT_DISCONNECT	(0)
#define		LSTAT_RESOLVED		(1)
#define		LSTAT_INIT			(2)
#define		LSTAT_CONNECT		(3)

class  ClientList;

//====== Объект сетевого соединения.
class  SocketCmd : public XThread
{
    Q_OBJECT

  public:
    SocketCmd(const QString &host, unsigned short port);
    ~SocketCmd(void);
	retErr	Disconnect(void);
    retErr	Connect();
	int		Status(void)	const	{return nStat;}
    const QString Host(void)	const	{return	host_name;}
    const unsigned short Port(void) const   {return port_;}


    retErr	SocketWriteData(const QByteArray &buf);
    QByteArray  SocketReadData();
    QByteArray  readData(){   return recData_.pop();  }

public slots:
    void connected();
    void disconnected(){    thread_done = false;    }
//    void bytesWritten(qint64 bytes);
    void readyRead(){
        recData_.push(SocketReadData());
    }

  private:
	void	PrintErrInfo(int errn);		// Вывод текстовых сообщений по номеру ошибки.

    void	run(void);                  // Процесс - обработчик событий объектов.

	unsigned long   recv_size;			// Число принимаемых байт данных.
	unsigned long   recv_cntr;			// Счётчик принятых байт.
	unsigned long   recv_buf_size;		// Размер буфера.
    QByteArray		recv_buf;			// Буфер приёма данных.
	unsigned long 	last_act;			// Время последней активности.
	struct sockaddr_in * addr;			//
	unsigned short	timer_period;		// Период таймера периодического вызова.

    QTcpSocket *socket;
    QStack<QByteArray> recData_;

	int 	bug_flg;		//
	int 	nStat;			//
	int		socket_fd;		// Файловый дескриптор соединения.
	bool	thread_done;	// Идентификатор запущенного процесса.
    QString  host_name;		// Имя хоста.
    unsigned short port_;   // Порт хоста.
};

#endif // TCP_SOCKET_CMD
//=============================================================================
