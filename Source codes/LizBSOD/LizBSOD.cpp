typedef struct IUnknown IUnknown;
#include "LizBSOD.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
		if (MessageBoxW(NULL, L"LizBSOD\n\nThis is a joke program designed to CRASH your computer. Author UnknownException505 will not be responsible for any damage or dataloss.",
		L"lizzie mcgayire", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		if (MessageBoxW(NULL, L"LizBSOD\n\nLAST WARNING!\n\nAs the previous message said, It crashes Windows.\n\nProceed at your own risk if you know what you are doing.",
		L"gryfyfyfhfh", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
		
		Sleep(1000 * 5);
		
		LizBSOD();
}
