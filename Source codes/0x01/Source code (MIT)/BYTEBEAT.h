HWAVEOUT hwo;

MMRESULT _RESET(VOID) {
	waveOutReset(hwo);
}

namespace Bytebeat {
	VOID Bytebeat1(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0};
		BYTE tbuffer[24000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (t*(t^6)>>12)-t+128;
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat2(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0};
		BYTE tbuffer[24000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (((t>>8)*(t>>4))&128)+t/4;
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat3(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 27000, 27000, 1, 8, 0};
		BYTE tbuffer[27000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = 127*sin((t/10+(t/5>>9^t/4>>3)>>2)-t/8)+128;
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat4(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 40000, 40000, 1, 8, 0};
		BYTE tbuffer[40000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = 10*sin((t&(t>>9)+t^(t>>9))>>6);
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat5(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0};
		BYTE tbuffer[24000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = 128+((-t&t>>5&t>>9&t>>11)*(t>>3));
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat6(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 25000, 25000, 1, 8, 0};
		BYTE tbuffer[25000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = 2*sin((t/4^(t/5>>9))-3);
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Bytebeat7(VOID) {
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 38000, 38000, 1, 8, 0};
		BYTE tbuffer[38000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (DWORD t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (t<<3)^-(t>>5&1); // Dollchan bytebeat, how original!
		}
		WAVEHDR wh = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0x7fffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
}
