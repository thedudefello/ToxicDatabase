HWAVEOUT hwo;

namespace Bytebeat {
	
	VOID Bytebeat1(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 27000, 27000, 1, 8, 0};
	  BYTE tbuffer[27000 * 29];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t&t>>12)*(t>>9)+t);
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	VOID Bytebeat2(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(t+((t>>4)^(t>>5)));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	VOID Bytebeat3(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(t/4^(t/4>>(t/4>>10&5))+t);
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	VOID Bytebeat4(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 31];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin(t>>t/19));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	VOID Bytebeat5(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin((t/5^(t/8>>6|t/8>>9))));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	VOID Bytebeat6(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 28];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin(t/9^(t/9>>7|t>>8)));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	VOID Bytebeat7(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 5];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(t*rand());
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
}
