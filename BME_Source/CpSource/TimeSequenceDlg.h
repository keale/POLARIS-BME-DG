#if !defined(AFX_TIMESEQUENCEDLG_H__434CAFD3_FB82_11D5_BF00_4AC945000000__INCLUDED_)
#define AFX_TIMESEQUENCEDLG_H__434CAFD3_FB82_11D5_BF00_4AC945000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TimeSequenceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeSequenceDlg dialog

class CTimeSequenceDlg : public CDialog
{
// Construction
public:
	virtual ~CTimeSequenceDlg();
	void DistributeVariables();
	void CollectVariables();
	CTimeSequenceDlg(CG0xData* p_GDat, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeSequenceDlg)
	enum { IDD = IDD_TIME_SEQUENCE };
	CComboBox	m_XParameterListCB;
	BOOL	m_Continuously;
	BOOL	m_DownAndUp;
	BOOL	m_Downwards;
	BOOL	m_Once;
	BOOL	m_UpAndDown;
	BOOL	m_Upwards;
	CString	m_XParameterWorkLine;
	CString	m_MaxNoDatasets;
	CString	m_TimePerStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSequenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeSequenceDlg)
	afx_msg void OnXParameterDefine();
	afx_msg void OnContinuously();
	afx_msg void OnDownAndUp();
	afx_msg void OnDownwards();
	afx_msg void OnOnce();
	afx_msg void OnUpAndDown();
	afx_msg void OnUpwards();
	afx_msg void OnSelendokXParameterList();
	afx_msg void OnEditParameter();
	afx_msg void OnRemoveLine();
	afx_msg void OnEraseList();
	afx_msg void OnRemoveColumn();
	afx_msg void OnChangeMaxNoDatasets();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeTimePerStep();
	afx_msg void OnKillfocusTimePerStep();
	virtual void OnCancel();
	afx_msg void OnSetfocusXParameterList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL	b_ListLoaded;
	CStringArray	m_XParameterList;
	CG0xData* p_G0xData;
	void DiscretizeValues();
	void UpdateXParameterList();
	BOOL b_DataModified;
	BOOL b_CBModified;
	int CurrentLineNo;
	CParameterRoutineDlg* p_ParameterRoutineDlg;
	CEditParameterLineDlg* p_EditParameterLineDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESEQUENCEDLG_H__434CAFD3_FB82_11D5_BF00_4AC945000000__INCLUDED_)
