///*==============================================================================
//// File:    XThreadCommon.h
//// Author:  Shvetsov Sergey <pp_serg@mail.ru>
//// Version: 1.1 beta
//// Begin:   30.10.13
//// Read license.txt for more informations.
////============================================================================*/
//// 	  	Процесс обработки событий чтения данных.
////=============================================================================

//#ifndef 	XTHREAD_COMMON_H
//#define 	XTHREAD_COMMON_H

//#include  "Defines.h"
//#include  "Common.h"
//#include  "XThread.h"
//#include  "PlatformDef.h"

////=============================================================================
////====== Базовый класс объекта ретранслятора.
//class  XThreadItem
//{
//  protected:
//	XThreadItem(void);
//	virtual ~XThreadItem(void) 	{}
//	virtual  int  ReadFD(void) const=0;
	
//  public:
//	virtual bool  IsEqual(const XThreadItem * item)	const {return (item==this);}

//  private:
//  friend class  XThreadCommon;

//	virtual  int  XThreadRecv(unsigned char * buf, unsigned short size, time_ms ntime, sockaddr_in xaddr)=0;
//	virtual  int  XThreadPeriodic(time_ms ntime)=0;

//	SPIN_LOCK lock;			// Семафор.
//	bool  	  remove_flg;	// Пометка для удаления объекта.
//	time_ms	  update_time;	// Время последнего периодического вызова.
//};

////=============================================================================
////====== Список объектов ретрансляторов.
//class  XThreadCommon : public XThread
//{
//  public:
//	unsigned short 	PackSize(void)  const	{return udp_buf_size;}	// Размер приёмного буфера.
//	unsigned short	EallSize(void)  const 	{return eall_size;}		// Действительное число клиентов.
  
//  protected:
//	XThreadCommon(const char * name, unsigned short usize, unsigned short isize, unsigned short idelta, unsigned short utime);
//	virtual ~XThreadCommon(void);
	
//	retErr 	AddItemToList(XThreadItem * item);
//	retErr 	DeleteItem(XThreadItem * item, int ret_cod=-1);
//	retErr 	DeleteItem(unsigned short index, int ret_cod=-1);
//	void 	SetBufSize(unsigned short udp_size);			// Изменить размер буфера приёма.
//	void	EallClear(void);								// Очистим список сканирования.
//	XThreadItem * EallItem(unsigned short index) const;		// Получение указателя на клиента по его индексу.

//  private:
//	virtual retErr 	XThreadRemoveItem(XThreadItem * item, int ret_cod)	{return NO_ERR;}
//	virtual retErr 	XThreadAddItem(XThreadItem *)						{return NO_ERR;}
	
//	void 	FreeBuffer(void);					//
//	void 	ListReSize(unsigned short size); 	// Увеличение размера списка объектов.
//	void	PrivateClearList(void);				// Удаление из списка всех помеченных для удаления.
//	void	Execute(void);						// Процесс - обработчик событий объектов.
	
//	//======
//	unsigned short 	uprt_time;		// Период обновления объектов.
//	unsigned short 	udp_buf_size;	// Размер приёмного буфера.
//	unsigned char * udp_buf;		// Приёмный буфер.
//	SPIN_LOCK		lock;			// Семафор.
//	bool			thread_done;	// Идентификатор запущенного процесса.
//	unsigned short	eall_size;		// Число указателей на клиентов в буфере.
//	unsigned short	eall_max_size;	// Размер буфера указателей на объекты.
//	unsigned short	eall_delta;		// Приращение размера списка.
//	XThreadItem  ** eall;			// Список указателей на объекты обрабатываемых этим процессом.
//};

//#endif // XTHREAD_COMMON_H
////=============================================================================
