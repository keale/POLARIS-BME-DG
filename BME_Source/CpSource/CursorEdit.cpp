// CursorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "CursorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCursorEdit

CCursorEdit::CCursorEdit()
{
}

CCursorEdit::~CCursorEdit()
{
}


BEGIN_MESSAGE_MAP(CCursorEdit, CEdit)
	//{{AFX_MSG_MAP(CCursorEdit)
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCursorEdit message handlers

void CCursorEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case 38:
		case 40:
		case 120:
		case 122:
			PresentCharacter = nChar;
			PresentCount = nRepCnt;
			p_ParentWindow->SendMessage(MessageNumber, 0, 0);
			break;
		default:
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
	}
}

void CCursorEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
