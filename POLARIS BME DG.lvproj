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
			<Item Name="Binaries and C" Type="Folder">
				<Item Name="DelayGenerator.dll" Type="Document" URL="../../BME Beispiele/BME DLL/DelayGenerator.dll"/>
				<Item Name="DG_DLL_1.c" Type="Document" URL="../BME DLL/DG_DLL_1.c"/>
				<Item Name="DG_DLL_1.h" Type="Document" URL="../BME DLL/DG_DLL_1.h"/>
				<Item Name="StringRout_C.c" Type="Document" URL="../BME DLL/StringRout_C.c"/>
				<Item Name="StringRout_C.h" Type="Document" URL="../BME DLL/StringRout_C.h"/>
				<Item Name="DG_Data.h" Type="Document" URL="../BME DLL/DG_Data.h"/>
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
				</Item>
				<Item Name="ChnlSettings.ctl" Type="VI" URL="../LV-BME Interface/ChnlSettings.ctl"/>
				<Item Name="ChnlWithModulo.ctl" Type="VI" URL="../LV-BME Interface/ChnlWithModulo.ctl"/>
				<Item Name="SignalType.ctl" Type="VI" URL="../LV-BME Interface/SignalType.ctl"/>
				<Item Name="ClockSource.ctl" Type="VI" URL="../LV-BME Interface/ClockSource.ctl"/>
				<Item Name="BME_DG_TriggerSettings.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_TriggerSettings.ctl"/>
				<Item Name="BME_G05P1Settings.ctl" Type="VI" URL="../LV-BME Interface/BME_G05P1Settings.ctl"/>
				<Item Name="BME_DG_Trigger.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_Trigger.ctl"/>
				<Item Name="BME_DG_MasterOrSlave.ctl" Type="VI" URL="../LV-BME Interface/BME_DG_MasterOrSlave.ctl"/>
			</Item>
			<Item Name="Low Level VIs" Type="Folder">
				<Item Name="BME_DG_Set_G05_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G05_Chnl.vi"/>
				<Item Name="BME_DG_Set_G02_Chnl.vi" Type="VI" URL="../LV-BME Interface/BME_DG_Set_G02_Chnl.vi"/>
				<Item Name="BME_DG_SetTriggerParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetTriggerParameters.vi"/>
				<Item Name="BME_DG_activate.vi" Type="VI" URL="../LV-BME Interface/BME_DG_activate.vi"/>
				<Item Name="BME_DG_SetClock.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetClock.vi"/>
				<Item Name="BME_Set_OutputLevel.vi" Type="VI" URL="../LV-BME Interface/BME_Set_OutputLevel.vi"/>
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
				<Item Name="BME_DG_ReadCalibrConst_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadCalibrConst_from_File.vi"/>
				<Item Name="BME_DG_SetDG_with_FileParameters.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetDG_with_FileParameters.vi"/>
				<Item Name="BME_DG_CalibrateGroup_from_File.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateGroup_from_File.vi"/>
				<Item Name="BME_DG_CalibrateModule.vi" Type="VI" URL="../LV-BME Interface/BME_DG_CalibrateModule.vi"/>
				<Item Name="BME_DG_SetCalibrationLevel.vi" Type="VI" URL="../LV-BME Interface/BME_DG_SetCalibrationLevel.vi"/>
				<Item Name="BME_DG_ReadParameterFile_V2.vi" Type="VI" URL="../LV-BME Interface/BME_DG_ReadParameterFile_V2.vi"/>
			</Item>
			<Item Name="Doku" Type="Folder">
				<Item Name="Bme_g0x.hlp" Type="Document" URL="../LV-BME Interface/Bme_g0x.hlp"/>
			</Item>
			<Item Name="DG Classes" Type="Folder">
				<Item Name="BME_DG_Base.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Base/BME_DG_Base.lvclass"/>
				<Item Name="BME_DG_G02.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_P02/BME_DG_G02.lvclass"/>
				<Item Name="BME_DG_G05.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_G05/BME_DG_G05.lvclass"/>
				<Item Name="BME_DG_Chnl.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Chnl/BME_DG_Chnl.lvclass"/>
				<Item Name="BME_DG_Chnl_Modulo.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Modulo/BME_DG_Chnl_Modulo.lvclass"/>
				<Item Name="BME_DG_Trigger.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_Trigger/BME_DG_Trigger.lvclass"/>
				<Item Name="BME_DG_System.lvclass" Type="LVClass" URL="../DG Classes/BME_DG_System/BME_DG_System.lvclass"/>
			</Item>
		</Item>
		<Item Name="Test.vi" Type="VI" URL="../Test.vi"/>
		<Item Name="RunDelay2.vi" Type="VI" URL="../Freiburg_DG/RunDelay2.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Merge Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Merge Errors.vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
