#include <Windows.h>
INT dword_140007018 = 0;
__int64 sub_140001300()
{
    unsigned int v0; // ebx
    unsigned int v1; // eax
    int v2; // xmm3
    char* v3; // rcx
    int v4; // xmm4
    int v5; // xmm0
    int v6; // xmm2
    unsigned int v7; // eax
    int v8; // xmm0
    int v9; // xmm2
    int v10; // xmm0
    int v11; // xmm0
    int v12; // xmm1
    int v13; // xmm0
    int v14; // xmm2
    int v15; // xmm2
    char* v16; // rdx
    unsigned int v17; // ecx
    HWAVEOUT phwo; // [rsp+30h] [rbp-D0h]
    struct wavehdr_tag pwh; // [rsp+38h] [rbp-C8h]
    WAVEFORMATEX pwfx; // [rsp+68h] [rbp-98h]
    char v22; // [rsp+80h] [rbp-80h]
    char v23; // [rsp+88h] [rbp-78h]

    *(DWORD*)&pwfx.wFormatTag = 65537;
    phwo = 0i64;
    pwfx.nSamplesPerSec = 8000;
    pwfx.nAvgBytesPerSec = 8000;
    *(DWORD*)&pwfx.nBlockAlign = 524289;
    v0 = 8;
    pwfx.cbSize = 0;
    waveOutOpen(&phwo, 0xFFFFFFFF, &pwfx, 0i64, 0i64, 0);
    memset(&v22, 0, 0x30D40ui64);
    v1 = 0;
    if (dword_140007018 < 2)
    {
        v16 = &v22;
        do
        {
            ++v16;
            v17 = v1 * v1;
            ++v1;
            *(v16 - 1) = v17 >> 12;
        } while (v1 < 0x30D40);
    }
    else
    {
       /* v2 = _mm_load_si128((const int*)&xmmword_140005630);
        v3 = &v23;
        v4 = _mm_cvtsi32_si128(0xCu);
        do
        {
            v3 += 16;
            v5 = _mm_add_epi32(_mm_shuffle_epi32(_mm_cvtsi32_si128(v0 - 8), 0), v2);
            v6 = _mm_and_si128(
                _mm_shuffle_epi32(
                    _mm_shufflehi_epi16(_mm_shufflelo_epi16(_mm_srl_epi32(_mm_mullo_epi32(v5, v5), v4), 216), 216),
                    216),
                (int)xmmword_140005640);
            *((_DWORD*)v3 - 6) = _mm_cvtsi128_si32(_mm_packus_epi16(v6, v6));
            v7 = v0 + 4;
            v8 = _mm_add_epi32(_mm_shuffle_epi32(_mm_cvtsi32_si128(v0 - 4), 0), v2);
            v9 = _mm_and_si128(
                _mm_shuffle_epi32(
                    _mm_shufflehi_epi16(_mm_shufflelo_epi16(_mm_srl_epi32(_mm_mullo_epi32(v8, v8), v4), 216), 216),
                    216),
                (int)xmmword_140005640);
            *((_DWORD*)v3 - 5) = _mm_cvtsi128_si32(_mm_packus_epi16(v9, v9));
            v10 = _mm_cvtsi32_si128(v0);
            v0 += 16;
            v11 = _mm_add_epi32(_mm_shuffle_epi32(v10, 0), v2);
            v12 = _mm_shufflehi_epi16(_mm_shufflelo_epi16(_mm_srl_epi32(_mm_mullo_epi32(v11, v11), v4), 216), 216);
            v13 = _mm_add_epi32(_mm_shuffle_epi32(_mm_cvtsi32_si128(v7), 0), v2);
            v14 = _mm_and_si128(_mm_shuffle_epi32(v12, 216), (int)xmmword_140005640);
            *((_DWORD*)v3 - 4) = _mm_cvtsi128_si32(_mm_packus_epi16(v14, v14));
            v15 = _mm_and_si128(
                _mm_shuffle_epi32(
                    _mm_shufflehi_epi16(_mm_shufflelo_epi16(_mm_srl_epi32(_mm_mullo_epi32(v13, v13), v4), 216), 216),
                    216),
                (int)xmmword_140005640);
            *((_DWORD*)v3 - 3) = _mm_cvtsi128_si32(_mm_packus_epi16(v15, v15));
        } while (v0 - 8 < 0x30D40);*/ 

        ///not fucking aroudnw with that
    }
    pwh.lpData = &v22;
    *(WORD*)&pwh.dwBufferLength = 200000i64;
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