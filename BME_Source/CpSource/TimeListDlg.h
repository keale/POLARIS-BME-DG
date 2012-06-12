#if !defined(AFX_TIMELISTDLG_H__52B5364F_8E60_4CDF_8016_3365833ED89D__INCLUDED_)
#define AFX_TIMELISTDLG_H__52B5364F_8E60_4CDF_8016_3365833ED89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeListDlg dialog

class CTimeListDlg : public CDialog
{
// Construction
public:
	virtual ~CTimeListDlg();
	void DistributeVariables();
	void CollectVariables();
	CTimeListDlg(CG0xData* p_GDat, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeListDlg)
	enum { IDD = IDD_TIME_LIST };
	CComboBox	m_FpgaMemoryListCB;
	CString	m_FpgaMemoryWorkLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeListDlg)
	afx_msg void OnXParameterDefine();
	afx_msg void OnSelendokFpgaMemoryList();
	afx_msg void OnSetfocusFpgaMemoryList();
	afx_msg void OnEditParameter();
	afx_msg void OnRemoveLine();
	afx_msg void OnReadFile();
	afx_msg void OnSaveFile();
	afx_msg void OnEraseList();
	afx_msg void OnRemoveColumn();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL	b_ListLoaded;
	CStringArray	m_FpgaMemoryList;
	CG0xData* p_G0xData;
	BOOL b_DataModified;
	BOOL b_CBModified;
	int CurrentLineNo;
	CParameterRoutineDlg* p_ParameterRoutineDlg;
	CEditParameterLineDlg* p_EditParameterLineDlg;
	CString CurrentFileName;
	CString CurrentPath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMELISTDLG_H__52B5364F_8E60_4CDF_8016_3365833ED89D__INCLUDED_)
