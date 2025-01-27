namespace Bytebeat
{
	void Sound1() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t>>2)*(t>>6)&t>>8);

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound2() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10*(t>>7|t|t>>(t>>16))+(7&t>>11));

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound3() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t>>2)*((t>>9|t>>11)&30));

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound4() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22000, 22000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[22000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t>>5|t|t>>7));

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound5() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t>>9|t|t>>7));

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	
	
	void Sound7() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[44100 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t*(t&t>>12)/t)*50);

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound8() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[24000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*t*((t>>3&t>>10)&50)+t);

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound9() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[24000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(((t&t>>8)+t)^t);

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}

	void Sound10() {
	HWAVEOUT wave = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&wave, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*(t>>5|t>>8)&t);

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutWrite(wave, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &hdr, sizeof(WAVEHDR));
	waveOutClose(wave);
}
}
