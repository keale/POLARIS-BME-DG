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
    Update:                    17. March 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "CommonDefinitions.h"
#include "ListRout.h"

CListRout::CListRout()
{
}

CListRout::~CListRout()
{
}


int CListRout::ReadFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx)
{
	CFile myFile;
	CFileException fileException;

	if ( !myFile.Open( lpszFileName, CFile::modeRead , &fileException ))
	{
			TRACE( "Can't open file %s, error = %u\n",
    		lpszFileName, fileException.m_cause );
			return 0;
	}
	CString str;
	cbx.ResetContent();
	int Lines;
	myFile.Read(&Lines, 4);
	int i1;
	for (i1 = 0; i1 < Lines; i1++)
	{
		ReadStringBinary(myFile, str);
		cbx.AddString(str);
	}
	myFile.Close();
	return Lines;
}

int CListRout::ReadTxtFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx)
{
	CStdioFile myFile;
	CFileException fileException;

	if ( !myFile.Open( lpszFileName, CFile::modeRead , &fileException ))
	{
			TRACE( "Can't open file %s, error = %u\n",
    		lpszFileName, fileException.m_cause );
			return 0;
	}
	CString str,jstr;
	cbx.ResetContent();
	int Lines = 0;
	while (myFile.ReadString(str))
	{
		Lines++;
		jstr.Format(" %2d : %s", Lines, str);
		cbx.AddString(jstr);
	}
	myFile.Close();
	return Lines;
}


int CListRout::WriteFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx)
{
	CFile myFile;
	CFileException fileException;

	if ( !myFile.Open( lpszFileName, CFile::modeCreate |   
						CFile::modeWrite , &fileException ))
	{
			TRACE( "Can't open file %s, error = %u\n",
    		lpszFileName, fileException.m_cause );
			return 0;
	}
	CString str;
	int Lines = cbx.GetCount();
	myFile.Write(&Lines, 4);
	int i1;
	for (i1 = 0; i1 < Lines; i1++)
	{
		cbx.GetLBText( i1, str);
		WriteStringBinary(myFile, str);
	}
	myFile.Close();
	return Lines;
}

int CListRout::WriteTxtFileComboBox( LPCTSTR lpszFileName, CComboBox& cbx)
{
	CStdioFile myFile;
	CFileException fileException;

	if ( !myFile.Open( lpszFileName, CFile::modeCreate |   
						CFile::modeWrite , &fileException ))
	{
			TRACE( "Can't open file %s, error = %u\n",
    		lpszFileName, fileException.m_cause );
			return 0;
	}
	CString str;
	int Lines = cbx.GetCount();
	int i1,pos;
	for (i1 = 0; i1 < Lines; i1++)
	{
		cbx.GetLBText( i1, str);
		pos = str.Find(": ");
		if (pos >= 0)
			str = str.Right(str.GetLength() - pos - 2);
		str += "\n";
		myFile.WriteString(str);
	}
	myFile.Close();
	return Lines;
}

int CListRout::WriteComboBox(CComboBox& output, CStringArray& input)
{
	if (output.m_hWnd != NULL)
	{
		CString str;
		output.ResetContent();
		int Lines = input.GetSize();
		int i1;
		for (i1 = 0; i1 < Lines; i1++)
		{
			str = input.GetAt(i1);
			output.AddString(str);
		}
		return Lines;
	}
	return 0;
}

int CListRout::ReadComboBox(CStringArray& output, CComboBox& input)
{
	if (input.m_hWnd != NULL)
	{
		CString str;
		int Lines = input.GetCount();
		output.RemoveAll();
		if (output.GetSize() < Lines)
			output.SetSize(Lines,20);
		int i1;
		for (i1 = 0; i1 < Lines; i1++)
		{
			input.GetLBText( i1, str);
			output.SetAtGrow(i1,str);
		}
		return Lines;
	}
	return 0;
}


int CListRout::CopyStringArray(CStringArray& output, CStringArray& input)
{
	CString str;
	int Lines = input.GetSize();
	output.RemoveAll();
	if (output.GetSize() < Lines)
	{
		output.RemoveAll();
		output.SetSize(Lines,20);
	}
	int i1;
	for (i1 = 0; i1 < Lines; i1++)
	{
		str = input.GetAt(i1);
		output.SetAt(i1,str);
	}
	return Lines;
}

int CListRout::GetLineCount(CStringArray& csa)
{
	CString str;
	int count = csa.GetSize();
	int listlen = 0;
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		pos = str.Find(": ");
		if (pos >= 0)
			listlen++;
	}
	return listlen;
}

int CListRout::GetLineCount(CComboBox& cbx)
{
	CString str;
	int count = cbx.GetCount();
	int listlen = 0;
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, str);
		pos = str.Find(": ");
		if (pos >= 0)
			listlen++;
	}
	return listlen;
}

BOOL CListRout::CheckXParameter(CComboBox& cbx)
{
	CString str;
	int count = cbx.GetCount();
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, str);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			if (XParameterExist(str))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CListRout::CheckXParameter(CStringArray& csa)
{
	CString str;
	int count = csa.GetSize();
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			str.MakeUpper();
			if (XParameterExist(str))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CListRout::CommandLineExist(CComboBox& cbx, LPCTSTR str, ...)
{
	int count = cbx.GetCount();
	if (count == 0)
		return FALSE;
	va_list marker;
	va_start(marker, str);     /* Initialize variable arguments. */
	int pos,i1;
	CString jstr,kstr;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, kstr);
		pos = kstr.Find(": ");
		if (pos >= 0)
		{
			jstr = kstr.Right(kstr.GetLength() - pos - 2);
			if (CommandType(jstr, marker, str))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CListRout::CommandExist(CComboBox& cbx, BOOL exact, LPCTSTR str, ...)
{
	int count = cbx.GetCount();
	if (count == 0)
		return FALSE;
	va_list marker;
	CString input,tstr,jstr;
	int i1,npos,len1,pos;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, input);
		npos = input.Find(": ");
		while (npos >0)
		{
			npos = NextCharacterGroup(input, tstr, npos);
			tstr.MakeUpper();
			len1 = tstr.GetLength();
			va_start(marker, str);     /* Initialize variable arguments. */
			jstr = str;
			jstr.MakeUpper();
			while( jstr[0] != '?' )
			{
				pos = jstr.Find(tstr);
				if (pos == 0)
				{
					if ((!exact) || (len1 == jstr.GetLength()))
						return TRUE;
				}
				jstr = va_arg( marker, LPCTSTR);
				jstr.MakeUpper();
			}
			va_end( marker );              /* Reset variable arguments.      */
		}
	}
	return FALSE;
}

int CListRout::XParameterInt(CString& input, CComboBox& cbx, int SubCycNum)
{
	CString jstr,kstr;
	int LineNo = SubCycNum + 1;
	int result = 0;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			int Position = atoi(kstr);
			jstr = ExtractParameter(cbx, LineNo, Position);
			if (jstr.GetLength() == 0)
			{
				kstr.Format("no X-Parameter has been defined for X%d !!", Position); 
				throw kstr;
			}
		}
		sscanf( jstr, "%i", &result );
	}
	return result;
}

int CListRout::XParameterInt(CString& input, CStringArray& csa, int SubCycNum)
{
	CString jstr,kstr;
	int LineNo = SubCycNum + 1;
	int result = 0;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			int Position = atoi(kstr);
			jstr = ExtractParameter(csa, LineNo, Position);
			if (jstr.GetLength() == 0)
			{
				kstr.Format("no X-Parameter has been defined for X%d !!", Position); 
				throw kstr;
			}
		}
		sscanf( jstr, "%i", &result );
	}
	return result;
}

double CListRout::XParameterDouble(CString& input, CComboBox& cbx, int SubCycNum)
{
	CString jstr,kstr;
	int LineNo = SubCycNum + 1;
	double result = 0.0;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			int Position = atoi(kstr);
			jstr = ExtractParameter(cbx, LineNo, Position);
			if (jstr.GetLength() == 0)
			{
				kstr.Format("no X-Parameter has been defined for X%d !!", Position); 
				throw kstr;
			}
		}
		//sscanf( jstr, "%f", &result );
		result = atof(jstr);
	}
	return result;
}

double CListRout::XParameterDouble(CString& input, CStringArray& csa, int SubCycNum)
{
	CString jstr,kstr;
	int LineNo = SubCycNum + 1;
	double result = 0.0;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			int Position = atoi(kstr);
			jstr = ExtractParameter(csa, LineNo, Position);
			if (jstr.GetLength() == 0)
			{
				kstr.Format("no X-Parameter has been defined for X%d !!", Position); 
				throw kstr;
			}
		}
		//sscanf( jstr, "%f", &result );
		result = atof(jstr);
	}
	return result;
}

double CListRout::XParameterDouble(CString& input, CStringArray& csa, int SubCycNum, BOOL& XCntrl)
{
	CString jstr,kstr;
	int LineNo = SubCycNum + 1;
	double result = 0.0;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			int Position = atoi(kstr);
			jstr = ExtractParameter(csa, LineNo, Position);
			if (jstr.GetLength() == 0)
			{
				kstr.Format("no X-Parameter has been defined for X%d !!", Position); 
				throw kstr;
			}
			XCntrl = TRUE;
		}
		//sscanf( jstr, "%f", &result );
		result = atof(jstr);
	}
	return result;
}

int CListRout::NumerateLines(CStringArray& csa)
{
	CString str,jstr;
	int count = csa.GetSize();
	int listlen = 0;
	int newpos,pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			listlen++;
			newpos = atoi(str.Left(pos));
			if (newpos != listlen)
			{
				jstr.Format("%4d%s", listlen, (LPCTSTR)str.Right(str.GetLength() - pos));
				csa.SetAt(i1, jstr);
			}
		}
	}
	return listlen;
}

int CListRout::NumerateLines(CComboBox& cbx)
{
	CString str,jstr;
	int count = cbx.GetCount();
	int listlen = 0;
	int newpos,pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, str);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			listlen++;
			newpos = atoi(str.Left(pos));
			if (newpos != listlen)
			{
				jstr.Format("%4d%s", listlen, (LPCTSTR)str.Right(str.GetLength() - pos));
				cbx.DeleteString(i1);
				cbx.InsertString(i1,jstr);
			}
		}
	}
	return listlen;
}

int CListRout::GetLinePosition(CComboBox& cbx, int LineNo)
{
	CString str;
	int count = cbx.GetCount();
	int listlen = 0;
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, str);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			listlen++;
			if (listlen == LineNo)
				return i1;
		}
	}
	return -1;
}

int CListRout::GetLinePosition(CStringArray& csa, int LineNo)
{
	CString str;
	int count = csa.GetSize();
	int listlen = 0;
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		pos = str.Find(": ");
		if (pos >= 0)
		{
			listlen++;
			if (listlen == LineNo)
				return i1;
		}
	}
	return -1;
}

CString CListRout::GetLine(CComboBox& cbx, int LineNo)
{
	CString str,jstr;
	int count = cbx.GetCount();
	int pos,i1;
	int start = max(0, (LineNo - 1));
	while (start >= 0)
	{
		for (i1 = max(0, (LineNo - 1)); i1 < count; i1++)
		{
			cbx.GetLBText( i1, str);
			pos = str.Find(": ");
			if (pos >= 0)
			{
				jstr = str;
				jstr.Left(pos);
				if (atoi(jstr) == LineNo)
					return str.Right(str.GetLength() - pos - 2);
			}
		}
		start = (start > 0) ? 0 : -1;
	}
	return _T("");
}

CString CListRout::GetLine(CStringArray& csa, int LineNo)
{
	CString str,jstr;
	int count = csa.GetSize();
	int pos,i1;
	int start = max(0, (LineNo - 1));
	while (start >= 0)
	{
		for (i1 = start; i1 < count; i1++)
		{
			str = csa.GetAt(i1);
			pos = str.Find(": ");
			if (pos >= 0)
			{
				jstr = str;
				jstr.Left(pos);
				if (atoi(jstr) == LineNo)
					return str.Right(str.GetLength() - pos - 2);
			}
		}
		start = (start > 0) ? 0 : -1;
	}
	return _T("");
}

CString CListRout::ExtractParameter(CComboBox& cbx, int LineNo, int Position)
{
	CString str,jstr;
	int lpos = GetLinePosition(cbx, LineNo);
	if (lpos < 0)
		return _T("");
	cbx.GetLBText( lpos, str);
	int npos = str.Find(": ");
	if (npos < 0)
		return _T("");
	int i1 = 0;
	npos += 2;
	while ((i1 < Position) && (npos > 0))
	{
		npos = NextCharacterGroup(str, jstr, npos);
		i1++;
	}
	if (i1 < Position)
		return _T("");
	else
		return jstr;
}

CString CListRout::ExtractParameter(CStringArray& csa, int LineNo, int Position)
{
	CString str,jstr;
	int lpos = GetLinePosition(csa, LineNo);
	if (lpos < 0)
		return _T("");
	str = csa.GetAt(lpos);
	int npos = str.Find(": ");
	if (npos < 0)
		return _T("");
	int i1 = 0;
	npos += 2;
	while ((i1 < Position) && (npos > 0))
	{
		npos = NextCharacterGroup(str, jstr, npos);
		i1++;
	}
	if (i1 < Position)
		return _T("");
	else
		return jstr;
}

int CListRout::ExtractParameterVector(double* p_Vector, CStringArray& csa, int Position)
{
	CString str,jstr;
	int count = csa.GetSize();
	int listlen = 0;
	int npos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		npos = str.Find(": ");
		if (npos >= 0)
		{
			npos +=2;
			int i1 = 0;
			while ((i1 <= Position) && (npos > 0))
			{
				npos = NextCharacterGroup(str, jstr, npos);
				i1++;
			}
			*(p_Vector + listlen) = atof(jstr);
			listlen++;
		}
	}
	return listlen;
}

int CListRout::ExtractParameterArray(double* p_Array, CStringArray& csa, int Width)
{
	CString str,jstr;
	int count = csa.GetSize();
	int npos,k1,i1;
	int ipos = 0;
	for (k1 = 0; k1 < count; k1++)
	{
		i1 = 0;
		str = csa.GetAt(k1);
		npos = str.Find(": ");
		if (npos >= 0)
		{
			npos +=2;
			while ((i1 < Width) && (npos > 0))
			{
				npos = NextCharacterGroup(str, jstr, npos);
				*(p_Array + ipos + i1) = atof(jstr);
				i1++;
			}
		}
		while (i1 < Width)
		{
			*(p_Array + ipos + i1) = 0.0;
			i1++;
		}
		ipos += Width;
	}
	return (Width * count);
}

int CListRout::ExtractParameterArray(double* p_Array, CStringArray& csa, int Width, double* p_Xvec, int XLength)
{
	CString str,jstr,kstr;
	int count = csa.GetSize();
	int npos,ivar,k1,i1;
	int ipos = 0;
	TCHAR tch;
	for (k1 = 0; k1 < count; k1++)
	{
		i1 = 0;
		str = csa.GetAt(k1);
		npos = str.Find(": ");
		if (npos >= 0)
		{
			npos +=2;
			while ((i1 < Width) && (npos > 0))
			{
				npos = NextCharacterGroup(str, jstr, npos);
				tch = jstr[0];
				switch (tch)
				{
				case 'x':
				case 'X':
					kstr = jstr.Right(jstr.GetLength() - 1);
					ivar = (RoundInt(atof(kstr)) - 1);
					ivar = max(0, ivar);
					if (ivar >= XLength)
					{
						CString tstr = "variable " + jstr + " has not been defined!!";
						throw tstr;
					}
					*(p_Array + ipos + i1) = *(p_Xvec + ivar);
					break;
				default:
					*(p_Array + ipos + i1) = atof(jstr);
					break;
				}
				i1++;
			}
		}
		while (i1 < Width)
		{
			*(p_Array + ipos + i1) = 0.0;
			i1++;
		}
		ipos += Width;
	}
	return (Width * count);
}

int CListRout::ExtractParameterArray(double* p_Array, CStringArray& csa, int Width, int* p_Loc)
{
	CString str,jstr,kstr;
	int count = csa.GetSize();
	int npos,ivar,k1,i1;
	int ipos = 0;
	TCHAR tch;
	for (k1 = 0; k1 < count; k1++)
	{
		i1 = 0;
		str = csa.GetAt(k1);
		npos = str.Find(": ");
		if (npos >= 0)
		{
			npos +=2;
			while ((i1 < Width) && (npos > 0))
			{
				npos = NextCharacterGroup(str, jstr, npos);
				tch = jstr[0];
				switch (tch)
				{
				case 'x':
				case 'X':
					kstr = jstr.Right(jstr.GetLength() - 1);
					ivar = (RoundInt(atof(kstr)) - 1);
					ivar = max(0, ivar);
					*(p_Loc + ipos + i1) = ivar;
					*(p_Array + ipos + i1) = 0.0;
					break;
				default:
					*(p_Array + ipos + i1) = atof(jstr);
					*(p_Loc + ipos + i1) = -1;
					break;
				}
				i1++;
			}
		}
		while (i1 < Width)
		{
			*(p_Array + ipos + i1) = 0.0;
			i1++;
		}
		ipos += Width;
	}
	return (Width * count);
}

BOOL CListRout::InsertParameter(CStringArray& csa, CString& Param, int LineNo, int Position)
{
	CString str,jstr;
	//int lpos = GetLinePosition(cbx, LineNo);
	//if (lpos < 0)
		//return FALSE;
	int lpos = LineNo - 1;
	str = csa.GetAt(lpos);
	int cpos = str.Find(": ");
	if (cpos < 0)
		return FALSE;
	cpos++;
	int i1 = 0;
	int npos =cpos;
	while ((i1 < Position) && (npos > 0))
	{
		cpos = npos;
		npos = NextCharacterGroup(str, jstr, cpos);
		i1++;
	}
	if (i1 < Position)
		return FALSE;
	BOOL AddBlank = FALSE;
	if (Param[0] != ' ')
		AddBlank = TRUE;
	if (npos > 0)
	{
		npos = cpos + jstr.GetLength() - 1;
		if (AddBlank)
			jstr = str.Left(npos) + " " + Param + str.Right(str.GetLength() - npos);
		else
			jstr = str.Left(npos) + Param + str.Right(str.GetLength() - npos);
	}
	else
	{
		if (AddBlank)
			jstr = str + " " + Param;
		else
			jstr = str + Param;
	}
	csa.SetAt(lpos, jstr);
	return TRUE;
}

BOOL CListRout::RemoveParameter(CComboBox& cbx, int LineNo, int Position)
{
	CString str,jstr;
	int lpos = GetLinePosition(cbx, LineNo);
	if (lpos < 0)
		return FALSE;
	cbx.GetLBText( lpos, str);
	int cpos = str.Find(": ");
	if (cpos < 0)
		return FALSE;
	cpos++;
	int i1 = 0;
	int npos =cpos;
	while ((i1 <= Position) && (npos > 0))
	{
		cpos = npos;
		npos = NextCharacterGroup(str, jstr, cpos);
		i1++;
	}
	if (i1 <= Position)
		return FALSE;
	jstr = str.Left(cpos - 1);
	if (npos > 0)
		jstr += str.Right(str.GetLength() - npos + 1);
	TrimString(jstr);
	cbx.DeleteString(lpos);
	cbx.InsertString(lpos, jstr);
	return TRUE;
}

int CListRout::GetNumberParameters(CComboBox& cbx, int LineNo)
{
	CString str,jstr;
	int lpos = GetLinePosition(cbx, LineNo);
	if (lpos < 0)
		return FALSE;
	cbx.GetLBText( lpos, str);
	int cpos = str.Find(": ");
	if (cpos < 0)
		return 0;
	cpos++;
	int i1 = 0;
	while (cpos > 0)
	{
		cpos = NextCharacterGroup(str, jstr, cpos);
		if (cpos > 0)
			i1++;
	}
	return i1;
}

int CListRout::GetNumberParameters(CStringArray& csa)
{
	CString str,jstr;
	int NumberParameters = 1000000;
	BOOL found = FALSE;
	int count = csa.GetSize();
	int npos,i1;
	int parcount;
	for (i1 = 0; i1 < count; i1++)
	{
		str = csa.GetAt(i1);
		npos = str.Find(": ");
		if (npos >= 0)
		{
			found = TRUE;
			parcount = 0;
			npos += 2;
			while (npos > 0)
			{
				npos = NextCharacterGroup(str, jstr, npos);
				if (jstr.GetLength() > 0)
					parcount++;
			}
			NumberParameters = min(NumberParameters, parcount);
		}
	}
	if (found)
		return NumberParameters;
	else
		return 0;
}


BOOL CListRout::ReplaceLine(CStringArray& cbx, CString& CmdLine, int LineNo)
{
	if (CmdLine.GetLength() == 0)
		return FALSE;
	CString str,jstr;
	int lpos = GetLinePosition(cbx, LineNo);
	if (lpos < 0)
		return FALSE;
	str = cbx[lpos];
	int cpos = str.Find(": ");
	if (cpos < 0)
		return FALSE;
	jstr.Format("%s: %s", (LPCTSTR)str.Left(cpos), (LPCTSTR)CmdLine);
	cbx[lpos] = jstr;
	return TRUE;
}

BOOL CListRout::ReplaceLine(CComboBox& cbx, CString& CmdLine, int LineNo)
{
	if (CmdLine.GetLength() == 0)
		return FALSE;
	CString str,jstr;
	int lpos = GetLinePosition(cbx, LineNo);
	if (lpos < 0)
		return FALSE;
	cbx.GetLBText( lpos, str);
	int cpos = str.Find(": ");
	if (cpos < 0)
		return FALSE;
	jstr.Format("%s: %s", (LPCTSTR)str.Left(cpos), (LPCTSTR)CmdLine);
	cbx.DeleteString(lpos);
	cbx.InsertString(lpos,jstr);
	return TRUE;
}

BOOL CListRout::InsertLine(CComboBox& cbx, CString& CmdLine, int LineNo, BOOL Before)
{
	if (CmdLine.GetLength() == 0)
		return FALSE;
	CString jstr;
	int lpos = -1;
	if (LineNo > 0)
	{
		lpos = GetLinePosition(cbx, LineNo);
		if (lpos < 0)
			return FALSE;
	}
	jstr.Format("   2: %s", (LPCTSTR)CmdLine);
	if (Before)
		cbx.InsertString(lpos,jstr);
	else
		cbx.InsertString(lpos + 1,jstr);
	NumerateLines(cbx);
	return TRUE;
}

BOOL CListRout::InsertLine(CComboBox& cbx, CString& CmdLine)
{
	if (CmdLine.GetLength() == 0)
		return FALSE;
	CString jstr;
	jstr.Format("   2: %s", (LPCTSTR)CmdLine);
	cbx.AddString(jstr);
	NumerateLines(cbx);
	return TRUE;
}

void CListRout::RemoveEmptyGroups(CComboBox& cbx)
{
	CString jstr,kstr;
	int count = cbx.GetCount();
	int pos;
	BOOL StartGroup = FALSE;
	int i1 = 0;
	while (i1 < count)
	{
		cbx.GetLBText( i1, jstr);
		if (StartGroup)
		{
			pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
			if ((pos > 0) && (kstr.GetLength() > 0))
			{
				cbx.DeleteString(i1--);
				cbx.DeleteString(i1--);
				count -= 2;
			}
			StartGroup = FALSE;
		}
		else
		{
			pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
			if ((pos > 0) && (kstr.GetLength() > 0))
				StartGroup = TRUE;
			else
				StartGroup = FALSE;
		}
		i1++;
	}
}

int CListRout::NumerateGroups(CComboBox& cbx)
{
	CString jstr,kstr,lstr;
	int count = cbx.GetCount();
	int GroupNo = 0;
	int pos;
	int i1 = 0;
	while (i1 < count)
	{
		cbx.GetLBText( i1, jstr);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			GroupNo++;
			pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "no", "?");
			lstr.Format("%s No. %2d {", (LPCTSTR)jstr.Left(pos-1), GroupNo);
			cbx.DeleteString(i1);
			cbx.InsertString(i1,lstr);
		}
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "no", "?");
			lstr.Format("%s No. %2d", (LPCTSTR)jstr.Left(pos-1), GroupNo);
			cbx.DeleteString(i1);
			cbx.InsertString(i1,lstr);
		}
		i1++;
	}
	return GroupNo;
}

BOOL CListRout::RemoveGroup(CComboBox& cbx, int RemGroup)
{
	CString jstr,kstr,lstr;
	int count = cbx.GetCount();
	int pos;
	int GroupNo = 0;
	BOOL result = FALSE;
	int i1 = 0;
	while (i1 < count)
	{
		cbx.GetLBText( i1, jstr);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			GroupNo++;
			if (GroupNo == RemGroup)
			{
				cbx.DeleteString(i1--);
				count--;
			}
		}
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			if (GroupNo == RemGroup)
			{
				cbx.DeleteString(i1--);
				count--;
				result = TRUE;
			}
		}
		i1++;
	}
	NumerateGroups(cbx);
	return result;
}

BOOL CListRout::UnGrouped(CComboBox& cbx, int first, int last)
{
	CString jstr,kstr;
	BOOL GroupRange = FALSE;
	int listpos = 0;
	int count = cbx.GetCount();
	int pos,i1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, jstr);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
			GroupRange = TRUE;
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
			GroupRange = FALSE;
		pos = jstr.Find(": ");
		if (pos >= 0)
		{
			listpos++;
			if (GroupRange)
			{
				if ((first <= listpos) && (listpos <= last))
					return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CListRout::FindFirstUnGrouped(CComboBox& cbx, int& first, int& last)
{
	CString jstr,kstr;
	BOOL GroupRange = FALSE;
	int listpos = 0;
	int count = cbx.GetCount();
	int pos,i1;
	int start = -1;
	int stop = -1;
	for (i1 = 0; i1 < count; i1++)
	{
		cbx.GetLBText( i1, jstr);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			GroupRange = TRUE;
			if (start != -1)
			{
				first = start;
				last = stop;
				return TRUE;
			}
		}
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
			GroupRange = FALSE;
		pos = jstr.Find(": ");
		if (pos >= 0)
		{
			listpos++;
			if (!GroupRange)
			{
				if (start == -1)
					start = atoi(jstr);
				if (start != -1)
					stop = atoi(jstr);
			}
		}
	}
	if (start != -1)
	{
		first = start;
		last = stop;
		return TRUE;
	}
	return FALSE;
}

BOOL CListRout::FindFirstGrouped(CComboBox& cbx, int StartLine, int& first, int& last)
{
	CString jstr,kstr;
	int pos,i1;
	BOOL found = FALSE;
	int start = GetLinePosition(cbx, StartLine);
	int count = cbx.GetCount();
	for (i1 = start; i1 < count; i1++)
	{
		cbx.GetLBText( i1, jstr);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			cbx.GetLBText( (i1+1), kstr);
			pos = kstr.Find(": ");
			kstr.Left(pos);
			first = atoi(kstr);
			found = TRUE;
		}
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			cbx.GetLBText( (i1-1), kstr);
			pos = kstr.Find(": ");
			kstr.Left(pos);
			last = atoi(kstr);
			return found;
		}
	}
	return FALSE;
}

BOOL CListRout::FindFirstGrouped(CStringArray& csa, int StartLine, int& first, int& last)
{
	CString jstr,kstr;
	int pos,i1;
	BOOL found = FALSE;
	int start = max(0, (GetLinePosition(csa, StartLine) - 1));
	int count = csa.GetSize();
	for (i1 = start; i1 < count; i1++)
	{
		jstr = csa.GetAt(i1);
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "begin", "{", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			kstr = csa.GetAt(i1 + 1);
			pos = kstr.Find(": ");
			kstr.Left(pos);
			first = atoi(kstr);
			found = TRUE;
		}
		pos = NextCommandPosition(jstr, kstr, 1, TRUE, "}", "end", "?");
		if ((pos > 0) && (kstr.GetLength() > 0))
		{
			kstr = csa.GetAt(i1 - 1);
			pos = kstr.Find(": ");
			kstr.Left(pos);
			last = atoi(kstr);
			return found;
		}
	}
	return FALSE;
}

BOOL CListRout::SetGroup(CComboBox& cbx, LPCTSTR name, int first, int last)
{
	CString jstr;
	int count = cbx.GetCount();
	int i1 = 0;
	if (UnGrouped(cbx,first, last))
	{
		int pos = GetLinePosition(cbx, first);
		jstr.Format(" Begin %s No. 1 {", (LPCTSTR)name);
		cbx.InsertString(pos,jstr);
		pos = GetLinePosition(cbx, last);
		jstr.Format(" } End %s No. 1", (LPCTSTR)name);
		cbx.InsertString(pos+1,jstr);
		NumerateGroups(cbx);
		return TRUE;
	}
	return FALSE;
}

BOOL CListRout::DeleteSelectedLine(CComboBox& cbx)
{
	CString str;
	int LinePos = cbx.GetCurSel();
	if (LinePos != CB_ERR)
	{
		cbx.GetLBText( LinePos, str);
		int pos = str.Find(": ");
		if (pos >= 0)
		{
			cbx.DeleteString(LinePos);
			RemoveEmptyGroups(cbx);
			NumerateLines(cbx);
			NumerateGroups(cbx);
			return TRUE;
		}
	}
	return FALSE;
}

void CListRout::CollapsTree(CTreeCtrl& TreeTC, HTREEITEM pItem)
{
	HTREEITEM pChild = TreeTC.GetChildItem(pItem);
	HTREEITEM pGrandChild;
	HTREEITEM pGrandGrandChild;
	HTREEITEM pGrandGrandGrandChild;
	HTREEITEM pGrandGrandGrandGrandChild;
	while (pChild != NULL)
	{
		pGrandChild = TreeTC.GetChildItem(pChild);
		while (pGrandChild != NULL)
		{
			pGrandGrandChild = TreeTC.GetChildItem(pGrandChild);
			while (pGrandGrandChild != NULL)
			{
				pGrandGrandGrandChild = TreeTC.GetChildItem(pGrandGrandChild);
				while (pGrandGrandGrandChild != NULL)
				{
					pGrandGrandGrandGrandChild = TreeTC.GetChildItem(pGrandGrandGrandChild);
					while (pGrandGrandGrandGrandChild != NULL)
					{
						TreeTC.Expand(pGrandGrandGrandGrandChild, TVE_COLLAPSE);
						pGrandGrandGrandGrandChild = TreeTC.GetNextSiblingItem(pGrandGrandGrandGrandChild);
					}
					TreeTC.Expand(pGrandGrandGrandChild, TVE_COLLAPSE);
					pGrandGrandGrandChild = TreeTC.GetNextSiblingItem(pGrandGrandGrandChild);
				}
				TreeTC.Expand(pGrandGrandChild, TVE_COLLAPSE);
				pGrandGrandChild = TreeTC.GetNextSiblingItem(pGrandGrandChild);
			}
			TreeTC.Expand(pGrandChild, TVE_COLLAPSE);
			pGrandChild = TreeTC.GetNextSiblingItem(pGrandChild);
		}
		TreeTC.Expand(pChild, TVE_COLLAPSE);
		pChild = TreeTC.GetNextSiblingItem(pChild);
	}
}
