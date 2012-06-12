/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 File Routines for Alpha Format
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
    Update:                    25. July 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#define XStart					10
#define YStart					10

#define YStep						20
#define YLargeStep			20
#define YSmallStep			16

#define RegularFont						0
#define MinorHeadingFont			1
#define HeadingFont						2
#define LargeHeadingFont			3

class CDelgenData
{
public:
  CDelgenData();
  ~CDelgenData();
	CSize WriteDelgenSetup(CG0xData* p_G0xData, CClientDC* p_ClientDC, 
																				CPoint ScrollPosition, CSize PreviousDataSize);
private:
	void NewLine();
	void HalfLine();
	void ResetLinePosition(CPoint ScrollPosition);
	void SetPrivateFont(CClientDC* p_ClientDC, int FontNumber);
	void WriteLine(CString& kstr, CSize& TextExtent, CSize& LineExtent, CClientDC* p_ClientDC);
	void WriteChannelVariables(CString& ChanStr, DelayChannelData& ChanData, BOOL FpgaMemoryExist,
														CG0xData* p_G0xData, DG_Type* p_DG, ChannelLocationType& ChanLoc,
														CSize& TextExtent, CSize& LineExtent, CClientDC* p_ClientDC);
	//void LoadDelgenTable();
	int XPosition,XLeft;
	int YPosition;
	int PresentYStep;
	CFont* p_RegularFont;
	CFont* p_HeadingFont;
	CFont* p_MinorHeadingFont;
	CFont* p_LargeHeadingFont;
	CStringArray ConfigurationTable;
};

