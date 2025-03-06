// COLOUR FUNCTON HEADER //

/* Credits to Venra/Sickdows on this one! */
typedef union _COLORPAL32 {
	COLORREF cp32Colors;
	struct {
		BYTE cp32Blue; // 8 bits
		BYTE cp32Green; // 16 bits
		BYTE cp32Red; // 24 bits
		BYTE cp32Unused; // 32 bits
	};
} COLORPAL32, *LPCOLORPAL32;


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
	
	float minr = fmin(fmin(fr, fg), fb), maxr = fmax(fmax(fr, fg), fb); // I fixed this part since that's what made the HSL so opaque!
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
