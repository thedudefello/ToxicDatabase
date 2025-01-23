#include <windows.h>

int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
int signx = 1, signy = 1, signxcopy = 1, signycopy = 1;
int increment = 10;
int x = 10, y = 10;
#define MERGEERASE 0x94ffbful

VOID WINAPI RotatePoints(LPPOINT lpPoint, float Theta, int SizeOfArray) {
	for (int t = 0; t < SizeOfArray; t++) {
		double x = lpPoint[t].x,
		y = lpPoint[t].y;
		
		lpPoint[t].x = static_cast<int>(x * cos(Theta) - y * sin(Theta));
		lpPoint[t].y = static_cast<int>(x * sin(Theta) + y * cos(Theta));
	}
}

COLORREF HSV(int crLength) { // I rewrote this from raduminecraft
    double H = fmod(crLength, 360);
    double S = 1.0;
    double V = 0.5;
    double C = (1.0-fabs(2.0*V-1.0)) * S;
    double X = C*(1.0-fabs(fmod(H/60.0, 2.0) - 1.0));
    double M = V - C / 2.0;
    double R, G, B;
    if (H < 60) {
        R = C; G = X, B = 0;
    }
    else if (H < 120) {
        R = X; G = C; B = 0;
    }
    else if (H < 180) {
        R = 0; G = C; B = X;
    }
    else if (H < 240) {
        R = 0; G = X; B = C;
    }
    else if (H < 300) {
        R = X; G = 0; B = C;
    }
    else {
        R = C; G = 0; B = X;
    }
    
    int crRed = static_cast<INT>((R + M) * 255);
    int crGreen = static_cast<INT>((G + M) * 255);
    int crBlue = static_cast<INT>((B + M) * 255);
    return RGB(crRed, crGreen, crBlue);
}

namespace GDI {
	/* DWORD WINAPI TextOuts(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HFONT hfnt = CreateFontW(75, 0, rand() % 360 - 180, 0, FW_BOLD, false, false, false, ANSI_CHARSET, 0, 0, 0, 0, L"Trebuchet MS");
			LPCWSTR lpTexts[] = {
				L"Lag.", L"Never using HALFTONE again!",
				L"I lost the project.", L"Be grateful...",
				L":("
			};
			LPCWSTR index = lpTexts[rand() % _countof(lpTexts)];
			SetBkColor(hdc, RGB(rand() % 100, rand() % 100, rand() % 100));
			SetTextColor(hdc, RGB(rand() % 109, rand() % 109, rand() % 109));
			SelectObject(hdc, hfnt);
			TextOutW(hdc, rand() % w, rand() % h, index, wcslen(index));
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	} Didn't end up using this in the final release. */ 
	
	DWORD WINAPI AnimGradientTriangle(LPVOID pvoid)
		{ // you must link the msimg32 library (or must you)
	//    HDC hdc = GetDC(0);
	    while (1) {
	    	HDC hdc = GetDC(0);
	        TRIVERTEX vtx[3];
	        x += increment * signx;
	        y += increment * signy;
	        vtx[0].x = x; vtx[0].y = y;
	        vtx[1].x = x+100; vtx[1].y = y;
	        vtx[2].x = x; vtx[2].y = y+100;
	        vtx[0].Red = 0; vtx[0].Green = 0; vtx[0].Blue = 0xff00; vtx[0].Alpha = 0xff00;
	        vtx[1].Red = 0; vtx[1].Green = 0xff00; vtx[1].Blue = 0; vtx[1].Alpha = 0xff00;
	        vtx[2].Red = 0; vtx[2].Green = 0; vtx[2].Blue = 0xff00; vtx[2].Alpha = 0xff00;
	        GRADIENT_TRIANGLE triangle = { 0, 1, 2 };
	        GradientFill(hdc, vtx, 4, &triangle, 1, GRADIENT_FILL_TRIANGLE);
	        if (y > h) signy = -1;
	        if (x > w) signx = -1;
			if (y == 0) signy = 1;
			if (x == 0) signx = 1; 
	        ReleaseDC(0, hdc);
	        Sleep(10);
	    }
	}
	
	DWORD WINAPI HalftonePixelate(LPVOID pvoid)
	{
	    while (true) {
	        HDC hdc = GetDC(0),
	        mdc = CreateCompatibleDC(hdc);
	        HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
	        SelectObject(mdc, hbit);
	        SetStretchBltMode(hdc, STRETCH_HALFTONE); SetStretchBltMode(mdc, STRETCH_HALFTONE);
	        StretchBlt(mdc, 0, 0, w/5, h/5, hdc, 0, 0, w, h, SRCCOPY);
	        StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/5, h/5, SRCCOPY);
	        ReleaseDC(0, hdc);
	        Sleep(10);
	    }
	}
	
	DWORD WINAPI EraseTrigonShake(LPVOID pvoid)
	{
		float angle = 0.f;
		while (true) {
			HDC hdc = GetDC(0);
			int x = cos(angle) * 10 - sin(angle) * 10;
			int y = sin(angle) * 10 + cos(angle) * 10;
			HBRUSH hbsh = CreateSolidBrush(RGB(rand() % 50, rand() % 50, rand() % 50));
			SelectObject(hdc, hbsh);
			BitBlt(hdc, x, y, w, h, hdc, 0, 0, MERGEERASE);
			ReleaseDC(0, hdc);
			angle += M_PI / 10;
			Sleep(10);
		}
	}
	
	DWORD WINAPI StretchPayload(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, -5, 5, w+10, h+10, hdc, 0, 0, w, h, SRCPAINT);
			StretchBlt(hdc, 5, 2, w-10, h-10, hdc, 0, 0, w, h, NOTSRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI RadiusRhombus(LPVOID pvoid)
	{
		float angle = 0.0;
		float incrementA = 0.0;
		while (true) {
			x += increment * signx;
			y += increment * signy;
			HDC hdc = GetDC(0);
			POINT polypoints[4];
			for (int t = 0; t < 4; t++) {
				int cx = x+100, cy = y+100, rad = 50;
				double angle = 2.0 * M_PI * t/4;
				polypoints[t].x = static_cast<int>(cx + rad * cos(angle));
				polypoints[t].y = static_cast<int>(cy + rad * sin(angle));
			}
			HBRUSH hbsh = CreateSolidBrush(HSV(incrementA));
			SelectObject(hdc, hbsh);
			RotatePoints(polypoints, angle, 4);
			Polygon(hdc, polypoints, _countof(polypoints));
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			angle += 0.1;
			incrementA += M_PI;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI RgbquadShader1(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { sizeof(bmp), w, h, 1, 32, BI_RGB }, 0 };
			RGBQUAD* rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			for (int t = 0; t < w * h; t++) {
				int x = t % w, y = t / h;
				rgbquad[t].rgbRed -= x^y;
				rgbquad[t].rgbGreen += x^y;
				rgbquad[t].rgbBlue = x^y;
			}
			BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ReflectionMirroring(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, 0, 0, w, h, hdc, w, 0, -w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI PatRaysShake(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
			SelectObject(hdc, hbsh);
			StretchBlt(hdc, -5, -5, w+10, h+10, hdc, 0, 0, w, h, 0xce464c);
			BitBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, SRCCOPY);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI TanSwirl(LPVOID pvoid)
	{
		int sizeX = h/10, sizeY = 3;
		while (true) {
			HDC hdc = GetDC(0);
			for (int t = 0; t < w * 2; t++) {
				int sine = tan(t / ((float)sizeX * M_PI) * sizeY);
				BitBlt(hdc, t, 0, 1, h, hdc, t, sine, SRCINVERT);
			}
			for (int t2 = 0; t2 < h * 2; t2++) {
				int sine = tan(t2 / ((float)sizeX * M_PI) * sizeY);
				BitBlt(hdc, 0, t2, w, 1, hdc, sine, t2, SRCAND);
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ScreenMelting(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int rw = rand() % w, rh = rand() % h;
			BitBlt(hdc, rw, 10, rand() % 50 - 25, h, hdc, rw, 0, SRCPAINT);
			BitBlt(hdc, 10, rh, w, rand() % 50 - 25, hdc, 0, rh, SRCAND);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI EraseMelt(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int rw = rand() % w, rh = rand() % h;
			BitBlt(hdc, rw, rand() % 50 - 25, 100, h, hdc, rw, 0, SRCERASE);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ORRotozoomer(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		int wp = w/5, hp = h/5;
		BITMAPINFO bmp = { sizeof(bmp), wp, hp, 1, 32, BI_RGB };
		RGBQUAD* rgbquad;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		double angle = 0.0;
		while (true) {
			StretchBlt(mdc, 0, 0, wp, hp, hdc, 0, 0, w, h, SRCCOPY);
			for (int x = 0; x < wp; x++) {
				for (int y = 0; y < hp; y++) {
					int cx = (x - (wp / 2)),
					cy = (y - (hp / 2));
					int index = y * wp + x;
					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;
					int preset = (zx+t)|(zy+t);
					RGBQUAD mrgbq;
					rgbquad[index].rgbRed = preset;
					rgbquad[index].rgbGreen = preset;
					rgbquad[index].rgbBlue = preset;
				}
			}
			t++;
			angle += 0.01;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wp, hp, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI FinalGDIPayload(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			int wp = w/8, hp = h/8;
			BITMAPINFO bmp = { sizeof(bmp), wp, hp, 1, 32, BI_RGB };
			RGBQUAD* rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wp, hp, hdc, 0, 0, w, h, SRCCOPY);
			for (int t = 0; t < wp * hp; t++) {
			//	int x = t % w, y = t / w;
				rgbquad[t].rgbRed += rand();
				rgbquad[t].rgbGreen += rand();
				rgbquad[t].rgbBlue += rand();
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wp, hp, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
}
