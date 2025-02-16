#ifndef NEPOTONOD
#define NEPOTONOD

#define UNICODE

// Enable XP styles
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma once

typedef int INT_16;

// Includes
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <psapi.h>
#include <time.h>

#include "data.h"
#include "payloads.h"

// Other defines and pragmas...
#define DESKTOP_WINDOW ((HWND)0)
#define MINUTE ((INT_16)60000)
#pragma warning(disable:4996)

// Global consts
int nWidth;
int nHeight;

#endif
