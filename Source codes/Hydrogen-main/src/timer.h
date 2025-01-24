#pragma once
#include <Windows.h>
extern DWORD Time;
extern void InitTimer(UINT uDelay);
extern void CALLBACK TimerProc(HWND hwndTimer, UINT uMsg, UINT_PTR ulTimerID, DWORD dwTime);