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

SET CONFIG=%1
IF NOT "%CONFIG%" == "Release" (
	IF NOT "%CONFIG%" == "Debug" (
		SET CONFIG=Release
	)
)

SET PLATFORM=%2
IF NOT "%PLATFORM%" == "x86" (
	IF NOT "%PLATFORM%" == "x64" (
		SET PLATFORM="x64"
	)
)

IF NOT "%3" == "HASNUGET" (
	mkdir Tools

	ECHO Fetching Latest NuGet...

	rem Get NuGet
	powershell -Command "Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile Tools/nuget.exe"

	rem Restore Required Packages
	cd Tools
	nuget.exe restore ../Red.sln
	cd ../
) ELSE (
	nuget.exe restore Red.sln
)

CALL "!VSINSTALLPATH!\Common7\Tools\VsDevCmd.bat"

MSBuild.exe "%~dp0\Red.sln" /t:Build /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /nologo

PAUSE
