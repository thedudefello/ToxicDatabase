#include <windows.h>

int main(){
	while(1){
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc,10,10,w,h,hdc,12,12,SRCAND);
		BitBlt(hdc,10,10,w,h,hdc,12,12,SRCPAINT);
		BitBlt(hdc,10,20,w,h,hdc,12,1,SRCCOPY);
		Sleep(1);
		
	}
}
