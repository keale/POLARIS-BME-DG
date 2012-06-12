// BME_G0XView.h : interface of the CBME_G0XView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BME_G0XVIEW_H__4F041DAF_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
#define AFX_BME_G0XVIEW_H__4F041DAF_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DelgenControl.h"
#include "DelgenParametersPS.h"

#define PathDefinitionFileName  "BME_G0x.cpn"

#define WM_ACTIVATE_BMEG0X				WM_USER + 31
#define WM_BMEG0X_ACTIVATED				WM_USER + 32
#define WM_DEACTIVATE_BMEG0X			WM_USER + 33
#define WM_BMEG0X_DEACTIVATED			WM_USER + 34

//#define	Staccato


class CBME_G0XView : public CScrollView
{
protected: // create from serialization only
	CBME_G0XView();
	DECLARE_DYNCREATE(CBME_G0XView)

// Attributes
public:
	void CheckControlThread();
	void DeactivateDelayGenerators();
	CBME_G0XDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBME_G0XView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBME_G0XView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBME_G0XView)
	afx_msg void OnConfigure();
	afx_msg void OnUpdateConfigure(CCmdUI* pCmdUI);
	afx_msg void OnDelay();
	afx_msg void OnUpdateDelay(CCmdUI* pCmdUI);
	afx_msg void OnActivate();
	afx_msg void OnUpdateActivate(CCmdUI* pCmdUI);
	afx_msg void OnDeactivate();
	afx_msg void OnUpdateDeactivate(CCmdUI* pCmdUI);
	afx_msg void OnTimeSequence();
	afx_msg void OnTimeList();
	afx_msg void OnFileOptions();
	afx_msg void OnUpdateTimeSequence(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTimeList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnSaveState();
	afx_msg void OnUpdateSaveState(CCmdUI* pCmdUI);
	//}}AFX_MSG
  afx_msg LRESULT OnChangeObjectProps(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnWriteExpParm(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	FileOptionsType FileOptions;
	void WriteToTextFile(CStdioFile& myFile, int value);
	void ReadFromTextFile(CStdioFile& myFile, int& value);
	void ResetFileOptions(FileOptionsType& FilOpt);
	void CopyFileOptions(FileOptionsType& OptOut, FileOptionsType& OptIn);
	void WritePathDefinitionFile(LPCTSTR FileName, FileOptionsType& FileOptions);
	void ReadPathDefinitionFile(LPCTSTR FileName, FileOptionsType& FilOpt);
	void UpdateExpSetup();
	HANDLE	ControlNotification;
	HANDLE	ExitNotification;
	CDelgenControl* p_DelgenControl;
	CG0xData* p_G0xData;
	CClientDC* p_ClientDC;
	CRITICAL_SECTION DataAccess;
	CString LocalPath;
	CString CurrentFileName;
	CString CurrentPath;
	CDelgenParametersPS* p_DelgenParametersPS;
};

#ifndef _DEBUG  // debug version in BME_G0XView.cpp
inline CBME_G0XDoc* CBME_G0XView::GetDocument()
   { return (CBME_G0XDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BME_G0XVIEW_H__4F041DAF_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
