#include "Common.hpp"

float GetCurrentVolume() {
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    IMMDevice* defaultDevice = NULL;
    IAudioEndpointVolume* endpointVolume = NULL;
    float currentVolume = 0.0f;

    CoInitialize(NULL);
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);

    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);

    endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

    endpointVolume->Release();
    defaultDevice->Release();
    deviceEnumerator->Release();

    CoUninitialize();
    return currentVolume;
}

void SetVolume(float volume) {
    IMMDeviceEnumerator* deviceEnumerator = NULL;
    IMMDevice* defaultDevice = NULL;
    IAudioEndpointVolume* endpointVolume = NULL;

    CoInitialize(NULL);
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&deviceEnumerator);

    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID*)&endpointVolume);

    endpointVolume->SetMasterVolumeLevelScalar(volume, NULL);

    endpointVolume->Release();
    defaultDevice->Release();
    deviceEnumerator->Release();

    CoUninitialize();
}