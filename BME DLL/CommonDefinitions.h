/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Constants and types for server and client
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
    Update:                    22. December 1998
    copyright:                 (c) 1998 by BME

----------------------------------------------------------------------------*/

//#define GoodOldToF
//#define HighMassToF
//#define EsiToF
//#define Neptune

//#define Reflector16Bit

#include <windows.h>
#include <time.h>
#include "..\Bme_g0x\DG_Data.h"
#include "ConfigurationDefinitions.h"

#define MaxNumDelGen							6
//#define GoodOldToFDelGen					4
//#define HighMassDelGen						4
//#define EsitofDelGen							2
//#define NeptuneDelGen							2

//#define MaxFormattableDelGen		max(GoodOldToFDelGen, EsitofDelGen)
#define MaxFormattableDelGen		4

#define MaxNoLoops						  8
#define MaxNoSlowDAC					  16
#define MaxSlaveOptions				  32
#define MaxNoLoopSegments       8

#define RepellerPosition				0


#define HARDWARE_CONFIGURATION		1
#define STRUCTURE_TABLE						2
#define ACTION_TABLE							3
#define MODIFICATION_TABLE				4
#define RECORDING_TABLE						5
#define FEEDBACK_TABLE						6
#define TRANSFER_DESCRIPTOR				7
#define MEASUREMENT_DATA					8
#define ERROR_REPORT							9
#define STANDBY_DATA							10
#define STANDBY_CONTROL						11

#define ZERO_SPECTRA							12
#define ACTIVATE_VOLTAGE					13
#define READJUST_VOLTAGE					14
#define TAKE_DATA									15
#define INTERRUPT_MEASUREMENT			16
#define CONTINUE_MEASUREMENT			17
#define STOP_MEASUREMENT					18
#define DEACTIVATE_VOLTAGE				19
#define COMMAND_ACKNOWLEDGE				20

#define MODIFY_ACTION_TABLE				21
#define MODIFY_CONTROL						22
#define MODIFY_STANDBY						23

#define ReflectorLensPosition		0
#define NeedlePosition					2
#define Aux1Position						3
#define PusherPosition					4
#define FocusPosition						5

#define ResoScale							(2.0 * sqrt(log(2.0)))
#define TimeBuffer						500.0
#define TimeToInterrupt				100.0
#define MaxGraphicsWindows		8
#define MaxCircle							50
#define MaxRecn								50
#define MaxNoSetup						8
#define PlanckTc							1239.703
#define BusCycleTime					1.3
#define GratingMax						285715
#define CalConst3002					2280.73
#define TriggerDelayADC				16
#define InterlaceDelay				31
#define MaxDAC								32
#define CheckLoop							0xA8104225
//#define CheckLoop							0x00000001
#define RelaisSerialLength		40
#define SwitchSerialLength		128
#define MaxValve							2
#define MaxLoopLength					14
#define MaxMemoLength					80
#define ListActivationLength	16
#define MaxTSParameter				16

#include "StandardDefinitions.h"
#include "OperationDefinitions.h"
   
typedef struct
{
    long           volatile ClockCounter; 
    unsigned short volatile ClockMin; 
    unsigned short volatile ClockMax; 
    unsigned short volatile Scaler,ClockDivider; 
    short          volatile OverrunCount; 
    long           volatile MeanTime;  

}   IntStatus, *pIntStatus;
   
   
typedef struct
{
	union
	{
		int		Info[16];
		struct
		{
			int MaxTdcFilled;
			int MinTdcFree;
			int MaxBufferNo;
			int BufferSkipped;
			int MaxBufferFilled;
			int MinBufferFree;
			int MaxInputNo;
			int InputSkipped;
			int MaxTransferNo;
			int TransferSkipped;
			int MaxTransferFilled;
			int MinTransferFree;
			int MaxReceiveNo;
			int ReceiveSkipped;
			int MaxReceiveFilled;
			int MinReceiveFree;
		};
	};
	BOOL RepRateNotification;
	double	NewRepRate;
}	BufferStatisticsType;
   
typedef struct
{
	union
	{
		double		Info[4];
		struct
		{
			double		RepRate;
			double		AverageDelay;
			double		ClockMax;
			double		ClockMin;
		};
	};
	int				OverrunCount;
}	IntStatisticsType;

typedef struct 
{
  int  ActiveMemory;
	int CurrentAction;
	BOOL CommandPerformed;
	BOOL DataAvailable;
	BOOL ServerActive;
	BOOL VoltageValid;
	BOOL HighVoltageActive;
	BOOL MeasurementActive;
	BOOL MeasurementWait;
} ServerStatusType;
   
typedef struct
{
	signed short Voltage[16];
}	OldDriftStatisticsType;
   
typedef struct
{
	unsigned short Voltage[MaxNoADC];
}	DriftStatisticsType;
   
typedef struct
{
	IntStatisticsType			Interrupt;
	BufferStatisticsType	Buffer;
	int										NoADCMeasurements;
	unsigned long					DigitalStatus;
	DriftStatisticsType		Drift;
	ServerStatusType			ServerStatus;
}	StatisticsType;
   
typedef struct
{
	int										NoADCMeasurements;
	unsigned long					DigitalStatus;
	DriftStatisticsType		Drift;
}	StandbyDataType;

typedef struct
{
	union
	{
		double		Info[2];
		struct
		{
			double		ZeroOrder;
			double		FirstOrder;
		};
	};
}	DriftResultType;

typedef struct
{
	union
	{
		unsigned short volatile TimeReg[3];
		struct
		{
			unsigned short volatile T0,T1,T2;
		};
	};
	unsigned char	Mode[3];
	BOOL	Active[3],DirectDefinition[3];
	BOOL	AnalogDefinition[3];
	double	Delay[3];
}  CounterRegisters;

typedef struct
{
	BOOL	m_Chromatography;
	BOOL	m_Continuously;
	BOOL	m_DownAndUp;
	BOOL	m_Downwards;
	BOOL	m_MassSpectra;
	BOOL	m_Once;
	BOOL	m_PeakSpectra;
	BOOL	m_UpAndDown;
	BOOL	m_Upwards;
} OldXParameterType;

typedef struct
{
	union
	{
		BOOL	Flag[MaxTSParameter];
		struct
		{
			BOOL	m_Chromatography;
			BOOL	m_Continuously;
			BOOL	m_DownAndUp;
			BOOL	m_Downwards;
			BOOL	m_MassSpectra;
			BOOL	m_Once;
			BOOL	m_PeakSpectra;
			BOOL	m_UpAndDown;
			BOOL	m_Upwards;
			BOOL	m_SubcycleLimit;
		};
	};
	union
	{
		int	IntNumber[MaxTSParameter];
		struct
		{
			int	MaxSubcycles;
		};
	};
} XParameterType;

typedef struct
{
	double Delay,TimeShift;
	double OffTime,SecondTrigger;
	BOOL Active,Positive,Terminate,HighDrive;
	BOOL OffTimeDefined,SecondTriggerDefined;
} DelayParameter;

typedef struct 
{
	DelayParameter T0,A,B;
	double MainCounterTime;
	BOOL Gate_AB;
	int DG_Product;
} DG_BME_Data;

typedef struct 
{
	double T0,A,B;
	BOOL	DoneT0,DoneA,DoneB;
	double CurrentT0,CurrentA,CurrentB;
} DG_BME_shift;

typedef struct 
{
	double Start,Stop;
	unsigned long PostTrigger;
	unsigned char ControlRegister, ChannelParameter, Frequency, Memory;
	BOOL Active,Dual;
	BOOL DirectDefinition;
} PAD_82_cntrl;

typedef struct 
{
	double FullScale,Offset;
	double Start,Stop;
	long Coupling,Bandwidth;
	long NoChannels,FirstChannel;
	int Baseline;
	BOOL Active;
} DC271_vert;

typedef struct 
{
	double Start,Stop,secpp;
	double TrigLevel,DelayTime;
	long NoChannels,NoSegments;
	long TrigCoupling,TrigSlope;
	unsigned long TrigSource;
	unsigned long UsedChannels,ConvertersPerChannel;
	BOOL Active;
	union
	{
		DC271_vert Chn[4];
		struct
		{
			DC271_vert C0;
			DC271_vert C1;
			DC271_vert C2;
			DC271_vert C3;
		};
	};
} DC271_cntrl;

typedef struct 
{
	double Start,Stop;
	int NoChannels;
	unsigned short PreTrigger,TimeBase,TriggerFilter;
	unsigned char AmpTrig, FunctionControl;
	BOOL Active;
} T_0410_cntrl;

typedef struct 
{
	double Start,Stop;
	double FstChan,Trigger;
	unsigned long PresetValue;
	unsigned long Range;
	BOOL Active,DirectDefinition;
} TDC_7886_cntrl;

typedef struct 
{
	unsigned short Register;
	BOOL DirectRegisterDefinition;
	CounterRegisters Timer;
} TimerIOCardType;

typedef struct 
{
	int Motor;
	unsigned short DacRegister[4];
	BOOL LaserActive,DacActive;
} IEC_cntrl;

typedef struct 
{
	unsigned long SerialBits[MaxLoopLength];
} LoopType;

typedef struct
{
	unsigned char		ADC[MaxNoADC];
	unsigned short  DAC[4];
	unsigned short	TTL_Register;
} ADC_cntrlType;

typedef struct 
{
	DG_BME_Registers	DG_BME[MaxNumDelGen];
	ADC_cntrlType			ADIODA_12;
	TimerIOCardType		Optoio_16,Witio_48;
	DC271_cntrl				DC_271;
	PAD_82_cntrl			PAD_82;
	T_0410_cntrl			T_0410;
	TDC_7886_cntrl		TDC_7886;
	IEC_cntrl					NAT_4882;
	LoopType					Loop[MaxNoLoops];
	int								RecList[MaxRecn];
	int								FbkList[MaxRecn];
	int								DiscValue[4];
	BOOL							InternalZero;
} ActionTableType;

typedef struct
{
	BOOL	Active;
	int		Gain;
} AdcSettingType;

typedef struct
{
	AdcSettingType	ADC[MaxNoADC];
	unsigned short  DAC[4];
	unsigned short	TTL_Register;
} ADC_CommandType;

typedef struct 
{
	double FullScale,Start,Stop;
	int Range,Bipolar,NoChannels,Baseline;
	BOOL Active;
} ADC_Channel;

typedef struct 
{
	double Start,Stop,nsecpp;
	double Threshold;
	BOOL Active;
	union
	{
		ADC_Channel Chn[4];
		struct
		{
			ADC_Channel C0;
			ADC_Channel C1;
			ADC_Channel C2;
			ADC_Channel C3;
		};
	};
} RecordingType;

typedef struct 
{
	double Open,Close;
	TCHAR Unit;
	TCHAR ControlState;
	BOOL Active;
	BOOL OpenDefine, CloseDefine;
} IonGateType;

typedef struct 
{
	double Wavelength;
	int Order;
	TCHAR Unit;
	BOOL Active;
	BOOL WavelengthDefine, OrderDefine;
} DyeLaserType;

typedef struct 
{
	double Beta,Delta,Start,Stop,Advance,Voltage;
	int DacSetting[4];
	TCHAR Unit,Trigger;
	BOOL Active,DefineDAC;
	BOOL BetaDefine, DeltaDefine, AdvanceDefine;
	BOOL StartDefine, StopDefine, VoltageDefine;
} MiniToFType;

typedef struct 
{
	DG_BME_Data					delgen[MaxNumDelGen];
	ADC_CommandType			Monitor_ADC;
	DyeLaserType				DyeLaser;	
	MiniToFType					MiniToF;
	IonGateType					IonGate;
	RecordingType				ADC,TDC,DGI;
	PAD_82_cntrl				PAD_82;
	TDC_7886_cntrl			TDC_7886;
	MinitofOpTableType	MinitofOperation;
	OperationTableType	Operation;
	int									RecList[MaxRecn];
	int									FbkList[MaxRecn];
	int									DiscValue[4];
	TimerIOCardType			Optoio_16,Witio_48;
	double							MainShift,AuxShift;
	double							VoltageScalingFactor;
	BOOL								FrequencyCompensation;
	BOOL								InternalZero;
} ActionInfoType;

typedef struct 
{
	int Action,RepeatFactor,DiscLevel,DeadSamples;
	int Channel,Range,Bipolar,NoChannels,Baseline;
	int Counter;
	TCHAR Unit,Mode,Source;
	double Start,Stop,nsecpp;
	double Target,SearchRange;
	double FullScale;
	int Int_Target,Int_SearchRange,Int_PresentReference;
	BOOL ShiftSpectrum,InternalZero;
} RecordingInfoType;

typedef struct 
{
	double Start,Stop,nsecpp,Target,SearchRange;
	int Int_Target,Int_SearchRange,Int_PresentReference;
	int Action,RepeatFactor,DiscLevel,DeadSamples;
	int ADC_Channel,Range,Bipolar,NoChannels;
	int Counter;
	int DelayGenerator;
	TCHAR Unit,Mode,Source;
	TCHAR DelayChannel,ShiftUnit;
	BOOL  AutoDefinition,InternalZero;
} FeedbackInfoType;

typedef struct
{
	union
	{
		BOOL	Active[ListActivationLength];
		struct
		{
			BOOL	Action;
			BOOL	Recording;
			BOOL	Feedback;
			BOOL	Groups;
			BOOL	Peaks;
			BOOL	Charts;
			BOOL	MassPeaks;
			BOOL	GatePeaks;
			BOOL	MinitofPeaks;
			BOOL	DriftVariables;
			BOOL	MassFitList;
			BOOL	Isotopes;
			BOOL	Substances;
			BOOL	LocatePeaks;
		};
	};
	union
	{
		int	Length[ListActivationLength];
		struct
		{
			int		NoAction;
			int		NoRecn;
			int		NoFeedback;
			int		NoGroups;
			int		NoPeaks;
			int		NoCharts;
			int		NoMassPeaks;
			int		NoGatePeaks;
			int		NoMinitofPeaks;
			int		NoDriftVariables;
			int		NoMassFitList;
			int		NoIsotopes;
			int		NoSubstances;
			int		NoLocatePeaks;
		};
	};
} ListActivationType;

typedef struct
{
	union
	{
		BOOL	Active[8];
		struct
		{
			BOOL	m_AuxTrigger;
			BOOL	m_MasterTrigger;
			BOOL	m_MinitofActive;
			BOOL	m_EsiActive;
			BOOL	m_RegisterCommands;
			BOOL	m_AllDelayGenerators;
			BOOL	m_DetectorTest;
			BOOL	m_IongateActive;
		};
	};
} ExpSetupType;
   
typedef struct
{
	union
	{
		BOOL		Info[MaxSlaveOptions];
		struct
		{
			BOOL			LoopActive[MaxNoLoops];
			BOOL			CheckLoopWord[MaxNoLoops];
			BOOL			WatchDogActive;
			BOOL			SquareWave;
			BOOL			SingleStep;
			BOOL			TestLoop;
			BOOL			FullInfo;
		};
	};
}	SlaveOptionType;

typedef struct
{
	BOOL							Master;
	int								DivideBy;
	int								BaseAddress;
	int								Product;
} DGC_Type;

typedef struct
{
	int					nVersion;
	int					DefaultConfiguration;
	int					TDC,Transient,ADC;
	int					TDC_Address,Transient_Address,ADC_Address;
	BOOL				VacuumMeasurement;
	int					ServerMemory;
	char				ServerNode[32];
	int					vNumDelGen;
	DGC_Type		DGC_List[MaxNumDelGen];
	int					vNoLoops;
	union
	{
		int		LoopPosition[MaxNoLoops];
		struct
		{
			int			vDetectorLoop;
			int			vEsqLoop;
			int			vReflectorLoop;
			int			vIopAnalogLoop;
			int			vIopSwitchLoop;
			int			vIopRelaisLoop;
		};
	};
} HwConfType;

   
typedef struct
{
	BOOL	Active;
	TCHAR Element;
	unsigned long Value;
	int	Length;
}	LoopSegmentType;

typedef struct
{
	BOOL							TestActive[MaxNoLoops];
	LoopSegmentType		LoopSegment[MaxNoLoopSegments];
}	LoopTestType;

typedef struct 
{
	_int64						Wait;
	int								LoopNo,LoopPosition;
	signed short			FreeRange,StepSize;
	BOOL							SlowDown;
} DACMotionType;

typedef struct
{
	union
	{
		DACMotionType	DAC[MaxNoSlowDAC];
		struct
		{
			DACMotionType	Repeller;
			DACMotionType	ReflectorLens;
			DACMotionType	Focus;
			DACMotionType	Pusher;
			DACMotionType	Needle;
			DACMotionType	Aux1;
		};
	};
} DACSlowDownType;

typedef struct 
{
	unsigned long			ValveBits[MaxLoopLength];
	unsigned long			GasBits[MaxLoopLength];
	unsigned long			PumpBits[MaxLoopLength];
} CheckValveType;

typedef struct 
{
	unsigned long			DACBits[MaxLoopLength];
	unsigned long			RelaisBits[MaxLoopLength];
	unsigned long			SlowDownBits[MaxLoopLength];
	_int64						Wait;
	int								Position,NoBits;
	int								FreeRange,StepSize;
	BOOL							SlowDown;
} CheckReversibleType;

typedef struct 
{
	CheckReversibleType		CheckList[MaxDAC];
	CheckValveType				CheckValve[MaxValve];
	unsigned long					StandByBits[MaxLoopLength];
	int SerialLine,ClockLine,StrobeLine,WatchDogLine;
	int InputLine;
	int Length;
	int NoDAC,NoRelais,NoValve;
	BOOL Reversible;
} LoopDefineType;

typedef struct 
{
	int NoSubCyc,NoAction,NoRecn,NoFeedback;
	int NoPeaks,NoCharts,NoXParameters;
	int NoMassPeaks,NoGatePeaks,NoMiniTofPeaks;
	int CircleList[MaxCircle];
	int ADC_Channels,DGI_Channels,TDC_Channels;
	int MilliSecPerSubcyc;
	TCHAR ReprateControl;
	BOOL DyeLaserActive,MiniToFActive;
	BOOL DacControlActive,DacActive;
	BOOL LocalExperimentActive;
	SlaveOptionType	SlaveOptions;
	LoopTestType  LoopTest;
	ExpSetupType ExpSetup;
	XParameterType TimeSequence;
	LoopDefineType LoopDef[MaxNoLoops];
} StructureInfo;

typedef struct 
{
	ADC_cntrlType			ADIODA_12;
} StandbyControlType;


typedef struct 
{
  int       DataType;
	int				DataLength;
	int				Direction;
} DataConfiguration;

typedef struct
{
	int	Length,Offset;
	int Counter;
	TCHAR Source;
} DataDescriptorType;

typedef struct
{
	int	Length,Offset;
	int MaxValue;
	TCHAR DataTreatment;
} CompressionDescriptorType;
