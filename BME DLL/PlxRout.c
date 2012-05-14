/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 String Routines
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    5. January 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

//#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\BME_G0x\PlxRout.h"


/* Error Variable for network functions */
char Err_Buf[ERR_SIZE];
static NetCfg strct_NetCfg[ANZ_NET_CONNECTS];

/*----------------------------------------------------------------------------------------*/


RETURN_CODE BmeDelgenWrite(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen)
{
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		return PlxBusIopWrite((p_PciDelgen->h_Delgen), IopSpace0, PciAddress, FALSE, p_PciData, 4, BitSize32);
#else
		return PlxPci_PciBarSpaceWrite(&(p_PciDelgen->Device), 2, PciAddress, p_PciData, 4, BitSize32, FALSE);
#endif
	}
	else
		return BmeDelgenWrite_IP(PciAddress, p_PciData, p_PciDelgen, &(p_PciDelgen->ip_address[0]));
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function sends its parameter to the server via
 *        an open socket and waits for the return value! 
 *
 * param[in]: U32 PciAddress, write address in th server Delgen.
 * param[in]: U32 p_PciDate, value write to the servers Delgen.
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.
 *
*/

RETURN_CODE BmeDelgenWrite_IP(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen, char * p_IpAddr)
{
	char command;
	RETURN_CODE rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind))
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
		//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenWrite;
	buf_len++;

	memcpy(&send_buffer[buf_len], &PciAddress, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_PciData, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	send_len = send(strct_NetCfg[Ind].sock, send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if(((sizeof(command) + sizeof(RETURN_CODE)) != buf_len) || (command != E_BmeDelgenWrite))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			memcpy((char *) &rc, &receive_buffer[1], sizeof(RETURN_CODE));
		}
	}

	return(rc);
}
				
RETURN_CODE BmeDelgenRead(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen)
{
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		return PlxBusIopRead((p_PciDelgen->h_Delgen), IopSpace0, PciAddress, FALSE, p_PciData, 4, BitSize32);
#else
		return PlxPci_PciBarSpaceRead(&(p_PciDelgen->Device), 2, PciAddress, p_PciData, 4, BitSize32, FALSE);
#endif
	}
	else
		return BmeDelgenRead_IP(PciAddress, p_PciData, p_PciDelgen, &(p_PciDelgen->ip_address[0]));
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function sends its parameter to the server via
 *        an open socket and waits for the return value! 
 *
 * param[in]: U32 PciAddress, read address in th server Delgen.
 * param[in]: U32 p_PciDate, read value returned  from the servers Delgen.
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.       
 *        
*/

RETURN_CODE BmeDelgenRead_IP(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen, char * p_IpAddr)
{
	char command;
	RETURN_CODE rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenRead;
	buf_len++;

	memcpy(&send_buffer[buf_len], &PciAddress, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_PciData, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	send_len = send(strct_NetCfg[Ind].sock, (char *) send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if(((sizeof(command) + sizeof(RETURN_CODE) + sizeof(U32)) != buf_len) || (command != E_BmeDelgenRead))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *) &rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len+= sizeof(RETURN_CODE);

			memcpy((char *) p_PciData, &receive_buffer[buf_len], sizeof(U32));
		}
	}

	return rc;
}


RETURN_CODE BmeDelgenDeviceOpen(long BusNumber, long SlotNumber, DelgenType* p_PciDelgen)
{
	RETURN_CODE     rc;
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		DEVICE_LOCATION PciDevice;
		PciDevice.BusNumber = (U32)BusNumber;
		PciDevice.SlotNumber = (U32)SlotNumber;
		PciDevice.VendorId = (U32)PlxVendorID;
		PciDevice.DeviceId = (U32)PlxDeviceID;
		PciDevice.SerialNumber[0] = '\0';
		rc = PlxPciDeviceOpen(&PciDevice, &(p_PciDelgen->h_Delgen));
		if (rc == ApiSuccess)
			p_PciDelgen->DeviceOpen = TRUE;
		return rc;
#else
		PLX_DEVICE_KEY    DeviceKey;
		U8                BarCnt;
		rc = ApiInvalidIndex;

		memset( &(p_PciDelgen->Device), PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_OBJECT));
		memset( &DeviceKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY) );

		DeviceKey.DeviceId = (U16)PlxDeviceID;
		DeviceKey.VendorId = (U16)PlxVendorID;
		DeviceKey.bus      = (U8)BusNumber;
		DeviceKey.slot     = (U8)SlotNumber;


		if(PlxPci_DeviceOpen(&DeviceKey, &(p_PciDelgen->Device)) == ApiSuccess)
		{
			for(BarCnt = 0; BarCnt < PCI_NUM_BARS_TYPE_00; BarCnt++)
			{
				rc = PlxPci_PciBarProperties(&(p_PciDelgen->Device), BarCnt, &(p_PciDelgen->Device.PciBar[BarCnt]));
			}
			p_PciDelgen->DeviceOpen = TRUE;
		}
		return rc;
#endif
	}
	else
		return BmeDelgenDeviceOpen_IP(BusNumber, SlotNumber, p_PciDelgen, &(p_PciDelgen->ip_address[0]));
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function sends its parameter to the server via
 *        an open socket and opens a Delgen on the PCI-Bus! 
 *
 * param[in]: long BusNumber, PCI-BusNumber.
 * param[in]: long SlotNumber, PCI-SlotNumber.
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.       
 *
*/

RETURN_CODE BmeDelgenDeviceOpen_IP(long BusNumber, long SlotNumber, DelgenType* p_PciDelgen, char * p_IpAddr)
{
	char command;
	RETURN_CODE rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenDeviceOpen;
	buf_len++;

	memcpy(&send_buffer[buf_len], &BusNumber, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], &SlotNumber, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	send_len = send(strct_NetCfg[Ind].sock, (char *) send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(DelgenType) != buf_len) || (command != E_BmeDelgenDeviceOpen))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *)&rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len+= sizeof(RETURN_CODE);

			memcpy((char *)p_PciDelgen, &receive_buffer[buf_len], sizeof(DelgenType));
		}
	}

	return rc;
}

RETURN_CODE BmeDelgenDeviceClose(DelgenType* p_PciDelgen)
{
	RETURN_CODE     rc;
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		rc = PlxPciDeviceClose((p_PciDelgen->h_Delgen));
#else
		rc = PlxPci_DeviceClose(&(p_PciDelgen->Device));
#endif
	}
	else
		rc = BmeDelgenDeviceClose_IP(p_PciDelgen, &(p_PciDelgen->ip_address[0]));
	if (rc == ApiSuccess)
		p_PciDelgen->DeviceOpen = FALSE;
	return rc;
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function sends its parameter to the server via
 *        an open socket and closes a Delgen on the PCI-Bus! 
 *
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.       
 *        
*/

RETURN_CODE BmeDelgenDeviceClose_IP(DelgenType* p_PciDelgen, char * p_IpAddr)
{
	char command;
	RETURN_CODE     rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenDeviceClose;
	buf_len++;

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	send_len = send(strct_NetCfg[Ind].sock, (char *) send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(DelgenType) != buf_len) || (command != E_BmeDelgenDeviceClose))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *) &rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len+= sizeof(RETURN_CODE);

			memcpy((char *)p_PciDelgen, &receive_buffer[buf_len], sizeof(DelgenType));
		}
	}
	return rc;
}

RETURN_CODE BmeDelgenNumberPciCards(U32* p_ReqLimit, char* p_IpAddr)
{
	if (*p_IpAddr == 0)
	{
#ifdef SDK3p2
		DEVICE_LOCATION PciDevice;
		PciDevice.BusNumber = (U32)-1;
		PciDevice.SlotNumber = (U32)-1;
		PciDevice.VendorId = (U32)-1;
		PciDevice.DeviceId = (U32)-1;
		PciDevice.SerialNumber[0] = '\0';
		*p_ReqLimit = FIND_AMOUNT_MATCHED;
		return PlxPciDeviceFind(&PciDevice, p_ReqLimit);
#else
		RETURN_CODE       rc;
		PLX_DEVICE_KEY    DeviceKey;
		U32								TestCard;
		TestCard = 0;
		*p_ReqLimit = (U32)-1;
		rc = ApiSuccess;
		while (rc == ApiSuccess)
		{
			memset( &DeviceKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY) );
			DeviceKey.DeviceId = (U16)PlxDeviceID;
			DeviceKey.VendorId = (U16)PlxVendorID;
			rc = PlxPci_DeviceFind(&DeviceKey, (U8)TestCard);
			if (rc == ApiSuccess)
			{
				*p_ReqLimit = (U32)TestCard;
				TestCard++;
			}
		}
		return ApiSuccess;
#endif
	}
	else
		return BmeDelgenNumberPciCards_IP(p_ReqLimit, p_IpAddr);
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function returns the number of installed Delgen on the Remote Computer! 
 *
 * param[in]: U32 p_ReqLimit,  number Delgen installed.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.
 *
*/

RETURN_CODE BmeDelgenNumberPciCards_IP(U32* p_ReqLimit, char * p_IpAddr)
{
	char command;
	RETURN_CODE rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			return(rc);
		}
	}

	*p_ReqLimit = (U32)-1;

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenNumberPciCards;
	buf_len++;

	memcpy(&send_buffer[buf_len], p_ReqLimit, sizeof(U32));
	buf_len += sizeof(U32);

	send_len = send(strct_NetCfg[Ind].sock, (char *)send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(U32) != buf_len) || (command != E_BmeDelgenNumberPciCards))
		{
				Error = WSAGetLastError();
				PrintWSA((int) Error, Err_Buf);
				rc = ApiFailed;
		}
		else
		{
			buf_len = 1;
			memcpy((char *) &rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len+= sizeof(RETURN_CODE);

			memcpy(p_ReqLimit, &receive_buffer[buf_len], sizeof(U32));
			buf_len+= sizeof(U32);
		}
	}

	return rc;
}

RETURN_CODE BmeDelgenDeviceFind(DelgenType* p_PciDelgen, int NoCard)
{
	RETURN_CODE			rc;	
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		DEVICE_LOCATION PciDevice;
		U32							ReqLimit;
		PciDevice.BusNumber = (U32)p_PciDelgen->BusNumber;
		PciDevice.SlotNumber = (U32)p_PciDelgen->SlotNumber;
		PciDevice.VendorId = (U32)-1;
		PciDevice.DeviceId = (U32)-1;
		PciDevice.SerialNumber[0] = '\0';
		ReqLimit = (U32)NoCard;
		rc = PlxPciDeviceFind(&PciDevice, &ReqLimit);
		if (rc == ApiSuccess)
		{
			p_PciDelgen->BusNumber = (long)PciDevice.BusNumber;
			p_PciDelgen->SlotNumber = (long)PciDevice.SlotNumber;
			p_PciDelgen->VendorId = (long)PciDevice.VendorId;
			p_PciDelgen->DeviceId = (long)PciDevice.DeviceId;
		}
#else
		PLX_DEVICE_KEY    DeviceKey;
		memset( &DeviceKey, PCI_FIELD_IGNORE, sizeof(PLX_DEVICE_KEY) );
		DeviceKey.bus = (U8)p_PciDelgen->BusNumber;
		DeviceKey.slot = (U8)p_PciDelgen->SlotNumber;
		rc = PlxPci_DeviceFind(&DeviceKey, (U8)NoCard);
		if (rc == ApiSuccess)
		{
			p_PciDelgen->BusNumber = (long)DeviceKey.bus;
			p_PciDelgen->SlotNumber = (long)DeviceKey.slot;
			p_PciDelgen->VendorId = (long)DeviceKey.VendorId;
			p_PciDelgen->DeviceId = (long)DeviceKey.DeviceId;
		}
#endif
	}
	else
		return BmeDelgenDeviceFind_IP(p_PciDelgen, (U8)NoCard, &(p_PciDelgen->ip_address[0]));
	return rc;
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function searchs on the server the NoCard installed on the Computer! 
 *
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: int NoCard,  number of Delgen.
 * param[in]: string IP-Address of the server.
 * return: RETURN_CODE rc, return value of the server function.       
 *        
*/

RETURN_CODE BmeDelgenDeviceFind_IP(DelgenType* p_PciDelgen, U8 NoCard, char * p_IpAddr)
{
	char command;
	RETURN_CODE      rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenDeviceFind;
	buf_len++;

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	memcpy(&send_buffer[buf_len], &NoCard, sizeof(U8));
	buf_len += sizeof(U8);

	send_len = send(strct_NetCfg[Ind].sock, (char *)send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{	
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(DelgenType) != buf_len) || (command != E_BmeDelgenDeviceFind))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *) &rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len += sizeof(RETURN_CODE);

			memcpy((char *)p_PciDelgen, &receive_buffer[buf_len], sizeof(DelgenType));
			buf_len += sizeof(DelgenType);
		}
	}

	return rc;
}

U32 BmeDelgenReadSubVendorID(DelgenType* p_PciDelgen, RETURN_CODE* p_rc)
{
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		return PlxPciConfigRegisterRead((U32)p_PciDelgen->BusNumber, (U32)p_PciDelgen->SlotNumber, 
																					CFG_SUB_VENDOR_ID, p_rc);
#else
		return PlxPci_PciRegisterRead((U8)p_PciDelgen->BusNumber, (U8)p_PciDelgen->SlotNumber, 0,
																					CFG_SUB_VENDOR_ID, p_rc);
#endif
	}
	else
		return BmeDelgenReadSubVendorID_IP(p_PciDelgen, p_rc, &(p_PciDelgen->ip_address[0]));
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function reads the sub vendor id of the selected Delgen on the server! 
 *
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: RETURN_CODE* p_rc,  rc error code.
 * param[in]: string IP-Address of the server.
 * return: U32, return Sub vendor id.       
 *        
*/

U32 BmeDelgenReadSubVendorID_IP(DelgenType* p_PciDelgen, RETURN_CODE* p_rc, char * p_IpAddr)
{
	char command;
	U32 rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenReadSubVendorID;
	buf_len++;

	memcpy(&send_buffer[buf_len], p_rc, sizeof(RETURN_CODE));
	buf_len += sizeof(RETURN_CODE);

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	send_len = send(strct_NetCfg[Ind].sock, (char *) send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(DelgenType) + sizeof(U32) != buf_len) || (command != E_BmeDelgenReadSubVendorID))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *)p_rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len += sizeof(RETURN_CODE);

			memcpy((char *)p_PciDelgen, &receive_buffer[buf_len], sizeof(DelgenType));
			buf_len += sizeof(DelgenType);

			memcpy((char *)&rc, &receive_buffer[buf_len], sizeof(U32));
		}
	}

	return rc;
}

U32 BmeDelgenVpdRead(DelgenType* p_PciDelgen, U32 Offset, RETURN_CODE* p_rc)
{
	if (p_PciDelgen->ip_address[0] == 0)
	{
#ifdef SDK3p2
		return PlxVpdRead(p_PciDelgen->h_Delgen, Offset, p_rc);
#else
		Register32 result,sw;
		sw.Value = PlxPci_VpdRead(&(p_PciDelgen->Device), (U16)Offset, p_rc);
		result.HighWord = sw.LowWord;
		result.LowWord = sw.HighWord;
		return result.Value;
#endif
	}
	else
		return BmeDelgenVpdRead_IP(p_PciDelgen, Offset, p_rc, &(p_PciDelgen->ip_address[0]));
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function reads the VpdRegister at Offset of the selected Delgen on the server! 
 *
 * param[in]: DelgenType* p_PciDelgen,  PCI-Card identifier.
 * param[in]: U32 Offset,  PCI-Addr Offset.
 * param[in]: RETURN_CODE* p_rc,  rc error code.
 * param[in]: string IP-Address of the server.
 * return: U32, return Sub vendor id.       
 *        
*/

U32 BmeDelgenVpdRead_IP(DelgenType* p_PciDelgen, U32 Offset, RETURN_CODE* p_rc, char * p_IpAddr)
{
	char command;
	U32 rc;
	int Ind;
	long Error;
	long send_len;
	long buf_len;
	char receive_buffer[RCVBUFSIZE];
	char send_buffer[SENDBUFSIZE];

	rc = ApiFailed;

	if(IsConnected(p_IpAddr, &Ind) < 0)
	{
		Error = ConnectToServer(p_IpAddr, &Ind);
		if(Error)
		{
			//TODO errorhandling
			return(rc);
		}
	}

	buf_len = 0;
	send_buffer[buf_len] = E_BmeDelgenVpdRead;
	buf_len++;

	memcpy(&send_buffer[buf_len], p_PciDelgen, sizeof(DelgenType));
	buf_len += sizeof(DelgenType);

	memcpy(&send_buffer[buf_len], &Offset, sizeof(U32));
	buf_len += sizeof(U32);

	memcpy(&send_buffer[buf_len], p_rc, sizeof(RETURN_CODE));
	buf_len += sizeof(RETURN_CODE);

	send_len = send(strct_NetCfg->sock, (char *) send_buffer, buf_len, 0);

	if(send_len != buf_len)
	{
		Error = WSAGetLastError();
		PrintWSA((int) Error, Err_Buf);
	}
	else
	{
		buf_len = recv(strct_NetCfg[Ind].sock, receive_buffer, RCVBUFSIZE, 0);
		command = receive_buffer[0];

		if((sizeof(command) + sizeof(RETURN_CODE) + sizeof(DelgenType) + sizeof(U32) != buf_len) || (command != E_BmeDelgenVpdRead))
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			buf_len = 1;
			memcpy((char *) p_rc, &receive_buffer[buf_len], sizeof(RETURN_CODE));
			buf_len += sizeof(RETURN_CODE);

			memcpy((char *) p_PciDelgen, &receive_buffer[buf_len], sizeof(DelgenType));
			buf_len += sizeof(DelgenType);

			memcpy((char *)&rc, &receive_buffer[buf_len], sizeof(U32));
		}
	}
	return rc;
}

RETURN_CODE BmeDelgenSerialEepromRead(DelgenType* p_PciDelgen, U32* p_Buffer, U32 Size)
{
#ifdef SDK3p2
	return PlxSerialEepromRead((p_PciDelgen->h_Delgen), Eeprom93CS66, p_Buffer, Size);
#else
	RETURN_CODE			rc;
	Register32 result,sw;
	int i1;
	for (i1 = 48; i1 < 52; i1++)
	{
		rc = PlxPci_EepromReadByOffset(&(p_PciDelgen->Device), (U16)(i1 * 4), &(sw.Value));
		result.HighWord = sw.LowWord;
		result.LowWord = sw.HighWord;
		*(p_Buffer + i1) = result.Value;
	}
	return rc;
#endif
}

RETURN_CODE BmeDelgenSerialEepromWrite(DelgenType* p_PciDelgen, U32* p_Buffer, U32 Size)
{
#ifdef SDK3p2
	return PlxSerialEepromWrite((p_PciDelgen->h_Delgen), Eeprom93CS66, p_Buffer, Size);
#else
	RETURN_CODE			rc;
	Register32 result,sw;
	int i1;
	for (i1 = 48; i1 < 52; i1++)
	{
		sw.Value = *(p_Buffer + i1);
		result.HighWord = sw.LowWord;
		result.LowWord = sw.HighWord;
		rc = PlxPci_EepromWriteByOffset(&(p_PciDelgen->Device), (U16)(i1 * 4), (U32)(result.Value));
	}
	return rc;
#endif
}


/*----------------------------------------------------------------------------------------*/
/**
 * @brief this function checks if a connction to this server has been already established. 
 *

 * param[in]: char *p_IpAddr, IP-Address in char buffer.
 * param[in]: int *p_ConnectNum, array number if connected and return code 0 .
 * return: int Index >= 0 if in strct_NetCfg array else -1.
 *
*/
int IsConnected(char *p_IpAddr, int *Index)
{
	struct sockaddr_in addr;
	int i;

	addr.sin_addr.s_addr=inet_addr(p_IpAddr); //Ip Address of the remote Server

	for(i = 0; i < ANZ_NET_CONNECTS; i++)
	{
		if((strct_NetCfg[i].server_addr.sin_addr.s_addr == addr.sin_addr.s_addr) &&
				(strct_NetCfg[i].IsConnected == 1))
		{
			*Index = i;
			return i;
		}
	}

	return -1;
}

/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function connects the client to the server. 
 *

 * param[in]: char *p_IpAddr, IP-Address in char buffer.
 * param[in]: int *p_ConnectNum, used index of strct_NetCfg array.
 * return: int Error: code 0 if connect OK.
 *
*/
int ConnectToServer(char *p_IpAddr, int *p_ConnectNum)
{
	struct sockaddr_in addr;
	int i;
	int Error;

	Error = 0;

	addr.sin_addr.s_addr=inet_addr(p_IpAddr); //IP Address of the remote Server

	for(i = 0; i < ANZ_NET_CONNECTS; i++)
	{
		if(strct_NetCfg[i].server_addr.sin_addr.s_addr == 0)
		{
			*p_ConnectNum = i;
			break;
		}
	}

	if(i < ANZ_NET_CONNECTS)
	{
		WORD wVersionRequested;
		WSADATA wsaData;

		wVersionRequested = MAKEWORD (1, 1); 

		if (WSAStartup (wVersionRequested, &wsaData) != 0)
		{
			Error = WSAGetLastError();
			PrintWSA((int) Error, Err_Buf);
		}
		else
		{
			strct_NetCfg[i].sock = socket( AF_INET, SOCK_STREAM, 0 );
    
			if(strct_NetCfg[i].sock < 0)
			{
				Error = WSAENOTSOCK;
			}
			else
			{
				memset(&strct_NetCfg[i].server_addr, 0, sizeof (strct_NetCfg[i].server_addr));
				memcpy(&strct_NetCfg[i].server_addr.sin_addr, &addr.sin_addr, sizeof(addr.sin_addr));
				/* IPv4-Connection */
				strct_NetCfg[i].server_addr.sin_family = AF_INET;
				/* Portnumber*/
				strct_NetCfg[i].server_addr.sin_port = htons(C_PORT);

				if(connect(strct_NetCfg[i].sock,(struct sockaddr*)&strct_NetCfg[i].server_addr,sizeof(strct_NetCfg[i].server_addr)) <0)
				{
					strct_NetCfg[i].IsConnected = 0;
					Error = WSAGetLastError();
					PrintWSA((int) Error, Err_Buf);
				}
				else
				{
					Error = 0;
					strct_NetCfg[i].IsConnected = 1;
				}
			}
		}
	}
	else
	{
		Error = -1;
	}

	return Error;
}

#if 0
/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function disconnects the client from the server. 
 *

 * param[in]: char *p_IpAddr, IP-Address in char buffer.
 * return: int Error: code 0 if connect OK.
 *
*/
int DisconnectServer(char *p_IpAddr)
{
	struct sockaddr_in addr;
	int i;
	int Error;

	Error = 0;

	addr.sin_addr.s_addr=inet_addr(p_IpAddr); //Ip Address of the remote Server

	for(i = 0; i < ANZ_NET_CONNECTS; i++)
	{
		if(strct_NetCfg[i].server_addr.sin_addr.s_addr == addr.sin_addr.s_addr)
		{
			break;
		}

		if(i < ANZ_NET_CONNECTS)
		{
			if(strct_NetCfg[i].IsConnected == 1)
			{
				Error = closesocket(strct_NetCfg[i].sock);
				strct_NetCfg[i].IsConnected = 0;

				/* Cleanup Winsock */
				Error = WSACleanup();
			}
		}
		else
		{
			Error = -1;
		}
	}

	return(Error);
}
#endif


/*----------------------------------------------------------------------------------------*/

/**
 * @brief this function disconnects the client from the server. 
 *

 * param[in]: int Index used index of strct_NetCfg array.
 * return: int Error: code 0 if connect OK.
 *
*/
int DisconnectServer(int Index)
{
	int Error;

	Error = 0;

	if(Index < ANZ_NET_CONNECTS)
	{
		if(strct_NetCfg[Index].IsConnected == 1)
		{
			Error = closesocket(strct_NetCfg[Index].sock);
			strct_NetCfg[Index].IsConnected = 0;

			/* Cleanup Winsock */
			Error = WSACleanup();
		}
	}
	else
	{
		Error = -1;
	}

	return(Error);
}

