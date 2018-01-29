@ECHO OFF
where /q msbuild.exe
IF ERRORLEVEL 1 (
	ECHO MSBuild was not found in your system PATH. Please install Visual Studio or add MSBuild.exe to the system PATH if it already exists.
	PAUSE
) ELSE (
	msbuild Red.sln /t:Build /p:Configuration=Release /p:Platform="x64"
	PAUSE
)
