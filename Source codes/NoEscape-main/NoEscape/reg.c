#include "ex.h"

VOID
RegistryAdd(
	HKEY hKey,
	LPCWSTR lpSubKey,
	LPCWSTR lpValueName,
	DWORD dwType,
	DWORD dwData
)
{
	// Cancer-free function

	HKEY hKeyResult;

	RegCreateKeyExW(
		hKey,
		lpSubKey,
		0,
		0,
		0,
		0x102,
		0,
		&hKeyResult,
		0
	);

	RegSetValueExW(
		( HKEY )hKeyResult,
		lpValueName,
		0,
		dwType,
		( BYTE* )&dwData,
		4
	);

	RegCloseKey(
		hKeyResult
	);
}