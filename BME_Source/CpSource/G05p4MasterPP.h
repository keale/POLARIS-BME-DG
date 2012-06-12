#if !defined(AFX_G05P4MASTERPP_H__0E927315_B11F_4591_9B6F_C276024B1C0D__INCLUDED_)
#define AFX_G05P4MASTERPP_H__0E927315_B11F_4591_9B6F_C276024B1C0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// G05p4MasterPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG05p4MasterPP dialog

#include "CursorEdit.h"
#include "DoneSelectDlg.h"

#define WM_USER_REQUEST_G05						(WM_USER + 1)
#define WM_LOAD_COUNTER_REQUEST_G05		(WM_USER + 4)
#define WM_FAST_APPLY_REQUEST_G05			(WM_USER + 5)
#define WM_LOAD_FREQUENCY_REQUEST_G05	(WM_USER + 6)

#define WM_USER_REQUEST_A    (WM_USER + 12)
#define WM_USER_REQUEST_B    (WM_USER + 13)
#define WM_USER_REQUEST_M_A  (WM_USER + 15)
#define WM_USER_REQUEST_M_B  (WM_USER + 16)
#define WM_USER_REQUEST_O_A  (WM_USER + 18)
#define WM_USER_REQUEST_O_B  (WM_USER + 19)
#define WM_USER_REQUEST_PRD  (WM_USER + 20)
#define WM_USER_REQUEST_TLV  (WM_USER + 21)
#define WM_USER_REQUEST_GD	 (WM_USER + 22)
#define WM_USER_REQUEST_PVA  (WM_USER + 23)
#define WM_USER_REQUEST_FTR  (WM_USER + 24)
#define WM_USER_REQUEST_GLV  (WM_USER + 25)
#define WM_USER_REQUEST_SBC  (WM_USER + 26)
#define WM_USER_REQUEST_BCT  (WM_USER + 27)
#define WM_USER_REQUEST_GDL  (WM_USER + 28)
#define WM_USER_REQUEST_INS  (WM_USER + 29)
#define WM_USER_REQUEST_DES  (WM_USER + 30)

#define WM_USER_REQUEST_C    (WM_USER + 31)
#define WM_USER_REQUEST_D    (WM_USER + 32)
#define WM_USER_REQUEST_E    (WM_USER + 33)
#define WM_USER_REQUEST_F    (WM_USER + 34)

#define WM_USER_REQUEST_W_A  (WM_USER + 35)
#define WM_USER_REQUEST_W_B  (WM_USER + 36)
#define WM_USER_REQUEST_W_C  (WM_USER + 37)
#define WM_USER_REQUEST_W_D  (WM_USER + 38)
#define WM_USER_REQUEST_W_E  (WM_USER + 39)
#define WM_USER_REQUEST_W_F  (WM_USER + 40)

#define WM_USER_REQUEST_M_C  (WM_USER + 41)
#define WM_USER_REQUEST_M_D  (WM_USER + 42)
#define WM_USER_REQUEST_M_E  (WM_USER + 43)
#define WM_USER_REQUEST_M_F  (WM_USER + 44)

#define WM_USER_REQUEST_O_C  (WM_USER + 47)
#define WM_USER_REQUEST_O_D  (WM_USER + 48)
#define WM_USER_REQUEST_O_E  (WM_USER + 49)
#define WM_USER_REQUEST_O_F  (WM_USER + 50)


class CG05p4MasterPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG05p4MasterPP)

// Construction
public:
	CString A_Name;
	CString B_Name;
	CString C_Name;
	CString D_Name;
	CString E_Name;
	CString F_Name;
	int m_DG_Number;
	_int64 NoEvents;
	double Frequency;
	CG0xData* p_G0xData;
	BOOL b_RequestZeroCounter;
	BOOL b_RequestZeroModulo;
	BOOL b_RequestJumpStart;
	CWnd* p_ParentWindow;
	BOOL* p_DataModified;
	HANDLE	DataNotification;
	BOOL b_PageActive;
	BOOL CollectVariables(DG_Type* p_DG);
	BOOL DistributeVariables(DG_Type* p_DG);
	CG05p4MasterPP();
	~CG05p4MasterPP();

// Dialog Data
	//{{AFX_DATA(CG05p4MasterPP)
	enum { IDD = IDD_G05P4_MASTER };
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
	CCursorEdit	m_Delay_CED;
	CCursorEdit	m_Delay_DED;
	CCursorEdit	m_Delay_EED;
	CCursorEdit	m_Delay_FED;
	CCursorEdit	m_Width_AED;
	CCursorEdit	m_Width_BED;
	CCursorEdit	m_Width_CED;
	CCursorEdit	m_Width_DED;
	CCursorEdit	m_Width_EED;
	CCursorEdit	m_Width_FED;
	CCursorEdit	m_ModuloAED;
	CCursorEdit	m_ModuloBED;
	CCursorEdit	m_ModuloCED;
	CCursorEdit	m_ModuloDED;
	CCursorEdit	m_ModuloEED;
	CCursorEdit	m_ModuloFED;
	CCursorEdit	m_OffsetAED;
	CCursorEdit	m_OffsetBED;
	CCursorEdit	m_OffsetCED;
	CCursorEdit	m_OffsetDED;
	CCursorEdit	m_OffsetEED;
	CCursorEdit	m_OffsetFED;
	CCursorEdit	m_InhibitTriggerED;
	CCursorEdit	m_InhibitSecondaryED;
	CCursorEdit	m_DelaySecondaryED;
	CCursorEdit	m_StepBackED;
	CCursorEdit	m_ForceTriggerED;
	CCursorEdit	m_BurstED;
	CCursorEdit	m_TriggerLevelED;
	CCursorEdit	m_GateDividerED;
	CCursorEdit	m_GateLevelED;
	CCursorEdit	m_GateDelayED;
	CCursorEdit	m_PresetValueED;
	CButton	m_SecondaryLocalAB;
	CButton	m_SecondaryLocalBB;
	CButton	m_SecondaryLocalCB;
	CButton	m_SecondaryLocalDB;
	CButton	m_SecondaryLocalEB;
	CButton	m_SecondaryLocalFB;
	CButton	m_SecondaryBusAB;
	CButton	m_SecondaryBusBB;
	CButton	m_SecondaryBusCB;
	CButton	m_SecondaryBusDB;
	CButton	m_SecondaryBusEB;
	CButton	m_SecondaryBusFB;
	CButton	m_InhibitAB;
	CButton	m_InhibitBB;
	CButton	m_InhibitCB;
	CButton	m_InhibitDB;
	CButton	m_InhibitEB;
	CButton	m_InhibitFB;
	CButton	m_SynchAB;
	CButton	m_SynchBB;
	CButton	m_SynchCB;
	CButton	m_SynchDB;
	CButton	m_SynchEB;
	CButton	m_SynchFB;
	CButton	m_SynchBurstB;
	CButton	m_RisingB;
	CButton	m_FallingB;
	CButton	m_ExternalB;
	CButton	m_Designator;
	CString	m_DelayA;
	CString	m_DelayB;
	CString	m_DelayC;
	CString	m_DelayD;
	CString	m_DelayE;
	CString	m_DelayF;
	CString	m_WidthA;
	CString	m_WidthB;
	CString	m_WidthC;
	CString	m_WidthD;
	CString	m_WidthE;
	CString	m_WidthF;
	CString	m_ModuloA;
	CString	m_ModuloB;
	CString	m_ModuloC;
	CString	m_ModuloD;
	CString	m_ModuloE;
	CString	m_ModuloF;
	CString	m_OffsetA;
	CString	m_OffsetB;
	CString	m_OffsetC;
	CString	m_OffsetD;
	CString	m_OffsetE;
	CString	m_OffsetF;
	CString	m_TriggerCount;
	CString	m_ExtFrequency;
	CString	m_InhibitTrigger;
	CString	m_InhibitSecondary;
	CString	m_DelaySecondary;
	CString	m_ForceTrigger;
	CString	m_Burst;
	CString	m_TriggerLevel;
	CString	m_GateDivider;
	CString	m_GateLevel;
	CString	m_GateDelay;
	BOOL	m_ReadTriggers;
	CString	m_PresetValue;
	BOOL	m_StopOnPreset;
	BOOL	m_External;
	BOOL	m_Rising;
	BOOL	m_Falling;
	BOOL	m_Internal;
	BOOL	m_GatePositive;
	BOOL	m_GateNegative;
	BOOL	m_Ignore;
	BOOL	m_Memorize;
	BOOL	m_SynchronizeGate;
	BOOL	m_GateAB;
	BOOL	m_AB_Xor;
	BOOL	m_AB_Or;
	BOOL	m_AB_And;
	BOOL	m_GateCD;
	BOOL	m_CD_Xor;
	BOOL	m_CD_Or;
	BOOL	m_CD_And;
	BOOL	m_GateEF;
	BOOL	m_EF_Xor;
	BOOL	m_EF_Or;
	BOOL	m_EF_And;
	BOOL	m_PrimaryLocalA;
	BOOL	m_SecondaryLocalA;
	BOOL	m_ForceLocalA;
	BOOL	m_PrimaryBusA;
	BOOL	m_SecondaryBusA;
	BOOL	m_ForceBusA;
	BOOL	m_PrimaryLocalB;
	BOOL	m_SecondaryLocalB;
	BOOL	m_ForceLocalB;
	BOOL	m_PrimaryBusB;
	BOOL	m_SecondaryBusB;
	BOOL	m_ForceBusB;
	BOOL	m_PrimaryLocalC;
	BOOL	m_SecondaryLocalC;
	BOOL	m_ForceLocalC;
	BOOL	m_PrimaryBusC;
	BOOL	m_SecondaryBusC;
	BOOL	m_ForceBusC;
	BOOL	m_PrimaryLocalD;
	BOOL	m_SecondaryLocalD;
	BOOL	m_ForceLocalD;
	BOOL	m_PrimaryBusD;
	BOOL	m_SecondaryBusD;
	BOOL	m_ForceBusD;
	BOOL	m_PrimaryLocalE;
	BOOL	m_SecondaryLocalE;
	BOOL	m_ForceLocalE;
	BOOL	m_PrimaryBusE;
	BOOL	m_SecondaryBusE;
	BOOL	m_ForceBusE;
	BOOL	m_PrimaryLocalF;
	BOOL	m_SecondaryLocalF;
	BOOL	m_ForceLocalF;
	BOOL	m_PrimaryBusF;
	BOOL	m_SecondaryBusF;
	BOOL	m_ForceBusF;
	BOOL	m_StbkLocA;
	BOOL	m_StbkBusA;
	CString	m_StbkRefA;
	BOOL	m_StbkLocB;
	BOOL	m_StbkBusB;
	CString	m_StbkRefB;
	BOOL	m_StbkLocC;
	BOOL	m_StbkBusC;
	CString	m_StbkRefC;
	BOOL	m_StbkLocD;
	BOOL	m_StbkBusD;
	CString	m_StbkRefD;
	BOOL	m_StbkLocE;
	BOOL	m_StbkBusE;
	CString	m_StbkRefE;
	BOOL	m_StbkLocF;
	BOOL	m_StbkBusF;
	CString	m_StbkRefF;
	CString	m_StepBack;
	BOOL	m_StartLocA;
	BOOL	m_StartBusA;
	BOOL	m_CircleA;
	BOOL	m_StartLocB;
	BOOL	m_StartBusB;
	BOOL	m_CircleB;
	BOOL	m_StartLocC;
	BOOL	m_StartBusC;
	BOOL	m_CircleC;
	BOOL	m_StartLocD;
	BOOL	m_StartBusD;
	BOOL	m_CircleD;
	BOOL	m_StartLocE;
	BOOL	m_StartBusE;
	BOOL	m_CircleE;
	BOOL	m_StartLocF;
	BOOL	m_StartBusF;
	BOOL	m_CircleF;
	BOOL	m_E_EnaA;
	BOOL	m_F_EnaA;
	BOOL	m_BusEnaA;
	BOOL	m_E_EnaB;
	BOOL	m_F_EnaB;
	BOOL	m_BusEnaB;
	BOOL	m_E_EnaC;
	BOOL	m_F_EnaC;
	BOOL	m_BusEnaC;
	BOOL	m_E_EnaD;
	BOOL	m_F_EnaD;
	BOOL	m_BusEnaD;
	BOOL	m_E_EnaE;
	BOOL	m_F_EnaE;
	BOOL	m_BusEnaE;
	BOOL	m_E_EnaF;
	BOOL	m_F_EnaF;
	BOOL	m_BusEnaF;
	BOOL	m_InhibitA;
	BOOL	m_InhibitB;
	BOOL	m_InhibitC;
	BOOL	m_InhibitD;
	BOOL	m_InhibitE;
	BOOL	m_InhibitF;
	BOOL	m_SynchA;
	BOOL	m_SynchB;
	BOOL	m_SynchC;
	BOOL	m_SynchD;
	BOOL	m_SynchE;
	BOOL	m_SynchF;
	BOOL	m_SynchBurst;
	CString	m_A_Name;
	CString	m_B_Name;
	CString	m_C_Name;
	CString	m_D_Name;
	CString	m_E_Name;
	CString	m_F_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG05p4MasterPP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG05p4MasterPP)
	afx_msg void OnChangeDelayA();
	afx_msg void OnChangeDelayB();
	afx_msg void OnChangeDelayC();
	afx_msg void OnChangeDelayD();
	afx_msg void OnChangeDelayE();
	afx_msg void OnChangeDelayF();
	afx_msg void OnKillfocusDelayA();
	afx_msg void OnKillfocusDelayB();
	afx_msg void OnKillfocusDelayC();
	afx_msg void OnKillfocusDelayD();
	afx_msg void OnKillfocusDelayE();
	afx_msg void OnKillfocusDelayF();
	afx_msg void OnChangeWidthA();
	afx_msg void OnChangeWidthB();
	afx_msg void OnChangeWidthC();
	afx_msg void OnChangeWidthD();
	afx_msg void OnChangeWidthE();
	afx_msg void OnChangeWidthF();
	afx_msg void OnKillfocusWidthA();
	afx_msg void OnKillfocusWidthB();
	afx_msg void OnKillfocusWidthC();
	afx_msg void OnKillfocusWidthD();
	afx_msg void OnKillfocusWidthE();
	afx_msg void OnKillfocusWidthF();
	afx_msg void OnChangeModuloA();
	afx_msg void OnChangeModuloB();
	afx_msg void OnChangeModuloC();
	afx_msg void OnChangeModuloD();
	afx_msg void OnChangeModuloE();
	afx_msg void OnChangeModuloF();
	afx_msg void OnKillfocusModuloA();
	afx_msg void OnKillfocusModuloB();
	afx_msg void OnKillfocusModuloC();
	afx_msg void OnKillfocusModuloD();
	afx_msg void OnKillfocusModuloE();
	afx_msg void OnKillfocusModuloF();
	afx_msg void OnChangeOffsetA();
	afx_msg void OnChangeOffsetB();
	afx_msg void OnChangeOffsetC();
	afx_msg void OnChangeOffsetD();
	afx_msg void OnChangeOffsetE();
	afx_msg void OnChangeOffsetF();
	afx_msg void OnKillfocusOffsetA();
	afx_msg void OnKillfocusOffsetB();
	afx_msg void OnKillfocusOffsetC();
	afx_msg void OnKillfocusOffsetD();
	afx_msg void OnKillfocusOffsetE();
	afx_msg void OnKillfocusOffsetF();
	afx_msg void OnZeroModulo();
	afx_msg void OnJumpStart();
	afx_msg void OnPrimaryLocalA();
	afx_msg void OnPrimaryLocalB();
	afx_msg void OnPrimaryLocalC();
	afx_msg void OnPrimaryLocalD();
	afx_msg void OnPrimaryLocalE();
	afx_msg void OnPrimaryLocalF();
	afx_msg void OnSecondaryLocalA();
	afx_msg void OnSecondaryLocalB();
	afx_msg void OnSecondaryLocalC();
	afx_msg void OnSecondaryLocalD();
	afx_msg void OnSecondaryLocalE();
	afx_msg void OnSecondaryLocalF();
	afx_msg void OnForceLocalA();
	afx_msg void OnForceLocalB();
	afx_msg void OnForceLocalC();
	afx_msg void OnForceLocalD();
	afx_msg void OnForceLocalE();
	afx_msg void OnForceLocalF();
	afx_msg void OnPrimaryBusA();
	afx_msg void OnPrimaryBusB();
	afx_msg void OnPrimaryBusC();
	afx_msg void OnPrimaryBusD();
	afx_msg void OnPrimaryBusE();
	afx_msg void OnPrimaryBusF();
	afx_msg void OnSecondaryBusA();
	afx_msg void OnSecondaryBusB();
	afx_msg void OnSecondaryBusC();
	afx_msg void OnSecondaryBusD();
	afx_msg void OnSecondaryBusE();
	afx_msg void OnSecondaryBusF();
	afx_msg void OnForceBusA();
	afx_msg void OnForceBusB();
	afx_msg void OnForceBusC();
	afx_msg void OnForceBusD();
	afx_msg void OnForceBusE();
	afx_msg void OnForceBusF();
	afx_msg void OnInhibitA();
	afx_msg void OnInhibitB();
	afx_msg void OnInhibitC();
	afx_msg void OnInhibitD();
	afx_msg void OnInhibitE();
	afx_msg void OnInhibitF();
	afx_msg void OnSynchA();
	afx_msg void OnSynchB();
	afx_msg void OnSynchC();
	afx_msg void OnSynchD();
	afx_msg void OnSynchE();
	afx_msg void OnSynchF();
	afx_msg void OnSynchBurst();
	afx_msg void OnStbkLocA();
	afx_msg void OnStbkLocB();
	afx_msg void OnStbkLocC();
	afx_msg void OnStbkLocD();
	afx_msg void OnStbkLocE();
	afx_msg void OnStbkLocF();
	afx_msg void OnStbkBusA();
	afx_msg void OnStbkBusB();
	afx_msg void OnStbkBusC();
	afx_msg void OnStbkBusD();
	afx_msg void OnStbkBusE();
	afx_msg void OnStbkBusF();
	afx_msg void OnChangeStbkRefA();
	afx_msg void OnChangeStbkRefB();
	afx_msg void OnChangeStbkRefC();
	afx_msg void OnChangeStbkRefD();
	afx_msg void OnChangeStbkRefE();
	afx_msg void OnChangeStbkRefF();
	afx_msg void OnKillfocusStbkRefA();
	afx_msg void OnKillfocusStbkRefB();
	afx_msg void OnKillfocusStbkRefC();
	afx_msg void OnKillfocusStbkRefD();
	afx_msg void OnKillfocusStbkRefE();
	afx_msg void OnKillfocusStbkRefF();
	afx_msg void OnStartLocA();
	afx_msg void OnStartLocB();
	afx_msg void OnStartLocC();
	afx_msg void OnStartLocD();
	afx_msg void OnStartLocE();
	afx_msg void OnStartLocF();
	afx_msg void OnStartBusA();
	afx_msg void OnStartBusB();
	afx_msg void OnStartBusC();
	afx_msg void OnStartBusD();
	afx_msg void OnStartBusE();
	afx_msg void OnStartBusF();
	afx_msg void OnCircleA();
	afx_msg void OnCircleB();
	afx_msg void OnCircleC();
	afx_msg void OnCircleD();
	afx_msg void OnCircleE();
	afx_msg void OnCircleF();
	afx_msg void OnE_EnaA();
	afx_msg void OnF_EnaA();
	afx_msg void OnBusEnaA();
	afx_msg void OnE_EnaB();
	afx_msg void OnF_EnaB();
	afx_msg void OnBusEnaB();
	afx_msg void OnE_EnaC();
	afx_msg void OnF_EnaC();
	afx_msg void OnBusEnaC();
	afx_msg void OnE_EnaD();
	afx_msg void OnF_EnaD();
	afx_msg void OnBusEnaD();
	afx_msg void OnE_EnaE();
	afx_msg void OnF_EnaE();
	afx_msg void OnBusEnaE();
	afx_msg void OnE_EnaF();
	afx_msg void OnF_EnaF();
	afx_msg void OnBusEnaF();
	afx_msg void OnGateAB();
	afx_msg void OnAB_Xor();
	afx_msg void OnAB_Or();
	afx_msg void OnAB_And();
	afx_msg void OnGateCD();
	afx_msg void OnCD_Xor();
	afx_msg void OnCD_Or();
	afx_msg void OnCD_And();
	afx_msg void OnGateEF();
	afx_msg void OnEF_Xor();
	afx_msg void OnEF_Or();
	afx_msg void OnEF_And();
	afx_msg void OnExternal();
	afx_msg void OnInternal();
	afx_msg void OnFalling();
	afx_msg void OnRising();
	afx_msg void OnGatePositive();
	afx_msg void OnGateNegative();
	afx_msg void OnIgnore();
	afx_msg void OnMemorize();
	afx_msg void OnSynchronizeGate();
	afx_msg void OnStopOnPreset();
	afx_msg void OnReadTriggers();
	afx_msg void OnResetCounter();
	afx_msg void OnChangeTriggerCount();
	afx_msg void OnChangeExtFrequency();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeStepBack();
	afx_msg void OnKillfocusStepBack();
	afx_msg void OnChangeInhibitTrigger();
	afx_msg void OnKillfocusInhibitTrigger();
	afx_msg void OnChangeInhibitSecondary();
	afx_msg void OnKillfocusInhibitSecondary();
	afx_msg void OnChangeDelaySecondary();
	afx_msg void OnKillfocusDelaySecondary();
	afx_msg void OnChangeGateDelay();
	afx_msg void OnKillfocusGateDelay();
	afx_msg void OnChangeForceTrigger();
	afx_msg void OnKillfocusForceTrigger();
	afx_msg void OnChangeGateDivider();
	afx_msg void OnKillfocusGateDivider();
	afx_msg void OnChangeTriggerLevel();
	afx_msg void OnKillfocusTriggerLevel();
	afx_msg void OnChangeGateLevel();
	afx_msg void OnKillfocusGateLevel();
	afx_msg void OnChangePresetValue();
	afx_msg void OnKillfocusPresetValue();
	afx_msg void OnChangeBurst();
	afx_msg void OnKillfocusBurst();
	//}}AFX_MSG
  afx_msg LRESULT OnChangeObjectProps(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnLoadFrequency(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayC(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayD(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayE(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayF(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthC(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthD(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthE(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollWidthF(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloC(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloD(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloE(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloF(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetC(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetD(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetE(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetF(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollInhibitTrigger(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollInhibitSecondary(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelaySecondary(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollGateDelay(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollStepBack(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollForceTrigger(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollTriggerLevel(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollGateLevel(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollGateDivider(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollPresetValue(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollBurst(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void LoadTriggerCounter(_int64* p_TriggerCount);
	void LoadFrequency(double* p_Frequency);
	void UpdateGoSignals();
	void CheckGateChannels();
	void CheckHardwareControls();
	int m_DG_Product;
	unsigned long m_ClockSource;
	BOOL b_ForceTriggerActive;
	BOOL b_CrystalOscillator;
	BOOL b_Master;
	BOOL b_FastApply;
	void DiscretizeValues();
	unsigned long GoSignal_A;
	unsigned long GoSignal_B;
	unsigned long GoSignal_C;
	unsigned long GoSignal_D;
	unsigned long GoSignal_E;
	unsigned long GoSignal_F;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G05P4MASTERPP_H__0E927315_B11F_4591_9B6F_C276024B1C0D__INCLUDED_)
