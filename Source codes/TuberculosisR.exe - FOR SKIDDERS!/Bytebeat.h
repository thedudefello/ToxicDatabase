void Sound1() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 28000, 28000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[28000 * 32] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t*(t>>5&255)>>8)+t*5)>>4);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound2() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 37000, 37000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[37000 * 17] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^(t>>2|t>>5)%255)*cosf(t>>5));

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound3() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 35000, 35000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[35000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t/40^t&80);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound4() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 30000, 30000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[30000 * 34] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(3.0f*t*cosf(t>>12)+t*5.0f);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound5() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 29000, 29000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[29000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t>>10|4)^t);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound6() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 19000, 19000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[19000 * 28] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^(t>>6))%255);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound7() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 20500, 20500, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[20500 * 45] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*4/5)&128);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound8() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 27000, 27000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[27000 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*t*(t>>8|19))&128);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

void Sound9() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 28000, 28000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[28000 * 10] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t*(-t>>4<<(t>>150)&255)>>8)+(t/3>>3+(t>>150)&255)*3+(t/2>>1+(t>>150)&255)*3); // Credits to Fello (I modified it)

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}
