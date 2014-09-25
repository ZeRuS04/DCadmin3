/*==============================================================================
// File:    DCAclient.cpp
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   30.05.2013
// Read license.txt for more informations.
//============================================================================*/

#define   _CRT_SECURE_NO_WARNINGS
#include  <QtWidgets/QApplication>
#include  <QtCore/qabstractitemmodel.h>
#include  "Common.h"
#include  "DCAclient.h"
#include  "DCAclientRoot.h"
#include  "TreeItem.h"
#include  "FrameInfo.h"
#include  "DCApack.h"

//======
#define   UPD_ACK_TIMEOUT 	(2000)	//2c Таймаут не ответа сервера на запрос.
#define   UPD_ITEM_TIME 	(1000)	//1c Период обновления данных.
//#define   UPD_ITEM_NODES 	(400)	// Период обновления данных.

//======
#define   UPD_ERROR			(0)		// Инициализация прошла с ошибкой.
#define   UPD_NOT_INIT		(1)		// Не инициализированно.
#define   UPD_NOT_INIT2		(2)		//
#define   UPD_WAIT_PAGES	(3)		// Ожидаем получения информации о всех страницах.
#define   UPD_REQ_FRAMES	(4)		// Посылаем запрос на получение информации о фреймах текущей страницы.
#define   UPD_WAIT_FRAMES	(5)		// Ожидание получения данных о фреймах текущей страницы.
#define   UPD_CHECK_VARS	(6)		// Ожидание получения данных о переменных текущего фрейма текущей страницы.
#define   UPD_IS_OK			(7)		// Инициализация прошла успешно.

//======
#define	  EVENT_INCOMING_PACK	(QEvent::Type)(QEvent::User + 2)
#define	  EVENT_CONNECTED		(QEvent::Type)(QEvent::User + 3)
#define	  EVENT_RECONNECT		(QEvent::Type)(QEvent::User + 4)
#define	  EVENT_DISCONNECTED	(QEvent::Type)(QEvent::User + 5)
#define	  EVENT_MY_TIMER		(QEvent::Type)(QEvent::User + 6)

//==============================================================================
//======
class  DCAclientSess
{
  public:
	DCAclientSess(DCAclient * _parent, unsigned long ntime) : 
							stat(UPD_NOT_INIT), ctime(ntime), 
							total_page(0), parent(_parent), pages(0L) 
							{spin_lock_init(&lock);}

	//====== 
	~DCAclientSess(void)	
	{
		spin_lock(&lock);
		delete  pages;
		pages = 0L;
		spin_lock_destroy(&lock);	
	}

	//====== Быстрая инициализация интерфейса после подключения.
	void 	InterfaceInit(time_ms ntime)
	{ 	  
		spin_lock(&lock);
		switch 	(stat)
		{
		  default:
			SetError("Internal <stat> error.", true);
			break;
			
		  case UPD_ERROR:				//====== Инициализация прошла с ошибкой.
			if (TDelta(ntime, ctime) > UPD_ACK_TIMEOUT)
			{
				stat= UPD_NOT_INIT;		// Повторим инициализацию с начала.
				ctime = ntime;
			}	
			break;
			
		  case UPD_NOT_INIT:			//====== Не инициализированно.
			{						
				dsa_header pk;

				pk.cmd = DCA_SERVER_INFO_REQ;
				pk.key = DCA_HEADER_ADMIN_KEY;
				pk.len = sizeof(dsa_header);

				ctime = ntime;
				stat = UPD_NOT_INIT2;	// Посылаем запрос на получение информации о сервере.
				parent->SocketWriteData((char *)&pk, sizeof(dsa_header));
			}
			break;
			
		  case UPD_NOT_INIT2:			//====== 
			{						
				dsa_header pk;

				pk.cmd = DCA_PAGE_INFO_REQ;
				pk.key = DCA_HEADER_ADMIN_KEY;
				pk.len = sizeof(dsa_header);

				ctime = ntime;
				stat  = UPD_WAIT_PAGES;	// Посылаем запрос на получение информации о страницах.
				parent->SocketWriteData((char *)&pk, sizeof(dsa_header));
			}			
			break;

		  case UPD_WAIT_PAGES:			//====== Ожидаем получения информации о всех страницах.
			if		(TDelta(ntime, ctime) > UPD_ACK_TIMEOUT)	SetError("Timeout wait pages.", false);
			else if	(pages)										// Если получено число страниц.
			{
				IIDX  i;
				for (i=0; (i < total_page) && pages[i]; ++i);	// Ищем ещё не инициализированные страницы.
				if	(i == total_page)							// Если все страницы инициализированны.
				{
				  	upd_page = 0;								// Начнём получение данных о фреймах с нулевой страницы.
					stat = UPD_REQ_FRAMES;
					PrintLog(8, QT_TRANSLATE_NOOP("","Init %u pages is OK"), total_page);
				}
			}
			break;
			
		  case UPD_REQ_FRAMES:			//====== Посылаем запрос на получение информации о фреймах страницы.
			if 		(!pages || !total_page)		SetError("No pages while request frames.", true);
			else if (upd_page >= total_page)	// Если все фреймы на всех страницах инициализированны.
			{
//				PrintLog(7, QT_TRANSLATE_NOOP("","Init all frames is OK"));
				upd_page = 0;
				stat = UPD_CHECK_VARS;
			}
			else
			{
				dsa_frame_info_req pk;
//				PrintLog(7, QT_TRANSLATE_NOOP("","Get frames for page %u/%u"), upd_page, total_page);
				
				pk.hdr.cmd = DCA_FRAME_INFO_REQ;
				pk.hdr.key = DCA_HEADER_ADMIN_KEY;
				pk.hdr.len = sizeof(dsa_frame_info_req);
				pk.npage   = upd_page;

				ctime = ntime;
				stat = UPD_WAIT_FRAMES;	
				parent->SocketWriteData((char *)&pk, sizeof(dsa_frame_info_req));
			}
			break;
			
		  case UPD_WAIT_FRAMES:				//====== Ожидание получения данных о фреймах текущей страницы.
			if 		(!pages || !total_page)				SetError("No pages while wait frames.", true);		
			else if (upd_page >= total_page)			SetError("Change total pages.", true);		
			else if ((ntime - ctime) > UPD_ACK_TIMEOUT)	SetError("Timeout wait frames.", false);
			else if (IsAllFrameInit(upd_page))				// Если фреймы на текущей странице инициализированны.
			{
				IIDX	i, n;
				const FrameInfo * frame;
				ItemPageInfo * pinfo = pages[upd_page]->GetPageInfo();

				dsa_item_info_req pk;
				pk.hdr.cmd = DCA_ITEM_INFO_REQ;
				pk.hdr.key = DCA_HEADER_ADMIN_KEY;
				pk.hdr.len = sizeof(dsa_item_info_req);

//				PrintLog(0, QT_TRANSLATE_NOOP("","Get items for page %u/%u frames %u"), upd_page, total_page, pages[upd_page]->TotalFrames());	
				
				upd_page++;									// Перейдём к следующей странице.
				stat = UPD_REQ_FRAMES;					
	
				for (i=0; i < pinfo->TotalFrames(); ++i)	// Посылаем запросы на получение информации о объектах данных всех фреймов данной страницы.
				{
					frame = pinfo->GetFrameInfo(i);
					if	(frame)	for (n=0; n < frame->NVars(); ++n)
					{				  
						pk.iframe = frame->IFrame();		// Индекс фрейма содержащего этот объект данных.
						pk.index  = n;						// Индекс переменной в фрейме.
						parent->SocketWriteData((char *)&pk, sizeof(dsa_item_info_req));
//						PrintLog(0, QT_TRANSLATE_NOOP("","Get items %u %u"), pk.iframe, );	
					}
				}
			}
			break;
			
		  case UPD_CHECK_VARS:		//====== Ожидание получения значения переменных всех фреймов текущей страницы.
			if 		(!pages || !total_page)		SetError("No pages while check items.", true);	
			else if	(upd_page >= total_page)
			{
				IIDX  k, i;	
				IIDX  total_frame= 0;
				IIDX  total_var  = 0;
				IIDX  total_table= 0;
				ItemPageInfo * pinfo;
				const FrameInfo * frame;

				for (k=0; k < total_page; ++k)
				{
					pinfo = pages[k]->GetPageInfo();
					for (i=0; i < pinfo->TotalFrames(); ++i)
					{
						frame = pages[k]->GetFrameInfo(i);
						if	(!frame)	continue;
						if	(frame->IsTable())	total_table++;
						else					total_frame++;
						total_var += frame->NVars();
					}
				}

				upd_page = 0;
				stat  = UPD_IS_OK;				
				PrintLog(1, QT_TRANSLATE_NOOP("","Interface init OK. pages %u frames %u tables %u variables %u"), 
																total_page, total_frame, total_table, total_var);	
			}
			else	upd_page++;
			break;
		}
		spin_unlock(&lock);
	}

	//====== 	
	
	bool	IsInitOK(void)	{return	 (stat == UPD_IS_OK);}
	
	//====== Получение информации о сервере.
	void 	EvServerInfo(dsa_server_info_ack * pk)
	{
		int	  slen = pk->hdr.len - sizeof(dsa_server_info_ack);
		if	(slen < 0)	slen = 0;
		
		char * server_name = new char [slen+1];
		strncpy(server_name,  (char *)pk + sizeof(dsa_server_info_ack), slen);
		server_name[slen] = 0;

		PrintLog(0, QT_TRANSLATE_NOOP("","RECV server info version %u.%u, name <%s>"), ((unsigned char *)&(pk->version))[0], ((unsigned char *)&(pk->version))[1], server_name);

		delete	server_name;

//		spin_lock(&lock);
		// ????????????????????????????????????????????
//		spin_unlock(&lock);	  
	}
 
	//====== Получение информации о страницах отображения.
	void 	EvPageInfo(dsa_page_info_ack * pk)
	{
//		PrintLog(9, QT_TRANSLATE_NOOP("","RECV info page=%u (%u)"), pk->npage, pk->total);
	  	if 	(stat == UPD_WAIT_PAGES)						// Если ответ по переданному ранее запросу.
		{
			int	  slen = pk->hdr.len - sizeof(dsa_page_info_ack);
			total_page = pk->total;
			
			spin_lock(&lock);			
			if 		(!total_page)	SetError("No pages while get pages info.", true);	
			else if ((pk->npage < total_page) && slen)
			{
				retErr	rcod;
				unsigned short i;
				const char * page_name = (char *)pk + sizeof(dsa_page_info_ack);
				((char *)pk + sizeof(dsa_page_info_ack))[slen-1] = 0;
				
				if 	(!pages)
				{
					pages = new TreeItem * [total_page];	// Если списка страниц ещё не существует, cоздадим новый список страниц.
					for	(i=0; i < total_page; ++i)	pages[i]=0L;
				}

				if	(!pages[pk->npage])						// Если у страница ещё не инициализированна.
				{
					pages[pk->npage] = 	new TreeItem("*Page*", pk->npage, pk->flags);
					if	(!page_name || !page_name[0])	page_name = "*NoName*";
					pages[pk->npage]->Name(page_name);

					rcod = parent->root->DCAaddItem(parent->Host(), pages[pk->npage]);	
					if	(rcod)
					{
						delete	pages[pk->npage];
						pages[pk->npage] = 0L;
						PrintLog(1, QT_TRANSLATE_NOOP("","Error add new page %u/%u <%s>. (%s)"), pk->npage, total_page, page_name, ErrToText(rcod));
					}
					else	PrintLog(4, QT_TRANSLATE_NOOP("","Add new page %u/%u <%s>"), pk->npage, total_page, page_name);
				}
//				else if	(xstrcmp((pages[pk->npage])->Name(), page_name))
//				{
//					SetError("Change page name.");	
//				}
			}
			spin_unlock(&lock);			
		}

		if 	(total_page && (total_page != pk->total))		// Если ответ пришёл самопроизвольно.
		{
			return;			// Изменилось число страниц ??? 
//			if	(xstrcmp(page[pk->npage].Name(),page_name))	// Если изменилось имя страницы, требуется переинциализация..
//			{}
		}
	}

	//====== Получение информации о фреймах отображения.
	void 	EvFrameInfo(dsa_frame_info_ack * pk)
	{
		spin_lock(&lock);
		if	(PageIsValid(pk->npage))
		{
			const char * name = (char *)pk + sizeof(dsa_frame_info_ack);
			pages[pk->npage]->CheckInitFrame(pk->total, pk->nframe, pk->index, pk->nitem, pk->flags, pk->px, pk->py, name);	
		}
		spin_unlock(&lock);
	}

	//====== Получение информации о объектах данных.
	void 	EvItemInfo(dsa_item_info_ack * pk)
	{
		IIDX   i;	
		char * data;   
		unsigned short dlen = pk->hdr.len - sizeof(dsa_item_info_ack);	

		spin_lock(&lock);
		if 	(pages && dlen)
		{
//			PrintLog(9, QT_TRANSLATE_NOOP("","RECV variable %u info"), pk->index);
			data = (char *)pk + sizeof(dsa_item_info_ack);

			for (i=0; i < total_page; ++i)						// Цикл по всем страницам.
					if	(pages[i])	pages[i]->UpdateVariableInfo(pk->iframe, pk->index, (enum dval_type)(pk->dtype), data, dlen);
		}
		spin_unlock(&lock);
	}

	//====== Контроль изменений в интерфейсе после инициализации.
	void	InterfacePeriodic(time_ms ntime)
	{
//		TreeItem * ditem=0L;
//		dsa_subpage_req pk;

		if	(upd_page >= total_page)	upd_page = 0;
		spin_lock(&lock);
/*
		if 	(pages && pages[upd_page])
		{
			if	(pages[upd_page]->SubpageCheck(ntime, &(pk.iframe), &(pk.spage), &ditem))
			{
				pk.hdr.cmd = DCA_SUBPAGE_REQ;
				pk.hdr.key = DCA_HEADER_ADMIN_KEY;
				pk.hdr.len = sizeof(dsa_subpage_req);
				pk.npage   = upd_page;
				parent->SocketWriteData((char *)&pk, sizeof(dsa_subpage_req));
				PrintLog(5, "Request subpage iframe %u, spage %u", pk.iframe, pk.spage);	
			}

			if	(ditem)
			{
				PrintLog(4, "Del Subpage from page %u, name <%s>", upd_page, (const char *)ditem->Name().toLocal8Bit());
				parent->root->DCAdelItem(pages[upd_page], ditem);
			}
		}
*/
		spin_unlock(&lock);
		upd_page++;
	}


/*
	//======
	void	EvSubpageAck(dsa_subpage_ack * pk)
	{
		spin_lock(&lock);
		if	(PageIsValid(pk->npage))
		{
			TreeItem * item=0L; 
			char  name[256];
			strncpy(name, ((char *)pk)+sizeof(dsa_subpage_ack), pk->hdr.len-sizeof(dsa_subpage_ack));
			name[pk->hdr.len-sizeof(dsa_subpage_ack)] = 0;
			char * class_name = &(pk->type[0]);
			class_name[15] = 0;

			if 	(pages && pages[pk->npage])
			{
				item = (TreeItem *)pages[pk->npage]->GetItem(pk->spage);
				if	(!item)
				{
					if	(pages[pk->npage]->Childs() == pk->spage)
					{
						if	((class_name[0] != '#')&&(class_name[1] != '#'))	return;

						item = new 	TreeItem(class_name, pk->spage, pk->iframe, 0);
						if	(!name[0])	item->Name("*NoName*");
						else			item->Name(name);

						retErr	rcod = parent->root->DCAaddItem(pages[pk->npage], item);
						if	(rcod != NO_ERR)	{delete	item;	return;}

						PrintLog(4, "Add Subpage iframe %u, spage %u, name <%s>", pk->iframe, pk->spage, name);
					}
				}
			}

			if	(item)
			{
				ItemPageInfo * pinfo = item->GetPageInfo();
				if	 (pinfo)
				{
					if	((item->Name() != QString::fromLocal8Bit(name))|| strcmp(item->ClassName(), class_name) || (pk->iframe != pinfo->XFrame()))
							pinfo->SetInvalid();
					else	pinfo->SubpageUpdate(Xtime());
				}
			}
		}
		spin_unlock(&lock);
	}
*/

	//======
	bool	IsAllPageInit(void)
	{
		IIDX i;	
		bool rcod = true;

		spin_lock(&lock);
		for (i=0; i < total_page; ++i)
			if	(!IsAllFrameInit(i))
		{		
			rcod = false;
			break;
		}
		spin_unlock(&lock);
		return rcod;	
	}

  private: 
	//======
	void	SetError(const char * str, bool wait)
	{
		PrintLog(1, "Error session. %s", str);
		total_page = 0;
		delete	pages;
		pages= 0L;
		ctime= Xtime();
		if	(wait)	stat = UPD_ERROR;
		else		stat = UPD_NOT_INIT;
	}	
	
	//======
	bool	PageIsValid(IIDX npage) const
	{
		if 	(!pages || (npage >= total_page) || !pages[npage])	return false;
		return	true;
	}

	//======
	bool	IsAllFrameInit(IIDX npage)
	{
		IIDX i;
		bool rcod = true;

		if	(!PageIsValid(npage))			rcod = false;
		else 
		{
			ItemPageInfo * pinfo = pages[npage]->GetPageInfo();
			if		(!pinfo)				rcod = false;
			else if	(!pinfo->TotalFrames())	rcod = false;
			else
			{
				for	 (i=0; i < pinfo->TotalFrames(); ++i)	// Цикл по всем фреймам.
					if	(! pinfo->IsFrameInit(i))		// Проверка, инициализирован ли этот фрейм.
				{
					rcod = false;
					break;
				}
			}
		}
		return rcod;
	}

	int 	stat;	
	time_ms ctime;			//
	IIDX	upd_page;		// Номер обновляемой страницы.
	IIDX	total_page;		// Число существующих страниц отображения (узлов).
	DCAclient  * parent;	//
	TreeItem  ** pages;		// Список страниц отображения.
	SPIN_LOCK  lock;		//
};

//==============================================================================
//==============================================================================
//======
class	PacketEvent : public QEvent
{
  public:
	PacketEvent(dsa_header * _pack) : QEvent(EVENT_INCOMING_PACK), pack(0L)
	{
		pack = (dsa_header *) new char [_pack->len];
		memcpy(pack, _pack, _pack->len);
	}
	virtual ~PacketEvent(void)	{delete pack;}

	dsa_header * pack;
};

//======
retErr	DCAclient::EventDisableReconnect(void)
{	
//	syslog->SetText("-------------- skip connecions ---------------");
	return NO_ERR;
}

//====== Прогоним через очередь событий, ибо вызов может быть из другого thread`а
retErr	DCAclient::EventIncomingPack(struct dsa_header * hd)
{
	if 	(!hd)	return 	-1;
	PacketEvent * evnt = new PacketEvent(hd);
	QApplication::postEvent(this, evnt);
	return NO_ERR;
}

//====== Прогоним через очередь событий, ибо вызов может быть из другого thread`а
retErr	DCAclient::EventConnected(void)
{
	QApplication::postEvent(this, new QEvent(EVENT_CONNECTED));
	return NO_ERR;
}

//====== Прогоним через очередь событий, ибо вызов может быть из другого thread`а
retErr	DCAclient::EventReconnect(void)
{
	QApplication::postEvent(this, new QEvent(EVENT_RECONNECT));
	return NO_ERR;
}

//====== Прогоним через очередь событий, ибо вызов может быть из другого thread`а
retErr	DCAclient::EventDisconnected(void)
{
	QApplication::postEvent(this, new QEvent(EVENT_DISCONNECTED));
	return NO_ERR;
}

//====== Прогоним через очередь событий, ибо вызов может быть из другого thread`а
retErr	DCAclient::EventTimer(void)
{
	QApplication::postEvent(this, new QEvent(EVENT_MY_TIMER));
	return NO_ERR;
}

//==============================================================================
//==============================================================================
DCAclient::DCAclient(QObject * parent, DCAclientRoot  * _root) : 
						QObject(parent), TCPsocketCmd(), root(_root), sess(0L)	
{
	root->DCAdelChild();
}

//======
DCAclient::~DCAclient(void)
{
	delete 	sess;
	sess = 0L;
}

//======
void  DCAclient::ChangesApply(const VarInfo * var, unsigned short row, const char * data, unsigned short lenght)
{
	if	(!sess || !var || !data)	return;

	unsigned short i, k, len=sizeof(dsa_item_value_set) + lenght;
	char * buf = new char [len];
	dsa_item_value_set * pk = (dsa_item_value_set *) buf;
	pk->hdr.cmd = DCA_ITEM_VALUE_SET; 
	pk->hdr.key = DCA_HEADER_ADMIN_KEY;
	pk->hdr.len = len;
	pk->iframe  = var->FrameIndex();			// Индекс фрейма содержащего этот объект данных.	
	pk->index   = rcl2add(row,var->VarIndex());	// Индекс объекта данных в фрейме.
	pk->dtype   = var->Type();					// Тип данных в объекте данных.

	i = 0;
	k = sizeof(dsa_item_value_set);
	while	(i < lenght)	buf[k++] = data[i++];

	SocketWriteData(buf, pk->hdr.len);
	PrintLog(7, QT_TRANSLATE_NOOP("", "Send changes frame %u var %u"), pk->iframe, pk->index);
	delete	buf;
}

//======
void  DCAclient::SendData(IIDX iframe, IIDX index, dval_type type, const char * data, unsigned short lenght)
{
	if	(!sess || !data)	return;

	unsigned short i, k, len=sizeof(dsa_item_value_set) + lenght;
	char * buf = new char [len];
	dsa_item_value_set * pk = (dsa_item_value_set *) buf;
	pk->hdr.cmd = DCA_ITEM_VALUE_SET;
	pk->hdr.key = DCA_HEADER_ADMIN_KEY;
	pk->hdr.len = len;
	pk->iframe  = iframe;		// Индекс фрейма содержащего этот объект данных.	
	pk->index   = index;		// Индекс объекта данных в фрейме.
	pk->dtype   = type;			// Тип данных в объекте данных.

	i = 0;
	k = sizeof(dsa_item_value_set);
	while	(i < lenght)	buf[k++] = data[i++];

	SocketWriteData(buf, pk->hdr.len);
	PrintLog(7, QT_TRANSLATE_NOOP("", "Send data frame %u var %u"), pk->iframe, pk->index);
	delete	buf;
}

//======
void  DCAclient::SendEvent(unsigned short iframe, const char * data, unsigned short lenght)
{
	if 	(!sess)	return;

	unsigned short i, k, len=sizeof(dsa_item_send_data) + lenght;
	char * buf = new char [len];
	dsa_item_send_data * pk = (dsa_item_send_data *)buf;	

	pk->hdr.cmd = DCA_ITEM_SEND_DATA;
	pk->hdr.key = DCA_HEADER_ADMIN_KEY;
	pk->hdr.len = len;
	pk->iframe  = iframe;

	k=sizeof(dsa_item_send_data);
	for	(i=0; i < lenght; ++i,++k)	buf[k] = data[i];
	
	SocketWriteData((char *)pk, len);
	PrintLog(7, QT_TRANSLATE_NOOP("", "Send volatile event frame %u"), iframe);
	delete	buf;
}

//======
void  DCAclient::SendEvent(unsigned short iframe, unsigned short event, unsigned short row, unsigned short col)
{
	if 	(!sess)	return;

	dsa_item_event pk;		
	pk.hdr.cmd = DCA_ITEM_EVENT; 
	pk.hdr.key = DCA_HEADER_ADMIN_KEY;
	pk.hdr.len = sizeof(dsa_item_event);
	pk.iframe  = iframe;
	pk.event   = event;	
	pk.addon   = rcl2add(row, col);
		
	SocketWriteData((char *)&pk, sizeof(dsa_item_event));	  
	PrintLog(7, QT_TRANSLATE_NOOP("", "Send event %u, row %u frame %u"), event, row, iframe);
}

//====== Пеиодическое обновления состояния переменных.
bool  DCAclient::PeriodicUpdate(time_ms ntime)
{
	dsa_item_value_get pk;
	pk.hdr.cmd = DCA_ITEM_VALUE_GET;
	pk.hdr.key = DCA_HEADER_ADMIN_KEY;
	pk.hdr.len = sizeof(dsa_item_value_get);	
	
	emit	GetNextUpdate(&(pk.iframe), &(pk.index), (enum dval_type *)&(pk.dtype), ntime);
	
	if	((pk.iframe == IIDX_ERR)||(pk.index == IIDX_ERR))	return 	false;

	SocketWriteData((const char *)&pk, sizeof(dsa_item_value_get));	  
//	PrintLog(0, QT_TRANSLATE_NOOP("", "SEND variable frame %u, index %u, type %u"), pk.iframe, pk.index, pk.dtype);
	return 	true;
}

//======
bool  DCAclient::event(QEvent * e)
{
  	if		(e->type() == EVENT_MY_TIMER)
	{
		if 	(sess && (Status() == LSTAT_CONNECT))	// Если сетевое подключение уже готов и сессия для него открыта.
		{
			time_ms ntime = Xtime();				
			
			if		(!sess->IsInitOK())				// Если интерфейс ещё не инициализирован.
			{
				sess->InterfaceInit(ntime);			// Вызовем периодическую функцию инициализации интерфейса.
				if	(sess->IsInitOK())				// Если инициализация интерфейса закончена.
							emit	EvConnected();	// Генерируем событие готовности подключения к серверу.	
			}
			else									// Если интерфейс уже инициализирован.
			{
				int		total=100, count=10;
				while 	(count && total--)	if	(PeriodicUpdate(ntime))	count--;
				sess->InterfacePeriodic(ntime);
			}
		}
		return true;
	}
  
  	if	(e->type() == EVENT_CONNECTED)
	{
		sess = new DCAclientSess(this, Xtime());
		return true;
	}

	if	((e->type() == EVENT_DISCONNECTED)||(e->type() == EVENT_RECONNECT))
	{
		if 	(sess)
		{
			delete 	sess;
			sess = 0L;
			root->DCAdelChild();
			emit	EvDisconnected();
		}
		else 	if	(e->type() == EVENT_RECONNECT)
		{
			emit	EvReconnect();
//			PrintLog(0, "!!!! EvReconnect !!!!");	
		}

		return true;
	}

	
	if	(e->type() == EVENT_INCOMING_PACK)
	{
		PacketEvent * ev = (PacketEvent *)e;
		if 	(sess)	switch 	(ev->pack->cmd)
		{
		  default:
			PrintLog(3, QT_TRANSLATE_NOOP("", "Unknown CMD type %04x"), ev->pack->cmd);
			break;

//		  case DCA_SUBPAGE_ACK:
//			sess->EvSubpageAck((dsa_subpage_ack *)(ev->pack));
//			break;
			
		  case DCA_SERVER_INFO_ACK:	//====== Получение информации о сервере.
			sess->EvServerInfo((dsa_server_info_ack *)(ev->pack));
			break;	

		  case DCA_SEND_TEXT_LOG:	//====== Вывод текста в лог.
			emit	EvSetSyslog(QString::fromLocal8Bit(((char *)(ev->pack))+sizeof(dsa_header), ev->pack->len-sizeof(dsa_header)-1));
			break;
	
		  case DCA_PAGE_INFO_ACK:	//====== Получение информации о страницах отображения.
			sess->EvPageInfo(((dsa_page_info_ack *)(ev->pack)));
			break;

		  case DCA_FRAME_INFO_ACK:	//====== Получение информации о фреймах отображения.
			sess->EvFrameInfo(((dsa_frame_info_ack *)(ev->pack)));
			break;

		  case DCA_ITEM_INFO_ACK:	//====== Получение информации о объектах данных.
			sess->EvItemInfo(((dsa_item_info_ack *)(ev->pack)));
			break;
			
		  case DCA_ITEM_VALUE_SET:	//====== 
			{
				dsa_item_value_set * pk = (dsa_item_value_set *)(ev->pack);

				char * data = 0L;
				unsigned short	dlen = pk->hdr.len - sizeof(dsa_item_value_set);	
				if (dlen)		data = (char *)pk  + sizeof(dsa_item_value_set);
				
				emit	UpdateValues(pk->iframe, pk->index, (enum dval_type)(pk->dtype), data, dlen);
			}
			break;
		}
		return true;
	}
	return	false;
}

//==============================================================================
