namespace GDIEffects
{
	DWORD __stdcall Payload1(LPVOID lpvd)
	{ 
	HDC hdc;
	int sw, sh;
	HPEN h;
	HBRUSH hbr;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		h = CreatePen(PS_SOLID, 8, PALETTERGB(rand () % 190, rand () % 190, rand () % 190));
		hbr = CreateSolidBrush(PALETTERGB(rand () % 255, rand () % 255, rand () % 255));
		POINT polyline[4] = {{rand () % sw, rand () % sh}, {rand () % sw, rand () % sh}, {rand () % sw, rand () % sh}};
		SelectObject(hdc, h); SelectObject(hdc, hbr);
		BitBlt(hdc, 0, 0, rand () % sw, sh, hdc, (rand () % 50) - 25, sh, NOTSRCCOPY);
		PatBlt(hdc, 1, 0, sw, sh, PATINVERT);
		Polyline(hdc, polyline, 4);
		DeleteObject(h); DeleteObject(hbr);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

COLORREF GetRandomRainbowSpectrum() {
    int color = rand () % 7;
    if (color == 0) {
        return RGB(255, 0, 0);
    }
    if (color == 1) {
        return RGB(255, 150, 0);
    }
    if (color == 2) {
        return RGB(255, 255, 0);
    }
    if (color == 3) {
        return RGB(0, 255, 0);
    }
    if (color == 4) {
        return RGB(0, 255, 255);
    }
    if (color == 5) {
        return RGB(0, 0, 255);
    }
    if (color == 6) {
        return RGB(255, 0, 255);
    }
} // my own code

	DWORD __stdcall Payload2(LPVOID lpvd)
	{
		HDC hdc;
		int sw, sh;
    int rw, rh;
    int tw, th, bw, bh;
    while (1) {
    	hdc = GetDC(NULL);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
        rw = rand () % sw, rh = rand () % sh;
        tw = rw + 0, th = rh + 0, bw = rw + 100, bh = rh + 100;
        HBRUSH paint = CreateSolidBrush(GetRandomRainbowSpectrum());
        SelectObject(hdc, paint);
        PaintRgn(hdc, CreateRectRgn(tw, th, bw, bh));
        StretchBlt(hdc, -10, -10, sw + 20, sh + 20, hdc, 0, 0, sw, sh, SRCINVERT);
        StretchBlt(hdc, 10, 10, sw - 20, sh - 20, hdc, 0, 0, sw, sh, SRCINVERT);
        DeleteObject(paint);
        Sleep(10);
    }
}

    DWORD __stdcall GaussianBlur(LPVOID lpvd)
    {
	HDC hdc, hcopy;
	int sw, sh;
	BITMAPINFO bmp = { 0 };
	BLENDFUNCTION blend;
	double angle = 0.0;
	while (1) {
		hdc = GetDC(NULL), hcopy = CreateCompatibleDC(hdc);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
		bmp.bmiHeader.biBitCount = 32;
		bmp.bmiHeader.biPlanes = 1;
		bmp.bmiHeader.biWidth = sw;
		bmp.bmiHeader.biHeight = sh;
		bmp.bmiHeader.biCompression = BI_RGB;
		HBITMAP hbmp = CreateDIBSection(hdc, &bmp, 0, 0, NULL, 0);
		SelectObject(hcopy, hbmp);
				blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.AlphaFormat = 0;
		blend.SourceConstantAlpha = 10;
		BitBlt(hcopy, (int)(cos(angle) * 10), (int)(sin(angle) * 10), sw, sh, hdc, 0, 0, SRCCOPY);
		angle += M_PI / 8;
		AlphaBlend(hdc, 0, 0, sw, sh, hcopy, 0, 0, sw, sh, blend);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall Icons(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		LPCSTR lpIcons[] = {
		IDI_ERROR, IDI_QUESTION, IDI_APPLICATION, IDI_ASTERISK, IDI_WARNING
		};
		int IconCount = rand () % 5;
		DrawIconEx(hdc, rand () % sw, rand () % sh, LoadIconA(NULL, lpIcons[IconCount]), (rand () % 5 + 1)  * GetSystemMetrics(SM_CXICON), (rand () % 5 + 1) * GetSystemMetrics(SM_CYICON), NULL, NULL, DI_NORMAL);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall Texts(LPVOID lpvd)
	{
	HDC hdc;
	HFONT hfnt;
	int sw, sh;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hfnt = CreateFont(rand () % 50, rand () % 50, 0, 0, FW_EXTRALIGHT, true, false, false, ANSI_CHARSET, 0, 0, 0, 0, "Arial");
		LPCSTR lpSystemStrings[] = {
		"shell32.dll", "imageres.dll", "moricons.dll", "ci.dll", "hal.dll", "logonui.exe", "winlogon.exe", "explorer.exe", "taskkill.exe", "services.msu", "taskmgr.exe", "cmmon32.exe", "rundll32.exe", "autoexec.bat"
		};
		int SystemStringCount = rand () % 13;
		SelectObject(hdc, hfnt);
		SetTextColor(hdc, GetRandomRainbowSpectrum());
		SetBkMode(hdc, 0);
		TextOut(hdc, rand () % sw, rand () % sh, lpSystemStrings[SystemStringCount], strlen(lpSystemStrings[SystemStringCount]));
		DeleteObject(hfnt);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall BitBltMadness(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		BitBlt(hdc, rand () % 4, -4, sw, sh, hdc, 0, 0, SRCERASE);
		BitBlt(hdc, 5, -5, sw, sh, hdc, 0, 0, SRCINVERT);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall InvertShake(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	while (1) {
		hdc = GetDC(NULL);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		SelectObject(hdc, CreateSolidBrush(PALETTERGB(0, 255, 0)));
		BitBlt(hdc, rand () % 10, rand () % 10, sw, sh, hdc, rand () % 10, rand () % 10, NOTSRCCOPY);
		PatBlt(hdc, 0, 0, sw, sh, PATINVERT);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall icoPayload(LPVOID lpvd)
	{
	HDC hdc, mhdc;
	int sw, sh;
	BITMAPINFO bmp = { 0 };
	BLENDFUNCTION blend = { 0 };
	while (1) {
		hdc = GetDC(0), mhdc = CreateCompatibleDC(hdc);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		LPCSTR lpIcons[] = {
		IDI_APPLICATION, IDI_QUESTION
		};
		bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
		bmp.bmiHeader.biBitCount = 32;
		bmp.bmiHeader.biPlanes = 1;
		bmp.bmiHeader.biWidth = sw;
		bmp.bmiHeader.biHeight = sh;
		bmp.bmiHeader.biCompression = BI_RGB;
		HBITMAP hbmp = CreateDIBSection(hdc, &bmp, 0, 0, NULL, 0);
		SelectObject(mhdc, hbmp);
		int icon = rand () % 2;
		blend.BlendOp = AC_SRC_OVER;
		blend.SourceConstantAlpha = 10;
		DrawIcon(hdc, rand () % sw, rand () % sh, LoadIconA(NULL, lpIcons[icon]));
		StretchBlt(mhdc, 0, -20, sw, sh + 40, hdc, 0, 0, sw, sh, SRCCOPY);
		AlphaBlend(hdc, 0, 0, sw, sh, mhdc, 0, 0, sw, sh, blend);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall NeonVision(LPVOID lpvd)
	{
	HDC hdc, mhdc;
	int sw, sh;
	BITMAPINFO bmp = { 0 };
	BLENDFUNCTION blend = { 0 };
	while (1) {
		hdc = GetDC(0), mhdc = CreateCompatibleDC(hdc);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
		bmp.bmiHeader.biBitCount = 32;
		bmp.bmiHeader.biPlanes = 1;
		bmp.bmiHeader.biWidth = sw;
		bmp.bmiHeader.biHeight = sh;
		bmp.bmiHeader.biCompression = BI_RGB;
		HBITMAP hbmp = CreateDIBSection(hdc, &bmp, 0, 0, NULL, 0);
		SelectObject(mhdc, hbmp);
//		int icon = rand () % 2;
		blend.BlendOp = AC_SRC_OVER;
		blend.SourceConstantAlpha = 10;
		SelectObject(mhdc, CreateSolidBrush(PALETTERGB(0, 255, 0)));
		PatBlt(mhdc, 0, 0, sw, sh, PATCOPY);
		AlphaBlend(hdc, 0, 0, sw, sh, mhdc, 0, 0, sw, sh, blend);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall Texts2(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	HFONT hfnt;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hfnt = CreateFont(40, 20, 0, 0, FW_BOLD, false, false, true, ANSI_CHARSET, 0, 0, 0, 0, "Arial");
		LPCSTR lpTexts[] = {
		"avif", "IT\'S ALL COMING DOWN!!", "THERE IS NO MERCY!!!", "SAY BYE TO YOUR COMPUTER!!!", "Tubercomiosis"
		};
		int Texts = rand () % 5;
		SelectObject(hdc, hfnt);
		SetTextColor(hdc, PALETTERGB(rand () % 255, rand () % 255, rand () % 255));
		SetBkMode(hdc, 0);
		TextOut(hdc, rand () % sw, rand () % sh, lpTexts[Texts], strlen(lpTexts[Texts]));
		DeleteObject(hfnt);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall TextRGBMash(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	HFONT hfnt;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hfnt = CreateFont(rand () % 59 + 1, rand () % 39 + 1, 0, 0, FW_EXTRALIGHT, false, false, false, ANSI_CHARSET, 0, 0, 0, 0, "Comic Sans MS");
		LPCSTR lpString = "avif";
		SelectObject(hdc, hfnt);
		SetTextColor(hdc, PALETTERGB(rand () % 239, rand () % 239, rand () % 239));
		SetBkMode(hdc, 0);
		TextOut(hdc, rand () % sw, rand () % sh, lpString, strlen(lpString));
		SelectObject(hdc, CreateSolidBrush(PALETTERGB(rand () % 255, rand () % 255, rand () % 255)));
		BitBlt(hdc, rand () % 7, rand () % 7, rand () % sw, rand () % sh, hdc, rand () % 5, rand () % 5, 0x1900ac010e);
		DeleteObject(hfnt);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall ProfectPayload(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	HBRUSH hpat;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hpat = CreateSolidBrush(GetRandomRainbowSpectrum());
		BitBlt(hdc, -30, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, sw - 30, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, -30, sw, sh, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, sh - 30, sw, sh, hdc, 0, 0, SRCCOPY);
		SelectObject(hdc, hpat);
		PatBlt(hdc, 0, 0, sw, sh, PATINVERT);
		DeleteObject(hpat);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}

	DWORD __stdcall tifShaking(LPVOID lpvd)
	{
    HDC hdc;
    int sw, sh;
    double angle = 0.0;
    int xadd, yadd; // x angle and y angle
    while (1) {
        hdc = GetDC(NULL);
        sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
        xadd = cos(angle) * 10, yadd = sin(angle) * 10;
        BitBlt(hdc, xadd, yadd, sw, sh, hdc, 0, 0, SRCCOPY);
        angle += M_PI / 8;
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

	DWORD __stdcall SlowPat(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	HBRUSH hpat;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hpat = CreateSolidBrush(GetRandomRainbowSpectrum());
		SelectObject(hdc, hpat);
		PatBlt(hdc, 0, 0, sw, sh, PATINVERT);
		DeleteObject(hpat);
		ReleaseDC(NULL, hdc);
		Sleep(500);
	}
}

	DWORD __stdcall PolyMash(LPVOID lpvd)
	{
	HDC hdc;
	int sw, sh;
	HBRUSH hfill;
	while (1) {
		hdc = GetDC(0);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		hfill = CreateSolidBrush(GetRandomRainbowSpectrum());
		POINT vertice[] = {
		{rand () % sw, rand () % sh},
		{rand () % sw, rand () % sh},
		{rand () % sw, rand () % sh}
		};
		SelectObject(hdc, hfill);
		Polygon(hdc, vertice, sizeof(vertice) / sizeof(vertice[0]));
		StretchBlt(hdc, -5, -5, sw + 10, sh + 10, hdc, 0, 0, sw, sh, SRCPAINT);
		StretchBlt(hdc, 5, 5, sw - 10, sh - 10, hdc, 0, 0, sw, sh, SRCPAINT);
		BitBlt(hdc, rand () % 5, rand () % 5, rand () % sw, rand () % sh, hdc, rand () % 5, rand () % 5, SRCCOPY);
		DeleteObject(hfill);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}
}
