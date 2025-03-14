// radiance.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable: 4995)
#pragma comment(lib, "Dwmapi.lib")
#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <ShlObj.h>
#include "Bytebeats.h"
#include "Payloads.h"

DWORD WINAPI fakeerror(LPVOID lpParam){
    MessageBoxA(NULL, "Failed to connect to https://www.getrickrolled.com, Please check your Internet Connection and try again.", "An error has occurred.", MB_ICONERROR);
    return 0;
}

DWORD WINAPI dumb(LPVOID lpParam) {
    while (true) {
        MessageBoxA(NULL, "A ray of radiance shots into your eyes and your destroyed computer.", "radiance.exe - System Warning", MB_ICONWARNING | MB_RETRYCANCEL);
    }
}

int StopThread(HANDLE thread) {
    TerminateThread(thread, 0);
    CloseHandle(thread);
    return 0;
}

int RefreshScreen() {
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN); InvalidateRect(0, 0, 0);
    Sleep(1);
    return 114514;
}

void RunPayload() {
    //hi dude!

    CreateThread(0, 0, fakeerror, 0, 0, 0);
    Sleep(3000);
    DwmEnableComposition(0); //Disable Aero in Windows Vista and Windows 7!
    sound1();
    HANDLE Payload1Num1 = CreateThread(0, 0, Payload1_num1, 0, 0, 0);
    HANDLE CursorDrawIconThread = CreateThread(0, 0, CursorDrawIcon, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload1Num1);
    RefreshScreen();

    sound2();
    HANDLE Payload2Num1 = CreateThread(0, 0, Payload2_num1, 0, 0, 0), Payload2Num2 = CreateThread(0, 0, Payload2_num2, 0, 0, 0), Payload2Num3 = CreateThread(0, 0, Payload2_num3, 0, 0, 0), Payload2Num4 = CreateThread(0, 0, Payload2_num4, 0, 0, 0);
    Sleep(30000); 
    StopThread(Payload2Num1); StopThread(Payload2Num2); StopThread(Payload2Num3); StopThread(Payload2Num4);
    RefreshScreen();

    sound3();
    HANDLE Payload3Num1 = CreateThread(0, 0, Payload3_num1, 0, 0, 0), Payload3Num2 = CreateThread(0, 0, Payload3_num2, 0, 0, 0);
    HANDLE DrawIconsThread = CreateThread(0, 0, DrawIcons, 0, 0, 0), DrawCursorsThread = CreateThread(0, 0, DrawCursors, 0, 0, 0);
    HANDLE DumbThread = CreateThread(0, 0, dumb, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload3Num1); StopThread(Payload3Num2);
    StopThread(DrawIconsThread); StopThread(DrawCursorsThread);
    RefreshScreen();

    sound4();
    HANDLE Payload4Num1 = CreateThread(0, 0, Payload4_num1, 0, 0, 0);
    HANDLE DrawTextsThread = CreateThread(0, 0, DrawTexts, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload4Num1);
    StopThread(DrawTextsThread);
    RefreshScreen();

    sound5();
    HANDLE Payload5Num1 = CreateThread(0, 0, Payload5_num1, 0, 0, 0), Payload5Num2 = CreateThread(0, 0, Payload5_num2, 0, 0, 0), Payload5Num3 = CreateThread(0, 0, Payload5_num3, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload5Num1); StopThread(Payload5Num2); StopThread(Payload5Num3);
    RefreshScreen();

    sound6();
    DrawIconsThread = CreateThread(0, 0, DrawIcons, 0, 0, 0), DrawCursorsThread = CreateThread(0, 0, DrawCursors, 0, 0, 0);
    HANDLE Payload6Num1 = CreateThread(0, 0, Payload6_num1, 0, 0, 0), Payload6Num2 = CreateThread(0, 0, Payload6_num2, 0, 0, 0), Payload6Num3 = CreateThread(0, 0, Payload6_num3, 0, 0, 0), Payload6Num4 = CreateThread(0, 0, Payload6_num4, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload6Num1); StopThread(Payload6Num2); StopThread(Payload6Num3); StopThread(Payload6Num4);
    StopThread(DrawIconsThread); StopThread(DrawCursorsThread); StopThread(CursorDrawIconThread);
    RefreshScreen();

    sound7();
    HANDLE Payload7Num1 = CreateThread(0, 0, Payload7_num1, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload7Num1);
    RefreshScreen();

    sound8();
    DrawIconsThread = CreateThread(0, 0, DrawIcons, 0, 0, 0), DrawCursorsThread = CreateThread(0, 0, DrawCursors, 0, 0, 0), CursorDrawIconThread = CreateThread(0, 0, CursorDrawIcon, 0, 0, 0);
    HANDLE Payload8Num1 = CreateThread(0, 0, Payload8_num1, 0, 0, 0), Payload8Num2 = CreateThread(0, 0, Payload8_num2, 0, 0, 0), Payload8Num3 = CreateThread(0, 0, Payload8_num3, 0, 0, 0), Payload8Num4 = CreateThread(0, 0, Payload8_num4, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload8Num1); StopThread(Payload8Num2); StopThread(Payload8Num3); StopThread(Payload8Num4);
    RefreshScreen();

    sound9();
    HANDLE Payload9Num1 = CreateThread(0, 0, Payload9_num1, 0, 0, 0), Payload9Num2 = CreateThread(0, 0, Payload9_num2, 0, 0, 0), Payload9Num3 = CreateThread(0, 0, Payload9_num3, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload9Num1); StopThread(Payload9Num2); StopThread(Payload9Num3);
    RefreshScreen();

    sound10();
    HANDLE Payload10Num1 = CreateThread(0, 0, Payload10_num1, 0, 0, 0), Payload10Num2 = CreateThread(0, 0, Payload10_num2, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload10Num1); StopThread(Payload10Num2);
    RefreshScreen();

    sound11();
    HANDLE Payload11Num1 = CreateThread(0, 0, Payload11_num1, 0, 0, 0);
    DrawTextsThread = CreateThread(0, 0, DrawTexts, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload11Num1);
    StopThread(DrawTextsThread);
    RefreshScreen();

    sound12();
    HANDLE Payload12Num1 = CreateThread(0, 0, Payload12_num1, 0, 0, 0), Payload12Num2 = CreateThread(0, 0, Payload12_num2, 0, 0, 0), Payload12Num3 = CreateThread(0, 0, Payload12_num3, 0, 0, 0), Payload12Num4 = CreateThread(0, 0, Payload12_num4, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload12Num1); StopThread(Payload12Num2); StopThread(Payload12Num3); StopThread(Payload12Num4);

    sound13();
    HANDLE Payload13Num1 = CreateThread(0, 0, Payload13_num1, 0, 0, 0), Payload13Num2 = CreateThread(0, 0, Payload13_num2, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload13Num1); StopThread(Payload13Num2);
    RefreshScreen();

    sound14();
    HANDLE Payload14Num1 = CreateThread(0, 0, Payload14_num1, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload14Num1);
    StopThread(DumbThread);
    RefreshScreen();

    sound15();
    HANDLE Payload15Num1 = CreateThread(0, 0, Payload15_num1, 0, 0, 0), Payload15Num2 = CreateThread(0, 0, Payload15_num2, 0, 0, 0);
    Sleep(30000);
    StopThread(Payload15Num1); StopThread(Payload15Num2);
    StopThread(CursorDrawIconThread); StopThread(DrawIconsThread); StopThread(DrawCursorsThread);
    RefreshScreen();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // This is my first time trying to no skid from other malwares.
    
    SetProcessDPIAware();
    if (MessageBoxA(NULL, "WARNING!\r\n\r\nYou are running a safety GDI malware called radiance.exe by camellia-y7x.\r\nThis malware will not destroy your computer. But it will show some cool effects on your screen and play some loud noises.\r\nIf you are running this program without the knowledge of what will this program do, Just click \"No\" to quit this malware.\r\n\r\nDo you want to execute this malware?", "First warning - radiance.exe (GDI only)", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
        if (MessageBoxA(NULL, "LAST WARNING!\r\n\r\nBefore you decide to continue execute radiance.exe, Please make sure you are running in virtual machine or a safe environment!\r\nIf you have photosensitive epilepsy, Please don't execute this malware!\r\n\r\nDo you really want to run this malware? camellia-y7x is not responsible for any damages by using this malware!", "LAST WARNING - radiance.exe (GDI only)", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
            RunPayload();
            ExitProcess(0);
        }
        else {
            ExitProcess(0);
        }
    }
    else {
        ExitProcess(0);
    }
}