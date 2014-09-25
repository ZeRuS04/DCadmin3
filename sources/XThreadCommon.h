///*==============================================================================
//// File:    XThreadCommon.h
//// Author:  Shvetsov Sergey <pp_serg@mail.ru>
//// Version: 1.1 beta
//// Begin:   30.10.13
//// Read license.txt for more informations.
////============================================================================*/
//// 	  	������� ��������� ������� ������ ������.
////=============================================================================

//#ifndef 	XTHREAD_COMMON_H
//#define 	XTHREAD_COMMON_H

//#include  "Defines.h"
//#include  "Common.h"
//#include  "XThread.h"
//#include  "PlatformDef.h"

////=============================================================================
////====== ������� ����� ������� �������������.
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

//	SPIN_LOCK lock;			// �������.
//	bool  	  remove_flg;	// ������� ��� �������� �������.
//	time_ms	  update_time;	// ����� ���������� �������������� ������.
//};

////=============================================================================
////====== ������ �������� ��������������.
//class  XThreadCommon : public XThread
//{
//  public:
//	unsigned short 	PackSize(void)  const	{return udp_buf_size;}	// ������ �������� ������.
//	unsigned short	EallSize(void)  const 	{return eall_size;}		// �������������� ����� ��������.
  
//  protected:
//	XThreadCommon(const char * name, unsigned short usize, unsigned short isize, unsigned short idelta, unsigned short utime);
//	virtual ~XThreadCommon(void);
	
//	retErr 	AddItemToList(XThreadItem * item);
//	retErr 	DeleteItem(XThreadItem * item, int ret_cod=-1);
//	retErr 	DeleteItem(unsigned short index, int ret_cod=-1);
//	void 	SetBufSize(unsigned short udp_size);			// �������� ������ ������ �����.
//	void	EallClear(void);								// ������� ������ ������������.
//	XThreadItem * EallItem(unsigned short index) const;		// ��������� ��������� �� ������� �� ��� �������.

//  private:
//	virtual retErr 	XThreadRemoveItem(XThreadItem * item, int ret_cod)	{return NO_ERR;}
//	virtual retErr 	XThreadAddItem(XThreadItem *)						{return NO_ERR;}
	
//	void 	FreeBuffer(void);					//
//	void 	ListReSize(unsigned short size); 	// ���������� ������� ������ ��������.
//	void	PrivateClearList(void);				// �������� �� ������ ���� ���������� ��� ��������.
//	void	Execute(void);						// ������� - ���������� ������� ��������.
	
//	//======
//	unsigned short 	uprt_time;		// ������ ���������� ��������.
//	unsigned short 	udp_buf_size;	// ������ �������� ������.
//	unsigned char * udp_buf;		// ������� �����.
//	SPIN_LOCK		lock;			// �������.
//	bool			thread_done;	// ������������� ����������� ��������.
//	unsigned short	eall_size;		// ����� ���������� �� �������� � ������.
//	unsigned short	eall_max_size;	// ������ ������ ���������� �� �������.
//	unsigned short	eall_delta;		// ���������� ������� ������.
//	XThreadItem  ** eall;			// ������ ���������� �� ������� �������������� ���� ���������.
//};

//#endif // XTHREAD_COMMON_H
////=============================================================================
