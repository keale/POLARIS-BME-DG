/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Delay Generator driver
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    programmer:                Thorald Bergmann
    Version:                   V1.1
    Update:                    18. February 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/


#include <stdlib.h>         /* For _MAX_PATH definition */
#include <malloc.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
//#include "..\Spectra_BME\CommonDefinitions.h"
#include "DG_DLL_1.h"
#include "StringRout_C.h"



#define  WINDOWSNT
#undef  WINDOWS95
#undef  WINDOWS31



#ifdef WINDOWSNT
#include <stdlib.h>
#include <malloc.h>
#include <winioctl.h>

#include "..\BME_G0x\mcdioctl.h"
#include "..\BME_G0x\fmcddev.h"

#endif



BOOL WINAPI DllMain(HANDLE hModule, DWORD dwFunction, LPVOID lpNot)
{
	switch (dwFunction)
	{
		case DLL_PROCESS_ATTACH:
			p_Internal = NULL;
			NoDelayGenerators = 0;
			NumberPciDelayGenerators = 0;
			break;
		default:
			break;
	}
	return TRUE;
}

_declspec (dllexport) long CC Reserve_DG_Data(long NumberOfDelayGenerators)
{
	int i1;
	p_Internal = malloc(NumberOfDelayGenerators * sizeof(DG_InternalData));
	NoDelayGenerators = NumberOfDelayGenerators;
	for (i1 = 0; i1 < NoDelayGenerators; i1++) 
	{
		ResetRegisters(&((p_Internal + i1)->DelayGeneratorState));
		ResetControl(&((p_Internal + i1)->DelayControlState));
		(p_Internal + i1)->NtDriverInitialized = FALSE;
		(p_Internal + i1)->PciDelgen.DeviceOpen = FALSE;
		(p_Internal + i1)->h_DelayGenerator = NULL;
		(p_Internal + i1)->SlotNumber = -1;
		(p_Internal + i1)->BusNumber = -1;
		memset(&((p_Internal + i1)->ip_address), 0, (40 * sizeof(char)));
	}
	InitializeCalibrationConstants();
	return 0;
}

_declspec (dllexport) long CC Release_DG_Data()
{
	int i1;
	DG_InternalData* p_Present;
	RETURN_CODE			rc;
	if (p_Internal != NULL)
	{
		for (i1 = 0; i1 < NoDelayGenerators; i1++) 
		{
			p_Present = (p_Internal + i1);
			if (p_Present->PciDelgen.DeviceOpen)
			{
				rc = BmeDelgenDeviceClose(&(p_Present->PciDelgen));
		    //rc = PlxPciDeviceClose(p_Present->h_DelayGenerator);
				p_Present->NtDriverInitialized = FALSE;
				p_Present->h_DelayGenerator = NULL;
				p_Present->SlotNumber = -1;
				p_Present->BusNumber = -1;
				memset(&(p_Present->ip_address), 0, (40 * sizeof(char)));
			}
		}
	}
#ifdef WINDOWSNT
	if (p_Internal != NULL)
	{
		for (i1 = 0; i1 < NoDelayGenerators; i1++) 
		{
			p_Present = (p_Internal + i1);
			if (p_Present->NtDriverInitialized)
			{
				if (mcd2open[i1]) closedeviceMCD(&mcd2id[i1]);
				mcd2open[i1] = 0;
				p_Present->NtDriverInitialized = FALSE;
			}
		}
		free(p_Internal);
		p_Internal = NULL;
		NoDelayGenerators = 0;
	}
#else
	if (p_Internal != NULL)
	{
		free(p_Internal);
		p_Internal = NULL;
		NoDelayGenerators = 0;
	}
#endif
	return 0;
}

_declspec (dllexport) long CC Initialize_DG_BME(long base, long Product, long DG_Number)
{
	long BusNumber = -1;
	return Initialize_Bus_DG_BME(BusNumber, base, Product, DG_Number);
}

_declspec (dllexport) long CC Initialize_Bus_DG_BME(long BusNumber, long base, long Product, long DG_Number)
{
	char ip_address[40];
	memset(&(ip_address), 0, (40 * sizeof(char)));
	return Initialize_Ethernet_DG_BME(BusNumber, base, &(ip_address[0]), Product, DG_Number);
}

_declspec (dllexport) long CC Initialize_Ethernet_DG_BME(long BusNumber, long base, char* p_ip_address, long Product, long DG_Number)
{
	RETURN_CODE			rc;
	//DEVICE_LOCATION Device;
	char info[80];
	unsigned short cntrl,value;
	unsigned short i,adr1;
	unsigned long DG_Product;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	p_Present->DG_Product = Product;
	DG_Product = p_Present->DG_Product;
	switch (p_Present->DG_Product)
	{
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->base_address = 0x0;
		p_Present->SlotNumber = base;
		p_Present->BusNumber = BusNumber;
		memcpy(&(p_Present->ip_address), p_ip_address, (40 * sizeof(char)));
		memcpy(&(p_Present->PciDelgen.ip_address), p_ip_address, (40 * sizeof(char)));
		InitializeInternalData(p_Present);
		//Device.BusNumber = (U32)BusNumber;
		//Device.SlotNumber = (U32)base;
		//Device.VendorId = (U32)PlxVendorID;
		//Device.DeviceId = (U32)PlxDeviceID;
		//Device.SerialNumber[0] = '\0';
		//rc = PlxPciDeviceOpen(&Device, &(p_Present->h_DelayGenerator));
		rc = BmeDelgenDeviceOpen(BusNumber, base, &(p_Present->PciDelgen));
		if (rc != ApiSuccess)
			return (long)rc;
		break;
	default:
		p_Present->base_address = (unsigned short)base;
		InitializeInternalData(p_Present);
#ifdef WINDOWSNT
		if (!p_Present->NtDriverInitialized)
		{
			mcd2id[DG_Number].Port = (unsigned short)base;
			if (opendeviceMCD(&mcd2id[DG_Number])) 
			{
				//char txt[80];
				//sprintf(txt,"Device Driver for Card %d at Port %x not installed!", 
				//					(DG_Number + 1), base);
				//AfxMessageBox(txt, MB_OK, 0);
				//SetForegroundWindow(hwndMCD);
				//MessageBox(hwndMCD, (LPSTR)txt, szAppName, MB_OK);
				//demomod[DG_Number] = 1;
				//goto goon;
				return 6;
			}
			mcd2open[DG_Number] = 1;
			p_Present->NtDriverInitialized = TRUE;
		}
#endif
		break;
	}
	sprintf(info,"Initialize : %x ", rc);
	//AfxMessageBox(info, MB_OK, 0);		
	switch (p_Present->DG_Product)
	{
	case SRS_DG135:
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->CommandRegister = 0x00;
		break;
	default:
		p_Present->CommandRegister = 0x20;
		break;
	}
	p_Present->CommandRegisterState = 0xFFFFFFFF;
	LoadCommandRegister(&(p_Present->CommandRegister), p_Present);
	if (DG_Product == SRS_DG135)
	{
		cntrl = 0x30;
		value = 0x01;
		adr1 = p_Present->Counter;
		for (i = 0; i <= 2; i++)
		{
			DataOut(p_Present->Counter_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
			DataOut(adr1, &value, &(p_Present->PciDelgen), 2);
			cntrl += 0x40;
			adr1 += 1;
		}
	}

	Synchronize_DG_State(DG_Number);
	switch (p_Present->DG_Product)
	{
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->DelayControlState.DT.MS_Bus |= Resynchronize;
		break;
	default:
		break;
	}
	//if (DG_Product == BME_SG02P4)
		//Test_BME_G02(DG_Number);
	//if (DG_Product == BME_SG02V5)
		//HardwareTest_BME_G02(DG_Number);
	//if (DG_Product == BME_G02V3)
		//HardwareTest_BME_G02(DG_Number);
	//if (DG_Product == BME_G02V2)
		//HardwareTest_BME_G02(DG_Number);
	//if (DG_Product == BME_G03V2)
		//HardwareTest_BME_G03(DG_Number);
	
	return 0;
}

_declspec (dllexport) long CC ReadCalibrationConstants()
{
	char Path[20];
	Path[0] = 0;
	return (ReadPathCalibrationConstants(Path));
}

_declspec (dllexport) long CC ReadPathCalibrationConstants(char* Path)
{
	int i1;
	char* res1;
	char line[200];
	BOOL Error;
	FILE *stream;
	char FileName[200];
	DG_InternalData* p_Present;
	Error = FALSE;
	if (strlen(Path) > 0)
	{
		strcpy(FileName, Path);
		strcat(FileName, "\\BME_G0x.cal");
	}
	else
		strcpy(FileName, "BME_G0x.cal");
	stream = fopen(FileName, "r" );
	if (stream != NULL)
	{
		res1 = (char*)&line[0];
		i1 = 0;
		while ((i1 < 19) && (res1 != NULL))
		{
			res1 = fgets((char*)line, 200, stream);
			if (res1 != NULL)
				CalData.CalibrationConstant[i1] = atof(line);
			else
				Error = TRUE;
			i1++;
		}
		fclose(stream);
	}
	else
		Error = TRUE;
	if (Error)
	{
		InitializeCalibrationConstants();

		stream = fopen( FileName, "w" );
		if (stream == NULL)
			return 2;
		fprintf(stream, "   %8.6f      BME_SG02 direct trigger delay\n", CalData.SG02_ZeroTime);
		fprintf(stream, "   %8.6f      BME_SG02 first clock cycle\n", CalData.SG02_p1Time);
		fprintf(stream, "   %8.6f      BME_SG02 second clock cycle\n", CalData.SG02_p2Time);

		fprintf(stream, "   %8.6f      BME_SG02V2 first clock cycle\n", CalData.SG02V2_p1Time);
		fprintf(stream, "   %8.6f      BME_SG02V2 second clock cycle\n", CalData.SG02V2_p2Time);

		fprintf(stream, "   %8.6f      BME_SG02V1 direct trigger delay\n", CalData.SG02V1_GoTime);
		fprintf(stream, "   %8.6f      BME_SG02V1 first clock cycle\n", CalData.SG02V1_p1Time);
		fprintf(stream, "   %8.6f      BME_SG02V1 second clock cycle\n", CalData.SG02V1_p2Time);

		fprintf(stream, "   %8.6f      BME_G02 direct trigger delay\n", CalData.G02_ZeroTime);
		fprintf(stream, "   %8.6f      BME_G02 first clock cycle\n", CalData.G02_p1Time);
		fprintf(stream, "   %8.6f      BME_G02 second clock cycle\n", CalData.G02_p2Time);

		fprintf(stream, "   %8.6f      BME_G03 direct trigger delay\n", CalData.G03_ZeroTime);
		fprintf(stream, "   %8.6f      BME_G03 first clock cycle\n", CalData.G03_p1Time);
		fprintf(stream, "   %8.6f      BME_G03 second clock cycle\n", CalData.G03_p2Time);
		fprintf(stream, "  %8.6f      BME_G03 set back shift\n", CalData.G03_ResetTime);

		fprintf(stream, "   %8.6f      Clock delay on slave modules\n", CalData.ClockDelay);
		fprintf(stream, "   %8.6f      delay of direct Trigger on slave modules\n", CalData.TriggerDelay);

		fprintf(stream, "   %8.6f      internal oscillator frequency\n", CalData.InternalOscillator);
		fprintf(stream, "   %8.6f      external oscillator frequency\n", CalData.ExternalOscillator);
		fclose(stream);
	}
	if (Error)
		return 1;
	else
	{
		if (p_Internal != NULL)
		{
			for (i1 = 0; i1 < NoDelayGenerators; i1++)
			{
				p_Present = (p_Internal + i1);
				p_Present->InternalOscillatorFrequency = CalData.InternalOscillator;
				p_Present->ExternalOscillatorFrequency = CalData.ExternalOscillator;
			}
		}
		return 0;
	}
}

_declspec (dllexport) long CC SaveState()
{
	BOOL Error;
	FILE *stream;
	char FileName[200];
	Error = FALSE;
	strcpy(FileName, "DG_DLL.sts");
	stream = fopen(FileName, "wb" );
	if (stream != NULL)
	{
		fwrite(&(NoDelayGenerators), sizeof(int), 1, stream);
		fwrite(p_Internal, sizeof(DG_InternalData), NoDelayGenerators, stream);
		fwrite(&(CalData), sizeof(CalData), 1, stream);
		fclose(stream);
		return 0;
	}
	else
		return 1;
}

_declspec (dllexport) long CC ReadState()
{
	BOOL Error;
	FILE *stream;
	char FileName[200];
	if (p_Internal != NULL)
		Release_DG_Data();
	Error = FALSE;
	strcpy(FileName, "DG_DLL.sts");
	stream = fopen(FileName, "rb" );
	if (stream != NULL)
	{
		fread(&(NoDelayGenerators), sizeof(int), 1, stream);
		Reserve_DG_Data(NoDelayGenerators);
		fread(p_Internal, sizeof(DG_InternalData), NoDelayGenerators, stream);
		fread(&(CalData), sizeof(CalData), 1, stream);
		fclose(stream);
		return 0;
	}
	else
		return 1;
}

#define CurrentParameterFileVersion					5

_declspec (dllexport) long CC SaveParameters(DG_BME_State* p_DGS, int NoDelayGenerators, 
														 BOOL b_CalibrateTiming, unsigned long m_CalibrationLevel, char* FileName)
{
	BOOL Error;
	FILE *stream;
	int nVersion;
	nVersion = CurrentParameterFileVersion;
	Error = FALSE;
	stream = fopen(FileName, "wb" );
	if (stream != NULL)
	{
		fwrite(&(nVersion), sizeof(int), 1, stream);
		fwrite(&(NoDelayGenerators), sizeof(int), 1, stream);
		fwrite(&(m_CalibrationLevel), sizeof(int), 1, stream);
		fwrite(&(b_CalibrateTiming), sizeof(BOOL), 1, stream);
		fwrite(p_DGS, sizeof(DG_BME_State), NoDelayGenerators, stream);
		fclose(stream);
		//int Module[20];
		//ReadParameters(p_DGS, &(Module[0]), &b_CalibrateTiming, &m_CalibrationLevel, &(FileName[0]));
		return 0;
	}
	else
		return 1;
}

_declspec (dllexport) long CC ReadParameters(DG_BME_State* p_DGS, int* p_module,
														 BOOL* p_CalibrateTiming, unsigned long* p_CalibrationLevel, char* FileName)
{
	BOOL Error;
	FILE *stream;
	int nVersion,i1;
	long position;
	char TestChar;
	DG_BME_State* p_TGS;
	DG_BME_State_V1* p_DGS_V1 = NULL;
	DG_BME_State_V2* p_DGS_V2 = NULL;
	DG_BME_State_V3* p_DGS_V3 = NULL;
	DG_BME_State_V4* p_DGS_V4 = NULL;
	Error = FALSE;
	stream = fopen(FileName, "rb" );
	if (stream != NULL)
	{
		fread(&(nVersion), sizeof(int), 1, stream);
		fread(&(NoDelayGenerators), sizeof(int), 1, stream);
		fread(p_CalibrationLevel, sizeof(int), 1, stream);
		fread(p_CalibrateTiming, sizeof(BOOL), 1, stream);
		position = ftell( stream );
		switch (nVersion)
		{
		case 1:
		case 2:
		case 3:
		case 4:
				p_DGS_V1 = malloc(NoDelayGenerators * sizeof(DG_BME_State_V1));
				fread(p_DGS_V1, sizeof(DG_BME_State_V1), NoDelayGenerators, stream);
				if (!feof(stream))
				{
					fread(&(TestChar), sizeof(char), 1, stream);
					if (feof(stream))
					{
						CopyState_V1(p_DGS, p_DGS_V1);
						break;
					}
				}
				p_DGS_V2 = malloc(NoDelayGenerators * sizeof(DG_BME_State_V2));
				fseek(stream, position, 0);
				fread(p_DGS_V2, sizeof(DG_BME_State_V2), NoDelayGenerators, stream);
				if (!feof(stream))
				{
					fread(&(TestChar), sizeof(char), 1, stream);
					if (feof(stream))
					{
						CopyState_V2(p_DGS, p_DGS_V2);
						break;
					}
				}
				p_DGS_V3 = malloc(NoDelayGenerators * sizeof(DG_BME_State_V3));
				fseek(stream, position, 0);
				fread(p_DGS_V3, sizeof(DG_BME_State_V3), NoDelayGenerators, stream);
				if (!feof(stream))
				{
					fread(&(TestChar), sizeof(char), 1, stream);
					if (feof(stream))
					{
						CopyState_V3(p_DGS, p_DGS_V3);
						break;
					}
				}
				p_DGS_V4 = malloc(NoDelayGenerators * sizeof(DG_BME_State_V4));
				fseek(stream, position, 0);
				fread(p_DGS_V4, sizeof(DG_BME_State_V4), NoDelayGenerators, stream);
				if (!feof(stream))
				{
					fread(&(TestChar), sizeof(char), 1, stream);
					if (feof(stream))
					{
						CopyState_V4(p_DGS, p_DGS_V4);
						break;
					}
				}
				fseek(stream, position, 0);
				fread(p_DGS, sizeof(DG_BME_State), NoDelayGenerators, stream);
			break;
		default:
			fread(p_DGS, sizeof(DG_BME_State), NoDelayGenerators, stream);
			break;
		}
		fclose(stream);
		if (p_DGS_V1 != NULL)
		{
			free(p_DGS_V1);
			p_DGS_V1 = NULL;
		}
		if (p_DGS_V2 != NULL)
		{
			free(p_DGS_V2);
			p_DGS_V2 = NULL;
		}
		if (p_DGS_V3 != NULL)
		{
			free(p_DGS_V3);
			p_DGS_V3 = NULL;
		}
		if (p_DGS_V4 != NULL)
		{
			free(p_DGS_V4);
			p_DGS_V4 = NULL;
		}
		for (i1 = 0; i1 < NoDelayGenerators; i1++)
		{
			p_TGS = (p_DGS + i1);
			if ((p_DGS + i1)->Master)
				*(p_module + i1) = MasterModule;
			else
				*(p_module + i1) = SlaveModule;
			if (nVersion < 5)
				(p_DGS + i1)->BusNumber = -1;
		}
		return NoDelayGenerators;
	}
	else
		return 0;
}

_declspec (dllexport) long CC CalibrateModule(long DG_Number)
{
	DG_InternalData* p_Present;
	DG_InternalData* p_Master;
	DelayTriggerData* p_DT;
	DelayTriggerData* p_ST;
	double MasterIncrement,SlaveIncrement;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	p_Master = (DG_InternalData*)p_Present->p_Master;
	p_DT = &(p_Master->DelayControlState.DT);
	switch (p_Present->DG_Product)
	{
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if (p_Present->b_ModuleCalibrated)
		{
			if (p_DT->ClockSource == CrystalOscillator)
			{
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Master->InternalOscillatorFrequency;
				p_Present->OscillatorIncrement = 1.0 / p_Master->InternalOscillatorFrequency;
			}
			else
			{
				MasterIncrement = ((double)p_DT->TriggerDivider) / (p_Master->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
				p_Present->OscillatorIncrement = 1.0 / (p_Master->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
			}
			if (p_Present == p_Master)
				SlaveIncrement = MasterIncrement;
			else
			{
				p_ST = &(p_Present->DelayControlState.DT);
				if (p_ST->ClockSource == MasterSlaveBus)
				{
					SlaveIncrement = ((double)p_ST->OscillatorDivider) * MasterIncrement;
					p_Present->OscillatorIncrement = MasterIncrement;
				}
				else
				{
					if (p_ST->ClockSource == CrystalOscillator)
					{
						SlaveIncrement = ((double)p_ST->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
						p_Present->OscillatorIncrement = 1.0 / p_Present->InternalOscillatorFrequency;
					}
					else
					{
						SlaveIncrement = ((double)p_ST->TriggerDivider) / (p_Present->ExternalOscillatorFrequency * max(1.0, p_ST->TriggerMultiplier));
						p_Present->OscillatorIncrement = 1.0 / (p_Present->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
					}
				}
			}
			p_Present->TimeIncrement = MasterIncrement;
			p_Present->TriggerIncrement = SlaveIncrement;
			if ((p_Present->DelayControlState.T0.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->T0_Increment = SlaveIncrement;
			else
				p_Present->T0_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.A.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->A_Increment = SlaveIncrement;
			else
				p_Present->A_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.B.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->B_Increment = SlaveIncrement;
			else
				p_Present->B_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.C.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->C_Increment = SlaveIncrement;
			else
				p_Present->C_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.D.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->D_Increment = SlaveIncrement;
			else
				p_Present->D_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.E.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->E_Increment = SlaveIncrement;
			else
				p_Present->E_Increment = MasterIncrement;
			if ((p_Present->DelayControlState.F.GoSignal & (LocalPrimary | LocalSecondary | LocalForce)) != 0x0)
				p_Present->F_Increment = SlaveIncrement;
			else
				p_Present->F_Increment = MasterIncrement;
		}
		else
		{
			//p_Present->InternalOscillatorFrequency = CalData.InternalOscillator;
			//p_Present->ExternalOscillatorFrequency = CalData.ExternalOscillator;
			if (p_DT->ClockSource == CrystalOscillator)
			{
				p_Present->OscillatorIncrement = 1.0 / p_Present->InternalOscillatorFrequency;
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
			}
			else
			{
				p_Present->OscillatorIncrement = 1.0 / (p_Present->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
				MasterIncrement = ((double)p_DT->TriggerDivider) / (p_Present->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
			}
			p_Present->TimeIncrement = MasterIncrement;
			p_Present->TriggerIncrement = MasterIncrement;
			p_Present->T0_Increment = MasterIncrement;
			p_Present->A_Increment = MasterIncrement;
			p_Present->B_Increment = MasterIncrement;
			p_Present->C_Increment = MasterIncrement;
			p_Present->D_Increment = MasterIncrement;
			p_Present->E_Increment = MasterIncrement;
			p_Present->F_Increment = MasterIncrement;
		}
		break;
	default:
		if (p_Present->b_ModuleCalibrated)
		{
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Master->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / (p_Master->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
		}
		else
		{
			//p_Present->InternalOscillatorFrequency = CalData.InternalOscillator;
			//p_Present->ExternalOscillatorFrequency = CalData.ExternalOscillator;
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / (p_Present->ExternalOscillatorFrequency * max(1.0, p_DT->TriggerMultiplier));
		}
		p_Present->TimeIncrement = MasterIncrement;
		p_Present->TriggerIncrement = MasterIncrement;
		p_Present->T0_Increment = MasterIncrement;
		p_Present->A_Increment = MasterIncrement;
		p_Present->B_Increment = MasterIncrement;
		break;
	}
	switch (p_Master->DG_Product)
	{
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if (!p_Present->b_ModuleCalibrated)
		{
			p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime;
			p_Present->TenMhzp1Time = CalData.SG02_p1Time;
			p_Present->TenMhzp2Time = CalData.SG02_p2Time;
		}
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			p_Present->ZeroTime = p_Present->TenMhzZeroTime;
			p_Present->p1Time = p_Present->TenMhzp1Time;
			p_Present->p2Time = p_Present->TenMhzp2Time - 0.1 + p_Present->TimeIncrement;
		}
		else
		{
			p_Present->ZeroTime = 0.0;
			p_Present->p1Time = p_Present->TimeIncrement;
			p_Present->p2Time = (2.0 * p_Present->TimeIncrement);
		}
		break;
	case BME_SG02V2:
		if (!p_Present->b_ModuleCalibrated)
		{
			p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime;
			p_Present->TenMhzp1Time = CalData.SG02V2_p1Time;
			p_Present->TenMhzp2Time = CalData.SG02V2_p2Time;
		}
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			p_Present->ZeroTime = p_Present->TenMhzZeroTime;
			p_Present->p1Time = p_Present->TenMhzp1Time;
			p_Present->p2Time = p_Present->TenMhzp2Time - 0.1 + p_Present->TimeIncrement;
		}
		else
		{
			p_Present->ZeroTime = 0.0;
			p_Present->p1Time = p_Present->TimeIncrement;
			p_Present->p2Time = (2.0 * p_Present->TimeIncrement);
		}
		break;
	case BME_SG02V1:
		if (!p_Present->b_ModuleCalibrated)
		{
			p_Present->TenMhzZeroTime = 0.0;
			p_Present->TenMhzp1Time = CalData.SG02V1_p1Time;
			p_Present->TenMhzp2Time = CalData.SG02V1_p2Time;
		}
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			p_Present->ZeroTime = p_Present->TenMhzZeroTime;
			p_Present->p1Time = p_Present->TenMhzp1Time - 0.1 + p_Present->TimeIncrement;
			p_Present->p2Time = p_Present->TenMhzp2Time - 0.2 + (2.0 * p_Present->TimeIncrement);
		}
		else
		{
			p_Present->ZeroTime = 0.0;
			p_Present->p1Time = p_Present->TimeIncrement;
			p_Present->p2Time = (2.0 * p_Present->TimeIncrement);
		}
		break;
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if (!p_Present->b_ModuleCalibrated)
			p_Present->TenMhzResetTime = CalData.G03_ResetTime;
		if (p_Present->CalibrationLevel == CalibrateOffset)
			p_Present->ResetTime = p_Present->TenMhzResetTime;
		else
			p_Present->ResetTime = 0.0;
	case BME_G02V3:
	case BME_G02V2:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
		if (!p_Present->b_ModuleCalibrated)
			p_Present->TenMhzZeroTime = CalData.G02_ZeroTime;
	case BME_G02V1:
		if (!p_Present->b_ModuleCalibrated)
		{
			p_Present->TenMhzp1Time = CalData.G02_p1Time;
			p_Present->TenMhzp2Time = CalData.G02_p2Time;
		}
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			p_Present->ZeroTime = p_Present->TenMhzZeroTime;
			p_Present->p1Time = p_Present->TenMhzp1Time - 0.1 + p_Present->TimeIncrement;
			p_Present->p2Time = p_Present->TenMhzp2Time - 0.2 + (2.0 * p_Present->TimeIncrement);
		}
		else
		{
			p_Present->ZeroTime = 0.0;
			p_Present->p1Time = p_Present->TimeIncrement;
			p_Present->p2Time = (2.0 * p_Present->TimeIncrement);
		}
		break;
	case BME_G03V2:
		if (!p_Present->b_ModuleCalibrated)
			p_Present->TenMhzZeroTime = CalData.G03_ZeroTime;
	case BME_G03V1:
		if (!p_Present->b_ModuleCalibrated)
		{
			p_Present->TenMhzp1Time = CalData.G03_p1Time;
			p_Present->TenMhzp2Time = CalData.G03_p2Time;
			p_Present->TenMhzResetTime = CalData.G03_ResetTime;
		}
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			p_Present->ZeroTime = p_Present->TenMhzZeroTime;
			p_Present->p1Time = p_Present->TenMhzp1Time - 0.2 + (2.0 * p_Present->TimeIncrement);
			p_Present->p2Time = p_Present->TenMhzp2Time - 0.3 + (3.0 * p_Present->TimeIncrement);
			p_Present->ResetTime = p_Present->TenMhzResetTime;
		}
		else
		{
			p_Present->ZeroTime = 0.0;
			p_Present->p1Time = (2.0 * p_Present->TimeIncrement);
			p_Present->p2Time = (3.0 * p_Present->TimeIncrement);
			p_Present->ResetTime = 0.0;
		}
		break;
	default:
		break;
	}
	p_Present->b_ModuleCalibrated = TRUE;
	return 0;
}

_declspec (dllexport) long CC UncalibrateModule(long DG_Number)
{
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	p_Present->ZeroTime = 0.0;
	p_Present->p1Time = 0.1;
	p_Present->p2Time = 0.2;
	p_Present->ResetTime = 0.0;
	p_Present->TimeIncrement = 0.1;
	p_Present->TriggerIncrement = 0.1;
	p_Present->OscillatorIncrement = (1.0 / p_Present->ExternalOscillatorFrequency);
	p_Present->T0_Increment = 0.1;
	p_Present->A_Increment = 0.1;
	p_Present->B_Increment = 0.1;
	p_Present->C_Increment = 0.1;
	p_Present->D_Increment = 0.1;
	p_Present->E_Increment = 0.1;
	p_Present->F_Increment = 0.1;
	p_Present->b_ModuleCalibrated = FALSE;
	p_Present->CalibrationLevel = CalibrateNone;
	return 0;
}

_declspec (dllexport) long CC CalibrateGroup(int* p_module)
{
	char Path[20];
	Path[0] = 0;
	return (CalibratePathGroup(p_module, Path));
}

_declspec (dllexport) long CC CalibratePathGroup(int* p_module, char* Path)
{
	DG_InternalData* p_Present;
	DG_InternalData* p_MasterCard;
	long DG_Number;
	int MasterCard;
	FILE *stream;
	BOOL Error;
	char FileName[200];
	p_MasterCard = NULL;
	if (strlen(Path) > 0)
	{
		strcpy(FileName, Path);
		strcat(FileName, "\\Modules.cal");
	}
	else
		strcpy(FileName, "Modules.cal");
	Error = FALSE;
	stream = fopen( FileName, "r" );
	if (stream != NULL)
	{
		Error = ReadCalibrationFile(stream, p_module, FileName);
		fclose(stream);
	}
	else
		Error = TRUE;
	if (Error)
	{
		DG_Number = 0;
		MasterCard = -1;
		while (DG_Number < NoDelayGenerators)
		{
			p_Present = (p_Internal + DG_Number);
			if ((*(p_module + DG_Number) == MasterModule) || (p_MasterCard == NULL))
			{
				MasterCard = p_Present->DG_Product;
				p_MasterCard = p_Present;
				p_Present->p_Master = p_MasterCard;
				CalibrateModule(DG_Number);
			}
			else
			{
				p_Present->p_Master = p_MasterCard;
				switch (MasterCard)
				{
				case BME_SG02V3:
				case BME_SG02V4:
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P3:
				case BME_SG02P4:
				case BME_SG02P5:
					switch (p_Present->DG_Product)
					{
					case BME_G03V3:
					case BME_G03V4:
					case BME_G03V5:
					case BME_G03P1:
					case BME_G03P2:
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
					case BME_G02V3:
					case BME_G02V2:
					case BME_SG02V2:
					case BME_SG02V3:
					case BME_SG02V4:
					case BME_SG02V5:
					case BME_SG02V6:
					case BME_SG02V7:
					case BME_SG02P1:
					case BME_SG02P2:
					case BME_SG02P3:
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05V1:
					case BME_G05V2:
					case BME_G05V3:
					case BME_G05P1:
					case BME_G05P2:
					case BME_G05P3:
					case BME_SG05P1:
					case BME_SG05P2:
					case BME_SG05P3:
					case BME_SG08P1:
					case BME_SG08P2:
						p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime + CalData.TriggerDelay;
					case BME_G02V1:
					case BME_SG02V1:
						p_Present->TenMhzp1Time = CalData.SG02_p1Time;
						p_Present->TenMhzp2Time = CalData.SG02_p2Time;
						break;
					case BME_G03V2:
						p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime + CalData.TriggerDelay;
					case BME_G03V1:
						p_Present->TenMhzp1Time = CalData.SG02_p2Time;
						p_Present->TenMhzp2Time = p_Present->TenMhzp1Time + 0.1;
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
						break;
					default:
						break;
					}
					break;
				case BME_SG02V2:
					switch (p_Present->DG_Product)
					{
					case BME_G03V3:
					case BME_G03V4:
					case BME_G03V5:
					case BME_G03P1:
					case BME_G03P2:
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
					case BME_G02V3:
					case BME_G02V2:
					case BME_SG02V3:
					case BME_SG02V4:
					case BME_SG02V5:
					case BME_SG02V6:
					case BME_SG02V7:
					case BME_SG02P1:
					case BME_SG02P2:
					case BME_SG02P3:
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05V1:
					case BME_G05V2:
					case BME_G05V3:
					case BME_G05P1:
					case BME_G05P2:
					case BME_G05P3:
					case BME_SG05P1:
					case BME_SG05P2:
					case BME_SG05P3:
						p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime + CalData.TriggerDelay;
					case BME_G02V1:
					case BME_SG02V1:
						p_Present->TenMhzp1Time = CalData.SG02V2_p1Time + CalData.ClockDelay;
						p_Present->TenMhzp2Time = CalData.SG02V2_p2Time + CalData.ClockDelay;
						break;
					case BME_G03V2:
						p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime + CalData.TriggerDelay;
					case BME_G03V1:
						p_Present->TenMhzp1Time = CalData.SG02V2_p2Time + CalData.ClockDelay;
						p_Present->TenMhzp2Time = p_Present->TenMhzp1Time + 0.1;
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
						break;
					default:
						break;
					}
					break;
				case BME_SG02V1:
					switch (p_Present->DG_Product)
					{
					case BME_G03V3:
					case BME_G03V4:
					case BME_G03V5:
					case BME_G03P1:
					case BME_G03P2:
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
					case BME_G02V3:
					case BME_G02V2:
					case BME_SG02V3:
					case BME_SG02V4:
					case BME_SG02V5:
					case BME_SG02V6:
					case BME_SG02V7:
					case BME_SG02P1:
					case BME_SG02P2:
					case BME_SG02P3:
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05V1:
					case BME_G05V2:
					case BME_G05V3:
					case BME_G05P1:
					case BME_G05P2:
					case BME_G05P3:
					case BME_SG05P1:
					case BME_SG05P2:
					case BME_SG05P3:
					case BME_SG08P1:
					case BME_SG08P2:
						p_Present->TenMhzZeroTime = CalData.SG02V1_GoTime + CalData.TriggerDelay;
					case BME_G02V1:
					case BME_SG02V1:
						p_Present->TenMhzp1Time = CalData.SG02V1_p1Time + CalData.ClockDelay;
						p_Present->TenMhzp2Time = CalData.SG02V1_p2Time + CalData.ClockDelay;
						break;
					case BME_G03V2:
						p_Present->TenMhzZeroTime = CalData.SG02V1_GoTime + CalData.TriggerDelay;
					case BME_G03V1:
						p_Present->TenMhzp1Time = CalData.SG02V1_p2Time + CalData.ClockDelay;
						p_Present->TenMhzp2Time = p_Present->TenMhzp1Time + 0.1;
						p_Present->TenMhzResetTime = CalData.G03_ResetTime;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				p_Present->b_ModuleCalibrated = TRUE;
				CalibrateModule(DG_Number);
			}
			DG_Number++;
		}
		stream = fopen( FileName, "w" );
		if (stream == NULL)
			return 2;
		DG_Number = 0;
		while (DG_Number < NoDelayGenerators)
		{
			p_Present = (p_Internal + DG_Number);
			switch (p_Present->DG_Product)
			{
				case BME_SG02V1:
					fprintf(stream, "BME_SG02V1    ");
					break;
				case BME_SG02V2:
					fprintf(stream, "BME_SG02V2    ");
					break;
				case BME_SG02V3:
					fprintf(stream, "BME_SG02V3    ");
					break;
				case BME_SG02V4:
					fprintf(stream, "BME_SG02V4    ");
					break;
				case BME_SG02V5:
					fprintf(stream, "BME_SG02V5    ");
					break;
				case BME_SG02V6:
					fprintf(stream, "BME_SG02V6    ");
					break;
				case BME_SG02V7:
					fprintf(stream, "BME_SG02V7    ");
					break;
				case BME_SG02P1:
					fprintf(stream, "BME_SG02P1    ");
					break;
				case BME_SG02P2:
					fprintf(stream, "BME_SG02P2    ");
					break;
				case BME_SG02P3:
					fprintf(stream, "BME_SG02P3    ");
					break;
				case BME_SG02P4:
					fprintf(stream, "BME_SG02P4    ");
					break;
				case BME_SG02P5:
					fprintf(stream, "BME_SG02P5    ");
					break;
				case BME_G03V1:
					fprintf(stream, "BME_G03V1     ");
					break;
				case BME_G03V2:
					fprintf(stream, "BME_G03V2     ");
					break;
				case BME_G03V3:
					fprintf(stream, "BME_G03V3     ");
					break;
				case BME_G03V4:
					fprintf(stream, "BME_G03V4     ");
					break;
				case BME_G03V5:
					fprintf(stream, "BME_G03V5     ");
					break;
				case BME_G03P1:
					fprintf(stream, "BME_G03P1     ");
					break;
				case BME_G03P2:
					fprintf(stream, "BME_G03P2     ");
					break;
				case BME_G02V1:
					fprintf(stream, "BME_G02V1     ");
					break;
				case BME_G02V3:
					fprintf(stream, "BME_G02V3     ");
					break;
				case BME_G02V2:
					fprintf(stream, "BME_G02V2     ");
					break;
				case BME_G05V1:
					fprintf(stream, "BME_G05V1     ");
					break;
				case BME_G05V2:
					fprintf(stream, "BME_G05V2     ");
					break;
				case BME_G05V3:
					fprintf(stream, "BME_G05V3     ");
					break;
				case BME_G05P1:
					fprintf(stream, "BME_G05P1     ");
					break;
				case BME_G05P2:
					fprintf(stream, "BME_G05P2     ");
					break;
				case BME_G05P3:
					fprintf(stream, "BME_G05P3     ");
					break;
				case BME_SG05P1:
					fprintf(stream, "BME_SG05P1    ");
					break;
				case BME_SG05P2:
					fprintf(stream, "BME_SG05P2    ");
					break;
				case BME_SG05P3:
					fprintf(stream, "BME_SG05P3    ");
					break;
				case BME_SG08P1:
					fprintf(stream, "BME_SG08P1    ");
					break;
				case BME_SG08P2:
					fprintf(stream, "BME_SG08P2    ");
					break;
				default:
					break;
			}
			if (*(p_module + DG_Number) == MasterModule)
				fprintf(stream, "Master\n");
			else
				fprintf(stream, "Slave\n");
			switch (p_Present->DG_Product)
			{
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
				case BME_SG08P1:
				case BME_SG08P2:
					fprintf(stream, "   %8.6f      internal oscillator frequency\n", 
																						p_Present->InternalOscillatorFrequency);
					fprintf(stream, "   %8.6f      external oscillator frequency\n", 
																						p_Present->ExternalOscillatorFrequency);
					break;
				default:
					if (*(p_module + DG_Number) == MasterModule)
					{
						fprintf(stream, "   %8.6f      internal oscillator frequency\n", 
																							p_Present->InternalOscillatorFrequency);
						fprintf(stream, "   %8.6f      external oscillator frequency\n", 
																							p_Present->ExternalOscillatorFrequency);
					}
					break;
			}
			switch (p_Present->DG_Product)
			{
				case BME_G02V3:
				case BME_G02V2:
				case BME_SG02V2:
				case BME_SG02V3:
				case BME_SG02V4:
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P3:
				case BME_SG02P4:
				case BME_SG02P5:
				case BME_G03V2:
				case BME_G03V3:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
				case BME_SG08P1:
				case BME_SG08P2:
					fprintf(stream, "   %8.6f      direct trigger delay\n", p_Present->ZeroTime);
				case BME_G02V1:
				case BME_SG02V1:
				case BME_G03V1:
					fprintf(stream, "   %8.6f      first clock cycle\n", p_Present->TenMhzp1Time);
					fprintf(stream, "   %8.6f      second clock cycle\n", p_Present->TenMhzp2Time);
					break;
				default:
					break;
			}
			switch (p_Present->DG_Product)
			{
				case BME_G03V1:
				case BME_G03V2:
				case BME_G03V3:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
					fprintf(stream, "  %8.6f      set back shift\n", p_Present->ResetTime);
					break;
				default:
					break;
			}
			DG_Number++;
		}
		fclose(stream);
	}
	if (Error)
		return 1;
	else
		return 0;
}

_declspec (dllexport) long CC Set_DG_BME(DG_BME_Registers* p_pdg, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long* p_LoadWord;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	if (p_pdg->DG_Product != DG_Product)
		return 1;
	//if (DG_Product == BME_G02V3)
		//printf("CDG_DLL::Set_DG_BME \n");
	p_LoadWord = &(p_Present->LoadVector);
	ModifyControlRegister(p_pdg, p_Present);
	PrepareCounterControl(p_pdg, p_LoadWord, p_Present);
	switch (DG_Product)
	{
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G02V3:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if (!IsEqualPS(p_pdg, &(p_Present->DelayGeneratorState), DG_Product))
			Set_Prescaler(p_pdg, p_LoadWord, p_Present);
		break;
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if (!IsEqualDT(&(p_pdg->DT), &(p_Present->DelayGeneratorState.DT), DG_Product))
			Set_Delay_Trigger(&(p_pdg->DT), p_LoadWord, p_Present);
		if (!IsEqualDC(&(p_pdg->A), &(p_Present->DelayGeneratorState.A), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->A), &(p_Present->DelayGeneratorState.A), p_LoadWord, 0, p_Present);
		if (!IsEqualDC(&(p_pdg->B), &(p_Present->DelayGeneratorState.B), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->B), &(p_Present->DelayGeneratorState.B), p_LoadWord, 1, p_Present);
		if (!IsEqualDC(&(p_pdg->C), &(p_Present->DelayGeneratorState.C), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->C), &(p_Present->DelayGeneratorState.C), p_LoadWord, 2, p_Present);
		if (!IsEqualDC(&(p_pdg->D), &(p_Present->DelayGeneratorState.D), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->D), &(p_Present->DelayGeneratorState.D), p_LoadWord, 3, p_Present);
		if (!IsEqualDC(&(p_pdg->E), &(p_Present->DelayGeneratorState.E), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->E), &(p_Present->DelayGeneratorState.E), p_LoadWord, 4, p_Present);
		if (!IsEqualDC(&(p_pdg->F), &(p_Present->DelayGeneratorState.F), DG_Product))
			Set_Delay_channel_SG05P4(&(p_pdg->F), &(p_Present->DelayGeneratorState.F), p_LoadWord, 5, p_Present);
		break;
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_G03V1:
	case BME_G03V2:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (!IsEqualMC(&(p_pdg->MC), &(p_Present->DelayGeneratorState.MC), DG_Product))
			Set_Main_Counter(&(p_pdg->MC), p_Present);
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
		if (!IsEqualDT(&(p_pdg->DT), &(p_Present->DelayGeneratorState.DT), DG_Product))
			Set_Delay_Trigger(&(p_pdg->DT), p_LoadWord, p_Present);
	default:
		if (!IsEqualDC(&(p_pdg->T0), &(p_Present->DelayGeneratorState.T0), DG_Product))
			Set_Reference_channel(&(p_pdg->T0), p_Present);
		if (!IsEqualDC(&(p_pdg->A), &(p_Present->DelayGeneratorState.A), DG_Product))
			Set_Delay_channel(&(p_pdg->A), &(p_Present->DelayGeneratorState.A), 1, p_Present);
		if (!IsEqualDC(&(p_pdg->B), &(p_Present->DelayGeneratorState.B), DG_Product))
			Set_Delay_channel(&(p_pdg->B), &(p_Present->DelayGeneratorState.B), 2, p_Present);
	}
	if (p_Present->b_DG_Activated)
		Activate_DG_BME(DG_Number);
	if (*p_LoadWord != 0x0)
	{
		switch (DG_Product)
		{
		case BME_SG08P1:
			*p_LoadWord &= ~0x18;
			Data32Out(p_Present->InitializeAddress, p_LoadWord, &(p_Present->PciDelgen), 4);
			*p_LoadWord = 0x0;
			break;
		case BME_SG08P2:
			if (!p_Present->b_DG_Activated)
			{
				Data32Out(p_Present->InitializeAddress, p_LoadWord, &(p_Present->PciDelgen), 4);
				*p_LoadWord = 0x0;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

_declspec (dllexport) long CC SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	double Increment;
	long result;
	DG_BME_Registers dgr;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	if (p_BDG->DG_Product != DG_Product)
		return 1;

	memcpy(&(p_Present->DelayControlState), p_BDG, sizeof(DG_BME_Control));
	ResetRegisters(&dgr);
	if (p_Present->b_ModuleCalibrated)
		CalibrateModule(DG_Number);
	Increment = p_Present->TimeIncrement;

	dgr.DG_Product = p_BDG->DG_Product;
	dgr.Gate_AB = p_BDG->Gate_AB;
	dgr.GateFunction = p_BDG->GateFunction;
	dgr.OutputLevel = p_BDG->OutputLevel;
	if ((dgr.OutputLevel < TTL_VoltageLevel) || (ECL_VoltageLevel < dgr.OutputLevel))
		return 6;
	dgr.PulseWidth = p_BDG->PulseWidth;

	result = SetTrigger(&dgr, p_BDG, DG_Number);
	if (result != 0)
		return result;

	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->TimeIncrement = p_Present->A_Increment;
		result = SetChannel_SG05P4(&(dgr.A), &(p_BDG->A), DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->B_Increment;
		result = SetChannel_SG05P4(&(dgr.B), &(p_BDG->B), DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->C_Increment;
		result = SetChannel_SG05P4(&(dgr.C), &(p_BDG->C), DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->D_Increment;
		result = SetChannel_SG05P4(&(dgr.D), &(p_BDG->D), DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->E_Increment;
		result = SetChannel_SG05P4(&(dgr.E), &(p_BDG->E), DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->F_Increment;
		result = SetChannel_SG05P4(&(dgr.F), &(p_BDG->F), DG_Number);
		if (result != 0)
			return result;
		break;
	default:
		Increment = p_Present->TimeIncrement;
		p_Present->TimeIncrement = p_Present->T0_Increment;
		result = SetReference(&(dgr.T0), &(p_BDG->T0), dgr.MC.Digital, DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->A_Increment;
		result = SetChannel(&(dgr.A), &(p_BDG->A), dgr.MC.Digital, DG_Number);
		if (result != 0)
			return result;
		p_Present->TimeIncrement = p_Present->B_Increment;
		result = SetChannel(&(dgr.B), &(p_BDG->B), dgr.MC.Digital, DG_Number);
		if (result != 0)
			return result;
		break;
	}

	p_Present->TimeIncrement = Increment;
	result = Set_DG_BME(&dgr, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC DelayLimit(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value,Delta;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	value = min(InValue, MaxBME_G0XRange);
	switch (p_Present->DG_Product)
	{
	case BME_G02V1:
	case BME_G03V1:
	case BME_SG02V1:
		value = max(value, p_Present->p1Time);
		break;
	default:
		value = max(value, p_Present->ZeroTime);
		Delta = 0.1 * 4095.0 / 4096.0;
		if (((p_Present->ZeroTime + Delta) < value) && (value < p_Present->p1Time))
		{
			if ((p_Present->p1Time - value) < (value - (p_Present->ZeroTime + Delta)))
				value = p_Present->p1Time;
			else
				value = p_Present->ZeroTime + Delta;
		}
	}
	*p_out = value;
	return 0;
}

_declspec (dllexport) long CC RoundRepCounter(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double Increment;
	int ipos;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Increment = p_Present->TimeIncrement;
	ipos = RoundInt(InValue / Increment);
	switch (p_Present->DG_Product)
	{
		case BME_SG02P3:
			ipos = max(0, ipos);
			if (ipos > 0)
				ipos = max(4, ipos);
			break;
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
		case BME_SG08P1:
		case BME_SG08P2:
			ipos = max(1, ipos);
			break;
		default:
			ipos = max(3, ipos);
			break;
	}
	*p_out = Increment * (double)ipos;
	return 0;
}

_declspec (dllexport) long CC RoundT0(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value,TestValue,Increment;
	int i1,ipos;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Increment = p_Present->TimeIncrement;
	if (InValue >= p_Present->p2Time)
	{
		value = InValue - p_Present->p2Time ;
		value = Increment * (double)RoundInt(value / Increment);
		*p_out = value + p_Present->p2Time;
		return 0;
	}
	else
	{
		ipos = 0;
		value = fabs(InValue - p_Present->ZeroTime);
		for (i1 = 1; i1 < 3; i1++)
		{
			TestValue = fabs(InValue - p_Present->IniTime[i1]);
			if (TestValue < value)
			{
				value = TestValue;
				ipos = i1;
			}
		}
		switch (p_Present->DG_Product)
		{
		case BME_G02V1:
		case BME_G03V1:
		case BME_SG02V1:
			ipos = max(1, ipos);
		default:
			*p_out = p_Present->IniTime[ipos];
		}
		return 0;
	}
	return 0;
}

_declspec (dllexport) long CC RoundWidth(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double Increment;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Increment = p_Present->TimeIncrement;
	if (InValue < (Increment * 0.75))
		*p_out = Increment * 0.5;
	else
		*p_out = Increment * (double)RoundInt(InValue / Increment);
	return 0;
}

_declspec (dllexport) long CC RoundGateDelay(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double Increment;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Increment = p_Present->OscillatorIncrement;
	*p_out = Increment * (double)max(0, min(63, RoundInt(InValue / Increment)));
	return 0;
}

_declspec (dllexport) long CC RoundSetBack(double* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	value = InValue - p_Present->ResetTime;
	RoundT0(p_out, value, DG_Number);
	*p_out += (p_Present->ResetTime);
	return 0;
}

_declspec (dllexport) long CC Set_BME_G08(double FireFirst_A, double PulseWidth_A, unsigned long OutputModulo_A,
													unsigned long OutputOffset_A, unsigned long GoSignal_A, BOOL Positive_A, BOOL Terminate_A, 
													double FireFirst_B, double PulseWidth_B, unsigned long OutputModulo_B,
													unsigned long OutputOffset_B, unsigned long GoSignal_B, BOOL Positive_B, BOOL Terminate_B, 
													double FireFirst_C, double PulseWidth_C, unsigned long OutputModulo_C,
													unsigned long OutputOffset_C, unsigned long GoSignal_C, BOOL Positive_C, BOOL Terminate_C, 
													double FireFirst_D, double PulseWidth_D, unsigned long OutputModulo_D,
													unsigned long OutputOffset_D, unsigned long GoSignal_D, BOOL Positive_D, BOOL Terminate_D, 
													double FireFirst_E, double PulseWidth_E, unsigned long OutputModulo_E,
													unsigned long OutputOffset_E, unsigned long GoSignal_E, BOOL Positive_E, BOOL Terminate_E, 
													BOOL Disconnect_E, BOOL OntoMsBus_E, BOOL InputPositive_E,
													double FireFirst_F, double PulseWidth_F, unsigned long OutputModulo_F,
													unsigned long OutputOffset_F, unsigned long GoSignal_F, BOOL Positive_F, BOOL Terminate_F, 
													BOOL Disconnect_F, BOOL OntoMsBus_F, BOOL InputPositive_F,
													unsigned long GateFunction, BOOL ClockEnable, unsigned long OscillatorDivider,
													unsigned long TriggerDivider,  unsigned long TriggerMultiplier,
													unsigned long ClockSource, BOOL TriggerTerminate, BOOL GateTerminate,
													double TriggerLevel, double GateLevel, double GateDelay, unsigned long MS_Bus,
													double InternalClock, unsigned long PresetValue, unsigned long GateDivider,
													double ForceTrigger, double StepBackTime, unsigned long BurstCounter,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL IgnoreGate, BOOL SynchronizeGate,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	long result,Action;
	DG_InternalData* p_Present;
	BOOL InternalArm,SoftwareTrigger;
	InternalArm = FALSE;
	SoftwareTrigger = FALSE;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	if (p_Present->b_DG_Activated)
	{
		Action = Modify_G08(OutputModulo_A, OutputOffset_A, GoSignal_A, Positive_A, Terminate_A,
													OutputModulo_B, OutputOffset_B, GoSignal_B, Positive_B, Terminate_B,
													OutputModulo_C, OutputOffset_C, GoSignal_C, Positive_C, Terminate_C,
													OutputModulo_D, OutputOffset_D, GoSignal_D, Positive_D, Terminate_D,
													OutputModulo_E, OutputOffset_E, GoSignal_E, Positive_E, Terminate_E,
													Disconnect_E, OntoMsBus_E, InputPositive_E,
													OutputModulo_F, OutputOffset_F, GoSignal_F, Positive_F, Terminate_F,
													Disconnect_F, OntoMsBus_F, InputPositive_F,
													TriggerTerminate, GateTerminate, ClockEnable,
													PresetValue, ClockSource, GateDivider,
													MS_Bus, PositiveGate, SynchronizeGate, InternalTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);
		if ((Action & 0x1) != 0)
			Deactivate_DG_BME(DG_Number);
	}
	else
		Action = 0x5;
	result = Set_G08_ClockParameters(ClockEnable, OscillatorDivider, TriggerDivider, 
																		TriggerMultiplier, ClockSource, DG_Number);
	if (result != 0)
		return result;
	result = Set_TriggerParameters(TriggerTerminate, InternalClock, 
													TriggerLevel, PresetValue, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);
	if (result != 0)
		return result;

	result = Set_G08_TriggerParameters(GateTerminate, GateLevel, GateDelay,IgnoreGate, SynchronizeGate,
																			ForceTrigger, StepBackTime, BurstCounter, MS_Bus, DG_Number);
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_A, FireFirst_A, PulseWidth_A, OutputModulo_A, OutputOffset_A, 
								GoSignal_A, Positive_A, Terminate_A, FALSE, FALSE, FALSE, DG_Number);	
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_B, FireFirst_B, PulseWidth_B, OutputModulo_B, OutputOffset_B, 
								GoSignal_B, Positive_B, Terminate_B, FALSE, FALSE, FALSE, DG_Number);	
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_C, FireFirst_C, PulseWidth_C, OutputModulo_C, OutputOffset_C, 
								GoSignal_C, Positive_C, Terminate_C, FALSE, FALSE, FALSE, DG_Number);	
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_D, FireFirst_D, PulseWidth_D, OutputModulo_D, OutputOffset_D, 
								GoSignal_D, Positive_D, Terminate_D, FALSE, FALSE, FALSE, DG_Number);	
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_E, FireFirst_E, PulseWidth_E, OutputModulo_E, OutputOffset_E, 
								GoSignal_E, Positive_E, Terminate_E, Disconnect_E, OntoMsBus_E, InputPositive_E, DG_Number);	
	if (result != 0)
		return result;
	result = Set_G08_Delay(DelayChannel_F, FireFirst_F, PulseWidth_F, OutputModulo_F, OutputOffset_F, 
								GoSignal_F, Positive_F, Terminate_F, Disconnect_F, OntoMsBus_F, InputPositive_F, DG_Number);	
	if (result != 0)
		return result;
	result = Set_GateFunction(GateFunction, DG_Number);
	if (result != 0)
		return result;
	if ((Action & 0x4) != 0)
		ResetOutputModuloCounters(DG_Number);
	Activate_DG_BME(DG_Number);
	return 0;
}

_declspec (dllexport) long CC Set_BME_G05(double FireFirst_T0, unsigned long OutputModulo_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, unsigned long OutputModulo_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, unsigned long OutputModulo_B,
													BOOL Active_B, BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	long result,Action;
	DG_InternalData* p_Present;
	unsigned long PulseWidth;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	PulseWidth = p_Present->DelayControlState.PulseWidth;

	if (p_Present->b_DG_Activated)
	{
		Action = Modify_DG(OutputModulo_T0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													OutputModulo_A, Active_A, Positive_A, Terminate_A, HighDrive_A,
													OutputModulo_B, Active_B, Positive_B, Terminate_B, HighDrive_B,
													OutputLevel, TriggerTerminate, ClockEnable, PresetValue, 
													ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
		if ((Action & 0x1) != 0)
			Deactivate_DG_BME(DG_Number);
	}
	else
		Action = 0x5;

	result = Set_OutputLevel(OutputLevel, PulseWidth, DG_Number);
	if (result != 0)
		return result;
	result = Set_ClockParameters(ClockEnable, DivideBy, ClockSource,  DG_Number);
	if (result != 0)
		return result;
	result = Set_TriggerParameters(TriggerTerminate, InternalClock, 
													TriggerLevel, PresetValue, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);
	if (result != 0)
		return result;
	result = Set_G05_Delay(DelayChannel_T0, FireFirst_T0, OutputModulo_T0,
								Active_T0, Positive_T0, Terminate_T0, HighDrive_T0, DG_Number);
	if (result != 0)
		return result;
	result = Set_G05_Delay(DelayChannel_A, FireFirst_A, OutputModulo_A,
								Active_A, Positive_A, Terminate_A, HighDrive_A, DG_Number);
	if (result != 0)
		return result;
	result = Set_G05_Delay(DelayChannel_B, FireFirst_B, OutputModulo_B,
								Active_B, Positive_B, Terminate_B, HighDrive_B, DG_Number);
	if (result != 0)
		return result;
	result = Set_Gate_AB(Gate_AB, DG_Number);
	if (result != 0)
		return result;
	if ((Action & 0x4) != 0)
		ResetOutputModuloCounters(DG_Number);
	Activate_DG_BME(DG_Number);
	return 0;
}

_declspec (dllexport) long CC Set_BME_G03(double FireFirst_T0, double SetBack_T0, BOOL Active_T0, 
													BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A, BOOL Active_A, 
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B, BOOL Active_B, 
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	long result;
	DG_InternalData* p_Present;
	unsigned long PulseWidth;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	PulseWidth = p_Present->DelayControlState.PulseWidth;
	if (p_Present->b_DG_Activated)
	{
		result = Modify_DG(0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													0, Active_A, Positive_A, Terminate_A, HighDrive_A,
													0, Active_B, Positive_B, Terminate_B, HighDrive_B,
													OutputLevel, TriggerTerminate, ClockEnable, PresetValue, 
													ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
		if ((result & 0x1) != 0)
			Deactivate_DG_BME(DG_Number);
	}

	result = Set_OutputLevel(OutputLevel, PulseWidth, DG_Number);
	if (result != 0)
		return result;
	result = Set_ClockParameters(ClockEnable, DivideBy, ClockSource,  DG_Number);
	if (result != 0)
		return result;
	result = Set_TriggerParameters(TriggerTerminate, InternalClock, 
													TriggerLevel, PresetValue, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);
	if (result != 0)
		return result;
	result = Set_G03_Delay(DelayChannel_T0, FireFirst_T0, SetBack_T0,
								Active_T0, Positive_T0, Terminate_T0, HighDrive_T0, DG_Number);
	if (result != 0)
		return result;
	result = Set_G03_Delay(DelayChannel_A, FireFirst_A, SetBack_A,
								Active_A, Positive_A, Terminate_A, HighDrive_A, DG_Number);
	if (result != 0)
		return result;
	result = Set_G03_Delay(DelayChannel_B, FireFirst_B, SetBack_B,
								Active_B, Positive_B, Terminate_B, HighDrive_B, DG_Number);
	if (result != 0)
		return result;
	result = Set_Gate_AB(Gate_AB, DG_Number);
	if (result != 0)
		return result;
	Activate_DG_BME(DG_Number);
	return 0;

}

_declspec (dllexport) long CC Set_BME_G02(double FireFirst_T0, BOOL Active_T0, BOOL Positive_T0, 
													BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, BOOL Active_A, BOOL Positive_A, 
													BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, BOOL Active_B, BOOL Positive_B, 
													BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	long result;
	DG_InternalData* p_Present;
	unsigned long PulseWidth;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	PulseWidth = p_Present->DelayControlState.PulseWidth;
	if (p_Present->b_DG_Activated)
	{
		result = Modify_DG(0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													0, Active_A, Positive_A, Terminate_A, HighDrive_A,
													0, Active_B, Positive_B, Terminate_B, HighDrive_B,
													OutputLevel, TriggerTerminate, ClockEnable, PresetValue, 
													ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
		if ((result & 0x1) != 0)
			Deactivate_DG_BME(DG_Number);
	}
	result = Set_OutputLevel(OutputLevel, PulseWidth, DG_Number);
	if (result != 0)
		return result;
	result = Set_ClockParameters(ClockEnable, DivideBy, ClockSource,  DG_Number);
	if (result != 0)
		return result;
	result = Set_TriggerParameters(TriggerTerminate, InternalClock, 
													TriggerLevel, PresetValue, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);
	if (result != 0)
		return result;
	result = Set_G02_Delay(DelayChannel_T0, FireFirst_T0, 
								Active_T0, Positive_T0, Terminate_T0, HighDrive_T0, DG_Number);
	if (result != 0)
		return result;
	result = Set_G02_Delay(DelayChannel_A, FireFirst_A, 
								Active_A, Positive_A, Terminate_A, HighDrive_A, DG_Number);
	if (result != 0)
		return result;
	result = Set_G02_Delay(DelayChannel_B, FireFirst_B, 
								Active_B, Positive_B, Terminate_B, HighDrive_B, DG_Number);
	if (result != 0)
		return result;
	result = Set_Gate_AB(Gate_AB, DG_Number);
	if (result != 0)
		return result;
	Activate_DG_BME(DG_Number);
	return 0;
}

_declspec (dllexport) long CC Set_TriggerParameters(BOOL TriggerTerminate, double InternalClock, 
													double TriggerLevel, unsigned long PresetValue, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));

	dgc.DT.InternalClock = InternalClock;
	dgc.DT.TriggerLevel = TriggerLevel;
	dgc.DT.PresetValue = PresetValue;
	dgc.DT.GateDivider = GateDivider;
	dgc.DT.PositiveGate = PositiveGate;
	dgc.DT.InternalTrigger = InternalTrigger;
	dgc.DT.InternalArm = InternalArm;
	dgc.DT.SoftwareTrigger = SoftwareTrigger;
	dgc.DT.RisingEdge = RisingEdge;
	dgc.DT.StopOnPreset = StopOnPreset;
	dgc.DT.ResetWhenDone = ResetWhenDone;
	dgc.DT.TriggerEnable = TriggerEnable;
	dgc.DT.Terminate = TriggerTerminate;

	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G08_TriggerParameters(BOOL GateTerminate, double GateLevel, double GateDelay,
													BOOL IgnoreGate, BOOL SynchronizeGate, double ForceTrigger,
													double StepBackTime, unsigned long BurstCounter, unsigned long MS_Bus,  long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));

	dgc.DT.GateTerminate = GateTerminate;
	dgc.DT.GateLevel = GateLevel;
	dgc.DT.GateDelay = GateDelay;
	dgc.DT.IgnoreGate = IgnoreGate;
	dgc.DT.SynchronizeGate = SynchronizeGate;
	dgc.DT.ForceTrigger = ForceTrigger;
	dgc.DT.StepBackTime = StepBackTime;
	dgc.DT.BurstCounter = BurstCounter;
	dgc.DT.MS_Bus = MS_Bus;

	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_V2_TriggerParameters(BOOL IgnoreGate, BOOL SynchronizeGate, double ForceTrigger, 
																			 unsigned long MS_Bus, long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));

	dgc.DT.IgnoreGate = IgnoreGate;
	dgc.DT.SynchronizeGate = SynchronizeGate;
	dgc.DT.ForceTrigger = ForceTrigger;
	dgc.DT.MS_Bus = MS_Bus;

	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_ClockParameters(BOOL ClockEnable, unsigned long DivideBy, unsigned long ClockSource, 
																	long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.DT.DivideBy = DivideBy;
	switch (ClockSource)
	{
		case TriggerInput:
		case TriggerAndOscillator:
			if (dgc.DT.TriggerDivider == 0)
				dgc.DT.TriggerDivider = dgc.DT.OscillatorDivider;
			break;
		default:
			break;
	}
	dgc.DT.ClockSource = ClockSource;
	dgc.DT.ClockEnable = ClockEnable;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G08_ClockParameters(BOOL ClockEnable, unsigned long OscillatorDivider, 
																				unsigned long TriggerDivider, unsigned long TriggerMultiplier, 
																				unsigned long ClockSource, long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.DT.OscillatorDivider = (unsigned short)(OscillatorDivider & 0xFFFF);
	dgc.DT.TriggerDivider = (unsigned short)(TriggerDivider & 0xFFFF);
	dgc.DT.TriggerMultiplier = TriggerMultiplier;
	switch (ClockSource)
	{
		case TriggerInput:
		case TriggerAndOscillator:
			if (dgc.DT.TriggerDivider == 0)
				dgc.DT.TriggerDivider = dgc.DT.OscillatorDivider;
			break;
		default:
			break;
	}
	dgc.DT.ClockSource = ClockSource;
	dgc.DT.ClockEnable = ClockEnable;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_Gate_AB(BOOL Gate_AB, long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.Gate_AB = Gate_AB;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_GateFunction(unsigned long GateFunction, long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.GateFunction = GateFunction;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_OutputLevel(unsigned long OutputLevel, unsigned long PulseWidth, long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.PulseWidth = min(255, max(0, PulseWidth));
	dgc.OutputLevel = OutputLevel;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G02_Delay(unsigned long Channel, double FireFirst, 
														BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
														long DG_Number)
{
	DG_BME_Control dgc;
	DelayChannelData* p_ch;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(dgc.T0);
		break;
	case DelayChannel_A:
		p_ch = &(dgc.A);
		break;
	case DelayChannel_B:
		p_ch = &(dgc.B);
		break;
	}
	
	if (Active)
	{
		p_ch->GoSignal |= MasterPrimary;
		p_ch->DoneSignal &= ~MasterPrimary;
	}
	else
	{
		p_ch->GoSignal &= 0x188;
		p_ch->DoneSignal = 0x0;
	}

	p_ch->FireFirst = FireFirst;
	p_ch->Positive = Positive;
	p_ch->Terminate = Terminate;
	p_ch->HighDrive = HighDrive;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G03_Delay(unsigned long Channel, 
													double FireFirst, double SetBack, 
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number)
{
	DG_BME_Control dgc;
	DelayChannelData* p_ch;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(dgc.T0);
		break;
	case DelayChannel_A:
		p_ch = &(dgc.A);
		break;
	case DelayChannel_B:
		p_ch = &(dgc.B);
		break;
	}

	if (Active)
	{
		p_ch->GoSignal |= MasterPrimary;
		p_ch->DoneSignal &= ~MasterPrimary;
	}
	else
	{
		p_ch->GoSignal &= 0x188;
		p_ch->DoneSignal = 0x0;
	}

	p_ch->FireFirst = FireFirst;
	p_ch->SetBack = SetBack;
	p_ch->Positive = Positive;
	p_ch->Terminate = Terminate;
	p_ch->HighDrive = HighDrive;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G05_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
														BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
														long DG_Number)
{
	DelayChannelData* p_ch;
	unsigned long GoSignal,DoneSignal;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(p_Present->DelayControlState.T0);
		break;
	case DelayChannel_A:
		p_ch = &(p_Present->DelayControlState.A);
		break;
	case DelayChannel_B:
		p_ch = &(p_Present->DelayControlState.B);
		break;
	case DelayChannel_C:
		p_ch = &(p_Present->DelayControlState.C);
		break;
	case DelayChannel_D:
		p_ch = &(p_Present->DelayControlState.D);
		break;
	case DelayChannel_E:
		p_ch = &(p_Present->DelayControlState.E);
		break;
	case DelayChannel_F:
		p_ch = &(p_Present->DelayControlState.F);
		break;
	}

	if (Active)
	{
		GoSignal = (p_ch->GoSignal | MasterPrimary);
		DoneSignal = (p_ch->DoneSignal & ~MasterPrimary);
	}
	else
	{
		GoSignal &= 0x388;
		DoneSignal = 0x0;
	}
	
	result = Set_G05P2_Delay(Channel, FireFirst, OutputModulo,
										GoSignal, DoneSignal, Positive, Terminate, HighDrive, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G05P2_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
															unsigned long GoSignal, unsigned long DoneSignal,
															BOOL Positive, BOOL Terminate, BOOL HighDrive, long DG_Number)
{
	DG_BME_Control dgc;
	DelayChannelData* p_ch;
	unsigned short *p_modulo;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(dgc.T0);
		break;
	case DelayChannel_A:
		p_ch = &(dgc.A);
		break;
	case DelayChannel_B:
		p_ch = &(dgc.B);
		break;
	case DelayChannel_C:
		p_ch = &(dgc.C);
		break;
	case DelayChannel_D:
		p_ch = &(dgc.D);
		break;
	case DelayChannel_E:
		p_ch = &(dgc.E);
		break;
	case DelayChannel_F:
		p_ch = &(dgc.F);
		break;
	}

	p_ch->GoSignal = GoSignal;
	p_ch->DoneSignal = DoneSignal;
	
	p_modulo = (unsigned short*)&OutputModulo;
	p_ch->OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	p_ch->OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);

	p_ch->FireFirst = FireFirst;
	p_ch->ListLength = 1;
	p_ch->Positive = Positive;
	p_ch->Terminate = Terminate;
	p_ch->HighDrive = HighDrive;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_DelayList(unsigned long Channel, double* p_DelayTime, double* p_PulseWidth, 
															unsigned long* p_StepBack, signed long ListLength, long DG_Number)
{
	DG_BME_Control dgc;
	DelayChannelData* p_ch;
	long result;
	int k1;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(dgc.T0);
		break;
	case DelayChannel_A:
		p_ch = &(dgc.A);
		break;
	case DelayChannel_B:
		p_ch = &(dgc.B);
		break;
	case DelayChannel_C:
		p_ch = &(dgc.C);
		break;
	case DelayChannel_D:
		p_ch = &(dgc.D);
		break;
	case DelayChannel_E:
		p_ch = &(dgc.E);
		break;
	case DelayChannel_F:
		p_ch = &(dgc.F);
		break;
	}

	p_ch->ListLength = min(ListLength, MemLength);
	for (k1 = 0; k1 < p_ch->ListLength; k1++)
	{
		p_ch->DelayTime[k1] = *(p_DelayTime + k1);
		p_ch->PulseWidth[k1] = *(p_PulseWidth + k1);
		p_ch->StepBack[k1] = *(p_StepBack + k1);
	}

	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G08_Delay(unsigned long Channel, double FireFirst, double PulseWidth, 
															unsigned long OutputModulo, unsigned long OutputOffset, 
															unsigned long GoSignal, BOOL Positive, BOOL Terminate, 
															BOOL Disconnect, BOOL OntoMsBus, BOOL InputPositive, long DG_Number)
{
	DG_BME_Control dgc;
	DelayChannelData* p_ch;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	switch (Channel)
	{
	case DelayChannel_T0:
		p_ch = &(dgc.T0);
		break;
	case DelayChannel_A:
		p_ch = &(dgc.A);
		break;
	case DelayChannel_B:
		p_ch = &(dgc.B);
		break;
	case DelayChannel_C:
		p_ch = &(dgc.C);
		break;
	case DelayChannel_D:
		p_ch = &(dgc.D);
		break;
	case DelayChannel_E:
		p_ch = &(dgc.E);
		break;
	case DelayChannel_F:
		p_ch = &(dgc.F);
		break;
	}

	p_ch->GoSignal = GoSignal;
	
	p_ch->OutputModulo = OutputModulo;
	p_ch->OutputOffset = OutputOffset;

	p_ch->FireFirst = FireFirst;
	p_ch->PulseWidth[0] = PulseWidth;
	p_ch->StepBack[0] = 0;
	p_ch->ListLength = 1;

	p_ch->Positive = Positive;
	p_ch->Terminate = Terminate;

	p_ch->Disconnect = Disconnect;
	p_ch->OntoMsBus = OntoMsBus;
	p_ch->InputPositive = InputPositive;

	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}


_declspec (dllexport) long CC Set_CalibrationLevel(unsigned long CalibrationLevel, long DG_Number)
{
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	p_Present->CalibrationLevel = CalibrationLevel;
	return 0;
}

_declspec (dllexport) long CC Set_CalibrationForAll(unsigned long CalibrationLevel)
{
	long DG_Number;
	for (DG_Number = 0; DG_Number < NoDelayGenerators; DG_Number++)
		Set_CalibrationLevel(CalibrationLevel, DG_Number);
	return 0;
}

_declspec (dllexport) long CC Test_BME_G02(long DG_Number)
{
	double FireFirst_T0 = 3.0;
	BOOL Active_T0 = TRUE;
	BOOL Positive_T0 = FALSE;
	BOOL Terminate_T0 = FALSE;
	BOOL HighDrive_T0 = FALSE;

	double FireFirst_A = 10.0;
	BOOL Active_A = TRUE;
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = FALSE;
	BOOL HighDrive_A = FALSE;

	double FireFirst_B = 21.0;
	BOOL Active_B = TRUE;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;
	BOOL HighDrive_B = FALSE;

	unsigned long OutputLevel = TTL_VoltageLevel;
	BOOL Gate_AB = TRUE;
	//BOOL Gate_AB = FALSE;

	//BOOL TriggerTerminate = TRUE;
	BOOL TriggerTerminate = FALSE;
	BOOL ClockEnable = TRUE;
	//double InternalClock = 1250.0;
	double InternalClock = 100.0;
	double TriggerLevel = 0.1;
	unsigned long PresetValue = 100000;
  //unsigned long PresetValue = 500000;
	unsigned long DivideBy = 0x40004;
	//unsigned long DivideBy = 4;
	//unsigned long ClockSource = CrystalOscillator;
	unsigned long ClockSource = TriggerInput;
	unsigned long GateDivider = 1;
	BOOL PositiveGate = TRUE;
	BOOL InternalTrigger = TRUE;
	BOOL InternalArm = FALSE;
	BOOL SoftwareTrigger = FALSE;
	BOOL RisingEdge = TRUE;
	BOOL StopOnPreset = FALSE;
	BOOL ResetWhenDone = TRUE;
	BOOL TriggerEnable = TRUE;

	long result;
	result = Set_BME_G02(FireFirst_T0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													FireFirst_A, Active_A, Positive_A, Terminate_A, HighDrive_A,
													FireFirst_B, Active_B, Positive_B, Terminate_B, HighDrive_B,
													Gate_AB, OutputLevel, TriggerTerminate, ClockEnable,
													InternalClock, TriggerLevel, PresetValue, 
													DivideBy, ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
	return result;
}

_declspec (dllexport) long CC Test_BME_G03(long DG_Number)
{
	
	double FireFirst_T0 = 3.0;
	double SetBack_T0 = 8.0;
	BOOL Active_T0 = TRUE;
	BOOL Positive_T0 = FALSE;
	BOOL Terminate_T0 = FALSE;
	BOOL HighDrive_T0 = FALSE;

	double FireFirst_A = 10.0;
	double SetBack_A = 15.0;
	BOOL Active_A = TRUE;
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = FALSE;
	BOOL HighDrive_A = FALSE;

	double FireFirst_B = 11.0;
	double SetBack_B = 16.0;
	BOOL Active_B = TRUE;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;
	BOOL HighDrive_B = FALSE;

	unsigned long OutputLevel = TTL_VoltageLevel;
	BOOL Gate_AB = TRUE;
	//BOOL Gate_AB = FALSE;

	BOOL TriggerTerminate = FALSE;
	BOOL ClockEnable = TRUE;
	double InternalClock = 500.0;
	double TriggerLevel = 1.25;
	unsigned long PresetValue = 100000;
  //unsigned long PresetValue = 10000000;
	unsigned long DivideBy = 1;
	unsigned long ClockSource = CrystalOscillator;
	unsigned long GateDivider = 1;
	BOOL PositiveGate = TRUE;
	BOOL InternalTrigger = TRUE;
	BOOL InternalArm = FALSE;
	BOOL SoftwareTrigger = FALSE;
	BOOL RisingEdge = TRUE;
	BOOL StopOnPreset = TRUE;
	BOOL ResetWhenDone = TRUE;
	BOOL TriggerEnable = TRUE;

	/*
	double FireFirst_T0 = 1.0;
	double SetBack_T0 = 0.0;
	BOOL Active_T0 = TRUE;
	BOOL Positive_T0 = TRUE;
	BOOL Terminate_T0 = FALSE;
	BOOL HighDrive_T0 = FALSE;

	double FireFirst_A = 2.0;
	double SetBack_A = 0.0;
	BOOL Active_A = TRUE;
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = FALSE;
	BOOL HighDrive_A = FALSE;

	double FireFirst_B = 3.0;
	double SetBack_B = 0.0;
	BOOL Active_B = TRUE;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;
	BOOL HighDrive_B = FALSE;

	unsigned long OutputLevel = TTL_VoltageLevel;
	BOOL Gate_AB = TRUE;
	//BOOL Gate_AB = FALSE;

	BOOL TriggerTerminate = FALSE;
	BOOL ClockEnable = TRUE;
	double InternalClock = 123.0;
	double TriggerLevel = 1.25;
	unsigned long PresetValue = 100000;
  //unsigned long PresetValue = 10000000;
	unsigned long DivideBy = 8;
	unsigned long ClockSource = CrystalOscillator;
	unsigned long GateDivider = 1;
	BOOL PositiveGate = TRUE;
	BOOL InternalTrigger = TRUE;
	BOOL InternalArm = FALSE;
	BOOL SoftwareTrigger = FALSE;
	BOOL RisingEdge = TRUE;
	BOOL StopOnPreset = FALSE;
	BOOL ResetWhenDone = TRUE;
	BOOL TriggerEnable = TRUE;
	*/

	long result = 0;
	result = Set_BME_G03(FireFirst_T0, SetBack_T0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													FireFirst_A, SetBack_A, Active_A, Positive_A, Terminate_A, HighDrive_A,
													FireFirst_B, SetBack_B, Active_B, Positive_B, Terminate_B, HighDrive_B,
													Gate_AB, OutputLevel, TriggerTerminate, ClockEnable,
													InternalClock, TriggerLevel, PresetValue, 
													DivideBy, ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
	return result;
}

_declspec (dllexport) long CC Test_BME_G05(long DG_Number)
{
	double FireFirst_T0 = 3.0;
	unsigned long OutputModulo_T0 = 0;
	BOOL Active_T0 = TRUE;
	BOOL Positive_T0 = FALSE;
	BOOL Terminate_T0 = FALSE;
	BOOL HighDrive_T0 = FALSE;

	double FireFirst_A = 10.0;
	unsigned long OutputModulo_A = 1;
	BOOL Active_A = TRUE;
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = FALSE;
	BOOL HighDrive_A = FALSE;

	double FireFirst_B = 11.0;
	unsigned long OutputModulo_B = 3;
	BOOL Active_B = TRUE;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;
	BOOL HighDrive_B = FALSE;

	unsigned long OutputLevel = TTL_VoltageLevel;
	BOOL Gate_AB = TRUE;
	//BOOL Gate_AB = FALSE;

	BOOL TriggerTerminate = FALSE;
	BOOL ClockEnable = TRUE;
	double InternalClock = 500.0;
	double TriggerLevel = 1.25;
	unsigned long PresetValue = 100000;
  //unsigned long PresetValue = 10000000;
	unsigned long DivideBy = 1;
	unsigned long ClockSource = CrystalOscillator;
	unsigned long GateDivider = 1;
	BOOL PositiveGate = TRUE;
	BOOL InternalTrigger = TRUE;
	BOOL InternalArm = FALSE;
	BOOL SoftwareTrigger = FALSE;
	BOOL RisingEdge = TRUE;
	BOOL StopOnPreset = TRUE;
	BOOL ResetWhenDone = TRUE;
	BOOL TriggerEnable = TRUE;

	long result;
	result = Set_BME_G05(FireFirst_T0, OutputModulo_T0, Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													FireFirst_A, OutputModulo_A, Active_A, Positive_A, Terminate_A, HighDrive_A,
													FireFirst_B, OutputModulo_B, Active_B, Positive_B, Terminate_B, HighDrive_B,
													Gate_AB, OutputLevel, TriggerTerminate, ClockEnable,
													InternalClock, TriggerLevel, PresetValue, 
													DivideBy, ClockSource, GateDivider,
													PositiveGate, InternalTrigger, InternalArm, SoftwareTrigger,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable,
													DG_Number);
	return result;
}


_declspec (dllexport) long CC Test_BME_G08(long DG_Number)
{
	double FireFirst_A = 0.02;
	double PulseWidth_A = 0.005;
	unsigned long OutputModulo_A = 1;
	unsigned long OutputOffset_A = 0;
	unsigned long GoSignal_A = SystemClock | DelayClock;     // channel A will give out the internal clock signal
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = TRUE;

	double FireFirst_B = 0.02;
	double PulseWidth_B = 0.005;
	unsigned long OutputModulo_B = 1;
	unsigned long OutputOffset_B = 0;
	unsigned long GoSignal_B = MasterPrimary;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;

	double FireFirst_C = 0.01;
	double PulseWidth_C = 0.005;
	unsigned long OutputModulo_C = 1;
	unsigned long OutputOffset_C = 0;
	unsigned long GoSignal_C = MasterPrimary;
	BOOL Positive_C = TRUE;
	BOOL Terminate_C = FALSE;

	double FireFirst_D = 0.005;
	double PulseWidth_D = 0.005;
	unsigned long OutputModulo_D = 1;
	unsigned long OutputOffset_D = 0;
	unsigned long GoSignal_D = MasterPrimary;
	BOOL Positive_D = TRUE;
	BOOL Terminate_D = FALSE;

	double FireFirst_E = 0.0;
	double PulseWidth_E = 0.005;
	unsigned long OutputModulo_E = 1;
	unsigned long OutputOffset_E = 0;
	unsigned long GoSignal_E = MasterPrimary;
	BOOL Positive_E = TRUE;
	BOOL Terminate_E = FALSE;
	BOOL Disconnect_E = FALSE;
	BOOL OntoMsBus_E = FALSE;
	BOOL InputPositive_E = TRUE;

	double FireFirst_F = 0.0;
	double PulseWidth_F = 0.005;
	unsigned long OutputModulo_F = 1;
	unsigned long OutputOffset_F = 0;
	unsigned long GoSignal_F = MasterPrimary;
	BOOL Positive_F = TRUE;
	BOOL Terminate_F = FALSE;
	BOOL Disconnect_F = FALSE;
	BOOL OntoMsBus_F = FALSE;
	BOOL InputPositive_F = TRUE;

	unsigned long GateFunction = 0x0;
	BOOL ClockEnable = TRUE;
	unsigned long OscillatorDivider = 2;
	unsigned long TriggerDivider = 1;
	unsigned long TriggerMultiplier = 4;
	unsigned long ClockSource = TriggerAndOscillator;
	//unsigned long ClockSource = CrystalOscillator;

	BOOL TriggerTerminate = TRUE;
	BOOL GateTerminate = TRUE;
	double TriggerLevel = 0.0;              
	double GateLevel = 1.0;                 
	double GateDelay = -1.0;								// not used
	unsigned long MS_Bus = LocalPrimary;
	//double InternalClock = 0.0;             // set to minimum
	double InternalClock = 0.1;             // set 10MHz
	//double InternalClock = 100.0;             // set 10kHz
	unsigned long PresetValue = 0x0;
	unsigned long GateDivider = 1;          // gives 1 output pulse per level crossing of the gate signal
	//unsigned long GateDivider = 0;          // gives output pulses as long as the gate signal is high
	double ForceTrigger = -1.0;             // not used
	double StepBackTime = -1.0;             // not used
	unsigned long BurstCounter = 1;         // set to minimum 
	//unsigned long BurstCounter = 10;         // Burst of 10 pulses
	BOOL PositiveGate = TRUE;
	BOOL InternalTrigger = TRUE;
	BOOL IgnoreGate = TRUE;
	BOOL SynchronizeGate = FALSE;
	BOOL RisingEdge = TRUE;
	BOOL StopOnPreset = FALSE;
	BOOL ResetWhenDone = TRUE;
	BOOL TriggerEnable = TRUE;
	//BOOL TriggerEnable = FALSE;              // Gate Mode

	long result;

	result = Set_BME_G08(FireFirst_A, PulseWidth_A, OutputModulo_A, OutputOffset_A, GoSignal_A, Positive_A, Terminate_A,
													FireFirst_B, PulseWidth_B, OutputModulo_B, OutputOffset_B, GoSignal_B, Positive_B, Terminate_B,
													FireFirst_C, PulseWidth_C, OutputModulo_C, OutputOffset_C, GoSignal_C, Positive_C, Terminate_C,
													FireFirst_D, PulseWidth_D, OutputModulo_D, OutputOffset_D, GoSignal_D, Positive_D, Terminate_D,
													FireFirst_E, PulseWidth_E, OutputModulo_E, OutputOffset_E, GoSignal_E, Positive_E, Terminate_E,
													Disconnect_E, OntoMsBus_E, InputPositive_E,
													FireFirst_F, PulseWidth_F, OutputModulo_F, OutputOffset_F, GoSignal_F, Positive_F, Terminate_F,
													Disconnect_F, OntoMsBus_F, InputPositive_F,
													GateFunction, ClockEnable, OscillatorDivider, TriggerDivider, TriggerMultiplier,
													ClockSource, TriggerTerminate, GateTerminate, TriggerLevel, GateLevel, GateDelay, MS_Bus,
													InternalClock, PresetValue, GateDivider, ForceTrigger, StepBackTime, BurstCounter,
													PositiveGate, InternalTrigger, IgnoreGate, SynchronizeGate,
													RisingEdge, StopOnPreset, ResetWhenDone, TriggerEnable, DG_Number);

	return result;
}

_declspec (dllexport) long CC ResetControl(DG_BME_Control* p_DGControl)
{
	p_DGControl->PulseWidth = 0;
	p_DGControl->Gate_AB = FALSE;
	p_DGControl->OutputLevel = TTL_VoltageLevel;
	p_DGControl->DG_Product = -1;
	p_DGControl->GateFunction = 0x0;
	ResetDelayControl(&(p_DGControl->T0));
	ResetDelayControl(&(p_DGControl->A));
	ResetDelayControl(&(p_DGControl->B));
	ResetDelayControl(&(p_DGControl->C));
	ResetDelayControl(&(p_DGControl->D));
	ResetDelayControl(&(p_DGControl->E));
	ResetDelayControl(&(p_DGControl->F));
	ResetTriggerControl(&(p_DGControl->DT));
	return 0;
}

_declspec (dllexport) long CC ResetRegisters(DG_BME_Registers* p_DGState)
{
	p_DGState->PulseWidth = 8;
	p_DGState->Gate_AB = FALSE;
	p_DGState->OutputLevel = TTL_VoltageLevel;
	p_DGState->DG_Product = -1;
	p_DGState->GateFunction = 0x0;
	ResetDelayChannel(&(p_DGState->T0));
	ResetDelayChannel(&(p_DGState->A));
	ResetDelayChannel(&(p_DGState->B));
	ResetDelayChannel(&(p_DGState->C));
	ResetDelayChannel(&(p_DGState->D));
	ResetDelayChannel(&(p_DGState->E));
	ResetDelayChannel(&(p_DGState->F));
	ResetMainCounter(&(p_DGState->MC));
	ResetDelayTrigger(&(p_DGState->DT));
	return 0;
}

_declspec (dllexport) long CC ResetState(DG_BME_State* p_DGS)
{
	ResetControl(&(p_DGS->Control));
	p_DGS->BaseAddress = -1;
	p_DGS->BusNumber = -1;
	p_DGS->Master = FALSE;
	p_DGS->DG_Product = -1;
	memset(&(p_DGS->ip_address), 0, (40 * sizeof(char)));
	return 0;
}

_declspec (dllexport) long CC CopyState_V1(DG_BME_State* p_DGS, DG_BME_State_V1* p_DGS_V1)
{
	ResetState(p_DGS);
	p_DGS->BaseAddress = p_DGS_V1->BaseAddress;
	p_DGS->Master = p_DGS_V1->Master;
	p_DGS->DG_Product = p_DGS_V1->DG_Product;
	CopyControl(&(p_DGS->Control), &(p_DGS_V1->Control));
	return 0;
}

_declspec (dllexport) long CC CopyState_V2(DG_BME_State* p_DGS, DG_BME_State_V2* p_DGS_V2)
{
	ResetState(p_DGS);
	p_DGS->BaseAddress = p_DGS_V2->BaseAddress;
	p_DGS->Master = p_DGS_V2->Master;
	p_DGS->DG_Product = p_DGS_V2->DG_Product;
	CopyControl_V2(&(p_DGS->Control), &(p_DGS_V2->Control));
	return 0;
}

_declspec (dllexport) long CC CopyState_V3(DG_BME_State* p_DGS, DG_BME_State_V3* p_DGS_V3)
{
	ResetState(p_DGS);
	p_DGS->BaseAddress = p_DGS_V3->BaseAddress;
	p_DGS->Master = p_DGS_V3->Master;
	p_DGS->DG_Product = p_DGS_V3->DG_Product;
	p_DGS->BusNumber = p_DGS_V3->BusNumber;
	CopyControl_V3(&(p_DGS->Control), &(p_DGS_V3->Control));
	return 0;
}

_declspec (dllexport) long CC CopyState_V4(DG_BME_State* p_DGS, DG_BME_State_V4* p_DGS_V4)
{
	ResetState(p_DGS);
	p_DGS->BaseAddress = p_DGS_V4->BaseAddress;
	p_DGS->Master = p_DGS_V4->Master;
	p_DGS->DG_Product = p_DGS_V4->DG_Product;
	p_DGS->BusNumber = p_DGS_V4->BusNumber;
	CopyControl_V4(&(p_DGS->Control), &(p_DGS_V4->Control));
	return 0;
}

_declspec (dllexport) long CC CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V1* p_Control_V1)
{
	ResetControl(p_Control);
	CopyTriggerControl_V1(&(p_Control->DT), &(p_Control_V1->DT));
	CopyDelayControl_V2(&(p_Control->T0), &(p_Control_V1->T0));
	CopyDelayControl_V2(&(p_Control->A), &(p_Control_V1->A));
	CopyDelayControl_V2(&(p_Control->B), &(p_Control_V1->B));
	p_Control->Gate_AB = p_Control_V1->Gate_AB;
	if (p_Control->Gate_AB)
		p_Control->GateFunction = GateXOR;
	p_Control->OutputLevel = p_Control_V1->OutputLevel;
	p_Control->DG_Product = p_Control_V1->DG_Product;
	p_Control->PulseWidth = p_Control_V1->PulseWidth;
	return 0;
}

_declspec (dllexport) long CC CopyControl_V2(DG_BME_Control* p_Control, DG_BME_Control_V2* p_Control_V2)
{
	ResetControl(p_Control);
	CopyTriggerControl_V2(&(p_Control->DT), &(p_Control_V2->DT));
	CopyDelayControl_V2(&(p_Control->T0), &(p_Control_V2->T0));
	CopyDelayControl_V2(&(p_Control->A), &(p_Control_V2->A));
	CopyDelayControl_V2(&(p_Control->B), &(p_Control_V2->B));
	p_Control->Gate_AB = p_Control_V2->Gate_AB;
	if (p_Control->Gate_AB)
		p_Control->GateFunction = GateXOR;
	p_Control->OutputLevel = p_Control_V2->OutputLevel;
	p_Control->DG_Product = p_Control_V2->DG_Product;
	p_Control->PulseWidth = p_Control_V2->PulseWidth;
	return 0;
}

_declspec (dllexport) long CC CopyControl_V3(DG_BME_Control* p_Control, DG_BME_Control_V3* p_Control_V3)
{
	ResetControl(p_Control);
	CopyTriggerControl_V3(&(p_Control->DT), &(p_Control_V3->DT));
	CopyDelayControl_V3(&(p_Control->T0), &(p_Control_V3->T0));
	CopyDelayControl_V3(&(p_Control->A), &(p_Control_V3->A));
	CopyDelayControl_V3(&(p_Control->B), &(p_Control_V3->B));
	p_Control->Gate_AB = p_Control_V3->Gate_AB;
	if (p_Control->Gate_AB)
		p_Control->GateFunction = GateXOR;
	p_Control->OutputLevel = p_Control_V3->OutputLevel;
	p_Control->DG_Product = p_Control_V3->DG_Product;
	p_Control->PulseWidth = p_Control_V3->PulseWidth;
	return 0;
}

_declspec (dllexport) long CC CopyControl_V4(DG_BME_Control* p_Control, DG_BME_Control_V4* p_Control_V4)
{
	ResetControl(p_Control);
	CopyTriggerControl_V4(&(p_Control->DT), &(p_Control_V4->DT));
	memcpy(&(p_Control->T0), &(p_Control_V4->T0), sizeof(DelayChannelData));
	memcpy(&(p_Control->A), &(p_Control_V4->A), sizeof(DelayChannelData));
	memcpy(&(p_Control->B), &(p_Control_V4->B), sizeof(DelayChannelData));
	memcpy(&(p_Control->C), &(p_Control_V4->C), sizeof(DelayChannelData));
	memcpy(&(p_Control->D), &(p_Control_V4->D), sizeof(DelayChannelData));
	memcpy(&(p_Control->E), &(p_Control_V4->E), sizeof(DelayChannelData));
	memcpy(&(p_Control->F), &(p_Control_V4->F), sizeof(DelayChannelData));
	p_Control->Gate_AB = p_Control_V4->Gate_AB;
	p_Control->GateFunction = p_Control_V4->GateFunction;
	p_Control->OutputLevel = p_Control_V4->OutputLevel;
	p_Control->DG_Product = p_Control_V4->DG_Product;
	p_Control->PulseWidth = p_Control_V4->PulseWidth;
	return 0;
}

_declspec (dllexport) long CC Deactivate_DG_BME(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long cntrl;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case BME_DP01:
	case SRS_DG135:
		cntrl &= 0x20;
		break;
	case BME_SG08P2:
		cntrl = p_Present->CommandRegister & 0x3FFE7B;
		break;
	default:
		cntrl = p_Present->CommandRegister & 0x3F3E2B;
	}
	LoadCommandRegister(&cntrl, p_Present);
	p_Present->b_DG_Activated = FALSE;
	return 0;
}

_declspec (dllexport) long CC Activate_DG_BME(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long cntrl;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		LoadCounterControl(p_Present->CounterControlRegister, p_Present);
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_SG08P2:
		if ((p_Present->CommandRegisterState & 0x80) == 0x0)
		{
			cntrl = p_Present->CommandRegister & ~0x80;
			LoadCommandRegister(&cntrl, p_Present);
		}
	default:
		LoadCommandRegister(&p_Present->CommandRegister, p_Present);
	}
	p_Present->b_DG_Activated = TRUE;
	return 0;
}

_declspec (dllexport) long CC SoftwareTrigger_DG_BME(long DG_Number)
{
	unsigned long cntrl;
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		cntrl = p_Present->CommandRegister & 0x3F3EFE;
		LoadCommandRegister(&cntrl, p_Present);
		cntrl = p_Present->CommandRegister | 0x01;
		LoadCommandRegister(&cntrl, p_Present);
		break;
	default:
		return 5;
	}
	return 0;
}

_declspec (dllexport) long CC ResetEventCounter(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short Value;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Value = 0x01;
	DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
	return 0;
}

_declspec (dllexport) long CC ResetOutputModuloCounters(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short Value;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Value = 0x20;
	DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
	return 0;
}

_declspec (dllexport) long CC ResetAllOutputModuloCounters()
{
	DG_InternalData* p_Present;
	unsigned short Value;
	unsigned long DG_Product;
	long DG_Number;
	Value = 0x20;
	for (DG_Number = 0; DG_Number < NoDelayGenerators; DG_Number++)
	{
		p_Present = (p_Internal + DG_Number);
		DG_Product = p_Present->DG_Product;
		switch (DG_Product)
		{
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
				break;
			default:
				break;
		}
	}
	return 0;
}

_declspec (dllexport) long CC JumpStartAllLists()
{
	DG_InternalData* p_Present;
	unsigned short Value;
	unsigned long DG_Product;
	long DG_Number;
	//unsigned long result;
	//char info[400];
	//int len;
	Value = 0x40;
	for (DG_Number = 0; DG_Number < NoDelayGenerators; DG_Number++)
	{
		p_Present = (p_Internal + DG_Number);
		DG_Product = p_Present->DG_Product;
		switch (DG_Product)
		{
			case BME_SG08P1:
			case BME_SG08P2:
				//result = Read_DG_Status(DG_Number);
				//len = sprintf(info,"Status      : %x \n", result);
				//result = ReadCounterControlRegister(DG_Number);
				//len += sprintf(&(info[len]),"CntControl : %x \n", result);
				//Data32In(p_Present->Delay_A, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel A : %x \n", result);
				//Data32In(p_Present->Delay_B, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel B : %x \n", result);
				//Data32In(p_Present->Delay_C, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel C : %x \n", result);
				//Data32In(p_Present->Delay_D, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel D : %x \n", result);
				//Data32In(p_Present->Delay_E, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel E : %x \n", result);
				//Data32In(p_Present->Delay_F, &result, &(p_Present->PciDelgen), 4);
				//len += sprintf(&(info[len]),"Channel F : %x ", result);
				//AfxMessageBox(info, MB_OK, 0);	
				DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
				break;
			default:
				break;
		}
	}
	return 0;
}

_declspec (dllexport) long CC LoadCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long* p_LoadWord;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	p_LoadWord = &(p_Present->LoadVector);
	if (b_EventCounter)
		*p_LoadWord |= 0x01;
	switch (DG_Product)
	{
		case BME_SG08P1:
			*p_LoadWord &= ~0x18;
		case BME_SG08P2:
			*p_LoadWord |= 0x80000000;
			if (b_TimeList)
				*p_LoadWord |= 0x40;
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (b_ModuloCounter)
				*p_LoadWord |= 0x20;
			break;
		default:
			break;
	}
	Data32Out(p_Present->InitializeAddress, p_LoadWord, &(p_Present->PciDelgen), 4);
	*p_LoadWord = 0x0;
	return 0;
}

_declspec (dllexport) long CC LoadAllCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList)
{
	long DG_Number;
	for (DG_Number = 0; DG_Number < NoDelayGenerators; DG_Number++)
		LoadCardParameters(b_EventCounter, b_ModuloCounter, b_TimeList, DG_Number);
	return 0;
}

_declspec (dllexport) long CC ResetCounter(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short Value;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	Value = 0x0;
	if (b_EventCounter)
		Value |= 0x01;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			if (b_TimeList)
				Value |= 0x40;
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (b_ModuloCounter)
				Value |= 0x20;
			break;
		default:
			break;
	}
	DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
	return 0;
}

_declspec (dllexport) long CC ResetCounterAllCards(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList)
{
	long DG_Number;
	for (DG_Number = 0; DG_Number < NoDelayGenerators; DG_Number++)
		ResetCounter(b_EventCounter, b_ModuloCounter, b_TimeList, DG_Number);
	return 0;
}

_declspec (dllexport) unsigned long CC ReadTriggerCounter(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long result = 0;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
		case BME_G02V1:
			DataIn(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), -1);
			if ((result & 0x10) != 0)
				return 0xFFFFFFFF;
			DataIn(p_Present->ModuloCounterAddress, &result, &(p_Present->PciDelgen), 4);
			break;
		case BME_G02V2:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_G03V1:
			DataIn(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), -1);
			if ((result & 0x10) != 0)
				return 0xFFFFFFFF;
		case BME_G02V3:
		case BME_SG02V3:
		case BME_SG02V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			DataIn(p_Present->TriggerCounterAddress, &result, &(p_Present->PciDelgen), 4);
			break;
		default:
			break;
	}
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) long CC Read64BitTriggerCounter(_int64* p_result, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long result = 0;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	*p_result = 0x0;
	switch (DG_Product)
	{
		case BME_G02V1:
			DataIn(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), -1);
			if ((result & 0x10) != 0)
			{
				*p_result = 0xFFFFFFFF;
				return 0;
			}
			DataIn(p_Present->ModuloCounterAddress, p_result, &(p_Present->PciDelgen), 4);
			break;
		case BME_G02V2:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_G03V1:
			DataIn(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), -1);
			if ((result & 0x10) != 0)
			{
				*p_result = 0xFFFFFFFF;
				return 0;
			}
		case BME_G02V3:
		case BME_SG02V3:
		case BME_SG02V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			DataIn(p_Present->TriggerCounterAddress, p_result, &(p_Present->PciDelgen), 4);
			break;
		case BME_SG08P1:
		case BME_SG08P2:
			Data32In(p_Present->TriggerCounterAddress, p_result, &(p_Present->PciDelgen), 8);
			break;
		default:
			break;
	}
	return 0;
}

_declspec (dllexport) long CC ReadFrequencyCounter(double* p_Frequency, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long result;
	unsigned long* p_result = &result;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	result = 0;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32In(p_Present->FrequencyCounterAddress, p_result, &(p_Present->PciDelgen), 4);
			*p_Frequency = ((double)result) / 1000000.0;
			break;
		default:
			*p_Frequency = 0.0;
			break;
	}
	return 0;
}

_declspec (dllexport) long CC EnableInterrupts(unsigned long value, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short IntCntrl = (unsigned short) value;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DataOut(p_Present->InterruptEnableAddress, &IntCntrl, &(p_Present->PciDelgen), -1);
	return 0;
}

_declspec (dllexport) unsigned long CC Read_DG_Status(long DG_Number)
{
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32In(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), 4);
			break;
		default:
			DataIn(p_Present->CommandAddress, &result, &(p_Present->PciDelgen), -1);
			break;
	}
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) unsigned long CC ReadCounterControlRegister(long DG_Number)
{
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32In(p_Present->CounterControlAddress, &result, &(p_Present->PciDelgen), 4);
			break;
		default:
			DataIn(p_Present->CounterControlAddress, &result, &(p_Present->PciDelgen), -1);
			break;
	}

	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) unsigned long CC ReadInterruptStatus(long DG_Number)
{
	Register32	tvl;
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32In(p_Present->InterruptEnableAddress, &(tvl.Value), &(p_Present->PciDelgen), 4);
			result = (unsigned long)tvl.HighWord;
			break;
		default:
			DataIn(p_Present->InterruptEnableAddress, &result, &(p_Present->PciDelgen), -1);
			break;
	}
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) long CC AcknowledgeInterrupts(unsigned long value, long DG_Number)
{
	unsigned short IntCntrl = (unsigned short) value;
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32Out(p_Present->InterruptAcknowledgeAddress, &value, &(p_Present->PciDelgen), 4);
			break;
		default:
			DataOut(p_Present->InterruptAcknowledgeAddress, &IntCntrl, &(p_Present->PciDelgen), -1);
			break;
	}
	return 0;
}

_declspec (dllexport) long CC LoadOutputState(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long cntrl;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	cntrl = p_Present->CommandRegisterState;
	if ((cntrl & 0x80) == 0)
	{
		cntrl |= 0x80;
		Data32Out(p_Present->CommandAddress, &cntrl, &(p_Present->PciDelgen), -1);
		cntrl &= 0x3F3E7F;
		Data32Out(p_Present->CommandAddress, &cntrl, &(p_Present->PciDelgen), -1);
	}
	else
	{
		cntrl &= 0x3F3E7F;
		Data32Out(p_Present->CommandAddress, &cntrl, &(p_Present->PciDelgen), -1);
		cntrl |= 0x80;
		Data32Out(p_Present->CommandAddress, &cntrl, &(p_Present->PciDelgen), -1);
	}
	return 0;
}

_declspec (dllexport) unsigned long CC Modify_DG(unsigned long OutputModulo_T0, BOOL Active_T0, 
																 BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													unsigned long OutputModulo_A, BOOL Active_A,
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													unsigned long OutputModulo_B, BOOL Active_B,
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													unsigned long PresetValue, 
													unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	unsigned short *p_modulo;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.OutputLevel = OutputLevel;

	dgc.DT.ClockSource = ClockSource;
	dgc.DT.ClockEnable = ClockEnable;

	dgc.DT.PresetValue = PresetValue;
	dgc.DT.GateDivider = GateDivider;
	dgc.DT.PositiveGate = PositiveGate;
	dgc.DT.InternalTrigger = InternalTrigger;
	dgc.DT.InternalArm = InternalArm;
	dgc.DT.SoftwareTrigger = SoftwareTrigger;
	dgc.DT.RisingEdge = RisingEdge;
	dgc.DT.StopOnPreset = StopOnPreset;
	dgc.DT.ResetWhenDone = ResetWhenDone;
	dgc.DT.TriggerEnable = TriggerEnable;
	dgc.DT.Terminate = TriggerTerminate;

	if (Active_T0)
	{
		dgc.T0.GoSignal |= MasterPrimary;
		dgc.T0.DoneSignal &= ~MasterPrimary;
	}
	else
	{
		dgc.T0.GoSignal &= 0x388;
		dgc.T0.DoneSignal = 0x0;
	}
	
	p_modulo = (unsigned short*)&OutputModulo_T0;
	dgc.T0.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.T0.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.T0.Positive = Positive_T0;
	dgc.T0.Terminate = Terminate_T0;
	dgc.T0.HighDrive = HighDrive_T0;

	if (Active_A)
	{
		dgc.A.GoSignal |= MasterPrimary;
		dgc.A.DoneSignal &= ~MasterPrimary;
	}
	else
	{
		dgc.A.GoSignal &= 0x288;
		dgc.A.DoneSignal = 0x0;
	}
	p_modulo = (unsigned short*)&OutputModulo_A;
	dgc.A.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.A.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.A.Positive = Positive_A;
	dgc.A.Terminate = Terminate_A;
	dgc.A.HighDrive = HighDrive_A;

	if (Active_B)
	{
		dgc.B.GoSignal |= MasterPrimary;
		dgc.B.DoneSignal &= ~MasterPrimary;
	}
	else
	{
		dgc.B.GoSignal &= 0x288;
		dgc.B.DoneSignal = 0x0;
	}
	p_modulo = (unsigned short*)&OutputModulo_B;
	dgc.B.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.B.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.B.Positive = Positive_B;
	dgc.B.Terminate = Terminate_B;
	dgc.B.HighDrive = HighDrive_B;
	result = ModifyAction(&dgc, DG_Number);
	return result;
}

_declspec (dllexport) unsigned long CC Modify_DG_V2(unsigned long OutputModulo_T0, 
													unsigned long GoSignal_T0, unsigned long DoneSignal_T0,
													BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													unsigned long OutputModulo_A, unsigned long GoSignal_A, unsigned long DoneSignal_A,
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													unsigned long OutputModulo_B, unsigned long GoSignal_B, unsigned long DoneSignal_B,
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													unsigned long PresetValue, unsigned long ClockSource, unsigned long GateDivider,
													unsigned long MS_Bus, BOOL PositiveGate, BOOL SynchronizeGate,
													BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	unsigned short *p_modulo;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));
	dgc.OutputLevel = OutputLevel;

	dgc.DT.ClockSource = ClockSource;
	dgc.DT.ClockEnable = ClockEnable;

	dgc.DT.PresetValue = PresetValue;
	dgc.DT.GateDivider = GateDivider;
	dgc.DT.MS_Bus = MS_Bus;
	dgc.DT.PositiveGate = PositiveGate;
	dgc.DT.SynchronizeGate = SynchronizeGate;
	dgc.DT.InternalTrigger = InternalTrigger;
	dgc.DT.InternalArm = InternalArm;
	dgc.DT.SoftwareTrigger = SoftwareTrigger;
	dgc.DT.RisingEdge = RisingEdge;
	dgc.DT.StopOnPreset = StopOnPreset;
	dgc.DT.ResetWhenDone = ResetWhenDone;
	dgc.DT.TriggerEnable = TriggerEnable;
	dgc.DT.Terminate = TriggerTerminate;

	dgc.T0.GoSignal = GoSignal_T0;
	dgc.T0.DoneSignal = DoneSignal_T0;
	p_modulo = (unsigned short*)&OutputModulo_T0;
	dgc.T0.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.T0.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.T0.Positive = Positive_T0;
	dgc.T0.Terminate = Terminate_T0;
	dgc.T0.HighDrive = HighDrive_T0;

	dgc.A.GoSignal = GoSignal_A;
	dgc.A.DoneSignal = DoneSignal_A;
	p_modulo = (unsigned short*)&OutputModulo_A;
	dgc.A.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.A.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.A.Positive = Positive_A;
	dgc.A.Terminate = Terminate_A;
	dgc.A.HighDrive = HighDrive_A;

	dgc.B.GoSignal = GoSignal_B;
	dgc.B.DoneSignal = DoneSignal_B;
	p_modulo = (unsigned short*)&OutputModulo_B;
	dgc.B.OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	dgc.B.OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);
	dgc.B.Positive = Positive_B;
	dgc.B.Terminate = Terminate_B;
	dgc.B.HighDrive = HighDrive_B;
	result = ModifyAction(&dgc, DG_Number);
	return result;
}

_declspec (dllexport) unsigned long CC Modify_G08(unsigned long OutputModulo_A, unsigned long OutputOffset_A, unsigned long GoSignal_A,
													BOOL Positive_A, BOOL Terminate_A,
													unsigned long OutputModulo_B, unsigned long OutputOffset_B, unsigned long GoSignal_B,
													BOOL Positive_B, BOOL Terminate_B,
													unsigned long OutputModulo_C, unsigned long OutputOffset_C, unsigned long GoSignal_C,
													BOOL Positive_C, BOOL Terminate_C,
													unsigned long OutputModulo_D, unsigned long OutputOffset_D, unsigned long GoSignal_D,
													BOOL Positive_D, BOOL Terminate_D,
													unsigned long OutputModulo_E, unsigned long OutputOffset_E, unsigned long GoSignal_E,
													BOOL Positive_E, BOOL Terminate_E, BOOL Disconnect_E, BOOL OntoMsBus_E, BOOL InputPositive_E,
													unsigned long OutputModulo_F, unsigned long OutputOffset_F, unsigned long GoSignal_F,
													BOOL Positive_F, BOOL Terminate_F, BOOL Disconnect_F, BOOL OntoMsBus_F, BOOL InputPositive_F,
													BOOL TriggerTerminate, BOOL GateTerminate, BOOL ClockEnable,
													unsigned long PresetValue, unsigned long ClockSource, unsigned long GateDivider,
													unsigned long MS_Bus, BOOL PositiveGate, BOOL SynchronizeGate, BOOL InternalTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number)
{
	DG_BME_Control dgc;
	long result;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);

	memcpy(&dgc, &(p_Present->DelayControlState), sizeof(DG_BME_Control));

	dgc.DT.ClockSource = ClockSource;
	dgc.DT.ClockEnable = ClockEnable;

	dgc.DT.PresetValue = PresetValue;
	dgc.DT.GateDivider = GateDivider;
	dgc.DT.MS_Bus = MS_Bus;
	dgc.DT.PositiveGate = PositiveGate;
	dgc.DT.SynchronizeGate = SynchronizeGate;
	dgc.DT.InternalTrigger = InternalTrigger;
	dgc.DT.RisingEdge = RisingEdge;
	dgc.DT.StopOnPreset = StopOnPreset;
	dgc.DT.ResetWhenDone = ResetWhenDone;
	dgc.DT.TriggerEnable = TriggerEnable;
	dgc.DT.Terminate = TriggerTerminate;
	dgc.DT.GateTerminate = GateTerminate;

	dgc.A.GoSignal = GoSignal_A;
	dgc.A.OutputModulo = OutputModulo_A;
	dgc.A.OutputOffset = OutputOffset_A;
	dgc.A.Positive = Positive_A;
	dgc.A.Terminate = Terminate_A;

	dgc.B.GoSignal = GoSignal_B;
	dgc.B.OutputModulo = OutputModulo_B;
	dgc.B.OutputOffset = OutputOffset_B;
	dgc.B.Positive = Positive_B;
	dgc.B.Terminate = Terminate_B;

	dgc.C.GoSignal = GoSignal_C;
	dgc.C.OutputModulo = OutputModulo_C;
	dgc.C.OutputOffset = OutputOffset_C;
	dgc.C.Positive = Positive_C;
	dgc.C.Terminate = Terminate_C;

	dgc.D.GoSignal = GoSignal_D;
	dgc.D.OutputModulo = OutputModulo_D;
	dgc.D.OutputOffset = OutputOffset_D;
	dgc.D.Positive = Positive_D;
	dgc.D.Terminate = Terminate_D;

	dgc.E.GoSignal = GoSignal_E;
	dgc.E.OutputModulo = OutputModulo_E;
	dgc.E.OutputOffset = OutputOffset_E;
	dgc.E.Positive = Positive_E;
	dgc.E.Terminate = Terminate_E;
	dgc.E.Disconnect = Disconnect_E;
	dgc.E.OntoMsBus = OntoMsBus_E;
	dgc.E.InputPositive = InputPositive_E;

	dgc.F.GoSignal = GoSignal_F;
	dgc.F.OutputModulo = OutputModulo_F;
	dgc.F.OutputOffset = OutputOffset_F;
	dgc.F.Positive = Positive_F;
	dgc.F.Terminate = Terminate_F;
	dgc.F.Disconnect = Disconnect_F;
	dgc.F.OntoMsBus = OntoMsBus_F;
	dgc.F.InputPositive = InputPositive_F;

	result = ModifyAction(&dgc, DG_Number);
	return result;
}

_declspec (dllexport) unsigned long CC ModifyAction(DG_BME_Control* p_BDG, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long Action = 0x0;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	ActionDT(&Action, &(p_BDG->DT), &(p_Present->DelayControlState.DT), DG_Product);
	ActionDC(&Action, &(p_BDG->A), &(p_Present->DelayControlState.A), DG_Product);
	ActionDC(&Action, &(p_BDG->B), &(p_Present->DelayControlState.B), DG_Product);
	switch (p_Present->DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		ActionDC(&Action, &(p_BDG->C), &(p_Present->DelayControlState.C), DG_Product);
		ActionDC(&Action, &(p_BDG->D), &(p_Present->DelayControlState.D), DG_Product);
		ActionDC(&Action, &(p_BDG->E), &(p_Present->DelayControlState.E), DG_Product);
		ActionDC(&Action, &(p_BDG->F), &(p_Present->DelayControlState.F), DG_Product);
		break;
	default:
		if (p_BDG->OutputLevel != p_Present->DelayControlState.OutputLevel)
			Action |= 0x1;
		ActionDC(&Action, &(p_BDG->T0), &(p_Present->DelayControlState.T0), DG_Product);
		break;
	}
	return Action;
}

_declspec (dllexport) long CC GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number)
{
	long BusNumber;
	return GetUnconnectedBusDelayGenerator(p_DG_Product, &BusNumber, p_SlotNumber, p_LineMaster, DG_Number);
}

_declspec (dllexport) long CC GetUnconnectedBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																							long* p_LineMaster, long DG_Number)
{
	char IpAddr[40];
	return GetUnconnectedEthernetDelayGenerator(p_DG_Product, &(IpAddr[0]), p_BusNumber, p_SlotNumber, p_LineMaster, DG_Number);
}

_declspec (dllexport) long CC GetUnconnectedEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																							long* p_LineMaster, long DG_Number)
{
	int LineNo;
	if ((DG_Number >= NumberPciDelayGenerators) || (DG_Number < 0))
		return 2;
	if (PciDelgen[DG_Number].Selected)
		return 1;
	*p_DG_Product = PciDelgen[DG_Number].DG_Product;
	memcpy(p_IpAddr, &(PciDelgen[DG_Number].ip_address), (40 * sizeof(char)));
	*p_BusNumber = PciDelgen[DG_Number].BusNumber;
	*p_SlotNumber = PciDelgen[DG_Number].SlotNumber;
	for (LineNo = 0; LineNo < 8; LineNo++)
		*(p_LineMaster + LineNo) = PciDelgen[DG_Number].LineMaster[LineNo];
	return 0;
}

_declspec (dllexport) long CC GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number)
{
	long BusNumber;
	return GetPciBusDelayGenerator(p_DG_Product, &BusNumber, p_SlotNumber, p_Master, DG_Number);

}

_declspec (dllexport) long CC GetPciBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																			BOOL* p_Master, long DG_Number)
{
	char IpAddr[40];
	return GetEthernetDelayGenerator(p_DG_Product, &(IpAddr[0]), p_BusNumber, p_SlotNumber, p_Master, DG_Number);
}

_declspec (dllexport) long CC GetEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber,
																			BOOL* p_Master, long DG_Number)
{
	if ((DG_Number >= NumberPciDelayGenerators) || (DG_Number < 0))
		return 2;
	*p_DG_Product = PciDelgen[DG_Number].DG_Product;
	memcpy(p_IpAddr, &(PciDelgen[DG_Number].ip_address), (40 * sizeof(char)));
	*p_BusNumber = PciDelgen[DG_Number].BusNumber;	
	*p_SlotNumber = PciDelgen[DG_Number].SlotNumber;
	if (PciDelgen[DG_Number].Master == DG_Number)
		*p_Master = TRUE;
	else
		*p_Master = FALSE;
	if (PciDelgen[DG_Number].Selected)
		return 0;
	else
		return 1;
}

_declspec (dllexport) long CC AddEthernetDelayGenerators(long* p_Error, char* p_IpAddr)
{
	long NoDelgen;
	NoDelgen = DetectEthernetDelayGenerators(p_Error, &(PciDelgen[NumberPciDelayGenerators]), p_IpAddr);
	NumberPciDelayGenerators = NumberPciDelayGenerators + NoDelgen;
	return NoDelgen;
}

_declspec (dllexport) long CC DetectPciDelayGenerators(long* p_Error)
{
	long NoDelgen;
	char ip_address[40];
	memset(&(ip_address), 0, (40 * sizeof(char)));
	NoDelgen = DetectEthernetDelayGenerators(p_Error, &(PciDelgen[0]), &(ip_address[0]));
	NumberPciDelayGenerators = NoDelgen;
	return NoDelgen;
}

_declspec (dllexport) long CC DataOut(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size)
{
	int i1,NoBytes;
	unsigned char* p_Value;
	int Count;
	U32 PciAddress;
	U16* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	if (p_PciDelgen->DeviceOpen)
	{
		PciAddress = (U32)Address;
		p_PciData = (U16*)p_data;
		if ((Address & 0xC0) == 0xC0)
		{
			Register.LowWord = 0x0;
			Register.HighWord = *p_PciData;
			//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
			Count = Size - 2;
			while (Count > 0)
			{
				p_PciData++;
				Register.HighWord = *p_PciData;
				//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
				Count -= 2;
			}
		}
		else
		{
			Register.HighWord = 0x0;
			Register.LowWord = *p_PciData;
			//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
			Count = Size - 2;
			while (Count > 0)
			{
				p_PciData++;
				Register.LowWord = *p_PciData;
				//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
				Count -= 2;
			}
		}
	}
	else
	{
		if (Size > 0)
			NoBytes = Size;
		else
			NoBytes = 1;
		p_Value = (unsigned char*)p_data;
		for (i1 = 0; i1 < NoBytes; i1++)
			IsaOutByte(Address, *(p_Value + i1));
	}
	return 0;
}

_declspec (dllexport) long CC Data32Out(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size)
{
	//char info[80];
	int Count;
	U32 PciAddress;
	U32* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	PciAddress = (U32)Address;
	p_PciData = (U32*)p_data;
	Register.Value = *p_PciData;
	//if (Address == 0xE0)
	//{
		//sprintf(info,"Address : %x, Value : %x ", Address, Register.Value);
		//AfxMessageBox(info, MB_OK, 0);	
	//}
	//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
	rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
	Count = Size - 4;
	while (Count > 0)
	{
		p_PciData++;
		Register.Value = *p_PciData;
		//rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
		rc = BmeDelgenWrite(PciAddress, &(Register.Value), p_PciDelgen);
		Count -= 4;
	}
	return 0;
}

_declspec (dllexport) long CC DataIn(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size)
{
	int i1,NoBytes;
	unsigned char* p_Value;
	int Count;
	U32 PciAddress;
	U16* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	if (p_PciDelgen->DeviceOpen)
	{
		PciAddress = (U32)Address;
		p_PciData = (U16*)p_data;
		if ((Address & 0xC0) == 0xC0)
		{
			Register.LowWord = 0x0;
			//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
			*p_PciData = Register.HighWord;
			Count = Size - 2;
			while (Count > 0)
			{
				//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
				p_PciData++;
				*p_PciData = Register.HighWord;
				Count -= 2;
			}
		}
		else
		{
			Register.HighWord = 0x0;
			//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
			*p_PciData = Register.LowWord;
			Count = Size - 2;
			while (Count > 0)
			{
				//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
				p_PciData++;
				*p_PciData = Register.LowWord;
				Count -= 2;
			}
		}
	}
	else
	{
		if (Size > 0)
			NoBytes = Size;
		else
			NoBytes = 1;
		p_Value = (unsigned char*)p_data;
		for (i1 = 0; i1 < NoBytes; i1++)
			*(p_Value + i1) = IsaInByte(Address);
	}
	return 0;
}

_declspec (dllexport) long CC Data32In(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size)
{
	int Count;
	U32 PciAddress;
	U32* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	PciAddress = (U32)Address;
	p_PciData = (U32*)p_data;
	Register.Value = 0x0;
	//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
	rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
	*p_PciData = Register.Value;
	Count = Size - 4;
	while (Count > 0)
	{
		//rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
		rc = BmeDelgenRead(PciAddress, &(Register.Value), p_PciDelgen);
		p_PciData++;
		*p_PciData = Register.Value;
		Count -= 4;
	}
	return 0;
}

_declspec (dllexport) long CC ResetPciDelayGenerator(DelgenType* p_PciDelgen)
{
	unsigned short Value,dg_type;
	unsigned long CommandWord,status;
	DataIn(0x20, &dg_type, p_PciDelgen, -1);
	dg_type &= 0xFF00;
	dg_type >>= 8;
	dg_type &= 0x00FF;
	switch (dg_type)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		CommandWord = 0x1F003F3F;
		Data32Out(0x120, &CommandWord, p_PciDelgen, -1);
		status = 0x10000;
		while ((status & 0x10000) != 0x0)
			Data32In(0x00, &status, p_PciDelgen, -1);
		CommandWord = 0x80;
		Data32Out(0x120, &CommandWord, p_PciDelgen, -1);
		CommandWord = 0xFFF;
		Data32Out(0x30, &CommandWord, p_PciDelgen, -1);
		CommandWord = 0x0;
		Data32Out(0x20, &CommandWord, p_PciDelgen, -1);
		CommandWord = 0xFFF;
		Data32Out(0x30, &CommandWord, p_PciDelgen, -1);
		CommandWord = 0x0;
		Data32Out(0x00, &CommandWord, p_PciDelgen, -1);

		Data32Out(0x10, &CommandWord, p_PciDelgen, -1);
		Data32Out(0x10, &CommandWord, p_PciDelgen, -1);
		Data32Out(0x10, &CommandWord, p_PciDelgen, -1);
		Data32Out(0x10, &CommandWord, p_PciDelgen, -1);
		Data32Out(0x10, &CommandWord, p_PciDelgen, -1);
		break;
	default:
		Value = 0x3F;
		DataOut(0xA0, &Value, p_PciDelgen, -1);
		Value = 0xFF;
		DataOut(0x30, &Value, p_PciDelgen, -1);
		Value = 0x0;
		DataOut(0x20, &Value, p_PciDelgen, -1);
		Value = 0xFF;
		DataOut(0x30, &Value, p_PciDelgen, -1);
		Value = 0x0;
		DataOut(0x00, &Value, p_PciDelgen, -1);

		DataOut(0x10, &Value, p_PciDelgen, -1);
		DataOut(0x10, &Value, p_PciDelgen, -1);
		DataOut(0x10, &Value, p_PciDelgen, -1);
		DataOut(0x10, &Value, p_PciDelgen, -1);
		break;
	}
	return 0;
}

BOOL MasterDelayGenerator(DelgenType* p_PciMaster, DelgenType* p_PciSlave)
{
	unsigned short dg_master,dg_slave;
	unsigned long MasterDgType,SlaveDgType;
	int NumBytes;
	BOOL MasterDg;
	unsigned long CommandWord,Result;
	unsigned long Value[6];
	unsigned long i1;
	DataIn(0x20, &dg_master, p_PciMaster, -1);
	dg_master &= 0xFF00;
	dg_master >>= 8;
	dg_master &= 0x00FF;
	switch (dg_master)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		NumBytes = 20;
		MasterDgType = XxDgType0;
		break;
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		NumBytes = 8;
		MasterDgType = QlDgType;
		break;
	default:
		NumBytes = -1;
		MasterDgType = QlDgType;
		break;
	}
	DataIn(0x20, &dg_slave, p_PciSlave, -1);
	dg_slave &= 0xFF00;
	dg_slave >>= 8;
	dg_slave &= 0x00FF;
	switch (dg_slave)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		SlaveDgType = XxDgType0;
		break;
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		SlaveDgType = QlDgType;
		break;
	default:
		SlaveDgType = QlDgType;
		break;
	}
	if (SlaveDgType != MasterDgType)
		return FALSE;
	for (i1 = 0; i1 < 6; i1++)
		Value[i1] = 0x0;
	MasterDg = TRUE;
	switch (MasterDgType)
	{
	case XxDgType0:
		CommandWord = 0x100;
		Data32Out(0x00, &CommandWord, p_PciMaster, -1);
		i1 = 0;
		Result = 0x0;
		while ((i1 < 256) && (MasterDg))
		{
			Value[0] = i1;
			Value[0] <<= 8;
			Value[0] &= 0xFF00;
			Data32Out(0x10, Value, p_PciMaster, NumBytes);
			Data32In(0x10, &Result, p_PciSlave, -1);
			Result >>= 8;
			if ((Value[0] & 0xFF00) != (Result & 0xFF00))
				MasterDg = FALSE;
			i1++;
		}
		CommandWord = 0x0;
		Data32Out(0x00, &CommandWord, p_PciMaster, -1);
		break;
	default:
		CommandWord = 0x100;
		DataOut(0x00, &CommandWord, p_PciMaster, -1);
		i1 = 0;
		Result = 0x0;
		while ((i1 < 8) && (MasterDg))
		{
			Value[0] = i1;
			Value[0] <<= 8;
			DataOut(0x10, Value, p_PciMaster, NumBytes);
			DataIn(0x10, &Result, p_PciSlave, -1);
			Result >>= 4;
			if ((Value[0] & 0x700) != (Result & 0x700))
				MasterDg = FALSE;
			i1++;
		}
		CommandWord = 0x0;
		DataOut(0x00, &CommandWord, p_PciMaster, -1);
		break;
	}
	return MasterDg;
}

BOOL MasterLineDG(DelgenType* p_PciMaster, DelgenType* p_PciSlave, int LineNo)
{
	unsigned long CommandWord,Result,Mask;
	unsigned long Value[6];
	unsigned long i1;
	unsigned long MasterDgType,SlaveDgType;
	unsigned short dg_master,dg_slave;
	int NumBytes;
	BOOL MasterDg;
	DataIn(0x20, &dg_master, p_PciMaster, -1);
	dg_master &= 0xFF00;
	dg_master >>= 8;
	dg_master &= 0x00FF;
	switch (dg_master)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		NumBytes = 20;
		MasterDgType = XxDgType0;
		break;
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		NumBytes = 8;
		MasterDgType = QlDgType;
		break;
	default:
		NumBytes = -1;
		MasterDgType = QlDgType;
		break;
	}
	DataIn(0x20, &dg_slave, p_PciSlave, -1);
	dg_slave &= 0xFF00;
	dg_slave >>= 8;
	dg_slave &= 0x00FF;
	switch (dg_slave)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		SlaveDgType = XxDgType0;
		break;
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		SlaveDgType = QlDgType;
		break;
	default:
		SlaveDgType = QlDgType;
		break;
	}
	if (SlaveDgType != MasterDgType)
		return FALSE;
	for (i1 = 0; i1 < 6; i1++)
		Value[i1] = 0x0;
	MasterDg = TRUE;


	switch (MasterDgType)
	{
	case XxDgType0:
		CommandWord = 0x100;
		Data32Out(0x00, &CommandWord, p_PciMaster, -1);
		Mask = 0x100;
		Mask <<= LineNo;
		Result = 0x0;
		Value[0] = Mask;
		Data32Out(0x10, Value, p_PciMaster, NumBytes);
		Data32In(0x10, &Result, p_PciSlave, -1);
		Result >>= 8;
		if ((Value[0] & Mask) != (Result & Mask))
			MasterDg = FALSE;
		Value[0] &= 0x0;
		Data32Out(0x10, Value, p_PciMaster, NumBytes);
		Data32In(0x10, &Result, p_PciSlave, -1);
		Result >>= 8;
		if ((Value[0] & Mask) != (Result & Mask))
			MasterDg = FALSE;
		CommandWord = 0x0;
		Data32Out(0x00, &CommandWord, p_PciMaster, -1);
		break;
	default:
		if (LineNo > 2)
			return FALSE;
		CommandWord = 0x100;
		DataOut(0x00, &CommandWord, p_PciMaster, -1);
		Mask = 0x100;
		Mask <<= LineNo;
		Result = 0x0;
		Value[0] = Mask;
		DataOut(0x10, Value, p_PciMaster, NumBytes);
		DataIn(0x10, &Result, p_PciSlave, -1);
		Result >>= 4;
		if ((Value[0] & Mask) != (Result & Mask))
			MasterDg = FALSE;
		Value[0] &= 0x0;
		DataOut(0x10, Value, p_PciMaster, NumBytes);
		DataIn(0x10, &Result, p_PciSlave, -1);
		Result >>= 4;
		if ((Value[0] & Mask) != (Result & Mask))
			MasterDg = FALSE;
		CommandWord = 0x0;
		DataOut(0x00, &CommandWord, p_PciMaster, -1);
		break;
	}
	return MasterDg;
}

void IsaOutByte(unsigned short Address, unsigned char value)
{
#if defined (WINDOWSNT)
	DG_InternalData* p_Present;
	USHORT port;
	long DG_Number = 0;
	while (DG_Number < NoDelayGenerators)
	{
		p_Present = (p_Internal + DG_Number);
		port = (Address - p_Present->base_address);
		if ((port & 0xFFF0) == 0x0)
		{
			outb(&mcd2id[DG_Number], port, value);
			return;
		}
		DG_Number++;
	}
#elif defined (WINDOWS95)
	_outp(Address, value);
#elif defined (WINDOWS31)
	outp(Address, value);
#endif
}

unsigned char IsaInByte(unsigned short Address)
{
	unsigned char value;
#if defined (WINDOWSNT)
	DG_InternalData* p_Present;
	USHORT port;
	long DG_Number = 0;
	value = 0;
	while (DG_Number < NoDelayGenerators)
	{
		p_Present = (p_Internal + DG_Number);
		port = (Address - p_Present->base_address);
		if ((port & 0xFFF0) == 0x0)
		{
			inb(&mcd2id[DG_Number], port, &value);
			return value;
		}
		DG_Number++;
	}
#elif defined (WINDOWS95)
	value = _inp(Address);
#elif defined (WINDOWS31)
	value = inp(Address);
#endif
	return value;
}

long DetectEthernetDelayGenerators(long* p_Error, DelgenType* p_DelgenList, char* p_IpAddr)
{
	long							NoDelgen,NoPlxCards;
	U32								ReqLimit;
	Register32				Register,DG_ID;
  //HANDLE						hDevice;
	RETURN_CODE				rc;
	//DEVICE_LOCATION		Device;
	int								i1,k1,LineNo,Count,TestSlot,memk1;
	int								MasterCount;
	DelgenType				DelgenList[20];
	DelgenType*				p_PciDelgen;
	DelgenType*				p_IpDelgen;
	BOOL							found;
	NoDelgen = 0;
	p_IpDelgen = p_DelgenList;
	//Device.BusNumber = (U32)-1;
	//Device.SlotNumber = (U32)-1;
	//Device.VendorId = (U32)-1;
	//Device.DeviceId = (U32)-1;
  //Device.SerialNumber[0] = '\0';
	ReqLimit = FIND_AMOUNT_MATCHED;
	//rc = PlxPciDeviceFind(&Device, &ReqLimit);
	rc = BmeDelgenNumberPciCards(&ReqLimit, p_IpAddr);
	if (rc != ApiSuccess)
	{
		if (p_Error != NULL)
			*p_Error = rc;
		return 0;
	}
	NoPlxCards = (long)ReqLimit;
	for (i1 = 0; i1 < NoPlxCards; i1++)
	{
		//Device.BusNumber = (U32)-1;
		//Device.SlotNumber = (U32)-1;
		//Device.VendorId = (U32)-1;
		//Device.DeviceId = (U32)-1;
		//Device.SerialNumber[0] = '\0';
		//ReqLimit = (U32)i1;
		//rc = PlxPciDeviceFind(&Device, &ReqLimit);
		p_PciDelgen = &(DelgenList[NoDelgen]);
		p_PciDelgen->BusNumber = -1;
		p_PciDelgen->SlotNumber = -1;
		memcpy(&(p_PciDelgen->ip_address), p_IpAddr, (40 * sizeof(char)));
		rc = BmeDelgenDeviceFind(p_PciDelgen, i1);
		//len = sprintf(info,"Address : %x, ini: %x, load: %x \n", DelayAddress, IniChar, LoadChar);
		//sprintf(&(info[len]),"Values : %x, %x, %x ", p_k->DelayList[0], p_k->PulseWidth[0], p_k->DacList[0]);
		//AfxMessageBox(info, MB_OK, 0);			
		if ((p_PciDelgen->VendorId == PlxVendorID) && (p_PciDelgen->DeviceId == PlxDeviceID))
		{
			//Register.Value = PlxPciConfigRegisterRead(Device.BusNumber, Device.SlotNumber, 
			//																		CFG_SUB_VENDOR_ID, &rc);
			Register.Value = BmeDelgenReadSubVendorID(p_PciDelgen, &rc);
			if (rc != ApiSuccess)
			{
				if (p_Error != NULL)
					*p_Error = rc;
				return 0;
			}
			if ((Register.LowWord == SubSystemVendorID) && (Register.HighWord == SubSystemDeviceID))
			{
				//rc = PlxPciDeviceOpen(&Device, &hDevice);
				rc = BmeDelgenDeviceOpen(p_PciDelgen->BusNumber, p_PciDelgen->SlotNumber, p_PciDelgen);
				if (rc != ApiSuccess)
				{
					if (p_Error != NULL)
						*p_Error = rc;
					return 0;
				}
				Register.Value = 0x0;
				//rc = PlxVpdWrite(hDevice, 0xc0, 0xffffffff);
				//Register.Value = PlxVpdRead(hDevice, 0xc0, &rc);
				Register.Value = BmeDelgenVpdRead(p_PciDelgen, 0xc0, &rc);
				if (Register.Value == BME_ID)
				{
					//DG_ID.Value = PlxVpdRead(hDevice, 0xc4, &rc);
					DG_ID.Value = BmeDelgenVpdRead(p_PciDelgen, 0xc4, &rc);
					if (rc != ApiSuccess)
					{
						if (p_Error != NULL)
							*p_Error = rc;
						return 0;
					}
					//ResetPciDelayGenerator(hDevice);
					ResetPciDelayGenerator(p_PciDelgen);
					p_PciDelgen->DG_Product = (unsigned long)DG_ID.LowWord;
					if (MasterDelayGenerator(p_PciDelgen, p_PciDelgen))
					{
						p_PciDelgen->Master = NoDelgen;
						for (LineNo = 0; LineNo < 8; LineNo++)
							p_PciDelgen->LineMaster[LineNo] = NoDelgen;
					}
					else
					{
						p_PciDelgen->Master = -1;
						for (LineNo = 0; LineNo < 8; LineNo++)
							p_PciDelgen->LineMaster[LineNo] = -1;
					}
					p_PciDelgen->OrderUpwards = TRUE;
					p_PciDelgen->Selected = FALSE;
					NoDelgen++;
				}
				else
				{
					//rc = PlxPciDeviceClose(hDevice);
					rc = BmeDelgenDeviceClose(p_PciDelgen);
					if (rc != ApiSuccess)
					{
						if (p_Error != NULL)
							*p_Error = rc;
						return 0;
					}
				}
			}
		}
	}
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		if (DelgenList[i1].Master == i1)
		{
			for (k1 = 0; k1 < NoDelgen; k1++)
			{
				if (i1 != k1)
				{
					if (MasterDelayGenerator(&(DelgenList[i1]), &(DelgenList[k1])))
					{
						DelgenList[k1].Master = i1;
						for (LineNo = 0; LineNo < 8; LineNo++)
							DelgenList[k1].LineMaster[LineNo] = i1;
						if (DelgenList[i1].SlotNumber < DelgenList[k1].SlotNumber)
							DelgenList[i1].OrderUpwards = TRUE;
						else
							DelgenList[i1].OrderUpwards = FALSE;
					}
				}
			}
		}
	}
	Count = 0;
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		if (DelgenList[i1].Master == i1)
		{
			memcpy(p_IpDelgen, &(DelgenList[i1]), sizeof(DelgenType));
			p_IpDelgen->Master = Count;
			for (LineNo = 0; LineNo < 8; LineNo++)
				p_IpDelgen->LineMaster[LineNo] = Count;
			p_IpDelgen->Selected = TRUE;
			MasterCount = Count;
			DelgenList[i1].Selected = TRUE;
			p_IpDelgen++;
			Count++;
			found = TRUE;
			while (found)
			{
				memk1 = -1;
				found = FALSE;
				if (DelgenList[i1].OrderUpwards)
					TestSlot = 1000;
				else
					TestSlot = -1000;
				for (k1 = 0; k1 < NoDelgen; k1++)
				{
					if ((i1 != k1) && (!DelgenList[k1].Selected))
					{
						if (DelgenList[k1].Master == i1)
						{
							if (DelgenList[i1].OrderUpwards)
							{
								if (DelgenList[k1].SlotNumber < TestSlot)
								{
									TestSlot = DelgenList[k1].SlotNumber;
									memk1 = k1;
									found = TRUE;
								}
							}
							else
							{
								if (DelgenList[k1].SlotNumber > TestSlot)
								{
									TestSlot = DelgenList[k1].SlotNumber;
									memk1 = k1;
									found = TRUE;
								}
							}
						}
					}
				}
				if (found)
				{
					memcpy(p_IpDelgen, &(DelgenList[memk1]), sizeof(DelgenType));
					p_IpDelgen->Master = MasterCount;
					p_IpDelgen->Selected = TRUE;
					for (LineNo = 0; LineNo < 8; LineNo++)
						p_IpDelgen->LineMaster[LineNo] = MasterCount;
					DelgenList[memk1].Selected = TRUE;
					p_IpDelgen++;
					Count++;
				}
			}
		}
	}
	found = FALSE;
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		if (!DelgenList[i1].Selected)
		{
			memcpy(p_IpDelgen, &(DelgenList[i1]), sizeof(DelgenType));
			DelgenList[i1].Selected = TRUE;
			p_IpDelgen++;
			Count++;
			found = TRUE;
		}
	}
	p_IpDelgen = &(PciDelgen[0]);
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		if (!(p_IpDelgen + i1)->Selected)
		{
			for (k1 = 0; k1 < NoDelgen; k1++)
			{
				for (LineNo = 0; LineNo < 8; LineNo++)
				{
					if (MasterLineDG((p_IpDelgen + k1), (p_IpDelgen + i1), LineNo))
						(p_IpDelgen + i1)->LineMaster[LineNo] = k1;
					else
						(p_IpDelgen + i1)->LineMaster[LineNo] = -1;
				}
			}
		}
	}
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		//rc = PlxPciDeviceClose(DelgenList[i1].h_Delgen);
		rc = BmeDelgenDeviceClose(&(DelgenList[i1]));
		if (rc != ApiSuccess)
		{
			if (p_Error != NULL)
				*p_Error = rc;
			return 0;
		}
	}
	if (p_Error != NULL)
	{
		if (found)
			*p_Error = 1;
		else
			*p_Error = 0;
	}
	return NoDelgen;
}

void InitializeInternalData(DG_InternalData* p_Present)
{
	unsigned short base_address = p_Present->base_address;
  p_Present->CommandAddress = base_address;
	p_Present->DelayGeneratorState.DG_Product = p_Present->DG_Product;
	p_Present->DelayControlState.DG_Product = p_Present->DG_Product;
	//printf("CDG_DLL() base_address: %x\n", base_address);
	switch (p_Present->DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		p_Present->Counter = base_address + 4;
		p_Present->Counter_N = base_address + 4;
		p_Present->Counter_J = base_address + 5;
		p_Present->Counter_K = base_address + 6;
		p_Present->Counter_cntrl = base_address + 7;

		p_Present->Large = base_address + 4;
		p_Present->Large_T0 = base_address + 4;
		p_Present->Large_A = base_address + 5;
		p_Present->Large_B = base_address + 6;
		p_Present->Large_cntrl = base_address + 7;

		p_Present->Delay = base_address + 8;
		p_Present->Delay_T0 = base_address + 8;
		p_Present->Delay_A = base_address + 9;
		p_Present->Delay_B = base_address + 10;
		p_Present->Delay_cntrl = base_address + 11;
		p_Present->DAC = base_address + 12;
		p_Present->DAC_A = base_address + 12;
		p_Present->DAC_B = base_address + 14;
		break;
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
		p_Present->CounterControlAddress = base_address + 1;
		p_Present->InterruptEnableAddress = base_address + 2;
		p_Present->InterruptAcknowledgeAddress = base_address + 3;
		p_Present->Delay_T0 = base_address + 4;
		p_Present->Delay_A = base_address + 5;
		p_Present->Delay_B = base_address + 6;
		p_Present->Delay_Aux = base_address + 7;
		p_Present->ModuloCounterAddress = base_address + 8;
		p_Present->TriggerCounterAddress = base_address + 9;
		p_Present->InitializeAddress = base_address + 10;
		p_Present->PrescalerAddress = base_address + 11;
		p_Present->DAC = base_address + 12;
		p_Present->DAC_T0 = base_address + 13;
		p_Present->DAC_A = base_address + 14;
		p_Present->DAC_B = base_address + 15;
		break;
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		p_Present->CounterControlAddress = 0x10;
		p_Present->InterruptEnableAddress = 0x20;
		p_Present->InterruptAcknowledgeAddress = 0x30;
		p_Present->Delay_T0 = 0x40;
		p_Present->Delay_A = 0x50;
		p_Present->Delay_B = 0x60;
		p_Present->Delay_Aux = 0x70;
		p_Present->ModuloCounterAddress = 0x80;
		p_Present->TriggerCounterAddress = 0x90;
		p_Present->InitializeAddress = 0xA0;
		p_Present->PrescalerAddress = 0xB0;
		p_Present->DAC = 0xC0;
		p_Present->DAC_T0 = 0xD0;
		p_Present->DAC_A = 0xE0;
		p_Present->DAC_B = 0xF0;
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->CounterControlAddress = 0x10;
		p_Present->InterruptEnableAddress = 0x20;
		p_Present->InterruptAcknowledgeAddress = 0x30;
		p_Present->FrequencyCounterAddress = 0x30;
		p_Present->Delay_A = 0x40;
		p_Present->Delay_B = 0x50;
		p_Present->Delay_C = 0x60;
		p_Present->Delay_D = 0x70;
		p_Present->Delay_E = 0x80;
		p_Present->Delay_F = 0x90;
		p_Present->Serial_DAC = 0xE0;
		p_Present->SecondaryCounterAddress = 0xF0;
		p_Present->ModuloCounterAddress = 0x100;
		p_Present->TriggerCounterAddress = 0x110;
		p_Present->InitializeAddress = 0x120;
		p_Present->PrescalerAddress = 0x130;
		p_Present->Modulo_A = 0x140;
		p_Present->Modulo_B = 0x150;
		p_Present->Modulo_C = 0x160;
		p_Present->Modulo_D = 0x170;
		p_Present->Modulo_E = 0x180;
		p_Present->Modulo_F = 0x190;
		break;
	}


	p_Present->b_DG_Activated = FALSE;
	p_Present->b_ModuleCalibrated = FALSE;
	p_Present->p_Master = p_Present;
	switch (p_Present->DG_Product)
	{
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		p_Present->InternalOscillatorFrequency = 80.0;
		p_Present->ExternalOscillatorFrequency = 80.0;
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		p_Present->InternalOscillatorFrequency = 160.0;
		p_Present->ExternalOscillatorFrequency = 80.0;
		break;
	default:
		p_Present->InternalOscillatorFrequency = 10.0;
		p_Present->ExternalOscillatorFrequency = 10.0;
		break;
	}
	p_Present->ZeroTime = 0.0;
	p_Present->TenMhzZeroTime = 0.0;
	p_Present->ResetTime = 0.0;
	p_Present->TenMhzResetTime = 0.0;
	p_Present->TimeIncrement = 0.1;
	p_Present->TriggerIncrement = 0.1;
	p_Present->OscillatorIncrement = (1.0 / p_Present->ExternalOscillatorFrequency);
	p_Present->T0_Increment = 0.1;
	p_Present->A_Increment = 0.1;
	p_Present->B_Increment = 0.1;
	p_Present->C_Increment = 0.1;
	p_Present->D_Increment = 0.1;
	p_Present->E_Increment = 0.1;
	p_Present->F_Increment = 0.1;
	p_Present->CalibrationLevel = CalibrateNone;
	switch (p_Present->DG_Product)
	{
	case BME_G03V1:
	case BME_G03V2:
		p_Present->p1Time = 0.2;
		p_Present->p2Time = 0.3;
		p_Present->TenMhzp1Time = 0.2;
		p_Present->TenMhzp2Time = 0.3;
		break;
	default:
		p_Present->p1Time = 0.1;
		p_Present->p2Time = 0.2;
		p_Present->TenMhzp1Time = 0.1;
		p_Present->TenMhzp2Time = 0.2;
		break;
	}
}

void Synchronize_DG_State(long DG_Number)
{
	DG_BME_Registers dgr;
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long  PrescalerValue[4];
	unsigned long  CounterControlValue[6];
	unsigned long Value;
	int i1;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	ResetRegisters(&dgr);
	dgr.DG_Product = DG_Product;
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		p_Present->CommandRegister |= 0x10;
		dgr.T0.GoSignal |= MasterPrimary;
		dgr.T0.Digital = 0xFFFFFFFF;
		dgr.A.GoSignal |= MasterPrimary;
		dgr.A.Digital = 0xFFFFFFFF;
		dgr.A.Analog = 0xFFF;
		dgr.B.GoSignal |= MasterPrimary;
		dgr.B.Digital = 0xFFFFFFFF;
		dgr.B.Analog = 0xFFF;
		Set_DG_BME(&dgr, DG_Number);

		dgr.T0.GoSignal = 0x0;
		dgr.A.GoSignal = 0x0;
		dgr.B.GoSignal = 0x0;
		Set_DG_BME(&dgr, DG_Number);
		break;
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
//		int i1;
//		while (TRUE)
//		{
//			for (i1 = 0 ; i1 < 0xFF; i1++)
//			{
//				Value = (unsigned short)i1;
//				DataOut(((Value & 0xFC) | 0x10), &Value, &(p_Present->PciDelgen), -1);
//			}
//		}
		LoadCommandRegister(&p_Present->CommandRegister, p_Present);
		for (i1 = 0; i1 < 5; i1++)
		{
			CounterControlValue[i1] = 0x0;
			p_Present->CounterControlRegister[i1] = 0x00;
			p_Present->CounterControlState[i1] = 0xFFFFFFFF;
		}
		LoadCounterControl(CounterControlValue, p_Present);
		p_Present->LoadVector = 0x0;
		Value = 0x1F003F1F;
		switch (DG_Product)
		{
		case BME_SG08P1:
			Value = 0x1F003F1F;
			Data32Out(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
			break;
		case BME_SG08P2:
			Value = 0x1F003F07;
			Data32Out(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
			break;
		default:
			Value = 0x1F003F1F;
			DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
			break;
		}
		Value = 0xFFFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, &(p_Present->PciDelgen), -1);
		Value = 0x0;
		DataOut(p_Present->InterruptEnableAddress, &Value, &(p_Present->PciDelgen), -1);
		Value = 0xFFFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, &(p_Present->PciDelgen), -1);
		PrescalerValue[0] = 0x09000709;
		PrescalerValue[1] = 0x0;
		PrescalerValue[2] = 0x0;
		p_Present->PrescalerState[0] = 0xFFFFFFFF;
		p_Present->PrescalerState[1] = 0xFFFFFFFF;
		p_Present->PrescalerState[2] = 0xFFFFFFFF;
		LoadPrescaler(PrescalerValue, p_Present);

		p_Present->CommandRegister |= 0x80;
		p_Present->InterruptEnableRegister = 0x00;

		dgr.OutputLevel = ECL_VoltageLevel;
		dgr.PulseWidth = 255;
		DelayTriggerTest(&(dgr.DT));

		dgr.MC.Active = TRUE;
		dgr.MC.Digital = 0xFFFFFFF0;

		DelayChannelTest(&(dgr.T0));
		DelayChannelTest(&(dgr.A));
		DelayChannelTest(&(dgr.B));
		DelayChannelTest(&(dgr.C));
		DelayChannelTest(&(dgr.D));
		DelayChannelTest(&(dgr.E));
		DelayChannelTest(&(dgr.F));
		switch (p_Present->DG_Product)
		{
		case BME_SG08P2:
			dgr.DT.MS_Bus |= StepBackOnBus;
			dgr.DT.MS_Bus |= StartOnBus;
			dgr.DT.MS_Bus |= InhibitOnBus;
			dgr.DT.MS_Bus |= LoadDataOnBus;
			break;
		default:
			break;
		}

		dgr.DT.ClockSource = TriggerInput;
		Set_DG_BME(&dgr, DG_Number);
		ResetDelayChannel(&(dgr.T0));
		ResetDelayChannel(&(dgr.A));
		ResetDelayChannel(&(dgr.B));
		ResetDelayChannel(&(dgr.C));
		ResetDelayChannel(&(dgr.D));
		ResetDelayChannel(&(dgr.E));
		ResetDelayChannel(&(dgr.F));
		dgr.T0.GoSignal = MasterPrimary;
		dgr.A.GoSignal = MasterPrimary;
		dgr.A.ListLength = MemLength;
		dgr.B.GoSignal = MasterPrimary;
		dgr.B.ListLength = MemLength;
		dgr.C.GoSignal = MasterPrimary;
		dgr.C.ListLength = MemLength;
		dgr.D.GoSignal = MasterPrimary;
		dgr.D.ListLength = MemLength;
		dgr.E.GoSignal = MasterPrimary;
		dgr.E.ListLength = MemLength;
		dgr.F.GoSignal = MasterPrimary;
		dgr.F.ListLength = MemLength;

		dgr.DT.ClockSource = CrystalOscillator;
		Set_DG_BME(&dgr, DG_Number);

		ResetDelayTrigger(&(dgr.DT));
		switch (p_Present->DG_Product)
		{
		case BME_SG08P2:
			dgr.DT.MS_Bus |= LocalSecondary;
			dgr.DT.MS_Bus |= StepBackOnBus;
			dgr.DT.MS_Bus |= StartOnBus;
			dgr.DT.MS_Bus |= InhibitOnBus;
		case BME_SG08P1:
			dgr.DT.MS_Bus |= Resynchronize;
			break;
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05P3:
		case BME_SG05P2:
		case BME_SG05P3:
			dgr.DT.MS_Bus |= Resynchronize;
		default:
			dgr.DT.MS_Bus |= LocalPrimary;
			dgr.PulseWidth = 8;
			break;
		}
		dgr.OutputLevel = TTL_VoltageLevel;

		dgr.MC.Active = FALSE;

		Value = 0x20;
		DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
		ResetDelayChannel(&(dgr.T0));
		ResetDelayChannel(&(dgr.A));
		ResetDelayChannel(&(dgr.B));
		ResetDelayChannel(&(dgr.C));
		ResetDelayChannel(&(dgr.D));
		ResetDelayChannel(&(dgr.E));
		ResetDelayChannel(&(dgr.F));
		dgr.DT.ClockSource = CrystalOscillator;
		Set_DG_BME(&dgr, DG_Number);
		DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
		break;
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		LoadCommandRegister(&p_Present->CommandRegister, p_Present);
		CounterControlValue[0] = 0x0;
		CounterControlValue[1] = 0x0;
		p_Present->CounterControlState[0] = 0xFFFFFFFF;
		p_Present->CounterControlState[1] = 0xFFFFFFFF;
		LoadCounterControl(CounterControlValue, p_Present);
		Value = 0x3F;
		DataOut(p_Present->InitializeAddress, &Value, &(p_Present->PciDelgen), -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, &(p_Present->PciDelgen), -1);
		Value = 0x0;
		DataOut(p_Present->InterruptEnableAddress, &Value, &(p_Present->PciDelgen), -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, &(p_Present->PciDelgen), -1);

		PrescalerValue[0] = 0x0;
		PrescalerValue[1] = 0x0;
		p_Present->PrescalerState[0] = 0xFFFFFFFF;
		p_Present->PrescalerState[1] = 0xFFFFFFFF;
		LoadPrescaler(PrescalerValue, p_Present);

		p_Present->CommandRegister |= 0x80;
		p_Present->CounterControlRegister[0] = 0x00;
		p_Present->CounterControlRegister[1] = 0x00;
		p_Present->InterruptEnableRegister = 0x00;


		dgr.DT.MS_Bus = 0x0;
		dgr.DT.InternalTrigger = TRUE;
		dgr.DT.StopOnPreset = TRUE;
		dgr.DT.ResetWhenDone = TRUE;
		dgr.DT.TriggerEnable = TRUE;
		dgr.DT.Terminate = TRUE;
		dgr.DT.ClockEnable = TRUE;
		dgr.DT.PositiveGate = FALSE;
		dgr.DT.OscillatorDivider = 32;
		dgr.DT.TriggerDivider = 32;
		dgr.DT.RepCounter = 0xFFFFFFFF;
		dgr.DT.PresetValue = 0xFFFFFFFF;
		dgr.DT.TriggerDAC = 0xFFF;
		dgr.OutputLevel = ECL_VoltageLevel;
		dgr.PulseWidth = 255;

		dgr.MC.Active = TRUE;
		dgr.MC.Digital = 0xFFFFFFF0;
		dgr.MC.Int3 = 0xFFFFFFFF;

		dgr.T0.GoSignal = 0xFF;
		dgr.T0.DoneSignal = 0xFF;
		dgr.T0.Positive = FALSE;
		dgr.T0.Terminate = TRUE;
		dgr.T0.HighDrive = TRUE;
		dgr.T0.Digital = 0xFFFFFFF0;
		dgr.T0.DigOff = 0xFFFFFFFF;
		dgr.T0.Analog = 0xFFF;

		dgr.A.GoSignal = 0xFF;
		dgr.A.DoneSignal = 0xFF;
		dgr.A.Positive = FALSE;
		dgr.A.Terminate = TRUE;
		dgr.A.HighDrive = TRUE;
		dgr.A.Digital = 0xFFFFFFF0;
		dgr.A.DigOff = 0xFFFFFFFF;
		dgr.A.Analog = 0xFFF;

		dgr.B.GoSignal = 0xFF;
		dgr.B.DoneSignal = 0xFF;
		dgr.B.Positive = FALSE;
		dgr.B.Terminate = TRUE;
		dgr.B.HighDrive = TRUE;
		dgr.B.Digital = 0xFFFFFFF0;
		dgr.B.DigOff = 0xFFFFFFFF;
		dgr.B.Analog = 0xFFF;

		dgr.DT.ClockSource = TriggerInput;
		Set_DG_BME(&dgr, DG_Number);
		dgr.DT.ClockSource = CrystalOscillator;
		Set_DG_BME(&dgr, DG_Number);

		dgr.DT.MS_Bus = LocalPrimary;
		dgr.DT.InternalTrigger = FALSE;
		dgr.DT.StopOnPreset = FALSE;
		dgr.DT.ResetWhenDone = FALSE;
		dgr.DT.TriggerEnable = FALSE;
		dgr.DT.ClockEnable = FALSE;
		dgr.DT.PositiveGate = TRUE;
		dgr.DT.OscillatorDivider = 8;
		dgr.DT.TriggerDivider = 8;
		dgr.DT.Terminate = FALSE;
		dgr.OutputLevel = TTL_VoltageLevel;
		dgr.PulseWidth = 8;

		dgr.MC.Active = FALSE;

		dgr.T0.GoSignal = 0x0;
		dgr.T0.DoneSignal = 0x0;
		dgr.T0.Positive = TRUE;
		dgr.T0.Terminate = FALSE;
		dgr.T0.HighDrive = FALSE;

		dgr.A.GoSignal = 0x0;
		dgr.A.DoneSignal = 0x0;
		dgr.A.Positive = TRUE;
		dgr.A.Terminate = FALSE;
		dgr.A.HighDrive = FALSE;

		dgr.B.GoSignal = 0x0;
		dgr.B.DoneSignal = 0x0;
		dgr.B.Positive = TRUE;
		dgr.B.Terminate = FALSE;
		dgr.B.HighDrive = FALSE;

		dgr.DT.ClockSource = TriggerInput;
		Set_DG_BME(&dgr, DG_Number);
		dgr.DT.ClockSource = CrystalOscillator;
		Set_DG_BME(&dgr, DG_Number);
		break;
	}
}

void HardwareTest_BME_G02(long DG_Number)
{
	//printf("HardwareTest_BME_G02()\n");
	char ch;
	unsigned long TriggerCount,Cctrl;
	unsigned long result;
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	DG_BME_Registers DGState;
	ResetRegisters(&DGState);
	DGState.DG_Product = p_Present->DG_Product;
	DGState.Gate_AB = FALSE;
	ResetDelayChannel(&(DGState.T0));
	ResetDelayChannel(&(DGState.A));
	ResetDelayChannel(&(DGState.B));
	ResetMainCounter(&(DGState.MC));
	ResetDelayTrigger(&(DGState.DT));
	DGState.DT.RepCounter = 5000;
	DGState.DT.PresetValue = 10000000;
	DGState.DT.InternalTrigger = TRUE;
	DGState.DT.TriggerEnable = TRUE;
	DGState.DT.ResetWhenDone = TRUE;
	DGState.DT.StopOnPreset = TRUE;

	DGState.T0.GoSignal = MasterPrimary;
	DGState.T0.Digital = 20;
	DGState.A.GoSignal = MasterPrimary;
	DGState.A.Digital = 2000;
	DGState.A.Analog = 0x1FF;
	DGState.B.GoSignal = MasterPrimary;
	DGState.B.Digital = 1000;
	DGState.B.Analog = 0x1FF;
	result = Test_BME_G02(DG_Number);
	if (result != 0)
		printf("value returned from Test_BME_G02(): %d", result);

	do
	{
		scanf("%c", &ch);
		TriggerCount = ReadTriggerCounter(DG_Number);
		Cctrl = ReadCounterControlRegister(DG_Number);
		printf("TriggerCount: %4d,    CounterControl: %x\n", TriggerCount, Cctrl);
	} while (ch != 'S');

	DGState.DT.InternalTrigger = FALSE;
	DGState.DT.ResetWhenDone = FALSE;
	DGState.DT.StopOnPreset = FALSE;
	DGState.T0.GoSignal = 0x0;
	DGState.A.GoSignal = 0x0;
	DGState.B.GoSignal = 0x0;
	DGState.MC.Active = FALSE;
	result = Deactivate_DG_BME(DG_Number);
	if (result != 0)
		printf("value returned from Deactivate_DG_BME(): %d", result);
	result = Set_DG_BME(&DGState, DG_Number);
	if (result != 0)
		printf("value returned from Set_DG_BME(): %d", result);
	result = Activate_DG_BME(DG_Number);
	if (result != 0)
		printf("value returned from Activate_DG_BME(): %d", result);
}

void HardwareTest_BME_G03(long DG_Number)
{
	//printf("HardwareTest_BME_G03()\n");
	char ch;
	unsigned long TriggerCount;
	unsigned long result;
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	DG_BME_Registers DGState;
	ResetRegisters(&DGState);
	DGState.DG_Product = p_Present->DG_Product;
	DGState.Gate_AB = FALSE;
	DGState.DT.RepCounter = 5000;
	DGState.DT.PresetValue = 10000000;
	DGState.DT.InternalTrigger = TRUE;
	DGState.DT.TriggerEnable = TRUE;
	DGState.DT.ResetWhenDone = TRUE;
	DGState.DT.StopOnPreset = TRUE;

	DGState.T0.GoSignal = MasterPrimary;
	DGState.T0.Digital = 2000;
	DGState.T0.DigOff = 1000;
	DGState.A.GoSignal = MasterPrimary;
	DGState.A.Digital = 2000;
	DGState.A.DigOff = 1500;
	DGState.A.Analog = 0x0FF;
	DGState.B.GoSignal = MasterPrimary;
	DGState.B.Digital = 1000;
	DGState.B.DigOff = 900;
	DGState.B.Analog = 0x0FF;

	DGState.MC.Active = TRUE;
	DGState.MC.Digital = 3000;
	DGState.MC.Int3 = 4000;
	result = Test_BME_G03(DG_Number);
	if (result != 0)
		printf("value returned from Test_BME_G03(): %d", result);

	do
	{
		scanf("%c", &ch);
		TriggerCount = ReadTriggerCounter(DG_Number);
		printf("TriggerCount: %4d\n", TriggerCount);
	} while (ch != 'S');

	DGState.DT.InternalTrigger = FALSE;
	DGState.DT.ResetWhenDone = FALSE;
	DGState.DT.StopOnPreset = FALSE;
	DGState.T0.GoSignal = 0x0;
	DGState.A.GoSignal = 0x0;
	DGState.B.GoSignal = 0x0;
	DGState.MC.Active = FALSE;
	result = Deactivate_DG_BME(DG_Number);
	//if (result != 0)
		//printf("value returned from Deactivate_DG_BME(): %d", result);
	result = Set_DG_BME(&DGState, DG_Number);
	//if (result != 0)
		//printf("value returned from Set_DG_BME(): %d", result);
	result = Activate_DG_BME(DG_Number);
	//if (result != 0)
		//printf("value returned from Activate_DG_BME(): %d", result);
}

void LoadPrescaler(unsigned long* p_value, DG_InternalData* p_Present)
{
	int NumBytes;
	if ((*p_value != p_Present->PrescalerState[0]) || 
						(*(p_value + 1) != p_Present->PrescalerState[1]) ||
						(*(p_value + 2) != p_Present->PrescalerState[2]))
	{
		p_Present->PrescalerState[0] = *p_value;
		p_Present->PrescalerState[1] = *(p_value + 1);
		p_Present->PrescalerState[2] = *(p_value + 2);
		switch (p_Present->DG_Product)
		{
		case BME_SG08P1:
		case BME_SG08P2:
			NumBytes = 12;
			Data32Out(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							&(p_Present->PciDelgen), NumBytes);
			break;
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			NumBytes = 8;
			DataOut(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							&(p_Present->PciDelgen), NumBytes);
			break;
		case BME_G03V3:
			NumBytes = 2;
			DataOut(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							&(p_Present->PciDelgen), NumBytes);
			break;
		case BME_SG02V4:
		case BME_G02V3:
			NumBytes = 1;
			DataOut(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							&(p_Present->PciDelgen), NumBytes);
			break;
		default:
			NumBytes = 0;
			DataOut(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							&(p_Present->PciDelgen), NumBytes);
			break;
		}
	}
}

void LoadCounterControl(unsigned long* p_value, DG_InternalData* p_Present)
{
	int NumBytes,i1;
	BOOL different;
	//char info[200];
	switch (p_Present->DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		different = FALSE;
		for (i1 = 0; i1 < 5; i1++)
		{
			if (*(p_value + i1) != p_Present->CounterControlState[i1])
			{
				p_Present->CounterControlState[i1] = *(p_value + i1);
				different = TRUE;
			}
		}
		if (different)
		{
			//sprintf(info,"LoadCounterControl : %x, %x ", p_Present->CounterControlState[0], p_Present->CounterControlState[1]);
			//AfxMessageBox(info, MB_OK, 0);	
			NumBytes = 20;
			Data32Out(p_Present->CounterControlAddress, p_Present->CounterControlState,
																						&(p_Present->PciDelgen), NumBytes);
		}
		break;
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((*p_value != p_Present->CounterControlState[0]) || 
							(*(p_value + 1) != p_Present->CounterControlState[1]))
		{
			p_Present->CounterControlState[0] = *p_value;
			p_Present->CounterControlState[1] = *(p_value + 1);
			NumBytes = 8;
			DataOut(p_Present->CounterControlAddress, p_Present->CounterControlState,
																						&(p_Present->PciDelgen), NumBytes);
		}
		break;
	default:
		if (*(p_value) != p_Present->CounterControlState[0])
		{
			p_Present->CounterControlState[0] = *(p_value);
			NumBytes = -1;
			DataOut(p_Present->CounterControlAddress, p_Present->CounterControlState,
																						&(p_Present->PciDelgen), NumBytes);
		}
		break;
	}
}

void LoadCommandRegister(unsigned long* p_value, DG_InternalData* p_Present)
{
	if (*p_value != p_Present->CommandRegisterState)
	{
		switch (p_Present->DG_Product)
		{
		case BME_SG08P1:
		case BME_SG08P2:
			Data32Out(p_Present->CommandAddress, p_value, &(p_Present->PciDelgen), -1);
			break;
		default:
			DataOut(p_Present->CommandAddress, p_value, &(p_Present->PciDelgen), -1);
			break;
		}
		p_Present->CommandRegisterState = *p_value;
		//printf("LoadCounterControl(): %2x\n", value);
	}
}

void SetMainCounterControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																		MainCounterType* p_mc, DG_InternalData* p_Present)
{
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		*p_FinalValue &= ~0x08;
		*p_Prepare &= ~0x08;
		break;
	case BME_G03V1:
	case BME_G03V2:
		if (p_mc->Active)
		{
			*p_FinalValue |= 0x08;
			if ((p_mc->Digital != p_Present->DelayGeneratorState.MC.Digital) ||
							(p_mc->Int3 != p_Present->DelayGeneratorState.MC.Int3))
			{
				*p_Prepare &= ~0x08;
			}
		}
		else
		{
			*p_FinalValue &= ~0x08;
			*p_Prepare &= ~0x08;
		}
		break;
	default:
		if (p_mc->Active)
		{
			*p_FinalValue |= 0x08;
			if (p_mc->Digital != p_Present->DelayGeneratorState.MC.Digital) 
				*p_Prepare &= ~0x08;
		}
		else
		{
			*p_FinalValue &= ~0x08;
			*p_Prepare &= ~0x08;
		}
		break;
	}
	p_Present->DelayGeneratorState.MC.Active = p_mc->Active;
}

void SetReferenceControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																						DelayChannel* p_rf, DG_InternalData* p_Present)
{
	unsigned long DG_Product = p_Present->DG_Product;
	if ((p_rf->GoSignal & 0x77) != 0x0)
	{
		switch (DG_Product)
		{
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if ((p_rf->DoneSignal & MasterPrimary) != 0x0)
				*(p_FinalValue + 1) |= 0x10000;
			else
				*(p_FinalValue + 1) &= ~0x10000;
			if ((p_rf->DoneSignal & LocalPrimary) != 0x0)
				*(p_FinalValue + 1) |= 0x01;
			else
				*(p_FinalValue + 1) &= ~0x01;
			if ((p_rf->DoneSignal & LocalSecondary) != 0x0)
				*(p_FinalValue + 1) |= 0x10;
			else
				*(p_FinalValue + 1) &= ~0x10;
			if ((p_rf->DoneSignal & LocalForce) != 0x0)
				*(p_FinalValue + 1) |= 0x100;
			else
				*(p_FinalValue + 1) &= ~0x100;
		case BME_SG02P3:
			if ((p_rf->GoSignal & MasterPrimary) != 0x0)
				*p_FinalValue |= 0x01;
			else
				*p_FinalValue &= ~0x01;
			if ((p_rf->GoSignal & LocalPrimary) != 0x0)
				*p_FinalValue |= 0x10000;
			else
				*p_FinalValue &= ~0x10000;
			if ((p_rf->GoSignal & LocalSecondary) != 0x0)
				*p_FinalValue |= 0x100000;
			else
				*p_FinalValue &= ~0x100000;
			if ((p_rf->GoSignal & LocalForce) != 0x0)
				*p_FinalValue |= 0x1000;
			else
				*p_FinalValue &= ~0x1000;
			if ((p_rf->GoSignal & InhibitLocal) != 0x0)
				*p_FinalValue |= 0x1000000;
			else
				*p_FinalValue &= ~0x1000000;
			break;
		default:
			*p_FinalValue |= 0x01;
			break;
		}
		switch (DG_Product)
		{
		case BME_G03V1:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_rf->DigOff != p_Present->DelayGeneratorState.T0.DigOff)
			{
				*p_Prepare &= ~0x111001;
				*(p_Prepare + 1) &= ~0x10111;
			}
		default:
			if (p_rf->Digital != p_Present->DelayGeneratorState.T0.Digital)
			{
				*p_Prepare &= ~0x111001;
				*(p_Prepare + 1) &= ~0x10111;
			}
		}
		switch (DG_Product)
		{
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_rf->OutputModulo != p_Present->DelayGeneratorState.T0.OutputModulo)
			{
				*p_Prepare &= ~0x111001;
				*(p_Prepare + 1) &= ~0x10111;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		*p_FinalValue &= ~0x111001;
		*(p_FinalValue + 1) &= ~0x10111;
		*p_Prepare &= ~0x111001;
		*(p_Prepare + 1) &= ~0x10111;
	}

	p_Present->DelayGeneratorState.T0.GoSignal |= (p_rf->GoSignal & 0x77);
	p_Present->DelayGeneratorState.T0.GoSignal &= (p_rf->GoSignal | ~0x77);
}

void SetDelayControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
					DelayChannel* p_k, DelayChannel* p_ChState, short int pos, DG_InternalData* p_Present)
{
	unsigned long ModBit[2];
	unsigned long DG_Product = p_Present->DG_Product;
	ModBit[0] = 0x1111001;
	ModBit[1] = 0x10111;
	ModBit[0] <<= pos;
	ModBit[1] <<= pos;
	if ((p_k->GoSignal & 0x77) != 0x0)
	{
		switch (DG_Product)
		{
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if ((p_k->DoneSignal & MasterPrimary) != 0x0)
				*(p_FinalValue + 1) |= (0x60000 & ModBit[1]);
			else
				*(p_FinalValue + 1) &= ~(0x60000 & ModBit[1]);
			if ((p_k->DoneSignal & LocalPrimary) != 0x0)
				*(p_FinalValue + 1) |= (0x06 & ModBit[1]);
			else
				*(p_FinalValue + 1) &= ~(0x06 & ModBit[1]);
			if ((p_k->DoneSignal & LocalSecondary) != 0x0)
				*(p_FinalValue + 1) |= (0x60 & ModBit[1]);
			else
				*(p_FinalValue + 1) &= ~(0x60 & ModBit[1]);
			if ((p_k->DoneSignal & LocalForce) != 0x0)
				*(p_FinalValue + 1) |= (0x600 & ModBit[1]);
			else
				*(p_FinalValue + 1) &= ~(0x600 & ModBit[1]);
		case BME_SG02P3:
			if ((p_k->GoSignal & MasterPrimary) != 0x0)
				*p_FinalValue |= (0x06 & ModBit[0]);
			else
				*p_FinalValue &= ~(0x06 & ModBit[0]);
			if ((p_k->GoSignal & LocalPrimary) != 0x0)
				*p_FinalValue |= (0x60000 & ModBit[0]);
			else
				*p_FinalValue &= ~(0x60000 & ModBit[0]);
			if ((p_k->GoSignal & LocalSecondary) != 0x0)
				*p_FinalValue |= (0x600000 & ModBit[0]);
			else
				*p_FinalValue &= ~(0x600000 & ModBit[0]);
			if ((p_k->GoSignal & LocalForce) != 0x0)
				*p_FinalValue |= (0x6000 & ModBit[0]);
			else
				*p_FinalValue &= ~(0x6000 & ModBit[0]);
			if ((p_k->GoSignal & InhibitLocal) != 0x0)
				*p_FinalValue |= (0x6000000 & ModBit[0]);
			else
				*p_FinalValue &= ~(0x6000000 & ModBit[0]);

			break;
		default:
			*p_FinalValue |= (0x06 & ModBit[0]);
			break;
		}
		switch (DG_Product)
		{
		case BME_G03V1:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_k->DigOff != p_ChState->DigOff)
			{
				*p_Prepare &= ~ModBit[0];
				*(p_Prepare + 1) &= ~ModBit[1];
			}
		default:
			if (p_k->Digital != p_ChState->Digital)
			{
				*p_Prepare &= ~ModBit[0];
				*(p_Prepare + 1) &= ~ModBit[1];
			}
		}
		switch (DG_Product)
		{
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_k->OutputModulo != p_ChState->OutputModulo)
			{
				*p_Prepare &= ~ModBit[0];
				*(p_Prepare + 1) &= ~ModBit[1];
			}
			break;
		default:
			break;
		}
	}
	else
	{
		*p_Prepare &= ~ModBit[0];
		*(p_Prepare + 1) &= ~ModBit[1];
		*p_FinalValue &= ~ModBit[0];
		*(p_FinalValue + 1) &= ~ModBit[1];
	}
	p_ChState->GoSignal |= (p_k->GoSignal & 0x77);
	p_ChState->GoSignal &= (p_k->GoSignal | ~0x77);
}

void SetDelayControl_SG05P4(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
					DelayChannel* p_k, DelayChannel* p_ChState, short int pos, DG_InternalData* p_Present)
{
	unsigned long ModBit;
	int i1;
	ModBit = 0x1010101;
	ModBit <<= pos;
	if ((p_k->GoSignal & 0x77) != 0x0)
	{
		if ((p_k->GoSignal & MasterPrimary) != 0x0)
			*(p_FinalValue + 2) |= (0x3F & ModBit);
		else
			*(p_FinalValue + 2) &= ~(0x3F & ModBit);
		if ((p_k->GoSignal & MasterSecondary) != 0x0)
			*(p_FinalValue + 2) |= (0x3F00 & ModBit);
		else
			*(p_FinalValue + 2) &= ~(0x3F00 & ModBit);
		if ((p_k->GoSignal & MasterForce) != 0x0)
			*(p_FinalValue + 2) |= (0x3F0000 & ModBit);
		else
			*(p_FinalValue + 2) &= ~(0x3F0000 & ModBit);
		if ((p_k->GoSignal & StepBackBus) != 0x0)
			*(p_FinalValue + 2) |= (0x3F000000 & ModBit);
		else
			*(p_FinalValue + 2) &= ~(0x3F000000 & ModBit);

		if ((p_k->GoSignal & LocalPrimary) != 0x0)
			*(p_FinalValue + 1) |= (0x3F & ModBit);
		else
			*(p_FinalValue + 1) &= ~(0x3F & ModBit);
		if ((p_k->GoSignal & LocalSecondary) != 0x0)
			*(p_FinalValue + 1) |= (0x3F00 & ModBit);
		else
			*(p_FinalValue + 1) &= ~(0x3F00 & ModBit);
		if ((p_k->GoSignal & LocalForce) != 0x0)
			*(p_FinalValue + 1) |= (0x3F0000 & ModBit);
		else
			*(p_FinalValue + 1) &= ~(0x3F0000 & ModBit);
		if ((p_k->GoSignal & StepBackLocal) != 0x0)
			*(p_FinalValue + 1) |= (0x3F000000 & ModBit);
		else
			*(p_FinalValue + 1) &= ~(0x3F000000 & ModBit);

		if ((p_k->GoSignal & StartLocal) != 0x0)
			*(p_FinalValue + 3) |= (0x3F & ModBit);
		else
			*(p_FinalValue + 3) &= ~(0x3F & ModBit);
		if ((p_k->GoSignal & StartBus) != 0x0)
			*(p_FinalValue + 3) |= (0x3F00 & ModBit);
		else
			*(p_FinalValue + 3) &= ~(0x3F00 & ModBit);
		if ((p_k->GoSignal & RunCircle) != 0x0)
			*(p_FinalValue + 3) |= (0x3F0000 & ModBit);
		else
			*(p_FinalValue + 3) &= ~(0x3F0000 & ModBit);
		*(p_FinalValue + 3) &= ~(0x3F000000 & ModBit);

		if ((p_k->GoSignal & EnableFromE) != 0x0)
			*(p_FinalValue + 4) |= (0x3F & ModBit);
		else
			*(p_FinalValue + 4) &= ~(0x3F & ModBit);
		if ((p_k->GoSignal & EnableFromF) != 0x0)
			*(p_FinalValue + 4) |= (0x3F00 & ModBit);
		else
			*(p_FinalValue + 4) &= ~(0x3F00 & ModBit);
		if ((p_k->GoSignal & EnableFromBus) != 0x0)
			*(p_FinalValue + 4) |= (0x3F0000 & ModBit);
		else
			*(p_FinalValue + 4) &= ~(0x3F0000 & ModBit);
		if ((p_k->GoSignal & InhibitLocal) != 0x0)
			*(p_FinalValue + 4) |= (0x3F000000 & ModBit);
		else
			*(p_FinalValue + 4) &= ~(0x3F000000 & ModBit);
		if ((p_k->GoSignal & (MasterSecondary | LocalSecondary)) != 0x0)
		{
			if ((*p_FinalValue & 0x50000) != 0x0)
				*p_FinalValue |= 0x20000;
			else
				*p_FinalValue &= ~0x20000;
		}
	}
	else
	{
		for (i1 = 1; i1 < 5; i1++)
		{
			*(p_Prepare + i1) &= ~ModBit;
			*(p_FinalValue + i1) &= ~ModBit;
		}
	}
	p_ChState->GoSignal |= (p_k->GoSignal & ~0x8188);
	p_ChState->GoSignal &= (p_k->GoSignal | 0x8188);
}

void SetDelayTriggerControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																				DelayTriggerType* p_dt, DG_InternalData* p_Present)
{
	unsigned long DG_Product = p_Present->DG_Product;
	//unsigned char *pch;
	//unsigned char dummy;
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		if (p_dt->TriggerEnable)
		{
			*p_Prepare &= ~0x80;
			*p_FinalValue &= ~0x80;
		}
		else
		{
			if (p_dt->GateDivider > 0)
				*p_FinalValue |= 0x80;
			else
			{
				*p_Prepare &= ~0x80;
				*p_FinalValue &= ~0x80;
			}
		}
		*p_FinalValue |= 0x40;
		if (p_dt->StopOnPreset)
		{
			p_Present->CommandRegister |= 0x08;
			if (p_dt->PresetValue != p_Present->DelayGeneratorState.DT.PresetValue) 
				*p_Prepare &= ~0x40;
		}
		else
			p_Present->CommandRegister &= ~0x08;
		p_Present->DelayGeneratorState.DT.StopOnPreset = p_dt->StopOnPreset;
		break;
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (p_dt->TriggerEnable)
		{
			*p_Prepare &= ~0x40;
			*p_FinalValue &= ~0x40;
		}
		else
		{
			if (p_dt->GateDivider > 0)
				*p_FinalValue |= 0x40;
			else
			{
				*p_Prepare &= ~0x40;
				*p_FinalValue &= ~0x40;
			}
		}
	default:
		*p_FinalValue |= 0x20;
		if (p_dt->StopOnPreset)
		{
			p_Present->CommandRegister |= 0x08;
			//*p_FinalValue |= 0x20;
			if (p_dt->PresetValue != p_Present->DelayGeneratorState.DT.PresetValue) 
				*p_Prepare &= ~0x20;
		}
		else
			p_Present->CommandRegister &= 0x3EF7;
		p_Present->DelayGeneratorState.DT.StopOnPreset = p_dt->StopOnPreset;
		break;
	}
	if ((p_dt->InternalTrigger) || (p_dt->InternalArm))
	{
		p_Present->CommandRegister &= ~0x05;
		p_Present->CommandRegister |= 0x02;
		if (p_dt->InternalArm)
		{
			p_Present->CommandRegister |= 0x04;
			if (p_dt->RisingEdge)
				p_Present->CommandRegister |= 0x01;
		}
	}
	else
	{
		if (p_dt->SoftwareTrigger)
		{
			p_Present->CommandRegister &= ~0x03;
			p_Present->CommandRegister |= 0x04;
		}
		else
		{
			if (p_dt->RisingEdge)
			{
				p_Present->CommandRegister &= ~0x06;
				p_Present->CommandRegister |= 0x01;
			}
			else
				p_Present->CommandRegister &= ~0x07;
		}
	}
	switch (DG_Product)
	{
	case BME_SG02P3:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_dt->ForceTrigger > 0) || (p_dt->InhibitTrigger > 0))
			*p_FinalValue |= 0x18;
		else
			*p_FinalValue &= ~0x18;
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_dt->ForceTrigger > 0) || (p_dt->InhibitTrigger > 0) || (p_dt->StepBackCounter > 0))
			*p_FinalValue |= 0x50000;
		else
			*p_FinalValue &= ~0x70000;
		if (p_dt->InhibitTrigger > 0)
			*p_FinalValue |= 0x8;
		else
			*p_FinalValue &= ~0x8;
		if (p_dt->ForceTrigger > 0)
			*p_FinalValue |= 0x10;
		else
			*p_FinalValue &= ~0x10;
		if (p_dt->StepBackCounter > 0)
			*p_FinalValue |= 0x20;
		else
			*p_FinalValue &= ~0x20;
		if (p_dt->BurstCounter > 0)
		{
			*p_FinalValue |= 0x01;
			if (p_dt->ForceTrigger > ((p_dt->BurstCounter + 1) * (p_dt->InhibitTrigger + 4)))
				*p_FinalValue |= 0x04;
			else
				*p_FinalValue &= ~0x04;
		}
		else
			*p_FinalValue &= ~0x05;
		break;
	default:
		if ((p_dt->InternalTrigger) || (p_dt->InternalArm))
		{
			*p_FinalValue |= 0x10;
			//if (p_dt->RepCounter != p_Present->DelayGeneratorState.DT.RepCounter) 
			//	*p_Prepare &= ~0x10;
		}
		else
		{
			*p_FinalValue &= ~0x10;
			*p_Prepare &= ~0x10;
		}
		break;
	}
	p_Present->DelayGeneratorState.DT.InternalTrigger = p_dt->InternalTrigger;
	p_Present->DelayGeneratorState.DT.InternalArm = p_dt->InternalArm;
	p_Present->DelayGeneratorState.DT.SoftwareTrigger = p_dt->SoftwareTrigger;
	p_Present->DelayGeneratorState.DT.RisingEdge = p_dt->RisingEdge;
	if (p_dt->ResetWhenDone)
		p_Present->CommandRegister |= 0x40;
	else
		p_Present->CommandRegister &= ~0x40;
	p_Present->DelayGeneratorState.DT.ResetWhenDone = p_dt->ResetWhenDone;
}

void Set_Main_Counter(MainCounterType* p_mc, DG_InternalData* p_Present)
{
	unsigned long DG_Product;
	if (p_mc->Active)
	{
		if ((p_mc->Digital != p_Present->DelayGeneratorState.MC.Digital) ||
								(p_mc->Int3 != p_Present->DelayGeneratorState.MC.Int3))
		{
			p_Present->DelayGeneratorState.MC.Digital = p_mc->Digital;
			p_Present->DelayGeneratorState.MC.Int3 = p_mc->Int3;
			DG_Product = p_Present->DG_Product;
			switch (DG_Product)
			{
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
			case BME_SG02V4:
				break;
			default:
				DataOut(p_Present->Delay_Aux, &(p_mc->Digital), &(p_Present->PciDelgen), 4);
				if ((DG_Product == BME_G03V1) || (DG_Product == BME_G03V2))
					DataOut(p_Present->Delay_Aux, &(p_mc->Int3), &(p_Present->PciDelgen), 4);
			}
		}
	}
}

void Set_Delay_Trigger(DelayTriggerType* p_dt, unsigned long* p_LoadWord, DG_InternalData* p_Present)
{
	int	DG_Product = p_Present->DG_Product;
	//char info[80];
	//int i1;
	unsigned long SerialWord;
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		//sprintf(info,"Set Delay Trigger");
		//AfxMessageBox(info, MB_OK, 0);	
		if ((p_dt->TriggerDAC & 0x0FFF) != (p_Present->DelayGeneratorState.DT.TriggerDAC & 0x0FFF))
		{
			p_Present->DelayGeneratorState.DT.TriggerDAC = p_dt->TriggerDAC;
			SerialWord = (0x8000 | (unsigned long)(p_dt->TriggerDAC & 0xFFF));
			Data32Out(p_Present->Serial_DAC, &SerialWord, &(p_Present->PciDelgen), 4);
		}
		if ((p_dt->GateDAC & 0x0FFF) != (p_Present->DelayGeneratorState.DT.GateDAC & 0x0FFF))
		{
			p_Present->DelayGeneratorState.DT.GateDAC = p_dt->GateDAC;
			SerialWord = (0x9000 | (unsigned long)(p_dt->GateDAC & 0xFFF));
			Data32Out(p_Present->Serial_DAC, &SerialWord, &(p_Present->PciDelgen), 4);
		}
		if (p_dt->StopOnPreset)
		{
			if (p_dt->PresetLong != p_Present->DelayGeneratorState.DT.PresetLong) 
			{
				p_Present->DelayGeneratorState.DT.PresetLong = p_dt->PresetLong;
				Data32Out(p_Present->TriggerCounterAddress, &(p_dt->PresetLong), &(p_Present->PciDelgen), 8);
			}
		}
		break;
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_dt->TriggerDAC & 0x0FFF) != (p_Present->DelayGeneratorState.DT.TriggerDAC & 0x0FFF))
		{
			p_Present->DelayGeneratorState.DT.TriggerLevel = p_dt->TriggerLevel;
			DataOut(p_Present->DAC, &(p_dt->TriggerDAC), &(p_Present->PciDelgen), 2);
		}
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_G03V1:
	case BME_G03V2:
		if (p_dt->StopOnPreset)
		{
			if (p_dt->PresetValue != p_Present->DelayGeneratorState.DT.PresetValue) 
			{
				p_Present->DelayGeneratorState.DT.PresetValue = p_dt->PresetValue;
				DataOut(p_Present->TriggerCounterAddress, &(p_dt->PresetValue), &(p_Present->PciDelgen), 4);
			}
		}
	}

	switch (DG_Product)
	{
	case BME_SG02P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_dt->InhibitTrigger != p_Present->DelayGeneratorState.DT.InhibitTrigger) ||
								(p_dt->ForceTrigger != p_Present->DelayGeneratorState.DT.ForceTrigger))
		{
			p_Present->DelayGeneratorState.DT.InhibitTrigger = p_dt->InhibitTrigger;
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->InhibitTrigger), &(p_Present->PciDelgen), 4);
			p_Present->DelayGeneratorState.DT.ForceTrigger = p_dt->ForceTrigger;
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->ForceTrigger), &(p_Present->PciDelgen), 4);
		}
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_dt->InhibitTrigger != p_Present->DelayGeneratorState.DT.InhibitTrigger) ||
								(p_dt->ForceTrigger != p_Present->DelayGeneratorState.DT.ForceTrigger) ||
								(p_dt->StepBackCounter != p_Present->DelayGeneratorState.DT.StepBackCounter) ||
								(p_dt->BurstCounter != p_Present->DelayGeneratorState.DT.BurstCounter))
		{
			//sprintf(info,"Address : %x, Value : %x ", p_Present->ModuloCounterAddress, p_dt->InhibitTrigger);
			//AfxMessageBox(info, MB_OK, 0);	
			p_Present->DelayGeneratorState.DT.InhibitTrigger = p_dt->InhibitTrigger;
			Data32Out(p_Present->ModuloCounterAddress, &(p_dt->InhibitTrigger), &(p_Present->PciDelgen), 4);
			p_Present->DelayGeneratorState.DT.ForceTrigger = p_dt->ForceTrigger;
			Data32Out(p_Present->ModuloCounterAddress, &(p_dt->ForceTrigger), &(p_Present->PciDelgen), 4);
			p_Present->DelayGeneratorState.DT.StepBackCounter = p_dt->StepBackCounter;
			Data32Out(p_Present->ModuloCounterAddress, &(p_dt->StepBackCounter), &(p_Present->PciDelgen), 4);
			p_Present->DelayGeneratorState.DT.BurstCounter = p_dt->BurstCounter;
			Data32Out(p_Present->ModuloCounterAddress, &(p_dt->BurstCounter), &(p_Present->PciDelgen), 4);
			*p_LoadWord |= 0x8;
		}
		if ((p_dt->InhibitSecondary != p_Present->DelayGeneratorState.DT.InhibitSecondary) ||
								(p_dt->DelaySecondary != p_Present->DelayGeneratorState.DT.DelaySecondary))
		{
			//sprintf(info,"Address : %x, Value : %x ", p_Present->ModuloCounterAddress, p_dt->InhibitTrigger);
			//AfxMessageBox(info, MB_OK, 0);	
			p_Present->DelayGeneratorState.DT.InhibitSecondary = p_dt->InhibitSecondary;
			Data32Out(p_Present->SecondaryCounterAddress, &(p_dt->InhibitSecondary), &(p_Present->PciDelgen), 4);
			p_Present->DelayGeneratorState.DT.DelaySecondary = p_dt->DelaySecondary;
			Data32Out(p_Present->SecondaryCounterAddress, &(p_dt->DelaySecondary), &(p_Present->PciDelgen), 4);
			*p_LoadWord |= 0x8;
		}
		break;
	case BME_G05P2:
	case BME_G05P3:
		if (p_dt->InhibitTrigger != p_Present->DelayGeneratorState.DT.InhibitTrigger)
		{
			p_Present->DelayGeneratorState.DT.InhibitTrigger = p_dt->InhibitTrigger;
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->InhibitTrigger), &(p_Present->PciDelgen), 4);
		}
		break;
	default:
		if ((p_dt->InternalTrigger) || (p_dt->InternalArm))
		{
			if (p_dt->RepCounter != p_Present->DelayGeneratorState.DT.RepCounter) 
			{
				p_Present->DelayGeneratorState.DT.RepCounter = p_dt->RepCounter;
				DataOut(p_Present->ModuloCounterAddress, &(p_dt->RepCounter), &(p_Present->PciDelgen), 4);
			}
		}
		break;
	}
}

void Set_Reference_channel(DelayChannel* p_rf, DG_InternalData* p_Present)
{
	unsigned short dummy,Value;
	unsigned short InvertedValue;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		if ((p_rf->GoSignal & 0x77) != (p_Present->DelayGeneratorState.T0.GoSignal & 0x77))
		{
			if ((p_rf->GoSignal & 0x77) != 0x0)
			{
				Value = 0x3A;
				DataOut(p_Present->Delay_cntrl, &Value, &(p_Present->PciDelgen), -1);
				if (DG_Product == BME_DP01)
				{
					if (p_rf->Digital_HW == 0)
					{
						Value = 0x30;
						DataOut(p_Present->Large_cntrl, &Value, &(p_Present->PciDelgen), -1);
						dummy = 0xFEFF;
						DataOut(p_Present->Large_T0, &dummy, &(p_Present->PciDelgen), 2);
					}
					else
					{
						Value = 0x3A;
						DataOut(p_Present->Large_cntrl, &Value, &(p_Present->PciDelgen), -1);
					}
				}
			}
			else
			{
				Value = 0x38;
				DataOut(p_Present->Delay_cntrl, &Value, &(p_Present->PciDelgen), -1);
				if (DG_Product == BME_DP01)
					DataOut(p_Present->Large_cntrl, &Value, &(p_Present->PciDelgen), -1);
			}
		}
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			DataOut(p_Present->Delay_T0, &(p_rf->Digital), &(p_Present->PciDelgen), 2);
			if (DG_Product == BME_DP01)
			{
				if ((p_rf->Digital_HW == 0) && (p_Present->DelayGeneratorState.T0.Digital_HW != 0))
				{
					Value = 0x30;
					DataOut(p_Present->Large_cntrl, &Value, &(p_Present->PciDelgen), -1);
					dummy = 0xFEFF;
					DataOut(p_Present->Large_T0, &dummy, &(p_Present->PciDelgen), 2);
				}
				if ((p_rf->Digital_HW != 0) && (p_Present->DelayGeneratorState.T0.Digital_HW == 0))
				{
					Value = 0x3A;
					DataOut(p_Present->Large_cntrl, &Value, &(p_Present->PciDelgen), -1);
				}
				if (p_rf->Digital_HW != 0)
					DataOut(p_Present->Large_T0, &(p_rf->Digital_HW), &(p_Present->PciDelgen), 2);
				else
				{
					dummy = 0xFEFF;
					DataOut(p_Present->Large_T0, &dummy, &(p_Present->PciDelgen), 2);
				}
			}
			p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
			p_Present->DelayGeneratorState.T0.DigOff = p_rf->DigOff;
			//printf("Digital T0: %2d \n", p_rf->Digital);
			//printf("Digital : %2d , pos : %1d\n", m.Digital, pos);
		}
		break;
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			if (p_rf->Digital != p_Present->DelayGeneratorState.T0.Digital)
			{
				p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), &(p_Present->PciDelgen), 4);
			}
		}
		break;
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			if ((p_rf->Digital != p_Present->DelayGeneratorState.T0.Digital) ||
						(p_rf->DigOff != p_Present->DelayGeneratorState.T0.DigOff))
			{
				p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
				p_Present->DelayGeneratorState.T0.DigOff = p_rf->DigOff;
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), &(p_Present->PciDelgen), 4);
				DataOut(p_Present->Delay_T0, &(p_rf->DigOff), &(p_Present->PciDelgen), 4);
				//printf("Set_Reference_channel(): %2d,   %2d\n", p_rf->Digital, p_rf->DigOff);
			}
		}
		break;
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			if ((p_rf->Digital != p_Present->DelayGeneratorState.T0.Digital) ||
						(p_rf->OutputModulo != p_Present->DelayGeneratorState.T0.OutputModulo))
			{
				p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
				p_Present->DelayGeneratorState.T0.OutputModulo = p_rf->OutputModulo;
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), &(p_Present->PciDelgen), 4);
				DataOut(p_Present->Delay_T0, &(p_rf->OutputModulo), &(p_Present->PciDelgen), 4);
			}
		}
		break;
	}
	switch (DG_Product)
	{
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			if ((p_rf->Analog & 0x0FFF) != p_Present->DelayGeneratorState.T0.Analog)
			{
				p_Present->DelayGeneratorState.T0.Analog = (p_rf->Analog & 0x0FFF);
				InvertedValue = ~(p_Present->DelayGeneratorState.T0.Analog);
				DataOut(p_Present->DAC_T0, &(InvertedValue), &(p_Present->PciDelgen), 2);
			}
		}
		break;
	default:
		break;
	}
	p_Present->DelayGeneratorState.T0.GoSignal |= (p_rf->GoSignal & 0x77);
	p_Present->DelayGeneratorState.T0.GoSignal &= (p_rf->GoSignal | ~0x77);
}

void Set_Delay_channel(DelayChannel* p_k, DelayChannel* p_ChState, short int pos, 
																															DG_InternalData* p_Present)
{
	unsigned char* pch;
	unsigned short cntrl;
	unsigned short dummy;
	unsigned short adr1,InvertedValue;
	unsigned short DelayAddress;
	unsigned short DacAddress;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (pos)
	{
	case 0: 
		DelayAddress = p_Present->Delay_T0;
		DacAddress = p_Present->DAC_T0;
		break;
	case 1: 
		DelayAddress = p_Present->Delay_A;
		DacAddress = p_Present->DAC_A;
		break;
	case 2: 
		DelayAddress = p_Present->Delay_B;
		DacAddress = p_Present->DAC_B;
		break;
	}
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		if ((p_k->GoSignal & 0x77) != (p_ChState->GoSignal & 0x77))
		{
			if ((p_k->GoSignal & 0x77) != 0x0)
			{
				cntrl = 0x3A + (pos * 0x40);
				DataOut(p_Present->Delay_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
				if (DG_Product == BME_DP01)
				{
					if (p_k->Digital_HW == 0)
					{
						cntrl &= 0xF0;
						DataOut(p_Present->Large_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
						dummy = 0xFEFF;
						DataOut((unsigned short)(p_Present->Large + pos), &dummy, &(p_Present->PciDelgen), 2);
					}
					else
						DataOut(p_Present->Large_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
				}
			}
			else
			{
				cntrl = 0x38 + (pos * 0x40);
				DataOut(p_Present->Delay_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
				if (DG_Product == BME_DP01)
					DataOut(p_Present->Large_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
			}
		}
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			DataOut(DelayAddress, &(p_k->Digital), &(p_Present->PciDelgen), 2);
			if (DG_Product == BME_DP01)
			{
				if ((p_k->Digital_HW == 0) && (p_ChState->Digital_HW != 0))
				{
					cntrl = 0x30 + (pos * 0x40);
					DataOut(p_Present->Large_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
					dummy = 0xFEFF;
					DataOut((unsigned short)(p_Present->Large + pos), &dummy, &(p_Present->PciDelgen), 2);
				}
				if ((p_k->Digital_HW != 0) && (p_ChState->Digital_HW == 0))
				{
					cntrl = 0x3A + (pos * 0x40);
					DataOut(p_Present->Large_cntrl, &cntrl, &(p_Present->PciDelgen), -1);
				}
				if (p_k->Digital_HW != 0)
				{
					DataOut((unsigned short)(p_Present->Large + pos), &(p_k->Digital_HW), 
																							&(p_Present->PciDelgen), 2);
				}
				else
				{
					dummy = 0xFEFF;
					DataOut((unsigned short)(p_Present->Large + pos), &dummy, &(p_Present->PciDelgen), 2);
				}
			}
			p_ChState->Digital = p_k->Digital;
			//printf("Digital : %2d , pos : %1d\n", p_ChState->Digital, pos);

			p_ChState->Analog = (p_k->Analog & 0x0FFF);
			pch = (unsigned char*) &(p_ChState->Analog);
			adr1 = p_Present->DAC + 2 * (pos - 1);
			DataOut(adr1, pch, &(p_Present->PciDelgen), -1);
			adr1 += 1;
			DataOut(adr1, (pch + 1), &(p_Present->PciDelgen), -1);
		}
		break;
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			if (p_k->Digital != p_ChState->Digital)
			{
				p_ChState->Digital = p_k->Digital;
				DataOut(DelayAddress, &(p_k->Digital), &(p_Present->PciDelgen), 4);
			}
		}
		break;
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			if ((p_k->Digital != p_ChState->Digital) ||
						(p_k->DigOff != p_ChState->DigOff))
			{
				p_ChState->Digital = p_k->Digital;
				p_ChState->DigOff = p_k->DigOff;
				DataOut(DelayAddress, &(p_k->Digital), &(p_Present->PciDelgen), 4);
				DataOut(DelayAddress, &(p_k->DigOff), &(p_Present->PciDelgen), 4);
				//printf("Set_Delay_channel() nr. %d: %2d,   %2d\n", pos, p_k->Digital, p_k->DigOff);
			}
		}
		break;
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			if ((p_k->Digital != p_ChState->Digital) ||
						(p_k->OutputModulo != p_ChState->OutputModulo))
			{
				p_ChState->Digital = p_k->Digital;
				p_ChState->OutputModulo = p_k->OutputModulo;
				DataOut(DelayAddress, &(p_k->Digital), &(p_Present->PciDelgen), 4);
				DataOut(DelayAddress, &(p_k->OutputModulo), &(p_Present->PciDelgen), 4);
			}
		}
		break;
	}
	if ((p_k->GoSignal & 0x77) != 0x0)
	{
		if ((p_k->Analog & 0x0FFF) != p_ChState->Analog)
		{
			p_ChState->Analog = (p_k->Analog & 0x0FFF);
			switch (DG_Product)
			{
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				InvertedValue = ~(p_ChState->Analog);
				DataOut(DacAddress, &(InvertedValue), &(p_Present->PciDelgen), 2);
				break;
			default:
				pch = (unsigned char*) &(p_ChState->Analog);
				adr1 = p_Present->DAC + 2 * (pos - 1);
				DataOut(adr1, pch, &(p_Present->PciDelgen), -1);
				adr1 += 1;
				DataOut(adr1, (pch + 1), &(p_Present->PciDelgen), -1);
				break;
			}
		}
	}
	p_ChState->GoSignal |= (p_k->GoSignal & 0x77);
	p_ChState->GoSignal &= (p_k->GoSignal | ~0x77);
}

void Set_Delay_channel_SG05P4(DelayChannel* p_k, DelayChannel* p_ChState, unsigned long* p_LoadWord,
																								unsigned short pos, DG_InternalData* p_Present)
{
	unsigned long IniChar,LoadChar;
	unsigned short DelayAddress;
	unsigned short ModuloAddress;
	int i1;
	BOOL same;
	unsigned long DG_Product = p_Present->DG_Product;
	IniChar = 0x100;
	IniChar <<= pos;
	LoadChar = 0x10000;
	LoadChar <<= pos;
	DelayAddress = p_Present->Delay_A;
	DelayAddress >>= 4;
	DelayAddress += pos;
	DelayAddress <<= 4;
	ModuloAddress = DelayAddress | 0x100;
	if ((p_k->GoSignal & 0x77) != 0x0)
	{
		same = TRUE;
		if (p_k->ListLength != p_ChState->ListLength)
			same = FALSE;
		i1 = 0;
		while ((same) && (i1 < p_k->ListLength))
		{
			if (p_k->DelayList[i1] != p_ChState->DelayList[i1])
				same = FALSE;
			if (p_k->PulseWidth[i1] != p_ChState->PulseWidth[i1])
				same = FALSE;
			if (p_k->DacList[i1] != p_ChState->DacList[i1])
				same = FALSE;
			i1++;
		}
		if(!same)
		{
			Data32Out(p_Present->InitializeAddress, &IniChar, &(p_Present->PciDelgen), 4);
			p_ChState->ListLength = p_k->ListLength;
			//len = sprintf(info,"Address : %x, ini: %x, load: %x \n", DelayAddress, IniChar, LoadChar);
			//sprintf(&(info[len]),"Values : %x, %x, %x ", p_k->DelayList[0], p_k->PulseWidth[0], p_k->DacList[0]);
			//AfxMessageBox(info, MB_OK, 0);	
			for (i1 = 0; i1 < p_k->ListLength; i1++)
			{
				p_ChState->DelayList[i1] = p_k->DelayList[i1];
				p_ChState->PulseWidth[i1] = p_k->PulseWidth[i1];
				p_ChState->DacList[i1] = p_k->DacList[i1];
				Data32Out(DelayAddress, &(p_k->DelayList[i1]), &(p_Present->PciDelgen), 4);
				Data32Out(DelayAddress, &(p_k->PulseWidth[i1]), &(p_Present->PciDelgen), 4);
				Data32Out(DelayAddress, &(p_k->DacList[i1]), &(p_Present->PciDelgen), 4);
			}
			*p_LoadWord |= LoadChar;
		}
		if ((p_k->OutputModulo != p_ChState->OutputModulo) ||
					(p_k->OutputOffset != p_ChState->OutputOffset))
		{
			//sprintf(info,"Modulo : %x, value: %x, offset: %x \n", ModuloAddress, p_k->OutputModulo, p_k->OutputOffset);
			//AfxMessageBox(info, MB_OK, 0);	
			p_ChState->OutputModulo = p_k->OutputModulo;
			p_ChState->OutputOffset = p_k->OutputOffset;
			Data32Out(ModuloAddress, &(p_k->OutputModulo), &(p_Present->PciDelgen), 4);
			Data32Out(ModuloAddress, &(p_k->OutputOffset), &(p_Present->PciDelgen), 4);
			*p_LoadWord |= 0x20;
		}
	}
	p_ChState->GoSignal |= (p_k->GoSignal & 0x77);
	p_ChState->GoSignal &= (p_k->GoSignal | ~0x77);
}


void PrepareCounterControl(DG_BME_Registers* p_pdg, unsigned long* p_LoadWord, DG_InternalData* p_Present)
{
	unsigned long DG_Product = p_Present->DG_Product;
	unsigned long cctrl[6];
	memcpy(cctrl, p_Present->CounterControlState, 20);
	memcpy(p_Present->CounterControlRegister, p_Present->CounterControlState, 20);
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		SetDelayTriggerControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->DT), p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->A), 
																	&(p_Present->DelayGeneratorState.A), 0, p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->B), 
																	&(p_Present->DelayGeneratorState.B), 1, p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->C), 
																	&(p_Present->DelayGeneratorState.C), 2, p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->D), 
																	&(p_Present->DelayGeneratorState.D), 3, p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->E), 
																	&(p_Present->DelayGeneratorState.E), 4, p_Present);
		SetDelayControl_SG05P4(cctrl, p_Present->CounterControlRegister, &(p_pdg->F), 
																	&(p_Present->DelayGeneratorState.F), 5, p_Present);
		if (memcmp(p_Present->CounterControlRegister, p_Present->CounterControlState, 20) != 0)
			*p_LoadWord |= 0x8;
		if ((p_Present->CommandRegisterState & 0x3F0011) != (p_Present->CommandRegister & 0x3F0011))
			*p_LoadWord |= 0x8;
		if (!p_Present->b_DG_Activated)
			LoadCounterControl(cctrl, p_Present);
		break;
	default:
		SetMainCounterControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->MC), p_Present);
		SetDelayTriggerControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->DT), p_Present);
		SetReferenceControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->T0), p_Present);
		SetDelayControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->A), 
																	&(p_Present->DelayGeneratorState.A), 1, p_Present);
		SetDelayControl(cctrl, p_Present->CounterControlRegister, &(p_pdg->B), 
																	&(p_Present->DelayGeneratorState.B), 2, p_Present);
		if (!p_Present->b_DG_Activated)
			LoadCounterControl(cctrl, p_Present);
		break;
	}
}

void ModifyControlRegister(DG_BME_Registers* p_pdg, DG_InternalData* p_Present)
{
	BOOL SetGate_AB;
	int NoBusLines;
	unsigned long DG_Product = p_Present->DG_Product;
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		break;
	default:
		if (p_pdg->Gate_AB != p_Present->DelayGeneratorState.Gate_AB)
		{
			if (((p_pdg->A.GoSignal & 0x77) != 0x0) && ((p_pdg->B.GoSignal & 0x77) != 0x0) && (p_pdg->Gate_AB))
				SetGate_AB = TRUE;
			else
				SetGate_AB = FALSE;
			if (SetGate_AB != p_Present->DelayGeneratorState.Gate_AB)
			{
				if (SetGate_AB)
				{
					if (DG_Product == SRS_DG135)
						p_Present->CommandRegister |= 0x20;
					else
						p_Present->CommandRegister &= 0x3EDF;
					p_Present->DelayGeneratorState.Gate_AB = TRUE;
				}
				else
				{
					if (DG_Product == SRS_DG135)
						p_Present->CommandRegister &= 0x3EDF;
					else
						p_Present->CommandRegister |= 0x20;
					p_Present->DelayGeneratorState.Gate_AB = FALSE;
				}
			}
		}
		break;
	}
	switch (DG_Product)
	{
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((p_pdg->GateFunction & 0x3000) != (p_Present->DelayGeneratorState.GateFunction & 0x3000))
		{
			p_Present->CommandRegister |= (p_pdg->GateFunction & 0x3000);
			p_Present->CommandRegister &= (p_pdg->GateFunction | 0xCFFF);
			p_Present->DelayGeneratorState.GateFunction = (p_pdg->GateFunction & 0x3000);
		}
		if ((p_pdg->DT.MS_Bus & 0x7) != (p_Present->DelayGeneratorState.DT.MS_Bus & 0x7))
		{
			if ((p_pdg->DT.MS_Bus & LocalPrimary) != 0x0)
				p_Present->CommandRegister |= 0x400;
			else
				p_Present->CommandRegister &= 0x3BFF;
			if ((p_pdg->DT.MS_Bus & LocalSecondary) != 0x0)
				p_Present->CommandRegister |= 0x800;
			else
				p_Present->CommandRegister &= 0x37FF;
			if ((p_pdg->DT.MS_Bus & LocalForce) != 0x0)
				p_Present->CommandRegister |= 0x200;
			else
				p_Present->CommandRegister &= 0x3DFF;
			p_Present->DelayGeneratorState.DT.MS_Bus = (p_pdg->DT.MS_Bus & 0x7);
		}
		break;
	case BME_SG08P2:
		if ((p_pdg->DT.MS_Bus & 0xF2) != (p_Present->DelayGeneratorState.DT.MS_Bus & 0xF2))
		{
			NoBusLines = 0;
			if ((p_pdg->DT.MS_Bus & LocalSecondary) != 0x0)
			{
				p_Present->CommandRegister |= 0x1000000;
				NoBusLines++;
			}
			else
				p_Present->CommandRegister &= ~0x1000000;
			if ((p_pdg->DT.MS_Bus & StepBackOnBus) != 0x0)
			{
				p_Present->CommandRegister |= 0x2000000;
				NoBusLines++;
			}
			else
				p_Present->CommandRegister &= ~0x2000000;
			if ((p_pdg->DT.MS_Bus & StartOnBus) != 0x0)
			{
				p_Present->CommandRegister |= 0x4000000;
				NoBusLines++;
			}
			else
				p_Present->CommandRegister &= ~0x4000000;
			if ((p_pdg->DT.MS_Bus & InhibitOnBus) != 0x0)
			{
				p_Present->CommandRegister |= 0x8000000;
				NoBusLines++;
			}
			else
				p_Present->CommandRegister &= ~0x8000000;
			if ((p_pdg->DT.MS_Bus & LoadDataOnBus) != 0x0)
			{
				p_Present->CommandRegister |= 0x10000000;
				NoBusLines++;
			}
			else
				p_Present->CommandRegister &= ~0x10000000;
			if (NoBusLines == 4)
			{
				p_Present->DelayGeneratorState.DT.MS_Bus |= (p_pdg->DT.MS_Bus & 0xF2);
				p_Present->DelayGeneratorState.DT.MS_Bus &= (p_pdg->DT.MS_Bus | ~0xF2);
			}
			else
			{
				p_Present->CommandRegister |= 0xF000000;
				p_Present->CommandRegister &= ~0x10000000;
				p_Present->DelayGeneratorState.DT.MS_Bus |= 0x72;
				p_Present->DelayGeneratorState.DT.MS_Bus &= ~0x80;
			}
		}
	case BME_SG08P1:
		if ((p_pdg->GateFunction & 0x3F0000) != (p_Present->DelayGeneratorState.GateFunction & 0x3F0000))
		{
			p_Present->CommandRegister |= (p_pdg->GateFunction & 0x3F0000);
			p_Present->CommandRegister &= (p_pdg->GateFunction | ~0x3F0000);
			p_Present->DelayGeneratorState.GateFunction = (p_pdg->GateFunction & 0x3F0000);
		}
		break;
	default:
		break;
	}
	if (p_pdg->DT.TriggerEnable != p_Present->DelayGeneratorState.DT.TriggerEnable)
	{
		if (p_pdg->DT.TriggerEnable)
		{
			if ((DG_Product == SRS_DG135) || (DG_Product == BME_DP01))
				p_Present->CommandRegister |= 0x01;
			else
				p_Present->CommandRegister |= 0x10;
		}
		else
		{
			if ((DG_Product == SRS_DG135) || (DG_Product == BME_DP01))
				p_Present->CommandRegister &= 0x3EFE;
			else
				p_Present->CommandRegister &= 0x3F3EEF;
		}
		p_Present->DelayGeneratorState.DT.TriggerEnable = p_pdg->DT.TriggerEnable;
	}
}

void ActionDC(unsigned long* p_Action, 
											 DelayChannelData* p_a, DelayChannelData* p_b, unsigned long DG_Product)
{
	BOOL BusSelect_A,BusSelect_B;
	int i1;
	switch (DG_Product)
	{
	case BME_SG02V7:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G03V5:
	case BME_G03P2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		break;
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_a->GoSignal & 0x70) != 0x0)
			BusSelect_A = TRUE;
		else
			BusSelect_A = FALSE;
		if ((p_b->GoSignal & 0x70) != 0x0)
			BusSelect_B = TRUE;
		else
			BusSelect_B = FALSE;
		//if (BusSelect_A != BusSelect_B)
			//*p_Action |= 0x1;
		if ((p_a->GoSignal & 0x77) != 0x0)
		{
			if ((p_a->GoSignal & 0x7C00) != (p_b->GoSignal & 0x7C00))
				*p_Action |= 0xC;
			else
			{
				if (p_a->ListLength != p_b->ListLength)
					*p_Action |= 0xC;
				else
				{
					for (i1 = 0; i1 < p_a->ListLength; i1++)
					{
						if (p_a->StepBack[i1] != p_b->StepBack[i1])
							*p_Action |= 0xC;
					}
				}
			}
		}
		if ((p_a->GoSignal & 0x180) != (p_b->GoSignal & 0x180))
			*p_Action |= 0x1;
		if (p_a->Disconnect != p_b->Disconnect)
			*p_Action |= 0x1;
		if (p_a->OntoMsBus != p_b->OntoMsBus)
			*p_Action |= 0x1;
		if (p_a->InputPositive != p_b->InputPositive)
			*p_Action |= 0x1;
		break;
	default:
		if (p_a->GoSignal != p_b->GoSignal)
			*p_Action |= 0x1;
		break;
	}
	if (p_a->Positive != p_b->Positive)
		*p_Action |= 0x1;
	if (p_a->Terminate != p_b->Terminate)
		*p_Action |= 0x1;
	if (p_a->HighDrive != p_b->HighDrive)
		*p_Action |= 0x1;
	switch (DG_Product)
	{
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_a->GoSignal & 0x77) != 0x0)
		{
			if (p_a->OutputModulo != p_b->OutputModulo)
				*p_Action |= 0x4;
			if (p_a->OutputOffset != p_b->OutputOffset)
				*p_Action |= 0x4;
		}
		break;
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (p_a->OutputModulo != p_b->OutputModulo)
			*p_Action |= 0x1;
		if (p_a->OutputOffset != p_b->OutputOffset)
			*p_Action |= 0x1;
		break;
	default:
		break;
	}
}

void ActionDT(unsigned long* p_Action, DelayTriggerData* p_a, DelayTriggerData* p_b, unsigned long DG_Product)
{
	if (p_a->InternalTrigger != p_b->InternalTrigger)
		*p_Action |= 0x1;
	if (p_a->InternalArm != p_b->InternalArm)
		*p_Action |= 0x1;
	if (p_a->SoftwareTrigger != p_b->SoftwareTrigger)
		*p_Action |= 0x1;
	if (p_a->ClockSource != p_b->ClockSource)
		*p_Action |= 0x1;
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_a->ClockSource == TriggerInput) ||
						(p_a->ClockSource == TriggerAndOscillator))
		{
			if (p_a->TriggerMultiplier != p_b->TriggerMultiplier)
				*p_Action |= 0x1;		
		}
		break;
	default:
		if (p_a->RisingEdge != p_b->RisingEdge)
			*p_Action |= 0x1;
		break;
	}
	if (p_a->ResetWhenDone != p_b->ResetWhenDone)
	{
		if (p_a->ResetWhenDone)
			*p_Action |= 0x1;
	}
	if (p_a->StopOnPreset != p_b->StopOnPreset)
		*p_Action |= 0x3;
	if (p_a->StopOnPreset)
	{
		if (p_a->PresetValue != p_b->PresetValue)
			*p_Action |= 0x3;
	}
	if (p_a->MS_Bus != p_b->MS_Bus)
		*p_Action |= 0x1;
	if (p_a->Terminate != p_b->Terminate)
		*p_Action |= 0x1;
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		break;
	default:
		if ((!p_a->TriggerEnable) && (!p_b->TriggerEnable))
		{
			if (p_a->PositiveGate != p_b->PositiveGate)
				*p_Action |= 0x1;
			if (p_a->SynchronizeGate != p_b->SynchronizeGate)
				*p_Action |= 0x1;
			if ((p_a->GateDivider == 0) && (p_b->GateDivider != 0))
				*p_Action |= 0x1;
		}
		break;
	}
	//if ((p_b->GateDelay == 0) && (p_a->GateDelay != 0))
		//*p_Action |= 0x1;
	if (p_a->ClockSource != p_b->ClockSource)
		*p_Action |= 0x1;
	if (p_a->ClockEnable != p_b->ClockEnable)
		*p_Action |= 0x1;
}

BOOL IsEqualDT(DelayTriggerType* p_a, DelayTriggerType* p_b, unsigned long DG_Product)
{
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if ((p_a->GateDAC & 0x0FFF) != (p_b->GateDAC & 0x0FFF))
			return FALSE;
		if (p_a->BurstCounter != p_b->BurstCounter)
			return FALSE;
		if (p_a->StepBackCounter != p_b->StepBackCounter)
			return FALSE;
		if (p_a->InhibitSecondary != p_b->InhibitSecondary)
			return FALSE;
		if (p_a->DelaySecondary != p_b->DelaySecondary)
			return FALSE;
	case BME_SG02P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (p_a->ForceTrigger != p_b->ForceTrigger)
			return FALSE;
	case BME_G05P2:
	case BME_G05P3:
		if (p_a->InhibitTrigger != p_b->InhibitTrigger)
			return FALSE;
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
		if ((p_a->TriggerDAC & 0x0FFF) != (p_b->TriggerDAC & 0x0FFF))
			return FALSE;
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_G03V1:
	case BME_G03V2:
		if ((!p_a->InternalTrigger) != (!p_b->InternalTrigger))
			return FALSE;
		if ((!p_a->InternalArm) != (!p_b->InternalArm))
			return FALSE;
		if ((p_a->InternalTrigger) || (p_a->InternalArm))
		{
			if (p_a->RepCounter != p_b->RepCounter)
				return FALSE;
		}
		if ((!p_a->SoftwareTrigger) != (!p_b->SoftwareTrigger))
			return FALSE;
		if ((!p_a->RisingEdge) != (!p_b->RisingEdge))
			return FALSE;
		if ((!p_a->ResetWhenDone) != (!p_b->ResetWhenDone))
			return FALSE;
		if ((!p_a->StopOnPreset) != (!p_b->StopOnPreset))
			return FALSE;
		if (p_a->StopOnPreset)
		{
			if (p_a->PresetValue != p_b->PresetValue)
				return FALSE;
		}
		if ((!p_a->TriggerEnable) != (!p_b->TriggerEnable))
			return FALSE;
	default:
		break;
	}
	return TRUE;
}

BOOL IsEqualMC(MainCounterType* p_a, MainCounterType* p_b, unsigned long DG_Product)
{
	if ((!p_a->Active) != (!p_b->Active))
		return FALSE;
	if (p_a->Active)
	{
		if (p_a->Digital != p_b->Digital)
			return FALSE;
		if ((DG_Product == BME_G03V1) || (DG_Product == BME_G03V2))
		{
			if (p_a->Int3 != p_b->Int3)
				return FALSE;
		}
	}
	return TRUE;
}

BOOL IsEqualDC(DelayChannel* p_a, DelayChannel* p_b, unsigned long DG_Product)
{
	int i1;
	if ((p_a->GoSignal & 0x77) != (p_b->GoSignal & 0x77))
		return FALSE;
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		switch (DG_Product)
		{
		case BME_G03V1:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_a->DigOff != p_b->DigOff)
				return FALSE;
		default:
			if (p_a->Digital != p_b->Digital)
				return FALSE;
		}
		switch (DG_Product)
		{
		case BME_SG08P1:
		case BME_SG08P2:
			if (p_a->ListLength != p_b->ListLength)
				return FALSE;
			for (i1 = 0; i1 < p_a->ListLength; i1++)
			{
				if (p_a->DacList[i1] != p_b->DacList[i1])
					return FALSE;
				if (p_a->DelayList[i1] != p_b->DelayList[i1])
					return FALSE;
				if (p_a->PulseWidth[i1] != p_b->PulseWidth[i1])
					return FALSE;
			}
			if (p_a->OutputOffset != p_b->OutputOffset)
				return FALSE;
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_a->OutputModulo != p_b->OutputModulo)
				return FALSE;
		default:
			break;
		}
		if ((p_a->Analog & 0x0FFF) != (p_b->Analog & 0x0FFF))
			return FALSE;
	}
	return TRUE;
}

BOOL IsEqualPS(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product)
{
	switch (DG_Product)
	{
	case BME_SG08P2:
		if ((p_a->DT.MS_Bus & GateBurstSynch) != (p_b->DT.MS_Bus & GateBurstSynch))
			return FALSE;
		if ((p_a->A.GoSignal & SynchReload) != (p_b->A.GoSignal & SynchReload))
			return FALSE;
		if ((p_a->B.GoSignal & SynchReload) != (p_b->B.GoSignal & SynchReload))
			return FALSE;
		if ((p_a->C.GoSignal & SynchReload) != (p_b->C.GoSignal & SynchReload))
			return FALSE;
		if ((p_a->D.GoSignal & SynchReload) != (p_b->D.GoSignal & SynchReload))
			return FALSE;
		if ((p_a->E.GoSignal & SynchReload) != (p_b->E.GoSignal & SynchReload))
			return FALSE;
		if ((p_a->F.GoSignal & SynchReload) != (p_b->F.GoSignal & SynchReload))
			return FALSE;
	case BME_SG08P1:
		if (p_a->DT.ClockSource != p_b->DT.ClockSource)
			return FALSE;
		if ((p_a->DT.ClockSource == TriggerInput) ||
						(p_a->DT.ClockSource == TriggerAndOscillator))
		{
			if (p_a->DT.TriggerDivider != p_b->DT.TriggerDivider)
				return FALSE;
			if (p_a->DT.TriggerMultiplier != p_b->DT.TriggerMultiplier)
				return FALSE;
		}
		if ((p_a->DT.ClockSource == CrystalOscillator) ||
						(p_a->DT.ClockSource == TriggerAndOscillator) ||
						(p_a->DT.ClockSource == MasterSlaveBus))
		{
			if (p_a->DT.OscillatorDivider != p_b->DT.OscillatorDivider)
				return FALSE;
		}
		if (p_a->DT.ClockEnable != p_b->DT.ClockEnable)
			return FALSE;
		if (p_a->DT.Terminate != p_b->DT.Terminate)
			return FALSE;
		if (p_a->DT.GateTerminate != p_b->DT.GateTerminate)
			return FALSE;
		if (p_a->DT.GateDelay != p_b->DT.GateDelay)
			return FALSE;
		if (p_a->DT.GateDivider != p_b->DT.GateDivider)
			return FALSE;
		if (p_a->DT.PositiveGate != p_b->DT.PositiveGate)
			return FALSE;
		if ((p_a->DT.MS_Bus & Resynchronize) != (p_b->DT.MS_Bus & Resynchronize))
			return FALSE;
		if (p_a->DT.SynchronizeGate != p_b->DT.SynchronizeGate)
			return FALSE;
		if (p_a->DT.IgnoreGate != p_b->DT.IgnoreGate)
			return FALSE;
		if (p_a->A.Positive != p_b->A.Positive)
			return FALSE;
		if (p_a->B.Positive != p_b->B.Positive)
			return FALSE;
		if (p_a->C.Positive != p_b->C.Positive)
			return FALSE;
		if (p_a->D.Positive != p_b->D.Positive)
			return FALSE;
		if (p_a->E.Positive != p_b->E.Positive)
			return FALSE;
		if (p_a->F.Positive != p_b->F.Positive)
			return FALSE;
		if (p_a->A.Terminate != p_b->A.Terminate)
			return FALSE;
		if (p_a->B.Terminate != p_b->B.Terminate)
			return FALSE;
		if (p_a->C.Terminate != p_b->C.Terminate)
			return FALSE;
		if (p_a->D.Terminate != p_b->D.Terminate)
			return FALSE;
		if (p_a->E.Terminate != p_b->E.Terminate)
			return FALSE;
		if (p_a->F.Terminate != p_b->F.Terminate)
			return FALSE;
		if (p_a->E.Disconnect != p_b->E.Disconnect)
			return FALSE;
		if (p_a->E.OntoMsBus != p_b->E.OntoMsBus)
			return FALSE;
		if (p_a->E.InputPositive != p_b->E.InputPositive)
			return FALSE;
		if (p_a->F.Disconnect != p_b->F.Disconnect)
			return FALSE;
		if (p_a->F.OntoMsBus != p_b->F.OntoMsBus)
			return FALSE;
		if (p_a->F.InputPositive != p_b->F.InputPositive)
			return FALSE;
		if ((p_a->A.GoSignal & (SystemClock | DelayClock)) != (p_b->A.GoSignal & (SystemClock | DelayClock)))
			return FALSE;
		if ((p_a->B.GoSignal & (SystemClock | DelayClock)) != (p_b->B.GoSignal & (SystemClock | DelayClock)))
			return FALSE;
		break;
	case BME_SG02P5:
	case BME_SG05P3:
		if ((p_a->T0.GoSignal & DelayClock) != (p_b->T0.GoSignal & DelayClock))
			return FALSE;
		if ((p_a->DT.MS_Bus & Resynchronize) != (p_b->DT.MS_Bus & Resynchronize))
			return FALSE;
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG02P4:
		if ((p_a->T0.GoSignal & SystemClock) != (p_b->T0.GoSignal & SystemClock))
			return FALSE;
	case BME_G05P2:
	case BME_SG05P1:
		if (p_a->DT.SynchronizeGate != p_b->DT.SynchronizeGate)
			return FALSE;
	case BME_SG02P3:
		if (p_a->DT.IgnoreGate != p_b->DT.IgnoreGate)
			return FALSE;
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_G05V3:
	case BME_G05P1:
		if (p_a->PulseWidth != p_b->PulseWidth)
			return FALSE;
	case BME_SG02V5:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05V1:
	case BME_G05V2:
		if (p_a->OutputLevel != p_b->OutputLevel)
			return FALSE;
		if (p_a->T0.HighDrive != p_b->T0.HighDrive)
			return FALSE;
		if (p_a->A.HighDrive != p_b->A.HighDrive)
			return FALSE;
		if (p_a->B.HighDrive != p_b->B.HighDrive)
			return FALSE;
		if (p_a->T0.Terminate != p_b->T0.Terminate)
			return FALSE;
		if (p_a->A.Terminate != p_b->A.Terminate)
			return FALSE;
		if (p_a->B.Terminate != p_b->B.Terminate)
			return FALSE;
		if (p_a->DT.GateDivider != p_b->DT.GateDivider)
			return FALSE;
		if (p_a->DT.PositiveGate != p_b->DT.PositiveGate)
			return FALSE;
	case BME_G03V3:
		if (p_a->T0.Positive != p_b->T0.Positive)
			return FALSE;
		if (p_a->A.Positive != p_b->A.Positive)
			return FALSE;
		if (p_a->B.Positive != p_b->B.Positive)
			return FALSE;
		if (p_a->DT.Terminate != p_b->DT.Terminate)
			return FALSE;
	case BME_SG02V4:
	case BME_G02V3:
		if (p_a->DT.TriggerDivider != p_b->DT.TriggerDivider)
			return FALSE;
		if (p_a->DT.OscillatorDivider != p_b->DT.OscillatorDivider)
			return FALSE;
		if (p_a->DT.ClockSource != p_b->DT.ClockSource)
			return FALSE;
		if (p_a->DT.ClockEnable != p_b->DT.ClockEnable)
			return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

void Set_Prescaler(DG_BME_Registers* p_pdg, unsigned long* p_LoadWord, DG_InternalData* p_Present)
{
	unsigned long Value;
	unsigned long Remainder;
	unsigned long  PrescalerValue[4];
	unsigned long pscl,psch,psct;
	unsigned long pscbits;
	DG_BME_Registers* p_state = &(p_Present->DelayGeneratorState);
	unsigned long DG_Product = p_Present->DG_Product;
	pscl = p_Present->PrescalerState[0];
	psch = p_Present->PrescalerState[1];
	psct = p_Present->PrescalerState[2];
	switch (DG_Product)
	{
	case BME_SG02P4:
	case BME_G05P3:
	case BME_SG05P2:
		pscl &= ~0x40000000;
		break;
	case BME_SG08P1:
	case BME_SG08P2:
	case BME_SG05P3:
	case BME_SG02P5:
		if ((p_pdg->DT.MS_Bus & Resynchronize) != (p_state->DT.MS_Bus  & Resynchronize))
		{
			p_state->DT.MS_Bus |= (p_pdg->DT.MS_Bus & Resynchronize);
			p_state->DT.MS_Bus &= (p_pdg->DT.MS_Bus | ~Resynchronize);
			if ((p_pdg->DT.MS_Bus & Resynchronize) != 0x0)
				pscl &= ~0x40000000;
			else
				pscl |= 0x40000000;
		}
		break;
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if (p_pdg->DT.UseF != p_state->DT.UseF)
		{
			p_state->DT.UseF = p_pdg->DT.UseF;
			if (p_pdg->DT.UseF)
				pscl |= 0x800;
			else
				pscl &= ~0x800;
		}
		if (p_pdg->DT.SynchronizeGate != p_state->DT.SynchronizeGate)
		{
			p_state->DT.SynchronizeGate = p_pdg->DT.SynchronizeGate;
			if (p_pdg->DT.SynchronizeGate)
				pscl |= 0x1000;
			else
				pscl &= ~0x1000;
		}
		if (p_pdg->DT.IgnoreGate != p_state->DT.IgnoreGate)
		{
			p_state->DT.IgnoreGate = p_pdg->DT.IgnoreGate;
			if (p_pdg->DT.IgnoreGate)
				pscl |= 0x2000;
			else
				pscl &= ~0x2000;
		}
		if (p_pdg->DT.ClockEnable != p_state->DT.ClockEnable)
		{
			p_state->DT.ClockEnable = p_pdg->DT.ClockEnable;
			if (p_pdg->DT.ClockEnable)
				pscl |= 0x80;
			else
				pscl &= ~0x80;
		}
		if (p_pdg->DT.PositiveGate != p_state->DT.PositiveGate)
		{
			p_state->DT.PositiveGate = p_pdg->DT.PositiveGate;
			if (p_pdg->DT.PositiveGate)
				pscl |= 0x8000;
			else
				pscl &= ~0x8000;
		}
		if (p_pdg->DT.GateDivider != p_state->DT.GateDivider)
		{
			p_state->DT.GateDivider = p_pdg->DT.GateDivider;
			Value = (unsigned long)p_pdg->DT.GateDivider;
			if (Value <= 0)
			{
				pscl |= 0x4000;
				pscl &= 0xFF00FFFF;
			}
			else
			{
				pscl &= ~0x4000;
				Value -= 1;
				Value &= 0xFF;
				Value <<= 16;
				Value &= 0xFF0000;
				pscl |= Value;
				Value |= 0xFF00FFFF;
				pscl &= Value;
			}
		}
		if (p_pdg->DT.GateDelay != p_state->DT.GateDelay)
		{
			p_state->DT.GateDelay = p_pdg->DT.GateDelay;
			Value = p_pdg->DT.GateDelay;
			if (Value == 0)
				psct &= ~0x3F00;
			else
			{
				Value <<= 8;
				Value &= 0x3F00;
				psct |= Value;
				Value |= 0xFFFFC0FF;
				psct &= Value;
			}
		}
		if (p_pdg->DT.ClockSource != p_state->DT.ClockSource)
		{
			p_state->DT.ClockSource = p_pdg->DT.ClockSource;
			if (p_pdg->DT.ClockSource == TriggerInput)
			{
				pscl |= 0x20;
				pscl &= ~0x20000040;
			}
			if (p_pdg->DT.ClockSource == TriggerAndOscillator)
			{
				pscl |= 0x20000020;
				pscl &= ~0x40;
			}
			if (p_pdg->DT.ClockSource == CrystalOscillator)
			{
				pscl &= ~0x20000060;
			}
			if (p_pdg->DT.ClockSource == MasterSlaveBus)
			{
				pscl |= 0x40;
				pscl &= ~0x20000020;
			}
		}
		if ((p_pdg->DT.ClockSource == CrystalOscillator) ||
						(p_pdg->DT.ClockSource == TriggerAndOscillator) ||
						(p_pdg->DT.ClockSource == MasterSlaveBus))
		{
			if (p_pdg->DT.OscillatorDivider != p_state->DT.OscillatorDivider)
			{
				p_state->DT.OscillatorDivider = p_pdg->DT.OscillatorDivider;
				Value = (unsigned long)p_pdg->DT.OscillatorDivider;
				pscbits = 0x0;
				if (Value > 1)
				{
					Value -= 1;
					pscbits |= Value;
				}
				pscl |= pscbits;
				pscbits |= 0xFFFFFFE0;
				pscl &= pscbits;
			}
		}
		if ((p_pdg->DT.ClockSource == TriggerInput) ||
						(p_pdg->DT.ClockSource == TriggerAndOscillator))
		{
			if (p_pdg->DT.TriggerDivider != p_state->DT.TriggerDivider)
			{
				p_state->DT.TriggerDivider = p_pdg->DT.TriggerDivider;
				Value = (unsigned long)p_pdg->DT.TriggerDivider;
				pscbits = 0x0;
				if (Value > 1)
				{
					Value -= 1;
					pscbits |= Value;
				}
				pscbits <<= 24;
				pscbits &= 0x1F000000;
				pscl |= pscbits;
				pscbits |= 0xE0FFFFFF;
				pscl &= pscbits;
			}
			if (p_pdg->DT.TriggerMultiplier != p_state->DT.TriggerMultiplier)
			{
				p_state->DT.TriggerMultiplier = p_pdg->DT.TriggerMultiplier;
				pscbits = p_pdg->DT.TriggerMultiplier;
				pscbits &= 0xF;
				psct |= pscbits;
				pscbits |= 0x3FF0;
				psct &= pscbits;
				pscbits = p_pdg->DT.TriggerMultiplier;
				pscbits &= 0x700;
				pscl |= pscbits;
				pscbits |= 0xFFFFF8FF;
				pscl &= pscbits;
			}
		}
		if ((p_pdg->DT.ClockSource == TriggerAndOscillator) || (p_pdg->DT.ClockSource == TriggerInput))
		{
			if (p_pdg->DT.ClockSource == TriggerAndOscillator)
				pscbits = (p_pdg->DT.OscillatorDivider / p_pdg->DT.TriggerDivider) + 3;
			else
				pscbits = 7;
			pscbits = min(15, pscbits);
			pscbits <<= 4;
			pscbits &= 0xF0;
			psct |= pscbits;
			pscbits |= 0xFFFFFF0F;
			psct &= pscbits;
		}
		if (p_pdg->DT.Terminate != p_state->DT.Terminate)
		{
			p_state->DT.Terminate = p_pdg->DT.Terminate;
			if (p_pdg->DT.Terminate)
				psch |= 0x10000;
			else
				psch &= ~0x10000;
		}
		if (p_pdg->DT.GateTerminate != p_state->DT.GateTerminate)
		{
			p_state->DT.GateTerminate = p_pdg->DT.GateTerminate;
			if (p_pdg->DT.GateTerminate)
				psch |= 0x20000;
			else
				psch &= ~0x20000;
		}
		if ((p_pdg->A.GoSignal & (DelayClock | SystemClock)) != (p_state->A.GoSignal & (DelayClock | SystemClock)))
		{
			p_state->A.GoSignal |= (p_pdg->A.GoSignal & (DelayClock | SystemClock));
			p_state->A.GoSignal &= (p_pdg->A.GoSignal | ~(DelayClock | SystemClock));
			if ((p_pdg->A.GoSignal & (DelayClock | SystemClock)) != 0x0)
				psch |= 0x40000;
			else
				psch &= ~0x40000;
		}
		if ((p_pdg->B.GoSignal & (DelayClock | SystemClock)) != (p_state->B.GoSignal & (DelayClock | SystemClock)))
		{
			p_state->B.GoSignal |= (p_pdg->B.GoSignal & (DelayClock | SystemClock));
			p_state->B.GoSignal &= (p_pdg->B.GoSignal | ~(DelayClock | SystemClock));
			if ((p_pdg->B.GoSignal & (DelayClock | SystemClock)) != 0x0)
				psch |= 0x80000;
			else
				psch &= ~0x80000;
		}
		if (p_pdg->A.Positive != p_state->A.Positive)
		{
			p_state->A.Positive = p_pdg->A.Positive;
			if (p_pdg->A.Positive)
				psch |= 0x100;
			else
				psch &= ~0x100;
		}
		if (p_pdg->A.Terminate != p_state->A.Terminate)
		{
			p_state->A.Terminate = p_pdg->A.Terminate;
			if (p_pdg->A.Terminate)
				psch |= 0x01;
			else
				psch &= ~0x01;
		}
		if ((p_pdg->A.GoSignal & SynchReload) != (p_state->A.GoSignal & SynchReload))
		{
			p_state->A.GoSignal |= (p_pdg->A.GoSignal & SynchReload);
			p_state->A.GoSignal &= (p_pdg->A.GoSignal | ~SynchReload);
			if ((p_pdg->A.GoSignal & SynchReload) != 0x0)
				psct |= 0x10000;
			else
				psct &= ~0x10000;
		}
		if (p_pdg->B.Positive != p_state->B.Positive)
		{
			p_state->B.Positive = p_pdg->B.Positive;
			if (p_pdg->B.Positive)
				psch |= 0x200;
			else
				psch &= ~0x200;
		}
		if (p_pdg->B.Terminate != p_state->B.Terminate)
		{
			p_state->B.Terminate = p_pdg->B.Terminate;
			if (p_pdg->B.Terminate)
				psch |= 0x02;
			else
				psch &= ~0x02;
		}
		if ((p_pdg->B.GoSignal & SynchReload) != (p_state->B.GoSignal & SynchReload))
		{
			p_state->B.GoSignal |= (p_pdg->B.GoSignal & SynchReload);
			p_state->B.GoSignal &= (p_pdg->B.GoSignal | ~SynchReload);
			if ((p_pdg->B.GoSignal & SynchReload) != 0x0)
				psct |= 0x20000;
			else
				psct &= ~0x20000;
		}
		if (p_pdg->C.Positive != p_state->C.Positive)
		{
			p_state->C.Positive = p_pdg->C.Positive;
			if (p_pdg->C.Positive)
				psch |= 0x400;
			else
				psch &= ~0x400;
		}
		if (p_pdg->C.Terminate != p_state->C.Terminate)
		{
			p_state->C.Terminate = p_pdg->C.Terminate;
			if (p_pdg->C.Terminate)
				psch |= 0x04;
			else
				psch &= ~0x04;
		}
		if ((p_pdg->C.GoSignal & SynchReload) != (p_state->C.GoSignal & SynchReload))
		{
			p_state->C.GoSignal |= (p_pdg->C.GoSignal & SynchReload);
			p_state->C.GoSignal &= (p_pdg->C.GoSignal | ~SynchReload);
			if ((p_pdg->C.GoSignal & SynchReload) != 0x0)
				psct |= 0x40000;
			else
				psct &= ~0x40000;
		}
		if (p_pdg->D.Positive != p_state->D.Positive)
		{
			p_state->D.Positive = p_pdg->D.Positive;
			if (p_pdg->D.Positive)
				psch |= 0x800;
			else
				psch &= ~0x800;
		}
		if (p_pdg->D.Terminate != p_state->D.Terminate)
		{
			p_state->D.Terminate = p_pdg->D.Terminate;
			if (p_pdg->D.Terminate)
				psch |= 0x08;
			else
				psch &= ~0x08;
		}
		if ((p_pdg->D.GoSignal & SynchReload) != (p_state->D.GoSignal & SynchReload))
		{
			p_state->D.GoSignal |= (p_pdg->D.GoSignal & SynchReload);
			p_state->D.GoSignal &= (p_pdg->D.GoSignal | ~SynchReload);
			if ((p_pdg->D.GoSignal & SynchReload) != 0x0)
				psct |= 0x80000;
			else
				psct &= ~0x80000;
		}
		if (p_pdg->E.Positive != p_state->E.Positive)
		{
			p_state->E.Positive = p_pdg->E.Positive;
			if (p_pdg->E.Positive)
				psch |= 0x1000;
			else
				psch &= ~0x1000;
		}
		if (p_pdg->E.Terminate != p_state->E.Terminate)
		{
			p_state->E.Terminate = p_pdg->E.Terminate;
			if (p_pdg->E.Terminate)
				psch |= 0x10;
			else
				psch &= ~0x10;
		}
		if (p_pdg->E.Disconnect != p_state->E.Disconnect)
		{
			p_state->E.Disconnect = p_pdg->E.Disconnect;
			if (p_pdg->E.Disconnect)
				psch |= 0x100000;
			else
				psch &= ~0x100000;
		}
		if (p_pdg->E.InputPositive != p_state->E.InputPositive)
		{
			p_state->E.InputPositive = p_pdg->E.InputPositive;
			if (p_pdg->E.InputPositive)
				psch &= ~0x400000;
			else
				psch |= 0x400000;
		}
		if (p_pdg->E.OntoMsBus != p_state->E.OntoMsBus)
		{
			p_state->E.OntoMsBus = p_pdg->E.OntoMsBus;
			if (p_pdg->E.OntoMsBus)
				psch |= 0x1000000;
			else
				psch &= ~0x1000000;
		}
		if ((p_pdg->E.GoSignal & SynchReload) != (p_state->E.GoSignal & SynchReload))
		{
			p_state->E.GoSignal |= (p_pdg->E.GoSignal & SynchReload);
			p_state->E.GoSignal &= (p_pdg->E.GoSignal | ~SynchReload);
			if ((p_pdg->E.GoSignal & SynchReload) != 0x0)
				psct |= 0x100000;
			else
				psct &= ~0x100000;
		}
		if (p_pdg->F.Positive != p_state->F.Positive)
		{
			p_state->F.Positive = p_pdg->F.Positive;
			if (p_pdg->F.Positive)
				psch |= 0x2000;
			else
				psch &= ~0x2000;
		}
		if (p_pdg->F.Terminate != p_state->F.Terminate)
		{
			p_state->F.Terminate = p_pdg->F.Terminate;
			if (p_pdg->F.Terminate)
				psch |= 0x20;
			else
				psch &= ~0x20;
		}
		if (p_pdg->F.Disconnect != p_state->F.Disconnect)
		{
			p_state->F.Disconnect = p_pdg->F.Disconnect;
			if (p_pdg->F.Disconnect)
				psch |= 0x200000;
			else
				psch &= ~0x200000;
		}
		if (p_pdg->F.InputPositive != p_state->F.InputPositive)
		{
			p_state->F.InputPositive = p_pdg->F.InputPositive;
			if (p_pdg->F.InputPositive)
				psch &= ~0x800000;
			else
				psch |= 0x800000;
		}
		if (p_pdg->F.OntoMsBus != p_state->F.OntoMsBus)
		{
			p_state->F.OntoMsBus = p_pdg->F.OntoMsBus;
			if (p_pdg->F.OntoMsBus)
				psch |= 0x2000000;
			else
				psch &= ~0x2000000;
		}
		if ((p_pdg->F.GoSignal & SynchReload) != (p_state->F.GoSignal & SynchReload))
		{
			p_state->F.GoSignal |= (p_pdg->F.GoSignal & SynchReload);
			p_state->F.GoSignal &= (p_pdg->F.GoSignal | ~SynchReload);
			if ((p_pdg->F.GoSignal & SynchReload) != 0x0)
				psct |= 0x200000;
			else
				psct &= ~0x200000;
		}
		if ((p_pdg->DT.MS_Bus & (GateOnBusPositive | GateOnBusNegative)) != (p_state->DT.MS_Bus  & (GateOnBusPositive | GateOnBusNegative)))
		{
			p_state->DT.MS_Bus |= (p_pdg->DT.MS_Bus & (GateOnBusPositive | GateOnBusNegative));
			p_state->DT.MS_Bus &= (p_pdg->DT.MS_Bus | ~(GateOnBusPositive | GateOnBusNegative));
			if ((p_pdg->DT.MS_Bus & (GateOnBusPositive | GateOnBusNegative)) != 0x0)
			{
				psch |= 0x8000000;
				if ((p_pdg->DT.MS_Bus & GateOnBusNegative) != 0x0)
					psch |= 0x4000000;
				else
					psch &= ~0x4000000;
			}
			else
				psch &= ~0xC000000;
		}
		if ((p_pdg->DT.MS_Bus & GateBurstSynch) != (p_state->DT.MS_Bus  & GateBurstSynch))
		{
			p_state->DT.MS_Bus |= (p_pdg->DT.MS_Bus & GateBurstSynch);
			p_state->DT.MS_Bus &= (p_pdg->DT.MS_Bus | ~GateBurstSynch);
			if ((p_pdg->DT.MS_Bus & GateBurstSynch) != 0x0)
				psct |= 0x8000;
			else
				psct &= ~0x8000;
		}
		PrescalerValue[0] = pscl;
		PrescalerValue[1] = psch;
		PrescalerValue[2] = psct;
		if (memcmp(PrescalerValue, p_Present->PrescalerState, 12) != 0)
			*p_LoadWord |= 0x18;
		LoadPrescaler(PrescalerValue, p_Present);
		break;
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (p_pdg->DT.SynchronizeGate != p_state->DT.SynchronizeGate)
		{
			p_state->DT.SynchronizeGate = p_pdg->DT.SynchronizeGate;
			if (p_pdg->DT.SynchronizeGate)
				pscl |= 0x1000;
			else
				pscl &= ~0x1000;
		}
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P2:
	case BME_G05P3:
		if (p_pdg->DT.IgnoreGate != p_state->DT.IgnoreGate)
		{
			p_state->DT.IgnoreGate = p_pdg->DT.IgnoreGate;
			if (p_pdg->DT.IgnoreGate)
				pscl |= 0x2000;
			else
				pscl &= ~0x2000;
		}
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
		if (p_pdg->DT.SynchronizeGate)
			Value = 1;
		else
			Value = (unsigned long)p_pdg->DT.OscillatorDivider;
		Value = min(16, Value);
		Value -= 1;
		Value <<= 8;
		Value &= 0xF00;
		pscl |= Value;
		Value |= 0xFFFFF0FF;
		pscl &= Value;
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
		if (p_pdg->DT.ClockSource != p_state->DT.ClockSource)
		{
			p_state->DT.ClockSource = p_pdg->DT.ClockSource;
			if (p_pdg->DT.ClockSource == TriggerInput)
			{
				pscl |= 0x20;
				pscl &= ~0x20000040;
			}
			if (p_pdg->DT.ClockSource == TriggerAndOscillator)
			{
				pscl |= 0x20000020;
				pscl &= ~0x40;
			}
			if (p_pdg->DT.ClockSource == CrystalOscillator)
			{
				pscl &= ~0x20000060;
			}
			if (p_pdg->DT.ClockSource == MasterSlaveBus)
			{
				pscl |= 0x40;
				pscl &= ~0x20000020;
			}
		}
		if ((p_pdg->DT.ClockSource == CrystalOscillator) ||
						(p_pdg->DT.ClockSource == TriggerAndOscillator) ||
						(p_pdg->DT.ClockSource == MasterSlaveBus))
		{
			if (p_pdg->DT.OscillatorDivider != p_state->DT.OscillatorDivider)
			{
				p_state->DT.OscillatorDivider = p_pdg->DT.OscillatorDivider;
				Value = (unsigned long)p_pdg->DT.OscillatorDivider;
				pscbits = 0x0;
				if (Value > 1)
				{
					switch (DG_Product)
					{
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05P3:
					case BME_SG05P2:
					case BME_SG05P3:
						Remainder = 1;
						break;
					default:
						Remainder = Value - (2 * (Value / 2));
						break;
					}
					if ((Remainder == 0) || (Value > 17))
					{
						pscbits |= 0x10;
						Value /= 2;
					}
					Value -= 1;
					pscbits |= Value;
				}
				pscl |= pscbits;
				pscbits |= 0xFFFFFFE0;
				pscl &= pscbits;
			}
		}
		if ((p_pdg->DT.ClockSource == TriggerInput) ||
						(p_pdg->DT.ClockSource == TriggerAndOscillator))
		{
			if (p_pdg->DT.TriggerDivider != p_state->DT.TriggerDivider)
			{
				p_state->DT.TriggerDivider = p_pdg->DT.TriggerDivider;
				Value = (unsigned long)p_pdg->DT.TriggerDivider;
				pscbits = 0x0;
				if (Value > 1)
				{
					switch (DG_Product)
					{
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05P3:
					case BME_SG05P2:
					case BME_SG05P3:
						if (p_Present->ExternalOscillatorFrequency < 150.0)
							Remainder = 1;
						else
							Remainder = Value - (2 * (Value / 2));
						break;
					default:
						Remainder = Value - (2 * (Value / 2));
						break;
					}
					if ((Remainder == 0) || (Value > 17))
					{
						pscbits |= 0x10;
						Value /= 2;
					}
					Value -= 1;
					pscbits |= Value;
				}
				if (p_pdg->DT.ClockSource == TriggerInput)
				{
					switch (DG_Product)
					{
					case BME_SG02V5:
					case BME_G03V4:
					case BME_G05V1:
						pscl |= pscbits;
						pscbits |= 0xFFFFFFE0;
						pscl &= pscbits;
						break;
					default:
						pscbits <<= 24;
						pscbits &= 0x1F000000;
						pscl |= pscbits;
						pscbits |= 0xE0FFFFFF;
						pscl &= pscbits;
						break;
					}
				}
				else
				{
					pscbits <<= 24;
					pscbits &= 0x1F000000;
					pscl |= pscbits;
					pscbits |= 0xE0FFFFFF;
					pscl &= pscbits;
				}
			}
		}
		if ((p_pdg->DT.ClockSource == TriggerAndOscillator) || (p_pdg->DT.ClockSource == TriggerInput))
		{
			if (p_pdg->DT.ClockSource == TriggerAndOscillator)
				pscbits = (p_pdg->DT.OscillatorDivider / p_pdg->DT.TriggerDivider) + 3;
			else
				pscbits = 7;
			pscbits = min(15, pscbits);
			pscbits <<= 16;
			pscbits &= 0xF0000;
			psch |= pscbits;
			pscbits |= 0xFFF0FFFF;
			psch &= pscbits;
		}
		if (p_pdg->OutputLevel != p_state->OutputLevel)
		{
			p_state->OutputLevel = p_pdg->OutputLevel;
			switch (p_pdg->OutputLevel)
			{
			case TTL_VoltageLevel:
				psch &= 0xFFFFCFFF;
				break;
			case NIM_VoltageLevel:
				psch |= 0x3000;
				break;
			case ECL_VoltageLevel:
				psch |= 0x1000;
				psch &= 0xFFFFDFFF;
				break;
			}
		}
		if ((p_pdg->T0.GoSignal & SystemClock) != (p_state->T0.GoSignal & SystemClock))
		{
			p_state->T0.GoSignal |= (p_pdg->T0.GoSignal & SystemClock);
			p_state->T0.GoSignal &= (p_pdg->T0.GoSignal | ~SystemClock);
			if ((p_pdg->T0.GoSignal & SystemClock) != 0x0)
				psch |= 0x800;
			else
				psch &= ~0x800;
		}
		if ((p_pdg->T0.GoSignal & DelayClock) != (p_state->T0.GoSignal & DelayClock))
		{
			p_state->T0.GoSignal |= (p_pdg->T0.GoSignal & DelayClock);
			p_state->T0.GoSignal &= (p_pdg->T0.GoSignal | ~DelayClock);
			if ((p_pdg->T0.GoSignal & DelayClock) != 0x0)
				psch &= ~0x4000;
			else
				psch |= 0x4000;
		}
		if (p_pdg->T0.Positive != p_state->T0.Positive)
		{
			p_state->T0.Positive = p_pdg->T0.Positive;
			if (p_pdg->T0.Positive)
				psch |= 0x10;
			else
				psch &= ~0x10;
		}
		if (p_pdg->T0.Terminate != p_state->T0.Terminate)
		{
			p_state->T0.Terminate = p_pdg->T0.Terminate;
			if (p_pdg->T0.Terminate)
				psch |= 0x01;
			else
				psch &= ~0x01;
		}
		if (p_pdg->T0.HighDrive != p_state->T0.HighDrive)
		{
			p_state->T0.HighDrive = p_pdg->T0.HighDrive;
			if (p_pdg->T0.HighDrive)
				psch |= 0x100;
			else
				psch &= ~0x100;
		}
		if (p_pdg->A.Positive != p_state->A.Positive)
		{
			p_state->A.Positive = p_pdg->A.Positive;
			if (p_pdg->A.Positive)
				psch |= 0x20;
			else
				psch &= ~0x20;
		}
		if (p_pdg->A.Terminate != p_state->A.Terminate)
		{
			p_state->A.Terminate = p_pdg->A.Terminate;
			if (p_pdg->A.Terminate)
				psch |= 0x02;
			else
				psch &= ~0x02;
		}
		if (p_pdg->A.HighDrive != p_state->A.HighDrive)
		{
			p_state->A.HighDrive = p_pdg->A.HighDrive;
			if (p_pdg->A.HighDrive)
				psch |= 0x200;
			else
				psch &= ~0x200;
		}
		if (p_pdg->B.Positive != p_state->B.Positive)
		{
			p_state->B.Positive = p_pdg->B.Positive;
			if (p_pdg->B.Positive)
				psch |= 0x40;
			else
				psch &= ~0x40;
		}
		if (p_pdg->B.Terminate != p_state->B.Terminate)
		{
			p_state->B.Terminate = p_pdg->B.Terminate;
			if (p_pdg->B.Terminate)
				psch |= 0x04;
			else
				psch &= ~0x04;
		}
		if (p_pdg->B.HighDrive != p_state->B.HighDrive)
		{
			p_state->B.HighDrive = p_pdg->B.HighDrive;
			if (p_pdg->B.HighDrive)
				psch |= 0x400;
			else
				psch &= ~0x400;
		}
		if (p_pdg->DT.Terminate != p_state->DT.Terminate)
		{
			p_state->DT.Terminate = p_pdg->DT.Terminate;
			if (p_pdg->DT.Terminate)
				psch |= 0x08;
			else
				psch &= ~0x08;
		}
		if (p_pdg->PulseWidth != p_state->PulseWidth)
		{
			p_state->PulseWidth = p_pdg->PulseWidth;
			Value = (unsigned long)p_pdg->PulseWidth;
			Value <<= 24;
			Value &= 0xFF000000;
			psch |= Value;
			Value |= 0x00FFFFFF;
			psch &= Value;
		}
		if (p_pdg->DT.ClockEnable != p_state->DT.ClockEnable)
		{
			p_state->DT.ClockEnable = p_pdg->DT.ClockEnable;
			if (p_pdg->DT.ClockEnable)
				pscl |= 0x80;
			else
				pscl &= ~0x80;
		}
		if (p_pdg->DT.PositiveGate != p_state->DT.PositiveGate)
		{
			p_state->DT.PositiveGate = p_pdg->DT.PositiveGate;
			if (p_pdg->DT.PositiveGate)
				pscl &= ~0x8000;
			else
				pscl |= 0x8000;
		}
		if (p_pdg->DT.GateDivider != p_state->DT.GateDivider)
		{
			p_state->DT.GateDivider = p_pdg->DT.GateDivider;
			Value = (unsigned long)p_pdg->DT.GateDivider;
			if (Value <= 0)
			{
				pscl |= 0x4000;
				pscl &= 0xFF00FFFF;
			}
			else
			{
				pscl &= ~0x4000;
				Value -= 1;
				Value &= 0xFF;
				Value <<= 16;
				Value &= 0xFF0000;
				pscl |= Value;
				Value |= 0xFF00FFFF;
				pscl &= Value;
			}
		}
		PrescalerValue[0] = pscl;
		PrescalerValue[1] = psch;
		LoadPrescaler(PrescalerValue, p_Present);
		break;
	case BME_G03V3:
		pscl &= 0xFFFF;
		if (p_pdg->T0.Positive != p_state->T0.Positive)
		{
			p_state->T0.Positive = p_pdg->T0.Positive;
			if (p_pdg->T0.Positive)
				pscl |= 0x1000;
			else
				pscl &= 0xEFFF;
		}
		if (p_pdg->A.Positive != p_state->A.Positive)
		{
			p_state->A.Positive = p_pdg->A.Positive;
			if (p_pdg->A.Positive)
				pscl |= 0x2000;
			else
				pscl &= 0xDFFF;
		}
		if (p_pdg->B.Positive != p_state->B.Positive)
		{
			p_state->B.Positive = p_pdg->B.Positive;
			if (p_pdg->B.Positive)
				pscl |= 0x4000;
			else
				pscl &= 0xBFFF;
		}
		if (p_pdg->DT.Terminate != p_state->DT.Terminate)
		{
			p_state->DT.Terminate = p_pdg->DT.Terminate;
			if (p_pdg->DT.Terminate)
				pscl |= 0x8000;
			else
				pscl &= 0x7FFF;
		}
		if (p_pdg->DT.ClockEnable != p_state->DT.ClockEnable)
		{
			p_state->DT.ClockEnable = p_pdg->DT.ClockEnable;
			if (p_pdg->DT.ClockEnable)
				pscl |= 0x80;
			else
				pscl &= 0xFF7F;
		}
		if (p_pdg->DT.ClockSource != p_state->DT.ClockSource)
		{
			p_state->DT.ClockSource = p_pdg->DT.ClockSource;
			if (p_pdg->DT.ClockSource == TriggerInput)
				pscl |= 0x20;
			else
				pscl &= 0xFFDF;
		}
		if (p_pdg->DT.OscillatorDivider != p_state->DT.OscillatorDivider)
		{
			p_state->DT.OscillatorDivider = p_pdg->DT.OscillatorDivider;
			Value = (unsigned long)p_pdg->DT.OscillatorDivider;
			if (Value > 1)
			{
				Remainder = Value - (2 * (Value / 2));
				if (Remainder == 0)
				{
					pscl |= 0x10;
					Value /= 2;
				}
				else
					pscl &= 0xFFEF;
				Value -= 1;
				pscl |= Value;
				Value |= 0xFFF0;
				pscl &= Value;
			}
			else
				pscl &= 0xFFE0;
		}
		PrescalerValue[0] = pscl;
		PrescalerValue[1] = psch;
		LoadPrescaler(PrescalerValue, p_Present);
		break;
	case BME_SG02V4:
	case BME_G02V3:
		pscl &= 0xFF;
		if (p_pdg->DT.ClockEnable != p_state->DT.ClockEnable)
		{
			p_state->DT.ClockEnable = p_pdg->DT.ClockEnable;
			if (p_pdg->DT.ClockEnable)
				pscl |= 0x08;
			else
				pscl &= 0xF7;
		}
		if (p_pdg->DT.ClockSource != p_state->DT.ClockSource)
		{
			p_state->DT.ClockSource = p_pdg->DT.ClockSource;
			if (p_pdg->DT.ClockSource == TriggerInput)
				pscl |= 0x10;
			else
				pscl &= 0xEF;
		}
		if (p_pdg->DT.OscillatorDivider != p_state->DT.OscillatorDivider)
		{
			p_state->DT.OscillatorDivider = p_pdg->DT.OscillatorDivider;
			if (p_pdg->DT.OscillatorDivider > 1)
			{
				Value = (unsigned long)RoundInt((log((double)p_pdg->DT.OscillatorDivider)) / log(2.0));
				Value = min(5, max(0, Value));
				pscl |= Value;
				Value |= 0xF8;
				pscl &= Value;
			}
			else
				pscl &= 0xF8;
		}
		PrescalerValue[0] = pscl;
		PrescalerValue[1] = psch;
		LoadPrescaler(PrescalerValue, p_Present);
		break;
	default:
		break;
	}
}


BOOL IsEqual(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product)
{
	if ((!p_a->Gate_AB) != (!p_b->Gate_AB))
		return FALSE;
	switch (DG_Product)
	{
	case BME_G02V3:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
	case BME_SG02V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (!IsEqualPS(p_a, p_b, DG_Product))
			return FALSE;
		break;
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G03V1:
	case BME_G03V2:
	case BME_G05V1:
	case BME_G05V2:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_G05P3:
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (!IsEqualMC(&(p_a->MC), &(p_b->MC), DG_Product))
			return FALSE;
	case BME_SG02V1:
	case BME_SG02V2:
	case BME_SG02V3:
	case BME_SG02V4:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if (!IsEqualDT(&(p_a->DT), &(p_b->DT), DG_Product))
			return FALSE;
	default:
		if (!IsEqualDC(&(p_a->T0), &(p_b->T0), DG_Product))
			return FALSE;
		if (!IsEqualDC(&(p_a->A), &(p_b->A), DG_Product))
			return FALSE;
		if (!IsEqualDC(&(p_a->B), &(p_b->B), DG_Product))
			return FALSE;
	}
	return TRUE;
}

BOOL ReadCalibrationFile(FILE *stream, int* p_module, char* FileName)
{
	DG_InternalData* p_Present;
	DG_InternalData* p_MasterCard;
	long DG_Number;
	int MasterCard;
	int start,npos;
	double value;
	double MasterIOF,MasterEOF;
	char* res1;
	char line[200];
	char word[200];
	BOOL Error;
	Error = FALSE;
	MasterIOF = CalData.InternalOscillator;
	MasterEOF = CalData.ExternalOscillator;
	MasterCard = -1;
	stream = fopen(FileName, "r" );
	DG_Number = 0;
	while (DG_Number < NoDelayGenerators)
	{
		p_Present = (p_Internal + DG_Number);
		res1 = fgets((char*)line, 200, stream);
		if (res1 != NULL)
		{
			start = 0;
			npos = NextCharacterGroup(word, line, start);
			start = npos;
			switch (p_Present->DG_Product)
			{
				case BME_G02V1:
					if (_stricmp(word, "BME_G02V1"))
						return TRUE;
					break;
				case BME_G02V2:
					if (_stricmp(word, "BME_G02V2"))
						return TRUE;
					break;
				case BME_G02V3:
					if (_stricmp(word, "BME_G02V3"))
						return TRUE;
					break;
				case BME_SG02V1:
					if (_stricmp(word, "BME_SG02V1"))
						return TRUE;
					break;
				case BME_SG02V3:
					if (_stricmp(word, "BME_SG02V3"))
						return TRUE;
					break;
				case BME_SG02V2:
					if (_stricmp(word, "BME_SG02V2"))
						return TRUE;
					break;
				case BME_SG02V4:
					if (_stricmp(word, "BME_SG02V4"))
						return TRUE;
					break;
				case BME_SG02V5:
					if (_stricmp(word, "BME_SG02V5"))
						return TRUE;
					break;
				case BME_SG02V6:
					if (_stricmp(word, "BME_SG02V6"))
						return TRUE;
					break;
				case BME_SG02V7:
					if (_stricmp(word, "BME_SG02V7"))
						return TRUE;
					break;
				case BME_SG02P1:
					if (_stricmp(word, "BME_SG02P1"))
						return TRUE;
					break;
				case BME_SG02P2:
					if (_stricmp(word, "BME_SG02P2"))
						return TRUE;
					break;
				case BME_SG02P3:
					if (_stricmp(word, "BME_SG02P3"))
						return TRUE;
					break;
				case BME_SG02P4:
					if (_stricmp(word, "BME_SG02P4"))
						return TRUE;
					break;
				case BME_SG02P5:
					if (_stricmp(word, "BME_SG02P5"))
						return TRUE;
					break;
				case BME_G03V1:
					if (_stricmp(word, "BME_G03V1"))
						return TRUE;
					break;
				case BME_G03V2:
					if (_stricmp(word, "BME_G03V2"))
						return TRUE;
					break;
				case BME_G03V3:
					if (_stricmp(word, "BME_G03V3"))
						return TRUE;
					break;
				case BME_G03V4:
					if (_stricmp(word, "BME_G03V4"))
						return TRUE;
					break;
				case BME_G03V5:
					if (_stricmp(word, "BME_G03V5"))
						return TRUE;
					break;
				case BME_G03P1:
					if (_stricmp(word, "BME_G03P1"))
						return TRUE;
					break;
				case BME_G03P2:
					if (_stricmp(word, "BME_G03P2"))
						return TRUE;
					break;
				case BME_G05V1:
					if (_stricmp(word, "BME_G05V1"))
						return TRUE;
					break;
				case BME_G05V2:
					if (_stricmp(word, "BME_G05V2"))
						return TRUE;
					break;
				case BME_G05V3:
					if (_stricmp(word, "BME_G05V3"))
						return TRUE;
					break;
				case BME_G05P1:
					if (_stricmp(word, "BME_G05P1"))
						return TRUE;
					break;
				case BME_G05P2:
					if (_stricmp(word, "BME_G05P2"))
						return TRUE;
					break;
				case BME_G05P3:
					if (_stricmp(word, "BME_G05P3"))
						return TRUE;
					break;
				case BME_SG05P1:
					if (_stricmp(word, "BME_SG05P1"))
						return TRUE;
					break;
				case BME_SG05P2:
					if (_stricmp(word, "BME_SG05P2"))
						return TRUE;
					break;
				case BME_SG05P3:
					if (_stricmp(word, "BME_SG05P3"))
						return TRUE;
					break;
				case BME_SG08P1:
					if (_stricmp(word, "BME_SG08P1"))
						return TRUE;
					break;
				case BME_SG08P2:
					if (_stricmp(word, "BME_SG08P2"))
						return TRUE;
					break;
				default:
					break;
			}
			npos = NextCharacterGroup(word, line, start);
			if (*(p_module + DG_Number) == MasterModule)
			{
				if (_stricmp(word, "Master"))
					return TRUE;
			}
			else
			{
				if (_stricmp(word, "Slave"))
					return TRUE;
			}
			switch (p_Present->DG_Product)
			{
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				res1 = fgets((char*)line, 200, stream);
				if (res1 != NULL)
				{
					value = atof(line);
					if (value >= 9.9)
						p_Present->InternalOscillatorFrequency = value;
					else
						return TRUE;
				}
				else
					return TRUE;
				res1 = fgets((char*)line, 200, stream);
				if (res1 != NULL)
				{
					value = atof(line);
					p_Present->ExternalOscillatorFrequency = value;
				}
				else
					return TRUE;
				if (*(p_module + DG_Number) == MasterModule)
				{
					p_MasterCard = p_Present;
					p_Present->p_Master = p_MasterCard;
					MasterCard = p_Present->DG_Product;
					MasterIOF = p_Present->InternalOscillatorFrequency;
					MasterEOF = p_Present->ExternalOscillatorFrequency;
				}
				else
					p_Present->p_Master = p_MasterCard;
				break;
			default:
				if (*(p_module + DG_Number) == MasterModule)
				{
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
					{
						value = atof(line);
						if (value >= 9.9)
							p_Present->InternalOscillatorFrequency = value;
						else
							return TRUE;
					}
					else
						return TRUE;
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
					{
						value = atof(line);
						p_Present->ExternalOscillatorFrequency = value;
					}
					else
						return TRUE;
					p_MasterCard = p_Present;
					p_Present->p_Master = p_MasterCard;
					MasterCard = p_Present->DG_Product;
					MasterIOF = p_Present->InternalOscillatorFrequency;
					MasterEOF = p_Present->ExternalOscillatorFrequency;
				}
				else
				{
					p_Present->p_Master = p_MasterCard;
					p_Present->InternalOscillatorFrequency = MasterIOF;
					p_Present->ExternalOscillatorFrequency = MasterEOF;
				}
				break;
			}
			switch (p_Present->DG_Product)
			{
				case BME_G02V2:
				case BME_G02V3:
				case BME_SG02V2:
				case BME_SG02V3:
				case BME_SG02V4:
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P3:
				case BME_SG02P4:
				case BME_SG02P5:
				case BME_G03V2:
				case BME_G03V3:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
				case BME_SG08P1:
				case BME_SG08P2:
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
						p_Present->TenMhzZeroTime = atof(line);
					else
						return TRUE;
				case BME_G02V1:
				case BME_SG02V1:
				case BME_G03V1:
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
						p_Present->TenMhzp1Time = atof(line);
					else
						return TRUE;
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
						p_Present->TenMhzp2Time = atof(line);
					else
						return TRUE;
					break;
				default:
					break;
			}
			switch (p_Present->DG_Product)
			{
				case BME_G03V1:
				case BME_G03V2:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
					res1 = fgets((char*)line, 200, stream);
					if (res1 != NULL)
						p_Present->TenMhzResetTime = atof(line);
					else
						return TRUE;
					break;
				default:
					break;
			}
		}
		else
			return TRUE;
		p_Present->b_ModuleCalibrated = TRUE;
		CalibrateModule(DG_Number);
		DG_Number++;
	}
	return FALSE;
}

void InitializeCalibrationConstants()
{
	DG_InternalData* p_Present;
	long DG_Number;
	double Factor;
	Factor = 1.0;
	DG_Number = 0;
	while (DG_Number < NoDelayGenerators)
	{
		p_Present = (p_Internal + DG_Number);
		switch (p_Present->DG_Product)
		{
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				Factor = max(8.0, Factor);
				break;
			default:
				break;
		}
		DG_Number++;
	}
	CalData.SG02_ZeroTime = BME_SG02_ZeroTime;
	CalData.SG02_p1Time = BME_SG02_p1Time;
	CalData.SG02_p2Time = BME_SG02_p2Time;

	CalData.SG02V2_p1Time = BME_SG02V2_p1Time;
	CalData.SG02V2_p2Time = BME_SG02V2_p2Time;

	CalData.SG02V1_GoTime = BME_SG02V1_GoTime;
	CalData.SG02V1_p1Time = BME_SG02V1_p1Time;
	CalData.SG02V1_p2Time = BME_SG02V1_p2Time;

	CalData.G02_ZeroTime = BME_G02_ZeroTime;
	CalData.G02_p1Time = BME_G02_p1Time;
	CalData.G02_p2Time = BME_G02_p2Time;

	CalData.G03_ZeroTime = BME_G03_ZeroTime;
	CalData.G03_p1Time = BME_G03_p1Time;
	CalData.G03_p2Time = BME_G03_p2Time;
	CalData.G03_ResetTime = BME_G03_ResetTime;

	CalData.ClockDelay = SlaveClockDelay;
	CalData.TriggerDelay = SlaveTriggerDelay;

	CalData.InternalOscillator = Factor * OscillatorFrequency;
	CalData.ExternalOscillator = Factor * OscillatorFrequency;
}

void DelayChannelTest(DelayChannel* p_dc)
{
	int i1;
	for (i1 = 0; i1 < MemDepth; i1++)
	{
		p_dc->DelayList[i1] = 0xFFFF;
		p_dc->PulseWidth[i1] = 0xFFFF;
		p_dc->DacList[i1] = 0xFF0FFF;
	}
	p_dc->Digital = 0xFFFF;
	p_dc->DigOff = 0;
	p_dc->ListLength = MemLength;
	p_dc->OutputModulo = 0xFFFF;
	p_dc->OutputOffset = 0xFFFF;
	p_dc->AnalogData = 0xFFF;
	p_dc->GoSignal = 0x73FFF;
	p_dc->DoneSignal = 0x0FF;
	p_dc->Positive = FALSE;
	p_dc->Terminate = TRUE;
	p_dc->HighDrive = TRUE;
	p_dc->Disconnect = TRUE;
	p_dc->OntoMsBus = TRUE;
	p_dc->InputPositive = FALSE;
}

void ResetDelayChannel(DelayChannel* p_dc)
{
	int i1;
	for (i1 = 0; i1 < MemDepth; i1++)
	{
		p_dc->DelayList[i1] = 0xF;
		p_dc->PulseWidth[i1] = 0xF;
		p_dc->DacList[i1] = 0;
	}
	p_dc->Digital = 0;
	p_dc->DigOff = 0;
	p_dc->ListLength = 0;
	p_dc->OutputModulo = 0;
	p_dc->OutputOffset = 0;
	p_dc->AnalogData = 0;
	p_dc->GoSignal = 0x0;
	p_dc->DoneSignal = 0x0;
	p_dc->Positive = TRUE;
	p_dc->Terminate = FALSE;
	p_dc->HighDrive = FALSE;
	p_dc->Disconnect = FALSE;
	p_dc->OntoMsBus = FALSE;
	p_dc->InputPositive = TRUE;
}

void ResetMainCounter(MainCounterType* p_mc)
{
	p_mc->Active = FALSE;
	p_mc->ReserveFlag = FALSE;
	p_mc->Digital = 0;
	p_mc->Int3 = 0;
}

void DelayTriggerTest(DelayTriggerType* p_dt)
{
	p_dt->InhibitTrigger = 0xFFFFFFFF;
	p_dt->ForceTrigger = 0xFFFFFFFF;
	p_dt->BurstCounter = 0xFFFFFFFF;
	p_dt->StepBackCounter = 0xFFFFFFFF;
	p_dt->GateDelay = 63;
	p_dt->TriggerLevel = 0x0;
	p_dt->PresetLong = 0xFFFFFFF;
	//p_dt->Prescaler = 0x08;
	p_dt->OscillatorDivider = 32;
	p_dt->TriggerDivider = 1;
	p_dt->TriggerMultiplier = 0x70F;
	p_dt->ClockSource = TriggerInput;
	p_dt->GateDivider = 255;
	p_dt->MS_Bus = 0x8;
	p_dt->PositiveGate = FALSE;
	p_dt->IgnoreGate = TRUE;
	p_dt->SynchronizeGate = TRUE;
	p_dt->ClockEnable = TRUE;
	p_dt->InternalTrigger = TRUE;
	p_dt->InternalArm = FALSE;
	p_dt->SoftwareTrigger = FALSE;
	p_dt->RisingEdge = FALSE;
	p_dt->StopOnPreset = TRUE;
	p_dt->ResetWhenDone = TRUE;
	p_dt->TriggerEnable = TRUE;
	p_dt->Terminate = FALSE;
	p_dt->GateTerminate = TRUE;
	p_dt->UseF = TRUE;
}

void ResetDelayTrigger(DelayTriggerType* p_dt)
{
	p_dt->InhibitTrigger = 0;
	p_dt->InhibitSecondary = 0;
	p_dt->ForceTrigger = 0;
	p_dt->BurstCounter = 0;
	p_dt->StepBackCounter = 0;
	p_dt->GateDelay = 0;
	p_dt->DelaySecondary = 0;
	p_dt->TriggerLevel = 0xC000C00;
	p_dt->PresetLong = 0;
	//p_dt->Prescaler = 0x08;
	p_dt->OscillatorDivider = 8;
	p_dt->TriggerDivider = 6;
	p_dt->TriggerMultiplier = 0;
	p_dt->ClockSource = CrystalOscillator;
	p_dt->GateDivider = 1;
	p_dt->MS_Bus = (LocalPrimary | LocalForce);
	p_dt->PositiveGate = TRUE;
	p_dt->IgnoreGate = FALSE;
	p_dt->SynchronizeGate = FALSE;
	p_dt->ClockEnable = FALSE;
	p_dt->InternalTrigger = FALSE;
	p_dt->InternalArm = FALSE;
	p_dt->SoftwareTrigger = FALSE;
	p_dt->RisingEdge = FALSE;
	p_dt->StopOnPreset = FALSE;
	p_dt->ResetWhenDone = FALSE;
	p_dt->TriggerEnable = FALSE;
	p_dt->Terminate = TRUE;
	p_dt->GateTerminate = FALSE;
	p_dt->UseF = FALSE;
}

void CopyTriggerControl_V4(DelayTriggerData* p_dt, DelayTriggerData_V4* p_dtv4)
{
	ResetTriggerControl(p_dt);
	p_dt->InternalClock = p_dtv4->InternalClock;
	p_dt->ForceTrigger = p_dtv4->ForceTrigger;
	p_dt->StepBackTime = p_dtv4->StepBackTime;
	p_dt->GateDelay = p_dtv4->GateDelay;
	p_dt->BurstCounter = p_dtv4->BurstCounter;
	p_dt->TriggerLevel = p_dtv4->TriggerLevel;
	p_dt->GateLevel = p_dtv4->GateLevel;
	p_dt->PresetLong = p_dtv4->PresetLong;
	p_dt->MS_Bus = p_dtv4->MS_Bus;

	p_dt->OscillatorDivider = p_dtv4->OscillatorDivider;
	p_dt->TriggerDivider = p_dtv4->TriggerDivider;
	p_dt->TriggerMultiplier = p_dtv4->TriggerMultiplier;
	p_dt->ClockSource = p_dtv4->ClockSource;
	p_dt->GateDivider = p_dtv4->GateDivider;
	p_dt->PositiveGate = p_dtv4->PositiveGate;
	p_dt->IgnoreGate = p_dtv4->IgnoreGate;
	p_dt->SynchronizeGate = p_dtv4->SynchronizeGate;
	p_dt->ClockEnable = p_dtv4->ClockEnable;
	p_dt->InternalTrigger = p_dtv4->InternalTrigger;
	p_dt->InternalArm = p_dtv4->InternalArm;
	p_dt->SoftwareTrigger = p_dtv4->SoftwareTrigger;
	p_dt->RisingEdge = p_dtv4->RisingEdge;
	p_dt->StopOnPreset = p_dtv4->StopOnPreset;
	p_dt->ResetWhenDone = p_dtv4->ResetWhenDone;
	p_dt->TriggerEnable = p_dtv4->TriggerEnable;
	p_dt->Terminate = p_dtv4->Terminate;
	p_dt->GateTerminate = p_dtv4->GateTerminate;
	p_dt->UseF = p_dtv4->UseF;
}

void CopyTriggerControl_V3(DelayTriggerData* p_dt, DelayTriggerData_V3* p_dtv3)
{
	ResetTriggerControl(p_dt);
	p_dt->InternalClock = p_dtv3->InternalClock;
	p_dt->ForceTrigger = p_dtv3->ForceTrigger;
	p_dt->TriggerLevel = p_dtv3->TriggerLevel;
	p_dt->PresetValue = p_dtv3->PresetValue;
	p_dt->MS_Bus = p_dtv3->MS_Bus;

	p_dt->OscillatorDivider = p_dtv3->OscillatorDivider;
	p_dt->TriggerDivider = p_dtv3->TriggerDivider;
	p_dt->ClockSource = p_dtv3->ClockSource;
	p_dt->GateDivider = p_dtv3->GateDivider;
	p_dt->PositiveGate = p_dtv3->PositiveGate;
	p_dt->IgnoreGate = p_dtv3->IgnoreGate;
	p_dt->ClockEnable = p_dtv3->ClockEnable;
	p_dt->InternalTrigger = p_dtv3->InternalTrigger;
	p_dt->InternalArm = p_dtv3->InternalArm;
	p_dt->SoftwareTrigger = p_dtv3->SoftwareTrigger;
	p_dt->RisingEdge = p_dtv3->RisingEdge;
	p_dt->StopOnPreset = p_dtv3->StopOnPreset;
	p_dt->ResetWhenDone = p_dtv3->ResetWhenDone;
	p_dt->TriggerEnable = p_dtv3->TriggerEnable;
	p_dt->Terminate = p_dtv3->Terminate;
}

void CopyTriggerControl_V2(DelayTriggerData* p_dt, DelayTriggerData_V2* p_dtv2)
{
	ResetTriggerControl(p_dt);
	p_dt->InternalClock = p_dtv2->InternalClock;
	p_dt->ForceTrigger = p_dtv2->ForceTrigger;
	p_dt->TriggerLevel = p_dtv2->TriggerLevel;
	p_dt->PresetValue = p_dtv2->PresetValue;
	p_dt->MS_Bus = (LocalPrimary | LocalForce);

	p_dt->OscillatorDivider = p_dtv2->OscillatorDivider;
	p_dt->TriggerDivider = p_dtv2->TriggerDivider;
	p_dt->ClockSource = p_dtv2->ClockSource;
	p_dt->GateDivider = p_dtv2->GateDivider;
	if ((!p_dtv2->TriggerEnable) && (p_dtv2->InternalTrigger))
		p_dt->PositiveGate = !p_dtv2->PositiveGate;
	else
		p_dt->PositiveGate = p_dtv2->PositiveGate;
	p_dt->IgnoreGate = p_dtv2->IgnoreGate;
	p_dt->ClockEnable = p_dtv2->ClockEnable;
	p_dt->InternalTrigger = p_dtv2->InternalTrigger;
	p_dt->InternalArm = p_dtv2->InternalArm;
	p_dt->SoftwareTrigger = p_dtv2->SoftwareTrigger;
	p_dt->RisingEdge = p_dtv2->RisingEdge;
	p_dt->StopOnPreset = p_dtv2->StopOnPreset;
	p_dt->ResetWhenDone = p_dtv2->ResetWhenDone;
	p_dt->TriggerEnable = p_dtv2->TriggerEnable;
	p_dt->Terminate = p_dtv2->Terminate;
}

void CopyTriggerControl_V1(DelayTriggerData* p_dt, DelayTriggerData_V1* p_dtv1)
{
	ResetTriggerControl(p_dt);
	p_dt->InternalClock = p_dtv1->InternalClock;
	p_dt->TriggerLevel = p_dtv1->TriggerLevel;
	p_dt->PresetValue = p_dtv1->PresetValue;
	p_dt->MS_Bus = LocalPrimary;

	p_dt->OscillatorDivider = p_dtv1->OscillatorDivider;
	p_dt->TriggerDivider = p_dtv1->TriggerDivider;
	p_dt->ClockSource = p_dtv1->ClockSource;
	p_dt->GateDivider = p_dtv1->GateDivider;
	if ((!p_dtv1->TriggerEnable) && (p_dtv1->InternalTrigger))
		p_dt->PositiveGate = !p_dtv1->PositiveGate;
	else
		p_dt->PositiveGate = p_dtv1->PositiveGate;
	p_dt->ClockEnable = p_dtv1->ClockEnable;
	p_dt->InternalTrigger = p_dtv1->InternalTrigger;
	p_dt->InternalArm = p_dtv1->InternalArm;
	p_dt->SoftwareTrigger = p_dtv1->SoftwareTrigger;
	p_dt->RisingEdge = p_dtv1->RisingEdge;
	p_dt->StopOnPreset = p_dtv1->StopOnPreset;
	p_dt->ResetWhenDone = p_dtv1->ResetWhenDone;
	p_dt->TriggerEnable = p_dtv1->TriggerEnable;
	p_dt->Terminate = p_dtv1->Terminate;
}

void ResetTriggerControl(DelayTriggerData* p_dt)
{
	p_dt->InternalClock = -1.0;
	p_dt->InhibitSecondary = -1.0;
	p_dt->ForceTrigger = -1.0;
	p_dt->StepBackTime = -1.0;
	p_dt->GateDelay = -1.0;
	p_dt->TriggerLevel = 1.25;
	p_dt->GateLevel = 1.25;
	p_dt->PresetLong = 0;
	p_dt->BurstCounter = 1;
	p_dt->DelaySecondary = 0;
	p_dt->MS_Bus = LocalPrimary;

	p_dt->OscillatorDivider = 1;
	p_dt->TriggerDivider = 6;
	p_dt->TriggerMultiplier = 1;
	p_dt->ClockSource = CrystalOscillator;
	p_dt->GateDivider = 1;
	p_dt->PositiveGate = TRUE;
	p_dt->IgnoreGate = FALSE;
	p_dt->SynchronizeGate = FALSE;
	p_dt->ClockEnable = FALSE;
	p_dt->InternalTrigger = FALSE;
	p_dt->InternalArm = FALSE;
	p_dt->SoftwareTrigger = FALSE;
	p_dt->RisingEdge = FALSE;
	p_dt->StopOnPreset = FALSE;
	p_dt->ResetWhenDone = FALSE;
	p_dt->TriggerEnable = FALSE;
	p_dt->Terminate = TRUE;
	p_dt->GateTerminate = FALSE;
	p_dt->UseF = FALSE;
}

void CopyDelayControl_V3(DelayChannelData* p_dc, DelayChannelData_V3* p_v3)
{
	ResetDelayControl(p_dc);
	p_dc->FireFirst = p_v3->FireFirst;
	p_dc->SetBack = p_v3->SetBack;
	p_dc->OutputModulo = p_v3->OutputModulo;
	p_dc->OutputOffset = p_v3->OutputOffset;
	p_dc->GoSignal =  p_v3->GoSignal;
	p_dc->DoneSignal =  p_v3->DoneSignal;
	p_dc->Positive = p_v3->Positive;
	p_dc->Terminate = p_v3->Terminate;
	p_dc->HighDrive = p_v3->HighDrive;
}

void CopyDelayControl_V2(DelayChannelData* p_dc, DelayChannelData_V2* p_v2)
{
	ResetDelayControl(p_dc);
	p_dc->FireFirst = p_v2->FireFirst;
	p_dc->SetBack = p_v2->SetBack;
	p_dc->OutputModulo = p_v2->OutputModulo;
	p_dc->GoSignal = 0x0;
	if (p_v2->Active)
		p_dc->GoSignal |= MasterPrimary;
	if (p_v2->FtActive)
		p_dc->GoSignal |= LocalForce;
	p_dc->DoneSignal = 0x0;
	if ((p_v2->Active) & (!p_v2->FtActive))
		p_dc->DoneSignal |= LocalForce;
	if ((!p_v2->Active) & (p_v2->FtActive))
		p_dc->DoneSignal |= MasterPrimary;
	p_dc->Positive = p_v2->Positive;
	p_dc->Terminate = p_v2->Terminate;
	p_dc->HighDrive = p_v2->HighDrive;
}

void ResetDelayControl(DelayChannelData* p_dc)
{
	int i1;
	for (i1 = 0; i1 < MemDepth; i1++)
	{
		p_dc->DelayTime[i1] = -1.0;
		p_dc->PulseWidth[i1] = -1.0;
		p_dc->StepBack[i1] = i1;
	}
	p_dc->ListLength = 0;
	p_dc->SetBack = -1.0;
	p_dc->OutputModulo = 1;
	p_dc->OutputOffset = 0;
	p_dc->GoSignal = 0x0;
	p_dc->DoneSignal = 0x0;
	p_dc->Positive = TRUE;
	p_dc->Terminate = FALSE;
	p_dc->HighDrive = FALSE;
	p_dc->Disconnect = FALSE;
	p_dc->OntoMsBus = FALSE;
	p_dc->InputPositive = TRUE;
}

long SetTrigger(DG_BME_Registers* p_dgr, DG_BME_Control* p_BDG, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	double MainCounterTime,Increment;
	int t_count,InhibitZeroShift,ForceZeroShift;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;

	Increment = p_Present->TriggerIncrement;

	p_dgr->DT.MS_Bus = p_BDG->DT.MS_Bus;
	p_dgr->DT.RisingEdge = p_BDG->DT.RisingEdge;
	p_dgr->DT.TriggerEnable = p_BDG->DT.TriggerEnable;
	p_dgr->DT.InternalTrigger = p_BDG->DT.InternalTrigger;
	p_dgr->DT.InternalArm = p_BDG->DT.InternalArm;
	p_dgr->DT.SoftwareTrigger = p_BDG->DT.SoftwareTrigger;
	p_dgr->DT.StopOnPreset = p_BDG->DT.StopOnPreset;
	p_dgr->DT.ResetWhenDone = p_BDG->DT.ResetWhenDone;
	p_dgr->DT.PresetLong = p_BDG->DT.PresetLong;

	p_dgr->DT.GateDivider = p_BDG->DT.GateDivider;
	p_dgr->DT.PositiveGate = p_BDG->DT.PositiveGate;
	p_dgr->DT.IgnoreGate = p_BDG->DT.IgnoreGate;
	p_dgr->DT.OscillatorDivider = p_BDG->DT.OscillatorDivider;
	p_dgr->DT.TriggerDivider = p_BDG->DT.TriggerDivider;
	p_dgr->DT.ClockEnable = p_BDG->DT.ClockEnable;
	p_dgr->DT.ClockSource = p_BDG->DT.ClockSource;
	if ((p_dgr->DT.ClockSource < CrystalOscillator) || (MasterSlaveBus < p_dgr->DT.ClockSource))
		return 7;
	p_dgr->DT.Terminate = p_BDG->DT.Terminate;
	
	p_dgr->DT.TriggerDAC = RoundInt(((p_BDG->DT.TriggerLevel + 2.5) * 4096.0 / 5.0));
	p_dgr->DT.TriggerDAC = max(0, min(4095, p_dgr->DT.TriggerDAC));

	t_count = 0;
	if (p_dgr->DT.InternalTrigger)
		t_count++;
	if (p_dgr->DT.InternalArm)
		t_count++;
	if (p_dgr->DT.SoftwareTrigger)
		t_count++;
	if (t_count > 1)
		return 4;

	switch (p_dgr->DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			if (RoundInt(p_BDG->DT.GateDelay / p_Present->OscillatorIncrement) < 1)
				InhibitZeroShift = 3;
			else
				InhibitZeroShift = 2;
			ForceZeroShift = 3;
			break;
		default:
			InhibitZeroShift = 3;
			ForceZeroShift = 3;
			if ((p_dgr->DT.ClockSource == CrystalOscillator) || (p_dgr->DT.ClockSource == MasterSlaveBus))
			{
				if (p_dgr->DT.OscillatorDivider >= 2)
				{
					InhibitZeroShift = 2;
					ForceZeroShift = 2;
				}
			}
			if ((p_dgr->DT.ClockSource == TriggerInput) || (p_dgr->DT.ClockSource == TriggerAndOscillator))
			{
				if (p_dgr->DT.TriggerDivider >= 2)
				{
					InhibitZeroShift = 2;
					ForceZeroShift = 2;
				}
			}
			break;
	}
	switch (p_dgr->DG_Product)
	{
		case BME_SG08P1:
		case BME_SG08P2:
			p_dgr->DT.GateTerminate = p_BDG->DT.GateTerminate;
			p_dgr->DT.UseF = p_BDG->DT.UseF;
			p_dgr->DT.SynchronizeGate = p_BDG->DT.SynchronizeGate;
			p_dgr->DT.GateDAC = RoundInt(((p_BDG->DT.GateLevel + 2.5) * 4096.0 / 5.0));
			p_dgr->DT.GateDAC = max(0, min(4095, p_dgr->DT.GateDAC));
			p_dgr->DT.GateDelay = max(0, min(63, RoundInt(p_BDG->DT.GateDelay / p_Present->OscillatorIncrement)));
			p_dgr->DT.BurstCounter = max(0, p_BDG->DT.BurstCounter - 1);
			p_dgr->DT.TriggerMultiplier = min(7, max(0, RoundInt(log((double)(p_BDG->DT.TriggerMultiplier))/log(2.0))));
			if (p_Present->InternalOscillatorFrequency > 164.0)
				p_dgr->DT.TriggerMultiplier |= 0x400;
			if (p_Present->ExternalOscillatorFrequency > 320.0)
				p_dgr->DT.TriggerMultiplier |= 0x200;
			else
			{
				if (p_Present->ExternalOscillatorFrequency > 160.0)
					p_dgr->DT.TriggerMultiplier |= 0x100;
			}
			p_dgr->DT.StepBackCounter = max(0, (RoundInt((p_BDG->DT.StepBackTime / Increment)) - ForceZeroShift));
			p_dgr->DT.InhibitSecondary = max(0, (RoundInt((p_BDG->DT.InhibitSecondary / Increment)) - InhibitZeroShift));
			p_dgr->DT.DelaySecondary = max(0, p_BDG->DT.DelaySecondary);
		case BME_SG05P2:
		case BME_SG05P3:
			if ((p_BDG->DT.SynchronizeGate) && (p_Present->ExternalOscillatorFrequency > 75.0))
				p_dgr->DT.SynchronizeGate = TRUE;
		case BME_SG05P1:
			if ((p_BDG->DT.SynchronizeGate) && (Increment <= 0.0135))
				p_dgr->DT.SynchronizeGate = TRUE;
		case BME_SG02P3:
			p_dgr->DT.ForceTrigger = max(0, (RoundInt((p_BDG->DT.ForceTrigger / Increment)) - ForceZeroShift));
		case BME_G05P2:
		case BME_G05P3:
			p_dgr->DT.InhibitTrigger = max(0, (RoundInt((p_BDG->DT.InhibitTrigger / Increment)) - InhibitZeroShift));
			break;
		default:
			if ((p_dgr->DT.InternalTrigger) || (p_dgr->DT.InternalArm))
				p_dgr->DT.RepCounter = max(0, (RoundInt((p_BDG->DT.InternalClock / Increment)) - 2));
			else
				p_dgr->DT.RepCounter = 0x3FFFFFFF;
			break;
	}
	switch (p_dgr->DG_Product)
	{
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
		case BME_SG08P1:
		case BME_SG08P2:
			break;
		default:
			p_dgr->DT.RepCounter = max(1, p_dgr->DT.RepCounter);
			break;
	}

	MainCounterTime = -1.0;
	switch (p_dgr->DG_Product)
	{
		case BME_G03V1:
		case BME_G03V2:
			if ((p_BDG->T0.GoSignal & 0x77) != 0x0)
			{
				MainCounterTime =  max(MainCounterTime, p_BDG->T0.FireFirst);
				MainCounterTime =  max(MainCounterTime, p_BDG->T0.SetBack);
			}
			if ((p_BDG->A.GoSignal & 0x77) != 0x0)
			{
				MainCounterTime =  max(MainCounterTime, p_BDG->A.FireFirst);
				MainCounterTime =  max(MainCounterTime, p_BDG->A.SetBack);
			}
			if ((p_BDG->B.GoSignal & 0x77) != 0x0)
			{
				MainCounterTime =  max(MainCounterTime, p_BDG->B.FireFirst);
				MainCounterTime =  max(MainCounterTime, p_BDG->B.SetBack);
			}
			if (MainCounterTime >= 0.0)
			{
				MainCounterTime += 1.0;
				MainCounterTime = Increment * (double)(RoundInt((MainCounterTime / Increment)));
				p_dgr->MC.Active = TRUE;
				p_dgr->MC.Digital = RoundInt((MainCounterTime / Increment));
				p_dgr->MC.Int3 = p_dgr->MC.Digital + 1;
			}
			break;
		default:
			break;
	}
	return 0;
}

long SetReference(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number)
{
	double Remainder;
	DG_InternalData* p_Present;
	unsigned int IntDelay,IntNumber;
	unsigned long DG_Product;
	long result;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;

	p_a->GoSignal = p_dl->GoSignal;
	p_a->DoneSignal = p_dl->DoneSignal;
	p_a->Positive = p_dl->Positive;
	p_a->Terminate = p_dl->Terminate;
	p_a->HighDrive = p_dl->HighDrive;
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		if (p_dl->FireFirst < 0.0)
			return 3;
		switch (DG_Product)
		{
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			result = DelayNumbers(&Remainder, &IntDelay, p_dl->FireFirst, DG_Number);
			if (result != 0)
				return result;
			p_a->Analog = RoundInt((Remainder * 40960.0));
			p_a->Analog = min(p_a->Analog, 4095);
			break;
		default:
			result = T0Numbers(&IntDelay, p_dl->FireFirst, DG_Number);
			if (result != 0)
				return result;
			break;
		}
		switch (DG_Product)
		{
		case BME_G03V1:
		case BME_G03V2:
			if ((p_dl->SetBack > MaxBME_G0XRange) || (p_dl->FireFirst > MaxBME_G0XRange))
				return 5;
			if (p_dl->FireFirst >= 0.0)
			{
				if (p_dl->SetBack > p_dl->FireFirst)
				{
					result = T0Numbers(&IntNumber, (p_dl->SetBack - p_Present->ResetTime), DG_Number);
					if (result != 0)
						return result;
					p_a->DigOff = MainCounter - IntNumber;
				}
				else
					p_a->DigOff = MainCounter + 1;
				p_a->Digital = MainCounter - IntDelay;
			}
			else
			{
				p_a->Digital = MainCounter + 1;
				p_a->DigOff = MainCounter + 1;
				return 3;
			}
			break;
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_dl->SetBack > MaxBME_G0XRange)
				return 5;
			if (p_dl->FireFirst >= 0.0)
			{
				if (p_dl->SetBack > p_dl->FireFirst)
				{
					result = T0Numbers(&IntNumber, (p_dl->SetBack - p_Present->ResetTime), DG_Number);
					if (result != 0)
						return result;
					p_a->DigOff = IntNumber;
				}
			}
		case BME_G02V1:
		case BME_G02V2:
		case BME_G02V3:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_SG02V3:
		case BME_SG02V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_dl->FireFirst > MaxBME_G0XRange)
				return 5;
			p_a->Digital = IntDelay;
			break;
		default:
			p_a->Digital = IntDelay;
		}
		switch (DG_Product)
		{
		case BME_G05P2:
		case BME_G05P3:
			p_a->ModOffset = (unsigned short)(p_dl->OutputOffset & 0xFFFF);
			p_a->ModOffset = max(0, (p_a->ModOffset + 1));
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
			p_a->ModCounter = (unsigned short)(p_dl->OutputModulo & 0xFFFF);
			p_a->ModCounter = max(1, p_a->ModCounter);
			break;
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			p_a->ModCounter = (unsigned short)(p_dl->OutputModulo & 0xFFFF);
			p_a->ModCounter = max(0, (p_a->ModCounter - 1));
			p_a->ModOffset = (unsigned short)(p_dl->OutputOffset & 0xFFFF);
			break;
		default:
			break;
		}
	}
	return 0;
}

long SetChannel(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number)
{
	double Remainder;
	unsigned int IntDelay,IntNumber;
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	long result;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;

	p_a->GoSignal = p_dl->GoSignal;
	p_a->DoneSignal = p_dl->DoneSignal;
	p_a->Positive = p_dl->Positive;
	p_a->Terminate = p_dl->Terminate;
	p_a->HighDrive = p_dl->HighDrive;
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		if (p_dl->FireFirst < 0.0)
			return 3;
		result = DelayNumbers(&Remainder, &IntDelay, p_dl->FireFirst, DG_Number);
		if (result != 0)
			return result;
		p_a->Analog = RoundInt((Remainder * 40960.0));
		p_a->Analog = min(p_a->Analog, 4095);
		switch (DG_Product)
		{
		case BME_G03V1:
		case BME_G03V2:
			if ((p_dl->SetBack > MaxBME_G0XRange) || (p_dl->FireFirst > MaxBME_G0XRange))
				return 5;
			if (p_dl->FireFirst >= 0.0)
			{
				if (p_dl->SetBack > p_dl->FireFirst)
				{
					result = T0Numbers(&IntNumber, (p_dl->SetBack - p_Present->ResetTime), DG_Number);
					if (result != 0)
						return result;
					p_a->DigOff = MainCounter - IntNumber;
				}
				else
					p_a->DigOff = MainCounter + 1;
				p_a->Digital = MainCounter - IntDelay;
			}
			else
			{
				p_a->Digital = MainCounter + 1;
				p_a->DigOff = MainCounter + 1;
				return 3;
			}
			break;
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_dl->SetBack > MaxBME_G0XRange)
				return 5;
			if (p_dl->FireFirst >= 0.0)
			{
				if (p_dl->SetBack > p_dl->FireFirst)
				{
					result = T0Numbers(&IntNumber, (p_dl->SetBack - p_Present->ResetTime), DG_Number);
					if (result != 0)
						return result;
					p_a->DigOff = IntNumber;
				}
			}
		case BME_G02V1:
		case BME_G02V2:
		case BME_G02V3:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_SG02V3:
		case BME_SG02V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_dl->FireFirst > MaxBME_G0XRange)
				return 5;
			p_a->Digital = IntDelay;
			break;
		default:
			p_a->Digital = IntDelay;
		}
		switch (DG_Product)
		{
		case BME_G05P2:
		case BME_G05P3:
			p_a->ModOffset = (unsigned short)(p_dl->OutputOffset & 0xFFFF);
			p_a->ModOffset = max(0, (p_a->ModOffset + 1));
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
			p_a->ModCounter = (unsigned short)(p_dl->OutputModulo & 0xFFFF);
			p_a->ModCounter = max(1, p_a->ModCounter);
			break;
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			p_a->ModCounter = (unsigned short)(p_dl->OutputModulo & 0xFFFF);
			p_a->ModCounter = max(0, (p_a->ModCounter - 1));
			p_a->ModOffset = (unsigned short)(p_dl->OutputOffset & 0xFFFF);
			break;
		default:
			break;
		}
	}
	return 0;
}

long SetChannel_SG05P4(DelayChannel* p_a, DelayChannelData* p_dl, long DG_Number)
{
	double Remainder;
	unsigned int IntDelay;
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	Register32	tvl;
	long result;
	int i1;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	p_a->GoSignal = p_dl->GoSignal;
	p_a->DoneSignal = 0x0;
	p_a->Positive = p_dl->Positive;
	p_a->Terminate = p_dl->Terminate;
	p_a->Disconnect = p_dl->Disconnect;
	p_a->OntoMsBus = p_dl->OntoMsBus;
	p_a->InputPositive = p_dl->InputPositive;
	p_a->HighDrive = FALSE;
	p_a->ListLength = p_dl->ListLength;
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		for (i1 = 0; i1 < p_a->ListLength; i1++)
		{
			if (p_dl->DelayTime[i1] < 0.0)
				return 3;
			result = DelayNumbers(&Remainder, &IntDelay, p_dl->DelayTime[i1], DG_Number);
			if (result != 0)
				return result;
			tvl.LowWord = RoundInt((Remainder * 40960.0));
			tvl.LowWord = min(tvl.LowWord, 4095);
			tvl.HighWord = (unsigned short)((min((unsigned)(p_a->ListLength - 1), p_dl->StepBack[i1])) & 0x1FF);
			p_a->DacList[i1] = (unsigned long)tvl.Value;
			p_a->DelayList[i1] = IntDelay;
			result = WidthNumber(&(p_a->PulseWidth[i1]), p_dl->PulseWidth[i1], DG_Number);
			if (result != 0)
				return result;
		}
		p_a->OutputModulo = p_dl->OutputModulo;
		p_a->OutputModulo = max(0, p_a->OutputModulo - 1);
		p_a->OutputOffset = p_dl->OutputOffset;
	}
	/*
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		if (p_dl->DelayTime[0] < 0.0)
			return 3;
		result = DelayNumbers(&Remainder, &IntDelay, p_dl->DelayTime[0], DG_Number);
		if (result != 0)
			return result;
		tvl.LowWord = RoundInt((Remainder * 40960.0));
		tvl.LowWord = min(tvl.LowWord, 4095);
		tvl.HighWord = (unsigned short)(p_dl->StepBack[0] & 0x1FF);
		p_a->DacList[0] = (unsigned long)tvl.Value;
		p_a->DelayList[0] = IntDelay;
		result = WidthNumber(&(p_a->PulseWidth[0]), p_dl->PulseWidth[0], DG_Number);
		if (result != 0)
			return result;
		if (p_a->ListLength > 1)
		{
			tvl.Value = p_a->DacList[0];
			tvl.HighWord = (unsigned short)((p_dl->StepBack[0] + 4) & 0x1FF);
			p_a->DacList[0] = (unsigned long)tvl.Value;
			for (i1 = 1; i1 < 5; i1++)
			{
				p_a->DelayList[i1] = p_a->DelayList[0];
				p_a->PulseWidth[i1] = p_a->PulseWidth[0];
				tvl.Value = p_a->DacList[0];
				tvl.HighWord = (unsigned short)((p_dl->StepBack[0] + 4) & 0x1FF);
				p_a->DacList[i1] = (unsigned long)tvl.Value;
			}
			for (i1 = 1; i1 < p_a->ListLength; i1++)
			{
				if (p_dl->DelayTime[i1] < 0.0)
					return 3;
				result = DelayNumbers(&Remainder, &IntDelay, p_dl->DelayTime[i1], DG_Number);
				if (result != 0)
					return result;
				tvl.LowWord = RoundInt((Remainder * 40960.0));
				tvl.LowWord = min(tvl.LowWord, 4095);
				tvl.HighWord = (unsigned short)((p_dl->StepBack[i1] + 4) & 0x1FF);
				p_a->DacList[i1 + 4] = (unsigned long)tvl.Value;
				p_a->DelayList[i1 + 4] = IntDelay;
				result = WidthNumber(&(p_a->PulseWidth[i1 + 4]), p_dl->PulseWidth[i1], DG_Number);
				if (result != 0)
					return result;
			}
			p_a->ListLength += 4;
		}
		p_a->OutputModulo = p_dl->OutputModulo;
		p_a->OutputModulo = max(0, p_a->OutputModulo - 1);
		p_a->OutputOffset = p_dl->OutputOffset;
	}
	*/
	return 0;
}

long WidthNumber(unsigned long* p_out, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double Increment;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	Increment = p_Present->TimeIncrement;
	if (InValue < (Increment * 0.75))
		*p_out = 0;
	else
		*p_out = (unsigned long)RoundInt(InValue / Increment);
	return 0;
}

long DelayNumbers(double* p_remainder, unsigned int* p_digital, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value,Delta,Increment;
	double ZeroTime,p1Time,p2Time;
	unsigned int IntVal;
	int DacMax,DacSteps,DacSwitch;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	*p_remainder = 0.0;
	*p_digital = 0;
	p_Present = (p_Internal + DG_Number);
	if (InValue >= 0.0)
	{
		Increment = p_Present->TimeIncrement;
		if (p_Present->CalibrationLevel == CalibrateOffset)
		{
			ZeroTime = p_Present->ZeroTime;
			p1Time = p_Present->p1Time;
			p2Time = p_Present->p2Time;
		}
		else
		{
			ZeroTime = 0.0;
			p1Time = Increment;
			p2Time = 2.0 * Increment;
		}
		DacSteps = (RoundInt((4096.0 * Increment / 0.1)) - 1);
		DacMax = min( 4095, DacSteps);
		DacSwitch = (DacMax + DacSteps) / 2;
		Delta = 0.1 * ((double)DacMax) / 4096.0;
		if (((p_Present->DG_Product == BME_SG08P1) || (p_Present->DG_Product == BME_SG08P2)) && ((InValue - ZeroTime) <= 0.035))
			*p_remainder = max(0.0, (InValue - ZeroTime));
		else
		{
			if (InValue >= p2Time)
			{
				value = (InValue - p2Time) / Increment;
				IntVal = (unsigned int)value;
				while (RoundInt(((double)(DacSteps + 1) * (value - (double)IntVal))) > DacSwitch)
					IntVal++;
				*p_remainder = max(0.0, (Increment * (value - (double)IntVal)));
				*p_digital = IntVal + 2;
			}
			else
			{
				Delta = 0.1 * 4095.0 / 4096.0;
				switch (p_Present->DG_Product)
				{
				case BME_G02V1:
				case BME_G03V1:
				case BME_SG02V1:
					*p_remainder = max(0.0, min(Delta, (InValue - p1Time)));
					*p_digital = 1;
					break;
				default:
					if (InValue <= (ZeroTime + Delta))
						*p_remainder = max(0.0, (InValue - ZeroTime));
					else
					{
						if (InValue >= p1Time)
						{
							if ((p2Time - InValue) < (InValue - (p1Time + Delta)))
								*p_digital = 2;
							else
							{
								*p_remainder = InValue - p1Time;
								*p_digital = 1;
							}
						}
						else
						{
							if ((p1Time - InValue) < (InValue - (ZeroTime + Delta)))
								*p_digital = 1;
							else
								*p_remainder = Delta;
						}
					}
				}
			}
		}
	}
	else
		*p_digital = 0xFFFFFFFF;
	return 0;
}

long T0Numbers(unsigned int* p_digital, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value,TestValue,Increment;
	unsigned int IntVal;
	int i1,ipos;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	*p_digital = 0;
	if (InValue >= 0.0)
	{
		Increment = p_Present->TimeIncrement;
		if (InValue >= p_Present->p2Time)
		{
			value = InValue - p_Present->p2Time;
			IntVal = RoundInt(value / Increment);
			*p_digital = IntVal + 2;
			return 0;
		}
		else
		{
			ipos = 0;
			value = fabs(InValue - p_Present->ZeroTime);
			for (i1 = 1; i1 < 3; i1++)
			{
				TestValue = fabs(InValue - p_Present->IniTime[i1]);
				if (TestValue < value)
				{
					value = TestValue;
					ipos = i1;
				}
			}
			switch (p_Present->DG_Product)
			{
			case BME_G02V1:
			case BME_G03V1:
			case BME_SG02V1:
				ipos = max(1, ipos);
			default:
				*p_digital = (unsigned int)ipos;
			}
			return 0;
		}
	}
	else
		*p_digital = 0xFFFFFFFF;
	return 0;
}
