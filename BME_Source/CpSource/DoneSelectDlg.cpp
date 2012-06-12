// DoneSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DoneSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoneSelectDlg dialog


CDoneSelectDlg::CDoneSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoneSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoneSelectDlg)
	m_A_Name = _T("");
	m_B_Name = _T("");
	m_DoneForceA = FALSE;
	m_DoneForceB = FALSE;
	m_DoneForceT0 = FALSE;
	m_DoneMsbA = FALSE;
	m_DoneMsbB = FALSE;
	m_DoneMsbT0 = FALSE;
	m_DonePrimaryA = FALSE;
	m_DonePrimaryB = FALSE;
	m_DonePrimaryT0 = FALSE;
	m_DoneSecondaryA = FALSE;
	m_DoneSecondaryB = FALSE;
	m_DoneSecondaryT0 = FALSE;
	m_T0_Name = _T("");
	//}}AFX_DATA_INIT
}


void CDoneSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoneSelectDlg)
	DDX_Text(pDX, IDC_A_NAME, m_A_Name);
	DDV_MaxChars(pDX, m_A_Name, 32);
	DDX_Text(pDX, IDC_B_NAME, m_B_Name);
	DDV_MaxChars(pDX, m_B_Name, 32);
	DDX_Check(pDX, IDC_DONE_FORCE_A, m_DoneForceA);
	DDX_Check(pDX, IDC_DONE_FORCE_B, m_DoneForceB);
	DDX_Check(pDX, IDC_DONE_FORCE_T0, m_DoneForceT0);
	DDX_Check(pDX, IDC_DONE_MSB_A, m_DoneMsbA);
	DDX_Check(pDX, IDC_DONE_MSB_B, m_DoneMsbB);
	DDX_Check(pDX, IDC_DONE_MSB_T0, m_DoneMsbT0);
	DDX_Check(pDX, IDC_DONE_PRIMARY_A, m_DonePrimaryA);
	DDX_Check(pDX, IDC_DONE_PRIMARY_B, m_DonePrimaryB);
	DDX_Check(pDX, IDC_DONE_PRIMARY_T0, m_DonePrimaryT0);
	DDX_Check(pDX, IDC_DONE_SECONDARY_A, m_DoneSecondaryA);
	DDX_Check(pDX, IDC_DONE_SECONDARY_B, m_DoneSecondaryB);
	DDX_Check(pDX, IDC_DONE_SECONDARY_T0, m_DoneSecondaryT0);
	DDX_Text(pDX, IDC_T0_NAME, m_T0_Name);
	DDV_MaxChars(pDX, m_T0_Name, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoneSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CDoneSelectDlg)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoneSelectDlg message handlers

BOOL CDoneSelectDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}
