#include <windows.h>
#include <cmath>
#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(z, a) ((z)>(a)?(z):(a))

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
	
	float minr = MIN(MIN(fr, fg), fb), maxr = MAX(MAX(fr, fg), fb); // I fixed this part since that's what made the HSL so opaque!
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

int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

int main() {
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
				int HslPreset = (int)((t*4)+(t^4)*sqrt(x+y));
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
