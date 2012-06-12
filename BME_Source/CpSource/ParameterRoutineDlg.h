// ParameterRoutineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameterRoutineDlg dialog

class CParameterRoutineDlg : public CDialog
{
// Construction
public:
	BOOL* p_DataModified;
	CComboBox* p_XParameterListCB;
	void RemoveWindow();
	BOOL b_onScreen;
	CParameterRoutineDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameterRoutineDlg)
	enum { IDD = IDD_PARAMETER_ROUTINE };
	BOOL	m_InsertColumn;
	BOOL	m_NewColumn;
	CString	m_FirstPoint;
	CString	m_LastPoint;
	CString	m_NoSteps;
	CString	m_StepSize;
	CString	m_ColumnNo;
	CString	m_ValidDigits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterRoutineDlg)
	public:
	virtual BOOL Create(UINT nID, CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameterRoutineDlg)
	afx_msg void OnMove(int x, int y);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnCalculateSequence();
	afx_msg void OnChangeColumnNo();
	afx_msg void OnChangeFirstPoint();
	afx_msg void OnInsertColumn();
	afx_msg void OnChangeLastPoint();
	afx_msg void OnNewColumn();
	afx_msg void OnChangeNoSteps();
	afx_msg void OnChangeStepSize();
	afx_msg void OnChangeValidDigits();
	afx_msg void OnApply();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void ApplyData();
	BOOL b_ValidList;
	WINDOWPLACEMENT WindowFrame;
};
