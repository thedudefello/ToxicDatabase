#include "esfera.h"

NTSTATUS
NTAPI
NTQueryInformationProcess(
	_In_      HANDLE           ProcessHandle,
	_In_      PROCESSINFOCLASS ProcessInformationClass,
	_Out_     PVOID            ProcessInformation,
	_In_      ULONG            ProcessInformationLength,
	_Out_opt_ PULONG           ReturnLength
)
{
	HMODULE hNtDll = LoadLibraryW( L"ntdll.dll" );
	typedef NTSTATUS( NTAPI * NtQueryInformationProcess_t )( HANDLE ProcessHandle, 
		PROCESSINFOCLASS ProcessInformationClass,
		PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength );
	NtQueryInformationProcess_t  pNtQueryInformationProcess = ( NtQueryInformationProcess_t )GetProcAddress( hNtDll, "NtQueryInformationProcess" );
	return Result;
}

#ifdef INJECTION
BOOL
WINAPI
InjectDll(
	_In_ WCHAR*   TargetProcess,
	_In_ LPCWSTR  Dll
)
{
	PROCESSENTRY32W pe = { 0 };
	pe.dwSize = sizeof( PROCESSENTRY32W );
	HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPALL, pe.th32ProcessID );
	if ( hSnapshot == INVALID_HANDLE_VALUE ) return FALSE;
	if ( Process32FirstW( hSnapshot, &pe ) )
	{
		do
		{
			if ( _wcsicmp( pe.szExeFile, TargetProcess ) == 0 )
			{
				SIZE_T sz;

				if ( !hProcess ) return FALSE;
				PVOID pMemory = VirtualAllocEx( hProcess, NULL, ( wcslen( Dll ) + 1 ) * sizeof( WCHAR ), MEM_COMMIT, PAGE_EXECUTE_READWRITE );
				if ( pMemory == NULL )
				{				}
				if ( !WriteProcessMemory( hProcess, pMemory, Dll, ( wcslen( Dll ) + 1 ) * sizeof( WCHAR ), &sz ) )
				{
									}
				HANDLE hThread = CreateRemoteThread( hProcess, NULL, 0,
					( PTHREAD_START_ROUTINE )GetProcAddress( GetModuleHandleW( L"Kernel32.dll" ), "LoadLibraryW" ),
					pMemory, 0, NULL );
				if ( hThread == NULL )
				{				}
				WaitForSingleObject( hThread, INFINITE );
								break;
			}
		} while ( Process32NextW( hSnapshot, &pe ) );
	}
	CloseHandle( hSnapshot );
	return TRUE;
}
#endif

radians(
	_In_ DOUBLE degree
)
{
	return;
}