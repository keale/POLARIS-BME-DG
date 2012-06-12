// G04SlavePP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G04SlavePP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG04SlavePP property page

IMPLEMENT_DYNCREATE(CG04SlavePP, CPropertyPage)

CG04SlavePP::CG04SlavePP() : CPropertyPage(CG04SlavePP::IDD)
{
	//{{AFX_DATA_INIT(CG04SlavePP)
	m_ActivateA = FALSE;
	m_ActivateB = FALSE;
	m_ActivateT0 = FALSE;
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayT0 = _T("");
	m_FireSecondA = _T("");
	m_FireSecondB = _T("");
	m_FireSecondT0 = _T("");
	m_GateAB = FALSE;
	m_SetBackA = _T("");
	m_SetBackB = _T("");
	m_SetBackT0 = _T("");
	//}}AFX_DATA_INIT
	b_FastApply = FALSE;
	b_PageActive = FALSE;
	m_DG_Number = -1;
	T0_Name = _T("");
	A_Name = _T("");
	B_Name = _T("");
}

CG04SlavePP::~CG04SlavePP()
{
}

void CG04SlavePP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG04SlavePP)
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_SET_BACK_A, m_SetBackAED);
	DDX_Control(pDX, IDC_SET_BACK_B, m_SetBackBED);
	DDX_Control(pDX, IDC_SET_BACK_T0, m_SetBackT0ED);
	DDX_Control(pDX, IDC_FIRE_SECOND_A, m_FireSecondAED);
	DDX_Control(pDX, IDC_FIRE_SECOND_B, m_FireSecondBED);
	DDX_Control(pDX, IDC_FIRE_SECOND_T0, m_FireSecondT0ED);
	DDX_Control(pDX, IDC_ACTIVATE_A, m_ActivateA_B);
	DDX_Control(pDX, IDC_ACTIVATE_T0, m_ActivateT0_B);
	DDX_Control(pDX, IDC_ACTIVATE_B, m_ActivateB_B);
	DDX_Check(pDX, IDC_ACTIVATE_A, m_ActivateA);
	DDX_Check(pDX, IDC_ACTIVATE_B, m_ActivateB);
	DDX_Check(pDX, IDC_ACTIVATE_T0, m_ActivateT0);
	DDX_Text(pDX, IDC_DELAY_A, m_DelayA);
	DDV_MaxChars(pDX, m_DelayA, 32);
	DDX_Text(pDX, IDC_DELAY_B, m_DelayB);
	DDV_MaxChars(pDX, m_DelayB, 32);
	DDX_Text(pDX, IDC_DELAY_T0, m_DelayT0);
	DDV_MaxChars(pDX, m_DelayT0, 32);
	DDX_Text(pDX, IDC_FIRE_SECOND_A, m_FireSecondA);
	DDV_MaxChars(pDX, m_FireSecondA, 32);
	DDX_Text(pDX, IDC_FIRE_SECOND_B, m_FireSecondB);
	DDV_MaxChars(pDX, m_FireSecondB, 32);
	DDX_Text(pDX, IDC_FIRE_SECOND_T0, m_FireSecondT0);
	DDV_MaxChars(pDX, m_FireSecondT0, 32);
	DDX_Check(pDX, IDC_GATE_AB, m_GateAB);
	DDX_Text(pDX, IDC_SET_BACK_A, m_SetBackA);
	DDV_MaxChars(pDX, m_SetBackA, 32);
	DDX_Text(pDX, IDC_SET_BACK_B, m_SetBackB);
	DDV_MaxChars(pDX, m_SetBackB, 32);
	DDX_Text(pDX, IDC_SET_BACK_T0, m_SetBackT0);
	DDV_MaxChars(pDX, m_SetBackT0, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG04SlavePP, CPropertyPage)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_R_T0, OnScrollSetBackT0)
	ON_MESSAGE(WM_USER_REQUEST_R_A, OnScrollSetBackA)
	ON_MESSAGE(WM_USER_REQUEST_R_B, OnScrollSetBackB)
	ON_MESSAGE(WM_USER_REQUEST_S_T0, OnScrollFireSecondT0)
	ON_MESSAGE(WM_USER_REQUEST_S_A, OnScrollFireSecondA)
	ON_MESSAGE(WM_USER_REQUEST_S_B, OnScrollFireSecondB)
	//{{AFX_MSG_MAP(CG04SlavePP)
	ON_BN_CLICKED(IDC_ACTIVATE_A, OnActivateA)
	ON_BN_CLICKED(IDC_ACTIVATE_B, OnActivateB)
	ON_BN_CLICKED(IDC_ACTIVATE_T0, OnActivateT0)
	ON_EN_CHANGE(IDC_DELAY_A, OnChangeDelayA)
	ON_EN_CHANGE(IDC_DELAY_B, OnChangeDelayB)
	ON_EN_CHANGE(IDC_DELAY_T0, OnChangeDelayT0)
	ON_EN_CHANGE(IDC_FIRE_SECOND_A, OnChangeFireSecondA)
	ON_EN_CHANGE(IDC_FIRE_SECOND_B, OnChangeFireSecondB)
	ON_EN_CHANGE(IDC_FIRE_SECOND_T0, OnChangeFireSecondT0)
	ON_BN_CLICKED(IDC_GATE_AB, OnGateAb)
	ON_EN_CHANGE(IDC_SET_BACK_A, OnChangeSetBackA)
	ON_EN_CHANGE(IDC_SET_BACK_B, OnChangeSetBackB)
	ON_EN_CHANGE(IDC_SET_BACK_T0, OnChangeSetBackT0)
	ON_EN_KILLFOCUS(IDC_DELAY_T0, OnKillfocusDelayT0)
	ON_EN_KILLFOCUS(IDC_FIRE_SECOND_T0, OnKillfocusFireSecondT0)
	ON_EN_KILLFOCUS(IDC_SET_BACK_A, OnKillfocusSetBackA)
	ON_EN_KILLFOCUS(IDC_SET_BACK_B, OnKillfocusSetBackB)
	ON_EN_KILLFOCUS(IDC_SET_BACK_T0, OnKillfocusSetBackT0)
	ON_EN_KILLFOCUS(IDC_FIRE_SECOND_A, OnKillfocusFireSecondA)
	ON_EN_KILLFOCUS(IDC_FIRE_SECOND_B, OnKillfocusFireSecondB)
	ON_EN_KILLFOCUS(IDC_DELAY_A, OnKillfocusDelayA)
	ON_EN_KILLFOCUS(IDC_DELAY_B, OnKillfocusDelayB)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG04SlavePP message handlers

void CG04SlavePP::OnActivateA() 
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

void CG04SlavePP::OnActivateB() 
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

void CG04SlavePP::OnActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG04SlavePP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollDelayT0(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusDelayT0() 
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

void CG04SlavePP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollDelayA(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusDelayA() 
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

void CG04SlavePP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollDelayB(WPARAM, LPARAM)
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
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusDelayB() 
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

void CG04SlavePP::OnChangeSetBackT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollSetBackT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_SetBackT0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_SetBackT0ED.GetSel(nStartChar, nEndChar);
			m_SetBackT0 = lr.ScrollEquation(m_SetBackT0, nEndChar, 
								m_SetBackT0ED.PresentCharacter, m_SetBackT0ED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_SetBackT0ED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusSetBackT0() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_SetBackT0))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackT0) == 1)
		{
			if (lr.Numeric(m_SetBackT0))
			{
				double t0 = atof(m_SetBackT0);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackT0.Format(" %8.6f",t0);
				m_SetBackT0 =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackT0);
			}
			else
				m_SetBackT0 = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackT0);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnChangeSetBackA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollSetBackA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_SetBackAED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_SetBackAED.GetSel(nStartChar, nEndChar);
			m_SetBackA = lr.ScrollEquation(m_SetBackA, nEndChar, 
								m_SetBackAED.PresentCharacter, m_SetBackAED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_SetBackAED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusSetBackA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_SetBackA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackA) == 1)
		{
			if (lr.Numeric(m_SetBackA))
			{
				double t0 = atof(m_SetBackA);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackA.Format(" %8.6f",t0);
				m_SetBackA =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackA);
			}
			else
				m_SetBackA = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnChangeSetBackB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollSetBackB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_SetBackBED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_SetBackBED.GetSel(nStartChar, nEndChar);
			m_SetBackB = lr.ScrollEquation(m_SetBackB, nEndChar, 
								m_SetBackBED.PresentCharacter, m_SetBackBED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_SetBackBED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusSetBackB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_SetBackB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackB) == 1)
		{
			if (lr.Numeric(m_SetBackB))
			{
				double t0 = atof(m_SetBackB);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackB.Format(" %8.6f",t0);
				m_SetBackB =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackB);
			}
			else
				m_SetBackB = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnChangeFireSecondT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollFireSecondT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_FireSecondT0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_FireSecondT0ED.GetSel(nStartChar, nEndChar);
			m_FireSecondT0 = lr.ScrollEquation(m_FireSecondT0, nEndChar, 
								m_FireSecondT0ED.PresentCharacter, m_FireSecondT0ED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_FireSecondT0ED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusFireSecondT0() 
{
	CListRout lr;
	CString jstr = m_FireSecondT0;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		if (lr.Numeric(jstr))
		{
			CString wstr = m_DelayT0;
			lr.TrimString(wstr);
			if (wstr.GetLength() > 0)
			{
				double t1 = atof(m_FireSecondT0);
				if (lr.Numeric(wstr))
				{
					double t0 = atof(m_DelayT0);
					t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
				}
				m_FireSecondT0.Format(" %8.6f",t1);
				m_FireSecondT0 =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondT0);
			}
		}
		else
			m_FireSecondT0 = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondT0);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnChangeFireSecondA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollFireSecondA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_FireSecondAED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_FireSecondAED.GetSel(nStartChar, nEndChar);
			m_FireSecondA = lr.ScrollEquation(m_FireSecondA, nEndChar, 
								m_FireSecondAED.PresentCharacter, m_FireSecondAED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_FireSecondAED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusFireSecondA() 
{
	CListRout lr;
	CString jstr = m_FireSecondA;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		if (lr.Numeric(jstr))
		{
			CString wstr = m_DelayA;
			lr.TrimString(wstr);
			if (wstr.GetLength() > 0)
			{
				double t1 = atof(m_FireSecondA);
				if (lr.Numeric(wstr))
				{
					double t0 = atof(m_DelayA);
					t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
				}
				m_FireSecondA.Format(" %8.6f",t1);
				m_FireSecondA =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondA);
			}
		}
		else
			m_FireSecondA = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondA);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnChangeFireSecondB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG04SlavePP::OnScrollFireSecondB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_FireSecondBED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_FireSecondBED.GetSel(nStartChar, nEndChar);
			m_FireSecondB = lr.ScrollEquation(m_FireSecondB, nEndChar, 
								m_FireSecondBED.PresentCharacter, m_FireSecondBED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_FireSecondBED.SetSel(nEndChar, nEndChar);
				if (b_FastApply)
					p_ParentWindow->SendMessage(WM_FAST_APPLY_REQUEST_G04, 0, 0);
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

void CG04SlavePP::OnKillfocusFireSecondB() 
{
	CListRout lr;
	CString jstr = m_FireSecondB;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		if (lr.Numeric(jstr))
		{
			CString wstr = m_DelayB;
			lr.TrimString(wstr);
			if (wstr.GetLength() > 0)
			{
				double t1 = atof(m_FireSecondB);
				if (lr.Numeric(wstr))
				{
					double t0 = atof(m_DelayB);
					t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
				}
				m_FireSecondB.Format(" %8.6f",t1);
				m_FireSecondB =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondB);
			}
		}
		else
			m_FireSecondB = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondB);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG04SlavePP::OnGateAb() 
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

BOOL CG04SlavePP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	return CPropertyPage::OnSetActive();
}

BOOL CG04SlavePP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG04SlavePP::DiscretizeValues()
{
	CListRout lr;
	double t0,t1;
	lr.TrimString(m_DelayT0);
	lr.TrimString(m_FireSecondT0);
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
				if (m_FireSecondT0.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondT0) == 1)
					{
						if (lr.Numeric(m_FireSecondT0))
						{
							t1 = atof(m_FireSecondT0);
							t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
							m_FireSecondT0.Format(" %8.6f",t1);
							m_FireSecondT0 =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondT0);
						}
						else
							m_FireSecondT0 = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondT0);
					}
					else
						m_FireSecondT0 = " " + m_FireSecondT0;
				}
			}
			else
			{
				m_DelayT0 = p_G0xData->AllowedParameter((LPCTSTR)m_DelayT0);
				if (m_FireSecondT0.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondT0) == 1)
					{
						if (lr.Numeric(m_FireSecondT0))
						{
							t1 = atof(m_FireSecondT0);
							m_FireSecondT0.Format(" %8.6f",t1);
							m_FireSecondT0 =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondT0);
						}
						else
							m_FireSecondT0 = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondT0);
					}
					else
						m_FireSecondT0 = " " + m_FireSecondT0;
				}
			}
		}
	}
	lr.TrimString(m_DelayA);
	lr.TrimString(m_FireSecondA);
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
				if (m_FireSecondA.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondA) == 1)
					{
						if (lr.Numeric(m_FireSecondA))
						{
							t1 = atof(m_FireSecondA);
							t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
							m_FireSecondA.Format(" %8.6f",t1);
							m_FireSecondA =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondA);
						}
						else
							m_FireSecondA = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondA);
					}
					else
						m_FireSecondA = " " + m_FireSecondA;
				}
			}
			else
			{
				m_DelayA = p_G0xData->AllowedParameter((LPCTSTR)m_DelayA);
				if (m_FireSecondA.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondA) == 1)
					{
						if (lr.Numeric(m_FireSecondA))
						{
							t1 = atof(m_FireSecondA);
							m_FireSecondA.Format(" %8.6f",t1);
							m_FireSecondA =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondA);
						}
						else
							m_FireSecondA = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondA);
					}
					else
						m_FireSecondA = " " + m_FireSecondA;
				}
			}
		}
	}
	lr.TrimString(m_DelayB);
	lr.TrimString(m_FireSecondB);
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
				if (m_FireSecondB.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondB) == 1)
					{
						if (lr.Numeric(m_FireSecondB))
						{
							t1 = atof(m_FireSecondB);
							t1 = p_G0xData->RoundFireSecond(t1, t0, m_DG_Number);
							m_FireSecondB.Format(" %8.6f",t1);
							m_FireSecondB =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondB);
						}
						else
							m_FireSecondB = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondB);
					}
					else
						m_FireSecondB = " " + m_FireSecondB;
				}
			}
			else
			{
				m_DelayB = p_G0xData->AllowedParameter((LPCTSTR)m_DelayB);
				if (m_FireSecondB.GetLength() > 0)
				{
					if (lr.NumberCharacterGroups((LPCTSTR)m_FireSecondB) == 1)
					{
						if (lr.Numeric(m_FireSecondB))
						{
							t1 = atof(m_FireSecondB);
							m_FireSecondB.Format(" %8.6f",t1);
							m_FireSecondB =  lr.TrimTrailingZeros((LPCTSTR) m_FireSecondB);
						}
						else
							m_FireSecondB = p_G0xData->AllowedParameter((LPCTSTR)m_FireSecondB);
					}
					else
						m_FireSecondB = " " + m_FireSecondB;
				}
			}
		}
	}

	lr.TrimString(m_SetBackT0);
	if (m_SetBackT0.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackT0) == 1)
		{
			if (lr.Numeric(m_SetBackT0))
			{
				t0 = atof(m_SetBackT0);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackT0.Format(" %8.6f",t0);
				m_SetBackT0 =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackT0);
			}
			else
				m_SetBackT0 = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackT0);
		}
		else
			m_SetBackT0 = " " + m_SetBackT0;
	}
	lr.TrimString(m_SetBackA);
	if (m_SetBackA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackA) == 1)
		{
			if (lr.Numeric(m_SetBackA))
			{
				t0 = atof(m_SetBackA);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackA.Format(" %8.6f",t0);
				m_SetBackA =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackA);
			}
			else
				m_SetBackA = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackA);
		}
		else
			m_SetBackA = " " + m_SetBackA;
	}
	lr.TrimString(m_SetBackB);
	if (m_SetBackB.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_SetBackB) == 1)
		{
			if (lr.Numeric(m_SetBackB))
			{
				t0 = atof(m_SetBackB);
				t0 = p_G0xData->RoundSetBack(t0, m_DG_Number);
				m_SetBackB.Format(" %8.6f",t0);
				m_SetBackB =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackB);
			}
			else
				m_SetBackB = p_G0xData->AllowedParameter((LPCTSTR)m_SetBackB);
		}
		else
			m_SetBackB = " " + m_SetBackB;
	}
	if (b_PageActive)
		UpdateData(FALSE);
}

BOOL CG04SlavePP::DistributeVariables(DG_Type* p_DG)
{
	m_Delay_T0ED.MessageNumber = WM_USER_REQUEST_T0;
	m_Delay_T0ED.p_ParentWindow = this;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	m_SetBackT0ED.MessageNumber = WM_USER_REQUEST_R_T0;
	m_SetBackT0ED.p_ParentWindow = this;
	m_SetBackAED.MessageNumber = WM_USER_REQUEST_R_A;
	m_SetBackAED.p_ParentWindow = this;
	m_SetBackBED.MessageNumber = WM_USER_REQUEST_R_B;
	m_SetBackBED.p_ParentWindow = this;
	m_FireSecondT0ED.MessageNumber = WM_USER_REQUEST_S_T0;
	m_FireSecondT0ED.p_ParentWindow = this;
	m_FireSecondAED.MessageNumber = WM_USER_REQUEST_S_A;
	m_FireSecondAED.p_ParentWindow = this;
	m_FireSecondBED.MessageNumber = WM_USER_REQUEST_S_B;
	m_FireSecondBED.p_ParentWindow = this;
	b_FastApply = FALSE;

	CListRout lr;
	T0_Name = lr.ReadMemo(p_DG->T0_Name);
	A_Name = lr.ReadMemo(p_DG->A_Name);
	B_Name = lr.ReadMemo(p_DG->B_Name);
	m_GateAB = p_DG->Control.Gate_AB;


	int MaxParameters = p_G0xData->ParameterList.NoParameters;


	m_ActivateT0 = FALSE;
	m_DelayT0 = _T("");
	m_SetBackT0 = _T("");
	m_FireSecondT0 = _T("");
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
			if (p_DG->VarLoc.T0.SetBack >= 0)
			{
				if (p_DG->VarLoc.T0.SetBack < MaxParameters)
					m_SetBackT0.Format(" X%d", (p_DG->VarLoc.T0.SetBack + 1));
			}
			else
			{
				if (p_DG->VarLoc.T0.SetBack == -1)
				{
					if (p_DG->Control.T0.SetBack > 0.0)
					{
						m_SetBackT0.Format(" %8.6f", p_DG->Control.T0.SetBack);
						m_SetBackT0 =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackT0);
					}
				}
				else
					m_SetBackT0 = lr.ReadMemo(p_DG->VarEqu.T0.SetBack);
			}
			if (p_DG->VarLoc.T0.FireSecond >= 0)
			{
				if (p_DG->VarLoc.T0.FireSecond < MaxParameters)
					m_FireSecondT0.Format(" X%d", (p_DG->VarLoc.T0.FireSecond + 1));
			}
			else
			{
				if (p_DG->VarLoc.T0.FireSecond == -1)
				{
					if (p_DG->Control.T0.FireSecond > 0.0)
					{
						m_FireSecondT0.Format(" %8.6f", p_DG->Control.T0.FireSecond);
						m_FireSecondT0 = lr.TrimTrailingZeros((LPCTSTR) m_FireSecondT0);
					}
				}
				else
					m_FireSecondT0 = lr.ReadMemo(p_DG->VarEqu.T0.FireSecond);
			}
		}
	}

	m_ActivateA = FALSE;
	m_DelayA = _T("");
	m_SetBackA = _T("");
	m_FireSecondA = _T("");
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
					m_DelayA = lr.TrimTrailingZeros((LPCTSTR) m_DelayA);
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
			if (p_DG->VarLoc.A.SetBack >= 0)
			{
				if (p_DG->VarLoc.A.SetBack < MaxParameters)
					m_SetBackA.Format(" X%d", (p_DG->VarLoc.A.SetBack + 1));
			}
			else
			{
				if (p_DG->VarLoc.A.SetBack == -1)
				{
					if (p_DG->Control.A.SetBack > 0.0)
					{
						m_SetBackA.Format(" %8.6f", p_DG->Control.A.SetBack);
						m_SetBackA =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackA);
					}
				}
				else
					m_SetBackA = lr.ReadMemo(p_DG->VarEqu.A.SetBack);
			}
			if (p_DG->VarLoc.A.FireSecond >= 0)
			{
				if (p_DG->VarLoc.A.FireSecond < MaxParameters)
					m_FireSecondA.Format(" X%d", (p_DG->VarLoc.A.FireSecond + 1));
			}
			else
			{
				if (p_DG->VarLoc.A.FireSecond == -1)
				{
					if (p_DG->Control.A.FireSecond > 0.0)
					{
						m_FireSecondA.Format(" %8.6f", p_DG->Control.A.FireSecond);
						m_FireSecondA = lr.TrimTrailingZeros((LPCTSTR) m_FireSecondA);
					}
				}
				else
					m_FireSecondA = lr.ReadMemo(p_DG->VarEqu.A.FireSecond);
			}
		}
	}

	m_ActivateB = FALSE;
	m_DelayB = _T("");
	m_SetBackB = _T("");
	m_FireSecondB = _T("");
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
					m_DelayB = lr.TrimTrailingZeros((LPCTSTR) m_DelayB);
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
			if (p_DG->VarLoc.B.SetBack >= 0)
			{
				if (p_DG->VarLoc.B.SetBack < MaxParameters)
					m_SetBackB.Format(" X%d", (p_DG->VarLoc.B.SetBack + 1));
			}
			else
			{
				if (p_DG->VarLoc.B.SetBack == -1)
				{
					if (p_DG->Control.B.SetBack > 0.0)
					{
						m_SetBackB.Format(" %8.6f", p_DG->Control.B.SetBack);
						m_SetBackB =  lr.TrimTrailingZeros((LPCTSTR) m_SetBackB);
					}
				}
				else
					m_SetBackB = lr.ReadMemo(p_DG->VarEqu.B.SetBack);
			}
			if (p_DG->VarLoc.B.FireSecond >= 0)
			{
				if (p_DG->VarLoc.B.FireSecond < MaxParameters)
					m_FireSecondB.Format(" X%d", (p_DG->VarLoc.B.FireSecond + 1));
			}
			else
			{
				if (p_DG->VarLoc.B.FireSecond == -1)
				{
					if (p_DG->Control.B.FireSecond > 0.0)
					{
						m_FireSecondB.Format(" %8.6f", p_DG->Control.B.FireSecond);
						m_FireSecondB = lr.TrimTrailingZeros((LPCTSTR) m_FireSecondB);
					}
				}
				else
					m_FireSecondB = lr.ReadMemo(p_DG->VarEqu.B.FireSecond);
			}
		}
	}
	DiscretizeValues();
	return TRUE;
}

BOOL CG04SlavePP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();

	CListRout lr;
	CString jstr;
	p_DG->Control.Gate_AB = m_GateAB;

	p_DG->Control.DT.ResetWhenDone = TRUE;
	p_DG->Control.DT.TriggerEnable = TRUE;


	p_DG->Control.T0.GoSignal &= 0x88;
	p_DG->Control.T0.DoneSignal = 0x0;
	p_DG->Control.T0.FireFirst = -1.0;
	p_DG->Control.T0.SetBack = -1.0;
	p_DG->Control.T0.FireSecond = -1.0;
	p_DG->Control.T0.OutputModulo = 1;
	p_DG->VarLoc.T0.FireFirst = -1;
	p_DG->VarLoc.T0.SetBack = -1;
	p_DG->VarLoc.T0.FireSecond = -1;
	p_DG->VarLoc.T0.OutputModulo = -1;
	p_DG->VarEqu.T0.FireFirst[0] = 0;
	p_DG->VarEqu.T0.SetBack[0] = 0;
	p_DG->VarEqu.T0.FireSecond[0] = 0;
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
			jstr = m_SetBackT0;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.T0.SetBack = atof(jstr);
						if ((p_DG->Control.T0.FireFirst >= 0.0) &&
									(p_DG->Control.T0.FireFirst >= p_DG->Control.T0.SetBack))
						{
							p_DG->Control.T0.SetBack = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.T0.SetBack = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.T0.SetBack = -2;
							lr.WriteMemo(p_DG->VarEqu.T0.SetBack, (LPCTSTR)m_SetBackT0, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.T0.SetBack = -2;
					lr.WriteMemo(p_DG->VarEqu.T0.SetBack, (LPCTSTR)m_SetBackT0, 64);
				}
			}
			jstr = m_FireSecondT0;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.T0.FireSecond = atof(jstr);
						if ((p_DG->Control.T0.SetBack >= 0.0) &&
									(p_DG->Control.T0.SetBack >= p_DG->Control.T0.FireSecond))
						{
							p_DG->Control.T0.FireSecond = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.T0.FireSecond = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.T0.FireSecond = -2;
							lr.WriteMemo(p_DG->VarEqu.T0.FireSecond, (LPCTSTR)m_FireSecondT0, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.T0.FireSecond = -2;
					lr.WriteMemo(p_DG->VarEqu.T0.FireSecond, (LPCTSTR)m_FireSecondT0, 64);
				}
			}
		}
	}

	p_DG->Control.A.GoSignal &= 0x88;
	p_DG->Control.A.DoneSignal = 0x0;
	p_DG->Control.A.FireFirst = -1.0;
	p_DG->Control.A.SetBack = -1.0;
	p_DG->Control.A.FireSecond = -1.0;
	p_DG->Control.A.OutputModulo = 1;
	p_DG->VarLoc.A.FireFirst = -1;
	p_DG->VarLoc.A.SetBack = -1;
	p_DG->VarLoc.A.FireSecond = -1;
	p_DG->VarEqu.A.FireFirst[0] = 0;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarEqu.A.SetBack[0] = 0;
	p_DG->VarEqu.A.FireSecond[0] = 0;
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
			jstr = m_SetBackA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.A.SetBack = atof(jstr);
						if ((p_DG->Control.A.FireFirst >= 0.0) &&
									(p_DG->Control.A.FireFirst >= p_DG->Control.A.SetBack))
						{
							p_DG->Control.A.SetBack = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.A.SetBack = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.A.SetBack = -2;
							lr.WriteMemo(p_DG->VarEqu.A.SetBack, (LPCTSTR)m_SetBackA, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.A.SetBack = -2;
					lr.WriteMemo(p_DG->VarEqu.A.SetBack, (LPCTSTR)m_SetBackA, 64);
				}
			}
			jstr = m_FireSecondA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.A.FireSecond = atof(jstr);
						if ((p_DG->Control.A.SetBack >= 0.0) &&
									(p_DG->Control.A.SetBack >= p_DG->Control.A.FireSecond))
						{
							p_DG->Control.A.FireSecond = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.A.FireSecond = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.A.FireSecond = -2;
							lr.WriteMemo(p_DG->VarEqu.A.FireSecond, (LPCTSTR)m_FireSecondA, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.A.FireSecond = -2;
					lr.WriteMemo(p_DG->VarEqu.A.FireSecond, (LPCTSTR)m_FireSecondA, 64);
				}
			}
		}
	}

	p_DG->Control.B.GoSignal &= 0x88;
	p_DG->Control.B.DoneSignal = 0x0;
	p_DG->Control.B.FireFirst = -1.0;
	p_DG->Control.B.SetBack = -1.0;
	p_DG->Control.B.FireSecond = -1.0;
	p_DG->Control.B.OutputModulo = 1;
	p_DG->VarLoc.B.FireFirst = -1;
	p_DG->VarLoc.B.SetBack = -1;
	p_DG->VarLoc.B.FireSecond = -1;
	p_DG->VarLoc.B.OutputModulo = -1;
	p_DG->VarEqu.B.FireFirst[0] = 0;
	p_DG->VarEqu.B.SetBack[0] = 0;
	p_DG->VarEqu.B.FireSecond[0] = 0;
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
			jstr = m_SetBackB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.B.SetBack = atof(jstr);
						if ((p_DG->Control.B.FireFirst >= 0.0) &&
									(p_DG->Control.B.FireFirst >= p_DG->Control.B.SetBack))
						{
							p_DG->Control.B.SetBack = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.B.SetBack = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.B.SetBack = -2;
							lr.WriteMemo(p_DG->VarEqu.B.SetBack, (LPCTSTR)m_SetBackB, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.B.SetBack = -2;
					lr.WriteMemo(p_DG->VarEqu.B.SetBack, (LPCTSTR)m_SetBackB, 64);
				}
			}
			jstr = m_FireSecondB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
					{
						p_DG->Control.B.FireSecond = atof(jstr);
						if ((p_DG->Control.B.SetBack >= 0.0) &&
									(p_DG->Control.B.SetBack >= p_DG->Control.B.FireSecond))
						{
							p_DG->Control.B.FireSecond = -1.0;
						}
					}
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.B.FireSecond = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.B.FireSecond = -2;
							lr.WriteMemo(p_DG->VarEqu.B.FireSecond, (LPCTSTR)m_FireSecondB, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.B.FireSecond = -2;
					lr.WriteMemo(p_DG->VarEqu.B.FireSecond, (LPCTSTR)m_FireSecondB, 64);
				}
			}
		}
	}


	return TRUE;
}

void CG04SlavePP::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	if (T0_Name.GetLength() > 0)
		m_ActivateT0_B.SetWindowText((LPCTSTR)T0_Name);
	if (A_Name.GetLength() > 0)
		m_ActivateA_B.SetWindowText((LPCTSTR)A_Name);
	if (B_Name.GetLength() > 0)
		m_ActivateB_B.SetWindowText((LPCTSTR)B_Name);
}
