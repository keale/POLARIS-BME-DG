// FileOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "FileOptionsDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileOptionsDlg dialog


CFileOptionsDlg::CFileOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileOptionsDlg)
	m_CalibrationPath = _T("");
	//}}AFX_DATA_INIT
}


void CFileOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileOptionsDlg)
	DDX_Text(pDX, IDC_CALIBRATION_PATH, m_CalibrationPath);
	DDV_MaxChars(pDX, m_CalibrationPath, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CFileOptionsDlg)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_CALIBRATION_PATH, OnChangeCalibrationPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileOptionsDlg message handlers

BOOL CFileOptionsDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CFileOptionsDlg::OnBrowse() 
{
	CString CurrentFileName = "Modules.cal";
	CFileDialog fdg( TRUE, "cal", CurrentFileName, (OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
														"Calibration Files (*.cal)|*.cal| All Files (*.*)|*.*||", this);
	fdg.m_ofn.lpstrInitialDir = (LPCTSTR)m_CalibrationPath;
	if (fdg.DoModal() == IDOK)
	{
		CString CurrentFileName = fdg.GetFileName();
		CString FileName = fdg.GetPathName();
		CListRout lr;
		lr.TrimString(CurrentFileName);
		lr.TrimString(FileName);
		int Length = FileName.GetLength() - CurrentFileName.GetLength() - 1;
		m_CalibrationPath = FileName.Left(Length);
		UpdateData(FALSE);
	}	
}

void CFileOptionsDlg::OnChangeCalibrationPath() 
{
	UpdateData(TRUE);	
}
