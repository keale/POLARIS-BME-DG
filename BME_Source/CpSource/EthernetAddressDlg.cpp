// EthernetAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "EthernetAddressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEthernetAddressDlg dialog


CEthernetAddressDlg::CEthernetAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEthernetAddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEthernetAddressDlg)
	m_IpAddress = _T("");
	//}}AFX_DATA_INIT
}


void CEthernetAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEthernetAddressDlg)
	DDX_Text(pDX, IDC_ETHERNET_ADDRESS, m_IpAddress);
	DDV_MaxChars(pDX, m_IpAddress, 24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEthernetAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CEthernetAddressDlg)
	ON_WM_HELPINFO()
	ON_EN_CHANGE(IDC_ETHERNET_ADDRESS, OnChangeEthernetAddress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEthernetAddressDlg message handlers

BOOL CEthernetAddressDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CEthernetAddressDlg::OnChangeEthernetAddress() 
{
	UpdateData(TRUE);	
}