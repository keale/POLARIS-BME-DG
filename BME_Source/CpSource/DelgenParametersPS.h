#if !defined(AFX_DELGENPARAMETERSPS_H__3B884333_0596_11D5_BD4F_267400000000__INCLUDED_)
#define AFX_DELGENPARAMETERSPS_H__3B884333_0596_11D5_BD4F_267400000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DelgenParametersPS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDelgenParametersPS

#include "G05MasterPP.h"
#include "G05p2MasterPP.h"
#include "G05p4MasterPP.h"
#include "G05SlavePP.h"
#include "G03MasterPP.h"
#include "G03SlavePP.h"
#include "G02p3MasterPP.h"
#include "G02MasterPP.h"
#include "G02SlavePP.h"

#define WM_USER_REQUEST							(WM_USER + 1)
#define WM_APPLY_REQUEST						(WM_USER + 2)
#define WM_LOAD_COUNTER_REQUEST			(WM_USER + 4)
#define WM_FAST_APPLY_REQUEST				(WM_USER + 5)
#define WM_LOAD_FREQUENCY_REQUEST		(WM_USER + 6)


typedef struct
{
	CString* p_Title;
	union
	{
		void* p_PP;
		CG05MasterPP* p_G05MasterPP;
		CG05p2MasterPP* p_G05p2MasterPP;
		CG05p4MasterPP* p_G05p4MasterPP;
		CG05SlavePP* p_G05SlavePP;
		CG03MasterPP* p_G03MasterPP;
		CG03SlavePP* p_G03SlavePP;
		CG02p3MasterPP* p_G02p3MasterPP;
		CG02MasterPP* p_G02MasterPP;
		CG02SlavePP* p_G02SlavePP;
	};
}	DG_PageType;

class CDelgenParametersPS : public CPropertySheet
{
	DECLARE_DYNAMIC(CDelgenParametersPS)

// Construction
public:
	int m_ActiveIndex	;
	CWnd* p_ParentWindow;
	void MainLoop();
	void ZeroSelectedCounter();
	CDelgenParametersPS(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDelgenParametersPS(CG0xData* p_GDat, LPCTSTR pszCaption, 
										CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelgenParametersPS)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDelgenParametersPS();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDelgenParametersPS)
	afx_msg void OnOkNow();
	afx_msg void OnCancelNow();
	afx_msg void OnApplyNow();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
  afx_msg LRESULT OnChangeObjectProps(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnFastApply(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	_int64 TriggerCount;
	HANDLE	DataNotification;
	BOOL b_DataModified;
	BOOL b_CounterThreadActive;
	BOOL b_RemoveCounterThread;
	BOOL b_ZeroCounterSynchronuously;
	CG0xData* p_G0xData;
	DG_PageType* p_Page;
	int NoPages;
	CFont* p_font;
	BOOL CollectVariables(BOOL b_RequestZeroModulo, BOOL b_RequestJumpStart);
	void CheckCounterThread();
	void LoadTriggerCounters();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELGENPARAMETERSPS_H__3B884333_0596_11D5_BD4F_267400000000__INCLUDED_)
