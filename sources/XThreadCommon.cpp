///*==============================================================================
//// File:    XThreadCommon.cpp
//// Author:  Shvetsov Sergey <pp_serg@mail.ru>
//// Version: 1.1 beta
//// Begin:   30.10.13
//// Read license.txt for more informations.
////============================================================================*/
//// 	  	������� ��������� ������� ������ ������.
////=============================================================================

//#include  "PlatformDef.h"
//#include  "XThreadCommon.h"

//#define  XTHREAD_MAX_INDEX		(1024) 	// ����������� ���������� ����� �������� � ������.
//#define  XTHREAD_URT_TIMEOUT	(500)	// ����� �������� �������/��������� ��������.

////======
//XThreadItem::XThreadItem(void) : remove_flg(false), update_time(Xtime())
//{
//	spin_unlock(&lock);  	// �� ������ ������ ������� ������ ����������.
//}

////=============================================================================
////=============================================================================
////======
//XThreadCommon::XThreadCommon(const char * name, unsigned short usize,
//								unsigned short isize, unsigned short idelta, unsigned short utime) :
//								XThread(name), uprt_time(utime), udp_buf(0L), eall(0L)
//{
//	spin_lock_init(&lock);	// �� ������ ������ ������� ������ ����������.
//	FreeBuffer();			// ������� ����������.
	
//	eall_delta = idelta;
//	ListReSize(isize);		// �������������� ������ ��������.
//	SetBufSize(usize);		// �������������� ����� ����� ������.

//	thread_done = true;		// ��������� ������� ���������� ������ ��������.
//	SafeStartThread();		// �������� ������� ���������.
//}

////======
//XThreadCommon::~XThreadCommon(void)
//{
//	thread_done = false;	// ��������� ������� ��������� ������ ��������.
//	spin_unlock(&lock);		// �� ������ ������ ������� ������ ����������.
//	SafeStopThread();		// ��������� ������� ���������.

//	PrivateClearList();		// ������ ��� �������.
//	FreeBuffer();			// ��������� ������.
//	spin_lock_destroy(&lock);
//}

////======
//void 	XThreadCommon::FreeBuffer(void)
//{
//	spin_lock(&lock);
	
//	delete 	udp_buf;		// ������ ����� ����� ������.
//	udp_buf_size = 0;		// ������ �������� ������.
//	udp_buf      = 0L;		// ������� �����.
	
//	delete 	eall;			// ������ ������.
//	eall 		 = 0L;		//
//	eall_size    = 0;		// ����� ���������� �� �������� � ������.
//	eall_max_size= 0;		// ������ ������ ���������� �� ��������.
//	eall_delta   = 0;		// ���������� ������� ������.
	
//	spin_unlock(&lock);
//}

////====== �������� ������ ������ �����.
//void 	XThreadCommon::SetBufSize(unsigned short new_udp_size)
//{
//	spin_lock(&lock);
	
//	delete udp_buf;
//	udp_buf = 0L;
//	udp_buf_size = new_udp_size;
//	if 	(udp_buf_size)	udp_buf = new unsigned char [udp_buf_size];
	
//	spin_unlock(&lock);
//}

////====== ���������� ������� ������ ��������.
//void 	XThreadCommon::ListReSize(unsigned short new_size)
//{
//	if 	(new_size > XTHREAD_MAX_INDEX) 	new_size = XTHREAD_MAX_INDEX;
//	if 	(new_size <= eall_max_size)		return;	// ������ ������ ����� ������ ��������������.
 	
//	unsigned short i;
//	XThreadItem ** new_eall = new XThreadItem * [new_size];
		
//	spin_lock(&lock);
	
//	eall_max_size = new_size;
//	for	(i=0; i < eall_max_size; ++i)			// �������� ������������ � ������� �� ������������ ���������.
//	{
//		if 	(i < eall_size)	new_eall[i] = eall[i];
//		else 				new_eall[i] = 0L;
//	}
		
//	delete 	eall;
//	eall = new_eall;
	
//	spin_unlock(&lock);
//}

////======
//retErr XThreadCommon::AddItemToList(XThreadItem * item)
//{
//	unsigned short i;

//	//====== �������� �����,  ���� ��� ��� ���.
//	if 	(!eall)									// ���� ������ �����������.
//	{
//		if 	(!eall_delta)						// � ��� �������� ����������.
//				return ERR_TOO_MANY_ITEMS;
//		ListReSize(eall_delta);					// �������� ������ ������ �� �������� ��������.
//	}
//	//====== ��������, ��� �� ������ �� ������� � ������.
//	else
//	{
//		for (i=0; i < eall_size; ++i)
//			if (eall[i] && !(eall[i]->remove_flg) && eall[i]->IsEqual(item))
//				return ERR_ITEM_ALREADY_EXIST;
//	}
	
//	//====== ����� ���������� ����� � ������ ��������.
//	if (eall_size >= eall_max_size)				// ���� ������ ��� �������� �� �����.
//	{
//		if 	(!eall_delta ||						// ���� ��������� ������� ������ ���������.
//		    (i >= XTHREAD_MAX_INDEX))			// ��� ������ ������ ����������� ����������� �������.
//				return ERR_TOO_MANY_ITEMS;
//		ListReSize(eall_max_size+eall_delta);	// �������� ������ ������ �� �������� ��������.
//	}
	
//	spin_lock(&lock);
//	eall[eall_size++] = item;
//	spin_unlock(&lock);
	
//	XThreadAddItem(item);
//	return	NO_ERR;
//}

////======
//XThreadItem  *	XThreadCommon::EallItem(unsigned short index) const
//{
//  // !!! ����� ����� ���� �������� ���������� ������� �  ������ thread
  
//	if (!eall || (index >= eall_size))				return 0L;
//	if (!eall[index] || (eall[index]->remove_flg))	return 0L;
		
//	return eall[index];
//}

////====== ������� ������� ��� ���������� � ��������� ����� ���������.
//retErr XThreadCommon::DeleteItem(unsigned short index, int ret_cod)
//{
//  // !!! ����� ����� ���� �������� ���������� ������� �  ������ thread
  
//	retErr rcod = ERR_ITEM_NOT_EXIST;
//	XThreadItem * item;
	
//	item = EallItem(index);
//	if 	(item)
//	{
//		rcod = XThreadRemoveItem(eall[index], ret_cod);
		
//		spin_lock(&lock);
//		item = EallItem(index);
//		if 	(item)	eall[index]->remove_flg = true;
//		spin_unlock(&lock);
//	}

//	return rcod;
//}

////====== ������� ������� ��� ���������� � ��������� ����� ���������.
//retErr XThreadCommon::DeleteItem(XThreadItem * item, int ret_cod)
//{
//	retErr rcod=NO_ERR;
//	unsigned int i, cnt=0;
	
//	if 	(!item)		return ERR_ZERO_POINTER;		// ������ ��������� �� ������ ��� ��������.
//	if 	(!eall)		return ERR_ITEM_NOT_EXIST;		// ���� ��� ������, �� � ����� ������� � �� ���.
	
//	//====== ���� ��� ������� ������� ��������� �������.
//	for (i=0; i < eall_size; ++i)
//			if (eall[i] && !(eall[i]->remove_flg) && eall[i]->IsEqual(item))
//	{
//		rcod = XThreadRemoveItem(eall[i], ret_cod);
//		eall[i]->remove_flg = true;
//		cnt++;
//	}

//	if 	(!cnt)	 return  ERR_ITEM_NOT_EXIST;
//	return rcod;
//}

////======= ������� ���� ������.
//void  XThreadCommon::EallClear(void)
//{
//	unsigned int i;
//	if 	(!eall)		return ;
	
//	//====== ���� ��� ������� ������� ��������� �������.
//  	spin_lock(&lock);
//	for (i=0; i < eall_size; ++i) if (eall[i])
//	{
////		EventRemoveItem(eall[i], -1);
//		delete  eall[i];
//		eall[i] = 0L;
//	}
//	eall_size = 0;
//  	spin_unlock(&lock);
//}

////====== �������� �� ������ ���� �������� ���������� ��� ��������.
//void  XThreadCommon::PrivateClearList(void)
//{
//	unsigned int i, k;
//	if (!eall)	return;

//  	spin_lock(&lock);
//	for (k=i=0; i < eall_size; ++i)
//	{
//		if (!eall[i] || eall[i]->remove_flg)	delete  eall[i];
//		else 									eall[k++] = eall[i];
//	}
	
//	for (; k < eall_size; ++k)	 {eall[k] = 0L;	--eall_size;}
//  	spin_unlock(&lock);
//}

////=============================================================================
////=============================================================================
////======  ������� - ���������� ������� ��������.
//void  XThreadCommon::Execute(void)
//{
//	int		rcod, fd, i, cnt, nds, lenght;
//	fd_set	readfds;
//	sockaddr_in xaddr;
//	socklen_t   slen;
//	time_ms ntime;

//	//====== ���� ��������� ������� �� �������.
//	while	(thread_done)
//	{
//		nds = 1;
//		cnt = 0;
//		FD_ZERO(&readfds);
			
//		//====== �������� ������ ������������.
//		if 	(eall)
//		{
//			spin_lock(&lock);
//			for	(i=0; i < eall_size; ++i)
//			{
//				if 	(eall[i] && !(eall[i]->remove_flg))
//						fd = eall[i]->ReadFD();
//				else 	fd = -1;
			
//				if 	(fd >= 0)
//				{
//					FD_SET(fd, &readfds);
//					if	(nds < (fd+1)) nds=fd+1;
//					cnt++;
//				}
//			}
//			spin_unlock(&lock);
//		}

//		rcod = XSelect(nds, cnt, 60, &readfds);

////		if	(!cnt)	{Sleep(xtime);	rcod = 0;}
////		else
////		{
// //			tv.tv_sec  = 0; 		//xtime / 1000;							// ��������� �������.
////			tv.tv_usec = xtime * 1000; 		//parent->uprt_time
////			rcod = select(nds, &readfds, 0L, 0L, &tv);
////		}
		
//		ntime = Xtime();
//		if	(rcod >= 0)
//		{
////			spin_lock(&(parent->lock));
//			if	(eall)	for	(i=0; i < eall_size; ++i)
//			{
//				if	(!(eall[i]) || eall[i]->remove_flg)	continue;
			
//				rcod = 0;
//				fd = eall[i]->ReadFD();
								
//				if	((fd > 0) && (FD_ISSET(fd, &readfds)))
//				{
//					slen   = sizeof(sockaddr_in);
//					lenght = recvfrom(fd, (char *)(udp_buf), udp_buf_size, RECV_FLAGS, (sockaddr *)&xaddr, &slen);
						
//					if 	(lenght < 0)	rcod = -1;		  // ����� �� ������...
//					else				rcod = eall[i]->XThreadRecv(udp_buf, lenght, ntime, xaddr);
//				}
				
//				if	(!(eall[i]->remove_flg) && (TDelta(ntime, eall[i]->update_time) > uprt_time))
//				{
//					eall[i]->update_time = ntime;
//					eall[i]->XThreadPeriodic(ntime);
//				}
//			}
////			spin_unlock(&lock);

//			PrivateClearList();		// ������ ��� ������� ������� ���������� ��� ��������.
//		}
//	}
//}

////=============================================================================
