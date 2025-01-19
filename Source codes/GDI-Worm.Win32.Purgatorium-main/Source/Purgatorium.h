typedef struct IUnknown IUnknown;

#pragma once

//Include libs in linking process
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")

//Pragma warnings
#pragma warning(disable : 4996)

//Include main libs
#include <Windows.h>
#include <math.h>
#include <time.h>

//Include local files
#include "Colors.h"
#include "Math.h"
#include "System.h"
#include "Payloads.h"
#include "Bytebeats.h"
#include "GDIPayloads.h"