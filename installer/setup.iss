; filepath: setup.iss
[Setup]
AppName=H3urisTius - Transport Solver
AppVersion=1.0
DefaultDirName={pf}\H3urisTius-Transport
OutputBaseFilename=H3urisTius_Transport_Setup
Compression=lzma
SolidCompression=yes

; Archivo de licencia que se mostrará durante la instalación
LicenseFile=license.txt

; Ícono del instalador y del programa en el Panel de Control
SetupIconFile=truck1.ico
UninstallDisplayIcon={app}\truck1.ico

; Dejamos estas páginas habilitadas para que el usuario elija la carpeta y el grupo de programas
DisableDirPage=no
DisableProgramGroupPage=no

[Files]
; El ejecutable principal de tu aplicación
Source: "..\main.exe"; DestDir: "{app}"
; El icono, si deseas copiarlo a la carpeta de instalación
Source: "truck1.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\H3urisTius - Transport Solver"; Filename: "{app}\H3urisTius.exe"; IconFilename: "{app}\truck1.ico"
; Acceso directo en el escritorio
Name: "{commondesktop}\H3urisTius - Transport Solver"; Filename: "{app}\H3urisTius.exe"; IconFilename: "{app}\truck1.ico"

[Run]
Filename: "{app}\main.exe"; Description: "Ejecutar aplicación"; Flags: nowait postinstall skipifsilent