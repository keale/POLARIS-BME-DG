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

#include "bme_net.h"



/*
 *@brief copied from RTB_CLI.C (SOFTWARE-BUERO-F-X-MAYER) 
*/ 

void PrintWSA(int Nr, char Err[])
{
  switch (Nr)
  { 
    case WSAEINTR             : strcpy (Err,"WSAEINTR           "); break; 
    case WSAEBADF             : strcpy (Err,"WSAEBADF           "); break;  
    case WSAEACCES            : strcpy (Err,"WSAEACCES          "); break;  
    case WSAEFAULT            : strcpy (Err,"WSAEFAULT          "); break;
    case WSAEINVAL            : strcpy (Err,"WSAEINVAL          "); break;  
    case WSAEMFILE            : strcpy (Err,"WSAEMFILE          "); break;  
    case WSAEWOULDBLOCK       : strcpy (Err,"WSAEWOULDBLOCK     "); break;  
    case WSAEINPROGRESS       : strcpy (Err,"WSAEINPROGRESS     "); break;  
    case WSAEALREADY          : strcpy (Err,"WSAEALREADY        "); break;  
    case WSAENOTSOCK          : strcpy (Err,"WSAENOTSOCK        "); break;  
    case WSAEDESTADDRREQ      : strcpy (Err,"WSAEDESTADDRREQ    "); break;  
    case WSAEMSGSIZE          : strcpy (Err,"WSAEMSGSIZE        "); break;  
    case WSAEPROTOTYPE        : strcpy (Err,"WSAEPROTOTYPE      "); break;  
    case WSAENOPROTOOPT       : strcpy (Err,"WSAENOPROTOOPT     "); break;  
    case WSAEPROTONOSUPPORT   : strcpy (Err,"WSAEPROTONOSUPPORT "); break;  
    case WSAESOCKTNOSUPPORT   : strcpy (Err,"WSAESOCKTNOSUPPORT "); break;  
    case WSAEOPNOTSUPP        : strcpy (Err,"WSAEOPNOTSUPP      "); break;  
    case WSAEPFNOSUPPORT      : strcpy (Err,"WSAEPFNOSUPPORT    "); break;  
    case WSAEAFNOSUPPORT      : strcpy (Err,"WSAEAFNOSUPPORT    "); break;  
    case WSAEADDRINUSE        : strcpy (Err,"WSAEADDRINUSE      "); break;  
    case WSAEADDRNOTAVAIL     : strcpy (Err,"WSAEADDRNOTAVAIL   "); break;  
    case WSAENETDOWN          : strcpy (Err,"WSAENETDOWN        "); break;  
    case WSAENETUNREACH       : strcpy (Err,"WSAENETUNREACH     "); break;  
    case WSAENETRESET         : strcpy (Err,"WSAENETRESET       "); break;  
    case WSAECONNABORTED      : strcpy (Err,"WSAECONNABORTED    "); break;  
    case WSAECONNRESET        : strcpy (Err,"WSAECONNRESET      "); break;  
    case WSAENOBUFS           : strcpy (Err,"WSAENOBUFS         "); break;  
    case WSAEISCONN           : strcpy (Err,"WSAEISCONN         "); break;  
    case WSAENOTCONN          : strcpy (Err,"WSAENOTCONN        "); break;  
    case WSAESHUTDOWN         : strcpy (Err,"WSAESHUTDOWN       "); break;  
    case WSAETOOMANYREFS      : strcpy (Err,"WSAETOOMANYREFS    "); break;  
    case WSAETIMEDOUT         : strcpy (Err,"WSAETIMEDOUT       "); break;  
    case WSAECONNREFUSED      : strcpy (Err,"WSAECONNREFUSED    "); break;  
    case WSAELOOP             : strcpy (Err,"WSAELOOP           "); break;  
    case WSAENAMETOOLONG      : strcpy (Err,"WSAENAMETOOLONG    "); break;  
    case WSAEHOSTDOWN         : strcpy (Err,"WSAEHOSTDOWN       "); break;  
    case WSAEHOSTUNREACH      : strcpy (Err,"WSAEHOSTUNREACH    "); break;  
    case WSAENOTEMPTY         : strcpy (Err,"WSAENOTEMPTY       "); break;  
    case WSAEPROCLIM          : strcpy (Err,"WSAEPROCLIM        "); break;  
    case WSAEUSERS            : strcpy (Err,"WSAEUSERS          "); break;  
    case WSAEDQUOT            : strcpy (Err,"WSAEDQUOT          "); break;  
    case WSAESTALE            : strcpy (Err,"WSAESTALE          "); break;  
    case WSAEREMOTE           : strcpy (Err,"WSAEREMOTE         "); break;  
    case WSAEDISCON           : strcpy (Err,"WSAEDISCON         "); break;  
    case WSASYSNOTREADY       : strcpy (Err,"WSASYSNOTREADY     "); break;  
    case WSAVERNOTSUPPORTED   : strcpy (Err,"WSAVERNOTSUPPORTED "); break;  
    case WSANOTINITIALISED    : strcpy (Err,"WSANOTINITIALISED  "); break;  
    case WSAHOST_NOT_FOUND    : strcpy (Err,"WSAHOST_NOT_FOUND  "); break;  
    case WSATRY_AGAIN         : strcpy (Err,"WSATRY_AGAIN       "); break;  
    case WSANO_RECOVERY       : strcpy (Err,"WSANO_RECOVERY     "); break;  
    case WSANO_DATA           : strcpy (Err,"WSANO_DATA         "); break;  
    default:
    strcpy (Err,"Unknown Error");
  }
}
            

//end of file