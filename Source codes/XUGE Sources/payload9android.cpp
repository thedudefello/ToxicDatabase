#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

HCRYPTPROV prov;
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

POINT mkp(int x, int y) {
	POINT p;
	p.x = x;
	p.y = y;
	return p;
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t + 19) ^ t >> 19 * (t - 8) + t >> 10);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
DWORD WINAPI winmain(LPVOID lpParam) {
	for (int t = 0; ; t++) {
		int n = t % 2 == 0 ? 1 : -1;
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		POINT pos[3];
		pos[0].x = n * 30, pos[0].y = -(n * 30);
		pos[1].x = w + n * 30, pos[1].y = n * 30;
		pos[2].x = -(n * 30), pos[2].y = h - n * 30;
		PlgBlt(hcdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, (t % 20 < 10 ? SRCPAINT : SRCAND));
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteDC(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
	return 0;
}

int main() {
	sound8();
	HANDLE thread1 = CreateThread(0, 0, winmain, 0, 0, 0);
	Sleep(30000);
	return 0;
}