/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel.   08841 - 5487
		Fax.   08841 - 90134
		email: bme-bergmann@t-online.de
		web:   http://www.bme-bergmann.de

    module:										 main data structures for BME_G0x
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
    Update:                    17. February 2001
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

#include <afxtempl.h>
#include "DG_DLL.h"


#define MaxTSParameter	8

typedef struct
{
	union
	{
		BOOL	Flag[MaxTSParameter];
		struct
		{
			BOOL	m_Continuously;
			BOOL	m_BothDirection;
			BOOL	m_Downwards;
			BOOL	m_Once;
			BOOL	m_Upwards;
			BOOL	m_SubcycleLimit;
		};
	};
	union
	{
		int	IntNumber[MaxTSParameter];
		struct
		{
			int	MilliSecondsPerStep;
			int	MaxSubcycles;
		};
	};
} XParameterType;

typedef struct
{
	double* p_Value;
	int* p_Loc;
	int NoParameters;
	int ListLength;
} ParameterListType;

typedef struct
{
	char FireFirst[64];
	char SetBack[64];
	char FireSecond[64];
} ChannelArithmeticV1Type;

typedef struct
{
	char FireFirst[64];
	char SetBack[64];
	char FireSecond[64];
	char OutputModulo[64];
} ChannelArithmeticV2Type;

typedef struct
{
	char FireFirst[64];
	char SetBack[64];
	char PulseWidth[64];
	char OutputModulo[64];
	char OutputOffset[64];
} ChannelArithmeticV3Type;

typedef struct
{
	char FireFirst[64];
	char SetBack[64];
	char PulseWidth[64];
	char OutputModulo[64];
	char OutputOffset[64];
	char StepBack[64];
} ChannelArithmeticType;

typedef struct
{
	ChannelArithmeticV1Type	T0,A,B;
} VariableArithmeticV1Type;

typedef struct
{
	ChannelArithmeticV2Type	T0,A,B;
} VariableArithmeticV2Type;

typedef struct
{
	ChannelArithmeticV3Type	T0,A,B;
	char ForceTrigger[64];
	char RepCounter[64];
} VariableArithmeticV3Type;

typedef struct
{
	ChannelArithmeticType	T0,A,B,C,D,E,F;
	char ForceTrigger[64];
	char RepCounter[64];
} VariableArithmeticV4Type;

typedef struct
{
	ChannelArithmeticType	T0,A,B,C,D,E,F;
	char ForceTrigger[64];
	char RepCounter[64];
	char RepSecondary[64];
} VariableArithmeticType;

typedef struct
{
	int FireFirst,SetBack,FireSecond;
} ChannelLocationV1Type;

typedef struct
{
	int FireFirst;
	int SetBack;
	int FireSecond;
	int OutputModulo;
} ChannelLocationV2Type;

typedef struct
{
	int FireFirst;
	int SetBack;
	int PulseWidth;
	int OutputModulo;
	int OutputOffset;
} ChannelLocationV3Type;

typedef struct
{
	int FireFirst;
	int SetBack;
	int PulseWidth;
	int OutputModulo;
	int OutputOffset;
	int StepBack;
} ChannelLocationType;

typedef struct
{
	ChannelLocationV1Type	T0,A,B;
} VariableLocationV1Type;

typedef struct
{
	ChannelLocationV2Type	T0,A,B;
} VariableLocationV2Type;

typedef struct
{
	ChannelLocationV3Type	T0,A,B;
	int ForceTrigger;
	int RepCounter;
} VariableLocationV3Type;

typedef struct
{
	ChannelLocationType	T0,A,B,C,D,E,F;
	int ForceTrigger;
	int RepCounter;
} VariableLocationV4Type;

typedef struct
{
	ChannelLocationType	T0,A,B,C,D,E,F;
	int ForceTrigger;
	int RepCounter;
	int RepSecondary;
} VariableLocationType;

typedef struct
{
	DG_BME_Control_V1				Control;
	VariableLocationV1Type	VarLoc;
	char										DG_Name[32];
	char										T0_Name[32];
	char										A_Name[32];
	char										B_Name[32];
	BOOL										ReadTriggers;
	BOOL										Master;
	int											BaseAddress;
	int											Product;
} Old_DG_Type;

typedef struct
{
	DG_BME_Control_V1					Control;
	VariableLocationV1Type		VarLoc;
	VariableArithmeticV1Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BaseAddress;
	int												Product;
} DG_V1_Type;

typedef struct
{
	DG_BME_Control_V1					Control;
	VariableLocationV2Type		VarLoc;
	VariableArithmeticV2Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BaseAddress;
	int												Product;
} DG_V2_Type;

typedef struct
{
	DG_BME_Control_V2					Control;
	VariableLocationV2Type		VarLoc;
	VariableArithmeticV2Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BaseAddress;
	int												Product;
} DG_V3_Type;

typedef struct
{
	DG_BME_Control_V3					Control;
	VariableLocationV3Type		VarLoc;
	VariableArithmeticV3Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BaseAddress;
	int												Product;
} DG_V4_Type;

typedef struct
{
	DG_BME_Control_V3					Control;
	VariableLocationV3Type		VarLoc;
	VariableArithmeticV3Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BusNumber;
	int												SystemNumber;
	union
	{
		int												BaseAddress;
		int												SlotNumber;
	};
	int												Product;
} DG_V5_Type;

typedef struct
{
	DG_BME_Control_V4					Control;
	VariableLocationV4Type		VarLoc;
	VariableArithmeticV4Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	char											C_Name[32];
	char											D_Name[32];
	char											E_Name[32];
	char											F_Name[32];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BusNumber;
	int												SystemNumber;
	union
	{
		int												BaseAddress;
		int												SlotNumber;
	};
	int												Product;
} DG_V6_Type;

typedef struct
{
	DG_BME_Control_V4					Control;
	VariableLocationV4Type		VarLoc;
	VariableArithmeticV4Type	VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	char											C_Name[32];
	char											D_Name[32];
	char											E_Name[32];
	char											F_Name[32];
	char											ip_address[40];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BusNumber;
	int												SystemNumber;
	union
	{
		int												BaseAddress;
		int												SlotNumber;
	};
	int												Product;
} DG_V7_Type;

typedef struct
{
	DG_BME_Control						Control;
	VariableLocationType			VarLoc;
	VariableArithmeticType		VarEqu;
	char											DG_Name[32];
	char											T0_Name[32];
	char											A_Name[32];
	char											B_Name[32];
	char											C_Name[32];
	char											D_Name[32];
	char											E_Name[32];
	char											F_Name[32];
	char											ip_address[40];
	BOOL											ReadTriggers;
	BOOL											Master;
	int												BusNumber;
	int												SystemNumber;
	union
	{
		int												BaseAddress;
		int												SlotNumber;
	};
	int												Product;
} DG_Type;


typedef struct
{
	union
	{
		_int64								Trigger64Events;
		unsigned long					TriggerEvents;
	};
	unsigned long					DG_Status;
} OpInfo_Type;


typedef struct
{
	int nVersion;
	CString CalibrationFilePath;
} FileOptionsType;

class CG0xData : public CObject 
{
public:
	CG0xData(int sdata );
	~CG0xData( );
protected:
	CG0xData( );
	DECLARE_SERIAL( CG0xData )
public:
	virtual void Serialize( CArchive& ar );
	CPoint ScrollPosition;
	BOOL b_ContextHelpActive;
	BOOL b_CalibrateTiming;
	BOOL b_RequestZeroModulo;
	BOOL b_RequestJumpStart;
	unsigned long m_CalibrationLevel;
	ParameterListType	ParameterList;
	ParameterListType	FpgaMemoryList;
	int m_ActiveIndex;
	int nVersion;
	CClientDC* p_ClientDC;

	CRITICAL_SECTION* p_DataAccess;
	void DeleteData();
	void ResetData();
	CString GetFileName();
	CString GetFileTitle();
	CString GetFileTime();
	CSize WriteExperimentalSetup();

	CDG_DLL* p_DelayGenerator;
	BOOL b_DelayGeneratorsInitialized;
	BOOL b_DelayGeneratorsActive;
	BOOL VariablesExist();
	BOOL FpgaMemoryExist();
	BOOL MemoryReferenceExist();
	void ResetOutOfRangeVariables();
	unsigned long ModifyAction(CTypedPtrList<CPtrList, DG_Type*>& m_List);
	void SetDelayGenerators(CTypedPtrList<CPtrList, DG_Type*>& m_List);
	BOOL AllDelayGeneratorsDone(CTypedPtrList<CPtrList, DG_Type*>& m_List);
	void ResetEventCounter(int DG_Number);
	void ResetOutputModuloCounters(int DG_Number);
	void ResetAllOutputModuloCounters();
	void LoadAllCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);
	void ResetCounterAllCards(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);
	void JumpStartAllLists();
	unsigned long ReadTriggerCounter(int DG_Number);
	void ReadFrequencyCounter(double* p_result, int DG_Number);
	void Read64BitTriggerCounter(_int64* p_result, int DG_Number);
	unsigned long Read_DG_Status(int DG_Number);
	long AddEthernetDelayGenerators(long* p_Error, char* p_IpAddr);
	long DetectPciDelayGenerators(long* p_Error);
	long GetEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																																								BOOL* p_Master, long DG_Number);
	long GetUnconnectedEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																																						long* p_LineMaster, long DG_Number);
	void InitializeDelayGenerators();
	void ActivateDelayGenerators();
	void DeactivateDelayGenerators();
	time_t							m_FileTime;
	CTypedPtrList<CPtrList, DG_Type*> m_DG_List;
	CTypedPtrList<CPtrList, DG_Type*> m_Show_List;
	OpInfo_Type* p_OpInfo;
	FileOptionsType FileOptions;
	void CopyDG_List(CTypedPtrList<CPtrList, DG_Type*>& out_List,
													 CTypedPtrList<CPtrList, DG_Type*>& in_List);
	void InitializeDG_List(CTypedPtrList<CPtrList, DG_Type*>& DG_List);
	void ResetDG_Element(DG_Type* p_DG);
	double RoundRepCounter(double InValue, int DG_Number);
	double RoundT0(double InValue, int DG_Number);
	double RoundWidth(double InValue, int DG_Number);
	double RoundGateDelay(double InValue, int DG_Number);
	double RoundSetBack(double InValue, int DG_Number);
	double DelayLimit(double InValue, int DG_Number);
	CString AllowedParameter(LPCTSTR istr);

	int WriteXParameter(CStringArray& csa, XParameterType& vct);
	int ReadXParameter(CStringArray& csa, XParameterType& vct);
	int WriteFpgaMemory(CStringArray& csa);
	int ReadFpgaMemory(CStringArray& csa);
	void ResetTimeSequence(XParameterType& vct);
	void ReadTimeSequence(XParameterType& vct);
	void SaveParameters(LPCTSTR FileName);


private:
	unsigned long					TestCounter;
	CString								m_FileName;
	CString								m_FileTitle;
	CSize									ExperimentalDataSize;
	int										b_ExperimentalSetupAccess;
	CStringArray					m_XParameter;
	CStringArray					m_FpgaMemory;
	XParameterType				m_TimeSequence;
	void CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV1Type* p_V1_A);
	void CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV2Type* p_V2_A);
	void CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV3Type* p_V3_A);
	void CopyArithmetic(VariableArithmeticType* p_A, VariableArithmeticV4Type* p_V4_A);
	void CopyLocation(VariableLocationType* p_L, VariableLocationV1Type* p_V1_L);
	void CopyLocation(VariableLocationType* p_L, VariableLocationV2Type* p_V2_L);
	void CopyLocation(VariableLocationType* p_L, VariableLocationV3Type* p_V3_L);
	void CopyLocation(VariableLocationType* p_L, VariableLocationV4Type* p_V4_L);
	void CopyDG_Element(DG_Type* p_DG, Old_DG_Type* p_Old_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V1_Type* p_V1_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V2_Type* p_V2_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V3_Type* p_V3_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V4_Type* p_V4_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V5_Type* p_V5_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V6_Type* p_V6_DG);
	void CopyDG_Element(DG_Type* p_DG, DG_V7_Type* p_V7_DG);
	void ResetInternalData();
	void WriteDG_List( CArchive& myFile, CTypedPtrList<CPtrList, DG_Type*>& DG_List);
	void ReadDG_List( CArchive& myFile, CTypedPtrList<CPtrList, DG_Type*>& DG_List);
	void ResetChannelLocation(ChannelLocationType& ChanLoc);
	void ResetLocation(VariableLocationType& VarLoc);
	void ResetChannelArithmetic(ChannelArithmeticType& ChanEqu);
	void ResetArithmetic(VariableArithmeticType& VarEqu);
	BOOL LoadParameterList(ParameterListType& plt, CStringArray& csa);
	void TestLoadDelayGenerator(DG_BME_Control* p_BDG, long DG_Number);
	BOOL ChannelFpgaMemoryExist(ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith);
	BOOL ChannelVariablesExist(ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith);
	BOOL ContainsVariables(CStringArray& csa);
	
protected:
	int m_dtyp;
};
