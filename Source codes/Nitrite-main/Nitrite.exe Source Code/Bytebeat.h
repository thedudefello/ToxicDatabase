#include <windows.h>

namespace Bytebeat {
	void Audio1(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t/70^t/50)+t/2);
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio2(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 19000, 19000, 1, 8, 0 };
	  BYTE tbuffer[19000 * 25];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t>>t*2)+t^9);
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio3(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 19000, 19000, 1, 8, 0 };
	  BYTE tbuffer[19000 * 15];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t^48)*t>>8^t);
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio4(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t^(t>>5|t>>8))%255);
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio5(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	  BYTE tbuffer[32000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(((t>>4)^(t>>9))+t);
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio6(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 34000, 34000, 1, 8, 0 };
	  BYTE tbuffer[34000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>((t>>9)*cos(t>>1));
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
	
	void Audio7(void) {
	  HWAVEOUT hwo;
	  WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 34000, 34000, 1, 8, 0 };
	  BYTE tbuffer[34000 * 30];
	  waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
	  for (FLONG t = 0; t < sizeof(tbuffer); t++) {
	    tbuffer[t] = static_cast<BYTE>(t*rand());
	  }
	  WAVEHDR hdr = { (LPSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
	  waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutWrite(hwo, &hdr, sizeof(hdr));
	  waveOutUnprepareHeader(hwo, &hdr, sizeof(hdr));
	  waveOutClose(hwo);
	}
}
