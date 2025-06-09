#include "../HEADER/HEADER.h"

char *__fastcall 
AllocateAndSanitizePath(char *_TrgtPath, 
                        unsigned int TrgtPath_length__) 
{
    char *TrgtPath = (char *)calloc(TrgtPath_length__ + 1, 1);
    if (!TrgtPath) return NULL;

    for (unsigned int i = 0; i < TrgtPath_length__ && _TrgtPath[i]; i++) {
        TrgtPath[i] = (_TrgtPath[i] == '\\') ? '/' : _TrgtPath[i];
    }

    return TrgtPath;
}

int __fastcall 
FindMatchingEntryInStructure(DWORD *SysInfo, 
                             const char *_TrgtPath, 
                             int indexPtr, 
                             int16 flags, 
                             unsigned int *matchIndex)
{
    if (matchIndex) *matchIndex = 0;
    if (!sysInfo || !_TrgtPath) {
        sysInfo[7] = 24;
        return 0;
    }

    int *entryList = (int *)sysInfo[18];
    if (!entryList) return 0;

    unsigned int pathLen = strlen(_TrgtPath);
    if (pathLen > 0xFFFF) {
        sysInfo[7] = 24;
        return 0;
    }

    unsigned int currentIndex = 0;
    int totalEntries = entryList[0];
    _DWORD *entryTable = (DWORD *)entryList[4];

    while (currentIndex < sysInfo[4]) {
        int entryBase = *entryTable;
        size_t entryLen = *(unsigned __int16 *)(entryBase + totalEntries + 28);
        char *entryName = (char *)(entryBase + totalEntries + 46);

        if (entryLen >= pathLen) {
            if ((flags & 0x200) && entryLen) {
                int i = entryLen - 1;
                while (i >= 0 && entryName[i] != '/' 
                              && entryName[i] != '\\' 
                              && entryName[i] != ':') 
                    i--;
                entryName += i + 1;
                entryLen -= i + 1;
            }

            if (entryLen == pathLen) {
                if (flags & 0x100) {
                    if (!memcmp(_TrgtPath, entryName, entryLen)) goto MATCH_FOUND;
                } else {
                    size_t matchedChars = 0;
                    while (matchedChars < entryLen) {
                        char c1 = (_TrgtPath[matchedChars] >= 'A' && _TrgtPath[matchedChars] <= 'Z') ? 
                                   _TrgtPath[matchedChars] + 32 : _TrgtPath[matchedChars];
                        char c2 = (entryName[matchedChars] >= 'A' && entryName[matchedChars] <= 'Z') ? 
                                   entryName[matchedChars] + 32 : entryName[matchedChars];
                        if (c1 != c2) break;
                        matchedChars++;
                    }
                    if (matchedChars == entryLen) goto MATCH_FOUND;
                }
            }
        }

        entryTable++;
        currentIndex++;
    }

    sysInfo[7] = 28;
    return 0;

MATCH_FOUND:
    if (matchIndex) *matchIndex = currentIndex;
    return 1;
}

int __fastcall 
ConvertTimeToCustomFormat(WORD *TimeofDay, 
                          WORD *date, 
                          __time64_t Time)
{
  int result, tm_mon;
  tm Tm;

  if ( _localtime64_s(&Tm, &Time) )
  {
    result = 0;
    *date = 0;
    *TimeofDay = 0;
  }
  else
  {
    tm_mon = Tm.tm_mon;
    *TimeofDay = (Tm.tm_sec >> 1) + 32 * (LOWORD(Tm.tm_min) + (LOWORD(Tm.tm_hour) << 6));
    result = Tm.tm_mday + 32 * (16 * Tm.tm_year + tm_mon + 769);
    *date = result;
  }
  return result;
}

int __fastcall 
ProcessFilePathAndUpdateSession(void **SysInfo, 
                                char *_TrgtPath) 
{
    unsigned int TrgtPath_length__, validationStatus;
    int entryIndex, matchingIndex, result, timeBuffer;
    __time64_t currentTime;
    __int64 dataOffset;
    bool sessionFlag;
    void *TrgtPath, *sessionData, *tempPtr;
 
    if (!SysInfo)
        return -1;
    
    dataOffset = *(_QWORD *)SysInfo;

    if (!_TrgtPath)
        return -2;
    
    TrgtPath_length__ = strlen(_TrgtPath);
    if (!TrgtPath_length__)
        return -2;

    if (SysInfo[23]) {
        free(SysInfo[23]);
        SysInfo[23] = NULL;
    }

    TrgtPath = AllocateAndSanitizePath(_TrgtPath, TrgtPath_length__);
    SysInfo[23] = TrgtPath;
    if (!TrgtPath)
        return -2;

    if (SysInfo[5] == (void *)1) {
        entryIndex = FindMatchingEntryInStructure(SysInfo, TrgtPath, (int *)&validationStatus, 0, &validationStatus); 
        matchingIndex = validationStatus;
        
        if (!entryIndex)
            matchingIndex = -1;
        
        SysInfo[22] = (void *)matchingIndex;

        if (matchingIndex >= 0 && RetrieveIndexedEntry((int)SysInfo, matchingIndex, (int)&sessionData)) { // IM here
            SysInfo[26] = ((void **)sessionData)[1];
            SysInfo[24] = ((void **)sessionData)[2];
            SysInfo[28] = ((void **)sessionData)[3];
            SysInfo[30] = ((void **)sessionData)[4];
            SysInfo[27] = ((void **)sessionData)[5];
            SysInfo[40] = ((void **)sessionData)[6];
            SysInfo[25] = ((void **)sessionData)[7];
            SysInfo[31] = ((void **)sessionData)[8];
            SysInfo[41] = ((void **)sessionData)[9];
            SysInfo[79874] = ((void **)sessionData)[10];
            SysInfo[79876] = ((void **)sessionData)[11];
            SysInfo[79877] = ((void **)sessionData)[12];
            return 0;
        }
        result = -3;
    } else {
        SysInfo[22] = SysInfo[4];
        SysInfo[31] = SysInfo[1];
        SysInfo[26] = NULL;
        SysInfo[27] = NULL;
        SysInfo[24] = NULL;
        SysInfo[25] = NULL;
        SysInfo[28] = NULL;
        SysInfo[30] = SysInfo[0];
        SysInfo[40] = SysInfo[0];
        SysInfo[41] = SysInfo[1];
        memset(SysInfo + 32, 0, 0x1C);
        
        sessionFlag = (unsigned int)SysInfo[20] & 0xF;
        *((_WORD *)SysInfo + 78) = 0;
        SysInfo[79874] = 0;
        *((_WORD *)SysInfo + 84) = sessionFlag ? 8 : 0;
        
        validationStatus = ValidateSessionState(SysInfo);
        if (SysInfo[18] == 0 || SysInfo[5] != (void *)2) {
            result = -4;
        } else if (((unsigned int)SysInfo[20] & 0x400) != 0) {
            result = -5;
        } else {
            if (!ReadDataChunks((int)SysInfo, validationStatus, (unsigned int)SysInfo[30], (unsigned int)SysInfo[31]))
                return -7;
            
            dataOffset += validationStatus;
            currentTime = SomeShitforTimestamp(0);
            *((_QWORD *)SysInfo + 39938) = currentTime;
            ConvertTimeToCustomFormat(&timeBuffer, &dataOffset, currentTime);
            
            if (!HIDWORD(dataOffset) && dataOffset != -1) {
                sessionData = &dataOffset;
            } else {
                sessionData = NULL;
            }
            char v57[28];
            __sessionData = PrepareDataBlock((int)v57, 0, 0, sessionData);
            if (InitializeFileHeader(SysInfo + 32, TrgtPath_length__, __sessionData, *((WORD *)SysInfo + 84), timeBuffer, dataOffset)) {
               void* __SysInfo23 = SysInfo[23];
                *((QWORD *)SysInfo + 15) += validationStatus + 30;
                
                if (WriteSessionData(SysInfo, TrgtPath_length__)) {
                    if (!sessionFlag)
                        return 0;

                    SysInfo[48] = 0;
                    SysInfo[49] = 0;
                    SysInfo[44] = SysInfo;
                    *((QWORD *)SysInfo + 23) = __SessionData;
                    
                    if (!InitializeSysInfo((int)(SysInfo + 44), GenerateFlagsFromValue(sessionFlag)))
                        return 0;
                    
                    result = -9;
                } else {
                    result = -8;
                }
            } else {
                result = -7;
            }
        }
    }

    if (SysInfo[23]) {
        free(SysInfo[23]);
        SysInfo[23] = NULL;
    }
    return result;
}
