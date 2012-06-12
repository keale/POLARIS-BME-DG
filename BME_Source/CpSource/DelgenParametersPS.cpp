// DelgenParametersPS.cpp : implementation file
//

#include "stdafx.h"
#include "BME_G0X.h"
#include "DG_Data.h"
#include "G0xData.h"
#include "DelgenParametersPS.h"
#include "..\Spectra_BME\StandardDefinitions.h"
#include "..\Spectra_BME\ListRout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelgenParametersPS

IMPLEMENT_DYNAMIC(CDelgenParametersPS, CPropertySheet)

CDelgenParametersPS::CDelgenParametersPS(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDelgenParametersPS::CDelgenParametersPS(CG0xData* p_GDat, LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	CListRout lr;
	b_CounterThreadActive = FALSE;
	DataNotification = CreateEvent(NULL, TRUE, FALSE, NULL);
	b_DataModified = FALSE;
	b_ZeroCounterSynchronuously = TRUE;
	p_G0xData = p_GDat;
	p_ParentWindow = pParentWnd;
	CString Title,jstr;
	int cpos,len;
	NoPages = p_G0xData->m_DG_List.GetCount();
	DG_PageType PP;
	p_Page = new DG_PageType[max(2, NoPages)];
	int Count = 0;
	DG_Type* p_DG;
	POSITION pos = p_G0xData->m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = p_G0xData->m_DG_List.GetNext(pos);
		if (strlen(p_DG->DG_Name) > 0)
			Title = (CString)p_DG->DG_Name;
		else
		{
			switch (p_DG->Product)
			{
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_G03P1:
			case BME_G03P2:
			case BME_G05P1:
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
			case BME_SG08P1:
			case BME_SG08P2:
				Title.Format("slot %d", p_DG->BaseAddress);
				if (p_DG->ip_address[0] != 0)
				{
					jstr = lr.ReadMemo(p_DG->ip_address);
					cpos = 0;
					cpos = 1 + jstr.Find('.', cpos);
					cpos = 1 + jstr.Find('.', cpos);
					len = jstr.GetLength();
					Title += (", " + jstr.Right(len - cpos));
				}
				break;
			default:
				Title = "0x";
				jstr.Format("%2x", p_DG->BaseAddress);
				Title += jstr;
				break;
			}
			if (p_DG->Master)
				Title += ", master";
		}
		(p_Page + Count)->p_Title = new CString;
		*((p_Page + Count)->p_Title) = Title;
		if (p_DG->Master)
		{
			switch (p_DG->Product)
			{
			case BME_SG02P3:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G02p3MasterPP = new CG02p3MasterPP;
				PP.p_G02p3MasterPP->m_DG_Number = Count;
				PP.p_G02p3MasterPP->p_G0xData = p_G0xData;
				PP.p_G02p3MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G02p3MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G02p3MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G02p3MasterPP);
				PP.p_G02p3MasterPP->p_ParentWindow = this;
				PP.p_G02p3MasterPP->DataNotification = DataNotification;
				PP.p_G02p3MasterPP->p_DataModified = &b_DataModified;
				PP.p_G02p3MasterPP->DistributeVariables(p_DG);
				break;
			case BME_G02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_G02V1:
			case BME_G02V2:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G02MasterPP = new CG02MasterPP;
				PP.p_G02MasterPP->m_DG_Number = Count;
				PP.p_G02MasterPP->p_G0xData = p_G0xData;
				PP.p_G02MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G02MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G02MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G02MasterPP);
				PP.p_G02MasterPP->p_ParentWindow = this;
				PP.p_G02MasterPP->DataNotification = DataNotification;
				PP.p_G02MasterPP->p_DataModified = &b_DataModified;
				PP.p_G02MasterPP->DistributeVariables(p_DG);
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G03MasterPP = new CG03MasterPP;
				PP.p_G03MasterPP->m_DG_Number = Count;
				PP.p_G03MasterPP->p_G0xData = p_G0xData;
				PP.p_G03MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G03MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G03MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G03MasterPP);
				PP.p_G03MasterPP->p_ParentWindow = this;
				PP.p_G03MasterPP->DataNotification = DataNotification;
				PP.p_G03MasterPP->p_DataModified = &b_DataModified;
				PP.p_G03MasterPP->DistributeVariables(p_DG);
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G05MasterPP = new CG05MasterPP;
				PP.p_G05MasterPP->m_DG_Number = Count;
				PP.p_G05MasterPP->p_G0xData = p_G0xData;
				PP.p_G05MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05MasterPP);
				PP.p_G05MasterPP->p_ParentWindow = this;
				PP.p_G05MasterPP->DataNotification = DataNotification;
				PP.p_G05MasterPP->p_DataModified = &b_DataModified;
				PP.p_G05MasterPP->DistributeVariables(p_DG);
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G05p2MasterPP = new CG05p2MasterPP;
				PP.p_G05p2MasterPP->m_DG_Number = Count;
				PP.p_G05p2MasterPP->p_G0xData = p_G0xData;
				PP.p_G05p2MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05p2MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05p2MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05p2MasterPP);
				PP.p_G05p2MasterPP->p_ParentWindow = this;
				PP.p_G05p2MasterPP->DataNotification = DataNotification;
				PP.p_G05p2MasterPP->p_DataModified = &b_DataModified;
				PP.p_G05p2MasterPP->DistributeVariables(p_DG);
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				PP.p_G05p4MasterPP = new CG05p4MasterPP;
				PP.p_G05p4MasterPP->m_DG_Number = Count;
				PP.p_G05p4MasterPP->p_G0xData = p_G0xData;
				PP.p_G05p4MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05p4MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05p4MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05p4MasterPP);
				PP.p_G05p4MasterPP->p_ParentWindow = this;
				PP.p_G05p4MasterPP->DataNotification = DataNotification;
				PP.p_G05p4MasterPP->p_DataModified = &b_DataModified;
				PP.p_G05p4MasterPP->DistributeVariables(p_DG);
				break;
			}
		}
		else
		{
			switch (p_DG->Product)
			{
			case BME_G02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
			case BME_G02V1:
			case BME_G02V2:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G02SlavePP = new CG02SlavePP;
				PP.p_G02SlavePP->m_DG_Number = Count;
				PP.p_G02SlavePP->p_G0xData = p_G0xData;
				PP.p_G02SlavePP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G02SlavePP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G02SlavePP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G02SlavePP);
				PP.p_G02SlavePP->p_ParentWindow = this;
				PP.p_G02SlavePP->p_DataModified = &b_DataModified;
				PP.p_G02SlavePP->DistributeVariables(p_DG);
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G03SlavePP = new CG03SlavePP;
				PP.p_G03SlavePP->m_DG_Number = Count;
				PP.p_G03SlavePP->p_G0xData = p_G0xData;
				PP.p_G03SlavePP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G03SlavePP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G03SlavePP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G03SlavePP);
				PP.p_G03SlavePP->p_ParentWindow = this;
				PP.p_G03SlavePP->p_DataModified = &b_DataModified;
				PP.p_G03SlavePP->DistributeVariables(p_DG);
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G05SlavePP = new CG05SlavePP;
				PP.p_G05SlavePP->m_DG_Number = Count;
				PP.p_G05SlavePP->p_G0xData = p_G0xData;
				PP.p_G05SlavePP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05SlavePP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05SlavePP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05SlavePP);
				PP.p_G05SlavePP->p_ParentWindow = this;
				PP.p_G05SlavePP->p_DataModified = &b_DataModified;
				PP.p_G05SlavePP->DistributeVariables(p_DG);
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				b_ZeroCounterSynchronuously = FALSE;
				PP.p_G05p2MasterPP = new CG05p2MasterPP;
				PP.p_G05p2MasterPP->m_DG_Number = Count;
				PP.p_G05p2MasterPP->p_G0xData = p_G0xData;
				PP.p_G05p2MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05p2MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05p2MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05p2MasterPP);
				PP.p_G05p2MasterPP->p_ParentWindow = this;
				PP.p_G05p2MasterPP->DataNotification = DataNotification;
				PP.p_G05p2MasterPP->p_DataModified = &b_DataModified;
				PP.p_G05p2MasterPP->DistributeVariables(p_DG);
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				PP.p_G05p4MasterPP = new CG05p4MasterPP;
				PP.p_G05p4MasterPP->m_DG_Number = Count;
				PP.p_G05p4MasterPP->p_G0xData = p_G0xData;
				PP.p_G05p4MasterPP->m_psp.dwFlags &= ~PSP_HASHELP;
				PP.p_G05p4MasterPP->m_psp.dwFlags |= PSP_USETITLE;
				PP.p_G05p4MasterPP->m_psp.pszTitle = *((p_Page + Count)->p_Title);
				AddPage(PP.p_G05p4MasterPP);
				PP.p_G05p4MasterPP->p_ParentWindow = this;
				PP.p_G05p4MasterPP->DataNotification = DataNotification;
				PP.p_G05p4MasterPP->p_DataModified = &b_DataModified;
				PP.p_G05p4MasterPP->DistributeVariables(p_DG);
				break;
			}
		}
		(p_Page + Count)->p_PP = PP.p_PP;
		Count++;
	}
	p_font = new CFont;
	p_font->CreateFont(14,5,0,0,400,0,0,0,
				DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, 
				PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, "MS Sans Serif");

}

CDelgenParametersPS::~CDelgenParametersPS()
{
	delete p_font;
	int Count = 0;
	DG_Type* p_DG;
	POSITION pos = p_G0xData->m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = p_G0xData->m_DG_List.GetNext(pos);
		delete (p_Page + Count)->p_Title;
		switch (p_DG->Product)
		{
		case BME_SG02P3:
			if (p_DG->Master)
				delete (p_Page + Count)->p_G02p3MasterPP;
			else
				delete (p_Page + Count)->p_G02SlavePP;
			break;
		case BME_G02V3:
		case BME_SG02V4:
		case BME_SG02V5:
		case BME_SG02V6:
		case BME_SG02V7:
		case BME_SG02P1:
		case BME_SG02P2:
		case BME_SG02P4:
		case BME_SG02P5:
		case BME_G02V1:
		case BME_G02V2:
		case BME_SG02V1:
		case BME_SG02V2:
		case BME_SG02V3:
			if (p_DG->Master)
				delete (p_Page + Count)->p_G02MasterPP;
			else
				delete (p_Page + Count)->p_G02SlavePP;
			break;
		case BME_G03V1:
		case BME_G03V2:
		case BME_G03V3:
		case BME_G03V4:
		case BME_G03V5:
		case BME_G03P1:
		case BME_G03P2:
			if (p_DG->Master)
				delete (p_Page + Count)->p_G03MasterPP;
			else
				delete (p_Page + Count)->p_G03SlavePP;
			break;
		case BME_G05V1:
		case BME_G05V2:
		case BME_G05V3:
		case BME_G05P1:
			if (p_DG->Master)
				delete (p_Page + Count)->p_G05MasterPP;
			else
				delete (p_Page + Count)->p_G05SlavePP;
			break;
		case BME_G05P2:
		case BME_G05P3:
		case BME_SG05P1:
		case BME_SG05P2:
		case BME_SG05P3:
			delete (p_Page + Count)->p_G05p2MasterPP;
			break;
		case BME_SG08P1:
		case BME_SG08P2:
			delete (p_Page + Count)->p_G05p4MasterPP;
			break;
		}
		Count++;
	}
	delete p_Page;
}


BEGIN_MESSAGE_MAP(CDelgenParametersPS, CPropertySheet)
	ON_MESSAGE(WM_USER_REQUEST, OnChangeObjectProps)
	ON_MESSAGE(WM_FAST_APPLY_REQUEST, OnFastApply)
	//{{AFX_MSG_MAP(CDelgenParametersPS)
	ON_COMMAND(IDOK, OnOkNow)
	ON_COMMAND(IDCANCEL, OnCancelNow)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	ON_WM_HELPINFO()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelgenParametersPS message handlers


LRESULT CDelgenParametersPS::OnChangeObjectProps(WPARAM, LPARAM)
{
	ZeroSelectedCounter();
	return 0;
}

void CDelgenParametersPS::ZeroSelectedCounter()
{
	int Count = 0;
	BOOL b_RequestZeroModulo = FALSE;
	BOOL b_RequestJumpStart = FALSE;
	DG_Type* p_DG;
	POSITION pos = p_G0xData->m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = p_G0xData->m_DG_List.GetNext(pos);
		if (p_DG->Master)
		{
			switch (p_DG->Product)
			{
			case BME_SG02P3:
				if ((p_Page + Count)->p_G02p3MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G02p3MasterPP->b_RequestZeroCounter = FALSE;
				}
				break;
			case BME_G02V1:
			case BME_G02V2:
			case BME_G02V3:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P4:
			case BME_SG02P5:
				if ((p_Page + Count)->p_G02MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G02MasterPP->b_RequestZeroCounter = FALSE;
				}
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				if ((p_Page + Count)->p_G03MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G03MasterPP->b_RequestZeroCounter = FALSE;
				}
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				if ((p_Page + Count)->p_G05MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G05MasterPP->b_RequestZeroCounter = FALSE;
				}
				if ((p_Page + Count)->p_G05MasterPP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05MasterPP->b_RequestZeroModulo = FALSE;
				}
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				if ((p_Page + Count)->p_G05p2MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G05p2MasterPP->b_RequestZeroCounter = FALSE;
				}
				if ((p_Page + Count)->p_G05p2MasterPP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05p2MasterPP->b_RequestZeroModulo = FALSE;
				}
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G05p4MasterPP->b_RequestZeroCounter = FALSE;
				}
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05p4MasterPP->b_RequestZeroModulo = FALSE;
				}
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestJumpStart)
				{
					b_RequestJumpStart = TRUE;
					(p_Page + Count)->p_G05p4MasterPP->b_RequestJumpStart = FALSE;
				}
				break;
			}
		}
		else
		{
			switch (p_DG->Product)
			{
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				if ((p_Page + Count)->p_G05SlavePP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05SlavePP->b_RequestZeroModulo = FALSE;
				}
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				if ((p_Page + Count)->p_G05p2MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G05p2MasterPP->b_RequestZeroCounter = FALSE;
				}
				if ((p_Page + Count)->p_G05p2MasterPP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05p2MasterPP->b_RequestZeroModulo = FALSE;
				}
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestZeroCounter)
				{
					p_G0xData->ResetEventCounter(Count);
					(p_Page + Count)->p_G05p4MasterPP->b_RequestZeroCounter = FALSE;
				}
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestZeroModulo)
				{
					b_RequestZeroModulo = TRUE;
					(p_Page + Count)->p_G05p4MasterPP->b_RequestZeroModulo = FALSE;
				}
				if ((p_Page + Count)->p_G05p4MasterPP->b_RequestJumpStart)
				{
					b_RequestJumpStart = TRUE;
					(p_Page + Count)->p_G05p4MasterPP->b_RequestJumpStart = FALSE;
				}
				break;
			default:
				break;
			}
		}
		Count++;
	}
	if (b_RequestZeroModulo || b_RequestJumpStart)
	{
		if (p_G0xData->b_DelayGeneratorsActive)
		{
			if (!b_ZeroCounterSynchronuously)
			{
				p_G0xData->DeactivateDelayGenerators();
				p_G0xData->ResetCounterAllCards(FALSE, b_RequestZeroModulo, b_RequestJumpStart);
				p_G0xData->ActivateDelayGenerators();
			}
			else
				p_G0xData->LoadAllCardParameters(FALSE, b_RequestZeroModulo, b_RequestJumpStart);
		}
		else
			CollectVariables(b_RequestZeroModulo, b_RequestJumpStart);
	}
}


BOOL CDelgenParametersPS::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	if (pHelpInfo->dwContextId != 0)
	{
		AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
		return TRUE;
	}
	else
		return CPropertySheet::OnHelpInfo(pHelpInfo);
}

void CDelgenParametersPS::OnApplyNow()
{
	if (b_DataModified)
		CollectVariables(FALSE, FALSE);
	CheckCounterThread();
	SetEvent(DataNotification);
}

void CDelgenParametersPS::OnOkNow()
{
	b_RemoveCounterThread = TRUE;
	SetEvent(DataNotification);
	if (b_DataModified)
		CollectVariables(FALSE, FALSE);
	EndDialog(IDOK);
}

LRESULT CDelgenParametersPS::OnFastApply(WPARAM, LPARAM)
{
	if (b_DataModified)
		CollectVariables(FALSE, FALSE);
	return 0;
}

void CDelgenParametersPS::OnCancelNow()
{
	b_RemoveCounterThread = TRUE;
	SetEvent(DataNotification);
	EndDialog(IDCANCEL);
}

BOOL CDelgenParametersPS::CollectVariables(BOOL b_RequestZeroModulo, BOOL b_RequestJumpStart)
{
	CDG_DLL dll;
	int Count = 0;
	DG_Type* p_DG;
	try
	{
		POSITION pos = p_G0xData->m_DG_List.GetHeadPosition();
		while (pos != NULL)
		{
			p_DG = p_G0xData->m_DG_List.GetNext(pos);
			//dll.ResetControl(&(p_DG->Control));
			if (p_DG->Master)
			{
				switch (p_DG->Product)
				{
				case BME_SG02P3:
					(p_Page + Count)->p_G02p3MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G02p3MasterPP->SetModified(FALSE);
					break;
				case BME_G02V1:
				case BME_G02V2:
				case BME_G02V3:
				case BME_SG02V1:
				case BME_SG02V2:
				case BME_SG02V3:
				case BME_SG02V4:
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P4:
				case BME_SG02P5:
					(p_Page + Count)->p_G02MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G02MasterPP->SetModified(FALSE);
					break;
				case BME_G03V1:
				case BME_G03V2:
				case BME_G03V3:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
					(p_Page + Count)->p_G03MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G03MasterPP->SetModified(FALSE);
					break;
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
					(p_Page + Count)->p_G05MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05MasterPP->SetModified(FALSE);
					break;
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
					(p_Page + Count)->p_G05p2MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05p2MasterPP->SetModified(FALSE);
					break;
				case BME_SG08P1:
				case BME_SG08P2:
					(p_Page + Count)->p_G05p4MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05p4MasterPP->SetModified(FALSE);
					break;
				}
			}
			else
			{
				switch (p_DG->Product)
				{
				case BME_G02V1:
				case BME_G02V2:
				case BME_G02V3:
				case BME_SG02V1:
				case BME_SG02V2:
				case BME_SG02V3:
				case BME_SG02V4:
				case BME_SG02V5:
				case BME_SG02V6:
				case BME_SG02V7:
				case BME_SG02P1:
				case BME_SG02P2:
				case BME_SG02P3:
				case BME_SG02P4:
				case BME_SG02P5:
					(p_Page + Count)->p_G02SlavePP->CollectVariables(p_DG);
					(p_Page + Count)->p_G02SlavePP->SetModified(FALSE);
					break;
				case BME_G03V1:
				case BME_G03V2:
				case BME_G03V3:
				case BME_G03V4:
				case BME_G03V5:
				case BME_G03P1:
				case BME_G03P2:
					(p_Page + Count)->p_G03SlavePP->CollectVariables(p_DG);
					(p_Page + Count)->p_G03SlavePP->SetModified(FALSE);
					break;
				case BME_G05V1:
				case BME_G05V2:
				case BME_G05V3:
				case BME_G05P1:
					(p_Page + Count)->p_G05SlavePP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05SlavePP->SetModified(FALSE);
					break;
				case BME_G05P2:
				case BME_G05P3:
				case BME_SG05P1:
				case BME_SG05P2:
				case BME_SG05P3:
					(p_Page + Count)->p_G05p2MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05p2MasterPP->SetModified(FALSE);
					break;
				case BME_SG08P1:
				case BME_SG08P2:
					(p_Page + Count)->p_G05p4MasterPP->CollectVariables(p_DG);
					(p_Page + Count)->p_G05p4MasterPP->SetModified(FALSE);
					break;
				}
			}
			p_DG->Control.DG_Product = p_DG->Product;
			Count++;
		}
		m_ActiveIndex = GetActiveIndex();
		b_DataModified = FALSE;
		if (b_RequestZeroModulo)
			p_G0xData->b_RequestZeroModulo = TRUE;
		if (b_RequestJumpStart)
			p_G0xData->b_RequestJumpStart = TRUE;
		p_ParentWindow->SendMessage(WM_APPLY_REQUEST, 0, 0);
	}
	catch(CString& str)
	{
		AfxMessageBox(str, MB_OK, 0);
	}
	catch(...)
	{
		AfxMessageBox("unspecified error has occurred!! ", MB_OK, 0);
	}
	return TRUE;
}

void CDelgenParametersPS::LoadTriggerCounters()
{
	_int64 TestCount;
	double Frequency;
	DG_Type* p_DG;
	POSITION pos;
	int Count = 0;
	pos = p_G0xData->m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = p_G0xData->m_DG_List.GetNext(pos);
		if (p_DG->ReadTriggers)
		{
			switch (p_DG->Product)
			{
			case BME_SG02P3:
				if (p_DG->Master)
				{
					p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
					if (TestCount != 0xFFFFFFFF)
						TriggerCount = TestCount;
					(p_Page + Count)->p_G02p3MasterPP->NoEvents = (unsigned long)TriggerCount;
					if ((p_Page + Count)->p_G02p3MasterPP->b_PageActive)
						(p_Page + Count)->p_G02p3MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				}
				break;
			case BME_G02V1:
			case BME_G02V2:
			case BME_G02V3:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P4:
			case BME_SG02P5:
				if (p_DG->Master)
				{
					p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
					if (TestCount != 0xFFFFFFFF)
						TriggerCount = TestCount;
					(p_Page + Count)->p_G02MasterPP->NoEvents = (unsigned long)TriggerCount;
					if ((p_Page + Count)->p_G02MasterPP->b_PageActive)
						(p_Page + Count)->p_G02MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				}
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				if (p_DG->Master)
				{
					p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
					if (TestCount != 0xFFFFFFFF)
						TriggerCount = TestCount;
					(p_Page + Count)->p_G03MasterPP->NoEvents = (unsigned long)TriggerCount;
					if ((p_Page + Count)->p_G03MasterPP->b_PageActive)
						(p_Page + Count)->p_G03MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				}
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				if (p_DG->Master)
				{
					p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
					if (TestCount != 0xFFFFFFFF)
						TriggerCount = TestCount;
					(p_Page + Count)->p_G05MasterPP->NoEvents = (unsigned long)TriggerCount;
					if ((p_Page + Count)->p_G05MasterPP->b_PageActive)
						(p_Page + Count)->p_G05MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				}
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
				if (TestCount != 0xFFFFFFFF)
					TriggerCount = TestCount;
				(p_Page + Count)->p_G05p2MasterPP->NoEvents = (unsigned long)TriggerCount;
				if ((p_Page + Count)->p_G05p2MasterPP->b_PageActive)
					(p_Page + Count)->p_G05p2MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				p_G0xData->Read64BitTriggerCounter(&TestCount, Count);
				if (TestCount != 0xFFFFFFFF)
					TriggerCount = TestCount;
				(p_Page + Count)->p_G05p4MasterPP->NoEvents = TriggerCount;
				if ((p_Page + Count)->p_G05p4MasterPP->b_PageActive)
					(p_Page + Count)->p_G05p4MasterPP->SendMessage(WM_LOAD_COUNTER_REQUEST, 0, 0);
				//if (p_DG->Master)
				//{
					p_G0xData->ReadFrequencyCounter(&Frequency, Count);
					(p_Page + Count)->p_G05p4MasterPP->Frequency = Frequency;
					if ((p_Page + Count)->p_G05p4MasterPP->b_PageActive)
						(p_Page + Count)->p_G05p4MasterPP->SendMessage(WM_LOAD_FREQUENCY_REQUEST, 0, 0);
				//}
				break;
			}
		}
		Count++;
	}
}

void CDelgenParametersPS::MainLoop()
{
	TriggerCount = 0;
	do
	{
		WaitForSingleObject(DataNotification, 1000);
		ResetEvent(DataNotification);
		//if (FALSE)
		if (!b_RemoveCounterThread)
			LoadTriggerCounters();
	}
	while (!b_RemoveCounterThread);
	b_RemoveCounterThread = FALSE;
	b_CounterThreadActive = FALSE;
}


UINT StartReadEventCounters( LPVOID pParam )
{
 	CDelgenParametersPS* p_DelgenParametersPS = (CDelgenParametersPS*)pParam;
	p_DelgenParametersPS->MainLoop();
	return 0;
}

void CDelgenParametersPS::CheckCounterThread()
{
	//return;
	if (!b_CounterThreadActive)
	{
		b_CounterThreadActive = TRUE;
		b_RemoveCounterThread = FALSE;
		LPVOID pParam = this;
		AfxBeginThread(StartReadEventCounters, pParam, THREAD_PRIORITY_BELOW_NORMAL);
	}
}

void CDelgenParametersPS::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertySheet::OnShowWindow(bShow, nStatus);
	int Count = 0;
	DG_Type* p_DG;
	POSITION pos = p_G0xData->m_DG_List.GetHeadPosition();
	while (pos != NULL)
	{
		p_DG = p_G0xData->m_DG_List.GetNext(pos);
		if (p_DG->Master)
		{
			switch (p_DG->Product)
			{
			case BME_SG02P3:
				(p_Page + Count)->p_G02p3MasterPP->SetModified(TRUE);
				break;
			case BME_G02V1:
			case BME_G02V2:
			case BME_G02V3:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P4:
			case BME_SG02P5:
				(p_Page + Count)->p_G02MasterPP->SetModified(TRUE);
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				(p_Page + Count)->p_G03MasterPP->SetModified(TRUE);
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				(p_Page + Count)->p_G05MasterPP->SetModified(TRUE);
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				(p_Page + Count)->p_G05p2MasterPP->SetModified(TRUE);
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				(p_Page + Count)->p_G05p4MasterPP->SetModified(TRUE);
				break;
			}
		}
		else
		{
			switch (p_DG->Product)
			{
			case BME_G02V1:
			case BME_G02V2:
			case BME_G02V3:
			case BME_SG02V1:
			case BME_SG02V2:
			case BME_SG02V3:
			case BME_SG02V4:
			case BME_SG02V5:
			case BME_SG02V6:
			case BME_SG02V7:
			case BME_SG02P1:
			case BME_SG02P2:
			case BME_SG02P3:
			case BME_SG02P4:
			case BME_SG02P5:
				(p_Page + Count)->p_G02SlavePP->SetModified(TRUE);
				break;
			case BME_G03V1:
			case BME_G03V2:
			case BME_G03V3:
			case BME_G03V4:
			case BME_G03V5:
			case BME_G03P1:
			case BME_G03P2:
				(p_Page + Count)->p_G03SlavePP->SetModified(TRUE);
				break;
			case BME_G05V1:
			case BME_G05V2:
			case BME_G05V3:
			case BME_G05P1:
				(p_Page + Count)->p_G05SlavePP->SetModified(TRUE);
				break;
			case BME_G05P2:
			case BME_G05P3:
			case BME_SG05P1:
			case BME_SG05P2:
			case BME_SG05P3:
				(p_Page + Count)->p_G05p2MasterPP->SetModified(TRUE);
				break;
			case BME_SG08P1:
			case BME_SG08P2:
				(p_Page + Count)->p_G05p4MasterPP->SetModified(TRUE);
				break;
			}
		}
		Count++;
	}
	b_DataModified = TRUE;
	if (p_G0xData->b_DelayGeneratorsActive)
		CheckCounterThread();
}
