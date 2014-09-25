/*==============================================================================
// File:    DCAclientRoot.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   25.03.2014
// Read license.txt for more informations.
//============================================================================*/

#ifndef  DCA_CLIENT_ROOT
#define  DCA_CLIENT_ROOT

#include  "Common.h"
#include  "TreeItem.h"

//======
class DCAclientRoot
{
  public:
	DCAclientRoot(void)	{}

	//====== Удалить все ноды этого DCA сервера.
	retErr	DCAdelChild(void)								{/*return	DelAllChild(DCArootItem(host));*/return -9;}

	//======Добавить ноду к этому DCA серверу.
	retErr	DCAaddItem(const char * host, TreeItem * item)	{return	AddItem(DCArootItem(host), item);}
	retErr	DCAaddItem(TreeItem * parent, TreeItem * item)	{return	AddItem(parent, item);}
	retErr	DCAdelItem(const char * host, TreeItem * item)	{return	DelItem(DCArootItem(host), item);}
	retErr	DCAdelItem(TreeItem * parent, TreeItem * item)	{return	DelItem(parent,  item);}

  protected:
	virtual	retErr	   AddItem(TreeItem  * parent, TreeItem * item)=0;
	virtual	retErr	   DelItem(TreeItem  * parent, TreeItem * item)=0;
	virtual	retErr	   DelAllChild(TreeItem  * parent)=0;
	virtual	TreeItem * DCArootItem(const char * host)=0;
};

#endif   // DCA_CLIENT_ROOT
//==============================================================================
