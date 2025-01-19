typedef struct IUnknown IUnknown;

#pragma once

#include "Purgatorium.h"

#define PI 3.14159265358979

typedef struct
{
	float x;
	float y;
	float z;
} VERTEX;

typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;

namespace Math
{
	//A = amplitude
	//B = frequency
	//C = phase displacement
	//D = period
	FLOAT SineWave(FLOAT a, FLOAT b, FLOAT c, FLOAT d)
	{
		return a * sin(2 * PI * b * c / d);
	}
}

namespace _3D
{
	VOID RotateX(VERTEX* vtx, float angle)
	{
		vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
		vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
	}

	VOID RotateY(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
		vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
	}

	VOID RotateZ(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
		vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
	}

	void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
	{
		int dx = abs(x1 - x0);
		int dy = -abs(y1 - y0);

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int error = dx + dy;

		int i = 0;

		while (true)
		{
			if (i == 0)
			{
				DrawIcon(dc, x0, y0, LoadIcon(NULL, icon));
				i = 10;
			}
			else
			{
				i--;
			}

			if (x0 == x1 && y0 == y1)
			{
				break;
			}

			int e2 = 2 * error;

			if (e2 >= dy)
			{
				if (x0 == x1)
				{
					break;
				}

				error += dy;
				x0 += sx;
			}

			if (e2 <= dx)
			{
				if (y0 == y1)
				{
					break;
				}

				error += dx;
				y0 += sy;
			}
		}
	}
}