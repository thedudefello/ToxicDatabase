BITS 16
org 0x7c00

; Format -> Binary file
; Base Address: 0000h Range: 0000h - 0200h Loaded length: 0200h -> 512 bytes

; Segment type: Pure code
; reasembling and reorganizing

; who actually knows assembler will understand what is going on

screen: ; this time im not going to fix it preparing correctly the video memory, since it wasn't actually
		; found in the reversed code, so yeah not gonna bother.
		
	mov 	ax, 13h ; minor fix
	int     10h             
										
	mov     al, 0
	mov     cx, 0
	mov     dx, 0
	mov     ah, 0Ch
	mov     bh, 0
	jmp     $+2 

payload:   ; draw the pixels                              
	add     al, bl
	add     bl, 7
	add     ch, al
	sub     cl, al
	int     10h

	cmp     cx, 140h ; ok
	jg      compare
	jmp     payload

compare:   ; compare pixel                            
    mov     cx, 0
	inc     dx
	cmp     dx, 0C8h ; imagination number 
	jg      reset_val
	jmp     payload

reset_val:   ; reset values                              
	mov     cx, 0
	mov     dx, 0
	jmp     payload

times 510 - ($-$$) db 0
dw 0xaa55