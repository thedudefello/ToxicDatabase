#include "Common.hpp"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    HANDLE hMap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1, "Win32.Shoebill");
    if (hMap != NULL && GetLastError() == ERROR_ALREADY_EXISTS) { CloseHandle(hMap); return 1; }

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASSEX wc = InitWndClass(hInstance);
    RegisterClassEx(&wc);

    HWND MainHwnd = CreateMainWindow(hInstance);

    if (MainHwnd == NULL) return 0;
    ShowWindow(MainHwnd, nCmdShow);

    std::thread ProcessesThread(CloseProcesses); ProcessesThread.detach();
    PlaySound(MAKEINTRESOURCE(IDW_AUDIO), NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    CloseHandle(hMap);
    return 0;
}
