#include "ex.h"
#include "native.h"

LRESULT __stdcall
WndProc(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	LRESULT result;
	HGDIOBJ v5;
	HDC hdcSrc;
	HDC hdc;
	HWND ProcessInformation;
	int pv;
	int v10;
	struct tagPAINTSTRUCT Paint;

	HANDLE ho = 0;

	ProcessInformation = hWnd;
	switch( Msg ) {
		case 1:
			ho = LoadImageW( hInstance, ( LPCWSTR )0x70, 0, 0, 0, 0 );
			result = 0;
			break;
		case 2:
			DeleteObject( ho );
			DestroyWindow( hWnd );
			PostQuitMessage( 0 );
			result = 0;
			break;
		case 0xF:
			memset( &Paint, 0, 0x40 );

			pv = 00;
			v10 = 00;

			hdc = BeginPaint( hWnd, &Paint );
			hdcSrc = CreateCompatibleDC( hdc );
			v5 = SelectObject( hdcSrc, ho );
			GetObjectW( ho, 24, &pv );

			BitBlt( hdc, 0, 0, pv, pv, hdcSrc, 0, 0, 0xCC0020 );

			SelectObject( hdcSrc, v5 );
			DeleteDC( hdcSrc );

			EndPaint( ProcessInformation, &Paint );

			result = 0;
			break;
		case 0x11:
			ProcessInformation = 0;
			NtSetInformationProcess( ProcessHandle, ProcessBreakOnTermination, &ProcessInformation, 4u );

			result = 0;
			break;
		case 0x16:
			ExitProcess( 0 );
			return result;
		default:
			result = DefWindowProcW( hWnd, Msg, wParam, lParam );
			break;
	}
	return result;
}