#if !defined(AFX_FILEOPTIONSDLG_H__9533CFD4_0C09_11D6_90AC_0050DADE1976__INCLUDED_)
#define AFX_FILEOPTIONSDLG_H__9533CFD4_0C09_11D6_90AC_0050DADE1976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FileOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileOptionsDlg dialog

class CFileOptionsDlg : public CDialog
{
// Construction
public:
	CFileOptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileOptionsDlg)
	enum { IDD = IDD_FILE_OPTIONS };
	CString	m_CalibrationPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileOptionsDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBrowse();
	afx_msg void OnChangeCalibrationPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPTIONSDLG_H__9533CFD4_0C09_11D6_90AC_0050DADE1976__INCLUDED_)
