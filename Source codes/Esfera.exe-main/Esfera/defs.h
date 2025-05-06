#pragma once
#include "esfera.h"

BOOL bIsApril;

#define PI 3.14159f
#define PAYLOAD_TIME 30000 /* 30 seconds */

NTSTATUS 
NTAPI
NTQueryInformationProcess(
	_In_      HANDLE           ProcessHandle,
	_In_      PROCESSINFOCLASS ProcessInformationClass,
	_Out_     PVOID            ProcessInformation,
	_In_      ULONG            ProcessInformationLength,
	_Out_opt_ PULONG           ReturnLength
);

#ifdef INJECTION
BOOL
WINAPI
InjectDll(
	_In_ WCHAR*   TargetProcess,
	_In_ LPCWSTR  Dll
);
#endif