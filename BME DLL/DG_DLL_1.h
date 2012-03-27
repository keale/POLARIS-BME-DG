/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Delay Generator driver
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    programmer:                Thorald Bergmann
    Version:                   V1.1
    Update:                    18. February 2005
    copyright:                 (c) 1997 by BME

----------------------------------------------------------------------------*/

//#define VB						// if defined generates a DLL callable from Visual Basic
#undef VB

#ifdef VB
	#define CC WINAPI
#else
	#define CC
#endif



// define the constants for the different delay generator products

#include "..\BME_G0x\DG_Data.h"

//  main entry point

BOOL WINAPI DllMain(HANDLE hModule, DWORD dwFunction, LPVOID lpNot);


//
// long Reserve_DG_Data(int NumberOfDelayGenerators);
//
//		call this function first to reserve memory for the internal
//    data structures.
//
//		NumberOfDelayGenerators:	number of delay generators simultaneously to be controlled
//

_declspec (dllexport) long CC Reserve_DG_Data(long NumberOfDelayGenerators);

//
// long Release_DG_Data();
//
//		call this function to release memory assigned by the "Reserve_DG_Data" function.
//

_declspec (dllexport) long CC Release_DG_Data();

//
// long SaveState();
//
//		call this function to save the internal memory of the DLL routines.
//

_declspec (dllexport) long CC SaveState();

//
// long ReadState();
//
//		call this function to recall previously saved internal memory of the DLL routines.
//

_declspec (dllexport) long CC ReadState();

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

_declspec (dllexport) long CC SaveParameters(DG_BME_State* p_DGS, int NoDelayGenerators, 
														 BOOL b_CalibrateTiming, unsigned long m_CalibrationLevel, char* FileName);


//
// long ReadParameters(DG_BME_State* p_DGS, int* p_module,
//														 BOOL& b_CalibrateTiming, unsigned long& m_CalibrationLevel, char* FileName);
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

_declspec (dllexport) long CC ReadParameters(DG_BME_State* p_DGS, int* p_module,
														 BOOL* p_CalibrateTiming, unsigned long* p_CalibrationLevel, char* FileName);
//
// long Initialize_DG_BME(long base, long Product, long DG_Number);
//
//		call this function individually for each delay generator to tell the driver:
//
//					base:				base adress jumpered on the ISA delay generator PC board or
//											slot number of a PCI delay generator board
//					Product:		product code (BME_G02, BME_G03, BME_G04)
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
_declspec (dllexport) long CC Initialize_DG_BME(long base, long Product, long DG_Number);

//
// long Initialize_Bus_DG_BME(long BusNumber, long base, long Product, long DG_Number);
//
//		call this function individually for each delay generator to tell the driver:
//
//					BusNumber:	number of the PCI bus, where the delay generator is located
//					base:				base adress jumpered on the ISA delay generator PC board or
//											slot number of a PCI delay generator board
//					Product:		product code (BME_G02, BME_G03, BME_G04)
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC Initialize_Bus_DG_BME(long BusNumber, long base, long Product, long DG_Number);

//
// long Set_DG_BME(DG_BME_Registers* p_pdg, long DG_Number);
//
//		call this function to individually set each delay generator to the desired parameters:
//
//					p_pdg:			Control structure, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//  delay generators can be set immediatly after calling "Initialize_DG_BME" or "Deactivate_DG_BME"

_declspec (dllexport) long CC Set_DG_BME(DG_BME_Registers* p_pdg, long DG_Number);


//
// long LoadOutputState(long DG_Number);
//
//		call this function to actually load the specified state (positive/negative, terminate)
//		to the outputs. 
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC LoadOutputState(long DG_Number);

//
// long Deactivate_DG_BME(long DG_Number);
//
//		call this function to deactivate the delay generator and make it ready to accept
//		control parameters. If more delay generators are slaved to a master, deactivate the
//		master first.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC Deactivate_DG_BME(long DG_Number);


//
// long Activate_DG_BME(long DG_Number);
//
//		call this function to activate the delay generator and make it ready to accept
//		control parameters. If more delay generators are slaved to a master, activate the
//		master last.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC Activate_DG_BME(long DG_Number);

//
// long ResetEventCounter(long DG_Number);
//
//		call this function to reset the Trigger-(Event-)counter of a delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC ResetEventCounter(long DG_Number);

//
// long ResetOutputModuloCounter(long DG_Number);
//
//		call this function to reset the output modulo-counter of a delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC ResetOutputModuloCounters(long DG_Number);

//
// long ResetAllOutputModuloCounter();
//
//		call this function to reset the output modulo-counter of all delay generators
//
//

_declspec (dllexport) long CC ResetAllOutputModuloCounters();

//
// unsigned long ReadTriggerCounter(long DG_Number);
//
//		this function returns the numnber of Trigger-Events since last calling 
//		the function "ResetEventCounter"
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//


_declspec (dllexport) unsigned long CC ReadTriggerCounter(long DG_Number);


//
// long SoftwareTrigger_DG_BME(long DG_Number);
//
//		call this function to trigger the delay sequence by software command
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC SoftwareTrigger_DG_BME(long DG_Number);



//
// long EnableInterrupts(unsigned long value, long DG_Number);
//
//		use this function to enable interrupts. The interrupt mask is contained in the
//		lower 8 bits of value.
//
//					value:			interrupt mask
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC EnableInterrupts(unsigned long value, long DG_Number);

//
// unsigned long ReadInterruptStatus(long DG_Number);
//
//		this function returns the interrupt status. The interrupt status is contained in the
//		lower 8 bits of the return value.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) unsigned long CC ReadInterruptStatus(long DG_Number);



//
// long AcknowledgeInterrupts(unsigned long value, long DG_Number);
//
//		use this function to acknowledge interrupts. The interrupt acknowledge bits are contained in the
//		lower 8 bits of value.
//
//					value:			interrupt acknowledge bits
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC AcknowledgeInterrupts(unsigned long value, long DG_Number);


//
// unsigned long Read_DG_Status(long DG_Number);
//
//		this function returns the status of the delay generator. The status is contained in the
//		lower 8 bits of the return value.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) unsigned long CC Read_DG_Status(long DG_Number);


//
// unsigned long ReadCounterControlRegister(long DG_Number);
//
//		this function returns the content of the counter control register. The function is meant
//		for diagnostic purposes
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) unsigned long CC ReadCounterControlRegister(long DG_Number);



//
// long ResetRegisters(DG_BME_Registers* p_DGState);
//
//		use this function to initialize the variable p_DGState to a known state.
//
//					p_DGState:			structure of type DG_BME_Registers that is passed to the
//													function Set_DG_BME.
//

_declspec (dllexport) long CC ResetRegisters(DG_BME_Registers* p_DGState);



//
// long ResetControl(DG_BME_Control* p_DGControl);
//
//		use this function to initialize the variable p_DGControl to a known state.
//
//					p_DGControl:		structure of type DG_BME_Control that is passed to the
//													function SetDelayGenerator
//

_declspec (dllexport) long CC ResetControl(DG_BME_Control* p_DGControl);


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
//

_declspec (dllexport) long CC CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V1* p_Control_V1);

//
// long CopyControl(DG_BME_Control* p_Control, DG_BME_Control_V2* p_Control_V2);
//
//		use this function to convert data from the old structure DG_BME_Control_V2
//    to the new structure DG_BME_Control
//
//					p_Control:	  	structure of type DG_BME_Control that is passed to the
//													function SetDelayGenerator
//					p_Control_V2:  	structure of type DG_BME_Control_V2 that is passed to the
//													function SetDelayGenerator
//

_declspec (dllexport) long CC CopyControl_V2(DG_BME_Control* p_Control, DG_BME_Control_V2* p_Control_V2);
	
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

_declspec (dllexport) unsigned long CC ModifyAction(DG_BME_Control* p_BDG, long DG_Number);

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


_declspec (dllexport) unsigned long CC Modify_DG(unsigned long OutputModulo_T0, BOOL Active_T0,
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

_declspec (dllexport) unsigned long CC Modify_DG_V2(unsigned long OutputModulo_T0, 
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
// long SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number);
//
//		call this function to individually set each delay generator to the desired parameters:
//
//					p_BDG:			Control structure, for details see "DG_Data.h"
//					DG_Number:	number of this delay generator (counting starts from zero!)
//
//  delay generators can be set immediatly after calling "Initialize_DG_BME" or "Deactivate_DG_BME"

_declspec (dllexport) long CC SetDelayGenerator(DG_BME_Control* p_BDG, long DG_Number);

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

_declspec (dllexport) long CC Set_BME_G06(double FireFirst_T0, double SetBack_T0, unsigned long OutputModulo_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A, unsigned long OutputModulo_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B, unsigned long OutputModulo_B,
													BOOL Active_B, BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

_declspec (dllexport) long CC Set_BME_G05(double FireFirst_T0, unsigned long OutputModulo_T0,
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

_declspec (dllexport) long CC Set_BME_G04(double FireFirst_T0, double SetBack_T0,  double FireSecond_T0,
													BOOL Active_T0, BOOL Positive_T0, BOOL Terminate_T0, BOOL HighDrive_T0,
													double FireFirst_A, double SetBack_A,  double FireSecond_A,
													BOOL Active_A, BOOL Positive_A, BOOL Terminate_A, BOOL HighDrive_A,
													double FireFirst_B, double SetBack_B,  double FireSecond_B,
													BOOL Active_B, BOOL Positive_B, BOOL Terminate_B, BOOL HighDrive_B,
													BOOL Gate_AB, unsigned long OutputLevel, BOOL TriggerTerminate, BOOL ClockEnable,
													double InternalClock, double TriggerLevel, unsigned long PresetValue, 
													unsigned long DivideBy, unsigned long ClockSource, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

_declspec (dllexport) long CC Set_BME_G03(double FireFirst_T0, double SetBack_T0, BOOL Active_T0, 
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


_declspec (dllexport) long CC Set_BME_G02(double FireFirst_T0, BOOL Active_T0, BOOL Positive_T0, 
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

_declspec (dllexport) long CC Set_TriggerParameters(BOOL TriggerTerminate, double InternalClock, 
													double TriggerLevel, unsigned long PresetValue, unsigned long GateDivider,
													BOOL PositiveGate, BOOL InternalTrigger, BOOL InternalArm, BOOL SoftwareTrigger,
													BOOL RisingEdge, BOOL StopOnPreset, BOOL ResetWhenDone, BOOL TriggerEnable,
													long DG_Number);

//
// long Set_V2_TriggerParameters(............., long DG_Number);
//
//		call this function to set the additional trigger parameters of the BME_SG02P3 delay generator;
//

_declspec (dllexport) long CC Set_V2_TriggerParameters(BOOL IgnoreGate, BOOL SynchronizeGate, double ForceTrigger, 
																			 unsigned long MS_Bus, long DG_Number);
		
//
// long Set_ClockParameters(............., long DG_Number);
//
//		call this function to set the clock parameters of the delay generator;
//

_declspec (dllexport) long CC Set_ClockParameters(BOOL ClockEnable, unsigned long DivideBy, unsigned long ClockSource, 
													long DG_Number);
//
// long Set_Gate_AB(BOOL Gate_AB, long DG_Number);
//
//		call this function to define, whether outputs A and B should be
//		independent or gated
//

_declspec (dllexport) long CC Set_Gate_AB(BOOL Gate_AB, long DG_Number);

//
// long Set_OutputLevel(unsigned long OutputLevel, unsigned long PulseWidth, long DG_Number);
//
//		call this function to define the voltage levels and pulse width of the outputs.
//		The constants are defined in "DG_Data.h"
//		(TTL_VoltageLevel, NIM_VoltageLevel, ECL_VoltageLevel)
//

_declspec (dllexport) long CC Set_OutputLevel(unsigned long OutputLevel, unsigned long PulseWidth, long DG_Number);

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

_declspec (dllexport) long CC Set_G02_Delay(unsigned long Channel, double FireFirst, 
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);
	
_declspec (dllexport) long CC Set_G03_Delay(unsigned long Channel, 
													double FireFirst, double SetBack,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);
	
_declspec (dllexport) long CC Set_G04_Delay(unsigned long Channel, 
													double FireFirst, double SetBack, double FireSecond,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);

_declspec (dllexport) long CC Set_G05_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);
	
_declspec (dllexport) long CC Set_G05P2_Delay(unsigned long Channel, double FireFirst, unsigned long OutputModulo,
															unsigned long GoSignal, unsigned long DoneSignal,
															BOOL Positive, BOOL Terminate, BOOL HighDrive, long DG_Number);

_declspec (dllexport) long CC Set_G06_Delay(unsigned long Channel, 
													double FireFirst, double SetBack, unsigned long OutputModulo,
													BOOL Active, BOOL Positive, BOOL Terminate, BOOL HighDrive,
													long DG_Number);


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

_declspec (dllexport) long CC Set_CalibrationLevel(unsigned long CalibrationLevel, long DG_Number);

//
// long Set_CalibrationForAll(unsigned long CalibrationLevel);
//
//		call this function to set the calibration level of the delay generator;
//								
//					CalibrationLevel:		constant defining how the delay times of the
//															delay generator are to be calibrated.
//															(CalibrateIncrement, CallibrateOffset,
//															values are defined in "DG_Data.h")

_declspec (dllexport) long CC Set_CalibrationForAll(unsigned long CalibrationLevel);

//
// long Test_BME_G0X(long DG_Number);
//
//		call this function to individually test each delay generator
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//					X:					2,3,4, depending on model of delay generator
//
//  delay generators can be tested immediatly after calling "Initialize_DG_BME"

_declspec (dllexport) long CC Test_BME_G02(long DG_Number);

_declspec (dllexport) long CC Test_BME_G03(long DG_Number);

_declspec (dllexport) long CC Test_BME_G04(long DG_Number);

_declspec (dllexport) long CC Test_BME_G05(long DG_Number);

//
// long ReadCalibrationConstants();
//
//		call this function to read the main calibration contants from
//		the file ''BME_G0x.cal''. If this file does not exist, an average set
//		of calibration constants will be used and also immediatly written to this file.
//

_declspec (dllexport) long CC ReadCalibrationConstants();

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

_declspec (dllexport) long CC ReadPathCalibrationConstants(char* Path);

//
// long CalibrateModule(long DG_Number);
//
//		use the calibration constants read by the function ''ReadCalibrationConstants()''
//		to calibrate this module as a standalone master.
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC CalibrateModule(long DG_Number);

//
// long UncalibrateModule(long DG_Number);
//
//		zero the calibration constants for this module
//
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC UncalibrateModule(long DG_Number);

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

_declspec (dllexport) long CC CalibrateGroup(int* p_module);

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

_declspec (dllexport) long CC CalibratePathGroup(int* p_module, char* Path);

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

_declspec (dllexport) long CC DelayLimit(double* p_out, double InValue, long DG_Number);

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

_declspec (dllexport) long CC RoundT0(double* p_out, double InValue, long DG_Number);

//
// long RoundSetBack(double* p_out, double InValue, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal Setback delay value that is nearest to InValue.
//		This routine calculates the delay values for the Setback function 
//		of the BME_G03 or BME_G04 delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC RoundSetBack(double* p_out, double InValue, long DG_Number);

//
// long RoundFireSecond(double* p_out, double InValue, double FireFirst, long DG_Number);
//
//		uses the calibration defined by the calibration routines, to calculate
//		the legal Setback delay value that is nearest to InValue.
//		This routine calculates the delay values for the Fire Second function 
//		of the BME_G04 delay generators.
//
//					p_out:			memory location (double), where the result is placed
//					InValue:		delay value (in usec) for which the nearest legal value has to be found
//					FireFirst:	delay value (in usec) for the already defined Fire First delay of this channel
//					DG_Number:	number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC RoundFireSecond(double* p_out, double InValue, double FireFirst, long DG_Number);

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

_declspec (dllexport) long CC RoundRepCounter(double* p_out, double InValue, long DG_Number);

//
// long DetectPciDelayGenerators(long* p_Error);
//
//		this function returns the number of delay generators installed on the PCI bus
//
//					p_Error:		pointer to a memory location for storing the (plx) error code
//
	
_declspec (dllexport) long CC DetectPciDelayGenerators(long* p_Error);

//
// long GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number);
//
//		use this function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_Master:				pointer to a memory location for storing the boolean
//	                        value that defines a master or slave
//					DG_Number:			number of this delay generator (counting starts from zero!)
//
	
_declspec (dllexport) long CC GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number);

//
// long GetPciDelayGenerator(long* p_DG_Product, long* p_SlotNumber, BOOL* p_Master, long DG_Number);
//
//		use this function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_BusNumber:		pointer to a memory location for storing the bus
//	                        number of the delay generator
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_Master:				pointer to a memory location for storing the boolean
//	                        value that defines a master or slave
//					DG_Number:			number of this delay generator (counting starts from zero!)
//
	
_declspec (dllexport) long CC GetPciBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																BOOL* p_Master, long DG_Number);

//
// long GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number)
//
//		use this function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_LineMaster:		pointer to a memory location for storing three long 
//	                        values signifying the master of that specific line
//					DG_Number:			number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number);

//
// long GetUnconnectedDelayGenerator(long* p_DG_Product, long* p_SlotNumber, long* p_LineMaster, long DG_Number)
//
//		use this function to sequentially recall the parameters of delay generators 
//	  detected on the PCI bus by the routine 'DetectPciDelayGenerators()'
//
//					p_DG_Product:		pointer to a memory location for storing the product
//	                        code of the delay generator. The product codes are
//													defined in the file ''DG_Data.h''
//					p_BusNumber:		pointer to a memory location for storing the bus
//	                        number of the delay generator
//					p_SlotNumber:		pointer to a memory location for storing the slot
//	                        number of the delay generator
//					p_LineMaster:		pointer to a memory location for storing three long 
//	                        values signifying the master of that specific line
//					DG_Number:			number of this delay generator (counting starts from zero!)
//

_declspec (dllexport) long CC GetUnconnectedBusDelayGenerator(long* p_DG_Product, long* p_BusNumber, long* p_SlotNumber, 
																				long* p_LineMaster, long DG_Number);


///////////////////////////////////////////////////////////////////////////////////////////////////////

//// private definitions and functions ////////////////////////////////////////////////////////////////

#define RoundInt(d) ((int)((d) + ((d) > 0 ? 0.5 : -0.5)))


typedef struct 
{
  unsigned short base_address,CommandAddress;
  unsigned short CounterControlAddress,InterruptEnableAddress;
  unsigned short InterruptAcknowledgeAddress,InitializeAddress,PrescalerAddress;
	unsigned short Counter,Counter_N,Counter_K,Counter_J,Counter_cntrl;
  unsigned short Delay,Delay_T0,Delay_A,Delay_B,Delay_Aux,Delay_cntrl;
	unsigned short ModuloCounterAddress,TriggerCounterAddress;
  unsigned short Large,Large_T0,Large_A,Large_B,Large_cntrl;
	unsigned short DAC,DAC_T0,DAC_A,DAC_B;
	unsigned short CommandRegister,CommandRegisterState,InterruptEnableRegister;
	unsigned long CounterControlRegister[2];
	unsigned long CounterControlState[2];
	unsigned long PrescalerState[2];
	union
	{
		double	IniTime[10];
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
	DG_BME_Registers	DelayGeneratorState;
	DG_BME_Control		DelayControlState;
	BOOL NtDriverInitialized;
  HANDLE h_DelayGenerator;
	long BusNumber;
	long SlotNumber;
	void* p_Master;
} DG_InternalData;



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

	void IsaOutByte(unsigned short Address, unsigned char value);
	unsigned char IsaInByte(unsigned short Address);
	void InitializeInternalData(DG_InternalData* p_Present);
	void Set_Delay_Trigger(DelayTriggerType* p_dt, DG_InternalData* p_Present); 
	void SetDelayTriggerControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																	DelayTriggerType* p_dt, DG_InternalData* p_Present);
	void Set_Prescaler(DG_BME_Registers* p_pdg, DG_InternalData* p_Present);
	void Set_Main_Counter(MainCounterType* p_mc, DG_InternalData* p_Present);
	void SetMainCounterControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																	MainCounterType* p_mc, DG_InternalData* p_Present);
	void Set_Reference_channel(DelayChannel* p_rf, DG_InternalData* p_Present);
	void SetReferenceControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
																DelayChannel* p_rf, DG_InternalData* p_Present);
	void Set_Delay_channel(DelayChannel* p_k, DelayChannel* p_m, short int pos, DG_InternalData* p_Present);
	void SetDelayControl(unsigned long* p_Prepare, unsigned long* p_FinalValue, 
				DelayChannel* p_k, DelayChannel* p_ChState, short int pos, DG_InternalData* p_Present);
	void Synchronize_DG_State(long DG_Number);
	void HardwareTest_BME_G03(long DG_Number);
	void HardwareTest_BME_G02(long DG_Number);
	void LoadPrescaler(unsigned long* p_value, DG_InternalData* p_Present);
	void LoadCommandRegister(unsigned short value, DG_InternalData* p_Present);
	void LoadCounterControl(unsigned long* p_value, DG_InternalData* p_Present);
	void PrepareCounterControl(DG_BME_Registers* p_pdg, DG_InternalData* p_Present);

	void ActionDC(unsigned long* p_Action, 
											 DelayChannelData* p_a, DelayChannelData* p_b, unsigned long DG_Product);
	void ActionDT(unsigned long* p_Action, DelayTriggerData* p_a, DelayTriggerData* p_b);
	BOOL IsEqualDT(DelayTriggerType* p_a, DelayTriggerType* p_b, unsigned long DG_Product);
	BOOL IsEqualMC(MainCounterType* p_a, MainCounterType* p_b, unsigned long DG_Product);
	BOOL IsEqualDC(DelayChannel* p_a, DelayChannel* p_b, unsigned long DG_Product);
	BOOL IsEqualPS(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product);
	BOOL IsEqual(DG_BME_Registers* p_a, DG_BME_Registers* p_b, unsigned long DG_Product);
	void CopyTriggerControl_V1(DelayTriggerData* p_dt, DelayTriggerData_V1* p_dtv1);
	void CopyTriggerControl_V2(DelayTriggerData* p_dt, DelayTriggerData_V2* p_dtv2);
	void CopyDelayControl(DelayChannelData* p_dc, DelayChannelData_V2* p_v2);
	void ResetDelayChannel(DelayChannel* p_dc);
	void ResetMainCounter(MainCounterType* p_mc);
	void ResetDelayTrigger(DelayTriggerType* p_dt);
	void ModifyControlRegister(DG_BME_Registers* p_pdg, DG_InternalData* p_Present);
	void ResetTriggerControl(DelayTriggerData* p_dt);
	void ResetDelayControl(DelayChannelData* p_dc);
	long SetChannel(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number);
	long SetReference(DelayChannel* p_a, DelayChannelData* p_dl, 
															unsigned long MainCounter, long DG_Number);
	BOOL ReadCalibrationFile(FILE *stream, int* p_module, char* FileName);
	void InitializeCalibrationConstants();
	long DelayNumbers(double* p_remainder, unsigned int* p_digital, double InValue, long DG_Number);
	long T0Numbers(unsigned int* p_digital, double InValue, long DG_Number);
	BOOL MasterDelayGenerator(HANDLE h_Master, int NumBytes, HANDLE h_Slave);
	BOOL MasterLineDG(HANDLE h_Master, int NumBytes, HANDLE h_Slave, int LineNo);
_declspec (dllexport) long CC ResetPciDelayGenerator(HANDLE h_Delgen);
_declspec (dllexport) long CC DataOut(unsigned short Address, void* p_data, HANDLE h_Device, int Size);
_declspec (dllexport) long CC DataIn(unsigned short Address, void* p_data, HANDLE h_Device, int Size);
