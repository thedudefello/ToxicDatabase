#include "esfera.h"

VOID
WINAPI
FakeBSOD(
	VOID
)
{
}

BOOL
WINAPI
CheckDebugger(
	VOID
)
{
}

BOOL
WINAPI
AprilPayload(
	VOID
)
{
	BreakOnTermination = FALSE;
	return TRUE;
}

VOID
WINAPI
EnumThread(
	VOID
)
{
}

VOID
WINAPI
CursorDraw(
	VOID
)
{
}

VOID
WINAPI
EllipseBall(
	VOID
)
{
}

LRESULT
CALLBACK
bsodProc(
	_In_	 HWND   hWnd,
	_In_	 UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
)
{
	switch (uMsg)
	{
	default:
		return DefWindowProcW(hwnd,  );
	}
}

LRESULT
CALLBACK
LastProc(
	_In_	 HWND   hWnd,
	_In_	 UINT   uMsg,
	_In_opt_ WPARAM wParam,
	_In_opt_ LPARAM lParam
)
{
	switch ( uMsg )
	{
		default: 
			return DefWindowProcW( hWnd );
	}
}