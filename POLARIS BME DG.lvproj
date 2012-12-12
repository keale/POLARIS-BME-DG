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
		<Item Name="CSMainAndLibs_DontTouch" Type="Folder">
			<Item Name="supportFiles" Type="Folder">
				<Item Name="CS_release_notes.txt" Type="Document" URL="../../../../CS_release_notes.txt"/>
				<Item Name="Classes.xls" Type="Document" URL="../../../../Classes.xls"/>
				<Item Name="CS_process.mdb" Type="Document" URL="../../../../CS_process.mdb"/>
				<Item Name="CS_readme.txt" Type="Document" URL="../../../../CS_readme.txt"/>
				<Item Name="CS.ico" Type="Document" URL="../../../../CS.ico"/>
				<Item Name="CS32_32.bmp" Type="Document" URL="../../../../CS32_32.bmp"/>
				<Item Name="CS_Start.rtm" Type="Document" URL="../../../../CS_Start.rtm"/>
				<Item Name="CSAS.ICO" Type="Document" URL="../../../CSAccessSystem/CSAS.ICO"/>
			</Item>
			<Item Name="externalLibraries" Type="Folder">
				<Item Name="UtilityLib.lvlib" Type="Library" URL="../../../../../../lib.lib/UtilityLib/UtilityLib.lvlib"/>
				<Item Name="LVDimInterface.lvlib" Type="Library" URL="../../../../../../lib.lib/DimLVEvent/LVDimInterface/LVDimInterface.lvlib"/>
				<Item Name="LVNodeInfo.lvlib" Type="Library" URL="../../../../../../lib.lib/NodeMon/LVNodeInfo/LVNodeInfo.lvlib"/>
				<Item Name="DimIndicators.lvlib" Type="Library" URL="../../../../../../lib.lib/DimLVEvent/DimIndicators/DimIndicators.lvlib"/>
				<Item Name="CS SQL Server.lvlib" Type="Library" URL="../../../../CSTools/CS SQL Server/CS SQL Server.lvlib"/>
			</Item>
			<Item Name="CSMain" Type="Folder">
				<Item Name="typedefs" Type="Folder">
					<Item Name="CoreDefs" Type="Folder">
						<Item Name="CoreDefs.call_type.ctl" Type="VI" URL="../../../CSCore/CSSystem/CoreDefs/CoreDefs.call_type.ctl"/>
						<Item Name="CoreDefs.error_severity.ctl" Type="VI" URL="../../../CSCore/CSSystem/CoreDefs/CoreDefs.error_severity.ctl"/>
						<Item Name="CoreDefs.error_type.ctl" Type="VI" URL="../../../CSCore/CSSystem/CoreDefs/CoreDefs.error_type.ctl"/>
						<Item Name="CoreDefs.rawDataType.ctl" Type="VI" URL="../../../CSCore/CSSystem/CoreDefs/CoreDefs.rawDataType.ctl"/>
						<Item Name="CoreDefs.remote_call_type.ctl" Type="VI" URL="../../../CSCore/CSSystem/CoreDefs/CoreDefs.remote_call_type.ctl"/>
					</Item>
				</Item>
				<Item Name="libraries" Type="Folder">
					<Item Name="CoreLib.lvlib" Type="Library" URL="../../../CSCore/CSSystem/CoreLib/CoreLib.lvlib"/>
					<Item Name="CSSystemLib.lvlib" Type="Library" URL="../../../CSCore/CSSystem/CSSystemLib/CSSystemLib.lvlib"/>
					<Item Name="CSAccessLib.lvlib" Type="Library" URL="../../../CSCore/CSSystem/CSAccessLib/CSAccessLib.lvlib"/>
				</Item>
				<Item Name="baseClasses" Type="Folder">
					<Item Name="CSObj.lvlib" Type="Library" URL="../../../CSCore/CSObj/CSObj.lvlib"/>
					<Item Name="CAEObj.lvlib" Type="Library" URL="../../../CSCore/CAEObj/CAEObj.lvlib"/>
					<Item Name="BaseSM.lvlib" Type="Library" URL="../../../CSCore/BaseSM/BaseSM.lvlib"/>
					<Item Name="BaseGUI.lvlib" Type="Library" URL="../../../CSCore/BaseGUI/BaseGUI.lvlib"/>
					<Item Name="BaseProcess.lvlib" Type="Library" URL="../../../CSCore/BaseProcess/BaseProcess.lvlib"/>
					<Item Name="CSAccessClient.lvlib" Type="Library" URL="../../../CSAccessSystem/CSAccessClient/CSAccessClient.lvlib"/>
					<Item Name="CSObj.panel.vit" Type="VI" URL="../../../CSCore/CSObj/CSObj.panel.vit"/>
				</Item>
				<Item Name="helperClasses" Type="Folder">
					<Item Name="SuperProc.lvlib" Type="Library" URL="../../../CSCore/SuperProc/SuperProc.lvlib"/>
					<Item Name="ObjectInspector.lvlib" Type="Library" URL="../../../CSGui/ObjectInspector/ObjectInspector.lvlib"/>
					<Item Name="GeneralObjectGUI.lvlib" Type="Library" URL="../../../CSGui/GeneralObjectGUI/GeneralObjectGUI.lvlib"/>
					<Item Name="GOGFrontPanel.lvlib" Type="Library" URL="../../../CSGui/GOGFrontPanel/GOGFrontPanel.lvlib"/>
					<Item Name="CSAccessViewer.lvlib" Type="Library" URL="../../../CSAccessSystem/CSAccessViewer/CSAccessViewer.lvlib"/>
				</Item>
				<Item Name="contributedClasses" Type="Folder">
					<Item Name="CSPopUpMsgBox.lvlib" Type="Library" URL="../../../CSGui/CSPopUpMsgBox/CSPopUpMsgBox.lvlib"/>
					<Item Name="CSTimer.lvlib" Type="Library" URL="../../../CSCore/CSTimer/CSTimer.lvlib"/>
					<Item Name="DIMHistogramGUI.lvlib" Type="Library" URL="../../../CSGui/DIMHistogramGUI/DIMHistogramGUI.lvlib"/>
					<Item Name="DIMTrendGUI.lvlib" Type="Library" URL="../../../CSGui/DIMTrendGUI/DIMTrendGUI.lvlib"/>
					<Item Name="DIMTableView.lvlib" Type="Library" URL="../../../CSGui/DIMTableView/DIMTableView.lvlib"/>
					<Item Name="CSPopUpMsgBox.panel.vit" Type="VI" URL="../../../CSGui/CSPopUpMsgBox/private/CSPopUpMsgBox.panel.vit"/>
					<Item Name="CSTimer.thread.vit" Type="VI" URL="../../../CSCore/CSTimer/private/CSTimer.thread.vit"/>
					<Item Name="DIMHistogramGUI.panel.vit" Type="VI" URL="../../../CSGui/DIMHistogramGUI/private/DIMHistogramGUI.panel.vit"/>
					<Item Name="DIMTrendGUI.panel.vit" Type="VI" URL="../../../CSGui/DIMTrendGUI/private/DIMTrendGUI.panel.vit"/>
				</Item>
				<Item Name="utilities" Type="Folder">
					<Item Name="CSAccessServer.lvlib" Type="Library" URL="../../../CSAccessSystem/CSAccessServer/CSAccessServer.lvlib"/>
					<Item Name="CSClassUtilities.TestClass.vi" Type="VI" URL="../../../../CSClassUtilities/CSClassUtilities.TestClass.vi"/>
					<Item Name="CSClassUtilities.InheritClass.vi" Type="VI" URL="../../../../CSClassUtilities/CSClassUtilities.InheritClass.vi"/>
					<Item Name="CSClassUtilities.CopyAndRenameClass.vi" Type="VI" URL="../../../../CSClassUtilities/CSClassUtilities.CopyAndRenameClass.vi"/>
					<Item Name="GenerateHTMLReportOfClasses.lvlib" Type="Library" URL="../../../../CSClassUtilities/GenerateHTMLReportOfClasses/GenerateHTMLReportOfClasses.lvlib"/>
				</Item>
				<Item Name="CS_Contents_Main.vi" Type="VI" URL="../../../../CS_Contents_Main.vi"/>
			</Item>
		</Item>
		<Item Name="POLARIS BME DG.lvlib" Type="Library" URL="../POLARIS BME DG.lvlib"/>
		<Item Name="CS POLARIS BME DG.lvlib" Type="Library" URL="../CS POLARIS BME DG/CS POLARIS BME DG.lvlib"/>
		<Item Name="CS POLARIS BME DG Client.lvlib" Type="Library" URL="../CS POLARIS BME DG Client/CS POLARIS BME DG Client.lvlib"/>
		<Item Name="CS_Start.vi" Type="VI" URL="../../../../CS_Start.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
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
				<Item Name="Merge Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Merge Errors.vi"/>
				<Item Name="compatReadText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatReadText.vi"/>
				<Item Name="Open File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Open File+.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_Gmath.lvlib" Type="Library" URL="/&lt;vilib&gt;/gmath/NI_Gmath.lvlib"/>
				<Item Name="LVStringsAndValuesArrayTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVStringsAndValuesArrayTypeDef.ctl"/>
				<Item Name="Read From XML File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File.vi"/>
				<Item Name="Read From XML File(array).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(array).vi"/>
				<Item Name="ParseXMLFragments.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/ParseXMLFragments.vi"/>
				<Item Name="FindFirstTag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindFirstTag.vi"/>
				<Item Name="FindElement.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindElement.vi"/>
				<Item Name="FindEmptyElement.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindEmptyElement.vi"/>
				<Item Name="FindMatchingCloseTag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindMatchingCloseTag.vi"/>
				<Item Name="FindElementStartByName.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindElementStartByName.vi"/>
				<Item Name="FindCloseTagByName.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/FindCloseTagByName.vi"/>
				<Item Name="Open_Create_Replace File.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/Open_Create_Replace File.vi"/>
				<Item Name="compatFileDialog.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatFileDialog.vi"/>
				<Item Name="compatOpenFileOperation.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatOpenFileOperation.vi"/>
				<Item Name="compatCalcOffset.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatCalcOffset.vi"/>
				<Item Name="Read From XML File(string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Read From XML File(string).vi"/>
				<Item Name="Write to XML File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File.vi"/>
				<Item Name="Write to XML File(string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File(string).vi"/>
				<Item Name="Write to XML File(array).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/xml.llb/Write to XML File(array).vi"/>
				<Item Name="subDisplayMessage.vi" Type="VI" URL="/&lt;vilib&gt;/express/express output/DisplayMessageBlock.llb/subDisplayMessage.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
				<Item Name="TCP Get Raw Net Object.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/tcp.llb/TCP Get Raw Net Object.vi"/>
				<Item Name="Recursive File List.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Recursive File List.vi"/>
				<Item Name="List Directory and LLBs.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/List Directory and LLBs.vi"/>
				<Item Name="Close Zip File.vi" Type="VI" URL="/&lt;vilib&gt;/zip/Close Zip File.vi"/>
				<Item Name="New Zip File.vi" Type="VI" URL="/&lt;vilib&gt;/zip/New Zip File.vi"/>
				<Item Name="Path To Command Line String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Path To Command Line String.vi"/>
				<Item Name="PathToUNIXPathString.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/CFURL.llb/PathToUNIXPathString.vi"/>
				<Item Name="Add File to Zip.vi" Type="VI" URL="/&lt;vilib&gt;/zip/Add File to Zip.vi"/>
				<Item Name="Relative Path To Platform Independent String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Relative Path To Platform Independent String.vi"/>
				<Item Name="NI_Unzip.lvlib" Type="Library" URL="/&lt;vilib&gt;/zip/NI_Unzip.lvlib"/>
				<Item Name="Not A Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Not A Semaphore.vi"/>
				<Item Name="Semaphore RefNum" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Semaphore RefNum"/>
				<Item Name="Semaphore Refnum Core.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Semaphore Refnum Core.ctl"/>
				<Item Name="Obtain Semaphore Reference.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Obtain Semaphore Reference.vi"/>
				<Item Name="Validate Semaphore Size.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Validate Semaphore Size.vi"/>
				<Item Name="AddNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/AddNamedSemaphorePrefix.vi"/>
				<Item Name="GetNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/GetNamedSemaphorePrefix.vi"/>
				<Item Name="Release Semaphore Reference.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Release Semaphore Reference.vi"/>
				<Item Name="RemoveNamedSemaphorePrefix.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/RemoveNamedSemaphorePrefix.vi"/>
				<Item Name="Acquire Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Acquire Semaphore.vi"/>
				<Item Name="Release Semaphore.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Release Semaphore.vi"/>
				<Item Name="LVDateTimeRec.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVDateTimeRec.ctl"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="NI_Database_API.lvlib" Type="Library" URL="/&lt;vilib&gt;/addons/database/NI_Database_API.lvlib"/>
				<Item Name="GOOP Object Repository Method.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/_goopsup.llb/GOOP Object Repository Method.ctl"/>
				<Item Name="GOOP Object Repository Statistics.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/_goopsup.llb/GOOP Object Repository Statistics.ctl"/>
				<Item Name="GOOP Object Repository.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/_goopsup.llb/GOOP Object Repository.vi"/>
				<Item Name="Get Semaphore Status.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/semaphor.llb/Get Semaphore Status.vi"/>
				<Item Name="Write File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write File+ (string).vi"/>
				<Item Name="compatWriteText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatWriteText.vi"/>
				<Item Name="NI_report.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/Utility/NIReport.llb/NI_report.lvclass"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="Create Directory Recursive.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Create Directory Recursive.vi"/>
				<Item Name="NI_ReportGenerationCore.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/NIReport.llb/NI_ReportGenerationCore.lvlib"/>
				<Item Name="NI_HTML.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/Utility/NIReport.llb/HTML/NI_HTML.lvclass"/>
				<Item Name="Write JPEG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Write JPEG File.vi"/>
				<Item Name="imagedata.ctl" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/imagedata.ctl"/>
				<Item Name="Check Data Size.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Data Size.vi"/>
				<Item Name="Check Color Table Size.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Color Table Size.vi"/>
				<Item Name="Check Path.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Path.vi"/>
				<Item Name="Directory of Top Level VI.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Directory of Top Level VI.vi"/>
				<Item Name="Check File Permissions.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check File Permissions.vi"/>
				<Item Name="Write PNG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/png.llb/Write PNG File.vi"/>
				<Item Name="Registry RtKey.ctl" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry RtKey.ctl"/>
				<Item Name="Close Registry Key.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Close Registry Key.vi"/>
				<Item Name="Registry refnum.ctl" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry refnum.ctl"/>
				<Item Name="Registry Handle Master.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry Handle Master.vi"/>
				<Item Name="Read Registry Value Simple.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value Simple.vi"/>
				<Item Name="Read Registry Value Simple STR.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value Simple STR.vi"/>
				<Item Name="Registry Simplify Data Type.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry Simplify Data Type.vi"/>
				<Item Name="Read Registry Value.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value.vi"/>
				<Item Name="Read Registry Value STR.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value STR.vi"/>
				<Item Name="Registry WinErr-LVErr.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry WinErr-LVErr.vi"/>
				<Item Name="Read Registry Value DWORD.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value DWORD.vi"/>
				<Item Name="Read Registry Value Simple U32.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Read Registry Value Simple U32.vi"/>
				<Item Name="Open Registry Key.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Open Registry Key.vi"/>
				<Item Name="Registry SAM.ctl" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry SAM.ctl"/>
				<Item Name="Registry View.ctl" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/Registry View.ctl"/>
				<Item Name="STR_ASCII-Unicode.vi" Type="VI" URL="/&lt;vilib&gt;/registry/registry.llb/STR_ASCII-Unicode.vi"/>
				<Item Name="Path to URL.vi" Type="VI" URL="/&lt;vilib&gt;/printing/PathToURL.llb/Path to URL.vi"/>
				<Item Name="Escape Characters for HTTP.vi" Type="VI" URL="/&lt;vilib&gt;/printing/PathToURL.llb/Escape Characters for HTTP.vi"/>
				<Item Name="Generate Temporary File Path.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Generate Temporary File Path.vi"/>
				<Item Name="Destroy ActiveX Event Queue.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/Destroy ActiveX Event Queue.vi"/>
				<Item Name="Create Error Clust.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/Create Error Clust.vi"/>
				<Item Name="Wait On ActiveX Event.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/Wait On ActiveX Event.vi"/>
				<Item Name="EventData.ctl" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/EventData.ctl"/>
				<Item Name="OccFireType.ctl" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/OccFireType.ctl"/>
				<Item Name="Create ActiveX Event Queue.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/Create ActiveX Event Queue.vi"/>
				<Item Name="Wait types.ctl" Type="VI" URL="/&lt;vilib&gt;/Platform/ax-events.llb/Wait types.ctl"/>
				<Item Name="Get LV Class Default Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/LVClass/Get LV Class Default Value.vi"/>
				<Item Name="Built App File Layout.vi" Type="VI" URL="/&lt;vilib&gt;/AppBuilder/Built App File Layout.vi"/>
				<Item Name="NI_Standard Report.lvclass" Type="LVClass" URL="/&lt;vilib&gt;/Utility/NIReport.llb/Standard Report/NI_Standard Report.lvclass"/>
				<Item Name="Write BMP File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/bmp.llb/Write BMP File.vi"/>
				<Item Name="Write BMP Data.vi" Type="VI" URL="/&lt;vilib&gt;/picture/bmp.llb/Write BMP Data.vi"/>
				<Item Name="Write BMP Data To Buffer.vi" Type="VI" URL="/&lt;vilib&gt;/picture/bmp.llb/Write BMP Data To Buffer.vi"/>
				<Item Name="Flip and Pad for Picture Control.vi" Type="VI" URL="/&lt;vilib&gt;/picture/bmp.llb/Flip and Pad for Picture Control.vi"/>
				<Item Name="Calc Long Word Padded Width.vi" Type="VI" URL="/&lt;vilib&gt;/picture/bmp.llb/Calc Long Word Padded Width.vi"/>
				<Item Name="compatOverwrite.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatOverwrite.vi"/>
				<Item Name="Read PNG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/png.llb/Read PNG File.vi"/>
				<Item Name="Create Mask By Alpha.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Create Mask By Alpha.vi"/>
				<Item Name="Bit-array To Byte-array.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Bit-array To Byte-array.vi"/>
				<Item Name="Color to RGB.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/Color to RGB.vi"/>
			</Item>
			<Item Name="Falling Edge Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Falling Edge Change Detector.vi"/>
			<Item Name="Rising Edge Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Rising Edge Change Detector.vi"/>
			<Item Name="Set Control State.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/Set Control State.vi"/>
			<Item Name="MGI Change Detector.vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector.vi"/>
			<Item Name="MGI Change Detector (T).vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector (T).vi"/>
			<Item Name="MGI Change Detector (F).vi" Type="VI" URL="../Applied Energetics Stuff/Extra/MGI Change Detector (F).vi"/>
			<Item Name="Enable Interrupts.vi" Type="VI" URL="../Applied Energetics Stuff/SubVI/Enable Interrupts.vi"/>
			<Item Name="wsock32.dll" Type="Document" URL="wsock32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="libc-2.10.1.so" Type="Document" URL="/lib/libc-2.10.1.so"/>
			<Item Name="libNodeInfo.dll" Type="Document" URL="../../../../../../../../C/GPL/Projects/NodeMon/bin/libNodeInfo.dll"/>
			<Item Name="libNodeInfo.so" Type="Document" URL="../../../../../../../../C/GPL/Projects/NodeMon/bin/libNodeInfo.so"/>
			<Item Name="Initialize Report.vi" Type="VI" URL="/E/Program Files/National Instruments/LabVIEW 2009/examples/reports/TextReport.llb/Initialize Report.vi"/>
			<Item Name="DeviceBase.lvlib" Type="Library" URL="../../../CSApplicationBaseClasses/DeviceBase/DeviceBase.lvlib"/>
			<Item Name="Advapi32.dll" Type="Document" URL="Advapi32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="kernel32.dll" Type="Document" URL="kernel32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="PRIVATE.i attribute.ctl" Type="VI" URL="../../A3-HumGUI/inheritance/PRIVATE.i attribute.ctl"/>
			<Item Name="PRIVATE.i attribute.vi" Type="VI" URL="../../A3-HumGUI/inheritance/PRIVATE.i attribute.vi"/>
			<Item Name="lvanlys.dll" Type="Document" URL="/C/Programme/National Instruments/LabVIEW 2009/resource/lvanlys.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="POLARIS_BME_DG" Type="EXE">
				<Property Name="App_applicationGUID" Type="Str">{7F3C10B4-915F-4210-BFAB-70B7B29A668A}</Property>
				<Property Name="App_applicationName" Type="Str">POLARIS_BME_DG.exe</Property>
				<Property Name="App_companyName" Type="Str">FSU</Property>
				<Property Name="App_fileDescription" Type="Str">POLARIS_BME_DG</Property>
				<Property Name="App_fileVersion.major" Type="Int">1</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{4E258EA9-3A6F-4B11-9397-86F85C395BCA}</Property>
				<Property Name="App_INI_GUID" Type="Str">{25F96D13-40BA-44D1-A77A-A49217A0623B}</Property>
				<Property Name="App_internalName" Type="Str">POLARIS_BME_DG</Property>
				<Property Name="App_legalCopyright" Type="Str">Copyright © 2012 FSU</Property>
				<Property Name="App_productName" Type="Str">POLARIS_BME_DG</Property>
				<Property Name="App_winsec.description" Type="Str">http://www.FSU.com</Property>
				<Property Name="Bld_buildSpecDescription" Type="Str">Configure DGs and run.</Property>
				<Property Name="Bld_buildSpecName" Type="Str">POLARIS_BME_DG</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Destination[0].destName" Type="Str">POLARIS_BME_DG.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../NI_AB_PROJECTNAME/builds/POLARIS_BME_DG.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../NI_AB_PROJECTNAME/builds/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{5DBA80BC-CBDA-48A8-94D7-0D1A58F3B398}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/POLARIS BME DG.lvlib/DG System class/BME_DG_System.lvclass/Configure Systems.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/POLARIS BME DG.lvlib/Test PC from CnfgFile.vi</Property>
				<Property Name="Source[2].properties[0].type" Type="Str">Run when opened</Property>
				<Property Name="Source[2].properties[0].value" Type="Bool">false</Property>
				<Property Name="Source[2].propertiesCount" Type="Int">1</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/POLARIS BME DG.lvlib/Binaries and C/DelayGenerator.dll</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/POLARIS BME DG.lvlib/Binaries and C/CpSource/DG_Data.h</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/POLARIS BME DG.lvlib/Binaries and C/PlxApi641.dll</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="SourceCount" Type="Int">6</Property>
			</Item>
		</Item>
	</Item>
</Project>
