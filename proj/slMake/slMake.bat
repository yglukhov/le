@REM () { cd "$(dirname "$0")"; python "$SLMAKE_PATH"; exit; }; @set () { export "$1"; }
@set SLMAKE_PATH="../../tools/slMake/slMain.py"

@REM $*
@echo off
cd "%~dp0"
C:\Python33\python %SLMAKE_PATH%
REM pause
