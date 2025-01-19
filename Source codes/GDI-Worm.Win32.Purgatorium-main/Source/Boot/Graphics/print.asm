[BITS    16]

;SI = STRING
;MINCOLOR = a in [a,b]
;MAXCOLOR = b in [a,b]
printstr:	
		pusha

		;Teletype output
		mov ah, 0x0E
		mov al, [si]
			
		xor bh, bh
			
		printstr.color:
				;Interval's min color
				mov bl, [mincolor]
				
				printstr.loop:
						;Next color index
						inc bl
							
						;Interval's max color
						cmp bl, [maxcolor]
						je printstr.color
						
						;Print char
						int 10h
							
						;Next char
						inc si
						mov al, [si]
							
						;Check if finished
						cmp al, 0x00
						jnz printstr.loop
		popa						
							
		ret

resetcursor:
		pusha
				mov ah, 0x02

				xor bh, bh
				xor dx, dx

				int 0x10
		popa

		ret

maxcolor: dw 0x00
mincolor: dw 0x00