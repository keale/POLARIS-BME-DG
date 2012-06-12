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
    Update:                    25. July 1997
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/



class CStrRout
{
public:

  CStrRout();
  ~CStrRout();
	CString WriteBinaryString(unsigned long input);
	CString WriteBinaryString(unsigned long* p_input, int Length);
	unsigned long ReadBinaryString(LPCTSTR instr);
	int ReadBinaryString(unsigned long* p_output, LPCTSTR instr, int MaxLength);
	unsigned long ReadHexadecimalString(LPCTSTR instr);
	int WriteMemo(TCHAR* p_char, LPCTSTR instr, int MaxLength);
	CString ReadMemo(TCHAR* p_char, int Length = -1);
	int WriteStringBinary(CArchive& myFile, LPCTSTR input);
	int WriteStringBinary(CFile& myFile, LPCTSTR input);
	int ReadStringBinary(CArchive& myFile, CString& str);
	int ReadStringBinary(CFile& myFile, CString& str);
	BOOL SameString(LPCTSTR str1, LPCTSTR str2);
	void TrimString(CString& inout);
	CString TrimLongBlanks(LPCTSTR input, int MaxBlank);
	void PadString(CString& inout, int Length);
	CString PrePadString(CString& input, int Num);
	CString BreakLines(int& NoLines, CWnd* p_Parent, LPCTSTR LongStr, int LineLength);
	int MetricPosition(LPCTSTR LongStr, LPCTSTR SubStr, int* p_width);
	int MetricEndPosition(LPCTSTR LongStr, LPCTSTR SubStr, int* p_width);
	CString ScrollEquation(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount, BOOL FloatValue = TRUE);
	CString ScrollDouble(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount);
	CString ScrollInteger(LPCTSTR instr, int& nEndChar, UINT Arrow, UINT nCount);
	CString TrimTrailingZeros(LPCTSTR instr);
	CString TrimDecimals(LPCTSTR instr);
	CString TrimEformatZeros(LPCTSTR instr);
	int CharPos(LPCTSTR input, int start);
	int CharPrevious(LPCTSTR input, int start);
	BOOL CompareChar(TCHAR ci, TCHAR cr, ...);
	int CLetPos(LPCTSTR input, int start);
	int CLetPos(LPCTSTR input, int start, TCHAR cr, ...);
	int CharIndex(LPCTSTR input, int start, TCHAR cr, ...);
	BOOL EthernetAddress(LPCTSTR input);
	BOOL Numeric(LPCTSTR input);
	BOOL NonNumeric(LPCTSTR input);
	BOOL Numeric(TCHAR ci);
	BOOL NonNumeric(TCHAR ci);
	int NextVar(LPCTSTR instr, CString& output, int start);
	void NextKeyPosition(LPCTSTR instr, int& npos, int& endvar, TCHAR cr, ...);
	int PreviousCharacterGroup(LPCTSTR instr, CString& output, int start);
	int NextLabel(LPCTSTR instr, CString& output, int start);
	int ThisNumberGroup(int& Start, int& Stop, LPCTSTR instr, int inpos);
	int NumberCharacterGroups(LPCTSTR instr);
	int NextCharacterGroup(LPCTSTR instr, CString& output, int start);
	int NextConsecutiveCharacterGroup(LPCTSTR instr, CString& output, int start);
	int ReadNumberVector(LPCTSTR instr, int* output, int lenmax);
	BOOL XParameter(CString& input);
	BOOL XParameterExist(LPCTSTR instr);
	int PreCommandPosition(LPCTSTR instr, CString& output, int start, BOOL exact, LPCTSTR str, ...);
	int NextCommandPosition(LPCTSTR instr, CString& output, int start, BOOL exact, LPCTSTR str, ...);
	void EliminateKeyWords(CString& input, int start, LPCTSTR str, ...);
	BOOL CommandPresent(LPCTSTR instr, int start, BOOL exact, LPCTSTR str, ...);
	CString WriteIntegerArray(int* p_int, int Length);
	int ReadIntegerArray(int* p_int, int MaxNumber, LPCTSTR instr);
	void DataSetsPresent(CUIntArray& DSet, LPCTSTR instr);
	int DataSetNumber(LPCTSTR instr);
	void FindReplaceString(CString& wstr, LPCTSTR FindStr, LPCTSTR ReplaceStr);
	BOOL ExtractOperationTerm(CString& input, CString& output, 
														CStringArray& Arguments, BOOL Remove, LPCTSTR str, ...);
	BOOL RemoveOuterBracket(LPCTSTR instr, CString& output);
	BOOL FindBracketTerm(LPCTSTR instr, CString& output);
	CString EvaluateString(CString& CommandLine);
	CString EvaluateOperationString(CStringArray& Arguments);
	CString EvaluateBaseString(CString& CommandLine);
	BOOL ExtractBaseTerm(CString& input, CString& output, BOOL Remove);
	BOOL ExtractFunction(CString& input, CString& output, BOOL Remove, BOOL exact, LPCTSTR str, ...);
	BOOL FindFunction(LPCTSTR instr, CString& output, 
																	int start, int& nextpos, BOOL exact, va_list& marker, LPCTSTR str);
	BOOL FindFunction(LPCTSTR instr, CString& output, 
										int start, int& nextpos, BOOL exact, LPCTSTR str, ...);
	int StringList(CStringArray& output,  LPCTSTR str, ...);
	CString GetCompositionString(LPCTSTR instr);
	CString GetVariableString(LPCTSTR instr);
	CString CombineCompositionAndVariable(LPCTSTR Composition, LPCTSTR Variable);
	BOOL FindEnclosingBrace(int& Start, int& Stop, LPCTSTR instr, int inpos);
	int FindMatchingBrace(LPCTSTR instr, int inpos);
	BOOL CheckBraceMatch(LPCTSTR instr, int ErrorAction = DisplayMessageBox);
	BOOL FindReplaceDataSet(CString& DataDef, CString& CommandLine, int FuncNo);
	BOOL FindReplaceDataSet(CString& DataDef, double& Multiplier, CString& CommandLine, int FuncNo);
	BOOL SubstanceSequence(LPCTSTR CommandLine);
	BOOL CheckIsotopeDefinition(LPCTSTR CommandLine, int ErrorAction = DisplayMessageBox);
	CString AddCommas(LPCTSTR instr);
	void ArgumentList(CStringArray& Arguments, LPCTSTR instr);
	void ArgumentList(CStringArray& Arguments, LPCTSTR instr, BOOL exact, LPCTSTR str, ...);
	void ArgumentList(CStringArray& Arguments, LPCTSTR instr, BOOL exact, 
																										int MinNoArguments, LPCTSTR str, ...);
	double DefaultArgument(double DefaultValue, CStringArray& Arguments, int ArgumentNo);
	TCHAR DefaultArgument(TCHAR DefaultValue, CStringArray& Arguments, int ArgumentNo);
	int DefaultArgument(int DefaultValue, CStringArray& Arguments, int ArgumentNo) ;
	CString DefaultArgument(LPCTSTR DefaultValue, CStringArray& Arguments, int ArgumentNo) ;
	BOOL CommandType(LPCTSTR instr, int start, BOOL exact, LPCTSTR str, ...);
	BOOL CommandType(LPCTSTR instr, LPCTSTR str, ...);
	BOOL CommandType(LPCTSTR instr, va_list& InMarker, LPCTSTR str);
	CString CommandParameters(LPCTSTR instr, LPCTSTR ignoreStr, ...);
	CString CommandParameters(LPCTSTR instr);
	int DecimalDigits(LPCTSTR instr);
	CString Compress_E_Format(LPCTSTR instr);
	CString FormatCharacters(int width, int precision, TCHAR cf);
	CString FormatCharacters(int width, TCHAR cf, BOOL Fixed = FALSE);
	BOOL CheckResult(LPCTSTR instr, LPCTSTR CommandLine);
	int ReadString(CStdioFile& myFile, int* p_int, ...);
	int ReadString(CStdioFile& myFile, double* p_double, ...);
	CString LabelFormat(LPCTSTR instr);
};
