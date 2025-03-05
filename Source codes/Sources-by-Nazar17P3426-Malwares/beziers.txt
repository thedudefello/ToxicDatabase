#include <windows.h>

int main(){
	int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    while(1){
    	HDC hdc = GetDC(0);
		POINT p[4]  = {rand() % sw, rand() % sh, rand() % sw, rand() % sh,  rand() % sw, rand() % sh};
        HPEN hPen = CreatePen(PS_SOLID,5,RGB(0,0,255));
        SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
    	DeleteObject(hPen);
		ReleaseDC(0, hdc);
	}
}