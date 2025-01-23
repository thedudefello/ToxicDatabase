// DECOMPILED AND UNRAVELED BY CHECKSUM128
#include <math.h>
#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

void __cdecl sub_27A9(float *a1, float a2, float a3, float a4);
// int __userpurge sub_293F@<eax>(int a1, float a2, float a3, float a4);
_DWORD *__cdecl sub_2B82(_DWORD *a1, int a2, int a3);
int __cdecl sub_2BAD(_DWORD *a1, char a2);
int __cdecl sub_2BEB(_DWORD *a1);
int __cdecl sub_2C1F(int a1);
void __noreturn sub_2C82(); // weak
int __cdecl sub_2CDA(int a1, int a2, int a3, int a4);
int __cdecl sub_2D10(int a1, int a2, int a3, int a4);
void __cdecl sub_2D2C(int a1, int a2, int a3, int a4, int a5, int a6);
int __cdecl sub_2E5B(int a1, int a2, int a3, int a4, int a5, int a6);
int __cdecl sub_2F02(int a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9, int a10);
int __cdecl sub_33EC(int a1, int a2, int a3, int a4, int a5);
int __cdecl sub_378C(int a1, int a2);
int __cdecl sub_37E4(int a1, char a2, int a3, int a4, int a5, int a6);
int __cdecl sub_38E2(int a1, char a2, int a3, int a4, int a5);
int __cdecl sub_398C(int a1, char *a2, int a3, int a4, int a5);
__int64 __cdecl sub_39F5(int a1);
signed int __cdecl sub_3A26(int a1, signed int a2);
int __cdecl sub_3A5F(int a1);
int __cdecl sub_3B4B(unsigned __int8 a1, int a2, __int16 a3, char a4);
_BYTE *sub_3B87();
unsigned __int8 __cdecl sub_3BBC(unsigned __int16 a1);
int __cdecl sub_3BC5(unsigned __int16 a1, int a2);
int sub_3BD1();
void __noreturn sub_3BDA(); // weak
void sub_3BE1();
void sub_3BE7();
void __noreturn sub_3BF3(); // weak
int __cdecl sub_3C07(int a1, int a2);
int sub_3C2C();
int sub_3CB2();
int sub_3E68();
int sub_4340();
double __cdecl sub_4357(double a1);
double __cdecl sub_438F(float); // weak
double __cdecl sub_4439(float a1, float a2);
double __cdecl sub_455E(float a1);
double __cdecl sub_457C(float a1);
double __cdecl sub_459A(double a1, double a2);
int sub_45DC();
__int64 __cdecl sub_4620(unsigned int a1, int a2, __int64 a3);
_BYTE *__cdecl sub_465B(_BYTE *a1, char a2, __int64 a3);
_DWORD *__cdecl sub_46B3(_DWORD *a1);
unsigned int __cdecl sub_46F1(unsigned int *a1, unsigned int a2);
int __cdecl sub_4749(int *a1, unsigned int a2, int a3);
unsigned __int8 sub_489B();
// int __usercall sub_49C7@<eax>(unsigned __int8 a1@<al>, char a2@<dl>, __int16 a3@<cx>);
int sub_4A38();
int __cdecl sub_4A7B(__int16 a1, int a2);
int __cdecl sub_4AA1(int a1);
unsigned int __cdecl sub_4AC8(unsigned int a1);
unsigned int __cdecl sub_4ADC(int a1, unsigned int a2);
int __cdecl sub_4D09(__int16 a1);
int sub_4D90();
int __cdecl sub_4E55(_BYTE *a1, int a2);
int __cdecl sub_4EA0(_BYTE *a1, int a2);
// int __usercall sub_4EEE@<eax>(int result@<eax>, _BYTE *a2, char *a3, char a4);
int __cdecl sub_4F60(int a1);
int sub_4F90();
int sub_4F9A();


//----- (000027A9) --------------------------------------------------------
void __cdecl sub_27A9(float *a1, float a2, float a3, float a4)
{
  float v4; // [esp+18h] [ebp-Ch]
  float v5; // [esp+18h] [ebp-Ch]
  float v6; // [esp+18h] [ebp-Ch]
  float v7; // [esp+18h] [ebp-Ch]
  float v8; // [esp+18h] [ebp-Ch]
  float v9; // [esp+18h] [ebp-Ch]

  v4 = sub_457C(a2) * a1[1];
  a1[1] = v4 - sub_455E(a2) * a1[2];
  v5 = sub_455E(a2) * a1[1];
  a1[2] = sub_457C(a2) * a1[2] + v5;
  v6 = sub_457C(a3) * *a1;
  *a1 = sub_455E(a3) * a1[2] + v6;
  v7 = -sub_455E(a3) * *a1;
  a1[2] = sub_457C(a3) * a1[2] + v7;
  v8 = sub_457C(a4) * *a1;
  *a1 = v8 - sub_455E(a4) * a1[1];
  v9 = sub_455E(a4) * *a1;
  a1[1] = sub_457C(a4) * a1[1] + v9;
}

//----- (0000293F) --------------------------------------------------------
int __userpurge sub_293F@<eax>(int a1, float a2, float a3, float a4)
{
  double v4; // st7
  double v5; // st5
  double v6; // st4
  bool v7; // cc
  double v8; // st7
  double v9; // st6
  double v10; // st5
  double v11; // st7
  double v12; // st4
  double v13; // st3
  double v14; // st6
  double v15; // st6
  double v16; // st6
  double v17; // st5
  double v18; // rtt
  double v19; // st5
  double v20; // st6
  double v21; // st6
  double v22; // st5
  double v23; // rt0
  double v24; // st4
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // rt2
  double v29; // st4
  double v30; // rt1
  double v31; // st4
  double v32; // rt1
  double v33; // st3
  double v34; // st4
  double v35; // st6
  float v37; // [esp+10h] [ebp-38h]
  double v38; // [esp+18h] [ebp-30h]
  double v39; // [esp+20h] [ebp-28h]
  double v40; // [esp+28h] [ebp-20h]
  float v41; // [esp+30h] [ebp-18h]
  float v42; // [esp+3Ch] [ebp-Ch]

  v4 = a2;
  if ( a2 <= (double)MEMORY[0x1047E0] && v4 >= 0.0 )
  {
    v5 = MEMORY[0x1047E4];
    if ( a3 <= (double)MEMORY[0x1047E4] && a3 >= 0.0 && a4 <= v5 && a4 >= 0.0 )
    {
      v6 = a4 / v5;
      v40 = v6 * (a3 / v5);
      v37 = v40;
      v38 = MEMORY[0x1047EC];
      v39 = v4 / MEMORY[0x1047E8];
      v7 = sub_459A(v39, MEMORY[0x1047EC]) - 1.0 >= 0.0;
      v8 = sub_459A(v39, v38);
      v9 = a2;
      if ( v7 )
      {
        v10 = 1.0 - (v8 - 1.0);
        v11 = v37;
      }
      else
      {
        v10 = v8 - 1.0 + 1.0;
        v11 = v37;
      }
      v42 = v10 * v40;
      v41 = v6;
      v12 = v41 - v11;
      if ( v9 >= 0.0 && MEMORY[0x1047E8] > v9 )
      {
        v19 = v12;
        v21 = v42;
      }
      else
      {
        if ( v9 < MEMORY[0x1047E8] )
        {
          v13 = a2;
          v14 = MEMORY[0x1047F0];
LABEL_17:
          if ( v13 < v14 )
          {
            v15 = MEMORY[0x1047F4];
          }
          else
          {
            if ( MEMORY[0x1047F4] > v13 )
            {
              v19 = v12;
              v26 = v42;
LABEL_33:
              v29 = v11;
              v25 = v26;
              v30 = v29;
              v24 = 0.0;
              v21 = v30;
              goto LABEL_37;
            }
            v15 = MEMORY[0x1047F4];
          }
          if ( v13 < v15 )
          {
            v16 = MEMORY[0x1047F8];
            goto LABEL_25;
          }
          if ( MEMORY[0x1047F8] <= v13 )
          {
            v16 = MEMORY[0x1047F8];
LABEL_25:
            if ( v13 < v16 )
            {
              v19 = v12;
              v20 = v42;
            }
            else if ( MEMORY[0x1047FC] <= v13 )
            {
              v19 = v12;
              v20 = v42;
            }
            else
            {
              v17 = v11;
              v11 = v42;
              v18 = v17;
              v19 = v12;
              v20 = v18;
            }
            v31 = v20;
            v21 = 0.0;
            v32 = v31;
            v24 = v11;
            v25 = v32;
            goto LABEL_37;
          }
          v27 = v11;
          v11 = v42;
          v28 = v27;
          v19 = v12;
          v26 = v28;
          goto LABEL_33;
        }
        if ( MEMORY[0x1047F0] <= v9 )
        {
          v13 = a2;
          v14 = MEMORY[0x1047F0];
          goto LABEL_17;
        }
        v22 = v11;
        v11 = v42;
        v23 = v22;
        v19 = v12;
        v21 = v23;
      }
      v24 = v11;
      v25 = 0.0;
LABEL_37:
      *(_WORD *)(a1 + 2) = 0;
      v33 = (v24 + v19) * MEMORY[0x104800];
      v34 = v21;
      v35 = MEMORY[0x104800];
      *(_BYTE *)a1 = (int)v33;
      *(_BYTE *)(a1 + 1) = (int)((v34 + v19) * v35);
      *(_BYTE *)(a1 + 2) = (int)((v25 + v19) * v35);
      return a1;
    }
  }
  *(_DWORD *)a1 = 0;
  return a1;
}

//----- (00002B82) --------------------------------------------------------
_DWORD *__cdecl sub_2B82(_DWORD *a1, int a2, int a3)
{
  _DWORD *result; // eax

  result = a1;
  a1[3] = a2;
  a1[4] = a2;
  *a1 = a3;
  a1[5] = 0;
  a1[1] = 0;
  a1[2] = 0;
  return result;
}

//----- (00002BAD) --------------------------------------------------------
int __cdecl sub_2BAD(_DWORD *a1, char a2)
{
  int result; // eax
  int v3; // edx
  bool v4; // zf

  if ( a1[4] )
  {
    *(_BYTE *)(*a1 + a1[1]) = a2;
    v3 = a1[1] + 1;
    v4 = v3 == a1[3];
    a1[1] = v3;
    if ( v4 )
      a1[1] = 0;
    --a1[4];
    result = 0;
  }
  else
  {
    a1[5] |= 1u;
    result = -1;
  }
  return result;
}

//----- (00002BEB) --------------------------------------------------------
int __cdecl sub_2BEB(_DWORD *a1)
{
  int result; // eax
  int v2; // ebx
  int v3; // esi
  int v4; // edx
  int v5; // edx

  result = -1;
  v2 = a1[4];
  v3 = a1[3];
  if ( v2 != v3 )
  {
    v4 = a1[2];
    result = *(unsigned __int8 *)(*a1 + v4);
    v5 = v4 + 1;
    if ( v3 == v5 )
      v5 = 0;
    a1[2] = v5;
    a1[4] = v2 + 1;
  }
  return result;
}

//----- (00002C1F) --------------------------------------------------------
int __cdecl sub_2C1F(int a1)
{
  return *(_DWORD *)(a1 + 12) - *(_DWORD *)(a1 + 16);
}

//----- (00002C82) --------------------------------------------------------
void __noreturn sub_2C82()
{
  MEMORY[0x1076C0] = 23;
  MEMORY[0x1076C2] = 1078984;
  MEMORY[0x1076C8] = 0;
  MEMORY[0x1076CC] = 0;
  MEMORY[0x1076D0] = 0xFFFF;
  MEMORY[0x1076D4] = 13605376;
  MEMORY[0x1076D8] = 0xFFFF;
  MEMORY[0x1076DC] = 13603328;
  __lgdt((void *)0x1076C0);
  JUMPOUT(0x10467C);
}
// 4FF5: control flows out of bounds to 10467C
// 2C82: using guessed type void __noreturn sub_2C82();

//----- (00002CDA) --------------------------------------------------------
int __cdecl sub_2CDA(int a1, int a2, int a3, int a4)
{
  int result; // eax

  result = ((unsigned __int8)a4 << 16) | a4 & 0xFF00 | BYTE2(a4);
  *(_DWORD *)(a1 + 4 * (a2 + a3 * MEMORY[0x8412])) = result;
  return result;
}

//----- (00002D10) --------------------------------------------------------
int __cdecl sub_2D10(int a1, int a2, int a3, int a4)
{
  int result; // eax

  result = a2 + a3 * MEMORY[0x8412];
  *(_DWORD *)(a1 + 4 * result) = a4;
  return result;
}

//----- (00002D2C) --------------------------------------------------------
void __cdecl sub_2D2C(int a1, int a2, int a3, int a4, int a5, int a6)
{
  unsigned int v6; // edi
  int v7; // ebx
  unsigned int v8; // esi
  double v9; // st7
  unsigned int v10; // eax
  float v11; // [esp+0h] [ebp-48h]
  float v12; // [esp+4h] [ebp-44h]
  float v13; // [esp+14h] [ebp-34h]
  float v14; // [esp+18h] [ebp-30h]

  v6 = 0;
  v7 = (__int64)sub_4357((double)((a5 - a3) * (a5 - a3) + (a4 - a2) * (a4 - a2)));
  v12 = (float)(a4 - a2);
  v11 = (float)(a5 - a3);
  v13 = sub_4439(v11, v12);
  while ( v6 != v7 )
  {
    v14 = (float)v6;
    v8 = (__int64)(sub_457C(v13) * v14 + (double)a2);
    v9 = sub_455E(v13);
    if ( v8 < MEMORY[0x8412] )
    {
      v10 = (__int64)(v9 * v14 + (double)a3);
      if ( v10 < MEMORY[0x8414] )
        *(_DWORD *)(a1 + 4 * (MEMORY[0x8412] * v10 + v8)) = BYTE2(a6) | ((unsigned __int8)a6 << 16) | a6 & 0xFF00;
    }
    ++v6;
  }
}

//----- (00002E5B) --------------------------------------------------------
int __cdecl sub_2E5B(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int i; // ecx

  result = ((unsigned __int8)a6 << 16) | a6 & 0xFF00 | BYTE2(a6);
  while ( a4 > a2 )
  {
    for ( i = a3; a5 > i; ++i )
    {
      if ( a2 >= 0 && i >= 0 && MEMORY[0x8412] > a2 && MEMORY[0x8414] > i )
        *(_DWORD *)(a1 + 4 * (a2 + i * MEMORY[0x8412])) = result;
    }
    ++a2;
  }
  return result;
}

//----- (00002F02) --------------------------------------------------------
int __cdecl sub_2F02(int a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8, double a9, int a10)
{
  int v10; // edx
  int result; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st5
  double v18; // st4
  double v19; // st6
  double v20; // st4
  double v21; // st6
  double v22; // st4
  double v23; // rt0
  double v24; // st4
  int v25; // edi
  double v26; // st3
  double v27; // st6
  int v28; // edx
  double v29; // st4
  double v30; // st3
  double v31; // rt1
  double v32; // st4
  double v33; // st5
  double v34; // st3
  double v35; // rt2
  double v36; // st3
  double v37; // rt0
  double v38; // st2
  double v39; // st0
  double v40; // rt2
  double v41; // st3
  double v42; // st4
  double v43; // rtt
  double v44; // st5
  double v45; // rt0
  double v46; // st3
  double v47; // st6
  double v48; // rtt
  double v49; // st2
  double v50; // rt2
  double v51; // st3
  int v52; // edx
  double v53; // st4
  double v54; // st3
  double v55; // st1
  double v56; // rtt
  double v57; // st3
  double v58; // st5
  double v59; // rt1
  double v60; // st2
  double v61; // st0
  double v62; // st4
  double v63; // st3
  double v64; // st6
  double v65; // rt0
  double v66; // st2
  int i; // edx
  double v68; // st6
  double v69; // st4
  double v70; // st3
  double v71; // st5
  double v72; // st5
  double v73; // st3
  double v74; // st6
  double v75; // rt1
  double v76; // st5
  double v77; // st7
  double v78; // rtt
  double v79; // rt1
  int v80; // [esp+24h] [ebp-84h]
  int v81; // [esp+24h] [ebp-84h]
  double v82; // [esp+28h] [ebp-80h]
  double v83; // [esp+30h] [ebp-78h]
  double v84; // [esp+38h] [ebp-70h]
  double v85; // [esp+40h] [ebp-68h]
  int v86; // [esp+40h] [ebp-68h]
  double v87; // [esp+48h] [ebp-60h]
  double v88; // [esp+50h] [ebp-58h]
  double v89; // [esp+58h] [ebp-50h]
  double v90; // [esp+60h] [ebp-48h]
  double v91; // [esp+68h] [ebp-40h]
  double v92; // [esp+70h] [ebp-38h]
  double v93; // [esp+78h] [ebp-30h]
  double v94; // [esp+80h] [ebp-28h]
  double v95; // [esp+88h] [ebp-20h]

  v10 = 3;
  v88 = a2;
  v89 = a4;
  v90 = a6;
  v91 = a8;
  v92 = a3;
  v93 = a5;
  v94 = a7;
  v95 = a9;
  do
  {
    result = 0;
    while ( v10 > result )
    {
      v12 = *(&v88 + result++);
      v13 = v12;
      v14 = *(&v88 + result);
      if ( v13 >= v14 )
      {
        *(&v87 + result) = v14;
        *(&v88 + result) = v13;
        v15 = *(&v91 + result);
        *(&v91 + result) = *(&v92 + result);
        *(&v92 + result) = v15;
      }
    }
    --v10;
  }
  while ( v10 );
  v84 = v89;
  v16 = v95;
  v82 = v91;
  v17 = v92;
  v85 = v88;
  v18 = v88 - v91;
  v19 = v18;
  if ( v18 == 0.0 )
  {
    v20 = v95;
    if ( v92 > v95 )
      v20 = v92;
  }
  else
  {
    v20 = (v92 - v95) / v18 * (v89 - v88) + v92;
  }
  v83 = v90;
  if ( v19 == 0.0 )
  {
    v21 = v20;
    v22 = v95;
    if ( v92 > v95 )
      v22 = v92;
  }
  else
  {
    v23 = v20;
    v24 = (v92 - v95) / v19 * (v90 - v88);
    v21 = v23;
    v22 = v24 + v92;
  }
  if ( v93 < v21 )
  {
    v26 = v21;
    v27 = v93;
  }
  else
  {
    v25 = 1;
    if ( v94 >= v22 )
    {
      v27 = v93;
      goto LABEL_24;
    }
    v26 = v21;
    v27 = v93;
  }
  v25 = 0;
  if ( v26 >= v27 )
  {
    result = v22 >= v94;
    v25 = result;
  }
LABEL_24:
  LOWORD(result) = HIWORD(v87) | 0xC00;
  WORD2(v87) = HIWORD(v87) | 0xC00;
  LODWORD(v87) = (int)v88;
  v28 = (int)v88;
  while ( 1 )
  {
    v29 = (double)v28;
    if ( v84 < v29 )
      break;
    v30 = v85 - v84;
    if ( v30 == 0.0 )
    {
      v31 = v29;
      v32 = v17;
      v33 = v31;
      v34 = v27;
      if ( v32 > v27 )
        v34 = v32;
    }
    else
    {
      v35 = (v17 - v27) / v30 * (v29 - v85) + v17;
      v36 = v17;
      v33 = v29;
      v37 = v36;
      v34 = v35;
      v32 = v37;
    }
    v38 = *(&v92 + v25 + 2);
    v39 = v85 - *(&v88 + v25 + 2);
    if ( v39 == 0.0 )
    {
      v40 = v34;
      v41 = v32;
      v42 = v40;
      if ( v41 <= v38 )
      {
        v50 = v41;
        v51 = v42;
        v32 = v50;
        v44 = v51;
        v46 = v27;
        v47 = v38;
      }
      else
      {
        v43 = v42;
        v32 = v41;
        v44 = v43;
        v45 = v41;
        v46 = v27;
        v47 = v45;
      }
    }
    else
    {
      v48 = (v32 - v38) / v39;
      v49 = v33 - v85;
      v44 = v34;
      v46 = v27;
      v47 = v48 * v49 + v32;
    }
    v80 = v28;
    LODWORD(v87) = (int)v44;
    sub_2D2C(a1, v28, (int)v44, v28, (int)v47, a10);
    LOWORD(result) = HIWORD(v87) | 0xC00;
    v27 = v46;
    v17 = v32;
    v28 = v80 + 1;
    WORD2(v87) = HIWORD(v87) | 0xC00;
  }
  LODWORD(v87) = (int)v84;
  v52 = (int)v84;
  while ( 1 )
  {
    v53 = (double)v52;
    if ( v83 < v53 )
      break;
    v54 = *(&v92 + v25 + 2);
    v55 = v85 - *(&v88 + v25 + 2);
    if ( v55 == 0.0 )
    {
      v56 = v54;
      v57 = v17;
      v58 = v56;
      if ( v57 <= v56 )
      {
        v59 = v57;
        v57 = v58;
        v17 = v59;
      }
      else
      {
        v17 = v57;
      }
    }
    else
    {
      v57 = (v17 - v54) / v55 * (v53 - v85) + v17;
    }
    v60 = *(&v92 + 3 - v25);
    v61 = v84 - *(&v88 + 3 - v25);
    if ( v61 == 0.0 )
    {
      v62 = v57;
      v63 = v27;
      v64 = v60;
      if ( v63 > v60 )
        v64 = v63;
    }
    else
    {
      v65 = (v27 - v60) / v61;
      v66 = v53 - v84;
      v62 = v57;
      v63 = v27;
      v64 = v65 * v66 + v27;
    }
    v81 = v52;
    LODWORD(v87) = (int)v62;
    sub_2D2C(a1, v52, (int)v62, v52, (int)v64, a10);
    LOWORD(result) = HIWORD(v87) | 0xC00;
    v27 = v63;
    v52 = v81 + 1;
    WORD2(v87) = HIWORD(v87) | 0xC00;
  }
  LODWORD(v87) = (int)v83;
  for ( i = (int)v83; ; i = v86 + 1 )
  {
    v68 = (double)i;
    if ( v82 < v68 )
      break;
    v69 = *(&v92 + 1 - v25);
    v70 = *(&v88 + 1 - v25);
    v71 = v70 - v82;
    if ( v71 == 0.0 )
    {
      v72 = v69;
      if ( v69 <= v16 )
        v72 = v16;
    }
    else
    {
      v72 = (v69 - v16) / v71 * (v68 - v70) + v69;
    }
    v73 = v83 - v82;
    if ( v73 == 0.0 )
    {
      if ( v94 > v16 )
      {
        v74 = v94;
        v79 = v72;
        v76 = v16;
        v77 = v79;
      }
      else
      {
        v74 = v16;
        v75 = v72;
        v76 = v16;
        v77 = v75;
      }
    }
    else
    {
      v74 = (v94 - v16) / v73 * (v68 - v83) + v94;
      v78 = v72;
      v76 = v16;
      v77 = v78;
    }
    v86 = i;
    WORD2(v87) = HIWORD(v87) | 0xC00;
    LODWORD(v87) = (int)v77;
    sub_2D2C(a1, i, (int)v77, i, (int)v74, a10);
    v16 = v76;
  }
  return result;
}

//----- (000033EC) --------------------------------------------------------
int __cdecl sub_33EC(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // eax
  int v6; // ebx

  v5 = a2;
  v6 = a3;
  if ( a2 >= a3 )
  {
    v5 = a3;
    v6 = a2;
  }
  while ( v6 >= v5 )
  {
    if ( v5 >= 0 && MEMORY[0x8412] > v5 && a4 >= 0 && MEMORY[0x8414] > a4 )
      *(_DWORD *)(a1 + 4 * (v5 + a4 * MEMORY[0x8412])) = BYTE2(a5) | a5 & 0xFF00 | ((unsigned __int8)a5 << 16);
    ++v5;
  }
  return BYTE2(a5) | a5 & 0xFF00 | ((unsigned __int8)a5 << 16);
}

//----- (0000378C) --------------------------------------------------------
int __cdecl sub_378C(int a1, int a2)
{
  int v2; // ebx
  int result; // eax
  int i; // esi
  int v5; // edx

  v2 = 0;
  result = ((unsigned __int8)a2 << 16) | a2 & 0xFF00 | BYTE2(a2);
  while ( MEMORY[0x8412] > v2 )
  {
    for ( i = 0; MEMORY[0x8414] > i; ++i )
    {
      v5 = i * MEMORY[0x8412];
      *(_DWORD *)(a1 + 4 * (v2 + v5)) = result;
    }
    ++v2;
  }
  return result;
}

//----- (000037E4) --------------------------------------------------------
int __cdecl sub_37E4(int a1, char a2, int a3, int a4, int a5, int a6)
{
  int v6; // edi
  int result; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebx
  int v11; // esi
  int v12; // edx
  int v13; // [esp+Ch] [ebp-30h]
  int v14[11]; // [esp+10h] [ebp-2Ch] BYREF

  qmemcpy(v14, (const void *)0x104820, 0x20u);
  v6 = 0;
  result = a4;
  do
  {
    v8 = 0;
    v13 = result - 11;
    do
    {
      v9 = v8 + a3;
      if ( (*(unsigned __int8 *)(16 * (a2 - 31) + v6 + 1077248) & v14[v8]) != 0 )
      {
        if ( v9 >= 0 && MEMORY[0x8412] > v9 && result > 11 && MEMORY[0x8414] >= v13 )
        {
          v10 = a1;
          v11 = v9 + MEMORY[0x8412] * (result - 12);
          v12 = BYTE2(a5) | a5 & 0xFF00 | ((unsigned __int8)a5 << 16);
LABEL_14:
          *(_DWORD *)(v10 + 4 * v11) = v12;
          goto LABEL_15;
        }
      }
      else if ( v9 >= 0 && MEMORY[0x8412] > v9 && result > 11 && MEMORY[0x8414] >= v13 )
      {
        v10 = a1;
        v11 = v9 + MEMORY[0x8412] * (result - 12);
        v12 = BYTE2(a6) | a6 & 0xFF00 | ((unsigned __int8)a6 << 16);
        goto LABEL_14;
      }
LABEL_15:
      ++v8;
    }
    while ( v8 != 8 );
    ++v6;
    ++result;
  }
  while ( v6 != 16 );
  return result;
}

//----- (000038E2) --------------------------------------------------------
int __cdecl sub_38E2(int a1, char a2, int a3, int a4, int a5)
{
  int v5; // ebx
  int result; // eax
  int v8; // esi
  int v9[11]; // [esp+Ch] [ebp-2Ch] BYREF

  v5 = 0;
  qmemcpy(v9, (const void *)0x104820, 0x20u);
  do
  {
    result = 0;
    do
    {
      if ( (*(unsigned __int8 *)(16 * (a2 - 31) + v5 + 1077248) & v9[result]) != 0 )
      {
        v8 = a3 + result;
        if ( a3 + result >= 0 && MEMORY[0x8412] > v8 && a4 > 11 && MEMORY[0x8414] >= a4 - 11 )
          *(_DWORD *)(a1 + 4 * (v8 + MEMORY[0x8412] * (a4 - 12))) = BYTE2(a5) | ((unsigned __int8)a5 << 16) | a5 & 0xFF00;
      }
      ++result;
    }
    while ( result != 8 );
    ++v5;
    ++a4;
  }
  while ( v5 != 16 );
  return result;
}

//----- (0000398C) --------------------------------------------------------
int __cdecl sub_398C(int a1, char *a2, int a3, int a4, int a5)
{
  int result; // eax
  int v8; // [esp-Ch] [ebp-14h]

  while ( 1 )
  {
    result = *a2++;
    if ( !(_BYTE)result )
      break;
    v8 = a3;
    a3 += 8;
    sub_38E2(a1, result, v8, a4, a5);
  }
  return result;
}

//----- (000039F5) --------------------------------------------------------
__int64 __cdecl sub_39F5(int a1)
{
  return sub_4620(MEMORY[0x8428], a1, 4 * MEMORY[0x8414] * (unsigned int)MEMORY[0x8412]);
}

//----- (00003A26) --------------------------------------------------------
signed int __cdecl sub_3A26(int a1, signed int a2)
{
  signed int result; // eax

  MEMORY[0x1076E4] = sub_46F1(0, a2);
  for ( result = 0; result < a2; ++result )
    *(_BYTE *)(MEMORY[0x1076E4] + result) = *(_BYTE *)(a1 + result);
  return result;
}

//----- (00003A5F) --------------------------------------------------------
int __cdecl sub_3A5F(int a1)
{
  double v1; // st7
  int result; // eax
  float v3[3]; // [esp-Ch] [ebp-44h] BYREF
  int v4[2]; // [esp+Ch] [ebp-2Ch] BYREF
  float v5[3]; // [esp+14h] [ebp-24h] BYREF

  v1 = MEMORY[0x104840] + MEMORY[0x107600];
  if ( MEMORY[0x104844] < v1 )
    v1 = v1 - MEMORY[0x104844];
  v5[0] = v1;
  v5[1] = MEMORY[0x104848];
  v5[2] = MEMORY[0x104848];
  qmemcpy(v3, v5, sizeof(v3));
  sub_293F((int)v4, v3[0], v3[1], v3[2]);
  sub_2E5B(a1, 0, MEMORY[0x8414] - 16, MEMORY[0x8412], MEMORY[0x8414], v4[0]);
  qmemcpy(v3, (const void *)0x107600, sizeof(v3));
  sub_293F((int)v4, v3[0], v3[1], v3[2]);
  result = sub_398C(a1, MEMORY[0x1076E4], MEMORY[0x8412] - MEMORY[0x1076E0], MEMORY[0x8414] - 4, v4[0]);
  if ( MEMORY[0x104844] <= (double)MEMORY[0x107600] )
    MEMORY[0x107600] = 0;
  else
    MEMORY[0x107600] = MEMORY[0x107600] + MEMORY[0x10484C];
  ++MEMORY[0x1076E0];
  return result;
}

//----- (00003B4B) --------------------------------------------------------
int __cdecl sub_3B4B(unsigned __int8 a1, int a2, __int16 a3, char a4)
{
  int result; // eax

  result = a1;
  *(_WORD *)(8 * a1 + 0x107720) = a2;
  *(_BYTE *)(8 * a1 + 0x107724) = 0;
  *(_WORD *)(8 * a1 + 0x107726) = HIWORD(a2);
  *(_WORD *)(8 * a1 + 0x107722) = a3;
  *(_BYTE *)(8 * a1 + 0x107725) = a4;
  return result;
}

//----- (00003B87) --------------------------------------------------------
_BYTE *sub_3B87()
{
  _BYTE *result; // eax

  MEMORY[0x107700] = 2047;
  MEMORY[0x107702] = 1079072;
  result = sub_465B((_BYTE *)0x107720, 0, 2048i64);
  __lidt((void *)0x107700);
  return result;
}

//----- (00003BBC) --------------------------------------------------------
unsigned __int8 __cdecl sub_3BBC(unsigned __int16 a1)
{
  return __inbyte(a1);
}

//----- (00003BC5) --------------------------------------------------------
int __cdecl sub_3BC5(unsigned __int16 a1, int a2)
{
  int result; // eax

  result = a2;
  __outbyte(a1, a2);
  return result;
}

//----- (00003BD1) --------------------------------------------------------
int sub_3BD1()
{
  int result; // eax

  result = 0;
  __outbyte(0x80u, 0);
  return result;
}

//----- (00003BDA) --------------------------------------------------------
void __noreturn sub_3BDA()
{
  _enable();
  __halt();
}
// 3BDA: using guessed type void __noreturn sub_3BDA();

//----- (00003BE1) --------------------------------------------------------
void sub_3BE1()
{
  _enable();
}

//----- (00003BE7) --------------------------------------------------------
void sub_3BE7()
{
  _disable();
}

//----- (00003BF3) --------------------------------------------------------
void __noreturn sub_3BF3()
{
  unsigned __int8 i; // al

  for ( i = 2; (i & 2) != 0; i = __inbyte(0x64u) )
    ;
  __outbyte(0x64u, 0xFEu);
  __halt();
}
// 3BF3: using guessed type void __noreturn sub_3BF3();

//----- (00003C07) --------------------------------------------------------
int __cdecl sub_3C07(int a1, int a2)
{
  int result; // eax

  result = a1;
  *(_DWORD *)(4 * a1 + 0x107F20) = a2;
  return result;
}

//----- (00003C2C) --------------------------------------------------------
int sub_3C2C()
{
  sub_3BC5(0x20u, 17);
  sub_3BC5(0xA0u, 17);
  sub_3BC5(0x21u, 32);
  sub_3BC5(0xA1u, 40);
  sub_3BC5(0x21u, 4);
  sub_3BC5(0xA1u, 2);
  sub_3BC5(0x21u, 1);
  sub_3BC5(0xA1u, 1);
  sub_3BC5(0x21u, 0);
  return sub_3BC5(0xA1u, 0);
}

//----- (00003CB2) --------------------------------------------------------
int sub_3CB2()
{
  sub_3C2C();
  sub_3B4B(0x20u, 1066512, 8, 142);
  sub_3B4B(0x21u, 1066519, 8, 142);
  sub_3B4B(0x22u, 1066526, 8, 142);
  sub_3B4B(0x23u, 1066533, 8, 142);
  sub_3B4B(0x24u, 1066540, 8, 142);
  sub_3B4B(0x25u, 1066547, 8, 142);
  sub_3B4B(0x26u, 1066554, 8, 142);
  sub_3B4B(0x27u, 1066561, 8, 142);
  sub_3B4B(0x28u, 1066568, 8, 142);
  sub_3B4B(0x29u, 1066575, 8, 142);
  sub_3B4B(0x2Au, 1066582, 8, 142);
  sub_3B4B(0x2Bu, 1066589, 8, 142);
  sub_3B4B(0x2Cu, 1066596, 8, 142);
  sub_3B4B(0x2Du, 1066603, 8, 142);
  sub_3B4B(0x2Eu, 1066610, 8, 142);
  return sub_3B4B(0x2Fu, 1066617, 8, 142);
}

//----- (00003E68) --------------------------------------------------------
int sub_3E68()
{
  sub_3B4B(0, 1066672, 8, 142);
  sub_3B4B(1u, 1066682, 8, 142);
  sub_3B4B(2u, 1066692, 8, 142);
  sub_3B4B(3u, 1066702, 8, 142);
  sub_3B4B(4u, 1066712, 8, 142);
  sub_3B4B(5u, 1066722, 8, 142);
  sub_3B4B(6u, 1066732, 8, 142);
  sub_3B4B(7u, 1066742, 8, 142);
  sub_3B4B(8u, 1066752, 8, 142);
  sub_3B4B(9u, 1066760, 8, 142);
  sub_3B4B(0xAu, 1066770, 8, 142);
  sub_3B4B(0xBu, 1066778, 8, 142);
  sub_3B4B(0xCu, 1066786, 8, 142);
  sub_3B4B(0xDu, 1066794, 8, 142);
  sub_3B4B(0xEu, 1066799, 8, 142);
  sub_3B4B(0xFu, 1066804, 8, 142);
  sub_3B4B(0x10u, 1066811, 8, 142);
  sub_3B4B(0x11u, 1066818, 8, 142);
  sub_3B4B(0x12u, 1066825, 8, 142);
  sub_3B4B(0x13u, 1066832, 8, 142);
  sub_3B4B(0x14u, 1066839, 8, 142);
  sub_3B4B(0x15u, 1066846, 8, 142);
  sub_3B4B(0x16u, 1066853, 8, 142);
  sub_3B4B(0x17u, 1066860, 8, 142);
  sub_3B4B(0x18u, 1066867, 8, 142);
  sub_3B4B(0x19u, 1066874, 8, 142);
  sub_3B4B(0x1Au, 1066881, 8, 142);
  sub_3B4B(0x1Bu, 1066888, 8, 142);
  sub_3B4B(0x1Cu, 1066895, 8, 142);
  sub_3B4B(0x1Du, 1066902, 8, 142);
  sub_3B4B(0x1Eu, 1066909, 8, 142);
  return sub_3B4B(0x1Fu, 1066916, 8, 142);
}

//----- (00004340) --------------------------------------------------------
int sub_4340()
{
  return sub_3C07(1, 1063198);
}

//----- (00004357) --------------------------------------------------------
double __cdecl sub_4357(double a1)
{
  double v1; // st6
  double v2; // st5

  if ( a1 < 0.0 )
    return 0.0;
  v1 = 1.0;
  if ( a1 > 1.0 )
    v1 = a1;
  do
  {
    v2 = v1;
    v1 = (a1 / v1 + v1) * MEMORY[0x105964];
  }
  while ( v2 > v1 );
  return v2;
}

//----- (0000438F) --------------------------------------------------------
double __cdecl sub_438F(float a1)
{
  double result; // st7
  double v2; // st6
  int i; // eax
  double v4; // st7
  double v5; // st6
  float v6; // [esp+0h] [ebp-28h]

  if ( a1 >= 0.0 )
  {
    v2 = a1;
    result = 0.0;
    if ( a1 != 0.0 )
    {
      for ( i = 1; i != 27; ++i )
      {
        if ( *(float *)(4 * i + 0x104EA0) >= v2 )
        {
          v4 = (v2 - *(float *)(4 * (i - 1) + 0x104EA0)) / *(float *)(4 * (i - 1) + 0x104F20) + (double)(24 * (i - 1));
          v5 = *(float *)(4 * (int)v4 + 0x104FA0);
          return (*(float *)(4 * (int)v4 + 0x104FA4) - v5) * (v4 - (double)(int)v4) + v5;
        }
      }
      result = MEMORY[0x105968];
    }
  }
  else
  {
    v6 = -a1;
    result = -sub_438F(v6);
  }
  return result;
}
// 438F: using guessed type double __cdecl sub_438F(float);

//----- (00004439) --------------------------------------------------------
double __cdecl sub_4439(float a1, float a2)
{
  double v2; // st5
  double result; // st7
  double v4; // st6
  double v6; // st5
  double v7; // st7
  bool v8; // al
  double v9; // rt1
  double v10; // st6
  double v11; // st7
  double v12; // rt2
  float v13; // [esp+0h] [ebp-28h]
  float v14; // [esp+0h] [ebp-28h]
  float v16; // [esp+30h] [ebp+8h]

  v2 = a2;
  if ( a2 > 0.0 )
  {
    v16 = a1 / v2;
    return sub_438F(v16);
  }
  if ( a1 < 0.0 )
  {
    v4 = a1;
    v6 = 0.0;
    v7 = a2;
  }
  else
  {
    v4 = a1;
    if ( v2 < 0.0 )
    {
      v13 = a1 / v2;
      return (float)(sub_438F(v13) + MEMORY[0x105978]);
    }
    v6 = 0.0;
    v7 = a2;
  }
  if ( v6 > v4 && v6 > v7 )
  {
    v14 = v4 / v7;
    return (float)(sub_438F(v14) - MEMORY[0x105978]);
  }
  v8 = v6 == v7;
  if ( v4 <= v6 )
  {
    v12 = v4;
    v10 = v6;
    v11 = v12;
  }
  else
  {
    if ( v6 == v7 )
      return MEMORY[0x10596C];
    v9 = v4;
    v10 = v6;
    v11 = v9;
  }
  if ( v10 <= v11 || (result = MEMORY[0x105970], !v8) )
    result = 0.0;
  return result;
}
// 438F: using guessed type double __cdecl sub_438F(float);

//----- (0000455E) --------------------------------------------------------
double __cdecl sub_455E(float a1)
{
  double result; // st7

  if ( a1 == 0.0 )
    result = -1.0;
  else
    result = sin(a1);
  return result;
}

//----- (0000457C) --------------------------------------------------------
double __cdecl sub_457C(float a1)
{
  double result; // st7

  if ( a1 == 0.0 )
    result = -1.0;
  else
    result = cos(a1);
  return result;
}

//----- (0000459A) --------------------------------------------------------
double __cdecl sub_459A(double a1, double a2)
{
  double result; // st7

  if ( a2 == 0.0 )
    result = 0.0;
  else
    result = a1 - a2 * (double)(int)(a1 / a2);
  return result;
}

//----- (000045DC) --------------------------------------------------------
int sub_45DC()
{
  unsigned int v0; // edx
  int v1; // eax
  int result; // eax

  v0 = MEMORY[0x1076AC] ^ (MEMORY[0x1076AC] << 11);
  MEMORY[0x1076AC] = MEMORY[0x1076A8];
  v1 = MEMORY[0x1076A4];
  MEMORY[0x1076A4] = MEMORY[0x1076A0];
  MEMORY[0x1076A8] = v1;
  result = (v0 >> 8) ^ v0 ^ MEMORY[0x1076A0] ^ (MEMORY[0x1076A0] >> 19);
  MEMORY[0x1076A0] = result;
  return result;
}

//----- (00004620) --------------------------------------------------------
__int64 __cdecl sub_4620(unsigned int a1, int a2, __int64 a3)
{
  __int64 result; // rax

  result = a1;
  while ( a3 )
  {
    --a3;
    *(_BYTE *)(a1 + HIDWORD(result)) = *(_BYTE *)(a2 + HIDWORD(result));
    ++HIDWORD(result);
  }
  HIDWORD(result) = 0;
  return result;
}

//----- (0000465B) --------------------------------------------------------
_BYTE *__cdecl sub_465B(_BYTE *a1, char a2, __int64 a3)
{
  _BYTE *v4; // edx

  v4 = a1;
  while ( a3 )
  {
    *v4++ = a2;
    --a3;
  }
  return a1;
}

//----- (000046B3) --------------------------------------------------------
_DWORD *__cdecl sub_46B3(_DWORD *a1)
{
  _DWORD *result; // eax

  result = a1;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  return result;
}

//----- (000046F1) --------------------------------------------------------
unsigned int __cdecl sub_46F1(unsigned int *a1, unsigned int a2)
{
  unsigned int v2; // ecx
  unsigned int v3; // ebx
  unsigned int *v4; // edx
  unsigned int result; // eax
  bool v6; // zf
  unsigned int v7; // ebx
  unsigned int v8; // edi

  v2 = 0;
  v3 = *a1;
  while ( 1 )
  {
    if ( v3 == v2 )
      return 0;
    if ( a1[2 * v2 + 5] >= a2 )
      break;
    ++v2;
  }
  v4 = &a1[2 * v2];
  result = v4[4];
  v4[4] = result + a2;
  v6 = v4[5] == a2;
  v4[5] -= a2;
  if ( v6 )
  {
    v7 = v3 - 1;
    *a1 = v7;
    while ( 1 )
    {
      v4 += 2;
      if ( v7 <= v2 )
        break;
      v8 = v4[5];
      ++v2;
      v4[2] = v4[4];
      v4[3] = v8;
    }
  }
  return result;
}

//----- (00004749) --------------------------------------------------------
int __cdecl sub_4749(int *a1, unsigned int a2, int a3)
{
  int v3; // edx
  int v4; // ecx
  int *v5; // esi
  int v6; // ebx
  int v7; // ebx
  int v8; // ecx
  int v9; // edi
  int *v10; // ebx
  int i; // ebx
  int v12; // edi
  int v13; // ecx
  bool v14; // cc
  int *v15; // eax

  v3 = 0;
  v4 = *a1;
  while ( 1 )
  {
    if ( v4 <= v3 )
    {
      if ( !v3 )
        goto LABEL_12;
      goto LABEL_6;
    }
    if ( a1[2 * v3 + 4] > a2 )
      break;
    ++v3;
  }
  if ( v3 )
  {
LABEL_6:
    v5 = &a1[2 * v3];
    v6 = v5[3];
    if ( v6 + v5[2] == a2 )
    {
      v7 = a3 + v6;
      v5[3] = v7;
      if ( v4 > v3 && a2 + a3 == v5[4] )
      {
        v8 = v4 - 1;
        v5[3] = v5[5] + v7;
        *a1 = v8;
        while ( v8 > v3 )
        {
          ++v3;
          v9 = a1[2 * v3 + 5];
          a1[2 * v3 + 2] = a1[2 * v3 + 4];
          a1[2 * v3 + 3] = v9;
        }
      }
      return 0;
    }
LABEL_12:
    if ( v4 > v3 )
      goto LABEL_13;
    if ( v4 <= 4095 )
      goto LABEL_20;
    goto LABEL_24;
  }
LABEL_13:
  v10 = &a1[2 * v3];
  if ( a2 + a3 == v10[4] )
  {
    v10[4] = a2;
    v10[5] += a3;
    return 0;
  }
  if ( v4 <= 4095 )
  {
    for ( i = *a1; i > v3; a1[2 * i + 7] = v12 )
    {
      --i;
      v12 = a1[2 * i + 5];
      a1[2 * i + 6] = a1[2 * i + 4];
    }
LABEL_20:
    v13 = v4 + 1;
    v14 = v13 <= a1[1];
    *a1 = v13;
    if ( !v14 )
      a1[1] = v13;
    v15 = &a1[2 * v3];
    v15[4] = a2;
    v15[5] = a3;
    return 0;
  }
LABEL_24:
  ++a1[3];
  a1[2] += a3;
  return -1;
}

//----- (0000489B) --------------------------------------------------------
unsigned __int8 sub_489B()
{
  unsigned __int8 result; // al

  do
    result = sub_3BBC(0x64u);
  while ( (result & 2) != 0 );
  return result;
}

//----- (000049C7) --------------------------------------------------------
int __usercall sub_49C7@<eax>(unsigned __int8 a1@<al>, char a2@<dl>, __int16 a3@<cx>)
{
  int result; // eax

  _disable();
  sub_3BC5(0x43u, (unsigned __int8)(2 * a2) | 0x30 | (unsigned __int8)(a1 << 6));
  sub_3BC5(a1 + 64, (unsigned __int8)a3);
  result = sub_3BC5(a1 + 64, HIBYTE(a3));
  _enable();
  return result;
}

//----- (00004A38) --------------------------------------------------------
int sub_4A38()
{
  unsigned __int8 v0; // al

  v0 = sub_3BBC(0x61u);
  return sub_3BC5(0x61u, v0 | 3);
}

//----- (00004A7B) --------------------------------------------------------
int __cdecl sub_4A7B(__int16 a1, int a2)
{
  sub_49C7(2u, 3, a1);
  return sub_4F60(a2);
}

//----- (00004AA1) --------------------------------------------------------
int __cdecl sub_4AA1(int a1)
{
  sub_49C7(2u, 3, 40);
  return sub_4F60(a1);
}

//----- (00004AC8) --------------------------------------------------------
unsigned int __cdecl sub_4AC8(unsigned int a1)
{
  unsigned int result; // eax

  result = 0xEA60 / a1;
  MEMORY[0x107FA8] = 0xEA60 / a1;
  return result;
}

//----- (00004ADC) --------------------------------------------------------
unsigned int __cdecl sub_4ADC(int a1, unsigned int a2)
{
  unsigned int result; // eax

  result = a2;
  if ( a2 == 4 )
  {
    MEMORY[0x107F9C] = MEMORY[0x107FA8];
    MEMORY[0x107FA4] = 4 * MEMORY[0x107FA8];
    MEMORY[0x107FA0] = 2 * MEMORY[0x107FA8];
    MEMORY[0x107F98] = MEMORY[0x107FA8] >> 1;
    result = MEMORY[0x107FA8] >> 3;
    MEMORY[0x107F94] = MEMORY[0x107FA8] >> 2;
  }
  else if ( a2 > 4 )
  {
    switch ( a2 )
    {
      case 0x10u:
        MEMORY[0x107F94] = MEMORY[0x107FA8];
        MEMORY[0x107FA4] = 16 * MEMORY[0x107FA8];
        MEMORY[0x107FA0] = 8 * MEMORY[0x107FA8];
        MEMORY[0x107F9C] = 4 * MEMORY[0x107FA8];
        result = MEMORY[0x107FA8] >> 1;
        MEMORY[0x107F98] = 2 * MEMORY[0x107FA8];
        break;
      case 0x20u:
        result = MEMORY[0x107FA8];
        MEMORY[0x107FA4] = 32 * MEMORY[0x107FA8];
        MEMORY[0x107FA0] = 16 * MEMORY[0x107FA8];
        MEMORY[0x107F9C] = 8 * MEMORY[0x107FA8];
        MEMORY[0x107F98] = 4 * MEMORY[0x107FA8];
        MEMORY[0x107F94] = 2 * MEMORY[0x107FA8];
        break;
      case 8u:
        MEMORY[0x107F98] = MEMORY[0x107FA8];
        MEMORY[0x107FA4] = 8 * MEMORY[0x107FA8];
        MEMORY[0x107FA0] = 4 * MEMORY[0x107FA8];
        MEMORY[0x107F9C] = 2 * MEMORY[0x107FA8];
        result = MEMORY[0x107FA8] >> 2;
        MEMORY[0x107F94] = MEMORY[0x107FA8] >> 1;
        break;
      default:
        return result;
    }
  }
  else if ( a2 == 1 )
  {
    MEMORY[0x107FA4] = MEMORY[0x107FA8];
    MEMORY[0x107FA0] = MEMORY[0x107FA8] >> 1;
    MEMORY[0x107F9C] = MEMORY[0x107FA8] >> 2;
    MEMORY[0x107F98] = MEMORY[0x107FA8] >> 3;
    result = MEMORY[0x107FA8] >> 5;
    MEMORY[0x107F94] = MEMORY[0x107FA8] >> 4;
  }
  else
  {
    if ( a2 != 2 )
      return result;
    MEMORY[0x107FA0] = MEMORY[0x107FA8];
    MEMORY[0x107FA4] = 2 * MEMORY[0x107FA8];
    MEMORY[0x107F9C] = MEMORY[0x107FA8] >> 1;
    MEMORY[0x107F98] = MEMORY[0x107FA8] >> 2;
    result = MEMORY[0x107FA8] >> 4;
    MEMORY[0x107F94] = MEMORY[0x107FA8] >> 3;
  }
  MEMORY[0x107F90] = result;
  return result;
}

//----- (00004D09) --------------------------------------------------------
int __cdecl sub_4D09(__int16 a1)
{
  return sub_4A7B(a1, MEMORY[0x107F90]);
}

//----- (00004D90) --------------------------------------------------------
int sub_4D90()
{
  return sub_4AA1(MEMORY[0x107F90]);
}

//----- (00004E55) --------------------------------------------------------
int __cdecl sub_4E55(_BYTE *a1, int a2)
{
  int v2; // ecx
  int v5; // eax
  int v7[14]; // [esp+8h] [ebp-38h]

  v2 = 0;
  while ( 1 )
  {
    v7[++v2] = a2 % 10;
    if ( a2 <= 9 )
      break;
    a2 /= 10;
  }
  v5 = v2;
  do
    *a1++ = v7[v5--] + 48;
  while ( v5 );
  return v2;
}

//----- (00004EA0) --------------------------------------------------------
int __cdecl sub_4EA0(_BYTE *a1, int a2)
{
  int v2; // ecx
  int v5; // eax
  int v6; // edx
  char v7; // bl
  int v9[14]; // [esp+4h] [ebp-38h]

  v2 = 0;
  while ( 1 )
  {
    v9[++v2] = a2 % 16;
    if ( a2 <= 15 )
      break;
    a2 >>= 4;
  }
  v5 = v2;
  do
  {
    v6 = v9[v5--];
    v7 = v6 + 55;
    if ( v6 <= 9 )
      v7 = v6 + 48;
    *a1++ = v7;
  }
  while ( v5 );
  return v2;
}

//----- (00004EEE) --------------------------------------------------------
int __usercall sub_4EEE@<eax>(int result@<eax>, _BYTE *a2, char *a3, char a4)
{
  int *v5; // edx
  char v7; // cl
  char v8; // cl
  int *v9; // edi

  v5 = (int *)&a4;
  while ( 1 )
  {
    v7 = *a3;
    if ( !*a3 )
      break;
    if ( v7 == 37 )
    {
      v8 = a3[1];
      if ( v8 == 100 )
      {
        v9 = v5 + 1;
        result = sub_4E55(a2, *v5);
      }
      else
      {
        if ( v8 != 120 )
          goto LABEL_9;
        v9 = v5 + 1;
        result = sub_4EA0(a2, *v5);
      }
      v5 = v9;
LABEL_9:
      a2 += result;
      a3 += 2;
    }
    else
    {
      *a2 = v7;
      ++a3;
      ++a2;
    }
  }
  *a2 = 0;
  return result;
}

//----- (00004F60) --------------------------------------------------------
int __cdecl sub_4F60(int a1)
{
  int result; // eax

  do
    result = MEMORY[0x107FE0];
  while ( (unsigned int)(MEMORY[0x107FE0] + a1) > MEMORY[0x107FE0] );
  return result;
}

//----- (00004F90) --------------------------------------------------------
int sub_4F90()
{
  return MEMORY[0x107FE0];
}

//----- (00004F9A) --------------------------------------------------------
int sub_4F9A()
{
  sub_3BC5(0x43u, 54);
  sub_3BC5(0x40u, 169);
  sub_3BC5(0x40u, 4);
  return sub_3C07(0, 1066320);
}

// nfuncs=61 queued=61 decompiled=61 lumina nreq=0 worse=0 better=0
// ALL OK, 61 function(s) have been successfully decompiled
