#include <windows.h>
#include "Colors.h"
typedef struct IUnknown IUnknown;

int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

COLORREF RndRGB(VOID) {
	COLORREF color;
	int colors = rand() % 5;
	if (colors == 0) color = RGB(255, 0, 0);
	if (colors == 1) color = RGB(0, 255, 0);
	if (colors == 2) color = RGB(0, 0, 255);
	if (colors == 3) color = RGB(255, 0, 255);
	if (colors == 4) color = RGB(255, 255, 0);
 
    return color;
}

#define xcbrt(a) ((a)/300)
#define xsqrt(b) ((b)/100)

typedef struct {
	float x;
	float y;
	float z;
} POINT3D, *PPOINT3D;



COLORREF HSV(int crLength) {
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

POINT3D RotatePoints(POINT3D point, float fx, float fy, float fz) {
	float cx = cos(fx), sx = sin(fx);
	float cy = cos(fy), sy = sin(fy);
	float cz = cos(fz), sz = sin(fz);
	
	float y = point.y * cx - point.z * sx;
	float z = point.y * sx + point.z * cx;
	point.y = y;
	point.z =z;
	float x = point.x * cy + point.z * sy;
	z = -point.x * sy + point.z * cy;
	point.x = x;
	point.z = z;
	x = point.x * cz - point.y * sz;
	y = point.x * sz + point.y * cz;
	point.x = x;
	point.y = y;
	
	return point;
}

DWORD WINAPI DrawCube(HDC hdc, POINT3D p3dCenter, float s, float fx, float fy, float fz) {
	POINT3D verts[] = {
		-s, -s, -s,
		s, -s, -s,
		s, s, -s,
		-s, s, -s,
		-s, -s, s,
		s, -s, s,
		s, s, s,
		-s, s, s
	};
	
	POINT spt[8];
	
	for (int t = 0; t < 8; t++) {
		POINT3D rotpoint = RotatePoints(verts[t], fx, fy, fz);
		int sx = static_cast<int>(p3dCenter.x + rotpoint.x),
		sy = static_cast<int>(p3dCenter.y + rotpoint.y);
		spt[t].x = sx;
		spt[t].y = sy;
		DrawIcon(hdc, sx, sy, LoadCursorA(NULL, IDC_ARROW));
	}
	
	POINT opt1[5] = {spt[0], spt[1], spt[2], spt[3], spt[0]};
	Polyline(hdc, opt1, 5);
	
	POINT opt2[5] = {spt[4], spt[5], spt[6], spt[7], spt[4]};
	Polyline(hdc, opt2, 5);
	
	POINT clpt[8] = {
		spt[0], spt[4], spt[1], spt[5],
		spt[2], spt[6], spt[3], spt[7]
	};
	Polyline(hdc, &clpt[0], 2);
	Polyline(hdc, &clpt[2], 2);
	Polyline(hdc, &clpt[4], 2);
	Polyline(hdc, &clpt[6], 2);
}

int signx = 1, signy = 1, signxcopy = 1, signycopy = 1;
int increment = 10;
float x = 10, y = 10;

namespace GDI {
	DWORD WINAPI InitialMovement(LPVOID pvoid)
	{
		// SCREEN SHAKING (UTILISES BITBLT) //
		HDC hdc = GetDC(0);
		DOUBLE intensity = 0.0;
		while (true) {
			BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
			intensity += 0.5;
			if (intensity > 5) Sleep(100);
			if (intensity < 5) Sleep(250);
			if (intensity > 10) intensity = 0.0;
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI Pixelation(LPVOID pvoid)
	{
		HDC hdc = GetDC(0),
	    mdc = CreateCompatibleDC(hdc);
		int wx = w / 4, hx = h / 4;
		HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(mdc, hbit);
		SetStretchBltMode(hdc, STRETCH_DELETESCANS);
		SetStretchBltMode(mdc, STRETCH_DELETESCANS);
		while (true) {
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI Melt(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			int wl = rand() % w, hl = rand() % h;
			BitBlt(hdc, wl, rand() % 20 - 10, 100, h, hdc, wl, 0, SRCPAINT);
			BitBlt(hdc, rand() % 20 - 10, hl, w, 100, hdc, 0, hl, SRCPAINT);
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI Shell32Icons(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			HINSTANCE hLib = LoadLibraryW(L"shell32.dll");
			DrawIcon(hdc, rand() % w, rand() % h, LoadIcon(hLib, MAKEINTRESOURCE(rand() % 2048)));
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI DLLTextouts(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			LPCSTR lpszStrings[] = {
				"advapi32", "winmm", "hal", "ci",
				"gdi32", "gdiplus", "shell32", "user32",
				"imageres", "moricons", "msvcrt", "ntdll",
				"kernel32", "msimg32"
			};
			int cnt = rand() % _countof(lpszStrings);
			HFONT hfnt = CreateFontW(70, 0, rand() % 50 - 25, 0, FW_SEMIBOLD, false, true, false, ANSI_CHARSET, 0, 0, 0, 0, L"Trebuchet MS");
			SelectObject(hdc, hfnt);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RndRGB());
			TextOutA(hdc, rand() % w, rand() % h, lpszStrings[cnt], strlen(lpszStrings[cnt]));
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI TheCollidoscope(LPVOID pvoid)
	{
		// OFFICIAL NAME: THE COLLIDOSCOPE //
		HDC hdc = GetDC(0);
		while (true) {
			StretchBlt(hdc, 0, 0, w, h, hdc, w/2, 0, -w, h, SRCINVERT);
			StretchBlt(hdc, w/2, 0, -w, h, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, NOTSRCCOPY);
			StretchBlt(hdc, 0, h/2, w, -h, hdc, 0, 0, w, h, SRCINVERT);
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI PatShake(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			HBRUSH hbsh = CreateSolidBrush(PALETTERGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(hdc, hbsh);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			BitBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, SRCCOPY);
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI CursorCube3D(LPVOID pvoid)
	{
		float ax = .0f, ay = .0f, az = .0f;
		float incrementA = 0.0;
		while (true) {
			HDC hdc = GetDC(0);
			x += increment * signx;
			y += increment * signy;
			if (x + 75 > w) {
				signx = -1;
				x = x - 76;
			}
			else if (x < 75) {
				signx = 1;
				x = 76;
			}
			if (y + 75 > h) {
				signy = -1;
				y = h - 76;
			}
			else if (y < 75) {
				signy = 1;
				y = 76;
			}
			POINT3D p3dCenter = { x, y, .0f };
			DrawCube(hdc, p3dCenter, 100, ax, ay, az);
			
			ax += 0.01;
			ay += 0.01;
			az += 0.01;
			incrementA += M_PI;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ColorNoise(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			int wx = w / 10, hx = h / 10;
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD* rgbquad;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			HBRUSH hbsh = CreateSolidBrush(RndRGB());
			SelectObject(mdc, hbsh);
			SelectObject(hdc, hbsh);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY|PATINVERT);
			for (int t = 0; t < wx * hx; t++) {
				rgbquad[t].rgbRed += rand();
				rgbquad[t].rgbGreen += rand();
				rgbquad[t].rgbBlue += rand();
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY|PATINVERT);
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
	
	DWORD WINAPI PlasmaRGB(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		INT t = 0;
		FLOAT angle = 0.0;
		while (true) {
			RGBQUAD* rgbquad;
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 3, hx = h / 3;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; ++x) {
				for (INT y = 0; y < hx; ++y) {
					INT index = y * wx + x;
					int cx = abs(x - (wx / 2)), cy = abs(y - (hx / 2));
					int rx = cosf(angle) * cx - sinf(angle) * cy,
					ry = sinf(angle) * cx + cosf(angle) * cy;
					int effect = t+((4*t)*sin(x/32.0))+((4*t)*sin(y/24.0));
					rgbquad[index].rgbRed += effect;
					rgbquad[index].rgbGreen += effect;
					rgbquad[index].rgbBlue += effect;
				}
			}
			t++;
			angle += 0.01;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10); 
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI ScreenBounce(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		FLOAT angle = 0.f;
		while (true) {
			int x = cos(angle) * 10, y = tan(angle) * 10;
			BitBlt(hdc, x, y, w, h, hdc, 0, 0, SRCPAINT);
			BitBlt(hdc, x, 0, w, h, hdc, 0, 0, SRCAND);
			angle += M_PI / 10;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI Grayscale(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)((t*4)+(t^4)*sqrt(RGB(5, 5, 5)));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+y/h*0.2f, 360);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI HSLCircles(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		float rx = 3, ry = 3;
		while (true) {
			int fw = rand() % w, fh = rand() % h;
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int cx = x - fw, cy = y - fh;
					
					int dx = (cx * cx) / (rx * rx);
					int dy = (cy * cy) / (ry * ry);
					
					int effect = 128 + (128 * sin(sqrt(dx + dy) / 12));
					int effect2 = effect + t;
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(effect2/400.f+y/h*0.2, 1.f);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI ShakeDeform(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			BitBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, SRCCOPY);
			BitBlt(hdc, 0, 0, w, rand() % h, hdc, rand() % 20 - 10, 0, SRCCOPY);
			BitBlt(hdc, 0, 0, rand() % w, h, hdc, 0, rand() % 20 - 10, SRCCOPY);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI ANDStrRoto(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		INT t = 0;
		FLOAT angle = 0.0;
		while (true) {
			RGBQUAD* rgbquad;
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 3, hx = h / 3;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; ++x) {
				for (INT y = 0; y < hx; ++y) {
					INT index = y * wx + x;
					int cx = (x - (wx / 2)), cy = (y - (hx / 2));
					int rx = cosf(angle) * cx - sinf(angle) * cy,
					ry = sinf(angle) * cx + cosf(angle) * cy;
					int effect = (rx+t)&(ry+t)+(rx+t);
					rgbquad[index].rgbRed += effect;
					rgbquad[index].rgbGreen += effect;
					rgbquad[index].rgbBlue += effect;
				}
			}
			t++;
			angle += 0.01;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10); 
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI HftnAnd(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		INT t = 0;
		FLOAT angle = 0.0;
		while (true) {
			RGBQUAD* rgbquad;
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 3, hx = h / 3;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			SetStretchBltMode(hdc, STRETCH_HALFTONE);
			SetStretchBltMode(mdc, STRETCH_HALFTONE);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; ++x) {
				for (INT y = 0; y < hx; ++y) {
					INT index = y * wx + x;
					int cx = abs(x - (wx / 2)), cy = abs(y - (hx / 2));
					int rx = cosf(angle) * cx - sinf(angle) * cy,
					ry = sinf(angle) * cx + cosf(angle) * cy;
					int effect = (rx+t)&(ry+t)+(rx+t);
					rgbquad[index].rgbRed += effect;
					rgbquad[index].rgbGreen += effect;
					rgbquad[index].rgbBlue += effect;
				}
			}
			t++;
			angle += 0.01;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10); 
		}
		ReleaseDC(0, hdc);
	}
}
