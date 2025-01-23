#include "main.h"

DWORD WINAPI wef2(LPVOID lpParam)
{
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
 
    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
 
        for (int i = 0; i < size; i+=100)
        {
            ci(x-i/2, y-i/2, i, i);
            Sleep(25);
        }
    }
}

DWORD WINAPI glitch(LPVOID lpParam)
{
    HWND v3; 
    HBITMAP h; 
    HDC hdcSrc; 
    HDC hdc; 
    void* lpvBits;
    int nHeight; 
    int nWidth; 
    DWORD v12; 
    int j; 
    int v14; 
    int i; 
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, NOTSRCCOPY);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xcc00200u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}

DWORD WINAPI shader(LPVOID lpParam)
{
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RedrawCounter, 0, 0, 0);
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    int rx;
    for (int i = 0;; i++) {
        SeedXorshift32(__rdtsc());
        desk = GetDC(0);
        rx = xorshift32() % sw;
        int ry = xorshift32() % sh;
        SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, 0x1900ac010e);
        BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, 0xcc00200);
        BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, SRCCOPY);
        BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, 0x1900ac010e);
        Sleep(1);
    }
}

DWORD WINAPI plgblt(LPVOID lpParam)
{
    HDC desk = GetDC(0);
    int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrM = GetSystemMetrics(SM_CYSCREEN);

    POINT wPt[3];
    RECT wRect;

    while (true)
    {
        HDC desk = GetDC(0);
        GetWindowRect(GetDesktopWindow(), &wRect);

        int c = 10;

        wPt[0].x = wRect.left + rand() % 35 - 5;
        wPt[0].y = wRect.top + rand() % 24 - 10;


        wPt[1].x = wRect.right + rand() % 59 - 11;
        wPt[1].y = wRect.top + rand() % 78 - rand () % 20;


        wPt[2].x = wRect.left + c - rand() % 140 - c;
        wPt[2].y = wRect.bottom - c + rand() % 21 - c;


        PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);

        Sleep(2);

    }

    return 0;

}

DWORD WINAPI bruh(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 250, rand() % 250, w, h, hdc, rand() % 40, rand() % 222, SRCINVERT);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI text(LPVOID lptxt)
 {
    int x = GetSystemMetrics(0);
        int y = GetSystemMetrics(1);
    LPCSTR text = 0;
    while (1)
    {
        HDC hdc = GetDC(0);
        SetBkMode(hdc, 0);
        text = "Beryllium.R has taken over your PC";
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(15, 15, 0, rand () % 360, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "System");
        SelectObject(hdc, font);
        TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
        Sleep(100);
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}

VOID WINAPI audio1() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(4*t&t>>8);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI audio2() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(2*t*(43&t>>9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI audio3() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*t>>(t/32));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI audio4() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t^t>>t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI audio5() {
	HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*rand());

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main () {
	if (MessageBoxW(NULL, L"This is a GDI only, Run?", L"Beryllium.R.exe (PRIVATE)", MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL) == IDNO)
	{
		return 0;
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It has flashing lights - NOT for epilepsy", L"Beeeeeeeeeeeeeeeeeeeee", MB_YESNO | MB_ICONWARNING | MB_SYSTEMMODAL) == IDNO)
		{
			return 0;
		}
		else
		{
			HANDLE payload1 = CreateThread(0, 0, wef2, 0, 0, 0);
			audio1();
			Sleep(30000);
			Thrkl(payload1);
			Rfrsh();
			HANDLE payload2 = CreateThread(0, 0, glitch, 0, 0, 0);
			audio2();
			Sleep(30000);
			Thrkl(payload2);
			Rfrsh();
			HANDLE payload3 = CreateThread(0, 0, shader, 0, 0, 0);
			audio3();
			Sleep(30000);
			HANDLE payload3b = CreateThread(0, 0, plgblt, 0, 0, 0);
			audio4();
			Sleep(30000);
			Thrkl(payload3);
			Thrkl(payload3b);
			Rfrsh();
			HANDLE payload4 = CreateThread(0, 0, bruh, 0, 0, 0);
			audio5();
			Sleep(5000);
			HANDLE payload4b = CreateThread(0, 0, wef2, 0, 0, 0);
			Sleep(5000);
			HANDLE payload4c = CreateThread(0, 0, text, 0, 0, 0);
			Sleep(25000);
			InvalidateRect(0, 0, 0);
			ExitProcess(0);
		}
	}
}
