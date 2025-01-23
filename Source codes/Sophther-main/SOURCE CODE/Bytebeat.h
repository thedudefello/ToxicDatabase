#define sign(a) ((a)+128)
typedef struct IUnknown IUnknown;

namespace Bytebeat {
	VOID Sound1(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 26000, 26000, 1, 8, 0};
		BYTE tbuffer[26000 * 40];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>((((t>>2)*(t&16384?4:3))*t&12-t)&t>>13);
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Sound2(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>(((t*(t>>10&3)>>5)^t)*t);
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Sound3(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 40000, 40000, 1, 8, 0};
		BYTE tbuffer[40000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>(2*sin((((t>>3)^(t>>9))-t)/16));
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Sound4(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0};
		BYTE tbuffer[24000 * 27];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>(2*sin((t>>3)^(t>>9)));
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Sound5(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 60];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>(2*sin((t&50-t)*t>>12));
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	VOID Sound6(VOID) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		BYTE tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (FLONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<BYTE>((t*t>>18)&128);
		}
		WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutWrite(hwo, &whdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
}
