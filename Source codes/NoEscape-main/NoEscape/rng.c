#include "ex.h"

UINT32 __ROL__( UINT32 value, int count )
{
	const UINT32 nbits = sizeof( UINT32 ) * 8;

	if( count > 0 ) {
		count %= nbits;
		UINT high = value >> ( nbits - count );
		if( ( -1 ) < 0 ) // signed value
			high &= ~( ( ( -1 ) << count ) );
		value <<= count;
		value |= high;
	} else {
		count = -count % nbits;
		INT low = value << ( nbits - count );
		value >>= count;
		value |= low;
	}
	return value;
}

inline UINT32 __ROL4__( UINT32 value, int count ) { return __ROL__( ( UINT32 )value, count ); }
inline UINT32 __ROR4__( UINT32 value, int count ) { return __ROL__( ( UINT32 )value, -count ); }

int __fastcall
RandomRange(
	int a1,
	int a2
)
{
	DWORD *v2 = RandomDataGenerated;
	unsigned int v3 = a2 - a1 + 1;
	int v4;
	int v5;
	int v6;
	unsigned int i;
	DWORD *v8;
	int v9;
	int v10;
	int v11;
	int v13 = a1;
	unsigned int v14 = 0xFFFFFFFF / v3;
	int v15 = 5 * *( ( DWORD * )RandomDataGenerated + 1 );
	int v16;
	unsigned int v17 = v3 * ( 0xFFFFFFFF / v3 );

	// Syncronize code
	EnterCriticalSection( &CriticalSection );

	// What the fuck is that
	v4 = *v2 ^ v2[ 2 ];
	v5 = v2[ 1 ];
	v6 = v5 ^ v2[ 3 ];
	v2[ 1 ] = v5 ^ v4;
	*v2 ^= v6;
	v2[ 2 ] = v4 ^ ( v5 << 9 );
	v2[ 3 ] = __ROL4__( v6, 11 );

	LeaveCriticalSection( &CriticalSection );

	// What the fuck is that
	for( i = 9 * __ROL4__( v15, 7 ); i >= v17; i = 9 * __ROL4__( v16, 7 ) ) {
		v8 = RandomDataGenerated;
		v16 = 5 * *( ( DWORD* )RandomDataGenerated + 1 );

		// Sync code
		EnterCriticalSection( &CriticalSection );

		// What the fuck is that
		v9 = *v8 ^ v8[ 2 ];
		v10 = v8[ 1 ];
		v11 = v10 ^ v8[ 3 ];
		v8[ 1 ] = v10 ^ v9;
		*v8 ^= v11;
		v8[ 2 ] = v9 ^ ( v10 << 9 );
		v8[ 3 ] = __ROL4__( v11, 11 );

		LeaveCriticalSection( &CriticalSection );
	}
	return v13 + i / v14;
}