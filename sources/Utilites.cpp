#define	  _CRT_SECURE_NO_WARNINGS

#include <QtWidgets/QWidget>
#include  "Common.h"


char * xstrcpy(char * dst, const char * src)
{
    unsigned short i;
    if 	(!dst || !src)
    {
        printf("Error STRCPY null\n");
        return dst;
    }

    for (i=0; i < 512; ++i)
    {
        dst[i] = src[i];
        if 	(!dst[i])	return 	dst + i;
    }

    printf("Error STRCPY long\n");
    return dst;
}

//======
int   xstrcmp(const char * str1, const char * str2)
{
    if 	(!str2 && !str1)	return 0;
    if 	(!str2 || !str1)	return 1;

    while (true)
    {
        if (*str1 != *str2) return 2;
        if (!(*str1)) 		return 0;
        str1++;	str2++;
    }
    return 3;
}

//======
char * xstrnum(char * dst, unsigned short num)
{
    unsigned short set=0;
    if 	(!dst)	{printf("Error STRNUM\n");	return dst;}

    if 	(num >= 10000)			{++set;	*dst++ = '0'+ num/10000; 	num %= 10000;}
    if 	(set ||(num >= 1000))	{++set;	*dst++ = '0'+ num/1000; 	num %= 1000;}
    if 	(set ||(num >= 100))	{++set;	*dst++ = '0'+ num/100; 		num %= 100;}
    if 	(set ||(num >= 10))		{		*dst++ = '0'+ num/10; 		num %= 10;}
    *dst++ = '0' + num;	*dst = 0;

    return dst;
}

//======
char * xstrnum(char * dst, unsigned long num)
{
    unsigned long set=0;
    if 	(!dst)	{printf("Error STRNUM\n");	return dst;}

    if 	(num >= 1000000000)			{++set;	*dst++ = '0'+ num/1000000000; 	num %= 1000000000;}
    if 	(set ||(num >= 100000000))	{++set;	*dst++ = '0'+ num/100000000; 	num %= 100000000;}
    if 	(set ||(num >= 10000000))	{++set;	*dst++ = '0'+ num/10000000; 	num %= 10000000;}
    if 	(set ||(num >= 1000000))	{++set;	*dst++ = '0'+ num/1000000; 		num %= 1000000;}
    if 	(set ||(num >= 100000))		{++set;	*dst++ = '0'+ num/100000; 		num %= 100000;}
    if 	(set ||(num >= 10000))		{++set;	*dst++ = '0'+ num/10000; 		num %= 10000;}
    if 	(set ||(num >= 1000))		{++set;	*dst++ = '0'+ num/1000; 		num %= 1000;}
    if 	(set ||(num >= 100))		{++set;	*dst++ = '0'+ num/100; 			num %= 100;}
    if 	(set ||(num >= 10))			{++set;	*dst++ = '0'+ num/10; 			num %= 10;}

    *dst++ = '0' + num;	*dst = 0;

    return dst;
}

//======
int 	ValidateHostName(const QString str)
{
    if 	(str.isEmpty()) 	return ERR_NET_PATH_EMPTY;
    int sz = str.size();
    if	(sz > 512)		return ERR_NET_PATH_TOO_LONG;

//    if	(str.contains(QRegExp("[0-255\.\s]")))
//        return ERR_NET_PATH_INVALID;

    return NO_ERR;
}

