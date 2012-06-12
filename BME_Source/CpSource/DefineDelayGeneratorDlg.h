#if !defined(AFX_DEFINEDELAYGENERATORDLG_H__0EACD133_050B_11D5_BD4E_8E9F54000000__INCLUDED_)
#define AFX_DEFINEDELAYGENERATORDLG_H__0EACD133_050B_11D5_BD4E_8E9F54000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DefineDelayGeneratorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDefineDelayGeneratorDlg dialog

class CDefineDelayGeneratorDlg : public CDialog
{
// Construction
public:
	CComboBox* p_DelgenTableCB;
	CTypedPtrList<CPtrList, DG_Type*>* p_DG_List;
	void ReadSelectedLine();
	void UpdateControls();
	BOOL UpdateEditLine();
	void RemoveWindow();
	BOOL* p_DataModified;
	BOOL b_onScreen;
	CDefineDelayGeneratorDlg(CG0xData* p_GDat, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDefineDelayGeneratorDlg)
	enum { IDD = IDD_DEFINE_DELAY_GENERATOR };
	CButton	m_T0_ClockB;
	CButton	m_T0_DelayClockB;
	CButton	m_A_DelayClockB;
	CButton	m_B_DelayClockB;
	CButton	m_ResynchB;
	CButton	m_MsBusClockB;
	CButton	m_SecondaryGoB;
	CButton	m_PrimaryGoB;
	CButton	m_ForceGoB;
	CButton	m_StepBackOnBusB;
	CButton	m_StartOnBusB;
	CButton	m_InhibitOnBusB;
	CButton	m_LoadDataOnBusB;
	CEdit	m_PulseWidthED;
	CStatic	m_AddressLine;
	CEdit	m_EthernetAddressED;
	CEdit	m_TriggerDividerED;
	CEdit	m_TriggerMultiplierED;
	CButton	m_FreeRunningB;
	CButton	m_EclLevelB;
	CButton	m_NimLevelB;
	CButton	m_TtlLevelB;
	CButton	m_T0_HighDriveB;
	CButton	m_B_HighDriveB;
	CButton	m_A_HighDriveB;
	CButton	m_CrystalOscillatorB;
	CButton	m_TriggerInputB;
	CEdit	m_DgPrescalerED;
	CButton	m_TriggerTerminateB;
	CButton	m_GateTerminateB;
	CButton	m_UseFB;
	CButton	m_GateMsPB;
	CButton	m_GateMsNB;
	CEdit	m_T0_NameED;
	CButton	m_T0_PositiveB;
	CButton	m_T0_TerminateB;
	CButton	m_T0_NegativeB;
	CButton	m_A_TerminateB;
	CButton	m_A_PositiveB;
	CButton	m_A_NegativeB;
	CButton	m_B_TerminateB;
	CButton	m_B_PositiveB;
	CButton	m_B_NegativeB;
	CEdit	m_C_NameED;
	CButton	m_C_TerminateB;
	CButton	m_C_PositiveB;
	CButton	m_C_NegativeB;
	CEdit	m_D_NameED;
	CButton	m_D_TerminateB;
	CButton	m_D_PositiveB;
	CButton	m_D_NegativeB;
	CEdit	m_E_NameED;
	CButton	m_E_TerminateB;
	CButton	m_E_PositiveB;
	CButton	m_E_NegativeB;
	CButton	m_E_DisconnectB;
	CButton	m_E_MsBusB;
	CButton	m_E_InputPB;
	CButton	m_E_InputNB;
	CButton	m_F_TerminateB;
	CEdit	m_F_NameED;
	CButton	m_F_PositiveB;
	CButton	m_F_NegativeB;
	CButton	m_F_DisconnectB;
	CButton	m_F_MsBusB;
	CButton	m_F_InputPB;
	CButton	m_F_InputNB;
	CEdit	m_DgBusED;
	CComboBox	m_DgTypeCB;
	CString	m_DgAddress;
	CString	m_DgBus;
	BOOL	m_DgMaster;
	CString	m_DgType;
	CString	m_DgPrescaler;
	CString	m_A_Name;
	BOOL	m_A_Negative;
	BOOL	m_A_Positive;
	BOOL	m_A_Terminate;
	CString	m_B_Name;
	BOOL	m_B_Negative;
	BOOL	m_B_Positive;
	BOOL	m_B_Terminate;
	CString	m_C_Name;
	BOOL	m_C_Negative;
	BOOL	m_C_Positive;
	BOOL	m_C_Terminate;
	CString	m_D_Name;
	BOOL	m_D_Negative;
	BOOL	m_D_Positive;
	BOOL	m_D_Terminate;
	CString	m_E_Name;
	BOOL	m_E_Negative;
	BOOL	m_E_Positive;
	BOOL	m_E_Terminate;
	CString	m_F_Name;
	BOOL	m_F_Negative;
	BOOL	m_F_Positive;
	BOOL	m_F_Terminate;
	CString	m_DgName;
	CString	m_T0_Name;
	BOOL	m_T0_Negative;
	BOOL	m_T0_Positive;
	BOOL	m_T0_Terminate;
	BOOL	m_TriggerTerminate;
	BOOL	m_GateTerminate;
	BOOL	m_UseF;
	BOOL	m_GateMsP;
	BOOL	m_GateMsN;
	BOOL	m_TriggerInput;
	BOOL	m_CrystalOscillator;
	BOOL	m_A_HighDrive;
	BOOL	m_B_HighDrive;
	BOOL	m_T0_HighDrive;
	BOOL	m_TtlLevel;
	BOOL	m_NimLevel;
	BOOL	m_EclLevel;
	BOOL	m_FreeRunning;
	CString	m_EthernetAddress;
	CString	m_TriggerDivider;
	CString	m_TriggerMultiplier;
	CString	m_PulseWidth;
	BOOL	m_ForceGo;
	BOOL	m_PrimaryGo;
	BOOL	m_SecondaryGo;
	BOOL	m_StepBackOnBus;
	BOOL	m_StartOnBus;
	BOOL	m_InhibitOnBus;
	BOOL	m_LoadDataOnBus;
	BOOL	m_MsBusClock;
	BOOL	m_T0_Clock;
	BOOL	m_T0_DelayClock;
	BOOL	m_A_DelayClock;
	BOOL	m_B_DelayClock;
	BOOL	m_Resynch;
	BOOL	m_E_Disconnect;
	BOOL	m_F_Disconnect;
	BOOL	m_E_MsBus;
	BOOL	m_F_MsBus;
	BOOL	m_E_InputP;
	BOOL	m_E_InputN;
	BOOL	m_F_InputP;
	BOOL	m_F_InputN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefineDelayGeneratorDlg)
	public:
	virtual BOOL Create(UINT nID, CWnd* pParentWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefineDelayGeneratorDlg)
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnChangeDgAddress();
	afx_msg void OnChangeDgBus();
	afx_msg void OnChangeIpAddress();
	afx_msg void OnKillfocusIpAddress();
	afx_msg void OnDgMaster();
	afx_msg void OnSelendokDgType();
	afx_msg void OnInsertLine();
	afx_msg void OnReplaceLine();
	virtual void OnCancel();
	afx_msg void OnChangeDgPrescaler();
	afx_msg void OnKillfocusDgPrescaler();
	afx_msg void OnANegative();
	afx_msg void OnAPositive();
	afx_msg void OnATerminate();
	afx_msg void OnADelayClock();
	afx_msg void OnBNegative();
	afx_msg void OnBPositive();
	afx_msg void OnBTerminate();
	afx_msg void OnBDelayClock();
	afx_msg void OnCNegative();
	afx_msg void OnCPositive();
	afx_msg void OnCTerminate();
	afx_msg void OnDNegative();
	afx_msg void OnDPositive();
	afx_msg void OnDTerminate();
	afx_msg void OnENegative();
	afx_msg void OnEPositive();
	afx_msg void OnETerminate();
	afx_msg void OnFNegative();
	afx_msg void OnFPositive();
	afx_msg void OnFTerminate();
	afx_msg void OnChangeAName();
	afx_msg void OnChangeBName();
	afx_msg void OnChangeCName();
	afx_msg void OnChangeDName();
	afx_msg void OnChangeEName();
	afx_msg void OnChangeFName();
	afx_msg void OnChangeDgName();
	afx_msg void OnChangeT0Name();
	afx_msg void OnT0Negative();
	afx_msg void OnT0Positive();
	afx_msg void OnT0Terminate();
	afx_msg void OnTriggerTerminate();
	afx_msg void OnGateTerminate();
	afx_msg void OnUseF();
	afx_msg void OnGateMsP();
	afx_msg void OnGateMsN();
	afx_msg void OnKillfocusDgName();
	afx_msg void OnKillfocusAName();
	afx_msg void OnKillfocusBName();
	afx_msg void OnKillfocusCName();
	afx_msg void OnKillfocusDName();
	afx_msg void OnKillfocusEName();
	afx_msg void OnKillfocusFName();
	afx_msg void OnKillfocusT0Name();
	afx_msg void OnCrystalOscillator();
	afx_msg void OnTriggerInput();
	afx_msg void OnAHighDrive();
	afx_msg void OnBHighDrive();
	afx_msg void OnT0HighDrive();
	afx_msg void OnTtlLevel();
	afx_msg void OnNimLevel();
	afx_msg void OnEclLevel();
	afx_msg void OnFreeRunning();
	afx_msg void OnChangeTriggerDivider();
	afx_msg void OnKillfocusTriggerDivider();
	afx_msg void OnChangeTriggerMultiplier();
	afx_msg void OnKillfocusTriggerMultiplier();
	afx_msg void OnChangePulseWidth();
	afx_msg void OnKillfocusPulseWidth();
	afx_msg void OnForceGo();
	afx_msg void OnPrimaryGo();
	afx_msg void OnSecondaryGo();
	afx_msg void OnStepBackOnBus();
	afx_msg void OnStartOnBus();
	afx_msg void OnInhibitOnBus();
	afx_msg void OnLoadDataOnBus();
	afx_msg void OnMsBusClock();
	afx_msg void OnT0Clock();
	afx_msg void OnT0DelayClock();
	afx_msg void OnResynch();
	afx_msg void OnEDisconnect();
	afx_msg void OnFDisconnect();
	afx_msg void OnEMsBus();
	afx_msg void OnFMsBus();
	afx_msg void OnEInputP();
	afx_msg void OnEInputN();
	afx_msg void OnFInputP();
	afx_msg void OnFInputN();
	//}}AFX_MSG
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int CountBusLines();
	void CheckHardwareControls();
	void InitializeOutputState();
	void ResetMenu();
	BOOL DiscretizeValues();
	void InsertList(int LineNo, BOOL Before);
	void ReplaceList(int LineNo);
	CG0xData* p_G0xData;
	CString WorkLine;
	WINDOWPLACEMENT WindowFrame;
	int CurrentLineNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFINEDELAYGENERATORDLG_H__0EACD133_050B_11D5_BD4E_8E9F54000000__INCLUDED_)
