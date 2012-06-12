/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Command List Routines
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    5. January 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#include "StrRout.h"



class CListRout: public CStrRout
{
public:
  CListRout();
  ~CListRout();
	int ReadFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx);
	int WriteFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx);
	int ReadTxtFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx);
	int WriteTxtFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx);
	int WriteComboBox(CComboBox& output, CStringArray& input);
	int ReadComboBox(CStringArray& output, CComboBox& input);
	int CopyStringArray(CStringArray& output, CStringArray& input);
	int GetLineCount(CComboBox& cbx);
	int GetLineCount(CStringArray& csa);
	BOOL CheckXParameter(CComboBox& cbx);
	BOOL CheckXParameter(CStringArray& csa);
	BOOL CommandLineExist(CComboBox& cbx, LPCTSTR str, ...);
	BOOL CommandExist(CComboBox& cbx, BOOL exact, LPCTSTR str, ...);
	int XParameterInt(CString& input, CComboBox& cbx, int SubCycNum);
	int XParameterInt(CString& input, CStringArray& csa, int SubCycNum);
	double XParameterDouble(CString& input, CComboBox& cbx, int SubCycNum);
	double XParameterDouble(CString& input, CStringArray& csa, int SubCycNum);
	double XParameterDouble(CString& input, CStringArray& csa, int SubCycNum, BOOL& XCntrl);
	int NumerateLines(CStringArray& csa);
	int NumerateLines(CComboBox& cbx);
	int GetLinePosition(CComboBox& cbx, int LineNo);
	int GetLinePosition(CStringArray& csa, int LineNo);
	CString GetLine(CComboBox& cbx, int LineNo);
	CString GetLine(CStringArray& csa, int LineNo);
	int NumerateGroups(CComboBox& cbx);
	BOOL UnGrouped(CComboBox& cbx, int first, int last);
	BOOL FindFirstUnGrouped(CComboBox& cbx, int& first, int& last);
	BOOL FindFirstGrouped(CComboBox& cbx, int StartLine, int& first, int& last);
	BOOL FindFirstGrouped(CStringArray& csa, int StartLine, int& first, int& last);
	BOOL SetGroup(CComboBox& cbx, LPCTSTR name, int first, int last);
	BOOL RemoveGroup(CComboBox& cbx, int RemGroup);
	void RemoveEmptyGroups(CComboBox& cbx);
	CString ExtractParameter(CComboBox& cbx, int LineNo, int Position);
	CString ExtractParameter(CStringArray& csa, int LineNo, int Position);
	int ExtractParameterArray(double* p_Array, CStringArray& csa, int Width);
	int ExtractParameterArray(double* p_Array, CStringArray& csa, int Width, double* p_Xvec, int XLength);
	int ExtractParameterArray(double* p_Array, CStringArray& csa, int Width, int* p_Loc);
	int ExtractParameterVector(double* p_Vector, CStringArray& csa, int Position);
	BOOL InsertParameter(CStringArray& csa, CString& Param, int LineNo, int Position);
	BOOL RemoveParameter(CComboBox& cbx, int LineNo, int Position);
	int GetNumberParameters(CComboBox& cbx, int LineNo);
	int GetNumberParameters(CStringArray& csa);
	BOOL ReplaceLine(CStringArray& cbx, CString& CmdLine, int LineNo);
	BOOL ReplaceLine(CComboBox& cbx, CString& CmdLine, int LineNo);
	BOOL InsertLine(CComboBox& cbx, CString& CmdLine);
	BOOL InsertLine(CComboBox& cbx, CString& CmdLine, int LineNo, BOOL Before);
	BOOL DeleteSelectedLine(CComboBox& cbx);
	void CollapsTree(CTreeCtrl& TreeTC, HTREEITEM pItem);
};

