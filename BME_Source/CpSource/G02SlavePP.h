#if !defined(AFX_G02SLAVEPP_H__3B884336_0596_11D5_BD4F_267400000000__INCLUDED_)
#define AFX_G02SLAVEPP_H__3B884336_0596_11D5_BD4F_267400000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// G02SlavePP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG02SlavePP dialog

#include "CursorEdit.h"

#define WM_FAST_APPLY_REQUEST_G02		(WM_USER + 5)

#define WM_USER_REQUEST_T0   (WM_USER + 11)
#define WM_USER_REQUEST_A    (WM_USER + 12)
#define WM_USER_REQUEST_B    (WM_USER + 13)


class CG02SlavePP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG02SlavePP)

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
	CG02SlavePP();
	~CG02SlavePP();

// Dialog Data
	//{{AFX_DATA(CG02SlavePP)
	enum { IDD = IDD_G02_SLAVE };
	CCursorEdit	m_Delay_T0ED;
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
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
	BOOL	m_GateAB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG02SlavePP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG02SlavePP)
	afx_msg void OnActivateA();
	afx_msg void OnActivateB();
	afx_msg void OnActivateT0();
	afx_msg void OnChangeDelayA();
	afx_msg void OnChangeDelayB();
	afx_msg void OnChangeDelayT0();
	afx_msg void OnGateAb();
	afx_msg void OnKillfocusDelayT0();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillfocusDelayA();
	afx_msg void OnKillfocusDelayB();
	//}}AFX_MSG
  afx_msg LRESULT OnScrollDelayT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int m_DG_Product;
	void DiscretizeValues();
	BOOL b_FastApply;
	BOOL b_PageActive;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G02SLAVEPP_H__3B884336_0596_11D5_BD4F_267400000000__INCLUDED_)
