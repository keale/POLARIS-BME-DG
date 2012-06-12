//
// help functions for adressing the fastmcd.sys driver
//
// 
// copyright by FAST ComTec GmbH, Grünwalder Weg 28a, 82041 Oberhaching
//
#include "stdafx.h"


#include <windows.h>
//#include "struct.h"

#ifdef WINDOWSNT
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <winioctl.h>

//#include "fmcddev.h"
//#include "mcdioctl.h"

SHORT SeekRegDevMCD(USHORT cnt);

int opendeviceMCD(PMCDID pId)
{
  int j;
	CHAR DevNumBuffer[MAX_PATH],DevNameBuffer[MAX_PATH];
	USHORT cnt;

  cnt = (USHORT)pId->Port;
  j=SeekRegDevMCD(cnt);
	if (j==-1)
	{
    (*pId).hBrd = INVALID_HANDLE_VALUE;
		return (-1);
	}

	wsprintf(DevNumBuffer,"%d",j+1);
  lstrcpy(DevNameBuffer,"\\\\.\\McdDev");
	lstrcat(DevNameBuffer,DevNumBuffer);
  pId->hBrd = CreateFile(  DevNameBuffer,
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);
//              0,
//              TRUE,
//              NULL,
//              OPEN_EXISTING,
//              0,
//              NULL);
	
  if (pId->hBrd==INVALID_HANDLE_VALUE)
    return (-2);

	return 0;
}

void closedeviceMCD(PMCDID pId)
{
  if (pId->hBrd) CloseHandle(pId->hBrd);
}

// -1, failed to access registry_base
// i, McdDevi, i=1..8
SHORT SeekRegDevMCD(USHORT cnt)
{
	HKEY hkdd;
	LONG lRes;
	BYTE RegDataBuffer[MAX_PATH];  

	CHAR ParDataBuffer[MAX_PATH];
	CHAR TempBuffer[MAX_PATH];
	DWORD RegDataTypes=MAX_PATH+1,NumofSubKeys;
	CHAR DevNumBuffer[MAX_PATH];
	CHAR DevPathBuffer[MAX_PATH];
	unsigned i=0;

	CHAR DRIVER_REGISTRY_BASE[MAX_PATH];
	OSVERSIONINFO version;

    // must set size of structure
    version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        // get version data
    GetVersionEx(&version);

    switch(version.dwPlatformId)
    {
        case VER_PLATFORM_WIN32_NT: //Windows NT
                // Uses fastmcd.sys driver
            lstrcpy(DRIVER_REGISTRY_BASE,"SYSTEM\\CurrentControlSet\\Services\\fastmcd");
            break;
        case VER_PLATFORM_WIN32_WINDOWS ://Windows95
                // Uses fastmcd fastmcdX.vxd
            lstrcpy(DRIVER_REGISTRY_BASE,"SYSTEM\\CurrentControlSet\\Services\\Class\\fastmcd");
            break;
		default:
			lstrcpy(DRIVER_REGISTRY_BASE,"");
    }   


	wsprintf(ParDataBuffer,"%x",cnt);
	// Open fastmcd Key
	lRes=RegOpenKeyEx(	HKEY_LOCAL_MACHINE,
						DRIVER_REGISTRY_BASE,
						0,
						KEY_READ,
						&hkdd);
	if (lRes!=ERROR_SUCCESS) return ((SHORT)-1);

	// Find Number of Drivers
//  RegQueryInfoKey(hkdd,NULL,NULL,NULL,&NumofSubKeys,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  NumofSubKeys=8;
  for (i=0;i<NumofSubKeys;i++)
	{
		// Open individial device Keys
		lstrcpy(DevPathBuffer,DRIVER_REGISTRY_BASE);
    //lstrcat(DevPathBuffer,"\\WinRTdev");
    lstrcat(DevPathBuffer,"\\Parameters\\fastmcd");
		wsprintf(DevNumBuffer,"%d",i);
		lstrcat(DevPathBuffer,DevNumBuffer);
		if (RegOpenKeyEx(	HKEY_LOCAL_MACHINE,
						DevPathBuffer,
						0,
						KEY_READ,
						&hkdd) != ERROR_SUCCESS) return ((SHORT)-1);
		RegQueryValueEx(hkdd,"IoPortAddress",0,NULL,RegDataBuffer,&RegDataTypes);
		wsprintf(TempBuffer,"%x",*(UINT *)RegDataBuffer);
		if(lstrcmp(TempBuffer,ParDataBuffer)==0)
			break;
	}
	RegCloseKey(hkdd);
	return(i);
}

int inb(PMCDID pId, USHORT Port, UCHAR *CharVal)
{
	LONG IoctlCode;
	ULONG DataLength;
	BOOL IoResult;
	ULONG DataReturned;
	long lPort = Port;

	IoctlCode = IOCTL_MCD_READ_PORT_UCHAR;
	DataLength = sizeof(UCHAR);

	IoResult = DeviceIoControl(
					pId->hBrd,
					IoctlCode,
					&lPort,
					sizeof(lPort),
					CharVal,
					DataLength,
					&DataReturned,
					NULL);
	
	if(IoResult)
		return(0);
	else
		return(-1);
}


int inw(PMCDID pId, USHORT Port, USHORT *ShortVal)
{
	LONG IoctlCode;
	ULONG DataLength;
	BOOL IoResult;
	ULONG DataReturned;
	long lPort = Port;

	IoctlCode = IOCTL_MCD_READ_PORT_USHORT;
	DataLength = sizeof(USHORT);

	IoResult = DeviceIoControl(
					pId->hBrd,
					IoctlCode,
					&lPort,
					sizeof(lPort),
					ShortVal,
					DataLength,
					&DataReturned,
					NULL);
	
	if(IoResult)
		return(0);
	else
		return(-1);
}


int outb(PMCDID pId, USHORT Port, UCHAR CharVal)
{
	LONG IoctlCode;
	FASTMCD_WRITE_BUF Buffer;
	ULONG BufferSize;
	BOOL IoResult;
	ULONG DataReturned;

	IoctlCode = IOCTL_MCD_WRITE_PORT_UCHAR;
	Buffer.PortNumber = Port;
	Buffer.CharData = CharVal;
	BufferSize = sizeof(ULONG) + sizeof(UCHAR);
	IoResult = DeviceIoControl(
					pId->hBrd,
					IoctlCode,
					&Buffer,
					BufferSize,
					NULL,
					0,
					&DataReturned,
					NULL);
	
	if(IoResult)
		return(0);
	else
		return(-1);
}


int outw(PMCDID pId, USHORT Port, USHORT ShortVal)
{
	LONG IoctlCode;
	FASTMCD_WRITE_BUF Buffer;
	ULONG BufferSize;
	BOOL IoResult;
	ULONG DataReturned;

	IoctlCode = IOCTL_MCD_WRITE_PORT_USHORT;
	Buffer.PortNumber = Port;
	Buffer.ShortData = ShortVal;
	BufferSize = sizeof(ULONG) + sizeof(USHORT);

	IoResult = DeviceIoControl(
					pId->hBrd,
					IoctlCode,
					&Buffer,
					BufferSize,
					NULL,
					0,
					&DataReturned,
					NULL);
	
	if(IoResult)
		return(0);
	else
		return(-1);
}


#endif
