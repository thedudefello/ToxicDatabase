#include "Common.hpp"
#include "..\Resource\resource.h"

void* pWaveData;
float originalVolume;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    HANDLE hMap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1, "MegaP3rdey");
    if (hMap != NULL && GetLastError() == ERROR_ALREADY_EXISTS) { CloseHandle(hMap); return 1; }

    HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(IDR_WAVE1), "WAVE");
    if (hRes) { HGLOBAL hResData = LoadResource(hInstance, hRes); if (hResData) pWaveData = LockResource(hResData); }

    while (true) {
        Sleep(360000);

        originalVolume = GetCurrentVolume();
        SetVolume(1);

        PlaySound((LPCSTR)pWaveData, NULL, SND_MEMORY | SND_ASYNC);
        
        SetVolume(originalVolume);
    }

    if (hMap != NULL) CloseHandle(hMap);
    return 0;
}