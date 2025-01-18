#include <windows.h>
#include <time.h>
#include <iostream>

HWND DESK = GetDesktopWindow(); HDC hdc = GetDC(DESK);

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	int ScrW = GetSystemMetrics(SM_CXSCREEN);
	int ScrH = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		int y = 0;

		for (int i = 0;; i++, i %= 6)
		{
			int x = rand() % ScrW, y = rand() % ScrH, sx = rand() % 21 - 10, sy = rand() % 21 - 10;

			HBRUSH brush = CreateHatchBrush(6, RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(hdc, brush);
			PatBlt(hdc, 0, 0, ScrW, ScrH, PATINVERT);
			for (int n = 0; n < 201 - 50; n++)
			{
				StretchBlt(hdc, x, 0, 0 + n, ScrH - n, hdc, x--, 1, n - 10, ScrH - n++, SRCCOPY);
				Sleep(1);
			}
		}
	}

	return 0;
}
