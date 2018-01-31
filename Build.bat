@ECHO OFF

SETLOCAL ENABLEDELAYEDEXPANSION

IF NOT EXIST "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
	ECHO "An installion of Microsoft Visual Studio 2017 version 15.2 or later does not exist."
	PAUSE
	EXIT /B
)

FOR /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath`) DO (
  SET VSINSTALLPATH=%%i
)

CALL "!VSINSTALLPATH!\Common7\Tools\VsDevCmd.bat"

MSBuild.exe "%~dp0\Red.sln" /t:Build /p:Configuration=Release /p:Platform="x64" /nologo

PAUSE
