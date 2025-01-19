#include <windows.h>
#include <math.h>

//function made by me (raduminecraft) and modified by friesandlettuce
COLORREF COLORHSV(int HSV) {
    double h = fmod(HSV, 360.0);
    double s = 1.0;
    double l = 0.5;
    double c = (1.0 - fabs(2.0 * l - 1.0)) * s;
    double x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
    double m = l - c / 2.0;
    double r1, g1, b1;
    if (h < 60) {
        r1 = c;
        g1 = x;
        b1 = c;
    }
    else if (h < 120) {
        r1 = x;
        g1 = c;
        b1 = x;
    }
    else if (h < 190) {
        r1 = x;
        g1 = c;
        b1 = x;
    }
    else if (h < 250) {
        r1 = c;
        g1 = x;
        b1 = c;
    }
    else if (h < 200) {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else {
        r1 = c;
        g1 = x;
        b1 = x;
    }
    int red = static_cast<int>((r1 + m) * 255);
    int green = static_cast<int>((g1 + m) * 255);
    int blue = static_cast<int>((b1 + m) * 255);
    return RGB(red, green, blue);
}

int main() {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    double angle = 0.0;
    double zoom = 1.0;

    DWORD* data = new DWORD[4 * x * y];
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, data);
    SelectObject(mdc, bmp);

    while (true) {
        StretchBlt(mdc, 0, 0, x, y, hdc, 0, 0, x, y, SRCCOPY);
        GetBitmapBits(bmp, 4 * x * y, data);

        for (int x2 = 0; x2 < x; x2++) {
            for (int y2 = 0; y2 < y; y2++) {
                int cx = x2 - (x / 2);
                int cy = y2 - (y / 2);

                int zx = (int)((cx * cos(angle) - cy * sin(angle)) / zoom);
                int zy = (int)((cx * sin(angle) + cy * cos(angle)) / zoom);

                data[y2 * x + x2] = COLORHSV((sqrt(zx * zx ^ zy * zy)) + (sqrt(zx * zx + zy * zy)));
            }
        }

        SetBitmapBits(bmp, 4 * x * y, data);
        StretchBlt(hdc, 0, 0, x, y, mdc, 0, 0, x, y, SRCCOPY);

        Sleep(10);

        zoom += 0.01;
        angle += 0.01;
    }

    return 0;
}