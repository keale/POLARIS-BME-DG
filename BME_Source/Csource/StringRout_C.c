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

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    5. January 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/


#include <stdlib.h>         /* For _MAX_PATH definition */
#include <malloc.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
//#include "..\Spectra_BME\CommonDefinitions.h"
#include "DG_DLL_1.h"


int CharPos(char* p_input, int start)
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

void GetSubstring(char* p_output, char* p_input, int start, int length)
{
	int i1;
	for (i1 = 0; i1 < length; i1++)
		*(p_output + i1) = *(p_input + start + i1);
	*(p_output + length) = 0;
}

int NextCharacterGroup(char* p_output, char* p_input, int start)
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
