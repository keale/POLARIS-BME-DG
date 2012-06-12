#if !defined(AFX_G05P2MASTERPP_H__09895F8E_ACE6_466E_B285_68E90D5D44DD__INCLUDED_)
#define AFX_G05P2MASTERPP_H__09895F8E_ACE6_466E_B285_68E90D5D44DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// G05p2MasterPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG05p2MasterPP dialog

#include "CursorEdit.h"
#include "DoneSelectDlg.h"

#define WM_USER_REQUEST_G05					(WM_USER + 1)
#define WM_LOAD_COUNTER_REQUEST_G05 (WM_USER + 4)
#define WM_FAST_APPLY_REQUEST_G05		(WM_USER + 5)

#define WM_USER_REQUEST_T0   (WM_USER + 11)
#define WM_USER_REQUEST_A    (WM_USER + 12)
#define WM_USER_REQUEST_B    (WM_USER + 13)
#define WM_USER_REQUEST_M_T0 (WM_USER + 14)
#define WM_USER_REQUEST_M_A  (WM_USER + 15)
#define WM_USER_REQUEST_M_B  (WM_USER + 16)
#define WM_USER_REQUEST_O_T0 (WM_USER + 17)
#define WM_USER_REQUEST_O_A  (WM_USER + 18)
#define WM_USER_REQUEST_O_B  (WM_USER + 19)
#define WM_USER_REQUEST_PRD  (WM_USER + 20)
#define WM_USER_REQUEST_TLV  (WM_USER + 21)
#define WM_USER_REQUEST_GD	 (WM_USER + 22)
#define WM_USER_REQUEST_PVA  (WM_USER + 23)
#define WM_USER_REQUEST_FTR  (WM_USER + 24)

class CG05p2MasterPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG05p2MasterPP)

// Construction
public:
	CString T0_Name;
	CString A_Name;
	CString B_Name;
	int m_DG_Number;
	unsigned long NoEvents;
	CG0xData* p_G0xData;
	BOOL b_RequestZeroCounter;
	BOOL b_RequestZeroModulo;
	CWnd* p_ParentWindow;
	BOOL* p_DataModified;
	HANDLE	DataNotification;
	BOOL b_PageActive;
	BOOL CollectVariables(DG_Type* p_DG);
	BOOL DistributeVariables(DG_Type* p_DG);
	CG05p2MasterPP();
	~CG05p2MasterPP();

// Dialog Data
	//{{AFX_DATA(CG05p2MasterPP)
	enum { IDD = IDD_G05P2_MASTER };
	CButton	m_SecondaryT0B;
	CButton	m_SecondaryBB;
	CButton	m_SecondaryAB;
	CButton	m_ForceT0B;
	CButton	m_ForceBB;
	CButton	m_ForceAB;
	CButton	m_InhibitT0B;
	CButton	m_InhibitBB;
	CButton	m_InhibitAB;
	CCursorEdit	m_Delay_T0ED;
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
	CCursorEdit	m_InhibitTriggerED;
	CCursorEdit	m_ForceTriggerED;
	CCursorEdit	m_TriggerLevelED;
	CCursorEdit	m_PresetValueED;
	CCursorEdit	m_GateDividerED;
	CCursorEdit	m_ModuloT0ED;
	CCursorEdit	m_ModuloAED;
	CCursorEdit	m_ModuloBED;
	CCursorEdit	m_OffsetT0ED;
	CCursorEdit	m_OffsetAED;
	CCursorEdit	m_OffsetBED;
	CButton	m_IgnoreB;
	CButton	m_MemorizeB;
	CButton	m_GatePositiveB;
	CButton	m_GateNegativeB;
	CButton	m_RisingB;
	CButton	m_FallingB;
	CButton	m_ExternalB;
	CButton	m_Designator;
	CString	m_DelayA;
	CString	m_DelayB;
	CString	m_DelayT0;
	CString	m_ModuloA;
	CString	m_ModuloB;
	CString	m_ModuloT0;
	CString	m_OffsetA;
	CString	m_OffsetB;
	CString	m_OffsetT0;
	BOOL	m_External;
	BOOL	m_Falling;
	BOOL	m_GateAB;
	BOOL	m_Internal;
	CString	m_PresetValue;
	BOOL	m_Rising;
	BOOL	m_StopOnPreset;
	CString	m_InhibitTrigger;
	CString	m_ForceTrigger;
	CString	m_TriggerCount;
	BOOL	m_ReadTriggers;
	CString	m_GateDivider;
	BOOL	m_GatePositive;
	CString	m_TriggerLevel;
	BOOL	m_GateNegative;
	BOOL	m_Ignore;
	BOOL	m_Memorize;
	BOOL	m_AcknowledgeDefault;
	BOOL	m_AcknowledgeNone;
	BOOL	m_ForceA;
	BOOL	m_ForceB;
	BOOL	m_ForceT0;
	BOOL	m_GateAnd;
	BOOL	m_GateOr;
	BOOL	m_GateXor;
	BOOL	m_MsBusA;
	BOOL	m_MsBusB;
	BOOL	m_MsBusT0;
	BOOL	m_PrimaryA;
	BOOL	m_PrimaryB;
	BOOL	m_PrimaryT0;
	BOOL	m_SecondaryA;
	BOOL	m_SecondaryB;
	BOOL	m_SecondaryT0;
	BOOL	m_InhibitA;
	BOOL	m_InhibitB;
	BOOL	m_InhibitT0;
	CString	m_A_Name;
	CString	m_B_Name;
	CString	m_T0_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG05p2MasterPP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG05p2MasterPP)
	afx_msg void OnAcknowledgeCustom();
	afx_msg void OnAcknowledgeDefault();
	afx_msg void OnAcknowledgeNone();
	afx_msg void OnForceA();
	afx_msg void OnForceB();
	afx_msg void OnForceT0();
	afx_msg void OnInhibitA();
	afx_msg void OnInhibitB();
	afx_msg void OnInhibitT0();
	afx_msg void OnGateAnd();
	afx_msg void OnGateOr();
	afx_msg void OnGateXor();
	afx_msg void OnGateAb();
	afx_msg void OnMsBusA();
	afx_msg void OnMsBusB();
	afx_msg void OnMsBusT0();
	afx_msg void OnPrimaryA();
	afx_msg void OnPrimaryB();
	afx_msg void OnPrimaryT0();
	afx_msg void OnSecondaryA();
	afx_msg void OnSecondaryB();
	afx_msg void OnSecondaryT0();
	afx_msg void OnChangeDelayA();
	afx_msg void OnChangeDelayB();
	afx_msg void OnChangeDelayT0();
	afx_msg void OnExternal();
	afx_msg void OnFalling();
	afx_msg void OnInternal();
	afx_msg void OnChangePresetValue();
	afx_msg void OnRising();
	afx_msg void OnStopOnPreset();
	afx_msg void OnChangeInhibitTrigger();
	afx_msg void OnKillfocusInhibitTrigger();
	afx_msg void OnChangeForceTrigger();
	afx_msg void OnKillfocusForceTrigger();
	afx_msg void OnKillfocusDelayT0();
	afx_msg void OnKillfocusPresetValue();
	afx_msg void OnResetCounter();
	afx_msg void OnChangeTriggerCount();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillfocusDelayA();
	afx_msg void OnKillfocusDelayB();
	afx_msg void OnReadTriggers();
	afx_msg void OnChangeGateDivider();
	afx_msg void OnKillfocusGateDivider();
	afx_msg void OnChangeTriggerLevel();
	afx_msg void OnKillfocusTriggerLevel();
	afx_msg void OnGatePositive();
	afx_msg void OnGateNegative();
	afx_msg void OnIgnore();
	afx_msg void OnMemorize();
	afx_msg void OnChangeModuloA();
	afx_msg void OnKillfocusModuloA();
	afx_msg void OnChangeModuloB();
	afx_msg void OnKillfocusModuloB();
	afx_msg void OnChangeModuloT0();
	afx_msg void OnKillfocusModuloT0();
	afx_msg void OnChangeOffsetA();
	afx_msg void OnKillfocusOffsetA();
	afx_msg void OnChangeOffsetB();
	afx_msg void OnKillfocusOffsetB();
	afx_msg void OnChangeOffsetT0();
	afx_msg void OnKillfocusOffsetT0();
	afx_msg void OnZeroModulo();
	//}}AFX_MSG
  afx_msg LRESULT OnChangeObjectProps(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollOffsetB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollInhibitTrigger(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollForceTrigger(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollTriggerLevel(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollGateDivider(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollPresetValue(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void DefaultDoneSignals(unsigned long* p_DoneT0, unsigned long* p_DoneA, unsigned long* p_DoneB);
	void LoadTriggerCounter(unsigned long TriggerCount);
	void UpdateGoSignals();
	void CheckGateChannels();
	void CheckHardwareControls();
	BOOL IsDefaultDoneSignal();
	int m_DG_Product;
	unsigned long m_ClockSource;
	BOOL b_ForceTriggerActive;
	BOOL b_CrystalOscillator;
	BOOL b_AllowArmInternal;
	BOOL b_FastApply;
	BOOL b_Master;
	void DiscretizeValues();
	unsigned long GoSignal_T0;
	unsigned long GoSignal_A;
	unsigned long GoSignal_B;
	unsigned long DoneSignal_T0;
	unsigned long DoneSignal_A;
	unsigned long DoneSignal_B;
	unsigned long MS_BusSignal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G05P2MASTERPP_H__09895F8E_ACE6_466E_B285_68E90D5D44DD__INCLUDED_)
