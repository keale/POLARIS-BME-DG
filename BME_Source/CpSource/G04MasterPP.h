#if !defined(AFX_G04MASTERPP_H__3B884334_0596_11D5_BD4F_267400000000__INCLUDED_)
#define AFX_G04MASTERPP_H__3B884334_0596_11D5_BD4F_267400000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// G04MasterPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG04MasterPP dialog

#include "CursorEdit.h"

#define WM_USER_REQUEST_G04 (WM_USER + 1)
#define WM_LOAD_COUNTER_REQUEST_G04 (WM_USER + 4)
#define WM_FAST_APPLY_REQUEST_G04		(WM_USER + 5)

#define WM_USER_REQUEST_T0   (WM_USER + 11)
#define WM_USER_REQUEST_A    (WM_USER + 12)
#define WM_USER_REQUEST_B    (WM_USER + 13)
#define WM_USER_REQUEST_R_T0 (WM_USER + 14)
#define WM_USER_REQUEST_R_A  (WM_USER + 15)
#define WM_USER_REQUEST_R_B  (WM_USER + 16)
#define WM_USER_REQUEST_S_T0 (WM_USER + 17)
#define WM_USER_REQUEST_S_A  (WM_USER + 18)
#define WM_USER_REQUEST_S_B  (WM_USER + 19)
#define WM_USER_REQUEST_PRD  (WM_USER + 20)
#define WM_USER_REQUEST_TLV  (WM_USER + 21)
#define WM_USER_REQUEST_GD	 (WM_USER + 22)
#define WM_USER_REQUEST_PVA  (WM_USER + 23)

class CG04MasterPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG04MasterPP)

// Construction
public:
	CString T0_Name;
	CString A_Name;
	CString B_Name;
	int m_DG_Number;
	unsigned long NoEvents;
	CG0xData* p_G0xData;
	BOOL b_RequestZeroCounter;
	CWnd* p_ParentWindow;
	BOOL* p_DataModified;
	HANDLE	DataNotification;
	BOOL b_PageActive;
	BOOL CollectVariables(DG_Type* p_DG);
	BOOL DistributeVariables(DG_Type* p_DG);
	CG04MasterPP();
	~CG04MasterPP();

// Dialog Data
	//{{AFX_DATA(CG04MasterPP)
	enum { IDD = IDD_G04_MASTER };
	CCursorEdit	m_Delay_T0ED;
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
	CCursorEdit	m_SetBackT0ED;
	CCursorEdit	m_SetBackAED;
	CCursorEdit	m_SetBackBED;
	CCursorEdit	m_FireSecondT0ED;
	CCursorEdit	m_FireSecondAED;
	CCursorEdit	m_FireSecondBED;
	CCursorEdit	m_TriggerPeriodED;
	CCursorEdit	m_TriggerLevelED;
	CCursorEdit	m_GateDividerED;
	CCursorEdit	m_PresetValueED;
	CButton	m_GateNegativeB;
	CButton	m_RisingB;
	CButton	m_FallingB;
	CButton	m_ExternalB;
	CButton	m_GatePositiveB;
	CButton	m_ArmByInternalB;
	CButton	m_ActivateA_B;
	CButton	m_ActivateT0_B;
	CButton	m_ActivateB_B;
	CButton	m_Designator;
	BOOL	m_ActivateA;
	BOOL	m_ActivateB;
	BOOL	m_ActivateT0;
	CString	m_DelayA;
	CString	m_DelayB;
	CString	m_DelayT0;
	BOOL	m_External;
	BOOL	m_Falling;
	BOOL	m_GateAB;
	BOOL	m_Internal;
	CString	m_PresetValue;
	BOOL	m_Rising;
	CString	m_SetBackA;
	CString	m_SetBackB;
	CString	m_SetBackT0;
	BOOL	m_StopOnPreset;
	CString	m_TriggerPeriod;
	CString	m_TriggerCount;
	BOOL	m_ReadTriggers;
	BOOL	m_ArmByInternal;
	CString	m_GateDivider;
	BOOL	m_GatePositive;
	CString	m_TriggerLevel;
	CString	m_FireSecondA;
	CString	m_FireSecondB;
	CString	m_FireSecondT0;
	BOOL	m_GateNegative;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG04MasterPP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG04MasterPP)
	afx_msg void OnChangeFireSecondA();
	afx_msg void OnChangeFireSecondB();
	afx_msg void OnChangeFireSecondT0();
	afx_msg void OnKillfocusFireSecondT0();
	afx_msg void OnKillfocusFireSecondA();
	afx_msg void OnKillfocusFireSecondB();
	afx_msg void OnActivateA();
	afx_msg void OnActivateB();
	afx_msg void OnActivateT0();
	afx_msg void OnChangeDelayA();
	afx_msg void OnChangeDelayB();
	afx_msg void OnChangeDelayT0();
	afx_msg void OnExternal();
	afx_msg void OnFalling();
	afx_msg void OnGateAb();
	afx_msg void OnInternal();
	afx_msg void OnChangePresetValue();
	afx_msg void OnRising();
	afx_msg void OnChangeSetBackA();
	afx_msg void OnChangeSetBackB();
	afx_msg void OnChangeSetBackT0();
	afx_msg void OnStopOnPreset();
	afx_msg void OnChangeTriggerPeriod();
	afx_msg void OnKillfocusDelayT0();
	afx_msg void OnKillfocusSetBackA();
	afx_msg void OnKillfocusSetBackB();
	afx_msg void OnKillfocusSetBackT0();
	afx_msg void OnKillfocusPresetValue();
	afx_msg void OnKillfocusTriggerPeriod();
	afx_msg void OnResetCounter();
	afx_msg void OnChangeTriggerCount();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillfocusDelayA();
	afx_msg void OnKillfocusDelayB();
	afx_msg void OnReadTriggers();
	afx_msg void OnArmByInternal();
	afx_msg void OnGatePositive();
	afx_msg void OnChangeGateDivider();
	afx_msg void OnKillfocusGateDivider();
	afx_msg void OnChangeTriggerLevel();
	afx_msg void OnKillfocusTriggerLevel();
	afx_msg void OnGateNegative();
	//}}AFX_MSG
  afx_msg LRESULT OnChangeObjectProps(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollTriggerPeriod(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollTriggerLevel(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollGateDivider(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollPresetValue(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void LoadTriggerCounter(unsigned long TriggerCount);
	int m_DG_Product;
	BOOL b_AllowArmInternal;
	BOOL b_CrystalOscillator;
	BOOL b_FastApply;
	void DiscretizeValues();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G04MASTERPP_H__3B884334_0596_11D5_BD4F_267400000000__INCLUDED_)
