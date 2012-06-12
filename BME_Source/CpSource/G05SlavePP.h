#if !defined(AFX_G05SLAVEPP_H__AAFDBE61_0819_11D6_BF16_E837C4000000__INCLUDED_)
#define AFX_G05SLAVEPP_H__AAFDBE61_0819_11D6_BF16_E837C4000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// G05SlavePP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CG05SlavePP dialog

#include "CursorEdit.h"

#define WM_USER_REQUEST_G05 (WM_USER + 1)
#define WM_FAST_APPLY_REQUEST_G05		(WM_USER + 5)

#define WM_USER_REQUEST_T0   (WM_USER + 11)
#define WM_USER_REQUEST_A    (WM_USER + 12)
#define WM_USER_REQUEST_B    (WM_USER + 13)
#define WM_USER_REQUEST_M_T0 (WM_USER + 14)
#define WM_USER_REQUEST_M_A  (WM_USER + 15)
#define WM_USER_REQUEST_M_B  (WM_USER + 16)


class CG05SlavePP : public CPropertyPage
{
	DECLARE_DYNCREATE(CG05SlavePP)

// Construction
public:
	CString T0_Name;
	CString A_Name;
	CString B_Name;
	int m_DG_Number;
	CG0xData* p_G0xData;
	BOOL* p_DataModified;
	CWnd* p_ParentWindow;
	BOOL b_RequestZeroModulo;
	BOOL CollectVariables(DG_Type* p_DG);
	BOOL DistributeVariables(DG_Type* p_DG);
	CG05SlavePP();
	~CG05SlavePP();

// Dialog Data
	//{{AFX_DATA(CG05SlavePP)
	enum { IDD = IDD_G05_SLAVE };
	CCursorEdit	m_Delay_T0ED;
	CCursorEdit	m_Delay_AED;
	CCursorEdit	m_Delay_BED;
	CCursorEdit	m_ModuloT0ED;
	CCursorEdit	m_ModuloAED;
	CCursorEdit	m_ModuloBED;
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
	CString	m_ModuloA;
	CString	m_ModuloB;
	CString	m_ModuloT0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CG05SlavePP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CG05SlavePP)
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
	afx_msg void OnChangeModuloA();
	afx_msg void OnKillfocusModuloA();
	afx_msg void OnChangeModuloB();
	afx_msg void OnKillfocusModuloB();
	afx_msg void OnChangeModuloT0();
	afx_msg void OnKillfocusModuloT0();
	afx_msg void OnZeroModulo();
	//}}AFX_MSG
  afx_msg LRESULT OnScrollDelayT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollDelayB(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloT0(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloA(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnScrollModuloB(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int m_DG_Product;
	void DiscretizeValues();
	BOOL b_PageActive;
	BOOL b_FastApply;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G05SLAVEPP_H__AAFDBE61_0819_11D6_BF16_E837C4000000__INCLUDED_)
