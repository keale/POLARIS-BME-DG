// G02SlavePP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G02SlavePP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG02SlavePP property page

IMPLEMENT_DYNCREATE(CG02SlavePP, CPropertyPage)

CG02SlavePP::CG02SlavePP() : CPropertyPage(CG02SlavePP::IDD)
{
	//{{AFX_DATA_INIT(CG02SlavePP)
	m_ActivateA = FALSE;
	m_ActivateB = FALSE;
	m_ActivateT0 = FALSE;
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayT0 = _T("");
	m_GateAB = FALSE;
	//}}AFX_DATA_INIT
	b_FastApply = FALSE;
	b_PageActive = FALSE;
	m_DG_Number = -1;
	m_DG_Product = -1;
	T0_Name = _T("");
	A_Name = _T("");
	B_Name = _T("");
}

CG02SlavePP::~CG02SlavePP()
{
}

void CG02SlavePP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG02SlavePP)
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_ACTIVATE_A, m_ActivateA_B);
	DDX_Control(pDX, IDC_ACTIVATE_T0, m_ActivateT0_B);
	DDX_Control(pDX, IDC_ACTIVATE_B, m_ActivateB_B);
	DDX_Control(pDX, IDC_DESIGNATOR, m_Designator);
	DDX_Check(pDX, IDC_ACTIVATE_A, m_ActivateA);
	DDX_Check(pDX, IDC_ACTIVATE_B, m_ActivateB);
	DDX_Check(pDX, IDC_ACTIVATE_T0, m_ActivateT0);
	DDX_Text(pDX, IDC_DELAY_A, m_DelayA);
	DDV_MaxChars(pDX, m_DelayA, 32);
	DDX_Text(pDX, IDC_DELAY_B, m_DelayB);
	DDV_MaxChars(pDX, m_DelayB, 32);
	DDX_Text(pDX, IDC_DELAY_T0, m_DelayT0);
	DDV_MaxChars(pDX, m_DelayT0, 32);
	DDX_Check(pDX, IDC_GATE_AB, m_GateAB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG02SlavePP, CPropertyPage)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	//{{AFX_MSG_MAP(CG02SlavePP)
	ON_BN_CLICKED(IDC_ACTIVATE_A, OnActivateA)
	ON_BN_CLICKED(IDC_ACTIVATE_B, OnActivateB)
	ON_BN_CLICKED(IDC_ACTIVATE_T0, OnActivateT0)
	ON_EN_CHANGE(IDC_DELAY_A, OnChangeDelayA)
	ON_EN_CHANGE(IDC_DELAY_B, OnChangeDelayB)
	ON_EN_CHANGE(IDC_DELAY_T0, OnChangeDelayT0)
	ON_BN_CLICKED(IDC_GATE_AB, OnGateAb)
	ON_EN_KILLFOCUS(IDC_DELAY_T0, OnKillfocusDelayT0)
	ON_WM_SHOWWINDOW()
	ON_EN_KILLFOCUS(IDC_DELAY_A, OnKillfocusDelayA)
	ON_EN_KILLFOCUS(IDC_DELAY_B, OnKillfocusDelayB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG02SlavePP message handlers

void CG02SlavePP::OnActivateA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_ActivateA)
	{
		m_GateAB = FALSE;
		UpdateData(FALSE);
	}
}

void CG02SlavePP::OnActivateB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_ActivateB)
	{
		m_GateAB = FALSE;
		UpdateData(FALSE);
	}
}

void CG02SlavePP::OnActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02SlavePP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02SlavePP::OnScrollDelayA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_AED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_AED.GetSel(nStartChar, nEndChar);
			m_DelayA = lr.ScrollEquation(m_DelayA, nEndChar, 
								m_Delay_AED.PresentCharacter, m_Delay_AED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_AED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G02, 0, 0);
			}
			break;
		case 120:
			b_FastApply = TRUE;
			break;
		case 122:
			b_FastApply = FALSE;
			break;
		default:
			break;
	}
	return 0;
}

void CG02SlavePP::OnKillfocusDelayA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayA) == 1)
		{
			if (lr.Numeric(m_DelayA))
			{
				double t0 = atof(m_DelayA);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayA.Format(" %8.6f",t0);
				m_DelayA =  lr.TrimTrailingZeros((LPCTSTR) m_DelayA);
			}
			else
				m_DelayA = p_G0xData->AllowedParameter((LPCTSTR)m_DelayA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG02SlavePP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02SlavePP::OnScrollDelayB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_BED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_BED.GetSel(nStartChar, nEndChar);
			m_DelayB = lr.ScrollEquation(m_DelayB, nEndChar, 
								m_Delay_BED.PresentCharacter, m_Delay_BED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_BED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G02, 0, 0);
			}
			break;
		case 120:
			b_FastApply = TRUE;
			break;
		case 122:
			b_FastApply = FALSE;
			break;
		default:
			break;
	}
	return 0;
}

void CG02SlavePP::OnKillfocusDelayB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayB) == 1)
		{
			if (lr.Numeric(m_DelayB))
			{
				double t0 = atof(m_DelayB);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayB.Format(" %8.6f",t0);
				m_DelayB =  lr.TrimTrailingZeros((LPCTSTR) m_DelayB);
			}
			else
				m_DelayB = p_G0xData->AllowedParameter((LPCTSTR)m_DelayB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG02SlavePP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02SlavePP::OnScrollDelayT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_T0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_T0ED.GetSel(nStartChar, nEndChar);
			m_DelayT0 = lr.ScrollEquation(m_DelayT0, nEndChar, 
								m_Delay_T0ED.PresentCharacter, m_Delay_T0ED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_T0ED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G02, 0, 0);
			}
			break;
		case 120:
			b_FastApply = TRUE;
			break;
		case 122:
			b_FastApply = FALSE;
			break;
		default:
			break;
	}
	return 0;
}

void CG02SlavePP::OnKillfocusDelayT0() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayT0))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayT0) == 1)
		{
			if (lr.Numeric(m_DelayT0))
			{
				double t0 = atof(m_DelayT0);
				switch (m_DG_Product)
				{
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P4:
				case BME_SG02P5:
					t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
					break;
				default:
					t0 = p_G0xData->RoundT0(t0, m_DG_Number);
					break;
				}
				m_DelayT0.Format(" %8.6f",t0);
				m_DelayT0 =  lr.TrimTrailingZeros((LPCTSTR) m_DelayT0);
			}
			else
				m_DelayT0 = p_G0xData->AllowedParameter((LPCTSTR)m_DelayT0);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG02SlavePP::OnGateAb() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateAB)
	{
		m_ActivateA = TRUE;
		m_ActivateB = TRUE;
		UpdateData(FALSE);
	}
}

BOOL CG02SlavePP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	return CPropertyPage::OnSetActive();
}

BOOL CG02SlavePP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG02SlavePP::DiscretizeValues()
{
	CListRout lr;
	double t0;
	lr.TrimString(m_DelayT0);
	if (m_DelayT0.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayT0) == 1)
		{
			if (lr.Numeric(m_DelayT0))
			{
				t0 = atof(m_DelayT0);
				switch (m_DG_Product)
				{
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P4:
				case BME_SG02P5:
					t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
					break;
				default:
					t0 = p_G0xData->RoundT0(t0, m_DG_Number);
					break;
				}
				m_DelayT0.Format(" %8.6f",t0);
				m_DelayT0 =  lr.TrimTrailingZeros((LPCTSTR) m_DelayT0);
			}
			else
				m_DelayT0 = p_G0xData->AllowedParameter((LPCTSTR)m_DelayT0);
		}
		else
			m_DelayT0 = " " + m_DelayT0;
	}
	lr.TrimString(m_DelayA);
	if (m_DelayA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayA) == 1)
		{
			if (lr.Numeric(m_DelayA))
			{
				t0 = atof(m_DelayA);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayA.Format(" %8.6f",t0);
				m_DelayA =  lr.TrimTrailingZeros((LPCTSTR) m_DelayA);
			}
			else
				m_DelayA = p_G0xData->AllowedParameter((LPCTSTR)m_DelayA);
		}
		else
			m_DelayA = " " + m_DelayA;
	}
	lr.TrimString(m_DelayB);
	if (m_DelayB.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayB) == 1)
		{
			if (lr.Numeric(m_DelayB))
			{
				t0 = atof(m_DelayB);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayB.Format(" %8.6f",t0);
				m_DelayB =  lr.TrimTrailingZeros((LPCTSTR) m_DelayB);
			}
			else
				m_DelayB = p_G0xData->AllowedParameter((LPCTSTR)m_DelayB);
		}
		else
			m_DelayB = " " + m_DelayB;
	}
	if (b_PageActive)
		UpdateData(FALSE);
}

BOOL CG02SlavePP::DistributeVariables(DG_Type* p_DG)
{
	m_Delay_T0ED.MessageNumber = WM_USER_REQUEST_T0;
	m_Delay_T0ED.p_ParentWindow = this;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	b_FastApply = FALSE;

	CListRout lr;
	m_DG_Product = p_DG->Control.DG_Product;
	T0_Name = lr.ReadMemo(p_DG->T0_Name);
	A_Name = lr.ReadMemo(p_DG->A_Name);
	B_Name = lr.ReadMemo(p_DG->B_Name);

	m_GateAB = p_DG->Control.Gate_AB;

	int MaxParameters = p_G0xData->ParameterList.NoParameters;

	m_ActivateT0 = FALSE;
	m_DelayT0 = _T("");
	if ((p_DG->Control.T0.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.T0.FireFirst >= 0)
		{
			if (p_DG->VarLoc.T0.FireFirst < MaxParameters)
			{
				m_ActivateT0 = TRUE;
				m_DelayT0.Format(" X%d", (p_DG->VarLoc.T0.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.T0.FireFirst == -1)
			{
				if (p_DG->Control.T0.FireFirst >= 0.0)
				{
					m_ActivateT0 = TRUE;
					m_DelayT0.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.T0.FireFirst, m_DG_Number));
					m_DelayT0 = lr.TrimTrailingZeros((LPCTSTR) m_DelayT0);
				}
			}
			else
			{
				m_ActivateT0 = TRUE;
				m_DelayT0 = lr.ReadMemo(p_DG->VarEqu.T0.FireFirst);
			}
		}
	}

	m_ActivateA = FALSE;
	m_DelayA = _T("");
	if ((p_DG->Control.A.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.A.FireFirst >= 0)
		{
			if (p_DG->VarLoc.A.FireFirst < MaxParameters)
			{
				m_ActivateA = TRUE;
				m_DelayA.Format(" X%d", (p_DG->VarLoc.A.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.A.FireFirst == -1)
			{
				if (p_DG->Control.A.FireFirst >= 0.0)
				{
					m_ActivateA = TRUE;
					m_DelayA.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.A.FireFirst, m_DG_Number));
					m_DelayA =  lr.TrimTrailingZeros((LPCTSTR) m_DelayA);
				}
			}
			else
			{
				m_ActivateA = TRUE;
				m_DelayA = lr.ReadMemo(p_DG->VarEqu.A.FireFirst);
			}
		}
	}

	m_ActivateB = FALSE;
	m_DelayB = _T("");
	if ((p_DG->Control.B.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.B.FireFirst >= 0)
		{
			if (p_DG->VarLoc.B.FireFirst < MaxParameters)
			{
				m_ActivateB = TRUE;
				m_DelayB.Format(" X%d", (p_DG->VarLoc.B.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.B.FireFirst == -1)
			{
				if (p_DG->Control.B.FireFirst >= 0.0)
				{
					m_ActivateB = TRUE;
					m_DelayB.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.B.FireFirst, m_DG_Number));
					m_DelayB =  lr.TrimTrailingZeros((LPCTSTR) m_DelayB);
				}
			}
			else
			{
				m_ActivateB = TRUE;
				m_DelayB = lr.ReadMemo(p_DG->VarEqu.B.FireFirst);
			}
		}
	}
	DiscretizeValues();
	return TRUE;
}

BOOL CG02SlavePP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();

	p_DG->Control.Gate_AB = m_GateAB;

	p_DG->Control.DT.ResetWhenDone = TRUE;
	p_DG->Control.DT.TriggerEnable = TRUE;


	CListRout lr;
	CString jstr;
	p_DG->Control.T0.GoSignal &= 0x88;
	p_DG->Control.T0.DoneSignal = 0x0;
	p_DG->Control.T0.FireFirst = -1.0;
	p_DG->Control.T0.SetBack = -1.0;
	p_DG->Control.T0.OutputModulo = 1;
	p_DG->VarLoc.T0.FireFirst = -1;
	p_DG->VarLoc.T0.SetBack = -1;
	p_DG->VarLoc.T0.OutputModulo = -1;
	p_DG->VarEqu.T0.FireFirst[0] = 0;
	p_DG->VarEqu.T0.SetBack[0] = 0;
	p_DG->VarEqu.T0.OutputModulo[0] = 0;
	if (m_ActivateT0)
	{
		jstr = m_DelayT0;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.T0.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.T0.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.T0.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.T0.FireFirst, (LPCTSTR)m_DelayT0, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.T0.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.T0.FireFirst, (LPCTSTR)m_DelayT0, 64);
			}
			p_DG->Control.T0.GoSignal |= MasterPrimary;
		}
	}

	p_DG->Control.A.GoSignal &= 0x88;
	p_DG->Control.A.DoneSignal = 0x0;
	p_DG->Control.A.FireFirst = -1.0;
	p_DG->Control.A.SetBack = -1.0;
	p_DG->Control.A.OutputModulo = 1;
	p_DG->VarLoc.A.FireFirst = -1;
	p_DG->VarLoc.A.SetBack = -1;
	p_DG->VarEqu.A.FireFirst[0] = 0;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarEqu.A.SetBack[0] = 0;
	p_DG->VarEqu.A.OutputModulo[0] = 0;
	if (m_ActivateA)
	{
		jstr = m_DelayA;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.A.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.A.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.A.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.A.FireFirst, (LPCTSTR)m_DelayA, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.A.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.A.FireFirst, (LPCTSTR)m_DelayA, 64);
			}
			p_DG->Control.A.GoSignal |= MasterPrimary;
		}
	}

	p_DG->Control.B.GoSignal &= 0x88;
	p_DG->Control.B.DoneSignal = 0x0;
	p_DG->Control.B.FireFirst = -1.0;
	p_DG->Control.B.SetBack = -1.0;
	p_DG->Control.B.OutputModulo = 1;
	p_DG->VarLoc.B.FireFirst = -1;
	p_DG->VarLoc.B.SetBack = -1;
	p_DG->VarLoc.B.OutputModulo = -1;
	p_DG->VarEqu.B.FireFirst[0] = 0;
	p_DG->VarEqu.B.SetBack[0] = 0;
	p_DG->VarEqu.B.OutputModulo[0] = 0;
	if (m_ActivateB)
	{
		jstr = m_DelayB;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.B.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.B.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.B.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.B.FireFirst, (LPCTSTR)m_DelayB, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.B.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.B.FireFirst, (LPCTSTR)m_DelayB, 64);
			}
			p_DG->Control.B.GoSignal |= MasterPrimary;
		}
	}
	return TRUE;
}

void CG02SlavePP::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	if (T0_Name.GetLength() > 0)
		m_ActivateT0_B.SetWindowText((LPCTSTR)T0_Name);
	if (A_Name.GetLength() > 0)
		m_ActivateA_B.SetWindowText((LPCTSTR)A_Name);
	if (B_Name.GetLength() > 0)
		m_ActivateB_B.SetWindowText((LPCTSTR)B_Name);
	switch (m_DG_Product)
	{
	case BME_G02V3:
		m_Designator.SetWindowText("G02V3 Delay Parameters");
		break;
	case BME_G02V2:
		m_Designator.SetWindowText("G02V2 Delay Parameters");
		break;
	case BME_G02V1:
		m_Designator.SetWindowText("G02V1 Delay Parameters");
		break;
	case BME_SG02V1:
		m_Designator.SetWindowText("SG02V1 Delay Parameters");
		break;
	case BME_SG02V2:
		m_Designator.SetWindowText("SG02V2 Delay Parameters");
		break;
	case BME_SG02V3:
		m_Designator.SetWindowText("SG02V3 Delay Parameters");
		break;
	case BME_SG02V4:
		m_Designator.SetWindowText("SG02V4 Delay Parameters");
		break;
	case BME_SG02V5:
		m_Designator.SetWindowText("SG02V5 Delay Parameters");
		break;
	case BME_SG02V6:
		m_Designator.SetWindowText("SG02V6 Delay Parameters");
		break;
	case BME_SG02V7:
		m_Designator.SetWindowText("SG02V7 Delay Parameters");
		break;
	case BME_SG02P1:
		m_Designator.SetWindowText("SG02P1 Delay Parameters");
		break;
	case BME_SG02P2:
		m_Designator.SetWindowText("SG02P2 Delay Parameters");
		break;
	case BME_SG02P4:
		m_Designator.SetWindowText("SG02P4 Delay Parameters");
		break;
	case BME_SG02P5:
		m_Designator.SetWindowText("SG02P5 Delay Parameters");
		break;
	}
}
