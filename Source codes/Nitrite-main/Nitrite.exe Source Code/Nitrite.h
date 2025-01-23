// << MAIN LIBRARIES >>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <tchar.h>
#include <xmmintrin.h>

// << LOCAL LIBRARIES >>
#include "Payloads.h"
#include "GDIPayloads.h"
#include "Bytebeat.h"

// << DYNAMIC-LINK LIBRARIES >>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "ntdll.lib")

// << DEFINES >>
#define HATCHPAINT 0x1900ac010eul
#define NOTSRCINVERT 0x99ffb9ul
#define MERGEPAINTEX 0xce646cul
