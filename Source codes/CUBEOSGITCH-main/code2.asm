[BITS 16]
[ORG 0x7C00]  ; Boot sector origin

%define WSCREEN 320
%define HSCREEN 200
%define WCUBE 60

    jmp short Start
    nop

; Disk signature (optional)
Signature db 0xAA, 0x55

Start:
    ;Setup Mode 13h
    mov ax, 0x0013
    int 0x10

    ;Init FPU
    fninit

ResetDraw:
    ; Integer time
    inc word [i]

    cmp word [i], 1500
    jae done_reset_draw

    ; time += dtime
    ; time += 0.90 (substantially increased dtime for very fast rotation)
    fld dword [time]
    fadd dword [dtime]
    fstp dword [time]

    ; r1 = sin(time)
    fld dword [time]
    fsin
    fstp dword [r1]

    ; r2 = cos(time)
    fld dword [time]
    fcos
    fstp dword [r2]

    call ClearBuffers

    mov cx, WCUBE
.loopY:
    mov ax, -WCUBE
.loopX:
    call DrawCubePixel

    ; Face rotation
    xchg bx, cx
    neg bx

    dec si
    cmp si, 0x00
    jnz .loopX

    ; Rotate 90 deg around Y
    xchg ax, cx
    neg cx
    call DrawCubePixel

    ; Rotate other face by 180 deg around Y
    neg ax
    neg cx
    call DrawCubePixel

    ; Rotate 90 deg again
    xchg ax, cx
    neg cx

    ; 6 Faces
    mov si, 0x06

    inc ax
    cmp ax, WCUBE
    jne .loopX

    inc bx
    cmp bx, WCUBE
    jne .loopY

    call RenderVGA

    jmp ResetDraw

done_reset_draw:
    ; Infinite loop or other code if necessary
    jmp done_reset_draw

DrawCubePixel:
    pushad

    ; Store X, Y, Z
    mov word [x], ax
    mov word [y], bx
    mov word [z], cx

    ; Convert int to float
    fild word [x]
    fstp dword [x]
    fild word [y]
    fstp dword [y]
    fild word [z]
    fstp dword [z]

    ; X Rotation:
    ; Y = cos * Y - sin * Z
    ; Z = sin * Y + cos * Z
    fld dword [r1]
    fld dword [r2]

    fld dword [y]
    fmul st0, st1
    fld dword [z]
    fmul st0, st3
    fsubp

    fld dword [y]
    fmul st0, st3
    fld dword [z]
    fmul st0, st3
    faddp

    fstp dword [z]
    fstp dword [y]

    fstp st0
    fstp st0

    ; Y Rotation:
    ; X = cos * X + sin * Z
    ; Z = cos * Z - sin * X
    fld dword [r1]
    fld dword [r2]

    fld dword [x]
    fmul st0, st1
    fld dword [z]
    fmul st0, st3
    faddp

    fld dword [x]
    fmul st0, st3
    fld dword [z]
    fmul st0, st3
    fsubp

    ; Convert our depth value to an integer that fits in a byte
    fld st0
    fmul dword [zbuffer_scale]
    fistp word [z]
    fadd dword [z_add]

    ; Perform perspective projection
    fld dword [y]
    fdiv st0, st1
    fmul dword [scr_scale]
    fistp word [y]
    fdivp st1, st0
    fmul dword [scr_scale]
    fistp word [x]

    fstp st0
    fstp st0

    ; (X ^ Y) / 8
    xor ax, bx
    shr ax, 0x03
    mov si, ax

    ; 0x0F Interval
    and si, 0x0F

    mov bl, byte [palette + si]
    mov si, word [x]
    mov di, word [y]

    ; Go to the center
    add si, WSCREEN / 2
    add di, HSCREEN / 2

    cmp si, WSCREEN
    jge .skip
    test si, si
    js .skip

    cmp di, HSCREEN
    jge .skip
    test di, di
    js .skip

    ; Index = Y * 320 + X
    imul di, di, 320
    add di, si

    ; Load Z-Buffer in memory
    push 0x7E00  ; Assuming Z-Buffer starts at 0x7E00
    pop es

    ; Check if Z is greater than
    ; the one in Z-Buffer
    mov al, byte [z]
    cmp al, byte [es:di]
    jge .skip

    ; Put new Z value into the Z-Buffer
    mov byte [es:di], al

    push 0x7C00  ; Assuming Pixel Buffer starts at 0x7C00
    pop es

    ; Set Pixel
    mov byte [es:di], bl

.skip:
    popad
    ret

ClearBuffers:
    ; Z Buffer -> 0x7E00
    push 0x7E00
    pop es

    ; Fill Z Buffer with 0x7F
    mov cx, WSCREEN * HSCREEN
    mov al, 0x7F
    xor di, di
    rep stosb

    ; Pixel Buffer -> 0x7C00
    push 0x7C00
    pop es

    ; Fill Pixel Buffer with 0x00
    mov cx, WSCREEN * HSCREEN
    xor di, di
    rep stosb

    ret

RenderVGA:
    push ds

    push 0x7C00
    pop ds

    push 0xA000
    pop es

    mov cx, WSCREEN * HSCREEN
    xor si, si
    xor di, di
    rep movsb

    pop ds
    ret

; Variables and Constants
i dw 0

time dd 0.0
dtime dd 0.90  ; Substantially increased dtime for very fast rotation

z_add dd 300.0
zbuffer_scale dd 1.2
scr_scale dd 160.0

r1 dd 0.0
r2 dd 0.0

x dd 0.0
y dd 0.0
z dd 0.0

palette:
    db 0x20, 0x21, 0x22, 0x23
    db 0x24, 0x25, 0x26, 0x27
    db 0x28, 0x29, 0x2A, 0x2B
    db 0x2C, 0x2D, 0x2E, 0x2F

; Pad to 512 bytes (if needed)
times 510 - ($ - $$) db 0
dw 0xAA55  ; Boot signature
