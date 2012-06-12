// BME_G0XView.cpp : implementation of the CBME_G0XView class
//

#include "stdafx.h"
#include "BME_G0X.h"

#include "DG_Data.h"
#include "G0xData.h"
#include "BME_G0XDoc.h"
#include "BME_G0XView.h"
#include "ConfigurationTableDlg.h"
#include "..\Spectra_BME\ParameterRoutineDlg.h"
#include "..\Spectra_BME\EditParameterLineDlg.h"
#include "TimeListDlg.h"
#include "TimeSequenceDlg.h"
#include "FileOptionsDlg.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define  G0x_ReadOnly


/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView

IMPLEMENT_DYNCREATE(CBME_G0XView, CScrollView)

BEGIN_MESSAGE_MAP(CBME_G0XView, CScrollView)
	//{{AFX_MSG_MAP(CBME_G0XView)
	ON_COMMAND(ID_CONFIGURE, OnConfigure)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE, OnUpdateConfigure)
	ON_COMMAND(ID_DELAY, OnDelay)
	ON_UPDATE_COMMAND_UI(ID_DELAY, OnUpdateDelay)
	ON_COMMAND(ID_ACTIVATE, OnActivate)
	ON_UPDATE_COMMAND_UI(ID_ACTIVATE, OnUpdateActivate)
	ON_COMMAND(ID_DEACTIVATE, OnDeactivate)
	ON_UPDATE_COMMAND_UI(ID_DEACTIVATE, OnUpdateDeactivate)
	ON_COMMAND(ID_TIME_SEQUENCE, OnTimeSequence)
	ON_COMMAND(ID_TIME_LIST, OnTimeList)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	ON_UPDATE_COMMAND_UI(ID_TIME_SEQUENCE, OnUpdateTimeSequence)
	ON_UPDATE_COMMAND_UI(ID_TIME_LIST, OnUpdateTimeList)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPTIONS, OnUpdateFileOptions)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_SAVE_STATE, OnSaveState)
	ON_UPDATE_COMMAND_UI(ID_SAVE_STATE, OnUpdateSaveState)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_APPLY_REQUEST, OnChangeObjectProps)
	ON_MESSAGE(WM_WRITE_REQUEST, OnWriteExpParm)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView construction/destruction

CBME_G0XView::CBME_G0XView()
{
	p_ClientDC = NULL;
	p_DelgenParametersPS = NULL;
	InitializeCriticalSection(&DataAccess);
	ControlNotification = CreateEvent(NULL, TRUE, FALSE, NULL);
	ExitNotification = CreateEvent(NULL, TRUE, FALSE, NULL);
	p_DelgenControl = new CDelgenControl(this);
	p_DelgenControl->ControlNotification = ControlNotification;
	p_DelgenControl->ExitNotification = ExitNotification;
	ResetFileOptions(FileOptions);
	CurrentFileName = _T("");
	CurrentPath = _T("");
}

CBME_G0XView::~CBME_G0XView()
{
	DeleteCriticalSection(&DataAccess);
	delete p_DelgenControl;
	if (p_DelgenParametersPS != NULL)
		delete p_DelgenParametersPS;
}

BOOL CBME_G0XView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView drawing

void CBME_G0XView::OnDraw(CDC* pDC)
{
	CBME_G0XDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//p_G0xData = (GetDocument()->p_G0xData);
	pDoc->DeleteContents();
	p_G0xData->ScrollPosition = GetDeviceScrollPosition();
	CSize TextExtent = p_G0xData->WriteExperimentalSetup();
	CSize MinExtent = GetDocument()->GetDocSize();
	TextExtent.cx = max(TextExtent.cx, MinExtent.cx);
	TextExtent.cy = max(TextExtent.cy, MinExtent.cy);
	SetScrollSizes( MM_TEXT, TextExtent );

}

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView printing

BOOL CBME_G0XView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	//return DoPreparePrinting(pInfo);
	AfxMessageBox("no printing has been implemeted yet!",MB_OK,0);
	return FALSE;
}

void CBME_G0XView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CBME_G0XView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView diagnostics

#ifdef _DEBUG
void CBME_G0XView::AssertValid() const
{
	CView::AssertValid();
}

void CBME_G0XView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBME_G0XDoc* CBME_G0XView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBME_G0XDoc)));
	return (CBME_G0XDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XView message handlers


LRESULT CBME_G0XView::OnChangeObjectProps(WPARAM, LPARAM)
{
	CheckControlThread();
	return 0;
}

LRESULT CBME_G0XView::OnWriteExpParm(WPARAM, LPARAM)
{
#ifdef WINDOWSNT
	UpdateExpSetup();
#endif
	return 0;
}

void CBME_G0XView::OnInitialUpdate() 
{
	CRect Rect;
	GetClientRect( &Rect );
	InvalidateRect(&Rect);
	GetDocument()->DeleteContents();
	p_G0xData->ScrollPosition = GetDeviceScrollPosition();
	CSize TextExtent = p_G0xData->WriteExperimentalSetup();
	CSize MinExtent = GetDocument()->GetDocSize();
	TextExtent.cx = max(TextExtent.cx, MinExtent.cx);
	TextExtent.cy = max(TextExtent.cy, MinExtent.cy);
	SetScrollSizes( MM_TEXT, TextExtent );
	CScrollView::OnInitialUpdate();
}

void CBME_G0XView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	p_G0xData = (GetDocument()->p_G0xData);
	p_G0xData->p_DataAccess = &DataAccess;
	CopyFileOptions(p_G0xData->FileOptions, FileOptions);
	p_DelgenControl->UpdateDataPointer(p_G0xData);
	if (p_ClientDC == NULL)
		p_ClientDC = new CClientDC(this);
	p_G0xData->p_ClientDC = p_ClientDC;
}

UINT StartControlThread( LPVOID pParam )
{
 	CDelgenControl* p_DelgenControl = (CDelgenControl*)pParam;
	p_DelgenControl->MainLoop();
	return 0;
}

void CBME_G0XView::UpdateExpSetup()
{
	CRect Rect;
	GetClientRect( &Rect );
	InvalidateRect(&Rect);
	GetDocument()->DeleteContents();
	p_G0xData->ScrollPosition = GetDeviceScrollPosition();
	if (p_ClientDC != NULL)
		delete p_ClientDC;
	//if (p_ClientDC == NULL)
	p_ClientDC = new CClientDC(this);
	p_G0xData->p_ClientDC = p_ClientDC;
	p_G0xData->WriteExperimentalSetup();
}

void CBME_G0XView::CheckControlThread()
{
	if (p_G0xData->m_DG_List.GetCount() > 0)
	{
		p_DelgenControl->b_InitializeControl = TRUE;
		if (!p_DelgenControl->b_ControlThreadActive)
		{
			p_DelgenControl->b_ControlThreadActive = TRUE;
			p_DelgenControl->b_RemoveControlThread = FALSE;
			p_DelgenControl->b_RequestRemoveControlThread = FALSE;
			LPVOID pParam = this->p_DelgenControl;
			AfxBeginThread(StartControlThread, pParam, THREAD_PRIORITY_BELOW_NORMAL);
			UpdateExpSetup();
		}
		SetEvent(ControlNotification);
#ifdef Staccato
// Bestätigung zurückschicken
			HWND hWndStaccato = ::FindWindow(NULL, _T("STACCATO"));
			if (hWndStaccato != NULL)
				::PostMessage(hWndStaccato, WM_BMEG0X_ACTIVATED, NULL, NULL);
#endif
	}
}

void CBME_G0XView::OnFileOptions() 
{
	CFileOptionsDlg dlg;
	dlg.m_CalibrationPath = FileOptions.CalibrationFilePath;
	if (dlg.DoModal() == IDOK)
	{
		FileOptions.CalibrationFilePath = dlg.m_CalibrationPath;
		WritePathDefinitionFile(PathDefinitionFileName, FileOptions);
		CopyFileOptions(p_G0xData->FileOptions, FileOptions);
	}
}

void CBME_G0XView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnUpdateFileOptions(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::DeactivateDelayGenerators()
{
	if (p_DelgenControl->b_ControlThreadActive)
	{
		ResetEvent(ExitNotification);
		p_DelgenControl->b_RequestRemoveControlThread = TRUE;
		SetEvent(ControlNotification);
		WaitForSingleObject(ExitNotification, 2000);
		UpdateExpSetup();
	}
}

void CBME_G0XView::OnConfigure() 
{
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		CString str;
		str = "   Delay generators are currently active,\n\n      deactivate them?";
		if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
			DeactivateDelayGenerators();
		else
			return;
	}
	CConfigurationTableDlg dlg(p_G0xData);
	if (dlg.DoModal() == IDOK)
	{
		p_G0xData->CopyDG_List(p_G0xData->m_DG_List, dlg.DG_List);
		p_G0xData->CopyDG_List(p_G0xData->m_Show_List, dlg.DG_List);
		p_G0xData->b_CalibrateTiming = dlg.m_CalibrateTiming;
		if (dlg.m_CalibrateOffset)
			p_G0xData->m_CalibrationLevel = CalibrateOffset;
		else
			p_G0xData->m_CalibrationLevel = CalibrateIncrement;
		p_G0xData->InitializeDelayGenerators();
		UpdateExpSetup();
	}
}

void CBME_G0XView::OnUpdateConfigure(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnDelay() 
{
	int ActiveIndex = max(0, min(p_G0xData->m_DG_List.GetCount(), p_G0xData->m_ActiveIndex));
	CString jstr = _T("Define Delay Parameters");
	if (p_G0xData->m_DG_List.GetCount() > 0)
	{
		if (!p_G0xData->b_DelayGeneratorsInitialized)
			p_G0xData->InitializeDelayGenerators();
	}
	if (p_DelgenParametersPS != NULL)
		delete p_DelgenParametersPS;
	p_DelgenParametersPS = new CDelgenParametersPS(p_G0xData, (LPCTSTR) jstr, this, ActiveIndex);
	//CDelgenParametersPS dlg(p_G0xData, (LPCTSTR) jstr, this, ActiveIndex);

	//dlg.m_psh.dwFlags &= ~PSH_HASHELP;
	p_DelgenParametersPS->m_psh.dwFlags &= ~PSH_HASHELP;
	if (p_DelgenParametersPS->DoModal() == IDOK)
	{
		p_G0xData->m_ActiveIndex = p_DelgenParametersPS->m_ActiveIndex;
//#ifndef WINDOWSNT
		UpdateExpSetup();
//#endif
	}
}

void CBME_G0XView::OnUpdateDelay(CCmdUI* pCmdUI)
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#else
	if (p_G0xData->m_DG_List.GetCount() > 0)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnTimeSequence() 
{
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		CString str;
		str = "   Delay generators are currently active,\n\n      deactivate them?";
		if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
			DeactivateDelayGenerators();
		else
			return;
	}
	CTimeSequenceDlg dlg(p_G0xData);
	dlg.DistributeVariables();
	if (dlg.DoModal() == IDOK)
	{
		dlg.CollectVariables();
		p_G0xData->ResetOutOfRangeVariables();
		UpdateExpSetup();
	}
}

void CBME_G0XView::OnUpdateTimeSequence(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnTimeList() 
{
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		CString str;
		str = "   Delay generators are currently active,\n\n      deactivate them?";
		if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
			DeactivateDelayGenerators();
		else
			return;
	}
	CTimeListDlg dlg(p_G0xData);
	dlg.DistributeVariables();
	if (dlg.DoModal() == IDOK)
	{
		dlg.CollectVariables();
		p_G0xData->ResetOutOfRangeVariables();
		UpdateExpSetup();
	}
}

void CBME_G0XView::OnUpdateTimeList(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#endif
}

void CBME_G0XView::OnActivate() 
{
	CheckControlThread();
}

void CBME_G0XView::OnUpdateActivate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(p_G0xData->b_DelayGeneratorsActive);
	pCmdUI->Enable((!p_G0xData->b_DelayGeneratorsActive) && (p_G0xData->m_DG_List.GetCount() > 0));
}

void CBME_G0XView::OnDeactivate() 
{
	DeactivateDelayGenerators();
}

void CBME_G0XView::OnUpdateDeactivate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_G0xData->b_DelayGeneratorsActive);
}

void CBME_G0XView::WriteToTextFile(CStdioFile& myFile, int value)
{
	CString kstr;
	kstr.Format(" %9d\n", value);
	myFile.WriteString( (LPCTSTR) kstr);
}

void CBME_G0XView::WritePathDefinitionFile(LPCTSTR FileName, FileOptionsType& FilOpt)
{

	CStdioFile myFile;
	CString CurrentFileName = LocalPath + "\\" + FileName;
	if( !myFile.Open((LPCTSTR) CurrentFileName, CFile::modeCreate
				 | CFile::modeWrite | CFile::typeText ) ) 
	{
		 #ifdef _DEBUG
				afxDump << "Unable to open file" << "\n";
		 #endif
		 exit( 1 );
	}
	FilOpt.nVersion = 1;
	WriteToTextFile(myFile, FilOpt.nVersion);
	myFile.WriteString( (LPCTSTR)FilOpt.CalibrationFilePath);
	myFile.Close();
}

void CBME_G0XView::ReadFromTextFile(CStdioFile& myFile, int& value)
{
	CListRout lr;
	CString kstr,jstr;
	myFile.ReadString(kstr);
	lr.NextCharacterGroup(kstr, jstr, 1);
	value = atoi(jstr);
}

void CBME_G0XView::ReadPathDefinitionFile(LPCTSTR FileName, FileOptionsType& FilOpt)
{

	CString CurrentFileName;
	CString CurrentFilePath;
	int Length;
	CStdioFile myFile;
	if( !myFile.Open((LPCTSTR) FileName,  CFile::modeRead 
				 | CFile::typeText ) ) 
	{
		 #ifdef _DEBUG
				afxDump << "Unable to open file" << "\n";
		 #endif
		 //exit( 1 );
		if( !myFile.Open(PathDefinitionFileName, CFile::modeCreate
					 | CFile::modeWrite | CFile::typeText ) ) 
		{
			 #ifdef _DEBUG
					afxDump << "Unable to open file" << "\n";
			 #endif
			 exit( 1 );
		}
		CurrentFileName = myFile.GetFileName();
		CurrentFilePath = myFile.GetFilePath();
		Length = CurrentFilePath.GetLength() - CurrentFileName.GetLength() - 1;
		LocalPath = CurrentFilePath.Left(Length);
		FilOpt.CalibrationFilePath = LocalPath;
		myFile.Close();
		WritePathDefinitionFile(PathDefinitionFileName, FilOpt);
	}
	else
	{
		CurrentFileName = myFile.GetFileName();
		CurrentFilePath = myFile.GetFilePath();
		Length = CurrentFilePath.GetLength() - CurrentFileName.GetLength() - 1;
		LocalPath = CurrentFilePath.Left(Length);
		ReadFromTextFile(myFile, FilOpt.nVersion);
		myFile.ReadString(FilOpt.CalibrationFilePath);
		myFile.Close();
	}
}

void CBME_G0XView::ResetFileOptions(FileOptionsType& FilOpt)
{
	FilOpt.nVersion = 1;
	FilOpt.CalibrationFilePath = _T("C:\\G0x\\Data");
	LocalPath = _T("");
	ReadPathDefinitionFile(PathDefinitionFileName, FilOpt);
}

void CBME_G0XView::CopyFileOptions(FileOptionsType& OptOut, FileOptionsType& OptIn)
{
	OptOut.nVersion = OptIn.nVersion;
	OptOut.CalibrationFilePath = OptIn.CalibrationFilePath;
}

void CBME_G0XView::OnSaveState() 
{
	CFileDialog fdg( FALSE, "g0y", CurrentFileName, (OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT),
														"Parameter Files (*.g0y)|*.g0y| All Files (*.*)|*.*||", this);
	fdg.m_ofn.lpstrInitialDir = (LPCTSTR)CurrentPath;
	if (fdg.DoModal() == IDOK)
	{
		CurrentFileName = fdg.GetFileName();
		CString FileName = fdg.GetPathName();
		CListRout lr;
		lr.TrimString(CurrentFileName);
		lr.TrimString(FileName);
		//lr.WriteFileComboBox(FileName, m_ActionTableCB); 
		p_G0xData->SaveParameters((LPCTSTR)FileName);
		int Length = FileName.GetLength() - CurrentFileName.GetLength() - 1;
		CurrentPath = FileName.Left(Length);
	}
}

void CBME_G0XView::OnUpdateSaveState(CCmdUI* pCmdUI) 
{
#ifdef G0x_ReadOnly
	pCmdUI->Enable(FALSE);
#else
	pCmdUI->Enable(p_G0xData->b_DelayGeneratorsActive);
#endif
}
