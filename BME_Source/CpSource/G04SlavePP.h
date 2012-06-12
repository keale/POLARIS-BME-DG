#if !defined(AFX_G04SLAVEPP_H__3B884339_0596_11D5_BD4F_267400000000__INCLUDED_)
#define AFX_G04SLAVEPP_H__3B884339_0596_11D5_BD4F_267400000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// G04SlavePP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG04SlavePP dialog

#include "CursorEdit.h"

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

class CG04SlavePP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG04SlavePP)

// Construction
public:
	CString T0_Name;
	CString A_Name;
	CString B_Name;
	int m_DG_Number;
	CG0xData* p_G0xData;
	BOOL* p_DataModified;
	CWnd* p_ParentWindow;
	BOOL CollectVariables(DG_Type* p_DG);
	BOOL DistributeVariables(DG_Type* p_DG);
	CG04SlavePP();
	~CG04SlavePP();

// Dialog Data
	//{{AFX_DATA(CG04SlavePP)
	enum { IDD = IDD_G04_SLAVE };
	CCursorEdit	m_Delay_T0ED;
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
	CCursorEdit	m_SetBackT0ED;
	CCursorEdit	m_SetBackAED;
	CCursorEdit	m_SetBackBED;
	CCursorEdit	m_FireSecondT0ED;
	CCursorEdit	m_FireSecondAED;
	CCursorEdit	m_FireSecondBED;
	CButton	m_ActivateA_B;
	CButton	m_ActivateT0_B;
	CButton	m_ActivateB_B;
	BOOL	m_ActivateA;
	BOOL	m_ActivateB;
	BOOL	m_ActivateT0;
	CString	m_DelayA;
	CString	m_DelayB;
	CString	m_DelayT0;
	CString	m_FireSecondA;
	CString	m_FireSecondB;
	CString	m_FireSecondT0;
	BOOL	m_GateAB;
	CString	m_SetBackA;
	CString	m_SetBackB;
	CString	m_SetBackT0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG04SlavePP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG04SlavePP)
	afx_msg void OnActivateA();
	afx_msg void OnActivateB();
	afx_msg void OnActivateT0();
	afx_msg void OnChangeDelayA();
	afx_msg void OnChangeDelayB();
	afx_msg void OnChangeDelayT0();
	afx_msg void OnChangeFireSecondA();
	afx_msg void OnChangeFireSecondB();
	afx_msg void OnChangeFireSecondT0();
	afx_msg void OnGateAb();
	afx_msg void OnChangeSetBackA();
	afx_msg void OnChangeSetBackB();
	afx_msg void OnChangeSetBackT0();
	afx_msg void OnKillfocusDelayT0();
	afx_msg void OnKillfocusFireSecondT0();
	afx_msg void OnKillfocusSetBackA();
	afx_msg void OnKillfocusSetBackB();
	afx_msg void OnKillfocusSetBackT0();
	afx_msg void OnKillfocusFireSecondA();
	afx_msg void OnKillfocusFireSecondB();
	afx_msg void OnKillfocusDelayA();
	afx_msg void OnKillfocusDelayB();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
  afx_msg LRESULT OnScrollDelayT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollSetBackB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollFireSecondB(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void DiscretizeValues();
	BOOL b_PageActive;
	BOOL b_FastApply;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G04SLAVEPP_H__3B884339_0596_11D5_BD4F_267400000000__INCLUDED_)
