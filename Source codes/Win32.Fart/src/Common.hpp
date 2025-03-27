#pragma once

#include <iostream>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

float GetCurrentVolume();
void SetVolume(float volume);