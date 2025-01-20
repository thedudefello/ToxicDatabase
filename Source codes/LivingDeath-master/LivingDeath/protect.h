#include <Windows.h>

typedef void ( _stdcall * RtlSetProcessIsCritical ) ( IN BOOLEAN New, OUT PBOOLEAN Old, IN BOOLEAN Log );
int protectProcess ( void );

int protectProcess ( void )
{
    int enablePriv ( const char * szPriv );
    HANDLE DLL;
    RtlSetProcessIsCritical setCritical;
 
    DLL = LoadLibraryA ( "ntdll.dll" );
 
    if ( DLL == NULL ) {
		return -1;
	}
 
	if ( enablePriv ( SE_DEBUG_NAME ) < 0 ) {
		return -1;
	}
 
	setCritical = ( RtlSetProcessIsCritical ) GetProcAddress( ( HINSTANCE ) DLL, "RtlSetProcessIsCritical" );
 
	if ( ! setCritical ) {
		return -1;
	}
 
	setCritical ( 1, 0, 0 );
	return 0;
}
int enablePriv ( const char * szPriv )
{
    HANDLE token;
    LUID luid;
    TOKEN_PRIVILEGES privs;
    memset ( &privs, 0, sizeof ( privs ) );
 
    if ( ! OpenProcessToken ( GetCurrentProcess ( ), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, & token ) ) {
       return -1;
    }
 
    if ( ! LookupPrivilegeValue ( NULL, szPriv, & luid ) )
	{
        CloseHandle ( token );
        return -1;
    }
 
    privs . PrivilegeCount = 1;
    privs . Privileges [ 0 ] . Luid = luid;
    privs . Privileges [ 0 ] . Attributes = SE_PRIVILEGE_ENABLED;
 
    if ( ! AdjustTokenPrivileges ( token, FALSE, & privs, sizeof ( privs ), NULL, NULL ) ) {
                        return -1;
    }
 
    CloseHandle ( token );
	return 0;
}