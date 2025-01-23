#include "Nitrite.h"

// This got replaced with the safe version source code, kill me now

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
		if (MessageBoxW(NULL,
		L"You are now about to run the Nitrite.exe GDI Trojan made by NotCCR that will overwrite your boot sector, hide the taskbar, disable system tools, copy itself to system directories, spam the keyboard, move the mouse and move all active windows.\nThe creator of this GDI malware assumes no responsbility for any actions taken as a result of this malware.\n\nIf you\'re seeing this message without knowledge of what you executed, press \'\'No\'\' and your device will be left unharmed.\nIf you are running on a controlled environment, like a virtual machine that has been snapshotted, you may hit \'\'Yes\'\' to wipe this system out.\n\nRemember, NotCCR is not responsible for any damages made by running or reverse-engineering this malware.\nProceed to execute it? You may hit \'\'No\'\' at any time.", 
		L"GDI-Trojan.Win32.Nitrite", 
		MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
		
		if (MessageBoxW(NULL,
		L"THIS IS THE FINAL WARNING,\n\nAFTER YOUR RUN THIS, ALL YOUR DATA WILL BE LOST AND 64 SECTORS OF THE HARD DRIVE WILL BE OVERWRITTEN!\nEXECUTE IT?",
		L"LAST WARNING",
		MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES) exit(0);
	Sleep(3000);
	/*CreateThread(NULL, 0, Payloads::MoveCursor, NULL, 0, 0);
	CreateThread(NULL, 0, Payloads::MoveWindows, NULL, 0, 0);*/
	HANDLE hSS = CreateThread(NULL, 0, GDI::ScreenShake, NULL, 0, 0);
	Bytebeat::Audio1();
	Sleep(5000);
	HANDLE hIP = CreateThread(NULL, 0, GDI::InitialPixelation, NULL, 0, 0);
	Sleep(5000);
	HANDLE hGZ = CreateThread(NULL, 0, GDI::GlideZoomer, NULL, 0, 0);
	Sleep(10000);
	HANDLE hCD = CreateThread(NULL, 0, GDI::CursorDraw, NULL, 0, 0);
	Sleep(10000);
	EndPayload(hIP); EndPayload(hCD); EndPayload(hGZ);
	Redraw();
	Bytebeat::Audio2();
	HANDLE hAS = CreateThread(NULL, 0, GDI::AlphaSquares, NULL, 0, 0);
	HANDLE hCTO = CreateThread(NULL, 0, GDI::ChemicalTextOuts, NULL, 0, 0);
	HANDLE hSEEYA /* wtf */ = CreateThread(NULL, 0, GDI::SustainEpicEffectYetAgain, NULL, 0, 0);
	Sleep(25000);
	EndPayload(hSS); EndPayload(hAS); EndPayload(hCTO);
	Redraw();
	Bytebeat::Audio3();
	HANDLE hKE = CreateThread(NULL, 0, GDI::KaleidoscopeEffect, NULL, 0, 0);
	Sleep(15000);
	EndPayload(hSEEYA); EndPayload(hKE);
	Redraw();
//	CreateThread(NULL, 0, Payloads::Inputs, NULL, 0, 0);
	HANDLE hCube = CreateThread(NULL, 0, GDI::Cube3D, NULL, 0, 0);
	HANDLE hWE = CreateThread(NULL, 0, GDI::WaveEffect, NULL, 0, 0);
	HANDLE hPHSL = CreateThread(NULL, 0, GDI::PlasmaHSL, NULL, 0, 0);
	Bytebeat::Audio4();
	Sleep(30000);
	EndPayload(hWE); EndPayload(hPHSL);
	Redraw();
	HANDLE hWT = CreateThread(NULL, 0, GDI::WindowText, NULL, 0, 0);
	HANDLE hDark = CreateThread(NULL, 0, GDI::Darkening, NULL, 0, 0);
	Bytebeat::Audio5();
	Sleep(30000);
	EndPayload(hCube); EndPayload(hDark);
	Redraw();
	HANDLE hXOR = CreateThread(NULL, 0, GDI::XORRotozoomer, NULL, 0, 0);
	HANDLE hSSc = CreateThread(NULL, 0, GDI::ScreenShake, NULL, 0, 0);
	Bytebeat::Audio6();
	Sleep(15000);
	EndPayload(hWT); EndPayload(hSSc); EndPayload(hXOR);
	Redraw();
	HANDLE hAND = CreateThread(NULL, 0, GDI::ANDRotozoomer, NULL, 0, 0);
	Sleep(15000);
	EndPayload(hAND);
	Redraw();
	Sleep(2000);
//	EndPayload(hstr);
	CreateThread(NULL, 0, GDI::StaticNoise, NULL, 0, 0);
	Bytebeat::Audio7();
	Sleep(30000);
}
