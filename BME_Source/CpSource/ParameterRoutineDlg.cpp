// ParameterRoutineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Spectra_BME.h"
#include "CommonDefinitions.h"
#include "ParameterRoutineDlg.h"
#include "ListRout.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterRoutineDlg dialog


CParameterRoutineDlg::CParameterRoutineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterRoutineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterRoutineDlg)
	m_InsertColumn = FALSE;
	m_NewColumn = TRUE;
	m_FirstPoint = _T("");
	m_LastPoint = _T("");
	m_NoSteps = _T("");
	m_StepSize = _T("");
	m_ColumnNo = _T("");
	m_ValidDigits = _T("");
	//}}AFX_DATA_INIT
	b_onScreen=FALSE;
	b_ValidList = FALSE;
	CRect crp;
	crp.SetRectEmpty();
	WindowFrame.rcNormalPosition = crp;
}


void CParameterRoutineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterRoutineDlg)
	DDX_Check(pDX, IDC_INSERT_COLUMN, m_InsertColumn);
	DDX_Check(pDX, IDC_NEW_COLUMN, m_NewColumn);
	DDX_Text(pDX, IDC_FIRST_POINT, m_FirstPoint);
	DDV_MaxChars(pDX, m_FirstPoint, 32);
	DDX_Text(pDX, IDC_LAST_POINT, m_LastPoint);
	DDV_MaxChars(pDX, m_LastPoint, 32);
	DDX_Text(pDX, IDC_NO_STEPS, m_NoSteps);
	DDV_MaxChars(pDX, m_NoSteps, 32);
	DDX_Text(pDX, IDC_PARAMETER_STEP_SIZE, m_StepSize);
	DDV_MaxChars(pDX, m_StepSize, 32);
	DDX_Text(pDX, IDC_COLUMN_NO, m_ColumnNo);
	DDV_MaxChars(pDX, m_ColumnNo, 32);
	DDX_Text(pDX, IDC_VALID_DIGITS, m_ValidDigits);
	DDV_MaxChars(pDX, m_ValidDigits, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterRoutineDlg, CDialog)
	//{{AFX_MSG_MAP(CParameterRoutineDlg)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CALCULATE_SEQUENCE, OnCalculateSequence)
	ON_EN_CHANGE(IDC_COLUMN_NO, OnChangeColumnNo)
	ON_EN_CHANGE(IDC_FIRST_POINT, OnChangeFirstPoint)
	ON_BN_CLICKED(IDC_INSERT_COLUMN, OnInsertColumn)
	ON_EN_CHANGE(IDC_LAST_POINT, OnChangeLastPoint)
	ON_BN_CLICKED(IDC_NEW_COLUMN, OnNewColumn)
	ON_EN_CHANGE(IDC_NO_STEPS, OnChangeNoSteps)
	ON_EN_CHANGE(IDC_PARAMETER_STEP_SIZE, OnChangeStepSize)
	ON_EN_CHANGE(IDC_VALID_DIGITS, OnChangeValidDigits)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterRoutineDlg message handlers

BOOL CParameterRoutineDlg::Create(UINT nID, CWnd* pParentWnd)
{
	BOOL nResult = FALSE;
	if (!b_onScreen)
	{
		nResult = CDialog::Create(nID, pParentWnd);
		CRect crp;
		crp = WindowFrame.rcNormalPosition;
		if (crp.IsRectEmpty())
			GetWindowPlacement(&WindowFrame);
		SetWindowPlacement(&WindowFrame);
		b_onScreen = TRUE;
	}
	else
		SetWindowPlacement(&WindowFrame);
	CWnd::SetFocus();
	return nResult;
}

void CParameterRoutineDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID != SC_MAXIMIZE)
	{
		if (nID == SC_CLOSE)
			RemoveWindow();
		CDialog::OnSysCommand(nID, lParam);		
	}
}

void CParameterRoutineDlg::PostNcDestroy() 
{
	b_onScreen=FALSE;
	CDialog::PostNcDestroy();
}

void CParameterRoutineDlg::RemoveWindow()
{
	b_onScreen=FALSE;
	DestroyWindow();	
}

void CParameterRoutineDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	if ((b_onScreen) && (!IsIconic()))
		GetWindowPlacement(&WindowFrame);
}

void CParameterRoutineDlg::OnCancel() 
{
	RemoveWindow();	
	//CDialog::OnCancel();
}

void CParameterRoutineDlg::OnOK() 
{
	if (b_ValidList)
	{
		ApplyData();
		RemoveWindow();
	}
	else
		AfxMessageBox("please first calculate a valid list!",MB_OK,0);
}

void CParameterRoutineDlg::OnApply() 
{
	if (b_ValidList)
		ApplyData();
	else
		AfxMessageBox("please first calculate a valid list!",MB_OK,0);
}

void CParameterRoutineDlg::ApplyData()
{
	CListRout lr;
	int NoSteps,TestNo,i1;
	double FirstPoint,StepSize,value;
	BOOL success;
	CString str,jstr;
	int ValidDigits = atoi(m_ValidDigits);
	TestNo = lr.GetLineCount(*p_XParameterListCB);
	if ((m_NewColumn) || (TestNo == 0))
	{
		m_ColumnNo = _T("1");
		UpdateData(FALSE);
		p_XParameterListCB->ResetContent();
		FirstPoint = atof(m_FirstPoint);
		StepSize = atof(m_StepSize);
		NoSteps = atoi(m_NoSteps);
		str = lr.FormatCharacters(10, ValidDigits, 'f');
		jstr = " %4d: " + str;
		i1 = 0;
		value = FirstPoint;
		while (i1 <= NoSteps)
		{
			str.Format(jstr, (i1 + 1), value);
			p_XParameterListCB->AddString(str);
			value += StepSize;
			i1++;
		}
		*p_DataModified = TRUE;
	}
	else
	{
		NoSteps = atoi(m_NoSteps);
		if ((TestNo - NoSteps) != 1)
		{
			str = "the number of steps specified does not\n match the existing list!! ";
			str += "\n\n you can either construct a new list\n or specify a differnt number of steps.";
			AfxMessageBox(str,MB_OK,0);
			return;
		}
		TestNo = lr.GetNumberParameters(*p_XParameterListCB, 1);
		m_ColumnNo.TrimRight();
		m_ColumnNo.TrimLeft();
		if (m_ColumnNo.GetLength() == 0)
		{
			str = "please enter column number where parameter list should go!";
			AfxMessageBox(str,MB_OK,0);
			return;
		}
		int ColumnNo = atoi(m_ColumnNo);
		ColumnNo = max(1, min((TestNo + 1), ColumnNo));
		m_ColumnNo.Format("%1d", ColumnNo);
		UpdateData(FALSE);
		CStringArray WorkArray;
		lr.ReadComboBox(WorkArray, *p_XParameterListCB);
		FirstPoint = atof(m_FirstPoint);
		StepSize = atof(m_StepSize);
		jstr = lr.FormatCharacters(10, ValidDigits, 'f');
		i1 = 0;
		value = FirstPoint;
		while (i1 <= NoSteps)
		{
			i1++;
			str.Format(jstr, value);
			success = lr.InsertParameter(WorkArray, str, i1, ColumnNo);
			if (!success)
			{
				AfxMessageBox("parameter could not be entered into list!",MB_OK,0);
				return;
			}
			value += StepSize;
		}
		lr.WriteComboBox(*p_XParameterListCB, WorkArray);
		WorkArray.RemoveAll();
		*p_DataModified = TRUE;
	}
}

void CParameterRoutineDlg::OnCalculateSequence() 
{
	CListRout sr;
	int npm = 0;
	int mark,NoSteps;
	double FirstPoint,LastPoint,StepSize;
	int Digits = 0;
	sr.TrimString(m_FirstPoint);
	sr.TrimString(m_LastPoint);
	sr.TrimString(m_NoSteps);
	sr.TrimString(m_StepSize);
	if (m_FirstPoint.GetLength() > 0)
	{
		FirstPoint = atof(m_FirstPoint);
		Digits = max(Digits, sr.DecimalDigits(m_FirstPoint));
		npm++;
	}
	else
		mark = 1;
	if (m_LastPoint.GetLength() > 0)
	{
		LastPoint = atof(m_LastPoint);
		Digits = max(Digits, sr.DecimalDigits(m_LastPoint));
		npm++;
		}
	else
		mark = 2;
	if (m_NoSteps.GetLength() > 0)
	{
		NoSteps = atoi(m_NoSteps);
		npm++;
	}
	else
		mark = 3;
	if (m_StepSize.GetLength() > 0)
	{
		StepSize = atof(m_StepSize);
		Digits = max(Digits, sr.DecimalDigits(m_StepSize));
		npm++;
	}
	else
		mark = 4;
	if (npm != 3)
	{
		AfxMessageBox("3 Parameters have to be defined,\n one field must be left empty!",MB_OK,0);
		return;
	}
	else
	{
		CString str;
		switch (mark)
		{
		case 1:
			FirstPoint = LastPoint - StepSize * NoSteps;
			str = sr.FormatCharacters(1, Digits, 'f');
			m_FirstPoint.Format(str,FirstPoint);
			break;
		case 2:
			LastPoint = FirstPoint + StepSize * NoSteps;
			str = sr.FormatCharacters(1, Digits, 'f');
			m_LastPoint.Format(str,LastPoint);
			break;
		case 3:
			NoSteps = max(1,RoundInt(((LastPoint - FirstPoint)/StepSize)));
			StepSize = (LastPoint - FirstPoint)/((double) NoSteps);
			str = sr.FormatCharacters(1, Digits, 'f');
			m_StepSize.Format(str,StepSize);
			str = sr.FormatCharacters(1,'d');
			m_NoSteps.Format(str,NoSteps);
			break;
		case 4:
			StepSize = (LastPoint - FirstPoint)/((double) NoSteps);
			str = sr.FormatCharacters(1, Digits, 'f');
			m_StepSize.Format(str,StepSize);
			double TestStep = atof(m_StepSize);
			while (fabs((StepSize - TestStep)/StepSize) > 1.0e-4)
			{
				Digits++;
				str = sr.FormatCharacters(1, Digits, 'f');
				m_StepSize.Format(str,StepSize);
				TestStep = atof(m_StepSize);
			}
			break;
		}
		m_ValidDigits.Format("%1d",Digits);
		b_ValidList = TRUE;
		UpdateData(FALSE);
	}
}

void CParameterRoutineDlg::OnChangeColumnNo() 
{
	UpdateData(TRUE);
}

void CParameterRoutineDlg::OnChangeFirstPoint() 
{
	UpdateData(TRUE);
	b_ValidList = FALSE;
}

void CParameterRoutineDlg::OnInsertColumn() 
{
	UpdateData(TRUE);
	m_NewColumn = !m_InsertColumn;
	UpdateData(FALSE);
}

void CParameterRoutineDlg::OnChangeLastPoint() 
{
	UpdateData(TRUE);
	b_ValidList = FALSE;
}

void CParameterRoutineDlg::OnNewColumn() 
{
	UpdateData(TRUE);
	m_InsertColumn = !m_NewColumn;
	UpdateData(FALSE);
}

void CParameterRoutineDlg::OnChangeNoSteps() 
{
	UpdateData(TRUE);
	b_ValidList = FALSE;
}

void CParameterRoutineDlg::OnChangeStepSize() 
{
	UpdateData(TRUE);
	b_ValidList = FALSE;
}

void CParameterRoutineDlg::OnChangeValidDigits() 
{
	UpdateData(TRUE);
}

BOOL CParameterRoutineDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CDialog::OnHelpInfo(pHelpInfo);
}
