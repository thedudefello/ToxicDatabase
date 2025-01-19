[BITS    16]
[ORG 0x7E00]

WSCREEN equ 320
HSCREEN equ 200

kernelmain:
		call setup
		call payloads

		jmp $

setup:	
		;Setup Video Segment
		push 0xA000
		pop es
			
		;Write graphics pixel function
		mov ah, 0x0C

		;Setup some registers
		xor al, al   ;AL = Color
		xor bx, bx   ;BX = Page
		xor cx, cx   ;CX = X
		mov dx, 0x08 ;DX = Y

		;Initialize FPU
		fninit

		mov word [mincolor], 14
		mov word [maxcolor], 16

		mov si, str1
		call printstr

		ret

;-------------------------------------

payloads:
		mov word [x], cx
		mov word [y], dx

		mov word [zx], cx
		mov word [zy], dx
		
		cmp word [time], 3328
		ja crash

		cmp word [time], 3072
		ja thread13

		cmp word [time], 2816
		ja thread12

		cmp word [time], 2560
		ja thread11

		cmp word [time], 2304
		ja thread10

		cmp word [time], 2048
		ja thread9

		cmp word [time], 1792
		ja thread8

		cmp word [time], 1536
		ja thread7

		cmp word [time], 1280
		ja thread6

		cmp word [time], 1024
		ja thread5

		cmp word [time], 768
		ja thread4

		cmp word [time], 512
		ja thread3

		cmp word [time], 256
		ja thread2
				
		cmp word [time], 30
		ja thread1

		jb statics

		jmp setpixel

;-------------------------------------	

%include "Graphics/print.asm"
%include "Graphics/graphics.asm"
%include "Graphics/colors.asm"
%include "Kernel/pcspeaker.asm"
%include "Kernel/payloads.asm"
%include "Kernel/threads.asm"