/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 String Routines
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

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "StandardDefinitions.h"
#include "StrRout.h"
#include <math.h>

#define MaxNoEvaluations  10

CStrRout::CStrRout()
{
}

CStrRout::~CStrRout()
{
}

CString CStrRout::WriteBinaryString(unsigned long input)
{
	unsigned long test = 0x80000000;
	CString result = _T("");
	int i1,j1,k1;
	for (i1 = 0; i1 < 4; i1++)
	{
		for (j1 = 0; j1 < 2; j1++)
		{
			for (k1 = 0; k1 < 4; k1++)
			{
				if ((input & test) == 0)
					result += "0";
				else
					result += "1";
				test >>= 1;
			}
			result += " ";
		}
		result += " ";
	}
	return result;
}

CString CStrRout::WriteBinaryString(unsigned long* p_input, int Length)
{
	unsigned long test = 0x1;
	CString result = _T("");
	int Count = 0;
	int IntCount = 0;
	int i1,j1,k1;
	while (Count < Length)
	{
		for (i1 = 0; i1 < 4; i1++)
		{
			for (j1 = 0; j1 < 2; j1++)
			{
				for (k1 = 0; k1 < 4; k1++)
				{
					if ((*(p_input + IntCount) & test) == 0)
						result += "0";
					else
						result += "1";
					test <<= 1;
					Count++;
					if (Count >= Length)
					{
						result.MakeReverse();
						TrimString(result);
						return result;
					}
				}
				result += " ";
			}
			result += " ";
		}
		result += " ";
		IntCount++;
		test = 0x1;
	}
	result.MakeReverse();
	TrimString(result);
	return result;
}

int CStrRout::ReadBinaryString(unsigned long* p_output, LPCTSTR instr, int MaxLength)
{
	CString input = instr;
	unsigned long test = 0x1;
	int Count = 0;
	int IntCount = 0;
	int Length = input.GetLength();
	int i1;
	TCHAR ch;
	for (i1 = (Length - 1); i1 >= 0; i1--)
	{
		ch = input[i1];
		if ((ch == '1') || (ch == '0'))
		{
			if (ch == '1')
				*(p_output + IntCount) |= test;
			else
				*(p_output + IntCount) &= ~test;
			test <<= 1;
			Count++;
			if (Count >= MaxLength)
				return Count;
			if ((Count % 32) == 0)
			{
				IntCount++;
				test = 0x1;
			}
		}
	}
	return Count;
}

unsigned long CStrRout::ReadBinaryString(LPCTSTR instr)
{
	CString input = instr;
	unsigned long test = 0x1;
	unsigned long result = 0;
	int Length = input.GetLength();
	int i1;
	TCHAR ch;
	for (i1 = (Length - 1); i1 >= 0; i1--)
	{
		ch = input[i1];
		if ((ch == '1') || (ch == '0'))
		{
			if (ch == '1')
				result |= test;
			test <<= 1;
		}
	}
	return result;
}

unsigned long CStrRout::ReadHexadecimalString(LPCTSTR instr)
{
	CString input = instr;
	unsigned long test = 0x1;
	unsigned long result = 0;
	BOOL EndPoint = FALSE;
	int Count = 0;
	int Length = input.GetLength();
	int i1;
	TCHAR ch;
	i1 = (Length - 1);
	while ((i1 >= 0) && (Count < 8) && (!EndPoint))
	{
		ch = input[i1];
		if ((48 <= ch) && (ch <= 57))
		{
			result += ((ch - 48) * test);
			test <<= 4;
			Count++;
		}
		if ((65 <= ch) && (ch <= 70))
		{
			result += ((ch - 55) * test);
			test <<= 4;
			Count++;
		}
		if ((97 <= ch) && (ch <= 102))
		{
			result += ((ch - 87) * test);
			test <<= 4;
			Count++;
		}
		if ((ch == 88) || (ch == 120))
			EndPoint = TRUE;
		i1--;
	}
	return result;
}

int CStrRout::CharPos(LPCTSTR input, int start)
{
	CString str = input;
	BOOL found = FALSE;
	TCHAR c1;
	int i1 = max(1, start);
	while ((!found) && (i1 <= str.GetLength()))
	{
		c1 = str.GetAt(i1 - 1);
		if ((c1 > 32) && (c1 < 127))
			found = TRUE;
		else
			i1++;
	}
	if (!found)
		i1 = 0;
	return i1;
}

int CStrRout::CharPrevious(LPCTSTR input, int start)
{
	CString str = input;
	BOOL found = FALSE;
	TCHAR c1;
	int i1 = min(str.GetLength(), start);
	while ((!found) && (i1 >= 1))
	{
		c1 = str.GetAt(i1-1);
		if ((c1 > 32) && (c1 < 127))
			found = TRUE;
		else
			i1--;
	}
	if (!found)
		i1 = 0;
	return i1;
}

BOOL CStrRout::CompareChar(TCHAR ci, TCHAR cr, ...)
{
	BOOL match = FALSE;
	TCHAR ct = 0;
  TCHAR ci1 = ci;
	if ((ci1 >= 97) && (ci1 <= 122))
		ci1 -= 32;
  va_list marker;
	va_start(marker, cr);     /* Initialize variable arguments. */
	ct = cr;
  while (( ct != -1 ) && (!match))
  {
		if (ct != -1)
		{
			if ((ct >= 97) && (ct <= 122))
				ct -= 32;
			if (ct == ci1)
				match = TRUE;
		}
    ct = va_arg( marker, TCHAR);
	}
  va_end( marker );              /* Reset variable arguments.      */
	return match;
}

int CStrRout::CLetPos(LPCTSTR input, int start)
{
	CString str = input;
	BOOL found = FALSE;
	TCHAR c1;
	int i1 = max(1,start);
	while ((!found) && (i1 <= str.GetLength()))
	{
		c1 = str.GetAt(i1 - 1);
		if ((65 <= c1) && (c1 <= 90))
			found = TRUE;
		else
			i1++;
	}
	if (!found)
		i1 = 0;
	return i1;
}

int CStrRout::CLetPos(LPCTSTR input, int start, TCHAR cr, ...)
{
	CString str = input;
  va_list marker;
	TCHAR ct = 0;
	BOOL found = FALSE;
	TCHAR c1;
	int i1 = max(1,start);
	while ((!found) && (i1 <= str.GetLength()))
	{
		c1 = str.GetAt(i1 - 1);
		if (((c1 > 63) && (c1 < 91)) || ((c1 >= 97) && (c1 <= 122)))
		{
			found = TRUE;
		}
		else
		{
			va_start(marker, cr);     /* Initialize variable arguments. */
			ct = cr;
			while (( ct != -1) && (!found))
			{
				if (ct != -1)
				{
					if (ct == c1)
						found = TRUE;
				}
				ct = va_arg( marker, TCHAR);
			}
			va_end( marker );              /* Reset variable arguments.      */
		}
		if (!found)
			i1++;
	}
	if (!found)
		i1 = 0;
	return i1;
}

int CStrRout::ReadString(CStdioFile& myFile, int* p_int, ...)
{
	CString str;
	if (!myFile.ReadString(str))
		return 0;
	TrimString(str);
	if (str.GetLength() == 0)
		return 0;
	int count = 0;
	CString jstr;
  va_list marker;
	va_start(marker, p_int);     /* Initialize variable arguments. */
	int* p_next = p_int;
	int npos = 1;
	while ((npos > 0) && (p_next != NULL))
	{
		npos = NextCharacterGroup((LPCTSTR)str, jstr, npos);
		TrimString(jstr);
		if (!Numeric(jstr))
		{
			CString kstr,mstr;
			kstr.Format("trying to read non numeric data on '%s' !!\n\n", (LPCTSTR)str);
			mstr.Format("count: %d, npos: %d, jstr: %s", count, npos, jstr);
			kstr += mstr;
			throw kstr;
		}
		*p_next = atoi(jstr);
		p_next = va_arg( marker, int*);
		count++;
	}
	va_end( marker );              /* Reset variable arguments.      */
	return count;
}

int CStrRout::ReadString(CStdioFile& myFile, double* p_double, ...)
{
	CString str;
	if (!myFile.ReadString(str))
		return 0;
	TrimString(str);
	if (str.GetLength() == 0)
		return 0;
	int count = 0;
	CString jstr;
  va_list marker;
	va_start(marker, p_double);     /* Initialize variable arguments. */
	double* p_next = p_double;
	int npos = 1;
	while ((npos > 0) && (p_next != NULL))
	{
		npos = NextCharacterGroup((LPCTSTR)str, jstr, npos);
		TrimString(jstr);
		if (!Numeric(jstr))
		{
			CString kstr;
			kstr.Format("trying to read non numeric data on '%s' !!", (LPCTSTR)str);
			throw kstr;
		}
		*p_next = atof(jstr);
		p_next = va_arg( marker, double*);
		count++;
	}
	va_end( marker );              /* Reset variable arguments.      */
	return count;
}

int CStrRout::CharIndex(LPCTSTR input, int start, TCHAR cr, ...)
{
	CString str = input;
  va_list marker;
	TCHAR ct = 0;
	BOOL found = FALSE;
	TCHAR c1;
	int i1 = max(1,start);
	while ((!found) && (i1 <= str.GetLength()))
	{
		c1 = str.GetAt(i1-1);
		va_start(marker, cr);     /* Initialize variable arguments. */
		ct = cr;
		while (( ct != -1 ) && (!found))
		{
			if (ct != -1)
			{
				if (ct == c1)
					found = TRUE;
			}
			ct = va_arg( marker, TCHAR);
		}
		va_end( marker );              /* Reset variable arguments.      */
		if (!found)
			i1++;
	}
	if (!found)
		i1 = 0;
	return i1;
}

BOOL CStrRout::EthernetAddress(LPCTSTR input)
{
	CString ci = (CString)input;
	int len = ci.GetLength();
	int GroupCount = 0;
	int NumberCount = 0;
	int pos = 0;
	while (pos < len)
	{
		if (ci[pos] == 46)
		{
			if ((NumberCount < 1) || (NumberCount > 3))
				return FALSE;
			NumberCount = 0;
			GroupCount++;
		}
		else
		{
			NumberCount++;
			if ((ci[pos] < 48) || (ci[pos] > 57))
				return FALSE;
		}
		pos++;
	}
	if (GroupCount != 3)
		return FALSE;
	return TRUE;
}

BOOL CStrRout::Numeric(LPCTSTR input)
{
	CString ci = (CString)input;
	if (ci.GetLength() == 0)
		return FALSE;
	int pos = (CharPos(ci, 1) - 1);
	if (pos < 0)
		return FALSE;
	switch (ci[pos])
	{
		case 43: return TRUE;		
		case 45: return TRUE;
		case 46: return TRUE;
		default:
		{
			if ((ci[pos]>=48) && (ci[pos]<=57))
				return TRUE;
			else
				return FALSE;
		}
	}
}

BOOL CStrRout::Numeric(TCHAR ci)
{
	switch (ci)
	{
		case 43: return TRUE;		
		case 45: return TRUE;
		case 46: return TRUE;
		default:
		{
			if ((ci>=48) && (ci<=57))
				return TRUE;
			else
				return FALSE;
		}
	}
}

BOOL CStrRout::NonNumeric(LPCTSTR input)
{
	CString ci = input;
	if (ci.GetLength() == 0)
		return FALSE;
	int pos = (CharPos(ci, 1) -1);
	switch (ci[pos])
	{
		case 44: return TRUE;		
		case 47: return TRUE;
		default:
		{
			if (((ci[pos]>=33) && (ci[pos]<=42)) || ((ci[pos]>=58) && (ci[pos]<=126)))
				return TRUE;
			else
				return FALSE;
		}
	}
}

BOOL CStrRout::NonNumeric(TCHAR ci)
{
	switch (ci)
	{
		case 44: return TRUE;		
		case 47: return TRUE;
		default:
		{
			if (((ci>=33) && (ci<=42)) || ((ci>=58) && (ci<=126)))
				return TRUE;
			else
				return FALSE;
		}
	}
}

int CStrRout::NextVar(LPCTSTR instr, CString& output, int start)
{
	CString input = instr;
	int i1 = CharPos(input,start);
	int len1 = input.GetLength();
	if (i1>0)
	{
		if (NonNumeric(input.GetAt(i1-1)))
		{
			output = input.Mid(i1-1,1);
			if (i1 >= len1)
				return 0;
			else
				return CharPos(input,i1+1);
		}
		else
		{
			int stava = i1;
			while ((Numeric(input.GetAt(i1-1))) && (i1 < len1))
				i1++;
			int NextChar = 0;
			int delta = 1;
			if (NonNumeric(input.GetAt(i1-1)) || (input.GetAt(i1-1) == 32))
			{
				NextChar = CharPos(input,i1);
				delta = 0;
			}
			output = input.Mid(stava-1,i1 - stava + delta);
			return NextChar;
		}
	}
	output = input;
	return 0;
}

void CStrRout::NextKeyPosition(LPCTSTR instr, int& npos, int& endvar, TCHAR cr, ...)
{
	CString input = instr;
	CString output;
	//endvar = CharIndex(input, (npos+1), cr, ...);
	if (endvar == 0)
		endvar = input.GetLength() + 1;
	npos = NextVar(input, output, npos);
}

int CStrRout::PreviousCharacterGroup(LPCTSTR instr, CString& output, int start)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	int stava = CharPrevious(input,start);
	TCHAR c1,c2;
	if (stava>0)
	{
		int i1 = stava;
		BOOL found = TRUE;
		c1 = input.GetAt(i1 - 1);
		if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)))
		{
			i1--;
			while ((found) && (i1 >= 1))
			{
				c1 = input.GetAt(i1 - 1);
				if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)) || (c1 == 95))
					i1--;
				else
					found = FALSE;
			}
			output = input.Mid(i1, (stava - i1));
			return CharPrevious(input, i1);
		}
		if (((48 <= c1) && (c1 <= 57)) || (c1 == 46))
		{
			c2 = c1;
			i1--;
			while ((found) && (i1 >= 1))
			{
				c1 = input.GetAt(i1 - 1);
				if (((48 <= c1) && (c1 <= 57)) || (c1 == 43) ||(c1 == 45) ||(c1 == 46) || 
													(c1 == 69) || (c1 == 88) || (c1 == 101) || (c1 == 120))
				{
					if ((c2 == 43) ||(c2 == 45))
					{
						if ((c1 != 69) && (c1 != 101))
							found = FALSE;
					}
					c2 = c1;
					i1--;
				}
				else
					found = FALSE;
			}
			output = input.Mid(i1, (stava - i1));
			return CharPrevious(input, i1);
		}
		if (c1 == 42)
		{
			while ((found) && (i1 >= 1))
			{
				c1 = input.GetAt(i1 - 1);
				if (c1 == 42)
					i1--;
				else
					found = FALSE;
			}
			output = input.Mid(i1, (stava - i1));
			return CharPrevious(input, i1);
		}
		output = input.Mid((stava - 1), 1);
		return CharPrevious(input, (i1 - 1));
	}
	output = input;
	return 0;
}

int CStrRout::NextLabel(LPCTSTR instr, CString& output, int start)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	int stava = CLetPos(input, start);
	int len1 = input.GetLength();
	TCHAR c1;
	if (stava > 0)
	{
		int i1 = stava + 1;
		BOOL found = TRUE;
		if (i1 <= len1)
		{
			c1 = input.GetAt(i1 - 1);
			while (((32 < c1) && (c1 < 127)) && ((c1 < 65) || (90 < c1)) && (i1 <= len1))
			{
				i1++;
				if (i1 <= len1)
					c1 = input.GetAt(i1 - 1);
			}
		}
		output = input.Mid((stava - 1), (i1 - stava));
		return CLetPos(input, i1);
	}
	output = input;
	return 0;
}

int CStrRout::ThisNumberGroup(int& Start, int& Stop, LPCTSTR instr, int inpos)
{
	CString input = instr;
	int count = 0;
	int stava = inpos;
	int i1 = stava;
	int len1 = input.GetLength();
	TCHAR c1;
	if (stava > 0)
	{
		BOOL found = TRUE;
		while ((found) && (i1 <= len1))
		{
			c1 = input.GetAt(i1 - 1);
			if (((48 <= c1) && (c1 <= 57)) || (c1 == 46))
			{
				i1++;
				count++;
			}
			else
				found = FALSE;
		}
		found = TRUE;
		while ((found) && (stava > 0))
		{
			c1 = input.GetAt(stava - 1);
			if (((48 <= c1) && (c1 <= 57)) || (c1 == 46))
			{
				stava--;
				count++;
			}
			else
				found = FALSE;
		}
	}
	if (count > 0)
	{
		Start = stava + 1;
		Stop = i1 - 1;
	}
	else
	{
		Start = 0;
		Stop = 0;
	}
	return count;
}

int CStrRout::NumberCharacterGroups(LPCTSTR instr)
{
	CString output;
	int count = 0;
	int npos = CharPos(instr, 1);
	while (npos > 0)
	{
		count++;
		npos = NextCharacterGroup(instr, output, npos);
	}
	return count;
}

int CStrRout::NextCharacterGroup(LPCTSTR instr, CString& output, int start)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	int stava = CharPos(input, start);
	int len1 = input.GetLength();
	TCHAR c1,c2;
	if (stava > 0)
	{
		int i1 = stava;
		BOOL found = TRUE;
		c1 = input.GetAt(i1 - 1);
		if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)))
		{
			i1++;
			while ((found) && (i1 <= len1))
			{
				c1 = input.GetAt(i1 - 1);
				if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)) ||
									((48 <= c1) && (c1 <= 57)) || (c1 == 95))
					i1++;
				else
					found = FALSE;
			}
			output = input.Mid(stava - 1,i1 - stava);
			return CharPos(input,i1);
		}
		if (((48 <= c1) && (c1 <= 57)) || (c1 == 43) || (c1 == 45) || (c1 == 46))
		{
			c2 = c1;
			i1++;
			while ((found) && (i1 <= len1))
			{
				c1 = input.GetAt(i1 - 1);
				if (((48 <= c1) && (c1 <= 57)) || (c1 == 43) || (c1 == 45) || (c1 == 46) || 
													((65 <= c1) && (c1 <= 70)) || ((97 <= c1) && (c1 <= 102)) ||
													(c1 == 88) || (c1 == 120))
				{
					if ((c1 == 43) || (c1 == 45))
					{
						if ((c2 == 69) || (c2 == 101))
						{
							c2 = c1;
							i1++;
						}
						else
							found = FALSE;
					}
					else
					{
						c2 = c1;
						i1++;
					}
				}
				else
					found = FALSE;
			}
			found = TRUE;
			while ((found) && (i1 > stava))
			{
				c1 = input.GetAt(i1 - 2);
				if ((i1 > (stava + 1)) && ((c1 == 43) || (c1 == 45) || (c1 == 69) || (c1 == 101)))
					i1--;
				else
					found = FALSE;
			}
			output = input.Mid(stava - 1,i1 - stava);
			return CharPos(input,i1);
		}
		if (c1 == 42)
		{
			while ((found) && (i1 <= len1))
			{
				c1 = input.GetAt(i1 - 1);
				if (c1 == 42)
					i1++;
				else
					found = FALSE;
			}
			output = input.Mid(stava - 1,i1 - stava);
			return CharPos(input,i1);
		}
		output = input.Mid(stava - 1,1);
		return CharPos(input,i1 + 1);
	}
	output = input;
	return 0;
}

int CStrRout::NextConsecutiveCharacterGroup(LPCTSTR instr, CString& output, int start)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	int stava = CharPos(input,start);
	int len1 = input.GetLength();
	TCHAR c1;
	if (stava>0)
	{
		int i1 = stava;
		BOOL found = TRUE;
		while ((found) && (i1 <= len1))
		{
			c1 = input.GetAt(i1-1);
			if ((32 < c1) && (c1 < 127))
				i1++;
			else
				found = FALSE;
		}
		output = input.Mid(stava - 1,i1 - stava);
		return CharPos(input,i1);
	}
	output = input;
	return 0;
}

int CStrRout::ReadNumberVector(LPCTSTR instr, int* output, int lenmax)
{
	CString input = instr;
	int count = 0;
	if (input.GetLength() == 0)
		return count;
	CString jstr;
	int npos = 1;
	while (npos > 0)
	{
		npos = NextCharacterGroup(input, jstr, npos);
		if (jstr.GetLength() > 0)
		{
			if (Numeric(jstr))
			{	
				if (count >= lenmax)
				{
					CString str;
					str.Format("only %2d numbers allowed in one line!", lenmax);
					AfxMessageBox(str,MB_OK,0);
					return count;
				}
				else
				{
					*output = atoi(jstr);
					output++;
					count++;
				}
			}
			else
				AfxMessageBox("cannot convert to int type!",MB_OK,0);
		}
	}
	return count;
}

BOOL CStrRout::XParameter(CString& input)
{
	CString jstr,kstr;
	int npos = NextCharacterGroup(input, jstr, 1);
	jstr.MakeUpper();
	int len = jstr.GetLength();
	if (len > 0)
	{
		if (jstr[0] == 'X')
		{
			kstr = jstr.Right(len - 1);
			if (Numeric(kstr))
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CStrRout::XParameterExist(LPCTSTR instr)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return FALSE;
	CString jstr,kstr;
	int len;
	int npos = 1;
	while (npos > 0)
	{
		npos = NextCharacterGroup(input, jstr, npos);
		len = jstr.GetLength();
		if (len > 1)
		{
			if ((jstr[0] == 'X') || (jstr[0] == 'x'))
			{
				kstr = jstr.Right(len - 1);
				if (Numeric(kstr))
					return TRUE;
			}
		}
	}
	return FALSE;
}

int CStrRout::PreCommandPosition(LPCTSTR instr, CString& output, 
																	int start, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	va_list marker;
	CString tstr,jstr;
	BOOL found = FALSE;
	int pos,npos,len1;
	int position;
	int stava = CharPos(input,start);
	int FirstLetter = stava;
	while ((!found) && (stava >0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
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
				{
					position = stava;
					found = TRUE;
				}
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava=npos;
	}
	if (found)
	{
		if (position > FirstLetter)
			output = input.Left(position - 1);
		else
			output = _T("");
		return position;
	}
	else
	{
		output = input;
		return 0;
	}
}

void CStrRout::EliminateKeyWords(CString& input, int start, LPCTSTR str, ...)
{
	if (input.GetLength() == 0)
		return;
	va_list marker;
	CString tstr,jstr;
	int pos,npos,len1,Length;
	int stava = CharPos(input,start);
	while (stava >0)
	{
		npos = NextCharacterGroup(input, tstr, stava);
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
				if (len1 == jstr.GetLength())
				{
					Length = input.GetLength();
					input = input.Left(stava - 1) + input.Right(Length - stava - len1 + 1);
				}
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava=npos;
	}
}

int CStrRout::NextCommandPosition(LPCTSTR instr, CString& output, 
																	int start, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		output = input;
		return 0;
	}
	va_list marker;
	CString tstr,jstr;
	int found = 0;
	int pos,npos,len1;
	int position[2];
	int stava = CharPos(input,start);
	while ((found<2) && (stava >0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
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
				{
					position[found] = stava;
					found++;
				}
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava=npos;
	}
	if (found == 0)
	{
		output = _T("");
		return 0;
	}
	if (found >= 2)
	{
		output = input.Mid(position[0]-1,(position[1]-position[0]));
		//output.MakeUpper();
		return position[1];
	}
	else
	{
		output = input.Mid(position[0]-1,(input.GetLength()-position[0]+1));
		//output.MakeUpper();
		return 0;
	}
}

BOOL CStrRout::CommandPresent(LPCTSTR instr, int start, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return FALSE;
	va_list marker;
	CString tstr,jstr;
	int pos,len1;
	int npos = CharPos(input,start);
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
				{
					va_end( marker );              /* Reset variable arguments.      */
					return TRUE;
				}
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
	}
	return FALSE;
}

int CStrRout::ReadIntegerArray(int* p_int, int MaxNumber, LPCTSTR instr)
{
	CString input = instr;
	TrimString(input);
	if (input.GetLength() == 0)
		return 0;
	int count = 0;
	CString jstr,kstr;
	int npos = 1;
	while ((npos > 0) && (count < MaxNumber))
	{
		npos = NextCharacterGroup(input, kstr, npos);
		if (Numeric(kstr))
			*(p_int + count++) = atoi(kstr);
	}
	return count;
}

CString CStrRout::WriteIntegerArray(int* p_int, int Length)
{
	CString Result = _T("");
	if (Length > 0)
	{
		Result.Format("%d", *p_int);
		int i1;
		CString jstr;
		for (i1 = 1; i1 < Length; i1++)
		{
			jstr.Format(", %d", *(p_int + i1));
			Result += jstr;
		}
	}
	return Result;
}

void CStrRout::DataSetsPresent(CUIntArray& DSet, LPCTSTR instr)
{
	CString input = instr;
	DSet.RemoveAll();
	int npos = input.Find('{');
	if (npos < 0)
		return;
	CString jstr,kstr;
	int jpos = 1;
	while (jpos > 0)
	{
		jpos = NextCommandPosition(input, jstr, jpos, FALSE, "{", "?");
		npos = NextCharacterGroup(jstr, kstr, 2);
		DSet.Add(atoi(kstr));
	}
}

int CStrRout::DataSetNumber(LPCTSTR instr)
{
	CString input = instr;
	CString kstr;
	int jpos = CharIndex(input, 1, '{', -1);
	if (jpos > 0)
	{
		jpos = NextCharacterGroup(input, kstr, (jpos + 1));
		return atoi(kstr);
	}
	return -1;
}

void CStrRout::FindReplaceString(CString& wstr, LPCTSTR FindStr, LPCTSTR ReplaceStr)
{
	CString fstr = FindStr;
	CString rstr = ReplaceStr;
	int start = wstr.Find(fstr);
	int npos = start + fstr.GetLength();
	int len = wstr.GetLength();
	wstr = wstr.Left(start) + rstr + wstr.Right(len - npos);
}

BOOL CStrRout::CheckResult(LPCTSTR instr, LPCTSTR CommandLine)
{
	CString input = instr;
	CString tstr,kstr;
	if (input.GetLength() == 0)
		return FALSE;
	int stava = 1 + input.Find('{');
	if (stava <= 0)
	{
		if (NonNumeric(input))
		{
			kstr.Format("nonnumeric result '%s' on '%s'!!", instr, CommandLine);
			throw kstr;
		}
		return TRUE;
	}
	int pos = stava;
	int npos = FindMatchingBrace(input, stava);
	if (stava > 1)
	{
		tstr = input.Left(stava - 1);
		TrimString(tstr);
		if (tstr.GetLength() > 0)
		{
			kstr.Format("cannot evaluate '%s' on '%s'!!", (LPCTSTR)tstr, CommandLine);
			throw kstr;
		}
	}
	int Length = input.GetLength();
	if (npos < Length)
	{
		tstr = input.Right(Length - npos);
		TrimString(tstr);
		if (tstr.GetLength() > 0)
		{
			kstr.Format("cannot evaluate '%s' on '%s'!!", (LPCTSTR)tstr, CommandLine);
			throw kstr;
		}
	}
	return TRUE;
}

BOOL CStrRout::ExtractOperationTerm(CString& input, CString& output, 
																		CStringArray& Arguments, BOOL Remove, LPCTSTR str, ...)
{
	if (input.GetLength() == 0)
	{
		output = _T("");
		return FALSE;
	}
	va_list marker;
	CString tstr,jstr;
	TCHAR c1;
	BOOL found = FALSE;
	int pos,npos,len1;
	int position,stava,startpos;
	startpos = CharPos(input,1);
	stava = startpos;
	while ((!found) && (stava >0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
		tstr.MakeUpper();
		c1 = tstr[0];
		if (((c1 == 43) || (c1 == 45)) && (stava > startpos))
		{
			if (tstr.GetLength() > 1)
			{
				tstr = _T("");
				tstr += c1;
				npos = stava + 1;
			}
		}
		len1 = tstr.GetLength();
		va_start(marker, str);     /* Initialize variable arguments. */
		jstr = str;
		jstr.MakeUpper();
		while ((!found) && ( jstr[0] != '?' ))
		{
			pos = jstr.Find(tstr);
			if (pos == 0)
			{
				if (len1 == jstr.GetLength())
				{
					position = stava;
					found = TRUE;
				}
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava = npos;
	}
	Arguments.RemoveAll();
	if (found)
	{
		if (stava == 0)
		{
			CString kstr;
			kstr.Format("argument missing after operator '%s' in '%s' !!", (LPCTSTR)tstr, (LPCTSTR)input);
			throw kstr;
		}
		Arguments.SetSize(3,10);
		Arguments.SetAt(1, tstr);
		npos = NextCharacterGroup(input, tstr, stava);
		if (tstr[0] == '{')
		{
			pos = stava;
			npos = FindMatchingBrace(input, stava);
			tstr = input.Mid(pos - 1, (npos - pos + 1));
			Arguments.SetAt(2, tstr);
			npos = CharPos(input, (npos + 1));
		}
		else
			Arguments.SetAt(2, tstr);
		if (npos == 0)
			npos = input.GetLength() + 1;
		if (CharPrevious(input, position - 1) == 0)
		{
			c1 = input[position - 1];
			if ((c1 == 43) || (c1 == 45))
			{
				tstr = _T("0.0");
				Arguments.SetAt(0, tstr);
				stava = 0;
			}
			else
			{
				CString kstr;
				kstr.Format("argument missing before operator '%s' in '%s' !!", (LPCTSTR)tstr, (LPCTSTR)input);
				throw kstr;
			}
		}
		else
		{
			stava = PreviousCharacterGroup(input, tstr, (position - 1));
			if (tstr[0] == '}')
			{
				stava = CharPrevious(input, position - 1);
				stava = FindMatchingBrace(input, stava);
				stava = CharPrevious(input, (stava - 1));
				if (stava > 0)
					tstr = input.Mid(stava, (position - stava - 1));
				else
					tstr = input.Left(position - 1);
				Arguments.SetAt(0, tstr);
			}
			else
				Arguments.SetAt(0, tstr);
		}
		output = input.Mid(stava, (npos - stava - 1));
		if (Remove)
		{
			jstr = output;
			stava = input.Find(jstr);
			npos = stava + jstr.GetLength();
			int len = input.GetLength();
			CString wstr = input.Left(stava);
			if (len > npos)
			{
				jstr = input.Right(len - npos);
				input = wstr + jstr;
			}
			else
				input = wstr;
		}
		return TRUE;
	}
	else
	{
		output = _T("");
		return FALSE;
	}
}

BOOL CStrRout::RemoveOuterBracket(LPCTSTR instr, CString& output)
{
	CString wstr = instr;
	int npos,len,start;
	BOOL BracketRemoved = FALSE;
	BOOL Found = TRUE;
	while (Found)
	{
		Found = FALSE;
		TrimString(wstr);
		start = CharPos(wstr, 1);
		if (start > 0)
		{
			if (wstr[start - 1] == '(')
			{
				npos = FindMatchingBrace(wstr, start);
				len = wstr.GetLength();
				if (len == npos)
				{
					wstr = wstr.Mid(start, npos - start -1);
					Found = TRUE;
					BracketRemoved = TRUE;
				}
			}
		}
	}
	output = wstr;
	return BracketRemoved;
}

BOOL CStrRout::FindBracketTerm(LPCTSTR instr, CString& output)
{
	CString input = instr;
	int start = CharIndex(input, 1, '(', -1);
	if (start > 0)
	{
		int npos = FindMatchingBrace(input, start);
		output = input.Mid(start - 1, npos - start + 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CStrRout::ExtractBaseTerm(CString& input, CString& output, BOOL Remove)
{
	CString wstr = input;
	CString jstr;
	BOOL found = FALSE;
	while (FindBracketTerm((LPCTSTR)wstr, jstr))
	{
		if (wstr.GetLength() > jstr.GetLength())
		{
			found = TRUE;
			RemoveOuterBracket((LPCTSTR)jstr, wstr);
		}
		else
			break;
	}
	if (found)
	{
		output = jstr;
		if (Remove)
		{
			int start = input.Find(jstr);
			int npos = start + jstr.GetLength();
			int len = input.GetLength();
			wstr = input.Left(start);
			if (len > npos)
			{
				jstr = input.Right(len - npos);
				input = wstr + jstr;
			}
			else
				input = wstr;
		}
		return TRUE;
	}
	else
	{
		output = _T("");
		return FALSE;
	}
}

CString CStrRout::EvaluateString(CString& CommandLine)
{
	CString wstr;
	RemoveOuterBracket((LPCTSTR)CommandLine, wstr);
	CString jstr,kstr;
	int Count = 0;
	BOOL Remove = FALSE;
	while (ExtractBaseTerm(wstr, jstr, Remove))
	{
		kstr = EvaluateBaseString(jstr);
		FindReplaceString(wstr, jstr, kstr);
		Count++;
		if (Count > MaxNoEvaluations)
			throw(CString)"exceeded base term evaluation limit!!";
	}
	kstr = EvaluateBaseString(wstr);
	return kstr;
}

CString CStrRout::EvaluateOperationString(CStringArray& Arguments)
{
	CString wstr;
	CString	jstr = Arguments.GetAt(0);
	CString tstr = Arguments.GetAt(1);
	CString	kstr = Arguments.GetAt(2);
	double p1,q1,r1;
	BOOL Exact = TRUE;
	if (CommandType(tstr, 1, Exact, "-", "?"))
	{
		r1 = atof(jstr) - atof(kstr);
		wstr.Format(" %13.11f",r1);
		wstr = TrimTrailingZeros(wstr);
		wstr += " ";
		return wstr;
	}
	if (CommandType(tstr, 1, Exact, "+", "?"))
	{
		r1 = atof(jstr) + atof(kstr);
		wstr.Format(" %13.11f",r1);
		wstr = TrimTrailingZeros(wstr);
		wstr += " ";
		return wstr;
	}
	if (CommandType(tstr, 1, Exact, "**", "^", "?"))
	{
		q1 = atof(kstr);
		p1 = atof(jstr);
		r1 = pow(p1, q1);
		wstr.Format(" %13.11f",r1);
		wstr = TrimTrailingZeros(wstr);
		wstr += " ";
		return wstr;
	}
	if (CommandType(tstr, 1, Exact, "*", "?"))
	{
		r1 = atof(jstr) * atof(kstr);
		wstr.Format(" %13.11f",r1);
		wstr = TrimTrailingZeros(wstr);
		wstr += " ";
		return wstr;
	}
	if (CommandType(tstr, 1, Exact, "/", "Div", "?"))
	{
		r1 = atof(jstr) / atof(kstr);
		wstr.Format(" %13.11f",r1);
		wstr = TrimTrailingZeros(wstr);
		wstr += " ";
		return wstr;
	}
	return _T("");
}

CString CStrRout::EvaluateBaseString(CString& CommandLine)
{
	CStringArray Arguments;
	CString wstr = CommandLine;
	int len;
	int npos = wstr.Find('(');
	if (npos >= 0)
	{
		len = wstr.GetLength();
		wstr = wstr.Right(len - npos - 1);
		wstr.TrimLeft();
	}
	npos = wstr.ReverseFind(')');
	if (npos >= 0)
	{
		wstr = wstr.Left(npos);
		wstr.TrimRight();
	}
	CString jstr,kstr;
	int Count = 0;
	BOOL Remove = FALSE;
	while (ExtractOperationTerm(wstr, jstr, Arguments, Remove, 
								"**", "^", "?"))
	{
		kstr = EvaluateOperationString(Arguments);
		if (kstr == jstr)
			break;
		FindReplaceString(wstr, jstr, kstr);
		Count++;
		if (Count > MaxNoEvaluations)
			throw(CString)"exceeded '**', '^' evaluation limit!!";
	}
	while (ExtractOperationTerm(wstr, jstr, Arguments, Remove, 
								"*", "/", "Div", "?"))
	{
		kstr = EvaluateOperationString(Arguments);
		if (kstr == jstr)
			break;
		FindReplaceString(wstr, jstr, kstr);
		Count++;
		if (Count > MaxNoEvaluations)
			throw(CString)"exceeded '*', '/' evaluation limit!!";
	}
	while (ExtractOperationTerm(wstr, jstr, Arguments, Remove, 
								"+", "-", "?"))
	{
		kstr = EvaluateOperationString(Arguments);
		if (kstr == jstr)
			break;
		FindReplaceString(wstr, jstr, kstr);
		Count++;
		if (Count > MaxNoEvaluations)
			throw(CString)"exceeded '+', '-' evaluation limit!!";
	}
	return wstr;
}

BOOL CStrRout::ExtractFunction(CString& input, CString& output, 
															 BOOL Remove, BOOL exact, LPCTSTR str, ...)
{
	va_list marker;
	va_start(marker, str);     /* Initialize variable arguments. */
	CString wstr = input;
	CString jstr,kstr;
	int start = 1;
	int npos;
	BOOL found = FALSE;
	while ((FindFunction(wstr, kstr, start, npos, exact, marker, str)) && (start > 0))
	{
		found = TRUE;
		jstr = kstr;
		start = npos;
	}
	if (found)
	{
		output = jstr;
		if (Remove)
		{
			start = input.Find(jstr);
			npos = start + jstr.GetLength();
			int len = input.GetLength();
			wstr = input.Left(start);
			if (len > npos)
			{
				jstr = input.Right(len - npos);
				input = wstr + jstr;
			}
			else
				input = wstr;
		}
		return TRUE;
	}
	else
	{
		output = _T("");
		return FALSE;
	}
}

int CStrRout::StringList(CStringArray& output,  LPCTSTR str, ...)
{
	va_list marker;
	CString jstr;
	output.RemoveAll();
	output.SetSize(0,10);
	va_start(marker, str);     /* Initialize variable arguments. */
	jstr = str;
	int i1 = 0;
	while( jstr[0] != '?' )
	{
		output.SetAtGrow(i1,jstr);
		jstr = va_arg( marker, LPCTSTR);
		i1++;
	} 
	output.SetAtGrow(i1,jstr);
	va_end( marker );              /* Reset variable arguments.      */
	return i1;
}

CString CStrRout::GetCompositionString(LPCTSTR instr)
{
	CString wstr = instr;
	TrimString(wstr);
	int npos = wstr.Find('?');
	if (npos >= 0)
	{
		wstr = wstr.Left(npos);
		TrimString(wstr);
	}
	return wstr;
}

CString CStrRout::GetVariableString(LPCTSTR instr)
{
	CString wstr = instr;
	TrimString(wstr);
	int npos = wstr.ReverseFind('?');
	if (npos >= 0)
	{
		int Length = wstr.GetLength();
		wstr = wstr.Right(Length - npos - 1);
		TrimString(wstr);
		return wstr;
	}
	else
		return _T("");
}

CString CStrRout::CombineCompositionAndVariable(LPCTSTR Composition, LPCTSTR Variable)
{
	CString cstr = Composition;
	TrimString(cstr);
	CString vstr = Variable;
	TrimString(vstr);
	CString kstr = _T("");
	if (cstr.GetLength() > 0)
		kstr = cstr;
	if (vstr.GetLength() > 0)
		kstr += (" ? " + vstr);
	return kstr;
}

BOOL CStrRout::FindFunction(LPCTSTR instr, CString& output, 
													int start, int& nextpos, BOOL exact, va_list& marker, LPCTSTR str)
{
	CString input = instr;
	va_list marker2;
	if (input.GetLength() == 0)
	{
		nextpos = 0;
		output = input;
		return FALSE;
	}
	CString tstr,jstr,kstr;
	BOOL found = FALSE;
	int pos,npos,len1;
	int position;
	int stava = CharPos(input, start);
	while ((!found) && (stava > 0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
		tstr.MakeUpper();
		len1 = tstr.GetLength();
		memcpy(&marker2, &marker, sizeof(va_list));
		jstr = str;
		jstr.MakeUpper();
		while( jstr[0] != '?' )
		{
			pos = jstr.Find(tstr);
			if (pos == 0)
			{
				if ((!exact) || (len1 == jstr.GetLength()))
				{
					position = stava;
					found = TRUE;
				}
			}
			jstr = va_arg( marker2, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker2 );              /* Reset variable arguments.      */
		stava = npos;
	}
	if (found)
	{
		if (npos <= 0)
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		if (input[npos - 1] != '(')
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
	  int last = FindMatchingBrace(input, npos);
		if (last <= 0)
		{
			kstr.Format("no closing brace ')' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		output = input.Mid((position - 1), (last - position + 1));
		nextpos = npos;
		return TRUE;
	}
	else
	{
		nextpos = 0;
		output = _T("");
		return FALSE;
	}
}

BOOL CStrRout::FindFunction(LPCTSTR instr, CString& output, 
																	int start, int& nextpos, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
	{
		nextpos = 0;
		output = input;
		return FALSE;
	}
	va_list marker;
	va_start(marker, str);  
	BOOL result = FindFunction(instr, output, start, nextpos, exact, marker, str);
	return result;
}


BOOL CStrRout::CheckBraceMatch(LPCTSTR instr, int ErrorAction /* = DisplayMessageBox*/)
{
	CString CommandLine = instr;
	CString braces = "()[]{}";
	TCHAR tch;
	int Length = CommandLine.GetLength();
	int tpos,jpos,kpos;
	for (tpos = 0; tpos < Length; tpos++)
	{
		tch = CommandLine[tpos];
		jpos = braces.Find(tch);
		if (jpos >= 0) 
		{
			kpos = FindMatchingBrace(instr, (tpos + 1));
			if (kpos <= 0)
			{
				CString kstr;
				kstr.Format("braces don't match on ''%s'' !!", instr);
				if (ErrorAction == DisplayMessageBox)
				{
					AfxMessageBox(kstr, MB_OK, 0);
					return FALSE;
				}
				else
					throw kstr;
			}
		}
	}
	return TRUE;
}

int CStrRout::FindMatchingBrace(LPCTSTR instr, int inpos) 
{
	CString CommandLine = instr;
	TCHAR inbrace = CommandLine[inpos - 1];
	CString braces = "()";
	int pos = braces.Find(inbrace);
	if (pos < 0)
	{
		braces = "[]";
		pos = braces.Find(inbrace);
		if (pos < 0)
		{
			braces = "{}";
			pos = braces.Find(inbrace);
			if (pos < 0)
			{
				braces = "''";
				pos = braces.Find(inbrace);
				if (pos < 0)
					return 0;
			}
		}
	}
	int len = CommandLine.GetLength();
	int jpos;
	TCHAR tch;
	if (pos == 0)
	{
		int tpos = inpos;
		int found = 1;
		while ((found > 0) && (tpos < len))
		{
			tch = CommandLine[tpos++];
			jpos = braces.Find(tch);
			if (jpos == 0)
				found++;
			if (jpos == 1)
				found--;
		}
		if (found == 0)
			return tpos;
		else
			return 0;
	}
	else
	{
		int tpos = inpos-2;
		int found = 1;
		while ((found > 0) && (tpos >= 0))
		{
			tch = CommandLine[tpos--];
			jpos = braces.Find(tch);
			if (jpos == 0)
				found--;
			if (jpos == 1)
				found++;
		}
		if (found == 0)
			return (tpos + 2);
		else
			return 0;
	}
}

BOOL CStrRout::FindEnclosingBrace(int& Start, int& Stop, LPCTSTR instr, int inpos) 
{
	CString CommandLine = instr;
	int Length = CommandLine.GetLength();
	CString LeftBraces = "([{";
	CString RightBraces = ")]}";
	TCHAR tch;
	int found = 0;
	int bpos;
	int jpos = 0;
	int tpos = inpos;
	while ((tpos < Length) && (found < 1))
	{
		tch = CommandLine[tpos++];
		bpos = RightBraces.Find(tch);
		if (bpos >= 0)
			found++;
		bpos = LeftBraces.Find(tch);
		if (bpos >= 0)
			found--;
	}
	if (found == 1)
	{
		Stop = tpos;
		Start = FindMatchingBrace(instr, Stop);
		return TRUE;
	}
	else
	{
		Start = -1;
		Stop = -1;
		return FALSE;
	}
}


BOOL CStrRout::FindReplaceDataSet(CString& DataDef, CString& CommandLine, int FuncNo) 
{
	int pos1 = CommandLine.Find('[');
	if (pos1 < 0)
		return FALSE;
	int pos2 = CommandLine.Find(']');
	if ((pos2 >= 0) && (pos2 < pos1))
	{
		throw(CString)"opening brace '[' is missing!!";
		return FALSE;
	}
	pos2 = FindMatchingBrace(CommandLine, (pos1 + 1));
	if (pos2 <= 0)
	{
		throw(CString)"closing brace ']' is missing!!";
		return FALSE;
	}
	else
	{
		DataDef = CommandLine.Mid(pos1, (pos2 - pos1));
		CString rstr;
		rstr.Format("{ %1d }", FuncNo);
		CString str1 = CommandLine.Left(pos1);
		int len = CommandLine.GetLength();
		if (len == pos2)
			CommandLine = (str1 + rstr);
		else
		{
			CString str2 = CommandLine.Right(len - pos2);
			CommandLine = str1 + rstr + str2;
		}
		return TRUE;
	}
}

BOOL CStrRout::FindReplaceDataSet(CString& DataDef, double& Multiplier, CString& CommandLine, int FuncNo) 
{
	Multiplier = 1.0;
	int pos1 = CommandLine.Find('[');
	if (pos1 < 0)
		return FALSE;
	int pos2 = FindMatchingBrace(CommandLine, (pos1 + 1));
	if (pos2 <= 0)
	{
		throw(CString)"closing brace ']' is missing!!";
		return FALSE;
	}
	else
	{
		DataDef = CommandLine.Mid(pos1, (pos2 - pos1));
		CString rstr;
		int stava = CharPrevious(CommandLine, pos1);
		if (stava > 0)
		{
			if (CommandLine.GetAt(stava - 1) == '*')
				stava = CharPrevious(CommandLine, (stava - 1));
			if (Numeric(CommandLine.GetAt(stava - 1)))
			{
				if (CommandLine.GetAt(stava - 1) == '-')
					Multiplier *= -1.0;
				else
				{
					stava = PreviousCharacterGroup(CommandLine, rstr, stava);
					Multiplier = atof(rstr);
					if ((Multiplier > 0) && (stava > 0))
					{
						if (CommandLine.GetAt(stava - 1) == '-')
							Multiplier *= -1.0;
					}
				}
			}
		}
		rstr.Format("{ %1d }", FuncNo);
		CString str1 = CommandLine.Left(pos1);
		int len = CommandLine.GetLength();
		if (len == pos2)
			CommandLine = (str1 + rstr);
		else
		{
			CString str2 = CommandLine.Right(len - pos2);
			CommandLine = str1 + rstr + str2;
		}
		return TRUE;
	}
}

BOOL CStrRout::SubstanceSequence(LPCTSTR CommandLine)
{
	CString wstr = CommandLine;
	TrimString(wstr);
	int npos = wstr.Find('?');
	if (npos >= 0)
		wstr = wstr.Left(npos);
	TrimString(wstr);
	if (wstr.GetLength() == 0)
		return FALSE;
	int FuncNo = 0;
	BOOL b_Sequence = FALSE;
	CStringArray	Arguments;
	CString DataDef,jstr,kstr;
	double Multiplier;
	while (FindReplaceDataSet(DataDef, Multiplier, wstr, FuncNo))
	{
		ArgumentList(Arguments, DataDef);
		if (Arguments.GetSize() > 1)
		{
			jstr = Arguments.GetAt(1);
			if (CommandType(jstr, "B-Sequence", "Y-Sequence", "Symbol", "Abbreviate", "?"))
			{
				if (CommandType(jstr, "Symbol", "Abbreviate", "?"))
				{
					if (Arguments.GetSize() > 2)
					{
						kstr = Arguments.GetAt(2);
						if (CommandType(kstr, "B-Sequence", "Y-Sequence", "?"))
							b_Sequence = TRUE;
					}
				}
				else
				{
					if (CommandType(jstr, "B-Sequence", "Y-Sequence", "?"))
						b_Sequence = TRUE;
				}
			}
		}
		FuncNo++;
	}
	return b_Sequence;
}

BOOL CStrRout::CheckIsotopeDefinition(LPCTSTR CommandLine, int ErrorAction /* = DisplayMessageBox*/) 
{
	CString kstr = CommandLine;
	TrimString(kstr);
	if (kstr.GetLength() == 0)
		return TRUE;
	CStringArray Arguments;
	CString str,jstr,lstr;
	TCHAR c1;
	int Length,ista;
	int pos1 = kstr.Find('[');
	int pos2 = kstr.Find(']');
	if ((pos1 < 0) && (pos2 < 0))
	{
		str.Format("at least one isotope or substance definition must be present on '%s'!!\n", 
																																(LPCTSTR)CommandLine);
		str += _T(" (enter the corresponding label between two square braces, e.g. [C] or [H])");
		if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
		{
			if (ErrorAction == DisplayMessageBox)
				AfxMessageBox(str, MB_OK, 0);
			return FALSE;
		}
		else
			throw str;
	}
	if (((pos1 < 0) && (pos2 >= 0)) || ((pos2 < 0) && (pos1 >= 0)))
	{
		str.Format("braces on '%s' dont match!!", (LPCTSTR)CommandLine);
		if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
		{
			if (ErrorAction == DisplayMessageBox)
				AfxMessageBox(str, MB_OK, 0);
			return FALSE;
		}
		else
			throw str;
	}
	while (pos1 >= 0)
	{
		if (pos2 < pos1)
		{
			str.Format("expected an opening brace '[' on '%s' !!", (LPCTSTR)CommandLine);
			if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
			{
				if (ErrorAction == DisplayMessageBox)
					AfxMessageBox(str, MB_OK, 0);
				return FALSE;
			}
			else
				throw str;
		}
		pos2 = FindMatchingBrace(kstr, (pos1 + 1));
		if (pos2 <= 0)
		{
			str.Format("closing brace ']' on '%s' is missing!!", (LPCTSTR)CommandLine);
			if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
			{
				if (ErrorAction == DisplayMessageBox)
					AfxMessageBox(str, MB_OK, 0);
				return FALSE;
			}
			else
				throw str;
		}
		jstr = kstr.Mid((pos1 + 1), (pos2 - pos1 - 2));
		TrimString(jstr);
		if (jstr.GetLength() <= 0)
		{
			str.Format("empty definition between braces '[]' on '%s' !!", (LPCTSTR)CommandLine);
			if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
			{
				if (ErrorAction == DisplayMessageBox)
					AfxMessageBox(str, MB_OK, 0);
				return FALSE;
			}
			else
				throw str;
		}
		else
		{
			ArgumentList(Arguments, (LPCTSTR)jstr);
			if (Arguments.GetSize() > 1)
			{
				lstr = Arguments.GetAt(1);
				if (!CommandType(lstr, "B-Sequence", "Y-Sequence", "?"))
				{
					if ((NonNumeric(lstr)) || (lstr.Find('.') >= 0))
					{
						str.Format("isotope selector on '%s' has to be an integer number!!", (LPCTSTR)CommandLine);
						if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
						{
							if (ErrorAction == DisplayMessageBox)
								AfxMessageBox(str, MB_OK, 0);
							return FALSE;
						}
						else
							throw str;
					}
				}
			}
		}
		ista = CharPos(kstr, 1);
		if (ista <= pos1)
		{
			c1 = kstr.GetAt(ista - 1);
			if ((c1 == 43) || (c1 == 45))
			{
				ista = NextCharacterGroup(kstr, jstr, ista);
				TrimString(jstr);
				if ((jstr.GetLength() == 1) && ((ista - pos1) < 1))
					ista = NextCharacterGroup(kstr, jstr, ista);
			}
			else
				ista = NextCharacterGroup(kstr, jstr, ista);
			if (NonNumeric(jstr))
			{
				str.Format("multiplier before braces '[ ]' on '%s' has to be an integer number!!", 
																																	(LPCTSTR)CommandLine);
				if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
				{
					if (ErrorAction == DisplayMessageBox)
						AfxMessageBox(str, MB_OK, 0);
					return FALSE;
				}
				else
					throw str;
			}
			if ((ista - pos1) != 1)
			{
				str.Format("only one multiplier before braces '[ ]' on '%s' is allowed!!", (LPCTSTR)CommandLine);
				if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
				{
					if (ErrorAction == DisplayMessageBox)
						AfxMessageBox(str, MB_OK, 0);
					return FALSE;
				}
				else
					throw str;
			}
		}
		Length = kstr.GetLength();
		kstr = kstr.Right(Length - pos2);
		pos1 = kstr.Find('[');
		pos2 = kstr.Find(']');
		if (((pos1 < 0) && (pos2 >= 0)) || ((pos2 < 0) && (pos1 >= 0)))
		{
			str.Format("braces on '%s' dont match!!", (LPCTSTR)CommandLine);
			if ((ErrorAction == DisplayMessageBox) || (ErrorAction == ReturnValueFalse))
			{
				if (ErrorAction == DisplayMessageBox)
					AfxMessageBox(str, MB_OK, 0);
				return FALSE;
			}
			else
				throw str;
		}
	}
	return TRUE;
}

double CStrRout::DefaultArgument(double DefaultValue, CStringArray& Arguments, int ArgumentNo)
{
	double result = DefaultValue;
	if (Arguments.GetSize() > ArgumentNo)
	{
		CString kstr = Arguments.GetAt(ArgumentNo);
		TrimString(kstr);
		if (kstr.GetLength() > 0)
			result = atof(kstr);
	}
	return result;
}

TCHAR CStrRout::DefaultArgument(TCHAR DefaultValue, CStringArray& Arguments, int ArgumentNo)
{
	TCHAR result = DefaultValue;
	if (Arguments.GetSize() > ArgumentNo)
	{
		CString kstr = Arguments.GetAt(ArgumentNo);
		TrimString(kstr);
		if (kstr.GetLength() > 0)
		{
			kstr.MakeUpper();
			result = kstr.GetAt(0);
		}
	}
	return result;
}

int CStrRout::DefaultArgument(int DefaultValue, CStringArray& Arguments, int ArgumentNo)
{
	int result = DefaultValue;
	if (Arguments.GetSize() > ArgumentNo)
	{
		CString kstr = Arguments.GetAt(ArgumentNo);
		TrimString(kstr);
		if (kstr.GetLength() > 0)
		{
			if (Numeric(kstr))
				result = atoi(kstr);
			else
			{
				if (CommandType(kstr, "TRUE", "?"))
					result = TRUE;
				if (CommandType(kstr, "FALSE", "?"))
					result = FALSE;
			}
		}
	}
	return result;
}

CString CStrRout::DefaultArgument(LPCTSTR DefaultValue, CStringArray& Arguments, int ArgumentNo)
{
	CString result = DefaultValue;
	if (Arguments.GetSize() > ArgumentNo)
	{
		CString kstr = Arguments.GetAt(ArgumentNo);
		TrimString(kstr);
		if (kstr.GetLength() > 0)
			result = kstr;
	}
	return result;
}

CString CStrRout::AddCommas(LPCTSTR instr)
{
	CString input = instr;
	BOOL SquareBrace = FALSE;
	BOOL RoundBrace = FALSE;
	BOOL WaveBrace = FALSE;
	CString wstr = input;
	wstr.TrimRight();
	wstr.TrimLeft();
	int len = wstr.GetLength();
	CString result = _T("");
	int start = CharIndex(wstr, 1, '(', '[', '{', -1);
	if (start > 0)
	{
		result = wstr.Left(start - 1);
		wstr = wstr.Right(len - start + 1);
		len -= (start - 1);
	}
	if (CompareChar(wstr[0], '[', '(', '{', -1))
	{
		if (CompareChar(wstr[0], '[', -1))
			SquareBrace = TRUE;
		if (CompareChar(wstr[0], '(', -1))
			RoundBrace = TRUE;
		if (CompareChar(wstr[0], '{', -1))
			WaveBrace = TRUE;
		len--;
		CString kstr = wstr.Right(len);
		if (CompareChar(kstr[len - 1], ']', ')', '}', -1))
		{
			if (!CompareChar(kstr[len - 1], ']', -1))
				SquareBrace = FALSE;
			if (!CompareChar(kstr[len - 1], ')', -1))
				RoundBrace = FALSE;
			if (!CompareChar(kstr[len - 1], '}', -1))
				WaveBrace = FALSE;
			len--;
			wstr = kstr.Left(len);
		}
	}
	if (SquareBrace)
		result += "[";
	if (RoundBrace)
		result += "(";
	if (WaveBrace)
		result += "{";
	int jpos,npos;
	CString jstr;
	//npos = 1;
	start = 1;
	while (start > 0)
	{
		npos = NextCharacterGroup(wstr, jstr, start);
		if (npos > 0)
		{
			jpos = npos;
			while ((jpos > 0) && (jpos <= npos))
			{
				jpos = CharIndex(wstr, jpos, '(', '[', '{', -1);
				if ((jpos > 0) && (jpos <= npos))
				{
					jpos = 1 + FindMatchingBrace(wstr, jpos);
					npos = NextCharacterGroup(wstr, jstr, jpos);
				}
			}
		}
		if (npos == 0)
		{
			if (start > 1)
			{
				result += ",";
				result += wstr.Right(len - start + 1);
			}
			else
				result += wstr;
			start = 0;
		}
		else
		{
			if (start > 1)
			{
				result += ",";
				result += wstr.Mid(start - 1,	npos - start);
			}
			else
				result += wstr.Left(npos - start);
			start = npos;
		}
	}
	if (SquareBrace)
		result += "]";
	if (RoundBrace)
		result += ")";
	if (WaveBrace)
		result += "}";
	return result;
}

void CStrRout::ArgumentList(CStringArray& Arguments, LPCTSTR instr) 
{
	CString input = instr;
	BOOL SquareBrace = FALSE;
	Arguments.RemoveAll();
	CString wstr = input;
	wstr.TrimRight();
	wstr.TrimLeft();
	int len = wstr.GetLength();
	if (CompareChar(wstr[0], '[', '(', '{', -1))
	{
		if (CompareChar(wstr[0], '[', -1))
			SquareBrace = TRUE;
		len--;
		CString kstr = wstr.Right(len);
		if (CompareChar(kstr[len - 1], ']', ')', '}', -1))
		{
			if (!CompareChar(kstr[len - 1], ']', -1))
				SquareBrace = FALSE;
			len--;
			wstr = kstr.Left(len);
		}
	}
	int jpos,npos,start;
	if ((SquareBrace) && (CharIndex(wstr, 1, ',', -1) == 0))
	{
		CString jstr;
		//npos = 1;
		start = 1;
		while (start > 0)
		{
			npos = NextCharacterGroup(wstr, jstr, start);
			if (npos > 0)
			{
				jpos = npos;
				while ((jpos > 0) && (jpos <= npos))
				{
					jpos = CharIndex(wstr, jpos, '(', '[', '{', -1);
					if ((jpos > 0) && (jpos <= npos))
					{
						jpos = 1 + FindMatchingBrace(wstr, jpos);
						npos = NextCharacterGroup(wstr, jstr, jpos);
					}
				}
			}
			if (npos == 0)
			{
				if (start > 1)
					Arguments.Add(wstr.Right(len - start + 1));
				else
					Arguments.Add(wstr);
				start = 0;
			}
			else
			{
				if (start > 1)
					Arguments.Add(wstr.Mid(start - 1,	npos - start));
				else
					Arguments.Add(wstr.Left(npos - start));
				start = npos;
			}
			//if (jstr.GetLength() > 0)
			//	Arguments.Add(jstr);
		}
	}
	else
	{
		start = 1;
		while (start > 0)
		{
			npos = CharIndex(wstr, start, ',', -1);
			if (npos > 0)
			{
				jpos = start;
				while ((jpos > 0) && (jpos < npos))
				{
					jpos = CharIndex(wstr, jpos, '(', '[', '{', -1);
					if ((jpos > 0) && (jpos < npos))
					{
						jpos = 1 + FindMatchingBrace(wstr, jpos);
						npos = CharIndex(wstr, jpos, ',', -1);
					}
				}
			}
			if (npos == 0)
			{
				if (start > 1)
					Arguments.Add(wstr.Right(len - start + 1));
				else
					Arguments.Add(wstr);
				start = 0;
			}
			else
			{
				if (start > 1)
					Arguments.Add(wstr.Mid(start - 1,	npos - start));
				else
					Arguments.Add(wstr.Left(npos - start));
				start = npos + 1;
			}
		}
	}
}

void CStrRout::ArgumentList(CStringArray& Arguments, LPCTSTR instr, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	va_list marker;
	CString tstr,jstr,kstr;
	BOOL found = FALSE;
	int pos,npos,len1;
	int start = 1;
	int stava = CharPos(input,start);
	while ((!found) && (stava >0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
		tstr.MakeUpper();
		len1 = tstr.GetLength();
		va_start(marker, str);     /* Initialize variable arguments. */
		jstr = str;
		jstr.MakeUpper();
		while ((jstr[0] != '?') && (!found))
		{
			pos = jstr.Find(tstr);
			if (pos == 0)
			{
				if ((!exact) || (len1 == jstr.GetLength()))
					found = TRUE;
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava = npos;
	}
	if (found)
	{
		if (npos <= 0)
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		if (input[npos - 1] != '(')
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
	  int last = FindMatchingBrace(input, npos);
		if (last <= 0)
		{
			kstr.Format("no closing brace ')' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		jstr = input.Mid((npos - 1), (last - npos + 1));
		ArgumentList(Arguments, jstr);
	}
	else
		Arguments.RemoveAll();
}

void CStrRout::ArgumentList(CStringArray& Arguments, LPCTSTR instr, BOOL exact, 
														int MinNoArguments, LPCTSTR str, ...)
{
	CString input = instr;
	va_list marker;
	CString tstr,jstr,kstr;
	BOOL found = FALSE;
	int pos,npos,len1;
	int start = 1;
	int stava = CharPos(input,start);
	while ((!found) && (stava >0))
	{
		npos = NextCharacterGroup(input, tstr, stava);
		tstr.MakeUpper();
		len1 = tstr.GetLength();
		va_start(marker, str);     /* Initialize variable arguments. */
		jstr = str;
		jstr.MakeUpper();
		while ((jstr[0] != '?') && (!found))
		{
			pos = jstr.Find(tstr);
			if (pos == 0)
			{
				if ((!exact) || (len1 == jstr.GetLength()))
					found = TRUE;
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
		stava = npos;
	}
	if (found)
	{
		if (npos <= 0)
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		if (input[npos - 1] != '(')
		{
			kstr.Format("no opening brace '(' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
	  int last = FindMatchingBrace(input, npos);
		if (last <= 0)
		{
			kstr.Format("no closing brace ')' found on '%s' !!", (LPCTSTR)input);
			throw kstr;
		}
		jstr = input.Mid((npos - 1), (last - npos + 1));
		ArgumentList(Arguments, jstr);
	}
	else
		Arguments.RemoveAll();
	if (Arguments.GetSize() < MinNoArguments)
	{
		jstr.Format("expected %1d or more arguments!!", MinNoArguments);
		throw jstr;
	}
}

BOOL CStrRout::CommandType(LPCTSTR instr, int start, BOOL exact, LPCTSTR str, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return FALSE;
	va_list marker;
	CString tstr,jstr;
	int pos,len1;
	int npos = CharPos(input, start);
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
//			pos = jstr.Find(tstr);
			pos = tstr.Find(jstr);
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
	return FALSE;
}

BOOL CStrRout::CommandType(LPCTSTR instr, va_list& InMarker, LPCTSTR str)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return FALSE;
	va_list marker;
	CString tstr,jstr;
	BOOL found = FALSE;
	int pos,npos;
	int stava = CharPos(input, 1);
	npos = NextCharacterGroup(input, tstr, stava);
	tstr.MakeUpper();
	memcpy(&marker, &InMarker, sizeof(va_list));
	jstr = str;
	jstr.MakeUpper();
	while( jstr[0] != '?' )
	{
//		pos = jstr.Find(tstr);
		pos = tstr.Find(jstr);
		if (pos == 0)
			return TRUE;
		jstr = va_arg( marker, LPCTSTR);
		jstr.MakeUpper();
	}
	va_end( marker );              /* Reset variable arguments.      */
	return FALSE;
}

BOOL CStrRout::CommandType(LPCTSTR instr, LPCTSTR str, ...)
{
	va_list marker;
	va_start(marker, str);     /* Initialize variable arguments. */
	return CommandType(instr, marker, str);
}

CString CStrRout::CommandParameters(LPCTSTR instr, LPCTSTR ignoreStr, ...)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return _T("");
	va_list marker;
	CString tstr,jstr;
	BOOL found = TRUE;
	int pos,npos;
	int stava = CharPos(input,1);
	stava = NextCharacterGroup(input, tstr, stava);
	npos = stava;
	while ((stava > 0) && (found)) 
	{
		found = FALSE;
		stava = NextCharacterGroup(input, tstr, stava);
		tstr.MakeUpper();
		va_start(marker, ignoreStr);     /* Initialize variable arguments. */
		jstr = ignoreStr;
		jstr.MakeUpper();
		while( jstr[0] != '?' )
		{
			pos = jstr.Find(tstr);
			if (pos == 0)
			{
				found = TRUE;
				npos = stava;
			}
			jstr = va_arg( marker, LPCTSTR);
			jstr.MakeUpper();
		}
		va_end( marker );              /* Reset variable arguments.      */
	}
	if (npos <= 0)
		return _T("");
	else
	{
		tstr = input.Right(input.GetLength() - npos + 1);
		tstr.TrimRight();
		return tstr;
	}
}

CString CStrRout::LabelFormat(LPCTSTR instr)
{
	CString input = instr;
	TrimString(input);
	int Length = input.GetLength();
	if (Length > 0)
	{
		TCHAR c1;
		c1 = input.GetAt(0);
		if ((97 <= c1) && (c1 <= 122))
		{
			c1 -= 32;
			input.SetAt(0, c1);
		}
		int i1;
		for (i1 = 1; i1 < Length; i1++)
		{
			c1 = input.GetAt(i1);
			if ((65 <= c1) && (c1 <= 90))
			{
				c1 += 32;
				input.SetAt(i1, c1);
			}
		}
	}
	return input;
}

CString CStrRout::CommandParameters(LPCTSTR instr)
{
	CString input = instr;
	if (input.GetLength() == 0)
		return _T("");
	CString tstr;
	int stava = CharPos(input,1);
	int npos = NextCharacterGroup(input, tstr, stava);
	if (npos <= 0)
		return _T("");
	else
	{
		tstr = input.Right(input.GetLength() - npos + 1);
		tstr.TrimRight();
		return tstr;
	}
}

int CStrRout::DecimalDigits(LPCTSTR instr)
{
	CString str = instr;
	str.TrimRight();
	int	pos = str.Find('.');
	if (pos > -1)
		return (str.GetLength() - pos - 1);
	else
		return 0;
}

CString CStrRout::Compress_E_Format(LPCTSTR instr)
{
	CString str = instr;
	str.TrimRight();
	str.TrimLeft();
	int	pos = str.FindOneOf("Ee");
	if (pos > -1)
	{
		if (str[pos + 1] != '0')
			pos++;
		CString jstr = str.Left(pos + 1);
		int len = str.GetLength();
		while ((str[pos + 1] == '0') && ((len - pos) > 2))
			pos++;
		CString kstr = str.Right(len - pos - 1);
		jstr += kstr;
		jstr.MakeUpper();
		return jstr;
	}
	else
		return str;
}

CString CStrRout::FormatCharacters(int width, int precision, TCHAR cf)
{
	TCHAR sf = '%';
	CString str;
	str.Format("%c%1d.%1d%c",sf,width,precision,cf);
	return str;
}

CString CStrRout::FormatCharacters(int width, TCHAR cf, BOOL Fixed /*= FALSE*/)
{
	TCHAR sf = '%';
	CString str;
	if (Fixed)
		str.Format("%c0%1d%c",sf,width,cf);
	else
		str.Format("%c%1d%c",sf,width,cf);
	return str;
}

BOOL CStrRout::SameString(LPCTSTR str1, LPCTSTR str2)
{
	CString jstr1 = str1;
	CString jstr2 = str2;
	TrimString(jstr1);
	TrimString(jstr2);
	if (jstr1 == jstr2)
		return TRUE;
	else
		return FALSE;
}

void CStrRout::TrimString(CString& inout)
{
	inout.TrimLeft();
	inout.TrimRight();
}

CString CStrRout::TrimLongBlanks(LPCTSTR input, int MaxBlank)
{
	CString kstr = input;
	TrimString(kstr);
	int Length = kstr.GetLength();
	CString output = _T("");
	int pos = 0;
	int blen = 0;
	TCHAR ch1;
	while (pos < Length)
	{
		ch1 = kstr[pos++];
		if (ch1 == 32)
			blen++;
		else
			blen = 0;
		if ((ch1 != 32) || (blen <= MaxBlank))
			output += ch1;
	}
	return output;
}

CString CStrRout::TrimTrailingZeros(LPCTSTR instr)
{
	CString kstr = instr;
	kstr.TrimRight();
	int zpos = kstr.Find(".");
	if (zpos >= 0)
	{
		int Length = kstr.GetLength();
		while ((TCHAR(kstr[Length - 1]) == '0') && (Length > (zpos + 2)))
			Length--;
		kstr = kstr.Left(Length);
	}
	return kstr;
}

CString CStrRout::TrimDecimals(LPCTSTR instr)
{
	CString kstr = instr;
	kstr.TrimRight();
	int zpos = kstr.Find(".");
	if (zpos >= 0)
		kstr = kstr.Left(zpos);
	return kstr;
}

CString CStrRout::ScrollEquation(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount, BOOL FloatValue)
{
	CString kstr = instr;
	TrimString(kstr);
	int Length = kstr.GetLength();
	if ((Length <= 0) || (nEndChar <= 0))
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	kstr = instr;
	kstr.TrimRight();
	Length = kstr.GetLength();
	int EndPos = min(nEndChar, Length);
	if (kstr[EndPos - 1] == ' ')
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	int Start,Stop;
	CString PreString = _T("");
	CString PostString = _T("");
	if (FindEnclosingBrace(Start, Stop, (LPCTSTR)kstr, EndPos))
	{
		PreString = kstr.Left(Start);
		PostString = kstr.Right(Length - Stop + 1);
		kstr = kstr.Mid(Start, (Stop - Start - 1));
		EndPos -= Start;
		Length = kstr.GetLength();
		EndPos = min(EndPos, Length);
	}
	int SignPosition = -1;
	TCHAR Sign = 0;
	BOOL AdditionOperator = FALSE;
	if (ThisNumberGroup(Start, Stop, (LPCTSTR)kstr, EndPos) == 0)
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	int len;
	if (Start > 1)
	{
		TCHAR c1 = kstr[Start - 2];
		if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)))
		{
			kstr = instr;
			nEndChar = -1;
			return kstr;
		}
		len = PreString.GetLength();
		PreString += kstr.Left(Start - 1);
		EndPos -= (Start - 1);
		int bpos = CharPrevious(kstr, (Start - 1));
		if (bpos > 0)
		{
			Sign = kstr[bpos - 1];
			CString mstr = "+-";
			if (mstr.Find(Sign) >= 0)
			{
				SignPosition = len + bpos;
				if (bpos > 1)
				{
					bpos = CharPrevious(kstr, (bpos - 1));
					if (bpos > 0)
					{
						TCHAR tch = kstr[bpos - 1];
						mstr = "([{*/";
						if (mstr.Find(tch) < 0)
							AdditionOperator = TRUE;
					}
				}
			}
		}
	}
	if (Stop < Length)
	{
		CString jstr = kstr.Right(Length - Stop) + PostString;
		PostString = jstr;
	}
	kstr = kstr.Mid((Start - 1), (Stop - Start + 1));
	int Exponent;
	double InValue = atof(kstr);
	int zpos = kstr.Find(".");
	if (zpos >= 0)
	{
		if (EndPos > zpos)
			Exponent = zpos - EndPos + 1;
		else
			Exponent = zpos - EndPos;
	}
	else
		Exponent = kstr.GetLength() - EndPos;
	if (!FloatValue)
	{
		zpos = -1;
		Exponent = 0;
	}
	double Fraction = exp(((double)Exponent) * log(10.0));
	double AbsValue = fabs(InValue) / Fraction;
	AbsValue = floor(AbsValue + 0.5);
	if ((SignPosition >= 0) && (Sign == '-'))
		AbsValue *= -1.0;
	switch (Arrow)
	{
		case 38:
			AbsValue += (max(1.0, (double)nCount));
			break;
		case 40:
			AbsValue -= (max(1.0, (double)nCount));
			break;
		default:
			break;
	}
	AbsValue *= Fraction;
	if (zpos >= 0)
	{
		int precision = max(1, -Exponent);
		int width = precision + 2;
		kstr.Format((LPCTSTR)FormatCharacters(width, precision, 'f'), fabs(AbsValue));
	}
	else
	{
		int width = max (0, Exponent) + 1;
		kstr.Format((LPCTSTR)FormatCharacters(width, 'd', TRUE), RoundInt(fabs(AbsValue)));
	}
	if (AdditionOperator)
	{
		if (AbsValue >= 0.0)
			PreString.SetAt((SignPosition - 1), '+');
		else
			PreString.SetAt((SignPosition - 1), '-');
	}
	else
	{
		if (AbsValue >= 0.0)
		{
			if (SignPosition >= 0)
			{
				CString mstr = PreString.Left(SignPosition - 1) + 
										PreString.Right(PreString.GetLength() - SignPosition);
				PreString = mstr;
			}
		}
		else
		{
			if (SignPosition >= 0)
				PreString.SetAt((SignPosition - 1), '-');
			else
				PreString += "-";
		}
	}

	Length = kstr.GetLength();
	if (Exponent <= -1)
		nEndChar = Length;
	else
	{
		nEndChar = Length - Exponent;
		if (zpos >= 0)
			nEndChar -= 2;
	}
	len = PreString.GetLength();
	if (len > 0)
	{
		nEndChar += len;
		kstr = PreString + kstr;
	}
	if (PostString.GetLength() > 0)
		kstr += PostString;
	return kstr;
}

CString CStrRout::ScrollDouble(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount)
{
	CString kstr = instr;
	TrimString(kstr);
	int Length = kstr.GetLength();
	if ((Length <= 0) || (nEndChar <= 0))
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	if (!Numeric(kstr))
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	kstr = instr;
	kstr.TrimRight();
	Length = kstr.GetLength();
	int EndPos = min(nEndChar, Length);
	if (kstr[EndPos - 1] == ' ')
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	int Exponent;
	double InValue = atof(kstr);
	int zpos = kstr.Find(".");
	if (zpos >= 0)
	{
		if (EndPos > zpos)
			Exponent = zpos - EndPos + 1;
		else
			Exponent = zpos - EndPos;
	}
	else
		Exponent = Length - EndPos;
	double Fraction = exp(((double)Exponent) * log(10.0));
	double AbsValue = fabs(InValue) / Fraction;
	AbsValue = floor(AbsValue + 0.5);
	if (InValue < 0.0)
		AbsValue *= -1.0;
	switch (Arrow)
	{
		case 38:
			AbsValue += (max(1.0, (double)nCount));
			break;
		case 40:
			AbsValue -= (max(1.0, (double)nCount));
			break;
		default:
			break;
	}
	AbsValue *= Fraction;
	int precision = max(1, -Exponent);
	int width = precision + 2;
	CString fstr = (" " + FormatCharacters(width, precision, 'f'));
	kstr.Format(fstr, AbsValue);
	Length = kstr.GetLength();
	if (Exponent <= -1)
		nEndChar = Length;
	else
		nEndChar = Length - 2 - Exponent;
	return kstr;
}

CString CStrRout::ScrollInteger(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount)
{
	CString kstr = instr;
	TrimString(kstr);
	int Length = kstr.GetLength();
	if ((Length <= 0) || (nEndChar <= 0))
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	if (!Numeric(kstr))
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	kstr = instr;
	kstr.TrimRight();
	Length = kstr.GetLength();
	int EndPos = min(nEndChar, Length);
	if (kstr[EndPos - 1] == ' ')
	{
		kstr = instr;
		nEndChar = -1;
		return kstr;
	}
	int Exponent;
	double InValue = atof(kstr);
	int zpos = kstr.Find(".");
	if (zpos >= 0)
	{
		if (EndPos > zpos)
			Exponent = zpos - EndPos + 1;
		else
			Exponent = zpos - EndPos;
	}
	else
		Exponent = Length - EndPos;
	Exponent = max(0, Exponent);
	double Fraction = exp(((double)Exponent) * log(10.0));
	double AbsValue = fabs(InValue) / Fraction;
	AbsValue = floor(AbsValue + 0.5);
	if (InValue < 0.0)
		AbsValue *= -1.0;
	switch (Arrow)
	{
		case 38:
			AbsValue += (max(1.0, (double)nCount));
			break;
		case 40:
			AbsValue -= (max(1.0, (double)nCount));
			break;
		default:
			break;
	}
	AbsValue *= Fraction;
	//kstr.Format(" %d", RoundInt(AbsValue));
	int width = max (0, Exponent) + 1;
	//CString fstr = (" " + FormatCharacters(width, 'd', TRUE));
	CString fstr = (" " + FormatCharacters(width, 0, 'f'));
	//kstr.Format(fstr, RoundInt(AbsValue));
	kstr.Format(fstr, AbsValue);
	Length = kstr.GetLength();
	nEndChar = Length - Exponent;
	return kstr;
}

CString CStrRout::TrimEformatZeros(LPCTSTR instr)
{
	CString kstr = instr;
	kstr.TrimRight();
	int zpos = kstr.FindOneOf("eE");
	if (zpos > 0)
	{
		int Length = kstr.GetLength();
		CString jstr = kstr.Left(zpos);
		jstr = TrimTrailingZeros((LPCTSTR) jstr);
		CString lstr = kstr.Right(Length - zpos);
		Length = lstr.GetLength();
		CString estr;
		zpos = lstr.FindOneOf("+-");
		if (zpos > 0)
			estr = lstr.Left(2);
		else
			estr = lstr.Left(1);
		lstr = lstr.Right(Length - zpos - 1);
		int value = atoi(lstr);
		lstr.Format("%d", value);
		kstr = jstr + estr + lstr;
	}
	return kstr;
}

void CStrRout::PadString(CString& inout, int Length)
{
	int len = inout.GetLength();
	while (len < Length)
	{
		inout += " ";
		len++;
	}
}

CString CStrRout::BreakLines(int& NoLines, CWnd* p_Parent, LPCTSTR LongStr, int LineLength)
{
	CString LongString = LongStr;
	TrimString(LongString);
	NoLines = 0;
	CString kstr = _T("");
	if (LongString.GetLength() == 0)
		return kstr;
	TEXTMETRIC tm; 
	CDC* p_dc = p_Parent->GetDC();
	HDC hdc = p_dc->GetSafeHdc();
	int* p_width = new int[128];
	GetCharWidth32(hdc, 0, 127, p_width);
	GetTextMetrics(hdc, &tm); 
	p_Parent->ReleaseDC(p_dc);
	NoLines = 1;
	CString jstr,rstr;
	TCHAR ch;
	int LastPos,afpos;
	int npos = 1;
	int mempos = 1;
	int ista = 1;
	int tpos = 0;
	int cfpos = 0;
	while (npos > 0)
	{
		mempos = npos;
		npos = NextConsecutiveCharacterGroup((LPCTSTR)LongString, rstr, npos);
		if (npos > 0)
			LastPos = npos;
		else
			LastPos = LongString.GetLength();
		afpos = 0;
		while (tpos < LastPos)
		{
			ch = (TCHAR)LongString[tpos];
			afpos += *(p_width + int(ch));
			tpos++;
		}
		if ((afpos + cfpos) > LineLength)
		{
			jstr.Format("%c%c ",13, 10);
			kstr += jstr;
			NoLines++;
			cfpos = 0;
		}
		cfpos += afpos;
		if (npos > 0)
			jstr = LongString.Mid((mempos - 1), (npos - mempos));
		else
			jstr = LongString.Right(LastPos - mempos + 1);
		kstr += jstr;
	}
	delete []p_width;
	return kstr;
}

int CStrRout::MetricPosition(LPCTSTR LongStr, LPCTSTR SubStr, int* p_width)
{
	CString LongString = LongStr;
	CString SubString = SubStr;
	int cfpos = LongString.Find(SubString);
	int pos = 0;
	int i1;
	TCHAR ch;
	for (i1 = 0; i1 < cfpos; i1++)
	{
		ch = (TCHAR)LongString[i1];
		pos += *(p_width + int(ch));
	}
	return pos;
}

int CStrRout::MetricEndPosition(LPCTSTR LongStr, LPCTSTR SubStr, int* p_width)
{
	CString LongString = LongStr;
	CString SubString = SubStr;
	int cfpos = LongString.Find(SubString);
	CString kstr = SubString;
	kstr.TrimRight();
	cfpos += min(SubString.GetLength(), (kstr.GetLength() + 1));
	int pos = 0;
	int i1;
	TCHAR ch;
	for (i1 = 0; i1 < cfpos; i1++)
	{
		ch = (TCHAR)LongString[i1];
		pos += *(p_width + int(ch));
	}
	return pos;
}

CString CStrRout::PrePadString(CString& input, int Num)
{
	CString kstr = _T("");
	int i1;
	//TCHAR ch1 = (TCHAR)0;
	for (i1 = 0; i1 < Num; i1++)
		kstr += " ";
	kstr += input;
	return kstr;
}

int CStrRout::WriteMemo(TCHAR* p_char, LPCTSTR instr, int MaxLength)
{
	CString input = instr;
	TrimString(input);
	int Length = input.GetLength();
	Length = min(Length, MaxLength);
	int i1;
	for (i1 = 0; i1 < Length; i1++)
		*(p_char + i1) = input[i1];
	if (Length < MaxLength)
		*(p_char + Length) = 0;
	return Length;
}

CString CStrRout::ReadMemo(TCHAR* p_char, int Length /*= -1*/)
{
	CString str = _T("");
	int i1;
	int len = Length;
	if (len < 0)
		len = strlen(p_char);
	for (i1 = 0; i1 < len; i1++)
		str += *(p_char + i1);
	return str;
}

int CStrRout::WriteStringBinary(CArchive& myFile, LPCTSTR input)
{
	CString wstr = input;
	int length = wstr.GetLength();
	TCHAR* p_char = new TCHAR[length + 2];
	int len = WriteMemo(p_char, wstr, (length + 2));
	myFile.Write(&len, 4);
	myFile.Write(p_char, len);
	delete []p_char;
	return len;
}

int CStrRout::WriteStringBinary(CFile& myFile, LPCTSTR input)
{
	CString wstr = input;
	int length = wstr.GetLength();
	TCHAR* p_char = new TCHAR[length + 2];
	int len = WriteMemo(p_char, wstr, (length + 2));
	myFile.Write(&len, 4);
	myFile.Write(p_char, len);
	delete []p_char;
	return len;
}

int CStrRout::ReadStringBinary(CArchive& myFile, CString& str)
{
	int len;
	myFile.Read(&len, 4);
	TCHAR* p_char = new TCHAR[len + 2];
	myFile.Read(p_char, len);
	str = ReadMemo(p_char, len);
	delete []p_char;
	return len;
}

int CStrRout::ReadStringBinary(CFile& myFile, CString& str)
{
	int len;
	myFile.Read(&len, 4);
	TCHAR* p_char = new TCHAR[len + 2];
	myFile.Read(p_char, len);
	str = ReadMemo(p_char, len);
	delete []p_char;
	return len;
}
