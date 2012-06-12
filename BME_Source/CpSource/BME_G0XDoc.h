// BME_G0XDoc.h : interface of the CBME_G0XDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BME_G0XDOC_H__4F041DAD_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
#define AFX_BME_G0XDOC_H__4F041DAD_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CBME_G0XDoc : public CDocument
{
protected: // create from serialization only
	void InitDocument();
	CBME_G0XDoc();
	DECLARE_DYNCREATE(CBME_G0XDoc)

// Attributes
public:
	CG0xData* p_G0xData;
protected:
	CSize m_sizeDoc;
public:
	CSize GetDocSize() { return m_sizeDoc; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBME_G0XDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBME_G0XDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBME_G0XDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BME_G0XDOC_H__4F041DAD_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
