#pragma once
#include <Windows.h>
extern RECT GetVirtualScreen();
extern BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, PRECT prcBounds, LPARAM lParam);
extern POINT GetVirtualScreenPos();
extern SIZE GetVirtualScreenSize();