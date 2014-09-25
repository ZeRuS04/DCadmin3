/*==============================================================================
// File:    XThread.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   12.10.12
// Read license.txt for more informations.
//============================================================================*/
//
//=============================================================================

#ifndef X_THREAD_H
#define X_THREAD_H

#include <QObject>
#include <QThread>

//======
class XThread: public QThread
{
  public:
    XThread(const QString &name);
	virtual ~XThread(void);
            // ��������� ������ ����������� ��������.
	int 	SafeStartThread(unsigned short timeout=200);	// ������ �������� � ��������� � ���������.
	int		SafeStopThread(unsigned short timeout=200);		// ��������� �������� � ��������� � ���������.
    const QString ThreadName(void)	{return thread_name;}	// ��������� ����� ��������.
//	int	  	XSelect(int nds, int cnt, time_ms timeout, fd_set * frd, fd_set * fwr=0L, fd_set * fex=0L);
	
  private:
	// ������� ������� ������, ����������� ������ ������. ����� �����������, ����� ��� ������� 
	// ����������� ������. ������ ������������� ������ ��� ���������� � ������ ������� ����� try-catch(...). 
	// ������������� ���������� ����� ���������� �������� � ����������� ������� ��������� ���
	// ����������� ��������� �������.
    virtual void run() = 0;
	
	// ������������� � ������. ������ ������� ������ ���������� ������ ����� ����� �������� ������. 
	// ����������� ��� ������������� �������, ���� ���� ��������� ���������� ������.
	void 	Join();
	
	// ����������� ������. ������������� ���������� ����� �����. ������ ������ ���������� ������ �������� 
	// ������ ���������������. ���������� ��������� ����� ���������, ������������ � ������� Execute() 
	// ������� ��� ������, ��� ����� ��������� ������ ���������� ����������.
	void 	Kill();
	
	// ������� ������� ������. �� ������ ���������� � ������������� ������, ��� ��� ����� ���������, 
	// ��� ����� ���������� �� ����, ��� ������ ����� ��������� �����������. � ��� ����� �������� 
	// ���������, ���� ������� pthread_create ��� CreateThread � /������������. 
	// � ����� ����������� ������� � ������������, �� ��� � � ������������ ������������������� �������, 
	// � ������ ������ �������� � ��������� ������ ������ ����� ����������� �������, ���� � ������ 
	// ������ ������� ��������� � ���������� ������ ������. ������ �� ������ ����� ������
	// ������������ ��������� �� ���� �������. 
	void 	Start();	


    QString	thread_name;	// ��� ������ ��� ������ ��������������� ���������.

	// ������ �� ���������� ����������� ������� � C++
	XThread(const XThread &);
	void operator=(const XThread &);
};

#endif // X_THREAD_H
//=============================================================================