;Uncompression code for the extra data of MEMZ/VineMEMZ
;It has been optimized for the larger file sizes of VineMEMZ
;It's not backwards compatible to the old compressor!

mov bx, daddr
mov es, bx
mov ds, bx

;Read from disk
mov ax, 0x0216
mov cx, 0x0003
mov dh, 0
mov bx, compressed
int 13h

xor ax, ax
mov bx, ax
mov cx, ax
mov dx, ax

mov si, compressed
mov di, uncompressed

readcommand:
    lodsb
    
    cmp si, uncompressed
    jae compressorDone
    
    cmp al, 128
    jae newdata
    jmp olddata
    
newdata:
    and al, 127
    mov cl, al
    
    newnextbyte:
        lodsb
        stosb
        
        dec cl
        cmp cl, -1
        jne newnextbyte
        jmp readcommand
        
olddata:
    mov ah, 0
    cmp al, 64
    jb xxx

    and al, 63
    mov ah, al
    lodsb
    
    xxx:
    mov cx, ax
    lodsw
    
    mov dx, si
    mov si, di
    sub si, ax
    
    oldnextbyte:
        lodsb
        stosb
        
        loop oldnextbyte
        
        mov si, dx
        jmp readcommand
