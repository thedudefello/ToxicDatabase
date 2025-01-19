#include <windows.h>
#include <math.h>

typedef union COLOR {
    COLORREF rgb;
    struct {
        BYTE blue;
        BYTE green;
        BYTE red;
    };
} COLOR;

DWORD WINAPI shader7(LPVOID lpParam) {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int j = 1;
    int c = 0;

    COLOR* data = (COLOR*)VirtualAlloc(0, (x * y + x) * sizeof(COLOR), MEM_COMMIT, PAGE_READWRITE);
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, data);
    SelectObject(mdc, bmp);

    while (true) {
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(bmp, x * y * sizeof(COLOR), data);

        for (int x2 = 0; x2 < x; x2++) {
            for (int y2 = 0; y2 < y; y2++) {
                int j = c * 4;

                int wave = (int)(j + (j * ((x2 * x2) + (y2 * y2)) / 64));

                data[y2 * x + x2].rgb += wave;
            }
        }
        c++;

        SetBitmapBits(bmp, x * y * sizeof(COLOR), data);
        BitBlt(hdc, 0, 0, x, y, mdc, 0, 0, SRCCOPY);

        Sleep(10);
    }
}

int main() {
    CreateThread(0, 0, shader7, 0, 0, 0);
    Sleep(-1);
}