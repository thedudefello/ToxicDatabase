HWAVEOUT hwo;

void ResetBytebeat(void) {
	waveOutReset(hwo);
}

namespace Bytebeat {
	void Sound1(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
		char tbuffer[24000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(((t>>10)*t&8)*t>>12);
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound2(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
		char tbuffer[24000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(2*t*(21&t>>8));
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound3(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
		char tbuffer[24000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t^12)*t>>12);
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound4(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 17000, 17000, 1, 8, 0 };
		char tbuffer[17000 * 31];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(2*sin(t^t>>12)); // Ununennium 0.5!
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound5(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
		char tbuffer[24000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t<<4>>(t>>(t>>12&15)&3))^t); // A lot of bitwise shifts.
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound6(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
		char tbuffer[16000 * 29];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(2*sin(t>>(t%32?4:3)|(t%128?t>>3:t>>4|t>>9))); // Xrotonium + Kloptonium intensifies
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	void Sound7(void) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0 };
		char tbuffer[24000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t>>3)*(t>>9)^t); // MalToolkit?
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD WINAPI Sound8(LPVOID pvoid) {
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
		char tbuffer[32000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 0, 0, CALLBACK_NULL);
		while (true) {
		
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(t*rand());
		}
		WAVEHDR hdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &hdr, sizeof(tbuffer));
		waveOutWrite(hwo, &hdr, sizeof(tbuffer));
		Sleep(30000);
	}
	}
}
