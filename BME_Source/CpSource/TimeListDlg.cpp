// TimeListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "..\Spectra_BME\ParameterRoutineDlg.h"
#include "..\Spectra_BME\EditParameterLineDlg.h"
#include "TimeListDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"
#include "..\Spectra_BME\ReplaceLineDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeListDlg dialog


CTimeListDlg::CTimeListDlg(CG0xData* p_GDat, CWnd* pParent /*=NULL*/)
	: CDialog(CTimeListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeListDlg)
	m_FpgaMemoryWorkLine = _T("");
	//}}AFX_DATA_INIT
	p_G0xData = p_GDat;
	b_CBModified = FALSE;
	b_DataModified = FALSE;
	p_ParameterRoutineDlg = NULL;
	p_EditParameterLineDlg = NULL;
	b_ListLoaded = FALSE;
	CurrentFileName = _T("");
	CurrentPath = _T("");
}


CTimeListDlg::~CTimeListDlg()
{
	delete p_ParameterRoutineDlg;
	delete p_EditParameterLineDlg;
	m_FpgaMemoryList.RemoveAll();
}
void CTimeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeListDlg)
	DDX_Control(pDX, IDC_FPGA_MEMORY_LIST, m_FpgaMemoryListCB);
	DDX_CBString(pDX, IDC_FPGA_MEMORY_LIST, m_FpgaMemoryWorkLine);
	DDV_MaxChars(pDX, m_FpgaMemoryWorkLine, 255);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeListDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeListDlg)
	ON_BN_CLICKED(IDC_X_PARAMETER_DEFINE, OnXParameterDefine)
	ON_CBN_SELENDOK(IDC_FPGA_MEMORY_LIST, OnSelendokFpgaMemoryList)
	ON_CBN_SETFOCUS(IDC_FPGA_MEMORY_LIST, OnSetfocusFpgaMemoryList)
	ON_BN_CLICKED(IDC_EDIT_PARAMETER, OnEditParameter)
	ON_BN_CLICKED(IDC_REMOVE_LINE, OnRemoveLine)
	ON_BN_CLICKED(IDC_ERASE_LIST, OnEraseList)
	ON_BN_CLICKED(IDC_REMOVE_COLUMN, OnRemoveColumn)
	ON_BN_CLICKED(IDC_READ_FILE, OnReadFile)
	ON_BN_CLICKED(IDC_SAVE_FILE, OnSaveFile)
	ON_WM_HELPINFO()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeListDlg message handlers

BOOL CTimeListDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CTimeListDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (p_ParameterRoutineDlg == NULL)
	{
		p_ParameterRoutineDlg = new CParameterRoutineDlg(this);
		p_ParameterRoutineDlg->p_XParameterListCB = &m_FpgaMemoryListCB;
		p_ParameterRoutineDlg->p_DataModified = &b_DataModified;
	}
	if (p_EditParameterLineDlg == NULL)
	{
		p_EditParameterLineDlg = new CEditParameterLineDlg(this);
		p_EditParameterLineDlg->p_ParameterLineCB = &m_FpgaMemoryListCB;
		p_EditParameterLineDlg->p_DataModified = &b_DataModified;
	}
}

void CTimeListDlg::OnXParameterDefine() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_FpgaMemoryListCB, m_FpgaMemoryList);
		b_ListLoaded = TRUE;
	}
	p_ParameterRoutineDlg->Create(IDD_PARAMETER_ROUTINE,this);
}

void CTimeListDlg::OnSetfocusFpgaMemoryList() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_FpgaMemoryListCB, m_FpgaMemoryList);
		b_ListLoaded = TRUE;
	}
}

void CTimeListDlg::OnSelendokFpgaMemoryList() 
{
	UpdateData(TRUE);
	CurrentLineNo = m_FpgaMemoryListCB.GetCurSel();
	p_EditParameterLineDlg->ReadSelectedLine();
	//m_FpgaMemoryListCB.SetEditSel(0,-1);
	//AfxMessageBox("CTimeListDlg::OnSelendokFpgaMemoryList",MB_OK,0);
}


void CTimeListDlg::OnEditParameter() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_FpgaMemoryListCB, m_FpgaMemoryList);
		b_ListLoaded = TRUE;
	}
	p_EditParameterLineDlg->Create(IDD_EDIT_PARAMETERS,this);
}

void CTimeListDlg::OnReadFile() 
{
	CFileDialog fdg( TRUE, "fpm", CurrentFileName, (OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
														"FPGA Memory Files (*.fpm)|*.fpm| All Files (*.*)|*.*||", this);
	fdg.m_ofn.lpstrInitialDir = (LPCTSTR)CurrentPath;
	if (fdg.DoModal() == IDOK)
	{
		CurrentFileName = fdg.GetFileName();
		CString FileName = fdg.GetPathName();
		CListRout lr;
		lr.TrimString(CurrentFileName);
		lr.TrimString(FileName);
		lr.ReadTxtFileComboBox(FileName, m_FpgaMemoryListCB);
		int Length = FileName.GetLength() - CurrentFileName.GetLength() - 1;
		CurrentPath = FileName.Left(Length);
		b_DataModified = TRUE;
	}
	CWnd::SetFocus();
}

void CTimeListDlg::OnSaveFile() 
{
	CFileDialog fdg( FALSE, "fpm", CurrentFileName, (OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
														"FPGA Memory Files (*.fpm)|*.fpm| All Files (*.*)|*.*||", this);
	fdg.m_ofn.lpstrInitialDir = (LPCTSTR)CurrentPath;
	if (fdg.DoModal() == IDOK)
	{
		CurrentFileName = fdg.GetFileName();
		CString FileName = fdg.GetPathName();
		CListRout lr;
		lr.TrimString(CurrentFileName);
		lr.TrimString(FileName);
		lr.WriteTxtFileComboBox(FileName, m_FpgaMemoryListCB); 
		int Length = FileName.GetLength() - CurrentFileName.GetLength() - 1;
		CurrentPath = FileName.Left(Length);
	}
	CWnd::SetFocus();
}

void CTimeListDlg::OnRemoveLine() 
{
	CListRout lr;
	BOOL success = lr.DeleteSelectedLine(m_FpgaMemoryListCB);
	if (!success)
		AfxMessageBox("no line removed!",MB_OK,0);
	else
		b_DataModified = TRUE;
}

void CTimeListDlg::OnEraseList() 
{
	int count = m_FpgaMemoryListCB.GetCount();
	if (count > 0)
	{
		if (AfxMessageBox("Erase content of parameter list?",MB_YESNO,0) == IDYES)
		{
			m_FpgaMemoryListCB.ResetContent();
			b_DataModified = TRUE;
		}
	}
}

void CTimeListDlg::OnRemoveColumn() 
{
	CListRout lr;
	int NoLines = lr.GetLineCount(m_FpgaMemoryListCB);
	if (NoLines > 0)
	{
		int NoColumns = lr.GetNumberParameters(m_FpgaMemoryListCB, 1);
		switch (NoColumns)
		{
			case 0:
				return;
			case 1:
				if (AfxMessageBox("Erase content of parameter list?",MB_YESNO,0) == IDYES)
				{
					m_FpgaMemoryListCB.ResetContent();
					b_DataModified = TRUE;
				}
				return;
			default:
				CReplaceLineDlg dlg;
				dlg.m_ReplaceLine = NoColumns;
				dlg.m_Title = _T("Remove Column");
				if (dlg.DoModal() == IDOK)
				{
					int SelectedColumn = dlg.m_ReplaceLine;
					if (SelectedColumn <= NoColumns)
					{
						int i1;
						BOOL success;
						for (i1 = 1; i1 <= NoLines; i1++)
						{
							success = lr.RemoveParameter(m_FpgaMemoryListCB, i1, SelectedColumn);
							if (!success)
							{
								AfxMessageBox("parameter could not be removed list!",MB_OK,0);
								return;
							}
						}
						b_DataModified = TRUE;
					}
					else
					{
						CString kstr;
						kstr.Format("Parameter list has only %d columns!", NoColumns);
						AfxMessageBox(kstr, MB_OK, 0);
					}
				}
				return;
		}
	}
}

void CTimeListDlg::CollectVariables() 
{
	if ((CurrentLineNo != CB_ERR) && (b_CBModified))
	{
		m_FpgaMemoryListCB.DeleteString(CurrentLineNo);
		m_FpgaMemoryListCB.InsertString(CurrentLineNo, m_FpgaMemoryWorkLine);
		b_CBModified = FALSE;
	}
	int NoLines = m_FpgaMemoryList.GetSize();
	if (NoLines > MemLength )
	{
		CString kstr,jstr;
		kstr.Format("FPGA memory list is %d lines long!", NoLines);
		jstr.Format("\n only %d lines allowed", MemLength);
		kstr += jstr;
		AfxMessageBox(kstr, MB_OK, 0);
	}
	else
	{
		p_G0xData->WriteFpgaMemory(m_FpgaMemoryList);
		b_DataModified = FALSE;
	}
}

void CTimeListDlg::DistributeVariables() 
{
	m_FpgaMemoryWorkLine = _T("");
	p_G0xData->ReadFpgaMemory(m_FpgaMemoryList);

	b_DataModified = FALSE;
}

void CTimeListDlg::OnCancel() 
{
	if (b_DataModified)
	{
		if (AfxMessageBox("Data has been modified\n    quit anyway?",
														(MB_YESNO | MB_DEFBUTTON2), 0) == IDYES)
		{
			m_FpgaMemoryListCB.ResetContent();
			CDialog::OnCancel();
		}
	}
	else
	{
		m_FpgaMemoryListCB.ResetContent();
		CDialog::OnCancel();
	}
}

void CTimeListDlg::OnOK() 
{
	CListRout lr;
	if (b_ListLoaded)
		lr.ReadComboBox(m_FpgaMemoryList, m_FpgaMemoryListCB);
	CDialog::OnOK();
}
