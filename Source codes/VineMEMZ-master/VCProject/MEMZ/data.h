#pragma once
#include "memz.h"

extern char *sites[];
extern const size_t nSites;

extern char *engines[];
extern const size_t nEngines;

extern const unsigned char code1[];
extern const unsigned char code2[];

extern const size_t code1_len;
extern const size_t code2_len;

extern const unsigned char msg[];
extern const size_t msg_len;

typedef struct {
	LPWSTR name;
	LPWSTR type;
	LPWSTR alias;
} Sound;