#pragma once
#include "esfera.h"

VOID
WINAPI
InitializeScreen(
	VOID
);

VOID
WINAPI
CreateEsferaWindow(
	VOID
);

LRESULT
CALLBACK
WndProc(
	_In_	 HWND   hWnd,
	_In_     UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
);

VOID
WINAPI
ExecutePayload(
	_In_  PAYLOAD  GdiPayload,
	_In_  DWORD	   dwTime
);