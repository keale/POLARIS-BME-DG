// DefineDelayGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "DefineDelayGeneratorDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"
#include "..\Spectra_BME\InsertLineDlg.h"
#include "..\Spectra_BME\ReplaceLineDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefineDelayGeneratorDlg dialog


CDefineDelayGeneratorDlg::CDefineDelayGeneratorDlg(CG0xData* p_GDat, CWnd* pParent /*=NULL*/)
	: CDialog(CDefineDelayGeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefineDelayGeneratorDlg)
	m_DgAddress = _T("");
	m_DgBus = _T("");
	m_EthernetAddress = _T("");
	m_DgMaster = FALSE;
	m_DgType = _T("");
	m_DgPrescaler = _T("");
	m_A_Name = _T("");
	m_A_Negative = FALSE;
	m_A_Positive = FALSE;
	m_A_Terminate = FALSE;
	m_B_Name = _T("");
	m_B_Negative = FALSE;
	m_B_Positive = FALSE;
	m_B_Terminate = FALSE;
	m_C_Name = _T("");
	m_C_Negative = FALSE;
	m_C_Positive = FALSE;
	m_C_Terminate = FALSE;
	m_D_Name = _T("");
	m_D_Negative = FALSE;
	m_D_Positive = FALSE;
	m_D_Terminate = FALSE;
	m_E_Name = _T("");
	m_E_Negative = FALSE;
	m_E_Positive = FALSE;
	m_E_Terminate = FALSE;
	m_F_Name = _T("");
	m_F_Negative = FALSE;
	m_F_Positive = FALSE;
	m_F_Terminate = FALSE;
	m_DgName = _T("");
	m_T0_Name = _T("");
	m_T0_Negative = FALSE;
	m_T0_Positive = FALSE;
	m_T0_Terminate = FALSE;
	m_TriggerTerminate = FALSE;
	m_GateTerminate = FALSE;
	m_UseF = FALSE;
	m_GateMsP = FALSE;
	m_GateMsN = FALSE;
	m_TriggerInput = FALSE;
	m_CrystalOscillator = FALSE;
	m_A_HighDrive = FALSE;
	m_B_HighDrive = FALSE;
	m_T0_HighDrive = FALSE;
	m_TtlLevel = FALSE;
	m_NimLevel = FALSE;
	m_EclLevel = FALSE;
	m_FreeRunning = FALSE;
	m_TriggerDivider = _T("");
	m_TriggerMultiplier = _T("");
	m_PulseWidth = _T("");
	m_ForceGo = FALSE;
	m_PrimaryGo = FALSE;
	m_SecondaryGo = FALSE;
	m_StepBackOnBus = FALSE;
	m_StartOnBus = FALSE;
	m_InhibitOnBus = FALSE;
	m_LoadDataOnBus = FALSE;
	m_MsBusClock = FALSE;
	m_T0_Clock = FALSE;
	m_T0_DelayClock = FALSE;
	m_A_DelayClock = FALSE;
	m_B_DelayClock = FALSE;
	m_Resynch = FALSE;
	m_E_Disconnect = FALSE;
	m_F_Disconnect = FALSE;
	m_E_MsBus = FALSE;
	m_F_MsBus = FALSE;
	m_E_InputP = FALSE;
	m_E_InputN = FALSE;
	m_F_InputP = FALSE;
	m_F_InputN = FALSE;
	//}}AFX_DATA_INIT
	p_G0xData = p_GDat;
	b_onScreen=FALSE;
	CRect crp;
	crp.SetRectEmpty();
	WindowFrame.rcNormalPosition = crp;
}


void CDefineDelayGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefineDelayGeneratorDlg)
	DDX_Control(pDX, IDC_T0_CLOCK, m_T0_ClockB);
	DDX_Control(pDX, IDC_T0_DELAY_CLOCK, m_T0_DelayClockB);
	DDX_Control(pDX, IDC_A_DELAY_CLOCK, m_A_DelayClockB);
	DDX_Control(pDX, IDC_B_DELAY_CLOCK, m_B_DelayClockB);
	DDX_Control(pDX, IDC_RESYNCH, m_ResynchB);
	DDX_Control(pDX, IDC_MS_BUS_CLOCK, m_MsBusClockB);
	DDX_Control(pDX, IDC_SECONDARY_GO, m_SecondaryGoB);
	DDX_Control(pDX, IDC_PRIMARY_GO, m_PrimaryGoB);
	DDX_Control(pDX, IDC_FORCE_GO, m_ForceGoB);
	DDX_Control(pDX, IDC_STEP_BACK_ON_BUS, m_StepBackOnBusB);
	DDX_Control(pDX, IDC_START_ON_BUS, m_StartOnBusB);
	DDX_Control(pDX, IDC_INHIBIT_ON_BUS, m_InhibitOnBusB);
	DDX_Control(pDX, IDC_LOAD_DATA_ON_BUS, m_LoadDataOnBusB);
	DDX_Control(pDX, IDC_PULSE_WIDTH, m_PulseWidthED);
	DDX_Control(pDX, IDC_ADDRESS_LINE, m_AddressLine);
	DDX_Control(pDX, IDC_TRIGGER_DIVIDER, m_TriggerDividerED);
	DDX_Control(pDX, IDC_TRIGGER_MULTIPLIER, m_TriggerMultiplierED);
	DDX_Control(pDX, IDC_FREE_RUNNING, m_FreeRunningB);
	DDX_Control(pDX, IDC_ECL_LEVEL, m_EclLevelB);
	DDX_Control(pDX, IDC_NIM_LEVEL, m_NimLevelB);
	DDX_Control(pDX, IDC_TTL_LEVEL, m_TtlLevelB);
	DDX_Control(pDX, IDC_T0_HIGH_DRIVE, m_T0_HighDriveB);
	DDX_Control(pDX, IDC_B_HIGH_DRIVE, m_B_HighDriveB);
	DDX_Control(pDX, IDC_A_HIGH_DRIVE, m_A_HighDriveB);
	DDX_Control(pDX, IDC_CRYSTAL_OSCILLATOR, m_CrystalOscillatorB);
	DDX_Control(pDX, IDC_TRIGGER_INPUT, m_TriggerInputB);
	DDX_Control(pDX, IDC_DG_PRESCALER, m_DgPrescalerED);
	DDX_Control(pDX, IDC_TRIGGER_TERMINATE, m_TriggerTerminateB);
	DDX_Control(pDX, IDC_GATE_TERMINATE, m_GateTerminateB);
	DDX_Control(pDX, IDC_USE_F, m_UseFB);
	DDX_Control(pDX, IDC_GATE_MS_P, m_GateMsPB);
	DDX_Control(pDX, IDC_GATE_MS_N, m_GateMsNB);
	DDX_Control(pDX, IDC_T0_NAME, m_T0_NameED);
	DDX_Control(pDX, IDC_T0_POSITIVE, m_T0_PositiveB);
	DDX_Control(pDX, IDC_T0_TERMINATE, m_T0_TerminateB);
	DDX_Control(pDX, IDC_T0_NEGATIVE, m_T0_NegativeB);
	DDX_Control(pDX, IDC_A_TERMINATE, m_A_TerminateB);
	DDX_Control(pDX, IDC_A_POSITIVE, m_A_PositiveB);
	DDX_Control(pDX, IDC_A_NEGATIVE, m_A_NegativeB);
	DDX_Control(pDX, IDC_B_TERMINATE, m_B_TerminateB);
	DDX_Control(pDX, IDC_B_POSITIVE, m_B_PositiveB);
	DDX_Control(pDX, IDC_B_NEGATIVE, m_B_NegativeB);
	DDX_Control(pDX, IDC_C_NAME, m_C_NameED);
	DDX_Control(pDX, IDC_C_TERMINATE, m_C_TerminateB);
	DDX_Control(pDX, IDC_C_POSITIVE, m_C_PositiveB);
	DDX_Control(pDX, IDC_C_NEGATIVE, m_C_NegativeB);
	DDX_Control(pDX, IDC_D_NAME, m_D_NameED);
	DDX_Control(pDX, IDC_D_TERMINATE, m_D_TerminateB);
	DDX_Control(pDX, IDC_D_POSITIVE, m_D_PositiveB);
	DDX_Control(pDX, IDC_D_NEGATIVE, m_D_NegativeB);
	DDX_Control(pDX, IDC_E_NAME, m_E_NameED);
	DDX_Control(pDX, IDC_E_TERMINATE, m_E_TerminateB);
	DDX_Control(pDX, IDC_E_POSITIVE, m_E_PositiveB);
	DDX_Control(pDX, IDC_E_NEGATIVE, m_E_NegativeB);
	DDX_Control(pDX, IDC_E_DISCONNECT, m_E_DisconnectB);
	DDX_Control(pDX, IDC_E_MS_BUS, m_E_MsBusB);
	DDX_Control(pDX, IDC_E_INPUT_P, m_E_InputPB);
	DDX_Control(pDX, IDC_E_INPUT_N, m_E_InputNB);
	DDX_Control(pDX, IDC_F_NAME, m_F_NameED);
	DDX_Control(pDX, IDC_F_TERMINATE, m_F_TerminateB);
	DDX_Control(pDX, IDC_F_POSITIVE, m_F_PositiveB);
	DDX_Control(pDX, IDC_F_NEGATIVE, m_F_NegativeB);
	DDX_Control(pDX, IDC_F_DISCONNECT, m_F_DisconnectB);
	DDX_Control(pDX, IDC_F_MS_BUS, m_F_MsBusB);
	DDX_Control(pDX, IDC_F_INPUT_P, m_F_InputPB);
	DDX_Control(pDX, IDC_F_INPUT_N, m_F_InputNB);
	DDX_Control(pDX, IDC_DG_TYPE, m_DgTypeCB);
	DDX_Control(pDX, IDC_IP_ADDRESS, m_EthernetAddressED);
	DDX_Control(pDX, IDC_DG_BUS, m_DgBusED);
	DDX_Text(pDX, IDC_DG_ADDRESS, m_DgAddress);
	DDV_MaxChars(pDX, m_DgAddress, 16);
	DDX_Text(pDX, IDC_IP_ADDRESS, m_EthernetAddress);
	DDV_MaxChars(pDX, m_EthernetAddress, 24);
	DDX_Text(pDX, IDC_DG_BUS, m_DgBus);
	DDV_MaxChars(pDX, m_DgBus, 16);
	DDX_Check(pDX, IDC_DG_MASTER, m_DgMaster);
	DDX_CBString(pDX, IDC_DG_TYPE, m_DgType);
	DDV_MaxChars(pDX, m_DgType, 16);
	DDX_Text(pDX, IDC_DG_PRESCALER, m_DgPrescaler);
	DDV_MaxChars(pDX, m_DgPrescaler, 8);
	DDX_Text(pDX, IDC_A_NAME, m_A_Name);
	DDV_MaxChars(pDX, m_A_Name, 16);
	DDX_Check(pDX, IDC_A_NEGATIVE, m_A_Negative);
	DDX_Check(pDX, IDC_A_POSITIVE, m_A_Positive);
	DDX_Check(pDX, IDC_A_TERMINATE, m_A_Terminate);
	DDX_Text(pDX, IDC_B_NAME, m_B_Name);
	DDV_MaxChars(pDX, m_B_Name, 16);
	DDX_Check(pDX, IDC_B_NEGATIVE, m_B_Negative);
	DDX_Check(pDX, IDC_B_POSITIVE, m_B_Positive);
	DDX_Check(pDX, IDC_B_TERMINATE, m_B_Terminate);
	DDX_Text(pDX, IDC_C_NAME, m_C_Name);
	DDV_MaxChars(pDX, m_C_Name, 16);
	DDX_Check(pDX, IDC_C_NEGATIVE, m_C_Negative);
	DDX_Check(pDX, IDC_C_POSITIVE, m_C_Positive);
	DDX_Check(pDX, IDC_C_TERMINATE, m_C_Terminate);
	DDX_Text(pDX, IDC_D_NAME, m_D_Name);
	DDV_MaxChars(pDX, m_D_Name, 16);
	DDX_Check(pDX, IDC_D_NEGATIVE, m_D_Negative);
	DDX_Check(pDX, IDC_D_POSITIVE, m_D_Positive);
	DDX_Check(pDX, IDC_D_TERMINATE, m_D_Terminate);
	DDX_Text(pDX, IDC_E_NAME, m_E_Name);
	DDV_MaxChars(pDX, m_E_Name, 16);
	DDX_Check(pDX, IDC_E_NEGATIVE, m_E_Negative);
	DDX_Check(pDX, IDC_E_POSITIVE, m_E_Positive);
	DDX_Check(pDX, IDC_E_TERMINATE, m_E_Terminate);
	DDX_Text(pDX, IDC_F_NAME, m_F_Name);
	DDV_MaxChars(pDX, m_F_Name, 16);
	DDX_Check(pDX, IDC_F_NEGATIVE, m_F_Negative);
	DDX_Check(pDX, IDC_F_POSITIVE, m_F_Positive);
	DDX_Check(pDX, IDC_F_TERMINATE, m_F_Terminate);
	DDX_Text(pDX, IDC_DG_NAME, m_DgName);
	DDV_MaxChars(pDX, m_DgName, 16);
	DDX_Text(pDX, IDC_T0_NAME, m_T0_Name);
	DDV_MaxChars(pDX, m_T0_Name, 16);
	DDX_Check(pDX, IDC_T0_NEGATIVE, m_T0_Negative);
	DDX_Check(pDX, IDC_T0_POSITIVE, m_T0_Positive);
	DDX_Check(pDX, IDC_T0_TERMINATE, m_T0_Terminate);
	DDX_Check(pDX, IDC_TRIGGER_TERMINATE, m_TriggerTerminate);
	DDX_Check(pDX, IDC_GATE_TERMINATE, m_GateTerminate);
	DDX_Check(pDX, IDC_USE_F, m_UseF);
	DDX_Check(pDX, IDC_GATE_MS_P, m_GateMsP);
	DDX_Check(pDX, IDC_GATE_MS_N, m_GateMsN);
	DDX_Check(pDX, IDC_TRIGGER_INPUT, m_TriggerInput);
	DDX_Check(pDX, IDC_CRYSTAL_OSCILLATOR, m_CrystalOscillator);
	DDX_Check(pDX, IDC_A_HIGH_DRIVE, m_A_HighDrive);
	DDX_Check(pDX, IDC_B_HIGH_DRIVE, m_B_HighDrive);
	DDX_Check(pDX, IDC_T0_HIGH_DRIVE, m_T0_HighDrive);
	DDX_Check(pDX, IDC_TTL_LEVEL, m_TtlLevel);
	DDX_Check(pDX, IDC_NIM_LEVEL, m_NimLevel);
	DDX_Check(pDX, IDC_ECL_LEVEL, m_EclLevel);
	DDX_Check(pDX, IDC_FREE_RUNNING, m_FreeRunning);
	DDX_Text(pDX, IDC_TRIGGER_DIVIDER, m_TriggerDivider);
	DDV_MaxChars(pDX, m_TriggerDivider, 8);
	DDX_Text(pDX, IDC_TRIGGER_MULTIPLIER, m_TriggerMultiplier);
	DDV_MaxChars(pDX, m_TriggerMultiplier, 8);
	DDX_Text(pDX, IDC_PULSE_WIDTH, m_PulseWidth);
	DDV_MaxChars(pDX, m_PulseWidth, 8);
	DDX_Check(pDX, IDC_FORCE_GO, m_ForceGo);
	DDX_Check(pDX, IDC_PRIMARY_GO, m_PrimaryGo);
	DDX_Check(pDX, IDC_SECONDARY_GO, m_SecondaryGo);
	DDX_Check(pDX, IDC_STEP_BACK_ON_BUS, m_StepBackOnBus);
	DDX_Check(pDX, IDC_START_ON_BUS, m_StartOnBus);
	DDX_Check(pDX, IDC_INHIBIT_ON_BUS, m_InhibitOnBus);
	DDX_Check(pDX, IDC_LOAD_DATA_ON_BUS, m_LoadDataOnBus);
	DDX_Check(pDX, IDC_MS_BUS_CLOCK, m_MsBusClock);
	DDX_Check(pDX, IDC_T0_CLOCK, m_T0_Clock);
	DDX_Check(pDX, IDC_T0_DELAY_CLOCK, m_T0_DelayClock);
	DDX_Check(pDX, IDC_A_DELAY_CLOCK, m_A_DelayClock);
	DDX_Check(pDX, IDC_B_DELAY_CLOCK, m_B_DelayClock);
	DDX_Check(pDX, IDC_RESYNCH, m_Resynch);
	DDX_Check(pDX, IDC_E_DISCONNECT, m_E_Disconnect);
	DDX_Check(pDX, IDC_F_DISCONNECT, m_F_Disconnect);
	DDX_Check(pDX, IDC_E_MS_BUS, m_E_MsBus);
	DDX_Check(pDX, IDC_F_MS_BUS, m_F_MsBus);
	DDX_Check(pDX, IDC_E_INPUT_P, m_E_InputP);
	DDX_Check(pDX, IDC_E_INPUT_N, m_E_InputN);
	DDX_Check(pDX, IDC_F_INPUT_P, m_F_InputP);
	DDX_Check(pDX, IDC_F_INPUT_N, m_F_InputN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefineDelayGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CDefineDelayGeneratorDlg)
	ON_WM_MOVE()
	ON_WM_HELPINFO()
	ON_EN_CHANGE(IDC_DG_ADDRESS, OnChangeDgAddress)
	ON_EN_CHANGE(IDC_DG_BUS, OnChangeDgBus)
	ON_EN_CHANGE(IDC_IP_ADDRESS, OnChangeIpAddress)
	ON_EN_KILLFOCUS(IDC_IP_ADDRESS, OnKillfocusIpAddress)
	ON_BN_CLICKED(IDC_DG_MASTER, OnDgMaster)
	ON_CBN_SELENDOK(IDC_DG_TYPE, OnSelendokDgType)
	ON_BN_CLICKED(IDC_INSERT_LINE, OnInsertLine)
	ON_BN_CLICKED(IDC_REPLACE_LINE, OnReplaceLine)
	ON_EN_CHANGE(IDC_DG_PRESCALER, OnChangeDgPrescaler)
	ON_EN_KILLFOCUS(IDC_DG_PRESCALER, OnKillfocusDgPrescaler)
	ON_BN_CLICKED(IDC_A_NEGATIVE, OnANegative)
	ON_BN_CLICKED(IDC_A_POSITIVE, OnAPositive)
	ON_BN_CLICKED(IDC_A_TERMINATE, OnATerminate)
	ON_BN_CLICKED(IDC_B_NEGATIVE, OnBNegative)
	ON_BN_CLICKED(IDC_B_POSITIVE, OnBPositive)
	ON_BN_CLICKED(IDC_B_TERMINATE, OnBTerminate)
	ON_BN_CLICKED(IDC_C_NEGATIVE, OnCNegative)
	ON_BN_CLICKED(IDC_C_POSITIVE, OnCPositive)
	ON_BN_CLICKED(IDC_C_TERMINATE, OnCTerminate)
	ON_BN_CLICKED(IDC_D_NEGATIVE, OnDNegative)
	ON_BN_CLICKED(IDC_D_POSITIVE, OnDPositive)
	ON_BN_CLICKED(IDC_D_TERMINATE, OnDTerminate)
	ON_BN_CLICKED(IDC_E_NEGATIVE, OnENegative)
	ON_BN_CLICKED(IDC_E_POSITIVE, OnEPositive)
	ON_BN_CLICKED(IDC_E_TERMINATE, OnETerminate)
	ON_BN_CLICKED(IDC_F_NEGATIVE, OnFNegative)
	ON_BN_CLICKED(IDC_F_POSITIVE, OnFPositive)
	ON_BN_CLICKED(IDC_F_TERMINATE, OnFTerminate)
	ON_EN_CHANGE(IDC_A_NAME, OnChangeAName)
	ON_EN_CHANGE(IDC_B_NAME, OnChangeBName)
	ON_EN_CHANGE(IDC_C_NAME, OnChangeCName)
	ON_EN_CHANGE(IDC_D_NAME, OnChangeDName)
	ON_EN_CHANGE(IDC_E_NAME, OnChangeEName)
	ON_EN_CHANGE(IDC_F_NAME, OnChangeFName)
	ON_EN_CHANGE(IDC_DG_NAME, OnChangeDgName)
	ON_EN_CHANGE(IDC_T0_NAME, OnChangeT0Name)
	ON_BN_CLICKED(IDC_T0_NEGATIVE, OnT0Negative)
	ON_BN_CLICKED(IDC_T0_POSITIVE, OnT0Positive)
	ON_BN_CLICKED(IDC_T0_TERMINATE, OnT0Terminate)
	ON_BN_CLICKED(IDC_TRIGGER_TERMINATE, OnTriggerTerminate)
	ON_BN_CLICKED(IDC_GATE_TERMINATE, OnGateTerminate)
	ON_BN_CLICKED(IDC_USE_F, OnUseF)
	ON_BN_CLICKED(IDC_GATE_MS_P, OnGateMsP)
	ON_BN_CLICKED(IDC_GATE_MS_N, OnGateMsN)
	ON_EN_KILLFOCUS(IDC_DG_NAME, OnKillfocusDgName)
	ON_EN_KILLFOCUS(IDC_A_NAME, OnKillfocusAName)
	ON_EN_KILLFOCUS(IDC_B_NAME, OnKillfocusBName)
	ON_EN_KILLFOCUS(IDC_C_NAME, OnKillfocusCName)
	ON_EN_KILLFOCUS(IDC_D_NAME, OnKillfocusDName)
	ON_EN_KILLFOCUS(IDC_E_NAME, OnKillfocusEName)
	ON_EN_KILLFOCUS(IDC_F_NAME, OnKillfocusFName)
	ON_EN_KILLFOCUS(IDC_T0_NAME, OnKillfocusT0Name)
	ON_BN_CLICKED(IDC_CRYSTAL_OSCILLATOR, OnCrystalOscillator)
	ON_BN_CLICKED(IDC_TRIGGER_INPUT, OnTriggerInput)
	ON_BN_CLICKED(IDC_A_HIGH_DRIVE, OnAHighDrive)
	ON_BN_CLICKED(IDC_B_HIGH_DRIVE, OnBHighDrive)
	ON_BN_CLICKED(IDC_T0_HIGH_DRIVE, OnT0HighDrive)
	ON_BN_CLICKED(IDC_TTL_LEVEL, OnTtlLevel)
	ON_BN_CLICKED(IDC_NIM_LEVEL, OnNimLevel)
	ON_BN_CLICKED(IDC_ECL_LEVEL, OnEclLevel)
	ON_BN_CLICKED(IDC_FREE_RUNNING, OnFreeRunning)
	ON_EN_CHANGE(IDC_TRIGGER_DIVIDER, OnChangeTriggerDivider)
	ON_EN_KILLFOCUS(IDC_TRIGGER_DIVIDER, OnKillfocusTriggerDivider)
	ON_EN_CHANGE(IDC_TRIGGER_MULTIPLIER, OnChangeTriggerMultiplier)
	ON_EN_KILLFOCUS(IDC_TRIGGER_MULTIPLIER, OnKillfocusTriggerMultiplier)
	ON_EN_CHANGE(IDC_PULSE_WIDTH, OnChangePulseWidth)
	ON_EN_KILLFOCUS(IDC_PULSE_WIDTH, OnKillfocusPulseWidth)
	ON_BN_CLICKED(IDC_FORCE_GO, OnForceGo)
	ON_BN_CLICKED(IDC_PRIMARY_GO, OnPrimaryGo)
	ON_BN_CLICKED(IDC_SECONDARY_GO, OnSecondaryGo)
	ON_BN_CLICKED(IDC_STEP_BACK_ON_BUS, OnStepBackOnBus)
	ON_BN_CLICKED(IDC_START_ON_BUS, OnStartOnBus)
	ON_BN_CLICKED(IDC_INHIBIT_ON_BUS, OnInhibitOnBus)
	ON_BN_CLICKED(IDC_LOAD_DATA_ON_BUS, OnLoadDataOnBus)
	ON_BN_CLICKED(IDC_MS_BUS_CLOCK, OnMsBusClock)
	ON_BN_CLICKED(IDC_T0_CLOCK, OnT0Clock)
	ON_BN_CLICKED(IDC_T0_DELAY_CLOCK, OnT0DelayClock)
	ON_BN_CLICKED(IDC_A_DELAY_CLOCK, OnADelayClock)
	ON_BN_CLICKED(IDC_B_DELAY_CLOCK, OnBDelayClock)
	ON_BN_CLICKED(IDC_RESYNCH, OnResynch)
	ON_BN_CLICKED(IDC_E_DISCONNECT, OnEDisconnect)
	ON_BN_CLICKED(IDC_F_DISCONNECT, OnFDisconnect)
	ON_BN_CLICKED(IDC_E_MS_BUS, OnEMsBus)
	ON_BN_CLICKED(IDC_F_MS_BUS, OnFMsBus)
	ON_BN_CLICKED(IDC_E_INPUT_P, OnEInputP)
	ON_BN_CLICKED(IDC_E_INPUT_N, OnEInputN)
	ON_BN_CLICKED(IDC_F_INPUT_P, OnFInputP)
	ON_BN_CLICKED(IDC_F_INPUT_N, OnFInputN)
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefineDelayGeneratorDlg message handlers

BOOL CDefineDelayGeneratorDlg::Create(UINT nID, CWnd* pParentWnd)
{
	BOOL nResult = FALSE;
	if (!b_onScreen)
	{
		nResult = CDialog::Create(nID, pParentWnd);
		CRect crp;
		crp = WindowFrame.rcNormalPosition;
		if (crp.IsRectEmpty())
			GetWindowPlacement(&WindowFrame);
		else
			SetWindowPlacement(&WindowFrame);
		b_onScreen = TRUE;
	}
	else
		SetWindowPlacement(&WindowFrame);
	ReadSelectedLine();
	CWnd::SetFocus();
	return nResult;
}

void CDefineDelayGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID != SC_MAXIMIZE)
	{
		if (nID == SC_CLOSE)
		{
			b_onScreen=FALSE;
			DestroyWindow();	
		}
		CDialog::OnSysCommand(nID, lParam);		
	}
}

BOOL CDefineDelayGeneratorDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CDefineDelayGeneratorDlg::PostNcDestroy() 
{
	b_onScreen=FALSE;
	CDialog::PostNcDestroy();
}

void CDefineDelayGeneratorDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	if ((b_onScreen) && (!IsIconic()))
		GetWindowPlacement(&WindowFrame);
}

void CDefineDelayGeneratorDlg::RemoveWindow()
{
	if (b_onScreen)
	{
		b_onScreen=FALSE;
		DestroyWindow();	
	}
}

void CDefineDelayGeneratorDlg::OnCancel() 
{
	b_onScreen=FALSE;
	DestroyWindow();	
	//CDialog::OnCancel();
}

void CDefineDelayGeneratorDlg::ReadSelectedLine()
{
	WorkLine = _T("");
	CurrentLineNo = 0;
	int pos = p_DelgenTableCB->GetCurSel();
	if (pos != CB_ERR)
	{
		CString str;
		p_DelgenTableCB->GetLBText(pos, str);
		int npos = str.Find(": ");
		if (npos >= 0)
		{
			CurrentLineNo = atoi(str);
			WorkLine = str.Right(str.GetLength()-npos-1);
		}
	}
	if (b_onScreen)
		UpdateControls(); 
}

BOOL CDefineDelayGeneratorDlg::DiscretizeValues()
{
	CListRout lr;
	CString jstr;
	lr.TrimString(m_DgPrescaler);
	if (m_DgPrescaler.GetLength() > 0)
	{
		if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2", 
													"BME_G05V1", "BME_G05V2", "BME_G05V3", 
													"BME_G05P1", "BME_G05P2", "BME_G05P3",
													"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", 
													"BME_SG02V5", "BME_SG02V6", "BME_SG02V7", 
													"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			int Prescaler = min(32, max(1, RoundInt(atof(m_DgPrescaler))));
			if (!lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2",  "?"))
			{
				if (Prescaler > 16)
					Prescaler = 2 * ((Prescaler + 1) / 2);
			}
			m_DgPrescaler.Format(" %d", Prescaler);
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_G02V3", "BME_SG02V4", "?"))
			{
				double value = max(1.0, atof(m_DgPrescaler));
				int result = RoundInt(log(value) / log(2.0));
				result = min(5, result);
				int Prescaler = RoundInt(exp(double(result) * log(2.0)));
				m_DgPrescaler.Format(" %d", Prescaler);
			}
			else
				m_DgPrescaler = _T("");
		}
		UpdateData(FALSE);
	}
	lr.TrimString(m_TriggerDivider);
	if (m_TriggerDivider.GetLength() > 0)
	{
		if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2", 
																		"BME_G05V1", "BME_G05V2", "BME_G05V3",
																		"BME_G05P1", "BME_G05P2", "BME_G05P3",
																		"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																		"BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																		"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			int Prescaler = min(32, max(1, RoundInt(atof(m_TriggerDivider))));
			if (!lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2",  "?"))
			{
				if (Prescaler > 16)
					Prescaler = 2 * ((Prescaler + 1) / 2);
			}
			m_TriggerDivider.Format(" %d", Prescaler);
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_G02V3", "BME_SG02V4", "?"))
			{
				double value = max(1.0, atof(m_TriggerDivider));
				int result = RoundInt(log(value) / log(2.0));
				result = min(5, result);
				int Prescaler = RoundInt(exp(double(result) * log(2.0)));
				m_TriggerDivider.Format(" %d", Prescaler);
			}
			else
				m_TriggerDivider = _T("");
		}
		UpdateData(FALSE);
	}
	lr.TrimString(m_TriggerMultiplier);
	if (m_TriggerMultiplier.GetLength() > 0)
	{
		double tm = min(128.0, max(1.0, atof(m_TriggerMultiplier)));
		double te = log(tm)/log(2.0);
		te = double(min(7, max(0, RoundInt(te))));
		tm = exp(te * log(2.0));
		int result = RoundInt(tm);
		m_TriggerMultiplier.Format(" %d", result);
		UpdateData(FALSE);
	}
	lr.TrimString(m_DgName);
	if (m_DgName.GetLength() > 0)
	{
		if (lr.CommandType(m_DgName, 1, TRUE, "master", "slave", "?"))
		{
			m_DgName = _T("");
			AfxMessageBox("the names 'master' and 'slave' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_T0_Name);
	if (m_T0_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_T0_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_T0_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_A_Name);
	if (m_A_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_A_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_A_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_B_Name);
	if (m_B_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_B_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_B_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_C_Name);
	if (m_C_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_C_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_C_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_D_Name);
	if (m_D_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_D_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_D_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_E_Name);
	if (m_E_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_E_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_E_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_F_Name);
	if (m_F_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_F_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_F_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
			return FALSE;
		}
	}
	lr.TrimString(m_PulseWidth);
	if (m_PulseWidth.GetLength() > 0)
	{
		if (lr.Numeric(m_PulseWidth))
		{
			int pw = RoundInt(atof(m_PulseWidth));
			pw = min(255, max(0, pw));
			if (pw > 0)
				pw = max(2, pw);
			m_PulseWidth.Format(" %d", pw);
		}
		else
			m_PulseWidth = _T("");
		UpdateData(FALSE);
	}
	return TRUE;
}

void CDefineDelayGeneratorDlg::InsertList(int LineNo, BOOL Before) 
{
	CListRout lr;
	DG_Type* p_DG = new DG_Type;
	p_G0xData->ResetDG_Element(p_DG);
	p_DG->Control.DT.ResetWhenDone = TRUE;
	p_DG->Control.DT.TriggerEnable = TRUE;
	p_DG->Control.DT.ClockEnable = TRUE;
	BOOL exact = TRUE;
	int start = 1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V1", "?"))
		p_DG->Product = BME_G02V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V2", "?"))
		p_DG->Product = BME_G02V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V3", "?"))
		p_DG->Product = BME_G02V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V1", "?"))
		p_DG->Product = BME_SG02V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V2", "?"))
		p_DG->Product = BME_SG02V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V3", "?"))
		p_DG->Product = BME_SG02V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V4", "?"))
		p_DG->Product = BME_SG02V4;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V5", "?"))
		p_DG->Product = BME_SG02V5;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V6", "?"))
		p_DG->Product = BME_SG02V6;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V7", "?"))
		p_DG->Product = BME_SG02V7;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P1", "?"))
		p_DG->Product = BME_SG02P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P2", "?"))
		p_DG->Product = BME_SG02P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P3", "?"))
		p_DG->Product = BME_SG02P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P4", "?"))
		p_DG->Product = BME_SG02P4;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P5", "?"))
		p_DG->Product = BME_SG02P5;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V1", "?"))
		p_DG->Product = BME_G03V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V2", "?"))
		p_DG->Product = BME_G03V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V3", "?"))
		p_DG->Product = BME_G03V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V4", "?"))
		p_DG->Product = BME_G03V4;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V5", "?"))
		p_DG->Product = BME_G03V5;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03P1", "?"))
		p_DG->Product = BME_G03P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03P2", "?"))
		p_DG->Product = BME_G03P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V1", "?"))
		p_DG->Product = BME_G05V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V2", "?"))
		p_DG->Product = BME_G05V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V3", "?"))
		p_DG->Product = BME_G05V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P1", "?"))
		p_DG->Product = BME_G05P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P2", "?"))
		p_DG->Product = BME_G05P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P3", "?"))
		p_DG->Product = BME_G05P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P1", "?"))
		p_DG->Product = BME_SG05P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P2", "?"))
		p_DG->Product = BME_SG05P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P3", "?"))
		p_DG->Product = BME_SG05P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG08P1", "?"))
		p_DG->Product = BME_SG08P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG08P2", "?"))
		p_DG->Product = BME_SG08P2;
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
		p_DG->BaseAddress = RoundInt(atof(m_DgAddress));
		p_DG->BusNumber = RoundInt(atof(m_DgBus));
		lr.TrimString(m_EthernetAddress);
		if (m_EthernetAddress.GetLength() > 0)
		  lr.WriteMemo(p_DG->ip_address, (LPCTSTR)m_EthernetAddress, 24);
		break;
	default:
		p_DG->BaseAddress = lr.ReadHexadecimalString((LPCTSTR)m_DgAddress);
		break;
	}
	p_DG->Master = m_DgMaster;
	lr.WriteMemo(p_DG->DG_Name, (LPCTSTR)m_DgName, 32);
	lr.WriteMemo(p_DG->T0_Name, (LPCTSTR)m_T0_Name, 32);
	lr.WriteMemo(p_DG->A_Name, (LPCTSTR)m_A_Name, 32);
	lr.WriteMemo(p_DG->B_Name, (LPCTSTR)m_B_Name, 32);
	lr.WriteMemo(p_DG->C_Name, (LPCTSTR)m_C_Name, 32);
	lr.WriteMemo(p_DG->D_Name, (LPCTSTR)m_D_Name, 32);
	lr.WriteMemo(p_DG->E_Name, (LPCTSTR)m_E_Name, 32);
	lr.WriteMemo(p_DG->F_Name, (LPCTSTR)m_F_Name, 32);
	p_DG->Control.DG_Product = p_DG->Product;
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
		p_DG->Control.DT.OscillatorDivider = 8;
		break;
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
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_PrimaryGo)
			p_DG->Control.DT.MS_Bus |= LocalPrimary;
		if (m_SecondaryGo)
			p_DG->Control.DT.MS_Bus |= LocalSecondary;
		if (m_ForceGo)
			p_DG->Control.DT.MS_Bus |= LocalForce;
		break;
	case BME_SG02P3:
		p_DG->Control.DT.MS_Bus = (LocalPrimary | LocalForce);
		break;
	case BME_SG08P1:
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_GateMsN)
			p_DG->Control.DT.MS_Bus |= GateOnBusNegative;
		else
		{
			if (m_GateMsP)
				p_DG->Control.DT.MS_Bus |= GateOnBusPositive;
		}
		break;
	case BME_SG08P2:
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_SecondaryGo)
			p_DG->Control.DT.MS_Bus |= LocalSecondary;
		if (m_StepBackOnBus)
			p_DG->Control.DT.MS_Bus |= StepBackOnBus;
		if (m_StartOnBus)
			p_DG->Control.DT.MS_Bus |= StartOnBus;
		if (m_InhibitOnBus)
			p_DG->Control.DT.MS_Bus |= InhibitOnBus;
		if (m_LoadDataOnBus)
			p_DG->Control.DT.MS_Bus |= LoadDataOnBus;
		if (m_GateMsN)
			p_DG->Control.DT.MS_Bus |= GateOnBusNegative;
		else
		{
			if (m_GateMsP)
				p_DG->Control.DT.MS_Bus |= GateOnBusPositive;
		}
		break;
	default:
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG02P5:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_Resynch)
			p_DG->Control.DT.MS_Bus |= Resynchronize;
		else
			p_DG->Control.DT.MS_Bus &= ~Resynchronize;
		break;
	case BME_SG02P4:
	case BME_G05P3:
	case BME_SG05P2:
		p_DG->Control.DT.MS_Bus |= Resynchronize;
		break;
	default:
		p_DG->Control.DT.MS_Bus &= ~Resynchronize;
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_A_DelayClock)
			p_DG->Control.A.GoSignal |= (SystemClock | DelayClock);
		else
			p_DG->Control.A.GoSignal &= ~(SystemClock | DelayClock);
		if (m_B_DelayClock)
			p_DG->Control.B.GoSignal |= (SystemClock | DelayClock);
		else
			p_DG->Control.B.GoSignal &= ~(SystemClock | DelayClock);
		if (m_A_Positive)
			p_DG->Control.A.Positive = TRUE;
		else
			p_DG->Control.A.Positive = FALSE;
		if (m_B_Positive)
			p_DG->Control.B.Positive = TRUE;
		else
			p_DG->Control.B.Positive = FALSE;
		if (m_C_Positive)
			p_DG->Control.C.Positive = TRUE;
		else
			p_DG->Control.C.Positive = FALSE;
		if (m_D_Positive)
			p_DG->Control.D.Positive = TRUE;
		else
			p_DG->Control.D.Positive = FALSE;
		if (m_E_Positive)
			p_DG->Control.E.Positive = TRUE;
		else
			p_DG->Control.E.Positive = FALSE;
		if (m_F_Positive)
			p_DG->Control.F.Positive = TRUE;
		else
			p_DG->Control.F.Positive = FALSE;
		if (m_A_Terminate)
			p_DG->Control.A.Terminate = TRUE;
		else
			p_DG->Control.A.Terminate = FALSE;
		if (m_B_Terminate)
			p_DG->Control.B.Terminate = TRUE;
		else
			p_DG->Control.B.Terminate = FALSE;
		if (m_C_Terminate)
			p_DG->Control.C.Terminate = TRUE;
		else
			p_DG->Control.C.Terminate = FALSE;
		if (m_D_Terminate)
			p_DG->Control.D.Terminate = TRUE;
		else
			p_DG->Control.D.Terminate = FALSE;
		if (m_E_Terminate)
			p_DG->Control.E.Terminate = TRUE;
		else
			p_DG->Control.E.Terminate = FALSE;
		if (m_F_Terminate)
			p_DG->Control.F.Terminate = TRUE;
		else
			p_DG->Control.F.Terminate = FALSE;
		if (m_E_Disconnect)
			p_DG->Control.E.Disconnect = TRUE;
		else
			p_DG->Control.E.Disconnect = FALSE;
		if (m_F_Disconnect)
			p_DG->Control.F.Disconnect = TRUE;
		else
			p_DG->Control.F.Disconnect = FALSE;
		if (m_E_MsBus)
			p_DG->Control.E.OntoMsBus = TRUE;
		else
			p_DG->Control.E.OntoMsBus = FALSE;
		if (m_E_InputP)
			p_DG->Control.E.InputPositive = TRUE;
		else
			p_DG->Control.E.InputPositive = FALSE;
		if (m_F_MsBus)
			p_DG->Control.F.OntoMsBus = TRUE;
		else
			p_DG->Control.F.OntoMsBus = FALSE;
		if (m_F_InputP)
			p_DG->Control.F.InputPositive = TRUE;
		else
			p_DG->Control.F.InputPositive = FALSE;
		if (m_GateTerminate)
			p_DG->Control.DT.GateTerminate = TRUE;
		else
			p_DG->Control.DT.GateTerminate = FALSE;
		if (m_UseF)
			p_DG->Control.DT.UseF = TRUE;
		else
			p_DG->Control.DT.UseF = FALSE;
		break;
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((m_T0_Clock) || (m_T0_DelayClock))
		{
			p_DG->Control.T0.GoSignal |= SystemClock;
			if (m_T0_DelayClock)
				p_DG->Control.T0.GoSignal |= DelayClock;
			else
				p_DG->Control.T0.GoSignal &= ~DelayClock;
		}
		else
			p_DG->Control.T0.GoSignal &= ~(SystemClock | DelayClock);
	default:
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_SG05P1:
		lr.TrimString(m_PulseWidth);
		if (m_PulseWidth.GetLength() > 0)
			p_DG->Control.PulseWidth = RoundInt(atof(m_PulseWidth));
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if (m_TtlLevel)
			p_DG->Control.OutputLevel = TTL_VoltageLevel;
		if (m_NimLevel)
			p_DG->Control.OutputLevel = NIM_VoltageLevel;
		if (m_EclLevel)
			p_DG->Control.OutputLevel = ECL_VoltageLevel;
		if (m_T0_Terminate)
			p_DG->Control.T0.Terminate = TRUE;
		else
			p_DG->Control.T0.Terminate = FALSE;
		if (m_A_Terminate)
			p_DG->Control.A.Terminate = TRUE;
		else
			p_DG->Control.A.Terminate = FALSE;
		if (m_B_Terminate)
			p_DG->Control.B.Terminate = TRUE;
		else
			p_DG->Control.B.Terminate = FALSE;
		if (m_T0_HighDrive)
			p_DG->Control.T0.HighDrive = TRUE;
		else
			p_DG->Control.T0.HighDrive = FALSE;
		if (m_A_HighDrive)
			p_DG->Control.A.HighDrive = TRUE;
		else
			p_DG->Control.A.HighDrive = FALSE;
		if (m_B_HighDrive)
			p_DG->Control.B.HighDrive = TRUE;
		else
			p_DG->Control.B.HighDrive = FALSE;
	case BME_G03V3:
	case BME_G03V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_G05V1:
	case BME_G05V2:
		if (m_T0_Positive)
			p_DG->Control.T0.Positive = TRUE;
		else
			p_DG->Control.T0.Positive = FALSE;
		if (m_A_Positive)
			p_DG->Control.A.Positive = TRUE;
		else
			p_DG->Control.A.Positive = FALSE;
		if (m_B_Positive)
			p_DG->Control.B.Positive = TRUE;
		else
			p_DG->Control.B.Positive = FALSE;
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_TriggerTerminate)
			p_DG->Control.DT.Terminate = TRUE;
		else
			p_DG->Control.DT.Terminate = FALSE;
	case BME_G02V3:
	case BME_SG02V4:
		if (m_TriggerInput)
			p_DG->Control.DT.ClockSource = TriggerInput;
		if (m_FreeRunning)
			p_DG->Control.DT.ClockSource = TriggerAndOscillator;
		if (m_CrystalOscillator)
			p_DG->Control.DT.ClockSource = CrystalOscillator;
		if (m_MsBusClock)
			p_DG->Control.DT.ClockSource = MasterSlaveBus;
		if ((m_TriggerInput) || (m_FreeRunning))
		{
			p_DG->Control.DT.InternalTrigger = TRUE;
			p_DG->Control.DT.InternalArm = FALSE;
		}
		if (p_DG->Control.DT.ClockSource != TriggerInput)
		{
			lr.TrimString(m_DgPrescaler);
			if (m_DgPrescaler.GetLength() > 0)
				p_DG->Control.DT.OscillatorDivider = min(32, max(1, RoundInt(atof(m_DgPrescaler))));
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
					p_DG->Control.DT.OscillatorDivider = 8;
					break;
				case BME_SG08P1:
				case BME_SG08P2:
					p_DG->Control.DT.OscillatorDivider = 16;
					break;
				default:
					break;
				}
			}
		}
		lr.TrimString(m_TriggerDivider);
		lr.TrimString(m_TriggerMultiplier);
		if (m_TriggerDivider.GetLength() > 0)
			p_DG->Control.DT.TriggerDivider = min(32, max(1, RoundInt(atof(m_TriggerDivider))));
		else
		{
			if (m_TriggerMultiplier.GetLength() > 0)
				p_DG->Control.DT.TriggerDivider = 1;
			else
				p_DG->Control.DT.TriggerDivider = 6;
		}
		if (m_TriggerMultiplier.GetLength() > 0)
			p_DG->Control.DT.TriggerMultiplier = min(128, max(1, RoundInt(atof(m_TriggerMultiplier))));
		else
			p_DG->Control.DT.TriggerMultiplier = 1;
		break;
	default:
		break;
	}
	if (LineNo == 0)
		p_DG_List->AddHead(p_DG);
	else
	{
		POSITION pos = p_DG_List->FindIndex(LineNo - 1);
		if (Before)
			p_DG_List->InsertBefore(pos, p_DG);
		else
			p_DG_List->InsertAfter(pos, p_DG);
	}
}


void CDefineDelayGeneratorDlg::ReplaceList(int LineNo)
{
	CListRout lr;
	int DG_Product = -1;
	POSITION pos = p_DG_List->FindIndex(LineNo - 1);
	DG_Type* p_DG = p_DG_List->GetAt(pos);
	BOOL exact = TRUE;
	int start = 1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V1", "?"))
		DG_Product = BME_G02V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V2", "?"))
		DG_Product = BME_G02V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G02V3", "?"))
		DG_Product = BME_G02V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V1", "?"))
		DG_Product = BME_SG02V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V2", "?"))
		DG_Product = BME_SG02V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V3", "?"))
		DG_Product = BME_SG02V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V4", "?"))
		DG_Product = BME_SG02V4;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V5", "?"))
		DG_Product = BME_SG02V5;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V6", "?"))
		DG_Product = BME_SG02V6;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02V7", "?"))
		DG_Product = BME_SG02V7;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P1", "?"))
		DG_Product = BME_SG02P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P2", "?"))
		DG_Product = BME_SG02P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P3", "?"))
		DG_Product = BME_SG02P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P4", "?"))
		DG_Product = BME_SG02P4;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG02P5", "?"))
		DG_Product = BME_SG02P5;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V1", "?"))
		DG_Product = BME_G03V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V2", "?"))
		DG_Product = BME_G03V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V3", "?"))
		DG_Product = BME_G03V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V4", "?"))
		DG_Product = BME_G03V4;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03V5", "?"))
		DG_Product = BME_G03V5;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03P1", "?"))
		DG_Product = BME_G03P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G03P2", "?"))
		DG_Product = BME_G03P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V1", "?"))
		DG_Product = BME_G05V1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V2", "?"))
		DG_Product = BME_G05V2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05V3", "?"))
		DG_Product = BME_G05V3;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P1", "?"))
		DG_Product = BME_G05P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P2", "?"))
		DG_Product = BME_G05P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_G05P3", "?"))
		DG_Product = BME_G05P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P1", "?"))
		DG_Product = BME_SG05P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P2", "?"))
		DG_Product = BME_SG05P2;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG05P3", "?"))
		DG_Product = BME_SG05P3;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG08P1", "?"))
		DG_Product = BME_SG08P1;
	if (lr.CommandType(m_DgType, start, exact, "BME_SG08P2", "?"))
		DG_Product = BME_SG08P2;
	if (DG_Product != p_DG->Product)
	{
		switch (DG_Product)
		{
		case BME_SG08P2:
			if (p_DG->Product == BME_SG08P1)
				break;
		default:
			p_G0xData->ResetDG_Element(p_DG);
			p_DG->Control.DT.TriggerEnable = TRUE;
			break;
		}
	}
	p_DG->Product = DG_Product;
	p_DG->Control.DT.ResetWhenDone = TRUE;
	p_DG->Control.DT.ClockEnable = TRUE;
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
		p_DG->BaseAddress = RoundInt(atof(m_DgAddress));
		p_DG->BusNumber = RoundInt(atof(m_DgBus));
		lr.TrimString(m_EthernetAddress);
		if (m_EthernetAddress.GetLength() > 0)
		  lr.WriteMemo(p_DG->ip_address, (LPCTSTR)m_EthernetAddress, 24);
		break;
	default:
		p_DG->BaseAddress = lr.ReadHexadecimalString((LPCTSTR)m_DgAddress);
		break;
	}
	p_DG->Master = m_DgMaster;
	lr.WriteMemo(p_DG->DG_Name, (LPCTSTR)m_DgName, 32);
	lr.WriteMemo(p_DG->T0_Name, (LPCTSTR)m_T0_Name, 32);
	lr.WriteMemo(p_DG->A_Name, (LPCTSTR)m_A_Name, 32);
	lr.WriteMemo(p_DG->B_Name, (LPCTSTR)m_B_Name, 32);
	lr.WriteMemo(p_DG->C_Name, (LPCTSTR)m_C_Name, 32);
	lr.WriteMemo(p_DG->D_Name, (LPCTSTR)m_D_Name, 32);
	lr.WriteMemo(p_DG->E_Name, (LPCTSTR)m_E_Name, 32);
	lr.WriteMemo(p_DG->F_Name, (LPCTSTR)m_F_Name, 32);
	p_DG->Control.DG_Product = p_DG->Product;
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
		p_DG->Control.DT.OscillatorDivider = 8;
		break;
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
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_PrimaryGo)
			p_DG->Control.DT.MS_Bus |= LocalPrimary;
		if (m_SecondaryGo)
			p_DG->Control.DT.MS_Bus |= LocalSecondary;
		if (m_ForceGo)
			p_DG->Control.DT.MS_Bus |= LocalForce;
		break;
	case BME_SG02P3:
		p_DG->Control.DT.MS_Bus = (LocalPrimary | LocalForce);
		break;
	case BME_SG08P1:
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_GateMsN)
			p_DG->Control.DT.MS_Bus |= GateOnBusNegative;
		else
		{
			if (m_GateMsP)
				p_DG->Control.DT.MS_Bus |= GateOnBusPositive;
		}
		break;
	case BME_SG08P2:
		p_DG->Control.DT.MS_Bus = 0x0;
		if (m_SecondaryGo)
			p_DG->Control.DT.MS_Bus |= LocalSecondary;
		if (m_StepBackOnBus)
			p_DG->Control.DT.MS_Bus |= StepBackOnBus;
		if (m_StartOnBus)
			p_DG->Control.DT.MS_Bus |= StartOnBus;
		if (m_InhibitOnBus)
			p_DG->Control.DT.MS_Bus |= InhibitOnBus;
		if (m_LoadDataOnBus)
			p_DG->Control.DT.MS_Bus |= LoadDataOnBus;
		if (m_GateMsN)
			p_DG->Control.DT.MS_Bus |= GateOnBusNegative;
		else
		{
			if (m_GateMsP)
				p_DG->Control.DT.MS_Bus |= GateOnBusPositive;
		}
		break;
	default:
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG02P5:
	case BME_SG05P3:
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_Resynch)
			p_DG->Control.DT.MS_Bus |= Resynchronize;
		else
			p_DG->Control.DT.MS_Bus &= ~Resynchronize;
		break;
	case BME_SG02P4:
	case BME_G05P3:
	case BME_SG05P2:
		p_DG->Control.DT.MS_Bus |= Resynchronize;
		break;
	default:
			p_DG->Control.DT.MS_Bus &= ~Resynchronize;
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_A_DelayClock)
			p_DG->Control.A.GoSignal |= (SystemClock | DelayClock);
		else
			p_DG->Control.A.GoSignal &= ~(SystemClock | DelayClock);
		if (m_B_DelayClock)
			p_DG->Control.B.GoSignal |= (SystemClock | DelayClock);
		else
			p_DG->Control.B.GoSignal &= ~(SystemClock | DelayClock);
		if (m_A_Positive)
			p_DG->Control.A.Positive = TRUE;
		else
			p_DG->Control.A.Positive = FALSE;
		if (m_B_Positive)
			p_DG->Control.B.Positive = TRUE;
		else
			p_DG->Control.B.Positive = FALSE;
		if (m_C_Positive)
			p_DG->Control.C.Positive = TRUE;
		else
			p_DG->Control.C.Positive = FALSE;
		if (m_D_Positive)
			p_DG->Control.D.Positive = TRUE;
		else
			p_DG->Control.D.Positive = FALSE;
		if (m_E_Positive)
			p_DG->Control.E.Positive = TRUE;
		else
			p_DG->Control.E.Positive = FALSE;
		if (m_F_Positive)
			p_DG->Control.F.Positive = TRUE;
		else
			p_DG->Control.F.Positive = FALSE;
		if (m_A_Terminate)
			p_DG->Control.A.Terminate = TRUE;
		else
			p_DG->Control.A.Terminate = FALSE;
		if (m_B_Terminate)
			p_DG->Control.B.Terminate = TRUE;
		else
			p_DG->Control.B.Terminate = FALSE;
		if (m_C_Terminate)
			p_DG->Control.C.Terminate = TRUE;
		else
			p_DG->Control.C.Terminate = FALSE;
		if (m_D_Terminate)
			p_DG->Control.D.Terminate = TRUE;
		else
			p_DG->Control.D.Terminate = FALSE;
		if (m_E_Terminate)
			p_DG->Control.E.Terminate = TRUE;
		else
			p_DG->Control.E.Terminate = FALSE;
		if (m_F_Terminate)
			p_DG->Control.F.Terminate = TRUE;
		else
			p_DG->Control.F.Terminate = FALSE;
		if (m_E_Disconnect)
			p_DG->Control.E.Disconnect = TRUE;
		else
			p_DG->Control.E.Disconnect = FALSE;
		if (m_F_Disconnect)
			p_DG->Control.F.Disconnect = TRUE;
		else
			p_DG->Control.F.Disconnect = FALSE;
		if (m_E_MsBus)
			p_DG->Control.E.OntoMsBus = TRUE;
		else
			p_DG->Control.E.OntoMsBus = FALSE;
		if (m_E_InputP)
			p_DG->Control.E.InputPositive = TRUE;
		else
			p_DG->Control.E.InputPositive = FALSE;
		if (m_F_MsBus)
			p_DG->Control.F.OntoMsBus = TRUE;
		else
			p_DG->Control.F.OntoMsBus = FALSE;
		if (m_F_InputP)
			p_DG->Control.F.InputPositive = TRUE;
		else
			p_DG->Control.F.InputPositive = FALSE;
		if (m_GateTerminate)
			p_DG->Control.DT.GateTerminate = TRUE;
		else
			p_DG->Control.DT.GateTerminate = FALSE;
		if (m_UseF)
			p_DG->Control.DT.UseF = TRUE;
		else
			p_DG->Control.DT.UseF = FALSE;
		break;
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG05P3:
		if ((m_T0_Clock) || (m_T0_DelayClock))
		{
			p_DG->Control.T0.GoSignal |= SystemClock;
			if (m_T0_DelayClock)
				p_DG->Control.T0.GoSignal |= DelayClock;
			else
				p_DG->Control.T0.GoSignal &= ~DelayClock;
		}
		else
			p_DG->Control.T0.GoSignal &= ~(SystemClock | DelayClock);
	default:
		break;
	}
	switch (p_DG->Product)
	{
	case BME_SG02P4:
	case BME_SG02P5:
	case BME_G05P3:
	case BME_SG05P2:
	case BME_SG05P3:
	case BME_SG02V7:
	case BME_SG02P1:
	case BME_SG02P2:
	case BME_SG02P3:
	case BME_G05V3:
	case BME_G05P1:
	case BME_G05P2:
	case BME_SG05P1:
		lr.TrimString(m_PulseWidth);
		if (m_PulseWidth.GetLength() > 0)
			p_DG->Control.PulseWidth = RoundInt(atof(m_PulseWidth));
	case BME_G03V5:
	case BME_G03P1:
	case BME_G03P2:
		if (m_TtlLevel)
			p_DG->Control.OutputLevel = TTL_VoltageLevel;
		if (m_NimLevel)
			p_DG->Control.OutputLevel = NIM_VoltageLevel;
		if (m_EclLevel)
			p_DG->Control.OutputLevel = ECL_VoltageLevel;
		if (m_T0_Terminate)
			p_DG->Control.T0.Terminate = TRUE;
		else
			p_DG->Control.T0.Terminate = FALSE;
		if (m_A_Terminate)
			p_DG->Control.A.Terminate = TRUE;
		else
			p_DG->Control.A.Terminate = FALSE;
		if (m_B_Terminate)
			p_DG->Control.B.Terminate = TRUE;
		else
			p_DG->Control.B.Terminate = FALSE;
		if (m_T0_HighDrive)
			p_DG->Control.T0.HighDrive = TRUE;
		else
			p_DG->Control.T0.HighDrive = FALSE;
		if (m_A_HighDrive)
			p_DG->Control.A.HighDrive = TRUE;
		else
			p_DG->Control.A.HighDrive = FALSE;
		if (m_B_HighDrive)
			p_DG->Control.B.HighDrive = TRUE;
		else
			p_DG->Control.B.HighDrive = FALSE;
	case BME_G03V3:
	case BME_G03V4:
	case BME_SG02V5:
	case BME_SG02V6:
	case BME_G05V1:
	case BME_G05V2:
		if (m_T0_Positive)
			p_DG->Control.T0.Positive = TRUE;
		else
			p_DG->Control.T0.Positive = FALSE;
		if (m_A_Positive)
			p_DG->Control.A.Positive = TRUE;
		else
			p_DG->Control.A.Positive = FALSE;
		if (m_B_Positive)
			p_DG->Control.B.Positive = TRUE;
		else
			p_DG->Control.B.Positive = FALSE;
	case BME_SG08P1:
	case BME_SG08P2:
		if (m_TriggerTerminate)
			p_DG->Control.DT.Terminate = TRUE;
		else
			p_DG->Control.DT.Terminate = FALSE;
	case BME_G02V3:
	case BME_SG02V4:
		if (m_TriggerInput)
			p_DG->Control.DT.ClockSource = TriggerInput;
		if (m_FreeRunning)
			p_DG->Control.DT.ClockSource = TriggerAndOscillator;
		if (m_CrystalOscillator)
			p_DG->Control.DT.ClockSource = CrystalOscillator;
		if (m_MsBusClock)
			p_DG->Control.DT.ClockSource = MasterSlaveBus;
		if ((m_TriggerInput) || (m_FreeRunning))
		{
			p_DG->Control.DT.InternalTrigger = TRUE;
			p_DG->Control.DT.InternalArm = FALSE;
		}
		if (p_DG->Control.DT.ClockSource != TriggerInput)
		{
			lr.TrimString(m_DgPrescaler);
			if (m_DgPrescaler.GetLength() > 0)
				p_DG->Control.DT.OscillatorDivider = min(32, max(1, RoundInt(atof(m_DgPrescaler))));
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
					p_DG->Control.DT.OscillatorDivider = 8;
					break;
				default:
					break;
				}
			}
		}
		lr.TrimString(m_TriggerDivider);
		lr.TrimString(m_TriggerMultiplier);
		if (m_TriggerDivider.GetLength() > 0)
			p_DG->Control.DT.TriggerDivider = min(32, max(1, RoundInt(atof(m_TriggerDivider))));
		else
		{
			if (m_TriggerMultiplier.GetLength() > 0)
				p_DG->Control.DT.TriggerDivider = 1;
			else
				p_DG->Control.DT.TriggerDivider = 6;
		}
		if (m_TriggerMultiplier.GetLength() > 0)
			p_DG->Control.DT.TriggerMultiplier = min(128, max(1, RoundInt(atof(m_TriggerMultiplier))));
		else
			p_DG->Control.DT.TriggerMultiplier = 1;
		break;
	default:
		break;
	}
}

void CDefineDelayGeneratorDlg::OnInsertLine() 
{
	CListRout lr;
	CInsertLineDlg dlg;
	if (!UpdateEditLine())
		return;
	int LineCount = lr.GetLineCount(*p_DelgenTableCB);
	if (LineCount == 0)
	{
		BOOL success = lr.InsertLine(*p_DelgenTableCB, WorkLine, 0, FALSE);
		if (!success)
			AfxMessageBox("no action line inserted!",MB_OK,0);
		else
		{
			InsertList(0, FALSE);
			*p_DataModified = TRUE;
		}
		return;
	}
	if (CurrentLineNo > 0)
		dlg.m_InsertLine = CurrentLineNo;
	else
	{
		int LineNo = lr.GetLineCount(*p_DelgenTableCB);
		if ( LineNo > 0)
			dlg.m_InsertLine = LineNo;
	}
	if (dlg.DoModal() == IDOK)
	{
		BOOL success = lr.InsertLine(*p_DelgenTableCB,
										WorkLine, dlg.m_InsertLine, dlg.m_InsertBefore);
		if (!success)
			AfxMessageBox("no action line inserted!",MB_OK,0);
		else
		{
			InsertList(dlg.m_InsertLine, dlg.m_InsertBefore);
			*p_DataModified = TRUE;
		}
	}
}

void CDefineDelayGeneratorDlg::OnReplaceLine() 
{
	CListRout lr;
	CReplaceLineDlg dlg;
	if (!UpdateEditLine())
		return;
	if (CurrentLineNo > 0)
		dlg.m_ReplaceLine = CurrentLineNo;
	if (dlg.DoModal() == IDOK)
	{
		BOOL success = lr.ReplaceLine(*p_DelgenTableCB, 
										WorkLine, dlg.m_ReplaceLine);
		if (!success)
			AfxMessageBox("no action line replaced!",MB_OK,0);
		else
		{
			ReplaceList(dlg.m_ReplaceLine);
			*p_DataModified = TRUE;
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeDgAddress() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnChangeDgBus() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnChangeIpAddress() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusIpAddress() 
{
	CListRout lr;
	lr.TrimString(m_EthernetAddress);
	if (m_EthernetAddress.GetLength() > 0)
	{
		if (!lr.EthernetAddress((LPCTSTR)m_EthernetAddress))
		{
			m_EthernetAddress = _T("");
			AfxMessageBox("Invalid Ethernet Address!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnDgMaster() 
{
	UpdateData(TRUE);
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnChangeDgPrescaler() 
{
	CListRout lr;
	if (!lr.CommandType(m_DgType, "BME_G02V3", "BME_G03V3", "BME_G03V4", "BME_G03V5", 
																			"BME_G03P1", "BME_G03P2",
																			"BME_G05V1", "BME_G05V2", "BME_G05V3",
																			"BME_G05P1", "BME_G05P2", "BME_G05P3", 
																			"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																			"BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																			"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		m_DgPrescaler = _T("");
		UpdateData(FALSE);
		CString jstr = m_DgType + " does not have a prescaler!";
		AfxMessageBox(jstr, MB_OK, 0);
	}
	else
	{
		if ((!m_DgMaster) && (!lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3",  "BME_SG08P1", "BME_SG08P2",
																										"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?")))
		{
			m_DgPrescaler = _T("");
			UpdateData(FALSE);
			AfxMessageBox("prescaler is only active\n  on the master module!", MB_OK, 0);
		}
		else
			UpdateData(TRUE);
	}
}

void CDefineDelayGeneratorDlg::OnKillfocusDgPrescaler() 
{
	CListRout lr;
	lr.TrimString(m_DgPrescaler);
	if (m_DgPrescaler.GetLength() > 0)
	{
		if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2",
																		"BME_G05V1", "BME_G05V2", "BME_G05V3",
																		"BME_G05P1", "BME_G05P2", "BME_G05P3", 
																		"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																		"BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																		"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4",  "BME_SG02P5", "?"))
		{
			int Prescaler = min(32, max(1, RoundInt(atof(m_DgPrescaler))));
			if (!lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2",  "?"))
			{
				if (Prescaler > 16)
					Prescaler = 2 * ((Prescaler + 1) / 2);
			}
			m_DgPrescaler.Format(" %d", Prescaler);
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_G02V3", "BME_SG02V4", "?"))
			{
				double value = max(1.0, atof(m_DgPrescaler));
				int result = RoundInt(log(value) / log(2.0));
				result = min(5, result);
				int Prescaler = RoundInt(exp(double(result) * log(2.0)));
				m_DgPrescaler.Format(" %d", Prescaler);
			}
			else
				m_DgPrescaler = _T("");
		}
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnChangeTriggerDivider() 
{
	CListRout lr;
	if (!lr.CommandType(m_DgType, "BME_G02V3", "BME_G03V3", "BME_G03V4", "BME_G03V5",
																			"BME_G03P1", "BME_G03P2",
																			"BME_G05V1", "BME_G05V2", "BME_G05V3",
																			"BME_G05P1", "BME_G05P2", "BME_G05P3", 
																			"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																			"BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																			"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4",  "BME_SG02P5", "?"))
	{
		m_TriggerDivider = _T("");
		UpdateData(FALSE);
		CString jstr = m_DgType + " does not have a prescaler!";
		AfxMessageBox(jstr, MB_OK, 0);
	}
	else
	{
		if ((!m_DgMaster) && (!lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG08P1", "BME_SG08P2",
																										"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?")))
		{
			m_TriggerDivider = _T("");
			UpdateData(FALSE);
			AfxMessageBox("prescaler is only active\n  on the master module!", MB_OK, 0);
		}
		else
			UpdateData(TRUE);
	}
}

void CDefineDelayGeneratorDlg::OnKillfocusTriggerDivider() 
{
	CListRout lr;
	CString jstr;
	lr.TrimString(m_TriggerDivider);
	if (m_TriggerDivider.GetLength() > 0)
	{
		if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2", 
																		"BME_G05V1", "BME_G05V2", "BME_G05V3",
																		"BME_G05P1", "BME_G05P2", "BME_G05P3",
																		"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																		"BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																		"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			int Prescaler = min(32, max(1, RoundInt(atof(m_TriggerDivider))));
			if (!lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2",  "?"))
			{
				if (Prescaler > 16)
					Prescaler = 2 * ((Prescaler + 1) / 2);
			}
			m_TriggerDivider.Format(" %d", Prescaler);
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_G02V3", "BME_SG02V4", "?"))
			{
				double value = max(1.0, atof(m_TriggerDivider));
				int result = RoundInt(log(value) / log(2.0));
				result = min(5, result);
				int Prescaler = RoundInt(exp(double(result) * log(2.0)));
				m_TriggerDivider.Format(" %d", Prescaler);
			}
			else
				m_TriggerDivider = _T("");
		}
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnChangeTriggerMultiplier() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusTriggerMultiplier() 
{
	CListRout lr;
	lr.TrimString(m_TriggerMultiplier);
	if (m_TriggerMultiplier.GetLength() > 0)
	{
		double tm = min(128.0, max(1.0, atof(m_TriggerMultiplier)));
		double te = log(tm)/log(2.0);
		te = double(min(7, max(0, RoundInt(te))));
		tm = exp(te * log(2.0));
		int result = RoundInt(tm);
		m_TriggerMultiplier.Format(" %d", result);
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::CheckHardwareControls() 
{
	CListRout lr;
	BOOL b_Polarity = FALSE;
	BOOL b_OutputTerminate = FALSE;
	BOOL b_HighDrive = FALSE;
	BOOL b_LevelSelect = FALSE;
	BOOL b_TriggerTerminate = FALSE;
	BOOL b_GateTerminate = FALSE;
	BOOL b_GateMsBus = FALSE;
	BOOL b_EfMsBus = FALSE;
	BOOL b_ClockSelect = FALSE;
	BOOL b_TriggerMultiplier = FALSE;
	BOOL b_FreeRunning = FALSE;
	BOOL b_Prescaler = FALSE;
	BOOL b_PulseWidth = FALSE;
	BOOL b_MsBusSelect = FALSE;
	BOOL b_MsWideBusSelect = FALSE;
	BOOL b_MsBusClock = FALSE;
	BOOL b_ForceAlways = FALSE;
	BOOL b_T0_Clock = FALSE;
	BOOL b_T0_DelayClock = FALSE;
	BOOL b_A_DelayClock = FALSE;
	BOOL b_B_DelayClock = FALSE;
	BOOL b_Resynch = FALSE;
	BOOL b_T0_Active = FALSE;
	BOOL b_C_Active = FALSE;
	BOOL b_D_Active = FALSE;
	BOOL b_E_Active = FALSE;
	BOOL b_F_Active = FALSE;
	if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
	{
		b_C_Active = TRUE;
		b_D_Active = TRUE;
		b_E_Active = TRUE;
		b_F_Active = TRUE;
		b_MsBusClock = TRUE;
		b_Polarity = TRUE;
		b_OutputTerminate = TRUE;
		b_TriggerTerminate = TRUE;
		b_GateTerminate = TRUE;
		b_ClockSelect = TRUE;
		b_TriggerMultiplier = TRUE;
		b_FreeRunning = TRUE;
		b_Prescaler = TRUE;
	}
	else
		b_T0_Active = TRUE;
	if (lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P2", "?"))
	{
		b_MsBusSelect = TRUE;
		b_MsBusClock = TRUE;
		if (lr.CommandType(m_DgType, "BME_SG08P2", "?"))
			b_MsWideBusSelect = TRUE;
	}
	else
	{
		if (lr.CommandType(m_DgType, "BME_SG02P3", "?"))
			b_ForceAlways = TRUE;
	}
	if (lr.CommandType(m_DgType, "BME_G05V3", "BME_G05P1", "BME_G05P2", "BME_G05P3", 
		                           "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG02V7",
															 "BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		b_PulseWidth = TRUE;
	}
	if (lr.CommandType(m_DgType, "BME_G03V5", "BME_G03P1", "BME_G03P2", "BME_G05V3",
																"BME_G05P1", "BME_G05P2", "BME_G05P3",
																"BME_SG05P1", "BME_SG05P2", "BME_SG05P3",
																"BME_SG02V7", "BME_SG02P1", "BME_SG02P2",
																"BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		b_Polarity = TRUE;
		b_OutputTerminate = TRUE;
		b_HighDrive = TRUE;
		b_LevelSelect = TRUE;
		b_TriggerTerminate = TRUE;
		b_ClockSelect = TRUE;
		b_FreeRunning = TRUE;
		b_Prescaler = TRUE;
	}
	else
	{
		if (lr.CommandType(m_DgType, "BME_G05V2", "BME_SG02V6", "?"))
		{
			b_Polarity = TRUE;
			b_TriggerTerminate = TRUE;
			b_ClockSelect = TRUE;
			b_FreeRunning = TRUE;
			b_Prescaler = TRUE;
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G05V1", "BME_G05V2", 
																					"BME_SG02V5", "BME_SG02V6", "?"))
			{
				b_Polarity = TRUE;
				b_TriggerTerminate = TRUE;
				b_ClockSelect = TRUE;
				b_Prescaler = TRUE;
			}
			else
			{
				if (lr.CommandType(m_DgType, "BME_G02V3", "BME_SG02V4", "?"))
				{
					b_ClockSelect = TRUE;
					b_Prescaler = TRUE;
				}
			}
		}
	}
	if (lr.CommandType(m_DgType, "BME_SG02P5", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "?"))
		b_Resynch = TRUE;
	if (m_DgMaster)
	{
		b_MsBusClock = FALSE;
		if (lr.CommandType(m_DgType, "BME_SG02P4", "BME_SG02P5", "BME_G05P3", "BME_SG05P2", "BME_SG05P3", "?"))
		{
			b_T0_Clock = TRUE;
			if (lr.CommandType(m_DgType, "BME_SG02P5", "BME_SG05P3", "?"))
				b_T0_DelayClock = TRUE;
		}
		else
		{
			if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
			{
				b_A_DelayClock = TRUE;
				b_B_DelayClock = TRUE;
				b_GateMsBus = TRUE;
				b_EfMsBus = TRUE;
			}
		}
	}
	else
	{
		if (!lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "?"))
		{
			b_Prescaler = FALSE;
			b_ClockSelect = FALSE;
			b_FreeRunning = FALSE;
			b_TriggerTerminate = FALSE;
		}
		if (!lr.CommandType(m_DgType, "BME_SG08P2", "?"))
			b_MsBusSelect = FALSE;
	}
	if (b_T0_Active)
	{
		m_T0_NameED.EnableWindow(TRUE);
		if (b_Polarity)
		{
			m_T0_NegativeB.EnableWindow(TRUE);
			m_T0_PositiveB.EnableWindow(TRUE);
			if ((!m_T0_Positive) && (!m_T0_Negative))
				m_T0_Positive = TRUE;
		}
		else
		{
			m_T0_Negative = FALSE;
			m_T0_NegativeB.EnableWindow(FALSE);
			m_T0_Positive = FALSE;
			m_T0_PositiveB.EnableWindow(FALSE);
		}
		if (b_OutputTerminate)
			m_T0_TerminateB.EnableWindow(TRUE);
		else
		{
			m_T0_Terminate = FALSE;
			m_T0_TerminateB.EnableWindow(FALSE);
		}
	}
	else
	{
		m_T0_Name =  _T("");
		m_T0_NameED.EnableWindow(FALSE);
		m_T0_Terminate = FALSE;
		m_T0_TerminateB.EnableWindow(FALSE);
		m_T0_Negative = FALSE;
		m_T0_NegativeB.EnableWindow(FALSE);
		m_T0_Positive = FALSE;
		m_T0_PositiveB.EnableWindow(FALSE);
	}
	if (b_C_Active)
	{
		m_C_NameED.EnableWindow(TRUE);
		m_C_NegativeB.EnableWindow(TRUE);
		m_C_PositiveB.EnableWindow(TRUE);
		if ((!m_C_Positive) && (!m_C_Negative))
			m_C_Positive = TRUE;
		m_C_TerminateB.EnableWindow(TRUE);
	}
	else
	{
		m_C_Name =  _T("");
		m_C_NameED.EnableWindow(FALSE);
		m_C_Terminate = FALSE;
		m_C_TerminateB.EnableWindow(FALSE);
		m_C_Negative = FALSE;
		m_C_NegativeB.EnableWindow(FALSE);
		m_C_Positive = FALSE;
		m_C_PositiveB.EnableWindow(FALSE);
	}
	if (b_D_Active)
	{
		m_D_NameED.EnableWindow(TRUE);
		m_D_NegativeB.EnableWindow(TRUE);
		m_D_PositiveB.EnableWindow(TRUE);
		if ((!m_D_Positive) && (!m_D_Negative))
			m_D_Positive = TRUE;
		m_D_TerminateB.EnableWindow(TRUE);
	}
	else
	{
		m_D_Name =  _T("");
		m_D_NameED.EnableWindow(FALSE);
		m_D_Terminate = FALSE;
		m_D_TerminateB.EnableWindow(FALSE);
		m_D_Negative = FALSE;
		m_D_NegativeB.EnableWindow(FALSE);
		m_D_Positive = FALSE;
		m_D_PositiveB.EnableWindow(FALSE);
	}
	if (b_E_Active)
	{
		m_E_NameED.EnableWindow(TRUE);
		m_E_NegativeB.EnableWindow(TRUE);
		m_E_PositiveB.EnableWindow(TRUE);
		if ((!m_E_Positive) && (!m_E_Negative))
			m_E_Positive = TRUE;
		m_E_TerminateB.EnableWindow(TRUE);
		m_E_DisconnectB.EnableWindow(TRUE);
		m_E_InputPB.EnableWindow(TRUE);
		m_E_InputNB.EnableWindow(TRUE);
		if ((!m_E_InputP) && (!m_E_InputN))
			m_E_InputP = TRUE;
	}
	else
	{
		m_E_Name =  _T("");
		m_E_NameED.EnableWindow(FALSE);
		m_E_Terminate = FALSE;
		m_E_TerminateB.EnableWindow(FALSE);
		m_E_Negative = FALSE;
		m_E_NegativeB.EnableWindow(FALSE);
		m_E_Positive = FALSE;
		m_E_PositiveB.EnableWindow(FALSE);
		m_E_Disconnect = FALSE;
		m_E_DisconnectB.EnableWindow(FALSE);
		m_E_InputP = FALSE;
		m_E_InputPB.EnableWindow(FALSE);
		m_E_InputN = FALSE;
		m_E_InputNB.EnableWindow(FALSE);
	}
	if (b_F_Active)
	{
		m_F_NameED.EnableWindow(TRUE);
		m_F_NegativeB.EnableWindow(TRUE);
		m_F_PositiveB.EnableWindow(TRUE);
		if ((!m_F_Positive) && (!m_F_Negative))
			m_F_Positive = TRUE;
		m_F_TerminateB.EnableWindow(TRUE);
		m_F_DisconnectB.EnableWindow(TRUE);
		m_F_InputPB.EnableWindow(TRUE);
		m_F_InputNB.EnableWindow(TRUE);
		if ((!m_F_InputP) && (!m_F_InputN))
			m_F_InputP = TRUE;
	}
	else
	{
		m_F_Name =  _T("");
		m_F_NameED.EnableWindow(FALSE);
		m_F_Terminate = FALSE;
		m_F_TerminateB.EnableWindow(FALSE);
		m_F_Negative = FALSE;
		m_F_NegativeB.EnableWindow(FALSE);
		m_F_Positive = FALSE;
		m_F_PositiveB.EnableWindow(FALSE);
		m_F_Disconnect = FALSE;
		m_F_DisconnectB.EnableWindow(FALSE);
		m_F_InputP = FALSE;
		m_F_InputPB.EnableWindow(FALSE);
		m_F_InputN = FALSE;
		m_F_InputNB.EnableWindow(FALSE);
	}
	if (b_Polarity)
	{
		m_A_NegativeB.EnableWindow(TRUE);
		m_A_PositiveB.EnableWindow(TRUE);
		if ((!m_A_Positive) && (!m_A_Negative))
			m_A_Positive = TRUE;
		m_B_NegativeB.EnableWindow(TRUE);
		m_B_PositiveB.EnableWindow(TRUE);
		if ((!m_B_Positive) && (!m_B_Negative))
			m_B_Positive = TRUE;
	}
	else
	{
		m_A_Negative = FALSE;
		m_A_NegativeB.EnableWindow(FALSE);
		m_A_Positive = FALSE;
		m_A_PositiveB.EnableWindow(FALSE);
		m_B_Negative = FALSE;
		m_B_NegativeB.EnableWindow(FALSE);
		m_B_Positive = FALSE;
		m_B_PositiveB.EnableWindow(FALSE);
	}
	if (b_OutputTerminate)
	{
		m_A_TerminateB.EnableWindow(TRUE);
		m_B_TerminateB.EnableWindow(TRUE);
	}
	else
	{
		m_A_Terminate = FALSE;
		m_A_TerminateB.EnableWindow(FALSE);
		m_B_Terminate = FALSE;
		m_B_TerminateB.EnableWindow(FALSE);
	}
	if (b_HighDrive)
	{
		m_T0_HighDriveB.EnableWindow(TRUE);
		m_A_HighDriveB.EnableWindow(TRUE);
		m_B_HighDriveB.EnableWindow(TRUE);
	}
	else
	{
		m_T0_HighDrive = FALSE;
		m_T0_HighDriveB.EnableWindow(FALSE);
		m_A_HighDrive = FALSE;
		m_A_HighDriveB.EnableWindow(FALSE);
		m_B_HighDrive = FALSE;
		m_B_HighDriveB.EnableWindow(FALSE);
	}
	if (b_LevelSelect)
	{
		m_TtlLevelB.EnableWindow(TRUE);
		m_NimLevelB.EnableWindow(TRUE);
		m_EclLevelB.EnableWindow(TRUE);
		if ((!m_TtlLevel) && (!m_NimLevel) && (!m_EclLevel))
			m_TtlLevel = TRUE;
	}
	else
	{
		m_TtlLevel = FALSE;
		m_TtlLevelB.EnableWindow(FALSE);
		m_NimLevel = FALSE;
		m_NimLevelB.EnableWindow(FALSE);
		m_EclLevel = FALSE;
		m_EclLevelB.EnableWindow(FALSE);
	}
	if (b_TriggerTerminate)
		m_TriggerTerminateB.EnableWindow(TRUE);
	else
	{
		m_TriggerTerminate = FALSE;
		m_TriggerTerminateB.EnableWindow(FALSE);
	}
	if (b_GateTerminate)
	{
		m_GateTerminateB.EnableWindow(TRUE);
		m_UseFB.EnableWindow(TRUE);
	}
	else
	{
		m_GateTerminate = FALSE;
		m_UseF = FALSE;
		m_GateTerminateB.EnableWindow(FALSE);
		m_UseFB.EnableWindow(FALSE);
	}
	if (b_GateMsBus)
	{
		m_GateMsPB.EnableWindow(TRUE);
		m_GateMsNB.EnableWindow(TRUE);
	}
	else
	{
		m_GateMsP = FALSE;
		m_GateMsN = FALSE;
		m_GateMsPB.EnableWindow(FALSE);
		m_GateMsNB.EnableWindow(FALSE);
	}
	if (b_EfMsBus)
	{
		m_E_MsBusB.EnableWindow(TRUE);
		m_F_MsBusB.EnableWindow(TRUE);
	}
	else
	{
		m_E_MsBus = FALSE;
		m_E_MsBusB.EnableWindow(FALSE);
		m_F_MsBus = FALSE;
		m_F_MsBusB.EnableWindow(FALSE);
	}
	if (b_ClockSelect)
	{
		m_TriggerInputB.EnableWindow(TRUE);
		m_CrystalOscillatorB.EnableWindow(TRUE);
		if (b_MsBusClock)
			m_MsBusClockB.EnableWindow(TRUE);
		else
		{
			m_MsBusClock = FALSE;
			m_MsBusClockB.EnableWindow(FALSE);
		}
		if (b_FreeRunning)
			m_FreeRunningB.EnableWindow(TRUE);
		else
		{
			m_FreeRunning = FALSE;
			m_FreeRunningB.EnableWindow(FALSE);
		}
		if ((!m_TriggerInput) && (!m_CrystalOscillator) && (!m_FreeRunning) && (!m_MsBusClock))
			m_CrystalOscillator = TRUE;
		if (m_FreeRunning)
		{
			m_DgPrescalerED.EnableWindow(TRUE);
			m_TriggerDividerED.EnableWindow(TRUE);
			if (b_TriggerMultiplier)
				m_TriggerMultiplierED.EnableWindow(TRUE);
			else
			{
				m_TriggerMultiplier = _T("");
				m_TriggerMultiplierED.EnableWindow(FALSE);
			}
		}
		else
		{
			if (m_CrystalOscillator || m_MsBusClock)
			{
				m_DgPrescalerED.EnableWindow(TRUE);
				m_TriggerDivider = _T("");
				m_TriggerDividerED.EnableWindow(FALSE);
				m_TriggerMultiplier = _T("");
				m_TriggerMultiplierED.EnableWindow(FALSE);
			}
			else
			{
				if (b_TriggerMultiplier)
					m_TriggerMultiplierED.EnableWindow(TRUE);
				else
				{
					m_TriggerMultiplier = _T("");
					m_TriggerMultiplierED.EnableWindow(FALSE);
				}
				m_TriggerDividerED.EnableWindow(TRUE);
				m_DgPrescaler = _T("");
				m_DgPrescalerED.EnableWindow(FALSE);
			}
		}
	}
	else
	{
		m_TriggerInput = FALSE;
		m_TriggerInputB.EnableWindow(FALSE);
		m_CrystalOscillator = FALSE;
		m_CrystalOscillatorB.EnableWindow(FALSE);
		m_FreeRunning = FALSE;
		m_FreeRunningB.EnableWindow(FALSE);
		m_MsBusClock = FALSE;
		m_MsBusClockB.EnableWindow(FALSE);
		m_DgPrescaler = _T("");
		m_DgPrescalerED.EnableWindow(FALSE);
		m_TriggerDivider = _T("");
		m_TriggerDividerED.EnableWindow(FALSE);
		m_TriggerMultiplier = _T("");
		m_TriggerMultiplierED.EnableWindow(FALSE);
	}
	if (b_PulseWidth)
		m_PulseWidthED.EnableWindow(TRUE);
	else
	{
		m_PulseWidth = _T("");
		m_PulseWidthED.EnableWindow(FALSE);
	}
	if (b_T0_Clock)
		m_T0_ClockB.EnableWindow(TRUE);
	else
	{
		m_T0_Clock = FALSE;
		m_T0_ClockB.EnableWindow(FALSE);
	}
	if (b_T0_DelayClock)
		m_T0_DelayClockB.EnableWindow(TRUE);
	else
	{
		m_T0_DelayClock = FALSE;
		m_T0_DelayClockB.EnableWindow(FALSE);
	}
	if (b_A_DelayClock)
		m_A_DelayClockB.EnableWindow(TRUE);
	else
	{
		m_A_DelayClock = FALSE;
		m_A_DelayClockB.EnableWindow(FALSE);
	}
	if (b_B_DelayClock)
		m_B_DelayClockB.EnableWindow(TRUE);
	else
	{
		m_B_DelayClock = FALSE;
		m_B_DelayClockB.EnableWindow(FALSE);
	}
	if (b_Resynch)
		m_ResynchB.EnableWindow(TRUE);
	else
	{
		if (lr.CommandType(m_DgType, "BME_SG02P4", "BME_G05P3", "BME_SG05P2", "?"))
			m_Resynch = TRUE;
		else
			m_Resynch = FALSE;
		m_ResynchB.EnableWindow(FALSE);
	}
	if (b_MsBusSelect)
	{
		if (lr.CommandType(m_DgType, "BME_SG08P2", "?"))
		{
			m_PrimaryGo = TRUE;
			m_PrimaryGoB.EnableWindow(FALSE);
			m_ForceGo = TRUE;
			m_ForceGoB.EnableWindow(FALSE);
		}
		else
		{
			m_PrimaryGoB.EnableWindow(TRUE);
			m_ForceGoB.EnableWindow(TRUE);
		}
		m_SecondaryGoB.EnableWindow(TRUE);
	}
	else
	{
		m_SecondaryGo = FALSE;
		if ((m_DgMaster) && (!lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?")))
		{
			m_PrimaryGo = TRUE;
			if (b_ForceAlways)
				m_ForceGo = TRUE;
			else
				m_ForceGo = FALSE;
		}
		else
		{
			m_PrimaryGo = FALSE;
			m_ForceGo = FALSE;
		}
		m_PrimaryGoB.EnableWindow(FALSE);
		m_SecondaryGoB.EnableWindow(FALSE);
		m_ForceGoB.EnableWindow(FALSE);
	}
	if (b_MsWideBusSelect)
	{
		m_StepBackOnBusB.EnableWindow(TRUE);
		m_StartOnBusB.EnableWindow(TRUE);
		m_InhibitOnBusB.EnableWindow(TRUE);
		m_LoadDataOnBusB.EnableWindow(TRUE);
		if (CountBusLines() != 4)
		{
			m_SecondaryGo = TRUE;
			m_StepBackOnBus = TRUE;
			m_StartOnBus = TRUE;
			m_InhibitOnBus = TRUE;
			m_LoadDataOnBus = FALSE;
		}
	}
	else
	{
		m_StepBackOnBus = FALSE;
		m_StepBackOnBusB.EnableWindow(FALSE);
		m_StartOnBus = FALSE;
		m_StartOnBusB.EnableWindow(FALSE);
		m_InhibitOnBus = FALSE;
		m_InhibitOnBusB.EnableWindow(FALSE);
		m_LoadDataOnBus = FALSE;
		m_LoadDataOnBusB.EnableWindow(FALSE);
	}
	if (lr.CommandType(m_DgType, "BME_G03P1", "BME_G03P2", "BME_G05P1", "BME_G05P2", "BME_G05P3", 
		                           "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
			                         "BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		m_AddressLine.SetWindowText("    Slot no.");
		m_DgBusED.EnableWindow(TRUE);
		m_EthernetAddressED.EnableWindow(TRUE);
	}
	else
	{
		m_AddressLine.SetWindowText("&Address (hex)");
		m_DgBus = _T("");
		m_DgBusED.EnableWindow(FALSE);
		m_EthernetAddress = _T("");
		m_EthernetAddressED.EnableWindow(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnSelendokDgType() 
{
	UpdateData(TRUE);
	int pos = m_DgTypeCB.GetCurSel();
	if (pos != CB_ERR)
	{
		m_DgTypeCB.GetLBText(pos, m_DgType);
		CheckHardwareControls();
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnANegative() 
{
	UpdateData(TRUE);
	m_A_Positive = !m_A_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnAPositive() 
{
	UpdateData(TRUE);
	m_A_Negative = !m_A_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnBNegative() 
{
	UpdateData(TRUE);
	m_B_Positive = !m_B_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnBPositive() 
{
	UpdateData(TRUE);
	m_B_Negative = !m_B_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnCNegative() 
{
	UpdateData(TRUE);
	m_C_Positive = !m_C_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnCPositive() 
{
	UpdateData(TRUE);
	m_C_Negative = !m_C_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnDNegative() 
{
	UpdateData(TRUE);
	m_D_Positive = !m_D_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnDPositive() 
{
	UpdateData(TRUE);
	m_D_Negative = !m_D_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnENegative() 
{
	UpdateData(TRUE);
	m_E_Positive = !m_E_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnEPositive() 
{
	UpdateData(TRUE);
	m_E_Negative = !m_E_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnFNegative() 
{
	UpdateData(TRUE);
	m_F_Positive = !m_F_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnFPositive() 
{
	UpdateData(TRUE);
	m_F_Negative = !m_F_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnT0Negative() 
{
	UpdateData(TRUE);
	m_T0_Positive = !m_T0_Negative;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnT0Positive() 
{
	UpdateData(TRUE);
	m_T0_Negative = !m_T0_Positive;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnT0Terminate() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_T0_Terminate)
			m_T0_HighDrive = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_T0_Terminate)
				m_T0_HighDrive = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnATerminate() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_A_Terminate)
			m_A_HighDrive = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_A_Terminate)
				m_A_HighDrive = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnBTerminate() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_B_Terminate)
			m_B_HighDrive = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_B_Terminate)
				m_B_HighDrive = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnCTerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnDTerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnETerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnFTerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnT0Clock() 
{
	UpdateData(TRUE);
	if (m_T0_Clock)
	{
		m_T0_DelayClock = FALSE;
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnT0DelayClock() 
{
	UpdateData(TRUE);
	if (m_T0_DelayClock)
	{
		m_T0_Clock = FALSE;
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnADelayClock() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnBDelayClock() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnResynch() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnEDisconnect() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnFDisconnect() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnEMsBus() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnFMsBus() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnEInputP() 
{
	UpdateData(TRUE);
	m_E_InputN = ! m_E_InputP;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnEInputN() 
{
	UpdateData(TRUE);
	m_E_InputP = ! m_E_InputN;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnFInputP() 
{
	UpdateData(TRUE);
	m_F_InputN = ! m_F_InputP;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnFInputN() 
{
	UpdateData(TRUE);
	m_F_InputP = ! m_F_InputN;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnT0HighDrive() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_T0_HighDrive)
			m_T0_Terminate = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_T0_HighDrive)
				m_T0_Terminate = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnAHighDrive() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_A_HighDrive)
			m_A_Terminate = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_A_HighDrive)
				m_A_Terminate = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnBHighDrive() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		if (m_A_HighDrive)
			m_A_Terminate = FALSE;
	}
	else
	{
		if (m_EclLevel)
		{
			if (!m_A_HighDrive)
				m_A_Terminate = TRUE;
		}
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnChangePulseWidth() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusPulseWidth() 
{
	CListRout lr;
	lr.TrimString(m_PulseWidth);
	if (m_PulseWidth.GetLength() > 0)
	{
		if (lr.Numeric(m_PulseWidth))
		{
			int pw = RoundInt(atof(m_PulseWidth));
			pw = min(255, max(0, pw));
			if (pw > 0)
				pw = max(2, pw);
			m_PulseWidth.Format(" %d", pw);
		}
		else
			m_PulseWidth = _T("");
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::InitializeOutputState()
{
	if (m_TtlLevel)
	{
		m_T0_HighDrive = FALSE;
		m_T0_Terminate = FALSE;
		m_A_HighDrive = FALSE;
		m_A_Terminate = FALSE;
		m_B_HighDrive = FALSE;
		m_B_Terminate = FALSE;
	}
	else
	{
		m_T0_Terminate = TRUE;
		m_A_Terminate = TRUE;
		m_B_Terminate = TRUE;
		if (m_EclLevel)
		{
			m_T0_HighDrive = TRUE;
			m_A_HighDrive = TRUE;
			m_B_HighDrive = TRUE;
		}
		else
		{
			m_T0_HighDrive = FALSE;
			m_A_HighDrive = FALSE;
			m_B_HighDrive = FALSE;
		}
	}
}

int CDefineDelayGeneratorDlg::CountBusLines() 
{
	int NoBusLines = 0;
	if (m_SecondaryGo)
		NoBusLines++;
	if (m_StepBackOnBus)
		NoBusLines++;
	if (m_StartOnBus)
		NoBusLines++;
	if (m_InhibitOnBus)
		NoBusLines++;
	if (m_LoadDataOnBus)
		NoBusLines++;
	return NoBusLines;
}

void CDefineDelayGeneratorDlg::OnForceGo() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnPrimaryGo() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnSecondaryGo() 
{
	CListRout lr;
	UpdateData(TRUE);
	if (lr.CommandType(m_DgType, "BME_SG08P2", "?"))
	{
		if (m_SecondaryGo)
		{
			m_StepBackOnBus = TRUE;
			m_StartOnBus = TRUE;
			m_InhibitOnBus = TRUE;
			m_LoadDataOnBus = FALSE;
		}
		else
		{
			m_StepBackOnBus = TRUE;
			m_StartOnBus = TRUE;
			m_InhibitOnBus = TRUE;
			m_LoadDataOnBus = TRUE;
		}
		UpdateData(FALSE);
	}
}

void CDefineDelayGeneratorDlg::OnStepBackOnBus() 
{
	UpdateData(TRUE);
	if (m_StepBackOnBus)
	{
		m_StartOnBus = TRUE;
		m_InhibitOnBus = TRUE;
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = FALSE;
	}
	else
	{
		m_StartOnBus = TRUE;
		m_InhibitOnBus = TRUE;
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = TRUE;
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnStartOnBus() 
{
	UpdateData(TRUE);
	if (m_StartOnBus)
	{
		m_InhibitOnBus = TRUE;
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = FALSE;
	}
	else
	{
		m_InhibitOnBus = TRUE;
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = TRUE;
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnInhibitOnBus() 
{
	UpdateData(TRUE);
	if (m_InhibitOnBus)
	{
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = TRUE;
		m_StartOnBus = FALSE;
	}
	else
	{
		m_LoadDataOnBus = TRUE;
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = TRUE;
		m_StartOnBus = TRUE;
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnLoadDataOnBus() 
{
	UpdateData(TRUE);
	if (m_LoadDataOnBus)
	{
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = TRUE;
		m_StartOnBus = TRUE;
		m_InhibitOnBus = FALSE;
	}
	else
	{
		m_SecondaryGo = TRUE;
		m_StepBackOnBus = TRUE;
		m_StartOnBus = TRUE;
		m_InhibitOnBus = TRUE;
	}
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnTtlLevel() 
{
	UpdateData(TRUE);
	if (m_TtlLevel)
	{
		m_NimLevel = FALSE;
		m_EclLevel = FALSE;
	}
	else
	{
		m_NimLevel = TRUE;
		m_EclLevel = FALSE;
	}
	InitializeOutputState();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnNimLevel() 
{
	UpdateData(TRUE);
	if (m_NimLevel)
	{
		m_TtlLevel = FALSE;
		m_EclLevel = FALSE;
	}
	else
	{
		m_TtlLevel = FALSE;
		m_EclLevel = TRUE;
	}
	InitializeOutputState();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnEclLevel() 
{
	UpdateData(TRUE);
	if (m_EclLevel)
	{
		m_NimLevel = FALSE;
		m_TtlLevel = FALSE;
	}
	else
	{
		m_NimLevel = FALSE;
		m_TtlLevel = TRUE;
	}
	InitializeOutputState();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnTriggerTerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnGateTerminate() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnUseF() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnGateMsP() 
{
	UpdateData(TRUE);
	if (m_GateMsP)
		m_GateMsN = FALSE;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnGateMsN()
{
	UpdateData(TRUE);
	if (m_GateMsN)
		m_GateMsP = FALSE;
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnCrystalOscillator() 
{
	UpdateData(TRUE);
	if (m_CrystalOscillator)
	{
		m_TriggerInput = FALSE;
		m_FreeRunning = FALSE;
		m_MsBusClock = FALSE;
	}
	else
	{
		m_TriggerInput = TRUE;
		m_FreeRunning = FALSE;
		m_MsBusClock = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnTriggerInput() 
{
	UpdateData(TRUE);
	if (m_TriggerInput)
	{
		m_CrystalOscillator = FALSE;
		m_FreeRunning = FALSE;
		m_MsBusClock = FALSE;
	}
	else
	{
		CListRout lr;
		if (lr.CommandType(m_DgType, "BME_G03V5", "BME_G03P1", "BME_G03P2",
											"BME_G05V2", "BME_G05V3", "BME_G05P1", "BME_G05P2", "BME_G05P3",
											"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
											"BME_SG02V6", "BME_SG02V7",
											"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			m_CrystalOscillator = FALSE;
			m_FreeRunning = TRUE;
		}
		else
		{
			m_CrystalOscillator = TRUE;
			m_FreeRunning = FALSE;
		}
		m_MsBusClock = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnFreeRunning() 
{
	UpdateData(TRUE);
	if (m_FreeRunning)
	{
		m_CrystalOscillator = FALSE;
		m_TriggerInput = FALSE;
		m_MsBusClock = FALSE;
	}
	else
	{
		CListRout lr;
		if ((!m_DgMaster) && (lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3",
																					"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "?")))
		{
			m_MsBusClock = TRUE;
			m_CrystalOscillator = FALSE;
			m_TriggerInput = FALSE;
		}
		else
		{
			m_CrystalOscillator = TRUE;
			m_TriggerInput = FALSE;
			m_MsBusClock = FALSE;
		}
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnMsBusClock() 
{
	UpdateData(TRUE);
	if (m_MsBusClock)
	{
		m_CrystalOscillator = FALSE;
		m_TriggerInput = FALSE;
		m_FreeRunning = FALSE;
	}
	else
	{
		m_CrystalOscillator = TRUE;
		m_TriggerInput = FALSE;
		m_FreeRunning = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CDefineDelayGeneratorDlg::OnChangeDgName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusDgName() 
{
	CListRout lr;
	lr.TrimString(m_DgName);
	if (m_DgName.GetLength() > 0)
	{
		if (lr.CommandType(m_DgName, 1, TRUE, "master", "slave", "?"))
		{
			m_DgName = _T("");
			AfxMessageBox("the names 'master' and 'slave' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeT0Name() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusT0Name() 
{
	CListRout lr;
	lr.TrimString(m_T0_Name);
	if (m_T0_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_T0_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_T0_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeAName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusAName() 
{
	CListRout lr;
	lr.TrimString(m_A_Name);
	if (m_A_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_A_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_A_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeBName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusBName() 
{
	CListRout lr;
	lr.TrimString(m_B_Name);
	if (m_B_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_B_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_B_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeCName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusCName() 
{
	CListRout lr;
	lr.TrimString(m_C_Name);
	if (m_C_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_C_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_C_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeDName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusDName() 
{
	CListRout lr;
	lr.TrimString(m_D_Name);
	if (m_D_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_D_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_D_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeEName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusEName() 
{
	CListRout lr;
	lr.TrimString(m_E_Name);
	if (m_E_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_E_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_E_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::OnChangeFName() 
{
	UpdateData(TRUE);
}

void CDefineDelayGeneratorDlg::OnKillfocusFName() 
{
	CListRout lr;
	lr.TrimString(m_F_Name);
	if (m_F_Name.GetLength() > 0)
	{
		if (lr.CommandType(m_F_Name, 1, TRUE, "positive", "negative", "?"))
		{
			m_F_Name = _T("");
			AfxMessageBox("the names 'positive' and 'negative' \n     are not allowed!!", MB_OK, 0);
			UpdateData(FALSE);
		}
	}
}

void CDefineDelayGeneratorDlg::ResetMenu()
{
	m_DgAddress = _T("");
	m_DgBus = _T("");
	m_EthernetAddress = _T("");
	m_DgMaster = FALSE;
	m_DgType = _T("");
	m_DgName = _T("");
	m_DgPrescaler = _T("");
	m_TriggerDivider = _T("");
	m_TriggerMultiplier = _T("");
	m_TriggerInput = FALSE;
	m_CrystalOscillator = FALSE;
	m_FreeRunning = FALSE;
	m_MsBusClock = FALSE;
	m_T0_Name = _T("");
	m_A_Name = _T("");
	m_B_Name = _T("");
	m_TriggerTerminate = FALSE;
	m_GateTerminate = FALSE;
	m_UseF = FALSE;
	m_GateMsP = FALSE;
	m_GateMsN = FALSE;
	m_T0_Terminate = FALSE;
	m_A_Terminate = FALSE;
	m_B_Terminate = FALSE;
	m_C_Terminate = FALSE;
	m_D_Terminate = FALSE;
	m_E_Terminate = FALSE;
	m_F_Terminate = FALSE;
	m_A_HighDrive = FALSE;
	m_B_HighDrive = FALSE;
	m_T0_Clock = FALSE;
	m_T0_DelayClock = FALSE;
	m_A_DelayClock = FALSE;
	m_B_DelayClock = FALSE;
	m_Resynch = FALSE;
	m_T0_HighDrive = FALSE;
	m_T0_Negative = FALSE;
	m_T0_Positive = FALSE;
	m_A_Negative = FALSE;
	m_A_Positive = FALSE;
	m_B_Negative = FALSE;
	m_B_Positive = FALSE;
	m_C_Negative = FALSE;
	m_C_Positive = FALSE;
	m_D_Negative = FALSE;
	m_D_Positive = FALSE;
	m_E_Negative = FALSE;
	m_E_Positive = FALSE;
	m_F_Negative = FALSE;
	m_F_Positive = FALSE;
	m_TtlLevel = FALSE;
	m_NimLevel = FALSE;
	m_EclLevel = FALSE;
	m_PrimaryGo = FALSE;
	m_SecondaryGo = FALSE;
	m_ForceGo = FALSE;
	m_StepBackOnBus = FALSE;
	m_StartOnBus = FALSE;
	m_InhibitOnBus = FALSE;
	m_LoadDataOnBus = FALSE;
	m_E_Disconnect = FALSE;
	m_F_Disconnect = FALSE;
	m_E_MsBus = FALSE;
	m_F_MsBus = FALSE;
	m_E_InputP = FALSE;
	m_E_InputN = FALSE;
	m_F_InputP = FALSE;
	m_F_InputN = FALSE;
}

void CDefineDelayGeneratorDlg::UpdateControls()
{
	CString wstr = WorkLine;
	CString jstr,kstr,lstr,mstr,nstr;
	CListRout lr;
	ResetMenu();
	int kpos,npos,pos;
	int start = 1;
	while (start > 0)
	{
		start = lr.NextCommandPosition(wstr, jstr, start, TRUE,
													"BME_G02V3", "BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
													"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5",
													"BME_G02V1", "BME_G02V2", "BME_SG02V1", "BME_SG02V2", "BME_SG02V3", 
													"BME_G03V1", "BME_G03V2", "BME_G03V3", "BME_G03V4", "BME_G03V5",
													"BME_G03P1", "BME_G03P2", 
													"BME_G05V1", "BME_G05V2", "BME_G05V3", 
													"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", 
													"T0", "A", "B", "C", "D", "E", "F", "pw", "?");
		if (jstr.GetLength() == 0)
			break;
		if (lr.CommandType(jstr, 1, TRUE, "BME_G02V3", "BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
												"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5",
												"BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2",
												"BME_G02V1", "BME_G02V2", "BME_SG02V1", "BME_SG02V2", "BME_SG02V3",
												"BME_G03V1", "BME_G03V2", "BME_G05V1", "BME_G05V2", "BME_G05V3",
												"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "?"))
		{
			npos = lr.NextCharacterGroup(jstr, kstr, 1);
			pos = m_DgTypeCB.SelectString(-1, kstr);
			m_DgTypeCB.GetLBText(pos, m_DgType);
			if (!lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?"))
				m_PrimaryGo = TRUE;
			if (lr.CommandType(m_DgType, "BME_SG02P3", "?"))
				m_ForceGo = TRUE;
			kstr = lr.CommandParameters(jstr, "BME_G02V3", "BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
												"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5",
												"BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2",
												"BME_G02V1", "BME_G02V2", "BME_SG02V1", "BME_SG02V2", "BME_SG02V3",
												"BME_G03V1", "BME_G03V2", "BME_G05V1", "BME_G05V2", "BME_G05V3",
												"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "master", "slave", "?"))
				{
					lr.PreCommandPosition(kstr, lstr, 1, TRUE, "master", "slave", "?");
					lr.TrimString(lstr);
					m_DgName = lstr;
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE, "master", "slave", 
								"trigger", "crystal", "switch", "msbus", 
								"rsync", "term", "gtrm", "usef", "gmsp", "gmsn", "TTL", "NIM", "ECL", "prim", "scnd", "frc", "stbk", "strt", "inhb", "ldob", "?");
					if (lr.CommandType(lstr, "master", "slave", "?"))
					{
						if (lr.CommandType(lstr, "master", "?"))
							m_DgMaster = TRUE;
						mstr = lr.CommandParameters(lstr, "master", "slave", "?");
						if (lr.Numeric(mstr))
						{
							kpos = lr.NextCharacterGroup(mstr, nstr, 1);
							if (lr.Numeric(nstr))
								m_DgAddress = (" " + nstr);
							if (kpos > 0)
							{
								kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
								if (lr.Numeric(nstr))
									m_DgBus = (" " + nstr);
								if (kpos > 0)
								{
									kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
									m_EthernetAddress = (" " + nstr);
								}
							}
						}

					}
					if (lr.CommandType(m_DgType, 
											"BME_G02V3", "BME_G03V3", "BME_G03V4", "BME_G03V5", "BME_G03P1", "BME_G03P2",
											"BME_G05V1", "BME_G05V2", "BME_G05V3", 
											"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", 
											"BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
											"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
					{
						if (lr.CommandType(lstr, "trigger", "crystal", "switch", "msbus", "?"))
						{
							mstr = lr.CommandParameters(lstr, "trigger", "crystal", "switch", "msbus", "?");
							if (lr.CommandType(lstr, "trigger", "?"))
							{
								m_TriggerInput = TRUE;
								kpos = 1;
								while (kpos > 0)
								{
									kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
									if (nstr.GetLength() > 0)
									{
										if (lr.Numeric(nstr))
											m_TriggerDivider = (" " + nstr);
										else
										{
											if (lr.CommandType(nstr, "mul", "?"))
											{
												kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
												if (nstr.GetLength() > 0)
												{
													if (lr.Numeric(nstr))
														m_TriggerMultiplier = (" " + nstr);
												}
											}
										}
									}
								}
							}
							if (lr.CommandType(lstr, "crystal", "?"))
							{
								m_CrystalOscillator = TRUE;
								kpos = lr.NextCharacterGroup(mstr, nstr, 1);
								if (nstr.GetLength() > 0)
								{
									if (lr.Numeric(nstr))
										m_DgPrescaler = (" " + nstr);
								}
							}
							if (lr.CommandType(lstr, "msbus", "?"))
							{
								m_MsBusClock = TRUE;
								kpos = lr.NextCharacterGroup(mstr, nstr, 1);
								if (nstr.GetLength() > 0)
								{
									if (lr.Numeric(nstr))
										m_DgPrescaler = (" " + nstr);
								}
							}
							if (lr.CommandType(lstr, "switch", "?"))
							{
								m_FreeRunning = TRUE;
								kpos = lr.NextCharacterGroup(mstr, nstr, 1);
								if (nstr.GetLength() > 0)
								{
									if (lr.Numeric(nstr))
									{
										m_TriggerDivider = (" " + nstr);
										if (kpos > 0)
										{
											kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
											if (lr.CommandType(nstr, "mul", "?"))
											{
												kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
												if (nstr.GetLength() > 0)
												{
													if (lr.Numeric(nstr))
														m_TriggerMultiplier = (" " + nstr);
												}
												if (kpos > 0)
												{
													kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
													if (nstr.GetLength() > 0)
													{
														if (lr.Numeric(nstr))
															m_DgPrescaler = (" " + nstr);
													}
												}
											}
											else
											{
												if (lr.Numeric(nstr))
													m_DgPrescaler = (" " + nstr);
											}
										}
									}
									else
									{
										if (lr.CommandType(nstr, "mul", "?"))
										{
											kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
											if (nstr.GetLength() > 0)
											{
												if (lr.Numeric(nstr))
													m_TriggerMultiplier = (" " + nstr);
											}
											if (kpos > 0)
											{
												kpos = lr.NextCharacterGroup(mstr, nstr, kpos);
												if (nstr.GetLength() > 0)
												{
													if (lr.Numeric(nstr))
														m_DgPrescaler = (" " + nstr);
												}
											}
										}
										else
										{
											if (lr.Numeric(nstr))
												m_DgPrescaler = (" " + nstr);
										}
									}
								}
							}
						}
						if (lr.CommandType(m_DgType, "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "BME_SG02P5", "?"))
						{
							if (lr.CommandType(lstr, "rsync", "?"))
								m_Resynch = TRUE;
						}
						if (lr.CommandType(m_DgType, "BME_G03V3", "BME_G03V4", "BME_G03V5",
																	"BME_G03P1", "BME_G03P2", 
																	"BME_G05V1", "BME_G05V2", "BME_G05V3",
																	"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																	"BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																	"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
						{
							if (lr.CommandType(lstr, "term", "?"))
								m_TriggerTerminate = TRUE;
							if (lr.CommandType(lstr, "gtrm", "?"))
								m_GateTerminate = TRUE;
							if (lr.CommandType(lstr, "usef", "?"))
								m_UseF = TRUE;
							if (lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?"))
							{
								if (lr.CommandType(lstr, "prim", "?"))
									m_PrimaryGo = TRUE;
								if (lr.CommandType(lstr, "scnd", "?"))
									m_SecondaryGo = TRUE;
								if (lr.CommandType(lstr, "frc", "?"))
									m_ForceGo = TRUE;
							}
							if (lr.CommandType(m_DgType, "BME_SG08P2", "?"))
							{
								if (lr.CommandType(lstr, "scnd", "?"))
									m_SecondaryGo = TRUE;
								if (lr.CommandType(lstr, "stbk", "?"))
									m_StepBackOnBus = TRUE;
								if (lr.CommandType(lstr, "strt", "?"))
									m_StartOnBus = TRUE;
								if (lr.CommandType(lstr, "inhb", "?"))
									m_InhibitOnBus = TRUE;
								if (lr.CommandType(lstr, "ldob", "?"))
									m_LoadDataOnBus = TRUE;
							}
							if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
							{
								if (lr.CommandType(lstr, "gmsn", "?"))
									m_GateMsN = TRUE;
								if (lr.CommandType(lstr, "gmsp", "?"))
									m_GateMsP = TRUE;
							}
							if (lr.CommandType(m_DgType, "BME_G05V3", "BME_G05P1", "BME_G05P2", 
								                  "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3",
																	"BME_G03V5", "BME_G03P1", "BME_G03P2", "BME_SG02V7",
																	"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
							{
								if (lr.CommandType(lstr, "TTL", "?"))
									m_TtlLevel = TRUE;
								if (lr.CommandType(lstr, "NIM", "?"))
									m_NimLevel = TRUE;
								if (lr.CommandType(lstr, "ECL", "?"))
									m_EclLevel = TRUE;
							}
						}
					}
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "T0", "?"))
		{
			kstr = lr.CommandParameters(jstr, "T0", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_T0_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_T0_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "hdrv", "sclk", "dclk", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_T0_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_T0_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_T0_Terminate = TRUE;
					if (lr.CommandType(lstr, "hdrv", "?"))
						m_T0_HighDrive = TRUE;
					if (lr.CommandType(lstr, "sclk", "?"))
						m_T0_Clock = TRUE;
					if (lr.CommandType(lstr, "dclk", "?"))
						m_T0_DelayClock = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "A", "?"))
		{
			kstr = lr.CommandParameters(jstr, "A", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_A_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_A_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "hdrv", "dclk", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_A_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_A_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_A_Terminate = TRUE;
					if (lr.CommandType(lstr, "hdrv", "?"))
						m_A_HighDrive = TRUE;
					if (lr.CommandType(lstr, "dclk", "?"))
						m_A_DelayClock = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "B", "?"))
		{
			kstr = lr.CommandParameters(jstr, "B", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_B_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_B_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "hdrv", "dclk", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_B_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_B_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_B_Terminate = TRUE;
					if (lr.CommandType(lstr, "hdrv", "?"))
						m_B_HighDrive = TRUE;
					if (lr.CommandType(lstr, "dclk", "?"))
						m_B_DelayClock = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "C", "?"))
		{
			kstr = lr.CommandParameters(jstr, "C", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_C_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_C_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_C_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_C_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_C_Terminate = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "D", "?"))
		{
			kstr = lr.CommandParameters(jstr, "D", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_D_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_D_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_D_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_D_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_D_Terminate = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "E", "?"))
		{
			kstr = lr.CommandParameters(jstr, "E", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_E_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_E_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "disc", "stbs", "inpos", "inneg", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_E_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_E_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_E_Terminate = TRUE;
					if (lr.CommandType(lstr, "disc", "?"))
						m_E_Disconnect = TRUE;
					if (lr.CommandType(lstr, "stbs", "?"))
						m_E_MsBus = TRUE;
					if (lr.CommandType(lstr, "inpos", "?"))
						m_E_InputP = TRUE;
					if (lr.CommandType(lstr, "inneg", "?"))
						m_E_InputN = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "F", "?"))
		{
			kstr = lr.CommandParameters(jstr, "F", "?");
			if (kstr.GetLength() > 0)
			{
				npos = lr.NextCharacterGroup(kstr, lstr, 1);
				if (!lr.CommandType(lstr, 1, TRUE, "positive", "negative", "?"))
				{
					lr.PreCommandPosition(kstr, m_F_Name, 1, TRUE, "positive", "negative", "?");
					lr.TrimString(m_F_Name);
				}
				npos = 1;
				while (npos > 0)
				{
					npos = lr.NextCommandPosition(kstr, lstr, npos, TRUE,
													"positive", "negative", "term", "disc", "stbs", "inpos", "inneg", "?");
					if (lr.CommandType(lstr, "positive", "?"))
						m_F_Positive = TRUE;
					if (lr.CommandType(lstr, "negative", "?"))
						m_F_Negative = TRUE;
					if (lr.CommandType(lstr, "term", "?"))
						m_F_Terminate = TRUE;
					if (lr.CommandType(lstr, "disc", "?"))
						m_F_Disconnect = TRUE;
					if (lr.CommandType(lstr, "stbs", "?"))
						m_F_MsBus = TRUE;
					if (lr.CommandType(lstr, "inpos", "?"))
						m_F_InputP = TRUE;
					if (lr.CommandType(lstr, "inneg", "?"))
						m_F_InputN = TRUE;
				}
			}
		}
		if (lr.CommandType(jstr, 1, TRUE, "pw", "?"))
		{
			kstr = lr.CommandParameters(jstr, "pw", "?");
			if (kstr.GetLength() > 0)
			{
				if (lr.Numeric(mstr))
					m_PulseWidth = (" " + kstr);
			}
		}
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

BOOL CDefineDelayGeneratorDlg::UpdateEditLine()
{
	if (!DiscretizeValues())
		return FALSE;
	CListRout lr;
	WorkLine = _T("");
	WorkLine += (m_DgType + "  ");
	while (WorkLine.GetLength() < 13)
		WorkLine += " ";
	lr.TrimString(m_DgAddress);
	if (m_DgAddress.GetLength() == 0)
	{
		if (lr.CommandType(m_DgType, "BME_G03P1", "BME_G03P2", 
			                        "BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
															"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			AfxMessageBox("please define a slot number!",MB_OK,0);
		}
		else
			AfxMessageBox("please define an address!",MB_OK,0);
		return FALSE;
	}	
	lr.TrimString(m_DgName);
	if (m_DgName.GetLength() > 0)
		WorkLine += (m_DgName + "   ");
	else
		WorkLine += " ";
	if (m_DgMaster)
		WorkLine += "master  ";
	else
		WorkLine += "slave  ";
	int BaseAddress,BusNumber;
	CString jstr;
	if (lr.CommandType(m_DgType, "BME_G03P1", "BME_G03P2", 
		                            "BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		BaseAddress = RoundInt(atof(m_DgAddress));
		lr.TrimString(m_DgBus);	
		if (m_DgBus.GetLength() == 0)
			jstr.Format("%2d -1 ", BaseAddress);
		else
		{
			BusNumber = RoundInt(atof(m_DgBus));
			jstr.Format("%2d %2d ", BaseAddress, BusNumber);
		}
		lr.TrimString(m_EthernetAddress);	
		if (m_EthernetAddress.GetLength() == 0)
			jstr += " ";
		else
			jstr += (m_EthernetAddress + " ");
	}
	else
	{
		BaseAddress = lr.ReadHexadecimalString((LPCTSTR)m_DgAddress);
		jstr.Format("0x%2x  ", BaseAddress);
	}
	WorkLine += jstr;
	if (lr.CommandType(m_DgType, "BME_G02V3", "BME_G03V3", "BME_G03V4", "BME_G03V5",
																"BME_G03P1", "BME_G03P2", 
																"BME_G05V1", "BME_G05V2", "BME_G05V3",
																"BME_G05P1", "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2",
																"BME_SG02V4", "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", "?"))
	{
		if (m_TriggerInput)
		{
			WorkLine += "trigger ";
			lr.TrimString(m_TriggerDivider);
			lr.TrimString(m_TriggerMultiplier);
			if (m_TriggerDivider.GetLength() > 0)
				WorkLine += (m_TriggerDivider + " ");
			else
			{
				if (m_TriggerMultiplier.GetLength() == 0)
					WorkLine += "6 ";
				else
				{
					if (RoundInt(atof(m_TriggerMultiplier)) <= 1)
						WorkLine += "6 ";
				}
			}
			if (m_TriggerMultiplier.GetLength() > 0)
			{
				if (RoundInt(atof(m_TriggerMultiplier)) > 1)
					WorkLine += "mul " + m_TriggerMultiplier + " ";
			}
		}
		if (m_CrystalOscillator)
		{
			WorkLine += "crystal ";
			lr.TrimString(m_DgPrescaler);
			if (m_DgPrescaler.GetLength() > 0)
				WorkLine += (m_DgPrescaler + " ");
			else
			{
				if (lr.CommandType(m_DgType, "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																			"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5", 
																			"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?"))
					WorkLine += "8 ";
				else
				{
					if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
						WorkLine += "16 ";
					else
						WorkLine += "1 ";
				}
			}
		}
		if (m_MsBusClock)
		{
			WorkLine += "msbus ";
			lr.TrimString(m_DgPrescaler);
			if (m_DgPrescaler.GetLength() > 0)
				WorkLine += (m_DgPrescaler + " ");
			else
				WorkLine += "1 ";
		}
		if (m_FreeRunning)
		{
			WorkLine += "switch ";
			lr.TrimString(m_DgPrescaler);
			lr.TrimString(m_TriggerDivider);
			lr.TrimString(m_TriggerMultiplier);
			if (m_TriggerDivider.GetLength() > 0)
				WorkLine += (m_TriggerDivider + " ");
			else
			{
				if (m_TriggerMultiplier.GetLength() == 0)
					WorkLine += "6 ";
			}
			if (m_TriggerMultiplier.GetLength() > 0)
			{
				if (RoundInt(atof(m_TriggerMultiplier)) > 1)
					WorkLine += "mul " + m_TriggerMultiplier + " ";
			}
			if (m_DgPrescaler.GetLength() > 0)
				WorkLine += (m_DgPrescaler + " ");
			else
			{
				if (lr.CommandType(m_DgType, "BME_SG02V5", "BME_SG02V6", "BME_SG02V7",
																			"BME_SG02P1", "BME_SG02P2", "BME_SG02P3", "BME_SG02P4", "BME_SG02P5",
																			"BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?"))
					WorkLine += "8 ";
				else
				{
					if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
						WorkLine += "16 ";
					else
						WorkLine += "1 ";
				}
			}
		}
		if (lr.CommandType(m_DgType, "BME_G05P3", "BME_SG05P2", "BME_SG05P3", "BME_SG08P1", "BME_SG08P2", "BME_SG02P4", "BME_SG02P5", "?"))
		{
			if (m_Resynch)
				WorkLine += ("rsync ");
		}
		WorkLine += (" ");
	}
	if (m_TriggerTerminate)
		WorkLine += "term  ";
	if (m_GateTerminate)
		WorkLine += "gtrm ";
	if (m_UseF)
		WorkLine += "usef ";
	WorkLine += (" ");
	if (lr.CommandType(m_DgType, "BME_G05P2", "BME_G05P3", "BME_SG05P1", "BME_SG05P2", "BME_SG05P3", "?"))
	{
		if (m_PrimaryGo)
			WorkLine += "prim ";
		if (m_SecondaryGo)
			WorkLine += "scnd ";
		if (m_ForceGo)
			WorkLine += "frc ";
		WorkLine += " ";
	}
	if (lr.CommandType(m_DgType, "BME_SG08P2", "?"))
	{
		if (m_SecondaryGo)
			WorkLine += "scnd ";
		if (m_StepBackOnBus)
			WorkLine += "stbk ";
		if (m_StartOnBus)
			WorkLine += "strt ";
		if (m_InhibitOnBus)
			WorkLine += "inhb ";
		if (m_LoadDataOnBus)
			WorkLine += "ldob ";
		WorkLine += " ";
	}
	if (lr.CommandType(m_DgType, "BME_SG08P1", "BME_SG08P2", "?"))
	{
		if (m_GateMsN)
			WorkLine += "gmsn ";
		if (m_GateMsP)
			WorkLine += "gmsp ";
		WorkLine += " ";
	}
	if (m_TtlLevel)
		WorkLine += "TTL  ";
	if (m_NimLevel)
		WorkLine += "NIM  ";
	if (m_EclLevel)
		WorkLine += "ECL  ";
	lr.TrimString(m_T0_Name);
	if ((m_T0_Name.GetLength() > 0) || (m_T0_Positive) || (m_T0_Negative) || 
																(m_T0_Terminate) || (m_T0_HighDrive) || (m_T0_DelayClock))
	{
		WorkLine += "T0  ";
		if (m_T0_Name.GetLength() > 0)
			WorkLine += (m_T0_Name + "  ");
		if (m_T0_Positive)
			WorkLine += "positive ";
		if (m_T0_Negative)
			WorkLine += "negative ";
		if (m_T0_Terminate)
			WorkLine += "term ";
		if (m_T0_HighDrive)
			WorkLine += "hdrv ";
		if (m_T0_Clock)
			WorkLine += "sclk ";
		if (m_T0_DelayClock)
			WorkLine += "dclk ";
		WorkLine += "  ";
	}
	lr.TrimString(m_A_Name);
	if ((m_A_Name.GetLength() > 0) || (m_A_Positive) || (m_A_Negative) || 
															(m_A_Terminate) || (m_A_HighDrive) || (m_A_DelayClock))
	{
		WorkLine += "A  ";
		if (m_A_Name.GetLength() > 0)
			WorkLine += (m_A_Name + "  ");
		if (m_A_Positive)
			WorkLine += "positive ";
		if (m_A_Negative)
			WorkLine += "negative ";
		if (m_A_Terminate)
			WorkLine += "term ";
		if (m_A_HighDrive)
			WorkLine += "hdrv ";
		if (m_A_DelayClock)
			WorkLine += "dclk ";
		WorkLine += "  ";
	}
	lr.TrimString(m_B_Name);
	if ((m_B_Name.GetLength() > 0) || (m_B_Positive) || (m_B_Negative) || 
																(m_B_Terminate) || (m_B_HighDrive) || (m_B_DelayClock))
	{
		WorkLine += "B  ";
		if (m_B_Name.GetLength() > 0)
			WorkLine += (m_B_Name + "  ");
		if (m_B_Positive)
			WorkLine += "positive ";
		if (m_B_Negative)
			WorkLine += "negative ";
		if (m_B_Terminate)
			WorkLine += "term ";
		if (m_B_HighDrive)
			WorkLine += "hdrv ";
		if (m_B_DelayClock)
			WorkLine += "dclk ";
		WorkLine += "  ";
	}
	lr.TrimString(m_C_Name);
	if ((m_C_Name.GetLength() > 0) || (m_C_Positive) || (m_C_Negative) || (m_C_Terminate))
	{
		WorkLine += "C  ";
		if (m_C_Name.GetLength() > 0)
			WorkLine += (m_C_Name + "  ");
		if (m_C_Positive)
			WorkLine += "positive ";
		if (m_C_Negative)
			WorkLine += "negative ";
		if (m_C_Terminate)
			WorkLine += "term ";
		WorkLine += "  ";
	}
	lr.TrimString(m_D_Name);
	if ((m_D_Name.GetLength() > 0) || (m_D_Positive) || (m_D_Negative) || (m_D_Terminate))
	{
		WorkLine += "D  ";
		if (m_D_Name.GetLength() > 0)
			WorkLine += (m_D_Name + "  ");
		if (m_D_Positive)
			WorkLine += "positive ";
		if (m_D_Negative)
			WorkLine += "negative ";
		if (m_D_Terminate)
			WorkLine += "term ";
		WorkLine += "  ";
	}
	lr.TrimString(m_E_Name);
	if ((m_E_Name.GetLength() > 0) || (m_E_Positive) || (m_E_Negative) || (m_E_Terminate) || 
														(m_E_Disconnect) || (m_E_MsBus) || (m_E_InputP) || (m_E_InputN))
	{
		WorkLine += "E  ";
		if (m_E_Name.GetLength() > 0)
			WorkLine += (m_E_Name + "  ");
		if (m_E_Positive)
			WorkLine += "positive ";
		if (m_E_Negative)
			WorkLine += "negative ";
		if (m_E_Terminate)
			WorkLine += "term ";
		if (m_E_Disconnect)
			WorkLine += "disc ";
		if (m_E_MsBus)
			WorkLine += "stbs ";
		if (m_E_InputP)
			WorkLine += "inpos ";
		if (m_E_InputN)
			WorkLine += "inneg ";
		WorkLine += "  ";
	}
	lr.TrimString(m_F_Name);
	if ((m_F_Name.GetLength() > 0) || (m_F_Positive) || (m_F_Negative) || (m_F_Terminate) || 
														(m_F_Disconnect) || (m_F_MsBus) || (m_F_InputP) || (m_F_InputN))
	{
		WorkLine += "F  ";
		if (m_F_Name.GetLength() > 0)
			WorkLine += (m_F_Name + "  ");
		if (m_F_Positive)
			WorkLine += "positive ";
		if (m_F_Negative)
			WorkLine += "negative ";
		if (m_F_Terminate)
			WorkLine += "term ";
		if (m_F_Disconnect)
			WorkLine += "disc ";
		if (m_F_MsBus)
			WorkLine += "stbs ";
		if (m_F_InputP)
			WorkLine += "inpos ";
		if (m_F_InputN)
			WorkLine += "inneg ";
		WorkLine += "  ";
	}
	lr.TrimString(m_PulseWidth);
	if (m_PulseWidth.GetLength() > 0)
		WorkLine += ("pw " + m_PulseWidth);
	lr.TrimString(WorkLine);
	return TRUE;
}
