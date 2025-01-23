#include <Windows.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

int main(){
	PlaySoundW(L"bytebeat.wav", NULL, SND_LOOP | SND_ASYNC);
	Sleep(-1);
}

