typedef struct IUnknown IUnknown;

#pragma once

#include "Purgatorium.h"

namespace Bytebeats
{
	DWORD WINAPI BytebeatAlpha(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];
		
		DWORD c = 0;
		DWORD e = 0;
		
		FLOAT volume = 0.0;
		FLOAT dx = 0.6;
		
		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == 35000)
				{
					c = 0;
					e++;

					dx += 0.1;

					if (dx > 0.7) dx = 0.5;

					if (e % 10 && volume != 3)
					{
						volume += 0.1;
					}
				}

				DWORD d = c * dx;

				DWORD freq = d % 30;
			
				DWORD sound = c & freq % 500;

				sbuffer[t] = sound * volume;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}

	DWORD WINAPI BytebeatBeta(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{

				DWORD d = (t & 1) * 4;

				DWORD freq = (d | d << 2) >> 100;

				DWORD sound = t | (freq | t) % 500;

				sbuffer[t] = sound * 0.5;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}

	DWORD WINAPI BytebeatGamma(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD freq = Math::SineWave(10, t % 1000, 1, 1000);

				sbuffer[t] = t ^ (freq % 5);
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}

	//Quantification
	DWORD WINAPI BytebeatA(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD wave = Math::SineWave(1, t, 1, wfx.nSamplesPerSec);

				DWORD freq = ((wave | t) * 1000);

				sbuffer[t] = t | (freq | t) % 500;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);

			waveOutReset(hWaveOut);
			waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
		}

		return 0x00;
	}

	//Blocky thing
	DWORD WINAPI BytebeatC(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				DWORD c = t * 4;

				DWORD freq = (c | c << 2) >> 100;

				sbuffer[t] = t | (freq | t) % 500;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}

	//Descending and Ascending
	DWORD WINAPI BytebeatB(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;
		FLOAT d = 4.9;
		DWORD e = 0;

		BOOL statementA = TRUE; //4.9 -> 4.1
		BOOL statementB = FALSE; //3.2 -> 3.8
		BOOL statementC = FALSE; //3.8 -> 3.2

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				//d = 4.9
				if (statementA && c == 10000)
				{
					c = 0;
					d -= 0.1;
					
					if (d <= 4.0)
					{
						d = 4.9;
						e++;

						if (e == 2)
						{
							statementA = false;
							statementB = true;

							d = 3.2;
							e = 0;
						}
					}
				}

				//d = 3.2
				if (statementB && c == 10000)
				{
					c = 0;
					d += 0.1;

					if (d >= 3.9)
					{
						d = 3.2;
						e++;

						if (e == 2)
						{
							statementB = false;
							statementC = true;

							d = 3.8;
							e = 0;
						}
					}
				}

				//d = 3.8
				if (statementC && c == 10000)
				{
					c = 0;
					d -= 0.1;

					if (d <= 3.1)
					{
						d = 3.9;
						e++;

						if (e == 2)
						{
							statementC = false;
							statementA = true;

							d = 4.9;
							e = 0;
						}
					}
				}

				int dx = c * d;
				int freq = dx % 500;

				double sound = c | freq % 100000;

				sbuffer[t] = sound;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}

	//Final bytebeat
	DWORD WINAPI Noise(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == 100000)
				{
					c = 0;
				}

				DWORD freq = (rand() % (c + 1)) % (c + 1);

				sbuffer[t] = c ^ freq % 500;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}

	//Exponential Siren
	DWORD WINAPI ExpSiren(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				//if (c == 900000)
				//{
					//c = 0;
				//}

				double wave = Math::SineWave(1, c * 0.0011, (c & 32767), wfx.nSamplesPerSec * 2);

				sbuffer[t] = (int(wave * 0xA) & 0xFFFF);

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}

	
	DWORD WINAPI DecrescendoSiren(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };

		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		DWORD dx = 0;

		DWORD c = 0;

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == 100000)
				{
					c = 0;
				}

				DWORD offset = c + 17000;

				double freq = (8 * sizeof(sbuffer)) / offset;

				sbuffer[t] = Math::SineWave(freq, 2, offset, 4000);
				sbuffer[t] *= 3;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(0xFFFF, 0xFFFF));

			Sleep(1000 * 31);
		}

		return 0x00;
	}

	//Chaos
	DWORD WINAPI Bytebeat2(LPVOID lpvd)
	{
		DWORD counter = 44000;
		DWORD d = 0;
		DWORD c = 0;

		BOOL statement = TRUE;

		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32100, 32100, 1, 8, 0 };
		waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

		BYTE sbuffer[17000 * 60];

		while (true)
		{
			for (DWORD t = 0; t < sizeof(sbuffer); t++)
			{
				if (c == counter)
				{
					if (statement)
					{
						d++;

						if (d == 10)
						{
							statement = FALSE;
						}
					}

					if (!statement)
					{
						d--;

						if (d == 0)
						{
							statement = TRUE;
						}
					}

					if (counter == 500) d = rand() % 10;

					if (counter > 1000) counter -= 1000;
					if (counter <= 1000) counter -= 50;

					if (counter == 0) counter = 500;

					c = 0;
				}

				int freq = c * (3 + ((float)d / (float)10));
				sbuffer[t] = t | freq % 500;

				c++;
			}

			WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };
			waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
			waveOutSetVolume(hWaveOut, MAKELONG(65535, 65535));

			Sleep(1000 * 31);
		}

		return 0x00;
	}
}
