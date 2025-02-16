BITS 16
ORG 00h

jmp init

init:
    push    cs                  ;code seg
    pop     ds                  ;data seg
    pop     es                  ;es seg reg (for di & si)
    push    word 0b800h         ;push gfx

    mov ax, 4f02h               ;set vesa compliant video modes
    mov bx, 117h                ;1024x768   65536  packed pixel
    int 10h

    call    main
    
main:                          ;after init
    call print_channel_description
    mov bl, 0fh
    mov si, str_endl
    call print

    mov ax, 0h

_oh:
    mov bl, 02h
    mov si, str_user_ultrasonic
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_ttm 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_gs 
    call print_user
    call print_oh

    mov bl, 04h
    mov si, str_user_lurka 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_nool       
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_andrej 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_wipet 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_chris 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_oht 
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_cry 
    call print_user
    call print_oh

    mov bl, 0dh
    mov si, str_user_hipster 
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_savage 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_elektro
    call print_user
    call print_oh

    mov bl, 0bh
    mov si, str_user_planethax 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_anoi 
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_ultralt 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_alryte 
    call print_user
    call print_oh

    mov bl, 08h
    mov si, str_user_sleepy 
    call print_user
    call print_oh

    mov bl, 09h
    mov si, str_user_cuberates 
    call print_user
    call print_oh

    mov bl, 02h
    mov si, str_user_everyone 
    call print_user
    call print_oh

    jmp _oh

print_channel_description:
    mov bl, 06h
    mov si, str_oh_channel_1
    call print
    mov si, str_oh_channel_2
    call print
    mov si, str_oh_channel_3
    call print
    mov si, str_oh_channel_4
    call print
    mov si, str_oh_channel_5
    call print

    ret

print_user:
    call wait_second
    call print

    ret

print_oh:
    add ax, 01h
    mov bl, 0fh
    mov si, str_endl
    call print
    mov si, str_oh
    call print
    cmp ax, 10h
    je print_edited
    mov si, str_endl
    call print
    mov si, str_endl
    call print

    ;mov ah, 09h
    ;mov al, ax
    ;mov cx, 01h
    ;int 10h

    ret

print_edited:
    mov bl, 09h
    mov si, str_edited
    call print
    ret

print:                         ;looping print character function
	lodsb                       ;load string
	or al, al
	jz done               ;is zf set?
	mov	ah,	0eh             ;teletype output
	int	10h                 ;BIOS function
	jmp	print              ;loop

wait_second:
    mov cx, 03h
    mov dx, 4240h
    mov ah, 86h
    int 15h

    ret

done:
    ret

halt:
    cli                          ;clear interrupts
    hlt                          ;halt cpu

; Full string
; let's break the world record (if there even is one)
; break chain = can't oh role
; only oh once, you can oh again after someone else ohs
; only use lowercase letters
; try not to edit, delete if you spelled it wrong

str_oh_channel_1 db    'let`s break the world record (if there even is one)', 0dh, 0ah, 0
str_oh_channel_2 db    'break chain = can`t oh role', 0dh, 0ah, 0
str_oh_channel_3 db    'only oh once, you can oh again after someone else ohs', 0dh, 0ah, 0
str_oh_channel_4 db    'only use lowercase letters', 0dh, 0ah, 0
str_oh_channel_5 db    'try not to edit, delete if you spelled it wrong', 0dh, 0ah, 0

str_oh db               'oh', 0
str_edited db           '(edited)', 0
str_endl db             0dh, 0ah, 0

str_user_ultrasonic db  'Ultrasonic', 0
str_user_ttm db         'tonythemaster999', 0
str_user_gs db          'G softwares', 0
str_user_lurka db       'Leurak', 0
str_user_nool db        'NullException', 0
str_user_andrej db      'Andrej Akan', 0
str_user_wipet db       'Wipet', 0
str_user_chris db       'Chris', 0
str_user_oht db         'oh 3', 0
str_user_cry db         'original me :(', 0
str_user_hipster db     'Mr Hipster Guy', 0
str_user_savage db      'Mr Savage Guy', 0
str_user_elektro db     'ElektroKill', 0
str_user_planethax db   'PlanetHax', 0
str_user_anoi db        'Anonimbus', 0
str_user_ultralt db     'idot', 0
str_user_alryte db      'Ryte', 0
str_user_sleepy db      'SleepMod', 0
str_user_cuberates db   'CuberatesPGR', 0
str_user_everyone db    'SomeOne', 0
str_user_idiot db       'picocode', 0
