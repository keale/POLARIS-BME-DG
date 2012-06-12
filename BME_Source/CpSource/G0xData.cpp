/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134
		email: bme-bergmann@t-online.de
		web:   http://www.bme-bergmann.de

    module:										 main data structures for BME_G0x
    category:                  
    purpose:

    description:               
                               

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    17. February 2001
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DG_Data.h"
#include "G0xData.h"
#include "DelgenData.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"
//#include <time.h>
//#include <math.h>

#define CurrentVersion								1
#define CurrentDG_FileVersion					8



 ///////////////////////////
// CG0xData

IMPLEMENT_SERIAL( CG0xData, CObject, VERSIONABLE_SCHEMA|CurrentVersion )
//IMPLEMENT_SERIAL( CG0xData, CObject, 1 )

CG0xData::CG0xData()
{
// This empty constructor should be used by serialization only
}

CG0xData::CG0xData(int sdata)
{
	m_dtyp = sdata;
	nVersion = CurrentVersion;

	ResetData();
}

CG0xData::~CG0xData()
{
	DeleteData();
}

void CG0xData::DeleteData()
{
	InitializeDG_List(m_DG_List);
	InitializeDG_List(m_Show_List);
	if (p_DelayGenerator != NULL)
	{
		p_DelayGenerator->Release_DG_Data();
		delete p_DelayGenerator;
	}
	if (ParameterList.p_Value != NULL)
		delete []ParameterList.p_Value;
	if (ParameterList.p_Loc != NULL)
		delete []ParameterList.p_Loc;
	if (FpgaMemoryList.p_Value != NULL)
		delete []FpgaMemoryList.p_Value;
	if (FpgaMemoryList.p_Loc != NULL)
		delete []FpgaMemoryList.p_Loc;
	if (p_OpInfo != NULL)
		delete []p_OpInfo;
	ResetData();
}


void CG0xData::SaveParameters(LPCTSTR FileName)
{
	char CharFileName[200];
	strcpy(CharFileName, FileName);
	DG_Type* p_DG;
  //int Modules[10];
	int NoDelayGenerators = m_Show_List.GetCount();
	DG_BME_State* p_DGS = new DG_BME_State[max(2, NoDelayGenerators)];
	POSITION pos1 = m_Show_List.GetHeadPosition();
	int i1 = 0;
	while (pos1 != NULL)
	{
		p_DG = m_Show_List.GetNext(pos1);
		memcpy(&((p_DGS + i1)->Control), &(p_DG->Control), sizeof(DG_BME_Control));
		(p_DGS + i1)->BaseAddress = p_DG->BaseAddress;
		(p_DGS + i1)->DG_Product = p_DG->Product;
		(p_DGS + i1)->Master = p_DG->Master;
		(p_DGS + i1)->BusNumber = p_DG->BusNumber;
		memcpy(&((p_DGS + i1)->ip_address), &(p_DG->ip_address), (40 * sizeof(char)));
		i1++;
	}
	p_DelayGenerator->SaveParameters(p_DGS, NoDelayGenerators, 
																		b_CalibrateTiming, m_CalibrationLevel, CharFileName);
	//NoDelayGenerators = p_DelayGenerator->ReadParameters(p_DGS, Modules,
  	//																&b_CalibrateTiming, &m_CalibrationLevel, CharFileName);
	//unsigned long result;
	//for (i1 = 0; i1 < NoDelayGenerators; i1++)
	//{
		//result = p_DelayGenerator->SetDelayGenerator(&((p_DGS + i1)->Control), i1);
	//}
	delete []p_DGS;
}

void CG0xData::Serialize( CArchive& ar )
{
	m_FileName = ar.GetFile()->GetFilePath();
	m_FileTitle = ar.GetFile()->GetFileTitle();
	CString LogInfo;
	//AfxMessageBox(kstr, MB_OK, 0);
	if( ar.IsStoring( ) )
	{
		//LogInfo.Format("writing to file: %s", (LPCTSTR)m_FileName);
		//fr.AddLogText(*p_ExperimentLog, (LPCTSTR) LogInfo);
		WriteDG_List(ar, m_DG_List);
		ar << b_CalibrateTiming;
		ar << m_CalibrationLevel;
		ar.Write(&m_TimeSequence, sizeof(XParameterType));
	}
	else
	{
		ResetInternalData();
		nVersion = ar.GetObjectSchema();
		ReadDG_List(ar, m_DG_List);
		ar >> b_CalibrateTiming;
		if (nVersion > 0)
			ar >> m_CalibrationLevel;
		ar.Read(&m_TimeSequence, sizeof(XParameterType));
	}
	if( ar.IsStoring())
	{
		m_FpgaMemory.Serialize(ar);
		m_XParameter.Serialize(ar);
	}
	else
	{
		if (nVersion > 6)
			m_FpgaMemory.Serialize(ar);
		if (nVersion > 5)
			m_XParameter.Serialize(ar);
		CopyDG_List(m_Show_List, m_DG_List);
		LoadParameterList(ParameterList, m_XParameter);
		LoadParameterList(FpgaMemoryList, m_FpgaMemory);
	}
}

BOOL CG0xData::ContainsVariables(CStringArray& csa)
{
	CString str;
	int count = csa.GetSize();
	int i1 = 0;
	while (i1 < count)
	{
		str = csa.GetAt(i1);
		if (strpbrk(str, "xX" ) != NULL)
			return TRUE;
		i1++;
	}
	return FALSE;
}

BOOL CG0xData::MemoryReferenceExist()
{
	DG_Type* p_DG;
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (p_DG->VarLoc.A.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.A.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.A.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.A.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.A.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.A.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.A.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.A.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.A.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}

		if (p_DG->VarLoc.B.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.B.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.B.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.B.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.B.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.B.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.B.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.B.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.B.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}

		if (p_DG->VarLoc.C.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.C.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.C.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.C.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.C.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.C.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.C.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.C.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.C.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}

		if (p_DG->VarLoc.D.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.D.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.D.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.D.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.D.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.D.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.D.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.D.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.D.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}

		if (p_DG->VarLoc.E.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.E.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.E.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.E.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.E.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.E.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.E.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.E.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.E.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}

		if (p_DG->VarLoc.F.FireFirst >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.F.FireFirst == -2)
			{
				if (strpbrk(p_DG->VarEqu.F.FireFirst, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.F.PulseWidth >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.F.PulseWidth == -2)
			{
				if (strpbrk(p_DG->VarEqu.F.PulseWidth, "yY" ) != NULL)
					return TRUE;
			}
		}
		if (p_DG->VarLoc.F.StepBack >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.F.StepBack == -2)
			{
				if (strpbrk(p_DG->VarEqu.F.StepBack, "yY" ) != NULL)
					return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CG0xData::ChannelFpgaMemoryExist(ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith)
{
	if (ChanLoc.FireFirst == -2)
	{
		if (strpbrk(ChanArith.FireFirst, "yY" ) != NULL)
			return TRUE;
	}
	if (ChanLoc.PulseWidth == -2)
	{
		if (strpbrk(ChanArith.PulseWidth, "yY" ) != NULL)
			return TRUE;
	}
	if (ChanLoc.StepBack == -2)
	{
		if (strpbrk(ChanArith.StepBack, "yY" ) != NULL)
			return TRUE;
	}
	return FALSE;
}

BOOL CG0xData::FpgaMemoryExist()
{
	DG_Type* p_DG;
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.A, p_DG->VarEqu.A))
			return TRUE;
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.B, p_DG->VarEqu.B))
			return TRUE;
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.C, p_DG->VarEqu.C))
			return TRUE;
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.D, p_DG->VarEqu.D))
			return TRUE;
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.E, p_DG->VarEqu.E))
			return TRUE;
		if (ChannelFpgaMemoryExist(p_DG->VarLoc.F, p_DG->VarEqu.F))
			return TRUE;
	}
	return FALSE;
}

BOOL CG0xData::ChannelVariablesExist(ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith)
{
	if (ChanLoc.FireFirst >= 0)
		return TRUE;
	else
	{
		if (ChanLoc.FireFirst == -2)
		{
			if (strpbrk(ChanArith.FireFirst, "xX" ) != NULL)
				return TRUE;
		}
	}	
	if (ChanLoc.SetBack >= 0)
		return TRUE;
	else
	{
		if (ChanLoc.SetBack == -2)
		{
			if (strpbrk(ChanArith.SetBack, "xX" ) != NULL)
				return TRUE;
		}
	}	
	if (ChanLoc.PulseWidth >= 0)
		return TRUE;
	else
	{
		if (ChanLoc.PulseWidth == -2)
		{
			if (strpbrk(ChanArith.PulseWidth, "xX" ) != NULL)
				return TRUE;
		}
	}	
	if (ChanLoc.OutputModulo >= 0)
		return TRUE;
	else
	{
		if (ChanLoc.OutputModulo == -2)
		{
			if (strpbrk(ChanArith.OutputModulo, "xX" ) != NULL)
				return TRUE;
		}
	}	
	if (ChanLoc.OutputOffset >= 0)
		return TRUE;
	else
	{
		if (ChanLoc.OutputOffset == -2)
		{
			if (strpbrk(ChanArith.OutputOffset, "xX" ) != NULL)
				return TRUE;
		}
	}	
	return FALSE;
}

BOOL CG0xData::VariablesExist()
{
	DG_Type* p_DG;
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (ChannelVariablesExist(p_DG->VarLoc.T0, p_DG->VarEqu.T0))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.A, p_DG->VarEqu.A))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.B, p_DG->VarEqu.B))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.C, p_DG->VarEqu.C))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.D, p_DG->VarEqu.D))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.E, p_DG->VarEqu.E))
			return TRUE;
		if (ChannelVariablesExist(p_DG->VarLoc.F, p_DG->VarEqu.F))
			return TRUE;

		if (p_DG->VarLoc.RepCounter >= 0)
			return TRUE;
		else
		{
			if (p_DG->VarLoc.RepCounter == -2)
			{
				if (strpbrk(p_DG->VarEqu.RepCounter, "xX" ) != NULL)
					return TRUE;
			}
		}
	}
	if (MemoryReferenceExist())
	{
		if (ContainsVariables(m_FpgaMemory))
			return TRUE;
	}

	return FALSE;
}

void CG0xData::ResetOutOfRangeVariables()
{
	DG_Type* p_DG;
	int Width = ParameterList.NoParameters;
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (p_DG->VarLoc.T0.FireFirst >= Width)
		{
			p_DG->Control.T0.GoSignal &= 0x188;
			p_DG->Control.T0.DoneSignal = 0x0;
			p_DG->VarLoc.T0.FireFirst = -1;
			p_DG->VarEqu.T0.FireFirst[0] = 0;
			p_DG->Control.T0.FireFirst = -1.0;
			p_DG->VarLoc.T0.SetBack = -1;
			p_DG->VarEqu.T0.SetBack[0] = 0;
			p_DG->Control.T0.SetBack = -1.0;
			p_DG->VarLoc.T0.PulseWidth = -1;
			p_DG->VarEqu.T0.PulseWidth[0] = 0;
			p_DG->Control.T0.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.T0.SetBack >= Width)
		{
			p_DG->VarLoc.T0.SetBack = -1;
			p_DG->VarEqu.T0.SetBack[0] = 0;
			p_DG->Control.T0.SetBack = -1.0;
			p_DG->VarLoc.T0.PulseWidth = -1;
			p_DG->VarEqu.T0.PulseWidth[0] = 0;
			p_DG->Control.T0.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.T0.PulseWidth >= Width)
		{
			p_DG->VarLoc.T0.PulseWidth = -1;
			p_DG->VarEqu.T0.PulseWidth[0] = 0;
			p_DG->Control.T0.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.A.FireFirst >= Width)
		{
			p_DG->Control.A.GoSignal &= 0x188;
			p_DG->Control.A.DoneSignal = 0x0;
			p_DG->VarLoc.A.FireFirst = -1;
			p_DG->VarEqu.A.FireFirst[0] = 0;
			p_DG->Control.A.FireFirst = -1.0;
			p_DG->VarLoc.A.SetBack = -1;
			p_DG->VarEqu.A.SetBack[0] = 0;
			p_DG->Control.A.SetBack = -1.0;
			p_DG->VarLoc.A.PulseWidth = -1;
			p_DG->VarEqu.A.PulseWidth[0] = 0;
			p_DG->Control.A.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.A.SetBack >= Width)
		{
			p_DG->VarLoc.A.SetBack = -1;
			p_DG->VarEqu.A.SetBack[0] = 0;
			p_DG->Control.A.SetBack = -1.0;
			p_DG->VarLoc.A.PulseWidth = -1;
			p_DG->VarEqu.A.PulseWidth[0] = 0;
			p_DG->Control.A.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.A.PulseWidth >= Width)
		{
			p_DG->VarLoc.A.PulseWidth = -1;
			p_DG->VarEqu.A.PulseWidth[0] = 0;
			p_DG->Control.A.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.B.FireFirst >= Width)
		{
			p_DG->Control.B.GoSignal &= 0x188;
			p_DG->Control.B.DoneSignal = 0x0;
			p_DG->VarLoc.B.FireFirst = -1;
			p_DG->VarEqu.B.FireFirst[0] = 0;
			p_DG->Control.B.FireFirst = -1.0;
			p_DG->VarLoc.B.SetBack = -1;
			p_DG->VarEqu.B.SetBack[0] = 0;
			p_DG->Control.B.SetBack = -1.0;
			p_DG->VarLoc.B.PulseWidth = -1;
			p_DG->VarEqu.B.PulseWidth[0] = 0;
			p_DG->Control.B.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.B.SetBack >= Width)
		{
			p_DG->VarLoc.B.SetBack = -1;
			p_DG->VarEqu.B.SetBack[0] = 0;
			p_DG->Control.B.SetBack = -1.0;
			p_DG->VarLoc.B.PulseWidth = -1;
			p_DG->VarEqu.B.PulseWidth[0] = 0;
			p_DG->Control.B.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.B.PulseWidth >= Width)
		{
			p_DG->VarLoc.B.PulseWidth = -1;
			p_DG->VarEqu.B.PulseWidth[0] = 0;
			p_DG->Control.B.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.C.FireFirst >= Width)
		{
			p_DG->Control.C.GoSignal &= 0x188;
			p_DG->Control.C.DoneSignal = 0x0;
			p_DG->VarLoc.C.FireFirst = -1;
			p_DG->VarEqu.C.FireFirst[0] = 0;
			p_DG->Control.C.FireFirst = -1.0;
			p_DG->VarLoc.C.SetBack = -1;
			p_DG->VarEqu.C.SetBack[0] = 0;
			p_DG->Control.C.SetBack = -1.0;
			p_DG->VarLoc.C.PulseWidth = -1;
			p_DG->VarEqu.C.PulseWidth[0] = 0;
			p_DG->Control.C.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.C.SetBack >= Width)
		{
			p_DG->VarLoc.C.SetBack = -1;
			p_DG->VarEqu.C.SetBack[0] = 0;
			p_DG->Control.C.SetBack = -1.0;
			p_DG->VarLoc.C.PulseWidth = -1;
			p_DG->VarEqu.C.PulseWidth[0] = 0;
			p_DG->Control.C.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.C.PulseWidth >= Width)
		{
			p_DG->VarLoc.C.PulseWidth = -1;
			p_DG->VarEqu.C.PulseWidth[0] = 0;
			p_DG->Control.C.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.D.FireFirst >= Width)
		{
			p_DG->Control.D.GoSignal &= 0x188;
			p_DG->Control.D.DoneSignal = 0x0;
			p_DG->VarLoc.D.FireFirst = -1;
			p_DG->VarEqu.D.FireFirst[0] = 0;
			p_DG->Control.D.FireFirst = -1.0;
			p_DG->VarLoc.D.SetBack = -1;
			p_DG->VarEqu.D.SetBack[0] = 0;
			p_DG->Control.D.SetBack = -1.0;
			p_DG->VarLoc.D.PulseWidth = -1;
			p_DG->VarEqu.D.PulseWidth[0] = 0;
			p_DG->Control.D.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.D.SetBack >= Width)
		{
			p_DG->VarLoc.D.SetBack = -1;
			p_DG->VarEqu.D.SetBack[0] = 0;
			p_DG->Control.D.SetBack = -1.0;
			p_DG->VarLoc.D.PulseWidth = -1;
			p_DG->VarEqu.D.PulseWidth[0] = 0;
			p_DG->Control.D.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.D.PulseWidth >= Width)
		{
			p_DG->VarLoc.D.PulseWidth = -1;
			p_DG->VarEqu.D.PulseWidth[0] = 0;
			p_DG->Control.D.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.E.FireFirst >= Width)
		{
			p_DG->Control.E.GoSignal &= 0x188;
			p_DG->Control.E.DoneSignal = 0x0;
			p_DG->VarLoc.E.FireFirst = -1;
			p_DG->VarEqu.E.FireFirst[0] = 0;
			p_DG->Control.E.FireFirst = -1.0;
			p_DG->VarLoc.E.SetBack = -1;
			p_DG->VarEqu.E.SetBack[0] = 0;
			p_DG->Control.E.SetBack = -1.0;
			p_DG->VarLoc.E.PulseWidth = -1;
			p_DG->VarEqu.E.PulseWidth[0] = 0;
			p_DG->Control.E.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.E.SetBack >= Width)
		{
			p_DG->VarLoc.E.SetBack = -1;
			p_DG->VarEqu.E.SetBack[0] = 0;
			p_DG->Control.E.SetBack = -1.0;
			p_DG->VarLoc.E.PulseWidth = -1;
			p_DG->VarEqu.E.PulseWidth[0] = 0;
			p_DG->Control.E.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.E.PulseWidth >= Width)
		{
			p_DG->VarLoc.E.PulseWidth = -1;
			p_DG->VarEqu.E.PulseWidth[0] = 0;
			p_DG->Control.E.PulseWidth[0] = -1.0;
		}

		if (p_DG->VarLoc.F.FireFirst >= Width)
		{
			p_DG->Control.F.GoSignal &= 0x188;
			p_DG->Control.F.DoneSignal = 0x0;
			p_DG->VarLoc.F.FireFirst = -1;
			p_DG->VarEqu.F.FireFirst[0] = 0;
			p_DG->Control.F.FireFirst = -1.0;
			p_DG->VarLoc.F.SetBack = -1;
			p_DG->VarEqu.F.SetBack[0] = 0;
			p_DG->Control.F.SetBack = -1.0;
			p_DG->VarLoc.F.PulseWidth = -1;
			p_DG->VarEqu.F.PulseWidth[0] = 0;
			p_DG->Control.F.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.F.SetBack >= Width)
		{
			p_DG->VarLoc.F.SetBack = -1;
			p_DG->VarEqu.F.SetBack[0] = 0;
			p_DG->Control.F.SetBack = -1.0;
			p_DG->VarLoc.F.PulseWidth = -1;
			p_DG->VarEqu.F.PulseWidth[0] = 0;
			p_DG->Control.F.PulseWidth[0] = -1.0;
		}
		if (p_DG->VarLoc.F.PulseWidth >= Width)
		{
			p_DG->VarLoc.F.PulseWidth = -1;
			p_DG->VarEqu.F.PulseWidth[0] = 0;
			p_DG->Control.F.PulseWidth[0] = -1.0;
		}

	}
}

void CG0xData::DeactivateDelayGenerators()
{
	DG_Type* p_DG;
	int Count = 0;
	EnterCriticalSection(p_DataAccess);
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (p_DG->Master)
			p_DelayGenerator->Deactivate_DG_BME(Count);
		Count++;
	}
	Count = 0;
	pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (!p_DG->Master)
			p_DelayGenerator->Deactivate_DG_BME(Count);
		Count++;
	}
	LeaveCriticalSection(p_DataAccess);
	b_DelayGeneratorsActive = FALSE;
}

void CG0xData::ActivateDelayGenerators()
{
	DG_Type* p_DG;
	int Count = 0;
	EnterCriticalSection(p_DataAccess);
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (!p_DG->Master)
			p_DelayGenerator->Activate_DG_BME(Count);
		Count++;
	}
	Count = 0;
	pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (p_DG->Master)
			p_DelayGenerator->Activate_DG_BME(Count);
		Count++;
	}
	LeaveCriticalSection(p_DataAccess);
	b_DelayGeneratorsActive = TRUE;
}

unsigned long CG0xData::ModifyAction(CTypedPtrList<CPtrList, DG_Type*>& m_List)
{
	DG_Type* p_DG;
	int Count = 0;
	unsigned long Action = 0x0;
	unsigned long result;
	EnterCriticalSection(p_DataAccess);
	POSITION pos = m_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_List.GetNext(pos);
		result = p_DelayGenerator->ModifyAction(&(p_DG->Control), Count);
		Action |= result;
		Count++;
	}
	LeaveCriticalSection(p_DataAccess);
	if (b_RequestZeroModulo)
	{
		Action |= 0x4;
		b_RequestZeroModulo = FALSE;
	}
	if (b_RequestJumpStart)
	{
		Action |= 0x8;
		b_RequestJumpStart = FALSE;
	}
	return Action;
}

void CG0xData::TestLoadDelayGenerator(DG_BME_Control* p_BDG, long DG_Number)
{
	p_DelayGenerator->Set_G08_ClockParameters(p_BDG->DT.ClockEnable, p_BDG->DT.OscillatorDivider, 
								p_BDG->DT.TriggerDivider, p_BDG->DT.TriggerMultiplier, p_BDG->DT.ClockSource,  DG_Number);
	p_DelayGenerator->Set_TriggerParameters(p_BDG->DT.Terminate, p_BDG->DT.InternalClock, 
													p_BDG->DT.TriggerLevel, p_BDG->DT.PresetValue, p_BDG->DT.GateDivider,
													p_BDG->DT.PositiveGate, p_BDG->DT.InternalTrigger, p_BDG->DT.InternalArm, p_BDG->DT.SoftwareTrigger,
													p_BDG->DT.RisingEdge, p_BDG->DT.StopOnPreset, p_BDG->DT.ResetWhenDone, p_BDG->DT.TriggerEnable, DG_Number);
	
	p_DelayGenerator->Set_G08_TriggerParameters(p_BDG->DT.GateTerminate, p_BDG->DT.GateLevel, p_BDG->DT.GateDelay, 
													p_BDG->DT.IgnoreGate, p_BDG->DT.SynchronizeGate, p_BDG->DT.ForceTrigger,
													p_BDG->DT.StepBackTime, p_BDG->DT.BurstCounter, p_BDG->DT.MS_Bus, DG_Number);
	p_DelayGenerator->Set_GateFunction(p_BDG->GateFunction, DG_Number);
	p_DelayGenerator->Set_G08_Delay(DelayChannel_A, p_BDG->A.FireFirst, p_BDG->A.PulseWidth[0], p_BDG->A.OutputModulo, p_BDG->A.OutputOffset,
															p_BDG->A.GoSignal, p_BDG->A.Positive, p_BDG->A.Terminate, 
															p_BDG->A.Disconnect, p_BDG->A.OntoMsBus, p_BDG->A.InputPositive, DG_Number);
	if (p_BDG->A.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_A, &(p_BDG->A.DelayTime[0]), &(p_BDG->A.PulseWidth[0]),
															&(p_BDG->A.StepBack[0]), p_BDG->A.ListLength, DG_Number);	
	p_DelayGenerator->Set_G08_Delay(DelayChannel_B, p_BDG->B.FireFirst, p_BDG->B.PulseWidth[0], p_BDG->B.OutputModulo, p_BDG->B.OutputOffset,
															p_BDG->B.GoSignal, p_BDG->B.Positive, p_BDG->B.Terminate, 
															p_BDG->B.Disconnect, p_BDG->B.OntoMsBus, p_BDG->B.InputPositive, DG_Number);
	if (p_BDG->B.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_B, &(p_BDG->B.DelayTime[0]), &(p_BDG->B.PulseWidth[0]),
															&(p_BDG->B.StepBack[0]), p_BDG->B.ListLength, DG_Number);	
	p_DelayGenerator->Set_G08_Delay(DelayChannel_C, p_BDG->C.FireFirst, p_BDG->C.PulseWidth[0], p_BDG->C.OutputModulo, p_BDG->C.OutputOffset,
															p_BDG->C.GoSignal, p_BDG->C.Positive, p_BDG->C.Terminate, 
															p_BDG->C.Disconnect, p_BDG->C.OntoMsBus, p_BDG->C.InputPositive, DG_Number);
	if (p_BDG->C.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_C, &(p_BDG->C.DelayTime[0]), &(p_BDG->C.PulseWidth[0]),
															&(p_BDG->C.StepBack[0]), p_BDG->C.ListLength, DG_Number);	
	p_DelayGenerator->Set_G08_Delay(DelayChannel_D, p_BDG->D.FireFirst, p_BDG->D.PulseWidth[0], p_BDG->D.OutputModulo, p_BDG->D.OutputOffset,
															p_BDG->D.GoSignal, p_BDG->D.Positive, p_BDG->D.Terminate, 
															p_BDG->D.Disconnect, p_BDG->D.OntoMsBus, p_BDG->D.InputPositive, DG_Number);
	if (p_BDG->D.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_D, &(p_BDG->D.DelayTime[0]), &(p_BDG->D.PulseWidth[0]),
															&(p_BDG->D.StepBack[0]), p_BDG->D.ListLength, DG_Number);	
	p_DelayGenerator->Set_G08_Delay(DelayChannel_E, p_BDG->E.FireFirst, p_BDG->E.PulseWidth[0], p_BDG->E.OutputModulo, p_BDG->E.OutputOffset,
															p_BDG->E.GoSignal, p_BDG->E.Positive, p_BDG->E.Terminate, 
															p_BDG->E.Disconnect, p_BDG->E.OntoMsBus, p_BDG->E.InputPositive, DG_Number);
	if (p_BDG->E.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_E, &(p_BDG->E.DelayTime[0]), &(p_BDG->E.PulseWidth[0]),
															&(p_BDG->E.StepBack[0]), p_BDG->E.ListLength, DG_Number);	
	p_DelayGenerator->Set_G08_Delay(DelayChannel_F, p_BDG->F.FireFirst, p_BDG->F.PulseWidth[0], p_BDG->F.OutputModulo, p_BDG->F.OutputOffset,
															p_BDG->F.GoSignal, p_BDG->F.Positive, p_BDG->F.Terminate, 
															p_BDG->F.Disconnect, p_BDG->F.OntoMsBus, p_BDG->F.InputPositive, DG_Number);
	if (p_BDG->F.ListLength > 1)
		p_DelayGenerator->Set_DelayList(DelayChannel_F, &(p_BDG->F.DelayTime[0]), &(p_BDG->F.PulseWidth[0]),
															&(p_BDG->F.StepBack[0]), p_BDG->F.ListLength, DG_Number);	


}

void CG0xData::SetDelayGenerators(CTypedPtrList<CPtrList, DG_Type*>& m_List)
{
	DG_Type* p_DG;
	DG_Type* p_SG;
	int Count = 0;
	EnterCriticalSection(p_DataAccess);
	POSITION pos = m_List.GetHeadPosition();
	POSITION pos1 = m_Show_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_List.GetNext(pos);
		p_SG = m_Show_List.GetNext(pos1);
		memcpy(p_SG, p_DG, sizeof(DG_Type));
		//p_DelayGenerator->Test_BME_G08(Count);
		p_DelayGenerator->SetDelayGenerator(&(p_DG->Control), Count);
		//TestLoadDelayGenerator(&(p_DG->Control), Count);
		Count++;
	}
	LeaveCriticalSection(p_DataAccess);
}

BOOL CG0xData::AllDelayGeneratorsDone(CTypedPtrList<CPtrList, DG_Type*>& m_List)
{
	int DG_Number,Count;
	unsigned long result = 0;
	BOOL AllDone = TRUE;
	EnterCriticalSection(p_DataAccess);
	Count = m_List.GetCount();
	for (DG_Number = 0; DG_Number < Count; DG_Number++)
	{
		result = p_DelayGenerator->Read_DG_Status(DG_Number);
		if ((result & 0x80) == 0)
			AllDone = FALSE;
	}
	LeaveCriticalSection(p_DataAccess);
	return AllDone;
}

void CG0xData::ResetEventCounter(int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	p_DelayGenerator->ResetEventCounter(DG_Number);
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::ResetOutputModuloCounters(int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	p_DelayGenerator->ResetOutputModuloCounters(DG_Number);
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::ResetAllOutputModuloCounters()
{
	EnterCriticalSection(p_DataAccess);
	p_DelayGenerator->ResetAllOutputModuloCounters();
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::ResetCounterAllCards(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList)
{
	EnterCriticalSection(p_DataAccess);
	p_DelayGenerator->ResetCounterAllCards(b_EventCounter, b_ModuloCounter, b_TimeList);
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::LoadAllCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList)
{
	DG_Type* p_DG;
	int Count = 0;
	EnterCriticalSection(p_DataAccess);
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (!p_DG->Master)
			p_DelayGenerator->LoadCardParameters(b_EventCounter, b_ModuloCounter, b_TimeList, Count);
		Count++;
	}
	Count = 0;
	pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		if (p_DG->Master)
			p_DelayGenerator->LoadCardParameters(b_EventCounter, b_ModuloCounter, b_TimeList, Count);
		Count++;
	}
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::JumpStartAllLists()
{
	EnterCriticalSection(p_DataAccess);
	p_DelayGenerator->JumpStartAllLists();
	LeaveCriticalSection(p_DataAccess);
}

unsigned long CG0xData::ReadTriggerCounter(int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	unsigned long result = 0;
	//TestCounter = 5372;
	//TestCounter++;
	//result = TestCounter;
	result = p_DelayGenerator->ReadTriggerCounter(DG_Number);
	LeaveCriticalSection(p_DataAccess);
	return result;
}

void CG0xData::Read64BitTriggerCounter(_int64* p_result, int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	unsigned long result = 0;
	//TestCounter = 5372;
	//TestCounter++;
	//result = TestCounter;
	p_DelayGenerator->Read64BitTriggerCounter(p_result, DG_Number);
	LeaveCriticalSection(p_DataAccess);
}

void CG0xData::ReadFrequencyCounter(double* p_result, int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	unsigned long result = 0;
	//TestCounter = 5372;
	//TestCounter++;
	//result = TestCounter;
	p_DelayGenerator->ReadFrequencyCounter(p_result, DG_Number);
	LeaveCriticalSection(p_DataAccess);
}

unsigned long CG0xData::Read_DG_Status(int DG_Number)
{
	EnterCriticalSection(p_DataAccess);
	unsigned long result = 0;
	result = p_DelayGenerator->Read_DG_Status(DG_Number);
	LeaveCriticalSection(p_DataAccess);
	return result;
}

long CG0xData::AddEthernetDelayGenerators(long* p_Error, char* p_IpAddr)
{
	BOOL ClassCreated = FALSE;
	EnterCriticalSection(p_DataAccess);
	if (p_DelayGenerator == NULL)
	{
		ClassCreated = TRUE;
		p_DelayGenerator = new CDG_DLL;
	}
	long NoDelgen = p_DelayGenerator->AddEthernetDelayGenerators(p_Error, p_IpAddr);
	if ((NoDelgen <= 0) && (ClassCreated))
	{
		delete p_DelayGenerator;
		p_DelayGenerator = NULL;
	}
	LeaveCriticalSection(p_DataAccess);
	return NoDelgen;
}

long CG0xData::DetectPciDelayGenerators(long* p_Error)
{
	EnterCriticalSection(p_DataAccess);
	if (p_DelayGenerator != NULL)
	{
		p_DelayGenerator->Release_DG_Data();
		delete p_DelayGenerator;
	}
	p_DelayGenerator = new CDG_DLL;
	long NoDelgen = p_DelayGenerator->DetectPciDelayGenerators(p_Error);
	if (NoDelgen <= 0)
	{
		delete p_DelayGenerator;
		p_DelayGenerator = NULL;
	}
	LeaveCriticalSection(p_DataAccess);
	return NoDelgen;
}

long CG0xData::GetEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																			 BOOL* p_Master, long DG_Number)
{
	long result;
	EnterCriticalSection(p_DataAccess);
	if (p_DelayGenerator != NULL)
		result = p_DelayGenerator->GetEthernetDelayGenerator(p_DG_Product, p_IpAddr, p_BusNumber, p_SlotNumber, p_Master, DG_Number);
	LeaveCriticalSection(p_DataAccess);
	return result;
}

long CG0xData::GetUnconnectedEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																							 long* p_LineMaster, long DG_Number)
{
	long result;
	EnterCriticalSection(p_DataAccess);
	if (p_DelayGenerator != NULL)
		result = p_DelayGenerator->GetUnconnectedEthernetDelayGenerator(p_DG_Product, p_IpAddr, p_BusNumber, p_SlotNumber, 
																																									p_LineMaster, DG_Number);
	LeaveCriticalSection(p_DataAccess);
	return result;
}


void CG0xData::InitializeDelayGenerators()
{
	char CalibrationPath[200];
	unsigned long Master_MS_Bus;
	strcpy(CalibrationPath, (LPCTSTR)FileOptions.CalibrationFilePath);
	EnterCriticalSection(p_DataAccess);
	TestCounter = 0;
	if (p_DelayGenerator != NULL)
	{
		p_DelayGenerator->Release_DG_Data();
		delete p_DelayGenerator;
	}
	p_DelayGenerator = new CDG_DLL;
	int Count = m_DG_List.GetCount();
	p_DelayGenerator->Reserve_DG_Data(Count);
	int* p_module = new int[max(2, Count)];
	DG_Type* p_DG;
	Count = 0;
	POSITION pos = m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_DG_List.GetNext(pos);
		p_DelayGenerator->Initialize_Ethernet_DG_BME(p_DG->BusNumber, p_DG->BaseAddress, &(p_DG->ip_address[0]), p_DG->Product, Count);
		if (p_DG->Master)
		{
			//AfxMessageBox("Start test",MB_OK,0);
			//p_DelayGenerator->Test_BME_G02(Count);
			//AfxMessageBox("End test",MB_OK,0);
			*(p_module + Count) = MasterModule;
			Master_MS_Bus = p_DG->Control.DT.MS_Bus; 
		}
		else
		{
			*(p_module + Count) = SlaveModule;
			if (p_DG->Product == BME_SG08P2)
			{
				p_DG->Control.DT.MS_Bus |= (Master_MS_Bus & 0xF2);
				p_DG->Control.DT.MS_Bus &= (Master_MS_Bus | ~0xF2);
			}
		}
		Count++;
	}
	//if (b_CalibrateTiming)
	if (FALSE)
	{
		Count = 0;
		//pos = m_DG_List.GetHeadPosition();
		//while (pos != NULL)
		//{
			//p_DG = m_DG_List.GetNext(pos);
			//p_DelayGenerator->SetDelayGenerator(&(p_DG->Control), Count);
			//Count++;
		//}
		p_DelayGenerator->Set_CalibrationForAll(m_CalibrationLevel);
		p_DelayGenerator->ReadPathCalibrationConstants(CalibrationPath);
		//p_DelayGenerator->CalibratePathGroup(p_module, CalibrationPath);
		p_DelayGenerator->CalibrateModule(Count);
		//p_DelayGenerator->Test_BME_G08(Count);
	}
	if (b_CalibrateTiming)
	{
		Count = 0;
		pos = m_DG_List.GetHeadPosition();
		while (pos != NULL)
		{
			p_DG = m_DG_List.GetNext(pos);
			p_DelayGenerator->SetDelayGenerator(&(p_DG->Control), Count);
			Count++;
		}
		p_DelayGenerator->Set_CalibrationForAll(m_CalibrationLevel);
		p_DelayGenerator->ReadPathCalibrationConstants(CalibrationPath);
		p_DelayGenerator->CalibratePathGroup(p_module, CalibrationPath);
	}
	LeaveCriticalSection(p_DataAccess);
	delete []p_module;
	b_DelayGeneratorsInitialized = TRUE;
	//SetDelayGenerators(m_DG_List);
}

double CG0xData::RoundRepCounter(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->RoundRepCounter(&result, InValue, DG_Number);
	return result;
}

double CG0xData::RoundT0(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->RoundT0(&result, InValue, DG_Number);
	return result;
}

double CG0xData::RoundWidth(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->RoundWidth(&result, InValue, DG_Number);
	return result;
}

double CG0xData::RoundGateDelay(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->RoundGateDelay(&result, InValue, DG_Number);
	return result;
}

double CG0xData::RoundSetBack(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->RoundSetBack(&result, InValue, DG_Number);
	return result;
}

double CG0xData::DelayLimit(double InValue, int DG_Number)
{
	double result;
	p_DelayGenerator->DelayLimit(&result, InValue, DG_Number);
	return result;
}

CString CG0xData::AllowedParameter(LPCTSTR istr) 
{
	CListRout lr;
	CString jstr = istr;
	lr.TrimString(jstr);
	CString result = _T("");
	if ((jstr[0] == 'x') || (jstr[0] == 'X'))
	{
		jstr = jstr.Right(jstr.GetLength() - 1);
		if (lr.Numeric(jstr))
		{
			int Param = RoundInt(atof(jstr));
			if ((Param > 0) && (Param <= ParameterList.NoParameters))
				result.Format(" X%d", Param);
		}
	}
	else
	{
		if ((jstr[0] == 'y') || (jstr[0] == 'Y'))
		{
			jstr = jstr.Right(jstr.GetLength() - 1);
			if (lr.Numeric(jstr))
			{
				int Param = RoundInt(atof(jstr));
				if ((Param > 0) && (Param <= FpgaMemoryList.NoParameters))
					result.Format(" Y%d", Param);
			}
		}
		else
			result = istr;
	}
	return result;
}


void CG0xData::ResetInternalData()
{
	p_ClientDC = NULL;
	ExperimentalDataSize.cx = 0;
	ExperimentalDataSize.cy = 0;
	b_ExperimentalSetupAccess = 0;
	b_CalibrateTiming = FALSE;
	m_CalibrationLevel = CalibrateOffset;
	b_ContextHelpActive = FALSE;
	p_DelayGenerator = NULL;
	b_DelayGeneratorsActive = FALSE;
	b_DelayGeneratorsInitialized = FALSE;
	b_RequestZeroModulo = FALSE;
	b_RequestJumpStart = FALSE;
	m_ActiveIndex = 0;
	m_XParameter.RemoveAll();
	m_FpgaMemory.RemoveAll();
	ResetTimeSequence(m_TimeSequence);
	ParameterList.p_Value = NULL;
	ParameterList.p_Loc = NULL;
	ParameterList.NoParameters = 0;
	ParameterList.ListLength = 0;
	FpgaMemoryList.p_Value = NULL;
	FpgaMemoryList.p_Loc = NULL;
	FpgaMemoryList.NoParameters = 0;
	FpgaMemoryList.ListLength = 0;
	p_OpInfo = NULL;
}

void CG0xData::ResetData()
{
	ResetInternalData();
	m_FileName = _T("");
	m_FileTitle = _T("");
	m_FileTime = NULL;
}

CString CG0xData::GetFileTime()
{
	if (m_FileTime == NULL)
		return _T("");
	struct tm *newtime;
  newtime = localtime( &m_FileTime ); 
	CString str,jstr;
	str = asctime(newtime);
	jstr = _T("");
	int i1;
	for (i1 = 0; i1 < 24; i1++)
		jstr += str[i1];
	return jstr;
}

CSize CG0xData::WriteExperimentalSetup()
{
	CSize result;
	CDelgenData dd;
	b_ExperimentalSetupAccess++;
	if ((b_ExperimentalSetupAccess <= 1) && (p_ClientDC != NULL))
	{
	  ExperimentalDataSize = dd.WriteDelgenSetup(this, p_ClientDC, ScrollPosition, ExperimentalDataSize);
		result = ExperimentalDataSize;
	}
	else
	{
		result.cx = 0;
		result.cy = 0;
	}
	b_ExperimentalSetupAccess--;
	return result;
}

void CG0xData::InitializeDG_List(CTypedPtrList<CPtrList, DG_Type*>& DG_List)
{
	POSITION pos1 = DG_List.GetHeadPosition();
	while (pos1 != NULL)
		delete DG_List.GetNext(pos1);
	DG_List.RemoveAll();
}

void CG0xData::WriteDG_List( CArchive& myFile, CTypedPtrList<CPtrList, DG_Type*>& DG_List)
{
	DG_Type* p_DG;
	nVersion = CurrentDG_FileVersion;
	myFile.Write(&nVersion, 4);
	int L1 = DG_List.GetCount();
	myFile.Write(&L1, 4);
	POSITION pos1 = DG_List.GetHeadPosition();
	while (pos1 != NULL)
	{
		p_DG = DG_List.GetNext(pos1);
		myFile.Write(p_DG, sizeof(DG_Type));
	}
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, Old_DG_Type* p_Old_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl(&(p_DG->Control), &(p_Old_DG->Control));
	//memcpy(&(p_DG->Control), &(p_Old_DG->Control), sizeof(DG_BME_Control));
	CopyLocation(&(p_DG->VarLoc), &(p_Old_DG->VarLoc));
	memcpy(&(p_DG->DG_Name), &(p_Old_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_Old_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_Old_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_Old_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_Old_DG->ReadTriggers;
	p_DG->Master = p_Old_DG->Master;
	p_DG->BaseAddress = p_Old_DG->BaseAddress;
	p_DG->Product = p_Old_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V1_Type* p_V1_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl(&(p_DG->Control), &(p_V1_DG->Control));
	//memcpy(&(p_DG->Control), &(p_V1_DG->Control), sizeof(DG_BME_Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V1_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V1_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V1_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V1_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V1_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V1_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V1_DG->ReadTriggers;
	p_DG->Master = p_V1_DG->Master;
	p_DG->BaseAddress = p_V1_DG->BaseAddress;
	p_DG->Product = p_V1_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V2_Type* p_V2_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl(&(p_DG->Control), &(p_V2_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V2_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V2_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V2_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V2_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V2_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V2_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V2_DG->ReadTriggers;
	p_DG->Master = p_V2_DG->Master;
	p_DG->BaseAddress = p_V2_DG->BaseAddress;
	p_DG->Product = p_V2_DG->Product;
}


void CG0xData::CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV1Type* p_V1_A)
{
	ResetArithmetic(*p_A);
	memcpy(&(p_A->T0), &(p_V1_A->T0), sizeof(ChannelArithmeticV1Type));
	memcpy(&(p_A->A), &(p_V1_A->A), sizeof(ChannelArithmeticV1Type));
	memcpy(&(p_A->B), &(p_V1_A->B), sizeof(ChannelArithmeticV1Type));
}

void CG0xData::CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV2Type* p_V2_A)
{
	ResetArithmetic(*p_A);
	memcpy(&(p_A->T0), &(p_V2_A->T0), sizeof(ChannelArithmeticV2Type));
	memcpy(&(p_A->A), &(p_V2_A->A), sizeof(ChannelArithmeticV2Type));
	memcpy(&(p_A->B), &(p_V2_A->B), sizeof(ChannelArithmeticV2Type));
}

void CG0xData::CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV3Type* p_V3_A)
{
	ResetArithmetic(*p_A);
	memcpy(&(p_A->T0), &(p_V3_A->T0), sizeof(ChannelArithmeticV3Type));
	memcpy(&(p_A->A), &(p_V3_A->A), sizeof(ChannelArithmeticV3Type));
	memcpy(&(p_A->B), &(p_V3_A->B), sizeof(ChannelArithmeticV3Type));
}

void CG0xData::CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV4Type* p_V4_A)
{
	ResetArithmetic(*p_A);
	memcpy(&(p_A->ForceTrigger), &(p_V4_A->ForceTrigger), (64 * sizeof(char)));
	memcpy(&(p_A->RepCounter), &(p_V4_A->RepCounter), (64 * sizeof(char)));
	memcpy(&(p_A->T0), &(p_V4_A->T0), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->A), &(p_V4_A->A), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->B), &(p_V4_A->B), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->C), &(p_V4_A->C), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->D), &(p_V4_A->D), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->E), &(p_V4_A->E), sizeof(ChannelArithmeticType));
	memcpy(&(p_A->F), &(p_V4_A->F), sizeof(ChannelArithmeticType));
}

void CG0xData::CopyLocation(VariableLocationType* p_L, VariableLocationV1Type* p_V1_L)
{
	ResetLocation(*p_L);
	memcpy(&(p_L->T0), &(p_V1_L->T0), sizeof(ChannelLocationV1Type));
	memcpy(&(p_L->A), &(p_V1_L->A), sizeof(ChannelLocationV1Type));
	memcpy(&(p_L->B), &(p_V1_L->B), sizeof(ChannelLocationV1Type));
}

void CG0xData::CopyLocation(VariableLocationType* p_L, VariableLocationV2Type* p_V2_L)
{
	ResetLocation(*p_L);
	memcpy(&(p_L->T0), &(p_V2_L->T0), sizeof(ChannelLocationV2Type));
	memcpy(&(p_L->A), &(p_V2_L->A), sizeof(ChannelLocationV2Type));
	memcpy(&(p_L->B), &(p_V2_L->B), sizeof(ChannelLocationV2Type));
}

void CG0xData::CopyLocation(VariableLocationType* p_L, VariableLocationV3Type* p_V3_L)
{
	ResetLocation(*p_L);
	memcpy(&(p_L->T0), &(p_V3_L->T0), sizeof(ChannelLocationV3Type));
	memcpy(&(p_L->A), &(p_V3_L->A), sizeof(ChannelLocationV3Type));
	memcpy(&(p_L->B), &(p_V3_L->B), sizeof(ChannelLocationV3Type));
}

void CG0xData::CopyLocation(VariableLocationType* p_L, VariableLocationV4Type* p_V4_L)
{
	ResetLocation(*p_L);
	p_L->ForceTrigger = p_V4_L->ForceTrigger;
	p_L->RepCounter = p_V4_L->RepCounter;
	memcpy(&(p_L->T0), &(p_V4_L->T0), sizeof(ChannelLocationType));
	memcpy(&(p_L->A), &(p_V4_L->A), sizeof(ChannelLocationType));
	memcpy(&(p_L->B), &(p_V4_L->B), sizeof(ChannelLocationType));
	memcpy(&(p_L->C), &(p_V4_L->C), sizeof(ChannelLocationType));
	memcpy(&(p_L->D), &(p_V4_L->D), sizeof(ChannelLocationType));
	memcpy(&(p_L->E), &(p_V4_L->E), sizeof(ChannelLocationType));
	memcpy(&(p_L->F), &(p_V4_L->F), sizeof(ChannelLocationType));
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V3_Type* p_V3_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl_V2(&(p_DG->Control), &(p_V3_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V3_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V3_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V3_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V3_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V3_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V3_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V3_DG->ReadTriggers;
	p_DG->Master = p_V3_DG->Master;
	p_DG->BaseAddress = p_V3_DG->BaseAddress;
	p_DG->Product = p_V3_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V4_Type* p_V4_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl_V3(&(p_DG->Control), &(p_V4_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V4_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V4_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V4_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V4_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V4_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V4_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V4_DG->ReadTriggers;
	p_DG->Master = p_V4_DG->Master;
	p_DG->BaseAddress = p_V4_DG->BaseAddress;
	p_DG->Product = p_V4_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V5_Type* p_V5_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl_V3(&(p_DG->Control), &(p_V5_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V5_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V5_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V5_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V5_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V5_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V5_DG->B_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V5_DG->ReadTriggers;
	p_DG->Master = p_V5_DG->Master;
	p_DG->BaseAddress = p_V5_DG->BaseAddress;
	p_DG->BusNumber = p_V5_DG->BusNumber;
	p_DG->SystemNumber = p_V5_DG->SystemNumber;
	p_DG->Product = p_V5_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V6_Type* p_V6_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl_V4(&(p_DG->Control), &(p_V6_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V6_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V6_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V6_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V6_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V6_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V6_DG->B_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->C_Name), &(p_V6_DG->C_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->D_Name), &(p_V6_DG->D_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->E_Name), &(p_V6_DG->E_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->F_Name), &(p_V6_DG->F_Name), (32 * sizeof(char)));
	p_DG->ReadTriggers = p_V6_DG->ReadTriggers;
	p_DG->Master = p_V6_DG->Master;
	p_DG->BaseAddress = p_V6_DG->BaseAddress;
	p_DG->BusNumber = p_V6_DG->BusNumber;
	p_DG->SystemNumber = p_V6_DG->SystemNumber;
	p_DG->Product = p_V6_DG->Product;
}

void CG0xData::CopyDG_Element(DG_Type* p_DG, DG_V7_Type* p_V7_DG)
{
	CDG_DLL dll;
	ResetDG_Element(p_DG);
	dll.CopyControl_V4(&(p_DG->Control), &(p_V7_DG->Control));

	CopyLocation(&(p_DG->VarLoc), &(p_V7_DG->VarLoc));
	CopyArithmetic(&(p_DG->VarEqu), &(p_V7_DG->VarEqu));

	memcpy(&(p_DG->DG_Name), &(p_V7_DG->DG_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->T0_Name), &(p_V7_DG->T0_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->A_Name), &(p_V7_DG->A_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->B_Name), &(p_V7_DG->B_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->C_Name), &(p_V7_DG->C_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->D_Name), &(p_V7_DG->D_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->E_Name), &(p_V7_DG->E_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->F_Name), &(p_V7_DG->F_Name), (32 * sizeof(char)));
	memcpy(&(p_DG->ip_address), &(p_V7_DG->ip_address), (40 * sizeof(char)));
	p_DG->ReadTriggers = p_V7_DG->ReadTriggers;
	p_DG->Master = p_V7_DG->Master;
	p_DG->BaseAddress = p_V7_DG->BaseAddress;
	p_DG->BusNumber = p_V7_DG->BusNumber;
	p_DG->SystemNumber = p_V7_DG->SystemNumber;
	p_DG->Product = p_V7_DG->Product;
}

void CG0xData::ReadDG_List( CArchive& myFile, CTypedPtrList<CPtrList, DG_Type*>& DG_List)
{
	InitializeDG_List(DG_List);
	DG_Type* p_DG;
	Old_DG_Type* p_Old_DG = NULL;
	DG_V1_Type* p_V1_DG = NULL;
	DG_V2_Type* p_V2_DG = NULL;
	DG_V3_Type* p_V3_DG = NULL;
	DG_V4_Type* p_V4_DG = NULL;
	DG_V5_Type* p_V5_DG = NULL;
	DG_V6_Type* p_V6_DG = NULL;
	DG_V7_Type* p_V7_DG = NULL;
	int L1,i1;
	myFile.Read(&nVersion, 4);
	myFile.Read(&L1, 4);
	for (i1 = 0; i1 < L1; i1++) 
	{
		p_DG = new DG_Type;
		switch (nVersion)
		{
		case 0:
			if (p_Old_DG == NULL)
				p_Old_DG = new Old_DG_Type;
			myFile.Read(p_Old_DG, sizeof(Old_DG_Type));
			CopyDG_Element(p_DG, p_Old_DG);
			break;
		case 1:
			if (p_V1_DG == NULL)
				p_V1_DG = new DG_V1_Type;
			myFile.Read(p_V1_DG, sizeof(DG_V1_Type));
			CopyDG_Element(p_DG, p_V1_DG);
			break;
		case 2:
			if (p_V2_DG == NULL)
				p_V2_DG = new DG_V2_Type;
			myFile.Read(p_V2_DG, sizeof(DG_V2_Type));
			CopyDG_Element(p_DG, p_V2_DG);
			break;
		case 3:
			if (p_V3_DG == NULL)
				p_V3_DG = new DG_V3_Type;
			myFile.Read(p_V3_DG, sizeof(DG_V3_Type));
			CopyDG_Element(p_DG, p_V3_DG);
			break;
		case 4:
			if (p_V4_DG == NULL)
				p_V4_DG = new DG_V4_Type;
			myFile.Read(p_V4_DG, sizeof(DG_V4_Type));
			CopyDG_Element(p_DG, p_V4_DG);
			break;
		case 5:
			if (p_V5_DG == NULL)
				p_V5_DG = new DG_V5_Type;
			myFile.Read(p_V5_DG, sizeof(DG_V5_Type));
			CopyDG_Element(p_DG, p_V5_DG);
			break;
		case 6:
			if (p_V6_DG == NULL)
				p_V6_DG = new DG_V6_Type;
			myFile.Read(p_V6_DG, sizeof(DG_V6_Type));
			CopyDG_Element(p_DG, p_V6_DG);
			break;
		case 7:
			if (p_V7_DG == NULL)
				p_V7_DG = new DG_V7_Type;
			myFile.Read(p_V7_DG, sizeof(DG_V7_Type));
			CopyDG_Element(p_DG, p_V7_DG);
			break;
		default:
			myFile.Read(p_DG, sizeof(DG_Type));
			break;
		}
		DG_List.AddTail(p_DG);
	}
	if (p_Old_DG != NULL)
		delete p_Old_DG;
	if (p_V1_DG != NULL)
		delete p_V1_DG;
	if (p_V2_DG != NULL)
		delete p_V2_DG;
	if (p_V3_DG != NULL)
		delete p_V3_DG;
	if (p_V4_DG != NULL)
		delete p_V4_DG;
	if (p_V5_DG != NULL)
		delete p_V5_DG;
	if (p_V6_DG != NULL)
		delete p_V6_DG;
	if (p_V7_DG != NULL)
		delete p_V7_DG;
}

void CG0xData::CopyDG_List(CTypedPtrList<CPtrList, DG_Type*>& out_List,
													 CTypedPtrList<CPtrList, DG_Type*>& in_List)
{
	InitializeDG_List(out_List);
	DG_Type* p_in;
	DG_Type* p_out;
	POSITION pos1 = in_List.GetHeadPosition();
	while (pos1 != NULL)
	{
		p_in = in_List.GetNext(pos1);
		p_out = new DG_Type;
		memcpy(p_out, p_in, sizeof(DG_Type));
		out_List.AddTail(p_out);
	}
}

void CG0xData::ReadTimeSequence(XParameterType& vct)
{
	memcpy(&vct, &m_TimeSequence, sizeof(XParameterType));
	return;
}

int CG0xData::WriteFpgaMemory(CStringArray& csa)
{
	CListRout lr;
	int Lines = lr.CopyStringArray(m_FpgaMemory, csa);
	LoadParameterList(FpgaMemoryList, m_FpgaMemory);
	return Lines;
}

int CG0xData::ReadFpgaMemory(CStringArray& csa)
{
	CListRout lr;
	int Lines = lr.CopyStringArray(csa, m_FpgaMemory);
	return (Lines);
}

int CG0xData::WriteXParameter(CStringArray& csa, XParameterType& vct)
{
	CListRout lr;
	int Lines = lr.CopyStringArray(m_XParameter, csa);
	LoadParameterList(ParameterList, m_XParameter);
	memcpy(&m_TimeSequence, &vct, sizeof(XParameterType));
	return Lines;
}

int CG0xData::ReadXParameter(CStringArray& csa, XParameterType& vct)
{
	CListRout lr;
	int Lines = lr.CopyStringArray(csa, m_XParameter);
	memcpy(&vct, &m_TimeSequence, sizeof(XParameterType));
	return (Lines);
}

BOOL CG0xData::LoadParameterList(ParameterListType& plt, CStringArray& csa)
{
	if (plt.p_Value != NULL)
		delete []plt.p_Value;
	plt.p_Value = NULL;
	if (plt.p_Loc != NULL)
		delete []plt.p_Loc;
	plt.p_Loc = NULL;
	plt.NoParameters = 0;
	plt.ListLength = csa.GetSize();
	if (plt.ListLength > 0)
	{
		CListRout lr;
		plt.NoParameters = lr.GetNumberParameters(csa);
		int Count = plt.NoParameters * plt.ListLength;
		plt.p_Value = new double[max(2, Count)];
		plt.p_Loc = new int[max(2, Count)];
		lr.ExtractParameterArray(plt.p_Value, csa, plt.NoParameters, plt.p_Loc);
		return TRUE;
	}
	return FALSE;
}

void CG0xData::ResetTimeSequence(XParameterType& vct)
{
	int i1;
	for (i1 = 0; i1 < MaxTSParameter; i1++)
	{
		vct.Flag[i1] = FALSE;
		vct.IntNumber[i1] = 0;
	}
	vct.MilliSecondsPerStep = 1000;
}

void CG0xData::ResetChannelLocation(ChannelLocationType& ChanLoc)
{
	ChanLoc.FireFirst = -1;
	ChanLoc.SetBack = -1;
	ChanLoc.PulseWidth = -1;
	ChanLoc.OutputModulo = -1;
	ChanLoc.OutputOffset = -1;
	ChanLoc.StepBack = -1;
}

void CG0xData::ResetLocation(VariableLocationType& VarLoc)
{
	ResetChannelLocation(VarLoc.T0);
	ResetChannelLocation(VarLoc.A);
	ResetChannelLocation(VarLoc.B);
	ResetChannelLocation(VarLoc.C);
	ResetChannelLocation(VarLoc.D);
	ResetChannelLocation(VarLoc.E);
	ResetChannelLocation(VarLoc.F);
	VarLoc.ForceTrigger = -1;
	VarLoc.RepCounter = -1;
	VarLoc.RepSecondary = -1;
}

void CG0xData::ResetChannelArithmetic(ChannelArithmeticType& ChanEqu)
{
	memset(&(ChanEqu.FireFirst), 0, (64 * sizeof(char)));
	memset(&(ChanEqu.SetBack), 0, (64 * sizeof(char)));
	memset(&(ChanEqu.PulseWidth), 0, (64 * sizeof(char)));
	memset(&(ChanEqu.OutputModulo), 0, (64 * sizeof(char)));
	memset(&(ChanEqu.OutputOffset), 0, (64 * sizeof(char)));
	memset(&(ChanEqu.StepBack), 0, (64 * sizeof(char)));
}

void CG0xData::ResetArithmetic(VariableArithmeticType& VarEqu)
{
	memset(&(VarEqu.ForceTrigger), 0, (64 * sizeof(char)));
	memset(&(VarEqu.RepCounter), 0, (64 * sizeof(char)));
	memset(&(VarEqu.RepSecondary), 0, (64 * sizeof(char)));
	ResetChannelArithmetic(VarEqu.T0);
	ResetChannelArithmetic(VarEqu.A);
	ResetChannelArithmetic(VarEqu.B);
	ResetChannelArithmetic(VarEqu.C);
	ResetChannelArithmetic(VarEqu.D);
	ResetChannelArithmetic(VarEqu.E);
	ResetChannelArithmetic(VarEqu.F);
}

void CG0xData::ResetDG_Element(DG_Type* p_DG)
{
	ResetLocation(p_DG->VarLoc);
	ResetArithmetic(p_DG->VarEqu);
	memset(&(p_DG->DG_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->T0_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->A_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->B_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->C_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->D_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->E_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->F_Name), 0, (32 * sizeof(char)));
	memset(&(p_DG->ip_address), 0, (40 * sizeof(char)));
	p_DG->ReadTriggers = FALSE;
	p_DG->Master = FALSE;
	p_DG->BusNumber = -1;
	p_DG->SystemNumber = -1;
	p_DG->BaseAddress = -1;
	p_DG->Product = -1;
	CDG_DLL dll;
	dll.ResetControl(&(p_DG->Control));
}
