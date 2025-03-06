// MAIN HEADER //

#pragma once

// PRAGMA OPTIONS //
#pragma warning(push, 1)
#pragma warning(disable: 4990)
#pragma warning(pop)

//// LINKERS ////
#pragma comment(lib, "WINMM")
#pragma comment(lib, "MSIMG32")
#pragma comment(lib, "NTDLL")

// DEFINES //
#define LCDECL __stdcall
#define pWinMain WinMain
#define USE_MATH_DEFINES TRUE

// MAIN INCLUDES //
#include <Windows.h>
#include <Math.h>
#include <Time.h>
#include <xmmIntrin.h>

// LOCAL INCLUDES //
#include "GDIFx.h"
#include "System.h"
#include "Bytebeat.h"
