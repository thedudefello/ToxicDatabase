HWAVEOUT hwo = 0;
VOID hwo_reset(VOID) {
	waveOutReset(hwo);
}
namespace Bytebeat {
	
	DWORD Bytebeat1(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0};
		BYTE tbuffer[44000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(2*sin(t/32+(t/13+t>>11)*t/15));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD wBytebeat2(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 26000, 26000, 1, 8, 0};
		BYTE tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(((t/3+(t>>2))^(t>>5))%205);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat3(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t*4>>t/60)+t);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat4(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(4*sin((t&84)+t>>9));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat5(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 38000, 38000, 1, 8, 0};
		BYTE tbuffer[32000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t<<2)^-(t>>8&1));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat6(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 38000, 38000, 1, 8, 0};
		BYTE tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(t^(t*12>>7)-t/1);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat7(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(64*sin(t/9^t/8>>5|t/9>>9));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Bytebeat8(VOID) {
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t*sin(t/4)/155)+t);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutSetVolume(hwo, 0xffffff);
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
}

