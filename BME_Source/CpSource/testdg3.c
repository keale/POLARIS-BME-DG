#define PCI_CODE
#define PLX_LINUX
//#define PLX_BIG_ENDIAN
#define PLX_LITTLE_ENDIAN
#undef  WINDOWSNT
#undef  WINDOWS95
#undef  WINDOWS31

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <malloc.h>
#include <sys/io.h>
//#include <conio.h>
#include <stdio.h>
#include <math.h>
//#include <windows.h>
//#include "..\Spectra_BME\CommonDefinitions.h"
#include "PlxRout.h"
#include "DG_DLL_1.h"

int main (int argc, char **argv)
{
  long p_Error, ret, a, b ;
  BOOL master ;
  long  DG_Number ;
  DG_BME_Control *Pars ;

  Reserve_DG_Data (1L) ;
  Initialize_DG_BME(9,BME_SG02P2,0) ;
  Pars = (DG_BME_Control *) malloc(sizeof(DG_BME_Control)) ;  
  ResetControl (Pars) ;
  
  Pars->GateFunction = GateXOR ;
  Pars->OutputLevel = TTL_VoltageLevel ;
  Pars->DG_Product = BME_SG02P2 ;
  Pars->PulseWidth = 8 ;
  Pars->Gate_AB = FALSE ;

  Pars->T0.FireFirst = 1.0 ;
  Pars->T0.SetBack = -1.0 ;
  Pars->T0.FireSecond = -1.0 ;
  Pars->T0.OutputModulo = 1 ;
  Pars->T0.OutputOffset = 0 ;
  Pars->T0.GoSignal = MasterPrimary ;
  Pars->T0.DoneSignal = 0x0 ;
  Pars->T0.Positive = TRUE ;
  Pars->T0.Terminate = TRUE ;
  Pars->T0.HighDrive = FALSE ;
  Pars->T0.Reserve = FALSE ;

  Pars->A.FireFirst = 2.0 ;
  Pars->A.SetBack = -1.0 ;
  Pars->A.FireSecond = -1.0 ;
  Pars->A.OutputModulo = 1 ;
  Pars->A.OutputOffset = 0 ;
  Pars->A.GoSignal = MasterPrimary ;
  Pars->A.DoneSignal = 0x0 ;
  Pars->A.Positive = TRUE ;
  Pars->A.Terminate = TRUE ;
  Pars->A.HighDrive = FALSE ;
  Pars->A.Reserve = FALSE ;

  Pars->B.FireFirst = 3.0 ;
  Pars->B.SetBack = -1.0 ;
  Pars->B.FireSecond = -1.0 ;
  Pars->B.OutputModulo = 1 ;
  Pars->B.OutputOffset = 0 ;
  Pars->B.GoSignal = MasterPrimary ;
  Pars->B.DoneSignal = 0x0 ;
  Pars->B.Positive = TRUE ;
  Pars->B.Terminate = TRUE ;
  Pars->B.HighDrive = FALSE ;
  Pars->B.Reserve = FALSE ;

  Pars->DT.InternalClock = 100.0 ;
  Pars->DT.ForceTrigger = -1.0 ;
  Pars->DT.TriggerLevel = 1.25 ;
  Pars->DT.PresetValue = 0 ;
  Pars->DT.MS_Bus = LocalPrimary ;
  Pars->DT.OscillatorDivider = 8 ;
  Pars->DT.TriggerDivider = 1 ;
  Pars->DT.ClockSource = CrystalOscillator ;
  Pars->DT.GateDivider = 1 ;
  Pars->DT.PositiveGate = TRUE ;
  Pars->DT.IgnoreGate = FALSE ;
  Pars->DT.SynchronizeGate = FALSE ;
  Pars->DT.ClockEnable = TRUE ;
  Pars->DT.InternalTrigger = TRUE ;
  Pars->DT.InternalArm = FALSE ;
  Pars->DT.SoftwareTrigger = FALSE ;
  Pars->DT.RisingEdge = FALSE ;
  Pars->DT.StopOnPreset = FALSE ;
  Pars->DT.ResetWhenDone = TRUE ;
  Pars->DT.TriggerEnable = TRUE ;
  Pars->DT.Terminate = TRUE ;
  Pars->DT.Reserve = FALSE ;
  
  SetDelayGenerator (Pars, 0L) ;
  Activate_DG_BME (0L) ;
  while (getchar()) ;
  // Test_BME_G02 (0L) ;
  Deactivate_DG_BME (0L) ;
  Release_DG_Data () ;
  return 0 ; 
}
