#include <windows.h>

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	HDC hdc = GetDC(GetDesktopWindow()); 
	int ScrW = GetSystemMetrics(SM_CXSCREEN);
	int ScrH = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		for (int i = 0;; i++, i %= 3)
		{
			for (int c = 0; c < rand() % 16; c++)
			{
				int y = rand() % ScrH;
				HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));

				SelectObject(hdc, brush);
				BitBlt(hdc, 0, y, ScrW, 300, hdc, rand() % 61 - 30, y, SRCCOPY);
				PatBlt(hdc, 0, y, ScrW, 300, PATINVERT);
			}

			if (!i) RedrawWindow(0, 0, 0, 133);
		}
	}
}
