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



class CStringRout
{
public:
	CStringRout();
	~CStringRout();
	void TrimTrailingZeros(char* p_word);
	void TrimString(char* p_word);
	unsigned long ReadHexadecimalString(char* p_input);
	BOOL CompareChar(char ci, char cr, ...);
	char ReadChar(char* p_question);
	int CharPos(char* p_input, int start);
	void GetSubstring(char* p_output, char* p_input, int start, int length);
	int NextCharacterGroup(char* p_output, char* p_input, int start);
};

