[BITS    16]

;Transition noise
statics:	
        call playsound

	;x = sin(x)
	fild dword [x]
	fsin
	fstp dword [x]
		
	mov al, [x]

        ;AL += TIME * 6
	add al, [time]
        add al, [time]
        add al, [time]
        add al, [time]
        add al, [time]
        add al, [time]
		
	call setgray
        jmp palette

;Payload 1
scroll:
        push cx
            push dx
                add cx, [time]
                add dx, [time]

                and cx, dx
                xor dx, cx
            
                mov word [x], cx
                mov word [y], dx 
            pop dx
        pop cx
        
        fild dword [x]
        fsin
        fstp dword [r2]
        
        mov al, [r2]
        shr al, 6

        sub al, [palette]
        sub al, 2

        call setrainbow

        jmp palette

;Payload 2
plasma:
        push cx
            add cx, [time]

            mov word [zx], cx
        pop cx

        ;pr3 = = 128.0 + (128.0 * sin(zx / 8.0)) 
        fild dword [zx]
        fdiv dword [pr4]
        fsin
        fdiv dword [pr1]
        fmul dword [pr1]
        fadd dword [pr1]
        fstp dword [pr3]

        ;pr2 = (128.0 + (128.0 * sin(zy / 8.0))) + pr3
        fild dword [zy]
        fdiv dword [pr4]
        fsin
        fdiv dword [pr1]
        fmul dword [pr1]
        fadd dword [pr1]
        fadd dword [pr3]
        fstp dword [pr2]

        mov al, [pr2]
        shr al, 1

        sub al, [time]

        call setrainbow
        jmp palette

;Payload 3
tunnel:
        sub word [x], WSCREEN / 2
        sub word [y], HSCREEN / 2
			
        ;SINA = sin(r3)
        fild dword [r3]
        fsin
        fstp dword [sina]

        ;COSA = cos(r3)
        fild dword [r3]
        fcos
        fstp dword [cosa]

        ;COSA * x = r1
        fild dword [x]
        fmul dword [cosa]
        fstp dword [r1]

        ;SINA * y = r2
        fild dword [y]
        fmul dword [sina]
        fstp dword [r2]

        ;r1 - r2 = gx
        fild dword [r1]
        fsub dword [r2]
        fstp dword [gx]
        
        mov bx, word [gx]
        mov al, bl
   
        sub al, [time]

        call setgray
        jmp palette

;Payload 4
overlap:
        ;r1 = sin(angle) * zy
        fild qword [angle]
        fsin
        fmul dword [zy]
        fstp dword [r1]

        ;gx = cos(angle) * zx - r1
        fild qword [angle]
        fcos
        fmul dword [zx]
        fsub dword [r1]
        fstp dword [gx]

        ;r2 = cos(angle) * zy
        fild qword [angle]
        fcos
        fmul dword [zy]
        fstp dword [r2]

        ;gy = sin(angle) * zx + r2
        fild qword [angle]
        fsin
        fmul dword [zx]
        fadd dword [r2]
        fstp dword [gy]
        
        shr word [gx], 1
        shr word [gy], 1

        mov bx, word [time]
        and word [gx], bx
        and word [gy], bx

        ;gx ^ gy
        mov bx, [gx]
        add bx, [gy]
        mov al, bl

        shr al, 2

        call setrainbow
        jmp palette

;Payload 5
lasers:
        ;r4 = x / y
        fild dword [x]
        fild dword [y]
        fdiv
        fstp dword [r4]
        
        mov al, [r4]
        shr al, 4
        
        sub al, [time]

        call setpastel
        jmp palette

;Payload 6
squares:
        push dx
                add dx, [time]

                mov word [zy], dx
        pop dx
        
        ;r1 = zx * zx
        fild dword [zx]
        fmul dword [zx]
        fstp dword [r1]

        ;r2 = zy * zy
        fild dword [zy]
        fmul dword [zy]
        fstp dword [r2]

        ;r2 = r2 | !r1
        mov bx, word [r1]
        not bx
        or word [r2], bx

        mov al, [r2]
        shr al, 4

        add al, [time]
        add al, [palette]
        or al, [time]

        call setvga
        jmp palette

;Payload 7
wave:
        ;x *= y
        fild dword [x]
        fmul dword [y]
        fstp dword [x]

        mov al, [x]
        shr al, 4

        sub al, [time]

        call setgray
        jmp palette

;Payload 8
chaos:
        push cx
            push dx
                xor cx, dx
                not cx

                sub cx, [time]
                add dx, cx

                and dx, cx
                mov al, dl
            pop dx
        pop cx

        add al, [time]

        shr al, 2

        call setvga
        jmp palette

;Payload 9
lines:
        push dx
                add dx, [time]
                add word [x], dx
        pop dx

        fild dword [x]
        fmul dword [y]
        fstp dword [x]

        mov al, [x]
        shr al, 2

        sub al, [time]

        call setpastel
        jmp palette

;Payload 10
scrollxor:
        push cx
            push dx
                add cx, [time]

                xor cx, dx
                not dx

                mov word [zx], cx
                mov word [zy], dx
            pop dx
        pop cx

        ;r1 = sin(zx * zx) 
        fild dword [zx]
        fmul dword [zx]
        fsin
        fstp dword [r1]
        
        ;r2 = sin(zy * zy)
        fild dword [zy]
        fmul dword [zy]
        fsin
        fstp dword [r2]

        ;r2 += r1
        mov bx, word [r1]
        add word [r2], bx

        mov al, [r2]
        shr al, 4
        
        add al, [time]

        call setrainbow
        jmp palette

;Payload 11
edge:
        ;r1 = zx * zx
        fild dword [zx]
        fmul dword [zx]
        fstp dword [r1]

        ;r2 = zy * zy
        fild dword [zy]
        fmul dword [zy]
        fstp dword [r2]

        mov bx, word [r1]
        sub bx, word [r2]
        rcr bx, 6
        
        mov al, bl
        shr al, 4

        sub al, [time]

        jmp palette

;Payload 12
rainbowscroll:
        mov word [zx], cx
        mov word [zy], dx
        
        shr dword [zx], 4
        shr dword [zy], 4
        
        mov bx, word [zy]
        add word [zx], bx

        mov al, [zx]

        add al, [time]

        call setrainbow
        jmp palette

;Payload 13
roto:
        ;r1 = sin(angle2) * zy
        fild qword [angle2]
        fsin
        fmul dword [zy]
        fstp dword [r1]

        ;gx = cos(angle2) * zx - r1
        fild qword [angle2]
        fcos
        fmul dword [zx]
        fsub dword [r1]
        fstp dword [gx]

        ;r2 = cos(angle2) * zy
        fild qword [angle2]
        fcos
        fmul dword [zy]
        fstp dword [r2]

        ;gy = sin(angle2) * zx + r2
        fild qword [angle2]
        fsin
        fmul dword [zx]
        fadd dword [r2]
        fstp dword [gy]

        ;gx ^ gy
        mov bx, [gx]
        xor bx, [gy]
        mov al, bl

        shr al, 1

        jmp setpixel

;Fast reboot
crash:
        mov ax, 0x03
	int 0x19

;PAYLOAD'S VARIABLES ----------

;INT X, Y, Z
x: dw 0
y: dw 0
z: dw 0

;DOUBLE X, Y
zx: dd 0.0
zy: dd 0.0

;RESERVED INT X, Y
gx: dw 0.0
gy: dw 0.0

;PLASMA RESERVED VARIABLES
pr1: dw 8.0
pr2: dw 256.0
pr3: dw 256.0
pr4: dd 12.0

;GENERAL PURPOSE VARIABLES
r1: dd 0.0
r2: dd 0.0
r3: dd 0.0
r4: dd 0.0
r5: dd 20.0
r6: dd 0.0

;TUNNEL RESERVED VARIABLES
cosa: dd 0.0
sina: dd 0.0

;OVERLAP RESERVED VARIABLES
angle: dq 0.00
theta: dq 0.1

;ROTOZOOMER RESERVED VARIABLE
angle2: dq 0.00
alpha: dq 0.1
