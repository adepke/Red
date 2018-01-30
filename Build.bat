@ECHO OFF

set MSBUILDPATH="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin"
start %MSBUILDPATH%\MSBuild.exe Red.sln /t:Build /p:Configuration=Release /p:Platform="x64" /nologo
