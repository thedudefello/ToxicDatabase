BITS 16
org 0x7c00

; Format -> Binary file
; Base Address: 0000h Range: 0000h - 0200h Loaded length: 0200h -> 512 bytes

; the way that the actual bootloader code organisation of is a total mess, so i had to fix it
; and way optimize it

segments:
	push    0x0A000
	pop     es
	xor     ax, ax
	xor     di, di
	
	mov     ax, 13h
	int 	10h
	
; print the pixels
x1:
	mov		ah, 0x0c
	inc 	al ; color
	xor 	bh, bh ; page
	inc 	cx ; x
	int 	10h
	cmp 	cx, 0xFFFF
	je 		keyboard
	jmp 	x1

keyboard:
	mov 	ax, 0
	int 	16h

	mov     ah, 0
	mov     al, 3
	int     10h
	
	mov 	si, msg
	
	print:
        push ax
        cld
		
		next:
			mov al,[si]
			cmp al,0
			je done
			call printchar
			inc si
			jmp next
		
		done:
			mov ax, 0
			int 16h
			; ineficient way
			jmp segments

		printchar:
			mov ah,0x0e
			int 0x10
			ret
		
	
	msg db "AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA AiVDsDOsA",0
	
times 510 - ($-$$) db 0
dw 0xaa55
