#if !defined(AFX_CONFIGURATIONTABLEDLG_H__C5322C14_04D3_11D5_8FD9_0050DADE1976__INCLUDED_)
#define AFX_CONFIGURATIONTABLEDLG_H__C5322C14_04D3_11D5_8FD9_0050DADE1976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfigurationTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigurationTableDlg dialog

#include "DefineDelayGeneratorDlg.h"

class CConfigurationTableDlg : public CDialog
{
// Construction
public:
	CTypedPtrList<CPtrList, DG_Type*> DG_List;
	virtual ~CConfigurationTableDlg();
	CConfigurationTableDlg(CG0xData* p_G0xData, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigurationTableDlg)
	enum { IDD = IDD_CONFIGURATION_TABLE };
	CComboBox	m_DelgenTableCB;
	BOOL	m_CalibrateTiming;
	BOOL	m_CalibrateOffset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigurationTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigurationTableDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnDefineDelayGenerator();
	afx_msg void OnSelendokDelgenTable();
	afx_msg void OnRemoveDelayGenerator();
	afx_msg void OnSetfocusDelgenTable();
	virtual void OnCancel();
	afx_msg void OnCalibrateTiming();
	afx_msg void OnDetectPci();
	afx_msg void OnAddEthernet();
	afx_msg void OnCalibrateOffset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDefineDelayGeneratorDlg* p_DefineDelayGeneratorDlg;
	CG0xData* p_G0xData;
	BOOL b_DataModified;
	BOOL b_DelgenTableLoaded;
	void LoadDelgenTable();
	void LoadDelgenList(int FirstPos, int NoDelgen, char* p_IpAddr);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATIONTABLEDLG_H__C5322C14_04D3_11D5_8FD9_0050DADE1976__INCLUDED_)
