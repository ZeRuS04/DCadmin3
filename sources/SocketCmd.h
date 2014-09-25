/*==============================================================================
// File:    TCPsocketCmd.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   10.04.13
// Read license.txt for more informations.
//============================================================================*/
//		�������� ����������� ���������� ��������.
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

//====== ������ �������� ����������.
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
	void	PrintErrInfo(int errn);		// ����� ��������� ��������� �� ������ ������.

    void	run(void);                  // ������� - ���������� ������� ��������.

	unsigned long   recv_size;			// ����� ����������� ���� ������.
	unsigned long   recv_cntr;			// ������� �������� ����.
	unsigned long   recv_buf_size;		// ������ ������.
    QByteArray		recv_buf;			// ����� ����� ������.
	unsigned long 	last_act;			// ����� ��������� ����������.
	struct sockaddr_in * addr;			//
	unsigned short	timer_period;		// ������ ������� �������������� ������.

    QTcpSocket *socket;
    QStack<QByteArray> recData_;

	int 	bug_flg;		//
	int 	nStat;			//
	int		socket_fd;		// �������� ���������� ����������.
	bool	thread_done;	// ������������� ����������� ��������.
    QString  host_name;		// ��� �����.
    unsigned short port_;   // ���� �����.
};

#endif // TCP_SOCKET_CMD
//=============================================================================
