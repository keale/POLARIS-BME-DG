// BME_G0X.h : main header file for the BME_G0X application
//

#if !defined(AFX_BME_G0X_H__4F041DA7_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
#define AFX_BME_G0X_H__4F041DA7_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBME_G0XApp:
// See BME_G0X.cpp for the implementation of this class
//

class CBME_G0XApp : public CWinApp
{
public:
	CBME_G0XApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBME_G0XApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBME_G0XApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BME_G0X_H__4F041DA7_FD0B_11D4_8FD0_0050DADE1976__INCLUDED_)
