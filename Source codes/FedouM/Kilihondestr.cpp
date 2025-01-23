#include <windows.h>
#pragma comment(lib, "winmm.lib")
#define _USE_MATH_DEFINES 1
#include <cmath>
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "msimg32.lib")

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

DWORD WINAPI ellipse(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		POINT cursor;
		GetCursorPos(&cursor);
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, cursor.x + 50, cursor.y + 50, cursor.x - 50, cursor.y - 50);
		Ellipse(hdc, cursor.x + 45, cursor.y + 45, cursor.x - 45, cursor.y - 45);
		Ellipse(hdc, cursor.x + 40, cursor.y + 40, cursor.x - 40, cursor.y - 40);
		Ellipse(hdc, cursor.x + 35, cursor.y + 35, cursor.x - 35, cursor.y - 35);
		Ellipse(hdc, cursor.x + 30, cursor.y + 30, cursor.x - 30, cursor.y - 30);
		Ellipse(hdc, cursor.x + 25, cursor.y + 25, cursor.x - 25, cursor.y - 25);
		Ellipse(hdc, cursor.x + 20, cursor.y + 20, cursor.x - 20, cursor.y - 20);
		Ellipse(hdc, cursor.x + 15, cursor.y + 15, cursor.x - 15, cursor.y - 15);
		Ellipse(hdc, cursor.x + 10, cursor.y + 10, cursor.x - 10, cursor.y - 10);
		Ellipse(hdc, cursor.x + 5, cursor.y + 5, cursor.x - 5, cursor.y - 5);
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
		BitBlt(hdc, rand() % 10, rand() % 10, xs, ys, hdc, rand() % 10, rand() % 10, SRCAND);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader1(LPVOID lpParam)
{
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3)
	{
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 1 / 2;
		BYTE byte = 255;
		if ((GetTickCount() - time) > 60000)
			byte = rand() % 8472151007;
		for (int i = 0; w * h > i; i++)
		{
			if (i % h == 0 && rand() % 100 == 0)
				v = rand() % 50;
			*((BYTE*)data + 4 * i) = ((BYTE*)(data + i + h))[v - i] ^ byte;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}

DWORD WINAPI stretch(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	double x = 0.0;
	while (1)
	{
		hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int a = (int)(sin(x) * 50.0);
		int b = (int)(cos(x) * 50.0);
		SetStretchBltMode(hdc, 3);
		StretchBlt(hdc, a / 2, b / 2, w - a, h - b, hdc, 0, 0, w, h, NOTSRCERASE);
		x = x + 0.1963495408493621;
		DeleteObject(hdc);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI invcc(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	while (1)
	{
		hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		HRGN hrgn = CreateEllipticRgn(rand() % w, rand() % h, rand() % w, rand() % h);
		InvertRgn(hdc, hrgn);
		DeleteObject(hdc);
		DeleteObject(hrgn);
		Sleep(10);
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

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if ((t >> 7 ^ t >> 12) != 0)
			buffer[t] = static_cast<char>(t * t / (t >> 7 ^ t >> 12));

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
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 7) | t >> 4 | t >> 5);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 4000, 4000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[4000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t & t % 255) ^ t) - t;

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
		buffer[t] = static_cast<char>(t >> 2) * (t >> 5) | t >> (t & 4096 ? 2 : 3);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main()
{
	if (MessageBoxW(NULL, L"Run Malware?", L"Kilihondestr.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure?", L"Kilihondestr.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(2000);
			HANDLE thread1 = CreateThread(0, 0, ink, 0, 0, 0);
			HANDLE thread1dot1 = CreateThread(0, 0, ellipse, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread2 = CreateThread(0, 0, shader1, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread3 = CreateThread(0, 0, stretch, 0, 0, 0);
			HANDLE thread3dot1 = CreateThread(0, 0, invcc, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			TerminateThread(thread3dot1, 0);
			CloseHandle(thread3dot1);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE thread4 = CreateThread(0, 0, melt, 0, 0, 0);
			HANDLE thread4dot1 = CreateThread(0, 0, polygon, 0, 0, 0);
			sound4();
			Sleep(30000);
		}
	}
}