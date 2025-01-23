#include <windows.h>

HHOOK hhk;

LONG_PTR CALLBACK cbtProc(int code, UINT_PTR uptr, LONG_PTR lptr) {
	if (code == HCBT_ACTIVATE) {
		HWND dlg = (HWND)uptr;
		HWND hbutton = GetDlgItem(dlg, IDOK);
		if (hbutton != NULL) EnableWindow(hbutton, false);
	}
	return CallNextHookEx(hhk, code, uptr, lptr);
}

int main() {
	hhk = SetWindowsHookExW(WH_CBT, &cbtProc, NULL, GetCurrentThreadId());
	MessageBoxW(NULL, L"Please wait...", L"Waiting", MB_ICONASTERISK);
	if (hhk != NULL) UnhookWindowsHookEx(hhk);
	return 0;
}
