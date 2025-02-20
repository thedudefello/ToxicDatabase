#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>

#if !defined(_UNICODE) && !defined(UNICODE)
#error "Please define _UNICODE and UNICODE in your project settings."
#endif

#define MESSAGE TEXT("Мышь была передвинута.\n\n")                  \
                TEXT("%WINDOWS_SHORT% должна быть перезагружена,")  \
                TEXT(" чтобы изменения вступили в силу.")

#define CAPTION TEXT("%WINDOWS_GENERIC%")

#define UM_MOUSEMOVE WM_USER + 1

typedef PWSTR (WINAPI *BrandingFormatString_t)(PCWSTR pstrFormat);

static PWSTR WINAPI BrandingFormatString(PCWSTR pstrFormat)
{
    FARPROC fpFuncAddress = NULL;
    HMODULE hWinBrandDll = NULL;
    
    hWinBrandDll = LoadLibraryEx(TEXT("winbrand.dll"), NULL,
                                 LOAD_LIBRARY_SEARCH_SYSTEM32);
    
    if (hWinBrandDll == NULL) {
        return NULL;
    }
    
    fpFuncAddress = GetProcAddress(hWinBrandDll, "BrandingFormatString");

    if (fpFuncAddress == NULL) {
        return NULL;
    }

    return ((BrandingFormatString_t) fpFuncAddress)(pstrFormat);
}

static BOOL EnablePrivilege(LPCTSTR lpszPrivilege)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    BOOL bResult = FALSE;

    bResult = OpenProcessToken(
        GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken
    );

    if (bResult == FALSE) {
        return FALSE;
    }

    LookupPrivilegeValue(NULL, lpszPrivilege, &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES),
                          NULL, NULL);

    bResult = (GetLastError() == ERROR_SUCCESS);

    CloseHandle(hToken);
    return bResult;
}

static DWORD WINAPI MouseMovedThread(LPVOID lpParam) 
{ 
    PWSTR pszFormatedMessage = BrandingFormatString(MESSAGE);
    PWSTR pszFormatedCaption = BrandingFormatString(CAPTION);

    MessageBox(
        NULL, pszFormatedMessage, pszFormatedCaption,
        MB_OK | MB_ICONWARNING | MB_SERVICE_NOTIFICATION | MB_SETFOREGROUND
    );

    GlobalFree(pszFormatedCaption);
    GlobalFree(pszFormatedMessage);

    if (EnablePrivilege(SE_SHUTDOWN_NAME) == FALSE) {
        return 0;
    }

    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_SOFTWARE);
    return 0;
} 

static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    PMSLLHOOKSTRUCT pMouseStruct = (PMSLLHOOKSTRUCT) lParam;

    if (nCode >= 0 && wParam == WM_MOUSEMOVE) {
        /* HACK: https://stackoverflow.com/a/14441981 */
        PostThreadMessage(
            GetCurrentThreadId(), UM_MOUSEMOVE,
            0, MAKELPARAM(pMouseStruct->pt.x, pMouseStruct->pt.y)
        );
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nCmdShow)
{
    RECT rcLock = {0};
    HHOOK hMouseHook = NULL;
    MSG msg = {0};

    Sleep(30000); /* 30s = 30000ms */

    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);

    if (hMouseHook == NULL) {
        return -1;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if ((msg.message == UM_MOUSEMOVE) && IsRectEmpty(&rcLock)) {
            rcLock.left = GET_X_LPARAM(msg.lParam);
            rcLock.top = GET_Y_LPARAM(msg.lParam);
            rcLock.right = rcLock.left + 1;
            rcLock.bottom = rcLock.top + 1;

            CreateThread(NULL, 0, MouseMovedThread, NULL, 0, NULL);
        }
        
        if (msg.message == UM_MOUSEMOVE) {
            ClipCursor(&rcLock);
            continue;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hMouseHook);
    return 0;
}