<?xml version='1.0' encoding='UTF-8'?>
<Library LVVersion="9008000">
	<Property Name="NI.Lib.Description" Type="Str">GERMAN

Diese Bibliothek bietet LVOOP Klassen für die BME PCI Delaygeneratoren (i.w. DG). 
Momentan werden die Produkte SG02P2, SG05P1, SG05P3, SG08P2 unterstützt. 
Die Klassen können auch mit  anderen Versionen arbeiten, dafür ist aber ein Test mit der jeweiligen Hardware (i.w. HW) erforderlich.

Die Basisklassen sind BME_DG_Base, welche die gemeinsamen Funktionen und Parameter für alle DGs  bereitstellen und BME_DG_Chnl entsprechend für Kanäle (i.w. Chnl).



ENGLISH

This Library offers some LVOOP classes for BME PCI Delay Generators (DG). Currently the types SG02P2, SG05P1, SG05P3, SG08P2  are supported. The operation with other types is possible, but requires intensive test.



author: Alexander Kessler, Helmholtz-Institut-Jena 
maintainer: Alexander Kessler: alexander.kessler@uni-jena.de

Last Change: 2012-07-03


License Agreement for this software:

Copyright (C)
Helmholtz-Institut-Jena
Fröbelsteg 3
07743 Jena
Germany

Contact: alexander.kessler@uni-jena.de

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the license, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General License for more details (http://www.gnu.org).

</Property>
	<Property Name="NI.Lib.HelpPath" Type="Str"></Property>
	<Property Name="NI.Lib.Icon" Type="Bin">#1#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!(]!!!*Q(C=\&gt;8"&lt;2MR%!813:!!O;K$1#V-#WJ",5Q,OPKI&amp;K9&amp;N;!7JA7VI";=JQVBZ"4F%#-ZG/O26X_ZZ$/87%&gt;M\6P%FXB^VL\_NHV=@X&lt;^39O0^N(_&lt;8NZOEH@@=^_CM?,3)VK63LD-&gt;8LS%=_]J'0@/1N&lt;XH,7^\SFJ?]Z#5P?=F,HP+5JTTF+5`Z&gt;MB$(P+1)YX*RU2DU$(![)Q3YW.YBG&gt;YBM@8'*\B':\B'2Z&gt;9HC':XC':XD=&amp;M-T0--T0-.DK%USWS(H'2\$2`-U4`-U4`/9-JKH!&gt;JE&lt;?!W#%;UC_WE?:KH?:R']T20]T20]\A=T&gt;-]T&gt;-]T?/7&lt;66[UTQ//9^BIHC+JXC+JXA-(=640-640-6DOCC?YCG)-G%:(#(+4;6$_6)]R?.8&amp;%`R&amp;%`R&amp;)^,WR/K&lt;75?GM=BZUG?Z%G?Z%E?1U4S*%`S*%`S'$;3*XG3*XG3RV320-G40!G3*D6^J-(3D;F4#J,(T\:&lt;=HN+P5FS/S,7ZIWV+7.NNFC&lt;+.&lt;GC0819TX-7!]JVO,(7N29CR6L%7,^=&lt;(1M4#R*IFV][.DX(X?V&amp;6&gt;V&amp;G&gt;V&amp;%&gt;V&amp;\N(L@_Z9\X_TVONVN=L^?Y8#ZR0J`D&gt;$L&amp;]8C-Q_%1_`U_&gt;LP&gt;WWPAO_0NB@$TP@4C`%`KH@[8`A@PRPA=PYZLD8Y![_ML^!!!!!!</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Item Name="Binaries and C" Type="Folder">
		<Item Name="CpSource" Type="Folder">
			<Item Name="BME_G0X.cpp" Type="Document" URL="../BME_Source/CpSource/BME_G0X.cpp"/>
			<Item Name="BME_G0X.h" Type="Document" URL="../BME_Source/CpSource/BME_G0X.h"/>
			<Item Name="BME_G0XDoc.cpp" Type="Document" URL="../BME_Source/CpSource/BME_G0XDoc.cpp"/>
			<Item Name="BME_G0XDoc.h" Type="Document" URL="../BME_Source/CpSource/BME_G0XDoc.h"/>
			<Item Name="BME_G0XView.cpp" Type="Document" URL="../BME_Source/CpSource/BME_G0XView.cpp"/>
			<Item Name="BME_G0XView.h" Type="Document" URL="../BME_Source/CpSource/BME_G0XView.h"/>
			<Item Name="ConfigurationTableDlg.cpp" Type="Document" URL="../BME_Source/CpSource/ConfigurationTableDlg.cpp"/>
			<Item Name="ConfigurationTableDlg.h" Type="Document" URL="../BME_Source/CpSource/ConfigurationTableDlg.h"/>
			<Item Name="CursorEdit.cpp" Type="Document" URL="../BME_Source/CpSource/CursorEdit.cpp"/>
			<Item Name="CursorEdit.h" Type="Document" URL="../BME_Source/CpSource/CursorEdit.h"/>
			<Item Name="DefineDelayGeneratorDlg.cpp" Type="Document" URL="../BME_Source/CpSource/DefineDelayGeneratorDlg.cpp"/>
			<Item Name="DefineDelayGeneratorDlg.h" Type="Document" URL="../BME_Source/CpSource/DefineDelayGeneratorDlg.h"/>
			<Item Name="DelgenControl.cpp" Type="Document" URL="../BME_Source/CpSource/DelgenControl.cpp"/>
			<Item Name="DelgenControl.h" Type="Document" URL="../BME_Source/CpSource/DelgenControl.h"/>
			<Item Name="DelgenData.cpp" Type="Document" URL="../BME_Source/CpSource/DelgenData.cpp"/>
			<Item Name="DelgenData.h" Type="Document" URL="../BME_Source/CpSource/DelgenData.h"/>
			<Item Name="DelgenParametersPS.cpp" Type="Document" URL="../BME_Source/CpSource/DelgenParametersPS.cpp"/>
			<Item Name="DelgenParametersPS.h" Type="Document" URL="../BME_Source/CpSource/DelgenParametersPS.h"/>
			<Item Name="DG_Data.h" Type="Document" URL="../BME_Source/CpSource/DG_Data.h"/>
			<Item Name="DG_DLL.cpp" Type="Document" URL="../BME_Source/CpSource/DG_DLL.cpp"/>
			<Item Name="DG_DLL.h" Type="Document" URL="../BME_Source/CpSource/DG_DLL.h"/>
			<Item Name="DoneSelectDlg.cpp" Type="Document" URL="../BME_Source/CpSource/DoneSelectDlg.cpp"/>
			<Item Name="DoneSelectDlg.h" Type="Document" URL="../BME_Source/CpSource/DoneSelectDlg.h"/>
			<Item Name="EthernetAddressDlg.cpp" Type="Document" URL="../BME_Source/CpSource/EthernetAddressDlg.cpp"/>
			<Item Name="EthernetAddressDlg.h" Type="Document" URL="../BME_Source/CpSource/EthernetAddressDlg.h"/>
			<Item Name="FileOptionsDlg.cpp" Type="Document" URL="../BME_Source/CpSource/FileOptionsDlg.cpp"/>
			<Item Name="FileOptionsDlg.h" Type="Document" URL="../BME_Source/CpSource/FileOptionsDlg.h"/>
			<Item Name="Fmcddev.cpp" Type="Document" URL="../BME_Source/CpSource/Fmcddev.cpp"/>
			<Item Name="G02MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G02MasterPP.cpp"/>
			<Item Name="G02MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G02MasterPP.h"/>
			<Item Name="G02p3MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G02p3MasterPP.cpp"/>
			<Item Name="G02p3MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G02p3MasterPP.h"/>
			<Item Name="G02SlavePP.cpp" Type="Document" URL="../BME_Source/CpSource/G02SlavePP.cpp"/>
			<Item Name="G02SlavePP.h" Type="Document" URL="../BME_Source/CpSource/G02SlavePP.h"/>
			<Item Name="G03MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G03MasterPP.cpp"/>
			<Item Name="G03MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G03MasterPP.h"/>
			<Item Name="G03SlavePP.cpp" Type="Document" URL="../BME_Source/CpSource/G03SlavePP.cpp"/>
			<Item Name="G03SlavePP.h" Type="Document" URL="../BME_Source/CpSource/G03SlavePP.h"/>
			<Item Name="G04MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G04MasterPP.cpp"/>
			<Item Name="G04MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G04MasterPP.h"/>
			<Item Name="G04SlavePP.cpp" Type="Document" URL="../BME_Source/CpSource/G04SlavePP.cpp"/>
			<Item Name="G04SlavePP.h" Type="Document" URL="../BME_Source/CpSource/G04SlavePP.h"/>
			<Item Name="G05MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G05MasterPP.cpp"/>
			<Item Name="G05MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G05MasterPP.h"/>
			<Item Name="G05p2MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G05p2MasterPP.cpp"/>
			<Item Name="G05p2MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G05p2MasterPP.h"/>
			<Item Name="G05p4MasterPP.cpp" Type="Document" URL="../BME_Source/CpSource/G05p4MasterPP.cpp"/>
			<Item Name="G05p4MasterPP.h" Type="Document" URL="../BME_Source/CpSource/G05p4MasterPP.h"/>
			<Item Name="G05SlavePP.cpp" Type="Document" URL="../BME_Source/CpSource/G05SlavePP.cpp"/>
			<Item Name="G05SlavePP.h" Type="Document" URL="../BME_Source/CpSource/G05SlavePP.h"/>
			<Item Name="G0xData.cpp" Type="Document" URL="../BME_Source/CpSource/G0xData.cpp"/>
			<Item Name="G0xData.h" Type="Document" URL="../BME_Source/CpSource/G0xData.h"/>
			<Item Name="ListRout.cpp" Type="Document" URL="../BME_Source/CpSource/ListRout.cpp"/>
			<Item Name="ListRout.h" Type="Document" URL="../BME_Source/CpSource/ListRout.h"/>
			<Item Name="MainFrm.cpp" Type="Document" URL="../BME_Source/CpSource/MainFrm.cpp"/>
			<Item Name="MainFrm.h" Type="Document" URL="../BME_Source/CpSource/MainFrm.h"/>
			<Item Name="ParameterRoutineDlg.cpp" Type="Document" URL="../BME_Source/CpSource/ParameterRoutineDlg.cpp"/>
			<Item Name="ParameterRoutineDlg.h" Type="Document" URL="../BME_Source/CpSource/ParameterRoutineDlg.h"/>
			<Item Name="PlxRout.cpp" Type="Document" URL="../BME_Source/CpSource/PlxRout.cpp"/>
			<Item Name="PlxRout.h" Type="Document" URL="../BME_Source/CpSource/PlxRout.h"/>
			<Item Name="resource.h" Type="Document" URL="../BME_Source/CpSource/resource.h"/>
			<Item Name="StdAfx.cpp" Type="Document" URL="../BME_Source/CpSource/StdAfx.cpp"/>
			<Item Name="StdAfx.h" Type="Document" URL="../BME_Source/CpSource/StdAfx.h"/>
			<Item Name="stdafx2.h" Type="Document" URL="../BME_Source/CpSource/stdafx2.h"/>
			<Item Name="StringRout.cpp" Type="Document" URL="../BME_Source/CpSource/StringRout.cpp"/>
			<Item Name="StringRout.h" Type="Document" URL="../BME_Source/CpSource/StringRout.h"/>
			<Item Name="StrRout.cpp" Type="Document" URL="../BME_Source/CpSource/StrRout.cpp"/>
			<Item Name="StrRout.h" Type="Document" URL="../BME_Source/CpSource/StrRout.h"/>
			<Item Name="testdg3.c" Type="Document" URL="../BME_Source/CpSource/testdg3.c"/>
			<Item Name="TimeListDlg.cpp" Type="Document" URL="../BME_Source/CpSource/TimeListDlg.cpp"/>
			<Item Name="TimeListDlg.h" Type="Document" URL="../BME_Source/CpSource/TimeListDlg.h"/>
			<Item Name="TimeSequenceDlg.cpp" Type="Document" URL="../BME_Source/CpSource/TimeSequenceDlg.cpp"/>
			<Item Name="TimeSequenceDlg.h" Type="Document" URL="../BME_Source/CpSource/TimeSequenceDlg.h"/>
		</Item>
		<Item Name="Csource" Type="Folder">
			<Item Name="bme_net.c" Type="Document" URL="../BME_Source/Csource/bme_net.c"/>
			<Item Name="BME_Net.h" Type="Document" URL="../BME_Source/Csource/BME_Net.h"/>
			<Item Name="CommonDefinitions.h" Type="Document" URL="../BME_Source/Csource/CommonDefinitions.h"/>
			<Item Name="DG_DLL_1.c" Type="Document" URL="../BME_Source/Csource/DG_DLL_1.c"/>
			<Item Name="DG_DLL_1.h" Type="Document" URL="../BME_Source/Csource/DG_DLL_1.h"/>
			<Item Name="FMCDDEV.H" Type="Document" URL="../BME_Source/Csource/FMCDDEV.H"/>
			<Item Name="MCDIOCTL.H" Type="Document" URL="../BME_Source/Csource/MCDIOCTL.H"/>
			<Item Name="PlxRout.c" Type="Document" URL="../BME_Source/Csource/PlxRout.c"/>
			<Item Name="StandardDefinitions.h" Type="Document" URL="../BME_Source/Csource/StandardDefinitions.h"/>
			<Item Name="StringRout_C.c" Type="Document" URL="../BME_Source/Csource/StringRout_C.c"/>
			<Item Name="StringRout_C.h" Type="Document" URL="../BME_Source/Csource/StringRout_C.h"/>
		</Item>
		<Item Name="DelayGenerator.dll" Type="Document" URL="../BME DLL/DelayGenerator.dll"/>
	</Item>
	<Item Name="Doku" Type="Folder">
		<Item Name="Bme_g0x.hlp" Type="Document" URL="../LV-BME Interface/Bme_g0x.hlp"/>
		<Item Name="POLARIS BME DG Docu.odt" Type="Document" URL="../Docu/POLARIS BME DG Docu.odt"/>
	</Item>
	<Item Name="Utility" Type="Folder">
		<Item Name="Conditional Error to Warning.vi" Type="VI" URL="../utility/Conditional Error to Warning.vi"/>
		<Item Name="Remove empty Errors.vi" Type="VI" URL="../utility/Remove empty Errors.vi"/>
		<Item Name="replace dot with coma if loc dez poin used.vi" Type="VI" URL="../utility/replace dot with coma if loc dez poin used.vi"/>
		<Item Name="TriggerModuloLCMultiple.vi" Type="VI" URL="../DG Classes/BME_DG_System/TriggerModuloLCMultiple.vi"/>
	</Item>
	<Item Name="Low Level VIs" Type="Folder">
		<Item Name="Applied Energetics Stuff" Type="Folder">
			<Item Name="SubVI" Type="Folder">
				<Item Name="G05" Type="Folder">
					<Item Name="Set BME G05.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G05/Set BME G05.vi"/>
					<Item Name="Set G05 Delay.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G05/Set G05 Delay.vi"/>
					<Item Name="Set G05P2 Delay.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G05/Set G05P2 Delay.vi"/>
					<Item Name="Test BME G05.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G05/Test BME G05.vi"/>
				</Item>
				<Item Name="G08" Type="Folder">
					<Item Name="Modify G08.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Modify G08.vi"/>
					<Item Name="Round Settings.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Round Settings.vi"/>
					<Item Name="Set BME G08.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Set BME G08.vi"/>
					<Item Name="Set G08 Clock Parameters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Set G08 Clock Parameters.vi"/>
					<Item Name="Set G08 Delay.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Set G08 Delay.vi"/>
					<Item Name="Set G08 Trigger Parameters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Set G08 Trigger Parameters.vi"/>
					<Item Name="Set Gate Function.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Set Gate Function.vi"/>
					<Item Name="Test BME G08.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/G08/Test BME G08.vi"/>
				</Item>
				<Item Name="GO3" Type="Folder">
					<Item Name="BME_G03_PCI.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/GO3/BME_G03_PCI.vi"/>
				</Item>
				<Item Name="Acknowledge Interrupts.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Acknowledge Interrupts.vi"/>
				<Item Name="Activate DG BME.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Activate DG BME.vi"/>
				<Item Name="Calibrate Group.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Calibrate Group.vi"/>
				<Item Name="Calibrate Module.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Calibrate Module.vi"/>
				<Item Name="Calibrate Path Group.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Calibrate Path Group.vi"/>
				<Item Name="Deactivate DG BME.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Deactivate DG BME.vi"/>
				<Item Name="Delay Limit.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Delay Limit.vi"/>
				<Item Name="Detect Pci Delay Generators.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Detect Pci Delay Generators.vi"/>
				<Item Name="DG_Info.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/DG_Info.vi"/>
				<Item Name="DG_Setup.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/DG_Setup.vi"/>
				<Item Name="Error Converter (ErrCode or Status).vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Error Converter (ErrCode or Status).vi"/>
				<Item Name="Get Pci Delay Generator.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Get Pci Delay Generator.vi"/>
				<Item Name="Get Unconnected Delay Generator.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Get Unconnected Delay Generator.vi"/>
				<Item Name="Initialize DG BME.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Initialize DG BME.vi"/>
				<Item Name="Jump Start All Lists.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Jump Start All Lists.vi"/>
				<Item Name="Load Output State.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Load Output State.vi"/>
				<Item Name="Modify DG.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Modify DG.vi"/>
				<Item Name="Read Calibration Constants.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Calibration Constants.vi"/>
				<Item Name="Read Counter Control Register.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Counter Control Register.vi"/>
				<Item Name="Read DG Status.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read DG Status.vi"/>
				<Item Name="Read Frequency Counter.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Frequency Counter.vi"/>
				<Item Name="Read Interrupt Status.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Interrupt Status.vi"/>
				<Item Name="Read Path Calibration Constants.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Path Calibration Constants.vi"/>
				<Item Name="Read State.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read State.vi"/>
				<Item Name="Read Trigger Counter.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Read Trigger Counter.vi"/>
				<Item Name="Release Delays.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Release Delays.vi"/>
				<Item Name="Release DG Data.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Release DG Data.vi"/>
				<Item Name="Reserve DG Data.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Reserve DG Data.vi"/>
				<Item Name="Reset All Output Modulo Counters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Reset All Output Modulo Counters.vi"/>
				<Item Name="Reset Event Counter.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Reset Event Counter.vi"/>
				<Item Name="Reset Output Modulo Counters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Reset Output Modulo Counters.vi"/>
				<Item Name="Round Gate Delay.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Round Gate Delay.vi"/>
				<Item Name="Round Rep Counter.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Round Rep Counter.vi"/>
				<Item Name="Round Set Back.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Round Set Back.vi"/>
				<Item Name="Round T0.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Round T0.vi"/>
				<Item Name="Round Width.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Round Width.vi"/>
				<Item Name="Save State.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Save State.vi"/>
				<Item Name="Set Calibration For All.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Calibration For All.vi"/>
				<Item Name="Set Calibration Level.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Calibration Level.vi"/>
				<Item Name="Set Clock Parameters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Clock Parameters.vi"/>
				<Item Name="Set Delay List.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Delay List.vi"/>
				<Item Name="Set Gate AB.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Gate AB.vi"/>
				<Item Name="Set Output Level.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Output Level.vi"/>
				<Item Name="Set Trigger Parameters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set Trigger Parameters.vi"/>
				<Item Name="Set V2 Trigger Parameters.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Set V2 Trigger Parameters.vi"/>
				<Item Name="Settings G08.ctl" Type="VI" URL="../Applied Energetics Stuff/SubVI/Settings G08.ctl"/>
				<Item Name="Settings.ctl" Type="VI" URL="../Applied Energetics Stuff/SubVI/Settings.ctl"/>
				<Item Name="Software Trigger DG BME.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Software Trigger DG BME.vi"/>
				<Item Name="Uncalibrate Module.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Uncalibrate Module.vi"/>
			</Item>
			<Item Name="DelayGeneratorSG05p.vi" Type="VI" URL="../Applied Energetics Stuff/DelayGeneratorSG05p.vi"/>
			<Item Name="Samle SG05p.vi" Type="VI" URL="../Applied Energetics Stuff/Samle SG05p.vi"/>
			<Item Name="Delay Generator SG08p.vi" Type="VI" URL="../Applied Energetics Stuff/Delay Generator SG08p.vi"/>
		</Item>
		<Item Name="BME_DG_activate.vi" Type="VI" URL="../LV-BME Interface/BME_DG_activate.vi"/>
		<Item Name="BME_DG_SetTriggerParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetTriggerParameters.vi"/>
		<Item Name="BME_DG_SetClock.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetClock.vi"/>
		<Item Name="BME_Set_OutputLevel.vi" Type="VI" URL="../LV-BME Interface/BME_Set_OutputLevel.vi"/>
		<Item Name="BME_DG_ResetCounters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ResetCounters.vi"/>
		<Item Name="BME_DG_ResetModuloCounter.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ResetModuloCounter.vi"/>
		<Item Name="BME_Set_G05.vi" Type="VI" URL="../LV-BME Interface/BME_Set_G05.vi"/>
		<Item Name="BME_DG_Deactivate.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Deactivate.vi"/>
		<Item Name="BME_DG_DetectOnPCIBus.vi" Type="VI" URL="../LV-BME Interface/BME_DG_DetectOnPCIBus.vi"/>
		<Item Name="BME_DG_ReserveMemory.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReserveMemory.vi"/>
		<Item Name="BME_DG_ReleaseMemory.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReleaseMemory.vi"/>
		<Item Name="BME_DG_GetPCIDGInfo.vi" Type="VI" URL="../LV-BME Interface/BME_DG_GetPCIDGInfo.vi"/>
		<Item Name="BME_DG_Initialize.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Initialize.vi"/>
		<Item Name="BME_DG_Gate_AB.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Gate_AB.vi"/>
		<Item Name="BME_DG_ReadStatus.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadStatus.vi"/>
		<Item Name="BME_DG_ReadTriggerCounter.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadTriggerCounter.vi"/>
		<Item Name="BME_DG_ReadTriggerCounter64Bit.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadTriggerCounter64Bit.vi"/>
		<Item Name="BME_DG_ReadCalibrConst_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadCalibrConst_from_File.vi"/>
		<Item Name="BME_DG_CalibrateGroup_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateGroup_from_File.vi"/>
		<Item Name="BME_DG_CalibrateModule.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateModule.vi"/>
		<Item Name="BME_DG_SetCalibrationLevel.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetCalibrationLevel.vi"/>
		<Item Name="BME_DG_Set_G02_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G02_Chnl.vi"/>
		<Item Name="BME_DG_Set_G05_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G05_Chnl.vi"/>
		<Item Name="BME_DG_LoadAllCardParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_LoadAllCardParameters.vi"/>
		<Item Name="BME_DG_LoadCardParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_LoadCardParameters.vi"/>
		<Item Name="BME_DG_SetG08TriggerParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetG08TriggerParameters.vi"/>
		<Item Name="BME_DG_SetV2TriggerParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetV2TriggerParameters.vi"/>
		<Item Name="BME_DG_GetPCIBusDGInfo.vi" Type="VI" URL="../LV-BME Interface/BME_DG_GetPCIBusDGInfo.vi"/>
		<Item Name="BME_DG_InitializeMultipleBus.vi" Type="VI" URL="../LV-BME Interface/BME_DG_InitializeMultipleBus.vi"/>
		<Item Name="BME_DG_Errors.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Errors.vi"/>
	</Item>
	<Item Name="TypeDefs" Type="Folder">
		<Item Name="ChnlSettings.ctl" Type="VI" URL="../LV-BME Interface/ChnlSettings.ctl"/>
		<Item Name="ChnlWithModulo.ctl" Type="VI" URL="../LV-BME Interface/ChnlWithModulo.ctl"/>
		<Item Name="SignalType.ctl" Type="VI" URL="../LV-BME Interface/SignalType.ctl"/>
		<Item Name="ClockSource.ctl" Type="VI" URL="../LV-BME Interface/ClockSource.ctl"/>
		<Item Name="BME_DG_TriggerSettings.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_TriggerSettings.ctl"/>
		<Item Name="BME_G05P1Settings.ctl" Type="VI" URL="../LV-BME Interface/BME_G05P1Settings.ctl"/>
		<Item Name="BME_DG_MasterOrSlave.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_MasterOrSlave.ctl"/>
		<Item Name="DetectDG.ctl" Type="VI" URL="../LV-BME Interface/DetectDG.ctl"/>
		<Item Name="UpdateChnlTask.ctl" Type="VI" URL="../DG Classes/BME_DG_System/UpdateChnlTask.ctl"/>
		<Item Name="System DG Selection.ctl" Type="VI" URL="../LV-BME Interface/System DG Selection.ctl"/>
		<Item Name="Card Config.ctl" Type="VI" URL="../LV-BME Interface/Card Config.ctl"/>
		<Item Name="SG08_Settings.ctl" Type="VI" URL="../LV-BME Interface/SG08_Settings.ctl"/>
		<Item Name="Go_Done_Chnl_Settings.ctl" Type="VI" URL="../LV-BME Interface/Go_Done_Chnl_Settings.ctl"/>
		<Item Name="SG08_Chnl_Settings.ctl" Type="VI" URL="../LV-BME Interface/SG08_Chnl_Settings.ctl"/>
		<Item Name="Chnl Settings Complete.ctl" Type="VI" URL="../LV-BME Interface/Chnl Settings Complete.ctl"/>
		<Item Name="BME_DG_V2TriggerSettings.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_V2TriggerSettings.ctl"/>
		<Item Name="ChnlOutputModulo.ctl" Type="VI" URL="../DG Classes/BME_DG_System/ChnlOutputModulo.ctl"/>
		<Item Name="SG05P2 Clock and Trigger Settings.ctl" Type="VI" URL="../DG Classes/BME_DG_G05P2/SG05P2 Clock and Trigger Settings.ctl"/>
		<Item Name="ChnlParam.ctl" Type="VI" URL="../LV-BME Interface/ChnlParam.ctl"/>
		<Item Name="GoSignalBits.ctl" Type="VI" URL="../LV-BME Interface/GoSignalBits.ctl"/>
		<Item Name="MSBusSignals.ctl" Type="VI" URL="../LV-BME Interface/MSBusSignals.ctl"/>
	</Item>
	<Item Name="Config Files" Type="Folder">
		<Item Name="Zentral Trigger PC.bmedg" Type="Document" URL="../Zentral Trigger PC.bmedg"/>
		<Item Name="Modules.cal" Type="Document" URL="../ParameterFiles/Modules.cal"/>
		<Item Name="BME_G0x.cal" Type="Document" URL="../ParameterFiles/BME_G0x.cal"/>
		<Item Name="Test sync update drei SG08P3 mit Externen Trigger bei MS Master.bmedg" Type="Document" URL="../ParameterFiles/Test sync update drei SG08P3 mit Externen Trigger bei MS Master.bmedg"/>
	</Item>
	<Item Name="DG Classes" Type="Folder">
		<Item Name="BME_DG_Base.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Base/BME_DG_Base.lvclass"/>
		<Item Name="BME_DG_G02.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G02/BME_DG_G02.lvclass"/>
		<Item Name="BME_DG_G05.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05/BME_DG_G05.lvclass"/>
		<Item Name="BME_DG_G05P2.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05P2/BME_DG_G05P2.lvclass"/>
		<Item Name="BME_DG_G08.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G08/BME_DG_G08.lvclass"/>
	</Item>
	<Item Name="DG Channel classes" Type="Folder">
		<Item Name="BME_DG_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Chnl/BME_DG_Chnl.lvclass"/>
		<Item Name="BME_DG_G02_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G02_Chnl/BME_DG_G02_Chnl.lvclass"/>
		<Item Name="BME_DG_G05_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05_Chnl/BME_DG_G05_Chnl.lvclass"/>
		<Item Name="BME_DG_G05P2_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05P2_Chnl/BME_DG_G05P2_Chnl.lvclass"/>
		<Item Name="BME_DG_G08_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G08_Chnl/BME_DG_G08_Chnl.lvclass"/>
	</Item>
	<Item Name="DG System class" Type="Folder">
		<Item Name="BME_DG_System.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_System/BME_DG_System.lvclass"/>
	</Item>
	<Item Name="Test PC from CnfgFile.vi" Type="VI" URL="../Test PC from CnfgFile.vi"/>
</Library>
