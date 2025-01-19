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

double intensity = 0.0;
bool state = false;

double fade(double maxIntensity) {
    if (state == false) {
        intensity += 1.0;
        if (intensity >= maxIntensity) {
            state = true;
        }
    }
    else {
        intensity -= 1.0;
        if (intensity <= 0) {
            state = false;
        }
    }
    return intensity;
}

DWORD WINAPI shader3b(LPVOID lpParam) {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int r = 0;

    COLOR* data = (COLOR*)VirtualAlloc(0, (x * y + x) * sizeof(COLOR), MEM_COMMIT, PAGE_READWRITE);
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, data);
    SelectObject(mdc, bmp);

    while (true) {
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(bmp, x * y * sizeof(COLOR), data);

        for (int i = 0; i < x * y; i++) {
            ((BYTE*)(data + i))[1 % 2] = ((BYTE*)(data + i))[r & 2];
        }

        SetBitmapBits(bmp, x * y * sizeof(COLOR), data);
        BitBlt(hdc, 0, 0, x, y, mdc, 0, 0, SRCCOPY);

        Sleep(10);

        r = fade(3);
    }
}

int main() {
    CreateThread(0, 0, shader3b, 0, 0, 0);
    Sleep(-1);
}