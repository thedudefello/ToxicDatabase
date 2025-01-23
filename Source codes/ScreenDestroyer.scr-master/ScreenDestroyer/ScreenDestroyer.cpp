#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <math.h>
#include <algorithm>
#include <VersionHelpers.h>
#pragma comment(lib, "msimg32.lib")
using namespace std;
bool DWM()
{
	HWND hwnd = FindWindow(L"DWM", NULL);
	return hwnd != NULL;
}
int Payload = 0;
int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);
struct Point3D {
	float x, y, z;
};
struct Point2D {
	float x, y, height;
};
struct Edge3D {
	Point3D PointA, PointB;
};
struct Edge2D {
	Point2D PointA, PointB;
};
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT v;
} HSV;
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
	double rd = rgbquad.rgbRed / 255.0;
	double gd = rgbquad.rgbGreen / 255.0;
	double bd = rgbquad.rgbBlue / 255.0;
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
void RedrawScreen() {
	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
}
Point2D Flatten3DPoint(const Point3D& InputPoint3D, float RotationX, float RotationY, float RotationZ) {
	float radX = RotationX * (M_PI / 180.0f);
	float radY = RotationY * (M_PI / 180.0f);
	float radZ = RotationZ * (M_PI / 180.0f);
	float cosX = cos(radX), sinX = sin(radX);
	float cosY = cos(radY), sinY = sin(radY);
	float cosZ = cos(radZ), sinZ = sin(radZ);
	float y1 = InputPoint3D.y * cosX - InputPoint3D.z * sinX;
	float z1 = InputPoint3D.y * sinX + InputPoint3D.z * cosX;
	float x1 = InputPoint3D.x * cosY + z1 * sinY;
	float z2 = -InputPoint3D.x * sinY + z1 * cosY;
	float x2 = x1 * cosZ - y1 * sinZ;
	float y2 = x1 * sinZ + y1 * cosZ;
	Point2D point2D;
	point2D.x = x2;
	point2D.y = y2;
	point2D.height = z2;
	return point2D;
}
vector<Point3D> EdgeToPoints(const Edge3D& InputEdge3D, uint16_t PointsAmount) {
	vector<Point3D> points;
	if (PointsAmount <= 0) return points;
	float stepX = (InputEdge3D.PointB.x - InputEdge3D.PointA.x) / (PointsAmount - 1);
	float stepY = (InputEdge3D.PointB.y - InputEdge3D.PointA.y) / (PointsAmount - 1);
	float stepZ = (InputEdge3D.PointB.z - InputEdge3D.PointA.z) / (PointsAmount - 1);
	for (int i = 0; i < PointsAmount; ++i) {
		Point3D point;
		point.x = InputEdge3D.PointA.x + i * stepX;
		point.y = InputEdge3D.PointA.y + i * stepY;
		point.z = InputEdge3D.PointA.z + i * stepZ;
		points.push_back(point);
	}
	return points;
}
bool HeightCompare2D(const Point2D& PointA, const Point2D& PointB) {
	return PointA.height < PointB.height;
}
void Payload1() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	while (true) {
		if (Payload >= 4 && Payload <= 7) {
			int size = rand() % 1000;
			int wsrc = rand() % w;
			int hsrc = rand() % h;
			BitBlt(dc, wsrc + rand() % 30, hsrc + rand() % 30, size, size, dc, wsrc, hsrc, SRCCOPY);
			size = rand() % 1000;
			wsrc = rand() % w;
			hsrc = rand() % h;
			BitBlt(dc, wsrc - rand() % 30, hsrc - rand() % 30, size, size, dc, wsrc, hsrc, SRCCOPY);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload2() {
	HDC dc = GetDC(NULL);
	HICON icon_list[] = { LoadIcon(NULL,IDI_APPLICATION),LoadIcon(NULL,IDI_ERROR),LoadIcon(NULL,IDI_INFORMATION),LoadIcon(NULL,IDI_WARNING),LoadIcon(NULL,IDI_WINLOGO) };
	HICON icon = icon_list[rand() % (sizeof(icon_list) / sizeof(icon_list[0]))];
	float posX = w / 2;
	float posY = h / 2;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	float dx = 10;
	float dy = 10;
	float rdx = 2.0f;
	float rdy = 2.0f;
	float rdz = 2.0f;
	float size = 200.0f;
	float ImportedModel[][2][3] = { {{-0.5,-0.5,-0.5},{-0.5,-0.5,0.5}},{{-0.5,-0.5,0.5},{-0.5,0.5,0.5}},{{-0.5,0.5,0.5},{-0.5,0.5,-0.5}},{{-0.5,0.5,-0.5},{-0.5,-0.5,-0.5}},{{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5}},{{-0.5,0.5,-0.5},{0.5,0.5,-0.5}},{{0.5,0.5,-0.5},{0.5,-0.5,-0.5}},{{0.5,-0.5,0.5},{0.5,-0.5,-0.5}},{{0.5,0.5,-0.5},{0.5,0.5,0.5}},{{0.5,0.5,0.5},{0.5,-0.5,0.5}},{{-0.5,-0.5,0.5},{0.5,-0.5,0.5}},{{0.5,0.5,0.5},{-0.5,0.5,0.5}},{{-1,-1,-1},{-1,-1,1}},{{-1,-1,1},{-1,1,1}},{{-1,1,1},{-1,1,-1}},{{-1,1,-1},{-1,-1,-1}},{{1,-1,-1},{-1,-1,-1}},{{-1,1,-1},{1,1,-1}},{{1,1,-1},{1,-1,-1}},{{1,-1,1},{1,-1,-1}},{{1,1,-1},{1,1,1}},{{1,1,1},{1,-1,1}},{{-1,-1,1},{1,-1,1}},{{1,1,1},{-1,1,1}},{{0.5,0.5,0.5},{1,1,1}},{{0.5,0.5,-0.5},{1,1,-1}},{{-0.5,0.5,-0.5},{-1,1,-1}},{{-0.5,0.5,0.5},{-1,1,1}},{{-0.5,-0.5,0.5},{-1,-1,1}},{{0.5,-0.5,0.5},{1,-1,1}},{{0.5,-0.5,-0.5},{1,-1,-1}},{{-0.5,-0.5,-0.5},{-1,-1,-1}} };
	// This one is actually imported from an .obj file I created with blender! 
	// Here's the code for the converter: 
	// #include <iostream>
	// #include <fstream>
	// #include <sstream>
	// #include <vector>
	// #include <tuple>
	// int main(int argc, char* argv[]) {
	//     std::cout << "Drag n' drop any .obj files into this window and we will convert it into an array of edges ready to be used for GDI effects. \n\n>";
	//     std::string filename;
	//     std::getline(std::cin, filename);
	//     std::ifstream infile(filename);
	//     std::vector<std::tuple<float, float, float>> vertices;
	//     std::vector<std::pair<int, int>> edges;
	//     std::string line;
	//     while (std::getline(infile, line)) {
	//         std::istringstream iss(line);
	//         std::string prefix;
	//         iss >> prefix;
	//         if (prefix == "v") {
	//             float x, y, z;
	//             iss >> x >> y >> z;
	//             vertices.emplace_back(x, y, z);
	//         }
	//         else if (prefix == "l") {
	//             int v1, v2;
	//             iss >> v1 >> v2;
	//             edges.emplace_back(v1 - 1, v2 - 1);  // Convert 1-indexed to 0-indexed
	//         }
	//     }
	//     std::cout << "\n\n\nResult: \n\nfloat ImportedModel[][2][3] = {";
	//     bool firstEdge = true;
	//     for (const auto& edge : edges) {
	//         if (!firstEdge) {
	//             std::cout << ",";
	//         }
	//         firstEdge = false;
	//         const auto& v1 = vertices[edge.first];
	//         const auto& v2 = vertices[edge.second];
	//         std::cout << "{{" << std::get<0>(v1) << "," << std::get<1>(v1) << "," << std::get<2>(v1) << "},{" << std::get<0>(v2) << "," << std::get<1>(v2) << "," << std::get<2>(v2) << "}}";
	//     }
	//     std::cout << "};" << std::endl;
	//     std::cout << "\n\nPress 'enter' exit... ";
	//     std::getline(std::cin, filename);
	//     return 0;
	// }
	Edge3D object3D[sizeof(ImportedModel) / sizeof(ImportedModel[0])];
	vector<Point3D> vertexes3D;
	for (int idx = 0; idx < sizeof(ImportedModel) / sizeof(ImportedModel[0]); idx++) {
		Edge3D edge;
		edge.PointA.x = ImportedModel[idx][0][0] * size;
		edge.PointA.y = ImportedModel[idx][0][1] * size;
		edge.PointA.z = ImportedModel[idx][0][2] * size;
		edge.PointB.x = ImportedModel[idx][1][0] * size;
		edge.PointB.y = ImportedModel[idx][1][1] * size;
		edge.PointB.z = ImportedModel[idx][1][2] * size;
		object3D[idx] = edge;
	}
	for (Edge3D edge : object3D) {
		vector<Point3D> generated = EdgeToPoints(edge, 20);
		vertexes3D.insert(vertexes3D.end(), generated.begin(), generated.end());
	}
	while (true) {
		if (Payload >= 5 && Payload <= 7) {
			vector<Point2D> vertexes2D;
			for (Point3D point : vertexes3D) {
				vertexes2D.push_back(Flatten3DPoint(point, rotX, rotY, rotZ));
			}
			sort(vertexes2D.begin(), vertexes2D.end(), HeightCompare2D);
			Sleep(10);
			if (rand() % 10 == 0) RedrawScreen();
			for (Point2D point : vertexes2D) {
				DrawIcon(dc, point.x + posX, point.y + posY, icon);
			}
			posX += dx;
			posY += dy;
			rotX += rdx;
			rotY += rdy;
			rotZ += rdz;
			if (posX + size >= w) {
				dx = -abs(dx);
				icon = icon_list[rand() % (sizeof(icon_list) / sizeof(icon_list[0]))];
			}
			if (posX - size <= 0) {
				dx = abs(dx);
				icon = icon_list[rand() % (sizeof(icon_list) / sizeof(icon_list[0]))];
			}
			if (posY + size >= h) {
				dy = -abs(dy);
				icon = icon_list[rand() % (sizeof(icon_list) / sizeof(icon_list[0]))];
			}
			if (posY - size <= 0) {
				dy = abs(dy);
				icon = icon_list[rand() % (sizeof(icon_list) / sizeof(icon_list[0]))];
			}
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload3() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
	SelectObject(dcCopy, bmp);
	BLENDFUNCTION blur = { 0 };
	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;
	while (true) {
		if (Payload >= 1 && Payload <= 4 || Payload == 8) {
			StretchBlt(dcCopy, rand() % 10, rand() % 10, w, h, dc, rand() % -10, rand() % -10, w, h, SRCCOPY);
			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
			if (rand() % (DWM() ? 50 : 5) == 0) RedrawScreen();
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload4() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	int ws = w / 4;
	int hs = h / 4;
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);
	SetStretchBltMode(dc, COLORONCOLOR);
	SetStretchBltMode(dcCopy, COLORONCOLOR);
	int color = 0;
	bool statementA = true;
	bool statementB = true;
	while (true) {
		if (Payload >= 6 && Payload <= 7) {
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);
			int r = rand() % 0xFF;
			int g = rand() % 0xFF;
			int b = rand() % 0xFF;
			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;
					int noise = rand() % 0xFF;
					noise %= (r * g * b + 1) % (color + 1) + 1;
					rgbquad[index].rgbRed += noise + r;
					rgbquad[index].rgbGreen += noise + g;
					rgbquad[index].rgbBlue += noise + b;
				}
			}
			if (statementA)
			{
				color++;
				if (color > 0xAA)
				{
					statementA = false;
					statementB = true;
				}
			}
			if (statementB)
			{
				color--;
				if (color == 0)
				{
					statementA = true;
					statementB = false;
				}
			}
			Sleep(rand() % 500 + 500);
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload5() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	HBITMAP hbmp = CreateCompatibleBitmap(dc, w, h);
	SelectObject(dcCopy, hbmp);
	INT x = 0;
	INT y = 0;
	while (true) {
		if (Payload >= 6 && Payload <= 7) {
			DWORD rop = SRCPAINT;
			int dx0 = rand() % 10;
			int dx1 = x;
			int dy0 = y;
			int dy1 = rand() % 10;
			int size = 80;
			BitBlt(dc, -dx0, dy0, w, size, dc, dx0, dy0, rop);
			BitBlt(dc, dx0, dy0, w, size, dc, -dx0, dy0, rop);
			BitBlt(dc, dx1, dy1, size, h, dc, dx1, -dy1, rop);
			BitBlt(dc, dx1, -dy1, size, h, dc, dx1, dy1, rop);
			x += size;
			y += size;
			if (x > w)
			{
				x = 0;
			}
			if (y > h)
			{
				y = 0;
			}
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload6() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);
	DWORD rop = SRCCOPY;
	bool statementA = true;
	bool statementB = false;
	int scrollX, scrollY;
	int cw = w / 2;
	int ch = h / 2;
	int limit = 25;
	int i = 0;
	while (true) {
		if (Payload == 7) {
			StretchBlt(dcCopy, 0, 0, w, h, dc, w, 0, -cw, h, rop);
			StretchBlt(dc, 0, 0, cw, h, dcCopy, 0, 0, w, h, rop);
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, h, rop);
			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;
					int dx = 10;
					if (statementA)
					{
						scrollX = (x + dx) % w;
						scrollY = (y + dx) % h;
					}
					else if (statementB)
					{
						scrollX = (x + dx) % w;
						scrollY = abs(y - dx) % h;
					}
					int srcIndex = scrollY * w + scrollX;
					rgbquad[index] = rgbquad[srcIndex];
				}
			}
			if (statementA)
			{
				i++;
				if (i > limit)
				{
					statementA = false;
					statementB = true;
				}
			}
			else if (statementB)
			{
				i--;
				if (i < 0)
				{
					statementA = true;
					statementB = true;
				}
			}
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, rop);
			StretchBlt(dcCopy, 0, 0, w, h, dc, 0, 0, w, ch, rop);
			StretchBlt(dc, 0, ch, w, ch, dcCopy, 0, h, w, -h, rop);
			Sleep(20);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload7() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	HBITMAP bmp = CreateCompatibleBitmap(dc, w, h);
	SelectObject(dcCopy, bmp);
	while (true) {
		if (Payload >= 4 && Payload <= 4 || Payload == 7) {
			StretchBlt(dcCopy, rand() % 30, rand() % 30, w, h, dc, rand() % 30, rand() % 30, w, h, SRCCOPY);
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload8() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	int ws = w / 4;
	int hs = h / 4;
	BLENDFUNCTION blur = { 0 };
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);
	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 20;
	INT i = 0;
	while (true) {
		if (Payload >= 1 && Payload <= 2) {
			StretchBlt(dcCopy, rand() % 1, rand() % 1, ws, hs, dc, rand() % -1, rand() % -1, w, h, SRCCOPY);
			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;
					rgbquad[index].rgbRed += i;
					rgbquad[index].rgbGreen += i;
					rgbquad[index].rgbBlue += i;
				}
			}
			i++;
			AlphaBlend(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, blur);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload9() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	int ws = w / 4;
	int hs = h / 4;
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);
	INT i = 0;
	FLOAT a = 5.0;
	FLOAT b = 3.0;
	SetStretchBltMode(dc, COLORONCOLOR);
	SetStretchBltMode(dcCopy, COLORONCOLOR);
	while (true) {
		if (Payload >= 2 && Payload <= 7) {
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);
			int randx = rand() % ws;
			int randy = rand() % hs;
			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;
					int cx = x - randx;
					int cy = y - randy;
					int zx = (cx * cx) / (a * a);
					int zy = (cy * cy) / (b * b);
					int fx = 128.0 + (128.0 * sin(sqrt(zx + zy) / 6.0));
					HSV hsv = RGBtoHSV(rgbquad[index]);
					hsv.h = fmod(fx + i, 360.0);
					rgbquad[index] = HSVtoRGB(hsv);
				}
			}
			i++;
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
			Sleep(rand() % 100);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload10() {
	HDC dc = GetDC(NULL);
	int i = 0;
	while (true) {
		if (Payload >= 3 && Payload <= 8) {
			for (int y = 0; y < h; y += 5)
			{
				int wavePhase = rand() % 70 - 40;
				int zx = 10 * sin(2 * M_PI * (y + i * 4) * wavePhase / h);
				BitBlt(dc, 0, y, w - zx, 5, dc, zx, y, SRCCOPY);
			}
			i++;
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload11() {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);
	int ws = w / 4;
	int hs = h / 4;
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);
	INT i = 0;
	DOUBLE angle = 0.f;
	while (true) {
		if (Payload == 7) {
			StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);
			RGBQUAD rgbquadCopy;
			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;
					int cx = (x - (ws / 2));
					int cy = (y - (hs / 2));
					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;
					int fx = (zx + i) ^ (zy + i);
					rgbquad[index].rgbRed += fx;
					rgbquad[index].rgbGreen += fx;
					rgbquad[index].rgbBlue += fx;
				}
			}
			i++; angle += 0.01f;
			StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void Payload12() {
	HDC hdc = GetDC(NULL);
	while (true) {
		if (Payload == 8) {
			int sides = rand() % 8 + 3;
			int radius = rand() % 400 + 100;
			int xCenter = rand() % (w - radius) + radius / 2;
			int yCenter = rand() % (h - radius) + radius / 2;
			float rotation = (float)rand() / RAND_MAX * (2 * M_PI);
			vector<HRGN> hRgn;
			while (radius > 0) {
				POINT* points = new POINT[sides];
				double angleStep = 2 * M_PI / sides;
				for (int i = 0; i < sides; ++i) {
					points[i].x = xCenter + static_cast<int>(radius * cos(i * angleStep + rotation));
					points[i].y = yCenter + static_cast<int>(radius * sin(i * angleStep + rotation));
				}
				hRgn.push_back(CreatePolygonRgn(points, sides, WINDING));
				radius -= 50;
			}
			for (HRGN region : hRgn) {
				InvertRgn(hdc, region);
				DeleteObject(region);
			}
			Sleep(DWM() ? 0 : rand() % 50);
		}
		Sleep(DWM() ? 1 : 5);
	}
}
void CtrlC() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 2;
	pos.Y = 2;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	while (true) {
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Press 'Ctrl + C' to end suffering...";
		Sleep(50);
	}
}
int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strstr(argv[i], "/p") || strstr(argv[i], "/P")) return 1;
		if (strstr(argv[i], "/c") || strstr(argv[i], "/C")) {
			cout << "Nice try, but you still cannot change your destiny...  :D\n\n";
			while (true) { Sleep(INFINITY); }
		}
	}
	cout << "Screen Destroyer v1.01 by Happy_mimimix\n\n";
	thread P1(Payload1);
	P1.detach();
	thread P2(Payload2);
	P2.detach();
	thread P3(Payload3);
	P3.detach();
	thread P4(Payload4);
	P4.detach();
	thread P5(Payload5);
	P5.detach();
	thread P6(Payload6);
	P6.detach();
	thread P7(Payload7);
	P7.detach();
	thread P8(Payload8);
	P8.detach();
	thread P9(Payload9);
	P9.detach();
	thread P10(Payload10);
	P10.detach();
	thread P11(Payload11);
	P11.detach();
	thread P12(Payload12);
	P12.detach();
	thread CC(CtrlC);
	CC.detach();
	while (true) {
		Payload = 1;
		Sleep(10000);
		Payload = 2;
		Sleep(10000);
		Payload = 3;
		Sleep(10000);
		Payload = 4;
		Sleep(10000);
		Payload = 5;
		Sleep(10000);
		Payload = 6;
		Sleep(10000);
		Payload = 7;
		Sleep(10000);
		Payload = 8;
		Sleep(10000);
	}
	return 0;
}