#include <windows.h>
int main()
{
	while(1){
    	HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN),
        h = GetSystemMetrics(SM_CYSCREEN),
        rx = rand() % w;
   		BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCCOPY);
    	ReleaseDC(NULL, hdc);
	}
}
