#include <windows.h>
#pragma comment(lib, "winmm.lib")
#define _USE_MATH_DEFINES 1
#include <cmath>
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "msimg32.lib")

#define Wave(i, xSize, ySize) (sin(i / ((float)xSize) * M_PI) * (ySize))
#define SquareWave(t, freq, sampleCount) (int)(((BYTE)(2.f * (FLOAT)(freq) * ((t) / (FLOAT)(sampleCount))) % 2) == 0 ? 1.f : -1.f)
#define TriangleWave(t, freq, sampleCount) (int)(4.f * ( FLOAT )fabs(((FLOAT)(t) / ((FLOAT)(sampleCount) / (FLOAT)(freq))) - floor(((FLOAT)(t) / ((FLOAT)(sampleCount) / (FLOAT)(freq)))) - .5f) - 1.f)
int sch(int v) {
	return (int)(tan(cos(ceil(v >> 10)))) ^ (((int)((99999 * sin(v * M_PI / 180.0) + 99999) / 15) >> 6));
}

static unsigned long xx = 123456789, yy = 362436069, zz = 521288629;
DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
	if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
	HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
	HDC hdc2 = CreateCompatibleDC(hdc); rand() % 6;
	SelectObject(hdc2, screenshot);
	BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
	BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
	BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
	DeleteDC(hdc2); DeleteObject(screenshot);
}
HDC hdcMemory, origHDC; HBITMAP hScreenshot;
VOID WINAPI pixelatehdc(HDC hdc, int w, int h, int power, int stretchmode, DWORD dwRop)
{
	origHDC = hdc; hdcMemory = CreateCompatibleDC(origHDC);
	hScreenshot = CreateCompatibleBitmap(origHDC, w / power, h / power);
	SelectObject(hdcMemory, hScreenshot);
	SetStretchBltMode(hdcMemory, stretchmode);
	StretchBlt(hdcMemory, 0, 0, w / power, h / power, origHDC, 0, 0, w, h, SRCCOPY);
	StretchBlt(origHDC, 0, 0, w, h, hdcMemory, 0, 0, w / power, h / power, dwRop);
}

POINT pt[3]; RECT rekt;
VOID WINAPI rotatehdc(HWND hWnd, HDC hDC, int w, int h, int power) {
	GetWindowRect(hWnd, &rekt);
	pt[0].x = rekt.left + power; pt[0].y = rekt.top - power;
	pt[1].x = rekt.right + power; pt[1].y = rekt.top + power;
	pt[2].x = rekt.left - power; pt[2].y = rekt.bottom - power;
	PlgBlt(hDC, pt, hDC, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
}

COLORREF RndRGB() {
	int clr = xorshift32() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}
VOID WINAPI soundboom()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 24] = {};

	for (DWORD t = 1; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(SquareWave(t, t, t * 999999));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI soundmash()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 24] = {};

	for (DWORD t = 1; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(SquareWave(t, t, t & 999999));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound1()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 24] = {};

	for (DWORD t = 1; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t & t >> t + t << 13 - t << SquareWave(t, t * sin(t), 320000) - t / 2 >> t | t << 100 & t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 32] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t & t >> t + t << 13 - t << SquareWave(t, t * sin(t), 320000) - t / 2 >> t | t << 100 & t) | sch(t));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 32] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((t & t >> t + t << 13 - t << SquareWave(t, t * sin(t), 320000)) - t / 2 >> t | t << 100) & t * (int)log10(t * M_PI / 3373));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 28] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t + t & t % 257) | t - 0x00ac000e ^ t ^ t & 0x34589ac | t ^ t - (t ^ t >> 3 & 0x00e64cd));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[44000 * 22] = {};

	for (DWORD t = 1; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t ^ t >> 9);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 29] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * tanf(t >> 10));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound7()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 31] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * tanf(t >> 8));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int rnm = 0;
int mp(int c, int m, int rn, int rm) {
	if (c > m && c < rm) return rn; else return 0;
}
VOID WINAPI sound8()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((t * t >> 4) / 3) | (t * t >> 3 * 5) | mp(t, 32000 * 11, sch(t), 32000 * 23));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound9()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = { };
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(t);
	}
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound10()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t) {
		buffer[t] = static_cast<char>(SquareWave(t, t, (t >> 8 & t >> 13) * 999999));
	}
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI soundfinal()
{
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};

	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((int)(tan(t >> 8) * t) & 100));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

DWORD WINAPI glchart(LPVOID lpParam) {
	int ticks = GetTickCount(), w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	SeedXorshift32(__rdtsc());
	for (int i = 1;; i++, i %= 21) {
		if (!i) for (int c = 0; c < 100; c++) InvalidateRect(0, 0, 0);
		HDC hdc = GetDC(0), hdcMem = CreateCompatibleDC(hdc); HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm); BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0; BYTE bt = 0;
		if ((GetTickCount() - ticks) > 60000) bt = 2 + xorshift32() & 0xff;
		for (int i = 1; w * h > i; i++) {
			if (i % h == 0 && xorshift32() % 100 == 0) v = 3 + xorshift32() % 50;
			((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + bt))[bt] ^ i;
		}
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		Sleep(90);
	}
}
DWORD WINAPI shk(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SelectObject(desk, CreateSolidBrush(RGB(245, 245, 66)));
		for (int angle = 0; angle < 361; angle++) {
			int x = 100 * cos(angle * M_PI / 180.F), y = 100 * sin(angle * M_PI / 180.F);
			train(desk, sw, sh, x, y, SRCCOPY ^ 0x2021e20);
			Sleep(0.5);
		}
	}
}
DWORD WINAPI pl2(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	SeedXorshift32(__rdtsc());
	while (1) {
		SelectObject(desk, CreateSolidBrush(RndRGB()));
		BitBlt(desk, 0, 0, sw, sh, desk, 0, 0, rand() % 2 ? PATINVERT : NOTSRCCOPY ^ PATCOPY);
		Sleep(349);
	}
}
DWORD WINAPI pxl(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	SeedXorshift32(__rdtsc());
	while (true) {
		pixelatehdc(desk, sw, sh, 8.4, STRETCH_DELETESCANS, SRCCOPY);
		DeleteDC(origHDC); DeleteDC(hdcMemory); DeleteObject(hScreenshot);
		Sleep(605);
	}
}
DWORD WINAPI rtscr(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	SeedXorshift32(__rdtsc());
	while (1) {
		int v = xorshift32() % 3;
		if (v == 0) { StretchBlt(desk, 0, 0, sw, sh, desk, sw, 0, -sw, sh, SRCCOPY); }
		if (v == 1) { StretchBlt(desk, 0, 0, sw, sh, desk, 0, sh, sw, -sh, SRCCOPY); }
		if (v == 2) { StretchBlt(desk, 0, 0, sw, sh, desk, sw, sh, -sw, -sh, SRCCOPY); }
		Sleep(100);
	}
}
DWORD WINAPI hrwvs(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sh / 11, ySize = 8, power = 43, dw = SRCCOPY, delay = 6;
	SeedXorshift32(__rdtsc());
	while (1) {
		HDC hdcMem = CreateCompatibleDC(desk); HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(hdcMem, screenshot); BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < power; i++) {
			for (int i = 0; i < sh + 5; i++) {
				int wave = sin(i / ((float)xSize) * M_PI) * (ySize); BitBlt(hdcMem, 0, i, sw, 1, desk, wave, i, dw);
			} BitBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY); Sleep(delay);
		}
		for (int i = 0; i < power; i++) {
			for (int i = 0; i < sh + 5; i++) {
				int wave = sin(i / ((float)xSize) * M_PI) * (ySize); BitBlt(hdcMem, 0, i, sw, 1, desk, -wave, i, dw);
			}BitBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY); Sleep(delay);
		}
		for (int i = 0; i < power; i++) {
			for (int i = 0; i < sh + 5; i++) {
				int wave = sin(i / ((float)xSize) * M_PI) * (ySize); BitBlt(hdcMem, 0, i, sw, 1, desk, -wave, i, dw);
			}BitBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY); Sleep(delay);
		}
		for (int i = 0; i < power; i++) {
			for (int i = 0; i < sh + 5; i++) {
				int wave = sin(i / ((float)xSize) * M_PI) * (ySize); BitBlt(hdcMem, 0, i, sw, 1, desk, wave, i, dw);
			}BitBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY); Sleep(delay);
		}
	}
}
DWORD WINAPI shd(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	SeedXorshift32(__rdtsc());
	while (1) {
		for (int r = 18; r < 256; r++) {
			SelectObject(desk, CreateSolidBrush(RGB(r, 0, 0)));
			BitBlt(desk, 0, 0, sw, sh, desk, xorshift32() % 3 - 1, xorshift32() % 3 - 1, SRCCOPY | 0x00ac000e); Sleep(1);
		}
		for (int c = 0; c < 11; c++) InvalidateRect(0, 0, 0);

		for (int g = 18; g < 256; g++) {
			SelectObject(desk, CreateSolidBrush(RGB(0, g, 0)));
			BitBlt(desk, 0, 0, sw, sh, desk, xorshift32() % 3 - 1, xorshift32() % 3 - 1, SRCCOPY | 0x00ac000e); Sleep(1);
		}
		for (int c = 0; c < 11; c++) InvalidateRect(0, 0, 0);

		for (int b = 18; b < 256; b++) {
			SelectObject(desk, CreateSolidBrush(RGB(0, 0, b)));
			BitBlt(desk, 0, 0, sw, sh, desk, xorshift32() % 3 - 1, xorshift32() % 3 - 1, SRCCOPY | 0x00ac000e); Sleep(1);
		}
		for (int c = 0; c < 11; c++) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI invcc(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 100, radius = 227;
	SeedXorshift32(__rdtsc());
	while (1) {
		int origX1 = xorshift32() % sw, origY1 = xorshift32() % sh;
		int origX2 = -20 + xorshift32() % (sw + 20), origY2 = -20 + xorshift32() % (sh + 20);
		int origX3 = -30 + xorshift32() % (sw + 30), origY3 = -30 + xorshift32() % (sh + 30);
		int origX4 = -20 + xorshift32() % (sw + 20), origY4 = -20 + xorshift32() % (sh + 20);
		int origX5 = xorshift32() % sw, origY5 = xorshift32() % sh;
		for (int angle = 0; angle < 1081; angle += 12.1) {
			InvalidateRect(0, 0, 0);
			int x1 = radius * cos(angle * M_PI / 180.0) + origX1, y1 = radius * sin(angle * M_PI / 180.0) + origY1;
			int x2 = radius * cos(angle * M_PI / 180.0) + origX2, y2 = radius * sin(angle * M_PI / 180.0) + origY2;
			int x3 = radius * cos(angle * M_PI / 180.0) + origX3, y3 = radius * sin(angle * M_PI / 180.0) + origY3;
			int x4 = radius * cos(angle * M_PI / 180.0) + origX4, y4 = radius * sin(angle * M_PI / 180.0) + origY4;
			int x5 = radius * cos(angle * M_PI / 180.0) + origX5, y5 = radius * sin(angle * M_PI / 180.0) + origY5;
			if (angle < 720) size += 20; if (angle > 720) size -= 39;
			HRGN circle1 = CreateEllipticRgn(x1, y1, x1 - size, y1 - size);
			HRGN circle2 = CreateEllipticRgn(x2, y2, x2 - size, y2 - size);
			HRGN circle3 = CreateEllipticRgn(x3, y3, x3 - size, y3 - size);
			HRGN circle4 = CreateEllipticRgn(x4, y4, x4 - size, y4 - size);
			HRGN circle5 = CreateEllipticRgn(x5, y5, x5 - size, y5 - size);
			InvertRgn(desk, circle1); InvertRgn(desk, circle2); InvertRgn(desk, circle3); InvertRgn(desk, circle4); InvertRgn(desk, circle5);
			Sleep(26.4);
		}
	}
}
DWORD WINAPI scmv(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius = 11.5f;
	double moveangle = 0; SeedXorshift32(__rdtsc());
	while (1) {
		desk = GetDC(0);
		double ax = (cos(moveangle) * radius), ay = (sin(moveangle) * radius);
		BitBlt(desk, 0, 0, sw, sh, desk, ax, ay, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / radius, M_PI * radius);
		Sleep(12);
	}
}

DWORD WINAPI wvs3(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = 9, ySize = xSize + 2;
	SeedXorshift32(__rdtsc());
	double angle = 0;
	for (int c = 0;; c++, c %= 509) {
		if (!c) InvalidateRect(0, 0, 0);
		int origY = xorshift32() % sh, h = ySize;
		for (int i = origY; i < origY + 80; i += ySize / 2) {
			int p = (cos(angle) * xSize);
			angle = fmod(angle + M_PI / xSize, M_PI * xSize);
			BitBlt(desk, 0, i, sw, h, desk, p, i, SRCCOPY);
			Sleep(0.99999999999);
		}
	}
}
DWORD WINAPI swrl(LPVOID lpParam) {
	HDC desk;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
	SeedXorshift32(__rdtsc());
	while (1) {
		desk = GetDC(0); HDC hdcMem = CreateCompatibleDC(desk);
		HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 111, 0 };
		AlphaBlend(desk, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		DeleteDC(desk); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}
DWORD WINAPI wvs4(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = 4, ySize = 60;
	SeedXorshift32(__rdtsc()); double angle = 0;
	while (1) {
		int origY = xorshift32() % sh, h = ySize;
		for (int i = origY; i < origY + 80; i += ySize / 2) {
			int p = (cos(angle) * xSize);
			angle = fmod(angle + M_PI / xSize, M_PI * xSize);
			BitBlt(desk, 0, i, sw, h, desk, p, i, SRCCOPY); Sleep(0.99999999999);
		}
	}
}
DWORD WINAPI plgscr(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(0), counter = 0, v = 0;
	POINT pt[3]; RECT rekt;
	SeedXorshift32(__rdtsc());
	while (1) {
		if ((xorshift32() % 100 + 1) % 29 == 0) for (int i = 0; i < 40; i++) InvalidateRect(0, 0, 0);
		v = xorshift32() % 2;
		if (v == 0) counter = 61; else counter = -61;
		GetWindowRect(GetDesktopWindow(), &rekt);
		for (int c = 0; c < 4 + xorshift32() % 5; c++) {
			pt[0].x = rekt.left + counter; pt[0].y = rekt.top - counter;
			pt[1].x = rekt.right + counter; pt[1].y = rekt.top + counter;
			pt[2].x = rekt.left - counter; pt[2].y = rekt.bottom - counter;
			PlgBlt(desk, pt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(21.6);
			Sleep(19);
		}
	}
}
DWORD WINAPI plgscr2(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(0), counter = -107.8f;
	POINT pt[3]; RECT rekt;
	SeedXorshift32(__rdtsc());
	while (1) {
		GetWindowRect(GetDesktopWindow(), &rekt);
		pt[0].x = rekt.left + counter; pt[0].y = rekt.top - counter;
		pt[1].x = rekt.right + counter; pt[1].y = rekt.top + counter;
		pt[2].x = rekt.left - counter; pt[2].y = rekt.bottom - counter;
		PlgBlt(desk, pt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
		Sleep(200);
	}
}
DWORD WINAPI cltr(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int r = 2, g = 1, b = 4, power = 22;
	SeedXorshift32(__rdtsc()); HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 3) {
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int v = 1 + xorshift32() % 13;
			((BYTE*)(data + i))[r] = ((BYTE*)(data + i + v + power))[r] + 5.2;
			((BYTE*)(data + i))[g] = ((BYTE*)(data + i + v + power))[g] + 5.2;
			((BYTE*)(data + i))[b] = ((BYTE*)(data + i + v + power))[b] + 5.2;
		}
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
	}
}
DWORD WINAPI omg(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	SeedXorshift32(__rdtsc()); HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			if (i % h == 0 && xorshift32() % 100 == 0)  v = 1 + xorshift32() % 6;
			rgb ^= (int)data + i % 255;
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
DWORD WINAPI expdes(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius = 100.f, size = 200, origX = xorshift32() % sw, origY = xorshift32() % sh - (size / 2);
	double angle = 0;
	while (1) {
		if (radius < sw) radius++; if (radius > sw - 2) { Sleep(100); origX = (xorshift32() % sw); origY = (xorshift32() % sh); radius = 10; };
		int x = (cos(angle + radius) * radius) + origX, y = (sin(angle + radius) * radius) + origY, newSize = size + 16.4f;
		int sx = (cos(angle + radius) * 1.9f), sy = (sin(angle + radius) * 1.9f);
		BitBlt(desk, x + sx, y + sy, size, size, desk, x, y, SRCCOPY);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
		Sleep(0.999999999999);
	}
}
DWORD WINAPI plbt(LPVOID lpParam) {
	HDC desk = GetDC(0); SeedXorshift32(__rdtsc());
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		desk = GetDC(0);
		int a = xorshift32() % sw, b = xorshift32() % sh;
		BitBlt(desk, a, b, sw, sh, desk, a + cos(xorshift32() % 101 - 50), b + sin(xorshift32() % 101 - 50), SRCCOPY);
	}
}
DWORD WINAPI rnbaur(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius = 3.f, size = 200.f, origX = (sw / 2) - (size / 2), origY = (sh / 2) - (size / 2);
	double angle = 0;
	while (1) {
		if (radius < sw) radius += size + 44; if (radius > (sw - 2)) { InvalidateRect(0, 0, 0); origX = xorshift32() % (sw - size); origY = xorshift32() % (sh - size); radius = 50.f; };
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 256, xorshift32() % 256, xorshift32() % 256)));
		for (int c = 0; c < ((radius * 2) + 90.8f); c++) {
			double x = (cos(angle + radius) * radius) + origX, y = (sin(angle + radius) * radius) + origY;
			BitBlt(desk, x, y, size, size, desk, x, y, MERGECOPY);
			angle = fmod(angle + M_PI / radius, M_PI * radius);
		}
	}
}
DWORD WINAPI pxl2(LPVOID lpParam) {
	HDC desk = GetDC(0); SeedXorshift32(__rdtsc());
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 200;
	while (1) {
		desk = GetDC(0);
		for (int x = 0; x < sw; x += size) {
			for (int y = 0; y < sh; y += size) {
				StretchBlt(desk, x, y, size, size, desk, x, y, size + 13, size + 13, SRCCOPY);
				StretchBlt(desk, x, y, size, size, desk, x, y, size - 13, size - 13, SRCCOPY);
			}
		}
	}
}
DWORD WINAPI schl(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius = 17.f; double angle = 0;
	int size = 200, origX = (sw / 2) - (size / 2), origY = (sh / 2) - (size / 2);
	while (1) {
		for (int c = 0; c < 34567; c++) {
			if (radius < sw + 1) radius += 1.f; if (radius > sw - 2) { radius = 17.f; }
			float x = (cos(angle + radius) * radius) + origX, y = (sin(angle + radius) * radius) + origY,
				sx = (cos(angle + radius) * (radius + 1)) + origX, sy = (sin(angle + radius) * (radius + 1)) + origY;
			BitBlt(desk, x, y, size, size, desk, sx, sy, SRCCOPY);
			angle = fmod(angle + M_PI / radius, M_PI * radius);
		}
		origX = -size + xorshift32() % (sw + size); origY = -size + xorshift32() % (sh + size);
	}
}
DWORD WINAPI scbm(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), radius = 17.f; double angle = 0;
	int size = 200, origX = (sw / 2) - (size / 2), origY = (sh / 2) - (size / 2);
	while (1) {
		for (int c = 0; c < 17659; c++) {
			if (radius < sw + 1) radius += 1.f; if (radius > sw - 2) { radius = 17.f; }
			float x = (cos(angle + radius) * radius) + origX, y = (sin(angle + radius) * radius) + origY,
				sx = (cos(angle + radius) * (radius - 1)) + origX, sy = (sin(angle + radius) * (radius - 1)) + origY;
			BitBlt(desk, x, y, size, size, desk, sx, sy, SRCCOPY);
			angle = fmod(angle + M_PI / radius, M_PI * radius);
		}
	}
}
DWORD WINAPI glh(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0), hdcMem; HBITMAP screenshot;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (sw * sh + sw) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	while (1) {
		hdcMem = CreateCompatibleDC(desk); screenshot = CreateBitmap(sw, sh, 1, 32, data);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY); GetBitmapBits(screenshot, sw * sh * 4, data);
		int v = xorshift32() % 3, c = 0;
		if (v == 0) c = 2; if (v == 1) c = 1; if (v == 3) c = 4;
		for (int i = 0; i < sw * sh; i++) {
			((BYTE*)(data + i))[c] = i;
		}
		SetBitmapBits(screenshot, sw * sh * 4, data); BitBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		DeleteDC(hdcMem); DeleteObject(screenshot);
		Sleep(2);
	}
}
DWORD WINAPI rtscr2(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), p = 0, v = 0;
	while (1) {
		v = xorshift32() % 2; if (v == 0) p = -51; else p = 51;
		for (int i = 0; i < 4; i++) {
			desk = GetDC(0); HDC hdcMem = CreateCompatibleDC(desk);
			HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);

			SelectObject(hdcMem, screenshot);
			BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

			rotatehdc(GetDesktopWindow(), hdcMem, sw, sh, p);

			BLENDFUNCTION blend = { AC_SRC_OVER, 0, 110, 0 };
			AlphaBlend(desk, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);

			DeleteDC(hdcMem); DeleteDC(desk); DeleteObject(screenshot);
			Sleep(1);
		}
	}
}

DWORD WINAPI blr(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 199;
	while (1) {
		desk = GetDC(0); HDC hdcMem = CreateCompatibleDC(desk);
		HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < 30; i++) {
			int x = -size + xorshift32() % (sw + size), y = -size + xorshift32() % (sh + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + xorshift32() % 17 - 8, y + xorshift32() % 17 - 8, SRCCOPY);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(desk, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(desk);
	}
}
DWORD WINAPI bnic(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), iw = GetSystemMetrics(11), ih = GetSystemMetrics(12), radius = 160.9f;
	int origX = (sw / 2) - (radius / 2), origY = (sh / 2) - (radius / 2), x = 0, y = 0, centerX = 0, centerY = 0,
		vx = 15, vy = 17;
	double angle = 0;
	LPCWSTR icons[6] = { IDI_ERROR, IDI_WARNING, IDI_QUESTION, IDI_INFORMATION, IDI_SHIELD, IDI_APPLICATION };
	while (1) {
		HICON icon = LoadIcon(0, icons[xorshift32() % 6]);

		origX += vx;
		if (origX < 0) vx = -vx;
		else if (origX + iw > sw) vx = -vx;
		origY += vy;
		if (origY < 0) vy = -vy;
		else if (origY + ih > sh) vy = -vy;
		for (int i = 0; i < radius + (iw + ih); i++) {
			centerX = origX - (iw / 2); centerY = origY - (ih / 2);
			x = (cos(angle) * radius) + centerX; y = (sin(angle) * radius) + centerY;

			DrawIcon(desk, x, y, icon);

			angle = fmod(angle + M_PI / radius, M_PI * radius);
		}
		Sleep(1);
	}
}
DWORD WINAPI fnl(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), h = sh / 44;
	for (int i = 0;; i++, i %= 6) {
		if (!i) InvalidateRect(0, 0, 0);
		for (int y = 0; y < sh + 1; y += h) {
			int v = xorshift32() % 2;
			if (v == 0) BitBlt(desk, 0, y, sw, h, desk, 0 + 23, y, SRCCOPY);
			if (v == 1) BitBlt(desk, 0, y, sw, h, desk, 0 - 23, y, SRCCOPY);
		}
		Sleep(1);
	}
}
DWORD WINAPI rnbscr(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int r = 2, g = 1, b = 4, c1 = r, c2 = r, c3 = r, v = 0, power = 5.f;
	SeedXorshift32(__rdtsc()); HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 3) {
		for (int cn = 0; cn < 255 / 14; cn++) {
			hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
			SelectObject(hdcMem, hbm);
			BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
			for (int i = 0; w * h > i; i++) {
				int r = GetRValue(((BYTE*)(data + i))[2]) % 255, g = GetGValue(((BYTE*)(data + i))[1]) % 255, b = GetBValue(((BYTE*)(data + i))[4]) % 255;
				((BYTE*)(data + i))[c1] = (((BYTE*)(data + i))[c1]) + power;
				((BYTE*)(data + i))[c2] = (((BYTE*)(data + i))[c2]) + power;
				((BYTE*)(data + i))[c3] = (((BYTE*)(data + i))[c3]) + power;
			}
			SetBitmapBits(hbm, w * h * 4, data); pixelatehdc(hdcMem, w, h, 4.0, STRETCH_DELETESCANS, SRCCOPY);
			BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
			DeleteObject(hbm); DeleteObject(hdcMem); DeleteDC(origHDC); DeleteDC(hdcMemory);
			DeleteObject(hdc); DeleteObject(hScreenshot);
		}
		v++;
		if (v > 0) c2 = g;
		if (v > 1) { c3 = b; }
		if (v > 3) { InvalidateRect(0, 0, 0); c1 = r; c2 = r; c3 = r; v = 0; }
	}
}
DWORD WINAPI pxl3(LPVOID lpParam) {
	SeedXorshift32(__rdtsc());
	HDC desk, hdcMem;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		for (int i = 0; i < 87; i++) InvalidateRect(0, 0, 0);
		for (int p = 2; p < sw / 16; p += 2) {
			desk = GetDC(0); hdcMem = CreateCompatibleDC(desk);
			HBITMAP screenshot = CreateCompatibleBitmap(desk, sw / p, sh / p);
			SetStretchBltMode(hdcMem, STRETCH_DELETESCANS);
			SelectObject(hdcMem, screenshot);
			StretchBlt(hdcMem, 0, 0, sw / p, sh / p, desk, 0, 0, sw, sh, SRCCOPY);
			StretchBlt(desk, 0, 0, sw, sh, hdcMem, 0, 0, sw / p, sh / p, SRCCOPY);
			DeleteDC(desk); DeleteDC(hdcMem); DeleteObject(screenshot);
			Sleep(64);
		}
		Sleep(1000);
		for (int i = 0; i < 87; i++) InvalidateRect(0, 0, 0);
	}
}

int main(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"Run Malware?", L"Polyhydroxyalkanoates.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure?", L"Polyhydroxyalkanoates.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			Sleep(1000);
			sound1();
			HANDLE pixelating = CreateThread(0, 0, pxl, 0, 0, 0);
			Sleep(24000);
			sound2();
			TerminateThread(pixelating, 0);
			HANDLE blurmash = CreateThread(0, 0, blr, 0, 0, 0);
			HANDLE shadow = CreateThread(0, 0, shd, 0, 0, 0);
			Sleep(32000);
			for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			TerminateThread(blurmash, 0); TerminateThread(shadow, 0);
			sound3();
			HANDLE payload2 = CreateThread(0, 0, pl2, 0, 0, 0);
			HANDLE rotatescreen = CreateThread(0, 0, rtscr, 0, 0, 0);
			Sleep(16000);
			TerminateThread(rotatescreen, 0);
			for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			HANDLE sinewaves = CreateThread(0, 0, hrwvs, 0, 0, 0);
			Sleep(16000);
			TerminateThread(sinewaves, 0); TerminateThread(payload2, 0);
			sound4();
			HANDLE glitchart = CreateThread(0, 0, glchart, 0, 0, 0);
			Sleep(14000);
			TerminateThread(glitchart, 0);
			for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			HANDLE shake = CreateThread(0, 0, shk, 0, 0, 0);
			Sleep(14000);
			TerminateThread(shake, 0);
			for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			soundboom();
			HANDLE explodedesktop = CreateThread(0, 0, expdes, 0, 0, 0);
			Sleep(24000);
			TerminateThread(explodedesktop, 0);
			sound5();
			HANDLE invertcircles = CreateThread(0, 0, invcc, 0, 0, 0);
			Sleep(28000);
			TerminateThread(invertcircles, 0);
			sound6();
			HANDLE waves3 = CreateThread(0, 0, wvs3, 0, 0, 0);
			HANDLE rotatescreen2 = CreateThread(0, 0, plgscr, 0, 0, 0);
			HANDLE screenmove = CreateThread(0, 0, scmv, 0, 0, 0);
			Sleep(30000);
			TerminateThread(screenmove, 0); TerminateThread(rotatescreen2, 0); TerminateThread(waves3, 0); for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			sound8();
			HANDLE waves4 = CreateThread(0, 0, wvs4, 0, 0, 0);
			HANDLE colortrain = CreateThread(0, 0, cltr, 0, 0, 0);
			Sleep(14000);
			TerminateThread(colortrain, 0);
			HANDLE colorlines = CreateThread(0, 0, omg, 0, 0, 0);
			Sleep(16000);
			TerminateThread(waves4, 0); TerminateThread(colorlines, 0);
			for (int i = 0; i < 79; i++) InvalidateRect(0, 0, 0);
			HANDLE thr0 = CreateThread(0, 0, glchart, 0, 0, 0);
			Sleep(5000);
		}
	}
}