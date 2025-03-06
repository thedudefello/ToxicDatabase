// GDI HEADER //
CONST FLOAT PI = acos(-1.0);
CONST FLOAT SQRT2 = sqrt(2);

CONST INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
typedef DWORD SHADER;
typedef DWORD GDIEFFECT;
typedef DWORD SPRITE3D;

#include "ColorFx.h" // Colour functions!

BITMAPINFO CreateBitmapInfo(INT width, INT height) {
	BITMAPINFO lpbmi = {sizeof(lpbmi), width, height, 1, 32, BI_RGB};
	return lpbmi;
}

SHORT PAYLOAD_S;
DWORD PAYLOAD_MS;

namespace GDI {
	GDIEFFECT WINAPI AngledSineRotation(LPVOID lpProc) {
		HDC hdc;
		FLOAT factor = 0.f;
		PAYLOAD_MS = 31 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (EndTime > GetTickCount()) {
			hdc = GetDC(0);
			HWND hwnd = GetDesktopWindow();
			RECT rect;
			GetWindowRect(hwnd, &rect);
			POINT point[3];
			INT fc = tan(factor) * 45;
			
			if (rand() % 2 == 0) {
				point[0].x = rect.left + fc; point[0].y = rect.top - fc;
				point[1].x = rect.right; point[1].y = rect.top + fc;
				point[2].x = rect.left; point[2].y = rect.bottom - fc;
			}
			
			PlgBlt(hdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			factor += PI / 15;
			Sleep(5);
			ReleaseDC(0, hdc);
		}
	}
	
	GDIEFFECT WINAPI AlphaGliding(LPVOID lpProc)
	{
		HDC hdc;
	//	INT i = 0;
		PAYLOAD_MS = 29 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			HWND hwnd = GetDesktopWindow();
			RECT rect;
			GetWindowRect(hwnd, &rect);
			POINT point[3];
			SelectObject(mdc, hbit);
			
			point[0].x = rect.left; point[0].y = rect.top - 90;
			point[1].x = rect.right; point[1].y = rect.top;
			point[2].x = rect.left; point[2].y = rect.bottom + 30;
			
			PlgBlt(mdc, point, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			Sleep(5);
			ReleaseDC(0, hdc);
		}
	}
	
	GDIEFFECT WINAPI GradientTriangles(LPVOID lpProc)
	{
		HDC hdc;
	//	INT i = 0;
		PAYLOAD_MS = 30 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			TRIVERTEX pVertex[3] = {
				// X, Y, RED, GREEN, BLUE, ALPHA //
				{rand() % w, rand() % h, 0x8000, 0x8000, 0x8000, 0xffff},
				{rand() % w, rand() % h, 0x0000, 0xd000, 0xd000, 0xffff},
				{rand() % w, rand() % h, 0x8000, 0x8000, 0x8000, 0xffff}
			};
			GRADIENT_TRIANGLE pMesh = {0, 1, 2};
			GdiGradientFill(hdc, pVertex, 3, &pMesh, 1, GRADIENT_FILL_TRIANGLE);
		}
	}
	
	GDIEFFECT WINAPI IconPattern(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 31 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		FLOAT radius = 0.f;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			INT rw = rand() % w, rh = rand() % h;
			for (INT j = 0; j < w; j++) {
				INT radius = 30;
				INT zx = radius * sin(j - radius * 5) + rw,
				zy = radius + j * sin(i - radius * 5) + rh;
				DrawIcon(hdc, zx, zy, LoadCursorA(NULL, rand() % 2 ? IDC_ARROW : IDC_WAIT));
			radius += sqrt(2);
			i++;
			}
			Sleep(5);
		}
	}
	
	GDIEFFECT WINAPI GreekLetterTexts(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 30 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		FLOAT incrementA = 0.f;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			LPCSTR lpszFonts[] = {
				"Arial", "Arial Black", "Impact",
				"Courier New", "Lucida Console", "Fixedsys"
			};
			LPCSTR lpszStrings[] = {
				"Delta", "Alpha", "Beta", "Gamma",
				"Omicron", "Epsilon", "Upsilon", "Sigma",
				"Zeta", "Kappa", "Omega", "Micro", "Psi"
			};
			INT totstr = _countof(lpszStrings);
			for (INT i = 0; i < totstr; i++) {
				HFONT hfnt = CreateFontA(rand() % 100 + 50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, OEM_CHARSET, 0, 0, 0, 0, lpszFonts[rand() % 6]);
				SelectObject(hdc, hfnt);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, Hue(incrementA));
				TextOutA(hdc, rand() % w, rand() % h, lpszStrings[i], strlen(lpszStrings[i]));
				incrementA++;
			}
			Sleep(5);
		}
	}
	
	GDIEFFECT WINAPI HalftoneStretch(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 29 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			SetStretchBltMode(hdc, STRETCH_HALFTONE);
			for (INT i = 0; i < 360; i++) {
				INT zx = i * sin(i * M_PI / 30), zy = i * log2(i * M_PI * 2);
				StretchBlt(hdc, zx / 2, zy / 2, w - zx, h - zy, hdc, 0, 0, w, h, SRCAND);
			}
			Sleep(2000);
		}
	}
	
	
}
namespace Shaders {
	SHADER WINAPI TiltedMovingXORRGB(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_S = 29;
		PAYLOAD_MS = 1000 * PAYLOAD_S;
		INT i = 0;
		DWORD EndTime = PAYLOAD_MS + GetTickCount();
		FLOAT incrementA = 0.f;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD* px = (LPDWORD)VirtualAlloc(NULL, w * h, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			COLORPAL32 *cp32;
			SelectObject(mdc, CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0));
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT j = 0; j < wx * hx; j++) {
				INT x = j % wx, y = j / wx;
				cp32[j].cp32Colors = ((x - y + i) * (y + x + i)) * Hue(incrementA);
			}
			i++;
			incrementA += PI;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
		}
		return 0x01;
	}
	
	
	SHADER WINAPI StripedRGBMovement(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_S = 29;
		PAYLOAD_MS = 1000 * PAYLOAD_S;
		INT i = 0;
		DWORD EndTime = PAYLOAD_MS + GetTickCount();
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD* px = (LPDWORD)VirtualAlloc(NULL, w * h, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			COLORPAL32 *cp32;
			SelectObject(mdc, CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0));
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT j = 0; j < wx * hx; j++) {
				INT x = j % wx, y = j / wx;
				INT FX = (INT)(y * (i & i * 5));
				cp32[j].cp32Blue ^= FX;
				cp32[j].cp32Green += FX;
				cp32[j].cp32Red = FX;
			}
			i++;
			StretchBlt(hdc, rand() % 20 - 10, rand() % 10 - 20, w, h, mdc, 0, 0, wx, hx, SRCINVERT);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI RainbowANDFractals(LPVOID lpProc)
	{
		HDC hdc;
		INT i = 0;
		PAYLOAD_MS = 31 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 5, hx = h / 5;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD *px = (DWORD *)VirtualAlloc(NULL, wx * hx, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			COLORPAL32 *cp32;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT j = 0; j < wx * hx; j++) {
				INT x = j % wx, y = j / wx;
				INT fx = (x + i * y + i) * RGB(i, i + 255, i + 250);
				cp32[j].cp32Colors += fx;
			}
			i++;
			if (i > 255) i = 0;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(5);
		}
	}
	
	SHADER WINAPI TangentPlasma(LPVOID lpProc)
	{
		HDC hdc;
		INT i = 0;
		PAYLOAD_MS = 30 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 5, hx = h / 5;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD *px = (DWORD *)VirtualAlloc(NULL, wx * hx, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			RGBQUAD *rgb;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&rgb, NULL, 0);
			SelectObject(mdc, hbit);
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff)));
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, PATCOPY | SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT dt = 128 + i;
					INT fx = dt + (dt * (sin(i + x / 30.0))) + dt + (dt * (sin(i + y / 30.0)));
					INT index = y * wx + x;
					rgb[index].rgbRed += fx;
					rgb[index].rgbGreen = fx;
					rgb[index].rgbBlue = fx;
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, PATCOPY | SRCCOPY);
			Sleep(5);
		}
	}
	
	SHADER WINAPI ORFractalClutter(LPVOID lpProc)
	{
		HDC hdc;
		INT i = 0;
		PAYLOAD_MS = 29 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD *px = (DWORD *)VirtualAlloc(NULL, wx * hx, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			COLORPAL32 *cp32;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT j = 0; j < wx * hx; j++) {
				INT x = j % wx, y = j / wx;
				cp32[j].cp32Colors = ((x | y) & i) - (i * RGB(i, i - 20, i));
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(5);
		}
	}
	
	SHADER WINAPI RandomCircle(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 30 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			INT rw = rand() % w, rh = rand() % h;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			DWORD *px = (DWORD *)VirtualAlloc(NULL, wx * hx, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			RGBQUAD *rgb;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&rgb, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT index = y * wx + x;
					INT cx = abs(x - (rw / 2)), cy = abs(y - (rh / 2));
					INT zx = cx * cx, zy = cy * cy;
					INT dt = 128;
					INT fx = dt + (dt * sin(sqrt(zx + zy) / 8));
					rgb[index].rgbRed += fx;
					rgb[index].rgbGreen += fx;
					rgb[index].rgbBlue += fx;
				}
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(5);
		}
	}
	
	SHADER WINAPI VerticalPlasma(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 31 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		INT i = 0;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			BITMAPINFO lpbmi = CreateBitmapInfo(w, h);
			COLORPAL32 *cp32;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < w; x++) {
				for (INT y = 0; y < h; y++) {
					INT index = y * w + x;
					INT dt = 128;
					INT fx = dt + (dt * sin((i + y) / 2));
					cp32[index].cp32Colors = fx - RGB(20, i - 5, i);
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(5);
		}
	}
	
	DWORD WINAPI ANDVerticalRotozoomer(LPVOID lpProc)
	{
		HDC hdc;
		PAYLOAD_MS = 30 * 1000;
		DWORD EndTime = GetTickCount() + PAYLOAD_MS;
		INT i = 0;
		FLOAT angle = 0.f;
		while (GetTickCount() < EndTime) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			COLORPAL32 *cp32;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&cp32, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT index = y * wx + x;
					INT cx = abs(x - (wx / 2)), cy = abs(y - (hx / 2));
					INT zx = cos(angle) * cx - sin(angle) * cy,
					zy = sin(angle) * cx + cos(angle) * cy;
					cp32[index].cp32Red = zx * zy;
					cp32[index].cp32Green += zy;
					cp32[index].cp32Blue += zy;
				}
			}
			i++; angle += 0.01;
			StretchBlt(hdc, 0, 3, w, h, mdc, 0, 1, wx, hx, SRCINVERT);
			Sleep(5);
		}
	}
}

namespace _3D {
	
	typedef struct {
		FLOAT x;
		FLOAT y;
		FLOAT z;
	} POINT3D, *PPOINT3D;
	
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
	
	COLORREF Hue2(INT clr, FLOAT cx, FLOAT cy, FLOAT cz) {
		clr = fmax(1, fmin(255, clr));
		if (clr <= 64) {
			INT gry = clr * 255 / 63.f;
			return RGB(gry, gry, gry);
		}
		FLOAT fc = (clr - 64) / 191.f;
		INT r = (INT)(255 * fc * (cx + 1.f) / 2.f);
		INT g = (INT)(255 * fc * (cy + 1.f) / 2.f);
		INT b = (INT)(255 * fc * (cz + 1.f) / 2.f);
		INT gry = 255 * (1.f - fc);
		return RGB(gry + r, gry + g, gry + b);
	}
	
	DWORD64 __stdcall Sphere2(HDC hdc, POINT3D pc, INT rad, FLOAT ax, FLOAT ay, FLOAT az, FLOAT clr) {
		for (INT i = 0; i <= 180; i += 10) {
			for (INT j = 0; j <= 360; j += 10) {
				FLOAT r = i * PI / 180.f;
				FLOAT rt = j * PI / 180.f;
				
				POINT3D pt = {rad * sin(r) * cos(rt), rad * cos(r) - sin(rt), rad * cos(r)};
				pt = RotatePoints(pt, ax, ay, az);
				INT x = (INT)(pc.x + pt.x);
				INT y = (INT)(pc.y + pt.y);
				HBRUSH hbsh = CreateSolidBrush(Hue2(clr, pt.x / rad, pt.y / rad, pt.z / rad));
				SelectObject(hdc, hbsh);
				Ellipse(hdc, x, y, x + 10, y + 10);
				DeleteObject(hbsh);
			}
		}
	}
	
	SPRITE3D WINAPI Model3D(LPVOID lpProc) {
		INT x = w / 2, y = h / 2;
		INT incr = 10, incr2 = 10;
		INT rad = 300;
		FLOAT spd = 0.05f;
		FLOAT ax = 0.f, ay = 0.f, az = 0.f;
		INT clr = 1;
		while (TRUE) {
			HDC hdc = GetDC(0);
			POINT3D pc = {x, y, 0.f};
			Sphere2(hdc, pc, rad, ax, ay, az, clr);
			x += incr, y += incr2;
			if (x - rad < 0 || x + rad > w) incr = -incr;
			if (y - rad < 0 || y + rad > h) incr2 = -incr2;
			ax += spd, ay += spd, az += spd;
			if (clr < 255) clr++;
			Sleep(5);
		}
		return 0x01;
	}
}
