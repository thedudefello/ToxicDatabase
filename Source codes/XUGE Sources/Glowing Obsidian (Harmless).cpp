#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include <iosfwd>
#include <cmath>
#include "icondll.h"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

int red, green, blue;
bool ifcolorblue = false, ifblue = false;

COLORREF fe(int length) {
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

void icondll(int code) {
	ofstream ofs;
	ofs.open("GLOWINGOBSIDIANICON.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)GLOWINGOBSIDIANICON, sizeof(GLOWINGOBSIDIANICON));
	ofs.close();
}

void icon2kdll(int code) {
	ofstream ofs;
	ofs.open("GLOWINGOBSIDIANICON2K.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)GLOWINGOBSIDIANICON2K, sizeof(GLOWINGOBSIDIANICON2K));
	ofs.close();
}

DWORD WINAPI Tunnel(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 20, 20, w - 40, h - 40, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI Fangda(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, -20, -20, w + 40, h + 40, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI lakuan(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, -20, 0, w + 40, h, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(25);
	}
	return 0;
}

DWORD WINAPI lagao(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 0, -20, w, h + 40, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(25);
	}
	return 0;
}

DWORD WINAPI lazhai(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 20, 0, w - 40, h, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(25);
	}
	return 0;
}

DWORD WINAPI ladi(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		StretchBlt(hdc, 0, 20, w, h - 40, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(25);
	}
	return 0;
}

DWORD WINAPI mousedrawicon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE hshell32 = LoadLibrary(_T("Shell32.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	for (;;)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x, point.y, LoadIcon(0, IDI_ERROR));

	}
}

DWORD WINAPI drawglowingobsidianicon(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	HINSTANCE GLOWINGOBSIDIANICON = LoadLibrary(_T("GLOWINGOBSIDIANICON.dll"));
	HDC hdc = GetWindowDC(hwnd);
	for (;;) {
		for (int x = 0; x <= w; x += 64) {
			for (int y = 0; y <= h; y += 64) {
				DrawIconEx(hdc, x, y, LoadIcon(GLOWINGOBSIDIANICON, MAKEINTRESOURCE(1)), 64, 64, NULL, NULL, DI_NORMAL);
			}
		}
	}
}

DWORD WINAPI drawglowingobsidianicon2k(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	HINSTANCE GLOWINGOBSIDIANICON2K = LoadLibrary(_T("GLOWINGOBSIDIANICON2K.dll"));
	HDC hdc = GetWindowDC(hwnd);
	for (;;) {
		for (int x = 0; x <= w; x += 64) {
			for (int y = 0; y <= h; y += 64) {
				DrawIconEx(hdc, x, y, LoadIcon(GLOWINGOBSIDIANICON2K, MAKEINTRESOURCE(1)), 64, 64, NULL, NULL, DI_NORMAL);
			}
		}
	}
}

DWORD WINAPI mypayload4(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = sw;
	bmi.bmiHeader.biHeight = sh;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, sw, sh, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < sw * sh; i++) {
			INT x = sw - i, y = i % sw;
			rgbScreen[i].rgb += x + y;
		}
		BitBlt(hdcScreen, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
		Sleep(25);
	}
}

DWORD WINAPI mypayload7(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		LPCWSTR lpText = L"Glowing Obsidian.exe";
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, p.x, p.y, lpText, wcslen(lpText));
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 25;
			p.y -= 5;
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
			p.x += 25;
			p.y -= 5;
			if (p.x >= w - 25 || p.y < 0) {
				if (p.x >= w - 25) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 25;
			p.y += 5;
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
			p.x += 25;
			p.y += 5;
			if (p.x >= w - 25 || p.y >= h - 5) {
				if (p.x >= w - 25) {
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

DWORD WINAPI shader3(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x ^ y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI Color(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1)
	{
		desk = GetDC(0);
		SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI ColorInvert(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

		ReleaseDC(0, hdc);
		DeleteObject(hdc);

		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI PAYLOAD08(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		POINT pos[3];
		pos[0].x = rand() % w, pos[0].y = rand() % h;
		pos[1].x = rand() % w, pos[1].y = rand() % h;
		pos[2].x = rand() % w, pos[2].y = rand() % h;
		PlgBlt(hcdc, pos, hcdc, 0, 0, w, h, 0, 0, 0);
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	return 0;
}

DWORD WINAPI drawsquare(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	for (;;) {
		for (int x = 0; x <= w; x += 64) {
			for (int y = 0; y <= h; y += 64) {
				HBRUSH brush = CreateSolidBrush(fe(255));
				SelectObject(hdc, brush);
				Rectangle(hdc, x, y, 64 + x, 64 + y);
			}
		}
		Sleep(50);
	}
}

DWORD WINAPI mypayload6(LPVOID lpParam) {
	HINSTANCE GLOWINGOBSIDIANICON = LoadLibrary(_T("GLOWINGOBSIDIANICON.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(GLOWINGOBSIDIANICON, MAKEINTRESOURCE(1)), 64, 64, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 64;
			p.y -= 64;
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
			p.x += 64;
			p.y -= 64;
			if (p.x >= w - 64 || p.y < 0) {
				if (p.x >= w - 64) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 64;
			p.y += 64;
			if (p.x < 0 || p.y >= h - 64) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 64) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 64 && p.y >= h - 64) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 64;
			p.y += 64;
			if (p.x >= w - 64 || p.y >= h - 64) {
				if (p.x >= w - 64) {
					status = 2;
				}
				if (p.y >= h - 64) {
					status = 1;
				}
			}
			break;
		}
		Sleep(25);
	}
}

DWORD WINAPI mypayload62k(LPVOID lpParam) {
	HINSTANCE GLOWINGOBSIDIANICON2K = LoadLibrary(_T("GLOWINGOBSIDIANICON2K.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(GLOWINGOBSIDIANICON2K, MAKEINTRESOURCE(1)), 64, 64, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 8;
			p.y -= 8;
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
			p.x += 8;
			p.y -= 8;
			if (p.x >= w - 8 || p.y < 0) {
				if (p.x >= w - 8) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 8;
			p.y += 8;
			if (p.x < 0 || p.y >= h - 8) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 8) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 8 && p.y >= h - 8) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 8;
			p.y += 8;
			if (p.x >= w - 8 || p.y >= h - 8) {
				if (p.x >= w - 8) {
					status = 2;
				}
				if (p.y >= h - 8) {
					status = 1;
				}
			}
			break;
		}
		Sleep(25);
	}
}

DWORD WINAPI colorbezier(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
		Sleep(25);
	}
}

DWORD WINAPI shader4(LPVOID lpParam) {
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
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader41(LPVOID lpParam) {
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
			rgbScreen[i].rgb = (x & y) * RGB(GetRValue(fe(255)), GetGValue(fe(255)), GetBValue(fe(255)));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI doudong(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		StretchBlt(hdc, rand() % 3 - 1, rand() % 3 - 1, sw + rand() % 3 - 1, sh + rand() % 3 - 1, hdc, 0, 0, sw, sh, SRCPAINT);
	}
	return(0);
}

DWORD WINAPI train(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	for (;;) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -15, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 15, 0, w, h, hdc, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(25);
	}
}

DWORD WINAPI manysquares(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	HINSTANCE GLOWINGOBSIDIANICON = LoadLibrary(_T("GLOWINGOBSIDIANICON.dll"));
	for (;;) {
		int x1 = rand() % sw;
		int y1 = rand() % sh;
		HBRUSH brush1 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		Rectangle(hdc, x1, y1, 100 + x1, 100 + y1);
		Sleep(50);
		int x2 = rand() % sw;
		int y2 = rand() % sh;
		StretchBlt(hdc, x2, y2, 100, 100, hdc, x2, y2, 100, 100, NOTSRCCOPY);
		Sleep(50);
		int x3 = rand() % sw;
		int y3 = rand() % sh;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, x3, y3, 100, 100, hdc, x3, y3, 100, 100, PATINVERT);
		Sleep(50);
		int x4 = rand() % sw;
		int y4 = rand() % sh;
		DrawIconEx(hdc, x4, y4, LoadIconW(GLOWINGOBSIDIANICON, MAKEINTRESOURCE(1)), 100, 100, NULL, NULL, DI_NORMAL);
		Sleep(50);
	}
}

DWORD WINAPI manysquares2k(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	HINSTANCE GLOWINGOBSIDIANICON2K = LoadLibrary(_T("GLOWINGOBSIDIANICON2K.dll"));
	for (;;) {
		int x1 = rand() % sw;
		int y1 = rand() % sh;
		HBRUSH brush1 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		Rectangle(hdc, x1, y1, 100 + x1, 100 + y1);
		Sleep(50);
		int x2 = rand() % sw;
		int y2 = rand() % sh;
		StretchBlt(hdc, x2, y2, 100, 100, hdc, x2, y2, 100, 100, NOTSRCCOPY);
		Sleep(50);
		int x3 = rand() % sw;
		int y3 = rand() % sh;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, x3, y3, 100, 100, hdc, x3, y3, 100, 100, PATINVERT);
		Sleep(50);
		int x4 = rand() % sw;
		int y4 = rand() % sh;
		DrawIconEx(hdc, x4, y4, LoadIconW(GLOWINGOBSIDIANICON2K, MAKEINTRESOURCE(1)), 100, 100, NULL, NULL, DI_NORMAL);
		Sleep(50);
	}
}

DWORD WINAPI manycircles(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		int x1 = rand() % sw;
		int y1 = rand() % sh;
		HBRUSH brush1 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		Ellipse(hdc, x1, y1, 100 + x1, 100 + y1);
		Sleep(50);
		int x2 = rand() % sw;
		int y2 = rand() % sh;
		HRGN hrgn1 = CreateEllipticRgn(x2, y2, x2 + 100, y2 + 100);
		SelectClipRgn(hdc, hrgn1);
		StretchBlt(hdc, x2, y2, 100, 100, hdc, x2, y2, 100, 100, NOTSRCCOPY);
		Sleep(50);
		int x3 = rand() % sw;
		int y3 = rand() % sh;
		HRGN hrgn2 = CreateEllipticRgn(x3, y3, x3 + 100, y3 + 100);
		SelectClipRgn(hdc, hrgn2);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, x3, y3, 100, 100, hdc, x3, y3, 100, 100, PATINVERT);
		Sleep(50);
	}
}

DWORD WINAPI shader0(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x * y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI mypayload1c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	int w;
	for (;;) {
		hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		w = rand() % sw;
		BitBlt(hdc, w, 0, 10, sh, hdc, w, 0, PATINVERT);
		Sleep(25);
	}
}

DWORD WINAPI mypayload2c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	int h;
	for (;;) {
		hdc = GetDC(0);
		h = rand() % sh;
		BitBlt(hdc, 0, h, sw, 10, hdc, 0, h, NOTSRCCOPY);
		Sleep(25);
	}
}

DWORD WINAPI squares2(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	for (;;) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, top_x, top_y, 100, 100, hdc, top_x, top_y, 100, 100, PATINVERT);
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
		Sleep(20);
		ReleaseDC(0, hdc);
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
	for (;;) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HRGN hrgn1 = CreateEllipticRgn(top_x, top_y, top_x + 100, top_y + 100);
		SelectClipRgn(hdc, hrgn1);
		StretchBlt(hdc, top_x, top_y, 100, 100, hdc, top_x, top_y, 100, 100, NOTSRCCOPY);
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
		Sleep(20);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 5 | t >> 8)) >> (t << 4);
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
		buffer[t] = static_cast<char>((t * (5 + ((t & t >> 8) | (t ^ t >> 13) | t >> 16) % 16)) * t << 1);
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
		buffer[t] = static_cast<char>(t >> 6 * (t >> 2) | (t >> 4));
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
		buffer[t] = static_cast<char>((t ^ t >> 10) * t >> 8 | t >> 16);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

//((t*(5+((t&t>>8)|(t^t>>13)|t>>16)%16))*t<<1)

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((t >> 12 & t >> 8) | (t >> 20 & t >> 12)) * (t << 3));
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
		buffer[t] = static_cast<char>(5 * t & t >> 7 | (3 * t & t >> 10)- t);
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
		buffer[t] = static_cast<char>(9 * t & t >> 4 | 5 * t & t >> 7) - 20;
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
		buffer[t] = static_cast<char>(t * (t >> 5 | t >> 8 | t >> 80 ^ t) + 64) >> (t >> 16);
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
		buffer[t] = static_cast<char>(t * (t >> 12 | t >> 8));
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
		buffer[t] = static_cast<char>(2 * t * (t & 16384 ? 6 : 5) * (4 - (3 & t >> 8)) >> (3 & -t >> (t & 4096 ? 2 : 15)) | t >> (t & 8192 ? t & 4096 ? 4 : 5 : 3));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
	OSVERSIONINFOEXW osvi = { 0 };
	DWORDLONG dwlConditionMask = 0;
	ZeroMemory(&osvi, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	osvi.dwMajorVersion = 5;
	osvi.dwMinorVersion = 0;
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_EQUAL);
	if (VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask))
	{
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Glowing Obsidian.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Glowing Obsidian.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				icon2kdll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, mousedrawicon, 0, 0, 0);
				HANDLE thread0b = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread1, 0);
				HANDLE thread2 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread2, 0);
				HANDLE thread3 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread3, 0);
				HANDLE thread4 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread4, 0);
				HANDLE thread5 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread5, 0);
				HANDLE thread6 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread6, 0);
				HANDLE thread7 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread7, 0);
				HANDLE thread8 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread8, 0);
				HANDLE thread9 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread9, 0);
				HANDLE thread10 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread10, 0);
				HANDLE thread11 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread11, 0);
				HANDLE thread12 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread12, 0);
				HANDLE thread13 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread13, 0);
				HANDLE thread14 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread14, 0);
				HANDLE thread15 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread15, 0);
				HANDLE thread16 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread16, 0);
				HANDLE thread17 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread17, 0);
				HANDLE thread18 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread18, 0);
				HANDLE thread19 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread19, 0);
				HANDLE thread20 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread20, 0);
				HANDLE thread21 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread21, 0);
				HANDLE thread22 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread22, 0);
				HANDLE thread23 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread23, 0);
				HANDLE thread24 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread0b, 0);
				TerminateThread(thread24, 0);
				sound2();
				HANDLE thread25 = CreateThread(0, 0, drawglowingobsidianicon2k, 0, 0, 0);
				HANDLE thread26 = CreateThread(0, 0, shader4, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread26, 0);
				sound3();
				HANDLE thread27 = CreateThread(0, 0, mypayload7, 0, 0, 0);
				HANDLE thread28 = CreateThread(0, 0, shader3, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread27, 0);
				TerminateThread(thread28, 0);
				sound4();
				HANDLE thread29 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread30 = CreateThread(0, 0, PAYLOAD08, 0, 0, 0);
				HANDLE thread31 = CreateThread(0, 0, colorbezier, 0, 0, 0);
				HANDLE thread32 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread32, 0);
				HANDLE thread33 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread33, 0);
				HANDLE thread34 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread34, 0);
				HANDLE thread35 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread35, 0);
				HANDLE thread36 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread36, 0);
				HANDLE thread37 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread37, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread30, 0);
				TerminateThread(thread31, 0);
				sound5();
				HANDLE thread38 = CreateThread(0, 0, drawsquare, 0, 0, 0);
				HANDLE thread39 = CreateThread(0, 0, mypayload62k, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread38, 0);
				TerminateThread(thread39, 0);
				sound6();
				HANDLE thread40 = CreateThread(0, 0, manysquares2k, 0, 0, 0);
				HANDLE thread41 = CreateThread(0, 0, train, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread40, 0);
				TerminateThread(thread41, 0);
				sound7();
				HANDLE thread42 = CreateThread(0, 0, manycircles, 0, 0, 0);
				HANDLE thread43 = CreateThread(0, 0, doudong, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread42, 0);
				TerminateThread(thread43, 0);
				sound8();
				HANDLE thread44 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				HANDLE thread45 = CreateThread(0, 0, squares2, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread44, 0);
				TerminateThread(thread45, 0);
				sound9();
				HANDLE thread46 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread47 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread46, 0);
				TerminateThread(thread47, 0);
				sound10();
				HANDLE thread48 = CreateThread(0, 0, shader41, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread48, 0);
				TerminateThread(thread0, 0);
				return 0;
			}


		}
	}
	else {
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Glowing Obsidian.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Glowing Obsidian.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				icondll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, mousedrawicon, 0, 0, 0);
				HANDLE thread0b = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread1, 0);
				HANDLE thread2 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread2, 0);
				HANDLE thread3 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread3, 0);
				HANDLE thread4 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread4, 0);
				HANDLE thread5 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread5, 0);
				HANDLE thread6 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread6, 0);
				HANDLE thread7 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread7, 0);
				HANDLE thread8 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread8, 0);
				HANDLE thread9 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread9, 0);
				HANDLE thread10 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread10, 0);
				HANDLE thread11 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread11, 0);
				HANDLE thread12 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread12, 0);
				HANDLE thread13 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread13, 0);
				HANDLE thread14 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread14, 0);
				HANDLE thread15 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread15, 0);
				HANDLE thread16 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread16, 0);
				HANDLE thread17 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread17, 0);
				HANDLE thread18 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread18, 0);
				HANDLE thread19 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread19, 0);
				HANDLE thread20 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread20, 0);
				HANDLE thread21 = CreateThread(0, 0, lazhai, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread21, 0);
				HANDLE thread22 = CreateThread(0, 0, ladi, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread22, 0);
				HANDLE thread23 = CreateThread(0, 0, lakuan, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread23, 0);
				HANDLE thread24 = CreateThread(0, 0, lagao, 0, 0, 0);
				Sleep(1250);
				TerminateThread(thread0b, 0);
				TerminateThread(thread24, 0);
				sound2();
				HANDLE thread25 = CreateThread(0, 0, drawglowingobsidianicon, 0, 0, 0);
				HANDLE thread26 = CreateThread(0, 0, shader4, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread26, 0);
				sound3();
				HANDLE thread27 = CreateThread(0, 0, mypayload7, 0, 0, 0);
				HANDLE thread28 = CreateThread(0, 0, shader3, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread27, 0);
				TerminateThread(thread28, 0);
				sound4();
				HANDLE thread29 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread30 = CreateThread(0, 0, PAYLOAD08, 0, 0, 0);
				HANDLE thread31 = CreateThread(0, 0, colorbezier, 0, 0, 0);
				HANDLE thread32 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread32, 0);
				HANDLE thread33 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread33, 0);
				HANDLE thread34 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread34, 0);
				HANDLE thread35 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread35, 0);
				HANDLE thread36 = CreateThread(0, 0, Tunnel, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread36, 0);
				HANDLE thread37 = CreateThread(0, 0, Fangda, 0, 0, 0);
				Sleep(5000);
				TerminateThread(thread37, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread30, 0);
				TerminateThread(thread31, 0);
				sound5();
				HANDLE thread38 = CreateThread(0, 0, drawsquare, 0, 0, 0);
				HANDLE thread39 = CreateThread(0, 0, mypayload6, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread38, 0);
				TerminateThread(thread39, 0);
				sound6();
				HANDLE thread40 = CreateThread(0, 0, manysquares, 0, 0, 0);
				HANDLE thread41 = CreateThread(0, 0, train, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread40, 0);
				TerminateThread(thread41, 0);
				sound7();
				HANDLE thread42 = CreateThread(0, 0, manycircles, 0, 0, 0);
				HANDLE thread43 = CreateThread(0, 0, doudong, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread42, 0);
				TerminateThread(thread43, 0);
				sound8();
				HANDLE thread44 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				HANDLE thread45 = CreateThread(0, 0, squares2, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread44, 0);
				TerminateThread(thread45, 0);
				sound9();
				HANDLE thread46 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread47 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread46, 0);
				TerminateThread(thread47, 0);
				sound10();
				HANDLE thread48 = CreateThread(0, 0, shader41, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread48, 0);
				TerminateThread(thread0, 0);
				return 0;
			}


		}
	}
}