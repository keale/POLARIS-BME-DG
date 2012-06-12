// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "BME_G0XDoc.h"
#include "BME_G0XView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CRect r;
	GetWindowRect(r);
	//r.DeflateRect(0,0,0,250);
	r.bottom=r.top + (22 * (r.bottom - r.top) / 30);	
	r.right=r.left + (22 * (r.right - r.left) / 30);
	MoveWindow(r);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	//AfxMessageBox("OnSysCommand", MB_YESNO,0);
	if (nID != SC_CLOSE)
	{
		//if (nID != SC_MAXIMIZE)
			CWnd::OnSysCommand(nID, lParam);
	}
	else
	{
		CBME_G0XDoc* p_Doc =  (CBME_G0XDoc*)GetActiveDocument( );
		CG0xData* p_G0xData =  p_Doc->p_G0xData;
		CBME_G0XView* pView = (CBME_G0XView*)GetActiveView();
		if (p_G0xData->b_DelayGeneratorsActive)
		{
			CString str;
			str = "   Delay generators are currently active,\n\n      continue anyway?";
			if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
			{
				CString jstr;
				jstr = "Deactivate Delay generators?";
				if (AfxMessageBox(jstr, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
					pView->DeactivateDelayGenerators();
				CWnd::OnSysCommand(nID, lParam);
			}
		}
		else
		{
			if (AfxMessageBox("Are you sure\nyou want to exit?",
															(MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
				CWnd::OnSysCommand(nID, lParam);
		}
	}
}

void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	CFrameWnd::WinHelp(dwData, nCmd);
	CBME_G0XDoc* p_Doc =  (CBME_G0XDoc*)GetActiveDocument( );
	CG0xData* p_G0xData =  p_Doc->p_G0xData;
	p_G0xData->b_ContextHelpActive = FALSE;
}

void CMainFrame::OnContextHelp() 
{
	CBME_G0XDoc* p_Doc =  (CBME_G0XDoc*)GetActiveDocument( );
	CG0xData* p_G0xData =  p_Doc->p_G0xData;
	p_G0xData->b_ContextHelpActive = TRUE;
	CFrameWnd::OnContextHelp();
}

void CMainFrame::OnAppExit() 
{
	CBME_G0XDoc* p_Doc =  (CBME_G0XDoc*)GetActiveDocument( );
	CG0xData* p_G0xData =  p_Doc->p_G0xData;
	CBME_G0XView* pView = (CBME_G0XView*)GetActiveView();
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		CString str;
		str = "   Delay generators are currently active,\n\n      continue anyway?";
		if (AfxMessageBox(str, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
		{
			CString jstr;
			jstr = "Deactivate Delay generators?";
			if (AfxMessageBox(jstr, (MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
				pView->DeactivateDelayGenerators();
			CWnd::DestroyWindow();
		}
	}
	else
	{
		if (AfxMessageBox("Are you sure\nyou want to exit?",
															(MB_YESNO | MB_DEFBUTTON2),0) == IDYES)
			CWnd::DestroyWindow();
	}
}

void CMainFrame::OnFileOptions() 
{
	// TODO: Add your command handler code here
	
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
#ifdef Staccato
	if (message == WM_DEACTIVATE_BMEG0X)
	{
		((CBME_G0XView*) GetActiveView())->DeactivateDelayGenerators();
// Bestätigung zurückschicken
		HWND hWndStaccato = ::FindWindow(NULL, _T("STACCATO"));
		if (hWndStaccato != NULL)
			::PostMessage(hWndStaccato, WM_BMEG0X_DEACTIVATED, NULL, NULL);
	}	
	if (message == WM_ACTIVATE_BMEG0X)
	{
		((CBME_G0XView*) GetActiveView())->CheckControlThread();
	}	
#endif
	return CFrameWnd::WindowProc(message, wParam, lParam);
}
