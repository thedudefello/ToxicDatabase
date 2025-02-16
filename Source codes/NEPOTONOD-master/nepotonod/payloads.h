#ifndef PAYLOADS
#define PAYLOADS

#include "nepotonod.h"

#define THREAD(name) DWORD WINAPI name(LPVOID lpParam)
#define PAYLOADFOOT return EXIT_SUCCESS;

// The actual payloads
THREAD(emptyPayload);
THREAD(captionsPayload);
THREAD(cursorPayload);
THREAD(trainPayload);
THREAD(glitchesPayload);
THREAD(iconsPayload);
THREAD(meltingPayload);
THREAD(invertPayload);

#endif

/*
===============================
ORIGINAL NEPOTONOD PAYLOADS
===============================
DWORD WINAPI pooDesktop(LPVOID lpParam);
DWORD WINAPI ohDesktop(LPVOID lpParam);
DWORD WINAPI messageBoxesPayload(LPVOID lpParam);
DWORD WINAPI captionsPayload(LPVOID lpParam);
DWORD WINAPI cursorPayload(LPVOID lpParam);
DWORD WINAPI killDesktop(LPVOID lpParam);
DWORD WINAPI trainPayload(LPVOID lpParam);
DWORD WINAPI invertedGlitchesPayload(LPVOID lpParam);
DWORD WINAPI errorsPayload(LPVOID lpParam);
DWORD WINAPI meltingPayload(LPVOID lpParam);
int invertDesktopAction();
DWORD WINAPI invertDesktopPayload(LPVOID lpParam);
DWORD WINAPI bouncingPayload(LPVOID lpParam);
*/
