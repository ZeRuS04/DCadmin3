/*==============================================================================
// File:    Common.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   26.03.13
// Read license.txt for more informations.
//============================================================================*/

#ifndef  COMMON_H
#define  COMMON_H
#include <QString>
#include "Structs.h"
#include  "Error.h"


//#include  "Defines.h"

#define	  ORG_NAME		"PapuaSoft"
#define	  ORG_DOMAIN	"pp_serg@mail.ru"

#define	  VER_RELEASE	"0"
#define	  VER_GLOBAL	"1"


//======
#ifdef _DEBUG
#define	  APP_VERSION(x) ("v" VER_RELEASE "." VER_GLOBAL "." x " (debug)")
#else
#define	  APP_VERSION(x) ("v" VER_RELEASE "." VER_GLOBAL "." x)
#endif

//======
#define	  XML_SERVER_CONFIG		"Config"
#define	  XML_SERVER_LIST		"ServerList"
#define	  XML_SERVICE_LIST		"ServiceList"
#define	  XML_GROUP_LIST		"GroupList"

//======
typedef unsigned long  time_utf;	// ���������� ����� � �������� (�� 00:00:00 UTC, 01.01.1970).
typedef unsigned long  time_sec;	// ����� � ��������.
typedef unsigned char  time_qs;		// ����� � 1/4 ����� �������.
typedef unsigned long  time_ms;		// ����� � ������������� �� 65.5 ������.

//======
extern  const char  * start_string;
extern  const char  * version_info;
extern  const char  * config_file_name;
extern  const char  * app_name;
extern  unsigned long start_time;

//======
inline 	time_ms  TDelta(time_ms a, time_ms  b)	{if (a <= b) return 0L; else return	(a-b);}
//inline 	time_ms  TDelta(time_qs a, time_qs  b)	{if (a <= b) return 0L; else return	ToMS(a-b);}
//inline 	time_ms  TDelta(time_ms a, time_qs  b)	{return  TDelta(a, ToMS(b));}
//inline 	time_ms  TDelta(time_qs a, time_ms  b)	{return  TDelta(ToMS(a), b);}

//======
unsigned long GetMyIP(const char * dev=0L);

//======
const char *  TextMyIP(const char * dev=0L);

//====== ��������� ������� �� ������ ��������� ������������
time_ms 	  Xtime(bool reset=false);

//====== ��������� ����������� �������  �� ����� �������.
unsigned long GetUTFtime(void);

//======
const char *  GetTimeText(char * str=0L);

//====== ����� ���������� ����������
extern  void (* PrintLog)(int level, const char * format, ...);

//====== ��������� ���������� ����� � �������� ��������� ��������.
unsigned long NRand(unsigned long max_value=0xffffffff);

//======
const char *  PackInfo(const void * data/*, int level=0*/);

//======
char * 	CopyString(const char * src, const char * dst=0L);

//======
char * xstrcpy(char * dst, const char * src);
char * xstrnum(char * dst, unsigned short num);
char * xstrnum(char * dst, unsigned long num);
int    xstrcmp(const char * str1, const char * str2);
//#define xstrendl(str)	{*str++=0x0d; *str++=0x0a;}

//======
unsigned short 	SymToByte(unsigned short sym);

//====== ������� ����� � ��� ��������� ������� HEX �������������.
unsigned short ByteToSym(unsigned char byte);

//======
int 	ValidateHostName(const QString str);
//int 	ParsePortFromAddr(char * net_addr);
//int 	GetPortFromAddr(const char * str, int * ps=0L);

//======
int 	CalcPortsFromStr(const char * str, unsigned short * pmin, unsigned short * pmax);
int 	CalcRangeUIDfromStr(const char * str, unsigned long * pmin, unsigned long * pmax);

//======
unsigned short 	UsageCPU(void);
unsigned long 	GetAvailPhysMem(void);

//======
const char * FormatMemSize(double size);

extern  int   DBGLV;		// ������� ���������� ���������.

//======
union diflg
{
    unsigned  short value;
    struct
    {
        unsigned  short ask_server_delete	: 1;
        unsigned  short info_err_add_server	: 1;
//		unsigned  short info_err_add_server	: 1;
//		unsigned  short info_err_add_server	: 1;
//		unsigned  short info_err_add_server	: 1;
//		unsigned  short info_err_add_server	: 1;
    };
};

extern union diflg	DIFLG;

#endif // COMMON_H
