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


#define WM_WRITE_REQUEST (WM_USER + 3)

typedef struct
{
	CString FireFirst;
	CString PulseWidth;
	CString StepBack;
	CString SetBack;
	CString FireSecond;
	CString OutputModulo;
	CString OutputOffset;
} ChannelStringType;

typedef struct
{
	ChannelStringType	T0,A,B,C,D,E,F;
	CString ForceTrigger;
	CString RepCounter;
} VariableStringType;


class CDelgenControl
{
public:
	BOOL b_InitializeControl;
	BOOL b_RemoveControlThread;
	BOOL b_RequestRemoveControlThread;
	BOOL b_ControlThreadActive;
	BOOL b_ResetWhenDone;
	HANDLE	ControlNotification;
	HANDLE	ExitNotification;
	void UpdateDataPointer(CG0xData* p_G0xDat);
	void MainLoop();
  CDelgenControl(CWnd* pParent);
  ~CDelgenControl();

private:
	int SubCycleCount;
	BOOL SweepActive;
	BOOL FpgaMemoryActive;
	BOOL MovingUp;
	XParameterType TimeSequence;
	DWORD CalculateWait(struct _timeb& NextTime);
	void ResetChannelVariables(ChannelStringType& ChanStr);
	void ResetVariableString(VariableStringType* p_Mat);
	CString ExpandString(CString& ExpStr, int DelgenNo, VariableStringType* p_VarMat,
												double* p_Val, double* p_Mem, int FpgaPosition, 
												CTypedPtrList<CPtrList, DG_Type*>& m_List, TCHAR Cvar = 'D');
	void ReplaceChannelVariables(ChannelStringType& ChanStr, DelayChannelData& ChanData, 
											  int DelgenNo, ChannelLocationType& ChanLoc, VariableStringType* p_VarMat, 
												double* p_Val, CTypedPtrList<CPtrList, DG_Type*>& m_List);
	void ReplaceVariables(VariableStringType* p_VarMat, double* p_Val, 
																			CTypedPtrList<CPtrList, DG_Type*>& m_List);
	void LoadChannelVariables(ChannelStringType& ChanStr, DelayChannelData& ChanData, 
										  ChannelLocationType& ChanLoc, ChannelArithmeticType& ChanArith, double* p_Val);
	void ReduceDelayList(DelayChannelData& ChanData);
	void LoadFpgaVector(double* p_Mem, double* p_Val, int FpgaPosition);
	void LoadVariables(CTypedPtrList<CPtrList, DG_Type*>& m_List, int ListPosition);
	void DefineRWD(CTypedPtrList<CPtrList, DG_Type*>& m_List, BOOL RWD);
	int GetNextPosition(int PresentPosition);
	int TimeDifference(struct _timeb& NextTime, struct _timeb& ThisTime);
	void AddTime(struct _timeb& NextTime, struct _timeb& ThisTime, int MilliSeconds);
	void GetNextTime(struct _timeb& NextTime, struct _timeb& ThisTime);
	CTypedPtrList<CPtrList, DG_Type*> DG_List;
	void SetDelayGenerators(BOOL ResetCounters);
	void ResetEventCounters();
	BOOL ReadTriggerCounters();
	_int64 TriggerCount;
	CWnd* p_ParentWindow;
	CG0xData* p_G0xData;
};

