// G05p4MasterPP.cpp : implementation file
//


#include "stdafx.h"
#include "BME_G0X.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "G05p4MasterPP.h"
#include "..\Spectra_BME\ListRout.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CG05p4MasterPP property page

IMPLEMENT_DYNCREATE(CG05p4MasterPP, CPropertyPage)

CG05p4MasterPP::CG05p4MasterPP() : CPropertyPage(CG05p4MasterPP::IDD)
{
	//{{AFX_DATA_INIT(CG05p4MasterPP)
	m_DelayA = _T("");
	m_DelayB = _T("");
	m_DelayC = _T("");
	m_DelayD = _T("");
	m_DelayE = _T("");
	m_DelayF = _T("");
	m_WidthA = _T("");
	m_WidthB = _T("");
	m_WidthC = _T("");
	m_WidthD = _T("");
	m_WidthE = _T("");
	m_WidthF = _T("");
	m_ModuloA = _T("");
	m_ModuloB = _T("");
	m_ModuloC = _T("");
	m_ModuloD = _T("");
	m_ModuloE = _T("");
	m_ModuloF = _T("");
	m_OffsetA = _T("");
	m_OffsetB = _T("");
	m_OffsetC = _T("");
	m_OffsetD = _T("");
	m_OffsetE = _T("");
	m_OffsetF = _T("");
	m_TriggerCount = _T("");
	m_ExtFrequency = _T("");
	m_InhibitTrigger = _T("");
	m_InhibitSecondary = _T("");
	m_DelaySecondary = _T("");
	m_ForceTrigger = _T("");
	m_Burst = _T("");
	m_TriggerLevel = _T("");
	m_GateDivider = _T("");
	m_GateLevel = _T("");
	m_GateDelay = _T("");
	m_ReadTriggers = FALSE;
	m_PresetValue = _T("");
	m_StopOnPreset = FALSE;
	m_External = FALSE;
	m_Rising = FALSE;
	m_Falling = FALSE;
	m_Internal = FALSE;
	m_GatePositive = FALSE;
	m_GateNegative = FALSE;
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	m_SynchronizeGate = FALSE;
	m_GateAB = FALSE;
	m_AB_Xor = FALSE;
	m_AB_Or = FALSE;
	m_AB_And = FALSE;
	m_GateCD = FALSE;
	m_CD_Xor = FALSE;
	m_CD_Or = FALSE;
	m_CD_And = FALSE;
	m_GateEF = FALSE;
	m_EF_Xor = FALSE;
	m_EF_Or = FALSE;
	m_EF_And = FALSE;
	m_PrimaryLocalA = FALSE;
	m_SecondaryLocalA = FALSE;
	m_ForceLocalA = FALSE;
	m_PrimaryBusA = FALSE;
	m_SecondaryBusA = FALSE;
	m_ForceBusA = FALSE;
	m_PrimaryLocalB = FALSE;
	m_SecondaryLocalB = FALSE;
	m_ForceLocalB = FALSE;
	m_PrimaryBusB = FALSE;
	m_SecondaryBusB = FALSE;
	m_ForceBusB = FALSE;
	m_PrimaryLocalC = FALSE;
	m_SecondaryLocalC = FALSE;
	m_ForceLocalC = FALSE;
	m_PrimaryBusC = FALSE;
	m_SecondaryBusC = FALSE;
	m_ForceBusC = FALSE;
	m_PrimaryLocalD = FALSE;
	m_SecondaryLocalD = FALSE;
	m_ForceLocalD = FALSE;
	m_PrimaryBusD = FALSE;
	m_SecondaryBusD = FALSE;
	m_ForceBusD = FALSE;
	m_PrimaryLocalE = FALSE;
	m_SecondaryLocalE = FALSE;
	m_ForceLocalE = FALSE;
	m_PrimaryBusE = FALSE;
	m_SecondaryBusE = FALSE;
	m_ForceBusE = FALSE;
	m_PrimaryLocalF = FALSE;
	m_SecondaryLocalF = FALSE;
	m_ForceLocalF = FALSE;
	m_PrimaryBusF = FALSE;
	m_SecondaryBusF = FALSE;
	m_ForceBusF = FALSE;
	m_StbkLocA = FALSE;
	m_StbkBusA = FALSE;
	m_StbkRefA = _T("");
	m_StbkLocB = FALSE;
	m_StbkBusB = FALSE;
	m_StbkRefB = _T("");
	m_StbkLocC = FALSE;
	m_StbkBusC = FALSE;
	m_StbkRefC = _T("");
	m_StbkLocD = FALSE;
	m_StbkBusD = FALSE;
	m_StbkRefD = _T("");
	m_StbkLocE = FALSE;
	m_StbkBusE = FALSE;
	m_StbkRefE = _T("");
	m_StbkLocF = FALSE;
	m_StbkBusF = FALSE;
	m_StbkRefF = _T("");
	m_StepBack = _T("");
	m_StartLocA = FALSE;
	m_StartBusA = FALSE;
	m_CircleA = FALSE;
	m_StartLocB = FALSE;
	m_StartBusB = FALSE;
	m_CircleB = FALSE;
	m_StartLocC = FALSE;
	m_StartBusC = FALSE;
	m_CircleC = FALSE;
	m_StartLocD = FALSE;
	m_StartBusD = FALSE;
	m_CircleD = FALSE;
	m_StartLocE = FALSE;
	m_StartBusE = FALSE;
	m_CircleE = FALSE;
	m_StartLocF = FALSE;
	m_StartBusF = FALSE;
	m_CircleF = FALSE;
	m_E_EnaA = FALSE;
	m_F_EnaA = FALSE;
	m_BusEnaA = FALSE;
	m_E_EnaB = FALSE;
	m_F_EnaB = FALSE;
	m_BusEnaB = FALSE;
	m_E_EnaC = FALSE;
	m_F_EnaC = FALSE;
	m_BusEnaC = FALSE;
	m_E_EnaD = FALSE;
	m_F_EnaD = FALSE;
	m_BusEnaD = FALSE;
	m_E_EnaE = FALSE;
	m_F_EnaE = FALSE;
	m_BusEnaE = FALSE;
	m_E_EnaF = FALSE;
	m_F_EnaF = FALSE;
	m_BusEnaF = FALSE;
	m_InhibitA = FALSE;
	m_InhibitB = FALSE;
	m_InhibitC = FALSE;
	m_InhibitD = FALSE;
	m_InhibitE = FALSE;
	m_InhibitF = FALSE;
	m_SynchA = FALSE;
	m_SynchB = FALSE;
	m_SynchC = FALSE;
	m_SynchD = FALSE;
	m_SynchE = FALSE;
	m_SynchF = FALSE;
	m_SynchBurst = FALSE;
	m_A_Name = _T("");
	m_B_Name = _T("");
	m_C_Name = _T("");
	m_D_Name = _T("");
	m_E_Name = _T("");
	m_F_Name = _T("");
	//}}AFX_DATA_INIT
	b_RequestZeroCounter = FALSE;
	b_RequestZeroModulo = FALSE;
	b_RequestJumpStart = FALSE;
	b_ForceTriggerActive = FALSE;
	b_CrystalOscillator = FALSE;
	b_Master = FALSE;
	b_FastApply = FALSE;
	b_PageActive = FALSE;
	m_ClockSource = -1;
	m_DG_Number = -1;
	m_DG_Product = -1;
	A_Name = _T("");
	B_Name = _T("");
	C_Name = _T("");
	D_Name = _T("");
	E_Name = _T("");
	F_Name = _T("");
	GoSignal_A = 0x0;
	GoSignal_B = 0x0;
	GoSignal_C = 0x0;
	GoSignal_D = 0x0;
	GoSignal_E = 0x0;
	GoSignal_F = 0x0;
}

CG05p4MasterPP::~CG05p4MasterPP()
{
}

void CG05p4MasterPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG05p4MasterPP)
	DDX_Control(pDX, IDC_DELAY_A, m_Delay_AED);
	DDX_Control(pDX, IDC_DELAY_B, m_Delay_BED);
	DDX_Control(pDX, IDC_DELAY_C, m_Delay_CED);
	DDX_Control(pDX, IDC_DELAY_D, m_Delay_DED);
	DDX_Control(pDX, IDC_DELAY_E, m_Delay_EED);
	DDX_Control(pDX, IDC_DELAY_F, m_Delay_FED);
	DDX_Control(pDX, IDC_WIDTH_A, m_Width_AED);
	DDX_Control(pDX, IDC_WIDTH_B, m_Width_BED);
	DDX_Control(pDX, IDC_WIDTH_C, m_Width_CED);
	DDX_Control(pDX, IDC_WIDTH_D, m_Width_DED);
	DDX_Control(pDX, IDC_WIDTH_E, m_Width_EED);
	DDX_Control(pDX, IDC_WIDTH_F, m_Width_FED);
	DDX_Control(pDX, IDC_MODULO_A, m_ModuloAED);
	DDX_Control(pDX, IDC_MODULO_B, m_ModuloBED);
	DDX_Control(pDX, IDC_MODULO_C, m_ModuloCED);
	DDX_Control(pDX, IDC_MODULO_D, m_ModuloDED);
	DDX_Control(pDX, IDC_MODULO_E, m_ModuloEED);
	DDX_Control(pDX, IDC_MODULO_F, m_ModuloFED);
	DDX_Control(pDX, IDC_OFFSET_A, m_OffsetAED);
	DDX_Control(pDX, IDC_OFFSET_B, m_OffsetBED);
	DDX_Control(pDX, IDC_OFFSET_C, m_OffsetCED);
	DDX_Control(pDX, IDC_OFFSET_D, m_OffsetDED);
	DDX_Control(pDX, IDC_OFFSET_E, m_OffsetEED);
	DDX_Control(pDX, IDC_OFFSET_F, m_OffsetFED);
	DDX_Control(pDX, IDC_INHIBIT_TRIGGER, m_InhibitTriggerED);
	DDX_Control(pDX, IDC_INHIBIT_SECONDARY, m_InhibitSecondaryED);
	DDX_Control(pDX, IDC_DELAY_SECONDARY, m_DelaySecondaryED);
	DDX_Control(pDX, IDC_STEP_BACK, m_StepBackED);
	DDX_Control(pDX, IDC_FORCE_TRIGGER, m_ForceTriggerED);
	DDX_Control(pDX, IDC_BURST, m_BurstED);
	DDX_Control(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevelED);
	DDX_Control(pDX, IDC_PRESET_VALUE, m_PresetValueED);
	DDX_Check(pDX, IDC_STOP_ON_PRESET, m_StopOnPreset);
	DDX_Control(pDX, IDC_GATE_DIVIDER, m_GateDividerED);
	DDX_Control(pDX, IDC_GATE_LEVEL, m_GateLevelED);
	DDX_Control(pDX, IDC_GATE_DELAY, m_GateDelayED);
	DDX_Control(pDX, IDC_INHIBIT_B, m_InhibitBB);
	DDX_Control(pDX, IDC_INHIBIT_A, m_InhibitAB);
	DDX_Control(pDX, IDC_INHIBIT_C, m_InhibitCB);
	DDX_Control(pDX, IDC_INHIBIT_D, m_InhibitDB);
	DDX_Control(pDX, IDC_INHIBIT_E, m_InhibitEB);
	DDX_Control(pDX, IDC_INHIBIT_F, m_InhibitFB);
	DDX_Control(pDX, IDC_SYNCH_A, m_SynchAB);
	DDX_Control(pDX, IDC_SYNCH_B, m_SynchBB);
	DDX_Control(pDX, IDC_SYNCH_C, m_SynchCB);
	DDX_Control(pDX, IDC_SYNCH_D, m_SynchDB);
	DDX_Control(pDX, IDC_SYNCH_E, m_SynchEB);
	DDX_Control(pDX, IDC_SYNCH_F, m_SynchFB);
	DDX_Control(pDX, IDC_SYNCH_BURST, m_SynchBurstB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_A, m_SecondaryLocalAB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_B, m_SecondaryLocalBB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_C, m_SecondaryLocalCB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_D, m_SecondaryLocalDB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_E, m_SecondaryLocalEB);
	DDX_Control(pDX, IDC_SECONDARY_LOCAL_F, m_SecondaryLocalFB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_A, m_SecondaryBusAB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_B, m_SecondaryBusBB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_C, m_SecondaryBusCB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_D, m_SecondaryBusDB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_E, m_SecondaryBusEB);
	DDX_Control(pDX, IDC_SECONDARY_BUS_F, m_SecondaryBusFB);
	DDX_Control(pDX, IDC_RISING, m_RisingB);
	DDX_Control(pDX, IDC_FALLING, m_FallingB);
	DDX_Control(pDX, IDC_EXTERNAL, m_ExternalB);
	DDX_Control(pDX, IDC_DESIGNATOR, m_Designator);
	DDX_Text(pDX, IDC_DELAY_A, m_DelayA);
	DDV_MaxChars(pDX, m_DelayA, 32);
	DDX_Text(pDX, IDC_DELAY_B, m_DelayB);
	DDV_MaxChars(pDX, m_DelayB, 32);
	DDX_Text(pDX, IDC_DELAY_C, m_DelayC);
	DDV_MaxChars(pDX, m_DelayC, 32);
	DDX_Text(pDX, IDC_DELAY_D, m_DelayD);
	DDV_MaxChars(pDX, m_DelayD, 32);
	DDX_Text(pDX, IDC_DELAY_E, m_DelayE);
	DDV_MaxChars(pDX, m_DelayE, 32);
	DDX_Text(pDX, IDC_DELAY_F, m_DelayF);
	DDV_MaxChars(pDX, m_DelayF, 32);
	DDX_Text(pDX, IDC_WIDTH_A, m_WidthA);
	DDV_MaxChars(pDX, m_WidthA, 32);
	DDX_Text(pDX, IDC_WIDTH_B, m_WidthB);
	DDV_MaxChars(pDX, m_WidthB, 32);
	DDX_Text(pDX, IDC_WIDTH_C, m_WidthC);
	DDV_MaxChars(pDX, m_WidthC, 32);
	DDX_Text(pDX, IDC_WIDTH_D, m_WidthD);
	DDV_MaxChars(pDX, m_WidthD, 32);
	DDX_Text(pDX, IDC_WIDTH_E, m_WidthE);
	DDV_MaxChars(pDX, m_WidthE, 32);
	DDX_Text(pDX, IDC_WIDTH_F, m_WidthF);
	DDV_MaxChars(pDX, m_WidthF, 32);
	DDX_Text(pDX, IDC_MODULO_A, m_ModuloA);
	DDV_MaxChars(pDX, m_ModuloA, 16);
	DDX_Text(pDX, IDC_MODULO_B, m_ModuloB);
	DDV_MaxChars(pDX, m_ModuloB, 16);
	DDX_Text(pDX, IDC_MODULO_C, m_ModuloC);
	DDV_MaxChars(pDX, m_ModuloC, 16);
	DDX_Text(pDX, IDC_MODULO_D, m_ModuloD);
	DDV_MaxChars(pDX, m_ModuloD, 16);
	DDX_Text(pDX, IDC_MODULO_E, m_ModuloE);
	DDV_MaxChars(pDX, m_ModuloE, 16);
	DDX_Text(pDX, IDC_MODULO_F, m_ModuloF);
	DDV_MaxChars(pDX, m_ModuloF, 16);
	DDX_Text(pDX, IDC_OFFSET_A, m_OffsetA);
	DDV_MaxChars(pDX, m_OffsetA, 16);
	DDX_Text(pDX, IDC_OFFSET_B, m_OffsetB);
	DDV_MaxChars(pDX, m_OffsetB, 16);
	DDX_Text(pDX, IDC_OFFSET_C, m_OffsetC);
	DDV_MaxChars(pDX, m_OffsetC, 16);
	DDX_Text(pDX, IDC_OFFSET_D, m_OffsetD);
	DDV_MaxChars(pDX, m_OffsetD, 16);
	DDX_Text(pDX, IDC_OFFSET_E, m_OffsetE);
	DDV_MaxChars(pDX, m_OffsetE, 16);
	DDX_Text(pDX, IDC_OFFSET_F, m_OffsetF);
	DDV_MaxChars(pDX, m_OffsetF, 16);
	DDX_Text(pDX, IDC_PRESET_VALUE, m_PresetValue);
	DDV_MaxChars(pDX, m_PresetValue, 32);
	DDX_Text(pDX, IDC_INHIBIT_TRIGGER, m_InhibitTrigger);
	DDV_MaxChars(pDX, m_InhibitTrigger, 32);
	DDX_Text(pDX, IDC_INHIBIT_SECONDARY, m_InhibitSecondary);
	DDV_MaxChars(pDX, m_InhibitSecondary, 32);
	DDX_Text(pDX, IDC_DELAY_SECONDARY, m_DelaySecondary);
	DDV_MaxChars(pDX, m_DelaySecondary, 16);
	DDX_Text(pDX, IDC_FORCE_TRIGGER, m_ForceTrigger);
	DDV_MaxChars(pDX, m_ForceTrigger, 32);
	DDX_Text(pDX, IDC_BURST, m_Burst);
	DDV_MaxChars(pDX, m_Burst, 16);
	DDX_Check(pDX, IDC_READ_TRIGGERS, m_ReadTriggers);
	DDX_Text(pDX, IDC_TRIGGER_COUNT, m_TriggerCount);
	DDV_MaxChars(pDX, m_TriggerCount, 32);
	DDX_Text(pDX, IDC_EXT_FREQUENCY, m_ExtFrequency);
	DDV_MaxChars(pDX, m_ExtFrequency, 32);
	DDX_Text(pDX, IDC_GATE_DIVIDER, m_GateDivider);
	DDV_MaxChars(pDX, m_GateDivider, 16);
	DDX_Text(pDX, IDC_GATE_LEVEL, m_GateLevel);
	DDV_MaxChars(pDX, m_GateLevel, 16);
	DDX_Text(pDX, IDC_GATE_DELAY, m_GateDelay);
	DDV_MaxChars(pDX, m_GateDelay, 16);
	DDX_Text(pDX, IDC_TRIGGER_LEVEL, m_TriggerLevel);
	DDV_MaxChars(pDX, m_TriggerLevel, 16);
	DDX_Check(pDX, IDC_EXTERNAL, m_External);
	DDX_Check(pDX, IDC_FALLING, m_Falling);
	DDX_Check(pDX, IDC_RISING, m_Rising);
	DDX_Check(pDX, IDC_INTERNAL, m_Internal);
	DDX_Check(pDX, IDC_IGNORE, m_Ignore);
	DDX_Check(pDX, IDC_MEMORIZE, m_Memorize);	
	DDX_Check(pDX, IDC_SYNCHRONIZE_GATE, m_SynchronizeGate);
	DDX_Check(pDX, IDC_GATE_POSITIVE, m_GatePositive);
	DDX_Check(pDX, IDC_GATE_NEGATIVE, m_GateNegative);
	DDX_Check(pDX, IDC_GATE_AB, m_GateAB);
	DDX_Check(pDX, IDC_AB_XOR, m_AB_Xor);
	DDX_Check(pDX, IDC_AB_OR, m_AB_Or);
	DDX_Check(pDX, IDC_AB_AND, m_AB_And);
	DDX_Check(pDX, IDC_GATE_CD, m_GateCD);
	DDX_Check(pDX, IDC_CD_XOR, m_CD_Xor);
	DDX_Check(pDX, IDC_CD_OR, m_CD_Or);
	DDX_Check(pDX, IDC_CD_AND, m_CD_And);
	DDX_Check(pDX, IDC_GATE_EF, m_GateEF);
	DDX_Check(pDX, IDC_EF_XOR, m_EF_Xor);
	DDX_Check(pDX, IDC_EF_OR, m_EF_Or);
	DDX_Check(pDX, IDC_EF_AND, m_EF_And);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_A, m_PrimaryLocalA);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_A, m_SecondaryLocalA);
	DDX_Check(pDX, IDC_FORCE_LOCAL_A, m_ForceLocalA);
	DDX_Check(pDX, IDC_PRIMARY_BUS_A, m_PrimaryBusA);
	DDX_Check(pDX, IDC_SECONDARY_BUS_A, m_SecondaryBusA);
	DDX_Check(pDX, IDC_FORCE_BUS_A, m_ForceBusA);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_B, m_PrimaryLocalB);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_B, m_SecondaryLocalB);
	DDX_Check(pDX, IDC_FORCE_LOCAL_B, m_ForceLocalB);
	DDX_Check(pDX, IDC_PRIMARY_BUS_B, m_PrimaryBusB);
	DDX_Check(pDX, IDC_SECONDARY_BUS_B, m_SecondaryBusB);
	DDX_Check(pDX, IDC_FORCE_BUS_B, m_ForceBusB);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_C, m_PrimaryLocalC);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_C, m_SecondaryLocalC);
	DDX_Check(pDX, IDC_FORCE_LOCAL_C, m_ForceLocalC);
	DDX_Check(pDX, IDC_PRIMARY_BUS_C, m_PrimaryBusC);
	DDX_Check(pDX, IDC_SECONDARY_BUS_C, m_SecondaryBusC);
	DDX_Check(pDX, IDC_FORCE_BUS_C, m_ForceBusC);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_D, m_PrimaryLocalD);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_D, m_SecondaryLocalD);
	DDX_Check(pDX, IDC_FORCE_LOCAL_D, m_ForceLocalD);
	DDX_Check(pDX, IDC_PRIMARY_BUS_D, m_PrimaryBusD);
	DDX_Check(pDX, IDC_SECONDARY_BUS_D, m_SecondaryBusD);
	DDX_Check(pDX, IDC_FORCE_BUS_D, m_ForceBusD);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_E, m_PrimaryLocalE);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_E, m_SecondaryLocalE);
	DDX_Check(pDX, IDC_FORCE_LOCAL_E, m_ForceLocalE);
	DDX_Check(pDX, IDC_PRIMARY_BUS_E, m_PrimaryBusE);
	DDX_Check(pDX, IDC_SECONDARY_BUS_E, m_SecondaryBusE);
	DDX_Check(pDX, IDC_FORCE_BUS_E, m_ForceBusE);
	DDX_Check(pDX, IDC_PRIMARY_LOCAL_F, m_PrimaryLocalF);
	DDX_Check(pDX, IDC_SECONDARY_LOCAL_F, m_SecondaryLocalF);
	DDX_Check(pDX, IDC_FORCE_LOCAL_F, m_ForceLocalF);
	DDX_Check(pDX, IDC_PRIMARY_BUS_F, m_PrimaryBusF);
	DDX_Check(pDX, IDC_SECONDARY_BUS_F, m_SecondaryBusF);
	DDX_Check(pDX, IDC_FORCE_BUS_F, m_ForceBusF);
	DDX_Check(pDX, IDC_STBK_LOC_A, m_StbkLocA);
	DDX_Check(pDX, IDC_STBK_BUS_A, m_StbkBusA);
	DDX_Text(pDX, IDC_STBK_REF_A, m_StbkRefA);
	DDV_MaxChars(pDX, m_StbkRefA, 4);
	DDX_Check(pDX, IDC_STBK_LOC_B, m_StbkLocB);
	DDX_Check(pDX, IDC_STBK_BUS_B, m_StbkBusB);
	DDX_Text(pDX, IDC_STBK_REF_B, m_StbkRefB);
	DDV_MaxChars(pDX, m_StbkRefB, 4);
	DDX_Check(pDX, IDC_STBK_LOC_C, m_StbkLocC);
	DDX_Check(pDX, IDC_STBK_BUS_C, m_StbkBusC);
	DDX_Text(pDX, IDC_STBK_REF_C, m_StbkRefC);
	DDV_MaxChars(pDX, m_StbkRefC, 4);
	DDX_Check(pDX, IDC_STBK_LOC_D, m_StbkLocD);
	DDX_Check(pDX, IDC_STBK_BUS_D, m_StbkBusD);
	DDX_Text(pDX, IDC_STBK_REF_D, m_StbkRefD);
	DDV_MaxChars(pDX, m_StbkRefD, 4);
	DDX_Check(pDX, IDC_STBK_LOC_E, m_StbkLocE);
	DDX_Check(pDX, IDC_STBK_BUS_E, m_StbkBusE);
	DDX_Text(pDX, IDC_STBK_REF_E, m_StbkRefE);
	DDV_MaxChars(pDX, m_StbkRefE, 4);
	DDX_Check(pDX, IDC_STBK_LOC_F, m_StbkLocF);
	DDX_Check(pDX, IDC_STBK_BUS_F, m_StbkBusF);
	DDX_Text(pDX, IDC_STBK_REF_F, m_StbkRefF);
	DDV_MaxChars(pDX, m_StbkRefF, 4);
	DDX_Text(pDX, IDC_STEP_BACK, m_StepBack);
	DDV_MaxChars(pDX, m_StepBack, 32);
	DDX_Check(pDX, IDC_START_LOC_A, m_StartLocA);
	DDX_Check(pDX, IDC_START_BUS_A, m_StartBusA);
	DDX_Check(pDX, IDC_CIRCLE_A, m_CircleA);
	DDX_Check(pDX, IDC_START_LOC_B, m_StartLocB);
	DDX_Check(pDX, IDC_START_BUS_B, m_StartBusB);
	DDX_Check(pDX, IDC_CIRCLE_B, m_CircleB);
	DDX_Check(pDX, IDC_START_LOC_C, m_StartLocC);
	DDX_Check(pDX, IDC_START_BUS_C, m_StartBusC);
	DDX_Check(pDX, IDC_CIRCLE_C, m_CircleC);
	DDX_Check(pDX, IDC_START_LOC_D, m_StartLocD);
	DDX_Check(pDX, IDC_START_BUS_D, m_StartBusD);
	DDX_Check(pDX, IDC_CIRCLE_D, m_CircleD);
	DDX_Check(pDX, IDC_START_LOC_E, m_StartLocE);
	DDX_Check(pDX, IDC_START_BUS_E, m_StartBusE);
	DDX_Check(pDX, IDC_CIRCLE_E, m_CircleE);
	DDX_Check(pDX, IDC_START_LOC_F, m_StartLocF);
	DDX_Check(pDX, IDC_START_BUS_F, m_StartBusF);
	DDX_Check(pDX, IDC_CIRCLE_F, m_CircleF);
	DDX_Check(pDX, IDC_E_ENA_A, m_E_EnaA);
	DDX_Check(pDX, IDC_F_ENA_A, m_F_EnaA);
	DDX_Check(pDX, IDC_BUS_ENA_A, m_BusEnaA);
	DDX_Check(pDX, IDC_E_ENA_B, m_E_EnaB);
	DDX_Check(pDX, IDC_F_ENA_B, m_F_EnaB);
	DDX_Check(pDX, IDC_BUS_ENA_B, m_BusEnaB);
	DDX_Check(pDX, IDC_E_ENA_C, m_E_EnaC);
	DDX_Check(pDX, IDC_F_ENA_C, m_F_EnaC);
	DDX_Check(pDX, IDC_BUS_ENA_C, m_BusEnaC);
	DDX_Check(pDX, IDC_E_ENA_D, m_E_EnaD);
	DDX_Check(pDX, IDC_F_ENA_D, m_F_EnaD);
	DDX_Check(pDX, IDC_BUS_ENA_D, m_BusEnaD);
	DDX_Check(pDX, IDC_E_ENA_E, m_E_EnaE);
	DDX_Check(pDX, IDC_F_ENA_E, m_F_EnaE);
	DDX_Check(pDX, IDC_BUS_ENA_E, m_BusEnaE);
	DDX_Check(pDX, IDC_E_ENA_F, m_E_EnaF);
	DDX_Check(pDX, IDC_F_ENA_F, m_F_EnaF);
	DDX_Check(pDX, IDC_BUS_ENA_F, m_BusEnaF);
	DDX_Check(pDX, IDC_INHIBIT_A, m_InhibitA);
	DDX_Check(pDX, IDC_INHIBIT_B, m_InhibitB);
	DDX_Check(pDX, IDC_INHIBIT_C, m_InhibitC);
	DDX_Check(pDX, IDC_INHIBIT_D, m_InhibitD);
	DDX_Check(pDX, IDC_INHIBIT_E, m_InhibitE);
	DDX_Check(pDX, IDC_INHIBIT_F, m_InhibitF);
	DDX_Check(pDX, IDC_SYNCH_A, m_SynchA);
	DDX_Check(pDX, IDC_SYNCH_B, m_SynchB);
	DDX_Check(pDX, IDC_SYNCH_C, m_SynchC);
	DDX_Check(pDX, IDC_SYNCH_D, m_SynchD);
	DDX_Check(pDX, IDC_SYNCH_E, m_SynchE);
	DDX_Check(pDX, IDC_SYNCH_F, m_SynchF);
	DDX_Check(pDX, IDC_SYNCH_BURST, m_SynchBurst);
	DDX_Text(pDX, IDC_A_NAME, m_A_Name);
	DDV_MaxChars(pDX, m_A_Name, 32);
	DDX_Text(pDX, IDC_B_NAME, m_B_Name);
	DDV_MaxChars(pDX, m_B_Name, 32);
	DDX_Text(pDX, IDC_C_NAME, m_C_Name);
	DDV_MaxChars(pDX, m_C_Name, 32);
	DDX_Text(pDX, IDC_D_NAME2, m_D_Name);
	DDV_MaxChars(pDX, m_D_Name, 32);
	DDX_Text(pDX, IDC_E_NAME2, m_E_Name);
	DDV_MaxChars(pDX, m_E_Name, 32);
	DDX_Text(pDX, IDC_F_NAME2, m_F_Name);
	DDV_MaxChars(pDX, m_F_Name, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CG05p4MasterPP, CPropertyPage)
	ON_MESSAGE(WM_LOAD_COUNTER_REQUEST_G05, OnChangeObjectProps)
	ON_MESSAGE(WM_LOAD_FREQUENCY_REQUEST_G05, OnLoadFrequency)
	ON_MESSAGE(WM_USER_REQUEST_A, OnScrollDelayA)
	ON_MESSAGE(WM_USER_REQUEST_B, OnScrollDelayB)
	ON_MESSAGE(WM_USER_REQUEST_C, OnScrollDelayC)
	ON_MESSAGE(WM_USER_REQUEST_D, OnScrollDelayD)
	ON_MESSAGE(WM_USER_REQUEST_E, OnScrollDelayE)
	ON_MESSAGE(WM_USER_REQUEST_F, OnScrollDelayF)
	ON_MESSAGE(WM_USER_REQUEST_W_A, OnScrollWidthA)
	ON_MESSAGE(WM_USER_REQUEST_W_B, OnScrollWidthB)
	ON_MESSAGE(WM_USER_REQUEST_W_C, OnScrollWidthC)
	ON_MESSAGE(WM_USER_REQUEST_W_D, OnScrollWidthD)
	ON_MESSAGE(WM_USER_REQUEST_W_E, OnScrollWidthE)
	ON_MESSAGE(WM_USER_REQUEST_W_F, OnScrollWidthF)
	ON_MESSAGE(WM_USER_REQUEST_M_A, OnScrollModuloA)
	ON_MESSAGE(WM_USER_REQUEST_M_B, OnScrollModuloB)
	ON_MESSAGE(WM_USER_REQUEST_M_C, OnScrollModuloC)
	ON_MESSAGE(WM_USER_REQUEST_M_D, OnScrollModuloD)
	ON_MESSAGE(WM_USER_REQUEST_M_E, OnScrollModuloE)
	ON_MESSAGE(WM_USER_REQUEST_M_F, OnScrollModuloF)
	ON_MESSAGE(WM_USER_REQUEST_O_A, OnScrollOffsetA)
	ON_MESSAGE(WM_USER_REQUEST_O_B, OnScrollOffsetB)
	ON_MESSAGE(WM_USER_REQUEST_O_C, OnScrollOffsetC)
	ON_MESSAGE(WM_USER_REQUEST_O_D, OnScrollOffsetD)
	ON_MESSAGE(WM_USER_REQUEST_O_E, OnScrollOffsetE)
	ON_MESSAGE(WM_USER_REQUEST_O_F, OnScrollOffsetF)
	ON_MESSAGE(WM_USER_REQUEST_PRD, OnScrollInhibitTrigger)
	ON_MESSAGE(WM_USER_REQUEST_INS, OnScrollInhibitSecondary)
	ON_MESSAGE(WM_USER_REQUEST_DES, OnScrollDelaySecondary)
	ON_MESSAGE(WM_USER_REQUEST_GDL, OnScrollGateDelay)
	ON_MESSAGE(WM_USER_REQUEST_SBC, OnScrollStepBack)
	ON_MESSAGE(WM_USER_REQUEST_FTR, OnScrollForceTrigger)
	ON_MESSAGE(WM_USER_REQUEST_TLV, OnScrollTriggerLevel)
	ON_MESSAGE(WM_USER_REQUEST_GLV, OnScrollGateLevel)
	ON_MESSAGE(WM_USER_REQUEST_GD, OnScrollGateDivider)
	ON_MESSAGE(WM_USER_REQUEST_PVA, OnScrollPresetValue)
	ON_MESSAGE(WM_USER_REQUEST_BCT, OnScrollBurst)
	//{{AFX_MSG_MAP(CG05p4MasterPP)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_A, OnPrimaryLocalA)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_B, OnPrimaryLocalB)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_C, OnPrimaryLocalC)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_D, OnPrimaryLocalD)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_E, OnPrimaryLocalE)
	ON_BN_CLICKED(IDC_PRIMARY_LOCAL_F, OnPrimaryLocalF)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_A, OnSecondaryLocalA)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_B, OnSecondaryLocalB)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_C, OnSecondaryLocalC)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_D, OnSecondaryLocalD)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_E, OnSecondaryLocalE)
	ON_BN_CLICKED(IDC_SECONDARY_LOCAL_F, OnSecondaryLocalF)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_A, OnForceLocalA)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_B, OnForceLocalB)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_C, OnForceLocalC)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_D, OnForceLocalD)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_E, OnForceLocalE)
	ON_BN_CLICKED(IDC_FORCE_LOCAL_F, OnForceLocalF)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_A, OnPrimaryBusA)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_B, OnPrimaryBusB)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_C, OnPrimaryBusC)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_D, OnPrimaryBusD)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_E, OnPrimaryBusE)
	ON_BN_CLICKED(IDC_PRIMARY_BUS_F, OnPrimaryBusF)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_A, OnSecondaryBusA)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_B, OnSecondaryBusB)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_C, OnSecondaryBusC)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_D, OnSecondaryBusD)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_E, OnSecondaryBusE)
	ON_BN_CLICKED(IDC_SECONDARY_BUS_F, OnSecondaryBusF)
	ON_BN_CLICKED(IDC_FORCE_BUS_A, OnForceBusA)
	ON_BN_CLICKED(IDC_FORCE_BUS_B, OnForceBusB)
	ON_BN_CLICKED(IDC_FORCE_BUS_C, OnForceBusC)
	ON_BN_CLICKED(IDC_FORCE_BUS_D, OnForceBusD)
	ON_BN_CLICKED(IDC_FORCE_BUS_E, OnForceBusE)
	ON_BN_CLICKED(IDC_FORCE_BUS_F, OnForceBusF)
	ON_BN_CLICKED(IDC_INHIBIT_A, OnInhibitA)
	ON_BN_CLICKED(IDC_INHIBIT_B, OnInhibitB)
	ON_BN_CLICKED(IDC_INHIBIT_C, OnInhibitC)
	ON_BN_CLICKED(IDC_INHIBIT_D, OnInhibitD)
	ON_BN_CLICKED(IDC_INHIBIT_E, OnInhibitE)
	ON_BN_CLICKED(IDC_INHIBIT_F, OnInhibitF)
	ON_BN_CLICKED(IDC_SYNCH_A, OnSynchA)
	ON_BN_CLICKED(IDC_SYNCH_B, OnSynchB)
	ON_BN_CLICKED(IDC_SYNCH_C, OnSynchC)
	ON_BN_CLICKED(IDC_SYNCH_D, OnSynchD)
	ON_BN_CLICKED(IDC_SYNCH_E, OnSynchE)
	ON_BN_CLICKED(IDC_SYNCH_F, OnSynchF)
	ON_BN_CLICKED(IDC_SYNCH_BURST, OnSynchBurst)
	ON_BN_CLICKED(IDC_STBK_LOC_A, OnStbkLocA)
	ON_BN_CLICKED(IDC_STBK_LOC_B, OnStbkLocB)
	ON_BN_CLICKED(IDC_STBK_LOC_C, OnStbkLocC)
	ON_BN_CLICKED(IDC_STBK_LOC_D, OnStbkLocD)
	ON_BN_CLICKED(IDC_STBK_LOC_E, OnStbkLocE)
	ON_BN_CLICKED(IDC_STBK_LOC_F, OnStbkLocF)
	ON_BN_CLICKED(IDC_STBK_BUS_A, OnStbkBusA)
	ON_BN_CLICKED(IDC_STBK_BUS_B, OnStbkBusB)
	ON_BN_CLICKED(IDC_STBK_BUS_C, OnStbkBusC)
	ON_BN_CLICKED(IDC_STBK_BUS_D, OnStbkBusD)
	ON_BN_CLICKED(IDC_STBK_BUS_E, OnStbkBusE)
	ON_BN_CLICKED(IDC_STBK_BUS_F, OnStbkBusF)
	ON_EN_CHANGE(IDC_STBK_REF_A, OnChangeStbkRefA)
	ON_EN_CHANGE(IDC_STBK_REF_B, OnChangeStbkRefB)
	ON_EN_CHANGE(IDC_STBK_REF_C, OnChangeStbkRefC)
	ON_EN_CHANGE(IDC_STBK_REF_D, OnChangeStbkRefD)
	ON_EN_CHANGE(IDC_STBK_REF_E, OnChangeStbkRefE)
	ON_EN_CHANGE(IDC_STBK_REF_F, OnChangeStbkRefF)
	ON_EN_KILLFOCUS(IDC_STBK_REF_A, OnKillfocusStbkRefA)
	ON_EN_KILLFOCUS(IDC_STBK_REF_B, OnKillfocusStbkRefB)
	ON_EN_KILLFOCUS(IDC_STBK_REF_C, OnKillfocusStbkRefC)
	ON_EN_KILLFOCUS(IDC_STBK_REF_D, OnKillfocusStbkRefD)
	ON_EN_KILLFOCUS(IDC_STBK_REF_E, OnKillfocusStbkRefE)
	ON_EN_KILLFOCUS(IDC_STBK_REF_F, OnKillfocusStbkRefF)
	ON_BN_CLICKED(IDC_START_LOC_A, OnStartLocA)
	ON_BN_CLICKED(IDC_START_LOC_B, OnStartLocB)
	ON_BN_CLICKED(IDC_START_LOC_C, OnStartLocC)
	ON_BN_CLICKED(IDC_START_LOC_D, OnStartLocD)
	ON_BN_CLICKED(IDC_START_LOC_E, OnStartLocE)
	ON_BN_CLICKED(IDC_START_LOC_F, OnStartLocF)
	ON_BN_CLICKED(IDC_START_BUS_A, OnStartBusA)
	ON_BN_CLICKED(IDC_START_BUS_B, OnStartBusB)
	ON_BN_CLICKED(IDC_START_BUS_C, OnStartBusC)
	ON_BN_CLICKED(IDC_START_BUS_D, OnStartBusD)
	ON_BN_CLICKED(IDC_START_BUS_E, OnStartBusE)
	ON_BN_CLICKED(IDC_START_BUS_F, OnStartBusF)
	ON_BN_CLICKED(IDC_CIRCLE_A, OnCircleA)
	ON_BN_CLICKED(IDC_CIRCLE_B, OnCircleB)
	ON_BN_CLICKED(IDC_CIRCLE_C, OnCircleC)
	ON_BN_CLICKED(IDC_CIRCLE_D, OnCircleD)
	ON_BN_CLICKED(IDC_CIRCLE_E, OnCircleE)
	ON_BN_CLICKED(IDC_CIRCLE_F, OnCircleF)
	ON_BN_CLICKED(IDC_E_ENA_A, OnE_EnaA)
	ON_BN_CLICKED(IDC_F_ENA_A, OnF_EnaA)
	ON_BN_CLICKED(IDC_BUS_ENA_A, OnBusEnaA)
	ON_BN_CLICKED(IDC_E_ENA_B, OnE_EnaB)
	ON_BN_CLICKED(IDC_F_ENA_B, OnF_EnaB)
	ON_BN_CLICKED(IDC_BUS_ENA_B, OnBusEnaB)
	ON_BN_CLICKED(IDC_E_ENA_C, OnE_EnaC)
	ON_BN_CLICKED(IDC_F_ENA_C, OnF_EnaC)
	ON_BN_CLICKED(IDC_BUS_ENA_C, OnBusEnaC)
	ON_BN_CLICKED(IDC_E_ENA_D, OnE_EnaD)
	ON_BN_CLICKED(IDC_F_ENA_D, OnF_EnaD)
	ON_BN_CLICKED(IDC_BUS_ENA_D, OnBusEnaD)
	ON_BN_CLICKED(IDC_E_ENA_E, OnE_EnaE)
	ON_BN_CLICKED(IDC_F_ENA_E, OnF_EnaE)
	ON_BN_CLICKED(IDC_BUS_ENA_E, OnBusEnaE)
	ON_BN_CLICKED(IDC_E_ENA_F, OnE_EnaF)
	ON_BN_CLICKED(IDC_F_ENA_F, OnF_EnaF)
	ON_BN_CLICKED(IDC_BUS_ENA_F, OnBusEnaF)
	ON_BN_CLICKED(IDC_GATE_AB, OnGateAB)
	ON_BN_CLICKED(IDC_AB_XOR, OnAB_Xor)
	ON_BN_CLICKED(IDC_AB_OR, OnAB_Or)
	ON_BN_CLICKED(IDC_AB_AND, OnAB_And)
	ON_BN_CLICKED(IDC_GATE_CD, OnGateCD)
	ON_BN_CLICKED(IDC_CD_XOR, OnCD_Xor)
	ON_BN_CLICKED(IDC_CD_OR, OnCD_Or)
	ON_BN_CLICKED(IDC_CD_AND, OnCD_And)
	ON_BN_CLICKED(IDC_GATE_EF, OnGateEF)
	ON_BN_CLICKED(IDC_EF_XOR, OnEF_Xor)
	ON_BN_CLICKED(IDC_EF_OR, OnEF_Or)
	ON_BN_CLICKED(IDC_EF_AND, OnEF_And)
	ON_BN_CLICKED(IDC_EXTERNAL, OnExternal)
	ON_BN_CLICKED(IDC_INTERNAL, OnInternal)
	ON_BN_CLICKED(IDC_FALLING, OnFalling)
	ON_BN_CLICKED(IDC_RISING, OnRising)
	ON_BN_CLICKED(IDC_GATE_POSITIVE, OnGatePositive)
	ON_BN_CLICKED(IDC_GATE_NEGATIVE, OnGateNegative)
	ON_BN_CLICKED(IDC_IGNORE, OnIgnore)
	ON_BN_CLICKED(IDC_MEMORIZE, OnMemorize)
	ON_BN_CLICKED(IDC_SYNCHRONIZE_GATE, OnSynchronizeGate)
	ON_BN_CLICKED(IDC_STOP_ON_PRESET, OnStopOnPreset)
	ON_BN_CLICKED(IDC_READ_TRIGGERS, OnReadTriggers)
	ON_BN_CLICKED(IDC_RESET_COUNTER, OnResetCounter)
	ON_EN_CHANGE(IDC_TRIGGER_COUNT, OnChangeTriggerCount)
	ON_EN_CHANGE(IDC_EXT_FREQUENCY, OnChangeExtFrequency)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_DELAY_A, OnChangeDelayA)
	ON_EN_CHANGE(IDC_DELAY_B, OnChangeDelayB)
	ON_EN_CHANGE(IDC_DELAY_C, OnChangeDelayC)
	ON_EN_CHANGE(IDC_DELAY_D, OnChangeDelayD)
	ON_EN_CHANGE(IDC_DELAY_E, OnChangeDelayE)
	ON_EN_CHANGE(IDC_DELAY_F, OnChangeDelayF)
	ON_EN_KILLFOCUS(IDC_DELAY_A, OnKillfocusDelayA)
	ON_EN_KILLFOCUS(IDC_DELAY_B, OnKillfocusDelayB)
	ON_EN_KILLFOCUS(IDC_DELAY_C, OnKillfocusDelayC)
	ON_EN_KILLFOCUS(IDC_DELAY_D, OnKillfocusDelayD)
	ON_EN_KILLFOCUS(IDC_DELAY_E, OnKillfocusDelayE)
	ON_EN_KILLFOCUS(IDC_DELAY_F, OnKillfocusDelayF)
	ON_EN_CHANGE(IDC_WIDTH_A, OnChangeWidthA)
	ON_EN_CHANGE(IDC_WIDTH_B, OnChangeWidthB)
	ON_EN_CHANGE(IDC_WIDTH_C, OnChangeWidthC)
	ON_EN_CHANGE(IDC_WIDTH_D, OnChangeWidthD)
	ON_EN_CHANGE(IDC_WIDTH_E, OnChangeWidthE)
	ON_EN_CHANGE(IDC_WIDTH_F, OnChangeWidthF)
	ON_EN_KILLFOCUS(IDC_WIDTH_A, OnKillfocusWidthA)
	ON_EN_KILLFOCUS(IDC_WIDTH_B, OnKillfocusWidthB)
	ON_EN_KILLFOCUS(IDC_WIDTH_C, OnKillfocusWidthC)
	ON_EN_KILLFOCUS(IDC_WIDTH_D, OnKillfocusWidthD)
	ON_EN_KILLFOCUS(IDC_WIDTH_E, OnKillfocusWidthE)
	ON_EN_KILLFOCUS(IDC_WIDTH_F, OnKillfocusWidthF)
	ON_EN_CHANGE(IDC_MODULO_A, OnChangeModuloA)
	ON_EN_CHANGE(IDC_MODULO_B, OnChangeModuloB)
	ON_EN_CHANGE(IDC_MODULO_C, OnChangeModuloC)
	ON_EN_CHANGE(IDC_MODULO_D, OnChangeModuloD)
	ON_EN_CHANGE(IDC_MODULO_E, OnChangeModuloE)
	ON_EN_CHANGE(IDC_MODULO_F, OnChangeModuloF)
	ON_EN_KILLFOCUS(IDC_MODULO_A, OnKillfocusModuloA)
	ON_EN_KILLFOCUS(IDC_MODULO_B, OnKillfocusModuloB)
	ON_EN_KILLFOCUS(IDC_MODULO_C, OnKillfocusModuloC)
	ON_EN_KILLFOCUS(IDC_MODULO_D, OnKillfocusModuloD)
	ON_EN_KILLFOCUS(IDC_MODULO_E, OnKillfocusModuloE)
	ON_EN_KILLFOCUS(IDC_MODULO_F, OnKillfocusModuloF)
	ON_EN_CHANGE(IDC_OFFSET_A, OnChangeOffsetA)
	ON_EN_CHANGE(IDC_OFFSET_B, OnChangeOffsetB)
	ON_EN_CHANGE(IDC_OFFSET_C, OnChangeOffsetC)
	ON_EN_CHANGE(IDC_OFFSET_D, OnChangeOffsetD)
	ON_EN_CHANGE(IDC_OFFSET_E, OnChangeOffsetE)
	ON_EN_CHANGE(IDC_OFFSET_F, OnChangeOffsetF)
	ON_EN_KILLFOCUS(IDC_OFFSET_A, OnKillfocusOffsetA)
	ON_EN_KILLFOCUS(IDC_OFFSET_B, OnKillfocusOffsetB)
	ON_EN_KILLFOCUS(IDC_OFFSET_C, OnKillfocusOffsetC)
	ON_EN_KILLFOCUS(IDC_OFFSET_D, OnKillfocusOffsetD)
	ON_EN_KILLFOCUS(IDC_OFFSET_E, OnKillfocusOffsetE)
	ON_EN_KILLFOCUS(IDC_OFFSET_F, OnKillfocusOffsetF)
	ON_BN_CLICKED(IDC_ZERO_MODULO, OnZeroModulo)
	ON_BN_CLICKED(IDC_JUMP_START, OnJumpStart)
	ON_EN_CHANGE(IDC_INHIBIT_TRIGGER, OnChangeInhibitTrigger)
	ON_EN_KILLFOCUS(IDC_INHIBIT_TRIGGER, OnKillfocusInhibitTrigger)
	ON_EN_CHANGE(IDC_INHIBIT_SECONDARY, OnChangeInhibitSecondary)
	ON_EN_KILLFOCUS(IDC_INHIBIT_SECONDARY, OnKillfocusInhibitSecondary)
	ON_EN_CHANGE(IDC_DELAY_SECONDARY, OnChangeDelaySecondary)
	ON_EN_KILLFOCUS(IDC_DELAY_SECONDARY, OnKillfocusDelaySecondary)
	ON_EN_CHANGE(IDC_GATE_DELAY, OnChangeGateDelay)
	ON_EN_KILLFOCUS(IDC_GATE_DELAY, OnKillfocusGateDelay)
	ON_EN_CHANGE(IDC_STEP_BACK, OnChangeStepBack)
	ON_EN_KILLFOCUS(IDC_STEP_BACK, OnKillfocusStepBack)
	ON_EN_CHANGE(IDC_FORCE_TRIGGER, OnChangeForceTrigger)
	ON_EN_KILLFOCUS(IDC_FORCE_TRIGGER, OnKillfocusForceTrigger)
	ON_EN_CHANGE(IDC_GATE_DIVIDER, OnChangeGateDivider)
	ON_EN_KILLFOCUS(IDC_GATE_DIVIDER, OnKillfocusGateDivider)
	ON_EN_CHANGE(IDC_TRIGGER_LEVEL, OnChangeTriggerLevel)
	ON_EN_KILLFOCUS(IDC_TRIGGER_LEVEL, OnKillfocusTriggerLevel)
	ON_EN_CHANGE(IDC_GATE_LEVEL, OnChangeGateLevel)
	ON_EN_KILLFOCUS(IDC_GATE_LEVEL, OnKillfocusGateLevel)
	ON_EN_CHANGE(IDC_PRESET_VALUE, OnChangePresetValue)
	ON_EN_KILLFOCUS(IDC_PRESET_VALUE, OnKillfocusPresetValue)
	ON_EN_CHANGE(IDC_BURST, OnChangeBurst)
	ON_EN_KILLFOCUS(IDC_BURST, OnKillfocusBurst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG05p4MasterPP message handlers


LRESULT CG05p4MasterPP::OnChangeObjectProps(WPARAM, LPARAM)
{
	LoadTriggerCounter(&NoEvents);
	return 0;
}

	LRESULT CG05p4MasterPP::OnLoadFrequency(WPARAM, LPARAM)
{
	LoadFrequency(&Frequency);
	return 0;
}

void CG05p4MasterPP::LoadTriggerCounter(_int64* p_TriggerCount)
{
	m_TriggerCount.Format(" %1.0f",double(*p_TriggerCount));
	if (b_PageActive)
		UpdateData(FALSE);
}

void CG05p4MasterPP::LoadFrequency(double* p_Frequency)
{
	CListRout lr;
	m_ExtFrequency.Format(" %8.6f",*p_Frequency);
	m_ExtFrequency =  lr.TrimTrailingZeros((LPCTSTR) m_ExtFrequency);
	if (b_PageActive)
		UpdateData(FALSE);
}

void CG05p4MasterPP::OnResetCounter() 
{
	b_RequestZeroCounter = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

void CG05p4MasterPP::OnZeroModulo() 
{
	b_RequestZeroModulo = TRUE;
	b_RequestJumpStart = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

void CG05p4MasterPP::OnJumpStart() 
{
	b_RequestZeroModulo = TRUE;
	b_RequestJumpStart = TRUE;
	p_ParentWindow->SendMessage(WM_USER_REQUEST_G05, 0, 0);
}

void CG05p4MasterPP::OnChangeTriggerCount() 
{
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeExtFrequency() 
{
	UpdateData(FALSE);
}

BOOL CG05p4MasterPP::OnSetActive() 
{
	b_PageActive = TRUE;
	b_FastApply = FALSE;
	SetEvent(DataNotification);
	return CPropertyPage::OnSetActive();
}

BOOL CG05p4MasterPP::OnKillActive() 
{
	b_PageActive = FALSE;
	b_FastApply = FALSE;
	return CPropertyPage::OnKillActive();
}

void CG05p4MasterPP::UpdateGoSignals() 
{

	if (m_PrimaryLocalA)
		GoSignal_A |= LocalPrimary;
	else
		GoSignal_A &= ~LocalPrimary;
	if (m_SecondaryLocalA)
		GoSignal_A |= LocalSecondary;
	else
		GoSignal_A &= ~LocalSecondary;
	if (m_ForceLocalA)
		GoSignal_A |= LocalForce;
	else
		GoSignal_A &= ~LocalForce;
	if (m_PrimaryBusA)
		GoSignal_A |= MasterPrimary;
	else
		GoSignal_A &= ~MasterPrimary;
	if (m_SecondaryBusA)
		GoSignal_A |= MasterSecondary;
	else
		GoSignal_A &= ~MasterSecondary;
	if (m_ForceBusA)
		GoSignal_A |= MasterForce;
	else
		GoSignal_A &= ~MasterForce;
	if (m_InhibitA)
		GoSignal_A |= InhibitLocal;
	else
		GoSignal_A &= ~InhibitLocal;
	if (m_StartLocA)
		GoSignal_A |= StartLocal;
	else
		GoSignal_A &= ~StartLocal;
	if (m_StartBusA)
		GoSignal_A |= StartBus;
	else
		GoSignal_A &= ~StartBus;
	if (m_StbkLocA)
		GoSignal_A |= StepBackLocal;
	else
		GoSignal_A &= ~StepBackLocal;
	if (m_StbkBusA)
		GoSignal_A |= StepBackBus;
	else
		GoSignal_A &= ~StepBackBus;
	if (m_CircleA)
		GoSignal_A |= RunCircle;
	else
		GoSignal_A &= ~RunCircle;
	if (m_SynchA)
		GoSignal_A |= SynchReload;
	else
		GoSignal_A &= ~SynchReload;
	if (m_E_EnaA)
		GoSignal_A |= EnableFromE;
	else
		GoSignal_A &= ~EnableFromE;
	if (m_F_EnaA)
		GoSignal_A |= EnableFromF;
	else
		GoSignal_A &= ~EnableFromF;
	if (m_BusEnaA)
		GoSignal_A |= EnableFromBus;
	else
		GoSignal_A &= ~EnableFromBus;

	if (m_PrimaryLocalB)
		GoSignal_B |= LocalPrimary;
	else
		GoSignal_B &= ~LocalPrimary;
	if (m_SecondaryLocalB)
		GoSignal_B |= LocalSecondary;
	else
		GoSignal_B &= ~LocalSecondary;
	if (m_ForceLocalB)
		GoSignal_B |= LocalForce;
	else
		GoSignal_B &= ~LocalForce;
	if (m_PrimaryBusB)
		GoSignal_B |= MasterPrimary;
	else
		GoSignal_B &= ~MasterPrimary;
	if (m_SecondaryBusB)
		GoSignal_B |= MasterSecondary;
	else
		GoSignal_B &= ~MasterSecondary;
	if (m_ForceBusB)
		GoSignal_B |= MasterForce;
	else
		GoSignal_B &= ~MasterForce;
	if (m_InhibitB)
		GoSignal_B |= InhibitLocal;
	else
		GoSignal_B &= ~InhibitLocal;
	if (m_StartLocB)
		GoSignal_B |= StartLocal;
	else
		GoSignal_B &= ~StartLocal;
	if (m_StartBusB)
		GoSignal_B |= StartBus;
	else
		GoSignal_B &= ~StartBus;
	if (m_StbkLocB)
		GoSignal_B |= StepBackLocal;
	else
		GoSignal_B &= ~StepBackLocal;
	if (m_StbkBusB)
		GoSignal_B |= StepBackBus;
	else
		GoSignal_B &= ~StepBackBus;
	if (m_CircleB)
		GoSignal_B |= RunCircle;
	else
		GoSignal_B &= ~RunCircle;
	if (m_SynchB)
		GoSignal_B |= SynchReload;
	else
		GoSignal_B &= ~SynchReload;
	if (m_E_EnaB)
		GoSignal_B |= EnableFromE;
	else
		GoSignal_B &= ~EnableFromE;
	if (m_F_EnaB)
		GoSignal_B |= EnableFromF;
	else
		GoSignal_B &= ~EnableFromF;
	if (m_BusEnaB)
		GoSignal_B |= EnableFromBus;
	else
		GoSignal_B &= ~EnableFromBus;

	if (m_PrimaryLocalC)
		GoSignal_C |= LocalPrimary;
	else
		GoSignal_C &= ~LocalPrimary;
	if (m_SecondaryLocalC)
		GoSignal_C |= LocalSecondary;
	else
		GoSignal_C &= ~LocalSecondary;
	if (m_ForceLocalC)
		GoSignal_C |= LocalForce;
	else
		GoSignal_C &= ~LocalForce;
	if (m_PrimaryBusC)
		GoSignal_C |= MasterPrimary;
	else
		GoSignal_C &= ~MasterPrimary;
	if (m_SecondaryBusC)
		GoSignal_C |= MasterSecondary;
	else
		GoSignal_C &= ~MasterSecondary;
	if (m_ForceBusC)
		GoSignal_C |= MasterForce;
	else
		GoSignal_C &= ~MasterForce;
	if (m_InhibitC)
		GoSignal_C |= InhibitLocal;
	else
		GoSignal_C &= ~InhibitLocal;
	if (m_StartLocC)
		GoSignal_C |= StartLocal;
	else
		GoSignal_C &= ~StartLocal;
	if (m_StartBusC)
		GoSignal_C |= StartBus;
	else
		GoSignal_C &= ~StartBus;
	if (m_StbkLocC)
		GoSignal_C |= StepBackLocal;
	else
		GoSignal_C &= ~StepBackLocal;
	if (m_StbkBusC)
		GoSignal_C |= StepBackBus;
	else
		GoSignal_C &= ~StepBackBus;
	if (m_CircleC)
		GoSignal_C |= RunCircle;
	else
		GoSignal_C &= ~RunCircle;
	if (m_SynchC)
		GoSignal_C |= SynchReload;
	else
		GoSignal_C &= ~SynchReload;
	if (m_E_EnaC)
		GoSignal_C |= EnableFromE;
	else
		GoSignal_C &= ~EnableFromE;
	if (m_F_EnaC)
		GoSignal_C |= EnableFromF;
	else
		GoSignal_C &= ~EnableFromF;
	if (m_BusEnaC)
		GoSignal_C |= EnableFromBus;
	else
		GoSignal_C &= ~EnableFromBus;

	if (m_PrimaryLocalD)
		GoSignal_D |= LocalPrimary;
	else
		GoSignal_D &= ~LocalPrimary;
	if (m_SecondaryLocalD)
		GoSignal_D |= LocalSecondary;
	else
		GoSignal_D &= ~LocalSecondary;
	if (m_ForceLocalD)
		GoSignal_D |= LocalForce;
	else
		GoSignal_D &= ~LocalForce;
	if (m_PrimaryBusD)
		GoSignal_D |= MasterPrimary;
	else
		GoSignal_D &= ~MasterPrimary;
	if (m_SecondaryBusD)
		GoSignal_D |= MasterSecondary;
	else
		GoSignal_D &= ~MasterSecondary;
	if (m_ForceBusD)
		GoSignal_D |= MasterForce;
	else
		GoSignal_D &= ~MasterForce;
	if (m_InhibitD)
		GoSignal_D |= InhibitLocal;
	else
		GoSignal_D &= ~InhibitLocal;
	if (m_StartLocD)
		GoSignal_D |= StartLocal;
	else
		GoSignal_D &= ~StartLocal;
	if (m_StartBusD)
		GoSignal_D |= StartBus;
	else
		GoSignal_D &= ~StartBus;
	if (m_StbkLocD)
		GoSignal_D |= StepBackLocal;
	else
		GoSignal_D &= ~StepBackLocal;
	if (m_StbkBusD)
		GoSignal_D |= StepBackBus;
	else
		GoSignal_D &= ~StepBackBus;
	if (m_CircleD)
		GoSignal_D |= RunCircle;
	else
		GoSignal_D &= ~RunCircle;
	if (m_SynchD)
		GoSignal_D |= SynchReload;
	else
		GoSignal_D &= ~SynchReload;
	if (m_E_EnaD)
		GoSignal_D |= EnableFromE;
	else
		GoSignal_D &= ~EnableFromE;
	if (m_F_EnaD)
		GoSignal_D |= EnableFromF;
	else
		GoSignal_D &= ~EnableFromF;
	if (m_BusEnaD)
		GoSignal_D |= EnableFromBus;
	else
		GoSignal_D &= ~EnableFromBus;

	if (m_PrimaryLocalE)
		GoSignal_E |= LocalPrimary;
	else
		GoSignal_E &= ~LocalPrimary;
	if (m_SecondaryLocalE)
		GoSignal_E |= LocalSecondary;
	else
		GoSignal_E &= ~LocalSecondary;
	if (m_ForceLocalE)
		GoSignal_E |= LocalForce;
	else
		GoSignal_E &= ~LocalForce;
	if (m_PrimaryBusE)
		GoSignal_E |= MasterPrimary;
	else
		GoSignal_E &= ~MasterPrimary;
	if (m_SecondaryBusE)
		GoSignal_E |= MasterSecondary;
	else
		GoSignal_E &= ~MasterSecondary;
	if (m_ForceBusE)
		GoSignal_E |= MasterForce;
	else
		GoSignal_E &= ~MasterForce;
	if (m_InhibitE)
		GoSignal_E |= InhibitLocal;
	else
		GoSignal_E &= ~InhibitLocal;
	if (m_StartLocE)
		GoSignal_E |= StartLocal;
	else
		GoSignal_E &= ~StartLocal;
	if (m_StartBusE)
		GoSignal_E |= StartBus;
	else
		GoSignal_E &= ~StartBus;
	if (m_StbkLocE)
		GoSignal_E |= StepBackLocal;
	else
		GoSignal_E &= ~StepBackLocal;
	if (m_StbkBusE)
		GoSignal_E |= StepBackBus;
	else
		GoSignal_E &= ~StepBackBus;
	if (m_CircleE)
		GoSignal_E |= RunCircle;
	else
		GoSignal_E &= ~RunCircle;
	if (m_SynchE)
		GoSignal_E |= SynchReload;
	else
		GoSignal_E &= ~SynchReload;
	if (m_E_EnaE)
		GoSignal_E |= EnableFromE;
	else
		GoSignal_E &= ~EnableFromE;
	if (m_F_EnaE)
		GoSignal_E |= EnableFromF;
	else
		GoSignal_E &= ~EnableFromF;
	if (m_BusEnaE)
		GoSignal_E |= EnableFromBus;
	else
		GoSignal_E &= ~EnableFromBus;

	if (m_PrimaryLocalF)
		GoSignal_F |= LocalPrimary;
	else
		GoSignal_F &= ~LocalPrimary;
	if (m_SecondaryLocalF)
		GoSignal_F |= LocalSecondary;
	else
		GoSignal_F &= ~LocalSecondary;
	if (m_ForceLocalF)
		GoSignal_F |= LocalForce;
	else
		GoSignal_F &= ~LocalForce;
	if (m_PrimaryBusF)
		GoSignal_F |= MasterPrimary;
	else
		GoSignal_F &= ~MasterPrimary;
	if (m_SecondaryBusF)
		GoSignal_F |= MasterSecondary;
	else
		GoSignal_F &= ~MasterSecondary;
	if (m_ForceBusF)
		GoSignal_F |= MasterForce;
	else
		GoSignal_F &= ~MasterForce;
	if (m_InhibitF)
		GoSignal_F |= InhibitLocal;
	else
		GoSignal_F &= ~InhibitLocal;
	if (m_StartLocF)
		GoSignal_F |= StartLocal;
	else
		GoSignal_F &= ~StartLocal;
	if (m_StartBusF)
		GoSignal_F |= StartBus;
	else
		GoSignal_F &= ~StartBus;
	if (m_StbkLocF)
		GoSignal_F |= StepBackLocal;
	else
		GoSignal_F &= ~StepBackLocal;
	if (m_StbkBusF)
		GoSignal_F |= StepBackBus;
	else
		GoSignal_F &= ~StepBackBus;
	if (m_CircleF)
		GoSignal_F |= RunCircle;
	else
		GoSignal_F &= ~RunCircle;
	if (m_SynchF)
		GoSignal_F |= SynchReload;
	else
		GoSignal_F &= ~SynchReload;
	if (m_E_EnaF)
		GoSignal_F |= EnableFromE;
	else
		GoSignal_F &= ~EnableFromE;
	if (m_F_EnaF)
		GoSignal_F |= EnableFromF;
	else
		GoSignal_F &= ~EnableFromF;
	if (m_BusEnaF)
		GoSignal_F |= EnableFromBus;
	else
		GoSignal_F &= ~EnableFromBus;
}

void CG05p4MasterPP::CheckGateChannels()
{
	if (m_GateAB)
	{
		if ((GoSignal_A & 0x77) == 0x0)
			m_PrimaryBusA = TRUE;
		if ((GoSignal_B & 0x77) == 0x0)
			m_PrimaryBusB = TRUE;
	}
	if (m_GateCD)
	{
		if ((GoSignal_C & 0x77) == 0x0)
			m_PrimaryBusC = TRUE;
		if ((GoSignal_D & 0x77) == 0x0)
			m_PrimaryBusD = TRUE;
	}
	if (m_GateEF)
	{
		if ((GoSignal_E & 0x77) == 0x0)
			m_PrimaryBusE = TRUE;
		if ((GoSignal_F & 0x77) == 0x0)
			m_PrimaryBusF = TRUE;
	}
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStopOnPreset() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (!m_StopOnPreset)
		m_PresetValue = _T("");
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnReadTriggers() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnExternal() 
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


void CG05p4MasterPP::OnInternal() 
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

void CG05p4MasterPP::OnFalling() 
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

void CG05p4MasterPP::OnRising() 
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

void CG05p4MasterPP::OnIgnore() 
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

void CG05p4MasterPP::OnMemorize() 
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

void CG05p4MasterPP::OnSynchronizeGate() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_SynchronizeGate)
	{
		if ((!m_Ignore) && (!m_Memorize))
			m_Ignore = TRUE;
		if ((!m_GatePositive) && (!m_GateNegative))
			m_GatePositive = TRUE;
		m_Internal = TRUE;
		m_External = FALSE;
		m_Rising = FALSE;
		m_Falling = FALSE;
		if (b_CrystalOscillator)
			m_TriggerLevel = _T("");
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnGatePositive() 
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
		m_GateLevel = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
		m_SynchronizeGate = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnGateNegative() 
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
		m_GateLevel = _T("");
		m_Ignore = FALSE;
		m_Memorize = FALSE;
		m_SynchronizeGate = FALSE;
	}
	CheckHardwareControls();
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeDelayA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayA(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusDelayA() 
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
	if (m_DelayA.GetLength() > 0)
	{
		if (m_WidthA.GetLength() == 0)
		{
			m_WidthA.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthA =  lr.TrimTrailingZeros((LPCTSTR) m_WidthA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelayB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayB(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusDelayB() 
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
	if (m_DelayB.GetLength() > 0)
	{
		if (m_WidthB.GetLength() == 0)
		{
			m_WidthB.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthB =  lr.TrimTrailingZeros((LPCTSTR) m_WidthB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelayC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayC(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_CED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_CED.GetSel(nStartChar, nEndChar);
			m_DelayC = lr.ScrollEquation(m_DelayC, nEndChar, 
								m_Delay_CED.PresentCharacter, m_Delay_CED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_CED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusDelayC() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayC))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayC) == 1)
		{
			if (lr.Numeric(m_DelayC))
			{
				double t0 = atof(m_DelayC);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayC.Format(" %8.6f",t0);
				m_DelayC =  lr.TrimTrailingZeros((LPCTSTR) m_DelayC);
			}
			else
				m_DelayC = p_G0xData->AllowedParameter((LPCTSTR)m_DelayC);
			UpdateData(FALSE);
		}
	}
	if (m_DelayC.GetLength() > 0)
	{
		if (m_WidthC.GetLength() == 0)
		{
			m_WidthC.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthC =  lr.TrimTrailingZeros((LPCTSTR) m_WidthC);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelayD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayD(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_DED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_DED.GetSel(nStartChar, nEndChar);
			m_DelayD = lr.ScrollEquation(m_DelayD, nEndChar, 
								m_Delay_DED.PresentCharacter, m_Delay_DED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_DED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusDelayD() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayD))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayD) == 1)
		{
			if (lr.Numeric(m_DelayD))
			{
				double t0 = atof(m_DelayD);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayD.Format(" %8.6f",t0);
				m_DelayD =  lr.TrimTrailingZeros((LPCTSTR) m_DelayD);
			}
			else
				m_DelayD = p_G0xData->AllowedParameter((LPCTSTR)m_DelayD);
			UpdateData(FALSE);
		}
	}
	if (m_DelayD.GetLength() > 0)
	{
		if (m_WidthD.GetLength() == 0)
		{
			m_WidthD.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthD =  lr.TrimTrailingZeros((LPCTSTR) m_WidthD);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelayE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayE(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_EED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_EED.GetSel(nStartChar, nEndChar);
			m_DelayE = lr.ScrollEquation(m_DelayE, nEndChar, 
								m_Delay_EED.PresentCharacter, m_Delay_EED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_EED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusDelayE() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayE))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayE) == 1)
		{
			if (lr.Numeric(m_DelayE))
			{
				double t0 = atof(m_DelayE);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayE.Format(" %8.6f",t0);
				m_DelayE =  lr.TrimTrailingZeros((LPCTSTR) m_DelayE);
			}
			else
				m_DelayE = p_G0xData->AllowedParameter((LPCTSTR)m_DelayE);
			UpdateData(FALSE);
		}
	}
	if (m_DelayE.GetLength() > 0)
	{
		if (m_WidthE.GetLength() == 0)
		{
			m_WidthE.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthE =  lr.TrimTrailingZeros((LPCTSTR) m_WidthE);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelayF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelayF(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Delay_FED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Delay_FED.GetSel(nStartChar, nEndChar);
			m_DelayF = lr.ScrollEquation(m_DelayF, nEndChar, 
								m_Delay_FED.PresentCharacter, m_Delay_FED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Delay_FED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusDelayF() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_DelayF))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayF) == 1)
		{
			if (lr.Numeric(m_DelayF))
			{
				double t0 = atof(m_DelayF);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayF.Format(" %8.6f",t0);
				m_DelayF =  lr.TrimTrailingZeros((LPCTSTR) m_DelayF);
			}
			else
				m_DelayF = p_G0xData->AllowedParameter((LPCTSTR)m_DelayF);
			UpdateData(FALSE);
		}
	}
	if (m_DelayF.GetLength() > 0)
	{
		if (m_WidthF.GetLength() == 0)
		{
			m_WidthF.Format(" %8.6f",p_G0xData->RoundWidth(0.1, m_DG_Number));
			m_WidthF =  lr.TrimTrailingZeros((LPCTSTR) m_WidthF);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthA(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_AED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_AED.GetSel(nStartChar, nEndChar);
			m_WidthA = lr.ScrollEquation(m_WidthA, nEndChar, 
								m_Width_AED.PresentCharacter, m_Width_AED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_AED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthA) == 1)
		{
			if (lr.Numeric(m_WidthA))
			{
				double t0 = atof(m_WidthA);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthA.Format(" %8.6f",t0);
				m_WidthA =  lr.TrimTrailingZeros((LPCTSTR) m_WidthA);
			}
			else
				m_WidthA = p_G0xData->AllowedParameter((LPCTSTR)m_WidthA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthB(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_BED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_BED.GetSel(nStartChar, nEndChar);
			m_WidthB = lr.ScrollEquation(m_WidthB, nEndChar, 
								m_Width_BED.PresentCharacter, m_Width_BED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_BED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthB) == 1)
		{
			if (lr.Numeric(m_WidthB))
			{
				double t0 = atof(m_WidthB);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthB.Format(" %8.6f",t0);
				m_WidthB =  lr.TrimTrailingZeros((LPCTSTR) m_WidthB);
			}
			else
				m_WidthB = p_G0xData->AllowedParameter((LPCTSTR)m_WidthB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthC(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_CED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_CED.GetSel(nStartChar, nEndChar);
			m_WidthC = lr.ScrollEquation(m_WidthC, nEndChar, 
								m_Width_CED.PresentCharacter, m_Width_CED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_CED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthC() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthC))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthC) == 1)
		{
			if (lr.Numeric(m_WidthC))
			{
				double t0 = atof(m_WidthC);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthC.Format(" %8.6f",t0);
				m_WidthC =  lr.TrimTrailingZeros((LPCTSTR) m_WidthC);
			}
			else
				m_WidthC = p_G0xData->AllowedParameter((LPCTSTR)m_WidthC);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthD(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_DED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_DED.GetSel(nStartChar, nEndChar);
			m_WidthD = lr.ScrollEquation(m_WidthD, nEndChar, 
								m_Width_DED.PresentCharacter, m_Width_DED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_DED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthD() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthD))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthD) == 1)
		{
			if (lr.Numeric(m_WidthD))
			{
				double t0 = atof(m_WidthD);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthD.Format(" %8.6f",t0);
				m_WidthD =  lr.TrimTrailingZeros((LPCTSTR) m_WidthD);
			}
			else
				m_WidthD = p_G0xData->AllowedParameter((LPCTSTR)m_WidthD);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthE(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_EED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_EED.GetSel(nStartChar, nEndChar);
			m_WidthE = lr.ScrollEquation(m_WidthE, nEndChar, 
								m_Width_EED.PresentCharacter, m_Width_EED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_EED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthE() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthE))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthE) == 1)
		{
			if (lr.Numeric(m_WidthE))
			{
				double t0 = atof(m_WidthE);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthE.Format(" %8.6f",t0);
				m_WidthE =  lr.TrimTrailingZeros((LPCTSTR) m_WidthE);
			}
			else
				m_WidthE = p_G0xData->AllowedParameter((LPCTSTR)m_WidthE);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeWidthF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollWidthF(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_Width_FED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_Width_FED.GetSel(nStartChar, nEndChar);
			m_WidthF = lr.ScrollEquation(m_WidthF, nEndChar, 
								m_Width_FED.PresentCharacter, m_Width_FED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_Width_FED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusWidthF() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_WidthF))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthF) == 1)
		{
			if (lr.Numeric(m_WidthF))
			{
				double t0 = atof(m_WidthF);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthF.Format(" %8.6f",t0);
				m_WidthF =  lr.TrimTrailingZeros((LPCTSTR) m_WidthF);
			}
			else
				m_WidthF = p_G0xData->AllowedParameter((LPCTSTR)m_WidthF);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloA(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusModuloA() 
{
	CListRout lr;
	lr.TrimString(m_ModuloA);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloA) == 1)
		{
			if (lr.Numeric(m_ModuloA))
			{
				signed long modulo = RoundInt(atof(m_ModuloA));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloA.Format(" %d", modulo);
			}
			else
				m_ModuloA = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloA);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloB(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusModuloB() 
{
	CListRout lr;
	lr.TrimString(m_ModuloB);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloB) == 1)
		{
			if (lr.Numeric(m_ModuloB))
			{
				signed long modulo = RoundInt(atof(m_ModuloB));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloB.Format(" %d", modulo);
			}
			else
				m_ModuloB = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloB);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloC(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloCED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloCED.GetSel(nStartChar, nEndChar);
			m_ModuloC = lr.ScrollInteger(m_ModuloC, nEndChar, 
								m_ModuloCED.PresentCharacter, m_ModuloCED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloCED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusModuloC() 
{
	CListRout lr;
	lr.TrimString(m_ModuloC);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloC))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloC) == 1)
		{
			if (lr.Numeric(m_ModuloC))
			{
				signed long modulo = RoundInt(atof(m_ModuloC));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloC.Format(" %d", modulo);
			}
			else
				m_ModuloC = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloC);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloD(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloDED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloDED.GetSel(nStartChar, nEndChar);
			m_ModuloD = lr.ScrollInteger(m_ModuloD, nEndChar, 
								m_ModuloDED.PresentCharacter, m_ModuloDED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloDED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusModuloD() 
{
	CListRout lr;
	lr.TrimString(m_ModuloD);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloD))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloD) == 1)
		{
			if (lr.Numeric(m_ModuloD))
			{
				signed long modulo = RoundInt(atof(m_ModuloD));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloD.Format(" %d", modulo);
			}
			else
				m_ModuloD = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloD);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloE(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloEED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloEED.GetSel(nStartChar, nEndChar);
			m_ModuloE = lr.ScrollInteger(m_ModuloE, nEndChar, 
								m_ModuloEED.PresentCharacter, m_ModuloEED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloEED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusModuloE() 
{
	CListRout lr;
	lr.TrimString(m_ModuloE);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloE))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloE) == 1)
		{
			if (lr.Numeric(m_ModuloE))
			{
				signed long modulo = RoundInt(atof(m_ModuloE));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloE.Format(" %d", modulo);
			}
			else
				m_ModuloE = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloE);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeModuloF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollModuloF(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_ModuloFED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_ModuloFED.GetSel(nStartChar, nEndChar);
			m_ModuloF = lr.ScrollInteger(m_ModuloF, nEndChar, 
								m_ModuloFED.PresentCharacter, m_ModuloFED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_ModuloFED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusModuloF() 
{
	CListRout lr;
	lr.TrimString(m_ModuloF);
	if (lr.CheckBraceMatch((LPCTSTR)m_ModuloF))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloF) == 1)
		{
			if (lr.Numeric(m_ModuloF))
			{
				signed long modulo = RoundInt(atof(m_ModuloF));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloF.Format(" %d", modulo);
			}
			else
				m_ModuloF = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloF);
			UpdateData(FALSE);
		}
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetA(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusOffsetA() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetA))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetA) == 1)
		{
			if (lr.Numeric(m_OffsetA))
			{
				signed long offset = RoundInt(atof(m_OffsetA));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetA.Format(" %d", offset);
			}
			else
				m_OffsetA = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetA);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetB(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusOffsetB() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetB))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetB) == 1)
		{
			if (lr.Numeric(m_OffsetB))
			{
				signed long offset = RoundInt(atof(m_OffsetB));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetB.Format(" %d", offset);
			}
			else
				m_OffsetB = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetB);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetC(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetCED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetCED.GetSel(nStartChar, nEndChar);
			m_OffsetC = lr.ScrollInteger(m_OffsetC, nEndChar, 
								m_OffsetCED.PresentCharacter, m_OffsetCED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetCED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusOffsetC() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetC))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetC) == 1)
		{
			if (lr.Numeric(m_OffsetC))
			{
				signed long offset = RoundInt(atof(m_OffsetC));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetC.Format(" %d", offset);
			}
			else
				m_OffsetC = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetC);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetD(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetDED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetDED.GetSel(nStartChar, nEndChar);
			m_OffsetD = lr.ScrollInteger(m_OffsetD, nEndChar, 
								m_OffsetDED.PresentCharacter, m_OffsetDED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetDED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusOffsetD() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetD))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetD) == 1)
		{
			if (lr.Numeric(m_OffsetD))
			{
				signed long offset = RoundInt(atof(m_OffsetD));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetD.Format(" %d", offset);
			}
			else
				m_OffsetD = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetD);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetE(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetEED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetEED.GetSel(nStartChar, nEndChar);
			m_OffsetE = lr.ScrollInteger(m_OffsetE, nEndChar, 
								m_OffsetEED.PresentCharacter, m_OffsetEED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetEED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusOffsetE() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetE))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetE) == 1)
		{
			if (lr.Numeric(m_OffsetE))
			{
				signed long offset = RoundInt(atof(m_OffsetE));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetE.Format(" %d", offset);
			}
			else
				m_OffsetE = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetE);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeOffsetF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollOffsetF(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_OffsetFED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_OffsetFED.GetSel(nStartChar, nEndChar);
			m_OffsetF = lr.ScrollInteger(m_OffsetF, nEndChar, 
								m_OffsetFED.PresentCharacter, m_OffsetFED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_OffsetFED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusOffsetF() 
{
	CListRout lr;
	if (lr.CheckBraceMatch((LPCTSTR)m_OffsetF))
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetF) == 1)
		{
			if (lr.Numeric(m_OffsetF))
			{
				signed long offset = RoundInt(atof(m_OffsetF));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetF.Format(" %d", offset);
			}
			else
				m_OffsetF = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetF);
			UpdateData(FALSE);
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnGateAB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateAB)
	{
		if (!(m_AB_Xor || m_AB_Or || m_AB_And))
			m_AB_Xor = TRUE;
		CheckGateChannels();
	}
	else
	{
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStepBack() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollStepBack(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_StepBackED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_StepBackED.GetSel(nStartChar, nEndChar);
			m_StepBack = lr.ScrollEquation(m_StepBack, nEndChar, 
								m_StepBackED.PresentCharacter, m_StepBackED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_StepBackED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusStepBack() 
{
	CListRout lr;
	lr.TrimString(m_StepBack);
	if (m_StepBack.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)m_StepBack))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)m_StepBack) == 1)
			{
				if (lr.Numeric(m_StepBack))
				{
					double t1 = p_G0xData->RoundRepCounter(atof(m_StepBack), m_DG_Number);
					m_StepBack.Format(" %8.6f",t1);
					m_StepBack =  lr.TrimTrailingZeros((LPCTSTR)m_StepBack);
				}
				else
					m_StepBack = p_G0xData->AllowedParameter((LPCTSTR)m_StepBack);
				UpdateData(FALSE);
			}
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeInhibitTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollInhibitTrigger(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusInhibitTrigger() 
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

void CG05p4MasterPP::OnChangeInhibitSecondary() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollInhibitSecondary(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_InhibitSecondaryED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_InhibitSecondaryED.GetSel(nStartChar, nEndChar);
			m_InhibitSecondary = lr.ScrollEquation(m_InhibitSecondary, nEndChar, 
								m_InhibitSecondaryED.PresentCharacter, m_InhibitSecondaryED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_InhibitSecondaryED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusInhibitSecondary() 
{
	CListRout lr;
	lr.TrimString(m_InhibitSecondary);
	if (m_InhibitSecondary.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)m_InhibitSecondary))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)m_InhibitSecondary) == 1)
			{
				if (lr.Numeric(m_InhibitSecondary))
				{
					double t1 = p_G0xData->RoundRepCounter(atof(m_InhibitSecondary), m_DG_Number);
					m_InhibitSecondary.Format(" %8.6f",t1);
					m_InhibitSecondary =  lr.TrimTrailingZeros((LPCTSTR)m_InhibitSecondary);
				}
				else
					m_InhibitSecondary = p_G0xData->AllowedParameter((LPCTSTR)m_InhibitSecondary);
				UpdateData(FALSE);
			}
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeGateDelay() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollGateDelay(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_GateDelayED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_GateDelayED.GetSel(nStartChar, nEndChar);
			m_GateDelay = lr.ScrollEquation(m_GateDelay, nEndChar, 
								m_GateDelayED.PresentCharacter, m_GateDelayED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_GateDelayED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusGateDelay() 
{
	CListRout lr;
	lr.TrimString(m_GateDelay);
	if (m_GateDelay.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)m_GateDelay))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)m_GateDelay) == 1)
			{
				if (lr.Numeric(m_GateDelay))
				{
					double t1 = p_G0xData->RoundGateDelay(atof(m_GateDelay), m_DG_Number);
					m_GateDelay.Format(" %8.6f",t1);
					m_GateDelay =  lr.TrimTrailingZeros((LPCTSTR)m_GateDelay);
				}
				UpdateData(FALSE);
			}
		}
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeForceTrigger() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollForceTrigger(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusForceTrigger() 
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
	UpdateData(FALSE);
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeTriggerLevel() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollTriggerLevel(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusTriggerLevel() 
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

void CG05p4MasterPP::OnChangeGateLevel() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollGateLevel(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_GateLevelED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_GateLevelED.GetSel(nStartChar, nEndChar);
			m_GateLevel = lr.ScrollDouble(m_GateLevel, nEndChar, 
								m_GateLevelED.PresentCharacter, m_GateLevelED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_GateLevelED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusGateLevel() 
{
	CListRout lr;
	lr.TrimString(m_GateLevel);
	if (m_GateLevel.GetLength() > 0)
	{
		double v0 = atof(m_GateLevel);
		int DAC_Value = RoundInt(((v0 + 2.5) * 4096.0 / 5.0));
		DAC_Value = max(0, min(4095, DAC_Value));
		v0 = (5.0 * double(DAC_Value) / 4096.0) - 2.5;
		m_GateLevel.Format(" %6.4f", v0);
		m_GateLevel =  lr.TrimTrailingZeros((LPCTSTR)m_GateLevel);
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeGateDivider() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollGateDivider(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusGateDivider() 
{
	CListRout lr;
	lr.TrimString(m_GateDivider);
	if (m_GateDivider.GetLength() > 0)
	{
		int t1 = min(256, max(0, RoundInt(atof(m_GateDivider))));
		m_GateDivider.Format(" %1d",t1);
		UpdateData(FALSE);
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangePresetValue() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollPresetValue(WPARAM, LPARAM)
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

void CG05p4MasterPP::OnKillfocusPresetValue() 
{
	CListRout lr;
	lr.TrimString(m_PresetValue);
	if (m_PresetValue.GetLength() > 0)
	{
		_int64 t1 = max(1, RoundInt_64(atof(m_PresetValue)));
		m_PresetValue.Format(" %1.0f",double(t1));
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeBurst() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollBurst(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_BurstED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_BurstED.GetSel(nStartChar, nEndChar);
			m_Burst = lr.ScrollInteger(m_Burst, nEndChar, 
								m_BurstED.PresentCharacter, m_BurstED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_BurstED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusBurst() 
{
	CListRout lr;
	lr.TrimString(m_Burst);
	if (m_Burst.GetLength() > 0)
	{
		int t1 = RoundInt(atof(m_Burst));
		if (t1 > 0)
			m_Burst.Format(" %1d",t1);
		else
			m_Burst = _T("");
		UpdateData(FALSE);
	}
	CheckHardwareControls();
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnChangeDelaySecondary() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

LRESULT CG05p4MasterPP::OnScrollDelaySecondary(WPARAM, LPARAM)
{
	CListRout lr;
	switch (m_DelaySecondaryED.PresentCharacter)
	{
		case 38:
		case 40:
			int nStartChar;
			int nEndChar;
			m_DelaySecondaryED.GetSel(nStartChar, nEndChar);
			m_DelaySecondary = lr.ScrollInteger(m_DelaySecondary, nEndChar, 
								m_DelaySecondaryED.PresentCharacter, m_DelaySecondaryED.PresentCount);
			if (nEndChar >= 0)
			{
				SetModified();
				*p_DataModified = TRUE;
				UpdateData(FALSE);
				m_DelaySecondaryED.SetSel(nEndChar, nEndChar);
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

void CG05p4MasterPP::OnKillfocusDelaySecondary() 
{
	CListRout lr;
	lr.TrimString(m_DelaySecondary);
	if (m_DelaySecondary.GetLength() > 0)
	{
		int t1 = RoundInt(atof(m_DelaySecondary));
		if (t1 > 0)
			m_DelaySecondary.Format(" %1d",t1);
		else
			m_DelaySecondary = _T("");
		UpdateData(FALSE);
	}
	b_FastApply = FALSE;
}

void CG05p4MasterPP::OnAB_Xor() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_AB_Xor)
	{
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_AB_Or || m_AB_And))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnAB_Or() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_AB_Or)
	{
		m_AB_Xor = FALSE;
		m_AB_And = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_AB_Xor || m_AB_And))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnAB_And() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_AB_And)
	{
		m_AB_Or = FALSE;
		m_AB_Xor = FALSE;
		m_GateAB = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_AB_Or || m_AB_Xor))
			m_GateAB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnGateCD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateCD)
	{
		if (!(m_CD_Xor || m_CD_Or || m_CD_And))
			m_CD_Xor = TRUE;
		CheckGateChannels();
	}
	else
	{
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnCD_Xor() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_CD_Xor)
	{
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		m_GateCD = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_CD_Or || m_CD_And))
			m_GateCD = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnCD_Or() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_CD_Or)
	{
		m_CD_Xor = FALSE;
		m_CD_And = FALSE;
		m_GateCD = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_CD_Xor || m_CD_And))
			m_GateCD = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnCD_And() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_CD_And)
	{
		m_CD_Or = FALSE;
		m_CD_Xor = FALSE;
		m_GateCD = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_CD_Or || m_CD_Xor))
			m_GateCD = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnGateEF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_GateEF)
	{
		if (!(m_EF_Xor || m_EF_Or || m_EF_And))
			m_EF_Xor = TRUE;
		CheckGateChannels();
	}
	else
	{
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnEF_Xor() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_EF_Xor)
	{
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		m_GateEF = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_EF_Or || m_EF_And))
			m_GateEF = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnEF_Or() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_EF_Or)
	{
		m_EF_Xor = FALSE;
		m_EF_And = FALSE;
		m_GateEF = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_EF_Xor || m_EF_And))
			m_GateEF = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnEF_And() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	if (m_EF_And)
	{
		m_EF_Or = FALSE;
		m_EF_Xor = FALSE;
		m_GateEF = TRUE;
		CheckGateChannels();
	}
	else
	{
		if (!(m_EF_Or || m_EF_Xor))
			m_GateEF = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnPrimaryLocalA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryLocalB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryLocalC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryLocalD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryLocalE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryLocalF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryLocalF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceLocalF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnPrimaryBusF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnSecondaryBusF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_A & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_B & 0x77) == 0x0)
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_C & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_D & 0x77) == 0x0)
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_E & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnForceBusF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
	CheckHardwareControls();
	if ((GoSignal_F & 0x77) == 0x0)
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
}

void CG05p4MasterPP::OnInhibitA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnInhibitB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnInhibitC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnInhibitD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnInhibitE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnInhibitF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnSynchBurst()
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnStbkLocA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkLocB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkLocC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkLocD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkLocE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkLocF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStbkBusF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnChangeStbkRefA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefA() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefA)))
	{
		int Param = RoundInt(atof(m_StbkRefA));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefA.Format(" %d", Param);
		else
		{
			m_StbkRefA = _T("");
			m_CircleA = FALSE;
			m_StbkLocA = FALSE;
			m_StbkBusA = FALSE;
		}
	}
	else
	{
		m_StbkRefA = _T("");
		m_CircleA = FALSE;
		m_StbkLocA = FALSE;
		m_StbkBusA = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStbkRefB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefB() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefB)))
	{
		int Param = RoundInt(atof(m_StbkRefB));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefB.Format(" %d", Param);
		else
		{
			m_StbkRefB = _T("");
			m_CircleB = FALSE;
			m_StbkLocB = FALSE;
			m_StbkBusB = FALSE;
		}
	}
	else
	{
		m_StbkRefB = _T("");
		m_CircleB = FALSE;
		m_StbkLocB = FALSE;
		m_StbkBusB = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStbkRefC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefC() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefC)))
	{
		int Param = RoundInt(atof(m_StbkRefC));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefC.Format(" %d", Param);
		else
		{
			m_StbkRefC = _T("");
			m_CircleC = FALSE;
			m_StbkLocC = FALSE;
			m_StbkBusC = FALSE;
		}
	}
	else
	{
		m_StbkRefC = _T("");
		m_CircleC = FALSE;
		m_StbkLocC = FALSE;
		m_StbkBusC = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStbkRefD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefD() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefD)))
	{
		int Param = RoundInt(atof(m_StbkRefD));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefD.Format(" %d", Param);
		else
		{
			m_StbkRefD = _T("");
			m_CircleD = FALSE;
			m_StbkLocD = FALSE;
			m_StbkBusD = FALSE;
		}
	}
	else
	{
		m_StbkRefD = _T("");
		m_CircleD = FALSE;
		m_StbkLocD = FALSE;
		m_StbkBusD = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStbkRefE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefE() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefE)))
	{
		int Param = RoundInt(atof(m_StbkRefE));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefE.Format(" %d", Param);
		else
		{
			m_StbkRefE = _T("");
			m_CircleE = FALSE;
			m_StbkLocE = FALSE;
			m_StbkBusE = FALSE;
		}
	}
	else
	{
		m_StbkRefE = _T("");
		m_CircleE = FALSE;
		m_StbkLocE = FALSE;
		m_StbkBusE = FALSE;
	}
	UpdateData(FALSE);
}

void CG05p4MasterPP::OnChangeStbkRefF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
}

void CG05p4MasterPP::OnKillfocusStbkRefF() 
{
	CListRout lr;
	if ((p_G0xData->FpgaMemoryList.NoParameters > 0) && (lr.Numeric(m_StbkRefF)))
	{
		int Param = RoundInt(atof(m_StbkRefF));
		if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
			m_StbkRefF.Format(" %d", Param);
		else
		{
			m_StbkRefF = _T("");
			m_CircleF = FALSE;
			m_StbkLocF = FALSE;
			m_StbkBusF = FALSE;
		}
	}
	else
	{
		m_StbkRefF = _T("");
		m_CircleF = FALSE;
		m_StbkLocF = FALSE;
		m_StbkBusF = FALSE;
	}
	UpdateData(FALSE);
}


void CG05p4MasterPP::OnStartLocA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartLocB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartLocC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartLocD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartLocE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartLocF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnStartBusF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnCircleF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaA() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaB() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaC() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaD() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaE() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnE_EnaF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnF_EnaF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::OnBusEnaF() 
{
	UpdateData(TRUE);
	SetModified();
	*p_DataModified = TRUE;
	UpdateGoSignals();
}

void CG05p4MasterPP::DiscretizeValues()
{
	CListRout lr;
	double t0,t1,v0;
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
	lr.TrimString(m_DelayC);
	if (m_DelayC.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayC) == 1)
		{
			if (lr.Numeric(m_DelayC))
			{
				t0 = atof(m_DelayC);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayC.Format(" %8.6f",t0);
				m_DelayC =  lr.TrimTrailingZeros((LPCTSTR) m_DelayC);
			}
			else
				m_DelayC = p_G0xData->AllowedParameter((LPCTSTR)m_DelayC);
		}
		else
			m_DelayC = " " + m_DelayC;
	}
	lr.TrimString(m_DelayD);
	if (m_DelayD.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayD) == 1)
		{
			if (lr.Numeric(m_DelayD))
			{
				t0 = atof(m_DelayD);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayD.Format(" %8.6f",t0);
				m_DelayD =  lr.TrimTrailingZeros((LPCTSTR) m_DelayD);
			}
			else
				m_DelayD = p_G0xData->AllowedParameter((LPCTSTR)m_DelayD);
		}
		else
			m_DelayD = " " + m_DelayD;
	}
	lr.TrimString(m_DelayE);
	if (m_DelayE.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayE) == 1)
		{
			if (lr.Numeric(m_DelayE))
			{
				t0 = atof(m_DelayE);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayE.Format(" %8.6f",t0);
				m_DelayE =  lr.TrimTrailingZeros((LPCTSTR) m_DelayE);
			}
			else
				m_DelayE = p_G0xData->AllowedParameter((LPCTSTR)m_DelayE);
		}
		else
			m_DelayE = " " + m_DelayE;
	}
	lr.TrimString(m_DelayF);
	if (m_DelayF.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_DelayF) == 1)
		{
			if (lr.Numeric(m_DelayF))
			{
				t0 = atof(m_DelayF);
				t0 = p_G0xData->DelayLimit(t0, m_DG_Number);
				m_DelayF.Format(" %8.6f",t0);
				m_DelayF =  lr.TrimTrailingZeros((LPCTSTR) m_DelayF);
			}
			else
				m_DelayF = p_G0xData->AllowedParameter((LPCTSTR)m_DelayF);
		}
		else
			m_DelayF = " " + m_DelayF;
	}

	lr.TrimString(m_WidthA);
	if (m_WidthA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthA) == 1)
		{
			if (lr.Numeric(m_WidthA))
			{
				t0 = atof(m_WidthA);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthA.Format(" %8.6f",t0);
				m_WidthA =  lr.TrimTrailingZeros((LPCTSTR) m_WidthA);
			}
			else
				m_WidthA = p_G0xData->AllowedParameter((LPCTSTR)m_WidthA);
		}
		else
			m_WidthA = " " + m_WidthA;
	}
	lr.TrimString(m_WidthB);
	if (m_WidthB.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthB) == 1)
		{
			if (lr.Numeric(m_WidthB))
			{
				t0 = atof(m_WidthB);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthB.Format(" %8.6f",t0);
				m_WidthB =  lr.TrimTrailingZeros((LPCTSTR) m_WidthB);
			}
			else
				m_WidthB = p_G0xData->AllowedParameter((LPCTSTR)m_WidthB);
		}
		else
			m_WidthB = " " + m_WidthB;
	}
	lr.TrimString(m_WidthC);
	if (m_WidthC.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthC) == 1)
		{
			if (lr.Numeric(m_WidthC))
			{
				t0 = atof(m_WidthC);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthC.Format(" %8.6f",t0);
				m_WidthC =  lr.TrimTrailingZeros((LPCTSTR) m_WidthC);
			}
			else
				m_WidthC = p_G0xData->AllowedParameter((LPCTSTR)m_WidthC);
		}
		else
			m_WidthC = " " + m_WidthC;
	}
	lr.TrimString(m_WidthD);
	if (m_WidthD.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthD) == 1)
		{
			if (lr.Numeric(m_WidthD))
			{
				t0 = atof(m_WidthD);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthD.Format(" %8.6f",t0);
				m_WidthD =  lr.TrimTrailingZeros((LPCTSTR) m_WidthD);
			}
			else
				m_WidthD = p_G0xData->AllowedParameter((LPCTSTR)m_WidthD);
		}
		else
			m_WidthD = " " + m_WidthD;
	}
	lr.TrimString(m_WidthE);
	if (m_WidthE.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthE) == 1)
		{
			if (lr.Numeric(m_WidthE))
			{
				t0 = atof(m_WidthE);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthE.Format(" %8.6f",t0);
				m_WidthE =  lr.TrimTrailingZeros((LPCTSTR) m_WidthE);
			}
			else
				m_WidthE = p_G0xData->AllowedParameter((LPCTSTR)m_WidthE);
		}
		else
			m_WidthE = " " + m_WidthE;
	}
	lr.TrimString(m_WidthF);
	if (m_WidthF.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_WidthF) == 1)
		{
			if (lr.Numeric(m_WidthF))
			{
				t0 = atof(m_WidthF);
				t0 = p_G0xData->RoundWidth(t0, m_DG_Number);
				m_WidthF.Format(" %8.6f",t0);
				m_WidthF =  lr.TrimTrailingZeros((LPCTSTR) m_WidthF);
			}
			else
				m_WidthF = p_G0xData->AllowedParameter((LPCTSTR)m_WidthF);
		}
		else
			m_WidthF = " " + m_WidthF;
	}

	lr.TrimString(m_ModuloA);
	if (m_ModuloA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloA) == 1)
		{
			if (lr.Numeric(m_ModuloA))
			{
				signed long modulo = RoundInt(atof(m_ModuloA));
				modulo = min(0xFFFFFFFF, max(0, modulo));
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
				signed long modulo = RoundInt(atof(m_ModuloB));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloB.Format(" %d", modulo);
			}
			else
				m_ModuloB = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloB);
		}
	}
	lr.TrimString(m_ModuloC);
	if (m_ModuloC.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloC) == 1)
		{
			if (lr.Numeric(m_ModuloC))
			{
				signed long modulo = RoundInt(atof(m_ModuloC));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloC.Format(" %d", modulo);
			}
			else
				m_ModuloC = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloC);
		}
	}
	lr.TrimString(m_ModuloD);
	if (m_ModuloD.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloD) == 1)
		{
			if (lr.Numeric(m_ModuloD))
			{
				signed long modulo = RoundInt(atof(m_ModuloD));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloD.Format(" %d", modulo);
			}
			else
				m_ModuloD = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloD);
		}
	}
	lr.TrimString(m_ModuloE);
	if (m_ModuloE.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloE) == 1)
		{
			if (lr.Numeric(m_ModuloE))
			{
				signed long modulo = RoundInt(atof(m_ModuloE));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloE.Format(" %d", modulo);
			}
			else
				m_ModuloE = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloE);
		}
	}
	lr.TrimString(m_ModuloF);
	if (m_ModuloF.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_ModuloF) == 1)
		{
			if (lr.Numeric(m_ModuloF))
			{
				signed long modulo = RoundInt(atof(m_ModuloF));
				modulo = min(0xFFFFFFFF, max(0, modulo));
				m_ModuloF.Format(" %d", modulo);
			}
			else
				m_ModuloF = p_G0xData->AllowedParameter((LPCTSTR)m_ModuloF);
		}
	}

	lr.TrimString(m_OffsetA);
	if (m_OffsetA.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetA) == 1)
		{
			if (lr.Numeric(m_OffsetA))
			{
				signed long offset = RoundInt(atof(m_OffsetA));
				offset = min(0xFFFFFFFF, max(0, offset));
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
				signed long offset = RoundInt(atof(m_OffsetB));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetB.Format(" %d", offset);
			}
			else
				m_OffsetB = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetB);
		}
	}
	lr.TrimString(m_OffsetC);
	if (m_OffsetC.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetC) == 1)
		{
			if (lr.Numeric(m_OffsetC))
			{
				signed long offset = RoundInt(atof(m_OffsetC));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetC.Format(" %d", offset);
			}
			else
				m_OffsetC = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetC);
		}
	}
	lr.TrimString(m_OffsetD);
	if (m_OffsetD.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetD) == 1)
		{
			if (lr.Numeric(m_OffsetD))
			{
				signed long offset = RoundInt(atof(m_OffsetD));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetD.Format(" %d", offset);
			}
			else
				m_OffsetD = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetD);
		}
	}
	lr.TrimString(m_OffsetE);
	if (m_OffsetE.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetE) == 1)
		{
			if (lr.Numeric(m_OffsetE))
			{
				signed long offset = RoundInt(atof(m_OffsetE));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetE.Format(" %d", offset);
			}
			else
				m_OffsetE = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetE);
		}
	}
	lr.TrimString(m_OffsetF);
	if (m_OffsetF.GetLength() > 0)
	{
		if (lr.NumberCharacterGroups((LPCTSTR)m_OffsetF) == 1)
		{
			if (lr.Numeric(m_OffsetF))
			{
				signed long offset = RoundInt(atof(m_OffsetF));
				offset = min(0xFFFFFFFF, max(0, offset));
				m_OffsetF.Format(" %d", offset);
			}
			else
				m_OffsetF = p_G0xData->AllowedParameter((LPCTSTR)m_OffsetF);
		}
	}

	
	lr.TrimString(m_PresetValue);
	if (m_PresetValue.GetLength() > 0)
	{
		int t1 = max(1, RoundInt(atof(m_PresetValue)));
		m_PresetValue.Format(" %1d",t1);
	}
	
	lr.TrimString(m_Burst);
	if (m_Burst.GetLength() > 0)
	{
		int t1 = max(1, RoundInt(atof(m_Burst)));
		m_Burst.Format(" %1d",t1);
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
				t1 = p_G0xData->RoundRepCounter(atof(m_InhibitTrigger), m_DG_Number);
				m_InhibitTrigger.Format(" %8.6f",t1);
				m_InhibitTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_InhibitTrigger);
			}
			else
				m_InhibitTrigger = p_G0xData->AllowedParameter((LPCTSTR)m_InhibitTrigger);
		}
		else
			m_InhibitTrigger = " " + m_InhibitTrigger;
	}
	
	lr.TrimString(m_GateDelay);
	if (m_GateDelay.GetLength() > 0)
	{
		t1 = p_G0xData->RoundGateDelay(atof(m_GateDelay), m_DG_Number);
		m_GateDelay.Format(" %8.6f",t1);
		m_GateDelay =  lr.TrimTrailingZeros((LPCTSTR)m_GateDelay);
	}

	lr.TrimString(m_ForceTrigger);
	if (m_ForceTrigger.GetLength() > 0)
	{
		t1 = p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger =  lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
	}
	int DAC_Value;
	lr.TrimString(m_TriggerLevel);
	if (m_TriggerLevel.GetLength() > 0)
	{
		v0 = atof(m_TriggerLevel);
		DAC_Value = RoundInt(((v0 + 2.5) * 4096.0 / 5.0));
		DAC_Value = max(0, min(4095, DAC_Value));
		v0 = (5.0 * double(DAC_Value) / 4096.0) - 2.5;
		m_TriggerLevel.Format(" %6.4f", v0);
		m_TriggerLevel =  lr.TrimTrailingZeros((LPCTSTR)m_TriggerLevel);
	}
	lr.TrimString(m_GateLevel);
	if (m_GateLevel.GetLength() > 0)
	{
		v0 = atof(m_GateLevel);
		DAC_Value = RoundInt(((v0 + 2.5) * 4096.0 / 5.0));
		DAC_Value = max(0, min(4095, DAC_Value));
		v0 = (5.0 * double(DAC_Value) / 4096.0) - 2.5;
		m_GateLevel.Format(" %6.4f", v0);
		m_GateLevel =  lr.TrimTrailingZeros((LPCTSTR)m_GateLevel);
	}
	if (b_PageActive)
		UpdateData(FALSE);
}

BOOL CG05p4MasterPP::DistributeVariables(DG_Type* p_DG)
{
	CString jstr;
	double t1;
	m_Delay_AED.MessageNumber = WM_USER_REQUEST_A;
	m_Delay_AED.p_ParentWindow = this;
	m_Delay_BED.MessageNumber = WM_USER_REQUEST_B;
	m_Delay_BED.p_ParentWindow = this;
	m_Delay_CED.MessageNumber = WM_USER_REQUEST_C;
	m_Delay_CED.p_ParentWindow = this;
	m_Delay_DED.MessageNumber = WM_USER_REQUEST_D;
	m_Delay_DED.p_ParentWindow = this;
	m_Delay_EED.MessageNumber = WM_USER_REQUEST_E;
	m_Delay_EED.p_ParentWindow = this;
	m_Delay_FED.MessageNumber = WM_USER_REQUEST_F;
	m_Delay_FED.p_ParentWindow = this;
	m_Width_AED.MessageNumber = WM_USER_REQUEST_W_A;
	m_Width_AED.p_ParentWindow = this;
	m_Width_BED.MessageNumber = WM_USER_REQUEST_W_B;
	m_Width_BED.p_ParentWindow = this;
	m_Width_CED.MessageNumber = WM_USER_REQUEST_W_C;
	m_Width_CED.p_ParentWindow = this;
	m_Width_DED.MessageNumber = WM_USER_REQUEST_W_D;
	m_Width_DED.p_ParentWindow = this;
	m_Width_EED.MessageNumber = WM_USER_REQUEST_W_E;
	m_Width_EED.p_ParentWindow = this;
	m_Width_FED.MessageNumber = WM_USER_REQUEST_W_F;
	m_Width_FED.p_ParentWindow = this;
	m_ModuloAED.MessageNumber = WM_USER_REQUEST_M_A;
	m_ModuloAED.p_ParentWindow = this;
	m_ModuloBED.MessageNumber = WM_USER_REQUEST_M_B;
	m_ModuloBED.p_ParentWindow = this;
	m_ModuloCED.MessageNumber = WM_USER_REQUEST_M_C;
	m_ModuloCED.p_ParentWindow = this;
	m_ModuloDED.MessageNumber = WM_USER_REQUEST_M_D;
	m_ModuloDED.p_ParentWindow = this;
	m_ModuloEED.MessageNumber = WM_USER_REQUEST_M_E;
	m_ModuloEED.p_ParentWindow = this;
	m_ModuloFED.MessageNumber = WM_USER_REQUEST_M_F;
	m_ModuloFED.p_ParentWindow = this;
	m_OffsetAED.MessageNumber = WM_USER_REQUEST_O_A;
	m_OffsetAED.p_ParentWindow = this;
	m_OffsetBED.MessageNumber = WM_USER_REQUEST_O_B;
	m_OffsetBED.p_ParentWindow = this;
	m_OffsetCED.MessageNumber = WM_USER_REQUEST_O_C;
	m_OffsetCED.p_ParentWindow = this;
	m_OffsetDED.MessageNumber = WM_USER_REQUEST_O_D;
	m_OffsetDED.p_ParentWindow = this;
	m_OffsetEED.MessageNumber = WM_USER_REQUEST_O_E;
	m_OffsetEED.p_ParentWindow = this;
	m_OffsetFED.MessageNumber = WM_USER_REQUEST_O_F;
	m_OffsetFED.p_ParentWindow = this;
	m_InhibitTriggerED.MessageNumber = WM_USER_REQUEST_PRD;
	m_InhibitTriggerED.p_ParentWindow = this;
	m_InhibitSecondaryED.MessageNumber = WM_USER_REQUEST_INS;
	m_InhibitSecondaryED.p_ParentWindow = this;
	m_DelaySecondaryED.MessageNumber = WM_USER_REQUEST_DES;
	m_DelaySecondaryED.p_ParentWindow = this;
	m_GateDelayED.MessageNumber = WM_USER_REQUEST_GDL;
	m_GateDelayED.p_ParentWindow = this;
	m_StepBackED.MessageNumber = WM_USER_REQUEST_SBC;
	m_StepBackED.p_ParentWindow = this;
	m_ForceTriggerED.MessageNumber = WM_USER_REQUEST_FTR;
	m_ForceTriggerED.p_ParentWindow = this;
	m_TriggerLevelED.MessageNumber = WM_USER_REQUEST_TLV;
	m_TriggerLevelED.p_ParentWindow = this;
	m_GateLevelED.MessageNumber = WM_USER_REQUEST_GLV;
	m_GateLevelED.p_ParentWindow = this;
	m_GateDividerED.MessageNumber = WM_USER_REQUEST_GD;
	m_GateDividerED.p_ParentWindow = this;
	m_PresetValueED.MessageNumber = WM_USER_REQUEST_PVA;
	m_PresetValueED.p_ParentWindow = this;
	m_BurstED.MessageNumber = WM_USER_REQUEST_BCT;
	m_BurstED.p_ParentWindow = this;
	b_FastApply = FALSE;

	CListRout lr;
	m_DG_Product = p_DG->Control.DG_Product;
	b_Master = p_DG->Master;
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
	C_Name = lr.ReadMemo(p_DG->C_Name);
	if (C_Name.GetLength() > 0)
		m_C_Name = C_Name;
	else
		m_C_Name = _T("C  ");
	D_Name = lr.ReadMemo(p_DG->D_Name);
	if (D_Name.GetLength() > 0)
		m_D_Name = D_Name;
	else
		m_D_Name = _T("D  ");
	E_Name = lr.ReadMemo(p_DG->E_Name);
	if (E_Name.GetLength() > 0)
		m_E_Name = E_Name;
	else
		m_E_Name = _T("E  ");
	F_Name = lr.ReadMemo(p_DG->F_Name);
	if (F_Name.GetLength() > 0)
		m_F_Name = F_Name;
	else
		m_F_Name = _T("F  ");
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

	m_GateAB = TRUE;
	m_AB_Xor = FALSE;
	m_AB_Or = FALSE;
	m_AB_And = FALSE;
	if ((p_DG->Control.GateFunction & 0x30000) == AB_XOR)
		m_AB_Xor = TRUE;
	else
	{
		if ((p_DG->Control.GateFunction & 0x30000) == AB_OR)
			m_AB_Or = TRUE;
		else
		{
			if ((p_DG->Control.GateFunction & 0x30000) == AB_AND)
				m_AB_And = TRUE;
			else
				m_GateAB = FALSE;
		}
	}
	m_GateCD = TRUE;
	m_CD_Xor = FALSE;
	m_CD_Or = FALSE;
	m_CD_And = FALSE;
	if ((p_DG->Control.GateFunction & 0xC0000) == CD_XOR)
		m_CD_Xor = TRUE;
	else
	{
		if ((p_DG->Control.GateFunction & 0xC0000) == CD_OR)
			m_CD_Or = TRUE;
		else
		{
			if ((p_DG->Control.GateFunction & 0xC0000) == CD_AND)
				m_CD_And = TRUE;
			else
				m_GateCD = FALSE;
		}
	}
	m_GateEF = TRUE;
	m_EF_Xor = FALSE;
	m_EF_Or = FALSE;
	m_EF_And = FALSE;
	if ((p_DG->Control.GateFunction & 0x300000) == EF_XOR)
		m_EF_Xor = TRUE;
	else
	{
		if ((p_DG->Control.GateFunction & 0x300000) == EF_OR)
			m_EF_Or = TRUE;
		else
		{
			if ((p_DG->Control.GateFunction & 0x300000) == EF_AND)
				m_EF_And = TRUE;
			else
				m_GateEF = FALSE;
		}
	}

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
		m_GateLevel.Format(" %6.4f", p_DG->Control.DT.GateLevel);
		m_GateLevel =  lr.TrimTrailingZeros((LPCTSTR)m_GateLevel);
	}
	else
	{
		m_GateDivider = _T("");
		m_GateLevel = _T("");
	}
	if ((p_DG->Control.DT.MS_Bus & GateBurstSynch) != 0x0)
		m_SynchBurst = TRUE;
	if (p_DG->Control.DT.GateDelay > 0.0)
	{
		t1 = p_G0xData->RoundGateDelay(p_DG->Control.DT.GateDelay, m_DG_Number);
		m_GateDelay.Format(" %8.6f",t1);
		m_GateDelay = lr.TrimTrailingZeros((LPCTSTR)m_GateDelay);
	}
	else
		m_GateDelay = _T("");
	if (p_DG->Control.DT.BurstCounter > 1)
		m_Burst.Format(" %d", max(0, p_DG->Control.DT.BurstCounter));
	else
		m_Burst = _T("");
	if (p_DG->Control.DT.DelaySecondary > 0)
		m_DelaySecondary.Format(" %d", max(0, p_DG->Control.DT.DelaySecondary));
	else
		m_DelaySecondary = _T("");
	m_Ignore = FALSE;
	m_Memorize = FALSE;
	m_SynchronizeGate = FALSE;
	if (m_GatePositive || m_GateNegative)
	{
		if (p_DG->Control.DT.IgnoreGate)
			m_Ignore = TRUE;
		else
			m_Memorize = TRUE;
		if (p_DG->Control.DT.SynchronizeGate)
			m_SynchronizeGate = TRUE;
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
	if (p_DG->VarLoc.RepSecondary >= 0)
	{
		if (p_DG->VarLoc.RepSecondary < MaxParameters)
		{
			m_InhibitSecondary.Format(" X%d", (p_DG->VarLoc.RepSecondary + 1));
		}
	}
	else
	{
		if (p_DG->VarLoc.RepSecondary == -1)
		{
			if (p_DG->Control.DT.InhibitSecondary >= 0.0)
			{
				t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.InhibitSecondary, m_DG_Number);
				m_InhibitSecondary.Format(" %8.6f",t1);
				m_InhibitSecondary = lr.TrimTrailingZeros((LPCTSTR)m_InhibitSecondary);
			}
		}
		else
		{
			m_InhibitSecondary = lr.ReadMemo(p_DG->VarEqu.RepSecondary);
		}
	}
	m_ForceTrigger =  _T("");
	b_ForceTriggerActive = FALSE;

	if (p_DG->Control.DT.ForceTrigger >= 0.0)
	{
		t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.ForceTrigger, m_DG_Number);
		m_ForceTrigger.Format(" %8.6f",t1);
		m_ForceTrigger = lr.TrimTrailingZeros((LPCTSTR)m_ForceTrigger);
		b_ForceTriggerActive = TRUE;
	}
	if (p_DG->Control.DT.StepBackTime >= 0.0)
	{
		t1 = p_G0xData->RoundRepCounter(p_DG->Control.DT.StepBackTime, m_DG_Number);
		m_StepBack.Format(" %8.6f",t1);
		m_StepBack = lr.TrimTrailingZeros((LPCTSTR)m_StepBack);
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
		m_PresetValue.Format(" %1d", p_DG->Control.DT.PresetLong);
	else
		m_PresetValue = _T("");

	BOOL b_ChannelActive;
	b_ChannelActive = FALSE;
	m_PrimaryLocalA = FALSE;
	m_SecondaryLocalA = FALSE;
	m_ForceLocalA = FALSE;
	m_PrimaryBusA = FALSE;
	m_SecondaryBusA = FALSE;
	m_ForceBusA = FALSE;
	m_InhibitA = FALSE;
	m_StartLocA = FALSE;
	m_StartBusA = FALSE;
	m_CircleA = FALSE;
	m_SynchA = FALSE;
	m_StbkLocA = FALSE;
	m_StbkBusA = FALSE;
	m_StbkRefA = _T("");
	m_E_EnaA = FALSE;
	m_F_EnaA = FALSE;
	m_BusEnaA = FALSE;
	m_DelayA = _T("");
	m_WidthA = _T("");
	m_ModuloA = _T("");
	m_OffsetA = _T("");
	GoSignal_A = p_DG->Control.A.GoSignal;
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
				m_PrimaryBusA = TRUE;
			if ((p_DG->Control.A.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusA = TRUE;
			if ((p_DG->Control.A.GoSignal & MasterForce) != 0x0)
				m_ForceBusA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalA = TRUE;
			if ((p_DG->Control.A.GoSignal & LocalForce) != 0x0)
				m_ForceLocalA = TRUE;
			if ((p_DG->Control.A.GoSignal & InhibitLocal) != 0x0)
				m_InhibitA = TRUE;
			if ((p_DG->Control.A.GoSignal & StartLocal) != 0x0)
				m_StartLocA = TRUE;
			if ((p_DG->Control.A.GoSignal & StartBus) != 0x0)
				m_StartBusA = TRUE;
			if ((p_DG->Control.A.GoSignal & SynchReload) != 0x0)
				m_SynchA = TRUE;
			if ((p_DG->Control.A.GoSignal & EnableFromE) != 0x0)
				m_E_EnaA = TRUE;
			if ((p_DG->Control.A.GoSignal & EnableFromF) != 0x0)
				m_F_EnaA = TRUE;
			if ((p_DG->Control.A.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaA = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.A.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.A.PulseWidth < MaxParameters)
					m_WidthA.Format(" X%d", (p_DG->VarLoc.A.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.A.PulseWidth == -1)
				{
					if (p_DG->Control.A.PulseWidth[0] >= 0.0)
					{
						m_WidthA.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.A.PulseWidth[0], m_DG_Number));
						m_WidthA = lr.TrimTrailingZeros((LPCTSTR) m_WidthA);
					}
				}
				else
					m_WidthA = lr.ReadMemo(p_DG->VarEqu.A.PulseWidth);
			}
			if (p_DG->VarLoc.A.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.A.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefA.Format(" %d", RoundInt(atof(jstr)));
				}
				if ((p_DG->Control.A.GoSignal & StepBackLocal) != 0x0)
					m_StbkLocA = TRUE;
				if ((p_DG->Control.A.GoSignal & StepBackBus) != 0x0)
					m_StbkBusA = TRUE;
				if ((p_DG->Control.A.GoSignal & RunCircle) != 0x0)
					m_CircleA = TRUE;
			}
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
	m_PrimaryLocalB = FALSE;
	m_SecondaryLocalB = FALSE;
	m_ForceLocalB = FALSE;
	m_PrimaryBusB = FALSE;
	m_SecondaryBusB = FALSE;
	m_ForceBusB = FALSE;
	m_InhibitB = FALSE;
	m_StartLocB = FALSE;
	m_StartBusB = FALSE;
	m_CircleB = FALSE;
	m_SynchB = FALSE;
	m_StbkLocB = FALSE;
	m_StbkBusB = FALSE;
	m_StbkRefB = _T("");
	m_E_EnaB = FALSE;
	m_F_EnaB = FALSE;
	m_BusEnaB = FALSE;
	m_DelayB = _T("");
	m_WidthB = _T("");
	m_ModuloB = _T("");
	m_OffsetB = _T("");
	GoSignal_B = p_DG->Control.B.GoSignal;
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
				m_PrimaryBusB = TRUE;
			if ((p_DG->Control.B.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusB = TRUE;
			if ((p_DG->Control.B.GoSignal & MasterForce) != 0x0)
				m_ForceBusB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalB = TRUE;
			if ((p_DG->Control.B.GoSignal & LocalForce) != 0x0)
				m_ForceLocalB = TRUE;
			if ((p_DG->Control.B.GoSignal & InhibitLocal) != 0x0)
				m_InhibitB = TRUE;
			if ((p_DG->Control.B.GoSignal & StartLocal) != 0x0)
				m_StartLocB = TRUE;
			if ((p_DG->Control.B.GoSignal & StartBus) != 0x0)
				m_StartBusB = TRUE;
			if ((p_DG->Control.B.GoSignal & SynchReload) != 0x0)
				m_SynchB = TRUE;
			if ((p_DG->Control.B.GoSignal & EnableFromE) != 0x0)
				m_E_EnaB = TRUE;
			if ((p_DG->Control.B.GoSignal & EnableFromF) != 0x0)
				m_F_EnaB = TRUE;
			if ((p_DG->Control.B.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaB = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.B.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.B.PulseWidth < MaxParameters)
					m_WidthB.Format(" X%d", (p_DG->VarLoc.B.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.B.PulseWidth == -1)
				{
					if (p_DG->Control.B.PulseWidth[0] >= 0.0)
					{
						m_WidthB.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.B.PulseWidth[0], m_DG_Number));
						m_WidthB = lr.TrimTrailingZeros((LPCTSTR) m_WidthB);
					}
				}
				else
					m_WidthB = lr.ReadMemo(p_DG->VarEqu.B.PulseWidth);
			}
			if (p_DG->VarLoc.B.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.B.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefB.Format(" %d", RoundInt(atof(jstr)));
					if ((p_DG->Control.B.GoSignal & StepBackLocal) != 0x0)
						m_StbkLocB = TRUE;
					if ((p_DG->Control.B.GoSignal & StepBackBus) != 0x0)
						m_StbkBusB = TRUE;
					if ((p_DG->Control.B.GoSignal & RunCircle) != 0x0)
						m_CircleB = TRUE;
				}
			}
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

	b_ChannelActive = FALSE;
	m_PrimaryLocalC = FALSE;
	m_SecondaryLocalC = FALSE;
	m_ForceLocalC = FALSE;
	m_PrimaryBusC = FALSE;
	m_SecondaryBusC = FALSE;
	m_ForceBusC = FALSE;
	m_InhibitC = FALSE;
	m_StartLocC = FALSE;
	m_StartBusC = FALSE;
	m_CircleC = FALSE;
	m_SynchC = FALSE;
	m_StbkLocC = FALSE;
	m_StbkBusC = FALSE;
	m_StbkRefC = _T("");
	m_E_EnaC = FALSE;
	m_F_EnaC = FALSE;
	m_BusEnaC = FALSE;
	m_DelayC = _T("");
	m_WidthC = _T("");
	m_ModuloC = _T("");
	m_OffsetC = _T("");
	GoSignal_C = p_DG->Control.C.GoSignal;
	if ((p_DG->Control.C.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.C.FireFirst >= 0)
		{
			if (p_DG->VarLoc.C.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayC.Format(" X%d", (p_DG->VarLoc.C.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.C.FireFirst == -1)
			{
				if (p_DG->Control.C.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayC.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.C.FireFirst, m_DG_Number));
					m_DelayC = lr.TrimTrailingZeros((LPCTSTR) m_DelayC);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayC = lr.ReadMemo(p_DG->VarEqu.C.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.C.GoSignal & MasterPrimary) != 0x0)
				m_PrimaryBusC = TRUE;
			if ((p_DG->Control.C.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusC = TRUE;
			if ((p_DG->Control.C.GoSignal & MasterForce) != 0x0)
				m_ForceBusC = TRUE;
			if ((p_DG->Control.C.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalC = TRUE;
			if ((p_DG->Control.C.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalC = TRUE;
			if ((p_DG->Control.C.GoSignal & LocalForce) != 0x0)
				m_ForceLocalC = TRUE;
			if ((p_DG->Control.C.GoSignal & InhibitLocal) != 0x0)
				m_InhibitC = TRUE;
			if ((p_DG->Control.C.GoSignal & StartLocal) != 0x0)
				m_StartLocC = TRUE;
			if ((p_DG->Control.C.GoSignal & StartBus) != 0x0)
				m_StartBusC = TRUE;
			if ((p_DG->Control.C.GoSignal & SynchReload) != 0x0)
				m_SynchC = TRUE;
			if ((p_DG->Control.C.GoSignal & EnableFromE) != 0x0)
				m_E_EnaC = TRUE;
			if ((p_DG->Control.C.GoSignal & EnableFromF) != 0x0)
				m_F_EnaC = TRUE;
			if ((p_DG->Control.C.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaC = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.C.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.C.PulseWidth < MaxParameters)
					m_WidthC.Format(" X%d", (p_DG->VarLoc.C.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.C.PulseWidth == -1)
				{
					if (p_DG->Control.C.PulseWidth[0] >= 0.0)
					{
						m_WidthC.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.C.PulseWidth[0], m_DG_Number));
						m_WidthC = lr.TrimTrailingZeros((LPCTSTR) m_WidthC);
					}
				}
				else
					m_WidthC = lr.ReadMemo(p_DG->VarEqu.C.PulseWidth);
			}
			if (p_DG->VarLoc.C.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.C.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefC.Format(" %d", RoundInt(atof(jstr)));
					if ((p_DG->Control.C.GoSignal & StepBackLocal) != 0x0)
						m_StbkLocC = TRUE;
					if ((p_DG->Control.C.GoSignal & StepBackBus) != 0x0)
						m_StbkBusC = TRUE;
					if ((p_DG->Control.C.GoSignal & RunCircle) != 0x0)
						m_CircleC = TRUE;
				}
			}
			if (p_DG->VarLoc.C.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.C.OutputModulo < MaxParameters)
					m_ModuloC.Format(" X%d", (p_DG->VarLoc.C.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.C.OutputModulo == -1)
				{
					if (p_DG->Control.C.OutputModulo > 1)
						m_ModuloC.Format(" %d", p_DG->Control.C.OutputModulo);
				}
				else
					m_ModuloC = lr.ReadMemo(p_DG->VarEqu.C.OutputModulo);
			}
			if (p_DG->VarLoc.C.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.C.OutputOffset < MaxParameters)
					m_OffsetC.Format(" X%d", (p_DG->VarLoc.C.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.C.OutputOffset == -1)
				{
					if (p_DG->Control.C.OutputOffset > 0)
						m_OffsetC.Format(" %d", p_DG->Control.C.OutputOffset);
				}
				else
					m_OffsetC = lr.ReadMemo(p_DG->VarEqu.C.OutputOffset);
			}
		}
	}

	b_ChannelActive = FALSE;
	m_PrimaryLocalD = FALSE;
	m_SecondaryLocalD = FALSE;
	m_ForceLocalD = FALSE;
	m_PrimaryBusD = FALSE;
	m_SecondaryBusD = FALSE;
	m_ForceBusD = FALSE;
	m_InhibitD = FALSE;
	m_StartLocD = FALSE;
	m_StartBusD = FALSE;
	m_CircleD = FALSE;
	m_SynchD = FALSE;
	m_StbkLocD = FALSE;
	m_StbkBusD = FALSE;
	m_StbkRefD = _T("");
	m_E_EnaD = FALSE;
	m_F_EnaD = FALSE;
	m_BusEnaD = FALSE;
	m_DelayD = _T("");
	m_WidthD = _T("");
	m_ModuloD = _T("");
	m_OffsetD = _T("");
	GoSignal_D = p_DG->Control.D.GoSignal;
	if ((p_DG->Control.D.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.D.FireFirst >= 0)
		{
			if (p_DG->VarLoc.D.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayD.Format(" X%d", (p_DG->VarLoc.D.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.D.FireFirst == -1)
			{
				if (p_DG->Control.D.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayD.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.D.FireFirst, m_DG_Number));
					m_DelayD = lr.TrimTrailingZeros((LPCTSTR) m_DelayD);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayD = lr.ReadMemo(p_DG->VarEqu.D.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.D.GoSignal & MasterPrimary) != 0x0)
				m_PrimaryBusD = TRUE;
			if ((p_DG->Control.D.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusD = TRUE;
			if ((p_DG->Control.D.GoSignal & MasterForce) != 0x0)
				m_ForceBusD = TRUE;
			if ((p_DG->Control.D.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalD = TRUE;
			if ((p_DG->Control.D.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalD = TRUE;
			if ((p_DG->Control.D.GoSignal & LocalForce) != 0x0)
				m_ForceLocalD = TRUE;
			if ((p_DG->Control.D.GoSignal & InhibitLocal) != 0x0)
				m_InhibitD = TRUE;
			if ((p_DG->Control.D.GoSignal & StartLocal) != 0x0)
				m_StartLocD = TRUE;
			if ((p_DG->Control.D.GoSignal & StartBus) != 0x0)
				m_StartBusD = TRUE;
			if ((p_DG->Control.D.GoSignal & SynchReload) != 0x0)
				m_SynchD = TRUE;
			if ((p_DG->Control.D.GoSignal & EnableFromE) != 0x0)
				m_E_EnaD = TRUE;
			if ((p_DG->Control.D.GoSignal & EnableFromF) != 0x0)
				m_F_EnaD = TRUE;
			if ((p_DG->Control.D.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaD = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.D.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.D.PulseWidth < MaxParameters)
					m_WidthD.Format(" X%d", (p_DG->VarLoc.D.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.D.PulseWidth == -1)
				{
					if (p_DG->Control.D.PulseWidth[0] >= 0.0)
					{
						m_WidthD.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.D.PulseWidth[0], m_DG_Number));
						m_WidthD = lr.TrimTrailingZeros((LPCTSTR) m_WidthD);
					}
				}
				else
					m_WidthD = lr.ReadMemo(p_DG->VarEqu.D.PulseWidth);
			}
			if (p_DG->VarLoc.D.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.D.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefD.Format(" %d", RoundInt(atof(jstr)));
					if ((p_DG->Control.D.GoSignal & StepBackLocal) != 0x0)
						m_StbkLocD = TRUE;
					if ((p_DG->Control.D.GoSignal & StepBackBus) != 0x0)
						m_StbkBusD = TRUE;
					if ((p_DG->Control.D.GoSignal & RunCircle) != 0x0)
						m_CircleD = TRUE;
				}
			}
			if (p_DG->VarLoc.D.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.D.OutputModulo < MaxParameters)
					m_ModuloD.Format(" X%d", (p_DG->VarLoc.D.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.D.OutputModulo == -1)
				{
					if (p_DG->Control.D.OutputModulo > 1)
						m_ModuloD.Format(" %d", p_DG->Control.D.OutputModulo);
				}
				else
					m_ModuloD = lr.ReadMemo(p_DG->VarEqu.D.OutputModulo);
			}
			if (p_DG->VarLoc.D.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.D.OutputOffset < MaxParameters)
					m_OffsetD.Format(" X%d", (p_DG->VarLoc.D.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.D.OutputOffset == -1)
				{
					if (p_DG->Control.D.OutputOffset > 0)
						m_OffsetD.Format(" %d", p_DG->Control.D.OutputOffset);
				}
				else
					m_OffsetD = lr.ReadMemo(p_DG->VarEqu.D.OutputOffset);
			}
		}
	}

	b_ChannelActive = FALSE;
	m_PrimaryLocalE = FALSE;
	m_SecondaryLocalE = FALSE;
	m_ForceLocalE = FALSE;
	m_PrimaryBusE = FALSE;
	m_SecondaryBusE = FALSE;
	m_ForceBusE = FALSE;
	m_InhibitE = FALSE;
	m_StartLocE = FALSE;
	m_StartBusE = FALSE;
	m_CircleE = FALSE;
	m_SynchE = FALSE;
	m_StbkLocE = FALSE;
	m_StbkBusE = FALSE;
	m_StbkRefE = _T("");
	m_E_EnaE = FALSE;
	m_F_EnaE = FALSE;
	m_BusEnaE = FALSE;
	m_DelayE = _T("");
	m_WidthE = _T("");
	m_ModuloE = _T("");
	m_OffsetE = _T("");
	GoSignal_E = p_DG->Control.E.GoSignal;
	if ((p_DG->Control.E.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.E.FireFirst >= 0)
		{
			if (p_DG->VarLoc.E.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayE.Format(" X%d", (p_DG->VarLoc.E.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.E.FireFirst == -1)
			{
				if (p_DG->Control.E.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayE.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.E.FireFirst, m_DG_Number));
					m_DelayE = lr.TrimTrailingZeros((LPCTSTR) m_DelayE);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayE = lr.ReadMemo(p_DG->VarEqu.E.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.E.GoSignal & MasterPrimary) != 0x0)
				m_PrimaryBusE = TRUE;
			if ((p_DG->Control.E.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusE = TRUE;
			if ((p_DG->Control.E.GoSignal & MasterForce) != 0x0)
				m_ForceBusE = TRUE;
			if ((p_DG->Control.E.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalE = TRUE;
			if ((p_DG->Control.E.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalE = TRUE;
			if ((p_DG->Control.E.GoSignal & LocalForce) != 0x0)
				m_ForceLocalE = TRUE;
			if ((p_DG->Control.E.GoSignal & InhibitLocal) != 0x0)
				m_InhibitE = TRUE;
			if ((p_DG->Control.E.GoSignal & StartLocal) != 0x0)
				m_StartLocE = TRUE;
			if ((p_DG->Control.E.GoSignal & StartBus) != 0x0)
				m_StartBusE = TRUE;
			if ((p_DG->Control.E.GoSignal & SynchReload) != 0x0)
				m_SynchE = TRUE;
			if ((p_DG->Control.E.GoSignal & EnableFromE) != 0x0)
				m_E_EnaE = TRUE;
			if ((p_DG->Control.E.GoSignal & EnableFromF) != 0x0)
				m_F_EnaE = TRUE;
			if ((p_DG->Control.E.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaE = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.E.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.E.PulseWidth < MaxParameters)
					m_WidthE.Format(" X%d", (p_DG->VarLoc.E.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.E.PulseWidth == -1)
				{
					if (p_DG->Control.E.PulseWidth[0] >= 0.0)
					{
						m_WidthE.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.E.PulseWidth[0], m_DG_Number));
						m_WidthE = lr.TrimTrailingZeros((LPCTSTR) m_WidthE);
					}
				}
				else
					m_WidthE = lr.ReadMemo(p_DG->VarEqu.E.PulseWidth);
			}
			if (p_DG->VarLoc.E.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.E.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefE.Format(" %d", RoundInt(atof(jstr)));
					if ((p_DG->Control.E.GoSignal & StepBackLocal) != 0x0)
						m_StbkLocE = TRUE;
					if ((p_DG->Control.E.GoSignal & StepBackBus) != 0x0)
						m_StbkBusE = TRUE;
					if ((p_DG->Control.E.GoSignal & RunCircle) != 0x0)
						m_CircleE = TRUE;
				}
			}
			if (p_DG->VarLoc.E.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.E.OutputModulo < MaxParameters)
					m_ModuloE.Format(" X%d", (p_DG->VarLoc.E.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.E.OutputModulo == -1)
				{
					if (p_DG->Control.E.OutputModulo > 1)
						m_ModuloE.Format(" %d", p_DG->Control.E.OutputModulo);
				}
				else
					m_ModuloE = lr.ReadMemo(p_DG->VarEqu.E.OutputModulo);
			}
			if (p_DG->VarLoc.E.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.E.OutputOffset < MaxParameters)
					m_OffsetE.Format(" X%d", (p_DG->VarLoc.E.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.E.OutputOffset == -1)
				{
					if (p_DG->Control.E.OutputOffset > 0)
						m_OffsetE.Format(" %d", p_DG->Control.E.OutputOffset);
				}
				else
					m_OffsetE = lr.ReadMemo(p_DG->VarEqu.E.OutputOffset);
			}
		}
	}

	b_ChannelActive = FALSE;
	m_PrimaryLocalF = FALSE;
	m_SecondaryLocalF = FALSE;
	m_ForceLocalF = FALSE;
	m_PrimaryBusF = FALSE;
	m_SecondaryBusF = FALSE;
	m_ForceBusF = FALSE;
	m_InhibitF = FALSE;
	m_StartLocF = FALSE;
	m_StartBusF = FALSE;
	m_CircleF = FALSE;
	m_SynchF = FALSE;
	m_StbkLocF = FALSE;
	m_StbkBusF = FALSE;
	m_StbkRefF = _T("");
	m_E_EnaF = FALSE;
	m_F_EnaF = FALSE;
	m_BusEnaF = FALSE;
	m_DelayF = _T("");
	m_WidthF = _T("");
	m_ModuloF = _T("");
	m_OffsetF = _T("");
	GoSignal_F = p_DG->Control.F.GoSignal;
	if ((p_DG->Control.F.GoSignal & 0x77) != 0x0)
	{
		if (p_DG->VarLoc.F.FireFirst >= 0)
		{
			if (p_DG->VarLoc.F.FireFirst < MaxParameters)
			{
				b_ChannelActive = TRUE;
				m_DelayF.Format(" X%d", (p_DG->VarLoc.F.FireFirst + 1));
			}
		}
		else
		{
			if (p_DG->VarLoc.F.FireFirst == -1)
			{
				if (p_DG->Control.F.FireFirst >= 0.0)
				{
					b_ChannelActive = TRUE;
					m_DelayF.Format(" %8.6f", p_G0xData->DelayLimit(p_DG->Control.F.FireFirst, m_DG_Number));
					m_DelayF = lr.TrimTrailingZeros((LPCTSTR) m_DelayF);
				}
			}
			else
			{
				b_ChannelActive = TRUE;
				m_DelayF = lr.ReadMemo(p_DG->VarEqu.F.FireFirst);
			}
		}
		if (b_ChannelActive)
		{
			if ((p_DG->Control.F.GoSignal & MasterPrimary) != 0x0)
				m_PrimaryBusF = TRUE;
			if ((p_DG->Control.F.GoSignal & MasterSecondary) != 0x0)
				m_SecondaryBusF = TRUE;
			if ((p_DG->Control.F.GoSignal & MasterForce) != 0x0)
				m_ForceBusF = TRUE;
			if ((p_DG->Control.F.GoSignal & LocalPrimary) != 0x0)
				m_PrimaryLocalF = TRUE;
			if ((p_DG->Control.F.GoSignal & LocalSecondary) != 0x0)
				m_SecondaryLocalF = TRUE;
			if ((p_DG->Control.F.GoSignal & LocalForce) != 0x0)
				m_ForceLocalF = TRUE;
			if ((p_DG->Control.F.GoSignal & InhibitLocal) != 0x0)
				m_InhibitF = TRUE;
			if ((p_DG->Control.F.GoSignal & StartLocal) != 0x0)
				m_StartLocF = TRUE;
			if ((p_DG->Control.F.GoSignal & StartBus) != 0x0)
				m_StartBusF = TRUE;
			if ((p_DG->Control.F.GoSignal & SynchReload) != 0x0)
				m_SynchF = TRUE;
			if ((p_DG->Control.F.GoSignal & EnableFromE) != 0x0)
				m_E_EnaF = TRUE;
			if ((p_DG->Control.F.GoSignal & EnableFromF) != 0x0)
				m_F_EnaF = TRUE;
			if ((p_DG->Control.F.GoSignal & EnableFromBus) != 0x0)
				m_BusEnaF = TRUE;
		}
		if (b_ChannelActive)
		{
			if (p_DG->VarLoc.F.PulseWidth >= 0)
			{
				if (p_DG->VarLoc.F.PulseWidth < MaxParameters)
					m_WidthF.Format(" X%d", (p_DG->VarLoc.F.PulseWidth + 1));
			}
			else
			{
				if (p_DG->VarLoc.F.PulseWidth == -1)
				{
					if (p_DG->Control.F.PulseWidth[0] >= 0.0)
					{
						m_WidthF.Format(" %8.6f", p_G0xData->RoundWidth(p_DG->Control.F.PulseWidth[0], m_DG_Number));
						m_WidthF = lr.TrimTrailingZeros((LPCTSTR) m_WidthF);
					}
				}
				else
					m_WidthF = lr.ReadMemo(p_DG->VarEqu.F.PulseWidth);
			}
			if (p_DG->VarLoc.F.StepBack == -2)
			{
				jstr = lr.ReadMemo(p_DG->VarEqu.F.StepBack);
				lr.TrimString(jstr);
				if (lr.CommandType(jstr, "y", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					m_StbkRefF.Format(" %d", RoundInt(atof(jstr)));
					if ((p_DG->Control.F.GoSignal & StepBackLocal) != 0x0)
						m_StbkLocF = TRUE;
					if ((p_DG->Control.F.GoSignal & StepBackBus) != 0x0)
						m_StbkBusF = TRUE;
					if ((p_DG->Control.F.GoSignal & RunCircle) != 0x0)
						m_CircleF = TRUE;
				}
			}
			if (p_DG->VarLoc.F.OutputModulo >= 0)
			{
				if (p_DG->VarLoc.F.OutputModulo < MaxParameters)
					m_ModuloF.Format(" X%d", (p_DG->VarLoc.F.OutputModulo + 1));
			}
			else
			{
				if (p_DG->VarLoc.F.OutputModulo == -1)
				{
					if (p_DG->Control.F.OutputModulo > 1)
						m_ModuloF.Format(" %d", p_DG->Control.F.OutputModulo);
				}
				else
					m_ModuloF = lr.ReadMemo(p_DG->VarEqu.F.OutputModulo);
			}
			if (p_DG->VarLoc.F.OutputOffset >= 0)
			{
				if (p_DG->VarLoc.F.OutputOffset < MaxParameters)
					m_OffsetF.Format(" X%d", (p_DG->VarLoc.F.OutputOffset + 1));
			}
			else
			{
				if (p_DG->VarLoc.F.OutputOffset == -1)
				{
					if (p_DG->Control.F.OutputOffset > 0)
						m_OffsetF.Format(" %d", p_DG->Control.F.OutputOffset);
				}
				else
					m_OffsetF = lr.ReadMemo(p_DG->VarEqu.F.OutputOffset);
			}
		}
	}
	DiscretizeValues();
	return TRUE;
}

BOOL CG05p4MasterPP::CollectVariables(DG_Type* p_DG)
{
	//DiscretizeValues();
	CListRout lr;
	CString jstr;
	int Param;
	p_DG->ReadTriggers = m_ReadTriggers;

	p_DG->Control.GateFunction = 0x0;
	if (m_GateAB)
	{
		if (m_AB_Xor)
			p_DG->Control.GateFunction |= AB_XOR;
		if (m_AB_Or)
			p_DG->Control.GateFunction |= AB_OR;
		if (m_AB_And)
			p_DG->Control.GateFunction |= AB_AND;
	}
	if (m_GateCD)
	{
		if (m_CD_Xor)
			p_DG->Control.GateFunction |= CD_XOR;
		if (m_CD_Or)
			p_DG->Control.GateFunction |= CD_OR;
		if (m_CD_And)
			p_DG->Control.GateFunction |= CD_AND;
	}
	if (m_GateEF)
	{
		if (m_EF_Xor)
			p_DG->Control.GateFunction |= EF_XOR;
		if (m_EF_Or)
			p_DG->Control.GateFunction |= EF_OR;
		if (m_EF_And)
			p_DG->Control.GateFunction |= EF_AND;
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
			lr.WriteMemo(p_DG->VarEqu.RepCounter, (LPCTSTR)m_InhibitTrigger, 64);
		}
	}
	else
		p_DG->Control.DT.InhibitTrigger = -1.0;
	jstr = m_InhibitSecondary;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
		if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
		{
			if (lr.Numeric(jstr))
			{
				p_DG->Control.DT.InhibitSecondary = 
										p_G0xData->RoundRepCounter(atof(m_InhibitSecondary), m_DG_Number);
			}
			else
			{
				if (lr.CommandType(jstr, "x", "?"))
				{
					jstr = jstr.Right(jstr.GetLength() - 1);
					p_DG->VarLoc.RepSecondary = (RoundInt(atof(jstr)) - 1);
				}
				else
				{
					p_DG->VarLoc.RepSecondary = -2;
					lr.WriteMemo(p_DG->VarEqu.RepSecondary, (LPCTSTR)m_InhibitSecondary, 64);
				}
			}
		}
		else
		{
			p_DG->VarLoc.RepCounter = -2;
			lr.WriteMemo(p_DG->VarEqu.RepSecondary, (LPCTSTR)m_InhibitSecondary, 64);
		}
	}
	else
		p_DG->Control.DT.InhibitSecondary = -1.0;
	jstr = m_DelaySecondary;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
		p_DG->Control.DT.DelaySecondary = max(0, RoundInt(atof(m_DelaySecondary)));
	else
		p_DG->Control.DT.DelaySecondary = 0;

	jstr = m_GateDelay;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		if (lr.CheckBraceMatch((LPCTSTR)jstr))
		{
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.DT.GateDelay = p_G0xData->RoundGateDelay(atof(m_GateDelay), m_DG_Number);
			}
		}
	}
	else
		p_DG->Control.DT.GateDelay = -1.0;

	jstr = m_ForceTrigger;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		p_DG->Control.DT.ForceTrigger = 
			p_G0xData->RoundRepCounter(atof(m_ForceTrigger), m_DG_Number);
	}
	else
		p_DG->Control.DT.ForceTrigger = -1.0;
	jstr = m_StepBack;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		p_DG->Control.DT.StepBackTime = 
			p_G0xData->RoundRepCounter(atof(m_StepBack), m_DG_Number);
	}
	else
		p_DG->Control.DT.StepBackTime = -1.0;
	jstr = m_Burst;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
		p_DG->Control.DT.BurstCounter = max(1, RoundInt(atof(m_Burst)));
	else
		p_DG->Control.DT.BurstCounter = 1;

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
		if (m_SynchronizeGate)
			p_DG->Control.DT.SynchronizeGate = TRUE;
	}
	if (m_SynchBurst)
		p_DG->Control.DT.MS_Bus |= GateBurstSynch;
	else
		p_DG->Control.DT.MS_Bus &= ~GateBurstSynch;
	if (m_StopOnPreset)
	{
		jstr = m_PresetValue;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
			p_DG->Control.DT.PresetLong = RoundInt(atof(m_PresetValue));
		else
			p_DG->Control.DT.PresetLong = 0;
	}
	p_DG->Control.DT.ResetWhenDone = TRUE;
	jstr = m_TriggerLevel;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
		p_DG->Control.DT.TriggerLevel = atof(m_TriggerLevel);
	jstr = m_GateLevel;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
		p_DG->Control.DT.GateLevel = atof(m_GateLevel);
	


	p_DG->Control.A.GoSignal &= 0x188;
	p_DG->Control.A.DoneSignal = 0x0;
	p_DG->Control.A.FireFirst = -1.0;
	p_DG->Control.A.PulseWidth[0] = -1.0;
	p_DG->Control.A.StepBack[0] = 0;
	p_DG->Control.A.ListLength = 0;
	p_DG->Control.A.SetBack = -1.0;
	p_DG->Control.A.OutputModulo = 1;
	p_DG->Control.A.OutputOffset = 0;
	p_DG->VarLoc.A.FireFirst = -1;
	p_DG->VarLoc.A.PulseWidth = -1;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarLoc.A.OutputModulo = -1;
	p_DG->VarLoc.A.StepBack = -1;
	p_DG->VarEqu.A.FireFirst[0] = 0;
	p_DG->VarEqu.A.PulseWidth[0] = 0;
	p_DG->VarEqu.A.StepBack[0] = 0;
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
			p_DG->Control.A.GoSignal |= (GoSignal_A & 0x78E77);
			p_DG->Control.A.GoSignal &= (GoSignal_A | ~0x78E77);
			jstr = m_WidthA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.A.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.A.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.A.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.A.PulseWidth, (LPCTSTR)m_WidthA, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.A.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.A.PulseWidth, (LPCTSTR)m_WidthA, 64);
				}
			}
			else
				p_DG->Control.A.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.A.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.A.StepBack = -2;
					p_DG->Control.A.GoSignal |= (GoSignal_A & 0x07000);
					p_DG->Control.A.GoSignal &= (GoSignal_A | ~0x07000);
				}
			}
			jstr = m_ModuloA;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.A.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
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
						p_DG->Control.A.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
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
	p_DG->Control.B.PulseWidth[0] = -1.0;
	p_DG->Control.B.StepBack[0] = 0;
	p_DG->Control.B.ListLength = 0;
	p_DG->Control.B.SetBack = -1.0;
	p_DG->Control.B.OutputModulo = 1;
	p_DG->Control.B.OutputOffset = 0;
	p_DG->VarLoc.B.FireFirst = -1;
	p_DG->VarLoc.B.PulseWidth = -1;
	p_DG->VarLoc.B.OutputModulo = -1;
	p_DG->VarLoc.B.OutputOffset = -1;
	p_DG->VarLoc.B.StepBack = -1;
	p_DG->VarEqu.B.FireFirst[0] = 0;
	p_DG->VarEqu.B.PulseWidth[0] = 0;
	p_DG->VarEqu.B.StepBack[0] = 0;
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
			p_DG->Control.B.GoSignal |= (GoSignal_B & 0x78E77);
			p_DG->Control.B.GoSignal &= (GoSignal_B | ~0x78E77);
			jstr = m_WidthB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.B.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.B.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.B.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.B.PulseWidth, (LPCTSTR)m_WidthB, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.B.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.B.PulseWidth, (LPCTSTR)m_WidthB, 64);
				}
			}
			else
				p_DG->Control.B.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.B.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.B.StepBack = -2;
					p_DG->Control.B.GoSignal |= (GoSignal_B & 0x07000);
					p_DG->Control.B.GoSignal &= (GoSignal_B | ~0x07000);
				}
			}
			jstr = m_ModuloB;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.B.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
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
						p_DG->Control.B.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
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
		p_DG->Control.GateFunction &= ~0x30000;


	p_DG->Control.C.GoSignal &= 0x188;
	p_DG->Control.C.DoneSignal = 0x0;
	p_DG->Control.C.FireFirst = -1.0;
	p_DG->Control.C.PulseWidth[0] = -1.0;
	p_DG->Control.C.StepBack[0] = 0;
	p_DG->Control.C.ListLength = 0;
	p_DG->Control.C.SetBack = -1.0;
	p_DG->Control.C.OutputModulo = 1;
	p_DG->Control.C.OutputOffset = 0;
	p_DG->VarLoc.C.FireFirst = -1;
	p_DG->VarLoc.C.PulseWidth = -1;
	p_DG->VarLoc.C.OutputModulo = -1;
	p_DG->VarLoc.C.OutputOffset = -1;
	p_DG->VarLoc.C.StepBack = -1;
	p_DG->VarEqu.C.FireFirst[0] = 0;
	p_DG->VarEqu.C.PulseWidth[0] = 0;
	p_DG->VarEqu.C.StepBack[0] = 0;
	p_DG->VarEqu.C.OutputModulo[0] = 0;
	p_DG->VarEqu.C.OutputOffset[0] = 0;
	if ((GoSignal_C & 0x77) != 0x0)
	{
		jstr = m_DelayC;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.C.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.C.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.C.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.C.FireFirst, (LPCTSTR)m_DelayC, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.C.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.C.FireFirst, (LPCTSTR)m_DelayC, 64);
			}
			p_DG->Control.C.GoSignal |= (GoSignal_C & 0x78E77);
			p_DG->Control.C.GoSignal &= (GoSignal_C | ~0x78E77);
			jstr = m_WidthC;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.C.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.C.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.C.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.C.PulseWidth, (LPCTSTR)m_WidthC, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.C.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.C.PulseWidth, (LPCTSTR)m_WidthC, 64);
				}
			}
			else
				p_DG->Control.C.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefC;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.C.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.C.StepBack = -2;
					p_DG->Control.C.GoSignal |= (GoSignal_C & 0x07000);
					p_DG->Control.C.GoSignal &= (GoSignal_C | ~0x07000);
				}
			}
			jstr = m_ModuloC;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.C.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.C.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.C.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.C.OutputModulo, (LPCTSTR)m_ModuloC, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.C.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.C.OutputModulo, (LPCTSTR)m_ModuloC, 64);
				}
			}
			jstr = m_OffsetC;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.C.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.C.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.C.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.C.OutputOffset, (LPCTSTR)m_OffsetC, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.C.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.C.OutputOffset, (LPCTSTR)m_OffsetC, 64);
				}
			}
		}
	}

	p_DG->Control.D.GoSignal &= 0x188;
	p_DG->Control.D.DoneSignal = 0x0;
	p_DG->Control.D.FireFirst = -1.0;
	p_DG->Control.D.PulseWidth[0] = -1.0;
	p_DG->Control.D.StepBack[0] = 0;
	p_DG->Control.D.ListLength = 0;
	p_DG->Control.D.SetBack = -1.0;
	p_DG->Control.D.OutputModulo = 1;
	p_DG->Control.D.OutputOffset = 0;
	p_DG->VarLoc.D.FireFirst = -1;
	p_DG->VarLoc.D.PulseWidth = -1;
	p_DG->VarLoc.D.OutputModulo = -1;
	p_DG->VarLoc.D.OutputOffset = -1;
	p_DG->VarLoc.D.StepBack = -1;
	p_DG->VarEqu.D.FireFirst[0] = 0;
	p_DG->VarEqu.D.PulseWidth[0] = 0;
	p_DG->VarEqu.D.StepBack[0] = 0;
	p_DG->VarEqu.D.OutputModulo[0] = 0;
	p_DG->VarEqu.D.OutputOffset[0] = 0;
	if ((GoSignal_D & 0x77) != 0x0)
	{
		jstr = m_DelayD;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.D.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.D.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.D.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.D.FireFirst, (LPCTSTR)m_DelayD, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.D.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.D.FireFirst, (LPCTSTR)m_DelayD, 64);
			}
			p_DG->Control.D.GoSignal |= (GoSignal_D & 0x78E77);
			p_DG->Control.D.GoSignal &= (GoSignal_D | ~0x78E77);
			jstr = m_WidthD;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.D.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.D.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.D.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.D.PulseWidth, (LPCTSTR)m_WidthD, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.D.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.D.PulseWidth, (LPCTSTR)m_WidthD, 64);
				}
			}
			else
				p_DG->Control.D.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefD;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.D.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.D.StepBack = -2;
					p_DG->Control.D.GoSignal |= (GoSignal_D & 0x07000);
					p_DG->Control.D.GoSignal &= (GoSignal_D | ~0x07000);
				}
			}
			jstr = m_ModuloD;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.D.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.D.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.D.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.D.OutputModulo, (LPCTSTR)m_ModuloD, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.D.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.D.OutputModulo, (LPCTSTR)m_ModuloD, 64);
				}
			}
			jstr = m_OffsetD;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.D.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.D.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.D.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.D.OutputOffset, (LPCTSTR)m_OffsetD, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.D.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.D.OutputOffset, (LPCTSTR)m_OffsetD, 64);
				}
			}
		}
	}
	if (((p_DG->Control.C.GoSignal & 0x77) == 0x0) || ((p_DG->Control.D.GoSignal & 0x77) == 0x0))
		p_DG->Control.GateFunction &= ~0xC0000;


	p_DG->Control.E.GoSignal &= 0x188;
	p_DG->Control.E.DoneSignal = 0x0;
	p_DG->Control.E.FireFirst = -1.0;
	p_DG->Control.E.PulseWidth[0] = -1.0;
	p_DG->Control.E.StepBack[0] = 0;
	p_DG->Control.E.ListLength = 0;
	p_DG->Control.E.SetBack = -1.0;
	p_DG->Control.E.OutputModulo = 1;
	p_DG->Control.E.OutputOffset = 0;
	p_DG->VarLoc.E.FireFirst = -1;
	p_DG->VarLoc.E.PulseWidth = -1;
	p_DG->VarLoc.E.OutputModulo = -1;
	p_DG->VarLoc.E.OutputOffset = -1;
	p_DG->VarLoc.E.StepBack = -1;
	p_DG->VarEqu.E.FireFirst[0] = 0;
	p_DG->VarEqu.E.PulseWidth[0] = 0;
	p_DG->VarEqu.E.StepBack[0] = 0;
	p_DG->VarEqu.E.OutputModulo[0] = 0;
	p_DG->VarEqu.E.OutputOffset[0] = 0;
	if ((GoSignal_E & 0x77) != 0x0)
	{
		jstr = m_DelayE;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.E.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.E.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.E.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.E.FireFirst, (LPCTSTR)m_DelayE, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.E.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.E.FireFirst, (LPCTSTR)m_DelayE, 64);
			}
			p_DG->Control.E.GoSignal |= (GoSignal_E & 0x78E77);
			p_DG->Control.E.GoSignal &= (GoSignal_E | ~0x78E77);
			jstr = m_WidthE;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.E.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.E.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.E.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.E.PulseWidth, (LPCTSTR)m_WidthE, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.E.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.E.PulseWidth, (LPCTSTR)m_WidthE, 64);
				}
			}
			else
				p_DG->Control.E.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefE;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.E.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.E.StepBack = -2;
					p_DG->Control.E.GoSignal |= (GoSignal_E & 0x07000);
					p_DG->Control.E.GoSignal &= (GoSignal_E | ~0x07000);
				}
			}
			jstr = m_ModuloE;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.E.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.E.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.E.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.E.OutputModulo, (LPCTSTR)m_ModuloE, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.E.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.E.OutputModulo, (LPCTSTR)m_ModuloE, 64);
				}
			}
			jstr = m_OffsetE;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.E.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.E.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.E.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.E.OutputOffset, (LPCTSTR)m_OffsetE, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.E.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.E.OutputOffset, (LPCTSTR)m_OffsetE, 64);
				}
			}
		}
	}

	p_DG->Control.F.GoSignal &= 0x188;
	p_DG->Control.F.DoneSignal = 0x0;
	p_DG->Control.F.FireFirst = -1.0;
	p_DG->Control.F.PulseWidth[0] = -1.0;
	p_DG->Control.F.StepBack[0] = 0;
	p_DG->Control.F.ListLength = 0;
	p_DG->Control.F.SetBack = -1.0;
	p_DG->Control.F.OutputModulo = 1;
	p_DG->Control.F.OutputOffset = 0;
	p_DG->VarLoc.F.FireFirst = -1;
	p_DG->VarLoc.F.PulseWidth = -1;
	p_DG->VarLoc.F.OutputModulo = -1;
	p_DG->VarLoc.F.OutputOffset = -1;
	p_DG->VarLoc.F.StepBack = -1;
	p_DG->VarEqu.F.FireFirst[0] = 0;
	p_DG->VarEqu.F.PulseWidth[0] = 0;
	p_DG->VarEqu.F.StepBack[0] = 0;
	p_DG->VarEqu.F.OutputModulo[0] = 0;
	p_DG->VarEqu.F.OutputOffset[0] = 0;
	if ((GoSignal_F & 0x77) != 0x0)
	{
		jstr = m_DelayF;
		lr.TrimString(jstr);
		if (jstr.GetLength() > 0)
		{
			lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
			if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
			{
				if (lr.Numeric(jstr))
					p_DG->Control.F.FireFirst = p_G0xData->DelayLimit(atof(jstr), m_DG_Number);
				else
				{
					if (lr.CommandType(jstr, "x", "?"))
					{
						jstr = jstr.Right(jstr.GetLength() - 1);
						p_DG->VarLoc.F.FireFirst = (RoundInt(atof(jstr)) - 1);
					}
					else
					{
						p_DG->VarLoc.F.FireFirst = -2;
						lr.WriteMemo(p_DG->VarEqu.F.FireFirst, (LPCTSTR)m_DelayF, 64);
					}
				}
			}
			else
			{
				p_DG->VarLoc.F.FireFirst = -2;
				lr.WriteMemo(p_DG->VarEqu.F.FireFirst, (LPCTSTR)m_DelayF, 64);
			}
			p_DG->Control.F.GoSignal |= (GoSignal_F & 0x78E77);
			p_DG->Control.F.GoSignal &= (GoSignal_F | ~0x78E77);
			jstr = m_WidthF;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.F.PulseWidth[0] = p_G0xData->RoundWidth(atof(jstr), m_DG_Number);
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.F.PulseWidth = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.F.PulseWidth = -2;
							lr.WriteMemo(p_DG->VarEqu.F.PulseWidth, (LPCTSTR)m_WidthF, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.F.PulseWidth = -2;
					lr.WriteMemo(p_DG->VarEqu.F.PulseWidth, (LPCTSTR)m_WidthF, 64);
				}
			}
			else
				p_DG->Control.F.PulseWidth[0] = p_G0xData->RoundWidth(0.1, m_DG_Number);
			jstr = m_StbkRefF;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				Param = RoundInt(atof(jstr));
				if ((0 < Param) && (Param <= p_G0xData->FpgaMemoryList.NoParameters))
				{
					jstr.Format(" Y%d", Param);
					lr.WriteMemo(p_DG->VarEqu.F.StepBack, (LPCTSTR)jstr, 64);
					p_DG->VarLoc.F.StepBack = -2;
					p_DG->Control.F.GoSignal |= (GoSignal_F & 0x07000);
					p_DG->Control.F.GoSignal &= (GoSignal_F | ~0x07000);
				}
			}
			jstr = m_ModuloF;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.F.OutputModulo = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.F.OutputModulo = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.F.OutputModulo = -2;
							lr.WriteMemo(p_DG->VarEqu.F.OutputModulo, (LPCTSTR)m_ModuloF, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.F.OutputModulo = -2;
					lr.WriteMemo(p_DG->VarEqu.F.OutputModulo, (LPCTSTR)m_ModuloF, 64);
				}
			}
			jstr = m_OffsetF;
			lr.TrimString(jstr);
			if (jstr.GetLength() > 0)
			{
				lr.CheckBraceMatch((LPCTSTR)jstr, ThrowCStringException);
				if (lr.NumberCharacterGroups((LPCTSTR)jstr) == 1)
				{
					if (lr.Numeric(jstr))
						p_DG->Control.F.OutputOffset = min(0xFFFFFFFF, max(0, RoundInt(atof(jstr))));
					else
					{
						if (lr.CommandType(jstr, "x", "?"))
						{
							jstr = jstr.Right(jstr.GetLength() - 1);
							p_DG->VarLoc.F.OutputOffset = (RoundInt(atof(jstr)) - 1);
						}
						else
						{
							p_DG->VarLoc.F.OutputOffset = -2;
							lr.WriteMemo(p_DG->VarEqu.F.OutputOffset, (LPCTSTR)m_OffsetF, 64);
						}
					}
				}
				else
				{
					p_DG->VarLoc.F.OutputOffset = -2;
					lr.WriteMemo(p_DG->VarEqu.F.OutputOffset, (LPCTSTR)m_OffsetF, 64);
				}
			}
		}
	}
	if (((p_DG->Control.E.GoSignal & 0x77) == 0x0) || ((p_DG->Control.F.GoSignal & 0x77) == 0x0))
		p_DG->Control.GateFunction &= ~0x300000;

	return TRUE;
}

void CG05p4MasterPP::CheckHardwareControls() 
{
	CListRout lr;
	CString jstr;
	BOOL b_Burst, b_SecondaryLocal, b_SecondaryBus;
	b_Burst = FALSE;
	jstr = m_Burst;
	lr.TrimString(jstr);
	if (jstr.GetLength() > 0)
	{
		if (RoundInt(atof(jstr)) > 1)
			b_Burst = TRUE;
	}
	b_SecondaryLocal = TRUE;
	b_SecondaryBus = TRUE;
	if (m_Internal)
	{
		if ((!(m_GatePositive || m_GateNegative)) || b_Burst)
		{
			b_SecondaryLocal = FALSE;
			if (b_Master)
				b_SecondaryBus = FALSE;
		}
	}
	if (b_SecondaryLocal)
	{
		m_SecondaryLocalAB.EnableWindow(TRUE);
		m_SecondaryLocalBB.EnableWindow(TRUE);
		m_SecondaryLocalCB.EnableWindow(TRUE);
		m_SecondaryLocalDB.EnableWindow(TRUE);
		m_SecondaryLocalEB.EnableWindow(TRUE);
		m_SecondaryLocalFB.EnableWindow(TRUE);
	}
	else
	{
		m_SecondaryLocalA = FALSE;
		m_SecondaryLocalAB.EnableWindow(FALSE);
		m_SecondaryLocalB = FALSE;
		m_SecondaryLocalBB.EnableWindow(FALSE);
		m_SecondaryLocalC = FALSE;
		m_SecondaryLocalCB.EnableWindow(FALSE);
		m_SecondaryLocalD = FALSE;
		m_SecondaryLocalDB.EnableWindow(FALSE);
		m_SecondaryLocalE = FALSE;
		m_SecondaryLocalEB.EnableWindow(FALSE);
		m_SecondaryLocalF = FALSE;
		m_SecondaryLocalFB.EnableWindow(FALSE);
	}
	if (b_SecondaryBus)
	{
		m_SecondaryBusAB.EnableWindow(TRUE);
		m_SecondaryBusBB.EnableWindow(TRUE);
		m_SecondaryBusCB.EnableWindow(TRUE);
		m_SecondaryBusDB.EnableWindow(TRUE);
		m_SecondaryBusEB.EnableWindow(TRUE);
		m_SecondaryBusFB.EnableWindow(TRUE);
	}
	else
	{
		m_SecondaryBusA = FALSE;
		m_SecondaryBusAB.EnableWindow(FALSE);
		m_SecondaryBusB = FALSE;
		m_SecondaryBusBB.EnableWindow(FALSE);
		m_SecondaryBusC = FALSE;
		m_SecondaryBusCB.EnableWindow(FALSE);
		m_SecondaryBusD = FALSE;
		m_SecondaryBusDB.EnableWindow(FALSE);
		m_SecondaryBusE = FALSE;
		m_SecondaryBusEB.EnableWindow(FALSE);
		m_SecondaryBusF = FALSE;
		m_SecondaryBusFB.EnableWindow(FALSE);
	}
	if (((GoSignal_A & 0x77) == 0x0) || ((GoSignal_B & 0x77) == 0x0))
	{
		m_GateAB = FALSE;
		m_AB_Xor = FALSE;
		m_AB_Or = FALSE;
		m_AB_And = FALSE;
		UpdateData(FALSE);
	}
	if (((GoSignal_C & 0x77) == 0x0) || ((GoSignal_D & 0x77) == 0x0))
	{
		m_GateCD = FALSE;
		m_CD_Xor = FALSE;
		m_CD_Or = FALSE;
		m_CD_And = FALSE;
		UpdateData(FALSE);
	}
	if (((GoSignal_E & 0x77) == 0x0) || ((GoSignal_F & 0x77) == 0x0))
	{
		m_GateEF = FALSE;
		m_EF_Xor = FALSE;
		m_EF_Or = FALSE;
		m_EF_And = FALSE;
		UpdateData(FALSE);
	}
	BOOL b_SynchA = FALSE;
	BOOL b_SynchB = FALSE;
	BOOL b_SynchC = FALSE;
	BOOL b_SynchD = FALSE;
	BOOL b_SynchE = FALSE;
	BOOL b_SynchF = FALSE;
	BOOL b_SynchBurst = FALSE;
	BOOL b_InhibitA = FALSE;
	BOOL b_InhibitB = FALSE;
	BOOL b_InhibitC = FALSE;
	BOOL b_InhibitD = FALSE;
	BOOL b_InhibitE = FALSE;
	BOOL b_InhibitF = FALSE;
	switch (m_DG_Product)
	{
	case BME_SG08P2:
		//if (((GoSignal_A & 0x77) != 0x0) && (m_ModuloA.GetLength() > 0))
			b_SynchA = TRUE;
		//if (((GoSignal_B & 0x77) != 0x0) && (m_ModuloB.GetLength() > 0))
			b_SynchB = TRUE;
		//if (((GoSignal_C & 0x77) != 0x0) && (m_ModuloC.GetLength() > 0))
			b_SynchC = TRUE;
		//if (((GoSignal_D & 0x77) != 0x0) && (m_ModuloD.GetLength() > 0))
			b_SynchD = TRUE;
		//if (((GoSignal_E & 0x77) != 0x0) && (m_ModuloE.GetLength() > 0))
			b_SynchE = TRUE;
		//if (((GoSignal_F & 0x77) != 0x0) && (m_ModuloF.GetLength() > 0))
			b_SynchF = TRUE;
		//if (m_Burst.GetLength() > 0)
			b_SynchBurst = TRUE;
		//if (m_GateDivider.GetLength() > 0)
		//{
			//if (RoundInt(atof(m_GateDivider)) == 0)
				//b_SynchBurst = TRUE;
		//}
	case BME_SG08P1:
		if (m_ClockSource == TriggerAndOscillator)
		{
			if ((b_Master) || ((GoSignal_A & 0x07) != 0x0))
				b_InhibitA = TRUE;
			if ((b_Master) || ((GoSignal_B & 0x07) != 0x0))
				b_InhibitB = TRUE;
			if ((b_Master) || ((GoSignal_C & 0x07) != 0x0))
				b_InhibitC = TRUE;
			if ((b_Master) || ((GoSignal_D & 0x07) != 0x0))
				b_InhibitD = TRUE;
			if ((b_Master) || ((GoSignal_E & 0x07) != 0x0))
				b_InhibitE = TRUE;
			if ((b_Master) || ((GoSignal_F & 0x07) != 0x0))
				b_InhibitF = TRUE;
		}
		else
		{
			if ((!b_Master) && ((GoSignal_A & 0x70) != 0x0))
				b_InhibitA = TRUE;
			if ((!b_Master) && ((GoSignal_B & 0x70) != 0x0))
				b_InhibitB = TRUE;
			if ((!b_Master) && ((GoSignal_C & 0x70) != 0x0))
				b_InhibitC = TRUE;
			if ((!b_Master) && ((GoSignal_D & 0x70) != 0x0))
				b_InhibitD = TRUE;
			if ((!b_Master) && ((GoSignal_E & 0x70) != 0x0))
				b_InhibitE = TRUE;
			if ((!b_Master) && ((GoSignal_F & 0x70) != 0x0))
				b_InhibitF = TRUE;
		}
		break;
	default:
		break;
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
	if (b_InhibitC)
		m_InhibitCB.EnableWindow(TRUE);
	else
	{
		m_InhibitC = FALSE;
		m_InhibitCB.EnableWindow(FALSE);
	}
	if (b_InhibitD)
		m_InhibitDB.EnableWindow(TRUE);
	else
	{
		m_InhibitD = FALSE;
		m_InhibitDB.EnableWindow(FALSE);
	}
	if (b_InhibitE)
		m_InhibitEB.EnableWindow(TRUE);
	else
	{
		m_InhibitE = FALSE;
		m_InhibitEB.EnableWindow(FALSE);
	}
	if (b_InhibitF)
		m_InhibitFB.EnableWindow(TRUE);
	else
	{
		m_InhibitF = FALSE;
		m_InhibitFB.EnableWindow(FALSE);
	}
	if (b_SynchA)
		m_SynchAB.EnableWindow(TRUE);
	else
	{
		m_SynchA = FALSE;
		m_SynchAB.EnableWindow(FALSE);
	}
	if (b_SynchB)
		m_SynchBB.EnableWindow(TRUE);
	else
	{
		m_SynchB = FALSE;
		m_SynchBB.EnableWindow(FALSE);
	}
	if (b_SynchC)
		m_SynchCB.EnableWindow(TRUE);
	else
	{
		m_SynchC = FALSE;
		m_SynchCB.EnableWindow(FALSE);
	}
	if (b_SynchD)
		m_SynchDB.EnableWindow(TRUE);
	else
	{
		m_SynchD = FALSE;
		m_SynchDB.EnableWindow(FALSE);
	}
	if (b_SynchE)
		m_SynchEB.EnableWindow(TRUE);
	else
	{
		m_SynchE = FALSE;
		m_SynchEB.EnableWindow(FALSE);
	}
	if (b_SynchF)
		m_SynchFB.EnableWindow(TRUE);
	else
	{
		m_SynchF = FALSE;
		m_SynchFB.EnableWindow(FALSE);
	}
	if (b_SynchBurst)
		m_SynchBurstB.EnableWindow(TRUE);
	else
	{
		m_SynchBurst = FALSE;
		m_SynchBurstB.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	UpdateGoSignals();
}

void CG05p4MasterPP::OnShowWindow(BOOL bShow, UINT nStatus) 
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
	case BME_SG08P1:
		m_Designator.SetWindowText("  SG08P1 Delay Parameters");
	case BME_SG08P2:
		m_Designator.SetWindowText("  SG08P2 Delay Parameters");
		break;
	}
	UpdateData(FALSE);
}
