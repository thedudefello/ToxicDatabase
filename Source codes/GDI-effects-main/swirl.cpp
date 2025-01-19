#include <windows.h>
#include <math.h>

int main() {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    double angle = 0.0;

    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, x, y);
    SelectObject(mdc, bmp);

    while (true) {
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

        for (int i = 0; i < x + y; i++) {
            BitBlt(hdc, 0, i, x, 1, mdc, sin(angle) * 40, i, SRCCOPY);

            angle += 3.14159 / 80;
        }

        Sleep(10);

        for (int i = 0; i < x + y; i++) {
            BitBlt(hdc, i, 0, 1, y, mdc, i, sin(angle) * 40, SRCCOPY);

            angle += 3.14159 / 80;
        }

        Sleep(10);
    }
}