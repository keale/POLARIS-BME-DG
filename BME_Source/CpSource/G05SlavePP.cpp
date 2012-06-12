// G05SlavePP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G05SlavePP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG05SlavePP property page

IMPLEMENT_DYNCREATE(CG05SlavePP, CPropertyPage)

CG05SlavePP::CG05SlavePP() : CPropertyPage(CG05SlavePP::IDD)
{
	//{{AFX_DATA_INIT(CG05SlavePP)
	m_ActivateA = FALSE;
	m_ActivateB = FALSE;
	m_ActivateT0 = FALSE;
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayT0 = _T("");
	m_GateAB = FALSE;
	//}}AFX_DATA_INIT
	b_FastApply = FALSE;
	b_RequestZeroModulo = FALSE;
	b_PageActive = FALSE;
	m_DG_Number = -1;
	m_DG_Product = -1;
	T0_Name = _T("");
	A_Name = _T("");
	B_Name = _T("");
}

CG05SlavePP::~CG05SlavePP()
{
}

void CG05SlavePP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG05SlavePP)
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_MODULO_A, m_ModuloAED);
	DDX_Control(pDX, IDC_MODULO_B, m_ModuloBED);
	DDX_Control(pDX, IDC_MODULO_T0, m_ModuloT0ED);
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
	DDX_Text(pDX, IDC_MODULO_A, m_ModuloA);
	DDV_MaxChars(pDX, m_ModuloA, 16);
	DDX_Text(pDX, IDC_MODULO_B, m_ModuloB);
	DDV_MaxChars(pDX, m_ModuloB, 16);
	DDX_Text(pDX, IDC_MODULO_T0, m_ModuloT0);
	DDV_MaxChars(pDX, m_ModuloT0, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG05SlavePP, CPropertyPage)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_M_T0, OnScrollModuloT0)
	ON_MESSAGE(WM_USER_REQUEST_M_A, OnScrollModuloA)
	ON_MESSAGE(WM_USER_REQUEST_M_B, OnScrollModuloB)
	//{{AFX_MSG_MAP(CG05SlavePP)
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
	ON_EN_CHANGE(IDC_MODULO_A, OnChangeModuloA)
	ON_EN_KILLFOCUS(IDC_MODULO_A, OnKillfocusModuloA)
	ON_EN_CHANGE(IDC_MODULO_B, OnChangeModuloB)
	ON_EN_KILLFOCUS(IDC_MODULO_B, OnKillfocusModuloB)
	ON_EN_CHANGE(IDC_MODULO_T0, OnChangeModuloT0)
	ON_EN_KILLFOCUS(IDC_MODULO_T0, OnKillfocusModuloT0)
	ON_BN_CLICKED(IDC_ZERO_MODULO, OnZeroModulo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG05SlavePP message handlers


void CG05SlavePP::OnActivateA() 
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

void CG05SlavePP::OnActivateB() 
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

void CG05SlavePP::OnActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05SlavePP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollDelayA(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusDelayA() 
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

void CG05SlavePP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollDelayB(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusDelayB() 
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

void CG05SlavePP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollDelayT0(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusDelayT0() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayT0))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayT0) == 1)
		{
			if (lr.Numeric(m_DelayT0))
			{
				double t0 = atof(m_DelayT0);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
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

void CG05SlavePP::OnGateAb() 
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

void CG05SlavePP::OnChangeModuloA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollModuloA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloAED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloAED.GetSel(nStartChar, nEndChar);
			m_ModuloA = lr.ScrollEquation(m_ModuloA, nEndChar, 
								m_ModuloAED.PresentCharacter, m_ModuloAED.PresentCount, FALSE);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloAED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusModuloA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloA) == 1)
		{
			if (lr.Numeric(m_ModuloA))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloA));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloA.Format(" %d", modulo);
			}
			else
				m_ModuloA = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05SlavePP::OnChangeModuloT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollModuloT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloT0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloT0ED.GetSel(nStartChar, nEndChar);
			m_ModuloT0 = lr.ScrollEquation(m_ModuloT0, nEndChar, 
								m_ModuloT0ED.PresentCharacter, m_ModuloT0ED.PresentCount, FALSE);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloT0ED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusModuloT0() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloT0))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloT0) == 1)
		{
			if (lr.Numeric(m_ModuloT0))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloT0));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloT0.Format(" %d", modulo);
			}
			else
				m_ModuloT0 = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloT0);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05SlavePP::OnChangeModuloB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05SlavePP::OnScrollModuloB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloBED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloBED.GetSel(nStartChar, nEndChar);
			m_ModuloB = lr.ScrollEquation(m_ModuloB, nEndChar, 
								m_ModuloBED.PresentCharacter, m_ModuloBED.PresentCount, FALSE);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloBED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G05, 0, 0);
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

void CG05SlavePP::OnKillfocusModuloB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloB) == 1)
		{
			if (lr.Numeric(m_ModuloB))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloB));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloB.Format(" %d", modulo);
			}
			else
				m_ModuloB = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05SlavePP::OnZeroModulo() 
{
	b_RequestZeroModulo = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

BOOL CG05SlavePP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	return CPropertyPage::OnSetActive();
}

BOOL CG05SlavePP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG05SlavePP::DiscretizeValues()
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
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayT0.Format(" %8.6f",t0);
				m_DelayT0 =  lr.TrimTrailingZeros((LPCTSTR) m_DelayT0);
			}
			else
				m_DelayT0 = p_G0xData->AllowedParameter((LPCTSTR)m_DelayT0);
		}
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
	}

	lr.TrimString(m_ModuloT0);
	if (m_ModuloT0.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloT0) == 1)
		{
			if (lr.Numeric(m_ModuloT0))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloT0));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloT0.Format(" %d", modulo);
			}
			else
				m_ModuloT0 = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloT0);
		}
	}
	lr.TrimString(m_ModuloA);
	if (m_ModuloA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloA) == 1)
		{
			if (lr.Numeric(m_ModuloA))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloA));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloA.Format(" %d", modulo);
			}
			else
				m_ModuloA = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloA);
		}
	}
	lr.TrimString(m_ModuloB);
	if (m_ModuloB.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloB) == 1)
		{
			if (lr.Numeric(m_ModuloB))
			{
				unsigned long modulo = RoundInt(atof(m_ModuloB));
				modulo = min(0xFFFF, max(0, modulo));
				m_ModuloB.Format(" %d", modulo);
			}
			else
				m_ModuloB = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloB);
		}
	}

	if (b_PageActive)
		UpdateData(FALSE);
}

BOOL CG05SlavePP::DistributeVariables(DG_Type* p_DG)
{
	m_Delay_T0ED.MessageNumber = WM_USER_REQUEST_T0;
	m_Delay_T0ED.p_ParentWindow = this;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	m_ModuloT0ED.MessageNumber = WM_USER_REQUEST_M_T0;
	m_ModuloT0ED.p_ParentWindow = this;
	m_ModuloAED.MessageNumber = WM_USER_REQUEST_M_A;
	m_ModuloAED.p_ParentWindow = this;
	m_ModuloBED.MessageNumber = WM_USER_REQUEST_M_B;
	m_ModuloBED.p_ParentWindow = this;
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
	m_ModuloT0 = _T("");
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
		if (m_ActivateT0)
		{
			if (p_DG->VarLoc.T0.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.T0.OutputModulo < MaxParameters)
					m_ModuloT0.Format(" X%d", (p_DG->VarLoc.T0.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.T0.OutputModulo == -1)
				{
					if (p_DG->Control.T0.OutputModulo > 1)
						m_ModuloT0.Format(" %d", p_DG->Control.T0.OutputModulo);
				}
				else
					m_ModuloT0 = lr.ReadMemo(p_DG->VarEqu.T0.OutputModulo);
			}
		}
	}

	m_ActivateA = FALSE;
	m_DelayA = _T("");
	m_ModuloA = _T("");
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
		if (m_ActivateA)
		{
			if (p_DG->VarLoc.A.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.A.OutputModulo < MaxParameters)
					m_ModuloA.Format(" X%d", (p_DG->VarLoc.A.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.A.OutputModulo == -1)
				{
					if (p_DG->Control.A.OutputModulo > 1)
						m_ModuloA.Format(" %d", p_DG->Control.A.OutputModulo);
				}
				else
					m_ModuloA = lr.ReadMemo(p_DG->VarEqu.A.OutputModulo);
			}
		}
	}

	m_ActivateB = FALSE;
	m_DelayB = _T("");
	m_ModuloB = _T("");
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
		if (m_ActivateB)
		{
			if (p_DG->VarLoc.B.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.B.OutputModulo < MaxParameters)
					m_ModuloB.Format(" X%d", (p_DG->VarLoc.B.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.B.OutputModulo == -1)
				{
					if (p_DG->Control.B.OutputModulo > 1)
						m_ModuloB.Format(" %d", p_DG->Control.B.OutputModulo);
				}
				else
					m_ModuloB = lr.ReadMemo(p_DG->VarEqu.B.OutputModulo);
			}
		}
	}
	DiscretizeValues();
	return TRUE;
}

BOOL CG05SlavePP::CollectVariables(DG_Type* p_DG)
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
			jstr = m_ModuloT0;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.T0.OutputModulo = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.T0.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.T0.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.T0.OutputModulo, (LPCTSTR)m_ModuloT0, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.T0.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.T0.OutputModulo, (LPCTSTR)m_ModuloT0, 64);
				}
			}
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
			jstr = m_ModuloA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.A.OutputModulo = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.A.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.A.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.A.OutputModulo, (LPCTSTR)m_ModuloA, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.A.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.A.OutputModulo, (LPCTSTR)m_ModuloA, 64);
				}
			}
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
			jstr = m_ModuloB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.B.OutputModulo = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.B.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.B.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.B.OutputModulo, (LPCTSTR)m_ModuloB, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.B.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.B.OutputModulo, (LPCTSTR)m_ModuloB, 64);
				}
			}
		}
	}
	return TRUE;
}

void CG05SlavePP::OnShowWindow(BOOL bShow, UINT nStatus) 
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
	case BME_G05V1:
		m_Designator.SetWindowText("G05V1 Delay Parameters");
		break;
	case BME_G05V2:
		m_Designator.SetWindowText("G05V2 Delay Parameters");
		break;
	case BME_G05V3:
		m_Designator.SetWindowText("G05V3 Delay Parameters");
		break;
	case BME_G05P1:
		m_Designator.SetWindowText("G05P1 Delay Parameters");
		break;
	case BME_G05P2:
		m_Designator.SetWindowText("G05P2 Delay Parameters");
		break;
	case BME_G05P3:
		m_Designator.SetWindowText("G05P3 Delay Parameters");
		break;
	case BME_SG05P1:
		m_Designator.SetWindowText("SG05P1 Delay Parameters");
		break;
	case BME_SG05P2:
		m_Designator.SetWindowText("SG05P2 Delay Parameters");
		break;
	case BME_SG05P3:
		m_Designator.SetWindowText("SG05P3 Delay Parameters");
		break;
	}
}
