#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <windowsx.h>
#include <cstdlib>
#include <thread>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#define M_PI   3.14159265358979323846264338327950288
#define _USE_MATH_DEFINES 1

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;

int red, green, blue;
bool ifcolorblue = false, ifblue = false;

COLORREF Hue(int length) {
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

DWORD WINAPI balls(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
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
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI bitblt1(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 1, 1, xs, ys, desktop, -2, 2, SRCERASE);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}

DWORD WINAPI copyscreen(LPVOID lpParam) {
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desktop = GetDC(NULL);
		BitBlt(desktop, 1, 1, xs, ys, desktop, -2, 2, SRCCOPY);
		ReleaseDC(0, desktop);
		Sleep(10);
	}
}

DWORD WINAPI hslfill(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(NULL);
		int x = GetSystemMetrics(SM_CXSCREEN),
			y = GetSystemMetrics(SM_CYSCREEN);

		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, PATCOPY);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

DWORD WINAPI payload(LPVOID lpParam) {
	int sw, sh;

	while (1) {
		HDC hdc = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(hdc, -20, -20, sw + 40, sh + 40, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(4);
	}
}

DWORD WINAPI sh(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int X = GetSystemMetrics(SM_CXSCREEN);
	int Y = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN);
		int sh = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % 10, rand() % 10, sw, sh, hdc, rand() % 10, rand() % 10, SRCINVERT);
		ReleaseDC(0, hdc);
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t & 16384 ? 6 : 5)*(1 + (3 & t >> 10)) >> (3 & t >> 8) | t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t * (t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t >> 6 | t | t >> (t >> 16)) + (7 & t >> 11));

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
		buffer[t] = static_cast<char>(t + (t&t^t >> 6) - t * (t >> 9 & (t % 16 ? 2 : 6)&t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
	if (MessageBoxW(NULL, L"happywin.exe, Run?", L"happywin.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO) {
		ExitProcess(0);
	}
	else if (MessageBoxW(NULL, L"Last warning.", L"happywin.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO) {
		ExitProcess(0);
	}
	Sleep(700);
	HANDLE BOSS = CreateThread(0, 0, bitblt1, 0, 0, 0);
	sound1();
	Sleep(30000);
	Sleep(200);
	TerminateThread(BOSS, 0);
	CloseHandle(BOSS);
	HANDLE SCREEN = CreateThread(0, 0, copyscreen, 0, 0, 0);
	sound1();
	Sleep(30000);
	Sleep(200);
	TerminateThread(SCREEN, 0);
	CloseHandle(SCREEN);
	HANDLE e1 = CreateThread(0, 0, hslfill, 0, 0, 0);
	sound2();
	Sleep(60000);
	Sleep(200);
	TerminateThread(e1, 0);
	CloseHandle(e1);
	HANDLE e2 = CreateThread(0, 0, payload, 0, 0, 0);
	HANDLE e3 = CreateThread(0, 0, balls, 0, 0, 0);
	sound3();
	Sleep(30000);
	Sleep(200);
	TerminateThread(e2, 0);
	CloseHandle(e2);
	TerminateThread(e3, 0);
	CloseHandle(e3);
	HANDLE e4 = CreateThread(0, 0, payload, 0, 0, 0);
	sound3();
	Sleep(30000);
	Sleep(200);
	TerminateThread(e4, 0);
	CloseHandle(e4);
	HANDLE e5 = CreateThread(0, 0, sh, 0, 0, 0);
	HANDLE e6 = CreateThread(0, 0, balls, 0, 0, 0);
	sound4();
	Sleep(30000);
	Sleep(200);
}
