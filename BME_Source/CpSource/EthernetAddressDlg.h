#if !defined(AFX_ETHERNETADDRESS_H__62092715_027E_4E50_8BF7_A626F28A8A26__INCLUDED_)
#define AFX_ETHERNETADDRESS_H__62092715_027E_4E50_8BF7_A626F28A8A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EthernetAddressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEthernetAddressDlg dialog

class CEthernetAddressDlg : public CDialog
{
// Construction
public:
	CEthernetAddressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEthernetAddressDlg)
	enum { IDD = IDD_ETHERNET_ADDRESS };
	CString	m_IpAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEthernetAddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEthernetAddressDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnChangeEthernetAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETHERNETADDRESS_H__62092715_027E_4E50_8BF7_A626F28A8A26__INCLUDED_)
