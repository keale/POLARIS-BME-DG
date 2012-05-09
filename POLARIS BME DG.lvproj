<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="9008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="POLARIS BME DG" Type="Folder">
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
			<Item Name="Binaries and C" Type="Folder">
				<Item Name="DG_DLL_1.c" Type="Document" URL="../BME DLL/DG_DLL_1.c"/>
				<Item Name="DG_DLL_1.h" Type="Document" URL="../BME DLL/DG_DLL_1.h"/>
				<Item Name="StringRout_C.c" Type="Document" URL="../BME DLL/StringRout_C.c"/>
				<Item Name="StringRout_C.h" Type="Document" URL="../BME DLL/StringRout_C.h"/>
				<Item Name="DG_Data.h" Type="Document" URL="../BME DLL/DG_Data.h"/>
				<Item Name="DelayGenerator.dll" Type="Document" URL="../BME DLL/DelayGenerator.dll"/>
			</Item>
			<Item Name="ParameterFiles" Type="Folder">
				<Item Name="201203-22 Test mit vier DG.g0y" Type="Document" URL="../ParameterFiles/201203-22 Test mit vier DG.g0y"/>
				<Item Name="parameters bme 201203-18.g0y" Type="Document" URL="../ParameterFiles/parameters bme 201203-18.g0y"/>
			</Item>
			<Item Name="TypeDefs" Type="Folder">
				<Item Name="For ReadParameters" Type="Folder">
					<Item Name="BME_DG_DelayChannelData.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_DelayChannelData.ctl"/>
					<Item Name="BME_DG_DelayTriggerData.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_DelayTriggerData.ctl"/>
					<Item Name="BME_DG_BME_State.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_BME_State.ctl"/>
					<Item Name="BME_DG_State_V2.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_State_V2.ctl"/>
					<Item Name="BME_DG_DelayChannelData_V2.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_DelayChannelData_V2.ctl"/>
					<Item Name="BME_DG_DelayTriggerData_V2.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_DelayTriggerData_V2.ctl"/>
					<Item Name="BME_DG_BME_Control_V2.ctl" Type="VI" URL="../LV-BME Interface/Typedefs For ReadParameters()/BME_DG_BME_Control_V2.ctl"/>
				</Item>
				<Item Name="ChnlSettings.ctl" Type="VI" URL="../LV-BME Interface/ChnlSettings.ctl"/>
				<Item Name="ChnlWithModulo.ctl" Type="VI" URL="../LV-BME Interface/ChnlWithModulo.ctl"/>
				<Item Name="SignalType.ctl" Type="VI" URL="../LV-BME Interface/SignalType.ctl"/>
				<Item Name="ClockSource.ctl" Type="VI" URL="../LV-BME Interface/ClockSource.ctl"/>
				<Item Name="BME_DG_TriggerSettings.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_TriggerSettings.ctl"/>
				<Item Name="BME_G05P1Settings.ctl" Type="VI" URL="../LV-BME Interface/BME_G05P1Settings.ctl"/>
				<Item Name="BME_DG_MasterOrSlave.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_MasterOrSlave.ctl"/>
			</Item>
			<Item Name="Low Level VIs" Type="Folder">
				<Item Name="BME_DG_Set_G05_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G05_Chnl.vi"/>
				<Item Name="BME_DG_Set_G02_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G02_Chnl.vi"/>
				<Item Name="BME_DG_SetTriggerParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetTriggerParameters.vi"/>
				<Item Name="BME_DG_activate.vi" Type="VI" URL="../LV-BME Interface/BME_DG_activate.vi"/>
				<Item Name="BME_DG_SetClock.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetClock.vi"/>
				<Item Name="BME_Set_OutputLevel.vi" Type="VI" URL="../LV-BME Interface/BME_Set_OutputLevel.vi"/>
				<Item Name="BME_DG_ResetTriggerCounter.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ResetTriggerCounter.vi"/>
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
				<Item Name="BME_DG_ReadParameterFile.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadParameterFile.vi"/>
				<Item Name="BME_DG_ReadParameterFile_V2.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadParameterFile_V2.vi"/>
				<Item Name="BME_DG_ReadCalibrConst_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadCalibrConst_from_File.vi"/>
				<Item Name="BME_DG_SetDG_with_FileParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetDG_with_FileParameters.vi"/>
				<Item Name="BME_DG_CalibrateGroup_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateGroup_from_File.vi"/>
				<Item Name="BME_DG_CalibrateModule.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateModule.vi"/>
				<Item Name="BME_DG_SetCalibrationLevel.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetCalibrationLevel.vi"/>
			</Item>
			<Item Name="Doku" Type="Folder">
				<Item Name="Bme_g0x.hlp" Type="Document" URL="../LV-BME Interface/Bme_g0x.hlp"/>
			</Item>
			<Item Name="DG Classes" Type="Folder">
				<Item Name="BME_DG_Base.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Base/BME_DG_Base.lvclass"/>
				<Item Name="BME_DG_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Chnl/BME_DG_Chnl.lvclass"/>
				<Item Name="BME_DG_G02.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G02/BME_DG_G02.lvclass"/>
				<Item Name="BME_DG_G02_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G02_Chnl/BME_DG_G02_Chnl.lvclass"/>
				<Item Name="BME_DG_G05.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05/BME_DG_G05.lvclass"/>
				<Item Name="BME_DG_G05_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05_Chnl/BME_DG_G05_Chnl.lvclass"/>
				<Item Name="BME_DG_G05P2.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05P2/BME_DG_G05P2.lvclass"/>
				<Item Name="BME_DG_G05P2_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05P2_Chnl/BME_DG_G05P2_Chnl.lvclass"/>
				<Item Name="BME_DG_G08.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G08/BME_DG_G08.lvclass"/>
				<Item Name="BME_DG_G08_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G08_Chnl/BME_DG_G08_Chnl.lvclass"/>
				<Item Name="BME_DG_System.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_System/BME_DG_System.lvclass"/>
			</Item>
		</Item>
		<Item Name="TriggerModuloLCMultiple.vi" Type="VI" URL="../DG Classes/BME_DG_System/TriggerModuloLCMultiple.vi"/>
		<Item Name="Test.vi" Type="VI" URL="../Test.vi"/>
		<Item Name="Test Classes.vi" Type="VI" URL="../Test Classes.vi"/>
		<Item Name="RunDelay2.vi" Type="VI" URL="../Freiburg_DG/RunDelay2.vi"/>
		<Item Name="BME_DG_ReadParameterFile_mittels array.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadParameterFile_mittels array.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Merge Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Merge Errors.vi"/>
				<Item Name="Read Characters From File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Characters From File.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="General Error Handler CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler CORE.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="Close File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Close File+.vi"/>
				<Item Name="Find First Error.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find First Error.vi"/>
				<Item Name="Read File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read File+ (string).vi"/>
				<Item Name="compatReadText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatReadText.vi"/>
				<Item Name="Open File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Open File+.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_Gmath.lvlib" Type="Library" URL="/&lt;vilib&gt;/gmath/NI_Gmath.lvlib"/>
			</Item>
			<Item Name="instr.lib" Type="Folder">
				<Item Name="DelayGenerator.dll" Type="Document" URL="/&lt;instrlib&gt;/BME Delay Generator/SubVI/DelayGenerator.dll"/>
			</Item>
			<Item Name="DelayGenerator.dll" Type="Document" URL="../Applied Energetics Stuff/DelayGenerator.dll"/>
			<Item Name="DelayGenerator.dll" Type="Document" URL="../../BME Beispiele/BME DLL/DelayGenerator.dll"/>
			<Item Name="Falling Edge Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Falling Edge Change Detector.vi"/>
			<Item Name="Rising Edge Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Rising Edge Change Detector.vi"/>
			<Item Name="Set Control State.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Set Control State.vi"/>
			<Item Name="MGI Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector.vi"/>
			<Item Name="MGI Change Detector (T).vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector (T).vi"/>
			<Item Name="MGI Change Detector (F).vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector (F).vi"/>
			<Item Name="Enable Interrupts.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Enable Interrupts.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
