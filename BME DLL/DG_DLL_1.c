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
#include "..\BME_G0x\PlxRout.h"


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
		(p_Internal + i1)->h_DelayGenerator = NULL;
		(p_Internal + i1)->SlotNumber = -1;
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
			if (p_Present->h_DelayGenerator != NULL)
			{
		    rc = PlxPciDeviceClose(p_Present->h_DelayGenerator);
				p_Present->h_DelayGenerator = NULL;
				p_Present->SlotNumber = -1;
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
#if (!defined(server) && !defined(D0xConsole))
	RETURN_CODE			rc;
	DEVICE_LOCATION Device;
#endif
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
#if (!defined(server) && !defined(D0xConsole))
		p_Present->base_address = 0x0;
		p_Present->SlotNumber = base;
		p_Present->BusNumber = BusNumber;
		InitializeInternalData(p_Present);
		Device.BusNumber = (U32)BusNumber;
		Device.SlotNumber = (U32)base;
		Device.VendorId = (U32)PlxVendorID;
		Device.DeviceId = (U32)PlxDeviceID;
		Device.SerialNumber[0] = '\0';
		rc = PlxPciDeviceOpen(&Device, &(p_Present->h_DelayGenerator));
		if (rc != ApiSuccess)
			return (long)rc;
#endif
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
	if (DG_Product == SRS_DG135)
		p_Present->CommandRegister = 0x00;
	else
		p_Present->CommandRegister = 0x20;
	p_Present->CommandRegisterState = 0xFFFF;
	LoadCommandRegister(p_Present->CommandRegister, p_Present);
	if (DG_Product == SRS_DG135)
	{
		cntrl = 0x30;
		value = 0x01;
		adr1 = p_Present->Counter;
		for (i = 0; i <= 2; i++)
		{
			DataOut(p_Present->Counter_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
			DataOut(adr1, &value, p_Present->h_DelayGenerator, 2);
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
		return 0;
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

#define CurrentParameterFileVersion					2

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
	Error = FALSE;
	stream = fopen(FileName, "rb" );
	if (stream != NULL)
	{
		fread(&(nVersion), sizeof(int), 1, stream);
		fread(&(NoDelayGenerators), sizeof(int), 1, stream);
		fread(p_CalibrationLevel, sizeof(int), 1, stream);
		fread(p_CalibrateTiming, sizeof(BOOL), 1, stream);
		fread(p_DGS, sizeof(DG_BME_State), NoDelayGenerators, stream);
		fclose(stream);
		for (i1 = 0; i1 < NoDelayGenerators; i1++)
		{
			if ((p_DGS + i1)->Master)
				*(p_module + i1) = MasterModule;
			else
				*(p_module + i1) = SlaveModule;
			if (nVersion < 2)
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
		
		if (p_Present->b_ModuleCalibrated)
		{
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Master->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / p_Master->ExternalOscillatorFrequency;
			if (p_Present == p_Master)
				SlaveIncrement = MasterIncrement;
			else
			{
				p_ST = &(p_Present->DelayControlState.DT);
				if (p_ST->ClockSource == MasterSlaveBus)
					SlaveIncrement = ((double)p_ST->OscillatorDivider) * MasterIncrement;
				else
				{
					if (p_ST->ClockSource == CrystalOscillator)
						SlaveIncrement = ((double)p_ST->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
					else
						SlaveIncrement = ((double)p_ST->TriggerDivider) / p_Present->ExternalOscillatorFrequency;
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
		}
		else
		{
			//p_Present->InternalOscillatorFrequency = CalData.InternalOscillator;
			//p_Present->ExternalOscillatorFrequency = CalData.ExternalOscillator;
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / p_Present->ExternalOscillatorFrequency;
			p_Present->TimeIncrement = MasterIncrement;
			p_Present->TriggerIncrement = MasterIncrement;
			p_Present->T0_Increment = MasterIncrement;
			p_Present->A_Increment = MasterIncrement;
			p_Present->B_Increment = MasterIncrement;
		}
		break;
	default:
		if (p_Present->b_ModuleCalibrated)
		{
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Master->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / p_Master->ExternalOscillatorFrequency;
		}
		else
		{
			//p_Present->InternalOscillatorFrequency = CalData.InternalOscillator;
			//p_Present->ExternalOscillatorFrequency = CalData.ExternalOscillator;
			if (p_DT->ClockSource == CrystalOscillator)
				MasterIncrement = ((double)p_DT->OscillatorDivider) / p_Present->InternalOscillatorFrequency;
			else
				MasterIncrement = ((double)p_DT->TriggerDivider) / p_Present->ExternalOscillatorFrequency;
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
	case BME_G04:
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
	p_Present->T0_Increment = 0.1;
	p_Present->A_Increment = 0.1;
	p_Present->B_Increment = 0.1;
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
						p_Present->TenMhzZeroTime = CalData.SG02_ZeroTime + CalData.TriggerDelay;
					case BME_G02V1:
					case BME_SG02V1:
						p_Present->TenMhzp1Time = CalData.SG02_p1Time;
						p_Present->TenMhzp2Time = CalData.SG02_p2Time;
						break;
					case BME_G03V2:
					case BME_G04:
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
					case BME_G04:
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
						p_Present->TenMhzZeroTime = CalData.SG02V1_GoTime + CalData.TriggerDelay;
					case BME_G02V1:
					case BME_SG02V1:
						p_Present->TenMhzp1Time = CalData.SG02V1_p1Time + CalData.ClockDelay;
						p_Present->TenMhzp2Time = CalData.SG02V1_p2Time + CalData.ClockDelay;
						break;
					case BME_G03V2:
					case BME_G04:
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
				case BME_G04:
					fprintf(stream, "BME_G04       ");
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
				case BME_G04:
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
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
				case BME_G04:
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
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	if (p_pdg->DG_Product != DG_Product)
		return 1;
	//if (DG_Product == BME_G02V3)
		//printf("CDG_DLL::Set_DG_BME \n");
	ModifyControlRegister(p_pdg, p_Present);
	PrepareCounterControl(p_pdg, p_Present);
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
		if (!IsEqualPS(p_pdg, &(p_Present->DelayGeneratorState), DG_Product))
			Set_Prescaler(p_pdg, p_Present);
		break;
	default:
		break;
	}
	switch (DG_Product)
	{
	case BME_G02V1:
	case BME_G02V2:
	case BME_G02V3:
	case BME_G04:
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
			Set_Delay_Trigger(&(p_pdg->DT), p_Present);
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
	return 0;
}

_declspec (dllexport) long CC SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	double MainCounterTime,Increment;
	long result;
	int t_count,ZeroShift;
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
	Increment = p_Present->TriggerIncrement;

	dgr.DG_Product = p_BDG->DG_Product;
	dgr.Gate_AB = p_BDG->Gate_AB;
	dgr.GateFunction = p_BDG->GateFunction;
	dgr.OutputLevel = p_BDG->OutputLevel;
	if ((dgr.OutputLevel < TTL_VoltageLevel) || (ECL_VoltageLevel < dgr.OutputLevel))
		return 6;
	dgr.PulseWidth = p_BDG->PulseWidth;

	dgr.DT.MS_Bus = p_BDG->DT.MS_Bus;
	dgr.DT.RisingEdge = p_BDG->DT.RisingEdge;
	dgr.DT.TriggerEnable = p_BDG->DT.TriggerEnable;
	dgr.DT.InternalTrigger = p_BDG->DT.InternalTrigger;
	dgr.DT.InternalArm = p_BDG->DT.InternalArm;
	dgr.DT.SoftwareTrigger = p_BDG->DT.SoftwareTrigger;
	dgr.DT.StopOnPreset = p_BDG->DT.StopOnPreset;
	dgr.DT.ResetWhenDone = p_BDG->DT.ResetWhenDone;
	dgr.DT.PresetValue = p_BDG->DT.PresetValue;

	dgr.DT.GateDivider = p_BDG->DT.GateDivider;
	dgr.DT.PositiveGate = p_BDG->DT.PositiveGate;
	dgr.DT.IgnoreGate = p_BDG->DT.IgnoreGate;
	dgr.DT.OscillatorDivider = p_BDG->DT.OscillatorDivider;
	dgr.DT.TriggerDivider = p_BDG->DT.TriggerDivider;
	dgr.DT.ClockEnable = p_BDG->DT.ClockEnable;
	dgr.DT.ClockSource = p_BDG->DT.ClockSource;
	if ((dgr.DT.ClockSource < CrystalOscillator) || (MasterSlaveBus < dgr.DT.ClockSource))
		return 7;
	dgr.DT.Terminate = p_BDG->DT.Terminate;
	
	dgr.DT.TriggerLevel = RoundInt(((p_BDG->DT.TriggerLevel + 2.5) * 4096.0 / 5.0));
	dgr.DT.TriggerLevel = max(0, min(4095, dgr.DT.TriggerLevel));

	t_count = 0;
	if (dgr.DT.InternalTrigger)
		t_count++;
	if (dgr.DT.InternalArm)
		t_count++;
	if (dgr.DT.SoftwareTrigger)
		t_count++;
	if (t_count > 1)
		return 4;

	ZeroShift = 3;
	if ((dgr.DT.ClockSource == CrystalOscillator) || (dgr.DT.ClockSource == MasterSlaveBus))
	{
		if (dgr.DT.OscillatorDivider >= 2)
		ZeroShift = 2;
	}
	if ((dgr.DT.ClockSource == TriggerInput) || (dgr.DT.ClockSource == TriggerAndOscillator))
	{
		if (dgr.DT.TriggerDivider >= 2)
		ZeroShift = 2;
	}
	switch (dgr.DG_Product)
	{
		case BME_SG05P2:
		case BME_SG05P3:
			if ((p_BDG->DT.SynchronizeGate) && (p_Present->ExternalOscillatorFrequency > 75.0))
				dgr.DT.SynchronizeGate = TRUE;
		case BME_SG05P1:
			if ((p_BDG->DT.SynchronizeGate) && (Increment <= 0.0135))
				dgr.DT.SynchronizeGate = TRUE;
		case BME_SG02P3:
			dgr.DT.ForceTrigger = max(0, (RoundInt((p_BDG->DT.ForceTrigger / Increment)) - ZeroShift));
		case BME_G05P2:
		case BME_G05P3:
			dgr.DT.InhibitTrigger = max(0, (RoundInt((p_BDG->DT.InhibitTrigger / Increment)) - ZeroShift));
			break;
		default:
			if ((dgr.DT.InternalTrigger) || (dgr.DT.InternalArm))
				dgr.DT.RepCounter = max(0, (RoundInt((p_BDG->DT.InternalClock / Increment)) - 2));
			else
				dgr.DT.RepCounter = 0x3FFFFFFF;
			break;
	}
	switch (dgr.DG_Product)
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
			break;
		default:
			dgr.DT.RepCounter = max(1, dgr.DT.RepCounter);
			break;
	}

	MainCounterTime = -1.0;
	switch (dgr.DG_Product)
	{
		case BME_G04:
			if ((p_BDG->T0.GoSignal & 0x77) != 0x0)
				MainCounterTime =  max(MainCounterTime, p_BDG->T0.FireSecond);
			if ((p_BDG->A.GoSignal & 0x77) != 0x0)
				MainCounterTime =  max(MainCounterTime, p_BDG->A.FireSecond);
			if ((p_BDG->B.GoSignal & 0x77) != 0x0)
				MainCounterTime =  max(MainCounterTime, p_BDG->B.FireSecond);
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
				dgr.MC.Active = TRUE;
				dgr.MC.Digital = RoundInt((MainCounterTime / Increment));
				dgr.MC.Int3 = dgr.MC.Digital + 1;
			}
			break;
		default:
			break;
	}
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

_declspec (dllexport) long CC RoundFireSecond(double* p_out, double InValue, double FireFirst, long DG_Number)
{
	double value,Remainder;
	unsigned int Digital;
	long result;
	result = DelayNumbers(&Remainder, &Digital, FireFirst, DG_Number);
	if (result  != 0)
		return result;
	value = InValue - Remainder;
	RoundT0(p_out, value, DG_Number);
	*p_out += Remainder;
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

_declspec (dllexport) long CC Set_BME_G06(double FireFirst_T0, double SetBack_T0, unsigned long OutputModulo_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A, unsigned long OutputModulo_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B, unsigned long OutputModulo_B,
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
	result = Set_G06_Delay(DelayChannel_T0, FireFirst_T0, SetBack_T0, OutputModulo_T0,
								Active_T0, Positive_T0, Terminate_T0, HighDrive_T0, DG_Number);
	if (result != 0)
		return result;
	result = Set_G06_Delay(DelayChannel_A, FireFirst_A, SetBack_A, OutputModulo_A,
								Active_A, Positive_A, Terminate_A, HighDrive_A, DG_Number);
	if (result != 0)
		return result;
	result = Set_G06_Delay(DelayChannel_B, FireFirst_B, SetBack_B, OutputModulo_B,
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

_declspec (dllexport) long CC Set_BME_G04(double FireFirst_T0, double SetBack_T0,  double FireSecond_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A,  double FireSecond_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B,  double FireSecond_B,
													BOOL Active_B, BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
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
	result = Set_G04_Delay(DelayChannel_T0, FireFirst_T0, SetBack_T0, FireSecond_T0,
								Active_T0, Positive_T0, Terminate_T0, HighDrive_T0, DG_Number);
	if (result != 0)
		return result;
	result = Set_G04_Delay(DelayChannel_A, FireFirst_A, SetBack_A, FireSecond_A,
								Active_A, Positive_A, Terminate_A, HighDrive_A, DG_Number);
	if (result != 0)
		return result;
	result = Set_G04_Delay(DelayChannel_B, FireFirst_B, SetBack_B, FireSecond_B,
								Active_B, Positive_B, Terminate_B, HighDrive_B, DG_Number);
	if (result != 0)
		return result;
	result = Set_Gate_AB(Gate_AB, DG_Number);
	if (result != 0)
		return result;
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

_declspec (dllexport) long CC Set_G04_Delay(unsigned long Channel, 
													double FireFirst, double SetBack, double FireSecond,
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
	p_ch->FireSecond = FireSecond;
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
	}

	p_ch->GoSignal = GoSignal;
	p_ch->DoneSignal = DoneSignal;
	
	p_modulo = (unsigned short*)&OutputModulo;
	p_ch->OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	p_ch->OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);

	p_ch->FireFirst = FireFirst;
	p_ch->Positive = Positive;
	p_ch->Terminate = Terminate;
	p_ch->HighDrive = HighDrive;
	result = SetDelayGenerator(&dgc, DG_Number);
	if (result != 0)
		return result;
	return 0;
}

_declspec (dllexport) long CC Set_G06_Delay(unsigned long Channel, 
													double FireFirst, double SetBack, unsigned long OutputModulo,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number)
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
	}

	if (Active)
	{
		p_ch->GoSignal |= MasterPrimary;
		p_ch->DoneSignal &= ~MasterPrimary;
	}
	else
	{
		p_ch->GoSignal &= 0x388;
		p_ch->DoneSignal = 0x0;
	}
	
	p_modulo = (unsigned short*)&OutputModulo;
	p_ch->OutputModulo = ((unsigned long)*p_modulo & 0xFFFF);
	p_ch->OutputOffset = ((unsigned long)*(p_modulo + 1) & 0xFFFF);

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

_declspec (dllexport) long CC Test_BME_G04(long DG_Number)
{
	double FireFirst_T0 = 3.0;
	double SetBack_T0 = 8.0;
	double FireSecond_T0 = 12.0;
	BOOL Active_T0 = TRUE;
	BOOL Positive_T0 = FALSE;
	BOOL Terminate_T0 = FALSE;
	BOOL HighDrive_T0 = FALSE;

	double FireFirst_A = 10.0;
	double SetBack_A = 15.0;
	double FireSecond_A = 19.0;
	BOOL Active_A = TRUE;
	BOOL Positive_A = TRUE;
	BOOL Terminate_A = FALSE;
	BOOL HighDrive_A = FALSE;

	double FireFirst_B = 11.0;
	double SetBack_B = 16.0;
	double FireSecond_B = 20.0;
	BOOL Active_B = TRUE;
	BOOL Positive_B = TRUE;
	BOOL Terminate_B = FALSE;
	BOOL HighDrive_B = FALSE;

	unsigned long OutputLevel = TTL_VoltageLevel;
	BOOL Gate_AB = FALSE;

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
	result = Set_BME_G04(FireFirst_T0, SetBack_T0, FireSecond_T0, 
													Active_T0, Positive_T0, Terminate_T0, HighDrive_T0,
													FireFirst_A, SetBack_A, FireSecond_A, 
													Active_A, Positive_A, Terminate_A, HighDrive_A,
													FireFirst_B, SetBack_B, FireSecond_B, 
													Active_B, Positive_B, Terminate_B, HighDrive_B,
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

_declspec (dllexport) long CC ResetControl(DG_BME_Control* p_DGControl)
{
	p_DGControl->PulseWidth = 8;
	p_DGControl->Gate_AB = FALSE;
	p_DGControl->OutputLevel = TTL_VoltageLevel;
	p_DGControl->DG_Product = -1;
	p_DGControl->GateFunction = GateXOR;
	ResetDelayControl(&(p_DGControl->T0));
	ResetDelayControl(&(p_DGControl->A));
	ResetDelayControl(&(p_DGControl->B));
	ResetTriggerControl(&(p_DGControl->DT));
	return 0;
}

_declspec (dllexport) long CC ResetRegisters(DG_BME_Registers* p_DGState)
{
	p_DGState->PulseWidth = 8;
	p_DGState->Gate_AB = FALSE;
	p_DGState->OutputLevel = TTL_VoltageLevel;
	p_DGState->DG_Product = -1;
	p_DGState->GateFunction = GateXOR;
	ResetDelayChannel(&(p_DGState->T0));
	ResetDelayChannel(&(p_DGState->A));
	ResetDelayChannel(&(p_DGState->B));
	ResetMainCounter(&(p_DGState->MC));
	ResetDelayTrigger(&(p_DGState->DT));
	return 0;
}

_declspec (dllexport) long CC CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V1* p_Control_V1)
{
	ResetControl(p_Control);
	CopyTriggerControl_V1(&(p_Control->DT), &(p_Control_V1->DT));
	CopyDelayControl(&(p_Control->T0), &(p_Control_V1->T0));
	CopyDelayControl(&(p_Control->A), &(p_Control_V1->A));
	CopyDelayControl(&(p_Control->B), &(p_Control_V1->B));
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
	CopyDelayControl(&(p_Control->T0), &(p_Control_V2->T0));
	CopyDelayControl(&(p_Control->A), &(p_Control_V2->A));
	CopyDelayControl(&(p_Control->B), &(p_Control_V2->B));
	p_Control->Gate_AB = p_Control_V2->Gate_AB;
	if (p_Control->Gate_AB)
		p_Control->GateFunction = GateXOR;
	p_Control->OutputLevel = p_Control_V2->OutputLevel;
	p_Control->DG_Product = p_Control_V2->DG_Product;
	p_Control->PulseWidth = p_Control_V2->PulseWidth;
	return 0;
}

_declspec (dllexport) long CC Deactivate_DG_BME(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned char cntrl;
	unsigned long DG_Product;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	cntrl = p_Present->CommandRegister & 0x3E2B;
	if ((DG_Product == BME_DP01) || (DG_Product == SRS_DG135))
		cntrl &= 0x20;
	LoadCommandRegister(cntrl, p_Present);
	p_Present->b_DG_Activated = FALSE;
	return 0;
}

_declspec (dllexport) long CC Activate_DG_BME(long DG_Number)
{
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
	case BME_G04:
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
		LoadCounterControl(p_Present->CounterControlRegister, p_Present);
	default:
		LoadCommandRegister(p_Present->CommandRegister, p_Present);
	}
	p_Present->b_DG_Activated = TRUE;
	return 0;
}

_declspec (dllexport) long CC SoftwareTrigger_DG_BME(long DG_Number)
{
	unsigned char cntrl;
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
	case BME_G04:
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
		cntrl = p_Present->CommandRegister & 0x3EFE;
		LoadCommandRegister(cntrl, p_Present);
		cntrl = p_Present->CommandRegister | 0x01;
		LoadCommandRegister(cntrl, p_Present);
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
	DataOut(p_Present->InitializeAddress, &Value, p_Present->h_DelayGenerator, -1);
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
	DataOut(p_Present->InitializeAddress, &Value, p_Present->h_DelayGenerator, -1);
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
				DataOut(p_Present->InitializeAddress, &Value, p_Present->h_DelayGenerator, -1);
				break;
			default:
				break;
		}
	}
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
			DataIn(p_Present->CommandAddress, &result, p_Present->h_DelayGenerator, -1);
			if ((result & 0x10) != 0)
				return 0xFFFFFFFF;
			DataIn(p_Present->ModuloCounterAddress, &result, p_Present->h_DelayGenerator, 4);
			break;
		case BME_G02V2:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_G03V1:
			DataIn(p_Present->CommandAddress, &result, p_Present->h_DelayGenerator, -1);
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
		case BME_G04:
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			DataIn(p_Present->TriggerCounterAddress, &result, p_Present->h_DelayGenerator, 4);
			break;
		default:
			break;
	}
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) long CC EnableInterrupts(unsigned long value, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short IntCntrl = (unsigned short) value;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DataOut(p_Present->InterruptEnableAddress, &IntCntrl, p_Present->h_DelayGenerator, -1);
	return 0;
}

_declspec (dllexport) unsigned long CC Read_DG_Status(long DG_Number)
{
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	DataIn(p_Present->CommandAddress, &result, p_Present->h_DelayGenerator, -1);
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) unsigned long CC ReadCounterControlRegister(long DG_Number)
{
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	DataIn(p_Present->CounterControlAddress, &result, p_Present->h_DelayGenerator, -1);
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) unsigned long CC ReadInterruptStatus(long DG_Number)
{
	DG_InternalData* p_Present = (p_Internal + DG_Number);
	unsigned long result = 0;
	DataIn(p_Present->InterruptEnableAddress, &result, p_Present->h_DelayGenerator, -1);
	//printf("result: %d\n", result);
	return result;
}

_declspec (dllexport) long CC AcknowledgeInterrupts(unsigned long value, long DG_Number)
{
	unsigned short IntCntrl = (unsigned short) value;
	DG_InternalData* p_Present;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	DataOut(p_Present->InterruptAcknowledgeAddress, &IntCntrl, p_Present->h_DelayGenerator, -1);
	return 0;
}

_declspec (dllexport) long CC LoadOutputState(long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned short cntrl;
	if ((DG_Number < 0) || (NoDelayGenerators <= DG_Number))
		return 2;
	p_Present = (p_Internal + DG_Number);
	cntrl = p_Present->CommandRegisterState;
	if ((cntrl & 0x80) == 0)
	{
		cntrl |= 0x80;
		DataOut(p_Present->CommandAddress, &cntrl, p_Present->h_DelayGenerator, -1);
		cntrl &= 0x3E7F;
		DataOut(p_Present->CommandAddress, &cntrl, p_Present->h_DelayGenerator, -1);
	}
	else
	{
		cntrl &= 0x3E7F;
		DataOut(p_Present->CommandAddress, &cntrl, p_Present->h_DelayGenerator, -1);
		cntrl |= 0x80;
		DataOut(p_Present->CommandAddress, &cntrl, p_Present->h_DelayGenerator, -1);
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

_declspec (dllexport) unsigned long CC ModifyAction(DG_BME_Control* p_BDG, long DG_Number)
{
	DG_InternalData* p_Present;
	unsigned long DG_Product;
	unsigned long Action = 0x0;
	p_Present = (p_Internal + DG_Number);
	DG_Product = p_Present->DG_Product;
	if (p_BDG->OutputLevel != p_Present->DelayControlState.OutputLevel)
		Action |= 0x1;
	ActionDT(&Action, &(p_BDG->DT), &(p_Present->DelayControlState.DT));
	ActionDC(&Action, &(p_BDG->T0), &(p_Present->DelayControlState.T0), DG_Product);
	ActionDC(&Action, &(p_BDG->A), &(p_Present->DelayControlState.A), DG_Product);
	ActionDC(&Action, &(p_BDG->B), &(p_Present->DelayControlState.B), DG_Product);
	return Action;
}

#if (!defined(server) && !defined(D0xConsole))

_declspec (dllexport) long CC GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number)
{
	long BusNumber;
	return GetUnconnectedBusDelayGenerator(p_DG_Product, &BusNumber, p_SlotNumber, p_LineMaster, DG_Number);
}

_declspec (dllexport) long CC GetUnconnectedBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																							long* p_LineMaster, long DG_Number)
{
	int LineNo;
	if ((DG_Number >= NumberPciDelayGenerators) || (DG_Number < 0))
		return 2;
	if (PciDelgen[DG_Number].Selected)
		return 1;
	*p_DG_Product = PciDelgen[DG_Number].DG_Product;
	*p_BusNumber = PciDelgen[DG_Number].BusNumber;
	*p_SlotNumber = PciDelgen[DG_Number].SlotNumber;
	for (LineNo = 0; LineNo < 3; LineNo++)
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
	if ((DG_Number >= NumberPciDelayGenerators) || (DG_Number < 0))
		return 2;
	*p_DG_Product = PciDelgen[DG_Number].DG_Product;
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

_declspec (dllexport) long CC DetectPciDelayGenerators(long* p_Error)
{
	long							NoDelgen,NoPlxCards;
	U32								ReqLimit;
	Register32				Register,DG_ID;
  HANDLE						hDevice;
	RETURN_CODE				rc;
	DEVICE_LOCATION		Device;
	int								i1,k1,LineNo,Count,TestSlot,memk1;
	int								MasterCount,NumBytes;
	unsigned short		CommandWord;
	DelgenType				DelgenList[20];
	BOOL							found;
	NoDelgen = 0;
	Device.BusNumber = (U32)-1;
	Device.SlotNumber = (U32)-1;
	Device.VendorId = (U32)-1;
	Device.DeviceId = (U32)-1;
  Device.SerialNumber[0] = '\0';
	ReqLimit = FIND_AMOUNT_MATCHED;
	rc = PlxPciDeviceFind(&Device, &ReqLimit);
	if (rc != ApiSuccess)
	{
		if (p_Error != NULL)
			*p_Error = rc;
		return 0;
	}
	NoPlxCards = (long)ReqLimit;
	for (i1 = 0; i1 < NoPlxCards; i1++)
	{
		Device.BusNumber = (U32)-1;
		Device.SlotNumber = (U32)-1;
		Device.VendorId = (U32)-1;
		Device.DeviceId = (U32)-1;
		Device.SerialNumber[0] = '\0';
		ReqLimit = (U32)i1;
		rc = PlxPciDeviceFind(&Device, &ReqLimit);
		if ((Device.VendorId == PlxVendorID) && (Device.DeviceId == PlxDeviceID))
		{
			Register.Value = PlxPciConfigRegisterRead(Device.BusNumber, Device.SlotNumber, 
																					CFG_SUB_VENDOR_ID, &rc);
			if (rc != ApiSuccess)
			{
				if (p_Error != NULL)
					*p_Error = rc;
				return 0;
			}
			if ((Register.LowWord == SubSystemVendorID) && (Register.HighWord == SubSystemDeviceID))
			{
				rc = PlxPciDeviceOpen(&Device, &hDevice);
				if (rc != ApiSuccess)
				{
					if (p_Error != NULL)
						*p_Error = rc;
					return 0;
				}
				Register.Value = 0x0;
				//rc = PlxVpdWrite(hDevice, 0xc0, 0xffffffff);
				Register.Value = PlxVpdRead(hDevice, 0xc0, &rc);
				if (Register.Value == BME_ID)
				{
					DG_ID.Value = PlxVpdRead(hDevice, 0xc4, &rc);
					if (rc != ApiSuccess)
					{
						if (p_Error != NULL)
							*p_Error = rc;
						return 0;
					}
					ResetPciDelayGenerator(hDevice);
					CommandWord = 0x100;
					DataOut(0x00, &CommandWord, hDevice, -1);
					DelgenList[NoDelgen].DG_Product = (unsigned long)DG_ID.LowWord;
					DelgenList[NoDelgen].SlotNumber = (long)Device.SlotNumber;
					DelgenList[NoDelgen].BusNumber = (long)Device.BusNumber;
					DelgenList[NoDelgen].h_Delgen = hDevice;
					switch (DelgenList[NoDelgen].DG_Product)
					{
					case BME_G05P2:
					case BME_G05P3:
					case BME_SG05P1:
					case BME_SG05P2:
					case BME_SG05P3:
						NumBytes = 8;
						break;
					default:
						NumBytes = -1;
						break;
					}
					if (MasterDelayGenerator(hDevice, NumBytes, hDevice))
					{
						DelgenList[NoDelgen].Master = NoDelgen;
						for (LineNo = 0; LineNo < 4; LineNo++)
							DelgenList[NoDelgen].LineMaster[LineNo] = NoDelgen;
					}
					else
					{
						DelgenList[NoDelgen].Master = -1;
						for (LineNo = 0; LineNo < 4; LineNo++)
							DelgenList[NoDelgen].LineMaster[LineNo] = -1;
					}
					DelgenList[NoDelgen].OrderUpwards = TRUE;
					DelgenList[NoDelgen].Selected = FALSE;
					NoDelgen++;
				}
				else
				{
					rc = PlxPciDeviceClose(hDevice);
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
			switch (DelgenList[i1].DG_Product)
			{
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				NumBytes = 8;
				break;
			default:
				NumBytes = -1;
				break;
			}
			for (k1 = 0; k1 < NoDelgen; k1++)
			{
				if (i1 != k1)
				{
					if (MasterDelayGenerator(DelgenList[i1].h_Delgen, NumBytes, DelgenList[k1].h_Delgen))
					{
						DelgenList[k1].Master = i1;
						for (LineNo = 0; LineNo < 4; LineNo++)
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
			memcpy(&(PciDelgen[Count]), &(DelgenList[i1]), sizeof(DelgenType));
			PciDelgen[Count].Master = Count;
			for (LineNo = 0; LineNo < 4; LineNo++)
				PciDelgen[Count].LineMaster[LineNo] = Count;
			PciDelgen[Count].Selected = TRUE;
			MasterCount = Count;
			DelgenList[i1].Selected = TRUE;
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
					memcpy(&(PciDelgen[Count]), &(DelgenList[memk1]), sizeof(DelgenType));
					PciDelgen[Count].Master = MasterCount;
					PciDelgen[Count].Selected = TRUE;
					for (LineNo = 0; LineNo < 4; LineNo++)
						PciDelgen[Count].LineMaster[LineNo] = MasterCount;
					DelgenList[memk1].Selected = TRUE;
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
			memcpy(&(PciDelgen[Count]), &(DelgenList[i1]), sizeof(DelgenType));
			DelgenList[i1].Selected = TRUE;
			Count++;
			found = TRUE;
		}
	}
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		if (!PciDelgen[i1].Selected)
		{
			for (k1 = 0; k1 < NoDelgen; k1++)
			{
				switch (PciDelgen[k1].DG_Product)
				{
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
					NumBytes = 8;
					break;
				default:
					NumBytes = -1;
					break;
				}
				for (LineNo = 0; LineNo < 3; LineNo++)
				{
					if (MasterLineDG(PciDelgen[k1].h_Delgen, NumBytes, PciDelgen[i1].h_Delgen, LineNo))
						PciDelgen[i1].LineMaster[LineNo] = k1;
				}
			}
		}
	}
	for (i1 = 0; i1 < NoDelgen; i1++)
	{
		rc = PlxPciDeviceClose(DelgenList[i1].h_Delgen);
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
	NumberPciDelayGenerators = NoDelgen;
	return NoDelgen;
}
#endif

_declspec (dllexport) long CC DataOut(unsigned short Address, void* p_data, HANDLE h_Device, int Size)
{
	int i1,NoBytes;
	unsigned char* p_Value;
#if (!defined(server) && !defined(D0xConsole))
	int Count;
	U32 PciAddress;
	U16* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	if (h_Device != NULL)
	{
		PciAddress = (U32)Address;
		p_PciData = (U16*)p_data;
		if ((Address & 0xC0) == 0xC0)
		{
			Register.LowWord = 0x0;
			Register.HighWord = *p_PciData;
			rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			Count = Size - 2;
			while (Count > 0)
			{
				p_PciData++;
				Register.HighWord = *p_PciData;
				rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				Count -= 2;
			}
		}
		else
		{
			Register.HighWord = 0x0;
			Register.LowWord = *p_PciData;
			rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			Count = Size - 2;
			while (Count > 0)
			{
				p_PciData++;
				Register.LowWord = *p_PciData;
				rc = PlxBusIopWrite(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				Count -= 2;
			}
		}
	}
	else
#endif
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

_declspec (dllexport) long CC DataIn(unsigned short Address, void* p_data, HANDLE h_Device, int Size)
{
	int i1,NoBytes;
	unsigned char* p_Value;

#if (!defined(server) && !defined(D0xConsole))
	int Count;
	U32 PciAddress;
	U16* p_PciData;
	Register32			Register;
	RETURN_CODE			rc;
	if (h_Device != NULL)
	{
		PciAddress = (U32)Address;
		p_PciData = (U16*)p_data;
		if ((Address & 0xC0) == 0xC0)
		{
			Register.LowWord = 0x0;
			rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			*p_PciData = Register.HighWord;
			Count = Size - 2;
			while (Count > 0)
			{
				rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				p_PciData++;
				*p_PciData = Register.HighWord;
				Count -= 2;
			}
		}
		else
		{
			Register.HighWord = 0x0;
			rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
			*p_PciData = Register.LowWord;
			Count = Size - 2;
			while (Count > 0)
			{
				rc = PlxBusIopRead(h_Device, IopSpace0, PciAddress, FALSE, &(Register.Value), 4, BitSize32);
				p_PciData++;
				*p_PciData = Register.LowWord;
				Count -= 2;
			}
		}
	}
	else
#endif
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

_declspec (dllexport) long CC ResetPciDelayGenerator(HANDLE h_Delgen)
{
	unsigned short Value;
	Value = 0x3F;
	DataOut(0xA0, &Value, h_Delgen, -1);
	Value = 0xFF;
	DataOut(0x30, &Value, h_Delgen, -1);
	Value = 0x0;
	DataOut(0x20, &Value, h_Delgen, -1);
	Value = 0xFF;
	DataOut(0x30, &Value, h_Delgen, -1);
	Value = 0x0;
	DataOut(0x00, &Value, h_Delgen, -1);

	DataOut(0x10, &Value, h_Delgen, -1);
	DataOut(0x10, &Value, h_Delgen, -1);
	DataOut(0x10, &Value, h_Delgen, -1);
	DataOut(0x10, &Value, h_Delgen, -1);
	return 0;
}

BOOL MasterDelayGenerator(HANDLE h_Master, int NumBytes, HANDLE h_Slave)
{
	unsigned long Result;
	unsigned long Value[2];
	unsigned long i1 = 0;
	Result = 0x0;
	Value[1] = 0x0;
	while (i1 < 8)
	{
		Value[0] = i1;
		Value[0] <<= 8;
		DataOut(0x10, Value, h_Master, NumBytes);
		DataIn(0x10, &Result, h_Slave, -1);
		Result >>= 4;
		if ((Value[0] & 0x700) != (Result & 0x700))
			return FALSE;
		i1++;
	}
	return TRUE;
}

BOOL MasterLineDG(HANDLE h_Master, int NumBytes, HANDLE h_Slave, int LineNo)
{
	unsigned long Result,Mask;
	unsigned long Value[2];
	unsigned long i1 = 0;
	Mask = 0x100;
	Mask <<= LineNo;
	Result = 0x0;
	Value[1] = 0x0;
	for (i1 = 0; i1 < 3; i1++)
	{
		Value[0] = Mask;
		DataOut(0x10, Value, h_Master, NumBytes);
		DataIn(0x10, &Result, h_Slave, -1);
		Result >>= 4;
		if ((Value[0] & Mask) != (Result & Mask))
			return FALSE;
		Value[0] = ~Mask;
		Value[0] &= 0x700;
		DataOut(0x10, Value, h_Master, NumBytes);
		DataIn(0x10, &Result, h_Slave, -1);
		Result >>= 4;
		if ((Value[0] & Mask) != (Result & Mask))
			return FALSE;
	}
	return TRUE;
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
	case BME_G04:
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
	p_Present->T0_Increment = 0.1;
	p_Present->A_Increment = 0.1;
	p_Present->B_Increment = 0.1;
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
	unsigned long  PrescalerValue[2];
	unsigned long  CounterControlValue[2];
	unsigned short Value;
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
//		int i1;
//		while (TRUE)
//		{
//			for (i1 = 0 ; i1 < 0xFF; i1++)
//			{
//				Value = (unsigned short)i1;
//				DataOut(((Value & 0xFC) | 0x10), &Value, p_Present->h_DelayGenerator, -1);
//			}
//		}
		LoadCommandRegister(p_Present->CommandRegister, p_Present);
		CounterControlValue[0] = 0x0;
		CounterControlValue[1] = 0x0;
		p_Present->CounterControlState[0] = 0xFFFFFFFF;
		p_Present->CounterControlState[1] = 0xFFFFFFFF;
		LoadCounterControl(CounterControlValue, p_Present);
		Value = 0x3F;
		DataOut(p_Present->InitializeAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0x0;
		DataOut(p_Present->InterruptEnableAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, p_Present->h_DelayGenerator, -1);
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
		dgr.DT.SynchronizeGate = TRUE;
		dgr.DT.PositiveGate = FALSE;
		dgr.DT.OscillatorDivider = 32;
		dgr.DT.TriggerDivider = 32;
		dgr.DT.InhibitTrigger = 0xFFFFFFFF;
		dgr.DT.ForceTrigger = 0xFFFFFFFF;
		dgr.DT.IgnoreGate = TRUE;
		dgr.DT.PresetValue = 0xFFFFFFFF;
		dgr.DT.TriggerDAC = 0xFFF;
		dgr.OutputLevel = ECL_VoltageLevel;
		dgr.PulseWidth = 255;

		dgr.MC.Active = TRUE;
		dgr.MC.Digital = 0xFFFFFFF0;

		dgr.T0.GoSignal = 0x3FF;
		dgr.T0.DoneSignal = 0xFF;
		dgr.T0.Positive = FALSE;
		dgr.T0.Terminate = TRUE;
		dgr.T0.HighDrive = TRUE;
		dgr.T0.Digital = 0xFFFFFFFF;
		dgr.T0.OutputModulo = 0xFFFFFFFF;
		dgr.T0.Analog = 0xFFF;

		dgr.A.GoSignal = 0x2FF;
		dgr.A.DoneSignal = 0xFF;
		dgr.A.Positive = FALSE;
		dgr.A.Terminate = TRUE;
		dgr.A.HighDrive = TRUE;
		dgr.A.Digital = 0xFFFFFFFF;
		dgr.A.OutputModulo = 0xFFFFFFFF;
		dgr.A.Analog = 0xFFF;

		dgr.B.GoSignal = 0x2FF;
		dgr.B.DoneSignal = 0xFF;
		dgr.B.Positive = FALSE;
		dgr.B.Terminate = TRUE;
		dgr.B.HighDrive = TRUE;
		dgr.B.Digital = 0xFFFFFFFF;
		dgr.B.OutputModulo = 0xFFFFFFFF;
		dgr.B.Analog = 0xFFF;

		dgr.DT.ClockSource = TriggerInput;
		Set_DG_BME(&dgr, DG_Number);
		dgr.DT.ClockSource = CrystalOscillator;
		Set_DG_BME(&dgr, DG_Number);

		switch (p_Present->DG_Product)
		{
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05P3:
		case BME_SG05P2:
		case BME_SG05P3:
			dgr.DT.MS_Bus |= Resynchronize;
		default:
			dgr.DT.MS_Bus |= LocalPrimary;
			break;
		}
		dgr.DT.InhibitTrigger = 0x0;
		dgr.DT.ForceTrigger = 0x0;
		dgr.DT.InternalTrigger = FALSE;
		dgr.DT.StopOnPreset = FALSE;
		dgr.DT.ResetWhenDone = FALSE;
		dgr.DT.TriggerEnable = FALSE;
		dgr.DT.ClockEnable = FALSE;
		dgr.DT.SynchronizeGate = FALSE;
		dgr.DT.PositiveGate = TRUE;
		dgr.DT.IgnoreGate = FALSE;
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
	case BME_G03V1:
	case BME_G03V2:
	case BME_G03V3:
	case BME_G03V4:
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		LoadCommandRegister(p_Present->CommandRegister, p_Present);
		CounterControlValue[0] = 0x0;
		CounterControlValue[1] = 0x0;
		p_Present->CounterControlState[0] = 0xFFFFFFFF;
		p_Present->CounterControlState[1] = 0xFFFFFFFF;
		LoadCounterControl(CounterControlValue, p_Present);
		Value = 0x3F;
		DataOut(p_Present->InitializeAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0x0;
		DataOut(p_Present->InterruptEnableAddress, &Value, p_Present->h_DelayGenerator, -1);
		Value = 0xFF;
		DataOut(p_Present->InterruptAcknowledgeAddress, &Value, p_Present->h_DelayGenerator, -1);

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
	case BME_G04:
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
						(*(p_value + 1) != p_Present->PrescalerState[1]))
	{
		p_Present->PrescalerState[0] = *p_value;
		p_Present->PrescalerState[1] = *(p_value + 1);
		switch (p_Present->DG_Product)
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
			NumBytes = 8;
			break;
		case BME_G03V3:
			NumBytes = 2;
			break;
		case BME_SG02V4:
		case BME_G02V3:
			NumBytes = 1;
			break;
		default:
			NumBytes = 0;
			break;
		}
		DataOut(p_Present->PrescalerAddress, &(p_Present->PrescalerState), 
																							p_Present->h_DelayGenerator, NumBytes);
	}
}

void LoadCounterControl(unsigned long* p_value, DG_InternalData* p_Present)
{
	int NumBytes;
	if ((*p_value != p_Present->CounterControlState[0]) || 
						(*(p_value + 1) != p_Present->CounterControlState[1]))
	{
		p_Present->CounterControlState[0] = *p_value;
		p_Present->CounterControlState[1] = *(p_value + 1);
		switch (p_Present->DG_Product)
		{
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			NumBytes = 8;
			break;
		default:
			NumBytes = -1;
			break;
		}
		DataOut(p_Present->CounterControlAddress, p_Present->CounterControlState,
																							p_Present->h_DelayGenerator, NumBytes);
	}
}

void LoadCommandRegister(unsigned short value, DG_InternalData* p_Present)
{
	if (value != p_Present->CommandRegisterState)
	{
		DataOut(p_Present->CommandAddress, &value, p_Present->h_DelayGenerator, -1);
		p_Present->CommandRegisterState = value;
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
		case BME_G04:
			if (p_rf->DigSecond != p_Present->DelayGeneratorState.T0.DigSecond)
			{
				*p_Prepare &= ~0x111001;
				*(p_Prepare + 1) &= ~0x10111;
			}
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
		case BME_G04:
			if (p_k->DigSecond != p_ChState->DigSecond)
			{
				*p_Prepare &= ~ModBit[0];
				*(p_Prepare + 1) &= ~ModBit[1];
			}
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
		{
			p_Present->CommandRegister &= 0x3EF7;
			//*p_FinalValue &= 0xDF;
			//*p_Prepare &= 0xDF;
		}
		p_Present->DelayGeneratorState.DT.StopOnPreset = p_dt->StopOnPreset;
		if ((p_dt->InternalTrigger) || (p_dt->InternalArm))
		{
			p_Present->CommandRegister &= 0x3EFA;
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
				p_Present->CommandRegister &= 0x3EFC;
				p_Present->CommandRegister |= 0x04;
			}
			else
			{
				if (p_dt->RisingEdge)
				{
					p_Present->CommandRegister &= 0x3EF9;
					p_Present->CommandRegister |= 0x01;
				}
				else
					p_Present->CommandRegister &= 0x3EF8;
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
			//if (p_dt->InhibitTrigger != p_Present->DelayGeneratorState.DT.InhibitTrigger) 
			//	*p_Prepare &= ~0x10;
			//if (p_dt->ForceTrigger != p_Present->DelayGeneratorState.DT.ForceTrigger) 
			//	*p_Prepare &= ~0x10;
			if ((p_dt->ForceTrigger > 0) || (p_dt->InhibitTrigger > 0))
				*p_FinalValue |= 0x18;
			else
				*p_FinalValue &= ~0x18;
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
			p_Present->CommandRegister &= 0x3EBF;
		p_Present->DelayGeneratorState.DT.ResetWhenDone = p_dt->ResetWhenDone;
		break;
	}
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
				DataOut(p_Present->Delay_Aux, &(p_mc->Digital), p_Present->h_DelayGenerator, 4);
				if ((DG_Product == BME_G03V1) || (DG_Product == BME_G03V2))
					DataOut(p_Present->Delay_Aux, &(p_mc->Int3), p_Present->h_DelayGenerator, 4);
			}
		}
	}
}

void Set_Delay_Trigger(DelayTriggerType* p_dt, DG_InternalData* p_Present)
{
	int	DG_Product = p_Present->DG_Product;
	//unsigned char dummy;
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
		if ((p_dt->TriggerDAC & 0x0FFF) != (p_Present->DelayGeneratorState.DT.TriggerDAC & 0x0FFF))
		{
			p_Present->DelayGeneratorState.DT.TriggerLevel = p_dt->TriggerLevel;
			DataOut(p_Present->DAC, &(p_dt->TriggerDAC), p_Present->h_DelayGenerator, 2);
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
	case BME_G04:
		if (p_dt->StopOnPreset)
		{
			if (p_dt->PresetValue != p_Present->DelayGeneratorState.DT.PresetValue) 
			{
				p_Present->DelayGeneratorState.DT.PresetValue = p_dt->PresetValue;
				DataOut(p_Present->TriggerCounterAddress, &(p_dt->PresetValue), p_Present->h_DelayGenerator, 4);
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
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->InhibitTrigger), p_Present->h_DelayGenerator, 4);
			p_Present->DelayGeneratorState.DT.ForceTrigger = p_dt->ForceTrigger;
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->ForceTrigger), p_Present->h_DelayGenerator, 4);
		}
		break;
	case BME_G05P2:
	case BME_G05P3:
		if (p_dt->InhibitTrigger != p_Present->DelayGeneratorState.DT.InhibitTrigger)
		{
			p_Present->DelayGeneratorState.DT.InhibitTrigger = p_dt->InhibitTrigger;
			DataOut(p_Present->ModuloCounterAddress, &(p_dt->InhibitTrigger), p_Present->h_DelayGenerator, 4);
		}
		break;
	default:
		if ((p_dt->InternalTrigger) || (p_dt->InternalArm))
		{
			if (p_dt->RepCounter != p_Present->DelayGeneratorState.DT.RepCounter) 
			{
				p_Present->DelayGeneratorState.DT.RepCounter = p_dt->RepCounter;
				DataOut(p_Present->ModuloCounterAddress, &(p_dt->RepCounter), p_Present->h_DelayGenerator, 4);
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
				DataOut(p_Present->Delay_cntrl, &Value, p_Present->h_DelayGenerator, -1);
				if (DG_Product == BME_DP01)
				{
					if (p_rf->Digital_HW == 0)
					{
						Value = 0x30;
						DataOut(p_Present->Large_cntrl, &Value, p_Present->h_DelayGenerator, -1);
						dummy = 0xFEFF;
						DataOut(p_Present->Large_T0, &dummy, p_Present->h_DelayGenerator, 2);
					}
					else
					{
						Value = 0x3A;
						DataOut(p_Present->Large_cntrl, &Value, p_Present->h_DelayGenerator, -1);
					}
				}
			}
			else
			{
				Value = 0x38;
				DataOut(p_Present->Delay_cntrl, &Value, p_Present->h_DelayGenerator, -1);
				if (DG_Product == BME_DP01)
					DataOut(p_Present->Large_cntrl, &Value, p_Present->h_DelayGenerator, -1);
			}
		}
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			DataOut(p_Present->Delay_T0, &(p_rf->Digital), p_Present->h_DelayGenerator, 2);
			if (DG_Product == BME_DP01)
			{
				if ((p_rf->Digital_HW == 0) && (p_Present->DelayGeneratorState.T0.Digital_HW != 0))
				{
					Value = 0x30;
					DataOut(p_Present->Large_cntrl, &Value, p_Present->h_DelayGenerator, -1);
					dummy = 0xFEFF;
					DataOut(p_Present->Large_T0, &dummy, p_Present->h_DelayGenerator, 2);
				}
				if ((p_rf->Digital_HW != 0) && (p_Present->DelayGeneratorState.T0.Digital_HW == 0))
				{
					Value = 0x3A;
					DataOut(p_Present->Large_cntrl, &Value, p_Present->h_DelayGenerator, -1);
				}
				if (p_rf->Digital_HW != 0)
					DataOut(p_Present->Large_T0, &(p_rf->Digital_HW), p_Present->h_DelayGenerator, 2);
				else
				{
					dummy = 0xFEFF;
					DataOut(p_Present->Large_T0, &dummy, p_Present->h_DelayGenerator, 2);
				}
			}
			p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
			p_Present->DelayGeneratorState.T0.DigOff = p_rf->DigOff;
			p_Present->DelayGeneratorState.T0.DigSecond = p_rf->DigSecond;
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
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), p_Present->h_DelayGenerator, 4);
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
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(p_Present->Delay_T0, &(p_rf->DigOff), p_Present->h_DelayGenerator, 4);
				//printf("Set_Reference_channel(): %2d,   %2d\n", p_rf->Digital, p_rf->DigOff);
			}
		}
		break;
	case BME_G04:
		if ((p_rf->GoSignal & 0x77) != 0x0)
		{
			if ((p_rf->Digital != p_Present->DelayGeneratorState.T0.Digital) ||
						(p_rf->DigOff != p_Present->DelayGeneratorState.T0.DigOff) ||
						(p_rf->DigSecond != p_Present->DelayGeneratorState.T0.DigSecond))
			{
				p_Present->DelayGeneratorState.T0.Digital = p_rf->Digital;
				p_Present->DelayGeneratorState.T0.DigOff = p_rf->DigOff;
				p_Present->DelayGeneratorState.T0.DigSecond = p_rf->DigSecond;
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(p_Present->Delay_T0, &(p_rf->DigOff), p_Present->h_DelayGenerator, 4);
				DataOut(p_Present->Delay_T0, &(p_rf->DigSecond), p_Present->h_DelayGenerator, 4);
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
				DataOut(p_Present->Delay_T0, &(p_rf->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(p_Present->Delay_T0, &(p_rf->OutputModulo), p_Present->h_DelayGenerator, 4);
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
				DataOut(p_Present->DAC_T0, &(InvertedValue), p_Present->h_DelayGenerator, 2);
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
				DataOut(p_Present->Delay_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
				if (DG_Product == BME_DP01)
				{
					if (p_k->Digital_HW == 0)
					{
						cntrl &= 0xF0;
						DataOut(p_Present->Large_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
						dummy = 0xFEFF;
						DataOut((unsigned short)(p_Present->Large + pos), &dummy, p_Present->h_DelayGenerator, 2);
					}
					else
						DataOut(p_Present->Large_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
				}
			}
			else
			{
				cntrl = 0x38 + (pos * 0x40);
				DataOut(p_Present->Delay_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
				if (DG_Product == BME_DP01)
					DataOut(p_Present->Large_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
			}
		}
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			DataOut(DelayAddress, &(p_k->Digital), p_Present->h_DelayGenerator, 2);
			if (DG_Product == BME_DP01)
			{
				if ((p_k->Digital_HW == 0) && (p_ChState->Digital_HW != 0))
				{
					cntrl = 0x30 + (pos * 0x40);
					DataOut(p_Present->Large_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
					dummy = 0xFEFF;
					DataOut((unsigned short)(p_Present->Large + pos), &dummy, p_Present->h_DelayGenerator, 2);
				}
				if ((p_k->Digital_HW != 0) && (p_ChState->Digital_HW == 0))
				{
					cntrl = 0x3A + (pos * 0x40);
					DataOut(p_Present->Large_cntrl, &cntrl, p_Present->h_DelayGenerator, -1);
				}
				if (p_k->Digital_HW != 0)
				{
					DataOut((unsigned short)(p_Present->Large + pos), &(p_k->Digital_HW), 
																							p_Present->h_DelayGenerator, 2);
				}
				else
				{
					dummy = 0xFEFF;
					DataOut((unsigned short)(p_Present->Large + pos), &dummy, p_Present->h_DelayGenerator, 2);
				}
			}
			p_ChState->Digital = p_k->Digital;
			//printf("Digital : %2d , pos : %1d\n", p_ChState->Digital, pos);

			p_ChState->Analog = (p_k->Analog & 0x0FFF);
			pch = (unsigned char*) &(p_ChState->Analog);
			adr1 = p_Present->DAC + 2 * (pos - 1);
			DataOut(adr1, pch, p_Present->h_DelayGenerator, -1);
			adr1 += 1;
			DataOut(adr1, (pch + 1), p_Present->h_DelayGenerator, -1);
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
				DataOut(DelayAddress, &(p_k->Digital), p_Present->h_DelayGenerator, 4);
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
				DataOut(DelayAddress, &(p_k->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(DelayAddress, &(p_k->DigOff), p_Present->h_DelayGenerator, 4);
				//printf("Set_Delay_channel() nr. %d: %2d,   %2d\n", pos, p_k->Digital, p_k->DigOff);
			}
		}
		break;
	case BME_G04:
		if ((p_k->GoSignal & 0x77) != 0x0)
		{
			if ((p_k->Digital != p_ChState->Digital) ||
						(p_k->DigOff != p_ChState->DigOff) ||
						(p_k->DigSecond != p_ChState->DigSecond))
			{
				p_ChState->Digital = p_k->Digital;
				p_ChState->DigOff = p_k->DigOff;
				p_ChState->DigSecond = p_k->DigSecond;
				DataOut(DelayAddress, &(p_k->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(DelayAddress, &(p_k->DigOff), p_Present->h_DelayGenerator, 4);
				DataOut(DelayAddress, &(p_k->DigSecond), p_Present->h_DelayGenerator, 4);
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
				DataOut(DelayAddress, &(p_k->Digital), p_Present->h_DelayGenerator, 4);
				DataOut(DelayAddress, &(p_k->OutputModulo), p_Present->h_DelayGenerator, 4);
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
				DataOut(DacAddress, &(InvertedValue), p_Present->h_DelayGenerator, 2);
				break;
			default:
				pch = (unsigned char*) &(p_ChState->Analog);
				adr1 = p_Present->DAC + 2 * (pos - 1);
				DataOut(adr1, pch, p_Present->h_DelayGenerator, -1);
				adr1 += 1;
				DataOut(adr1, (pch + 1), p_Present->h_DelayGenerator, -1);
				break;
			}
		}
	}
	p_ChState->GoSignal |= (p_k->GoSignal & 0x77);
	p_ChState->GoSignal &= (p_k->GoSignal | ~0x77);
}


void PrepareCounterControl(DG_BME_Registers* p_pdg, DG_InternalData* p_Present)
{
	unsigned long DG_Product = p_Present->DG_Product;
	unsigned long cctrl[2];
	memcpy(cctrl, p_Present->CounterControlState, 8);
	memcpy(p_Present->CounterControlRegister, p_Present->CounterControlState, 8);
	switch (DG_Product)
	{
	case SRS_DG135:
	case BME_DP01:
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
	unsigned long DG_Product = p_Present->DG_Product;
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
				p_Present->CommandRegister &= 0x3EEF;
		}
		p_Present->DelayGeneratorState.DT.TriggerEnable = p_pdg->DT.TriggerEnable;
	}
}


void ActionDC(unsigned long* p_Action, 
											 DelayChannelData* p_a, DelayChannelData* p_b, unsigned long DG_Product)
{
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
		if (p_a->OutputModulo != p_b->OutputModulo)
			*p_Action |= 0x4;
		if (p_a->OutputOffset != p_b->OutputOffset)
			*p_Action |= 0x4;
		break;
	default:
		break;
	}
}

void ActionDT(unsigned long* p_Action, DelayTriggerData* p_a, DelayTriggerData* p_b)
{
	if (p_a->InternalTrigger != p_b->InternalTrigger)
		*p_Action |= 0x1;
	if (p_a->InternalArm != p_b->InternalArm)
		*p_Action |= 0x1;
	if (p_a->SoftwareTrigger != p_b->SoftwareTrigger)
		*p_Action |= 0x1;
	if (p_a->RisingEdge != p_b->RisingEdge)
		*p_Action |= 0x1;
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
	if (p_a->TriggerEnable != p_b->TriggerEnable)
		*p_Action |= 0x1;
	if (p_a->Terminate != p_b->Terminate)
		*p_Action |= 0x1;
	if (p_a->PositiveGate != p_b->PositiveGate)
		*p_Action |= 0x1;
	if (p_a->SynchronizeGate != p_b->SynchronizeGate)
		*p_Action |= 0x1;
	if ((p_a->GateDivider == 0) && (p_b->GateDivider != 0))
		*p_Action |= 0x1;
	if ((p_b->GateDivider == 0) && (p_a->GateDivider != 0))
		*p_Action |= 0x1;
	if (p_a->ClockSource != p_b->ClockSource)
		*p_Action |= 0x1;
	if (p_a->ClockEnable != p_b->ClockEnable)
		*p_Action |= 0x1;
}

BOOL IsEqualDT(DelayTriggerType* p_a, DelayTriggerType* p_b, unsigned long DG_Product)
{
	switch (DG_Product)
	{
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
	case BME_G04:
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
	if ((p_a->GoSignal & 0x77) != (p_b->GoSignal & 0x77))
		return FALSE;
	if ((p_a->GoSignal & 0x77) != 0x0)
	{
		switch (DG_Product)
		{
		case BME_G04:
			if (p_a->DigSecond != p_b->DigSecond)
				return FALSE;
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
	case BME_SG02P5:
	case BME_SG05P3:
		if ((p_a->T0.GoSignal & 0x100) != (p_b->T0.GoSignal & 0x100))
			return FALSE;
		if ((p_a->DT.MS_Bus & Resynchronize) != (p_b->DT.MS_Bus & Resynchronize))
			return FALSE;
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG02P4:
		if ((p_a->T0.GoSignal & 0x80) != (p_b->T0.GoSignal & 0x80))
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

void Set_Prescaler(DG_BME_Registers* p_pdg, DG_InternalData* p_Present)
{
	unsigned long Value;
	unsigned long Remainder;
	unsigned long  PrescalerValue[2];
	unsigned long pscl,psch;
	unsigned long pscbits;
	DG_BME_Registers* p_state = &(p_Present->DelayGeneratorState);
	unsigned long DG_Product = p_Present->DG_Product;
	pscl = p_Present->PrescalerState[0];
	psch = p_Present->PrescalerState[1];
	switch (DG_Product)
	{
	case BME_SG02P4:
	case BME_G05P3:
	case BME_SG05P2:
		pscl &= ~0x40000000;
		break;
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
	case BME_G04:
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
				case BME_G04:
					if (_stricmp(word, "BME_G04"))
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
				case BME_G04:
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
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
				case BME_G04:
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

void ResetDelayChannel(DelayChannel* p_dc)
{
	p_dc->Digital = 0;
	p_dc->DigOff = 0;
	p_dc->DigSecond = 0;
	p_dc->OutputModulo = 1;
	p_dc->AnalogData = 0;
	p_dc->GoSignal = 0x0;
	p_dc->DoneSignal = 0x0;
	p_dc->Positive = TRUE;
	p_dc->Terminate = FALSE;
	p_dc->HighDrive = FALSE;
}

void ResetMainCounter(MainCounterType* p_mc)
{
	p_mc->Active = FALSE;
	p_mc->ReserveFlag = FALSE;
	p_mc->Digital = 0;
	p_mc->Int3 = 0;
}

void ResetDelayTrigger(DelayTriggerType* p_dt)
{
	p_dt->RepCounter = 0;
	p_dt->ForceTrigger = 0;
	p_dt->TriggerLevel = 3072;
	p_dt->PresetValue = 0;
	//p_dt->Prescaler = 0x08;
	p_dt->OscillatorDivider = 1;
	p_dt->TriggerDivider = 6;
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
	p_dt->ForceTrigger = -1.0;
	p_dt->TriggerLevel = 1.25;
	p_dt->PresetValue = 0;
	p_dt->MS_Bus = LocalPrimary;

	p_dt->OscillatorDivider = 1;
	p_dt->TriggerDivider = 6;
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
	p_dt->Reserve = FALSE;
}

void CopyDelayControl(DelayChannelData* p_dc, DelayChannelData_V2* p_v2)
{
	ResetDelayControl(p_dc);
	p_dc->FireFirst = p_v2->FireFirst;
	p_dc->SetBack = p_v2->SetBack;
	p_dc->FireSecond = p_v2->FireSecond;
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
	p_dc->FireFirst = -1.0;
	p_dc->SetBack = -1.0;
	p_dc->FireSecond = -1.0;
	p_dc->OutputModulo = 1;
	p_dc->OutputOffset = 0;
	p_dc->GoSignal = 0x0;
	p_dc->DoneSignal = 0x0;
	p_dc->Positive = TRUE;
	p_dc->Terminate = FALSE;
	p_dc->HighDrive = FALSE;
	p_dc->Reserve = FALSE;
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
		case BME_G04:
			if (p_dl->FireSecond > MaxBME_G0XRange)
				return 5;
			if ((p_dl->FireSecond > p_dl->SetBack) && 
						(p_dl->SetBack > p_dl->FireFirst) && (p_dl->FireFirst > 0.0))
			{
				result = T0Numbers(&IntNumber, p_dl->FireSecond, DG_Number);
				if (result != 0)
					return result;
				p_a->DigSecond = MainCounter - IntNumber;
			}
			else
				p_a->DigSecond = MainCounter + 1;
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
		case BME_G04:
			if (p_dl->FireSecond > MaxBME_G0XRange)
				return 5;
			if ((p_dl->FireSecond > p_dl->SetBack) && 
						(p_dl->SetBack > p_dl->FireFirst) && (p_dl->FireFirst > 0.0))
			{
				result = T0Numbers(&IntNumber, (p_dl->FireSecond - Remainder), DG_Number);
				if (result != 0)
					return result;
				p_a->DigSecond = MainCounter - IntNumber;
			}
			else
				p_a->DigSecond = MainCounter + 1;
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

long DelayNumbers(double* p_remainder, unsigned int* p_digital, double InValue, long DG_Number)
{
	DG_InternalData* p_Present;
	double value,Delta,Increment;
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
		DacSteps = (RoundInt((4096.0 * Increment / 0.1)) - 1);
		DacMax = min( 4095, DacSteps);
		DacSwitch = (DacMax + DacSteps) / 2;
		Delta = 0.1 * ((double)DacMax) / 4096.0;
		if (InValue >= p_Present->p2Time)
		{
			value = (InValue - p_Present->p2Time) / Increment;
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
				*p_remainder = max(0.0, min(Delta, (InValue - p_Present->p1Time)));
				*p_digital = 1;
				break;
			default:
				if (InValue <= (p_Present->ZeroTime + Delta))
					*p_remainder = max(0.0, (InValue - p_Present->ZeroTime));
				else
				{
					if (InValue >= p_Present->p1Time)
					{
						if ((p_Present->p2Time - InValue) < (InValue - (p_Present->p1Time + Delta)))
							*p_digital = 2;
						else
						{
							*p_remainder = InValue - p_Present->p1Time;
							*p_digital = 1;
						}
					}
					else
					{
						if ((p_Present->p1Time - InValue) < (InValue - (p_Present->ZeroTime + Delta)))
							*p_digital = 1;
						else
							*p_remainder = Delta;
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
