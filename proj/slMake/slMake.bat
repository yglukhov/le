@REM () { echo hi; }
set SLMAKE_PATH="..\..\tools\slMake\slMain.py"

@echo off
cd "%~dp0"
C:\Python33\python %SLMAKE_PATH%
pause
