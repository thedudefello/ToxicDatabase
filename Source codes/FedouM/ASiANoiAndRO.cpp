//ASiANoiAndRO.exe - safety malware
#pragma once

#include <Windows.h>
#include <cmath>
#define _USE_MATH_DEFINES 1
#pragma comment(lib, "winmm.lib")
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "msimg32.lib")
static unsigned long xx = 123456789, yy = 362436069, zz = 521288629;
DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}

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

DWORD WINAPI cur(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		POINT cursor;
		GetCursorPos(&cursor);
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, cursor.x + 30, cursor.y + 30, cursor.x - 30, cursor.y - 30);
		Ellipse(hdc, cursor.x + 45, cursor.y + 45, cursor.x - 45, cursor.y - 45);
		Ellipse(hdc, cursor.x + 40, cursor.y + 40, cursor.x - 40, cursor.y - 40);
		Ellipse(hdc, cursor.x + 25, cursor.y + 25, cursor.x - 25, cursor.y - 25);
		Ellipse(hdc, cursor.x + 30, cursor.y + 30, cursor.x - 30, cursor.y - 30);
		Ellipse(hdc, cursor.x + 25, cursor.y + 25, cursor.x - 25, cursor.y - 25);
		Ellipse(hdc, cursor.x + 20, cursor.y + 20, cursor.x - 20, cursor.y - 20);
		Ellipse(hdc, cursor.x + 10, cursor.y + 10, cursor.x - 10, cursor.y - 10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI ink(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int xs = GetSystemMetrics(0);
	int ys = GetSystemMetrics(1);
	while (true)
	{
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 10, rand() % 10, xs, ys, hdc, rand() % 10, rand() % 10, SRCPAINT);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI polygon(LPVOID lpParam)
{
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1)
	{
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		POINT vertices[] =
		{
			{
				rand() % w, rand() % h
			},
			{
				rand() % w, rand() % h
			},
			{
				rand() % w, rand() % h
			}
		};
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI melt(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		int x = rand() % sw;
		int y = rand() % sh;
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, x, rand() % 8 - 4, rand() % 100, sh, hdc, x, 0, 0x1900AC010E);
		BitBlt(hdc, rand() % 8 - 4, y, sw, rand() % 100, hdc, 0, y, 0x1900AC010E);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload6(LPVOID lpParam) {
	int sw, sh;

	while (1) {
		HDC hdc = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(hdc, -20, -20, sw + 40, sh + 40, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(20);
	}
}


DWORD WINAPI blr(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 199;
	while (1) {
		desk = GetDC(0); HDC hdcMem = CreateCompatibleDC(desk);
		HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < 30; i++) {
			int x = -size + xorshift32() % (sw + size), y = -size + xorshift32() % (sh + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + xorshift32() % 17 - 8, y + xorshift32() % 17 - 8, SRCCOPY);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(desk, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(desk);
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

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(7 * (t >> 2 & 13 | t >> 7));

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
		buffer[t] = static_cast<char>(t*(0xCA98 >> (t >> 9 & 14) & 15) | t >> 8);

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
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t ^ t + (t >> 15 | 1) / (t - 1280 ^ t) >> 10));

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
		buffer[t] = static_cast<char>((t * (t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
	{
		if (MessageBoxW(NULL, L"Run Malware?", L"ASiANoiAndRO.exe", MB_YESNO) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"Are you sure?", L"ASiANoiAndRO.exe", MB_YESNO) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				Sleep(1000);
				HANDLE thread1dot1 = CreateThread(0, 0, cur, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, polygon, 0, 0, 0);
				HANDLE thread2 = CreateThread(0, 0, ink, 0, 0, 0);
				sound1();
				Sleep(30000);
				Sleep(200);
				TerminateThread(thread1, 0);
				CloseHandle(thread1);
				TerminateThread(thread2, 0);
				CloseHandle(thread2);
				HANDLE thread3 = CreateThread(0, 0, melt, 0, 0, 0);
				sound2();
				Sleep(30000);
				Sleep(200);
				TerminateThread(thread3, 0);
				CloseHandle(thread3);
				HANDLE thread4 = CreateThread(0, 0, payload6, 0, 0, 0);
				sound3();
				Sleep(30000);
				Sleep(200);
				TerminateThread(thread4, 0);
				CloseHandle(thread4);
				HANDLE thread5 = CreateThread(0, 0, blr, 0, 0, 0);
				sound4();
				Sleep(30000);
				Sleep(200);
				TerminateThread(thread5, 0);
				CloseHandle(thread5);
				HANDLE thread6 = CreateThread(0, 0, bitblt1, 0, 0, 0);
				sound5();
				Sleep(60000);
				Sleep(200);
			}
		}
	}
}