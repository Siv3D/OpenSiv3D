[Setup]
AppName=OpenSiv3D(0.6.5) for Web
AppVersion=0.6.5
WizardStyle=modern
SetupIconFile=..\..\WindowsDesktop\App\icon.ico
OutputBaseFilename=OpenSiv3D(0.6.5)Web
DefaultDirName={userdocs}\OpenSiv3D_0.6.5_Web
VersionInfoVersion=0.6.5.6
VersionInfoDescription=OpenSiv3D (0.6.5) for Web Installer
Compression=lzma2
SolidCompression=yes
ChangesEnvironment=yes
PrivilegesRequired=lowest
OutputDir=userdocs:Inno Setup Examples Output
DisableDirPage=no
DisableReadyPage=yes

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "ja"; MessagesFile: "compiler:Languages\Japanese.isl"

[Files]
Source: "..\..\Siv3D\include\*"; DestDir: "{app}\include"; Flags: recursesubdirs
Source: "..\Package\lib\libSiv3D.a"; DestDir: "{app}\lib"
Source: "..\Package\lib\libSiv3DScript.a"; DestDir: "{app}\lib"
Source: "..\Package\lib\libSiv3DWebGPU.a"; DestDir: "{app}\lib"
Source: "..\Package\lib\libSiv3DBrowserImageEncodeDecode.a"; DestDir: "{app}\lib"
Source: "..\Siv3D.js"; DestDir: "{app}\lib"
Source: "..\Siv3D.pre.js"; DestDir: "{app}\lib"
Source: "..\Siv3D.post.js"; DestDir: "{app}\lib"
Source: "..\Package\lib\Siv3D\*"; DestDir: "{app}\lib"; Flags: recursesubdirs
Source: "..\VisualStudioTemplate\OpenSiv3D(0.6.5)Web.zip"; DestDir: "{userdocs}\Visual Studio 2017\Templates\ProjectTemplates"
Source: "..\VisualStudioTemplate\OpenSiv3D(0.6.5)Web.zip"; DestDir: "{userdocs}\Visual Studio 2019\Templates\ProjectTemplates"
Source: "..\VisualStudioTemplate\OpenSiv3D(0.6.5)Web.zip"; DestDir: "{userdocs}\Visual Studio 2022\Templates\ProjectTemplates"

[Registry]
Root: HKCU; Subkey: "Environment"; ValueType:string; ValueName: "SIV3D_0_6_5_WEB"; \
    ValueData: "{app}"; Flags: preservestringtype
