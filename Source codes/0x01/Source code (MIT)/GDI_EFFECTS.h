#pragma comment(lib, "GDI32")
#include "COLOR_EFFECTS.h"

CONST INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
CONST FLOAT PI = acos(-1);

typedef union _COLORPAL32 {
	COLORREF cpColors;
	struct {
		BYTE cpBlue;
		BYTE cpGreen;
		BYTE cpRed;
		BYTE cpUnused;
	};
} COLORPAL32, *lpCOLORPAL32;

typedef DWORD GDI_EFFECT;
DWORD GDI_TIME;

BITMAPINFO bmicrt(INT x, INT y) {
	BITMAPINFO bmi = {sizeof(bmi), x, y, 1, 32, BI_RGB};
	return bmi;
}

typedef HANDLE *DIBSECTIONBITS;

namespace GDI {
	GDI_EFFECT WINAPI IconGrid(LPVOID lpVoid) {
		GDI_TIME = 29 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			for (INT x = 0; x < w; x += 20) {
				for (INT y = 0; y < h; y += 20) {
					DrawIcon(hdc, x, y, LoadIcon(NULL, IDI_QUESTION));
				}
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI AngleGliding(LPVOID lpVoid) {
		GDI_TIME = 29 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			RECT rect;
			POINT point[3];
			GetWindowRect(GetDesktopWindow(), &rect);
			point[0].x = rect.left - 5; point[0].y = rect.top;
			point[1].x = rect.right + 15; point[1].y = rect.top;
			point[2].x = rect.left + 20; point[2].y = rect.bottom - 5;
			PlgBlt(hdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI RandomCircle(LPVOID lpVoid)
	{
		GDI_TIME = 29 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = bmicrt(wx, hx);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			INT rw = rand() % w, rh = rand() % h;
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT INDEX = y * wx + x;
					INT cx = x - rw / 2, cy = y - rh / 2;
					INT dx = cx * cx, dy = cy * cy;
					INT d = 128;
					INT fx = d + (d * sin(sqrt(dx + dy) / d));
					rgb[INDEX].rgbRed += fx;
					rgb[INDEX].rgbGreen += fx;
					rgb[INDEX].rgbBlue += fx;
				}
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, PATINVERT | SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI HSVShader1(LPVOID lpVoid)
	{
		GDI_TIME = 30 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			INT wx = w / 8, hx = h / 8;
			HSV hsv;
			BITMAPINFO bmi = bmicrt(wx, hx);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			SetStretchBltMode(mdc, STRETCH_DELETESCANS);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT INDEX = y * wx + x;
					RGBQUAD rgb2 = rgb[INDEX];
					hsv = rgbQuadToHSV(rgb2);
					INT FX = (((i + x) * (x - i)) + ((i + y) * (i + y))) / 10;
					hsv.h = fmod((FX / 400.f) + y / h * .05f, 1);
					hsv.s = 1.f;
					hsv.v = 0.5f;
					rgb[INDEX] = hsvToRGB(hsv);
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI IconPattern(LPVOID lpVoid)
	{
		GDI_TIME = 30 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			INT zx = cos(i * 3) * (w / 2) + (w / 2), zy = tan(i * 4) * (h / 2) + (h / 2);
			DrawIcon(hdc, zx, zy, LoadIcon(NULL, IDI_APPLICATION));
			i++;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI HSVShader2(LPVOID lpVoid)
	{
		GDI_TIME = 31 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			INT wx = w / 8, hx = h / 8;
			HSV hsv;
			BITMAPINFO bmi = bmicrt(wx, hx);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			SetStretchBltMode(mdc, STRETCH_DELETESCANS);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT INDEX = y * wx + x;
					RGBQUAD rgb2 = rgb[INDEX];
					hsv = rgbQuadToHSV(rgb2);
					INT FX = i ^ (x ^ y) * RGB(5, 10, 0);
					hsv.h = fmod((FX / 400.f) + hsv.h + .05f, 1);
					hsv.s = 1.f;
					rgb[INDEX] = hsvToRGB(hsv);
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI RotateDownBlend(LPVOID lpVoid)
	{
		GDI_TIME = 31 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			SelectObject(mdc, CreateDiscardableBitmap(hdc, w, h));
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			RECT rect;
			POINT point[3];
			GetWindowRect(GetDesktopWindow(), &rect);
			point[0].x = rect.left + 30; point[0].y = rect.top;
			point[1].x = rect.right + 30; point[1].y = rect.top + 30;
			point[2].x = rect.left - 20; point[2].y = rect.bottom;
			PlgBlt(mdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI IntegerTextouts(LPVOID lpVoid)
	{
		GDI_TIME = 31 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			LPCSTR szStrings[] = {
				"1", "2", "4", "8", "16",
				"32", "64", "128", "256", "512",
				"1024", "2048", "4096", "8192", "16384",
				"32768", "65536", "131072", "262144", "2147483648" // Jumped straight into 2147483648 because idk
			};
			INT totstr = sizeof(szStrings) / sizeof(szStrings[0]);
			for (INT i = 0; i < totstr; i++) {
				HFONT hfont = CreateFontW(rand() % 25 + 50, 0, rand() % 50 - 25, 0, FW_BOLD, FALSE, TRUE, FALSE, OEM_CHARSET, 0, 0, 0, 0, L"Roman");
				SelectObject(hdc, hfont);
				INT rgb = rand() % 255;
				SetBkColor(hdc, RGB(rgb, rgb, rgb));
				SetTextColor(hdc, RGB(0, 0, 0));
				TextOutA(hdc, rand() % w, rand() % h, szStrings[i], lstrlenA(szStrings[i]));
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI FractalRotation(LPVOID lpVoid)
	{
		GDI_TIME = 30 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		DOUBLE angle = 0.f;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			COLORPAL32 *cp;
			BITMAPINFO bmi = bmicrt(w, h);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&cp, NULL, 0));
			StretchBlt(mdc, rand() % 8, rand() % 8, w, h, hdc, rand() % 8, rand() % 8, w, h, SRCCOPY); // What was the shaking for
			for (INT y = 0; y < h; y++) {
				for (INT x = 0; x < w; x++) {
					INT data = y * w + x;
					INT cx = x - w / 2, cy = y - h / 2;
					INT ax = cos(angle) * cx - sin(angle) * cy;
					INT ay = sin(angle) * cx + cos(angle) * cy;
					cp[data].cpRed = (x^y) ^ i;
					cp[data].cpGreen = ay - i;
					cp[data].cpBlue = ax + i;
				}
			}
			i += 16;
			angle += 0.02f;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI UnknownPlgBlt(LPVOID lpVoid)
	{
		GDI_TIME = 30 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			SelectObject(mdc, CreateDiscardableBitmap(hdc, w, h));
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			RECT rect;
			POINT point[3];
			GetWindowRect(GetDesktopWindow(), &rect);
			point[0].x = rect.left + 10; point[0].y = rect.top - 20;
			point[1].x = rect.right + 30; point[1].y = rect.top - 50;
			point[2].x = rect.left - 20; point[2].y = rect.bottom;
			PlgBlt(mdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI SpinBlur(LPVOID lpVoid)
	{
		GDI_TIME = 29 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		DOUBLE angle = 0.f;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			SelectObject(mdc, CreateDiscardableBitmap(hdc, w, h));
			RECT rect;
			POINT point[3];
			GetWindowRect(GetDesktopWindow(), &rect);
			INT i = cos(angle) * 30;
			point[0].x = rect.left + i; point[0].y = rect.top - i;
			point[1].x = rect.right + i; point[1].y = rect.top + i;
			point[2].x = rect.left - i; point[2].y = rect.bottom - i;
			PlgBlt(mdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			angle += PI / 10;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI HSVShader3(LPVOID lpVoid)
	{
		GDI_TIME = 29 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			HSV hsv;
			BITMAPINFO bmi = bmicrt(w, h);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < w; x++) {
				for (INT y = 0; y < h; y++) {
					INT INDEX = y * w + x;
					RGBQUAD rgb2 = rgb[INDEX];
					hsv = rgbQuadToHSV(rgb2);
					INT FX = i * 24;
					hsv.h = fmod((FX / 400.f) + hsv.h + .05f, 1);
					hsv.s = 1.f;
					rgb[INDEX] = hsvToRGB(hsv);
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI UnknownRGB(LPVOID lpVoid)
	{
		GDI_TIME = 30 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = bmicrt(wx, hx);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			SetStretchBltMode(mdc, STRETCH_HALFTONE);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					rgb[data].rgbRed = (x - i) * (y - i);
					rgb[data].rgbGreen = (x + i) * 4;
					rgb[data].rgbBlue = i ^ (x * y) / 10;
				}
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCPAINT);
			i++;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI IconGrid2(LPVOID lpVoid)
	{
		GDI_TIME = 61 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			for (INT y = 0; y < h; y += 52) {
				for (INT x = 0; x < w; x += 64) {
					DrawIcon(hdc, x, y, LoadIcon(NULL, IDI_ERROR));
					DrawIcon(hdc, y, x, LoadIcon(NULL, IDI_QUESTION));
				}
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI GradientTriangles(LPVOID lpVoid) // Screw off "gradient" or "trianglez"
	{
		GDI_TIME = 31 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
//		INT i = 0; No
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			// X, Y, RED, GREEN, BLUE, ALPHA //
			TRIVERTEX pVertex[3] = {
				rand() % w, rand() % h, 0xffff, 0, 0, 0xffff,
				rand() % w, rand() % h, 0, 0, 0, 0xffff,
				rand() % w, rand() % h, 0xffff, 0xffff, 0xffff, 0xffff
			};
			GRADIENT_TRIANGLE pMesh = {0, 1, 2};
			GdiGradientFill(hdc, pVertex, 3, &pMesh, 1, GRADIENT_FILL_TRIANGLE);
//			i++;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	GDI_EFFECT WINAPI FinalNoise(LPVOID lpVoid)
	{
		GDI_TIME = 31 * 1000;
		DWORD EndTime = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgb;
			INT wx = w / 16, hx = h / 16;
			BITMAPINFO bmi = bmicrt(wx, hx);
			SelectObject(mdc, CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (DIBSECTIONBITS)&rgb, NULL, 0));
			StretchBlt(mdc, rand() % 16, rand() % 16, wx, hx, hdc, rand() % 16, rand() % 16, w, h, SRCERASE);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					rgb[data].rgbRed = rand();
					rgb[data].rgbGreen = rand();
					rgb[data].rgbBlue = rand();
				}
			}
			StretchBlt(hdc, rand() % 3, rand() % 3, w, h, mdc, rand() % 3, rand() % 3, wx, hx, SRCERASE);
			i++;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
}
