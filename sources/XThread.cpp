/*==============================================================================
// File:    XThread.cpp
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   12.10.12
// Read license.txt for more informations.
//============================================================================*/
//
//=============================================================================

#include  "XThread.h"
#include  "Common.h"

//======
//int		XThread::XSelect(int nds, int cnt, time_ms timeout, fd_set * frd, fd_set * fwr, fd_set * fex)
//{
//	int  rcod;
//	timeval	tv;

//	if	(timeout > 999)	timeout = 999;
//	if	(!cnt)		{Sleep(timeout);	return 0;}

// 	tv.tv_sec  = 0;					// Период меньше секунды.
//	tv.tv_usec = timeout * 1000; 	// Установим таймаут.
//	rcod = select(nds, frd, fwr, fex, &tv);

//	if	(rcod >= 0)	return rcod;	// Нормальный выход по срабатыванию или таймауту.

//	if	(!errno ||(errno == EINTR)||(errno == EINVAL))	return 0;
//	PrintLog(0, QT_TRANSLATE_NOOP("","Thread <%s> select error: %d  %s"), ThreadName(), errno,  strerror(errno));

//	return	rcod;
//}

//====== Запуск процесса с ожиданием и контролем.
int 	XThread::SafeStartThread(unsigned short timeout)
{
//	time_ms  xtime = Xtime();	// Запомним время начала запуска процесса.
//    if	(isRunning())	return -1;	// Если уже запущен.
	
    start();					// Запустим процесс обработки ожиданий.
//    while	(!isRunning())			// Ждем, когда запустится.
//	{
////		Sleep(10);
//		if	(TDelta(Xtime(), xtime) > timeout)	// Если не запустился.
//		{
//			PrintLog(0, QT_TRANSLATE_NOOP("","Error: Unable started <%s> process."), ThreadName());
//			return -2;
//		}
//	}
	return 	0;	
}

//====== Остановка процесса с ожиданием и контролем.
int 	XThread::SafeStopThread(unsigned short timeout)
{
//	time_ms  xtime = Xtime();	// Запомним время начала запуска процесса.
//	while	(isRunning())			// Ждем, когда остановится.
//	{
        exit();
//		if	(TDelta(Xtime(), xtime) > timeout)	// Если не остановился.
//		{
//					// Остапновим насильно.
//			PrintLog(0, QT_TRANSLATE_NOOP("","Error: Unable stopped <%s> process. Stop it anyway"), ThreadName());
//			return -2;
//		}
//	}
	return 	0;	
}

//======
//void XThread::XThreadCallback(XThread * who)
//{
//#ifndef WIN32
//#ifndef ANDROID

//	// Далаем поток "убиваемым" через pthread_cancel.../common/XThread.cpp
//	int old_thread_type;
//	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_thread_type);
//#endif
//#endif

//	who->is_run = true;
//	PrintLog(0, QT_TRANSLATE_NOOP("","Thread <%s> started OK."), who->ThreadName());

//	who->Execute();

//	who->is_run = false;
// 	PrintLog(0, QT_TRANSLATE_NOOP("","Thread <%s> stopped OK"), who->ThreadName());
//}

//======
XThread::XThread(const QString &name)
{
	unsigned short i;
    if (!name.isEmpty())
        thread_name = "Unknown";
    else
        thread_name = name;
}

//======
XThread::~XThread() 
{
//	if	(is_run) Kill();
    exit();
//	CloseHandle(__handle);
}

//======
//void XThread::Start()
//{
//	__handle = CreateThread(
//    0, 0,
//    reinterpret_cast<LPTHREAD_START_ROUTINE>(XThreadCallback), this,
//    0, 0);
//}

//======
//void XThread::Join()
//{
//	WaitForSingleObject(__handle,  INFINITE);
//}

//======
//void XThread::Kill()
//{
//	TerminateThread(__handle, 0);
//}

//#else

////======
//XThread::~XThread() {}

//extern "C"
//typedef void *(*pthread_callback)(void *);

////======
//void XThread::Start()
//{
//	pthread_create(
//    &__handle, 0,
//    reinterpret_cast<pthread_callback>(XThreadCallback),
//    this);
//}

////======
//void XThread::Join()
//{
//	pthread_join(__handle, 0);
//}

//void XThread::Kill()
//{
//#ifndef ANDROID
//	pthread_cancel(__handle);
//#endif
//}

//#endif
//=============================================================================
