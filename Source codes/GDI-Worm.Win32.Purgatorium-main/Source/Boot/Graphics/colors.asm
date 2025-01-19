[BITS    16]

;-------------------------------------

;Put the color in AL to a interval
;Defined by [PXMINCOLOR, PXMAXCOLOR]

palette:
	cmp al, [pxmaxcolor]
        ja delcolor
        
        cmp al, [pxmincolor]
        jb addcolor
		
	jmp setpixel

addcolor:
        add al, [addcol]
        jmp palette

delcolor:
        sub al, [delcol]
        jmp palette
		
;-------------------------------------		

;BX = Start index
setvgapalette:
        pusha
                palette.loop:
                        ;Setup VGA palette
                        mov dx, 0x3C8
                        mov al, bl
                        out dx, al

                        ;Color's index port
                        mov dx, 0x3C9

                        ;Red
                        xor al, al
                        out dx, al

                        ;Green
                        mov al, bl
                        out dx, al

                        ;Blue
                        xor al, al
                        out dx, al

                        ;Next palette index
                        inc bx

                        cmp bx, 0xFF
                        jb palette.loop
        popa

        ret

;-------------------------------------

;Some predefined intervals for palette

setrainbow:
        mov byte [pxmaxcolor], 55
        mov byte [pxmincolor], 32

        ret

setgray:
        mov byte [pxmaxcolor], 31
        mov byte [pxmincolor], 16

        ret

setpastel:
        mov byte [pxmaxcolor], 103
        mov byte [pxmincolor], 80

        ret

setvga:
        mov byte [pxmaxcolor], 15
        mov byte [pxmincolor], 0

        ret

;-------------------------------------

;These variables will manage the min 
;And max color interval for palette.

pxmaxcolor: dw 0x00
pxmincolor: dw 0x00

;'Add' and 'Sub' factors for colors who
;Aren't in the interval given by
;[pxmincolor, pxmaxcolor]

addcol: dw 32
delcol: dw 16