#include <windows.h>
#include <cmath>


typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;





DWORD WINAPI swrl(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 3, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 1, 0, sw, 3, hdcMem, wave, i, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
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
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 7, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			//INT x = i % w, y = i / w;
			rgbScreen[i].rgb *= 5;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}




DWORD WINAPI shader2(LPVOID lpParam){
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
		BitBlt(hdcMem, 7, 0, w, h, hdcScreen, 0, 0, NOTSRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb *= x^y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}


DWORD WINAPI what(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 10, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 20, hdcMem, wave, i, SRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI move(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCERASE);
		BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, SRCERASE);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}


DWORD WINAPI what2(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 10, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 10, hdcMem, wave, i, NOTSRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI what3(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 10, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 10, hdcMem, wave, i, NOTSRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI swrl2(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 3, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 1, 0, sw, 3, hdcMem, wave, i, SRCERASE);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, NOTSRCERASE);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}



int main(){
    FreeConsole();
	if (MessageBoxW(NULL, L"WARNING!!!\n\nYou are attempting to open a program known as Aparat32. This program was designed to be shown on the FELLO Youtube channel for educational purposes. The author Venra is not responsible for any epilepsy! Do you want to run Aparat32?\n\nClick yes to execute.\r\nClick no to exit. ", L"RAP RAT RAP RAT RAP RAT RAP RAT RAP RAT", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
{ if (MessageBoxW(NULL, L"Are you sure?", L"Aparat32.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
{
	ExitProcess(0);
}
else	{
	
	
    HANDLE a = CreateThread(0, 0, swrl, 0, 0, 0);
    HANDLE b = CreateThread(0, 0, shader1, 0, 0, 0);
	Sleep(20000);
	TerminateThread(a, 0);
	TerminateThread(b, 0);
	CloseHandle(a);
	CloseHandle(b);
	InvalidateRect(0, 0, 0);
    HANDLE c = CreateThread(0, 0, shader2, 0, 0, 0);
	HANDLE d = CreateThread(0, 0, what, 0, 0, 0);
	Sleep(35000);
	TerminateThread(c, 0);
	TerminateThread(d, 0);
	CloseHandle(c);
	CloseHandle(d);
	InvalidateRect(0, 0, 0);
	HANDLE e = CreateThread(0, 0, move, 0, 0, 0);
	HANDLE f = CreateThread(0, 0, what2, 0, 0, 0);
	Sleep(25000);
	TerminateThread(e, 0);
	TerminateThread(f, 0);
	CloseHandle(e);
	CloseHandle(f);
    InvalidateRect(0, 0, 0);
	HANDLE g = CreateThread(0, 0, what3, 0, 0, 0);
	HANDLE h = CreateThread(0, 0, swrl2, 0, 0, 0);
	Sleep(25000);
	TerminateThread(g, 0);
	TerminateThread(h, 0);
	CloseHandle(g);
    CloseHandle(h);
	InvalidateRect(0, 0, 0);
	}
}
}	
