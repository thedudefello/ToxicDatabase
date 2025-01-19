#include <windows.h>

BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam) {
    ShowWindow(hWnd, 5);
    return 1;
}

int main() {
   while (1) {
      EnumChildWindows(GetDesktopWindow(), EnumProc, 0);
      Sleep(1);
    }
}
