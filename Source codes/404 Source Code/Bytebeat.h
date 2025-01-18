HWAVEOUT hwo;

namespace Bytebeat {
	
	DWORD Sound1(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 29];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin(t>>11^t/3));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound2(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin(t>>4)*(t>>10));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound3(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 31];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((int)(2*sin(t/15>>t/36))^t);
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound4(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((int)(5*sin(t/15>>t/3))-t);
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound5(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 29];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*tan(t/15^(t/5>>7|t/3>>3)));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound6(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin((t&56)-t>>7));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound7(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 31];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(2*sin(t/10*(t/5>>10&3|t>>12)^t>>8));
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD Sound8(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (ULONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t&128)^t/5);
	  }
	  WAVEHDR whdr = {(CHAR*)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
	  waveOutPrepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutWrite(hwo, &whdr, sizeof(tbuffer));
	  waveOutUnprepareHeader(hwo, &whdr, sizeof(tbuffer));
	  waveOutClose(hwo);
	}
	
	DWORD NOISE(VOID) {
	  WAVEFORMATEX wftx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
	  BYTE tbuffer[32000 * 30];
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
