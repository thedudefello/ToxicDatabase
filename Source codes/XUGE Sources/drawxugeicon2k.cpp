#include<tchar.h>
#include<windows.h>
#include<ctime>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

DWORD WINAPI drawxugeicon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE XUGEICON = LoadLibrary(_T("XUGEICON2K.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	while (1)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

	}Sleep(1);
}

int main() {
	HANDLE thread1 = CreateThread(0, 0, drawxugeicon, 0, 0, 0);
	Sleep(310000);
	return 0;
}