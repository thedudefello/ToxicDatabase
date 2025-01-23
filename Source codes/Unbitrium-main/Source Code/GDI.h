typedef LPVOID *VOID_PTR;


#define min(x, y) ((x)<(y)?(x):(y))
#define max(z, a) ((z)>(a)?(z):(a))

typedef struct _HSL {
  float h;
  float s;
  float l;
} HSL, *PHSL, *LPHSL;

HSL rgbQuadRGB(RGBQUAD rgbQuad) { // I only rewrote this.
	HSL hsl;
	
	BYTE r = rgbQuad.rgbRed, g = rgbQuad.rgbGreen, b = rgbQuad.rgbBlue;
	float fr = (float)r/255.f;
	float fg = (float)g/255.f;
	float fb = (float)b/255.f;
	
	float minr = min(min(fr, fg), fb), maxr = max(max(fr, fg), fb); // I fixed this part since that's what made the HSL so opaque!
	float delta = maxr-minr;
	float delr, delg, delb;
	
	float h = 0.f, s = 0.f, l = (float)((maxr+minr)/2.f);
	
	if (delta != 0.f) {
		s = l < 0.5f ? (float)(delta / (maxr + minr)) : (float)(delta / (2.f - maxr - minr));
		delr = (float)(((maxr - fr) / 6.f + (delta / 2.f)) / delta);
		delg = (float)(((maxr - fg) / 6.f + (delta / 2.f)) / delta);
		delb = (float)(((maxr - fb) / 6.f + (delta / 2.f)) / delta);
		
		if (fr == maxr) h = delb-delg;
		else if (fg == maxr) h = (1.f / 3.f) + delr - delb;
		else if (fb == maxr) h = (2.f / 3.f) + delg - delr;
		if (h < 0.f) h += 1.f;
		if (h > 1.f) h -= 1.f;
	}
	
	hsl.h = h;
	hsl.s = s;
	hsl.l = l;
	return hsl;
}

RGBQUAD hslRGB(HSL hsl) {
	RGBQUAD rgbq;
	float r = hsl.l, g = hsl.l, b = hsl.l;
	float h = hsl.h, s2 = hsl.s, l = hsl.l;
	float vh = (l <= 0.5f) ? (l*(1.f + s2)) : (l+s2-l*s2);
	
	float m, sv, frac, vsf, mid, mid2;
	int st;
	
	if (vh > 0.f) {
		m = l + l - vh;
		sv = (vh - m) / vh;
		h *= 6.f;
		st = (int)h;
		frac = h-st;
		vsf = vh*sv*frac;
		mid = m+vsf;
		mid2 = vh-vsf;
		switch(st) {
			case 0:
				r = vh;
				g = mid;
				b = m;
				break;
			case 1:
				r = mid2;
				g = vh;
				b = m;
				break;
			case 2:
				r = m;
				g = vh;
				b = mid;
				break;
			case 3:
				r = m;
				g = mid2;
				b = vh;
				break;
			case 4:
				r = mid;
				g = m;
				b = vh;
				break;
			case 5:
				r = vh;
				g = m;
				b = mid2;
				break;
        }
	}
	
	rgbq.rgbRed = (BYTE)(r*255.f);
	rgbq.rgbGreen = (BYTE)(g*255.f);
	rgbq.rgbBlue = (BYTE)(b*255.f);
	return rgbq;
}

INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
INT iconX = GetSystemMetrics(SM_CXICON), iconY = GetSystemMetrics(SM_CYICON);

FLOAT WINAPI RotatePoints(LPPOINT lpPoint, POINT pCenter, FLOAT fAngle, INT nCount) {
	for (INT t = 0; t < nCount; t++) {
		FLOAT x = lpPoint[t].x - pCenter.x;
		FLOAT y = lpPoint[t].y - pCenter.y;
		lpPoint[t].x = static_cast<INT>(cosf(fAngle) * x - sinf(fAngle) * y + pCenter.x);
		lpPoint[t].y = static_cast<INT>(sinf(fAngle) * x + cosf(fAngle) * y + pCenter.y);
	}
}

INT signx = 1, signy = 1;
INT increment = 10;
FLOAT x = 10, y = 10;

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



namespace GDI {
	DWORD WINAPI InitialGradientRect(LPVOID pvoid) {
		HDC hdc = GetDC(0);
		while (true) {
			POINT cpt;
			GetCursorPos(&cpt);
			TRIVERTEX vtx[2] = {
				// X, Y, RED, GREEN, BLUE, ALPHA //
				{cpt.x, cpt.y, 0xffff, 0, 0xffff, 0xffff},
				{cpt.x + 100, cpt.y + 200, 0xffff, 0xffff, 0, 0xffff}
			};
			GRADIENT_RECT rectangle = {0, 1};
			GdiGradientFill(hdc, vtx, 2, &rectangle, 1, GRADIENT_FILL_RECT_V);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI InitialColorize(LPVOID pvoid)
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
					int HslPreset = (int)((t*4)+(t^4)*sqrt(20));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/500.f+hsl.h+0.02f, 1.f);
					hsl.s = 1.f;
					hsl.l = 0.5f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI TanWaves(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		FLOAT angle = 0.0f;
		while (true) {
			for (INT t = 0; t < w + h; t++) {
				int tangent = tan(angle) * 50;
				BitBlt(hdc, 0, t, w, 15, hdc, tangent, t, SRCPAINT);
				BitBlt(hdc, t, 0, 15, h, hdc, t, tangent, SRCAND);
				angle += M_PI / 90;
			}
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI AnimRotoInvRhombus(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		FLOAT rotate = 0.0f;
		while (true) {
			POINT vpt[4];
			x += increment * signx;
			y += increment * signy;
			INT cx = x + 100, cy = y + 100, radius = 100;
			for (INT t = 0; t < 4; t++) {
				FLOAT angle = 2.f * M_PI * t / 4;
				vpt[t].x = cx + static_cast<INT>(radius * cosf(angle));
				vpt[t].y = cy + static_cast<INT>(radius * sinf(angle));
			}
			POINT center = {(x + cx) / 2, (y + cy) / 2};
			RotatePoints(vpt, center, rotate, 4);
			HRGN rgn = CreatePolygonRgn(vpt, 4, WINDING);
			InvertRgn(hdc, rgn);
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			rotate += 0.05f;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI AnimHeptagon(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		INT incrementA = 0;
		while (true) {
			POINT vpt[7];
			x += increment * signx;
			y += increment * signy;
			INT cx = x + 100, cy = y + 100, radius = 100;
			for (INT t = 0; t < 7; t++) {
				FLOAT angle = 2.f * M_PI * t / 7;
				vpt[t].x = cx + static_cast<INT>(radius * cosf(angle));
				vpt[t].y = cy + static_cast<INT>(radius * sinf(angle));
			}
			HBRUSH hbsh = CreateSolidBrush(Hue(incrementA));
			SelectObject(hdc, hbsh);
			Polygon(hdc, vpt, 7);
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			incrementA++;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI GrayscaleGradientTriangles(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			TRIVERTEX vtx[3] = {
				// X, Y, RED, GREEN, BLUE, ALPHA //
				{rand() % w, rand() % h, 0, 0, 0, 0xffff},
				{rand() % w, rand() % h, 0, 0, 0, 0xffff},
				{rand() % w, rand() % h, 0xffff, 0xffff, 0xffff, 0xffff}
			};
			GRADIENT_TRIANGLE triangle = {0, 1, 2};
			GdiGradientFill(hdc, vtx, 3, &triangle, 1, GRADIENT_FILL_TRIANGLE);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI TiltedXORHSVShake(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32, BI_RGB }, 0 };
		LPRGBQUAD rgbq = NULL;
		HSL hsl;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (VOID_PTR)&rgbq, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		while (true) {
			StretchBlt(mdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, w, h, SRCCOPY);
			RGBQUAD mrgbq;
			for (int x = 0; x < w; x++) {
				for (int y = 0; y < h; y++) {
					int iIndex = y * w + x;
					int HslPreset = (int)(x+(t*4)^(x+y));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/500.f+hsl.h+0.02f, 1.f);
					hsl.s = 1.f;
					hsl.l = .5f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI HSVPlasma(LPVOID pvoid)
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
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					INT FX = ((t^4)+((t*4)*sin(x / 16.f))+((t*4)*sin(y / 8.f))+((t*4)*sin(x + y / 8.f))+((t*4)*sin(sqrt((x*x)+(y*y)/4.f))));
					hsl.h = fmod((FX/500.0)+y/h+0.05, 1);
					hsl.s = 1.f;
					hsl.l = .5f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI SystemFileTexts(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0);
		while (true) {
			LPCSTR lpszStrings[] = {
				"autoexec", "command", "desktop.ini", "adfs.msi", "dialer",
				"explorer.exe", "notepad", "regedit", "system.ini", "vb.ini",
				"win.ini", "winnt.bmp", "alg", "calc", "charmap", "chkdsk", "choice",
				"cipher", "cliconfg", "cmdlib", "cmmgr32", "cmmon32", "cmstp"
			};
			INT totstr = sizeof(lpszStrings) / sizeof(lpszStrings[0]);
			for (INT t = 0; t < totstr; t++) {
				HFONT hfnt = CreateFontA(70, 40, rand() % 60, 0, FW_LIGHT, false, true, false, OEM_CHARSET, 0, 0, 0, 0, "System");
				SelectObject(hdc, hfnt);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(rand() % 50 + 205, 0, rand() % 50 + 205));
				TextOutA(hdc, rand() % w, rand() % h, lpszStrings[t], strlen(lpszStrings[t]));
				Sleep(10);
			}
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI AlphaStretch(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (true) {
			HBITMAP hbit = CreateDiscardableBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 127, AC_SRC_ALPHA};
			StretchBlt(mdc, -20, 20, w + 40, h - 40, hdc, 0, 0, w, h, SRCCOPY);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI AngleGlide(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0);
		while (true) {
			HWND hwnd = GetDesktopWindow();
			RECT rc;
			GetWindowRect(hwnd, &rc);
			POINT lpt[3];
			
			lpt[0].x = rc.left - 50; lpt[0].y = rc.top;
			lpt[1].x = rc.right + 40; lpt[1].y = rc.top;
			lpt[2].x = rc.left; lpt[2].y = rc.bottom;
			
			PlgBlt(hdc, lpt, hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL, 0, 0);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI GrayscaleAnimGradientRect(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			x += increment * signx;
			y += increment * signy;
			TRIVERTEX vtx[2] = {
				// X, Y, RED, GREEN, BLUE, ALPHA //
				{x, y, 0, 0, 0, 0xffff},
				{x + 150, y + 150, 0xffff, 0xffff, 0xffff, 0xffff}
			};
			GRADIENT_RECT rectangle = {0, 1};
			GdiGradientFill(hdc, vtx, 2, &rectangle, 1, GRADIENT_FILL_RECT_V);
			if (x > w) signx = -1;
			if (y > h) signy = -1;
			if (x == 0) signx = 1;
			if (y == 0) signy = 1;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI RainbowStretchWithIcons(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0);
		FLOAT incrementA = 0.f;
		while (true) {
			HBRUSH hbsh = CreateSolidBrush(Hue(incrementA));
			SelectObject(hdc, hbsh);
			StretchBlt(hdc, 0, -20, w, h + 40, hdc, 0, 0, w, h, 0xce646c);
			DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(NULL, IDI_APPLICATION), rand() % 10 * iconX, rand() % 10 * iconY, 0, NULL, DI_NORMAL);
			incrementA++;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI TintScreenBounce(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0);
		FLOAT angle = 0.0;
		FLOAT incrementA = 0.0;
		while (true) {
			INT lx = cos(angle) * 10, ly = tan(angle) * 15;
			HBRUSH hbsh = CreateSolidBrush(Hue(incrementA));
			SelectObject(hdc, hbsh);
			StretchBlt(hdc, lx, ly, w, h, hdc, 0, 0, w, h, 0xcff008);
			angle += M_PI / 8;
			incrementA++;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI RGBPlasma(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		INT t = 0;
		while (true) {
			BITMAPINFO bi = {sizeof(bi), w, h, 1, 32, BI_RGB};
			RGBQUAD *rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (PHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			for (INT x = 0; x < w; x++) {
				for (INT y = 0; y < h; y++) {
					//INT cx = x - (w / 2), cy = y - (h / 2); Why?
					INT plasma = (INT)(128.f + (128.f * sin((x) / 64.f)) + 128.f + (128.f * sin((y) / 48.f)));
					INT index = y * w + x;
					rgbquad[index].rgbRed = (rgbquad[index].rgbRed / 5) + plasma;
					rgbquad[index].rgbGreen = plasma;
					rgbquad[index].rgbBlue = plasma;
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI RectangleCurRadius(LPVOID pvoid)
	{ 
		HDC hdc = GetDC(0);
		FLOAT diameter = 0.f;
		FLOAT incrementA = 0.f;
		while (true) {
			POINT cpt;
			GetCursorPos(&cpt);
			INT lx = cos(diameter) * 50, ly = sin(diameter) * 50;
			INT curx = lx + cpt.x, cury = ly + cpt.y;
			HBRUSH hbsh = CreateSolidBrush(Hue(incrementA));
			SelectObject(hdc, hbsh);
			Rectangle(hdc, curx + 15, cury + 15, curx - 15, cury - 15);
			Rectangle(hdc, curx - 100 + 15, cury - 100 + 15, curx - 100 - 15, cury - 100 - 15);
			incrementA++;
			diameter += 0.1;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI XORHSL(LPVOID pvoid)
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
					int HslPreset = (int)((t^4)^((x^y)/4));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+y/h*0.2f, 1.f);
					hsl.s = 1.f;
					hsl.l = .5f;
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI RandomCircles(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			INT rndrgb = rand() % 255;
			INT rndsize = rand() % 100 + 50;
			INT rw = rand() % w, rh = rand() % h;
			HRGN rgn = CreateEllipticRgn(rw, rh, rw + rndsize, rh + rndsize);
			SelectClipRgn(hdc, rgn);
			HBRUSH hbsh = CreateSolidBrush(RGB(rndrgb, rndrgb, rndrgb));
			SelectObject(hdc, hbsh);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
			Sleep(10);
		}
		return 0;
	}
	
	DWORD WINAPI StretchTangent(LPVOID pvoid)
	{
		HDC hdc = GetDC(0);
		while (true) {
			SetStretchBltMode(hdc, STRETCH_DELETESCANS);
			for (FLOAT angle = 0.f; angle < 361.f; angle++) {
				INT lx = 25 * cos(angle * M_PI / 20), ly = 25 * tan(angle * M_PI / 20);
				StretchBlt(hdc, lx / 2, ly / 2, w - lx, h - ly, hdc, 0, 0, w, h, SRCCOPY);
				Sleep(10);
			}
		}
		ReleaseDC(0, hdc);
	}
	
	DWORD WINAPI LastRGBShader(LPVOID pvoid)
	{
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		while (true) {
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bi = {sizeof(bi), wx, hx, 1, 32, BI_RGB};
			RGBQUAD *rgbquad;
			HBITMAP hbit = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (PHANDLE)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT t = 0; t < wx * hx; t++) {
				rgbquad[t].rgbRed += rand();
				rgbquad[t].rgbGreen = t;
				rgbquad[t].rgbBlue = t;
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	}
}
