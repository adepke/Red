@ECHO OFF

CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
MSBuild.exe "D:\Code\Projects\Red\Red.sln" /t:Build /p:Configuration=Release /p:Platform="x64" /nologo
