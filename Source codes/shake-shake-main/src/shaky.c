#pragma comment(lib, "User32.lib")
#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include "resource.h"
#include <stdio.h>

#define LEFT 1
#define RIGHT -1

void shaker(int direction, HWND window)
{
    RECT windowRect;
    GetWindowRect(window, &windowRect);
    long moveX = windowRect.left;

    if (direction == LEFT)
    { moveX += 10; }
    if (direction == RIGHT)
    { moveX -= 10; }

    SetWindowPos(window, NULL, moveX, windowRect.top, 0, 0, SWP_NOSIZE);
}

int main(int argc, char** argv)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

    int currDirection = LEFT;

    while (1)
    {
        Sleep(35);
        shaker(currDirection, GetForegroundWindow());

        switch (currDirection)
        {
        case LEFT:
            currDirection = RIGHT;
            break;

        case RIGHT:
            currDirection = LEFT;
            break;
        
        default:
            break;
        }
    }

    return 0;
} 