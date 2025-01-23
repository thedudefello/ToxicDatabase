#include <Windows.h>
#include <cmath>
#pragma comment(lib, "winmm.lib")
#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
/*typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;*/
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
/*COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}*/

DWORD WINAPI RGBCircle(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	int xs = rand() % x;
	int ys = rand() % y;

	HBRUSH circle = CreateSolidBrush(RGB(255, 0, 0));
	HPEN border = CreatePen(0, 1, RGB(255, 255, 255));

	int color = 0;

	while (true) {
		if (color == 1) {
			circle = CreateSolidBrush(RGB(255, 165, 0));
		}
		else if (color == 2) {
			circle = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (color == 3) {
			circle = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (color == 4) {
			circle = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (color == 5) {
			circle = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (color == 6) {
			circle = CreateSolidBrush(RGB(148, 0, 211));
		}
		else if (color == 7) {
			circle = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (color == 8) {
			circle = CreateSolidBrush(RGB(255, 0, 0));
			color = 0;
		}

		SelectObject(hdc, circle);
		SelectObject(hdc, border);

		if (xs >= x) {
			xs = rand() % x;
			ys = rand() % y;
		}
		else if (ys >= y) {
			xs = rand() % x;
			ys = rand() % y;
		}
		else if (xs <= 0) {
			xs = rand() % x;
			ys = rand() % y;
		}
		else if (ys <= 0) {
			xs = rand() % x;
			ys = rand() % y;
		}

		int sel = rand() % 4 + 1;

		for (int runtime = 0; runtime < 10; runtime++) {
			if (sel == 1) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs += 20;
				ys += 20;
				Sleep(130);
			}
			else if (sel == 2) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs += 20;
				ys -= 20;
				Sleep(130);
			}
			else if (sel == 3) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs -= 20;
				ys += 20;
				Sleep(130);
			}
			else if (sel == 4) {
				Ellipse(hdc, xs - 60, ys - 60, xs + 60, ys + 60);
				xs -= 20;
				ys -= 20;
				Sleep(130);
			}
		}
		color++;
	}
}


DWORD WINAPI Cursors(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);
	CURSORINFO cur;

	while (true) {
		int xs = 0;
		int ys = 0;
		int sel = rand() % 4 + 1;

		if (sel == 1) {
			xs = rand() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += 2;
				if (xs >= x) {
					ys = y;
				}
				Sleep(1);
			}
		}
		else if (sel == 2) {
			xs = rand() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += 2;
				if (xs >= x) {
					ys = 0;
				}
				Sleep(1);
			}
		}
		else if (sel == 3) {
			xs = rand() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = y;
				}
				Sleep(1);
			}
		}
		else if (sel == 4) {
			xs = rand() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = 0;
				}
				Sleep(1);
			}
		}
	}
}

DWORD WINAPI Sinewave(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i = 0;

	while (true) {
		for (int ys = 0; ys < y; ys++) {
			BitBlt(hdc, 8 * sin(i), ys, x, 1, hdc, 0, ys, SRCCOPY);
			i += 0.04;
		}
		Sleep(40);
	}
}

DWORD WINAPI Shake(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		BitBlt(hdc, 10, 10, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(50);
		BitBlt(hdc, -10, 10, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(50);
		BitBlt(hdc, 10, -10, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(50);
		BitBlt(hdc, -10, -10, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(50);
	}
}

DWORD WINAPI IconWave(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i;
	double wave;
	int xs;
	int ys;

	while (true) {
		int sel = rand() % 4 + 1;
		wave = 0;
		i = 0;

		if (sel == 1) {
			xs = 0;
			ys = rand() % y;

			for (; xs < x; xs += 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_ERROR));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 2) {
			xs = x;
			ys = rand() % y;

			for (; xs > 0; xs -= 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_WARNING));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 3) {
			xs = rand() % x;
			ys = 0;

			for (; ys < y; ys += 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_INFORMATION));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
		else if (sel == 4) {
			xs = rand() % x;
			ys = y;

			for (; ys > 0; ys -= 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_QUESTION));
				i += 0.05;
				wave += 0.32;
				Sleep(10);
			}
		}
	}
}

DWORD WINAPI Rotate(LPVOID lpstart) {
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

DWORD WINAPI Sinewave2(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i = 0;

	while (true) {
		for (int ys = 0; ys < y; ys++) {
			BitBlt(hdc, 8 * sin(i), ys, x, 1, hdc, 0, ys, SRCERASE);
			i += 0.04;
		}
		Sleep(40);
	}
}

DWORD WINAPI swirl(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
		}
		for (int i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
		Sleep(1);
	}
}

DWORD WINAPI shader1(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
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
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = (y + i * 4);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
		Sleep(5);
	}

	return 0x00;
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t*(t >> 7 | t << 2));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t*(t >> 7 | t << 8 | t >> 2));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(t*(t >> 8 | t << 4 | t & 16384));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(10 * (t >> 6 | t | t >> (t >> 16)) + (7 & t >> 11));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(2 * (t * (t >> 6 | t | t) + (7 & t >> 11)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
	if (MessageBoxW(NULL, L"This is a GDI Only, Run?", L"Holzet.exe by Nyfol2290", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It still contains flashing lights - NOT for epilepsy", L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷ - Holzet.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(1000);
			HANDLE thread1 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, Cursors, 0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, Sinewave, 0, 0, 0);
			sound1();
			Sleep(30000);
			Sleep(200);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			HANDLE thread4 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, Shake, 0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, IconWave, 0, 0, 0);
			sound2();
			Sleep(30000);
			Sleep(200);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			HANDLE thread7 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread8 = CreateThread(0, 0, Cursors, 0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, Shake, 0, 0, 0);
			HANDLE thread11 = CreateThread(0, 0, Rotate, 0, 0, 0);
			HANDLE thread12 = CreateThread(0, 0, IconWave, 0, 0, 0);
			sound2();
			Sleep(30000);
			Sleep(200);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			TerminateThread(thread9, 0);
			CloseHandle(thread9);
			TerminateThread(thread11, 0);
			CloseHandle(thread11);
			TerminateThread(thread12, 0);
			CloseHandle(thread12);
			HANDLE thread13 = CreateThread(0, 0, Sinewave2, 0, 0, 0);
			HANDLE thread14 = CreateThread(0, 0, IconWave, 0, 0, 0);
			HANDLE thread15 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread16 = CreateThread(0, 0, Shake, 0, 0, 0);
			sound3();
			Sleep(30000);
			Sleep(200);
			TerminateThread(thread13, 0);
			CloseHandle(thread13);
			TerminateThread(thread14, 0);
			CloseHandle(thread14);
			TerminateThread(thread15, 0);
			CloseHandle(thread15);
			TerminateThread(thread16, 0);
			CloseHandle(thread16);
			HANDLE thread17 = CreateThread(0, 0, swirl, 0, 0, 0);
			HANDLE thread18 = CreateThread(0, 0, IconWave, 0, 0, 0);
			HANDLE thread19 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread20 = CreateThread(0, 0, Cursors, 0, 0, 0);
			sound4();
			Sleep(30000);
			Sleep(200);
			TerminateThread(thread17, 0);
			CloseHandle(thread17);
			TerminateThread(thread18, 0);
			CloseHandle(thread18);
			TerminateThread(thread19, 0);
			CloseHandle(thread19);
			TerminateThread(thread20, 0);
			CloseHandle(thread20);
			HANDLE thread21 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread22 = CreateThread(0, 0, RGBCircle, 0, 0, 0);
			HANDLE thread23 = CreateThread(0, 0, IconWave, 0, 0, 0);
			HANDLE thread24 = CreateThread(0, 0, Cursors, 0, 0, 0);
			sound5();
			Sleep(60000);
			Sleep(200);
		}
	}
}