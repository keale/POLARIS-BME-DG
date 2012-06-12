// TimeSequenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "..\Spectra_BME\ParameterRoutineDlg.h"
#include "..\Spectra_BME\EditParameterLineDlg.h"
#include "TimeSequenceDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"
#include "..\Spectra_BME\ReplaceLineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeSequenceDlg dialog


CTimeSequenceDlg::CTimeSequenceDlg(CG0xData* p_GDat, CWnd* pParent /*=NULL*/)
	: CDialog(CTimeSequenceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeSequenceDlg)
	m_Continuously = TRUE;
	m_DownAndUp = FALSE;
	m_Downwards = FALSE;
	m_Once = FALSE;
	m_UpAndDown = TRUE;
	m_Upwards = FALSE;
	m_XParameterWorkLine = _T("");
	m_MaxNoDatasets = _T("");
	m_TimePerStep = _T("");
	//}}AFX_DATA_INIT
	p_G0xData = p_GDat;
	b_CBModified = FALSE;
	b_DataModified = FALSE;
	p_ParameterRoutineDlg = NULL;
	p_EditParameterLineDlg = NULL;
	b_ListLoaded = FALSE;
}

CTimeSequenceDlg::~CTimeSequenceDlg()
{
	delete p_ParameterRoutineDlg;
	delete p_EditParameterLineDlg;
	m_XParameterList.RemoveAll();
}


void CTimeSequenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeSequenceDlg)
	DDX_Control(pDX, IDC_X_PARAMETER_LIST, m_XParameterListCB);
	DDX_Check(pDX, IDC_CONTINUOUSLY, m_Continuously);
	DDX_Check(pDX, IDC_DOWN_AND_UP, m_DownAndUp);
	DDX_Check(pDX, IDC_DOWNWARDS, m_Downwards);
	DDX_Check(pDX, IDC_ONCE, m_Once);
	DDX_Check(pDX, IDC_UP_AND_DOWN, m_UpAndDown);
	DDX_Check(pDX, IDC_UPWARDS, m_Upwards);
	DDX_CBString(pDX, IDC_X_PARAMETER_LIST, m_XParameterWorkLine);
	DDV_MaxChars(pDX, m_XParameterWorkLine, 255);
	DDX_Text(pDX, IDC_MAX_NO_DATASETS, m_MaxNoDatasets);
	DDV_MaxChars(pDX, m_MaxNoDatasets, 8);
	DDX_Text(pDX, IDC_TIME_PER_STEP, m_TimePerStep);
	DDV_MaxChars(pDX, m_TimePerStep, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeSequenceDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeSequenceDlg)
	ON_BN_CLICKED(IDC_X_PARAMETER_DEFINE, OnXParameterDefine)
	ON_BN_CLICKED(IDC_CONTINUOUSLY, OnContinuously)
	ON_BN_CLICKED(IDC_DOWN_AND_UP, OnDownAndUp)
	ON_BN_CLICKED(IDC_DOWNWARDS, OnDownwards)
	ON_BN_CLICKED(IDC_ONCE, OnOnce)
	ON_BN_CLICKED(IDC_UP_AND_DOWN, OnUpAndDown)
	ON_BN_CLICKED(IDC_UPWARDS, OnUpwards)
	ON_CBN_SELENDOK(IDC_X_PARAMETER_LIST, OnSelendokXParameterList)
	ON_BN_CLICKED(IDC_EDIT_PARAMETER, OnEditParameter)
	ON_BN_CLICKED(IDC_REMOVE_LINE, OnRemoveLine)
	ON_BN_CLICKED(IDC_ERASE_LIST, OnEraseList)
	ON_BN_CLICKED(IDC_REMOVE_COLUMN, OnRemoveColumn)
	ON_EN_CHANGE(IDC_MAX_NO_DATASETS, OnChangeMaxNoDatasets)
	ON_WM_HELPINFO()
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_TIME_PER_STEP, OnChangeTimePerStep)
	ON_EN_KILLFOCUS(IDC_TIME_PER_STEP, OnKillfocusTimePerStep)
	ON_CBN_SETFOCUS(IDC_X_PARAMETER_LIST, OnSetfocusXParameterList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeSequenceDlg message handlers

void CTimeSequenceDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (p_ParameterRoutineDlg == NULL)
	{
		p_ParameterRoutineDlg = new CParameterRoutineDlg(this);
		p_ParameterRoutineDlg->p_XParameterListCB = &m_XParameterListCB;
		p_ParameterRoutineDlg->p_DataModified = &b_DataModified;
	}
	if (p_EditParameterLineDlg == NULL)
	{
		p_EditParameterLineDlg = new CEditParameterLineDlg(this);
		p_EditParameterLineDlg->p_ParameterLineCB = &m_XParameterListCB;
		p_EditParameterLineDlg->p_DataModified = &b_DataModified;
	}
}

BOOL CTimeSequenceDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}

void CTimeSequenceDlg::OnChangeTimePerStep() 
{
	UpdateData(TRUE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnKillfocusTimePerStep() 
{
	CListRout lr;
	lr.TrimString(m_TimePerStep);
	if (m_TimePerStep.GetLength() > 0)
	{
		double t0 = atof(m_TimePerStep);
		t0 = max(0.001, t0);
		m_TimePerStep.Format(" %4.3f", t0);
		m_TimePerStep = lr.TrimTrailingZeros(m_TimePerStep);
	}
	UpdateData(FALSE);
}

void CTimeSequenceDlg::OnXParameterDefine() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_XParameterListCB, m_XParameterList);
		b_ListLoaded = TRUE;
	}
	p_ParameterRoutineDlg->Create(IDD_PARAMETER_ROUTINE,this);
}

void CTimeSequenceDlg::OnOnce() 
{
	UpdateData(TRUE);
	m_Continuously = !m_Once;
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnContinuously() 
{
	UpdateData(TRUE);
	m_Once = !m_Continuously;
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnUpAndDown() 
{
	UpdateData(TRUE);
	if (m_UpAndDown)
	{
		m_DownAndUp = FALSE;
		m_Downwards = FALSE;
		m_Upwards = FALSE;
	}
	else
	{
		m_DownAndUp = TRUE;
		m_Downwards = FALSE;
		m_Upwards = FALSE;
	}
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnDownAndUp() 
{
	UpdateData(TRUE);
	if (m_DownAndUp)
	{
		m_UpAndDown = FALSE;
		m_Downwards = FALSE;
		m_Upwards = FALSE;
	}
	else
	{
		m_UpAndDown = FALSE;
		m_Downwards = FALSE;
		m_Upwards = TRUE;
	}
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnUpwards() 
{
	UpdateData(TRUE);
	if (m_Upwards)
	{
		m_UpAndDown = FALSE;
		m_Downwards = FALSE;
		m_DownAndUp = FALSE;
	}
	else
	{
		m_UpAndDown = FALSE;
		m_DownAndUp = FALSE;
		m_Downwards = TRUE;
	}
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnDownwards() 
{
	UpdateData(TRUE);
	if (m_Downwards)
	{
		m_UpAndDown = FALSE;
		m_Upwards = FALSE;
		m_DownAndUp = FALSE;
	}
	else
	{
		m_DownAndUp = FALSE;
		m_Upwards = FALSE;
		m_UpAndDown = TRUE;
	}
	UpdateData(FALSE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnChangeMaxNoDatasets() 
{
	UpdateData(TRUE);
	b_DataModified = TRUE;
}

void CTimeSequenceDlg::UpdateXParameterList()
{
	if ((CurrentLineNo != CB_ERR) && (b_CBModified))
	{
		m_XParameterListCB.DeleteString(CurrentLineNo);
		m_XParameterListCB.InsertString(CurrentLineNo, m_XParameterWorkLine);
		b_CBModified = FALSE;
		b_DataModified = TRUE;
	 	//AfxMessageBox("CTimeSequenceDlg::UpdateXParameterList",MB_OK,0);
	  //AfxMessageBox(m_XParameterWorkLine,MB_OK,0);
	}
}

void CTimeSequenceDlg::OnSetfocusXParameterList() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_XParameterListCB, m_XParameterList);
		b_ListLoaded = TRUE;
	}
}

void CTimeSequenceDlg::OnSelendokXParameterList() 
{
	UpdateData(TRUE);
	CurrentLineNo = m_XParameterListCB.GetCurSel();
	p_EditParameterLineDlg->ReadSelectedLine();
	//m_XParameterListCB.SetEditSel(0,-1);
	//AfxMessageBox("CTimeSequenceDlg::OnSelendokXParameterList",MB_OK,0);
}


void CTimeSequenceDlg::OnEditParameter() 
{
	if (!b_ListLoaded)
	{
		CListRout lr;
		lr.WriteComboBox(m_XParameterListCB, m_XParameterList);
		b_ListLoaded = TRUE;
	}
	p_EditParameterLineDlg->Create(IDD_EDIT_PARAMETERS,this);
}

void CTimeSequenceDlg::OnRemoveLine() 
{
	CListRout lr;
	BOOL success = lr.DeleteSelectedLine(m_XParameterListCB);
	if (!success)
		AfxMessageBox("no line removed!",MB_OK,0);
	else
		b_DataModified = TRUE;
}

void CTimeSequenceDlg::OnEraseList() 
{
	int count = m_XParameterListCB.GetCount();
	if (count > 0)
	{
		if (AfxMessageBox("Erase content of parameter list?",MB_YESNO,0) == IDYES)
		{
			m_XParameterListCB.ResetContent();
			b_DataModified = TRUE;
		}
	}
}

void CTimeSequenceDlg::OnRemoveColumn() 
{
	CListRout lr;
	int NoLines = lr.GetLineCount(m_XParameterListCB);
	if (NoLines > 0)
	{
		int NoColumns = lr.GetNumberParameters(m_XParameterListCB, 1);
		switch (NoColumns)
		{
			case 0:
				return;
			case 1:
				if (AfxMessageBox("Erase content of parameter list?",MB_YESNO,0) == IDYES)
				{
					m_XParameterListCB.ResetContent();
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
							success = lr.RemoveParameter(m_XParameterListCB, i1, SelectedColumn);
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

void CTimeSequenceDlg::DiscretizeValues()
{
	CListRout lr;
	lr.TrimString(m_TimePerStep);
	if (m_TimePerStep.GetLength() > 0)
	{
		double t0 = atof(m_TimePerStep);
		t0 = max(0.001, t0);
		m_TimePerStep.Format(" %4.3f", t0);
		m_TimePerStep = lr.TrimTrailingZeros(m_TimePerStep);
	}
}

void CTimeSequenceDlg::CollectVariables() 
{
	DiscretizeValues();
	XParameterType vct;
	p_G0xData->ResetTimeSequence(vct);
	vct.m_Continuously = m_Continuously;
	vct.m_Once = m_Once;
	if ((m_DownAndUp) || (m_Downwards))
	{
		vct.m_Downwards = TRUE;
		if (m_DownAndUp)
			vct.m_BothDirection = TRUE;
	}
	if ((m_UpAndDown) || (m_Upwards))
	{
		vct.m_Upwards = TRUE;
		if (m_UpAndDown)
			vct.m_BothDirection = TRUE;
	}
	vct.m_SubcycleLimit = FALSE;
	vct.MaxSubcycles = 0;
	CListRout lr;
	lr.TrimString(m_MaxNoDatasets);
	if (m_MaxNoDatasets.GetLength() > 0)
	{
		if (lr.Numeric(m_MaxNoDatasets))
		{
			if (RoundInt(atof(m_MaxNoDatasets)) > 0)
			{
				vct.m_SubcycleLimit = TRUE;
				vct.MaxSubcycles = RoundInt(atof(m_MaxNoDatasets));
			}
		}
	}
	lr.TrimString(m_TimePerStep);
	if (m_TimePerStep.GetLength() > 0)
	{
		double t0 = 1000.0 * atof(m_TimePerStep);
		t0 = max(1.0, t0);
		vct.MilliSecondsPerStep = RoundInt(t0);
	}
	if ((CurrentLineNo != CB_ERR) && (b_CBModified))
	{
		m_XParameterListCB.DeleteString(CurrentLineNo);
		m_XParameterListCB.InsertString(CurrentLineNo, m_XParameterWorkLine);
		b_CBModified = FALSE;
	}
	p_G0xData->WriteXParameter(m_XParameterList, vct);
	b_DataModified = FALSE;
}


void CTimeSequenceDlg::DistributeVariables() 
{
	XParameterType vct;
	m_XParameterWorkLine = _T("");
	p_G0xData->ReadXParameter(m_XParameterList, vct);
	m_Downwards = FALSE;
	m_Upwards = FALSE;
	m_DownAndUp = FALSE;
	m_UpAndDown = FALSE;
	if (vct.m_Downwards)
	{
		if (vct.m_BothDirection)
			m_DownAndUp = TRUE;
		else
			m_Downwards = TRUE;
	}
	if (vct.m_Upwards)
	{
		if (vct.m_BothDirection)
			m_UpAndDown = TRUE;
		else
			m_Upwards = TRUE;
	}
	m_Once = vct.m_Once;
	m_Continuously = vct.m_Continuously;
	m_MaxNoDatasets = _T("");
	if ((vct.m_SubcycleLimit) && (vct.MaxSubcycles > 0))
		m_MaxNoDatasets.Format(" %d", vct.MaxSubcycles);
	double t0 = (double(vct.MilliSecondsPerStep) / 1000.0);
	m_TimePerStep.Format(" %4.3f", t0);
	CListRout lr;
	m_TimePerStep = lr.TrimTrailingZeros(m_TimePerStep);
	b_DataModified = FALSE;
}

void CTimeSequenceDlg::OnCancel() 
{
	if (b_DataModified)
	{
		if (AfxMessageBox("Data has been modified\n    quit anyway?",
														(MB_YESNO | MB_DEFBUTTON2), 0) == IDYES)
		{
			m_XParameterListCB.ResetContent();
			CDialog::OnCancel();
		}
	}
	else
	{
		m_XParameterListCB.ResetContent();
		CDialog::OnCancel();
	}
}

void CTimeSequenceDlg::OnOK() 
{
	CListRout lr;
	if (b_ListLoaded)
		lr.ReadComboBox(m_XParameterList, m_XParameterListCB);
	CDialog::OnOK();
}
