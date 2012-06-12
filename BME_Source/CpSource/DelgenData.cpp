/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 File Routines for Alpha Format
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

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "DelgenData.h"
#include "..\Spectra_BME\ListRout.h"


CDelgenData::CDelgenData()
{
	p_LargeHeadingFont = new CFont;
	p_LargeHeadingFont->CreateFont(20,8,0,0,900,0,0,0,
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, 
				PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "MS Sans Serif");
	p_HeadingFont = new CFont;
	p_HeadingFont->CreateFont(16,6,0,0,700,0,0,0,
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, 
				PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "MS Sans Serif");
	p_MinorHeadingFont = new CFont;
	p_MinorHeadingFont->CreateFont(14,5,0,0,700,0,0,0,
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, 
				PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "MS Sans Serif");
	p_RegularFont = new CFont;
	p_RegularFont->CreateFont(14,5,0,0,550,0,0,0,
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, 
				PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "MS Sans Serif");
	PresentYStep = YLargeStep;
}

CDelgenData::~CDelgenData()
{
	ConfigurationTable.RemoveAll();
	delete p_LargeHeadingFont;
	delete p_HeadingFont;
	delete p_MinorHeadingFont;
	delete p_RegularFont;
}

void CDelgenData::ResetLinePosition(CPoint ScrollPosition)
{
	XPosition = XStart - ScrollPosition.x;
	YPosition = YStart - ScrollPosition.y;
	XLeft = XPosition;
}

void CDelgenData::NewLine()
{
	XPosition = XLeft;
	YPosition += PresentYStep;
}

void CDelgenData::HalfLine()
{
	XPosition = XLeft;
	YPosition += (PresentYStep / 2);
}

void CDelgenData::SetPrivateFont(CClientDC* p_ClientDC, int FontNumber)
{
	switch (FontNumber)
	{
		case RegularFont:
			PresentYStep = YSmallStep;
			p_ClientDC->SelectObject(p_RegularFont);
			break;
		case MinorHeadingFont:
			PresentYStep = YSmallStep;
			p_ClientDC->SelectObject(p_MinorHeadingFont);
			break;
		case HeadingFont:
			PresentYStep = YLargeStep;
			p_ClientDC->SelectObject(p_HeadingFont);
			break;
		case LargeHeadingFont:
			PresentYStep = YLargeStep;
			p_ClientDC->SelectObject(p_LargeHeadingFont);
			break;
	}
}

void CDelgenData::WriteLine(CString& kstr, CSize& TextExtent, CSize& LineExtent, CClientDC* p_ClientDC)
{
	LineExtent = p_ClientDC->GetTextExtent(kstr);
	TextExtent.cx = max((XStart + LineExtent.cx), TextExtent.cx);
	p_ClientDC->TextOut(XPosition, YPosition, kstr );
	NewLine();
}

void CDelgenData::WriteChannelVariables(CString& ChanStr, DelayChannelData& ChanData, BOOL FpgaMemoryExist,
																				CG0xData* p_G0xData, DG_Type* p_DG, ChannelLocationType& ChanLoc,
																				CSize& TextExtent, CSize& LineExtent, CClientDC* p_ClientDC)
{
	CListRout lr;
	CString kstr,jstr;
	int FpgaPosition;
	BOOL NtDefined = FALSE;
#ifdef WINDOWSNT
	NtDefined = TRUE;
#endif
	kstr = ChanStr;
	if ((ChanData.GoSignal & SystemClock) != 0x0)
	{
		if ((ChanData.GoSignal & DelayClock) != 0x0)
			kstr += "prescaled delay clock";
		else
			kstr += "prescaled system clock";
	}
	else
	{
		if (p_G0xData->b_DelayGeneratorsActive)
		{
			switch (p_DG->Product)
			{
			case BME_SG02P3:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				if ((ChanData.GoSignal & 0x77) != 0x0)
				{
					int TrigEventCount = 0;
					kstr += "active on";
					if ((ChanData.GoSignal & MasterPrimary) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " master/slave-bus";
						switch (p_DG->Product)
						{
						case BME_SG08P1:
						case BME_SG08P2:
							kstr += " primary";
							break;
						default:
							break;
						}
						TrigEventCount++;
					}
					if ((ChanData.GoSignal & MasterSecondary) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " master/slave-bus secondary";
						TrigEventCount++;
					}
					if ((ChanData.GoSignal & MasterForce) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " master/slave-bus force trigger";
						TrigEventCount++;
					}
					if ((ChanData.GoSignal & LocalPrimary) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " local primary";
						TrigEventCount++;
					}
					if ((ChanData.GoSignal & LocalSecondary) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " local secondary";
						TrigEventCount++;
					}
					if ((ChanData.GoSignal & LocalForce) != 0x0)
					{
						if (TrigEventCount > 0)
							kstr += ",";
						kstr += " local force trigger";
						TrigEventCount++;
					}
					kstr += " trigger events";
					switch (p_DG->Product)
					{
					case BME_SG08P1:
					case BME_SG08P2:
						if ((ChanData.GoSignal & (EnableFromE | EnableFromF | EnableFromBus)) != 0x0)
						{
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							int EnaCauseCount = 0;
							kstr = "    output is enabled by ";
							if ((ChanData.GoSignal & EnableFromE) != 0x0)
							{
								kstr += " input from E connector";
								EnaCauseCount++;
							}
							if ((ChanData.GoSignal & EnableFromF) != 0x0)
							{
								if (EnaCauseCount > 0)
									kstr += ",";
								kstr += " input from F connector";
								EnaCauseCount++;
							}
							if ((ChanData.GoSignal & EnableFromBus) != 0x0)
							{
								if (EnaCauseCount > 0)
									kstr += ",";
								kstr += " enable signal from master/slave bus";
							}
						}
						if (FpgaMemoryExist)
						{
							if ((ChanData.GoSignal & (StepBackLocal | StepBackBus)) != 0x0)
							{
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								int SbSource = 0;
								kstr = "    delay list is stepped back with signal from ";
								if ((ChanData.GoSignal & StepBackLocal) != 0x0)
								{
									kstr += " local";
									SbSource++;
								}
								if ((ChanData.GoSignal & StepBackBus) != 0x0)
								{
									if (SbSource > 0)
										kstr += " and";
									kstr += " master";
								}
								kstr += " step back timer";
							}
							if ((ChanData.GoSignal & (StartLocal | StartBus)) != 0x0)
							{
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								int StSource = 0;
								kstr.Format("    delay list is started from position %d with signal from ", ChanData.ListLength);
								if ((ChanData.GoSignal & StartLocal) != 0x0)
								{
									kstr += " local";
									StSource++;
								}
								if ((ChanData.GoSignal & StartBus) != 0x0)
								{
									if (StSource > 0)
										kstr += " and";
									kstr += " master";
								}
								kstr += " start signal";
							}
							if ((ChanData.GoSignal & RunCircle) != 0x0)
							{
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								kstr = "    items from the delay list will be read in circle";
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								kstr.Format("        when reaching position 1 of the delay list, next item will be taken from position %d", (ChanData.StepBack[0] + 1));
							}
						}
						break;
					default:
						break;
					}
				}
				else
					kstr += "disabled";
				break;
			default:
				if ((ChanData.GoSignal & 0x77) != 0x0)
					kstr += "active";
				else
					kstr += "disabled";
				break;
			}
		}
		else
			kstr += "disabled";
	}
	WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
	if ((((ChanData.GoSignal & 0x77) != 0x0) && (p_G0xData->b_DelayGeneratorsActive)) ||
								((ChanData.GoSignal & SystemClock) != 0x0))
	{
		switch (p_DG->Product)
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
		case BME_SG08P1:
		case BME_SG08P2:
			if (ChanData.Positive)
				kstr = _T("    positive output, ");
			else
				kstr = _T("    negative output, ");
			if (ChanData.Terminate)
			{
				if (ChanData.HighDrive)
					kstr += " must be externally terminated into 50 ohms";
				else
					kstr += " internally terminated into 50 ohms";
			}
			else
			{
				if (ChanData.HighDrive)
					kstr += " must be externally terminated into 25 ohms";
				else
					kstr += " must be externally terminated into 50 ohms";
			}
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			break;
		default:
			break;
		}
	}
	if ((((ChanData.GoSignal & 0x77) != 0x0) && (p_G0xData->b_DelayGeneratorsActive)) &&
								((ChanData.GoSignal & 0x80) == 0x0))
	{
		if ((ChanLoc.FireFirst >= 0) && (!NtDefined))
			kstr.Format("    Delay time  : X%d", (ChanLoc.FireFirst + 1));
		else
		{
			switch (p_DG->Product)
			{
			case BME_SG08P1:
			case BME_SG08P2:
				kstr = "  Position   Delay time      Pulse width      Step back to";
				for (FpgaPosition = 0; FpgaPosition < ChanData.ListLength; FpgaPosition++)
				{
					WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
					kstr.Format("        %3d        ", (FpgaPosition + 1));
					jstr.Format("   %6.5f", ChanData.DelayTime[FpgaPosition]);
					jstr = lr.TrimTrailingZeros(jstr);
					lr.PadString(jstr, 20);
					kstr += jstr;
					jstr.Format("   %6.5f", ChanData.PulseWidth[FpgaPosition]);
					jstr = lr.TrimTrailingZeros(jstr);
					lr.PadString(jstr, 20);
					kstr += jstr;
					jstr.Format("   %d", (ChanData.StepBack[FpgaPosition] + 1));
					kstr += jstr;
				}
				break;
			default:
				kstr.Format("    Delay time  : %6.5f", ChanData.FireFirst);
				kstr = lr.TrimTrailingZeros(kstr);
				break;
			}
		}
		WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
		switch (p_DG->Product)
		{
		case BME_G03V1:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (ChanData.SetBack > ChanData.FireFirst)
			{
				if ((ChanLoc.SetBack >= 0) && (!NtDefined))
					kstr.Format("    Reset time  : X%d", (ChanLoc.SetBack + 1));
				else
				{
					kstr.Format("    Reset time  : %6.5f", ChanData.SetBack);
					kstr = lr.TrimTrailingZeros(kstr);
				}
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			break;
		default:
			break;
		}
		switch (p_DG->Product)
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
			if (ChanData.OutputModulo > 1)
			{
				kstr.Format("    one output pulse every %d trigger events", 
																	ChanData.OutputModulo);
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				switch (p_DG->Product)
				{
				case BME_SG08P2:
					if ((ChanData.GoSignal & SynchReload) != 0x0)
					{
						kstr = _T("    new parameters can only be loaded when this modulo counter has reached zero");
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
					}
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	if ((ChanStr[0] == 'E') || (ChanStr[0] == 'F'))
	{
		if (ChanData.Disconnect)
		{
			kstr = "    output driver is disconnected";
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
		}
		if (!ChanData.InputPositive)
		{
			kstr = "    input signal from channel output connector is inverted";
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
		}
		if (ChanData.OntoMsBus)
		{
			kstr = "    signal is placed onto the master/slave bus";
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
		}
	}
}

CSize CDelgenData::WriteDelgenSetup(CG0xData* p_G0xData, CClientDC* p_ClientDC,
																							 CPoint ScrollPosition, CSize PreviousDataSize)
{
	CTypedPtrList<CPtrList, DG_Type*> DG_List;
	DG_Type* p_DG;
	p_G0xData->CopyDG_List(DG_List, p_G0xData->m_Show_List);
	BOOL NtDefined = FALSE;
#ifdef WINDOWSNT
	NtDefined = TRUE;
#endif
	//LoadDelgenTable();
	BOOL FpgaMemoryExist = p_G0xData->FpgaMemoryExist();
	if ((PreviousDataSize.cx > 0) && (PreviousDataSize.cy > 0))
	{
		COLORREF clr = p_ClientDC->GetBkColor();
		CRect rect;
		rect.SetRect(0, 0, PreviousDataSize.cx, PreviousDataSize.cy);
		p_ClientDC->FillSolidRect(rect, clr);
	}
	CSize TextExtent;
	TextExtent.cx = 0;
	TextExtent.cy = 0;
	CSize LineExtent;
	CListRout lr;
	ResetLinePosition(ScrollPosition);
	CString kstr,jstr;
	int NoDelgen = DG_List.GetCount();
	if (NoDelgen > 0)
	{
		int Count = 0;
		NewLine();
		kstr = "Delay Generators:";
		//p_ClientDC->LPtoDP(&pt);
		SetPrivateFont(p_ClientDC, HeadingFont);
		WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
		POSITION pos = DG_List.GetHeadPosition();
		while (pos != NULL)
		{
			p_DG = DG_List.GetNext(pos);
			SetPrivateFont(p_ClientDC, RegularFont);
			NewLine();
			SetPrivateFont(p_ClientDC, MinorHeadingFont);
			if (strlen(p_DG->DG_Name) > 0)
			{
				kstr = lr.ReadMemo(p_DG->DG_Name);
				kstr += "   ";
			}
			else
				kstr = _T("");
			switch (p_DG->Product)
			{
			case BME_G02V1:
				kstr += "BME_G02V1    ";
				break;
			case BME_G02V2:
				kstr += "BME_G02V2    ";
				break;
			case BME_G02V3:
				kstr += "BME_G02V3    ";
				break;
			case BME_SG02V1:
				kstr += "BME_SG02V1   ";
				break;
			case BME_SG02V2:
				kstr += "BME_SG02V2   ";
				break;
			case BME_SG02V3:
				kstr += "BME_SG02V3   ";
				break;
			case BME_SG02V4:
				kstr += "BME_SG02V4   ";
				break;
			case BME_SG02V5:
				kstr += "BME_SG02V5   ";
				break;
			case BME_SG02V6:
				kstr += "BME_SG02V6   ";
				break;
			case BME_SG02V7:
				kstr += "BME_SG02V7   ";
				break;
			case BME_SG02P1:
				kstr += "BME_SG02P1   ";
				break;
			case BME_SG02P2:
				kstr += "BME_SG02P2   ";
				break;
			case BME_SG02P3:
				kstr += "BME_SG02P3   ";
				break;
			case BME_SG02P4:
				kstr += "BME_SG02P4   ";
				break;
			case BME_SG02P5:
				kstr += "BME_SG02P5   ";
				break;
			case BME_G03V1:
				kstr += "BME_G03V1    ";
				break;
			case BME_G03V2:
				kstr += "BME_G03V2    ";
				break;
			case BME_G03V3:
				kstr += "BME_G03V3    ";
				break;
			case BME_G03V4:
				kstr += "BME_G03V4    ";
				break;
			case BME_G03V5:
				kstr += "BME_G03V5    ";
				break;
			case BME_G03P1:
				kstr += "BME_G03P1    ";
				break;
			case BME_G03P2:
				kstr += "BME_G03P2    ";
				break;
			case BME_G05V1:
				kstr += "BME_G05V1    ";
				break;
			case BME_G05V2:
				kstr += "BME_G05V2    ";
				break;
			case BME_G05V3:
				kstr += "BME_G05V3    ";
				break;
			case BME_G05P1:
				kstr += "BME_G05P1    ";
				break;
			case BME_G05P2:
				kstr += "BME_G05P2    ";
				break;
			case BME_G05P3:
				kstr += "BME_G05P3    ";
				break;
			case BME_SG05P1:
				kstr += "BME_SG05P1   ";
				break;
			case BME_SG05P2:
				kstr += "BME_SG05P2   ";
				break;
			case BME_SG05P3:
				kstr += "BME_SG05P3   ";
				break;
			case BME_SG08P1:
				kstr += "BME_SG08P1   ";
				break;
			case BME_SG08P2:
				kstr += "BME_SG08P2   ";
				break;
			}
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			SetPrivateFont(p_ClientDC, RegularFont);
			if (p_DG->Master)
				kstr = _T("Master card,  ");
			else
				kstr = _T("Slave card,   ");
			switch (p_DG->Product)
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
				jstr.Format("in slot no. %d,  bus no. %d", p_DG->BaseAddress, p_DG->BusNumber);
				if (strlen(p_DG->ip_address) > 0)
				{
					jstr += ",  Ethernet Address: ";
					jstr += lr.ReadMemo(p_DG->ip_address);
				}
				break;
			default:
				jstr.Format("Base address : 0x%x", p_DG->BaseAddress);
				break;
			}
			kstr += jstr;
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			switch (p_DG->Product)
			{
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
			case BME_G03V1:
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
				if (!p_DG->Master)
					break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				if (p_DG->Control.DT.ClockEnable)
					kstr = _T("Clock : active");
				else
					kstr = _T("Clock : disabled");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				if (p_DG->Control.DT.ClockEnable)
				{
					if ((p_DG->Control.DT.ClockSource == CrystalOscillator) ||
												(p_DG->Control.DT.ClockSource == MasterSlaveBus))
					{
						kstr.Format("    Prescaler divide by : %d", p_DG->Control.DT.OscillatorDivider);
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						if (p_DG->Control.DT.ClockSource == CrystalOscillator)
							kstr = _T("    Clock source  :  Internal quarz oscillator");
						else
							kstr = _T("    Clock source  :  Master/Slave bus");
					}
					else
					{
						kstr.Format("    Prescaler divide by : %d", p_DG->Control.DT.TriggerDivider);
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						if (p_DG->Control.DT.TriggerMultiplier > 1)
						{
							kstr.Format("    external clock multiplied by : %d", p_DG->Control.DT.TriggerMultiplier);
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						}
						if (p_DG->Control.DT.Terminate)
							kstr = _T("    Clock source  :  External trigger input (50 ohms)");
						else
							kstr = _T("    Clock source  :  External trigger input (high-Z)");
						if (p_DG->Control.DT.ClockSource == TriggerAndOscillator)
						{
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							kstr = _T("    Backup clock  :  Internal quarz oscillator");
						}
						switch (p_DG->Product)
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
						case BME_SG08P1:
						case BME_SG08P2:
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							kstr.Format("        trigger level : %6.5f", p_DG->Control.DT.TriggerLevel);
							kstr = lr.TrimTrailingZeros(kstr);
							kstr += " V";
							break;
						default:
							break;
						}
					}
					WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				}
				BOOL ValidTrigger = FALSE;
				if (p_G0xData->b_DelayGeneratorsActive)
				{
					if (p_DG->Control.DT.TriggerEnable) 
					{
						kstr = _T("Trigger :  active");
						ValidTrigger = TRUE;
					}
					else
					{
						switch (p_DG->Product)
						{
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
						case BME_SG08P1:
						case BME_SG08P2:
							kstr = _T("Trigger :  enabled by external gate");
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							if (p_DG->Control.DT.GateDivider <= 0)
							{
								if (p_DG->Control.DT.PositiveGate)
									kstr = _T("    trigger is enabled while external gate is HIGH");
								else
									kstr = _T("    trigger is enabled while external gate is LOW");
								if (p_DG->Control.DT.UseF)
								{
									WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
									kstr = _T("        signal from F output connector replaces the gate signal");
								}
							}
							else
							{
								if (p_DG->Control.DT.PositiveGate)
									kstr = _T("    trigger is enabled by Rising edge of external gate signal");
								else
									kstr = _T("    trigger is enabled by Falling edge of external gate signal");
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								if ((p_DG->Control.DT.MS_Bus & Resynchronize) != 0x0)
								{
									if ((p_DG->Control.DT.ClockSource == CrystalOscillator) ||
												(p_DG->Control.DT.ClockSource == MasterSlaveBus))
									{
										if (p_DG->Control.DT.OscillatorDivider > 1)
										{
											kstr = _T("        internal clock signal will be resynchronized to the nearest input clock period");
											WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
										}
									}
									else
									{
										if (p_DG->Control.DT.TriggerDivider > 1)
										{
											kstr = _T("        internal clock signal will be resynchronized to the nearest input clock period");
											WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
										}
									}
								}
								kstr.Format("        divisor for external gate signal : %d", p_DG->Control.DT.GateDivider);
							}
							switch (p_DG->Product)
							{
							case BME_SG08P1:
							case BME_SG08P2:
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								kstr.Format("        gate threshold level : %6.5f", p_DG->Control.DT.GateLevel);
								kstr = lr.TrimTrailingZeros(kstr);
								kstr += " V";
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								if (p_DG->Control.DT.GateTerminate)
									kstr = _T("        gate input is terminated with 50 ohms");
								else
									kstr = _T("        gate input is high-Z");
								if ((p_DG->Control.DT.MS_Bus & GateOnBusPositive) != 0x0)
								{
									WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
									kstr = _T("        gate signal is placed as start signal on the master/slave bus with positive polarity");
								}
								if ((p_DG->Control.DT.MS_Bus & GateOnBusNegative) != 0x0)
								{
									WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
									kstr = _T("        gate signal is placed as start signal on the master/slave bus with negative polarity");
								}
								if (p_DG->Control.DT.GateDelay > 0.0)
								{
									WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
									kstr.Format("        gate signal delay : %6.5f", p_DG->Control.DT.GateDelay);
									kstr = lr.TrimTrailingZeros(kstr);
								}
								break;
							default:
								break;
							}
							ValidTrigger = TRUE;
							break;
						default:
							kstr = _T("Trigger :  disabled");
							break;
						}
					}
				}
				else
					kstr = _T("Trigger :  disabled");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				if (ValidTrigger)
				{
					switch (p_DG->Product)
					{
					case BME_SG02P3:
					case BME_SG02P4:
					case BME_SG02P5:
					case BME_G05P2:
					case BME_G05P3:
					case BME_SG05P1:
					case BME_SG05P2:
					case BME_SG05P3:
					case BME_SG08P1:
					case BME_SG08P2:
						if (p_DG->Control.DT.InternalTrigger)
							kstr = _T("    Trigger mode:  Internal clock signal");
						else
							kstr = _T("    Trigger mode:  external trigger input");
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						if (p_DG->Control.DT.InhibitTrigger > 0.0)
						{
							kstr.Format("        Inhibit time after valid trigger event : %6.5f", 
																																	p_DG->Control.DT.InhibitTrigger);
							kstr = lr.TrimTrailingZeros(kstr);
							kstr += _T(" usec");
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							if (!p_DG->Control.DT.TriggerEnable) 
							{
								if (p_DG->Control.DT.DelaySecondary > 0)
								{
									kstr.Format("          the first %d delay cycles after a valid trigger signal will have an inhibit time of %6.5f", 
															p_DG->Control.DT.DelaySecondary, p_DG->Control.DT.InhibitSecondary);
									kstr = lr.TrimTrailingZeros(kstr);
									kstr += _T(" usec");
									WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								}
								if (p_DG->Control.DT.IgnoreGate)
									kstr = _T("          Gate events occurring during the inhibit phase will be ignored");
								else
									kstr = _T("          Gate events occurring during the inhibit phase will be memorized");
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							}
						}
						if (p_DG->Control.DT.ForceTrigger > 0.0)
						{
							kstr.Format("        Forced trigger comes %6.5f", p_DG->Control.DT.ForceTrigger);
							kstr = lr.TrimTrailingZeros(kstr);
							kstr += _T(" usec after valid trigger event");
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						}
						break;
					default:
						if (p_DG->Control.DT.InternalTrigger)
							kstr = _T("    Trigger mode:  Internal rate generator");
						else
						{
							if (p_DG->Control.DT.InternalArm)
								kstr = _T("    Trigger mode:  Internal rate generator arms external trigger");
							else
								kstr = _T("    Trigger mode:  external trigger input");
						}
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						if ((p_DG->Control.DT.InternalTrigger) || (p_DG->Control.DT.InternalArm))
						{
							if (p_DG->Control.DT.InternalClock > 0.0)
							{
								kstr.Format("        Period of internal rate generator : %6.5f", 
																																		p_DG->Control.DT.InternalClock);
								kstr = lr.TrimTrailingZeros(kstr);
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							}
						}
						break;
					}
					if (!p_DG->Control.DT.InternalTrigger)
					{
						if (p_DG->Control.DT.RisingEdge)
							kstr = _T("        external signal generates trigger on rising slope");
						else
							kstr = _T("        external signal generates trigger on falling slope");
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						if (p_DG->Control.DT.ClockSource == CrystalOscillator)
						{
							if (p_DG->Control.DT.Terminate)
								kstr = _T("        external trigger input is terminated with 50 ohms");
							else
								kstr = _T("        external trigger input is high-Z");
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							switch (p_DG->Product)
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
							case BME_SG08P1:
							case BME_SG08P2:
								kstr.Format("        trigger level : %6.5f", p_DG->Control.DT.TriggerLevel);
								kstr = lr.TrimTrailingZeros(kstr);
								kstr += " V";
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
								break;
							default:
								break;
							}
						}
					}
					switch (p_DG->Product)
					{
					case BME_SG08P1:
					case BME_SG08P2:
						if (p_DG->Control.DT.BurstCounter > 1)
						{
							kstr = _T("    Burst Trigger Mode enabled");
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							kstr.Format("        number of pulses after valid trigger event: %d", (p_DG->Control.DT.BurstCounter));
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						}
						if (FpgaMemoryExist)
						{
							if (p_DG->Control.DT.StepBackTime > 0.0)
							{
								kstr.Format("    Local step back signal generated after: %6.5f", p_DG->Control.DT.StepBackTime);
								kstr = lr.TrimTrailingZeros(kstr);
								kstr += " usec";
								WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
							}
						}
						break;
					default:
						break;
					}
					if (p_DG->Master)
					{
						if (p_DG->Control.DT.ResetWhenDone)
							kstr = _T("    outputs will automatically reset when all delays have elapsed");
						else
							kstr = _T("    outputs must be reset by software when all delays have elapsed");
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
					}
					if (p_DG->Control.DT.StopOnPreset)
					{
						kstr.Format("    trigger will be disabled after %d events", p_DG->Control.DT.PresetValue);
						WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
					}
					if ((p_G0xData->p_OpInfo != NULL) && (p_DG->ReadTriggers) && (NtDefined))
					{
						if ((p_G0xData->p_OpInfo + Count)->TriggerEvents != 0)
						{
							kstr.Format("    no. of trigger events : %1.0f", 
															double((p_G0xData->p_OpInfo + Count)->Trigger64Events));
							WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
						}
						//kstr.Format("    delay generator status : %x", (p_G0xData->p_OpInfo + Count)->DG_Status);
						//WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
					}
				}
				break;
			}

			switch (p_DG->Product)
			{
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
			case BME_G05V3:
			case BME_G05P1:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				switch (p_DG->Control.OutputLevel)
				{
				case TTL_VoltageLevel:
					kstr = _T("voltage level for all outputs:   TTL");
					break;
				case NIM_VoltageLevel:
					kstr = _T("voltage level for all outputs:   NIM");
					break;
				case ECL_VoltageLevel:
					kstr = _T("voltage level for all outputs:   ECL");
					break;
				default:
					break;
				}
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				break;
			default:
				break;
			}
			switch (p_DG->Product)
			{
			case BME_G05V3:
			case BME_G05P1:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				kstr.Format("pulse width:  %d clock cycles", p_DG->Control.PulseWidth);
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				break;
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
				if (p_DG->Control.PulseWidth > 0)
					kstr.Format("pulse width:  %d clock cycles", p_DG->Control.PulseWidth);
				else
					kstr.Format("pulse reset 8 clock cycles after last delay elapses");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				break;
			default:
				break;
			}
			switch (p_DG->Product)
			{
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
			case BME_G03V1:
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
				if (strlen(p_DG->T0_Name) > 0)
				{
					kstr = lr.ReadMemo(p_DG->T0_Name);
					kstr += ",  ";
				}
				else
					kstr = _T("");
				kstr += "T delaychannel : ";
				WriteChannelVariables(kstr, p_DG->Control.T0, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.T0,
																				TextExtent, LineExtent, p_ClientDC);
				break;
			default:
				break;
			}

			if (strlen(p_DG->A_Name) > 0)
			{
				kstr = lr.ReadMemo(p_DG->A_Name);
				kstr += ",  ";
			}
			else
				kstr = _T("");
			kstr += "A delaychannel : ";
			WriteChannelVariables(kstr, p_DG->Control.A, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.A,
																				TextExtent, LineExtent, p_ClientDC);

			if (strlen(p_DG->B_Name) > 0)
			{
				kstr = lr.ReadMemo(p_DG->B_Name);
				kstr += ",  ";
			}
			else
				kstr = _T("");
			kstr += "B delaychannel : ";
			WriteChannelVariables(kstr, p_DG->Control.B, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.B,
																				TextExtent, LineExtent, p_ClientDC);
			if (((p_DG->Control.A.GoSignal & 0x77) != 0x0) && ((p_DG->Control.B.GoSignal & 0x77) != 0x0))
			{
				switch (p_DG->Product)
				{
				case BME_SG08P1:
				case BME_SG08P2:
					if ((p_DG->Control.GateFunction & AB_XOR) != 0)
						kstr = _T("channels A and B are combined to form a gate output");
					else
						kstr = _T("channels A and B give independent delayed pulse outputs");
					break;
				default:
					if (p_DG->Control.Gate_AB)
						kstr = _T("channels A and B are combined to form a gate output");
					else
					{
						switch (p_DG->Product)
						{
						case BME_G05V3:
						case BME_G05P1:
						case BME_G05P2:
						case BME_G05P3:
						case BME_SG05P1:
						case BME_SG05P2:
						case BME_SG05P3:
							kstr = _T("channels A and B give independent delayed pulse outputs");
							break;
						case BME_SG02V7:
						case BME_SG02P1:
						case BME_SG02P2:
						case BME_SG02P3:
						case BME_SG02P4:
						case BME_SG02P5:
							if (p_DG->Control.PulseWidth > 0)
								kstr = _T("channels A and B give independent delayed pulse outputs");
							else
								kstr = _T("channels A and B give independent delayed slope outputs");
							break;
						default:
							kstr = _T("channels A and B give independent delayed slope outputs");
							break;
						}
					}
					break;
				}
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			switch (p_DG->Product)
			{
			case BME_SG08P1:
			case BME_SG08P2:
				if (strlen(p_DG->C_Name) > 0)
				{
					kstr = lr.ReadMemo(p_DG->C_Name);
					kstr += ",  ";
				}
				else
					kstr = _T("");
				kstr += "C delaychannel : ";
				WriteChannelVariables(kstr, p_DG->Control.C, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.C,
																				TextExtent, LineExtent, p_ClientDC);
				if (strlen(p_DG->D_Name) > 0)
				{
					kstr = lr.ReadMemo(p_DG->D_Name);
					kstr += ",  ";
				}
				else
					kstr = _T("");
				kstr += "D delaychannel : ";
				WriteChannelVariables(kstr, p_DG->Control.D, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.D,
																				TextExtent, LineExtent, p_ClientDC);
				if (((p_DG->Control.C.GoSignal & 0x77) != 0x0) && ((p_DG->Control.D.GoSignal & 0x77) != 0x0) &&
																																	(p_G0xData->b_DelayGeneratorsActive))
				{
					if ((p_DG->Control.GateFunction & CD_XOR) != 0)
						kstr = _T("channels C and D are combined to form a gate output");
					else
						kstr = _T("channels C and D give independent delayed pulse outputs");
					WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				}
				if (strlen(p_DG->E_Name) > 0)
				{
					kstr = lr.ReadMemo(p_DG->E_Name);
					kstr += ",  ";
				}
				else
					kstr = _T("");
				kstr += "E delaychannel : ";
				WriteChannelVariables(kstr, p_DG->Control.E, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.E,
																				TextExtent, LineExtent, p_ClientDC);
				if (strlen(p_DG->F_Name) > 0)
				{
					kstr = lr.ReadMemo(p_DG->F_Name);
					kstr += ",  ";
				}
				else
					kstr = _T("");
				kstr += "F delaychannel : ";
				WriteChannelVariables(kstr, p_DG->Control.F, FpgaMemoryExist, p_G0xData, p_DG, p_DG->VarLoc.F,
																				TextExtent, LineExtent, p_ClientDC);
				if (((p_DG->Control.E.GoSignal & 0x77) != 0x0) && ((p_DG->Control.F.GoSignal & 0x77) != 0x0) &&
																																	(p_G0xData->b_DelayGeneratorsActive))
				{
					if ((p_DG->Control.GateFunction & EF_XOR) != 0)
						kstr = _T("channels E and F are combined to form a gate output");
					else
						kstr = _T("channels E and F give independent delayed pulse outputs");
					WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
				}
				break;
			default:
				break;
			}
			Count++;
		}
		if (FpgaMemoryExist)
		{
			NewLine();
			kstr = "Fpga Memory Variables:";
			//p_ClientDC->LPtoDP(&pt);
			SetPrivateFont(p_ClientDC, HeadingFont);
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			SetPrivateFont(p_ClientDC, RegularFont);
			NewLine();
			CStringArray m_FpgaMemoryList;
			p_G0xData->ReadFpgaMemory(m_FpgaMemoryList);
			Count = m_FpgaMemoryList.GetSize();
			int i1;
			for (i1 = 0; i1 < Count; i1++)
			{
				kstr = m_FpgaMemoryList.GetAt(i1);
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			NewLine();
		}
		if (p_G0xData->VariablesExist())
		{
			NewLine();
			kstr = "Sweep Variables:";
			//p_ClientDC->LPtoDP(&pt);
			SetPrivateFont(p_ClientDC, HeadingFont);
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			SetPrivateFont(p_ClientDC, RegularFont);
			NewLine();
			XParameterType vct;
			CStringArray m_XParameterList;
			p_G0xData->ReadXParameter(m_XParameterList, vct);
			Count = m_XParameterList.GetSize();
			int i1;
			for (i1 = 0; i1 < Count; i1++)
			{
				kstr = m_XParameterList.GetAt(i1);
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			NewLine();
			if (vct.m_Once)
			{
				kstr = _T("list of variables will be stepped through once");
				if (vct.m_BothDirection)
					kstr += " in both directions";
			}
			else
			{
				if (vct.m_SubcycleLimit)
				{
					kstr.Format("stepping through the list will be stopped after %d steps", 
																															vct.MaxSubcycles);
				}
				else
					kstr = _T("list of variables will be stepped through continuously");
			}
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			kstr.Format("time per step : %4.3f", (double(vct.MilliSecondsPerStep) / 1000.0));
			kstr = lr.TrimTrailingZeros(kstr);
			kstr += " seconds";
			WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			if (vct.m_BothDirection)
			{
				kstr = _T("list will be stepped through both directions");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			if (vct.m_Upwards)
			{
				kstr = _T("delay generators are first loaded with parameters from the first line");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
			if (vct.m_Downwards)
			{
				kstr = _T("delay generators are first loaded with parameters from the last line");
				WriteLine(kstr, TextExtent, LineExtent, p_ClientDC);
			}
		}
	}
	TextExtent.cx += 10;
	TextExtent.cy = YPosition + ScrollPosition.y + 20;
	p_G0xData->InitializeDG_List(DG_List);
	return TextExtent;
}

