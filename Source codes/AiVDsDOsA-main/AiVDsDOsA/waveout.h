#include <Windows.h>
__int64 sub_1400011A0()
{
    char v0; // r9
    char* v1; // r8
    unsigned int i; // eax
    char v3; // cl
    HWAVEOUT phwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag pwh; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX pwfx; // [rsp+68h] [rbp-98h]
    char v8; // [rsp+80h] [rbp-80h]
    char v9; // [rsp+81h] [rbp-7Fh]

    *(DWORD*)&pwfx.wFormatTag = 65537;
    phwo = 0i64;
    pwfx.nSamplesPerSec = 8000;
    pwfx.nAvgBytesPerSec = 8000;
    *(DWORD*)&pwfx.nBlockAlign = 524289;
    pwfx.cbSize = 0;
    waveOutOpen(&phwo, 0xFFFFFFFF, &pwfx, 0i64, 0i64, 0);
    memset(&v9, 0, 0x2903Fui64);
    v0 = NULL;
    v1 = &v8;
    for (i = 0; i < 0x29040; ++i)
    {
        v3 = i;
        *(++v1 - 1) = v3 * v0;
    }
    pwh.lpData = &v8;
    *(WORD*)&pwh.dwBufferLength = 168000i64;
    pwh.dwUser = 0i64;
    *(WORD*)&pwh.dwFlags = 0i64;
    pwh.lpNext = 0i64;
    pwh.reserved = 0i64;
    waveOutPrepareHeader(phwo, &pwh, 0x30u);
    waveOutWrite(phwo, &pwh, 0x30u);
    waveOutUnprepareHeader(phwo, &pwh, 0x30u);
    waveOutClose(phwo);
    return 1i64;
}