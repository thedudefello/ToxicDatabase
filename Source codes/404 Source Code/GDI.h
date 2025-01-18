#include "ColorFx.h"

INT w = GetSystemMetrics(SM_CXSCREEN);
INT h = GetSystemMetrics(SM_CYSCREEN);

INT signx = 1, signy = 1;
INT xincrement = 2;
INT increment = 10;
INT x = 10, y = 10;

COLORREF Hue(int crLength) {
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

FLOAT incrementA = 0.f;

namespace GDI {
	DWORD WINAPI InitialEllipseRadius(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		DOUBLE radius = 0.f;
		while (TRUE) {
			x += xincrement * signx, y += xincrement * signy;
			INT zx = x + cos(radius) * 100, zy = y + sin(radius) * 100;
			SelectObject(hdc, CreateSolidBrush(Hue(incrementA)));
			Ellipse(hdc, zx - 25, zy - 25, zx + 25, zy + 25);
			radius += 0.5f;
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			incrementA++;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI XORRotozoomerHSL(LPVOID lpProc)
	{ // egg
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0; DOUBLE angle = 0.f;
		while (true) {
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					INT cx = (x - (w / 2)), cy = (y - (h / 2));
					INT rx = cos(angle) * cx - sin(angle) * cy,
					ry = sin(angle) * cx + cos(angle) * cy;
					INT FX = (rx+t)^(ry+t);
					hsl.h = fmod((FX/500.0)+hsl.h+0.05, 1);
					hsl.s = 1.f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			angle += 0.01f;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI BrightPixelation(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (true) {
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 64, 0};
			HBITMAP hbit = CreateDiscardableBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			SetStretchBltMode(hdc, STRETCH_ORSCANS);
			SetStretchBltMode(mdc, STRETCH_ORSCANS);
			StretchBlt(mdc, 0, 0, w / 5, h / 5, hdc, 0, 0, w, h, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w / 5, h / 5, ftn);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	VOID RectangleWef(INT x, INT y, INT w, INT h) {
		HDC hdc = GetDC(0);
		HRGN rgn = CreateRectRgn(x, y, w+x, h+y);
		SelectClipRgn(hdc, rgn);
		BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI RectanglePayload(LPVOID lpProc)
	{
		while (TRUE) {
			INT Size = 500;
//			for (INT i = 0;; i++) {
				INT x = rand() % (w + Size) - Size / 2;
				INT y = rand() % (h + Size) - Size / 2;
				for (INT j = 0; j < Size; j += 50) {
					RectangleWef(x - j / 2, y - j / 2, j, j);
					Sleep(10);
				}
			}
		}
//	}

	DWORD WINAPI ORHSV(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, rand() % 5, rand() % 5, w, h, hdc, rand() % 5, rand() % 5, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)(x|y);
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+hsl.h+0.2f, 1.f);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCERASE);
			Sleep(10);
		}
		return 0;
	}
	
	DOUBLE Sine(DOUBLE amplitude, DOUBLE frequency, DOUBLE phaser, DOUBLE period) {
	    return amplitude * sin(2 * M_PI * frequency * phaser / period);
	}
	
	DWORD WINAPI FrequencyWaves(LPVOID pvoid)
	{
	    HDC hdc = GetDC(0);
	    while (TRUE) {
	        INT t = 0;
	        for (INT y = 0; y < h; ++y) {
	            INT phase = rand() % 100 - 50;
	            INT sx = Sine(10, y + t * 5, phase, h);
	            BitBlt(hdc, 0, y, w - sx, 1, hdc, sx, y, SRCCOPY);
	        }
	        Sleep(10);
	        t++;
	    }
	    return 0x01;
	}
	
	BITMAPINFO CreateBitmapInfo(INT width, INT height) {
		BITMAPINFO lpbmi;
		lpbmi.bmiHeader.biSize = sizeof(BITMAPINFO);
		lpbmi.bmiHeader.biWidth = width;
		lpbmi.bmiHeader.biHeight = height;
		lpbmi.bmiHeader.biPlanes = 1;
		lpbmi.bmiHeader.biBitCount = 32;
		lpbmi.bmiHeader.biCompression = BI_RGB;
		return lpbmi;
	}
	
	DWORD WINAPI RedBlueXOR(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		INT i = 0;
		while (true) {
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgbquad;
			BITMAPINFO lpbmi = CreateBitmapInfo(w, h);
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (PHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < w; x++) {
				for (INT y = 0; y < h; y++) {
					INT Index = y * w + x;
					rgbquad[Index].rgbGreen = (x ^ y) + i;
					rgbquad[Index].rgbBlue = (x ^ y) + i;
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI AnimHalfPentagon(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (true) {
			POINT apt[5];
			x += increment * signx, y += increment * signy;
			INT cx = x + 100, cy = y + 100;
			INT radius = 100;
			for (INT i = 0; i < 5; i++) {
				DOUBLE angle = 2.f * M_PI * i / 6;
				apt[i].x = cx + (INT)(cos(angle) * radius);
				apt[i].y = cy + (INT)(sin(angle) * radius);
			}
			SelectObject(hdc, CreateSolidBrush(Hue(incrementA)));
			Polygon(hdc, apt, 5);
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			incrementA++;
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI PlgBltThing(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (true) {
			HWND hwnd = GetDesktopWindow();
			RECT lpRect;
			GetWindowRect(hwnd, &lpRect);
			POINT lpPoint[3];
			
			lpPoint[0].x = lpRect.left; lpPoint[0].y = lpRect.top;
			lpPoint[1].x = lpRect.right + 50; lpPoint[1].y = lpRect.top + 20;
			lpPoint[2].x = lpRect.left; lpPoint[2].y = lpRect.bottom + 5;
			
			PlgBlt(hdc, lpPoint, hdc, lpRect.left, lpRect.top, lpRect.right - lpRect.left, lpRect.bottom - lpRect.top, NULL, 0, 0);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI RedAndFractals(LPVOID lpProc)
	{
		/* This shader was made by Sickdows!
		I converted it to a rotozoomer. */
		HDC hdc = GetDC(0);
		INT i = 0;
		DOUBLE angle = 0.f;
		while (true) {
			HDC mdc = CreateCompatibleDC(hdc);
			RGBQUAD *rgbquad;
			BITMAPINFO lpbmi = CreateBitmapInfo(w, h);
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (PHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < w; x++) {
				for (INT y = 0; y < h; y++) {
					INT Index = y * w + x;
					INT cx = abs(x - (w / 2)), cy = abs(y - (h / 2));
					INT rx = cos(angle) * cx - sin(angle) * cy;
					INT ry = sin(angle) * cx + cos(angle) * cy;
					rgbquad[Index].rgbRed = rx&ry;
				}
			}
			i++;
			angle += 0.01f;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCERASE);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI AlphaStretching(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (true) {
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 64, 0};
			HBITMAP hbit = CreateDiscardableBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, -10, 10, w + 30, h + 40, hdc, 0, 0, w, h, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI ANDHSV(LPVOID lpProc)
	{ // egg
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
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(((x&y)/10000.0)+hsl.h+0.05, 1);
					hsl.s = 1.f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI ExeRadius(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		DOUBLE radius = 0.f;
		while (true) {
			POINT lpPoint;
			GetCursorPos(&lpPoint);
			INT zx = lpPoint.x + cos(radius) * 100, zy = lpPoint.y + sin(radius) * 100;
			DrawIconEx(hdc, zx, zy, LoadIcon(NULL, IDI_APPLICATION), 3 * GetSystemMetrics(SM_CXICON), 3 * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
			Sleep(10);
			radius += 0.5f;
		}
		return 0x01;
	}
	
	DWORD WINAPI FontTextouts(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (true) {
			LPCSTR lpString[] = {
				"Arial", "Arial Black", "Marlett", "Courier New",
				"Trebuchet MS", "Comic Sans MS", "MV Boli", "Wingdings",
				"Wingdings 2", "System", "Fixedsys", "Tahoma",
				"Verdana", "Times New Roman", "Webdings", "Lucida Console",
				"Microsoft Sans Serif", "Script", "System", "Roman"
			};
			INT totstr = _countof(lpString);
			for (INT i = 0; i < totstr; i++) {
				HFONT hfnt = CreateFontA(70, 0, -rand() % 60, 0, FW_EXTRALIGHT, FALSE, TRUE, FALSE, OEM_CHARSET, 0, 0, 0, 0, lpString[i]);
				SelectObject(hdc, hfnt);
				TextOutA(hdc, rand() % w, rand() % h, lpString[i], strlen(lpString[i]));
				Sleep(10);
			}
		}
		return 0x01;
	}
	
	DWORD WINAPI StrongSineStretch(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (true) {
			SetStretchBltMode(hdc, STRETCH_DELETESCANS);
			for (FLOAT i = 0; i < 360; i += 0.9f) {
						SelectObject(hdc, CreateSolidBrush(Hue(incrementA)));
				INT zx = 25 * sin(i * M_PI / 20), zy = 90 * cos(i * M_PI / 20);
				StretchBlt(hdc, zx / 2, zy / 2, w - zx, h - zy, hdc, 0, 0, w, h, 0x890000);
				incrementA++;
				Sleep(10);
			}
		}
		return 0x01;
	}
	
	DWORD WINAPI GrayEllipses(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (true) {
			INT Random = rand() % 0xff;
			SelectObject(hdc, CreateSolidBrush(RGB(Random, Random, Random)));
			INT rw = rand() % w, rh = rand() % h;
			Ellipse(hdc, rw, rh, rw + 35, rh + 35);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI GrayscaleShake(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, rand() % 5, rand() % 5, w, h, hdc, rand() % 5, rand() % 5, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)((t*4)+(t^4)*sqrt(RGB(1, 1, 1)));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+hsl.h+0.2f, 360);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI AlphaPlg(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (TRUE) {
			HBITMAP hbit = CreateDiscardableBitmap(hdc, w, h);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			SelectObject(mdc, hbit);
			HWND hwnd = GetDesktopWindow();
			RECT lpRect;
			GetWindowRect(hwnd, &lpRect);
			POINT lpPoint[3];
			
			lpPoint[0].x = lpRect.left - 10; lpPoint[0].y = lpRect.top;
			lpPoint[1].x = lpRect.right + 10; lpPoint[1].y = lpRect.top - 5;
			lpPoint[2].x = lpRect.left; lpPoint[2].y = lpRect.bottom;
			
			PlgBlt(mdc, lpPoint, hdc, lpRect.left, lpRect.top, lpRect.right - lpRect.left, lpRect.bottom - lpRect.top, NULL, 0, 0);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI TrianglePayload(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (TRUE) {
			INT size = 500;
			INT zx = rand() % (w + size) - size / 2,
			zy = rand() % (h + size) - size / 2;
			for (INT i = 0; i < size; i += 50) {
				POINT pptl[3] = {
					zx, zy - i / 2,
					zx - i / 2, zy + i / 2,
					zx + i / 2, zy + i / 4
				};
				HRGN rgn = CreatePolygonRgn(pptl, 3, WINDING);
				SelectClipRgn(hdc, rgn);
//				SelectObject(hdc, CreateSolidBrush(Hue(incrementA)));
				BitBlt(hdc, zx - i / 2, zy - i / 2, i, i, hdc, zx - i / 2, zy - i / 2, NOTSRCCOPY);
//				incrementA++;
			}
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI RadialBlur(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (TRUE) {
			HBITMAP hbit = CreateDiscardableBitmap(hdc, w, h);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, 0};
			SelectObject(mdc, hbit);
			StretchBlt(mdc, -4, -4, w + 8, h + 8, hdc, 0, 0, w, h, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI LastHSVShader(LPVOID lpProc)
	{ // egg
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, -h, 1, 32, BI_RGB }, 0 };
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
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					INT FX = x + y;
					hsl.h = fmod((FX/500.0)+hsl.h+0.05, 1);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, rand() % 5, rand() % 5, w, h, mdc, rand() % 5, rand() % 5, w, h, SRCERASE);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI RGBCircle(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		INT i = 0;
		while (TRUE) {
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < wx; x++) {
				for (INT y = 0; y < hx; y++) {
					INT Index = y * wx + x;
					INT cx = abs(x - (wx / 2.f)), cy = abs(y - (hx / 2.f));
					INT xi = 128.f + i;
					INT FX = xi + (xi * sin(sqrt((cx * cx) + (cy * cy)) / xi));
					rgbquad[Index].rgbRed += FX;
					rgbquad[Index].rgbGreen = FX;
					rgbquad[Index].rgbBlue = FX;
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI GradientTriangles(LPVOID lpProc)
	{
		HDC hdc = GetDC(0);
		while (TRUE) {
			TRIVERTEX pVertex[3] = {
				// X, Y, RED, GREEN, BLUE, ALPHA //
				rand() % w, rand() % h, 0x78ff, 0x5fff, 0xa3ff, 0xffff,
				rand() % w, rand() % h, 0x85ff, 0x1dff, 0x14ff, 0xffff,
				rand() % w, rand() % h, 0x0000, 0x0000, 0xffff, 0xffff
			};
			GRADIENT_TRIANGLE pMesh = {0, 1, 2};
			GradientFill(hdc, pVertex, 3, &pMesh, 1, GRADIENT_FILL_TRIANGLE);
			Sleep(10);
		}
		return 0x01;
	}
	
	DWORD WINAPI Noise(LPVOID lpProc)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (TRUE) {
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO lpbmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &lpbmi, DIB_RGB_COLORS, (LPHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			SetStretchBltMode(hdc, STRETCH_HALFTONE);
			SetStretchBltMode(mdc, STRETCH_HALFTONE);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT i = 0; i < wx * hx; i++) {
				rgbquad[i].rgbRed = rand();
				rgbquad[i].rgbGreen = rand();
				rgbquad[i].rgbBlue = rand();
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
		}
		return 0x01;
	}
}
