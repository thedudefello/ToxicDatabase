#pragma once
#include "esfera.h"

VOID
WINAPI
InitializeScreen(
	VOID
)
{
	hWndDesktop = HWND_DESKTOP;
	hdcDesktop = GetDC( hWndDesktop );
}

VOID
WINAPI
CreateEsferaWindow(
	VOID
)
{
	CreateEsferaWindow( );
}

VOID
WINAPI
ExecutePayload(
	_In_  PAYLOAD  GdiPayload,
	_In_  DWORD	   dwTime
)
{
	RedrawWindow( hWndDesktop, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN );
}

LRESULT
CALLBACK
WndProc(
	_In_	 HWND   hWnd,
	_In_     UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
)
{
	return 0;
}