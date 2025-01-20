; recreated version aka most crap, atlest he can put colors.

bits 16
org 0x7c00
jmp load_clr

load_clr:
	mov ah,0x07
	mov al,0x00
	mov dx,0x184f
	int 0x10
	mov ax,cx
	mov dx,ax
	mov si,msg
	push ax
	cld
	
halal:
	mov al,[si]
	cmp al,0
	je nje
	mov ah,0x0e
	int 0x10
	inc si
	jmp halal
	
nje:
	jmp $
	
msg:
	db "Whoa, Where did you come from?",13,10,"Well, Welcome to the Polaris Payload!",13,10,"You are staying here for long >:D",0
	times 512 - ($-$$) db 0
	dw 0xaa55