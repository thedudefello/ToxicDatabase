#include <windows.h>

#define DA_ELLIPSE 0
#define DA_RECT 1
#define DA_ROUNDRECT 2
#define _c(ar) (sizeof(ar)/sizeof(ar[0]))

typedef struct {
	float x;
	float y;
	float z;
} POINT3D, *PPOINT3D;

INT WINAPI DrawAt(HDC hdc, int xDest, int yDest, int size, int rounds, DWORD dwShapeType) {
	if (dwShapeType == 0) Ellipse(hdc, xDest - size, yDest - size, xDest + size, yDest + size);
	if (dwShapeType == 1) Rectangle(hdc, xDest - size, yDest - size, xDest + size, yDest + size);
	if (dwShapeType == 2) RoundRect(hdc, xDest - size, yDest - size, xDest + size, yDest + size, rounds, rounds);
} 

INT WINAPI DrawIconAt(HDC hdc, int xDest, int yDest, HICON hic) {
	DrawIcon(hdc, xDest, yDest, hic);
}

double Sine(double amp, double freq, double phase, double per) {
	return amp * sin(2 * M_PI * freq * phase / per);
}

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
	
	float minr = __min(__min(fr, fg), fb), maxr = __max(__max(fr, fg), fb); // I fixed this part since that's what made the HSL so opaque!
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
		DrawAt(hdc, sx, sy, 20, 0, DA_RECT);
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
int xincrement = 2;
float x = 10, y = 10;
int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
int xw = GetSystemMetrics(SM_CXICON), xh = GetSystemMetrics(SM_CYICON);

namespace GDI {
	DWORD WINAPI Cube3D(LPVOID pvoid)
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
			HBRUSH hbsh = CreateSolidBrush(HSV(incrementA));
			HPEN hp = CreatePen(PS_SOLID, 20, HSV(incrementA));
			SelectObject(hdc, hbsh);
			SelectObject(hdc, hp);
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
	
	DWORD WINAPI ScreenShake(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, w, h, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI InitialPixelation(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			int wx = w/16, hx = h/16;
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			SetStretchBltMode(hdc, STRETCH_DELETESCANS);
			SetStretchBltMode(mdc, STRETCH_DELETESCANS);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 15, 0};
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, ftn);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI GlideZoomer(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			StretchBlt(hdc, -5, -5, w+20, h+20, hdc, 10, 0, rand() % w, h, SRCPAINT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI CursorDraw(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			POINT cpt;
			GetCursorPos(&cpt);
			DrawIconEx(hdc, cpt.x - xw, cpt.y - xh, LoadCursorA(NULL, IDC_ARROW), 3 * xw, 3 * xh, 0, NULL, DI_NORMAL);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI AlphaSquares(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 10, 0};
			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(mdc, hbit);
			int fw = rand() % w, fh = rand() % h;
			BitBlt(mdc, fw, fh, 200, 300, hdc, fw + rand() % 50, fh + rand() % 50, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI ChemicalTextOuts(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			LPCSTR lpArray[] = {
				"Nitrite", "Radioactivity", "Toxicity", "Poison", "Acid",
				"Solid", "Liquid", "Gas", "Noble gas", "Atom", "Chemical",
				"Compound", "Element", "Alkaline", "Alkali"
			};
			int count = rand() % _countof(lpArray);
			HFONT hfnt = CreateFontW(60, 30, rand() % 60, 0, FW_MEDIUM, false, false, false, ANSI_CHARSET, 0, 0, 0, 0, L"Lucida Console");
			SelectObject(hdc, hfnt);
			SetBkColor(hdc, RGB(rand() % 256, rand() % 256, rand() % 256));
			//SetTextColor(hdc, RGB(255, 255, 255));
			TextOutA(hdc, rand() % w, rand() % h, lpArray[count], strlen(lpArray[count]));
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI KaleidoscopeEffect(LPVOID pvoid) {
		while (true) {
			HDC hdc = GetDC(0);
			// SetStretchBltMode(hdc, STRETCH_HALFTONE); Why?
			StretchBlt(hdc, 0, 0, w, h, hdc, w/2, 0, -w, h, SRCCOPY);
			StretchBlt(hdc, w/2, 0, -w, h, hdc, 0, 0, w, h, NOTSRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, SRCCOPY);
			StretchBlt(hdc, 0, h/2, w, -h, hdc, 0, 0, w, h, NOTSRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI SustainEpicEffectYetAgain(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateSolidBrush(PALETTERGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(hdc, hbsh);
			BitBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, SRCCOPY);
			StretchBlt(hdc, -4, -4, w+8, h+8, hdc, 0, 0, w, h, SRCPAINT);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI WaveEffect(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int phase = rand() % 10 - 5;
			int t = 0;
			for (int y = 0; y < h; ++y) {
				int sine = Sine(5, y + t * 4, phase, w+h);
				BitBlt(hdc, 0, y, w - sine, 1, hdc, sine, y, SRCCOPY);
				t++;
			}
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI Darkening(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0);
			int fw = rand() % w, fh = rand() % h;
			StretchBlt(hdc, rand() % 15, rand() % 15, w, h, hdc, rand() % 15, rand() % 15, w, h, SRCAND);
			BitBlt(hdc, fw, rand() % 20 - 10, 100, h, hdc, fw, 0, SRCPAINT);
			BitBlt(hdc, rand() % 20 - 10, fh, w, 100, hdc, 0, fh, SRCPAINT);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI XORRotozoomer(LPVOID pvoid)
	{
		float angle = 0.0f;
			int t = 0;
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			int wx = w/8, hx = h/8;
			LPRGBQUAD rgbquad;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			SetStretchBltMode(hdc, STRETCH_DELETESCANS);
			SetStretchBltMode(mdc, STRETCH_DELETESCANS);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (int x = 0; x < wx; x++) {
				for (int y = 0; y < hx; y++) {
					int cx = abs(x - (w / 2)), cy = abs(y - (h / 2));
					int rX = cos(angle) * cx - sin(angle) * cy,
					rY = sin(angle) * cx + cos(angle) * cy;
					int rgb = (rX+t)&(rY+t);
					int index = y * wx + x;
					rgbquad[index].rgbRed = rgb;
					rgbquad[index].rgbGreen = rgb;
				}
			}
			t++;
			angle += 0.01f;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
	//		ReleaseDC(0, hdc);
			Sleep(10);
		}
	//	return 0;
	}
	
	DWORD WINAPI ANDRotozoomer(LPVOID pvoid)
	{
		float angle = 0.0f;
			int t = 0;
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			int wx = w/8, hx = h/8;
			LPRGBQUAD rgbquad;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (int x = 0; x < wx; x++) {
				for (int y = 0; y < hx; y++) {
					int cx = abs(x - (wx / 2)), cy = abs(y - (hx / 2));
					int rX = log2(angle) * cx - sin(angle) * cy,
					rY = sin(angle) * cx + log(angle) * cy;
					int rgb = (rX+t)&(rY+t);
					int index = y * wx + x;
					rgbquad[index].rgbRed += rgb;
					rgbquad[index].rgbGreen += rgb;
					rgbquad[index].rgbBlue += rgb;
				}
			}
			t++;
			angle += 0.01f;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
	//		ReleaseDC(0, hdc);
			Sleep(10);
		}
	//	return 0;
	}
	
	DWORD WINAPI StaticNoise(LPVOID pvoid)
	{
		while (true) {
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			int wx = w/4, hx = h/4;
			LPRGBQUAD rgbquad;
			BITMAPINFO bmp = {sizeof(bmp), wx, hx, 1, 32, BI_RGB};
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
			SelectObject(mdc, hbit);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (int t = 0; t < wx * hx; t++) {
				rgbquad[t].rgbRed = rand();
				rgbquad[t].rgbGreen = rand();
				rgbquad[t].rgbBlue = rand();
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI WindowText(LPVOID pvoid)
	{
		LPCSTR lpFonts[] = {
			"Arial", "Verdana", "Tahoma", "Trebuchet MS",
			"Comic Sans MS", "MV Boli", "Wingdings", "Symbol",
			"Roman", "Script", "Microsoft Sans Serif", "Lucida Console",
			"Webdings", "Marlett", "Times New Roman"
		};
		float incrementA = 0.0f;
		float incrementB = 48.0f;
		while (true) {
			HDC hdc = GetDC(0);
			LPCSTR Text = "Nitrite";
			HFONT hfnt = CreateFontA(80, 40, 0, 0, FW_BOLD, false, rand() % 2, rand() % 2, ANSI_CHARSET, 0, 0, 0, 0, lpFonts[rand() % _c(lpFonts)]);
			SelectObject(hdc, hfnt);
		 	x += xincrement * signx;
		 	y += xincrement * signy;
		 	SetBkColor(hdc, HSV(incrementA));
		 	SetTextColor(hdc, HSV(incrementB));
		 	TextOutA(hdc, x, y, Text, strlen(Text));
		 	if (x > w) signx = -1;
		 	if (y > h) signy = -1;
		 	if (x == 0) signx = 1;
		 	if (y == 0) signy = 1;
		 	incrementA += M_PI_2;
		    incrementB += M_PI_2;
		    ReleaseDC(0, hdc);
		    Sleep(10);
		}
	}
	
	DWORD WINAPI PlasmaHSL(LPVOID pvoid)
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
					int HslPreset = (int)((t*4)+((t^4)*sin(x/32))+(t*4)+((t^4)*sin(y/32)));
					mrgbq = rgbq[iIndex];
					hsl = rgbQuadRGB(mrgbq);
					hsl.h = fmod(HslPreset/400.f+y/h*0.2f, 1.f);
					rgbq[iIndex] = hslRGB(hsl);
				}
			}
			t++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
}
