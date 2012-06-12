// ConfigurationTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "ConfigurationTableDlg.h"
#include "EthernetAddressDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigurationTableDlg dialog


CConfigurationTableDlg::CConfigurationTableDlg(CG0xData* p_GDat, CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigurationTableDlg)
	m_CalibrateTiming = FALSE;
	m_CalibrateOffset = FALSE;
	//}}AFX_DATA_INIT
	p_G0xData = p_GDat;
	p_G0xData->CopyDG_List(DG_List, p_G0xData->m_DG_List);
	m_CalibrateTiming = p_G0xData->b_CalibrateTiming;
	if (m_CalibrateTiming)
	{
		if (p_G0xData->m_CalibrationLevel >= CalibrateOffset)
			m_CalibrateOffset = TRUE;
	}
	b_DelgenTableLoaded = FALSE;
	b_DataModified = FALSE;
	p_DefineDelayGeneratorDlg = new CDefineDelayGeneratorDlg(p_G0xData, this);
	p_DefineDelayGeneratorDlg->p_DelgenTableCB = &m_DelgenTableCB;
	p_DefineDelayGeneratorDlg->p_DG_List = &DG_List;
	p_DefineDelayGeneratorDlg->p_DataModified = &b_DataModified;
}

CConfigurationTableDlg::~CConfigurationTableDlg()
{
	delete p_DefineDelayGeneratorDlg;
	b_DelgenTableLoaded = FALSE;
	p_G0xData->InitializeDG_List(DG_List);
}

void CConfigurationTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigurationTableDlg)
	DDX_Control(pDX, IDC_DELGEN_TABLE, m_DelgenTableCB);
	DDX_Check(pDX, IDC_CALIBRATE_TIMING, m_CalibrateTiming);
	DDX_Check(pDX, IDC_CALIBRATE_OFFSET, m_CalibrateOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigurationTableDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigurationTableDlg)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DEFINE_DELAY_GENERATOR, OnDefineDelayGenerator)
	ON_CBN_SELENDOK(IDC_DELGEN_TABLE, OnSelendokDelgenTable)
	ON_BN_CLICKED(IDC_REMOVE_DELAY_GENERATOR, OnRemoveDelayGenerator)
	ON_CBN_SETFOCUS(IDC_DELGEN_TABLE, OnSetfocusDelgenTable)
	ON_BN_CLICKED(IDC_CALIBRATE_TIMING, OnCalibrateTiming)
	ON_BN_CLICKED(IDC_DETECT_PCI, OnDetectPci)
	ON_BN_CLICKED(IDC_ADD_ETHERNET, OnAddEthernet)
	ON_BN_CLICKED(IDC_CALIBRATE_OFFSET, OnCalibrateOffset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigurationTableDlg message handlers

BOOL CConfigurationTableDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CConfigurationTableDlg::OnDefineDelayGenerator() 
{
	if (!b_DelgenTableLoaded)
	{
		LoadDelgenTable();
		b_DelgenTableLoaded = TRUE;
	}
	p_DefineDelayGeneratorDlg->Create(IDD_DEFINE_DELAY_GENERATOR, this);
}

void CConfigurationTableDlg::OnAddEthernet() 
{
	CListRout lr;
	CEthernetAddressDlg dlg;
	dlg.m_IpAddress = _T("");
	if (dlg.DoModal() == IDOK)
	{
		CString jstr = dlg.m_IpAddress;
		lr.TrimString(jstr);
		if (lr.EthernetAddress((LPCTSTR) jstr))
		{
			char IpAddr[40];
			memset(IpAddr, 0, (40 * sizeof(char)));
		  lr.WriteMemo(IpAddr, (LPCTSTR)jstr, 24);
			long Error;
			long NoDelgen = p_G0xData->AddEthernetDelayGenerators(&Error, IpAddr);
			switch (Error)
			{
				case 0:
					break;
				case 1:
					//AfxMessageBox("A slave card has not been connected to its master!",MB_OK,0);
					//return;
					break;
				case 0x228:
					AfxMessageBox("no PLX chip has been detected while booting the computer!",MB_OK,0);
					return;
				default:
					AfxMessageBox("Error detecting PCI Delay Generators!",MB_OK,0);
					return;
			}
			if (NoDelgen <= 0)
			{
				AfxMessageBox("No PCI Delay Generators detected!",MB_OK,0);
				return;
			}
			int FirstPos = DG_List.GetCount();
			int DelgenCount = FirstPos + NoDelgen;
			LoadDelgenList(FirstPos, DelgenCount, IpAddr);
		}
		else
			AfxMessageBox("Invalid Ethernet Address!",MB_OK,0);
	}
}

void CConfigurationTableDlg::OnDetectPci() 
{
	if (DG_List.GetCount() > 0)
	{
		CString str = "  Remove all current Delay Generator Definitions \n";
		str += "and create new list containing all PCI Delay Generators ?";
		if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDNO)
			return;
	}
	p_G0xData->InitializeDG_List(DG_List);
	m_DelgenTableCB.ResetContent();
	b_DelgenTableLoaded = FALSE;
	long Error;
	long NoDelgen = p_G0xData->DetectPciDelayGenerators(&Error);
	switch (Error)
	{
		case 0:
			break;
		case 1:
			//AfxMessageBox("A slave card has not been connected to its master!",MB_OK,0);
			//return;
			break;
		case 0x228:
			AfxMessageBox("no PLX chip has been detected while booting the computer!",MB_OK,0);
			return;
		default:
			AfxMessageBox("Error detecting PCI Delay Generators!",MB_OK,0);
			return;
	}
	if (NoDelgen <= 0)
	{
		AfxMessageBox("No PCI Delay Generators detected!",MB_OK,0);
		return;
	}
	char IpAddr[40];
	memset(IpAddr, 0, (40 * sizeof(char)));
	LoadDelgenList(0, NoDelgen, IpAddr);
}

void CConfigurationTableDlg::LoadDelgenList(int FirstPos, int NoDelgen, char* p_IpAddr) 
{
	CListRout lr;
	DG_Type* p_DG;
	int i1;
	int MaxLines = 3;
	CString jstr = "The following PCI Delay Generators have been detected: \n";
	CString kstr;
	BOOL ErrorStatementWritten = FALSE;
	char IpAddr[40];
	long BusNumber;
	long SlotNumber;
	long GetPciResult;
	char	UcIpAddr[40];
	long	UcBusNumber;
	long	UcBaseAddress;
	long	UcProduct;
	long	UcLineMaster[8];
	BOOL  UcMaster;
	int LineNo;
	if (&(p_IpAddr) != 0)
		jstr += ("         Ethernet Address: " + lr.ReadMemo(p_IpAddr) + " \n");
	for (i1 = FirstPos; i1 < NoDelgen; i1++)
	{
		p_DG = new DG_Type;
		p_G0xData->ResetDG_Element(p_DG);
		p_DG->Control.DT.ResetWhenDone = TRUE;
		p_DG->Control.DT.TriggerEnable = TRUE;
		p_DG->Control.DT.ClockEnable = TRUE;
//		GetPciResult = p_G0xData->GetPciDelayGenerator((long*)&(p_DG->Product), 
//																				(long*)&(p_DG->BaseAddress), &(p_DG->Master), i1);
		GetPciResult = p_G0xData->GetEthernetDelayGenerator((long*)&(p_DG->Product),
										&(IpAddr[0]), &BusNumber, &SlotNumber, &(p_DG->Master), i1);
		//kstr.Format("GetPciResult: %d,    ", GetPciResult);
		//AfxMessageBox(kstr,MB_OK,0);
		p_DG->SlotNumber = (unsigned short)SlotNumber;
		p_DG->BusNumber = (signed short)BusNumber;
		memcpy(&(p_DG->ip_address[0]), &(IpAddr[0]), (40 * sizeof(char)));
		p_DG->Control.DG_Product = p_DG->Product;
		p_DG->Control.PulseWidth = 8;
		switch (p_DG->Product)
		{
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G05P3:
		case BME_SG05P2:
		case BME_SG05P3:
		case BME_SG08P1:
		case BME_SG08P2:
			p_DG->Control.DT.MS_Bus |= Resynchronize;
			break;
		default:
			break;
		}		
		switch (p_DG->Product)
		{
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P3:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			MaxLines = 3;
			p_DG->Control.DT.OscillatorDivider = 8;
			break;
		case BME_SG08P1:
		case BME_SG08P2:
			MaxLines = 8;
			p_DG->Control.PulseWidth = 0;
			p_DG->Control.DT.OscillatorDivider = 16;
			break;
		default:
			MaxLines = 3;
			break;
		}
		switch (p_DG->Product)
		{
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
		case BME_G03P1:
		case BME_G03P2:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
			if (GetPciResult == 0)
				DG_List.AddTail(p_DG);
			break;
		default:
			delete p_DG;
			break;
		}
		if (GetPciResult != 0)
		{
			if (!ErrorStatementWritten)
			{
				jstr += "\n\n";
				jstr += "The following PCI Delay Generators are not correctly connected: \n";
				ErrorStatementWritten = TRUE;
			}
		}
		jstr += "\n          ";
		switch (p_DG->Product)
		{
		case BME_SG02P1:
			jstr += "BME_SG02P1,   ";
			break;
		case BME_SG02P2:
			jstr += "BME_SG02P2,   ";
			break;
		case BME_SG02P3:
			jstr += "BME_SG02P3,   ";
			break;
		case BME_SG02P4:
			jstr += "BME_SG02P4,   ";
			break;
		case BME_SG02P5:
			jstr += "BME_SG02P5,   ";
			break;
		case BME_G03P1:
			jstr += "BME_G03P1,    ";
			break;
		case BME_G03P2:
			jstr += "BME_G03P2,    ";
			break;
		case BME_G05P1:
			jstr += "BME_G05P1,    ";
			break;
		case BME_G05P2:
			jstr += "BME_G05P2,    ";
			break;
		case BME_G05P3:
			jstr += "BME_G05P3,    ";
			break;
		case BME_SG05P1:
			jstr += "BME_SG05P1,   ";
			break;
		case BME_SG05P2:
			jstr += "BME_SG05P2,   ";
			break;
		case BME_SG05P3:
			jstr += "BME_SG05P3,   ";
			break;
		case BME_SG08P1:
			jstr += "BME_SG08P1,   ";
			break;
		case BME_SG08P2:
			jstr += "BME_SG08P2,   ";
			break;
		}
		kstr.Format("Bus no. %d,    ", p_DG->BusNumber);
		jstr += kstr;
		kstr.Format("Slot no. %d,    ", p_DG->SlotNumber);
		jstr += kstr;
		if (p_DG->Master)
			jstr += "master";
		else
		{
			jstr += "slave";
			switch (p_DG->Product)
			{
			case BME_SG08P1:
			case BME_SG08P2:
				p_DG->Control.DT.OscillatorDivider = 1;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				p_DG->Control.DT.ClockSource = MasterSlaveBus;
				break;
			default:
				break;
			}
		}
		if (GetPciResult != 0)
		{
			delete p_DG;
			p_G0xData->GetUnconnectedEthernetDelayGenerator(&(UcProduct),
											&(UcIpAddr[0]), &(UcBusNumber), &(UcBaseAddress), &(UcLineMaster[0]), i1);
			for (LineNo = 0; LineNo < MaxLines; LineNo++)
			{
				jstr += "\n                    ";
				if (UcLineMaster[LineNo] >= 0)
				{
					kstr.Format("Line no. %d, connected to  ", LineNo);
					jstr += kstr;
					p_G0xData->GetEthernetDelayGenerator(&(UcProduct), 
											&(UcIpAddr[0]), &(UcBusNumber), &(UcBaseAddress), &(UcMaster), UcLineMaster[LineNo]);
					switch (UcProduct)
					{
					case BME_SG02P1:
						jstr += "BME_SG02P1,   ";
						break;
					case BME_SG02P2:
						jstr += "BME_SG02P2,   ";
						break;
					case BME_SG02P3:
						jstr += "BME_SG02P3,   ";
						break;
					case BME_SG02P4:
						jstr += "BME_SG02P4,   ";
						break;
					case BME_SG02P5:
						jstr += "BME_SG02P5,   ";
						break;
					case BME_G03P1:
						jstr += "BME_G03P1,    ";
						break;
					case BME_G03P2:
						jstr += "BME_G03P2,    ";
						break;
					case BME_G05P1:
						jstr += "BME_G05P1,    ";
						break;
					case BME_G05P2:
						jstr += "BME_G05P2,    ";
						break;
					case BME_G05P3:
						jstr += "BME_G05P3,    ";
						break;
					case BME_SG05P1:
						jstr += "BME_SG05P1,   ";
						break;
					case BME_SG05P2:
						jstr += "BME_SG05P2,   ";
						break;
					case BME_SG05P3:
						jstr += "BME_SG05P3,   ";
						break;
					case BME_SG08P1:
						jstr += "BME_SG08P1,   ";
						break;
					case BME_SG08P2:
						jstr += "BME_SG08P2,   ";
						break;
					}
					kstr.Format("Bus no. %d,    ", UcBusNumber);
					jstr += kstr;
					kstr.Format("Slot no. %d,    ", UcBaseAddress);
					jstr += kstr;
				}
				else
				{
					kstr.Format("Line no. %d is unconnected  ", LineNo);
					jstr += kstr;
				}
			}
		}
	}
	LoadDelgenTable();
	b_DelgenTableLoaded = TRUE;
	AfxMessageBox(jstr, (MB_OK | MB_ICONINFORMATION), 0);
}

void CConfigurationTableDlg::OnSelendokDelgenTable() 
{
	p_DefineDelayGeneratorDlg->ReadSelectedLine();
}

void CConfigurationTableDlg::OnCalibrateTiming() 
{
	UpdateData(TRUE);
	if (!m_CalibrateTiming)
		m_CalibrateOffset = FALSE;
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CConfigurationTableDlg::OnCalibrateOffset() 
{
	UpdateData(TRUE);
	if (m_CalibrateOffset)
		m_CalibrateTiming = TRUE;
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CConfigurationTableDlg::OnRemoveDelayGenerator() 
{
	if (!b_DelgenTableLoaded)
	{
		LoadDelgenTable();
		b_DelgenTableLoaded = TRUE;
	}
	CListRout lr;
	int LineNo = m_DelgenTableCB.GetCurSel();
	BOOL success = lr.DeleteSelectedLine(m_DelgenTableCB);
	if (!success)
		AfxMessageBox("no line removed!",MB_OK,0);
	else
	{
		POSITION pos = DG_List.FindIndex(LineNo);
		DG_Type* p_DG = DG_List.GetAt(pos);
		DG_List.RemoveAt(pos);
		delete p_DG;
	  b_DataModified = TRUE;
	}
}

void CConfigurationTableDlg::LoadDelgenTable()
{
	CListRout lr;
	CString wstr,jstr;
	m_DelgenTableCB.ResetContent();
	DG_Type* p_DG;
	int Count = 1;
	POSITION pos = DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = DG_List.GetNext(pos);
		p_DG->Control.DG_Product = p_DG->Product;
		wstr.Format("   %2d : ", Count);
		switch (p_DG->Product)
		{
		case BME_G02V1:
			wstr += "BME_G02V1    ";
			break;
		case BME_G02V2:
			wstr += "BME_G02V2    ";
			break;
		case BME_G02V3:
			wstr += "BME_G02V3    ";
			break;
		case BME_SG02V1:
			wstr += "BME_SG02V1   ";
			break;
		case BME_SG02V2:
			wstr += "BME_SG02V2   ";
			break;
		case BME_SG02V3:
			wstr += "BME_SG02V3   ";
			break;
		case BME_SG02V4:
			wstr += "BME_SG02V4   ";
			break;
		case BME_SG02V5:
			wstr += "BME_SG02V5   ";
			break;
		case BME_SG02V6:
			wstr += "BME_SG02V6   ";
			break;
		case BME_SG02V7:
			wstr += "BME_SG02V7   ";
			break;
		case BME_SG02P1:
			wstr += "BME_SG02P1   ";
			break;
		case BME_SG02P2:
			wstr += "BME_SG02P2   ";
			break;
		case BME_SG02P3:
			wstr += "BME_SG02P3   ";
			break;
		case BME_SG02P4:
			wstr += "BME_SG02P4   ";
			break;
		case BME_SG02P5:
			wstr += "BME_SG02P5   ";
			break;
		case BME_G03V1:
			wstr += "BME_G03V1    ";
			break;
		case BME_G03V2:
			wstr += "BME_G03V2    ";
			break;
		case BME_G03V3:
			wstr += "BME_G03V3    ";
			break;
		case BME_G03V4:
			wstr += "BME_G03V4    ";
			break;
		case BME_G03V5:
			wstr += "BME_G03V5    ";
			break;
		case BME_G03P1:
			wstr += "BME_G03P1    ";
			break;
		case BME_G03P2:
			wstr += "BME_G03P2    ";
			break;
		case BME_G05V1:
			wstr += "BME_G05V1    ";
			break;
		case BME_G05V2:
			wstr += "BME_G05V2    ";
			break;
		case BME_G05V3:
			wstr += "BME_G05V3    ";
			break;
		case BME_G05P1:
			wstr += "BME_G05P1    ";
			break;
		case BME_G05P2:
			wstr += "BME_G05P2    ";
			break;
		case BME_G05P3:
			wstr += "BME_G05P3    ";
			break;
		case BME_SG05P1:
			wstr += "BME_SG05P1   ";
			break;
		case BME_SG05P2:
			wstr += "BME_SG05P2   ";
			break;
		case BME_SG05P3:
			wstr += "BME_SG05P3   ";
			break;
		case BME_SG08P1:
			wstr += "BME_SG08P1   ";
			break;
		case BME_SG08P2:
			wstr += "BME_SG08P2   ";
			break;
		}
		if (strlen(p_DG->DG_Name) > 0)
			wstr += (lr.ReadMemo(p_DG->DG_Name) + "   ");
		if (p_DG->Master)
			wstr += "master  ";
		else
			wstr += "slave  ";
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
			jstr.Format("%2d %2d ", p_DG->BaseAddress, p_DG->BusNumber);
			if (p_DG->ip_address[0] != 0)
				jstr += (lr.ReadMemo(p_DG->ip_address) + "  ");
			else
				jstr += " ";
			break;
		default:
			jstr.Format("0x%2x  ", p_DG->BaseAddress);
			break;
		}
		wstr += jstr;
		switch (p_DG->Product)
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
			if (!p_DG->Master)
				break;
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
		case BME_SG08P1:
		case BME_SG08P2:
			switch (p_DG->Control.DT.ClockSource)
			{
			case TriggerInput:
				switch (p_DG->Product)
				{
				case BME_SG08P1:
				case BME_SG08P2:
					wstr += "trigger ";
					if (p_DG->Control.DT.TriggerDivider >= 1)
					{
						jstr.Format("%1d ", max(1, p_DG->Control.DT.TriggerDivider));
						wstr += jstr;
					}
					if (p_DG->Control.DT.TriggerMultiplier > 1)
					{
						jstr.Format("mul %1d ", max(1, p_DG->Control.DT.TriggerMultiplier));
						wstr += jstr;
					}
					break;
				default:
					jstr.Format("trigger %1d ", max(1, p_DG->Control.DT.TriggerDivider));
					wstr += jstr;
					break;
				}
				break;
			case CrystalOscillator:
				jstr.Format("crystal %1d ", max(1, p_DG->Control.DT.OscillatorDivider));
				wstr += jstr;
				break;
			case MasterSlaveBus:
				jstr.Format("msbus %1d ", max(1, p_DG->Control.DT.OscillatorDivider));
				wstr += jstr;
				break;
			case TriggerAndOscillator:
				switch (p_DG->Product)
				{
				case BME_SG08P1:
				case BME_SG08P2:
					wstr += "switch ";
					jstr.Format("%1d ", max(1, p_DG->Control.DT.TriggerDivider));
					wstr += jstr;
					if (p_DG->Control.DT.TriggerMultiplier > 1)
					{
						jstr.Format("mul %1d ", max(1, p_DG->Control.DT.TriggerMultiplier));
						wstr += jstr;
					}
					jstr.Format("%1d ", max(1, p_DG->Control.DT.OscillatorDivider));
					wstr += jstr;
					break;
				default:
					jstr.Format("switch %1d %1d ", max(1, p_DG->Control.DT.TriggerDivider)
																				, max(1, p_DG->Control.DT.OscillatorDivider));
					wstr += jstr;
					break;
				}
				break;
			}
			switch (p_DG->Product)
			{
			case BME_G05P3:
			case BME_SG05P2:
			case BME_SG02P4:
				wstr += "rsync ";
				break;
			case BME_SG02P5:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				if ((p_DG->Control.DT.MS_Bus & Resynchronize) != 0x0)
					wstr += "rsync ";
				break;
			default:
				break;
			}
			if (p_DG->Control.DT.Terminate)
				wstr += "term ";
			switch (p_DG->Product)
			{
			case BME_SG08P1:
			case BME_SG08P2:
				if (p_DG->Control.DT.GateTerminate)
					wstr += "gtrm ";
				if (p_DG->Control.DT.UseF)
					wstr += "usef ";
				break;
			default:
				break;
			}
			wstr += " ";
		default:
			break;
		}
		switch (p_DG->Product)
		{
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			if (p_DG->Master)
			{
				if ((p_DG->Control.DT.MS_Bus & LocalPrimary) != 0x0)
					wstr += "prim ";
				if ((p_DG->Control.DT.MS_Bus & LocalSecondary) != 0x0)
					wstr += "scnd ";
				if ((p_DG->Control.DT.MS_Bus & LocalForce) != 0x0)
					wstr += "frc ";
				wstr += " ";
			}
			break;
			case BME_SG08P2:
				if ((p_DG->Control.DT.MS_Bus & LocalSecondary) != 0x0)
					wstr += "scnd ";
				if ((p_DG->Control.DT.MS_Bus & StepBackOnBus) != 0x0)
					wstr += "stbk ";
				if ((p_DG->Control.DT.MS_Bus & StartOnBus) != 0x0)
					wstr += "strt ";
				if ((p_DG->Control.DT.MS_Bus & InhibitOnBus) != 0x0)
					wstr += "inhb ";
				if ((p_DG->Control.DT.MS_Bus & LoadDataOnBus) != 0x0)
					wstr += "ldob ";
				wstr += " ";
			case BME_SG08P1:
			if (p_DG->Master)
			{
				if ((p_DG->Control.DT.MS_Bus & GateOnBusNegative) != 0x0)
					wstr += "gmsn ";
				if ((p_DG->Control.DT.MS_Bus & GateOnBusPositive) != 0x0)
					wstr += "gmsp ";
				wstr += " ";
			}
			break;
		default:
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
				wstr += "TTL  ";
				break;
			case NIM_VoltageLevel:
				wstr += "NIM  ";
				break;
			case ECL_VoltageLevel:
				wstr += "ECL  ";
				break;
			default:
				break;
			}
		case BME_G03V3:
		case BME_G03V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_G05V1:
		case BME_G05V2:
			wstr += "T0  ";
			if (strlen(p_DG->T0_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->T0_Name) + "  ");
			if (p_DG->Control.T0.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.T0.Terminate)
				wstr += "term ";
			if (p_DG->Control.T0.HighDrive)
				wstr += "hdrv ";
			if ((p_DG->Control.T0.GoSignal & SystemClock) != 0x0)
			{
				if ((p_DG->Control.T0.GoSignal & DelayClock) != 0x0)
					wstr += "dclk ";
				else
					wstr += "sclk ";
			}
			wstr += "  ";
		case BME_SG08P1:
		case BME_SG08P2:
			wstr += "A  ";
			if (strlen(p_DG->A_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->A_Name) + "  ");
			if (p_DG->Control.A.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.A.Terminate)
				wstr += "term ";
			if (p_DG->Control.A.HighDrive)
				wstr += "hdrv ";
			if ((p_DG->Control.A.GoSignal & (SystemClock | DelayClock)) != 0x0)
					wstr += "dclk ";
			wstr += "  ";
			wstr += "B  ";
			if (strlen(p_DG->B_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->B_Name) + "  ");
			if (p_DG->Control.B.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.B.Terminate)
				wstr += "term ";
			if (p_DG->Control.B.HighDrive)
				wstr += "hdrv ";
			if ((p_DG->Control.B.GoSignal & (SystemClock | DelayClock)) != 0x0)
					wstr += "dclk ";
			wstr += "  ";
			break;
		default:
			if (strlen(p_DG->T0_Name) > 0) 
				wstr += ("T0  " + lr.ReadMemo(p_DG->T0_Name) + "   ");
			if (strlen(p_DG->A_Name) > 0) 
				wstr += ("A  " + lr.ReadMemo(p_DG->A_Name) + "   ");
			if (strlen(p_DG->B_Name) > 0) 
				wstr += ("B  " + lr.ReadMemo(p_DG->B_Name) + "   ");
			break;
		}
		switch (p_DG->Product)
		{
		case BME_SG08P1:
		case BME_SG08P2:
			wstr += "C  ";
			if (strlen(p_DG->C_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->C_Name) + "  ");
			if (p_DG->Control.C.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.C.Terminate)
				wstr += "term ";
			wstr += "  ";
			wstr += "D  ";
			if (strlen(p_DG->D_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->D_Name) + "  ");
			if (p_DG->Control.D.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.D.Terminate)
				wstr += "term ";
			wstr += "  ";
			wstr += "E  ";
			if (strlen(p_DG->E_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->E_Name) + "  ");
			if (p_DG->Control.E.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.E.Terminate)
				wstr += "term ";
			if (p_DG->Control.E.Disconnect)
				wstr += "disc ";
			if (p_DG->Control.E.OntoMsBus)
				wstr += "stbs ";
			if (p_DG->Control.E.InputPositive)
				wstr += "inpos ";
			else
				wstr += "inneg ";
			wstr += "  ";
			wstr += "F  ";
			if (strlen(p_DG->E_Name) > 0) 
				wstr += (lr.ReadMemo(p_DG->F_Name) + "  ");
			if (p_DG->Control.F.Positive)
				wstr += "positive ";
			else
				wstr += "negative ";
			if (p_DG->Control.F.Terminate)
				wstr += "term ";
			if (p_DG->Control.F.Disconnect)
				wstr += "disc ";
			if (p_DG->Control.F.OntoMsBus)
				wstr += "stbs ";
			if (p_DG->Control.F.InputPositive)
				wstr += "inpos ";
			else
				wstr += "inneg ";
			wstr += "  ";
		default:
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
		case BME_G05V3:
		case BME_G05P1:
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			jstr.Format("pw %d", p_DG->Control.PulseWidth);
			wstr += jstr;
			break;
		default:
			break;
		}
		m_DelgenTableCB.AddString((LPCTSTR) wstr);
		Count++;
	}
	lr.NumerateLines(m_DelgenTableCB);
}


void CConfigurationTableDlg::OnSetfocusDelgenTable() 
{
	if (!b_DelgenTableLoaded)
	{
		LoadDelgenTable();
		b_DelgenTableLoaded = TRUE;
	}
}

void CConfigurationTableDlg::OnCancel() 
{
	if (b_DataModified)
	{
		if (AfxMessageBox("Data has been modified\n    quit anyway?",
														(MB_YESNO | MB_DEFBUTTON2), 0) == IDYES)
		{
			m_DelgenTableCB.ResetContent();
			CDialog::OnCancel();
		}
	}
	else
	{
		m_DelgenTableCB.ResetContent();
		CDialog::OnCancel();
	}
}
