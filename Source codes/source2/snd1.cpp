#include <Windows.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

int main(){
	PlaySoundW(L"snd1.wav", NULL, SND_FILENAME | SND_ASYNC);
	Sleep(-1);
}

