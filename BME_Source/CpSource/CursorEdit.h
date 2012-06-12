#if !defined(AFX_CURSOREDIT_H__03039F54_40D1_11D6_BA77_185A05000000__INCLUDED_)
#define AFX_CURSOREDIT_H__03039F54_40D1_11D6_BA77_185A05000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CursorEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCursorEdit window

class CCursorEdit : public CEdit
{
// Construction
public:
	UINT PresentCharacter;
	UINT PresentCount;
	int	MessageNumber;
	CWnd* p_ParentWindow;
	CCursorEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCursorEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCursorEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCursorEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURSOREDIT_H__03039F54_40D1_11D6_BA77_185A05000000__INCLUDED_)
