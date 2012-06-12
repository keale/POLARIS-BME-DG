/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Graphics routines
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          Window NT
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    12. February 2001
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#include "stdafx.h"

#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "DelgenControl.h"
#include "..\Spectra_BME\ListRout.h"
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MaxReplacements 30

CDelgenControl::CDelgenControl(CWnd* pParent)
{
	p_ParentWindow = pParent;
	b_RemoveControlThread = FALSE;
	b_RequestRemoveControlThread = FALSE;
	b_ControlThreadActive = FALSE;
	b_InitializeControl = FALSE;
	b_ResetWhenDone = FALSE;
	SweepActive = FALSE;
	FpgaMemoryActive = FALSE;
	SubCycleCount = 0;
}
  

CDelgenControl::~CDelgenControl()
{
	p_G0xData->InitializeDG_List(DG_List);
}

void CDelgenControl::UpdateDataPointer(CG0xData* p_G0xDat)
{
	p_G0xData = p_G0xDat;
}

void CDelgenControl::ResetEventCounters()
{
	DG_Type* p_DG;
	POSITION pos;
	int Count = 0;
	pos = DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = DG_List.GetNext(pos);
		if ((p_DG->Master) && (p_DG->ReadTriggers))
			p_G0xData->ResetEventCounter(Count);
		Count++;
	}
}

BOOL CDelgenControl::ReadTriggerCounters()
{
	_int64 TestCount;
	DG_Type* p_DG;
	POSITION pos;
	int Count = 0;
	BOOL NewValue = FALSE;
	pos = DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = DG_List.GetNext(pos);
		if ((p_DG->Master) && (p_DG->ReadTriggers))
		{
			p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
			if (TestCount != 0xFFFFFFFF)
				TriggerCount = TestCount;
			(p_G0xData->p_OpInfo + Count)->Trigger64Events = TriggerCount;
			NewValue = TRUE;
			//TestCount = p_G0xData->Read_DG_Status(Count);
			//(p_G0xData->p_OpInfo + Count)->DG_Status = TestCount;
		}
		Count++;
	}
	return NewValue;
}

void CDelgenControl::SetDelayGenerators(BOOL ResetCounters)
{
	unsigned long Action;
	BOOL b_EventCounter = FALSE;
	BOOL b_ModuloCounter = FALSE;
	BOOL b_TimeList = FALSE;
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		Action = p_G0xData->ModifyAction(DG_List);
		if (ResetCounters)
			Action |= 0x2;
	}
	else
		Action = 0x7;
	if ((Action & 0x1) != 0)
	{
		if (p_G0xData->b_DelayGeneratorsActive)
			p_G0xData->DeactivateDelayGenerators();
	}
	if (!p_G0xData->b_DelayGeneratorsInitialized)
		p_G0xData->InitializeDelayGenerators();
	p_G0xData->SetDelayGenerators(DG_List);
	if ((Action & 0x2) != 0)
		b_EventCounter = TRUE;
	if ((Action & 0x4) != 0)
		b_ModuloCounter = TRUE;
	if ((Action & 0x8) != 0)
		b_TimeList = TRUE;
	p_G0xData->LoadAllCardParameters(b_EventCounter, b_ModuloCounter, b_TimeList);
	if (!p_G0xData->b_DelayGeneratorsActive)
		p_G0xData->ActivateDelayGenerators();
}


int CDelgenControl::GetNextPosition(int PresentPosition)
{
	int NextPosition = PresentPosition;
	if (TimeSequence.m_SubcycleLimit)
	{
		if (SubCycleCount >= TimeSequence.MaxSubcycles)
		{
			SweepActive = FALSE;
			b_RequestRemoveControlThread = TRUE;
			return NextPosition;
		}
	}
	if (MovingUp)
	{
		NextPosition++;
		if (NextPosition >= p_G0xData->ParameterList.ListLength)
		{
			if (TimeSequence.m_BothDirection)
			{
				NextPosition = p_G0xData->ParameterList.ListLength - 1;
				MovingUp = FALSE;
				if ((TimeSequence.m_Once) && (TimeSequence.m_Downwards))
				{
					SweepActive = FALSE;
					b_RequestRemoveControlThread = TRUE;
				}
			}
			else
			{
				NextPosition = 0;
				if (TimeSequence.m_Once)
				{
					SweepActive = FALSE;
					b_RequestRemoveControlThread = TRUE;
				}
			}
		}
	}
	else
	{
		NextPosition--;
		if (NextPosition < 0)
		{
			if (TimeSequence.m_BothDirection)
			{
				NextPosition = 0;
				MovingUp = TRUE;
				if ((TimeSequence.m_Once) && (TimeSequence.m_Upwards))
				{
					SweepActive = FALSE;
					b_RequestRemoveControlThread = TRUE;
				}
			}
			else
			{
				NextPosition = p_G0xData->ParameterList.ListLength - 1;
				if (TimeSequence.m_Once)
				{
					SweepActive = FALSE;
					b_RequestRemoveControlThread = TRUE;
				}
			}
		}
	}
	return NextPosition;
}

int CDelgenControl::TimeDifference(struct _timeb& NextTime, struct _timeb& ThisTime)
{
	int seconds = NextTime.time - ThisTime.time;
	int millisec = NextTime.millitm - ThisTime.millitm;
	millisec += (seconds * 1000);
	return millisec;
}

DWORD CDelgenControl::CalculateWait(struct _timeb& NextTime)
{
	int MilliDiff = 1000;
	if (b_RequestRemoveControlThread)
		MilliDiff = 100;
	else
	{
		if (SweepActive)
		{
			struct _timeb ThisTime;
			_ftime(&ThisTime);
			MilliDiff = TimeDifference(NextTime, ThisTime);
			MilliDiff = max(0, MilliDiff);
			while (MilliDiff > 2000)
				MilliDiff /= 2;
		}
	}
	return (DWORD)MilliDiff;
}

void CDelgenControl::AddTime(struct _timeb& NextTime, struct _timeb& ThisTime, int MilliSeconds)
{
  struct _timeb MemTime;
	int seconds = MilliSeconds / 1000;
	memcpy(&MemTime, &ThisTime, sizeof(_timeb));
	MemTime.time += seconds;
	MemTime.millitm += (MilliSeconds - 1000 * seconds);
	while (MemTime.millitm >= 1000)
	{
		MemTime.time++;
		MemTime.millitm -= 1000;
	}
	memcpy(&NextTime, &MemTime, sizeof(_timeb));
}

void CDelgenControl::GetNextTime(struct _timeb& NextTime, struct _timeb& ThisTime)
{
	AddTime(NextTime, ThisTime, TimeSequence.MilliSecondsPerStep);
}

void CDelgenControl::ResetChannelVariables(ChannelStringType& ChanStr)
{
	ChanStr.FireFirst = _T("");
	ChanStr.PulseWidth = _T("");
	ChanStr.StepBack = _T("");
	ChanStr.SetBack = _T("");
	ChanStr.PulseWidth = _T("");
	ChanStr.OutputModulo = _T("");
	ChanStr.OutputOffset = _T("");
}

void CDelgenControl::ResetVariableString(VariableStringType* p_Mat)
{
	ResetChannelVariables(p_Mat->T0);
	ResetChannelVariables(p_Mat->A);
	ResetChannelVariables(p_Mat->B);
	ResetChannelVariables(p_Mat->C);
	ResetChannelVariables(p_Mat->D);
	ResetChannelVariables(p_Mat->E);
	ResetChannelVariables(p_Mat->F);
	p_Mat->RepCounter = _T("");
	p_Mat->ForceTrigger = _T("");
}

CString CDelgenControl::ExpandString(CString& ExpStr, int DelgenNo, VariableStringType* p_VarMat, 
																		double* p_Val, double* p_Mem, int FpgaPosition, 
																		CTypedPtrList<CPtrList, DG_Type*>& m_List, TCHAR Cvar)
{
	CListRout lr;
	DG_Type* p_RD;
	VariableStringType* p_RM;
	ChannelLocationType* p_CL;
	ChannelStringType* p_CS;
	DelayChannelData* p_DC;
	CString jstr,kstr,lstr;
	CString mstr = _T("aAbBcCdDeEfFtTpPrRxXyY");
	int ivar,npos,CardNo,ReadPosition;
	double value;
	BOOL StringFound;
	TCHAR tch,c1,c2;
	TCHAR CV,Chan;
	POSITION CardPos;
	int NoDelgen = m_List.GetCount();
	int ReplaceCount = 0;
	int ScanCount = 0;
	jstr = ExpStr;
	while(mstr.FindOneOf(jstr) >= 0)
	{
		npos = 1;
		while (npos > 0)
		{
			npos = lr.NextCharacterGroup(jstr, kstr, npos);
			tch = kstr[0];
			if ((tch == '-') || (tch == '+'))
			{
				if (kstr.GetLength() > 1)
				{
					kstr = kstr.Right(kstr.GetLength() - 1);
					tch = kstr[0];
				}
			}
			CardNo = DelgenNo;
			CV = Cvar;
			switch (tch)
			{
			case 'a':
			case 'A':
			case 'b':
			case 'B':
			case 'c':
			case 'C':
			case 'd':
			case 'D':
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 't':
			case 'T':
			case 'p':
			case 'P':
			case 'r':
			case 'R':
				Chan = tch;
				if (kstr.GetLength() > 1)
				{
					c1 = kstr[1];
					if (lr.Numeric(c1))
					{
						lstr = kstr.Right(kstr.GetLength() - 1);
						CardNo = RoundInt(atof(lstr)) - 1;
					}
					else
					{
						if (CV == Cvar)
						{
							switch (c1)
							{
							case 'd':
							case 'D':
							case 'r':
							case 'R':
							case 'w':
							case 'W':
							case 'm':
							case 'M':
							case 'n':
							case 'N':
								CV = c1;
								break;
							default:
								if (((65 <= c1) && (tch <= c1)) || ((97 <= c1) && (tch <= c1)))
								{
									CString estr;
									estr.Format("character '%c' not allowed in delay specification!!\n\n", c1);
									estr += "second character specifies Delay-, Reset- or PulseWidth-time\n";
									estr += "     use 'D' (default) for delay\n";
									estr += "         'R' for reset time\n";
									estr += "         'W' for pulse width\n";
									estr += "         'M' for modulo\n";
									estr += "         'N' for offset\n";
									throw estr;
								}
								break;
							}
							if (kstr.GetLength() > 2)
							{
								c2 = kstr[2];
								if (lr.Numeric(c1))
								{
									lstr = kstr.Right(kstr.GetLength() - 2);
									CardNo = RoundInt(atof(lstr)) - 1;
								}
							}
						}
					}
				}
				if (CardNo >= NoDelgen)
				{
					CString estr;
					estr.Format("Delay generator no. %d has not been defined", (CardNo + 1));
					throw estr;
				}
				StringFound = FALSE;
				CardPos = m_List.FindIndex(CardNo);
				p_RD = m_List.GetAt(CardPos);
				p_RM = (p_VarMat + CardNo);
				switch (Chan)
				{
				case 't':
				case 'T':
					p_DC = &(p_RD->Control.T0);
					p_CL = &(p_RD->VarLoc.T0);
					p_CS = &(p_RM->T0);
					break;
				case 'a':
				case 'A':
					p_DC = &(p_RD->Control.A);
					p_CL = &(p_RD->VarLoc.A);
					p_CS = &(p_RM->A);
					break;
				case 'b':
				case 'B':
					p_DC = &(p_RD->Control.B);
					p_CL = &(p_RD->VarLoc.B);
					p_CS = &(p_RM->B);
					break;
				case 'c':
				case 'C':
					switch (p_RD->Product)
					{
					case BME_SG08P1:
					case BME_SG08P2:
						p_DC = &(p_RD->Control.C);
						p_CL = &(p_RD->VarLoc.C);
						p_CS = &(p_RM->C);
						break;
					default:
						if (p_RD->VarLoc.RepCounter == -2)
							lstr = ("(" + p_RM->RepCounter + ")");
						else
						{
							lstr.Format("%13.11f", p_RD->Control.DT.InternalClock);
							lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
							lstr = (" " + lstr + " ");
						}
						StringFound = TRUE;
						break;
					}
					break;
				case 'd':
				case 'D':
					p_DC = &(p_RD->Control.D);
					p_CL = &(p_RD->VarLoc.D);
					p_CS = &(p_RM->D);
					break;
				case 'e':
				case 'E':
					p_DC = &(p_RD->Control.E);
					p_CL = &(p_RD->VarLoc.E);
					p_CS = &(p_RM->E);
					break;
				case 'f':
				case 'F':
					switch (p_RD->Product)
					{
					case BME_SG08P1:
					case BME_SG08P2:
						p_DC = &(p_RD->Control.F);
						p_CL = &(p_RD->VarLoc.F);
						p_CS = &(p_RM->F);
						break;
					default:
						if (p_RD->VarLoc.ForceTrigger == -2)
							lstr = ("(" + p_RM->ForceTrigger + ")");
						else
						{
							lstr.Format("%13.11f", p_RD->Control.DT.ForceTrigger);
							lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
							lstr = (" " + lstr + " ");
						}
						StringFound = TRUE;
						break;
					}
					break;
				case 'p':
				case 'P':
					if (p_RD->VarLoc.RepCounter == -2)
						lstr = ("(" + p_RM->RepCounter + ")");
					else
					{
						lstr.Format("%13.11f", p_RD->Control.DT.InternalClock);
						lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
						lstr = (" " + lstr + " ");
					}
					StringFound = TRUE;
					break;
				case 'r':
				case 'R':
					if (p_RD->VarLoc.ForceTrigger == -2)
						lstr = ("(" + p_RM->ForceTrigger + ")");
					else
					{
						lstr.Format("%13.11f", p_RD->Control.DT.ForceTrigger);
						lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
						lstr = (" " + lstr + " ");
					}
					StringFound = TRUE;
					break;
				}
				if (!StringFound)
				{
					ReadPosition = max(0, min((p_DC->ListLength - 1), FpgaPosition));
					switch (CV)
					{
					case 'd':
					case 'D':
						if (p_CL->FireFirst == -2)
							lstr = ("(" + p_CS->FireFirst + ")");
						else
						{
							lstr.Format("%13.11f", p_DC->DelayTime[ReadPosition]);
							lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
							lstr = (" " + lstr + " ");
						}
						break;
					case 'r':
					case 'R':
						if (p_CL->SetBack == -2)
							lstr = ("(" + p_CS->SetBack + ")");
						else
						{
							lstr.Format("%13.11f", p_DC->SetBack);
							lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
							lstr = (" " + lstr + " ");
						}
						break;
					case 'w':
					case 'W':
						if (p_CL->PulseWidth == -2)
							lstr = ("(" + p_CS->PulseWidth + ")");
						else
						{
							lstr.Format("%13.11f", p_DC->PulseWidth[ReadPosition]);
							lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
							lstr = (" " + lstr + " ");
						}
						break;
					case 'm':
					case 'M':
						if (p_CL->OutputModulo == -2)
							lstr = ("(" + p_CS->OutputModulo + ")");
						else
						{
							lstr.Format("%d", p_DC->OutputModulo);
							lstr = (" " + lstr + " ");
						}
						break;
					case 'n':
					case 'N':
						if (p_CL->OutputOffset == -2)
							lstr = ("(" + p_CS->OutputOffset + ")");
						else
						{
							lstr.Format("%d", p_DC->OutputOffset);
							lstr = (" " + lstr + " ");
						}
						break;
					case 'c':
					case 'C':
					case 'f':
					case 'F':
						break;
					}
				}
				lr.FindReplaceString(jstr, kstr, lstr);
				npos = 1;
				ReplaceCount++;
				break;
			case 'x':
			case 'X':
				lstr = kstr.Right(kstr.GetLength() - 1);
				ivar = (RoundInt(atof(lstr)) - 1);
				ivar = max(0, ivar);
				if (ivar >= p_G0xData->ParameterList.NoParameters)
				{
					CString tstr = "variable " + kstr + " has not been defined!!";
					throw tstr;
				}
				value = *(p_Val + ivar);
				lstr.Format("%13.11f", value);
				lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
				lstr = (" " + lstr + " ");
				lr.FindReplaceString(jstr, kstr, lstr);
				npos = 1;
				ReplaceCount++;
				break;
			case 'y':
			case 'Y':
				lstr = kstr.Right(kstr.GetLength() - 1);
				ivar = (RoundInt(atof(lstr)) - 1);
				ivar = max(0, ivar);
				if (ivar >= p_G0xData->FpgaMemoryList.NoParameters)
				{
					CString tstr = "Fpga Memory Column " + kstr + " has not been defined!!";
					throw tstr;
				}
				value = *(p_Mem + ivar);
				lstr.Format("%13.11f", value);
				lstr =  lr.TrimTrailingZeros((LPCTSTR)lstr);
				lstr = (" " + lstr + " ");
				lr.FindReplaceString(jstr, kstr, lstr);
				npos = 1;
				ReplaceCount++;
				break;
			default:
				break;
			}
			if (ReplaceCount > MaxReplacements)
			{
				CString tstr = "maximum number of replacements exceeded!!\n\n";
				tstr += "       are your definitions recursive?";
				throw tstr;
			}
		}
		ScanCount++;
		if (ScanCount > MaxReplacements)
		{
			CString tstr = "maximum number of attempts to resolve string exceeded!!\n\n";
			tstr += "           are your variable names correct?";
			throw tstr;
		}
	}
	npos = 1;
	while (npos > 0)
	{
		npos = lr.NextCharacterGroup(jstr, kstr, npos);
		tch = kstr[0];
		if (((65 <= tch) && (tch <= tch)) || ((97 <= tch) && (tch <= tch)))
		{
			CString estr = "'" + kstr + "' is not a variable!!";
			throw estr;
		}
	}
	return jstr;
}

void CDelgenControl::LoadFpgaVector(double* p_Mem, double* p_Val, int FpgaPosition)
{
	int pos;
	if (p_G0xData->FpgaMemoryList.ListLength > 0)
	{
		double* p_Fpga = (p_G0xData->FpgaMemoryList.p_Value + 
											(FpgaPosition * p_G0xData->FpgaMemoryList.NoParameters));
		int* p_Loc = (p_G0xData->FpgaMemoryList.p_Loc + 
											(FpgaPosition * p_G0xData->FpgaMemoryList.NoParameters));
		memcpy(p_Mem, p_Fpga, (sizeof(double) * p_G0xData->FpgaMemoryList.NoParameters));
		for (pos = 0; pos < p_G0xData->FpgaMemoryList.NoParameters; pos++)
		{
			if (*(p_Loc + pos) >= 0)
				*(p_Mem + pos) = *(p_Val + *(p_Loc + pos));
		}
	}
}

void CDelgenControl::ReplaceChannelVariables(ChannelStringType& ChanStr, DelayChannelData& ChanData, 
											  int DelgenNo, ChannelLocationType& ChanLoc, VariableStringType* p_VarMat, 
												double* p_Val, CTypedPtrList<CPtrList, DG_Type*>& m_List)
{
	CListRout lr;
	CString jstr;
	double* p_Mem = NULL;
	int MemCount = 0;
	int NoParameters = 0;
	if (FpgaMemoryActive)
	{
		MemCount = p_G0xData->FpgaMemoryList.ListLength;
		if (MemCount > MemLength)
		{
			CString estr,jstr;
			estr.Format("FPGA memory list is %d lines long!", MemCount);
			jstr.Format("\n      only %d lines allowed", MemLength);
			estr += jstr;
			throw estr;
		}
		NoParameters = p_G0xData->FpgaMemoryList.NoParameters;
		p_Mem = new double[max(2, NoParameters)];
	}
	int FpgaMemLength = max(1, MemCount);
	ChanData.ListLength = FpgaMemLength;
	int FpgaPosition;
	for (FpgaPosition = 0; FpgaPosition < FpgaMemLength; FpgaPosition++)
	{
		if (p_Mem != NULL)
			LoadFpgaVector(p_Mem, p_Val, FpgaPosition);
		if (ChanLoc.FireFirst == -2)
		{
			if (ChanStr.FireFirst.GetLength() > 0)
			{
				jstr = ChanStr.FireFirst;
				jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, p_Mem, FpgaPosition, m_List);
				jstr = lr.EvaluateString(jstr);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
				{
					CString estr = "cannot evaluate '" + jstr + "' !!";
					throw estr;
				}
				ChanData.DelayTime[FpgaPosition] = max(0.0, atof(jstr));
			}
		}
		else
		{
			if (FpgaPosition > 0)
				ChanData.DelayTime[FpgaPosition] = ChanData.DelayTime[0];
		}
		if (ChanLoc.PulseWidth == -2)
		{
			if (ChanStr.PulseWidth.GetLength() > 0)
			{
				jstr = ChanStr.PulseWidth;
				jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, p_Mem, FpgaPosition, m_List);
				jstr = lr.EvaluateString(jstr);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
				{
					CString estr = "cannot evaluate '" + jstr + "' !!";
					throw estr;
				}
				ChanData.PulseWidth[FpgaPosition] = max(0.0, atof(jstr));
			}
		}
		else
		{
			if (FpgaPosition > 0)
				ChanData.PulseWidth[FpgaPosition] = ChanData.PulseWidth[0];
		}
		if (ChanLoc.StepBack == -2)
		{
			if (ChanStr.StepBack.GetLength() > 0)
			{
				jstr = ChanStr.StepBack;
				jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, p_Mem, FpgaPosition, m_List);
				jstr = lr.EvaluateString(jstr);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
				{
					CString estr = "cannot evaluate '" + jstr + "' !!";
					throw estr;
				}
				ChanData.StepBack[FpgaPosition] = max(FpgaPosition, min((MemCount-1), (RoundInt(atof(jstr)) - 1)));
			}
		}
	}
	ChanLoc.FireFirst = -1;
	ChanStr.FireFirst = _T("");
	ChanLoc.PulseWidth = -1;
	ChanStr.PulseWidth = _T("");
	ChanLoc.StepBack = -1;
	ChanStr.StepBack = _T("");
	if (ChanLoc.SetBack == -2)
	{
		if (ChanStr.SetBack.GetLength() > 0)
		{
			jstr = ChanStr.SetBack;
			jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, NULL, 0, m_List);
			jstr = lr.EvaluateString(jstr);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
			{
				CString estr = "cannot evaluate '" + jstr + "' !!";
				throw estr;
			}
			ChanData.SetBack = max(0.0, atof(jstr));
			ChanLoc.SetBack = -1;
			ChanStr.SetBack = _T("");
		}
	}
	if (ChanLoc.OutputModulo == -2)
	{
		if (ChanStr.OutputModulo.GetLength() > 0)
		{
			jstr = ChanStr.OutputModulo;
			jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, NULL, 0, m_List, 'M');
			jstr = lr.EvaluateString(jstr);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
			{
				CString estr = "cannot evaluate '" + jstr + "' !!";
				throw estr;
			}
			ChanData.OutputModulo = max(1, RoundInt(atof(jstr)));
			ChanLoc.OutputModulo = -1;
			ChanStr.OutputModulo = _T("");
		}
	}
	if (ChanLoc.OutputOffset == -2)
	{
		if (ChanStr.OutputOffset.GetLength() > 0)
		{
			jstr = ChanStr.OutputOffset;
			jstr = ExpandString(jstr, DelgenNo, p_VarMat, p_Val, NULL, 0, m_List, 'N');
			jstr = lr.EvaluateString(jstr);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
			{
				CString estr = "cannot evaluate '" + jstr + "' !!";
				throw estr;
			}
			ChanData.OutputOffset = max(1, RoundInt(atof(jstr)));
			ChanLoc.OutputOffset = -1;
			ChanStr.OutputOffset = _T("");
		}
	}
	if (p_Mem != NULL)
		delete []p_Mem;
}

void CDelgenControl::ReplaceVariables(VariableStringType* p_VarMat, double* p_Val, 
																			CTypedPtrList<CPtrList, DG_Type*>& m_List)
{
	CListRout lr;
	DG_Type* p_DG;
	VariableStringType* p_Mat;
	CString jstr;
	POSITION pos = m_List.GetHeadPosition();
	int Count = 0;
	while (pos != NULL)
	{
		p_DG = m_List.GetNext(pos);
		p_Mat = (p_VarMat + Count);
		ReplaceChannelVariables(p_Mat->T0, p_DG->Control.T0, Count, p_DG->VarLoc.T0, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->A, p_DG->Control.A, Count, p_DG->VarLoc.A, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->B, p_DG->Control.B, Count, p_DG->VarLoc.B, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->C, p_DG->Control.C, Count, p_DG->VarLoc.C, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->D, p_DG->Control.D, Count, p_DG->VarLoc.D, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->E, p_DG->Control.E, Count, p_DG->VarLoc.E, p_VarMat, p_Val, m_List);
		ReplaceChannelVariables(p_Mat->F, p_DG->Control.F, Count, p_DG->VarLoc.F, p_VarMat, p_Val, m_List);

		if (p_DG->VarLoc.ForceTrigger == -2)
		{
			if (p_Mat->ForceTrigger.GetLength() > 0)
			{
				jstr = p_Mat->ForceTrigger;
				jstr = ExpandString(jstr, Count, p_VarMat, p_Val, NULL, 0, m_List, 'F');
				jstr = lr.EvaluateString(jstr);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
				{
					CString estr = "cannot evaluate '" + jstr + "' !!";
					throw estr;
				}
				p_DG->Control.DT.ForceTrigger = max(0.0, atof(jstr));
				p_DG->VarLoc.ForceTrigger = -1;
				p_Mat->ForceTrigger = _T("");
			}
		}
		if (p_DG->VarLoc.RepCounter == -2)
		{
			if (p_Mat->RepCounter.GetLength() > 0)
			{
				jstr = p_Mat->RepCounter;
				jstr = ExpandString(jstr, Count, p_VarMat, p_Val, NULL, 0, m_List, 'C');
				jstr = lr.EvaluateString(jstr);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) > 1)
				{
					CString estr = "cannot evaluate '" + jstr + "' !!";
					throw estr;
				}
				p_DG->Control.DT.InternalClock = max(0.0, atof(jstr));
				p_DG->VarLoc.RepCounter = -1;
				p_Mat->RepCounter = _T("");
			}
		}

		Count++;
	}
}

void CDelgenControl::ReduceDelayList(DelayChannelData& ChanData)
{
	BOOL found = FALSE;
	int FpgaPosition = 0;
	while ((!found) && (FpgaPosition < ChanData.ListLength))
	{
		if (ChanData.DelayTime[FpgaPosition] != ChanData.DelayTime[0])
			found = TRUE;
		if (ChanData.PulseWidth[FpgaPosition] != ChanData.PulseWidth[0])
			found = TRUE;
		FpgaPosition++;
	}
	if (!found)
	{
		ChanData.ListLength = 1;
		ChanData.StepBack[0] = 0;
	}
}

void CDelgenControl::LoadChannelVariables(ChannelStringType& ChanStr, DelayChannelData& ChanData, 
											  ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith, double* p_Val)
{
	CListRout lr;
	int MemCount = 0;
	if (FpgaMemoryActive)
		MemCount = p_G0xData->FpgaMemoryList.ListLength;
	if (ChanLoc.FireFirst >= 0)
		ChanData.FireFirst = *(p_Val + ChanLoc.FireFirst);
	else
	{
		if (ChanLoc.FireFirst == -2)
			ChanStr.FireFirst = lr.ReadMemo(ChanArith.FireFirst);
	}
	if (ChanLoc.SetBack >= 0)
		ChanData.SetBack = *(p_Val + ChanLoc.SetBack);
	else
	{
		if (ChanLoc.SetBack == -2)
			ChanStr.SetBack = lr.ReadMemo(ChanArith.SetBack);
	}
	if (ChanLoc.PulseWidth >= 0)
		ChanData.PulseWidth[0] = *(p_Val + ChanLoc.PulseWidth);
	else
	{
		if (ChanLoc.PulseWidth == -2)
			ChanStr.PulseWidth = lr.ReadMemo(ChanArith.PulseWidth);
	}
	if (ChanLoc.OutputModulo >= 0)
		ChanData.OutputModulo = RoundInt(*(p_Val + ChanLoc.OutputModulo));
	else
	{
		if (ChanLoc.OutputModulo == -2)
			ChanStr.OutputModulo = lr.ReadMemo(ChanArith.OutputModulo);
	}
	if (ChanLoc.OutputOffset >= 0)
		ChanData.OutputOffset = RoundInt(*(p_Val + ChanLoc.OutputOffset));
	else
	{
		if (ChanLoc.OutputOffset == -2)
			ChanStr.OutputOffset = lr.ReadMemo(ChanArith.OutputOffset);
	}
	if (ChanLoc.StepBack >= 0)
		ChanData.StepBack[0] = max(0, min((MemCount - 1), (RoundInt(*(p_Val + ChanLoc.StepBack)) - 1)));
	else
	{
		if (ChanLoc.StepBack == -2)
			ChanStr.StepBack = lr.ReadMemo(ChanArith.StepBack);
	}
}

void CDelgenControl::LoadVariables(CTypedPtrList<CPtrList, DG_Type*>& m_List, int ListPosition)
{
	CListRout lr;
	DG_Type* p_DG;
	VariableStringType* p_VarMat;
	VariableStringType* p_Mat;
	double* p_Val = (p_G0xData->ParameterList.p_Value + 
										(ListPosition * p_G0xData->ParameterList.NoParameters));
	int Count = m_List.GetCount();
	p_VarMat = new VariableStringType[max(2, Count)];
	POSITION pos = m_List.GetHeadPosition();
	Count = 0;
	while (pos != NULL)
	{
		p_DG = m_List.GetNext(pos);
		p_Mat = (p_VarMat + Count);
		ResetVariableString(p_Mat);
		LoadChannelVariables(p_Mat->T0, p_DG->Control.T0, p_DG->VarLoc.T0, p_DG->VarEqu.T0, p_Val);
		LoadChannelVariables(p_Mat->A, p_DG->Control.A, p_DG->VarLoc.A, p_DG->VarEqu.A, p_Val);
		LoadChannelVariables(p_Mat->B, p_DG->Control.B, p_DG->VarLoc.B, p_DG->VarEqu.B, p_Val);
		LoadChannelVariables(p_Mat->C, p_DG->Control.C, p_DG->VarLoc.C, p_DG->VarEqu.C, p_Val);
		LoadChannelVariables(p_Mat->D, p_DG->Control.D, p_DG->VarLoc.D, p_DG->VarEqu.D, p_Val);
		LoadChannelVariables(p_Mat->E, p_DG->Control.E, p_DG->VarLoc.E, p_DG->VarEqu.E, p_Val);
		LoadChannelVariables(p_Mat->F, p_DG->Control.F, p_DG->VarLoc.F, p_DG->VarEqu.F, p_Val);

		if (p_DG->VarLoc.ForceTrigger >= 0)
			p_DG->Control.DT.ForceTrigger = RoundInt(*(p_Val + p_DG->VarLoc.ForceTrigger));
		else
		{
			if (p_DG->VarLoc.ForceTrigger == -2)
				p_Mat->ForceTrigger = lr.ReadMemo(p_DG->VarEqu.ForceTrigger);
		}
		if (p_DG->VarLoc.RepCounter >= 0)
			p_DG->Control.DT.InternalClock = *(p_Val + p_DG->VarLoc.RepCounter);
		else
		{
			if (p_DG->VarLoc.RepCounter == -2)
				p_Mat->RepCounter = lr.ReadMemo(p_DG->VarEqu.RepCounter);
		}

		Count++;
	}
	ReplaceVariables(p_VarMat, p_Val, m_List);
	delete []p_VarMat;
	if (FpgaMemoryActive)
	{
		pos = m_List.GetHeadPosition();
		while (pos != NULL)
		{
			p_DG = m_List.GetNext(pos);
			ReduceDelayList(p_DG->Control.T0);
			ReduceDelayList(p_DG->Control.A);
			ReduceDelayList(p_DG->Control.B);
			ReduceDelayList(p_DG->Control.C);
			ReduceDelayList(p_DG->Control.D);
			ReduceDelayList(p_DG->Control.E);
			ReduceDelayList(p_DG->Control.F);
		}
	}
}

void CDelgenControl::DefineRWD(CTypedPtrList<CPtrList, DG_Type*>& m_List, BOOL RWD)
{
	DG_Type* p_DG;
	POSITION pos = m_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = m_List.GetNext(pos);
		p_DG->Control.DT.ResetWhenDone = RWD;
	}
	b_ResetWhenDone = RWD;
}

void CDelgenControl::MainLoop()
{
  struct _timeb PresentTime;
  struct _timeb NextTime;
  struct _timeb InfoTime;
	int PresentListPosition;
	int NextListPosition;
	SweepActive = FALSE;
	SubCycleCount = 0;
	DWORD WaitMilliSeconds = 1000;
	_ftime(&NextTime);
	int i1, Count;
	TriggerCount = 0;
	try
	{
		do
		{
			WaitForSingleObject(ControlNotification, WaitMilliSeconds);
			ResetEvent(ControlNotification);
			if ((b_InitializeControl) && (!b_RemoveControlThread)) 
			{
				b_InitializeControl = FALSE;
				SweepActive = FALSE;
				SubCycleCount = 0;
				p_G0xData->CopyDG_List(DG_List, p_G0xData->m_DG_List);
				p_G0xData->ReadTimeSequence(TimeSequence);
				if (p_G0xData->p_OpInfo != NULL)
					delete []p_G0xData->p_OpInfo;
				Count = DG_List.GetCount();
				p_G0xData->p_OpInfo = new OpInfo_Type[max(2, Count)];
				for (i1 = 0; i1 < Count; i1++)
				{
					(p_G0xData->p_OpInfo + i1)->TriggerEvents = 0;
					(p_G0xData->p_OpInfo + i1)->DG_Status = 0x0;
				}
				SweepActive = p_G0xData->VariablesExist();
				FpgaMemoryActive = p_G0xData->FpgaMemoryExist();
				PresentListPosition = 0;
				if (SweepActive)
				{
					if (TimeSequence.m_Upwards)
					{
						MovingUp = TRUE;
						PresentListPosition = 0;
					}
					else
					{
						MovingUp = FALSE;
						PresentListPosition = p_G0xData->ParameterList.ListLength - 1;
					}
				}
				LoadVariables(DG_List, PresentListPosition);
				if (!b_ResetWhenDone)
					DefineRWD(DG_List, TRUE);
				_ftime(&NextTime);
				SetDelayGenerators(TRUE);
				memcpy(&InfoTime, &NextTime, sizeof(_timeb));
				InfoTime.time -= 1;
				SubCycleCount++;
				if (SweepActive)
				{
					GetNextTime(NextTime, NextTime);
					p_G0xData->CopyDG_List(DG_List, p_G0xData->m_DG_List);
					NextListPosition = GetNextPosition(PresentListPosition);
					LoadVariables(DG_List, NextListPosition);
				}
			}
			if (b_RequestRemoveControlThread)
			{
				if (b_ResetWhenDone)
				{
					_ftime(&PresentTime);
					AddTime(NextTime, PresentTime, 1000);
					SweepActive = FALSE;
					DefineRWD(DG_List, FALSE);
					SetDelayGenerators(FALSE);
				}
				_ftime(&PresentTime);
				if (TimeDifference(PresentTime, NextTime) >= 0)
				{
					b_RequestRemoveControlThread = FALSE;
					b_RemoveControlThread = TRUE;
				}
				else
				{
					if (p_G0xData->AllDelayGeneratorsDone(DG_List))
					{
						b_RequestRemoveControlThread = FALSE;
						b_RemoveControlThread = TRUE;
					}
				}
			}
			if ((SweepActive) && (!b_RemoveControlThread))
			{
				_ftime(&PresentTime);
				if (TimeDifference(PresentTime, NextTime) >= 0)
				{
					SetDelayGenerators(FALSE);
					SubCycleCount++;
					GetNextTime(NextTime, NextTime);
					p_G0xData->CopyDG_List(DG_List, p_G0xData->m_DG_List);
					NextListPosition = GetNextPosition(NextListPosition);
					LoadVariables(DG_List, NextListPosition);
					p_ParentWindow->SendMessage(WM_WRITE_REQUEST, 0, 0);
				}
			}
			if (!b_RemoveControlThread)
			{
				_ftime(&PresentTime);
				if (TimeDifference(PresentTime, InfoTime) >= 1000)
				{
					memcpy(&InfoTime, &PresentTime, sizeof(_timeb));
					if (ReadTriggerCounters())
						p_ParentWindow->SendMessage(WM_WRITE_REQUEST, 0, 0);
				}
			}
			WaitMilliSeconds = CalculateWait(NextTime);
		}
		while (!b_RemoveControlThread);
		p_G0xData->DeactivateDelayGenerators();
	}
	catch(CString& str)
	{
		AfxMessageBox(str, MB_OK, 0);
	}
	catch(...)
	{
		AfxMessageBox("unspecified error has occurred!! ", MB_OK, 0);
	}
	b_RemoveControlThread = FALSE;
	b_RequestRemoveControlThread = FALSE;
	b_ControlThreadActive = FALSE;
	SetEvent(ExitNotification);
}
