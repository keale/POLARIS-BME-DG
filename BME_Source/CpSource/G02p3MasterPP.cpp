// G02p3MasterPP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G02p3MasterPP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG02p3MasterPP property page

IMPLEMENT_DYNCREATE(CG02p3MasterPP, CPropertyPage)

CG02p3MasterPP::CG02p3MasterPP() : CPropertyPage(CG02p3MasterPP::IDD)
{
	//{{AFX_DATA_INIT(CG02p3MasterPP)
	m_ActivateA = FALSE;
	m_ActivateB = FALSE;
	m_ActivateT0 = FALSE;
	m_FtActivateA = FALSE;
	m_FtActivateB = FALSE;
	m_FtActivateT0 = FALSE;
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayT0 = _T("");
	m_External = FALSE;
	m_Falling = FALSE;
	m_GateAB = FALSE;
	m_Internal = FALSE;
	m_PresetValue = _T("");
	m_Rising = FALSE;
	m_StopOnPreset = FALSE;
	m_InhibitTrigger = _T("");
	m_ForceTrigger = _T("");
	m_TriggerCount = _T("");
	m_TriggerLevel = _T("");
	m_ReadTriggers = FALSE;
	m_GateDivider = _T("");
	m_GatePositive = FALSE;
	m_GateNegative = FALSE;
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	m_A_Name = _T("");
	m_B_Name = _T("");
	m_T0_Name = _T("");
	//}}AFX_DATA_INIT
	b_CrystalOscillator = FALSE;
	b_FastApply = FALSE;
	b_PageActive = FALSE;
	b_RequestZeroCounter = FALSE;
	m_DG_Number = -1;
	m_DG_Product = -1;
	T0_Name = _T("");
	A_Name = _T("");
	B_Name = _T("");
	NoEvents = 0;
}

CG02p3MasterPP::~CG02p3MasterPP()
{
}

void CG02p3MasterPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG02p3MasterPP)
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevelED);
	DDX_Control(pDX, IDC_PRESET_VALUE, m_PresetValueED);
	DDX_Control(pDX, IDC_INHIBIT_TRIGGER, m_InhibitTriggerED);
	DDX_Control(pDX, IDC_FORCE_TRIGGER, m_ForceTriggerED);
	DDX_Control(pDX, IDC_GATE_DIVIDER, m_GateDividerED);
	DDX_Control(pDX, IDC_RISING, m_RisingB);
	DDX_Control(pDX, IDC_FALLING, m_FallingB);
	DDX_Control(pDX, IDC_EXTERNAL, m_ExternalB);
	DDX_Control(pDX, IDC_DESIGNATOR, m_Designator);
	DDX_Check(pDX, IDC_ACTIVATE_A, m_ActivateA);
	DDX_Check(pDX, IDC_ACTIVATE_B, m_ActivateB);
	DDX_Check(pDX, IDC_ACTIVATE_T0, m_ActivateT0);
	DDX_Check(pDX, IDC_FT_ACTIVATE_A, m_FtActivateA);
	DDX_Check(pDX, IDC_FT_ACTIVATE_B, m_FtActivateB);
	DDX_Check(pDX, IDC_FT_ACTIVATE_T0, m_FtActivateT0);
	DDX_Text(pDX, IDC_DELAY_A, m_DelayA);
	DDV_MaxChars(pDX, m_DelayA, 32);
	DDX_Text(pDX, IDC_DELAY_B, m_DelayB);
	DDV_MaxChars(pDX, m_DelayB, 32);
	DDX_Text(pDX, IDC_DELAY_T0, m_DelayT0);
	DDV_MaxChars(pDX, m_DelayT0, 32);
	DDX_Check(pDX, IDC_EXTERNAL, m_External);
	DDX_Check(pDX, IDC_FALLING, m_Falling);
	DDX_Check(pDX, IDC_GATE_AB, m_GateAB);
	DDX_Check(pDX, IDC_INTERNAL, m_Internal);
	DDX_Text(pDX, IDC_PRESET_VALUE, m_PresetValue);
	DDV_MaxChars(pDX, m_PresetValue, 32);
	DDX_Check(pDX, IDC_RISING, m_Rising);
	DDX_Check(pDX, IDC_STOP_ON_PRESET, m_StopOnPreset);
	DDX_Text(pDX, IDC_INHIBIT_TRIGGER, m_InhibitTrigger);
	DDV_MaxChars(pDX, m_InhibitTrigger, 32);
	DDX_Text(pDX, IDC_FORCE_TRIGGER, m_ForceTrigger);
	DDV_MaxChars(pDX, m_ForceTrigger, 32);
	DDX_Text(pDX, IDC_TRIGGER_COUNT, m_TriggerCount);
	DDV_MaxChars(pDX, m_TriggerCount, 16);
	DDX_Check(pDX, IDC_READ_TRIGGERS, m_ReadTriggers);
	DDX_Text(pDX, IDC_GATE_DIVIDER, m_GateDivider);
	DDV_MaxChars(pDX, m_GateDivider, 16);
	DDX_Text(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevel);
	DDV_MaxChars(pDX, m_TriggerLevel, 16);
	DDX_Check(pDX, IDC_GATE_POSITIVE, m_GatePositive);
	DDX_Check(pDX, IDC_GATE_NEGATIVE, m_GateNegative);
	DDX_Check(pDX, IDC_IGNORE, m_Ignore);
	DDX_Check(pDX, IDC_MEMORIZE, m_Memorize);
	DDX_Text(pDX, IDC_A_NAME, m_A_Name);
	DDV_MaxChars(pDX, m_A_Name, 32);
	DDX_Text(pDX, IDC_B_NAME, m_B_Name);
	DDV_MaxChars(pDX, m_B_Name, 32);
	DDX_Text(pDX, IDC_T0_NAME, m_T0_Name);
	DDV_MaxChars(pDX, m_T0_Name, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG02p3MasterPP, CPropertyPage)
	ON_MESSAGE(WM_LOAD_COUNTER_REQUEST_G02, OnChangeObjectProps)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_PRD, OnScrollInhibitTrigger)
	ON_MESSAGE(WM_USER_REQUEST_FTR, OnScrollForceTrigger)
	ON_MESSAGE(WM_USER_REQUEST_TLV, OnScrollTriggerLevel)
	ON_MESSAGE(WM_USER_REQUEST_GD, OnScrollGateDivider)
	ON_MESSAGE(WM_USER_REQUEST_PVA, OnScrollPresetValue)
	//{{AFX_MSG_MAP(CG02p3MasterPP)
	ON_BN_CLICKED(IDC_ACTIVATE_A, OnActivateA)
	ON_BN_CLICKED(IDC_ACTIVATE_B, OnActivateB)
	ON_BN_CLICKED(IDC_ACTIVATE_T0, OnActivateT0)
	ON_BN_CLICKED(IDC_FT_ACTIVATE_A, OnFtActivateA)
	ON_BN_CLICKED(IDC_FT_ACTIVATE_B, OnFtActivateB)
	ON_BN_CLICKED(IDC_FT_ACTIVATE_T0, OnFtActivateT0)
	ON_EN_CHANGE(IDC_DELAY_A, OnChangeDelayA)
	ON_EN_CHANGE(IDC_DELAY_B, OnChangeDelayB)
	ON_EN_CHANGE(IDC_DELAY_T0, OnChangeDelayT0)
	ON_BN_CLICKED(IDC_EXTERNAL, OnExternal)
	ON_BN_CLICKED(IDC_FALLING, OnFalling)
	ON_BN_CLICKED(IDC_GATE_AB, OnGateAb)
	ON_BN_CLICKED(IDC_INTERNAL, OnInternal)
	ON_EN_CHANGE(IDC_PRESET_VALUE, OnChangePresetValue)
	ON_BN_CLICKED(IDC_RISING, OnRising)
	ON_BN_CLICKED(IDC_STOP_ON_PRESET, OnStopOnPreset)
	ON_EN_CHANGE(IDC_INHIBIT_TRIGGER, OnChangeInhibitTrigger)
	ON_EN_KILLFOCUS(IDC_INHIBIT_TRIGGER, OnKillfocusInhibitTrigger)
	ON_EN_CHANGE(IDC_FORCE_TRIGGER, OnChangeForceTrigger)
	ON_EN_KILLFOCUS(IDC_FORCE_TRIGGER, OnKillfocusForceTrigger)
	ON_EN_KILLFOCUS(IDC_DELAY_T0, OnKillfocusDelayT0)
	ON_EN_KILLFOCUS(IDC_PRESET_VALUE, OnKillfocusPresetValue)
	ON_BN_CLICKED(IDC_RESET_COUNTER, OnResetCounter)
	ON_EN_CHANGE(IDC_TRIGGER_COUNT, OnChangeTriggerCount)
	ON_WM_SHOWWINDOW()
	ON_EN_KILLFOCUS(IDC_DELAY_A, OnKillfocusDelayA)
	ON_EN_KILLFOCUS(IDC_DELAY_B, OnKillfocusDelayB)
	ON_BN_CLICKED(IDC_READ_TRIGGERS, OnReadTriggers)
	ON_EN_CHANGE(IDC_GATE_DIVIDER, OnChangeGateDivider)
	ON_EN_KILLFOCUS(IDC_GATE_DIVIDER, OnKillfocusGateDivider)
	ON_EN_CHANGE(IDC_TRIGGER_LEVEL, OnChangeTriggerLevel)
	ON_EN_KILLFOCUS(IDC_TRIGGER_LEVEL, OnKillfocusTriggerLevel)
	ON_BN_CLICKED(IDC_GATE_POSITIVE, OnGatePositive)
	ON_BN_CLICKED(IDC_GATE_NEGATIVE, OnGateNegative)
	ON_BN_CLICKED(IDC_IGNORE, OnIgnore)
	ON_BN_CLICKED(IDC_MEMORIZE, OnMemorize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG02p3MasterPP message handlers

LRESULT CG02p3MasterPP::OnChangeObjectProps(WPARAM, LPARAM)
{
	LoadTriggerCounter(NoEvents);
	return 0;
}

void CG02p3MasterPP::OnActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02p3MasterPP::OnActivateA() 
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

void CG02p3MasterPP::OnActivateB() 
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

void CG02p3MasterPP::OnFtActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02p3MasterPP::OnFtActivateA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_FtActivateA)
	{
		m_GateAB = FALSE;
		UpdateData(FALSE);
	}
}

void CG02p3MasterPP::OnFtActivateB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_FtActivateB)
	{
		m_GateAB = FALSE;
		UpdateData(FALSE);
	}
}

void CG02p3MasterPP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollDelayA(WPARAM, LPARAM)
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

void CG02p3MasterPP::OnKillfocusDelayA() 
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

void CG02p3MasterPP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollDelayB(WPARAM, LPARAM)
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

void CG02p3MasterPP::OnKillfocusDelayB() 
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

void CG02p3MasterPP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollDelayT0(WPARAM, LPARAM)
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

void CG02p3MasterPP::OnKillfocusDelayT0() 
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

void CG02p3MasterPP::OnGateAb() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateAB)
	{
		if ((m_FtActivateA) || (m_FtActivateB))
		{
			m_FtActivateA = TRUE;
			m_FtActivateB = TRUE;
		}
		if ((m_ActivateA) || (m_ActivateB))
		{
			m_ActivateA = TRUE;
			m_ActivateB = TRUE;
		}
		UpdateData(FALSE);
	}
}

void CG02p3MasterPP::OnReadTriggers() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02p3MasterPP::OnStopOnPreset() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_StopOnPreset)
		m_PresetValue = _T("");
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnChangePresetValue() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollPresetValue(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_PresetValueED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_PresetValueED.GetSel(nStartChar, nEndChar);
			m_PresetValue = lr.ScrollInteger(m_PresetValue, nEndChar, 
								m_PresetValueED.PresentCharacter, m_PresetValueED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_PresetValueED.SetSel(nEndChar, nEndChar);
			}
			b_FastApply = FALSE;
			break;
		default:
			break;
	}
	return 0;
}

void CG02p3MasterPP::OnKillfocusPresetValue() 
{
	CListRout lr;
	lr.TrimString(m_PresetValue);
	if (m_PresetValue.GetLength() > 0)
	{
		int t1 = max(1, RoundInt(atof(m_PresetValue)));
		m_PresetValue.Format(" %1d",t1);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG02p3MasterPP::OnExternal() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_External)
	{
		m_Internal = FALSE;
		if ((!m_Falling) && (!m_Rising))
			m_Rising = TRUE;
	}
	else
	{
		m_Internal = TRUE;
		m_Rising = FALSE;
		m_Falling = FALSE;
	}
	UpdateData(FALSE);
}


void CG02p3MasterPP::OnInternal() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_External = FALSE;
		m_Rising = FALSE;
		m_Falling = FALSE;
		if (b_CrystalOscillator)
			m_TriggerLevel = _T("");
	}
	else
	{
		if (b_CrystalOscillator)
			m_External = TRUE;
		else
		{
			m_Internal = TRUE;
			m_External = FALSE;
			m_Rising = FALSE;
			m_Falling = FALSE;
		}
		if (m_External)
		{
			if ((!m_Falling) && (!m_Rising))
				m_Rising = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnFalling() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_Internal = FALSE;
		m_External = TRUE;
	}
	m_Rising = !m_Falling;
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnRising() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_Internal = FALSE;
		m_External = TRUE;
	}
	m_Falling = !m_Rising;
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnIgnore() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Ignore)
	{
		m_Memorize = FALSE;
		if ((!m_GatePositive) && (!m_GateNegative))
			m_GatePositive = TRUE;
	}
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnMemorize() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Memorize)
	{
		m_Ignore = FALSE;
		if ((!m_GatePositive) && (!m_GateNegative))
			m_GatePositive = TRUE;
	}
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnGatePositive() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GatePositive)
		m_GateNegative = FALSE;
	if ((!m_GatePositive) && (!m_GateNegative))
	{
		m_GateDivider = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
	}
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnGateNegative() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateNegative)
		m_GatePositive = FALSE;
	if ((!m_GatePositive) && (!m_GateNegative))
	{
		m_GateDivider = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
	}
	UpdateData(FALSE);
}

void CG02p3MasterPP::OnChangeGateDivider() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollGateDivider(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_GateDividerED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_GateDividerED.GetSel(nStartChar, nEndChar);
			m_GateDivider = lr.ScrollInteger(m_GateDivider, nEndChar, 
								m_GateDividerED.PresentCharacter, m_GateDividerED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_GateDividerED.SetSel(nEndChar, nEndChar);
			}
			b_FastApply = FALSE;
			break;
		default:
			break;
	}
	return 0;
}

void CG02p3MasterPP::OnKillfocusGateDivider() 
{
	CListRout lr;
	lr.TrimString(m_GateDivider);
	if (m_GateDivider.GetLength() > 0)
	{
		int t1 = min(256, max(0, RoundInt(atof(m_GateDivider))));
		m_GateDivider.Format(" %1d",t1);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG02p3MasterPP::OnChangeInhibitTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollInhibitTrigger(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_InhibitTriggerED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_InhibitTriggerED.GetSel(nStartChar, nEndChar);
			m_InhibitTrigger = lr.ScrollEquation(m_InhibitTrigger, nEndChar, 
								m_InhibitTriggerED.PresentCharacter, m_InhibitTriggerED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_InhibitTriggerED.SetSel(nEndChar, nEndChar);
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

void CG02p3MasterPP::OnKillfocusInhibitTrigger() 
{
	CListRout lr;
	lr.TrimString(m_InhibitTrigger);
	if (m_InhibitTrigger.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)m_InhibitTrigger))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)m_InhibitTrigger) == 1)
			{
				if (lr.Numeric(m_InhibitTrigger))
				{
					double t1 = p_G0xData->RoundRepCounter(atof(m_InhibitTrigger), m_DG_Number);
					m_InhibitTrigger.Format(" %8.6f",t1);
					m_InhibitTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_InhibitTrigger);
				}
				else
					m_InhibitTrigger = p_G0xData->AllowedParameter((LPCTSTR)m_InhibitTrigger);
				UpdateData(FALSE);
			}
		}
	}
	b_FastApply = FALSE;
}

void CG02p3MasterPP::OnChangeForceTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollForceTrigger(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ForceTriggerED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ForceTriggerED.GetSel(nStartChar, nEndChar);
			m_ForceTrigger = lr.ScrollDouble(m_ForceTrigger, nEndChar, 
								m_ForceTriggerED.PresentCharacter, m_ForceTriggerED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ForceTriggerED.SetSel(nEndChar, nEndChar);
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

void CG02p3MasterPP::OnKillfocusForceTrigger() 
{
	CListRout lr;
	lr.TrimString(m_ForceTrigger);
	if (m_ForceTrigger.GetLength() > 0)
	{
		double t1 = p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG02p3MasterPP::OnChangeTriggerLevel() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02p3MasterPP::OnScrollTriggerLevel(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_TriggerLevelED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_TriggerLevelED.GetSel(nStartChar, nEndChar);
			m_TriggerLevel = lr.ScrollDouble(m_TriggerLevel, nEndChar, 
								m_TriggerLevelED.PresentCharacter, m_TriggerLevelED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_TriggerLevelED.SetSel(nEndChar, nEndChar);
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

void CG02p3MasterPP::OnKillfocusTriggerLevel() 
{
	CListRout lr;
	lr.TrimString(m_TriggerLevel);
	if (m_TriggerLevel.GetLength() > 0)
	{
		double v0 = atof(m_TriggerLevel);
		int DAC_Value = RoundInt(((v0 + 2.5) * 4096.0 / 5.0));
		DAC_Value = max(0, min(4095, DAC_Value));
		v0 = (5.0 * double(DAC_Value) / 4096.0) - 2.5;
		m_TriggerLevel.Format(" %6.4f", v0);
		m_TriggerLevel =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerLevel);
		if (m_Internal)
		{
			if (b_CrystalOscillator)
			{
				m_Internal = FALSE;
				m_External = TRUE;
				if ((!m_Rising) && (!m_Falling))
					m_Rising = TRUE;
			}
		}
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG02p3MasterPP::OnResetCounter() 
{
	b_RequestZeroCounter = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G02, 0, 0);
}

void CG02p3MasterPP::OnChangeTriggerCount() 
{
	UpdateData(FALSE);
}

BOOL CG02p3MasterPP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	SetEvent(DataNotification);
	return CPropertyPage::OnSetActive();
}

BOOL CG02p3MasterPP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG02p3MasterPP::LoadTriggerCounter(unsigned long TriggerCount)
{
	m_TriggerCount.Format(" %u", TriggerCount);
	if (b_PageActive)
		UpdateData(FALSE);
}

void CG02p3MasterPP::DiscretizeValues()
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
	lr.TrimString(m_PresetValue);
	if (m_PresetValue.GetLength() > 0)
	{
		int t1 = max(1, RoundInt(atof(m_PresetValue)));
		m_PresetValue.Format(" %1d",t1);
	}
	lr.TrimString(m_GateDivider);
	if (m_GateDivider.GetLength() > 0)
	{
		int t1 = min(256, max(0, RoundInt(atof(m_GateDivider))));
		m_GateDivider.Format(" %1d",t1);
	}
	
	lr.TrimString(m_InhibitTrigger);
	if (m_InhibitTrigger.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_InhibitTrigger) == 1)
		{
			if (lr.Numeric(m_InhibitTrigger))
			{
				double t1 = p_G0xData->RoundRepCounter(atof(m_InhibitTrigger), m_DG_Number);
				m_InhibitTrigger.Format(" %8.6f",t1);
				m_InhibitTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_InhibitTrigger);
			}
			else
				m_InhibitTrigger = p_G0xData->AllowedParameter((LPCTSTR)m_InhibitTrigger);
		}
		else
			m_InhibitTrigger = " " + m_InhibitTrigger;
	}
	lr.TrimString(m_ForceTrigger);
	if (m_ForceTrigger.GetLength() > 0)
	{
		double t1 = p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
	}
	lr.TrimString(m_TriggerLevel);
	if (m_TriggerLevel.GetLength() > 0)
	{
		double v0 = atof(m_TriggerLevel);
		int DAC_Value = RoundInt(((v0 + 2.5) * 4096.0 / 5.0));
		DAC_Value = max(0, min(4095, DAC_Value));
		v0 = (5.0 * double(DAC_Value) / 4096.0) - 2.5;
		m_TriggerLevel.Format(" %6.4f", v0);
		m_TriggerLevel =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerLevel);
	}
	if (b_PageActive)
		UpdateData(FALSE);
}

BOOL CG02p3MasterPP::DistributeVariables(DG_Type* p_DG)
{
	double t1;
	m_Delay_T0ED.MessageNumber = WM_USER_REQUEST_T0;
	m_Delay_T0ED.p_ParentWindow = this;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	m_InhibitTriggerED.MessageNumber = WM_USER_REQUEST_PRD;
	m_InhibitTriggerED.p_ParentWindow = this;
	m_ForceTriggerED.MessageNumber = WM_USER_REQUEST_FTR;
	m_ForceTriggerED.p_ParentWindow = this;
	m_TriggerLevelED.MessageNumber = WM_USER_REQUEST_TLV;
	m_TriggerLevelED.p_ParentWindow = this;
	m_GateDividerED.MessageNumber = WM_USER_REQUEST_GD;
	m_GateDividerED.p_ParentWindow = this;
	m_PresetValueED.MessageNumber = WM_USER_REQUEST_PVA;
	m_PresetValueED.p_ParentWindow = this;
	b_FastApply = FALSE;

	CListRout lr;
	m_DG_Product = p_DG->Control.DG_Product;
	T0_Name = lr.ReadMemo(p_DG->T0_Name);
	if (T0_Name.GetLength() > 0)
		m_T0_Name = T0_Name;
	else
		m_T0_Name = _T("T  ");
	A_Name = lr.ReadMemo(p_DG->A_Name);
	if (A_Name.GetLength() > 0)
		m_A_Name = A_Name;
	else
		m_A_Name = _T("A  ");
	B_Name = lr.ReadMemo(p_DG->B_Name);
	if (B_Name.GetLength() > 0)
		m_B_Name = B_Name;
	else
		m_B_Name = _T("B  ");
	m_ReadTriggers = p_DG->ReadTriggers;
	b_CrystalOscillator = TRUE;
	switch (p_DG->Control.DT.ClockSource)
	{
		case TriggerInput:
		case TriggerAndOscillator:
			b_CrystalOscillator = FALSE;
			break;
		default:
			break;
	}

	
	m_GateAB = p_DG->Control.Gate_AB;

	m_Internal = p_DG->Control.DT.InternalTrigger;
	m_External = !m_Internal;
	if (!b_CrystalOscillator)
	{
		m_External = FALSE;
		m_Internal = TRUE;
	}
	m_GatePositive = FALSE;
	m_GateNegative = FALSE;
	if (!p_DG->Control.DT.TriggerEnable)
	{
		if (p_DG->Control.DT.PositiveGate)
			m_GatePositive = TRUE;
		else
			m_GateNegative = TRUE;
		m_GateDivider.Format(" %d", max(0, min(256, p_DG->Control.DT.GateDivider)));
	}
	else
		m_GateDivider = _T("");
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	if (m_GatePositive || m_GateNegative)
	{
		if (p_DG->Control.DT.IgnoreGate)
			m_Ignore = TRUE;
		else
			m_Memorize = TRUE;
	}
	if (m_Internal)
	{
		m_Rising = FALSE;
		m_Falling = FALSE;
	}
	else
	{
		m_Rising = p_DG->Control.DT.RisingEdge;
		m_Falling = !m_Rising;
	}
	int MaxParameters = p_G0xData->ParameterList.NoParameters;
	if (p_DG->VarLoc.RepCounter >= 0)
	{
		if (p_DG->VarLoc.RepCounter < MaxParameters)
		{
			m_InhibitTrigger.Format(" X%d", (p_DG->VarLoc.RepCounter + 1));
		}
	}
	else
	{
		if (p_DG->VarLoc.RepCounter == -1)
		{
			if (p_DG->Control.DT.InhibitTrigger >= 0.0)
			{
				t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.InhibitTrigger, m_DG_Number);
				m_InhibitTrigger.Format(" %8.6f",t1);
				m_InhibitTrigger = lr.TrimTrailingZeros((LPCTSTR)m_InhibitTrigger);
			}
		}
		else
		{
			m_InhibitTrigger = lr.ReadMemo(p_DG->VarEqu.RepCounter);
		}
	}
	if (p_DG->Control.DT.ForceTrigger >= 0.0)
	{
		t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.ForceTrigger, m_DG_Number);
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
	}
	if ((m_External) || (p_DG->Control.DT.ClockSource == TriggerInput) ||
											(p_DG->Control.DT.ClockSource == TriggerAndOscillator))
	{
		m_TriggerLevel.Format(" %6.4f", p_DG->Control.DT.TriggerLevel);
		m_TriggerLevel =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerLevel);
	}
	else
		m_TriggerLevel = _T("");
	m_StopOnPreset = p_DG->Control.DT.StopOnPreset;
	if (m_StopOnPreset)
		m_PresetValue.Format(" %1d", p_DG->Control.DT.PresetValue);
	else
		m_PresetValue = _T("");

	BOOL b_ChannelActive;
	b_ChannelActive = FALSE;
	m_ActivateT0 = FALSE;
	m_FtActivateT0 = FALSE;
	m_DelayT0 = _T("");
	if ((p_DG->Control.T0.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.T0.FireFirst >= 0)
		{
			if (p_DG->VarLoc.T0.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayT0.Format(" X%d", (p_DG->VarLoc.T0.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.T0.FireFirst == -1)
			{
				if (p_DG->Control.T0.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayT0.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.T0.FireFirst, m_DG_Number));
					m_DelayT0 = lr.TrimTrailingZeros((LPCTSTR) m_DelayT0);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayT0 = lr.ReadMemo(p_DG->VarEqu.T0.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.T0.GoSignal & MasterPrimary) != 0x0)
				m_ActivateT0 = TRUE;
			if ((p_DG->Control.T0.GoSignal & LocalForce) != 0x0)
				m_FtActivateT0 = TRUE;
		}
	}

	b_ChannelActive = FALSE;
	m_ActivateA = FALSE;
	m_FtActivateA = FALSE;
	m_DelayA = _T("");
	if ((p_DG->Control.A.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.A.FireFirst >= 0)
		{
			if (p_DG->VarLoc.A.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayA.Format(" X%d", (p_DG->VarLoc.A.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.A.FireFirst == -1)
			{
				if (p_DG->Control.A.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayA.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.A.FireFirst, m_DG_Number));
					m_DelayA = lr.TrimTrailingZeros((LPCTSTR) m_DelayA);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayA = lr.ReadMemo(p_DG->VarEqu.A.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.A.GoSignal & MasterPrimary) != 0x0)
				m_ActivateA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalForce) != 0x0)
				m_FtActivateA = TRUE;
		}
	}

	b_ChannelActive = FALSE;
	m_ActivateB = FALSE;
	m_FtActivateB = FALSE;
	m_DelayB = _T("");
	if ((p_DG->Control.B.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.B.FireFirst >= 0)
		{
			if (p_DG->VarLoc.B.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayB.Format(" X%d", (p_DG->VarLoc.B.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.B.FireFirst == -1)
			{
				if (p_DG->Control.B.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayB.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.B.FireFirst, m_DG_Number));
					m_DelayB = lr.TrimTrailingZeros((LPCTSTR) m_DelayB);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayB = lr.ReadMemo(p_DG->VarEqu.B.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.B.GoSignal & MasterPrimary) != 0x0)
				m_ActivateB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalForce) != 0x0)
				m_FtActivateB = TRUE;
		}
	}

	DiscretizeValues();
	return TRUE;
}

BOOL CG02p3MasterPP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();
	CListRout lr;
	CString jstr;
	p_DG->ReadTriggers = m_ReadTriggers;

	p_DG->Control.Gate_AB = m_GateAB;

	p_DG->Control.DT.SoftwareTrigger = FALSE;
	p_DG->Control.DT.InternalTrigger = m_Internal;

	p_DG->VarLoc.RepCounter = -1;
	p_DG->VarEqu.RepCounter[0] = 0;
	jstr = m_InhibitTrigger;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
		if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
		{
			if (lr.Numeric(jstr))
			{
				p_DG->Control.DT.InhibitTrigger = 
										p_G0xData->RoundRepCounter(atof(m_InhibitTrigger), m_DG_Number);
			}
			else
			{
				if (lr.CommandType(jstr, "x", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					p_DG->VarLoc.RepCounter = (RoundInt(atof(jstr)) - 1);
				}
				else
				{
					p_DG->VarLoc.RepCounter = -2;
					lr.WriteMemo(p_DG->VarEqu.RepCounter, (LPCTSTR)m_InhibitTrigger, 64);
				}
			}
		}
		else
		{
			p_DG->VarLoc.RepCounter = -2;
			lr.WriteMemo(p_DG->VarEqu.T0.FireFirst, (LPCTSTR)m_InhibitTrigger, 64);
		}
	}
	else
		p_DG->Control.DT.InhibitTrigger = -1.0;
	jstr = m_ForceTrigger;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		p_DG->Control.DT.ForceTrigger = 
			p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
	}
	else
		p_DG->Control.DT.ForceTrigger = -1.0;

	p_DG->Control.DT.RisingEdge = m_Rising;
	p_DG->Control.DT.StopOnPreset = m_StopOnPreset;
	if (m_GatePositive)
	{
		p_DG->Control.DT.TriggerEnable = FALSE;
		p_DG->Control.DT.PositiveGate = TRUE;
	}
	else
	{
		if (m_GateNegative)
		{
			p_DG->Control.DT.TriggerEnable = FALSE;
			p_DG->Control.DT.PositiveGate = FALSE;
		}
		else
			p_DG->Control.DT.TriggerEnable = TRUE;
	}
	if ((m_GatePositive) || (m_GateNegative))
	{
		jstr = m_GateDivider;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
			p_DG->Control.DT.GateDivider = RoundInt(atof(m_GateDivider));
		if (m_Ignore)
			p_DG->Control.DT.IgnoreGate = TRUE;
		else
			p_DG->Control.DT.IgnoreGate = FALSE;
	}
	if (m_StopOnPreset)
	{
		jstr = m_PresetValue;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
			p_DG->Control.DT.PresetValue = RoundInt(atof(m_PresetValue));
	}
	p_DG->Control.DT.ResetWhenDone = TRUE;
	jstr = m_TriggerLevel;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
		p_DG->Control.DT.TriggerLevel = atof(m_TriggerLevel);
	


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
	if ((m_ActivateT0) || (m_FtActivateT0))
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
			if (m_ActivateT0)
				p_DG->Control.T0.GoSignal |= MasterPrimary;
			else
				p_DG->Control.T0.DoneSignal |= MasterPrimary;
			if (m_FtActivateT0)
				p_DG->Control.T0.GoSignal |= LocalForce;
			else
				p_DG->Control.T0.DoneSignal |= LocalForce;
		}
	}

	p_DG->Control.A.GoSignal &= 0x88;
	p_DG->Control.A.DoneSignal = 0x0;
	p_DG->Control.A.FireFirst = -1.0;
	p_DG->Control.A.SetBack = -1.0;
	p_DG->Control.A.OutputModulo = 1;
	p_DG->VarLoc.A.FireFirst = -1;
	p_DG->VarLoc.A.SetBack = -1;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarEqu.A.FireFirst[0] = 0;
	p_DG->VarEqu.A.SetBack[0] = 0;
	p_DG->VarEqu.A.OutputModulo[0] = 0;
	if ((m_ActivateA) || (m_FtActivateA))
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
			if (m_ActivateA)
				p_DG->Control.A.GoSignal |= MasterPrimary;
			else
				p_DG->Control.A.DoneSignal |= MasterPrimary;
			if (m_FtActivateA)
				p_DG->Control.A.GoSignal |= LocalForce;
			else
				p_DG->Control.A.DoneSignal |= LocalForce;
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
	if ((m_ActivateB) || (m_FtActivateB))
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
			if (m_ActivateB)
				p_DG->Control.B.GoSignal |= MasterPrimary;
			else
				p_DG->Control.B.DoneSignal |= MasterPrimary;
			if (m_FtActivateB)
				p_DG->Control.B.GoSignal |= LocalForce;
			else
				p_DG->Control.B.DoneSignal |= LocalForce;
		}
	}
	return TRUE;
}

void CG02p3MasterPP::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	if (b_CrystalOscillator)
	{
		m_ExternalB.EnableWindow(TRUE);
		m_RisingB.EnableWindow(TRUE);
		m_FallingB.EnableWindow(TRUE);
	}
	else
	{
		m_External = FALSE;
		m_ExternalB.EnableWindow(FALSE);
		m_Rising = FALSE;
		m_RisingB.EnableWindow(FALSE);
		m_Falling = FALSE;
		m_FallingB.EnableWindow(FALSE);
	}
	switch (m_DG_Product)
	{
	case BME_SG02P3:
		m_Designator.SetWindowText("SG02P3 Delay Parameters");
		break;
	}
}