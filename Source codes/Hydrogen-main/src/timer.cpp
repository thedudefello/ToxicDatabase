#include "timer.h"
DWORD Time;
void InitTimer(UINT uDelay) {
	UINT_PTR id = SetTimer(NULL, 0, uDelay, TimerProc);
	MSG msg = { 0 };
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
void CALLBACK TimerProc(HWND hwndTimer, UINT uMsg, UINT_PTR ulTimerID, DWORD dwTime) {
	Time++;
}