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

//====== Коды ошибок.
#define	 NO_ERR						  0		// Ошибки нет.

#define	 ERR_PARAMS					-86		// 
#define	 ERR_SERVICE_NOT_EXIST		-93		// Сервис НЕ существует.

#define	 ERR_AUDIO_OUTPUT_NOT_EXIST	-100	//
#define	 ERR_AUDIO_INPUT_NOT_EXIST	-101	//
#define	 ERR_OPEN_AUDIO_OUTPUT		-102	//
#define	 ERR_OPEN_AUDIO_INPUT		-103	//

#define	 ERR_RESIZE_PORTS_ARRAY		-104	// 
#define	 ERR_DESTROY_OBJECT			-105	//

#define	 ERR_HANG_TIME_END			-110	// Закрытие мультисессии по окончанию hang time.
#define	 ERR_HANG_TIME_BEGIN		-111	// Начало ожидания hang time завершения мультисессии.
#define	 ERR_TIMEOUT_WRITE_CONFIRM	-112	//
#define	 ERR_ABORT_BY_ADMIN			-113	// Прервано администратором.

#define	 ERR_DUPLICATE_ID			-123	// Дублирование идентификаторов.
#define	 ERR_DUPLICATE_FROM			-124	// Дублирование источников.

#define	 ERR_NO_LOGIN				-125	// Нет логина.
#define	 ERR_NO_PASSWD				-126	// Нет пароля.
#define	 ERR_PASSWD					-127	// Пароль не соответствует.
#define	 ERR_NO_SESSION				-128	// Сессия не открыта.
#define	 ERR_NO_MESSAGE				-129	//

#define	 ERR_PEER_NOT_EXIST			-130	//
#define	 ERR_PACKET_SIZE			-131	// Ошибка размера пакета.

//=========
#define	 ERR_CLIENT_LIST_EMPTY		-135 	// Пустой список клиентов.
#define	 ERR_NOT_CLIENT_LIST		-136 	// Нет списка клиентов.
#define	 ERR_TOO_MANY_CLIENTS		-137	// Очень много клиентов.
#define	 ERR_CLIENT_NO_SESSION		-138	// Для этого клиента не открыта сессия.
#define	 ERR_CLIENT_NO_BASE			-139	// Клиент не принадлежит этому подсписку.
#define	 ERR_CLIENT_ALREADY_EXIST	-140	// Клиент уже существует.
#define	 ERR_CLIENT_NOT_EXIST		-141	// Клиент НЕ существует.
#define	 ERR_CLIENT_ID_INVALID		-142	// Клиент НЕ существует.
#define	 ERR_CLIENT_DISABLED		-143	// Клиент запрещён.
#define	 ERR_CLIENT_NOT_READY		-144	// Клиент не готов.
#define	 ERR_CLIENT_NOT_REGISTRED	-145	// Клиент не зарегистрирован сервером.
#define	 ERR_CLIENT_STREAM_OUTPUT	-146 	// Для этого клиента уже открыта сессия потокового вывода.
#define	 ERR_CLIENT_STREAM_INPUT	-147 	// Для этого клиента уже открыта сессия потокового ввода.
#define	 ERR_CLIENT_UNREGISTRED		-148	// Клиент разрегистрировался.
#define	 ERR_CLIENT_ZERO_ID			-149	// Нулевой идентификатор не допускается.
#define	 ERR_CLIENT_SESSION			-150	// Идентификатор сессии не соответсвует номеру регистрации клиента.

//=========
#define	 ERR_NET_PATH_TOO_LONG		-155	//
#define	 ERR_NET_PORT_NUMBER		-156	//
#define	 ERR_NO_FREE_PORTS			-157	// Нет свободного номера порта.
#define	 ERR_PORTS_UNDEFINED		-158	// Порты не определены.
#define	 ERR_PARSE_PORT_NUMBER		-159	// Ошибка парсинга номера порта.
#define	 ERR_ZERO_PORT_NUMBER		-160	// Номер порта не может быть нулевым.
#define	 ERR_PORT_NUMBER			-161	// Недопустимый номер порта.
#define	 ERR_RESOLVE_HOST_NAME		-162	// Невозможно отрезольвить IP адрес по имени хоста.
#define	 ERR_NET_PATH_EMPTY			-163	// Пустой сетевой путь.
#define	 ERR_NET_PATH_INVALID		-164	// Сетевой путь содержит недопустимые символы.
#define	 ERR_SOCKET_BIND			-165	//
#define	 ERR_SOCKET_OPEN			-166	//
#define	 ERR_NOT_CONNECTED			-167	// Соединение не установлено.
#define	 ERR_SOCKET_NOT_OPEN		-168	//
#define	 ERR_SOCKET_SETSOCKOPT		-169	//

#define	 ERR_TOO_MANY_ITEMS			-170	// Очень много объектов.
#define	 ERR_ITEM_POINTER			-171	// Ошибочный указатель на объект.
#define  ERR_ITEM_NOT_EXIST			-172	// Объект не существует.
#define  ERR_ITEM_ALREADY_EXIST		-173	// Объект уже существует.

#define	 ERR_START_THREAD			-174	// Ошибка при запуске процесса обработки сетевых событий.
#define	 ERR_DATA_TOO_SHORT			-175	// Недостаточный размер блока данных.
#define	 ERR_DATA_TOO_LONG		    -176	// Превышение размера блока данных.
#define	 ERR_TIMEOUT_DELETE_OBJECTS -177	//

#define	 ERR_EMPTY_FILE_NAME		-181	// Не задан путь и имя файла для сохранения.
#define	 ERR_FILE_HEADER			-182	// Ошибка заголовка файла.
#define	 ERR_READ_FILE				-183	// Ошибка при чтении файла.
#define	 ERR_WRITE_FILE				-184	// Ошибка при записи файла.
#define	 ERR_OPEN_READ_FILE			-185	// Ошибка открытия файла на чтение.
#define	 ERR_OPEN_WRITE_FILE		-186	// Ошибка открытия файла на запись.
#define	 ERR_FILE_DESCRIPTOR		-187	// Не определённый дескриптор файла или сокета.

#define	 ERR_ZERO_POINTER			-190	// Пустой указатель.
#define	 ERR_INDEX_NOT_EXIST		-191	// Данные под этим индексом отсутствуют.
#define	 ERR_NAME_INVALID			-192	// Не допустимое имя.
#define	 ERR_NAME_EXIST				-193	// Имя уже имеется в списке.


#define	 ERR_UNKNOW_DATA_TYPE		-201	//
#define	 ERR_UNKNOW_PROTOCOL		-202	//

#define	 ERR_SIP_BUSY				-1001	// В ответ на INVITE принят BUSY
#define	 ERR_SIP_TIMEOUT_CONFIRM	-1002	// Таймаут ожидания ответа на INVITE. 
#define	 ERR_SIP_STREAM_TIMEOUT		-1003	// Таймаут ожидания потока от SIP сервера.
#define	 ERR_SIP_RECV_CANCEL		-1004	// Принята команда CANCEL.
#define	 ERR_SIP_RECV_BYE			-1005	// Принята команда BYE.
#define	 ERR_SIP_TIMEOUT_RINGING	-1006	// Таймаут окончания RINGING.
#define	 ERR_SIP_SYSTEM_ERR			-1007	// Внутренняя ошибка потока SIP обработчика.
#define	 ERR_SIP_TRY_INVITE			-1008	// Прекращение SIP сессии по окончанию числа INVITE попыток.
#define	 ERR_SIP_TRY_CONFIRM		-1009	// Прекращение SIP сессии по окончанию числа CONFIRM попыток.
#define	 ERR_SIP_END_WAIT_NOTIFY	-1010	// Прекращение SIP сессии по окончанию таймаута ожидания подтверждения от получателей.
#define	 ERR_SIP_RTP_SEND			-1011	// Ошибка передачи RTP данных SIP сессии.
#define	 ERR_SIP_RTP_STREAM_REOPEN	-1012	// Переоткрытие уже существующего потока.
#define	 ERR_SIP_REMOTE_BYE			-1013	// Закрытие по отключению всех получателей.

#define	 ERR_STREAM_CLOSE_END		-2001	// Отключение потока по отключению источника.
#define	 ERR_STREAM_CLOSE_NO_DATA	-2002	// Отключение потока по отсутствию передачи данных.
#define	 ERR_STREAM_CLOSE_NO_TARGET	-2003	// Отключение потока по отсутствию получателей.
#define	 ERR_STREAM_CLOSE_BY_USER	-2004	// Отключение потока по запросу пользователя.
#define	 ERR_STREAM_REOPEN			-2005	// Переоткрытие уже существующего потока.
#define	 ERR_STREAM_REOPEN_BACK		-2006	// Переоткрытие уже существующего потока.
#define	 ERR_STREAM_NOT_EXIST		-2007	// Поток НЕ существует.
#define	 ERR_STREAM_NOT_OPEN		-2008	// Поток НЕ открыт.
#define	 ERR_STREAM_PARM_CHANGED	-2009	// Изменились параметры потока.
#define	 ERR_STREAM_PACK_SIZE		-2010	// Недопустимый размер пакета потока.
#define	 ERR_STREAM_TIMEOUT_READ	-2011	// Таймаут ожидания получения данных передаваемого потока.
#define	 ERR_STREAM_TIMEOUT_WRITE	-2012	// Таймаут ожидания получения данных принимаемого потока.
#define	 ERR_TOO_MANY_STREAMS		-2013	// Очень много потоков передачи данных.

#define	 ERR_GROUP_NOT_EXIST		-3001	// Группа не существует.
#define	 ERR_GROUP_ALREADY_EXIST	-3002	// Группа уже существует.
#define	 ERR_GROUP_IS_TEMPORARY		-3003	// Это временная группа.
#define	 ERR_GROUP_IS_SYNC			-3004	// Группа синхронизированна.
#define	 ERR_GROUP_IS_NOT_SYNC		-3005	// Группа НЕ синхронизированна.
#define	 ERR_GROUP_IS_DELETED		-3006	// 

#define	 ERR_CODEC_NOT_INIT			-4001	// Кодек не инициализирован.
#define	 ERR_CODEC_DEC_NOT_INIT		-4002	// Модуль декодирования кодека не инициализирован.
#define	 ERR_CODEC_ENC_NOT_INIT		-4003	// Модуль енкодирования кодека не инициализирован.
#define	 ERR_ENCODE_ERROR			-4004	// 
#define	 ERR_DECODE_ERROR			-4005	// 
#define	 ERR_NO_FREE_CODEC			-4006	// Нет свободных кодеков.

#define	 ERR_XML_LOAD_FILE			-5001	// Ошибка открытия XML файла.
#define	 ERR_XML_SAVE_FILE			-5002	// Ошибка открытия XML файла.
#define	 ERR_XML_STRUCT				-5003	// Ошибка в структуре XML файла.
#define	 ERR_XML_HEX_PARSER			-5004	// 

#define	 ERR_SERVER_LIST_NOT_EXIST	-6001	//
#define	 ERR_SERVER_NOT_EXIST		-6002	// Сервер НЕ существует.
#define	 ERR_SERVER_ALREADY_EXIST	-6003	// Сервер уже существует.
#define	 ERR_SERVER_IS_ITSELF		-6004	// Удалённый сервер эквивалентен текущему.

#define	 ERR_NO_FREE_SLOT			-7004	// Нет свободных слотов.
#define	 ERR_SLOT_BUSY				-7005	// Слот занят.

#define	 ERR_CRC8					-8001	//	
#define	 ERR_CRC9					-8002	//
#define	 ERR_CRC16					-8003	//
#define	 ERR_CRC32					-8004	//

#endif // ERROR_H
//=============================================================================

