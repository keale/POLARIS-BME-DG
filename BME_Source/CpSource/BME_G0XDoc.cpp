// BME_G0XDoc.cpp : implementation of the CBME_G0XDoc class
//

#include "stdafx.h"
#include "BME_G0X.h"

#include "DG_Data.h"
#include "G0xData.h"
#include "BME_G0XDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XDoc

IMPLEMENT_DYNCREATE(CBME_G0XDoc, CDocument)

BEGIN_MESSAGE_MAP(CBME_G0XDoc, CDocument)
	//{{AFX_MSG_MAP(CBME_G0XDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XDoc construction/destruction

CBME_G0XDoc::CBME_G0XDoc()
{
	p_G0xData = new CG0xData(1);
	p_G0xData->ResetData();
}

CBME_G0XDoc::~CBME_G0XDoc()
{
	delete p_G0xData;
}

BOOL CBME_G0XDoc::OnNewDocument()
{
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		AfxMessageBox("a new file can not be created while delay generators are active!!",MB_OK,0);
		return FALSE;
	}
	else
	{
		if (!CDocument::OnNewDocument())
			return FALSE;
		p_G0xData->DeleteData();
		InitDocument();
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBME_G0XDoc serialization

void CBME_G0XDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << p_G0xData;
	}
	else
	{
		p_G0xData->DeleteData();
		ar >> p_G0xData;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XDoc diagnostics

#ifdef _DEBUG
void CBME_G0XDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBME_G0XDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XDoc commands

void CBME_G0XDoc::InitDocument()
{
	DeleteContents( );
	//SetModifiedFlag();
	UpdateAllViews( NULL );
	m_sizeDoc = CSize(600,500);
}

BOOL CBME_G0XDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (p_G0xData->b_DelayGeneratorsActive)
	{
		AfxMessageBox("a new file can not be created while delay generators are active!!",MB_OK,0);
		return FALSE;
	}
	else
	{
		if (!CDocument::OnOpenDocument(lpszPathName))
			return FALSE;
	}
	InitDocument();
	return TRUE;
}

void CBME_G0XDoc::ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::ReportSaveLoadException(lpszPathName, e, bSaving, nIDPDefault);
}
