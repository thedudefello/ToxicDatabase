#include<tchar.h>
#include<windows.h>
#include<ctime>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

DWORD WINAPI drawandroidicon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE ANDROIDICON = LoadLibrary(_T("ANDROIDICON2K.dll"));
	HDC hdc = GetWindowDC(hwnd);
	srand(time(0));
	Sleep(1000);
	while (1) {
		for (int x = 0; x <= 3840; x += 32) {
			for (int y = 0; y <= 2160; y += 32) {
				DrawIcon(hdc, x, y, LoadIcon(ANDROIDICON, MAKEINTRESOURCE(rand() % 256)));
			}
		}
		Sleep(1000);
	}
	while (1);
}

int main() {
	HANDLE thread1 = CreateThread(0, 0, drawandroidicon, 0, 0, 0);
	Sleep(310000);
	return 0;
}