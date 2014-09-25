/*==============================================================================
// File:    Error.h
// Author:  Shvetsov Sergey <pp_serg@mail.ru>
// Version: 1.1 beta
// Begin:   22.05.2014
// Read license.txt for more informations.
//============================================================================*/
//
//=============================================================================

#ifndef	  ERROR_H
#define   ERROR_H

typedef	 signed int	  retErr;
const char * ErrToText(retErr rcod);

//====== ���� ������.
#define	 NO_ERR						  0		// ������ ���.

#define	 ERR_PARAMS					-86		// 
#define	 ERR_SERVICE_NOT_EXIST		-93		// ������ �� ����������.

#define	 ERR_AUDIO_OUTPUT_NOT_EXIST	-100	//
#define	 ERR_AUDIO_INPUT_NOT_EXIST	-101	//
#define	 ERR_OPEN_AUDIO_OUTPUT		-102	//
#define	 ERR_OPEN_AUDIO_INPUT		-103	//

#define	 ERR_RESIZE_PORTS_ARRAY		-104	// 
#define	 ERR_DESTROY_OBJECT			-105	//

#define	 ERR_HANG_TIME_END			-110	// �������� ������������ �� ��������� hang time.
#define	 ERR_HANG_TIME_BEGIN		-111	// ������ �������� hang time ���������� ������������.
#define	 ERR_TIMEOUT_WRITE_CONFIRM	-112	//
#define	 ERR_ABORT_BY_ADMIN			-113	// �������� ���������������.

#define	 ERR_DUPLICATE_ID			-123	// ������������ ���������������.
#define	 ERR_DUPLICATE_FROM			-124	// ������������ ����������.

#define	 ERR_NO_LOGIN				-125	// ��� ������.
#define	 ERR_NO_PASSWD				-126	// ��� ������.
#define	 ERR_PASSWD					-127	// ������ �� �������������.
#define	 ERR_NO_SESSION				-128	// ������ �� �������.
#define	 ERR_NO_MESSAGE				-129	//

#define	 ERR_PEER_NOT_EXIST			-130	//
#define	 ERR_PACKET_SIZE			-131	// ������ ������� ������.

//=========
#define	 ERR_CLIENT_LIST_EMPTY		-135 	// ������ ������ ��������.
#define	 ERR_NOT_CLIENT_LIST		-136 	// ��� ������ ��������.
#define	 ERR_TOO_MANY_CLIENTS		-137	// ����� ����� ��������.
#define	 ERR_CLIENT_NO_SESSION		-138	// ��� ����� ������� �� ������� ������.
#define	 ERR_CLIENT_NO_BASE			-139	// ������ �� ����������� ����� ���������.
#define	 ERR_CLIENT_ALREADY_EXIST	-140	// ������ ��� ����������.
#define	 ERR_CLIENT_NOT_EXIST		-141	// ������ �� ����������.
#define	 ERR_CLIENT_ID_INVALID		-142	// ������ �� ����������.
#define	 ERR_CLIENT_DISABLED		-143	// ������ ��������.
#define	 ERR_CLIENT_NOT_READY		-144	// ������ �� �����.
#define	 ERR_CLIENT_NOT_REGISTRED	-145	// ������ �� ��������������� ��������.
#define	 ERR_CLIENT_STREAM_OUTPUT	-146 	// ��� ����� ������� ��� ������� ������ ���������� ������.
#define	 ERR_CLIENT_STREAM_INPUT	-147 	// ��� ����� ������� ��� ������� ������ ���������� �����.
#define	 ERR_CLIENT_UNREGISTRED		-148	// ������ ������������������.
#define	 ERR_CLIENT_ZERO_ID			-149	// ������� ������������� �� �����������.
#define	 ERR_CLIENT_SESSION			-150	// ������������� ������ �� ������������ ������ ����������� �������.

//=========
#define	 ERR_NET_PATH_TOO_LONG		-155	//
#define	 ERR_NET_PORT_NUMBER		-156	//
#define	 ERR_NO_FREE_PORTS			-157	// ��� ���������� ������ �����.
#define	 ERR_PORTS_UNDEFINED		-158	// ����� �� ����������.
#define	 ERR_PARSE_PORT_NUMBER		-159	// ������ �������� ������ �����.
#define	 ERR_ZERO_PORT_NUMBER		-160	// ����� ����� �� ����� ���� �������.
#define	 ERR_PORT_NUMBER			-161	// ������������ ����� �����.
#define	 ERR_RESOLVE_HOST_NAME		-162	// ���������� ������������ IP ����� �� ����� �����.
#define	 ERR_NET_PATH_EMPTY			-163	// ������ ������� ����.
#define	 ERR_NET_PATH_INVALID		-164	// ������� ���� �������� ������������ �������.
#define	 ERR_SOCKET_BIND			-165	//
#define	 ERR_SOCKET_OPEN			-166	//
#define	 ERR_NOT_CONNECTED			-167	// ���������� �� �����������.
#define	 ERR_SOCKET_NOT_OPEN		-168	//
#define	 ERR_SOCKET_SETSOCKOPT		-169	//

#define	 ERR_TOO_MANY_ITEMS			-170	// ����� ����� ��������.
#define	 ERR_ITEM_POINTER			-171	// ��������� ��������� �� ������.
#define  ERR_ITEM_NOT_EXIST			-172	// ������ �� ����������.
#define  ERR_ITEM_ALREADY_EXIST		-173	// ������ ��� ����������.

#define	 ERR_START_THREAD			-174	// ������ ��� ������� �������� ��������� ������� �������.
#define	 ERR_DATA_TOO_SHORT			-175	// ������������� ������ ����� ������.
#define	 ERR_DATA_TOO_LONG		    -176	// ���������� ������� ����� ������.
#define	 ERR_TIMEOUT_DELETE_OBJECTS -177	//

#define	 ERR_EMPTY_FILE_NAME		-181	// �� ����� ���� � ��� ����� ��� ����������.
#define	 ERR_FILE_HEADER			-182	// ������ ��������� �����.
#define	 ERR_READ_FILE				-183	// ������ ��� ������ �����.
#define	 ERR_WRITE_FILE				-184	// ������ ��� ������ �����.
#define	 ERR_OPEN_READ_FILE			-185	// ������ �������� ����� �� ������.
#define	 ERR_OPEN_WRITE_FILE		-186	// ������ �������� ����� �� ������.
#define	 ERR_FILE_DESCRIPTOR		-187	// �� ����������� ���������� ����� ��� ������.

#define	 ERR_ZERO_POINTER			-190	// ������ ���������.
#define	 ERR_INDEX_NOT_EXIST		-191	// ������ ��� ���� �������� �����������.
#define	 ERR_NAME_INVALID			-192	// �� ���������� ���.
#define	 ERR_NAME_EXIST				-193	// ��� ��� ������� � ������.


#define	 ERR_UNKNOW_DATA_TYPE		-201	//
#define	 ERR_UNKNOW_PROTOCOL		-202	//

#define	 ERR_SIP_BUSY				-1001	// � ����� �� INVITE ������ BUSY
#define	 ERR_SIP_TIMEOUT_CONFIRM	-1002	// ������� �������� ������ �� INVITE. 
#define	 ERR_SIP_STREAM_TIMEOUT		-1003	// ������� �������� ������ �� SIP �������.
#define	 ERR_SIP_RECV_CANCEL		-1004	// ������� ������� CANCEL.
#define	 ERR_SIP_RECV_BYE			-1005	// ������� ������� BYE.
#define	 ERR_SIP_TIMEOUT_RINGING	-1006	// ������� ��������� RINGING.
#define	 ERR_SIP_SYSTEM_ERR			-1007	// ���������� ������ ������ SIP �����������.
#define	 ERR_SIP_TRY_INVITE			-1008	// ����������� SIP ������ �� ��������� ����� INVITE �������.
#define	 ERR_SIP_TRY_CONFIRM		-1009	// ����������� SIP ������ �� ��������� ����� CONFIRM �������.
#define	 ERR_SIP_END_WAIT_NOTIFY	-1010	// ����������� SIP ������ �� ��������� �������� �������� ������������� �� �����������.
#define	 ERR_SIP_RTP_SEND			-1011	// ������ �������� RTP ������ SIP ������.
#define	 ERR_SIP_RTP_STREAM_REOPEN	-1012	// ������������ ��� ������������� ������.
#define	 ERR_SIP_REMOTE_BYE			-1013	// �������� �� ���������� ���� �����������.

#define	 ERR_STREAM_CLOSE_END		-2001	// ���������� ������ �� ���������� ���������.
#define	 ERR_STREAM_CLOSE_NO_DATA	-2002	// ���������� ������ �� ���������� �������� ������.
#define	 ERR_STREAM_CLOSE_NO_TARGET	-2003	// ���������� ������ �� ���������� �����������.
#define	 ERR_STREAM_CLOSE_BY_USER	-2004	// ���������� ������ �� ������� ������������.
#define	 ERR_STREAM_REOPEN			-2005	// ������������ ��� ������������� ������.
#define	 ERR_STREAM_REOPEN_BACK		-2006	// ������������ ��� ������������� ������.
#define	 ERR_STREAM_NOT_EXIST		-2007	// ����� �� ����������.
#define	 ERR_STREAM_NOT_OPEN		-2008	// ����� �� ������.
#define	 ERR_STREAM_PARM_CHANGED	-2009	// ���������� ��������� ������.
#define	 ERR_STREAM_PACK_SIZE		-2010	// ������������ ������ ������ ������.
#define	 ERR_STREAM_TIMEOUT_READ	-2011	// ������� �������� ��������� ������ ������������� ������.
#define	 ERR_STREAM_TIMEOUT_WRITE	-2012	// ������� �������� ��������� ������ ������������ ������.
#define	 ERR_TOO_MANY_STREAMS		-2013	// ����� ����� ������� �������� ������.

#define	 ERR_GROUP_NOT_EXIST		-3001	// ������ �� ����������.
#define	 ERR_GROUP_ALREADY_EXIST	-3002	// ������ ��� ����������.
#define	 ERR_GROUP_IS_TEMPORARY		-3003	// ��� ��������� ������.
#define	 ERR_GROUP_IS_SYNC			-3004	// ������ �����������������.
#define	 ERR_GROUP_IS_NOT_SYNC		-3005	// ������ �� �����������������.
#define	 ERR_GROUP_IS_DELETED		-3006	// 

#define	 ERR_CODEC_NOT_INIT			-4001	// ����� �� ���������������.
#define	 ERR_CODEC_DEC_NOT_INIT		-4002	// ������ ������������� ������ �� ���������������.
#define	 ERR_CODEC_ENC_NOT_INIT		-4003	// ������ ������������� ������ �� ���������������.
#define	 ERR_ENCODE_ERROR			-4004	// 
#define	 ERR_DECODE_ERROR			-4005	// 
#define	 ERR_NO_FREE_CODEC			-4006	// ��� ��������� �������.

#define	 ERR_XML_LOAD_FILE			-5001	// ������ �������� XML �����.
#define	 ERR_XML_SAVE_FILE			-5002	// ������ �������� XML �����.
#define	 ERR_XML_STRUCT				-5003	// ������ � ��������� XML �����.
#define	 ERR_XML_HEX_PARSER			-5004	// 

#define	 ERR_SERVER_LIST_NOT_EXIST	-6001	//
#define	 ERR_SERVER_NOT_EXIST		-6002	// ������ �� ����������.
#define	 ERR_SERVER_ALREADY_EXIST	-6003	// ������ ��� ����������.
#define	 ERR_SERVER_IS_ITSELF		-6004	// �������� ������ ������������ ��������.

#define	 ERR_NO_FREE_SLOT			-7004	// ��� ��������� ������.
#define	 ERR_SLOT_BUSY				-7005	// ���� �����.

#define	 ERR_CRC8					-8001	//	
#define	 ERR_CRC9					-8002	//
#define	 ERR_CRC16					-8003	//
#define	 ERR_CRC32					-8004	//

#endif // ERROR_H
//=============================================================================

