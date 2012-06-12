// mcdioctl.h    Include file for the FAST ComTec MCD - Driver
//
// Define the IOCTL codes we will use.  The IOCTL code contains a command
// identifier, plus other information about the device, the type of access
// with which the file must have been opened, and the type of buffering.
//
// Copyright by FAST ComTec GmbH

// Device type           -- in the "User Defined" range."
#define MCD_TYPE 40002

// The IOCTL function codes from 0x800 to 0xFFF are for customer use.

#define IOCTL_MCD_READ_PORT_UCHAR \
    CTL_CODE( MCD_TYPE, 0x900, METHOD_BUFFERED, FILE_READ_ACCESS )

#define IOCTL_MCD_READ_PORT_USHORT \
    CTL_CODE( MCD_TYPE, 0x901, METHOD_BUFFERED, FILE_READ_ACCESS )

#define IOCTL_MCD_WRITE_PORT_UCHAR \
    CTL_CODE(MCD_TYPE,  0x910, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define IOCTL_MCD_WRITE_PORT_USHORT \
    CTL_CODE(MCD_TYPE,  0x911, METHOD_BUFFERED, FILE_WRITE_ACCESS)

typedef struct  _FASTMCD_WRITE_BUF {
    ULONG   PortNumber;     // Port # to write to
    union   {               // Data to be output to port 
        USHORT  ShortData;
        UCHAR   CharData;
		ULONG   Amount;		//Amount of data to be output
    };
}   FASTMCD_WRITE_BUF;


