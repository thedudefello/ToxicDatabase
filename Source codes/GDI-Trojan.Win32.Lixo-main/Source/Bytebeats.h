typedef struct IUnknown IUnknown;

#pragma once

#include "Lixo.h"

namespace Bytebeats
{
	DWORD WINAPI Bytebeat1(LPVOID lpvd)
	{
		while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
			WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	DWORD d = 1000;
		    	DWORD c = 0;

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				sbuffer[t] = t * sinf((PI * t * 2 / 100000));
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
	}

    	DWORD WINAPI Bytebeat2(LPVOID lpvd)
	{
		while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	DWORD d = 1000;
		    	DWORD c = 0;

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				if (c == 10000)
				{
			    		d = rand() % 5000;
			    		if (d < 500) d += 300;

			    		c = 0;
				}

				int freq = 20 + (c / d);
				sbuffer[t] = (c * 12) % (freq * 10);

				c++;
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
    	}

    	DWORD WINAPI Bytebeat3(LPVOID lpvd)
    	{
        	while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				sbuffer[t] = 0.001 * ((t << 1) * sin(t | 333));
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
	}

	DWORD WINAPI Bytebeat4(LPVOID lpvd)
	{
		while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	DWORD c = 0;

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++) 
		    	{
				if (c == 516855) c = 0;

				sbuffer[t] = ((t >> 4) & 24555) * sin(t | 3);
				c++;
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
	}

        DWORD WINAPI Bytebeat5(LPVOID lpvd)
        {
		while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				sbuffer[t] = 0.01 * (t * (t & 100000) >> 1000);
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
    	}

    	DWORD WINAPI Bytebeat6(LPVOID lpvd)
    	{
		while (1)
		{
			HWAVEOUT hWaveOut;
			WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
			waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

			BYTE sbuffer[17000 * 60];

			for (int t = 0; t < sizeof(sbuffer); t++)
			{
				float i = (t / 44100.0f);

				float alpha = sinf(i * 3000.0f * sinf(i * 4.0f + sinf(i * 2.0f)));
				float beta = (1.0f / PI) * atanf(1.0f / tanf(i * 5000.0f));
				float gamma = (1.0f / PI) * asinf(sinf(i * 8000.0f));
				float delta = (1.0f / PI) * atanf(sinf(i * 10000.0f));

				float sound = alpha + beta + gamma + delta;

				sbuffer[t] = (sound * 127.0f);
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
			waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
			waveOutWrite(hWaveOut, &header, sizeof(header));
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
			waveOutClose(hWaveOut);

			Sleep(8000 * 1000);
		}

		return 0x00;
    	}

    	DWORD WINAPI Bytebeat7(LPVOID lpvd)
    	{
		while (1)
		{
			HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				sbuffer[t] = 0.01 * (t * (t & 999) >> 1000);
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
    	}

    	DWORD WINAPI Bytebeat8(LPVOID lpvd)
    	{
		while (1)
		{
			HWAVEOUT hWaveOut = 0;
			WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
			waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

			BYTE sbuffer[17000 * 60];

			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				int freq = 1;

				if ((t % 32) < 16) freq += t;
				if ((t % 64) < 32) freq -= 2;
				if ((t % 128) < 64) freq += 4;
				if ((t % 256) < 128) freq -= 8;
				if ((t % 512) < 256) freq += 16;
				if ((t % 1024) < 512) freq -= 32;
				if ((t % 2048) < 1024) freq += 64;
				if ((t % 4096) < 2048) freq -= 128;
				if ((t % 8192) < 4096) freq += 256;
				if ((t % 8192) > 4096) freq -= 512;

				freq += sin(freq + t);

				sbuffer[t] = 12 * sin((PI * t * 2 / log2(t * freq)));
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutClose(hWaveOut);

			Sleep(8000 * 1000);
		}

		return 0x00;
    	}

    	DWORD WINAPI Bytebeat9(LPVOID lpvd)
    	{
		while (1)
		{
		    	HWAVEOUT hWaveOut = 0;
		    	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
		    	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		    	BYTE sbuffer[17000 * 60];

		    	for (DWORD t = 0; t < sizeof(sbuffer); t++)
		    	{
				sbuffer[t] = (t >> (rand() % 50)) + t;
		    	}

		    	WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
		    	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		    	waveOutClose(hWaveOut);

		    	Sleep(8000 * 1000);
		}

		return 0x00;
    	}
}
