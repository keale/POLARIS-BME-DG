RSRC
 LVCCLBVW  1h  �      1H   x	 �  0           < � @       ����            Hz�ޯ9�@��t��          ����'B�4znG�����ُ ��	���B~  @                           . LVCCBME_DG_DelayTriggerData_V2.ctl                        0         E  �x�c`��� H120�5 iVt��P�E+� �\lv��^�F���M�f � cv```I@VņE' _��      . VIDSBME_DG_DelayTriggerData_V2.ctl            o  �x��`g`�4�0��0����
�;�b���"�cO��Q�
�.QQ�Q��e�l=�������zHwo����w���<y�f���"����}ͱd*���]K�J�[��@1F�9P&�FE��
��Q�`�8�a�V�Q�X�`T%بbj�6J�F=fu�������,��`J��B�h]�ɂ��B��L�t��u;���wG�X�@կ��e JJ��������g&�:��֩J���L���H��r�uڒ���l�'���O��P�uJ���!�:������,]�d�b��~�;��2�n;����v����7E���(qhȨ�@ �gd`f0c�cwC�r��]\��� �M��    	 �"  9.0    �  �//		DelayTriggerData:
//
// the structure ''DelayTriggerType'' has the controls for the trigger system,
// and trigger counters
//
// TriggerLevel:			trigger threshold in Volt. 
// GateLevel:					gate threshold in Volt (only for BME_SG08)
//							
// InternalClock:			period of the internal clock in microseconds
// InhibitTrigger:		time for which the trigger circuit should be deactivated
//										after a valid trigger event. 
// ForceTrigger:			time after a valid trigger event, when the delays
//										should be retriggered.
// StepBackTime:			time after a valid trigger event, when the delay list
//										are stepped back
// BurstCounter:			number of pulses after a valid external trigger event.
// GateDelay:					time that an external trigger event is delayed
// PresetLong:				64-bit version of PresetValue
// PresetValue:				preset value for the internal event counter. When
//										this number of triggers has occurred, the trigger will
//										be disabled, if the StopOnPreset flag is set.
// DivideBy:					the crystal oscillator will be divided by this number
// TriggerDivider:		the external clock will be divided by this number
// TriggerMultiplier:	the external clock will be multiplied by this number
// ClockSource:				defines which signal to use as clock source,
//										CrystalOscillator = 1 :    crystal oscillator only
//										TriggerInput = 2 :         trigger input only
//										TriggerAndOscillator = 3 : trigger input backed up 
//																						 by the crystal oscillator
//										(The corresponding constants are defined in DG_Data.h)
// GateDivider:				the external gate signal will be divided by this number.
//										A zero will mean that the state of the gate signal, as defined
//										by the PositiveGate flag will enable the trigger circuit.
//										A nonzero number always means the edge as defined by the
//										PositiveGate flag.
// MS_Bus:						The bits of this unsigned long variable define which of 
//										the trigger signals is placed on the master/slave bus.
//										See the definitions of LocalPrimary, LocalSecondary, LocalForce,
//										GateOnBusPositive, and GateOnBusNegative.
//										LocalPrimary =			0x1		:		the primary trigger signal is used to 
//																									start the channel
//										LocalSecondary =		0x2		:		the secondary trigger signal is used to 
//																									start the channel
//										LocalForce =				0x4		:   the signal from the force trigger counter is 
//																									used to start the channel
//										GateOnBusPositive =	0x100	:		a signal, which is high when the trigger system is active
//																									is placed as Start signal on the MS bus with positive polarity
//										GateOnBusNegative =	0x200	:		a signal, which is high when the trigger system is active
//																									is placed as Start signal on the MS bus with negative polarity
// PositiveGate:			set this flag to TRUE, if a positive signal on the gate input
//										should enable the trigger circuit, otherwise FALSE
// IgnoreGate:				set this flag to TRUE, if a gate signal should be ignored
//										as long as the InhibitTrigger counter has not yet elapsed.
//										Set this flag to FALSE, if a valid gate signal should
//										be memorized until the InhibitTrigger counter has elapsed.
// SynchronizeGate:		this flag defines the way the time difference is measured
//										between primary and secondary gate signal. Provided, the 
//										oscillator frequency to which the gate signal is referenced,
//										is above 70MHz, it is possible to provide a unique function
//										(number of oscillator cycles counter) <--> gate width
// ClockEnable:				set this flag to TRUE to enable the clock circuit
//                  
// InternalTrigger:		set this flag to TRUE, if internal triggering is used
//										Internal trigger exists only in the BME_G02, BME_SG02 and BME_G03
//										versions of the delay generator.
// InternalArm:				set this flag to TRUE, if internal rate counter is used to arm
//										the external trigger.
//										Internal trigger exists only in the BME_G02, BME_SG02 and BME_G03
//										versions of the delay generator.
// SoftwareTrigger:		set this flag to TRUE, if delay generator is to be triggered
//										by software command.
// RisingEdge:				TRUE triggers on rising edge of external trigger, 
//										FALSE triggers on falling edge of external trigger.
// StopOnPreset:			TRUE if trigger is to be disabled once preset of
//										TriggerCounter is reached.
// ResetWhenDone:			TRUE if all delay channels should be reset to the
//										ready state once all delays have elapsed.
// TriggerEnable:			TRUE to activate trigger circuit. This signal is or'ed with 
//										the signal coming from the external gate input. Actually,
//										the rising or falling edge of the (divided) gate signal clocks 
//										a flip-flop allowing a trigger. After a trigger has occurred,
//										the flip-flop is reset.
// Terminate:					TRUE to terminate the trigger input with 50 ohms. FALSE
//										for high-Z input. (Applies to BME_G03V4, BME_SG02V5)
// GateTerminate:			TRUE to terminate the gate input with 50 ohms. FALSE
//										for high-Z input. (Applies to BME_SG08)
// UseF:							set this flag to TRUE, if the gate signal should be derived
//										the F output connector instead of the regular gate input. (Applies to BME_SG08)

typedef struct
{
	double TriggerLevel;
	double GateLevel;
	union
	{
		double InternalClock;
		double InhibitTrigger;
	};
	double InhibitSecondary;
	double ForceTrigger;
	double StepBackTime;
	double GateDelay;
	unsigned long BurstCounter;
	unsigned long DelaySecondary;
	union
	{
		_int64 PresetLong;
		unsigned long PresetValue;
	};
	union
	{
		unsigned long	DivideBy;
		struct
		{
			unsigned short OscillatorDivider;
			unsigned short TriggerDivider;
		};
	};
	unsigned long TriggerMultiplier;
	unsigned long ClockSource;
	unsigned long GateDivider;
	unsigned long MS_Bus;
	BOOL PositiveGate;
	BOOL IgnoreGate;
	BOOL SynchronizeGate;
	BOOL ClockEnable;
	BOOL InternalTrigger;
	BOOL InternalArm;
	BOOL SoftwareTrigger;
	BOOL RisingEdge;
	BOOL StopOnPreset;
	BOOL ResetWhenDone;
	BOOL TriggerEnable;
	BOOL Terminate;
	BOOL GateTerminate;
	BOOL UseF;
} DelayTriggerData;    ������  �  �@ �� a�� ��  �� !�� A�� ��� �� �� �� �� �� �� �� �� ��0��,�����$���.9��$�� ���,��0�@ �  �  ����   ���������������������������������                              ��                              ��        +                     ��       +��              ��    ��      +����            �  �   ��   ��V                    �   ��       ���               �    ��       ���              �     ��       ���             �      ��       ���             ����   ��       ��� ��                 ��   ��V ���Vu�                 ��      +�P&Ju�+                ��     V��Jutu�+                ��      ����uv�+                ��      �����ʬ+                ��       ����V�+                ��   ��V ���  ++                ��       ���       ��+          ��       Ь�       ���+        ��       ���     ##���+      ��       ���       ����+    ��       ���       �����##  ��   V�V ���       ����+    ��               �����+      ��      +����      ���+        ��       +��       ��+          ��        +                     ��                              ��                              ���������������������������������         . FPHPBME_DG_DelayTriggerData_V2.ctl            
�  T�x���kp� �ݻ�9�B����ԏȎgS��!�ز���`�P�d	���\=���TIK>x:Çf2C_��C�B��a:	u�C��!�y4҄4�Hb��u�$�|�=�88i�a�ƾ�������u ���u*�� ZG���0�c��z����M '����.�����<��X-���.����¿ZϡS��e�&S��cSJ��V�o��;�*K�t�N���W\ewF�5����z��Q�0��N����5ֳeB���:b���}�F��A�J�"â��UTeؿ6�4T+\F#�aP3�8F�ń������ڙ�i�Q���|Pn�{E��o�?1�	K���mH���x3[ƞs�2�_}@ �ֱ�� fã���Nε�~�i��.tܕ ��8`P[�M`��^0dz�W��d8�/Cg$��{N8Cr�������V��c�Q;��P}3Q��6�W��V��֚/�V3T=��	�=Ay�>���_mJ�$�0����n
�={���Ee6��N��ŸRt���bW���o5{Ͽ��y�*P�8�u��w�����޽|	��q_RI�x�P~ė�_���Ҽ�/-F!��/m'���Bl�P�K�U�d��K�,���R����F�<#D�	Q�Pb���bvD>�Fd�5��IF��?"q��ٖ3"�e��1FלTШY���\#f.�闌�:�Nc���Fd�#f��u���!�k׮�!�"�HL�����nq����q�����,�:Q��cE�BM�]� �.
�0.��cGP1ꆵcwCeH�"[�����z�������	ۻ�c��=n5�&�F����G�J��~����Q�jG���7��h�fF��t��-��L{�jm.ނZ�̨���AT*K+�'��e0IWU����)��)U|i�N�[[�W/?��*���j��^�Yt5�3ң�f���~5.�W�\Mq�v�+k��KR�J��OBWs��t5�gwWc���k�֐jN8�ʨ�����W�5�Mc�v>g�+A�j��/��l���&?���Vq�ՙ�:�t�kn�5/@����͖㊚׫�\���Π'�	W�p�"�I�Z����u]_�(ݖ�����r�$ݖS��m9�Q��F7s��ݞ^��b����h�����mG�p#��'��Uj�F|�Ϲ�����-��ۼM��~�l���d��T�m���h��]�m�|�65e,�$�l�.H,��+Z^�Ҳ%�k�C�@�/_ԟM�n�"�t�$ɦ[$I6%�/ٔ�(��a$�%�C��an i>!�̾�(�M�d�{�3�&f�b6v�߻�WtþE�b�0I���_1�O���#���Z���]kd�ż���JfV�`=��wE��~YQ�G��Rw�����EG ����r�O$!��Lr�/�GNjDN� g�#�aq
�����I�í���5�/�l��d��u��C�n�$I�����5�Oat��ތn�s�{wV�u/Q�{�;���}� �$	8����5p�z���p�
7��soK�3#���W	��Z��`3Wty�d����Fl�z�a374�fnb`�!�n�n !��?��w��pu{��~��+~L�k�R���-��uZ?�Ql�+����"�GrRz��w��s���~��'�L�E2�I��c$I���9����a���ɴ(9�$��Mz�8�aq-��Wn���W�d�>����l&J��H�h�\��l�K��D�k��(��D2�BQ�J��~��p�o�?�I.�L��2
#2��$����C���Z��\"�ψ���Ii��cE��UB.v-���Vw�|>������$��"I����.k��}�al�0n��F�3)�ي�]j����
�ov=鵲��#�X�C��DYn.����˥r��p�2�1�l�ޕ敏*Z�Pi��j翺�w��7������#�18N�cp� i�a�i��6��~��!n Y�D��E�kT���Js2xV��#������� ����1�'`,? Zލ,ʝ�ޅ9���yB!���}�}@���w\��F�E��8�(wl�%:ފ����Z�8���[�=��w�gn_���Ų��$ˆ6�,��߲a�Fˆv��I�ݽ�E����V�tw�'���N]���A<c��l���$���Ib��� �{{�n���x2fS�U��ĸ�;'�yM�q��Trg �{7�!ӯ�'�I��7I�L�
�'��=���S0{"D�,�<#��B��!?�2�ut�k����!C�l���$��!�S�`;�u��!o`O�n_<��\\jX�9o���8��:�n�1	J�=��(ȋ���� �;�B^��\��9-B�f����UE�'d,��`fg�>�!���$����|�u7��4d1���]�i)d�,�e��"��lܼ�2�-	�x}>g8LO�_���J�6�'���2C��̰ Yf�5�qY��,�G��R��0��MOpI�7=)񍒮������D�w#&�|Y�7J>%	2��$���l��h�.���\~�L��z}�ǝ���"�_�j���~�����(����� I+�?`��s�;D�s���I
�K��U�rg����7�bɼ譈�[�ˉB��(�+��Q��Wa�Iz��� �N�4�Usmwp�?X[Q;�	0��b{����_l;�j}�JB� ��ؑ����(:�Hl#z��W�S�l�M      9               . BDHPBME_DG_DelayTriggerData_V2.ctl             b   rx�c``��`��P���I�+�!���YЏ�7���a �( 	����.��>��� �l���9�2-�����z�\�8Se�<� b                   �   (                                        �                   ha    ISUUA N 	                                                                       IS   ?          �  Cx��T[W[E�B B�����j��Z[�M�L-�H�\&aV'g�s� ��¿�����{�E���Z�����u�= zX��Q���D�T\������O���	�G5�����p�ȹt�Ɍ�EZ-��Ӂ��,B[��ș)�7b�p��9�m	�L��z	+�j�ad�:���%��*�0B�F wU��~7�0{����{�\y!}јڌ��ȓJ9F�)ގ���=�M��Xe�Q��DI{�΃J����1�ɡ$�̾Jh!VG��FeFnWG��a����%�3
t�IQnx���ML��$�A�Jd��E��̘9�8�̾�_��g�{2����e�}�''Aڽ��n��?;AK"�7�c��݁�2HR^"Pt�D/����`f�qtp�:<Kn-o�c���{w<���Ŏ%b̡�y��XDKXF+�b5�a��k������,5U��(ã���H/��t�)v��g�-�2���K�8'u�	�j�����3) ��L�����-����%�"�\Jv������}���d�����kz0�����u=�KÖu��������NvE��Z�ł��N��K;b�(�IS�"�"ʦ%��}3��/t8�>�l�j*���A:��vS@����?���:����Q���T˾���҈��9�7	m:���=���x�41G���%IeAF}�QN�����N��phUF���+�����ź&��$A�L˦U�ے�'Ӟx��W���(�-�~(t�-9�Ҝ,�j��_R�E�X��q�KX屌<�f"�r��1;��[)��Ԉ4�r���Dؾ�F��jn��d�q�n��vғ������vӳ��3�L~Z��A���g���� ���W���[|�G�<FM�p�6�=:x��G��gp����)3�����[�wq�9��R�����}Jx�b.q
��]S�۔�e�I9�sFk�w�2�$�����ac�[   q       X      � �   _      � �   f      � �   m� � �   � �   o� � �  � �TahomaTahomaTahoma00   RSRC
 LVCCLBVW  1h  �      1H               4  �   LVSR      TRTSG      hLIvi      |CONP      �TM80      �DFDS      �LIds      �VICD      �vers      �STRG      ICON      icl8      0CPC2      DLIfp      XFPHb      lFPSE      �IPSR      �CNST      �LPIN      �LIbd      �BDHb      �BDSE      �DTHP      MUID       HIST      4PRT       HVCTP      \FTAB      p                        ����       |        ����       �        ����       �        ����       �        ����       �        ����      <        ����      p       ����      �        ����      �        ����      �        ����      t        ����       x        ����       �        ����       �        ����      +|        ����      +�        ����      +�        ����      +�        ����      +�        ����      +�        ����      ,,        ����      ,4        ����      ,<        ����      ,D        ����      ,p        ����      ,�       �����      0�    BME_DG_DelayTriggerData_V2.ctl