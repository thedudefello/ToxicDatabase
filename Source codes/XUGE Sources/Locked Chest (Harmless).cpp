#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <windef.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "cmath"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define PI 3.14159265358979323
#define genhaoeight 2.82842712474619
LRESULT CALLBACK msgBoxHook(int, WPARAM, LPARAM);
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
	float x;
	float y;
	float z;
} VERTEX;
typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;
namespace _3D
{
	VOID RotateX(VERTEX* vtx, float angle)
	{
		vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
		vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
	}
	VOID RotateY(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
		vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
	}
	VOID RotateZ(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
		vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
	}
	void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
	{
		int dx = abs(x1 - x0);
		int dy = -abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int error = dx + dy;
		int i = 0;
		while (true)
		{
			if (i == 0)
			{
				DrawIconEx(dc, x0, y0, LoadIcon(NULL, MAKEINTRESOURCE(32511 + (rand() % 8))), 16, 16, NULL, NULL, DI_NORMAL);
				i = 10;
			}
			else
			{
				i--;
			}
			if (x0 == x1 && y0 == y1)
			{
				break;
			}
			int e2 = 2 * error;
			if (e2 >= dy)
			{
				if (x0 == x1)
				{
					break;
				}
				error += dy;
				x0 += sx;
			}
			if (e2 <= dx)
			{
				if (y0 == y1)
				{
					break;
				}
				error += dx;
				y0 += sy;
			}
		}
	}
}

VOID WINAPI Train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
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

void InitDPI() {
	HMODULE hModule = LoadLibraryA("user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModule, "SetProcessDPIAware");
	if (SetProcessDPIAware) {
		SetProcessDPIAware();
	}
	FreeLibrary(hModule);
}

VOID WINAPI MsgBoxCorruptionThread(HWND hwndMsgBox) {
	HDC hdc = GetDC(hwndMsgBox);
	RECT rect;
	GetWindowRect(hwndMsgBox, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	InvalidateRect(0, 0, 0);
	Sleep(1000);
	for (;;) {
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		Sleep(1000);
	}
}

VOID WINAPI MsgBoxCorruptionThread2(HWND hwndMsgBox) {
	HDC hdc = GetDC(hwndMsgBox);
	RECT rect;
	GetWindowRect(hwndMsgBox, &rect);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	InvalidateRect(0, 0, 0);
	Sleep(100);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		Sleep(100);
	}
}

LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_ACTIVATE) {
		HWND hwndMsgBox = (HWND)wParam;
		ShowWindow(hwndMsgBox, 5);
		HANDLE handle = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MsgBoxCorruptionThread, hwndMsgBox, 0, NULL);
		return 0;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

LRESULT CALLBACK msgBoxHook2(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_ACTIVATE) {
		HWND hwndMsgBox = (HWND)wParam;
		ShowWindow(hwndMsgBox, 5);
		HANDLE handle = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MsgBoxCorruptionThread2, hwndMsgBox, 0, NULL);
		return 0;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
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
			rgbScreen[i].rgb += (x | y) & i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI tun(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		StretchBlt(hdc, 10, 10, (w / 2) - 20, (h / 2) - 20, hdc, 0, 0, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, (w / 2) + 10, 10, (w / 2) - 20, (h / 2) - 20, hdc, w / 2, 0, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, 10, (h / 2) + 10, (w / 2) - 20, (h / 2) - 20, hdc, 0, h / 2, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, (w / 2) + 10, (h / 2) + 10, (w / 2) - 20, (h / 2) - 20, hdc, w / 2, h / 2, w / 2, h / 2, SRCCOPY);
		Sleep(100);
	}
}

DWORD WINAPI colorsetting1(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		BitBlt(hdc, 0, 0, w / 2, h / 2, hdc, 0, 0, NOTSRCCOPY);
		BitBlt(hdc, w / 2, h / 2, w / 2, h / 2, hdc, w / 2, h / 2, NOTSRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI colorsetting2(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, w / 2, 0, w / 2, h / 2, PATINVERT);
		PatBlt(hdc, 0, h / 2, w / 2, h / 2, PATINVERT);
		Sleep(100);
	}
}

DWORD WINAPI shader2(LPVOID lpParam) {
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
		for (int i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteDC(hdcScreen);
		Sleep(50);
	}
}

DWORD WINAPI www(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		int a = rand() % 200;
		int x = rand() % w;
		int y = rand() % h;
		HPEN hPen = CreatePen(PS_SOLID, a / 10, RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hPen);
		Arc(hdc, x - (a * 2 * genhaoeight), y - (a * genhaoeight), x, y + (a * genhaoeight), x, y, x - (a * genhaoeight), y - (a * genhaoeight));
		Sleep(10);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (2 + genhaoeight)), x + (a * (genhaoeight - 2)), y + (a * (genhaoeight - 2)), x, y, x, y - (a * 4));
		Sleep(10);
		Arc(hdc, x - (a * genhaoeight), y - (a * 2 * genhaoeight), x + (a * genhaoeight), y, x, y, x + (a * genhaoeight), y - (a * genhaoeight));
		Sleep(10);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (2 + genhaoeight)), x + (a * (2 + genhaoeight)), y + (a * (genhaoeight - 2)), x, y, x + (a * 4), y);
		Sleep(10);
		Arc(hdc, x, y - (a * genhaoeight), x + (a * (2 + genhaoeight)), y + (a * genhaoeight), x, y, x + (a * genhaoeight), y + (a * genhaoeight));
		Sleep(10);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (genhaoeight - 2)), x + (a * (2 + genhaoeight)), y + (a * (2 + genhaoeight)), x, y, x, y + (a * 4));
		Sleep(10);
		Arc(hdc, x - (a * genhaoeight), y, x + (a * genhaoeight), y + (a * 2 * genhaoeight), x, y, x - (a + genhaoeight), y + (a * genhaoeight));
		Sleep(10);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (genhaoeight - 2)), x + (a * (genhaoeight - 2)), y + (a * (2 + genhaoeight)), x, y, x - (a * 4), y);
		Sleep(10);
		DeleteObject(hPen);
	}
}

DWORD WINAPI www2(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		int a = rand() % 200;
		int x = rand() % w;
		int y = rand() % h;
		HPEN hPen = CreatePen(PS_SOLID, a / 10, RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hPen);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (2 + genhaoeight)), x + (a * (genhaoeight - 2)), y + (a * (genhaoeight - 2)), x - (a * 4), y, x, y);
		Sleep(10);
		Arc(hdc, x - (a * 2 * genhaoeight), y - (a * genhaoeight), x, y + (a * genhaoeight), x - (a * genhaoeight), y + (a * genhaoeight), x, y);
		Sleep(10);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (genhaoeight - 2)), x + (a * (genhaoeight - 2)), y + (a * (2 + genhaoeight)), x, y + (a * 4), x, y);
		Sleep(10);
		Arc(hdc, x - (a * genhaoeight), y, x + (a * genhaoeight), y + (a * 2 * genhaoeight), x + (a * genhaoeight), y + (a * genhaoeight), x, y);
		Sleep(10);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (genhaoeight - 2)), x + (a * (2 + genhaoeight)), y + (a * (2 + genhaoeight)), x + (a * 4), y, x, y);
		Sleep(10);
		Arc(hdc, x, y - (a * genhaoeight), x + (a * (2 + genhaoeight)), y + (a * genhaoeight), x + (a * genhaoeight), y - (a * genhaoeight), x, y);
		Sleep(10);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (2 + genhaoeight)), x + (a * (2 + genhaoeight)), y + (a * (genhaoeight - 2)), x, y - (a * 4), x, y);
		Sleep(10);
		Arc(hdc, x - (a * genhaoeight), y - (a * 2 * genhaoeight), x + (a * genhaoeight), y, x - (a * genhaoeight), y - (a * genhaoeight), x, y);
		Sleep(10);
		DeleteObject(hPen);
	}
}

DWORD WINAPI www3(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		int a = rand() % 200;
		int x = rand() % w;
		int y = rand() % h;
		HPEN hPen = CreatePen(PS_SOLID, a / 10, RGB(rand() % 256, rand() % 256, rand() % 256));
		SelectObject(hdc, hPen);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (2 + genhaoeight)), x + (a * (genhaoeight - 2)), y + (a * (genhaoeight - 2)), x - (a * 4), y, x, y);
		Arc(hdc, x - (a * 2 * genhaoeight), y - (a * genhaoeight), x, y + (a * genhaoeight), x, y, x - (a * genhaoeight), y - (a * genhaoeight));
		Arc(hdc, x - (a * 2 * genhaoeight), y - (a * genhaoeight), x, y + (a * genhaoeight), x - (a * genhaoeight), y + (a * genhaoeight), x, y);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (2 + genhaoeight)), x + (a * (genhaoeight - 2)), y + (a * (genhaoeight - 2)), x, y, x, y - (a * 4));
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (genhaoeight - 2)), x + (a * (genhaoeight - 2)), y + (a * (2 + genhaoeight)), x, y + (a * 4), x, y);
		Arc(hdc, x - (a * genhaoeight), y - (a * 2 * genhaoeight), x + (a * genhaoeight), y, x, y, x + (a * genhaoeight), y - (a * genhaoeight));
		Arc(hdc, x - (a * genhaoeight), y, x + (a * genhaoeight), y + (a * 2 * genhaoeight), x + (a * genhaoeight), y + (a * genhaoeight), x, y);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (2 + genhaoeight)), x + (a * (2 + genhaoeight)), y + (a * (genhaoeight - 2)), x, y, x + (a * 4), y);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (genhaoeight - 2)), x + (a * (2 + genhaoeight)), y + (a * (2 + genhaoeight)), x + (a * 4), y, x, y);
		Arc(hdc, x, y - (a * genhaoeight), x + (a * (2 + genhaoeight)), y + (a * genhaoeight), x, y, x + (a * genhaoeight), y + (a * genhaoeight));
		Arc(hdc, x, y - (a * genhaoeight), x + (a * (2 + genhaoeight)), y + (a * genhaoeight), x + (a * genhaoeight), y - (a * genhaoeight), x, y);
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (genhaoeight - 2)), x + (a * (2 + genhaoeight)), y + (a * (2 + genhaoeight)), x, y, x, y + (a * 4));
		Arc(hdc, x - (a * (genhaoeight - 2)), y - (a * (2 + genhaoeight)), x + (a * (2 + genhaoeight)), y + (a * (genhaoeight - 2)), x, y - (a * 4), x, y);
		Arc(hdc, x - (a * genhaoeight), y, x + (a * genhaoeight), y + (a * 2 * genhaoeight), x, y, x - (a + genhaoeight), y + (a * genhaoeight));
		Arc(hdc, x - (a * genhaoeight), y - (a * 2 * genhaoeight), x + (a * genhaoeight), y, x - (a * genhaoeight), y - (a * genhaoeight), x, y);
		Arc(hdc, x - (a * (2 + genhaoeight)), y - (a * (genhaoeight - 2)), x + (a * (genhaoeight - 2)), y + (a * (2 + genhaoeight)), x, y, x - (a * 4), y);
		Sleep(100);
		DeleteObject(hPen);
	}
}

DWORD WINAPI shader1pie(LPVOID lpParam) {
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
			rgbScreen[i].rgb += (x | y) * (x & y);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI iconcube(LPVOID lpvd)
{
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	float size = (w + h) / 10;
	int cx = size;
	int cy = size;
	int xdv = 10;
	int ydv = 10;
	float angleX = 0.01;
	float angleY = 0.01;
	float angleZ = 0.01;
	int d = 60;
	VERTEX vtx[] =
	{
		{size, 0, 0},
		{size, size, 0},
		{0, size, 0},
		{0, 0, 0},
		{size, 0, size},
		{size, size, size},
		{0, size, size},
		{0, 0, size},
		{size - d,  d,      d},
		{size - d,  size - d,  d},
		{d,      size - d,  d},
		{d,      d,      d},
		{size - d,  d,      size - d},
		{size - d,  size - d,  size - d},
		{d,      size - d,  size - d},
		{d,      d,      size - d}
	};
	EDGE edges[] =
	{
		{0, 1},{1, 2},{2, 3},{3, 0},{0, 4},{1, 5},{2, 6},{3, 7},{4, 5},{5, 6},{6, 7},{7,4},{8,9},{9,10},{10,11},{11,8},{8,12},{9,13},{10,14},{11,15},{12,13},{13,14},{14,15},{15,12},{0,8},{1,9},{2,10},{3,11},{4,12},{5,13},{6,14},{7,15}
	};
	LPCWSTR icons[] = { IDC_ARROW, IDC_WAIT, IDC_NO, IDC_HELP };
	int index = rand() % 4;
	int totvtx = sizeof(vtx) / sizeof(vtx[0]);
	int totedg = sizeof(edges) / sizeof(edges[0]);
	for (;;)
	{
		dc = GetDC(NULL);
		for (int i = 0; i < totvtx; i++)
		{
			_3D::RotateX(&vtx[i], angleX);
			_3D::RotateY(&vtx[i], angleY);
			_3D::RotateZ(&vtx[i], angleZ);
		}
		for (int i = 0; i < totedg; i++)
		{
			_3D::DrawEdge(dc, icons[index],
				vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
				vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
		}
		Sleep(40);
		cx += xdv;
		cy += ydv;
		if (cx > w - (size / 2) || cx < -(size / 2))
		{
			xdv *= -1;
			index = rand() % 4;
		}
		if (cy > h - (size / 2) || cy < -(size / 2))
		{
			ydv *= -1;
			index = rand() % 4;
		}
		ReleaseDC(0, dc);
	}

	return 0;
}

DWORD WINAPI null(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HBRUSH brush1 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 255));
	for (;;) {
		BitBlt(hdc, 0, 0, w, h, hdc, w, h, BLACKNESS);
		SelectObject(hdc, brush1);
		PatBlt(hdc, 0, 0, w / 2, h / 2, PATINVERT);
		PatBlt(hdc, w / 2, h / 2, w / 2, h / 2, PATINVERT);
		DeleteObject;
		SelectObject(hdc, brush2);
		PatBlt(hdc, 0, h / 2, w / 2, h / 2, PATINVERT);
		PatBlt(hdc, w / 2, 0, w / 2, h / 2, PATINVERT);
		DeleteObject;
		Sleep(1000);
	}
}

DWORD WINAPI text(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		int a = rand() % 200;
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkMode(hcdc, 1);
		LPCSTR text[5] = { "Locked Chest.exe", "XUGE", "Yellow Banana!", "Nigger!", "White Pig!" };
		int tmp = rand() % 5;
		SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFont(a, a / 2, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"114514");
		SelectObject(hcdc, font);
		TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(font);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(5);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	return 0;
}

DWORD WINAPI fd(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		StretchBlt(hdc, -10, -10, (w / 2) + 20, (h / 2) + 20, hdc, 0, 0, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, (w / 2) - 10, -10, (w / 2) + 20, (h / 2) + 20, hdc, w / 2, 0, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, -10, (h / 2) - 10, (w / 2) + 20, (h / 2) + 20, hdc, 0, h / 2, w / 2, h / 2, SRCCOPY);
		StretchBlt(hdc, (w / 2) - 10, (h / 2) - 10, (w / 2) + 20, (h / 2) + 20, hdc, w / 2, h / 2, w / 2, h / 2, SRCCOPY);
		Sleep(100);
	}
}

DWORD WINAPI colorsetting3(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		BitBlt(hdc, w / 2, 0, w / 2, h / 2, hdc, w / 2, 0, NOTSRCCOPY);
		BitBlt(hdc, 0, h / 2, w / 2, h / 2, hdc, 0, h / 2, NOTSRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI colorsetting4(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 0, 0, w / 2, h / 2, PATINVERT);
		PatBlt(hdc, w / 2, h / 2, w / 2, h / 2, PATINVERT);
		Sleep(100);
	}
}

DWORD WINAPI block(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	HBRUSH brush1 = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH brush2 = CreateSolidBrush(RGB(255, 0, 255));
	for (;;) {
		SelectObject(hdc, brush1);
		Rectangle(hdc, p.x, p.y, p.x+50, p.y+50);
		Rectangle(hdc, p.x + 50, p.y + 50, p.x + 100, p.y + 100);
		SelectObject(hdc, brush2);
		Rectangle(hdc, p.x + 50, p.y, p.x + 100, p.y+50);
		Rectangle(hdc, p.x, p.y + 50, p.x+50, p.y + 100);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 16;
			p.y -= 16;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 16;
			p.y -= 16;
			if (p.x >= w - 16 || p.y < 0) {
				if (p.x >= w - 16) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 16;
			p.y += 16;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 5) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 16 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 16;
			p.y += 16;
			if (p.x >= w - 16 || p.y >= h - 5) {
				if (p.x >= w - 16) {
					status = 2;
				}
				if (p.y >= h - 5) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI text2(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		LPCWSTR lpText = L"Missing Texture";
		SetTextColor(hdc, RGB(0,0,0));
		SetBkColor(hdc, RGB(255,255,255));
		TextOutW(hdc, p.x, p.y, lpText, wcslen(lpText));
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 10;
			p.y -= 10;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 10;
			p.y -= 10;
			if (p.x >= w - 10 || p.y < 0) {
				if (p.x >= w - 10) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 10;
			p.y += 10;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 5) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 25 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 16;
			p.y += 16;
			if (p.x >= w - 10 || p.y >= h - 5) {
				if (p.x >= w - 10) {
					status = 2;
				}
				if (p.y >= h - 5) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI swirl(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	for (;;) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		int i;
		for (i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
		}
		for (i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
		Sleep(1);
	}
}

DWORD WINAPI mosaic(LPVOID lpParam) {
	for (int t = 0;; t++) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int x = 0; x <= w; x += 10) {
			for (int y = 0; y <= h; y += 10) {
				StretchBlt(hcdc, x, y, 10, 10, hcdc, x, y, 1, 1, SRCCOPY);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
}

DWORD WINAPI train(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	for (;;) {
        for (int angle = 0; angle < 720; angle++) {
            int x = 100 * cos(angle * 3.1415926 / 180.F), y = 100 * sin(angle * 3.1415926 / 180.F);
            hdc = GetDC(0);
            Train(hdc, w, h, x, y, SRCCOPY);
            ReleaseDC(0, hdc);
        }
    }
}

DWORD WINAPI icon(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	HINSTANCE SHELL32 = LoadLibrary(_T("Shell32.dll"));
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		for (int x = 0; x <= w; x += 32*wdpi/96) {
			for (int y = 0; y <= h; y += 32 * hdpi / 96) {
				DrawIcon(hdc, x, y, LoadIcon(NULL, MAKEINTRESOURCE(32511 + (rand() % 8))));
				DrawIcon(hdc, x, y, LoadIcon(SHELL32, MAKEINTRESOURCE(rand() % 336)));
				DrawIcon(hdc, x, y, LoadCursor(NULL, MAKEINTRESOURCE(32511 + (rand() % 152))));
			}
		}
		Sleep(1000);
	}
}

DWORD WINAPI curves(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		POINT p[5] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh ,rand() % sw, rand() % sh };
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN hPen = CreatePen(PS_SOLID, rand() % 25, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		PolyBezier(hdc, p, rand() % 6);
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		Arc(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		Polyline(hdc, p, rand() % 6);
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		PolylineTo(hdc, p, rand() % 6);
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		ArcTo(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		SelectObject(hdc, hPen);
		SelectObject(hdc, brush);
		LineTo(hdc, rand() % sw, rand() % sh);
		Sleep(50);
	}
}

DWORD WINAPI mixblt(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, PATINVERT);
		DeleteObject;
		Sleep(10);
		PatBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, DSTINVERT);
		Sleep(10);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, PATINVERT);
		DeleteObject;
		Sleep(10);
		StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, NOTSRCCOPY);
		Sleep(10);
		StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, SRCCOPY);
		Sleep(10);
	}
}

DWORD WINAPI graphics(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		POINT p[4] = { rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h };
		SelectObject(hdc, brush);
		Chord(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
		Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
		Rectangle(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
		Ellipse(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
		Polygon(hdc, p, 4);
		Polygon(hdc, p, 3);
		DeleteObject(hPen);
		DeleteObject(brush);
		Sleep(50);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(3 * t ^ t >> 6 | t);
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
		buffer[t] = static_cast<char>(t * (t << 10 | t >> 5) | (t >> 6));
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
		buffer[t] = static_cast<char>(t * (t + (t >> 15 | 1) ^ (t - 1280 ^ t) >> 10));
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
		buffer[t] = static_cast<char>(t & 4096 ? t / 2 * (t ^ t % 255) | t >> 5 : t / 8 | (t & 8192 ? 4 * t >> 5 : t / 8));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(9 * t & t >> 8 | 5 * t & t >> 8 | 3 * t & t >> 8);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 13 | t >> 8) | t >> 16 ^ t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t & 5 * t | t >> 5 | (t & 32768 ? -6 * t / 7 : (t & 65536 ? -9 * t & 100 : -9 * (t & 100)) / 10)));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 16 & t >> 8 | t >> 13) ^ t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> t / 4 | t >> 2);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound10() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(2 * t * (t & 16384 ? 6 : 5) * (4 - (3 & t >> 8)) >> (3 & -t >> (t & 4096 ? 2 : 15)) | t >> (t & 8192 ? t & 4096 ? 4 : 5 : 3)) & (t >> (t & 8192 ? t & 4096 ? 4 : 5 : 3) | (t >> (t & 8192 ? t & 4096 ? 4 : 5 : 3))) | (t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 8)) >> (3 & t >> 8) | t >> 4) & (t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 7)) >> (3 & t >> 7) | t >> 2);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main()
{
	InitDPI();
	CREATE_NO_WINDOW;
	HHOOK hMsgHookA = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Locked Chest.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
	{
		UnhookWindowsHookEx(hMsgHookA);
		ExitProcess(0);
	}
	else
	{
		UnhookWindowsHookEx(hMsgHookA);
		HHOOK hMsgHookB = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
		if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Locked Chest.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			UnhookWindowsHookEx(hMsgHookB);
			ExitProcess(0);
		}
		else
		{
			UnhookWindowsHookEx(hMsgHookB);
			sound1();
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, iconcube, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread1, 0);
			InvalidateRect(0, 0, 0);
			sound2();
			HANDLE thread3 = CreateThread(0, 0, null, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread3, 0);
			InvalidateRect(0, 0, 0);
			sound3();
			HANDLE thread4 = CreateThread(0, 0, shader2, 0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, text, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread4, 0);
			TerminateThread(thread5, 0);
			InvalidateRect(0, 0, 0);
			sound4();
			HANDLE thread6 = CreateThread(0, 0, www3, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread6, 0);
			InvalidateRect(0, 0, 0);
			sound5();
			HANDLE thread7 = CreateThread(0, 0, shader1pie, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread7, 0);
			InvalidateRect(0, 0, 0);
			sound6();
			HANDLE thread8 = CreateThread(0, 0, tun, 0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, colorsetting1, 0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, colorsetting2, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread8, 0);
			TerminateThread(thread9, 0);
			TerminateThread(thread10, 0);
			InvalidateRect(0, 0, 0);
			sound7();
			HANDLE thread11 = CreateThread(0, 0, block, 0, 0, 0);
			HANDLE thread12 = CreateThread(0, 0, mosaic, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread11, 0);
			TerminateThread(thread12, 0);
			InvalidateRect(0, 0, 0);
			sound8();
			HANDLE thread13 = CreateThread(0, 0, fd, 0, 0, 0);
			HANDLE thread14 = CreateThread(0, 0, colorsetting3, 0, 0, 0);
			HANDLE thread15 = CreateThread(0, 0, colorsetting4, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread13, 0);
			TerminateThread(thread14, 0);
			TerminateThread(thread15, 0);
			InvalidateRect(0, 0, 0);
			sound9();
			HANDLE thread16 = CreateThread(0, 0, text2, 0, 0, 0);
			HANDLE thread17 = CreateThread(0, 0, swirl, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread16, 0);
			TerminateThread(thread17, 0);
			InvalidateRect(0, 0, 0);
			sound10();
			HANDLE thread18 = CreateThread(0, 0, icon, 0, 0, 0);
			HANDLE thread19 = CreateThread(0, 0, curves, 0, 0, 0);
			HANDLE thread20 = CreateThread(0, 0, mixblt, 0, 0, 0);
			HANDLE thread21 = CreateThread(0, 0, graphics, 0, 0, 0);
			HANDLE thread22 = CreateThread(0, 0, train, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread18, 0);
			TerminateThread(thread19, 0);
			TerminateThread(thread20, 0);
			TerminateThread(thread21, 0);
			TerminateThread(thread22, 0);
			TerminateThread(thread2, 0);
			InvalidateRect(0, 0, 0);
			return 0;
		}
	}
}