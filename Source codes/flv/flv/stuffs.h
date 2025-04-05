#pragma once
#include "Windows.h"
#include "math.h"

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


namespace _3D //credits to ArTicZera/JhoPro for this stuff, but I modified it with moricons.dll icons
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

	void DrawEdge(HDC dc, int x0, int y0, int x1, int y1, int r)
	{
		int dx = abs(x1 - x0);
		int dy = -abs(y1 - y0);

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int error = dx + dy;

		int i = 0;
		HMODULE hModule = LoadLibrary(TEXT("moricons.dll"));
		int randomIcon = rand() % (114 - 50 + 1) + 50;
		while (true)
		{
			if (i == 0)
			{
				DrawIcon(dc, x0, y0, LoadIcon(hModule, MAKEINTRESOURCE(randomIcon)));
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