RSRC
 LVCCLBVW  *,  �      *      POLARIS BME DG.lvlib      x	 �  0           < � @�      ����            �c��G���h\�m          �8v��nHB�K u�\���ُ ��	���B~  @                           v LVCC3POLARIS BME DG.lvlib:BME_DG_DelayChannelData_V2.ctl      VILB      PTH0        POLARIS BME DG.lvlib               $            0        t  )�x���;@@��)t�a�f�z� � QPH���o��dR:�BD�R=D6������X�������
   � w    �/� �[���q������+��*�~--�j��[vYm ,"y   B VIDS3POLARIS BME DG.lvlib:BME_DG_DelayChannelData_V2.ctl             Xx�;����ila��� ��)� �(��!>.*2:�����������������L'�� �����]y:]d�L�`�Kd��
��1t���Dd� �/@��)*"� F	���@�;@2���49���bLw���?K�����s@�g!�xK,ƃ5�������!
?pJ:yx�������������˃'������$�)p���w}b��]������x<�|��ۢ��Kg�n���1�����@)��/��@y��7�١:�k����'��e��|�佛�̋�f3<���58�������%+�l>��|�ÿ�?C����7;�)���o}Č%飄��Pz�J:ko���Pz�Y{J ���eB������gF��4�� ��	��K� s?�v<��dY����@�#H�w#��t��|g@�wF��(��@���KP�usw�Y�B��$Ȼ,@�`��i�=���#@U���t`�v�w�Y�C5�(I����:�$��$��%I�}RTo$Iu3	�K#�V�O�JV0V���'���'�ⳔaG/0u�i�Pb �;ΰ�h�PX���V	�s����3P�A \AH#3�-�G�������n7  J(�r    	 �"  9.0    ]  Y//																					the selection of the DelayClock bit
//																					(only possible for the T channel of the 
//																					versions BME_SG05P2, BME_SG05P3, 
//																					BME_SG02P4, BME_SG02P5, and the A and B channel
//																					of the version BME_SG08P1)
//							DelayClock		=	 0x100	:		if this bit is set together with the 
//																					SystemClock, the delay clock of the 
//																					delay generator is routed to the output of 
//																					this channel, otherwise the system clock 
//																					will be routed to the output of this 
//																					channel
//																					(only possible for the T channel of the 
//																					versions BME_SG05P3, BME_SG02P5, and the A and B channel
//																					of the version BME_SG08P1)
//							InhibitLocal	=	 0x200	:		when the delay generator runs from an external clock,
//																					backed up by the local oscillator, this channel will
//																					only give an output when running from the local oscillator, 
//																					if this bit has not been set.
//							StartLocal		=	 0x400	:		when this bit is set, the signal from the local F output
//																					connector is used to set the delay lists to their start position.
//							StartBus			=	 0x800	:		when this bit is set, the signal from the F output connector
//																					of the master card is used to set the delay lists the their start position.
//							StepBackLocal	=	 0x1000	:		when this bit is set, the signal from the local step back counter
//																					is used to step the delay lists back as prescribed by the
//																					value in the Step Back array.
//							StepBackBus		=	 0x2000	:		when this bit is set, the signal from the step back counter of the master card
//																					is used to step the delay lists back as prescribed by the
//																					value in the Step Back array.
//							RunCircle			=	 0x4000	:		when this bit is set, the delay lists is not run from start to end, but when
//																					the end is reached, the next item to be used in the delay list is referenced by the
//																					step back pointer.
//							EnableFromE		=	 0x10000:		when this bit is set, the delay channel will only produce an output signal 
//																					when the signal coming from the E output connector is true.
//							EnableFromF		=	 0x20000:		when this bit is set, the delay channel will only produce an output signal 
//																					when the signal coming from the F output connector is true.
//							EnableFromBus	=	 0x40000:		when this bit is set, the delay channel will only produce an output signal 
//																					when the signal coming from the master/slave bus is true.
// DoneSignal:	the bits of this unsigned long define which of the trigger signals
//							is immediatly acknowledged by a delay channel
// Positive:		set this flag to TRUE for positive polarity of output
//							set this flag to FALSE for negative polarity of output
//							(applies to BME_G03V4, BME_SG02V5)
// Terminate:		TRUE to apply an internal termination to the output channel.
//							(not yet implemented on hardware)
// HighDrive:		TRUE to supply extra current for a 25 ohm load.
//							(not yet implemented on hardware)
// Disconnect:		set this flag to TRUE for channels E or F of the BME_SG08 card
//								if the output driver should be disconnected from the connector
//								at the slot. The output driver must be disconnected, if some
//								external signal is to be entered.
// OntoMsBus:			set this flag to TRUE for channels E or F of the BME_SG08 card
//								if the signal from this connector should be placed onto the 
//								master/slave bus for use at the slave cards
// InputPositive:	set this flag to FALSE for channels E or F of the BME_SG08 card
//	              if the signal should be inverted before it is used e.g. as enable

typedef struct
{
	union
	{
		double FireFirst;
		double DelayTime[MemDepth];
	};
	double PulseWidth[MemDepth];
	double SetBack;
	unsigned long StepBack[MemDepth];
	signed long ListLength;
	signed long	OutputModulo;
	signed long	OutputOffset;
	unsigned long GoSignal;
	unsigned long DoneSignal;
	BOOL Positive;
	BOOL Terminate;
	BOOL HighDrive;
	BOOL Disconnect;
	BOOL OntoMsBus;
	BOOL InputPositive;
} DelayChannelData;      ������  �  �@ �� !�� a�  !�� !�� !�� !�� !�� �� �� �� �� �� �� �� ��0��,�����$���.9��$�� ���,��0�@ �  �  ����   ���������������������������������                              ��                              ��        +                     ��       +��               �    ��      +����             ��    ��   ��V                   �    ��       ���               �    ��       ���               �    ��       ���               �    ��       ���               �    ��       ��� ��                 ��   ��V ���Vu�                 ��      +�P&Ju�+                ��     V��Jutu�+                ��      ����uv�+                ��      �����ʬ+                ��       ����V�+                ��   ��V ���  ++                ��       ���       ��+          ��       Ь�       ���+        ��       ���     ##���+      ��       ���       ����+    ��       ���       �����##  ��   V�V ���       ����+    ��               �����+      ��      +����      ���+        ��       +��       ��+          ��        +                     ��                              ��                              ���������������������������������         B FPHP3POLARIS BME DG.lvlib:BME_DG_DelayChannelData_V2.ctl           	�  c�x��kl��ϝ�}��c�~,�v��Tqb�W	!�@ 5�b(��l�bo1k׻N� U[Z'JԨi�R�m�<�|���Z�:���*�#R!��Cɣ�EP�����>fvg�Ô�G�䫑uϽ���;�;s��O���L a/�Eg���lqB��]�S /I�f�.�5C'��kr���pQ��@ǞǪv֋-�P��T���Y���ܸ-�d9��>Nf����+�ǣ��D�Ų��� ��&���
D9��Wjҕ ��-��˰E���I⡚��d��M6����3N�S��j���1���S��}�\�f��-�`?�S��u3�c��]r1�D��'G,���4�����N����m���'� ��%L�R<�V
�Q�"��m�RH���k	ۍ��	h�ƨ��`��)h�����Z0��X�kA6Ik���Y�,���g��g&X>0������P(0��FzsWgs��.�!�Q5+gz&&&p�Xf\W�kO�U�E�����g�M�53mkp�����'�q-%![."K���$|������sR�'��G*�%}�T�.��V����|WH����e�`�A�=ZU���ip[r0+`���*���I�{p���h����*�`?�S�J�v>�f���T_�<8z�hvt�T���t6\����K�4}�H�P.�u��cv�����(��V��\ƣ� %��:��oKhd,�5F�g���	��c\�qq�����Aܙ�P!{zz����G�3T��j�Foiݗl�4�Tcj����j�x��J���'ObKXV��h)�Kfh�d��X)V�IU�ŒmH�Y��Al>����b����DS���iE4�п�x4}���SES�`j��w-/��Tfƫ0���}�;��M�Bl�j�ܝt}����uK���ۊ>]	ƛu�*G����YoU�"ŭjG�|���|�T/45��!ɏ�I^�$��YE2���$߫�dw��Pdxk�},�C1u�(S��b�#3QL}<�S�����Ō��D��Ŧ/S���(vO�x�^�;��Hg 4�)f�#�\3��`��/
�����E3��~i��v�ll�+`ێ�c�#��A��|��>!L���v%ɶ=�I�rd@����F�����g�+a��+u����ڹW�r�m)?˥�l��_3`T�|Ԯ�����(��)��T��l6�ʰ�N�䪳q��\��Q�d��`49�/uN��c4_SI�L��i��ro���gڽ�����Kq��}���7�w[�������ި��P�;5��{Wj�Qf|e��:�N�=\���(����4��p�{�Q�s9����v�6��aEf���	�'�!m��@Ac)�\)�A�ۼm��.὇����D1sm
��'�y"sИ��,����3�p�>�p�:z���(��"^�>9�x�������?W��Y/�x9�اR�T�C��rf�ʺ��+�D�DpWUV�ל�Օ5�˚���&v����,u��.��}uu���V�56��#�a]��{������[�T�v�T��G���'}se�}۰����з�ѷ�з�ַwꛭGC��I}��-�o�w��o��n��}L�L�I��q3�����7�y��f�ҷ��>�pQ4��wJ]6�?]��g��{L�VԽ�Y�G˫{!���>���=�':e�~�h�G��L�G��L�G�ܠ���i�^i������q٣_4 {�K�/{��Fe�~Š�ѿА�Iك
��K���h�~3��${�o�e�j�^�.�ct������Za�ZM��b�w��u��/�����P(Я�	�Ey3o�`�7���f���ܿ��}l�ͼ��,(���d[�\B�k����֞�v�N7�Q������P̛�⍦�x�<P|�Q�7kP��R�lMS|F�"��A}��;/żn�wFC��C,;�s�e��(f�l&����p��>��X�נ�"�b��4�H��SQL�:/�ktR���{�>U��ߘ	b�3AL�v�!�'BL��q�ķ�!>�O@��5y!��{+�C���@�w(��š���x��(�s(^o��4(^�K1u0MqR|8�VLE�R�J'��{��0L}�8�	���a�;fb���<�&7z��Q�={��!�=ТfxQ^���d�t�Xdd,�}߾p �uSq8^l*�������q�Q�}Wi���K��%e�q��8&�y9�q}o���pL�E�|�L��f��=��A�IH���\�����'�)8��L?��q�N�݁H���m�S7a�7��fB�6��ùG~daxF�ٿ�x]�X��ď(4��{�� Xf�e�Yf�e�Yf�e�Yf�e���Xf�e�Yf�e�Yf�e�Yf�gˬw�Yf�e�YfYa�9]�n�f�P����S���dpnqnd�Q3�$��y�yy��֘�LT���7�gꜵ����         �               B BDHP3POLARIS BME DG.lvlib:BME_DG_DelayChannelData_V2.ctl            b   rx�c``��`��P���I�+�!���YЏ�7���a �( 	����.��>��� �l���9�2-�����z�\�8Se�<� b                   
�   (                                        �                   ha    ISUUA N 	                                                                       IS   ?          L  �x��Tks�D=����8mڔ6�B��@��j�N�$�'6�� KkG��5�U��S�?�_�wf�H���d��=�sϽ:{�\��V��	~���B�o~��-g���B�*^�Ɓ�|O�)Ԙ^�	�p�_X�p��틜|���D��5�@��W�P�#}�dV��I�����3*���.Ȟ?
� �R�@��>{Е�����⃾��~�h1O��Ggv�R�2�}��0��3:��G��̷��!U\��9������ �ֻ��g'��n����}���`��S��4m^��a��v�s��Ѿ�<��XEK0`b<J(��*jXa�^�w.�.���y&��(�3�d���W%�e�u�ʨ�#�D��0�h�6�� !��S��;xw�����e�A�Ⓑ�;�K�nsma�jw��o�]�������z<1ո��-�6qo�<�Կf����h�o���.�[��P�\�=1�tX�0�IS�4�����.M6a�H5Q�s#�'%<RM䇁Cw׬�i��x�l���^�r�?j3�@�S�ߒ1Q�<�*�hJ�ּGh�б�ă��v"O�I�5���e�J)���:�%�T�$����%sZ�W�kb*���h�E��DV�e���Nį���@�t};2�B��LS��F�m{SΛ��hEr|��KY�1�4h�	���8����"j̲��kEŃ�l"��ᮕLF���J�q�e'��"7.#}��mg���X"f��-|��>�>>����G�_�K<�W���	��w�?�)3���&l<Gk>�9�AɌ�с����x�k�������6w������,���%f8�F�VX�D'r��o*.�   q       X      � �   _      � �   f      � �   m� � �   � �   o� � �  � �TahomaTahomaTahoma00   RSRC
 LVCCLBVW  *,  �      *               4  �   LIBN      `LVSR      tRTSG      �LIvi      �CONP      �TM80      �DFDS      �LIds      �VICD       vers      STRG      (ICON      <icl8      PCPC2      dLIfp      xFPHb      �FPSE      �IPSR      �CNST      �LPIN      �LIbd      �BDHb      BDSE      DTHP      ,MUID      @HIST      TPRT       hVCTP      |FTAB      �    ����                                    ����       �        ����       �        ����      ,        ����      4        ����      \        ����      �        ����             ����      �        ����      �        ����              ����      �        ����      �        ����      �        ����      �        ����      $�        ����      $�        ����      $�        ����      $�        ����      $�        ����      %        ����      %|        ����      %�        ����      %�        ����      %�        ����      %�        ����      &D       �����      )�    BME_DG_DelayChannelData_V2.ctl