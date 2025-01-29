//
// Melter - By Napalm @ NetCore2K.net
// Inspired by MetalHead (http://www.rohitab.com/discuss/index.php?showtopic=23191)
// modded by pankoza
#include <windows.h>
int	nRandWidth = 150, nRandHeight = 15, nSpeed = 1;
int	nScreenWidth, nScreenHeight;

LRESULT WINAPI MelterProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg){
		case WM_CREATE:
			{
				HDC hdcDesktop = GetDC(HWND_DESKTOP);
				HDC hdcWindow  = GetDC(hWnd);	
				BitBlt(hdcWindow, 0, 0, nScreenWidth, nScreenHeight, hdcDesktop, 0, 0, SRCCOPY);
				ReleaseDC(hWnd, hdcWindow);
				ReleaseDC(HWND_DESKTOP, hdcDesktop);
				SetTimer(hWnd, 0, nSpeed, NULL);
				ShowWindow(hWnd, SW_SHOW);
			}
			return 0;
		case WM_ERASEBKGND:
			return 0;
		case WM_PAINT:
			ValidateRect(hWnd, NULL);
			return 0;
		case WM_TIMER:
			{
				HDC hdcWindow  = GetDC(hWnd);
				int	nXPos  = (rand() % nScreenWidth) - (nRandWidth / 2),
					nYPos  = (rand() % nRandHeight),
					nWidth = (rand() % nRandWidth);
				BitBlt(hdcWindow, nXPos, nYPos, nWidth, nScreenHeight, hdcWindow, nXPos, 0, SRCCOPY);
				ReleaseDC(hWnd, hdcWindow);
			}
			return 0;
		case WM_CLOSE:
		case WM_DESTROY:
			{
				KillTimer(hWnd, 0);
				PostQuitMessage(0);
			}
			return 0;				
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
	nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	WNDCLASS wndClass = { 0, MelterProc, 0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW), 0, NULL, "Melter" };
	if(!RegisterClass(&wndClass)) return MessageBox(HWND_DESKTOP, "Cannot register class!", NULL, MB_ICONERROR | MB_OK);
	
	HWND hWnd = CreateWindow("Melter", NULL, WS_POPUP, 0, 0, nScreenWidth, nScreenHeight, HWND_DESKTOP, NULL, hInstance, NULL);
	if(!hWnd) return MessageBox(HWND_DESKTOP, "Cannot create window!", NULL, MB_ICONERROR | MB_OK);
	
	srand(GetTickCount());
	MSG Msg = { 0 };
	while(Msg.message != WM_QUIT){
		if(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return 0;
}
