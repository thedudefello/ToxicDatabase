#pragma once
#include "esfera.h"

BOOL bChangeResolution, bSkipRSOD;

LRESULT
CALLBACK
bsodProc(
	_In_	 HWND   hWnd,
	_In_	 UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
);

LRESULT
CALLBACK
LastProc(
	_In_	 HWND   hWnd,
	_In_	 UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
);

BOOL
WINAPI
CheckDebugger(
	VOID
);

BOOL
WINAPI
AprilPayload(
	VOID
);

VOID
WINAPI
EnumThread(
	VOID
);

VOID
WINAPI
CursorDraw(
	VOID
);

VOID
WINAPI
EllipseBall(
	VOID
);

VOID
WINAPI
ExtraMess(
	VOID
);

VOID
WINAPI
FakeBSOD(
	VOID
);

VOID
WINAPI
LastPayload(
	VOID
);