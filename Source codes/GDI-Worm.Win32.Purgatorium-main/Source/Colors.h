typedef struct IUnknown IUnknown;

#pragma once

#include "Purgatorium.h"

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT v;
} HSV;

namespace Colors
{
	RGBQUAD HSVtoRGB(HSV hsv)
	{
		int hi = (int)floor(hsv.h / 60.0) % 6;
		double f = hsv.h / 60.0 - floor(hsv.h / 60.0);
		double p = hsv.v * (1.0 - hsv.s);
		double q = hsv.v * (1.0 - f * hsv.s);
		double t = hsv.v * (1.0 - (1.0 - f) * hsv.s);

		switch (hi) 
		{
			case 0:
				return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255) };
			case 1:
				return { static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255) };
			case 2:
				return { static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255) };
			case 3:
				return { static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255) };
			case 4:
				return { static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255) };
			default:
				return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255) };
		}
	}

	HSV RGBtoHSV(RGBQUAD rgbquad)
	{
		HSV hsv;

		double rd = rgbquad.rgbRed   / 255.0;
		double gd = rgbquad.rgbGreen / 255.0;
		double bd = rgbquad.rgbBlue  / 255.0;

		double cmax = max(max(rd, gd), bd);
		double cmin = min(min(rd, gd), bd);
		double delta = cmax - cmin;

		hsv.v = cmax;

		if (cmax > 0.0)
			hsv.s = delta / cmax;
		else
			hsv.s = 0.0;

		if (delta > 0.0)
		{
			if (cmax == rd)
				hsv.h = 60.0 * fmod((gd - bd) / delta, 6.0);
			else if (cmax == gd)
				hsv.h = 60.0 * ((bd - rd) / delta + 2.0);
			else if (cmax == bd)
				hsv.h = 60.0 * ((rd - gd) / delta + 4.0);

			if (hsv.h < 0.0)
				hsv.h += 360.0;
		}
		else
		{
			hsv.h = 0.0;
		}

		return hsv;
	}
}