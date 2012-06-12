// G02MasterPP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G02MasterPP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG02MasterPP property page

IMPLEMENT_DYNCREATE(CG02MasterPP, CPropertyPage)

CG02MasterPP::CG02MasterPP() : CPropertyPage(CG02MasterPP::IDD)
{
	//{{AFX_DATA_INIT(CG02MasterPP)
	m_ActivateA = FALSE;
	m_ActivateB = FALSE;
	m_ActivateT0 = FALSE;
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
	m_TriggerPeriod = _T("");
	m_TriggerCount = _T("");
	m_ReadTriggers = FALSE;
	m_ArmByInternal = FALSE;
	m_GateDivider = _T("");
	m_GatePositive = FALSE;
	m_TriggerLevel = _T("");
	m_GateNegative = FALSE;
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	//}}AFX_DATA_INIT
	b_AllowArmInternal = FALSE;
	b_CrystalOscillator = FALSE;
	b_AllowIgnore = FALSE;
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

CG02MasterPP::~CG02MasterPP()
{
}

void CG02MasterPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG02MasterPP)
	DDX_Control(pDX, IDC_PERIOD_NAME, m_PeriodName);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_TRIGGER_PERIOD, m_TriggerPeriodED);
	DDX_Control(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevelED);
	DDX_Control(pDX, IDC_GATE_DIVIDER, m_GateDividerED);
	DDX_Control(pDX, IDC_PRESET_VALUE, m_PresetValueED);
	DDX_Control(pDX, IDC_GATE_NEGATIVE, m_GateNegativeB);
	DDX_Control(pDX, IDC_RISING, m_RisingB);
	DDX_Control(pDX, IDC_FALLING, m_FallingB);
	DDX_Control(pDX, IDC_EXTERNAL, m_ExternalB);
	DDX_Control(pDX, IDC_IGNORE, m_IgnoreB);
	DDX_Control(pDX, IDC_MEMORIZE, m_MemorizeB);
	DDX_Control(pDX, IDC_GATE_POSITIVE, m_GatePositiveB);
	DDX_Control(pDX, IDC_ARM_BY_INTERNAL, m_ArmByInternalB);
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
	DDX_Check(pDX, IDC_EXTERNAL, m_External);
	DDX_Check(pDX, IDC_FALLING, m_Falling);
	DDX_Check(pDX, IDC_GATE_AB, m_GateAB);
	DDX_Check(pDX, IDC_INTERNAL, m_Internal);
	DDX_Text(pDX, IDC_PRESET_VALUE, m_PresetValue);
	DDV_MaxChars(pDX, m_PresetValue, 32);
	DDX_Check(pDX, IDC_RISING, m_Rising);
	DDX_Check(pDX, IDC_STOP_ON_PRESET, m_StopOnPreset);
	DDX_Text(pDX, IDC_TRIGGER_PERIOD, m_TriggerPeriod);
	DDV_MaxChars(pDX, m_TriggerPeriod, 32);
	DDX_Text(pDX, IDC_TRIGGER_COUNT, m_TriggerCount);
	DDV_MaxChars(pDX, m_TriggerCount, 16);
	DDX_Check(pDX, IDC_READ_TRIGGERS, m_ReadTriggers);
	DDX_Check(pDX, IDC_ARM_BY_INTERNAL, m_ArmByInternal);
	DDX_Text(pDX, IDC_GATE_DIVIDER, m_GateDivider);
	DDV_MaxChars(pDX, m_GateDivider, 16);
	DDX_Check(pDX, IDC_GATE_POSITIVE, m_GatePositive);
	DDX_Text(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevel);
	DDV_MaxChars(pDX, m_TriggerLevel, 16);
	DDX_Check(pDX, IDC_GATE_NEGATIVE, m_GateNegative);
	DDX_Check(pDX, IDC_IGNORE, m_Ignore);
	DDX_Check(pDX, IDC_MEMORIZE, m_Memorize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG02MasterPP, CPropertyPage)
	ON_MESSAGE(WM_LOAD_COUNTER_REQUEST_G02, OnChangeObjectProps)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_PRD, OnScrollTriggerPeriod)
	ON_MESSAGE(WM_USER_REQUEST_TLV, OnScrollTriggerLevel)
	ON_MESSAGE(WM_USER_REQUEST_GD, OnScrollGateDivider)
	ON_MESSAGE(WM_USER_REQUEST_PVA, OnScrollPresetValue)
	//{{AFX_MSG_MAP(CG02MasterPP)
	ON_BN_CLICKED(IDC_ACTIVATE_A, OnActivateA)
	ON_BN_CLICKED(IDC_ACTIVATE_B, OnActivateB)
	ON_BN_CLICKED(IDC_ACTIVATE_T0, OnActivateT0)
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
	ON_EN_CHANGE(IDC_TRIGGER_PERIOD, OnChangeTriggerPeriod)
	ON_EN_KILLFOCUS(IDC_DELAY_T0, OnKillfocusDelayT0)
	ON_EN_KILLFOCUS(IDC_PRESET_VALUE, OnKillfocusPresetValue)
	ON_EN_KILLFOCUS(IDC_TRIGGER_PERIOD, OnKillfocusTriggerPeriod)
	ON_BN_CLICKED(IDC_RESET_COUNTER, OnResetCounter)
	ON_EN_CHANGE(IDC_TRIGGER_COUNT, OnChangeTriggerCount)
	ON_WM_SHOWWINDOW()
	ON_EN_KILLFOCUS(IDC_DELAY_A, OnKillfocusDelayA)
	ON_EN_KILLFOCUS(IDC_DELAY_B, OnKillfocusDelayB)
	ON_BN_CLICKED(IDC_READ_TRIGGERS, OnReadTriggers)
	ON_BN_CLICKED(IDC_ARM_BY_INTERNAL, OnArmByInternal)
	ON_BN_CLICKED(IDC_GATE_POSITIVE, OnGatePositive)
	ON_EN_CHANGE(IDC_GATE_DIVIDER, OnChangeGateDivider)
	ON_EN_KILLFOCUS(IDC_GATE_DIVIDER, OnKillfocusGateDivider)
	ON_EN_CHANGE(IDC_TRIGGER_LEVEL, OnChangeTriggerLevel)
	ON_EN_KILLFOCUS(IDC_TRIGGER_LEVEL, OnKillfocusTriggerLevel)
	ON_BN_CLICKED(IDC_GATE_NEGATIVE, OnGateNegative)
	ON_BN_CLICKED(IDC_IGNORE, OnIgnore)
	ON_BN_CLICKED(IDC_MEMORIZE, OnMemorize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG02MasterPP message handlers


LRESULT CG02MasterPP::OnChangeObjectProps(WPARAM, LPARAM)
{
	LoadTriggerCounter(NoEvents);
	return 0;
}

void CG02MasterPP::OnActivateA() 
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

void CG02MasterPP::OnActivateB() 
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

void CG02MasterPP::OnActivateT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02MasterPP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollDelayA(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusDelayA() 
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

void CG02MasterPP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollDelayB(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusDelayB() 
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

void CG02MasterPP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollDelayT0(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusDelayT0() 
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

void CG02MasterPP::OnGateAb() 
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

void CG02MasterPP::OnReadTriggers() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG02MasterPP::OnStopOnPreset() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_StopOnPreset)
		m_PresetValue = _T("");
	UpdateData(FALSE);
}

void CG02MasterPP::OnChangePresetValue() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollPresetValue(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusPresetValue() 
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

void CG02MasterPP::OnExternal() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_External)
	{
		m_Internal = FALSE;
		m_ArmByInternal = FALSE;
		switch (m_DG_Product)
		{
		case BME_SG02P4:
		case BME_SG02P5:
			break;
		default:
			m_TriggerPeriod = _T("");
			break;
		}
		if ((!m_Falling) && (!m_Rising))
			m_Rising = TRUE;
	}
	else
	{
		m_Internal = TRUE;
		m_ArmByInternal = FALSE;
		m_Rising = FALSE;
		m_Falling = FALSE;
	}
	UpdateData(FALSE);
}

void CG02MasterPP::OnArmByInternal() 
{
	if (b_AllowArmInternal)
	{
		UpdateData(TRUE);
		SetModified();
		*p_DataModified = TRUE;
		if (m_ArmByInternal)
		{
			m_External = FALSE;
			m_Internal = FALSE;
			if ((!m_Falling) && (!m_Rising))
				m_Rising = TRUE;
		}
		else
		{
			m_Internal = FALSE;
			m_External = TRUE;
			m_TriggerPeriod = _T("");
			if ((!m_Falling) && (!m_Rising))
				m_Rising = TRUE;
		}
	}
	else
		m_ArmByInternal = FALSE;
	UpdateData(FALSE);
}

void CG02MasterPP::OnInternal() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_External = FALSE;
		m_ArmByInternal = FALSE;
		m_Rising = FALSE;
		m_Falling = FALSE;
		if (b_CrystalOscillator)
			m_TriggerLevel = _T("");
	}
	else
	{
		if (b_AllowArmInternal)
		{
			m_ArmByInternal = TRUE;
			m_External = FALSE;
		}
		else
		{
			m_ArmByInternal = FALSE;
			if (b_CrystalOscillator)
			{
				m_External = TRUE;
				switch (m_DG_Product)
				{
				case BME_SG02P4:
				case BME_SG02P5:
					break;
				default:
					m_TriggerPeriod = _T("");
					break;
				}
			}
			else
			{
				m_Internal = TRUE;
				m_External = FALSE;
				m_Rising = FALSE;
				m_Falling = FALSE;
			}
		}
		if ((m_ArmByInternal) || (m_External))
		{
			if ((!m_Falling) && (!m_Rising))
				m_Rising = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CG02MasterPP::OnFalling() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_Internal = FALSE;
		if (b_AllowArmInternal)
		{
			m_ArmByInternal = TRUE;
			m_External = FALSE;
		}
		else
		{
			m_ArmByInternal = FALSE;
			m_External = TRUE;
			switch (m_DG_Product)
			{
			case BME_SG02P4:
			case BME_SG02P5:
				break;
			default:
				m_TriggerPeriod = _T("");
				break;
			}
		}
	}
	m_Rising = !m_Falling;
	UpdateData(FALSE);
}

void CG02MasterPP::OnRising() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_Internal)
	{
		m_Internal = FALSE;
		if (b_AllowArmInternal)
		{
			m_ArmByInternal = TRUE;
			m_External = FALSE;
		}
		else
		{
			m_ArmByInternal = FALSE;
			m_External = TRUE;
			switch (m_DG_Product)
			{
			case BME_SG02P4:
			case BME_SG02P5:
				break;
			default:
				m_TriggerPeriod = _T("");
				break;
			}
		}
	}
	m_Falling = !m_Rising;
	UpdateData(FALSE);
}

void CG02MasterPP::OnIgnore() 
{
	if (b_AllowIgnore)
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
	}
	else
		m_Ignore = FALSE;
	UpdateData(FALSE);
}

void CG02MasterPP::OnMemorize() 
{
	if (b_AllowIgnore)
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
	}
	else
		m_Memorize = FALSE;
	UpdateData(FALSE);
}

void CG02MasterPP::OnGatePositive() 
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

void CG02MasterPP::OnGateNegative() 
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

void CG02MasterPP::OnChangeGateDivider() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollGateDivider(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusGateDivider() 
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

void CG02MasterPP::OnChangeTriggerPeriod() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollTriggerPeriod(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_TriggerPeriodED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_TriggerPeriodED.GetSel(nStartChar, nEndChar);
			m_TriggerPeriod = lr.ScrollEquation(m_TriggerPeriod, nEndChar, 
								m_TriggerPeriodED.PresentCharacter, m_TriggerPeriodED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_TriggerPeriodED.SetSel(nEndChar, nEndChar);
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

void CG02MasterPP::OnKillfocusTriggerPeriod() 
{
	CListRout lr;
	lr.TrimString(m_TriggerPeriod);
	if (m_TriggerPeriod.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)m_TriggerPeriod))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)m_TriggerPeriod) == 1)
			{
				if (lr.Numeric(m_TriggerPeriod))
				{
					double t1 = p_G0xData->RoundRepCounter(atof(m_TriggerPeriod), m_DG_Number);
					m_TriggerPeriod.Format(" %8.6f",t1);
					m_TriggerPeriod =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerPeriod);
				}
				else
					m_TriggerPeriod = p_G0xData->AllowedParameter((LPCTSTR)m_TriggerPeriod);
			}
			switch (m_DG_Product)
			{
			case BME_SG02P4:
			case BME_SG02P5:
				break;
			default:
				if (m_External)
				{
					m_External = FALSE;
					if (b_AllowArmInternal)
					{
						m_ArmByInternal = TRUE;
						m_Internal = FALSE;
					}
					else
					{
						m_ArmByInternal = FALSE;
						m_Internal = TRUE;
						m_Rising = FALSE;
						m_Falling = FALSE;
					}
				}
				break;
			}
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG02MasterPP::OnChangeTriggerLevel() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG02MasterPP::OnScrollTriggerLevel(WPARAM, LPARAM)
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

void CG02MasterPP::OnKillfocusTriggerLevel() 
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
				if (b_AllowArmInternal)
					m_ArmByInternal = TRUE;
				else
				{
					m_External = TRUE;
					switch (m_DG_Product)
					{
					case BME_SG02P4:
					case BME_SG02P5:
						break;
					default:
						m_TriggerPeriod = _T("");
						break;
					}
				}
				if ((!m_Rising) && (!m_Falling))
					m_Rising = TRUE;
			}
		}
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG02MasterPP::OnResetCounter() 
{
	b_RequestZeroCounter = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G02, 0, 0);
}

void CG02MasterPP::OnChangeTriggerCount() 
{
	UpdateData(FALSE);
}

BOOL CG02MasterPP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	SetEvent(DataNotification);
	return CPropertyPage::OnSetActive();
}

BOOL CG02MasterPP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG02MasterPP::LoadTriggerCounter(unsigned long TriggerCount)
{
	m_TriggerCount.Format(" %u", TriggerCount);
	if (b_PageActive)
		UpdateData(FALSE);
}

void CG02MasterPP::DiscretizeValues()
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
	lr.TrimString(m_TriggerPeriod);
	if (m_TriggerPeriod.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_TriggerPeriod) == 1)
		{
			if (lr.Numeric(m_TriggerPeriod))
			{
				double t1 = p_G0xData->RoundRepCounter(atof(m_TriggerPeriod), m_DG_Number);
				m_TriggerPeriod.Format(" %8.6f",t1);
				m_TriggerPeriod =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerPeriod);
			}
			else
				m_TriggerPeriod = p_G0xData->AllowedParameter((LPCTSTR)m_TriggerPeriod);
		}
		else
			m_TriggerPeriod = " " + m_TriggerPeriod;
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

BOOL CG02MasterPP::DistributeVariables(DG_Type* p_DG)
{
	double t1;
	m_Delay_T0ED.MessageNumber = WM_USER_REQUEST_T0;
	m_Delay_T0ED.p_ParentWindow = this;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	m_TriggerPeriodED.MessageNumber = WM_USER_REQUEST_PRD;
	m_TriggerPeriodED.p_ParentWindow = this;
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
	A_Name = lr.ReadMemo(p_DG->A_Name);
	B_Name = lr.ReadMemo(p_DG->B_Name);
	m_ReadTriggers = p_DG->ReadTriggers;
	b_AllowArmInternal = FALSE;
	b_AllowIgnore = FALSE;
	b_CrystalOscillator = TRUE;
	switch (p_DG->Control.DT.ClockSource)
	{
		case TriggerInput:
		case TriggerAndOscillator:
			b_CrystalOscillator = FALSE;
			break;
		default:
			switch (m_DG_Product)
			{
			case BME_G02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
				b_AllowArmInternal = TRUE;
				break;
			default:
				break;
			}
			break;
	}
	switch (m_DG_Product)
	{
		case BME_SG02P4:
		case BME_SG02P5:
			b_AllowIgnore = TRUE;
			break;
		default:
			break;
	}

	
	m_GateAB = p_DG->Control.Gate_AB;

	m_Internal = p_DG->Control.DT.InternalTrigger;
	m_ArmByInternal = p_DG->Control.DT.InternalArm;
	if (!b_CrystalOscillator)
	{
		m_External = FALSE;
		m_ArmByInternal = FALSE;
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
	}
	if ((m_GatePositive) || (m_GateNegative))
		m_GateDivider.Format(" %d", max(0, min(256, p_DG->Control.DT.GateDivider)));
	else
		m_GateDivider = _T("");

	int MaxParameters = p_G0xData->ParameterList.NoParameters;
	if (p_DG->VarLoc.RepCounter >= 0)
	{
		if (p_DG->VarLoc.RepCounter < MaxParameters)
		{
			m_TriggerPeriod.Format(" X%d", (p_DG->VarLoc.RepCounter + 1));
		}
	}
	else
	{
		if (p_DG->VarLoc.RepCounter == -1)
		{
			if (p_DG->Control.DT.InternalClock > 0.01)
			{
				t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.InternalClock, m_DG_Number);
				m_TriggerPeriod.Format(" %8.6f",t1);
				m_TriggerPeriod = lr.TrimTrailingZeros((LPCTSTR)m_TriggerPeriod);
			}
			else
				m_TriggerPeriod = _T("");
		}
		else
		{
			m_TriggerPeriod = lr.ReadMemo(p_DG->VarEqu.RepCounter);
		}
	}
	if ((m_Internal) || (m_ArmByInternal))
		m_External = FALSE;
	else
	{
		m_External = TRUE;
		switch (m_DG_Product)
		{
			case BME_SG02P4:
			case BME_SG02P5:
				break;
			default:
				m_TriggerPeriod = _T("");
				break;
		}
	}
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	if (m_GatePositive || m_GateNegative)
	{
		if (b_AllowIgnore)
		{
			if (p_DG->Control.DT.IgnoreGate)
				m_Ignore = TRUE;
			else
				m_Memorize = TRUE;
		}
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
	if ((m_External) || (m_ArmByInternal) || (p_DG->Control.DT.ClockSource == TriggerInput) || 
																				(p_DG->Control.DT.ClockSource == TriggerAndOscillator))
	{
		switch (m_DG_Product)
		{
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P4:
		case BME_SG02P5:
			m_TriggerLevel.Format(" %6.4f", p_DG->Control.DT.TriggerLevel);
			m_TriggerLevel =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerLevel);
			break;
		default:
			m_TriggerLevel = _T("");
			break;
		}
	}
	else
		m_TriggerLevel = _T("");
	m_StopOnPreset = p_DG->Control.DT.StopOnPreset;
	if (m_StopOnPreset)
		m_PresetValue.Format(" %1d", p_DG->Control.DT.PresetValue);
	else
		m_PresetValue = _T("");

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

BOOL CG02MasterPP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();
	CListRout lr;
	CString jstr;
	p_DG->ReadTriggers = m_ReadTriggers;

	p_DG->Control.Gate_AB = m_GateAB;

	p_DG->Control.DT.SoftwareTrigger = FALSE;
	p_DG->Control.DT.InternalTrigger = m_Internal;
	p_DG->Control.DT.InternalArm = m_ArmByInternal;
	p_DG->VarLoc.RepCounter = -1;
	p_DG->VarEqu.RepCounter[0] = 0;
	jstr = m_TriggerPeriod;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
		if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
		{
			if (lr.Numeric(jstr))
			{
				p_DG->Control.DT.InternalClock = 
										p_G0xData->RoundRepCounter(atof(m_TriggerPeriod), m_DG_Number);
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
					lr.WriteMemo(p_DG->VarEqu.RepCounter, (LPCTSTR)m_TriggerPeriod, 64);
				}
			}
		}
		else
		{
			p_DG->VarLoc.RepCounter = -2;
			lr.WriteMemo(p_DG->VarEqu.T0.FireFirst, (LPCTSTR)m_TriggerPeriod, 64);
		}
	}
	else
		p_DG->Control.DT.InternalClock = -1.0;
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
	


	p_DG->Control.T0.GoSignal &= 0x188;
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

void CG02MasterPP::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	if (T0_Name.GetLength() > 0)
		m_ActivateT0_B.SetWindowText((LPCTSTR)T0_Name);
	if (A_Name.GetLength() > 0)
		m_ActivateA_B.SetWindowText((LPCTSTR)A_Name);
	if (B_Name.GetLength() > 0)
		m_ActivateB_B.SetWindowText((LPCTSTR)B_Name);
	if (b_AllowArmInternal)
		m_ArmByInternalB.EnableWindow(TRUE);
	else
	{
		m_ArmByInternal = FALSE;
		m_ArmByInternalB.EnableWindow(FALSE);
	}
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
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P4:
	case BME_SG02P5:
		m_TriggerLevelED.EnableWindow(TRUE);
		m_GateDividerED.EnableWindow(TRUE);
		m_GatePositiveB.EnableWindow(TRUE);
		m_GateNegativeB.EnableWindow(TRUE);
		break;
	default:
		m_TriggerLevel = _T("");
		m_TriggerLevelED.EnableWindow(FALSE);
		m_GateDivider = _T("");
		m_GateDividerED.EnableWindow(FALSE);
		m_GatePositive = FALSE;
		m_GatePositiveB.EnableWindow(FALSE);
		m_GateNegative = FALSE;
		m_GateNegativeB.EnableWindow(FALSE);
		break;
	}
	if (b_AllowIgnore)
	{
		m_IgnoreB.EnableWindow(TRUE);
		m_MemorizeB.EnableWindow(TRUE);
	}
	else
	{
		m_Ignore = FALSE;
		m_Memorize = FALSE;
		m_IgnoreB.EnableWindow(FALSE);
		m_MemorizeB.EnableWindow(FALSE);
	}
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
	switch (m_DG_Product)
	{
	case BME_SG02P4:
	case BME_SG02P5:
		m_PeriodName.SetWindowText("Inhibit");
		break;
	default:
		m_PeriodName.SetWindowText("&Period");
		break;
	}
}
