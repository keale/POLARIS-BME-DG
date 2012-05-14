

#ifndef _BME_NET_H
#define _BME_NET_H

/*******************************************************************************
 * Copyright (c) Fetron GmbH 2011.
 *
 * Autor : Steffen Müller
 * 
 * 
 * File Name: BME_Net.h
 *
 *      
 *
 * Description:
 *
 *			This file defines the basic types for remote communication.
 *			Defines and Typedefs for the Network communication.
 *
 * Revision:
 *
 *     Date:  20110609 : Version First Edit
 *
 ******************************************************************************/

#pragma comment(lib, "Ws2_32.lib") //bind for VC++

#include <winsock.h>

//TODO SM 

#ifdef __cplusplus
extern "C" {
#endif


/*for Network communication port definiton*/
//TODO SM
#define C_PORT 8001

/* defines for send and receive buffer size*/
/* Buffer size for receive messages */
#define RCVBUFSIZE 1024
/* Buffer size for send messages */
#define SENDBUFSIZE 1024

//#define HOST "BME_Server\0"

#define ANZ_NET_CONNECTS      5

/* Error Variable for network functions */
#define ERR_SIZE              30


/**
 * @brief this structure stores the net address of the connected client
 *        and the socket number got from the accept() function.
*/
typedef struct _NetCfg
{
  struct sockaddr_in server_addr;
  int IsConnected;
  SOCKET sock;
} NetCfg;

/*----------------------------------------------------------------------------------------
*/
/**
 *@brief defines for remote function calls and error messages.
 *
*/

#define C_MAX_MSG_LEN      100   // 100 chars

typedef enum _BME_REMOTE_COMMAND
{ 
  E_BmeDelgenWrite = 10,
  E_BmeDelgenRead,
  E_BmeDelgenDeviceOpen,
  E_BmeDelgenDeviceClose,
  E_BmeDelgenNumberPciCards,
  E_BmeDelgenDeviceFind,
  E_BmeDelgenReadSubVendorID,
  E_BmeDelgenVpdRead,
  E_ReceiveBufferLen,
  E_ErrorBufferLen,                    //for error Messages send to the client
  E_ErrorFunctionNotImplemented,
  E_ErrorUndefined
}BME_REMOTE_COMMAND;

/*----------------------------------------------------------------------------------------
*/
/**
 *@brief defines for remote error messages.
 *
*/

#define C_FUNKTION_NOT_IMPLEMENTED     "Function not implemented!\0"
#define C_SEND_BUFFER_TO_SMALL         "Send buffer to small, result could not send\0"
#define C_RECEIVE_BUFFER_OVERFLOW      "Receive buffer overflow\0"
#define C_ERROR_UNDEF                  "undefined error\0"
#define C_ERROR_DEFAULT                "Error default, not seperated or not planed\0"


void PrintWSA(int Nr, char Err[]);


#ifdef __cplusplus
}
#endif

#endif;

//end of file