// G05p2MasterPP.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G05p2MasterPP.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG05p2MasterPP property page

IMPLEMENT_DYNCREATE(CG05p2MasterPP, CPropertyPage)

CG05p2MasterPP::CG05p2MasterPP() : CPropertyPage(CG05p2MasterPP::IDD)
{
	//{{AFX_DATA_INIT(CG05p2MasterPP)
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayT0 = _T("");
	m_ModuloA = _T("");
	m_ModuloB = _T("");
	m_ModuloT0 = _T("");
	m_OffsetA = _T("");
	m_OffsetB = _T("");
	m_OffsetT0 = _T("");
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
	m_ReadTriggers = FALSE;
	m_GateDivider = _T("");
	m_GatePositive = FALSE;
	m_TriggerLevel = _T("");
	m_GateNegative = FALSE;
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	m_AcknowledgeDefault = FALSE;
	m_AcknowledgeNone = FALSE;
	m_InhibitA = FALSE;
	m_InhibitB = FALSE;
	m_InhibitT0 = FALSE;
	m_ForceA = FALSE;
	m_ForceB = FALSE;
	m_ForceT0 = FALSE;
	m_GateAnd = FALSE;
	m_GateOr = FALSE;
	m_GateXor = FALSE;
	m_MsBusA = FALSE;
	m_MsBusB = FALSE;
	m_MsBusT0 = FALSE;
	m_PrimaryA = FALSE;
	m_PrimaryB = FALSE;
	m_PrimaryT0 = FALSE;
	m_SecondaryA = FALSE;
	m_SecondaryB = FALSE;
	m_SecondaryT0 = FALSE;
	m_A_Name = _T("");
	m_B_Name = _T("");
	m_T0_Name = _T("");
	//}}AFX_DATA_INIT
	b_ForceTriggerActive = FALSE;
	b_CrystalOscillator = FALSE;
	m_ClockSource = -1;
	b_FastApply = FALSE;
	b_PageActive = FALSE;
	b_RequestZeroCounter = FALSE;
	b_RequestZeroModulo = FALSE;
	b_Master = FALSE;
	m_DG_Number = -1;
	m_DG_Product = -1;
	T0_Name = _T("");
	A_Name = _T("");
	B_Name = _T("");
	NoEvents = 0;
	GoSignal_T0 = 0x0;
	GoSignal_A = 0x0;
	GoSignal_B = 0x0;
	DoneSignal_T0 = 0x0;
	DoneSignal_A = 0x0;
	DoneSignal_B = 0x0;
	MS_BusSignal = 0x0;
}

CG05p2MasterPP::~CG05p2MasterPP()
{
}

void CG05p2MasterPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG05p2MasterPP)
	DDX_Control(pDX, IDC_SECONDARY_T0, m_SecondaryT0B);
	DDX_Control(pDX, IDC_SECONDARY_B, m_SecondaryBB);
	DDX_Control(pDX, IDC_SECONDARY_A, m_SecondaryAB);
	DDX_Control(pDX, IDC_INHIBIT_T0, m_InhibitT0B);
	DDX_Control(pDX, IDC_INHIBIT_B, m_InhibitBB);
	DDX_Control(pDX, IDC_INHIBIT_A, m_InhibitAB);
	DDX_Control(pDX, IDC_FORCE_T0, m_ForceT0B);
	DDX_Control(pDX, IDC_FORCE_B, m_ForceBB);
	DDX_Control(pDX, IDC_FORCE_A, m_ForceAB);
	DDX_Control(pDX, IDC_DELAY_T0, m_Delay_T0ED);
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_INHIBIT_TRIGGER, m_InhibitTriggerED);
	DDX_Control(pDX, IDC_FORCE_TRIGGER, m_ForceTriggerED);
	DDX_Control(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevelED);
	DDX_Control(pDX, IDC_PRESET_VALUE, m_PresetValueED);
	DDX_Control(pDX, IDC_GATE_DIVIDER, m_GateDividerED);
	DDX_Control(pDX, IDC_MODULO_T0, m_ModuloT0ED);
	DDX_Control(pDX, IDC_MODULO_A, m_ModuloAED);
	DDX_Control(pDX, IDC_MODULO_B, m_ModuloBED);
	DDX_Control(pDX, IDC_OFFSET_T0, m_OffsetT0ED);
	DDX_Control(pDX, IDC_OFFSET_A, m_OffsetAED);
	DDX_Control(pDX, IDC_OFFSET_B, m_OffsetBED);
	DDX_Control(pDX, IDC_RISING, m_RisingB);
	DDX_Control(pDX, IDC_FALLING, m_FallingB);
	DDX_Control(pDX, IDC_EXTERNAL, m_ExternalB);
	DDX_Control(pDX, IDC_DESIGNATOR, m_Designator);
	DDX_Text(pDX, IDC_DELAY_A, m_DelayA);
	DDV_MaxChars(pDX, m_DelayA, 32);
	DDX_Text(pDX, IDC_DELAY_B, m_DelayB);
	DDV_MaxChars(pDX, m_DelayB, 32);
	DDX_Text(pDX, IDC_DELAY_T0, m_DelayT0);
	DDV_MaxChars(pDX, m_DelayT0, 32);
	DDX_Text(pDX, IDC_MODULO_A, m_ModuloA);
	DDV_MaxChars(pDX, m_ModuloA, 16);
	DDX_Text(pDX, IDC_MODULO_B, m_ModuloB);
	DDV_MaxChars(pDX, m_ModuloB, 16);
	DDX_Text(pDX, IDC_MODULO_T0, m_ModuloT0);
	DDV_MaxChars(pDX, m_ModuloT0, 16);
	DDX_Text(pDX, IDC_OFFSET_A, m_OffsetA);
	DDV_MaxChars(pDX, m_OffsetA, 16);
	DDX_Text(pDX, IDC_OFFSET_B, m_OffsetB);
	DDV_MaxChars(pDX, m_OffsetB, 16);
	DDX_Text(pDX, IDC_OFFSET_T0, m_OffsetT0);
	DDV_MaxChars(pDX, m_OffsetT0, 16);
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
	DDX_Check(pDX, IDC_GATE_POSITIVE, m_GatePositive);
	DDX_Text(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevel);
	DDV_MaxChars(pDX, m_TriggerLevel, 16);
	DDX_Check(pDX, IDC_GATE_NEGATIVE, m_GateNegative);
	DDX_Check(pDX, IDC_IGNORE, m_Ignore);
	DDX_Check(pDX, IDC_MEMORIZE, m_Memorize);
	DDX_Check(pDX, IDC_ACKNOWLEDGE_DEFAULT, m_AcknowledgeDefault);
	DDX_Check(pDX, IDC_ACKNOWLEDGE_NONE, m_AcknowledgeNone);
	DDX_Check(pDX, IDC_INHIBIT_A, m_InhibitA);
	DDX_Check(pDX, IDC_INHIBIT_B, m_InhibitB);
	DDX_Check(pDX, IDC_INHIBIT_T0, m_InhibitT0);
	DDX_Check(pDX, IDC_FORCE_A, m_ForceA);
	DDX_Check(pDX, IDC_FORCE_B, m_ForceB);
	DDX_Check(pDX, IDC_FORCE_T0, m_ForceT0);
	DDX_Check(pDX, IDC_GATE_AND, m_GateAnd);
	DDX_Check(pDX, IDC_GATE_OR, m_GateOr);
	DDX_Check(pDX, IDC_GATE_XOR, m_GateXor);
	DDX_Check(pDX, IDC_MS_BUS_A, m_MsBusA);
	DDX_Check(pDX, IDC_MS_BUS_B, m_MsBusB);
	DDX_Check(pDX, IDC_MS_BUS_T0, m_MsBusT0);
	DDX_Check(pDX, IDC_PRIMARY_A, m_PrimaryA);
	DDX_Check(pDX, IDC_PRIMARY_B, m_PrimaryB);
	DDX_Check(pDX, IDC_PRIMARY_T0, m_PrimaryT0);
	DDX_Check(pDX, IDC_SECONDARY_A, m_SecondaryA);
	DDX_Check(pDX, IDC_SECONDARY_B, m_SecondaryB);
	DDX_Check(pDX, IDC_SECONDARY_T0, m_SecondaryT0);
	DDX_Text(pDX, IDC_A_NAME, m_A_Name);
	DDV_MaxChars(pDX, m_A_Name, 32);
	DDX_Text(pDX, IDC_B_NAME, m_B_Name);
	DDV_MaxChars(pDX, m_B_Name, 32);
	DDX_Text(pDX, IDC_T0_NAME, m_T0_Name);
	DDV_MaxChars(pDX, m_T0_Name, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG05p2MasterPP, CPropertyPage)
	ON_MESSAGE(WM_LOAD_COUNTER_REQUEST_G05, OnChangeObjectProps)
	ON_MESSAGE(WM_USER_REQUEST_T0, OnScrollDelayT0)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_PRD, OnScrollInhibitTrigger)
	ON_MESSAGE(WM_USER_REQUEST_FTR, OnScrollForceTrigger)
	ON_MESSAGE(WM_USER_REQUEST_TLV, OnScrollTriggerLevel)
	ON_MESSAGE(WM_USER_REQUEST_GD, OnScrollGateDivider)
	ON_MESSAGE(WM_USER_REQUEST_PVA, OnScrollPresetValue)
	ON_MESSAGE(WM_USER_REQUEST_M_T0, OnScrollModuloT0)
	ON_MESSAGE(WM_USER_REQUEST_M_A, OnScrollModuloA)
	ON_MESSAGE(WM_USER_REQUEST_M_B, OnScrollModuloB)
	ON_MESSAGE(WM_USER_REQUEST_O_T0, OnScrollOffsetT0)
	ON_MESSAGE(WM_USER_REQUEST_O_A, OnScrollOffsetA)
	ON_MESSAGE(WM_USER_REQUEST_O_B, OnScrollOffsetB)
	//{{AFX_MSG_MAP(CG05p2MasterPP)
	ON_BN_CLICKED(IDC_ACKNOWLEDGE_CUSTOM, OnAcknowledgeCustom)
	ON_BN_CLICKED(IDC_ACKNOWLEDGE_DEFAULT, OnAcknowledgeDefault)
	ON_BN_CLICKED(IDC_ACKNOWLEDGE_NONE, OnAcknowledgeNone)
	ON_BN_CLICKED(IDC_INHIBIT_A, OnInhibitA)
	ON_BN_CLICKED(IDC_INHIBIT_B, OnInhibitB)
	ON_BN_CLICKED(IDC_INHIBIT_T0, OnInhibitT0)
	ON_BN_CLICKED(IDC_FORCE_A, OnForceA)
	ON_BN_CLICKED(IDC_FORCE_B, OnForceB)
	ON_BN_CLICKED(IDC_FORCE_T0, OnForceT0)
	ON_BN_CLICKED(IDC_GATE_AND, OnGateAnd)
	ON_BN_CLICKED(IDC_GATE_OR, OnGateOr)
	ON_BN_CLICKED(IDC_GATE_XOR, OnGateXor)
	ON_BN_CLICKED(IDC_MS_BUS_A, OnMsBusA)
	ON_BN_CLICKED(IDC_MS_BUS_B, OnMsBusB)
	ON_BN_CLICKED(IDC_MS_BUS_T0, OnMsBusT0)
	ON_BN_CLICKED(IDC_PRIMARY_A, OnPrimaryA)
	ON_BN_CLICKED(IDC_PRIMARY_B, OnPrimaryB)
	ON_BN_CLICKED(IDC_PRIMARY_T0, OnPrimaryT0)
	ON_BN_CLICKED(IDC_SECONDARY_A, OnSecondaryA)
	ON_BN_CLICKED(IDC_SECONDARY_B, OnSecondaryB)
	ON_BN_CLICKED(IDC_SECONDARY_T0, OnSecondaryT0)
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
	ON_EN_CHANGE(IDC_MODULO_A, OnChangeModuloA)
	ON_EN_KILLFOCUS(IDC_MODULO_A, OnKillfocusModuloA)
	ON_EN_CHANGE(IDC_MODULO_B, OnChangeModuloB)
	ON_EN_KILLFOCUS(IDC_MODULO_B, OnKillfocusModuloB)
	ON_EN_CHANGE(IDC_MODULO_T0, OnChangeModuloT0)
	ON_EN_KILLFOCUS(IDC_MODULO_T0, OnKillfocusModuloT0)
	ON_EN_CHANGE(IDC_OFFSET_A, OnChangeOffsetA)
	ON_EN_KILLFOCUS(IDC_OFFSET_A, OnKillfocusOffsetA)
	ON_EN_CHANGE(IDC_OFFSET_B, OnChangeOffsetB)
	ON_EN_KILLFOCUS(IDC_OFFSET_B, OnKillfocusOffsetB)
	ON_EN_CHANGE(IDC_OFFSET_T0, OnChangeOffsetT0)
	ON_EN_KILLFOCUS(IDC_OFFSET_T0, OnKillfocusOffsetT0)
	ON_BN_CLICKED(IDC_ZERO_MODULO, OnZeroModulo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG05p2MasterPP message handlers


LRESULT CG05p2MasterPP::OnChangeObjectProps(WPARAM, LPARAM)
{
	LoadTriggerCounter(NoEvents);
	return 0;
}

void CG05p2MasterPP::OnAcknowledgeCustom() 
{
	CDoneSelectDlg dlg;
	dlg.m_T0_Name = m_T0_Name;
	dlg.m_A_Name = m_A_Name;
	dlg.m_B_Name = m_B_Name;
	if ((DoneSignal_T0 & MasterPrimary) != 0x0)
		dlg.m_DoneMsbT0 = TRUE;
	if ((DoneSignal_T0 & LocalPrimary) != 0x0)
		dlg.m_DonePrimaryT0 = TRUE;
	if ((DoneSignal_T0 & LocalSecondary) != 0x0)
		dlg.m_DoneSecondaryT0 = TRUE;
	if ((DoneSignal_T0 & LocalForce) != 0x0)
		dlg.m_DoneForceT0 = TRUE;

	if ((DoneSignal_A & MasterPrimary) != 0x0)
		dlg.m_DoneMsbA = TRUE;
	if ((DoneSignal_A & LocalPrimary) != 0x0)
		dlg.m_DonePrimaryA = TRUE;
	if ((DoneSignal_A & LocalSecondary) != 0x0)
		dlg.m_DoneSecondaryA = TRUE;
	if ((DoneSignal_A & LocalForce) != 0x0)
		dlg.m_DoneForceA = TRUE;

	if ((DoneSignal_B & MasterPrimary) != 0x0)
		dlg.m_DoneMsbB = TRUE;
	if ((DoneSignal_B & LocalPrimary) != 0x0)
		dlg.m_DonePrimaryB = TRUE;
	if ((DoneSignal_B & LocalSecondary) != 0x0)
		dlg.m_DoneSecondaryB = TRUE;
	if ((DoneSignal_B & LocalForce) != 0x0)
		dlg.m_DoneForceB = TRUE;
	if (dlg.DoModal() == IDOK)
	{
		unsigned long MemDone_T0 = DoneSignal_T0;
		unsigned long MemDone_A = DoneSignal_A;
		unsigned long MemDone_B = DoneSignal_B;
		DoneSignal_T0 = 0x0;
		DoneSignal_A = 0x0;
		DoneSignal_B = 0x0;
		if (dlg.m_DoneMsbT0)
			DoneSignal_T0 |= MasterPrimary;
		if (dlg.m_DonePrimaryT0)
			DoneSignal_T0 |= LocalPrimary;
		if (dlg.m_DoneSecondaryT0)
			DoneSignal_T0 |= LocalSecondary;
		if (dlg.m_DoneForceT0)
			DoneSignal_T0 |= LocalForce;

		if (dlg.m_DoneMsbA)
			DoneSignal_A |= MasterPrimary;
		if (dlg.m_DonePrimaryA)
			DoneSignal_A |= LocalPrimary;
		if (dlg.m_DoneSecondaryA)
			DoneSignal_A |= LocalSecondary;
		if (dlg.m_DoneForceA)
			DoneSignal_A |= LocalForce;

		if (dlg.m_DoneMsbB)
			DoneSignal_B |= MasterPrimary;
		if (dlg.m_DonePrimaryB)
			DoneSignal_B |= LocalPrimary;
		if (dlg.m_DoneSecondaryB)
			DoneSignal_B |= LocalSecondary;
		if (dlg.m_DoneForceB)
			DoneSignal_B |= LocalForce;
		if ((MemDone_T0 != DoneSignal_T0) || (MemDone_A != DoneSignal_A) || (MemDone_B != DoneSignal_B))
		{
			SetModified();
			*p_DataModified = TRUE;
		}
		m_AcknowledgeNone = FALSE;
		m_AcknowledgeDefault = FALSE;
		if (IsDefaultDoneSignal())
			m_AcknowledgeDefault = TRUE;
		else
		{
			if ((DoneSignal_T0 | DoneSignal_A | DoneSignal_B) == 0x0)
				m_AcknowledgeNone = TRUE;
		}
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnAcknowledgeDefault() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_AcknowledgeDefault)
	{
		m_AcknowledgeNone = FALSE;
		DefaultDoneSignals(&DoneSignal_T0, &DoneSignal_A, &DoneSignal_B);
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnAcknowledgeNone() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_AcknowledgeNone)
	{
		m_AcknowledgeDefault = FALSE;
		DoneSignal_T0 = 0x0;
		DoneSignal_A = 0x0;
		DoneSignal_B = 0x0;
		UpdateData(FALSE);
	}
}

BOOL CG05p2MasterPP::IsDefaultDoneSignal() 
{
	unsigned long TestDoneT0;
	unsigned long TestDoneA;
	unsigned long TestDoneB;
	DefaultDoneSignals(&TestDoneT0, &TestDoneA, &TestDoneB);
	if (DoneSignal_T0 != TestDoneT0)
		return FALSE;
	if (DoneSignal_A != TestDoneA)
		return FALSE;
	if (DoneSignal_B != TestDoneB)
		return FALSE;
	return TRUE;
}

void CG05p2MasterPP::DefaultDoneSignals(unsigned long* p_DoneT0, unsigned long* p_DoneA, unsigned long* p_DoneB) 
{
	*p_DoneT0 = 0x0;
	*p_DoneA = 0x0;
	*p_DoneB = 0x0;
	if (b_Master)
	{
		if (b_ForceTriggerActive)
		{
			if ((GoSignal_T0 & 0x77) != 0x0)
			{
				if (((GoSignal_T0 & LocalForce) == 0x0) && 
						(((GoSignal_T0 & MasterPrimary) == 0x0) || ((MS_BusSignal & LocalForce) == 0x0)))
					*p_DoneT0 |= LocalForce;
			}
			if ((GoSignal_A & 0x77) != 0x0)
			{
				if (((GoSignal_A & LocalForce) == 0x0) &&
						(((GoSignal_A & MasterPrimary) == 0x0) || ((MS_BusSignal & LocalForce) == 0x0)))
					*p_DoneA |= LocalForce;
			}
			if ((GoSignal_B & 0x77) != 0x0)
			{
				if (((GoSignal_B & LocalForce) == 0x0) &&
						(((GoSignal_B & MasterPrimary) == 0x0) || ((MS_BusSignal & LocalForce) == 0x0)))
					*p_DoneB |= LocalForce;
			}
		}
		if ((!m_Internal) || (m_GatePositive) || (m_GateNegative))
		{
			if ((GoSignal_T0 & 0x77) != 0x0)
			{
				if (((GoSignal_T0 & (LocalSecondary | LocalPrimary)) == 0x0) && 
						(((GoSignal_T0 & MasterPrimary) == 0x0) || 
												((MS_BusSignal & (LocalSecondary | LocalPrimary)) == 0x0)))
					*p_DoneT0 |= LocalSecondary;
			}
			if ((GoSignal_A & 0x77) != 0x0)
			{
				if (((GoSignal_A & (LocalSecondary | LocalPrimary)) == 0x0) &&
						(((GoSignal_A & MasterPrimary) == 0x0) || 
												((MS_BusSignal & (LocalSecondary | LocalPrimary)) == 0x0)))
					*p_DoneA |= LocalSecondary;
			}
			if ((GoSignal_B & 0x77) != 0x0)
			{
				if (((GoSignal_B & (LocalSecondary | LocalPrimary)) == 0x0) &&
						(((GoSignal_B & MasterPrimary) == 0x0) || 
												((MS_BusSignal & (LocalSecondary | LocalPrimary)) == 0x0)))
					*p_DoneB |= LocalSecondary;
			}
		}
	}
	else
	{
		if (((GoSignal_T0 & 0x77) != 0x0) && ((GoSignal_T0 & MasterPrimary) == 0x0))
			*p_DoneT0 |= MasterPrimary;
		if (((GoSignal_A & 0x77) != 0x0) && ((GoSignal_A & MasterPrimary) == 0x0))
			*p_DoneA |= MasterPrimary;
		if (((GoSignal_B & 0x77) != 0x0) && ((GoSignal_B & MasterPrimary) == 0x0))
			*p_DoneB |= MasterPrimary;
	}
	
}

void CG05p2MasterPP::UpdateGoSignals() 
{
	if (m_PrimaryT0)
		GoSignal_T0 |= LocalPrimary;
	else
		GoSignal_T0 &= ~LocalPrimary;
	if (m_SecondaryT0)
		GoSignal_T0 |= LocalSecondary;
	else
		GoSignal_T0 &= ~LocalSecondary;
	if (m_ForceT0)
		GoSignal_T0 |= LocalForce;
	else
		GoSignal_T0 &= ~LocalForce;
	if (m_MsBusT0)
		GoSignal_T0 |= MasterPrimary;
	else
		GoSignal_T0 &= ~MasterPrimary;
	if (m_InhibitT0)
		GoSignal_T0 |= InhibitLocal;
	else
		GoSignal_T0 &= ~InhibitLocal;

	if (m_PrimaryA)
		GoSignal_A |= LocalPrimary;
	else
		GoSignal_A &= ~LocalPrimary;
	if (m_SecondaryA)
		GoSignal_A |= LocalSecondary;
	else
		GoSignal_A &= ~LocalSecondary;
	if (m_ForceA)
		GoSignal_A |= LocalForce;
	else
		GoSignal_A &= ~LocalForce;
	if (m_MsBusA)
		GoSignal_A |= MasterPrimary;
	else
		GoSignal_A &= ~MasterPrimary;
	if (m_InhibitA)
		GoSignal_A |= InhibitLocal;
	else
		GoSignal_A &= ~InhibitLocal;

	if (m_PrimaryB)
		GoSignal_B |= LocalPrimary;
	else
		GoSignal_B &= ~LocalPrimary;
	if (m_SecondaryB)
		GoSignal_B |= LocalSecondary;
	else
		GoSignal_B &= ~LocalSecondary;
	if (m_ForceB)
		GoSignal_B |= LocalForce;
	else
		GoSignal_B &= ~LocalForce;
	if (m_MsBusB)
		GoSignal_B |= MasterPrimary;
	else
		GoSignal_B &= ~MasterPrimary;
	if (m_InhibitB)
		GoSignal_B |= InhibitLocal;
	else
		GoSignal_B &= ~InhibitLocal;
	if (m_AcknowledgeDefault)
		DefaultDoneSignals(&DoneSignal_T0, &DoneSignal_A, &DoneSignal_B);
	if (m_AcknowledgeNone)
	{
		DoneSignal_T0 = 0x0;
		DoneSignal_A = 0x0;
		DoneSignal_B = 0x0;
	}
}

void CG05p2MasterPP::OnPrimaryT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
}

void CG05p2MasterPP::OnPrimaryA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnPrimaryB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnSecondaryT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
}

void CG05p2MasterPP::OnSecondaryA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnSecondaryB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnForceT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
}

void CG05p2MasterPP::OnForceA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnForceB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnMsBusT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
}

void CG05p2MasterPP::OnMsBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnMsBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	if (!b_Master)
		CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p2MasterPP::OnInhibitT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p2MasterPP::OnInhibitA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p2MasterPP::OnInhibitB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p2MasterPP::CheckGateChannels()
{
	if ((GoSignal_A & 0x77) == 0x0)
		m_MsBusA = TRUE;
	if ((GoSignal_B & 0x77) == 0x0)
		m_MsBusB = TRUE;
	UpdateGoSignals();
}

void CG05p2MasterPP::OnGateXor() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateXor)
	{
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_GateOr || m_GateAnd))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnGateOr() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateOr)
	{
		m_GateXor = FALSE;
		m_GateAnd = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_GateXor || m_GateAnd))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnGateAnd() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateAnd)
	{
		m_GateOr = FALSE;
		m_GateXor = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_GateOr || m_GateXor))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnGateAb() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateAB)
	{
		if (!(m_GateXor || m_GateOr || m_GateAnd))
			m_GateXor = TRUE;
		CheckGateChannels();
	}
	else
	{
		m_GateXor = FALSE;
		m_GateOr = FALSE;
		m_GateAnd = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollDelayA(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusDelayA() 
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

void CG05p2MasterPP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollDelayB(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusDelayB() 
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

void CG05p2MasterPP::OnChangeDelayT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollDelayT0(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusDelayT0() 
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

void CG05p2MasterPP::OnChangeModuloA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollModuloA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloAED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloAED.GetSel(nStartChar, nEndChar);
			m_ModuloA = lr.ScrollInteger(m_ModuloA, nEndChar, 
								m_ModuloAED.PresentCharacter, m_ModuloAED.PresentCount);
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

void CG05p2MasterPP::OnKillfocusModuloA() 
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

void CG05p2MasterPP::OnChangeModuloT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollModuloT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloT0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloT0ED.GetSel(nStartChar, nEndChar);
			m_ModuloT0 = lr.ScrollInteger(m_ModuloT0, nEndChar, 
								m_ModuloT0ED.PresentCharacter, m_ModuloT0ED.PresentCount);
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

void CG05p2MasterPP::OnKillfocusModuloT0() 
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

void CG05p2MasterPP::OnChangeModuloB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollModuloB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloBED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloBED.GetSel(nStartChar, nEndChar);
			m_ModuloB = lr.ScrollInteger(m_ModuloB, nEndChar, 
								m_ModuloBED.PresentCharacter, m_ModuloBED.PresentCount);
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

void CG05p2MasterPP::OnKillfocusModuloB() 
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

void CG05p2MasterPP::OnChangeOffsetA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollOffsetA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetAED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetAED.GetSel(nStartChar, nEndChar);
			m_OffsetA = lr.ScrollInteger(m_OffsetA, nEndChar, 
								m_OffsetAED.PresentCharacter, m_OffsetAED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetAED.SetSel(nEndChar, nEndChar);
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

void CG05p2MasterPP::OnKillfocusOffsetA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetA) == 1)
		{
			if (lr.Numeric(m_OffsetA))
			{
				unsigned long offset = RoundInt(atof(m_OffsetA));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetA.Format(" %d", offset);
			}
			else
				m_OffsetA = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p2MasterPP::OnChangeOffsetT0() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollOffsetT0(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetT0ED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetT0ED.GetSel(nStartChar, nEndChar);
			m_OffsetT0 = lr.ScrollInteger(m_OffsetT0, nEndChar, 
								m_OffsetT0ED.PresentCharacter, m_OffsetT0ED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetT0ED.SetSel(nEndChar, nEndChar);
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

void CG05p2MasterPP::OnKillfocusOffsetT0() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetT0))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetT0) == 1)
		{
			if (lr.Numeric(m_OffsetT0))
			{
				unsigned long offset = RoundInt(atof(m_OffsetT0));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetT0.Format(" %d", offset);
			}
			else
				m_OffsetT0 = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetT0);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p2MasterPP::OnChangeOffsetB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollOffsetB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetBED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetBED.GetSel(nStartChar, nEndChar);
			m_OffsetB = lr.ScrollInteger(m_OffsetB, nEndChar, 
								m_OffsetBED.PresentCharacter, m_OffsetBED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetBED.SetSel(nEndChar, nEndChar);
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

void CG05p2MasterPP::OnKillfocusOffsetB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetB) == 1)
		{
			if (lr.Numeric(m_OffsetB))
			{
				unsigned long offset = RoundInt(atof(m_OffsetB));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetB.Format(" %d", offset);
			}
			else
				m_OffsetB = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p2MasterPP::OnZeroModulo() 
{
	b_RequestZeroModulo = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

void CG05p2MasterPP::OnReadTriggers() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p2MasterPP::OnStopOnPreset() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_StopOnPreset)
		m_PresetValue = _T("");
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnChangePresetValue() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollPresetValue(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusPresetValue() 
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

void CG05p2MasterPP::OnExternal() 
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
	CheckHardwareControls();
	UpdateData(FALSE);
}


void CG05p2MasterPP::OnInternal() 
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
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnFalling() 
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

void CG05p2MasterPP::OnRising() 
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

void CG05p2MasterPP::OnIgnore() 
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
	else
	{
		if (m_GatePositive || m_GateNegative)
			m_Memorize = TRUE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnMemorize() 
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
	else
	{
		if (m_GatePositive || m_GateNegative)
			m_Ignore = TRUE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnGatePositive() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GatePositive)
	{
		m_GateNegative = FALSE;
		if ((!m_Ignore) && (!m_Memorize))
			m_Ignore = TRUE;
	}
	if ((!m_GatePositive) && (!m_GateNegative))
	{
		m_GateDivider = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnGateNegative() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateNegative)
	{
		m_GatePositive = FALSE;
		if ((!m_Ignore) && (!m_Memorize))
			m_Ignore = TRUE;
	}
	if ((!m_GatePositive) && (!m_GateNegative))
	{
		m_GateDivider = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p2MasterPP::OnChangeGateDivider() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollGateDivider(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusGateDivider() 
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

void CG05p2MasterPP::OnChangeInhibitTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollInhibitTrigger(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusInhibitTrigger() 
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

void CG05p2MasterPP::OnChangeForceTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollForceTrigger(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusForceTrigger() 
{
	CListRout lr;
	lr.TrimString(m_ForceTrigger);
	if (m_ForceTrigger.GetLength() > 0)
	{
		double t1 = p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
		if (t1 > 0.0)
			b_ForceTriggerActive = TRUE;
		else
			b_ForceTriggerActive = FALSE;
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
	}
	else
		b_ForceTriggerActive = FALSE;
	DefaultDoneSignals(&DoneSignal_T0, &DoneSignal_A, &DoneSignal_B);
	UpdateData(FALSE);
	b_FastApply = FALSE;
}

void CG05p2MasterPP::OnChangeTriggerLevel() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p2MasterPP::OnScrollTriggerLevel(WPARAM, LPARAM)
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

void CG05p2MasterPP::OnKillfocusTriggerLevel() 
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

void CG05p2MasterPP::OnResetCounter() 
{
	b_RequestZeroCounter = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

void CG05p2MasterPP::OnChangeTriggerCount() 
{
	UpdateData(FALSE);
}

BOOL CG05p2MasterPP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	SetEvent(DataNotification);
	return CPropertyPage::OnSetActive();
}

BOOL CG05p2MasterPP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG05p2MasterPP::LoadTriggerCounter(unsigned long TriggerCount)
{
	m_TriggerCount.Format(" %u", TriggerCount);
	if (b_PageActive)
		UpdateData(FALSE);
}

void CG05p2MasterPP::DiscretizeValues()
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

	lr.TrimString(m_OffsetT0);
	if (m_OffsetT0.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetT0) == 1)
		{
			if (lr.Numeric(m_OffsetT0))
			{
				unsigned long offset = RoundInt(atof(m_OffsetT0));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetT0.Format(" %d", offset);
			}
			else
				m_OffsetT0 = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetT0);
		}
	}
	lr.TrimString(m_OffsetA);
	if (m_OffsetA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetA) == 1)
		{
			if (lr.Numeric(m_OffsetA))
			{
				unsigned long offset = RoundInt(atof(m_OffsetA));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetA.Format(" %d", offset);
			}
			else
				m_OffsetA = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetA);
		}
	}
	lr.TrimString(m_OffsetB);
	if (m_OffsetB.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetB) == 1)
		{
			if (lr.Numeric(m_OffsetB))
			{
				unsigned long offset = RoundInt(atof(m_OffsetB));
				offset = min(0xFFFF, max(0, offset));
				m_OffsetB.Format(" %d", offset);
			}
			else
				m_OffsetB = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetB);
		}
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

BOOL CG05p2MasterPP::DistributeVariables(DG_Type* p_DG)
{
	double t1;
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
	m_OffsetT0ED.MessageNumber = WM_USER_REQUEST_O_T0;
	m_OffsetT0ED.p_ParentWindow = this;
	m_OffsetAED.MessageNumber = WM_USER_REQUEST_O_A;
	m_OffsetAED.p_ParentWindow = this;
	m_OffsetBED.MessageNumber = WM_USER_REQUEST_O_B;
	m_OffsetBED.p_ParentWindow = this;
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
	b_Master = p_DG->Master;
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
	m_ClockSource = p_DG->Control.DT.ClockSource;
	switch (m_ClockSource)
	{
		case TriggerInput:
		case TriggerAndOscillator:
			b_CrystalOscillator = FALSE;
			break;
		default:
			break;
	}

	m_GateAB = p_DG->Control.Gate_AB;
	m_GateXor = FALSE;
	m_GateOr = FALSE;
	m_GateAnd = FALSE;
	if (m_GateAB)
	{
		if ((p_DG->Control.GateFunction & 0x3000) == GateXOR)
			m_GateXor = TRUE;
		else
		{
			if ((p_DG->Control.GateFunction & 0x3000) == GateOR)
				m_GateOr = TRUE;
			else
			{
				if ((p_DG->Control.GateFunction & 0x3000) == GateAND)
					m_GateAnd = TRUE;
				else
					m_GateXor = TRUE;
			}
		}
	}

	MS_BusSignal = 	p_DG->Control.DT.MS_Bus;
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
	m_ForceTrigger =  _T("");
	b_ForceTriggerActive = FALSE;
	switch (m_DG_Product)
	{
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		if (p_DG->Control.DT.ForceTrigger >= 0.0)
		{
			t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.ForceTrigger, m_DG_Number);
			m_ForceTrigger.Format(" %8.6f",t1);
			m_ForceTrigger = lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
			b_ForceTriggerActive = TRUE;
		}
		break;
	default:
		break;
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
	m_MsBusT0 = FALSE;
	m_PrimaryT0 = FALSE;
	m_SecondaryT0 = FALSE;
	m_ForceT0 = FALSE;
	m_InhibitT0 = FALSE;
	m_DelayT0 = _T("");
	m_ModuloT0 = _T("");
	m_OffsetT0 = _T("");
	GoSignal_T0 = p_DG->Control.T0.GoSignal;
	DoneSignal_T0 = p_DG->Control.T0.DoneSignal;
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
				m_MsBusT0 = TRUE;
			if ((p_DG->Control.T0.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryT0 = TRUE;
			if ((p_DG->Control.T0.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryT0 = TRUE;
			if ((p_DG->Control.T0.GoSignal & LocalForce) != 0x0)
				m_ForceT0 = TRUE;
			if ((p_DG->Control.T0.GoSignal & InhibitLocal) != 0x0)
				m_InhibitT0 = TRUE;
		}
		if (b_ChannelActive)
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
			if (p_DG->VarLoc.T0.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.T0.OutputOffset < MaxParameters)
					m_OffsetT0.Format(" X%d", (p_DG->VarLoc.T0.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.T0.OutputOffset == -1)
				{
					if (p_DG->Control.T0.OutputOffset > 0)
						m_OffsetT0.Format(" %d", p_DG->Control.T0.OutputOffset);
				}
				else
					m_OffsetT0 = lr.ReadMemo(p_DG->VarEqu.T0.OutputOffset);
			}
		}
	}

	b_ChannelActive = FALSE;
	m_MsBusA = FALSE;
	m_PrimaryA = FALSE;
	m_SecondaryA = FALSE;
	m_ForceA = FALSE;
	m_InhibitA = FALSE;
	m_DelayA = _T("");
	m_ModuloA = _T("");
	m_OffsetA = _T("");
	GoSignal_A = p_DG->Control.A.GoSignal;
	DoneSignal_A = p_DG->Control.A.DoneSignal;
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
				m_MsBusA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalForce) != 0x0)
				m_ForceA = TRUE;
			if ((p_DG->Control.A.GoSignal & InhibitLocal) != 0x0)
				m_InhibitA = TRUE;
		}
		if (b_ChannelActive)
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
			if (p_DG->VarLoc.A.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.A.OutputOffset < MaxParameters)
					m_OffsetA.Format(" X%d", (p_DG->VarLoc.A.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.A.OutputOffset == -1)
				{
					if (p_DG->Control.A.OutputOffset > 0)
						m_OffsetA.Format(" %d", p_DG->Control.A.OutputOffset);
				}
				else
					m_OffsetA = lr.ReadMemo(p_DG->VarEqu.A.OutputOffset);
			}
		}
	}

	b_ChannelActive = FALSE;
	m_MsBusB = FALSE;
	m_PrimaryB = FALSE;
	m_SecondaryB = FALSE;
	m_ForceB = FALSE;
	m_InhibitB = FALSE;
	m_DelayB = _T("");
	m_ModuloB = _T("");
	m_OffsetB = _T("");
	GoSignal_B = p_DG->Control.B.GoSignal;
	DoneSignal_B = p_DG->Control.B.DoneSignal;
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
				m_MsBusB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalForce) != 0x0)
				m_ForceB = TRUE;
			if ((p_DG->Control.B.GoSignal & InhibitLocal) != 0x0)
				m_InhibitB = TRUE;
		}
		if (b_ChannelActive)
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
			if (p_DG->VarLoc.B.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.B.OutputOffset < MaxParameters)
					m_OffsetB.Format(" X%d", (p_DG->VarLoc.B.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.B.OutputOffset == -1)
				{
					if (p_DG->Control.B.OutputOffset > 0)
						m_OffsetB.Format(" %d", p_DG->Control.B.OutputOffset);
				}
				else
					m_OffsetB = lr.ReadMemo(p_DG->VarEqu.B.OutputOffset);
			}
		}
	}
	m_AcknowledgeNone = FALSE;
	m_AcknowledgeDefault = FALSE;
	if (IsDefaultDoneSignal())
		m_AcknowledgeDefault = TRUE;
	else
	{
		if ((DoneSignal_T0 | DoneSignal_A | DoneSignal_B) == 0x0)
			m_AcknowledgeNone = TRUE;
	}
	DiscretizeValues();
	return TRUE;
}

BOOL CG05p2MasterPP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();
	CListRout lr;
	CString jstr;
	p_DG->ReadTriggers = m_ReadTriggers;

	p_DG->Control.Gate_AB = m_GateAB;
	p_DG->Control.GateFunction = 0x0;
	if (m_GateAB)
	{
		if (m_GateXor)
			p_DG->Control.GateFunction |= GateXOR;
		if (m_GateOr)
			p_DG->Control.GateFunction |= GateOR;
		if (m_GateAnd)
			p_DG->Control.GateFunction |= GateAND;
	}

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
	p_DG->Control.DT.SynchronizeGate = FALSE;
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
		if (m_Internal)
			p_DG->Control.DT.SynchronizeGate = TRUE;
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
	p_DG->Control.T0.OutputOffset = 0;
	p_DG->VarLoc.T0.FireFirst = -1;
	p_DG->VarLoc.T0.SetBack = -1;
	p_DG->VarLoc.T0.OutputModulo = -1;
	p_DG->VarLoc.T0.OutputOffset = -1;
	p_DG->VarEqu.T0.FireFirst[0] = 0;
	p_DG->VarEqu.T0.SetBack[0] = 0;
	p_DG->VarEqu.T0.OutputModulo[0] = 0;
	p_DG->VarEqu.T0.OutputOffset[0] = 0;
	if ((GoSignal_T0 & 0x77) != 0x0)
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
			p_DG->Control.T0.GoSignal |= (GoSignal_T0 & 0x277);
			p_DG->Control.T0.GoSignal &= (GoSignal_T0 | ~0x277);
			p_DG->Control.T0.DoneSignal = DoneSignal_T0;
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
			jstr = m_OffsetT0;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.T0.OutputOffset = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.T0.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.T0.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.T0.OutputOffset, (LPCTSTR)m_OffsetT0, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.T0.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.T0.OutputOffset, (LPCTSTR)m_OffsetT0, 64);
				}
			}
		}
	}

	p_DG->Control.A.GoSignal &= 0x188;
	p_DG->Control.A.DoneSignal = 0x0;
	p_DG->Control.A.FireFirst = -1.0;
	p_DG->Control.A.SetBack = -1.0;
	p_DG->Control.A.OutputModulo = 1;
	p_DG->Control.A.OutputOffset = 0;
	p_DG->VarLoc.A.FireFirst = -1;
	p_DG->VarLoc.A.SetBack = -1;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarLoc.A.OutputOffset = -1;
	p_DG->VarEqu.A.FireFirst[0] = 0;
	p_DG->VarEqu.A.SetBack[0] = 0;
	p_DG->VarEqu.A.OutputModulo[0] = 0;
	p_DG->VarEqu.A.OutputOffset[0] = 0;
	if ((GoSignal_A & 0x77) != 0x0)
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
			p_DG->Control.A.GoSignal |= (GoSignal_A & 0x277);
			p_DG->Control.A.GoSignal &= (GoSignal_A | ~0x277);
			p_DG->Control.A.DoneSignal = DoneSignal_A;
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
			jstr = m_OffsetA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.A.OutputOffset = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.A.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.A.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.A.OutputOffset, (LPCTSTR)m_OffsetA, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.A.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.A.OutputOffset, (LPCTSTR)m_OffsetA, 64);
				}
			}
		}
	}

	p_DG->Control.B.GoSignal &= 0x188;
	p_DG->Control.B.DoneSignal = 0x0;
	p_DG->Control.B.FireFirst = -1.0;
	p_DG->Control.B.SetBack = -1.0;
	p_DG->Control.B.OutputModulo = 1;
	p_DG->Control.B.OutputOffset = 0;
	p_DG->VarLoc.B.FireFirst = -1;
	p_DG->VarLoc.B.SetBack = -1;
	p_DG->VarLoc.B.OutputModulo = -1;
	p_DG->VarLoc.B.OutputOffset = -1;
	p_DG->VarEqu.B.FireFirst[0] = 0;
	p_DG->VarEqu.B.SetBack[0] = 0;
	p_DG->VarEqu.B.OutputModulo[0] = 0;
	p_DG->VarEqu.B.OutputOffset[0] = 0;
	if ((GoSignal_B & 0x77) != 0x0)
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
			p_DG->Control.B.GoSignal |= (GoSignal_B & 0x277);
			p_DG->Control.B.GoSignal &= (GoSignal_B | ~0x277);
			p_DG->Control.B.DoneSignal = DoneSignal_B;
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
			jstr = m_OffsetB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.B.OutputOffset = min(0xFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.B.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.B.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.B.OutputOffset, (LPCTSTR)m_OffsetB, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.B.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.B.OutputOffset, (LPCTSTR)m_OffsetB, 64);
				}
			}
		}
	}
	if (((p_DG->Control.A.GoSignal & 0x77) == 0x0) || ((p_DG->Control.B.GoSignal & 0x77) == 0x0))
	{
		p_DG->Control.Gate_AB = FALSE;
		p_DG->Control.GateFunction = 0x0;
	}
	return TRUE;
}

void CG05p2MasterPP::CheckHardwareControls() 
{
	if (m_Internal && (!(m_GatePositive || m_GateNegative)))
	{
		m_SecondaryT0 = FALSE;
		m_SecondaryT0B.EnableWindow(FALSE);
		m_SecondaryA = FALSE;
		m_SecondaryAB.EnableWindow(FALSE);
		m_SecondaryB = FALSE;
		m_SecondaryBB.EnableWindow(FALSE);
		UpdateGoSignals();
		if (((GoSignal_A & 0x77) == 0x0) || ((GoSignal_B & 0x77) == 0x0))
		{
			m_GateAB = FALSE;
			m_GateXor = FALSE;
			m_GateOr = FALSE;
			m_GateAnd = FALSE;
			UpdateData(FALSE);
		}
	}
	else
	{
		m_SecondaryT0B.EnableWindow(TRUE);
		m_SecondaryAB.EnableWindow(TRUE);
		m_SecondaryBB.EnableWindow(TRUE);
	}
	if (!b_Master)
		UpdateGoSignals();
	BOOL b_InhibitT0 = FALSE;
	BOOL b_InhibitA = FALSE;
	BOOL b_InhibitB = FALSE;
	switch (m_DG_Product)
	{
	case BME_SG05P2:
	case BME_SG05P3:
		if (m_ClockSource == TriggerAndOscillator)
		{
			if ((b_Master) || ((GoSignal_T0 & 0x07) != 0x0))
				b_InhibitT0 = TRUE;
			if ((b_Master) || ((GoSignal_A & 0x07) != 0x0))
				b_InhibitA = TRUE;
			if ((b_Master) || ((GoSignal_B & 0x07) != 0x0))
				b_InhibitB = TRUE;
		}
		break;
	default:
		break;
	}
	if (b_InhibitT0)
		m_InhibitT0B.EnableWindow(TRUE);
	else
	{
		m_InhibitT0 = FALSE;
		m_InhibitT0B.EnableWindow(FALSE);
	}
	if (b_InhibitA)
		m_InhibitAB.EnableWindow(TRUE);
	else
	{
		m_InhibitA = FALSE;
		m_InhibitAB.EnableWindow(FALSE);
	}
	if (b_InhibitB)
		m_InhibitBB.EnableWindow(TRUE);
	else
	{
		m_InhibitB = FALSE;
		m_InhibitBB.EnableWindow(FALSE);
	}
}

void CG05p2MasterPP::OnShowWindow(BOOL bShow, UINT nStatus) 
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
	CheckHardwareControls();
	switch (m_DG_Product)
	{
	case BME_SG05P1:
	case BME_SG05P2:
	case BME_SG05P3:
		m_ForceT0B.EnableWindow(TRUE);
		m_ForceAB.EnableWindow(TRUE);
		m_ForceBB.EnableWindow(TRUE);
		m_ForceTriggerED.EnableWindow(TRUE);
		break;
	case BME_G05P2:
	case BME_G05P3:
		m_ForceT0 = FALSE;
		m_ForceT0B.EnableWindow(FALSE);
		m_ForceA = FALSE;
		m_ForceAB.EnableWindow(FALSE);
		m_ForceB = FALSE;
		m_ForceBB.EnableWindow(FALSE);
		m_ForceTrigger = _T("");
		m_ForceTriggerED.EnableWindow(FALSE);
		break;
	}	
	switch (m_DG_Product)
	{
	case BME_SG05P1:
		m_Designator.SetWindowText("SG05P1 Delay Parameters");
		break;
	case BME_SG05P2:
		m_Designator.SetWindowText("SG05P2 Delay Parameters");
		break;
	case BME_SG05P3:
		m_Designator.SetWindowText("SG05P3 Delay Parameters");
		break;
	case BME_G05P2:
		m_Designator.SetWindowText("G05P2 Delay Parameters");
		break;
	case BME_G05P3:
		m_Designator.SetWindowText("G05P3 Delay Parameters");
		break;
	}
	UpdateData(FALSE);
}
