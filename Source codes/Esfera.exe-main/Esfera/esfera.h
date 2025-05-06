#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <Winternl.h>
#include <Shlwapi.h>
#include <AccCtrl.h>
#include <Aclapi.h>
#include <Stdio.h>
#include <Time.h>
#include <Math.h>

#include "defs.h"
#include "extra.h"
#include "engine.h"
#include "colors.h"
#include "sounds.h"
#include "shaders.h"
#include "payloads.h"
#include "destruction.h"

#pragma comment( lib, "Shlwapi.lib" )
#pragma comment( lib, "WinMM.lib" )
#pragma comment( lib, "Msimg32.lib" )