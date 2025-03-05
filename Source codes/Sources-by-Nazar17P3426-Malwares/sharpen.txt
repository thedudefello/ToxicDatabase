#include <windows.h>

int main() {
	while (1) {
		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, 0, 0, sw + 1, sh - 1, hdc, 0, 0, sw, sh, SRCCOPY);
		StretchBlt(hdc, 0, 0, sw - 1, sh + 1, hdc, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}