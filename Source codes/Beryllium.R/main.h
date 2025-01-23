#include <windows.h>
#include <intrin.h>
VOID WINAPI Thrkl(HANDLE thread) {
	TerminateThread(thread, 0);
	CloseHandle(thread);
}

VOID WINAPI Rfrsh() {
	InvalidateRect(0, 0, 0);
	Sleep(1000);
}

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w+x, h-y);
    HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 255));
    SelectClipRgn(hdc, hrgn);
    SelectObject(hdc, hbr);
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    DeleteObject(hrgn); DeleteObject(hbr);
    ReleaseDC(NULL, hdc);
}
DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs << 17;
	xs ^= xs << 5;
	return xs;
}

DWORD WINAPI RedrawCounter(LPVOID lpRedraw) {
	while (1) {
		Sleep(500);
		InvalidateRect(0, 0, 0);
	}
}

