#if !defined(AFX_DONESELECTDLG_H__BFC4184F_9234_4ADC_BF04_CB90211C6BE2__INCLUDED_)
#define AFX_DONESELECTDLG_H__BFC4184F_9234_4ADC_BF04_CB90211C6BE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoneSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoneSelectDlg dialog

class CDoneSelectDlg : public CDialog
{
// Construction
public:
	CDoneSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDoneSelectDlg)
	enum { IDD = IDD_DONE_SELECT };
	CString	m_A_Name;
	CString	m_B_Name;
	BOOL	m_DoneForceA;
	BOOL	m_DoneForceB;
	BOOL	m_DoneForceT0;
	BOOL	m_DoneMsbA;
	BOOL	m_DoneMsbB;
	BOOL	m_DoneMsbT0;
	BOOL	m_DonePrimaryA;
	BOOL	m_DonePrimaryB;
	BOOL	m_DonePrimaryT0;
	BOOL	m_DoneSecondaryA;
	BOOL	m_DoneSecondaryB;
	BOOL	m_DoneSecondaryT0;
	CString	m_T0_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoneSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDoneSelectDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DONESELECTDLG_H__BFC4184F_9234_4ADC_BF04_CB90211C6BE2__INCLUDED_)
