typedef struct IUnknown IUnknown;

#pragma once

#include "Purgatorium.h"

//Store the width and height
int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

//Shake & Warp Pre-Config
int shakeIntensity = 1;
int warpIntensity = 3;

//Wave Pre-Config
int waveDelay = rand() % 30;

//Random Thing Pre-Config
bool random = true;

//Random colors Pre-Config
int colorsdelay = 50;

/*
	Every payload below wasn't organized
	      By order of execution!
*/

namespace GDIPayloads
{
	DWORD WINAPI ScreenShake(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		/*
			Intensity:
			1  - WEAK
			10 - HARD
		*/

		while (1)
		{
			for (int i = 1; i <= shakeIntensity; i++)
			{
				StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
				StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			}

			/*
				+Intensity, +Fast
				-Intensity, -Fast
			*/

			if (shakeIntensity < 10)
			{
				Sleep(rand() % 25);
			}
			else
			{
				Sleep(rand() % 5);
			}

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}

	//COLOR OVERDOSE
	DWORD WINAPI ColorOverdose(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 16;
		int hs = h / 16;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		//Counter variable
		INT i = 0;

		while (1)
		{
			//Create a random color brush
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(dcCopy, hBrush);
			SelectObject(dc, hBrush);

			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCPAINT | PATINVERT);

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int i = rand() % 10;

					rgbquad[index].rgbRed   += i;
					rgbquad[index].rgbGreen += i;
					rgbquad[index].rgbBlue  += i;
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCPAINT | PATINVERT);

			Sleep(rand() % 10);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//XOR ROTOZOOMER
	DWORD WINAPI XORRoto(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		DOUBLE angle = 0.f;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					//CenterX and CenterY
					int cx = (x - (ws / 2));
					int cy = (y - (hs / 2));

					//2D Rotating Matrix
					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;

					//XOR Pattern
					int fx = (zx + i) ^ (zy + i);

					rgbquad[index].rgbRed   += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue  += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 10);
			System::RedrawScreen();

			if (rand() % 25 == 0 && random)
			{
				Sleep(1000);
			}
		}

		return 0x00;
	}
	
	//XOR ABS ROTOZOOMER
	DWORD WINAPI ABSXORRoto(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		DOUBLE angle = 0.f;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					/*
					  Now its the absolute value
					     Like a Kaleidoscope
					*/

					int cx = abs(x - (ws / 2));
					int cy = abs(y - (hs / 2));

					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;

					int fx = (zx + i) ^ (zy + i);

					rgbquad[index].rgbRed   += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue  += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 10);
			System::RedrawScreen();

			if (rand() % 25 == 0 && random)
			{
				Sleep(1000);
			}
		}

		return 0x00;
	}

	//XOR ABS ROTOZOOMER HALFTONE
	DWORD WINAPI HFTNXOR(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		DOUBLE angle = 0.f;

		//Just added a HALFTONE effect
		SetStretchBltMode(dcCopy, HALFTONE);
		SetStretchBltMode(dc, HALFTONE);

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = abs(x - (ws / 2));
					int cy = abs(y - (hs / 2));

					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;

					int fx = (zx + i) ^ (zy + i);

					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 10);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//ALPHABLEND DARK
	DWORD WINAPI InitialBlur(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 8;
		int hs = h / 8;

		BLENDFUNCTION blur = { 0 };
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		//Set our blur
		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 20;

		//Counter variable
		INT i = 0;

		while (1)
		{
			//Random position at the memory
			StretchBlt(dcCopy, rand() % 1, rand() % 1, ws, hs, dc, rand() % -1, rand() % -1, w, h, SRCCOPY);

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					rgbquad[index].rgbRed   += i;
					rgbquad[index].rgbGreen += i;
					rgbquad[index].rgbBlue  += i;
				}
			}

			i++;

			Sleep(rand() % 500);
			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, blur);

			if (rand() % 5 == 0)
			{
				System::RedrawScreen();
			}
		}

		return 0x00;
	}

	//Random Texts
	DWORD WINAPI RandomTexts(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		LOGFONTW lFont = { 0 };

		//Setup our font style
		lFont.lfWidth = 20;
		lFont.lfHeight = 50;
		lFont.lfOrientation = 400;
		lFont.lfWeight = 800;
		lFont.lfUnderline = TRUE;
		lFont.lfQuality = DRAFT_QUALITY;
		lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;

		lstrcpy(lFont.lfFaceName, L"Times New Roman");

		while (true)
		{
			if (rand() % 25 == 24)
			{
				LPCSTR lpStrings[] =
				{
					"Do pills work?", "I don't want live anymore", "Waiting for my end",
					"Everyday is a infinite loop", "My thoughts are killing me", "Kill me",
					"Dissociating", "Fleeing reality", "Am I Real?", "I'am not safe",
					"HELP ME", "cold.", "Transcending", "Anxiety", "Hear the voices",
					"Trapped by illusion", "Full of emptiness", "Dreaming forever",
					"Questioning my existence", "Losing control regressively", "pain",
					"Don't want to suffer anymore", "Panic attacks", "Dark forever",
					"Faking my happiness", "Seeking eternal peace", "Can't breathe", "sad",
					"Existential Crisis", "Viewing shadows", "Beyond the stars", "Alone",
					"Can't kill myself", "What am I", "Made with rotten flesh", "Isolated",
					"Wearing masks", "My final destination", "Hurting myself", "Farewell"
				};

				//Setup the angle
				lFont.lfEscapement = rand() % 60;

				HFONT hFont = CreateFontIndirectW(&lFont);
				SelectObject(dc, hFont);

				//Setup the colors
				SetTextColor(dc, RGB(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF));
				SetBkColor(dc, RGB(rand() % 0xA0, rand() % 0xA0, rand() % 0xA0));

				int index = rand() % 40;

				TextOutA(dc, rand() % w, rand() % h, lpStrings[index], lstrlenA(lpStrings[index]));

				if (rand() % 25 == 24)
				{
					if (rand() % 2 == 0)
					{
						BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x999999);
					}
					else
					{
						BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x666666);
					}
				}

				Sleep(rand() % 5);

				if (rand() % 25 == 24)
				{
					System::RedrawScreen();
				}
			}
		}

		return 0x00;
	}

	//Warp Blocks in Screen
	DWORD WINAPI WarpScreen(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		/*
		  Intensity:
		  3 - WEAK
		  5 - HARD
		*/
		float warpIntensity = 3;

		while (1)
		{
			for (int i = 1; i <= warpIntensity; i++)
			{
				int size = rand() % 400;

				int wsrc = rand() % w;
				int hsrc = rand() % h;

				BitBlt(dc, wsrc + rand() % i, hsrc + rand() % i, size, size, dc, wsrc, hsrc, SRCCOPY);
			}

			Sleep(rand() % 2);

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}

	//Rotating Tesseract
	DWORD WINAPI Tesseract(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		/*
			   Setup the Tesseract's size
			By your screen's width and height
		*/

		float size = (w + h) / 10;

		int cx = size;
		int cy = size;

		int xdv = 10;
		int ydv = 10;

		float angleX = 0.01;
		float angleY = 0.01;
		float angleZ = 0.01;

		int d = 60;

		VERTEX vtx[] =
		{
			//BOTTOM HYPER CUBE
			{size, 0, 0},
			{size, size, 0},
			{0, size, 0},
			{0, 0, 0},

			//TOP HYPER CUBE
			{size, 0, size},
			{size, size, size},
			{0, size, size},
			{0, 0, size},

			//BOTTOM INSIDE HYPER CUBE
			{size - d,  d,      d},
			{size - d,  size - d,  d},
			{d,      size - d,  d},
			{d,      d,      d},

			//TOP INSIDE HYPER CUBE
			{size - d,  d,      size - d},
			{size - d,  size - d,  size - d},
			{d,      size - d,  size - d},
			{d,      d,      size - d}
		};

		//32 EDGES
		EDGE edges[] =
		{
			//BOTTOM HYPER CUBE FACE (0, 1, 2, 3)
			{0, 1},
			{1, 2},
			{2, 3},
			{3, 0},

			//BOTTOM-TOP HYPER CUBE FACE
			{0, 4},
			{1, 5},
			{2, 6},
			{3, 7},

			//TOP HYPER CUBE FACE (4, 5, 6, 7)
			{4, 5},
			{5, 6},
			{6, 7},
			{7, 4},

			//BOTTOM INSIDE HYPER CUBE FACE (8, 9, 10, 11)
			{8,   9},
			{9,  10},
			{10, 11},
			{11,  8},

			//BOTTOM-TOP INSIDE HYPER CUBE FACE
			{8,  12},
			{9,  13},
			{10, 14},
			{11, 15},

			//TOP INSIDE HYPER CUBE FACE (12, 13, 14, 15)
			{12, 13},
			{13, 14},
			{14, 15},
			{15, 12},

			//HYPER CUBE AND INSIDE CONNECTION BOTTOM
			{0,  8},
			{1,  9},
			{2, 10},
			{3, 11},

			//HYPER CUBE AND INSIDE CONNECTION TOP
			{4, 12},
			{5, 13},
			{6, 14},
			{7, 15}
		};

		LPCWSTR icons[] = {IDI_ERROR, IDI_EXCLAMATION, IDI_ASTERISK, IDI_APPLICATION };

		int index = rand() % 4;

		//Calculate the number of vertex and edges
		int totvtx = sizeof(vtx) / sizeof(vtx[0]);
		int totedg = sizeof(edges) / sizeof(edges[0]);

		while (true)
		{
			//Rotate Axis
			for (int i = 0; i < totvtx; i++)
			{
				_3D::RotateX(&vtx[i], angleX);
				_3D::RotateY(&vtx[i], angleY);
				_3D::RotateZ(&vtx[i], angleZ);
			}

			//Draw the edge
			for (int i = 0; i < totedg; i++)
			{
				_3D::DrawEdge(dc, icons[index],
							  vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy, 
					          vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
			}

			Sleep(40);
			if (rand() % 5 == 0) System::RedrawScreen();

			//Moves the tesseract around
			cx += xdv;
			cy += ydv;

			//Right and left collisions
			if (cx > w - (size / 2) || cx < -(size / 2))
			{
				xdv *= -1;
				index = rand() % 4;
			}

			//Top and bottom collisions
			if (cy > h - (size / 2) || cy < -(size / 2))
			{
				ydv *= -1;
				index = rand() % 4;
			}
		}

		return 0x00;
	}

	//Random HSV Ellipses
	DWORD WINAPI RandomEllipses(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;
		
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;

		//semi-major axis and semi-minor axis
		FLOAT a = 5.0;
		FLOAT b = 3.0;

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			//Set a random (x,y) pos
			int randx = rand() % ws;
			int randy = rand() % hs;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = x - randx;
					int cy = y - randy;

					//(x²/a²) + (y²+b²) = 1
					int zx = (cx * cx) / (a * a);
					int zy = (cy * cy) / (b * b);

					//Plasma it
					int fx = 128.0 + (128.0 * sin(sqrt(zx + zy) / 6.0));

					//Convert the screen colors to HSV
					HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

					//Apply the effect from fx+i [0,360]
					hsv.h = fmod(fx + i, 360.0);

					//Return the HSV back to RGB and show it
					rgbquad[index] = Colors::HSVtoRGB(hsv);
				}
			}

			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 1000);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//Custom Waves
	DWORD WINAPI CustomWaves(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);

		int i = 0;

		while (true)
		{
			int waveAmplitude = rand() % 3;
			int wavePhase = rand() % 20;

			if (rand() % 25 == 0)
			{
				for (int y = 0; y < h; y++)
				{
					int zx = Math::SineWave(waveAmplitude, y + i * 4, wavePhase, h);

					BitBlt(dc, 0, y, w - zx, 1, dc, zx, y, SRCCOPY);
				}

				Sleep(1);

				if (rand() % 25 == 0) System::RedrawScreen();

				i++;
			}
		}

		return 0x00;
	}

	//High Frequency Waves
	DWORD WINAPI HighFreqWaves(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);

		int i = 0;

		while (true)
		{
			for (int y = 0; y < h; y++)
			{
				int wavePhase = rand() % 70 - 40;

				int zx = Math::SineWave(5, y + i * 4, wavePhase, h);

				BitBlt(dc, 0, y, w - zx, 1, dc, zx, y, SRCCOPY);
			}

			Sleep(waveDelay);

			i++;
		}

		return 0x00;
	}

	//Center Circle (to put with Tesseract)
	DWORD WINAPI CenterCircle(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 32;

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = x - (ws / 2);
					int cy = y - (hs / 2);

					int zx = (cx * cx);
					int zy = (cy * cy);

					int di = 128.0 + i;

					int fx = di + (di * sin(sqrt(zx + zy) / 32.0));

					HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

					hsv.h = fmod(fx + i, 360.0);

					rgbquad[index] = Colors::HSVtoRGB(hsv);
				}
			}

			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(rand() % 1000);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//HSV Random Inverted Colors
	DWORD WINAPI RandomColors(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 1;
		int hs = h / 1;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			int color = rand() % 360;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

					hsv.h = fmod(color, 360.0);

					rgbquad[index] = Colors::HSVtoRGB(hsv);
				}
			}

			i++;
			
			Sleep(rand() % 1000);

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
			StretchBlt(dc, 0, 0, w, h, dc, 0, 0, w, h, PATINVERT);
			
			Sleep(colorsdelay);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//Normal And Generic Screen Blur
	DWORD WINAPI BlurScreen(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		BLENDFUNCTION blur = { 0 };

		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 10;

		while (1)
		{
			StretchBlt(dcCopy, rand() % 10, rand() % 10, w, h, dc, rand() % -10, rand() % -10, w, h, SRCCOPY);

			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

			if (rand() % 10 == 0)
			{
				Sleep(5);

				System::RedrawScreen();
			}
		}

		return 0x00;
	}

	//Generic Bit Colors
	DWORD WINAPI BitColors(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		SetStretchBltMode(dc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);

		int color = 0;

		bool statementA = true;
		bool statementB = true;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

			int r = rand() % 0xFF;
			int g = rand() % 0xFF;
			int b = rand() % 0xFF;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int noise = rand() % 0xFF;

					noise %= (r * g * b + 1) % (color + 1) + 1;

					rgbquad[index].rgbRed   += noise + r;
					rgbquad[index].rgbGreen += noise + g;
					rgbquad[index].rgbBlue  += noise + b;
				}
			}

			if (statementA)
			{
				color++;

				if (color > 0xAA)
				{
					statementA = false;
					statementB = true;
				}
			}

			if (statementB)
			{
				color--;

				if (color == 0)
				{
					statementA = true;
					statementB = false;
				}
			}

			Sleep(rand() % 500);

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

			Sleep(50);
			System::RedrawScreen();
		}

		return 0x00;
	}

	//SRCPAINT Strips
	DWORD WINAPI ScreenStrips(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		HBITMAP hbmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, hbmp);

		INT x = 0; INT y = 0;

		while (true)
		{
			DWORD rop = SRCPAINT;

			int dx0 = rand() % 20;
			int dx1 = x;

			int dy0 = y;
			int dy1 = rand() % 20;

			int size = 20;

			//Y DISPLACEMENT
			if (rand() % 2 == 0) BitBlt(dc, -dx0, dy0, w, size, dc, dx0, dy0, rop);
			if (rand() % 2 == 0) BitBlt(dc, dx0, dy0, w, size, dc, -dx0, dy0, rop);

			//X DISPLACEMENT
			if (rand() % 2 == 0) BitBlt(dc, dx1, dy1, size, h, dc, dx1, -dy1, rop);
			if (rand() % 2 == 0) BitBlt(dc, dx1, -dy1, size, h, dc, dx1, dy1, rop);

			x += size;
			y += size;

			if (x > w)
			{
				x = 0;

				Sleep(25);
				if (rand() % 5 == 0) System::RedrawScreen();
			}
			if (y > h)
			{
				y = 0;
			}
		}

		return 0x00;
	}

	//Kaleidoscope + Screen Scroller
	DWORD WINAPI Kaleidoscope(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		DWORD rop = SRCCOPY;

		bool statementA = true;
		bool statementB = false;

		int scrollX, scrollY;

		int cw = w / 2;
		int ch = h / 2;

		int limit = 25;

		int i = 0;

		while (1)
		{
			//Put right on left and reflect it with lateral shift
			StretchBlt(dcCopy, 0, 0, w, h, dc, w, 0, -cw, h, rop);
			StretchBlt(dc, 0, 0, cw, h, dcCopy, 0, 0, w, h, rop);
			
			System::RedrawScreen();

			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, rop);

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					int dx = 10;

					//First scroll
					if (statementA)
					{
						scrollX = (x + dx) % w;
						scrollY = (y + dx) % h;
					}

					//Second scroll
					else if (statementB)
					{
						scrollX = (x + dx) % w;
						scrollY = abs(y - dx) % h;
					}

					int srcIndex = scrollY * w + scrollX;

					rgbquad[index] = rgbquad[srcIndex];
				}
			}

			if (statementA)
			{
				i++;

				if (i > limit)
				{
					statementA = false;
					statementB = true;

					System::RedrawScreen();
				}
			}

			else if (statementB)
			{
				i--;

				if (i < 0)
				{
					statementA = true;
					statementB = true;

					System::RedrawScreen();
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, rop);

			//Put top on bottom and reflect it with lateral shift
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, ch, rop);
			StretchBlt(dc, 0, ch, w, ch, dcCopy, 0, h, w, -h, rop);

			Sleep(20);
		}

		return 0x00;
	}

	//Rainbow Circles (to put with Kaleidoscope)
	DWORD WINAPI PaletteCircles(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				//Randow brush
				LOGBRUSH logBrush = { BS_SOLID, RGB(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF) };
				HBRUSH hbrush = CreateBrushIndirect(&logBrush);

				SelectObject(dc, hbrush);

				PatBlt(dc, 0, 0, w, h, PATINVERT);

				//Random (x,y)
				int randx = rand() % w;
				int randy = rand() % h;

				//Radius
				int r = 30;

				Ellipse(dc, randx - r, randy - r, randx + r, randy + r);

				DeleteObject(hbrush);

				Sleep(25);
			}
		}

		return 0x00;
	}

	//Rainbow Noise
	DWORD WINAPI GDIPayloadFINAL(LPVOID lpvd)
	{
		HDC dc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(dc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		int color = 0;

		bool statementA = true;
		bool statementB = true;

		while (1)
		{
			SetStretchBltMode(dc, COLORONCOLOR);
			SetStretchBltMode(dcCopy, COLORONCOLOR);

			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, h, w, 0, SRCCOPY);

			int r = rand() % 0xFF;
			int g = rand() % 0xFF;
			int b = rand() % 0xFF;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					int noise = rand() % 0xFF;

					noise %= (r * g * b + 1) % (color + 1) + 1;

					/*
						   Kinda same from BitColors();
						The difference is that it doesn't
						     Sum the noise to itself
					*/

					rgbquad[index].rgbRed = noise + r;
					rgbquad[index].rgbGreen = noise + g;
					rgbquad[index].rgbBlue = noise + b;
				}
			}

			if (statementA)
			{
				color++;

				if (color > 0xAA)
				{
					statementA = false;
					statementB = true;
				}
			}

			if (statementB)
			{
				color--;

				if (color == 0)
				{
					statementA = true;
					statementB = false;
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		}

		return 0x00;
	}
}