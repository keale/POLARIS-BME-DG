/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Hagener Leite 24
		D-82418 Murnau

		Tel. +49-8841-487769-1
		Fax. +49-8841-487769-9

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
    Version:                   V1.1
    Update:                    18. February 2005
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/



#define  WINDOWSNT
#undef  WINDOWS95
#undef  WINDOWS31


#if (!defined(server) && !defined(D0xConsole))
	#include "PlxRout.h"
#endif


typedef struct 
{
  unsigned short base_address,CommandAddress;
  unsigned short CounterControlAddress,InterruptEnableAddress;
  unsigned short InterruptAcknowledgeAddress,InitializeAddress,PrescalerAddress;
	unsigned short Counter,Counter_N,Counter_K,Counter_J,Counter_cntrl;
  unsigned short Delay,Delay_T0,Delay_Aux,Delay_cntrl;
  unsigned short Delay_A,Delay_B,Delay_C,Delay_D,Delay_E,Delay_F;
  unsigned short Modulo_A,Modulo_B,Modulo_C,Modulo_D,Modulo_E,Modulo_F;
	unsigned short SecondaryCounterAddress,ModuloCounterAddress;
	unsigned short TriggerCounterAddress,FrequencyCounterAddress;
  unsigned short Large,Large_T0,Large_A,Large_B,Large_cntrl;
	unsigned short DAC,DAC_T0,DAC_A,DAC_B,Serial_DAC;
	unsigned short InterruptEnableRegister;
	unsigned long CommandRegister,CommandRegisterState;
	unsigned long CounterControlRegister[6];
	unsigned long CounterControlState[6];
	unsigned long PrescalerState[4];
	union
	{
		double	IniTime[16];
		struct
		{
			double ZeroTime;
			double p1Time;
			double p2Time;
			double ResetTime;
			double TimeIncrement;
			double T0_Increment;
			double A_Increment;
			double B_Increment;
			double TriggerIncrement;
			double C_Increment;
			double D_Increment;
			double E_Increment;
			double F_Increment;
			double OscillatorIncrement;
		};
	};
	double TenMhzZeroTime;
	double TenMhzp1Time;
	double TenMhzp2Time;
	double TenMhzResetTime;
	double InternalOscillatorFrequency;
	double ExternalOscillatorFrequency;
	BOOL b_DG_Activated,b_ModuleCalibrated;
	unsigned long CalibrationLevel;
	unsigned long DG_Product;
	unsigned long LoadVector;
	DG_BME_Registers	DelayGeneratorState;
	DG_BME_Control		DelayControlState;
	BOOL NtDriverInitialized;
  HANDLE h_DelayGenerator;
	DelgenType PciDelgen;
	char ip_address[40];
	long BusNumber;
	long SlotNumber;
	void* p_Master;
} DG_InternalData;



class CDG_DLL
{

	union
	{
		double	CalibrationConstant[32];
		struct
		{
			double SG02_ZeroTime;
			double SG02_p1Time;
			double SG02_p2Time;

			double SG02V2_p1Time;
			double SG02V2_p2Time;

			double SG02V1_GoTime;
			double SG02V1_p1Time;
			double SG02V1_p2Time;

			double G02_ZeroTime;
			double G02_p1Time;
			double G02_p2Time;

			double G03_ZeroTime;
			double G03_p1Time;
			double G03_p2Time;
			double G03_ResetTime;

			double ClockDelay;
			double TriggerDelay;

			double InternalOscillator;
			double ExternalOscillator;
		};
	} CalData;


	DG_InternalData* p_Internal;
	int NoDelayGenerators;
	int NumberPciDelayGenerators;
	DelgenType PciDelgen[40];

	void IsaOutByte(unsigned short Address, unsigned char value);
	unsigned char IsaInByte(unsigned short Address);
	void InitializeInternalData(DG_InternalData* p_Present);
	void Set_Delay_Trigger(DelayTriggerType* p_dt, unsigned long* p_LoadWord, DG_InternalData* p_Present);
	void SetDelayTriggerControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																	DelayTriggerType* p_dt, DG_InternalData* p_Present);
	void Set_Prescaler(DG_BME_Registers* p_pdg, unsigned long* p_LoadWord, DG_InternalData* p_Present);
	void Set_Main_Counter(MainCounterType* p_mc, DG_InternalData* p_Present);
	void SetMainCounterControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																	MainCounterType* p_mc, DG_InternalData* p_Present);
	void Set_Reference_channel(DelayChannel* p_rf, DG_InternalData* p_Present);
	void SetReferenceControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																DelayChannel* p_rf, DG_InternalData* p_Present);
	void Set_Delay_channel(DelayChannel* p_k, DelayChannel* p_m, short int pos, DG_InternalData* p_Present);
	void Set_Delay_channel_SG05P4(DelayChannel* p_k, DelayChannel* p_ChState, unsigned long* LoadWord,
																								unsigned short pos, DG_InternalData* p_Present);
	void SetDelayControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
				DelayChannel* p_k, DelayChannel* p_ChState, short int pos, DG_InternalData* p_Present);
	void SetDelayControl_SG05P4(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
				DelayChannel* p_k, DelayChannel* p_ChState, short int pos, DG_InternalData* p_Present);
	void Synchronize_DG_State(long DG_Number);
	void HardwareTest_BME_G03(long DG_Number);
	void HardwareTest_BME_G02(long DG_Number);
	void LoadPrescaler(unsigned long* p_value, DG_InternalData* p_Present);
	void LoadCommandRegister(unsigned long* p_value, DG_InternalData* p_Present);
	void LoadCounterControl(unsigned long* p_value, DG_InternalData* p_Present);
	void PrepareCounterControl(DG_BME_Registers* p_pdg, unsigned long* p_LoadWord, DG_InternalData* p_Present);

	void ActionDC(unsigned long* p_Action, DelayChannelData* p_a, DelayChannelData* p_b, unsigned long DG_Product);
	void ActionDT(unsigned long* p_Action, DelayTriggerData* p_a, DelayTriggerData* p_b, unsigned long DG_Product);
	BOOL IsEqualDT(DelayTriggerType* p_a, DelayTriggerType* p_b, unsigned long DG_Product);
	BOOL IsEqualMC(MainCounterType* p_a, MainCounterType* p_b, unsigned long DG_Product);
	BOOL IsEqualDC(DelayChannel* p_a, DelayChannel* p_b, unsigned long DG_Product);
	BOOL IsEqualPS(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product);
	BOOL IsEqual(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product);
	void CopyTriggerControl_V1(DelayTriggerData* p_dt, DelayTriggerData_V1* p_dtv1);
	void CopyTriggerControl_V2(DelayTriggerData* p_dt, DelayTriggerData_V2* p_dtv2);
	void CopyTriggerControl_V3(DelayTriggerData* p_dt, DelayTriggerData_V3* p_dtv3);
	void CopyTriggerControl_V4(DelayTriggerData* p_dt, DelayTriggerData_V4* p_dtv4);
	void CopyDelayControl_V2(DelayChannelData* p_dc, DelayChannelData_V2* p_v2);
	void CopyDelayControl_V3(DelayChannelData* p_dc, DelayChannelData_V3* p_v3);
	void DelayChannelTest(DelayChannel* p_dc);
	void ResetDelayChannel(DelayChannel* p_dc);
	void ResetMainCounter(MainCounterType* p_mc);
	void DelayTriggerTest(DelayTriggerType* p_dt);
	void ResetDelayTrigger(DelayTriggerType* p_dt);
	void ModifyControlRegister(DG_BME_Registers* p_pdg, DG_InternalData* p_Present);
	void ResetTriggerControl(DelayTriggerData* p_dt);
	void ResetDelayControl(DelayChannelData* p_dc);
	long SetChannel_SG05P4(DelayChannel* p_a, DelayChannelData* p_dl, long DG_Number);
	long SetChannel(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number);
	long SetReference(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number);
	long SetTrigger(DG_BME_Registers* p_dgr, DG_BME_Control* p_BDG, long DG_Number);
	BOOL ReadCalibrationFile(FILE *stream, int* p_module, char* FileName);
	void InitializeCalibrationConstants();
	long WidthNumber(unsigned long* p_out, double InValue, long DG_Number);
	long DelayNumbers(double* p_remainder, unsigned int* p_digital, double InValue, long DG_Number);
	long T0Numbers(unsigned int* p_digital, double InValue, long DG_Number);
	long DetectEthernetDelayGenerators(long* p_Error, DelgenType* p_DelgenList, char* p_IpAddr);
	BOOL MasterDelayGenerator(DelgenType* p_PciMaster, DelgenType* p_PciSlave);
	BOOL MasterLineDG(DelgenType* p_PciMaster, DelgenType* p_PciSlave, int LineNo);
	long ResetPciDelayGenerator(DelgenType* p_PciDelgen);
	long DataOut(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size);
	long Data32Out(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size);
	long DataIn(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size);
	long Data32In(unsigned short Address, void* p_data, DelgenType* p_PciDelgen, int Size);
public:
  CDG_DLL();
  ~CDG_DLL();
	long Set_DG_BME_Offset(DG_BME_Registers* p_InPdg, BOOL Offset, long DG_Number);

//
// long Reserve_DG_Data(int NumberOfDelayGenerators);
//
//		call this function first to reserve memory for the internal
//    data structures.
//
//		NumberOfDelayGenerators:	number of delay generators simultaneously to be controlled
//

	long Reserve_DG_Data(long NumberOfDelayGenerators);

//
// long Release_DG_Data();
//
//		call this function to release memory assigned by the "Reserve_DG_Data" function.
//

	long Release_DG_Data();

//
// long SaveState();
//
//		call this function to save the internal memory of the DLL routines.
//

	long SaveState();

//
// long ReadState();
//
//		call this function to recall previously saved internal memory of the DLL routines.
//

	long ReadState();

//
// long SaveParameters(DG_BME_State* p_DGS, int NoDelayGenerators,
//														 BOOL b_CalibrateTiming, unsigned long m_CalibrationLevel, char* FileName);
//
//		call this function to save the present parameter set of the delay generators to a file
//
//					p_DGS:							pointer to a structure that contains all control and initialization parameters,
//															for details see "DG_Data.h"
//					NoDelayGenerators:	number of delay generators that are known and controlled by the program
//					b_CalibrateTiming:	TRUE if delay and clock times are to calibrated to some external clock
//															frequency other than 10MHz or 80MHz
//					m_CalibrationLevel: 0:  no timing calibration
//															1:  calibrate clock period
//															2:  calibrate also the insertion delay of the delay generators
//					FileName:						file name and path, under which these parameters should be stored
//

	long SaveParameters(DG_BME_State* p_DGS, int NoDelayGenerators, 
														 BOOL b_CalibrateTiming, unsigned long m_CalibrationLevel, char* FileName);


//
// long ReadParameters(DG_BME_State* p_DGS, int* p_module,
//														 BOOL* p_CalibrateTiming, unsigned long* p_CalibrationLevel, char* FileName);
//
//		call this function to retrieve a parameter set of the delay generators from file
//
//					p_DGS:							pointer to a structure that will take all control and initialization parameters,
//															for details see "DG_Data.h". Reserve enough memory for this structure to
//															take all data for the delay generators that will be read from file.
//					p_module:						the numbers on this vector show, whether the corresponging delay
//															generator is a master or a slave.Reserve enough memory for this vector to
//															take all data for the delay generators that will be read from file.
//															1: MasterModule
//															2: SlaveModule
//					p_CalibrateTiming:	pointer to a boolean variable that is TRUE if delay and clock times 
//															are to calibrated to some external clock frequency other than 10MHz or 80MHz
//					p_CalibrationLevel: pointer to the address of an unsigned long variable. The return value is
//															0:  no timing calibration
//															1:  calibrate clock period
//															2:  calibrate also the insertion delay of the delay generators
//					FileName:						file name and path, under which these parameters will be read
//

	long ReadParameters(DG_BME_State* p_DGS, int* p_module,
														 BOOL* p_CalibrateTiming, unsigned long* p_CalibrationLevel, char* FileName);

//
// long Initialize_DG_BME(long base, long Product, long DG_Number);
//
//
// long Initialize_Bus_DG_BME(long BusNumber, long base, long Product, long DG_Number);
//
//
// long Initialize_Ethernet_DG_BME(long BusNumber, long base, char* p_ip_address, long Product, long DG_Number);
//
//		call this function individually for each delay generator to tell the driver:
//
//					BusNumber:		number of the PCI bus, where the delay generator is located
//					base:					base adress jumpered on the ISA delay generator PC board or
//												slot number of a PCI delay generator board
//					p_ip_address: pointer to the ethernet address
//					Product:			product code (BME_G02, BME_G03)
//					DG_Number:		number of this delay generator (counting starts from zero!)
//
	long Initialize_DG_BME(long base, long Product, long DG_Number);

	long Initialize_Bus_DG_BME(long BusNumber, long base, long Product, long DG_Number);

	long Initialize_Ethernet_DG_BME(long BusNumber, long base, char* p_ip_address, long Product, long DG_Number);

//
// long Set_DG_BME(DG_BME_Registers* p_pdg, long DG_Number);
//
//		call this function to individually set each delay generator to the desired parameters:
//
//					p_pdg:			Control structure, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//  delay generators can be set immediatly after calling "Initialize_DG_BME" or "Deactivate_DG_BME"

	long Set_DG_BME(DG_BME_Registers* p_pdg, long DG_Number);


//
// long LoadOutputState(long DG_Number);
//
//		call this function to actually load the specified state (positive/negative, terminate)
//		to the outputs. 
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long LoadOutputState(long DG_Number);

//
// long Deactivate_DG_BME(long DG_Number);
//
//		call this function to deactivate the delay generator and make it ready to accept
//		control parameters. If more delay generators are slaved to a master, deactivate the
//		master first.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long Deactivate_DG_BME(long DG_Number);


//
// long Activate_DG_BME(long DG_Number);
//
//		call this function to activate the delay generator and make it ready to accept
//		control parameters. If more delay generators are slaved to a master, activate the
//		master last.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long Activate_DG_BME(long DG_Number);

//
// long ResetEventCounter(long DG_Number);
//
//		call this function to reset the Trigger-(Event-)counter of a delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long ResetEventCounter(long DG_Number);

//
// long ResetOutputModuloCounter(long DG_Number);
//
//		call this function to reset the output modulo-counter of a delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long ResetOutputModuloCounters(long DG_Number);

//
// long ResetAllOutputModuloCounter();
//
//		call this function to reset the output modulo-counter of all delay generators
//
//

	long ResetAllOutputModuloCounters();


//
// long JumpStartAllLists();
//
//		call this function to set the memory read pointers of all delay generators to
//		the beginning of the delay lists
//
//

	long JumpStartAllLists();

//
// long LoadCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number);
//
//		call this function to load all modified parameters and to set selected counters to zero synchronuously
//
//					b_EventCounter:		set this flag TRUE to reset the event counter
//					b_ModuloCounter:	set this flag TRUE to reset the modulo counter for all channels
//														of this delay generator
//					b_TimeList:				set this flag TRUE to set all memory read pointers of this delay generator
//														to the beginning of the delay lists
//					DG_Number:				number of this delay generator (counting starts from zero!)
//
//

	long LoadCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number);

//
// long LoadAllCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);
//
//		call this function to load all modified parameters and  to set selected counters to zero 
//					synchronuously on the individual card, sequentially from one card to the next
//
//					b_EventCounter:		set this flag TRUE to reset the event counter
//					b_ModuloCounter:	set this flag TRUE to reset the modulo counter for all channels
//														of this delay generator
//					b_TimeList:				set this flag TRUE to set all memory read pointers of this delay generator
//														to the beginning of the delay lists
//
//

	long LoadAllCardParameters(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);


//
// long ResetCounter(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number);
//
//		call this function to set selected counters to zero synchronuously
//
//					b_EventCounter:		set this flag TRUE to reset the event counter
//					b_ModuloCounter:	set this flag TRUE to reset the modulo counter for all channels
//														of this delay generator
//					b_TimeList:				set this flag TRUE to set all memory read pointers of this delay generator
//														to the beginning of the delay lists
//					DG_Number:				number of this delay generator (counting starts from zero!)
//
//

	long ResetCounter(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList, long DG_Number);

//
// long ResetCounterAllCards(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);
//
//		call this function to set selected counters to zero synchronuously on the individual card,
//					sequentially from one card to the next
//
//					b_EventCounter:		set this flag TRUE to reset the event counter
//					b_ModuloCounter:	set this flag TRUE to reset the modulo counter for all channels
//														of this delay generator
//					b_TimeList:				set this flag TRUE to set all memory read pointers of this delay generator
//														to the beginning of the delay lists
//
//

	long ResetCounterAllCards(BOOL b_EventCounter, BOOL b_ModuloCounter, BOOL b_TimeList);


//
// unsigned long ReadTriggerCounter(long DG_Number);
//
//		this function returns the numnber of Trigger-Events since last calling 
//		the function "ResetEventCounter"
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//


	unsigned long ReadTriggerCounter(long DG_Number);

//
// long Read64bitTriggerCounter(_int64* p_result, long DG_Number);
//
//		this function returns the numnber of Trigger-Events since last calling 
//		the function "ResetEventCounter"
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//


	long Read64BitTriggerCounter(_int64* p_result, long DG_Number);

//
// long ReadFrequencyCounter(double* p_Frequency, long DG_Number);
//
//		this function returns the frequency of th internal clock signal
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long ReadFrequencyCounter(double* p_Frequency, long DG_Number);

//
// long SoftwareTrigger_DG_BME(long DG_Number);
//
//		call this function to trigger the delay sequence by software command
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long SoftwareTrigger_DG_BME(long DG_Number);



//
// long EnableInterrupts(unsigned long value, long DG_Number);
//
//		use this function to enable interrupts. The interrupt mask is contained in the
//		lower 8 bits of value.
//
//					value:			interrupt mask
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long EnableInterrupts(unsigned long value, long DG_Number);

//
// unsigned long ReadInterruptStatus(long DG_Number);
//
//		this function returns the interrupt status. The interrupt status is contained in the
//		lower 8 bits of the return value.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	unsigned long ReadInterruptStatus(long DG_Number);



//
// long AcknowledgeInterrupts(unsigned long value, long DG_Number);
//
//		use this function to acknowledge interrupts. The interrupt acknowledge bits are contained in the
//		lower 8 bits of value.
//
//					value:			interrupt acknowledge bits
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long AcknowledgeInterrupts(unsigned long value, long DG_Number);


//
// unsigned long Read_DG_Status(long DG_Number);
//
//		this function returns the status of the delay generator. The status is contained in the
//		lower 8 bits of the return value.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	unsigned long Read_DG_Status(long DG_Number);


//
// unsigned long ReadCounterControlRegister(long DG_Number);
//
//		this function returns the content of the counter control register. The function is meant
//		for diagnostic purposes
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	unsigned long ReadCounterControlRegister(long DG_Number);



//
// long ResetRegisters(DG_BME_Registers* p_DGState);
//
//		use this function to initialize the variable p_DGState to a known state.
//
//					p_DGState:			structure of type DG_BME_Registers that is passed to the
//													function Set_DG_BME.
//

	long ResetRegisters(DG_BME_Registers* p_DGState);



//
// long ResetControl(DG_BME_Control* p_DGControl);
//
//		use this function to initialize the variable p_DGControl to a known state.
//
//					p_DGControl:		structure of type DG_BME_Control that is passed to the
//													function SetDelayGenerator
//

	long ResetControl(DG_BME_Control* p_DGControl);

//
// long ResetState(DG_BME_State* p_DGS);
//
//		use this function to initialize the variable p_DGS to a known state.
//
//					p_DGS:					structure of type DG_BME_State that is passed to the
//													functions SaveParameters or ReadParameters
//

	long ResetState(DG_BME_State* p_DGS);

//
// long CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V1* p_Control_V1);
//
//		use this function to convert data from the old structure DG_BME_Control_V1
//    to the new structure DG_BME_Control
//
//					p_Control:	  	structure of type DG_BME_Control that is passed to the
//													function SetDelayGenerator
//					p_Control_V1:  	structure of type DG_BME_Control_V1 that is passed to the
//													function SetDelayGenerator
//					p_Control_V2:  	structure of type DG_BME_Control_V2 that is passed to the
//													function SetDelayGenerator
//					p_Control_V3:  	structure of type DG_BME_Control_V3 that is passed to the
//													function SetDelayGenerator
//					p_Control_V4:  	structure of type DG_BME_Control_V4 that is passed to the
//													function SetDelayGenerator
//

	long CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V1* p_Control_V1);
	long CopyControl_V2(DG_BME_Control* p_Control, DG_BME_Control_V2* p_Control_V2);
	long CopyControl_V3(DG_BME_Control* p_Control, DG_BME_Control_V3* p_Control_V3);
	long CopyControl_V4(DG_BME_Control* p_Control, DG_BME_Control_V4* p_Control_V4);

//
// long CopyState(DG_BME_State* p_DGS, DG_BME_State_V1* p_DGS_V1);
//
//		use this function to convert data from the old structure DG_BME_State_V1
//    to the new structure DG_BME_State
//
//
	
	long CopyState_V1(DG_BME_State* p_DGS, DG_BME_State_V1* p_DGS_V1);
	long CopyState_V2(DG_BME_State* p_DGS, DG_BME_State_V2* p_DGS_V2);
	long CopyState_V3(DG_BME_State* p_DGS, DG_BME_State_V3* p_DGS_V3);
	long CopyState_V4(DG_BME_State* p_DGS, DG_BME_State_V4* p_DGS_V4);

//
// unsigned ModifyAction(DG_BME_Control* p_BDG, long DG_Number);
//
//		call this function to find out for each delay generator the required actions
//		before calling 
//									SetDelayGenerator(...)
//
//					p_BDG:			Control structure, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//		Return values:
//					bit 0 TRUE: it is necessary to call the function Deactivate_DG_BME(...)
//					bit 1 TRUE: it is necessary to call the function ResetEventCounter(...)
//					bit 2 TRUE: it is necessary to call the function ResetOutputModuloCounters(...)

	unsigned long ModifyAction(DG_BME_Control* p_BDG, long DG_Number);

//
// unsigned long Modify_DG(..................., long DG_Number);
//
//		call this function to find out for each delay generator the required actions
//		before calling 
//									SetDelayGenerator(...), Set_G0X_Delay(...), etc.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//		Return values:
//					bit 0 TRUE: it is necessary to call the function Deactivate_DG_BME(...)
//					bit 1 TRUE: it is necessary to call the function ResetEventCounter(...)
//					bit 2 TRUE: it is necessary to call the function ResetOutputModuloCounters(...)


	unsigned long Modify_DG(unsigned long OutputModulo_T0, BOOL Active_T0,
													BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													unsigned long OutputModulo_A, BOOL Active_A,
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													unsigned long OutputModulo_B, BOOL Active_B,
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													unsigned long PresetValue, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

//
// unsigned long Modify_DG_V2(..................., long DG_Number);
//
//		call this function to find out for each delay generator the required actions
//		before calling 
//									SetDelayGenerator(...), Set_G0X_Delay(...), etc.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//		Return values:
//					bit 0 TRUE: it is necessary to call the function Deactivate_DG_BME(...)
//					bit 1 TRUE: it is necessary to call the function ResetEventCounter(...)
//					bit 2 TRUE: it is necessary to call the function ResetOutputModuloCounters(...)
//
//    Note: This function is similar to the function Modify_DG(...), it applies to the
//          newer versions of the delay generators.

	unsigned long Modify_DG_V2(unsigned long OutputModulo_T0, 
													unsigned long GoSignal_T0, unsigned long DoneSignal_T0,
													BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													unsigned long OutputModulo_A, unsigned long GoSignal_A, unsigned long DoneSignal_A,
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													unsigned long OutputModulo_B, unsigned long GoSignal_B, unsigned long DoneSignal_B,
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													unsigned long PresetValue, unsigned long ClockSource, unsigned long GateDivider,
													unsigned long MS_Bus, BOOL PositiveGate, BOOL SynchronizeGate,
													BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

//
// unsigned long Modify_G08(..................., long DG_Number);
//
//		call this function to find out for each delay generator the required actions
//		before calling 
//									SetDelayGenerator(...), Set_G0X_Delay(...), etc.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//		Return values:
//					bit 0 TRUE: it is necessary to call the function Deactivate_DG_BME(...)
//					bit 1 TRUE: it is necessary to call the function ResetEventCounter(...)
//					bit 2 TRUE: it is necessary to call the function ResetOutputModuloCounters(...)
//
//    Note: This function is similar to the function Modify_DG(...), it applies to the
//          SG08 versions of the delay generators.


	unsigned long Modify_G08(unsigned long OutputModulo_A, unsigned long OutputOffset_A, unsigned long GoSignal_A,
													BOOL Positive_A, BOOL Terminate_A,
													unsigned long OutputModulo_B, unsigned long OutputOffset_B, unsigned long GoSignal_B,
													BOOL Positive_B, BOOL Terminate_B,
													unsigned long OutputModulo_C, unsigned long OutputOffset_C, unsigned long GoSignal_C,
													BOOL Positive_C, BOOL Terminate_C,
													unsigned long OutputModulo_D, unsigned long OutputOffset_D, unsigned long GoSignal_D,
													BOOL Positive_D, BOOL Terminate_D,
													unsigned long OutputModulo_E, unsigned long OutputOffset_E, unsigned long GoSignal_E,
													BOOL Positive_E, BOOL Terminate_E, BOOL Disconnect_E, BOOL OntoMsBus_E, BOOL InputPositive_E,
													unsigned long OutputModulo_F, unsigned long OutputOffset_F, unsigned long GoSignal_F,
													BOOL Positive_F, BOOL Terminate_F, BOOL Disconnect_F, BOOL OntoMsBus_F, BOOL InputPositive_F,
													BOOL TriggerTerminate, BOOL GateTerminate, BOOL ClockEnable,
													unsigned long PresetValue, unsigned long ClockSource, unsigned long GateDivider,
													unsigned long MS_Bus, BOOL PositiveGate, BOOL SynchronizeGate, BOOL InternalTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);


//
// long SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number);
//
//		call this function to individually set each delay generator to the desired parameters:
//
//					p_BDG:			Control structure, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//  delay generators can be set immediatly after calling "Initialize_DG_BME" or "Deactivate_DG_BME"

	long SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number);

//
// long Set_BME_G0X(............., long DG_Number);
//
//		call this function to individually set each delay generator to the desired parameters:
//
//					......:			Control parameters, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//					X:					2,3,4, depending on model of delay generator
//
//  delay generators can be set immediatly after calling "Initialize_DG_BME"
	long Set_BME_G08(double FireFirst_A, double PulseWidth_A, unsigned long OutputModulo_A,
													unsigned long OutputOffset_A, unsigned long GoSignal_A, BOOL Positive_A, BOOL Terminate_A, 
													double FireFirst_B, double PulseWidth_B, unsigned long OutputModulo_B,
													unsigned long OutputOffset_B, unsigned long GoSignal_B, BOOL Positive_B, BOOL Terminate_B, 
													double FireFirst_C, double PulseWidth_C, unsigned long OutputModulo_C,
													unsigned long OutputOffset_C, unsigned long GoSignal_C, BOOL Positive_C, BOOL Terminate_C, 
													double FireFirst_D, double PulseWidth_D, unsigned long OutputModulo_D,
													unsigned long OutputOffset_D, unsigned long GoSignal_D, BOOL Positive_D, BOOL Terminate_D, 
													double FireFirst_E, double PulseWidth_E, unsigned long OutputModulo_E,
													unsigned long OutputOffset_E, unsigned long GoSignal_E, BOOL Positive_E, BOOL Terminate_E, 
													BOOL Disconnect_E, BOOL OntoMsBus_E, BOOL InputPositive_E,
													double FireFirst_F, double PulseWidth_F, unsigned long OutputModulo_F,
													unsigned long OutputOffset_F, unsigned long GoSignal_F, BOOL Positive_F, BOOL Terminate_F, 
													BOOL Disconnect_F, BOOL OntoMsBus_F, BOOL InputPositive_F,
													unsigned long GateFunction, BOOL ClockEnable, unsigned long OscillatorDivider,
													unsigned long TriggerDivider,  unsigned long TriggerMultiplier,
													unsigned long ClockSource, BOOL TriggerTerminate, BOOL GateTerminate,
													double TriggerLevel, double GateLevel, double GateDelay, unsigned long MS_Bus,
													double InternalClock, unsigned long PresetValue, unsigned long GateDivider,
													double ForceTrigger, double StepBackTime, unsigned long BurstCounter,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL IgnoreGate, BOOL SynchronizeGate,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

	long Set_BME_G05(double FireFirst_T0, unsigned long OutputModulo_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, unsigned long OutputModulo_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, unsigned long OutputModulo_B,
													BOOL Active_B, BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

	long Set_BME_G03(double FireFirst_T0, double SetBack_T0, BOOL Active_T0, 
													BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A, BOOL Active_A, 
													BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B, BOOL Active_B, 
													BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);


	long Set_BME_G02(double FireFirst_T0, BOOL Active_T0, BOOL Positive_T0, 
													BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, BOOL Active_A, BOOL Positive_A, 
													BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, BOOL Active_B, BOOL Positive_B, 
													BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);



//
// long Set_TriggerParameters(............., long DG_Number);
//
//		call this function to set the trigger parameters of the delay generator;
//

	long Set_TriggerParameters(BOOL TriggerTerminate, double InternalClock, 
													double TriggerLevel, unsigned long PresetValue, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

//
// long Set_V2_TriggerParameters(............., long DG_Number);
//
//		call this function to set the additional trigger parameters of the BME_SG02P3 delay generator;
//

	long Set_V2_TriggerParameters(BOOL IgnoreGate, BOOL SynchronizeGate, double ForceTrigger, 
																			 unsigned long MS_Bus, long DG_Number);
//
// long Set_G08_TriggerParameters(............., long DG_Number);
//
//		call this function to set the additional trigger parameters of the BME_SG08P1 delay generator;
//

	long Set_G08_TriggerParameters(BOOL GateTerminate, double GateLevel, double GateDelay,
													BOOL IgnoreGate, BOOL SynchronizeGate, double ForceTrigger,
													double StepBackTime, unsigned long BurstCounter, unsigned long MS_Bus, long DG_Number);

		
//
// long Set_ClockParameters(............., long DG_Number);
//
//		call these functions to set the clock parameters of the delay generator;
//

	long Set_ClockParameters(BOOL ClockEnable, unsigned long DivideBy, unsigned long ClockSource, 
													long DG_Number);

	long Set_G08_ClockParameters(BOOL ClockEnable, unsigned long OscillatorDivider, 
																				unsigned long TriggerDivider, unsigned long TriggerMultiplier, 
																				unsigned long ClockSource, long DG_Number);

//
// long Set_Gate_AB(BOOL Gate_AB, long DG_Number);
//
//		call this function to define, whether outputs A and B should be
//		independent or gated
//

	long Set_Gate_AB(BOOL Gate_AB, long DG_Number);

//
// long Set_GateFunction(unsigned long GateFunction, long DG_Number);
//
//		call this function to define, whether outputs AB, CD, EF should be
//		independent or gated
//

	long Set_GateFunction(unsigned long GateFunction, long DG_Number);

//
// long Set_OutputLevel(unsigned long OutputLevel, unsigned long PulseWidth, long DG_Number);
//
//		call this function to define the voltage levels and pulse width of the outputs.
//		The constants are defined in "DG_Data.h"
//		(TTL_VoltageLevel, NIM_VoltageLevel, ECL_VoltageLevel)
//

	long Set_OutputLevel(unsigned long OutputLevel, unsigned long PulseWidth, long DG_Number);

//
// long Set_G0X_Delay(............., long DG_Number);
//
//		call this function to set the delay parameters of the delay generator;
//								
//					Channel:		constant defining which channel to set
//											(DelayChannel_T0, DelayChannel_A, DelayChannel_B,
//											values are defined in "DG_Data.h")
//					......:			Control parameters, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//					X:					2,3,4, depending on model of delay generator

	long Set_G02_Delay(unsigned long Channel, double FireFirst, 
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);
	
	long Set_G03_Delay(unsigned long Channel, 
													double FireFirst, double SetBack,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);

	long Set_G05_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);
	
	long Set_G05P2_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
															unsigned long GoSignal, unsigned long DoneSignal,
															BOOL Positive, BOOL Terminate, BOOL HighDrive, long DG_Number);


	long Set_G08_Delay(unsigned long Channel, double FireFirst, double PulseWidth, 
															unsigned long OutputModulo, unsigned long OutputOffset, 
															unsigned long GoSignal, BOOL Positive, BOOL Terminate, 
															BOOL Disconnect, BOOL OntoMsBus, BOOL InputPositive, long DG_Number);

//
// long Set_DelayList(unsigned long CalibrationLevel, long DG_Number);
//
//		call this function to load a list of delay values into the FPGA of the delay generator
//								
	
	long Set_DelayList(unsigned long Channel, double* p_DelayTime, double* p_PulseWidth, 
															unsigned long* p_StepBack, signed long ListLength, long DG_Number);


//
// long Set_CalibrationLevel(unsigned long CalibrationLevel, long DG_Number);
//
//		call this function to set the calibration level of the delay generator;
//								
//					CalibrationLevel:		constant defining how the delay times of the
//															delay generator are to be calibrated.
//															(CalibrateIncrement, CallibrateOffset,
//															values are defined in "DG_Data.h")
//					DG_Number:	number of this delay generator (counting starts from zero!)

	long Set_CalibrationLevel(unsigned long CalibrationLevel, long DG_Number);

//
// long Set_CalibrationForAll(unsigned long CalibrationLevel);
//
//		call this function to set the calibration level of the delay generator;
//								
//					CalibrationLevel:		constant defining how the delay times of the
//															delay generator are to be calibrated.
//															(CalibrateIncrement, CallibrateOffset,
//															values are defined in "DG_Data.h")

	long Set_CalibrationForAll(unsigned long CalibrationLevel);

//
// long Test_BME_G0X(long DG_Number);
//
//		call this function to individually test each delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//					X:					2,3,4, depending on model of delay generator
//
//  delay generators can be tested immediatly after calling "Initialize_DG_BME"

	long Test_BME_G02(long DG_Number);

	long Test_BME_G03(long DG_Number);

	long Test_BME_G05(long DG_Number);	
	
	long Test_BME_G08(long DG_Number);

//
// long ReadCalibrationConstants();
//
//		call this function to read the main calibration contants from
//		the file ''BME_G0x.cal''. If this file does not exist, an average set
//		of calibration constants will be used and also immediatly written to this file.
//

	long ReadCalibrationConstants();

//
// long ReadPathCalibrationConstants(char* Path);
//
//		call this function to read the main calibration contants from
//		the file ''BME_G0x.cal''. If this file does not exist, an average set
//		of calibration constants will be used and also immediatly written to this file.
//
//					Path:			zero-terminated string specifying the Path of the calibration
//										file 'BME_G0x.cal'
//

	long ReadPathCalibrationConstants(char* Path);

//
// long CalibrateModule(long DG_Number);
//
//		use the calibration constants read by the function ''ReadCalibrationConstants()''
//		to calibrate this module as a standalone master.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long CalibrateModule(long DG_Number);

//
// long UncalibrateModule(long DG_Number);
//
//		zero the calibration constants for this module
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long UncalibrateModule(long DG_Number);

//
// long CalibrateGroup(int* p_module);
//
//		calibrate the complete set of delay generators, using also the information
//		which ones of these are slaves of defined masters
//
//					p_module:	integer vector as long as the number of modules defined
//										in the routine ''Reserve_DG_Data(...)''.Write the constant
//										''MasterModule'' onto the vector for a master, write
//										''Slavemodule'' for a slave. (The master shuld always come
//										before its slaves.)
//

	long CalibrateGroup(int* p_module);

//
// long CalibratePathGroup(int* p_module, char* Path)
//
//		calibrate the complete set of delay generators, using also the information
//		which ones of these are slaves of defined masters
//
//					p_module:	integer vector as long as the number of modules defined
//										in the routine ''Reserve_DG_Data(...)''.Write the constant
//										''MasterModule'' onto the vector for a master, write
//										''Slavemodule'' for a slave. (The master shuld always come
//										before its slaves.)
//					Path:			zero-terminated string specifying the Path of the calibration
//										file 'Modules.cal'
//

	long CalibratePathGroup(int* p_module, char* Path);

//
// long DelayLimit(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal A or B delay value that is nearest to InValue.
//		This routine calculates the delay values for the A and B channels of the delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long DelayLimit(double* p_out, double InValue, long DG_Number);

//
// long RoundT0(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal T0 delay value that is nearest to InValue.
//		This routine calculates the delay values for the T0 channel of the delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long RoundT0(double* p_out, double InValue, long DG_Number);

//
// long RoundWidth(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal Width value that is nearest to InValue.
//		This routine calculates the width for all channels of the delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long RoundWidth(double* p_out, double InValue, long DG_Number);

//
// long RoundGateDelay(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal Gate Delay that is nearest to InValue.
//		This routine calculates the width for all channels of the delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long RoundGateDelay(double* p_out, double InValue, long DG_Number);

//
// long RoundSetBack(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal Setback delay value that is nearest to InValue.
//		This routine calculates the delay values for the Setback function 
//		of the BME_G03 delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long RoundSetBack(double* p_out, double InValue, long DG_Number);

//
// long RoundRepCounter(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal period value for the RepCounter that is nearest to InValue.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		period value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

	long RoundRepCounter(double* p_out, double InValue, long DG_Number);

//
// long DetectPciDelayGenerators(long* p_Error);
//
//		this function returns the number of delay generators installed on the PCI bus
//
//					p_Error:		pointer to a memory location for storing the (plx) error code
//
	
	long DetectPciDelayGenerators(long* p_Error);

//
// long AddEthernetDelayGenerators(long* p_Error, char* p_IpAddr);
//
//		this function returns the number of delay generators installed on the PCI bus
//
//					p_Error:		pointer to a memory location for storing the (plx) error code
//					p_IpAddr:		pointer to a memory location for storing the Ethernet Address
//

	long AddEthernetDelayGenerators(long* p_Error, char* p_IpAddr);


//
// long GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number);
//
//
// long GetPciBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber,
//                              BOOL* p_Master, long DG_Number);
//
//
// long GetEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
//                                    BOOL* p_Master, long DG_Number);
//
//		use this function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_IpAddr:		    pointer to a memory location for storing the Ethernet Address
//	                        of the delay generator
//					p_BusNumber:		pointer to a memory location for storing the bus
//	                        number of the delay generator
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_Master:				pointer to a memory location for storing the boolean
//	                        value that defines a master or slave
//					DG_Number:			number of this delay generator (counting starts from zero!)
//

	long GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number);

	long GetPciBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																BOOL* p_Master, long DG_Number);

	long GetEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber,
																			BOOL* p_Master, long DG_Number);

//
// long GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number)
//
//
// long GetUnconnectedBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber,
//                                              long* p_LineMaster, long DG_Number)
//
//
// long GetUnconnectedEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
//																							long* p_LineMaster, long DG_Number);
//
//		use these function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//    This routine recalls the parameters of delay generators that have not been correctly connected
//    via the master/slave bus
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_IpAddr:		    pointer to a memory location for storing the Ethernet Address
//	                        of the delay generator
//					p_BusNumber:		pointer to a memory location for storing the bus
//	                        number of the delay generator
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_LineMaster:		pointer to a memory location for storing three long 
//	                        values signifying the master of that specific line
//					DG_Number:			number of this delay generator (counting starts from zero!)
//

	long GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number);

	long GetUnconnectedBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																				long* p_LineMaster, long DG_Number);

	long GetUnconnectedEthernetDelayGenerator(long* p_DG_Product, char* p_IpAddr, long* p_BusNumber, long* p_SlotNumber, 
																							long* p_LineMaster, long DG_Number);

};

