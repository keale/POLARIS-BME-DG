/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 DG 135 driver
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      C 
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    5. January 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/


#if (defined(server) || defined(D0xConsole))
	#define		StringRout_Header			"stdafx2.h"
#else
	#define		StringRout_Header			"stdafx.h"
#endif

#include StringRout_Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <conio.h>
#include <stdio.h>
#if (defined(D0xConsole) || defined(server))
	#include <windows.h>
#endif
#include "StringRout.h"




CStringRout::CStringRout()
{
}

CStringRout::~CStringRout()
{
}

unsigned long CStringRout::ReadHexadecimalString(char* p_input)
{
	unsigned long test;
	unsigned long result;
	BOOL EndPoint;
	int i1,Count,Length;
	char ch;
	EndPoint = FALSE;
	Length = strlen(p_input);
	test = 0x1;
	result = 0;
	Count = 0;
	i1 = (Length - 1);
	while ((i1 >= 0) && (Count < 8) && (!EndPoint))
	{
		ch = *(p_input + i1);
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

void CStringRout::TrimString(char* p_word)
{
	int len,pos;
	len = strlen(p_word);
	pos = len - 1;
	while ((*(p_word + pos) == 32) && (pos >= 0))
	{
		*(p_word + pos) = 0;
		pos--;
		len--;
	}
	while ((*p_word == 32) && (len > 0))
	{
		for (pos = 1; pos <= len; pos++)
			*(p_word + pos - 1) = *(p_word + pos);
		len--;
	}
}

void CStringRout::TrimTrailingZeros(char* p_word)
{
	int len,pos;
	char *pdest;
	len = strlen(p_word);
	pos = len - 1;
	while ((*(p_word + pos) == 32) && (pos >= 0))
	{
		*(p_word + pos) = 0;
		pos--;
		len--;
	}
	pdest = strrchr(p_word, '.' );
  pos = pdest - p_word;
	while ((*(p_word + len - 1) == '0') && (len > (pos + 2)))
	{
		*(p_word + len - 1) = 0;
		len--;
	}
}

BOOL CStringRout::CompareChar(char ci, char cr, ...)
{
	BOOL match = FALSE;
	char ct = 0;
  char ci1 = ci;
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
    ct = va_arg( marker, char);
	}
  va_end( marker );              /* Reset variable arguments.      */
	return match;
}


int CStringRout::CharPos(char* p_input, int start)
{
	BOOL found;
	int i1,Len;
	char c1;
	found = FALSE;
	i1 = max(0, start);
	Len = strlen(p_input);
	while ((!found) && (i1 < Len))
	{
		c1 = *(p_input + i1);
		if ((c1 > 32) && (c1 < 127))
			found = TRUE;
		else
			i1++;
	}
	if (!found)
		i1 = -1;
	return i1;
}

char CStringRout::ReadChar(char* p_question)
{
	char answer;
	printf(p_question);
	answer = _getch();
	printf("%c\n", answer);
	//scanf("%s", &answer);
	return answer;
}

void CStringRout::GetSubstring(char* p_output, char* p_input, int start, int length)
{
	int i1;
	for (i1 = 0; i1 < length; i1++)
		*(p_output + i1) = *(p_input + start + i1);
	*(p_output + length) = 0;
}

int CStringRout::NextCharacterGroup(char* p_output, char* p_input, int start)
{
	int stava,len1,i1;
	char c1;
	BOOL found;
	len1 = strlen(p_input);
	if (len1 <= 0)
		return -1;
	stava = CharPos(p_input, start);
	if (stava >= 0)
	{
		i1 = stava;
		found = TRUE;
		c1 = *(p_input + i1);
		if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)))
		{
			while ((found) && (i1 <= len1))
			{
				c1 = *(p_input + i1);
				if (((65 <= c1) && (c1 <= 90)) || ((97 <= c1) && (c1 <= 122)) ||
									((48 <= c1) && (c1 <= 57)) || (c1 == 95))
					i1++;
				else
					found = FALSE;
			}
			GetSubstring(p_output, p_input, stava, (i1 - stava));
			return CharPos(p_input, i1);
		}
		if (((48 <= c1) && (c1 <= 57)) || (c1 == 43) || (c1 == 45) || (c1 == 46))
		{
			while ((found) && (i1 <= len1))
			{
				c1 = *(p_input + i1);
				if (((48 <= c1) && (c1 <= 57)) || (c1 == 43) || (c1 == 45) || (c1 == 46) || 
													((65 <= c1) && (c1 <= 70)) || ((97 <= c1) && (c1 <= 102)) ||
													(c1 == 88) || (c1 == 120))
					i1++;
				else
					found = FALSE;
			}
			found = TRUE;
			while ((found) && (i1 > stava))
			{
				c1 = *(p_input + i1 - 1);
				if ((i1 > (stava + 1)) && ((c1 == 43) || (c1 == 45) || (c1 == 69) || (c1 == 101)))
					i1--;
				else
					found = FALSE;
			}
			GetSubstring(p_output, p_input, stava, (i1 - stava));
			return CharPos(p_input, i1);
		}
		if (c1 == 42)
		{
			while ((found) && (i1 <= len1))
			{
				c1 = *(p_input + i1);
				if (c1 == 42)
					i1++;
				else
					found = FALSE;
			}
			GetSubstring(p_output, p_input, stava, (i1 - stava));
			return CharPos(p_input, i1);
		}
		GetSubstring(p_output, p_input, stava, 1);
		return CharPos(p_input, (i1 + 1));
	}
	GetSubstring(p_output, p_input, 0, len1);
	return -1;
}
