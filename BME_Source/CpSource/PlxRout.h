/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 DG 135 driver
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






#include "PlxApi.h"
#include "Reg9030.h"
#include "PlxTypes.h"
#include "BME_Net.h"



#define  SDK3p2
#undef  SDK6p4

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	union
	{
		U32	Value;
		struct
		{
			U16 LowWord;
			U16 HighWord;
		};
		struct
		{
			U8 Byte0;
			U8 Byte1;
			U8 Byte2;
			U8 Byte3;
		};
	};
} Register32;


typedef struct
{
	unsigned long DG_Product;
	long SlotNumber;
	long BusNumber;
	long VendorId;
	long DeviceId;
	long Master;
	long LineMaster[8];
	char ip_address[40];
	BOOL OrderUpwards;
	BOOL Selected;
	BOOL DeviceOpen;
#ifdef SDK3p2
	HANDLE	h_Delgen;
#else
	PLX_DEVICE_OBJECT Device;
#endif
} DelgenType;

//DelgenType PciDelgen[20];

#define PlxVendorID					0x10b5
#define PlxDeviceID					0x3001
#define PlxDeviceID_ini			0x9030
#define SubSystemVendorID		0x10b5
#define SubSystemDeviceID		0x2739
//#define SubSystemDeviceID		0x9030
#define BME_ID							0x8b09b1
//#define BME_ID							0xffffffff



	RETURN_CODE BmeDelgenWrite(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen);
	RETURN_CODE BmeDelgenRead(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen);
	RETURN_CODE BmeDelgenDeviceOpen(long BusNumber, long SlotNumber, DelgenType* p_PciDelgen);
	RETURN_CODE BmeDelgenDeviceClose(DelgenType* p_PciDelgen);
	RETURN_CODE BmeDelgenNumberPciCards(U32* p_ReqLimit, char * p_IpAddr);
	RETURN_CODE BmeDelgenDeviceFind(DelgenType* p_PciDelgen, int NoCard);
	U32 BmeDelgenReadSubVendorID(DelgenType* p_PciDelgen, RETURN_CODE* p_rc);
	U32 BmeDelgenVpdRead(DelgenType* p_PciDelgen, U32 Offset, RETURN_CODE* p_rc);
	RETURN_CODE BmeDelgenSerialEepromRead(DelgenType* p_PciDelgen, U32* p_Buffer, U32 Size);
	RETURN_CODE BmeDelgenSerialEepromWrite(DelgenType* p_PciDelgen, U32* p_Buffer, U32 Size);

	RETURN_CODE BmeDelgenWrite_IP(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen, char * p_IpAddr);
	RETURN_CODE BmeDelgenRead_IP(U32 PciAddress, U32* p_PciData, DelgenType* p_PciDelgen, char *p_IpAddr);
	RETURN_CODE BmeDelgenDeviceOpen_IP(long BusNumber, long SlotNumber, DelgenType* p_PciDelgen, char *p_IpAddr);
	RETURN_CODE BmeDelgenDeviceClose_IP(DelgenType* p_PciDelgen, char *p_IpAddr);
	RETURN_CODE BmeDelgenNumberPciCards_IP(U32* p_ReqLimit, char *p_IpAddr);
	RETURN_CODE BmeDelgenDeviceFind_IP(DelgenType* p_PciDelgen, U8 NoCard, char *p_IpAddr);
	U32 BmeDelgenReadSubVendorID_IP(DelgenType* p_PciDelgen, RETURN_CODE* p_rc, char *p_IpAddr);
	U32 BmeDelgenVpdRead_IP(DelgenType* p_PciDelgen, U32 Offset, RETURN_CODE* p_rc, char *p_IpAddr);

	int IsConnected(char *p_IpAddr, int *Index);
	int ConnectToServer(char *p_IpAddr, int *Index);
//	int DisconnectServer(char *p_IpAddr);
	int DisconnectServer(int Index);

#ifdef __cplusplus
}
#endif