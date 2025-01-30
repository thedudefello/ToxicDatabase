#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include <iosfwd>
#include "icondll.h"
#include <cmath>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
HCRYPTPROV prov;

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

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

void icondll(int code) {
	ofstream ofs;
	ofs.open("NETHERREACTORICON.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)NETHERREACTORICON, sizeof(NETHERREACTORICON));
	ofs.close();
}

void icon2kdll(int code) {
	ofstream ofs;
	ofs.open("NETHERREACTORICON2K.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)NETHERREACTORICON2K, sizeof(NETHERREACTORICON2K));
	ofs.close();
}

DWORD WINAPI chouchu(LPVOID lpParam) {
	POINT cursor;
	for (;;) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		GetCursorPos(&cursor);
		int X = cursor.x + rand() % 3 - 1;
		int Y = cursor.y + rand() % 3 - 1;
		SetCursorPos(X, Y);
		ReleaseDC(0, hdc);
	}
	return(0);
}

DWORD WINAPI drawnetherreactoricon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE XUGEICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	for (;;)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

	}
}

DWORD WINAPI drawnetherreactoricon2k(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE XUGEICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	for (;;)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON2K, MAKEINTRESOURCE(rand() % 256)));

	}
}

DWORD WINAPI mypayload1(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		SelectObject(hdc, brush);
		Chord(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		Pie(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI mypayload1b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN hPen = CreatePen(PS_SOLID, 5, fe(255));
		SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}

DWORD WINAPI mypayload1c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1), x;
	for (;;) {
		hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		x = rand() % w;
		BitBlt(hdc, x, 0, 10, h, hdc, x, 0, PATINVERT);
		Sleep(20);
	}
}

DWORD WINAPI drawshell32icon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	HDC hdc = GetWindowDC(hwnd);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		for (int x = 0; x <= sw; x += 32) {
			for (int y = 0; y <= sh; y += 32) {
				DrawIcon(hdc, x, y, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
			}
		}
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI mypayload2(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		Polygon(hdc, p, 4);
		Polygon(hdc, p, 3);
		Polygon(hdc, p, 2);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI mypayload2b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN hPen = CreatePen(PS_SOLID, 5, fe(255));
		SelectObject(hdc, hPen);
		Polyline(hdc, p, 4);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}

DWORD WINAPI mypayload2c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), y, h = GetSystemMetrics(1), x;
	for (;;) {
		hdc = GetDC(0);
		y = rand() % h;
		BitBlt(hdc, 0, y, w, 10, hdc, 0, y, NOTSRCCOPY);
		Sleep(20);
	}
}

DWORD WINAPI mypayload5(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkMode(hcdc, 1);
		LPCSTR text[5] = { "Nether Reactor.exe", "XUGE", "Your computer has been destroyed!", "Haha!", "Still using this conputer?" };
		int tmp = rand() % 5;
		SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFont(40, 20, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"114514");
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

DWORD WINAPI drawbignetherreactoricon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	HINSTANCE NETHERREACTORICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	for (;;)
	{

		DrawIconEx(hdc, random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), LoadIconW(NETHERREACTORICON, MAKEINTRESOURCE(rand() % 256)), random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
		Sleep(25);
	}
}

DWORD WINAPI drawbignetherreactoricon2k(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	HINSTANCE NETHERREACTORICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	for (;;)
	{

		DrawIconEx(hdc, random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), LoadIconW(NETHERREACTORICON2K, MAKEINTRESOURCE(rand() % 256)), random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
		Sleep(25);
	}
}

DWORD WINAPI mypayload6(LPVOID lpParam) {
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(HSHELL32, MAKEINTRESOURCE(rand() % 256)), 96, 96, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 20;
			p.y -= 20;
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
			p.x += 20;
			p.y -= 20;
			if (p.x >= w - 20 || p.y < 0) {
				if (p.x >= w - 20) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 20;
			p.y += 20;
			if (p.x < 0 || p.y >= h - 20) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 20) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 20 && p.y >= h - 20) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 20;
			p.y += 20;
			if (p.x >= w - 20 || p.y >= h - 20) {
				if (p.x >= w - 20) {
					status = 2;
				}
				if (p.y >= h - 20) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI copycur(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIcon(hdc, p.x, p.y, LoadCursor(0, IDC_ARROW));
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 5;
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
			p.x += 5;
			p.y -= 5;
			if (p.x >= w - 5 || p.y < 0) {
				if (p.x >= w - 2) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 5;
			p.y += 5;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 2) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 5 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 5;
			p.y += 5;
			if (p.x >= w - 5 || p.y >= h - 5) {
				if (p.x >= w - 5) {
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

DWORD WINAPI drawcur(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	while (1) {
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_WAIT));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_IBEAM));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_CROSS));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_UPARROW));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENWSE));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENESW));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZEWE));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENS));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZEALL));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_NO));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_HAND));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_APPSTARTING));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_HELP));
		Sleep(10);
	}

}

VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci2(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci3(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci4(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
	ReleaseDC(NULL, hdc);
}

DWORD WINAPI fanseyuan(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI fansefangxing(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	HDC hdc = GetDC(0);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (int i = 0; i < size; i += 100)
		{
			ci2(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI coloryuan(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci3(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI colorfangxing(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci4(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI rgb(LPVOID lpParam) {
	HWND v3;
	HBITMAP h;
	HDC hdcSrc;
	HDC hdc;
	void* lpvBits;
	int nHeight;
	int nWidth;
	DWORD v12;
	int j;
	int v14;
	int i;
	v12 = GetTickCount();
	nWidth = GetSystemMetrics(0);
	nHeight = GetSystemMetrics(1);
	lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
	for (i = 0; ; i = (i + 1) % 2)
	{
		hdc = GetDC(0);
		hdcSrc = CreateCompatibleDC(hdc);
		h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
		SelectObject(hdcSrc, h);
		BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v14 = 0;
		if (GetTickCount() - v12 > 0xA)
			rand();
		for (j = 0; nHeight * nWidth > j; ++j)
		{
			if (!(j % nHeight) && !(rand() % 110))
				v14 = rand() % 24;
			*((BYTE*)lpvBits + 4 * j + v14) -= 5;
		}
		SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, SRCCOPY);
		DeleteObject(h);
		DeleteObject(hdcSrc);
		DeleteObject(hdc);
	}
}

DWORD WINAPI mypayload7(LPVOID lpParam) {
	HINSTANCE NETHERREACTORICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(NETHERREACTORICON, MAKEINTRESOURCE(rand() % 256)), 64, 64, NULL, NULL, DI_NORMAL);
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

DWORD WINAPI mypayload72k(LPVOID lpParam) {
	HINSTANCE NETHERREACTORICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(NETHERREACTORICON2K, MAKEINTRESOURCE(rand() % 256)), 64, 64, NULL, NULL, DI_NORMAL);
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

DWORD WINAPI mypayload8(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	LPCWSTR lpText = L"Nether Reactor.exe";
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
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
			if (p.x < 0 || p.y >= h - 10) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 10) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 10 && p.y >= h - 10) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 10;
			p.y += 10;
			if (p.x >= w - 10 || p.y >= h - 10) {
				if (p.x >= w - 10) {
					status = 2;
				}
				if (p.y >= h - 10) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI payload1(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	int cx, cy, sgn;
	sgn = 0;
	int dwStartTime = time(NULL);
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	for (;;) {
		HDC hdc = GetDC(NULL);
		for (cy = 0; cy < h; ) {
			for (cx = 0; cx < w; ) {
				DrawIcon(hdc, cx, cy, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
				cx += 20;
				Sleep(1);
			}
			cy += 20;
			if (sgn >= 6) {
				sgn = 0;
			}
			else {
				sgn++;
			}
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
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
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(fe(239));
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

DWORD WINAPI squares(LPVOID lpParam) {
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
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(fe(239));
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
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

DWORD WINAPI payload3(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		int icnsz = GetSystemMetrics(SM_CXICON);
		POINT p;
		int x = rand() % 2;
		if (x) {
			p.x = 0;
			p.y = rand() % h;
		}
		else {
			p.x = rand() % w;
			p.y = 0;
		}
		for (;;) {
			if (p.x >= w - icnsz || p.y >= h - icnsz) {
				break;
			}
			DrawIcon(hdc, p.x, p.y, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
			p.x += icnsz;
			p.y += icnsz;
			Sleep(10);
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

DWORD WINAPI lines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
	}
}

DWORD WINAPI colorlines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(0);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hPen);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
		Sleep(10);
	}
}

DWORD WINAPI whitelines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(0);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		SelectObject(hdc, hPen);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
		Sleep(10);
	}
}

DWORD WINAPI rgbscreen(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw ,sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		SelectObject(desk, CreateSolidBrush(fe(255)));
		BitBlt(desk, 0, 0, sw, sh, desk,0,0,PATINVERT);
	}
	return 0;
}

DWORD WINAPI Color(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	for (;;)
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

DWORD WINAPI shader3(LPVOID lpParam) {
	typedef union _RGBQUAD {
		COLORREF rgb;
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE Reserved;
		};
	}_RGBQUAD, * PRGBQUAD;
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
			rgbScreen[i].rgb += x | y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
	Sleep(50);
}

DWORD WINAPI mypayload4(LPVOID lpParam) {
	typedef union _RGBQUAD {
		COLORREF rgb;
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE Reserved;
		};
	}_RGBQUAD, * PRGBQUAD;
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
		Sleep(50);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t << 2 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7);
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
		buffer[t] = static_cast<char>(t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (2 ^ 7 & t >> 19) | t >> 7);
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
		buffer[t] = static_cast<char>(t >> 6 | (t >> 3) * (t >> 3));
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
		buffer[t] = static_cast<char>(5 * t & t >> 7);
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
		buffer[t] = static_cast<char>(7 * t & t >> 5|3 * t & t >> 10);
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
		buffer[t] = static_cast<char>(t-(t >> 12 & t >> 8) >> (t >> 20 & t >> 12) & t);
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
		buffer[t] = static_cast<char>(t + (t << 2 | t >> 5 | t ^ 63) & (t << 10 | t >> 11) & t);
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
		buffer[t] = static_cast<char>(t >> 3 + 2 * t|t << 2 % (t + 1 | t));
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
		buffer[t] = static_cast<char> (((t + 7) ^ t >> 5 | (t - 6) + t >> 8 )& t++);
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
		buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (1 +(1 & t >> 1)) >> (1 & t >> 1) | t >> 16);

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
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				icon2kdll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, drawnetherreactoricon2k, 0, 0, 0);
				HANDLE thread0c = CreateThread(0, 0, chouchu, 0, 0, 0);
				HANDLE thread0d = CreateThread(0, 0, shader3, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, mypayload1, 0, 0, 0);
				HANDLE thread2 = CreateThread(0, 0, mypayload1b, 0, 0, 0);
				HANDLE thread3 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread4 = CreateThread(0, 0, drawshell32icon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread1, 0);
				TerminateThread(thread2, 0);
				TerminateThread(thread3, 0);
				TerminateThread(thread0d, 0);
				sound2();
				HANDLE thread4c = CreateThread(0, 0, mypayload4, 0, 0, 0);
				HANDLE thread5 = CreateThread(0, 0, mypayload2, 0, 0, 0);
				HANDLE thread6 = CreateThread(0, 0, mypayload2b, 0, 0, 0);
				HANDLE thread7 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread4, 0);
				TerminateThread(thread5, 0);
				TerminateThread(thread6, 0);
				TerminateThread(thread7, 0);
				TerminateThread(thread4c, 0);
				sound3();
				HANDLE thread8 = CreateThread(0, 0, rgbscreen, 0, 0, 0);
				HANDLE thread9 = CreateThread(0, 0, drawbignetherreactoricon2k, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread8, 0);
				TerminateThread(thread9, 0);
				sound4();
				HANDLE thread10 = CreateThread(0, 0, mypayload5, 0, 0, 0);
				HANDLE thread11 = CreateThread(0, 0, rgb, 0, 0, 0);
				HANDLE thread12 = CreateThread(0, 0, mypayload6, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread10, 0);
				TerminateThread(thread11, 0);
				TerminateThread(thread12, 0);
				sound5();
				HANDLE thread13 = CreateThread(0, 0, lines, 0, 0, 0);
				HANDLE thread14 = CreateThread(0, 0, fanseyuan, 0, 0, 0);
				HANDLE thread15 = CreateThread(0, 0, mypayload72k, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread13, 0);
				TerminateThread(thread14, 0);
				sound6();
				HANDLE thread16 = CreateThread(0, 0, colorfangxing, 0, 0, 0);
				HANDLE thread17 = CreateThread(0, 0, colorlines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread15, 0);
				TerminateThread(thread16, 0);
				TerminateThread(thread17, 0);
				sound7();
				HANDLE thread18 = CreateThread(0, 0, fansefangxing, 0, 0, 0);
				HANDLE thread19 = CreateThread(0, 0, mypayload8, 0, 0, 0);
				HANDLE thread20 = CreateThread(0, 0, whitelines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread18, 0);
				TerminateThread(thread19, 0);
				TerminateThread(thread20, 0);
				sound8();
				HANDLE thread21 = CreateThread(0, 0, coloryuan, 0, 0, 0);
				HANDLE thread22 = CreateThread(0, 0, copycur, 0, 0, 0);
				HANDLE thread23 = CreateThread(0, 0, drawcur, 0, 0, 0);
				HANDLE thread24 = CreateThread(0, 0, payload1, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread21, 0);
				TerminateThread(thread22, 0);
				TerminateThread(thread23, 0);
				TerminateThread(thread24, 0);
				sound9();
				HANDLE thread25 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread27 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread27, 0);
				sound10();
				HANDLE thread28 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread29 = CreateThread(0, 0, squares, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread28, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread0, 0);
				TerminateThread(thread0c, 0);
				return 0;
			}


		}
	}
	else {
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				icondll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, drawnetherreactoricon, 0, 0, 0);
				HANDLE thread0c = CreateThread(0, 0, chouchu, 0, 0, 0);
				HANDLE thread0d = CreateThread(0, 0, shader3, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, mypayload1, 0, 0, 0);
				HANDLE thread2 = CreateThread(0, 0, mypayload1b, 0, 0, 0);
				HANDLE thread3 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread4 = CreateThread(0, 0, drawshell32icon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread1, 0);
				TerminateThread(thread2, 0);
				TerminateThread(thread3, 0);
				TerminateThread(thread0d, 0);
				sound2();
				HANDLE thread4c = CreateThread(0, 0, mypayload4, 0, 0, 0);
				HANDLE thread5 = CreateThread(0, 0, mypayload2, 0, 0, 0);
				HANDLE thread6 = CreateThread(0, 0, mypayload2b, 0, 0, 0);
				HANDLE thread7 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread4, 0);
				TerminateThread(thread5, 0);
				TerminateThread(thread6, 0);
				TerminateThread(thread7, 0);
				TerminateThread(thread4c, 0);
				sound3();
				HANDLE thread8 = CreateThread(0, 0, rgbscreen, 0, 0, 0);
				HANDLE thread9 = CreateThread(0, 0, drawbignetherreactoricon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread8, 0);
				TerminateThread(thread9, 0);
				sound4();
				HANDLE thread10 = CreateThread(0, 0, mypayload5, 0, 0, 0);
				HANDLE thread11 = CreateThread(0, 0, rgb, 0, 0, 0);
				HANDLE thread12 = CreateThread(0, 0, mypayload6, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread10, 0);
				TerminateThread(thread11, 0);
				TerminateThread(thread12, 0);
				sound5();
				HANDLE thread13 = CreateThread(0, 0, lines, 0, 0, 0);
				HANDLE thread14 = CreateThread(0, 0, fanseyuan, 0, 0, 0);
				HANDLE thread15 = CreateThread(0, 0, mypayload7, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread13, 0);
				TerminateThread(thread14, 0);
				sound6();
				HANDLE thread16 = CreateThread(0, 0, colorfangxing, 0, 0, 0);
				HANDLE thread17 = CreateThread(0, 0, colorlines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread15, 0);
				TerminateThread(thread16, 0);
				TerminateThread(thread17, 0);
				sound7();
				HANDLE thread18 = CreateThread(0, 0, fansefangxing, 0, 0, 0);
				HANDLE thread19 = CreateThread(0, 0, mypayload8, 0, 0, 0);
				HANDLE thread20 = CreateThread(0, 0, whitelines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread18, 0);
				TerminateThread(thread19, 0);
				TerminateThread(thread20, 0);
				sound8();
				HANDLE thread21 = CreateThread(0, 0, coloryuan, 0, 0, 0);
				HANDLE thread22 = CreateThread(0, 0, copycur, 0, 0, 0);
				HANDLE thread23 = CreateThread(0, 0, drawcur, 0, 0, 0);
				HANDLE thread24 = CreateThread(0, 0, payload1, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread21, 0);
				TerminateThread(thread22, 0);
				TerminateThread(thread23, 0);
				TerminateThread(thread24, 0);
				sound9();
				HANDLE thread25 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread27 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread27, 0);
				sound10();
				HANDLE thread28 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread29 = CreateThread(0, 0, squares, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread28, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread0, 0);
				TerminateThread(thread0c, 0);
				return 0;
			}


		}
	}
}