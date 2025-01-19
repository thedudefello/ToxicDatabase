[BITS    16]

;SI = STRING
;DI = POSITION
strthread:
        call resetcursor
        call printstr

        inc byte [printed + di]

        ret

;scroll
thread1:
        cmp byte [printed], 0x00
        jnz scroll

        call stopsound

        mov word [mincolor], 52
        mov word [maxcolor], 55

        mov si, str2
        mov di, 0x00
        call strthread

        jmp scroll

;plasma
thread2:
        cmp byte [printed + 1], 0x00
        jnz plasma

        mov word [mincolor], 64
        mov word [maxcolor], 79

        mov word [delcol], 31

        mov si, str3
        mov di, 0x01
        call strthread

        jmp plasma

;tunnel
thread3:
        cmp byte [printed + 2], 0x00
        jnz tunnel

        mov word [mincolor], 14
        mov word [maxcolor], 16

        ;Restore previous change
        mov word [delcol], 16

        mov si, str4
        mov di, 0x02
        call strthread

        jmp tunnel

;overlap
thread4:
        ;ANGLE += 0.1
        fild dword [theta]
        fdiv dword [angle]
        fstp dword [angle]

        cmp byte [printed + 3], 0x00
        jnz overlap

        mov word [mincolor], 32
        mov word [maxcolor], 55

        mov si, str5
        mov di, 0x03
        call strthread

        jmp overlap

;lasers
thread5:
        cmp byte [printed + 4], 0x00
        jnz lasers

        mov word [mincolor], 80
        mov word [maxcolor], 103

        mov si, str6
        mov di, 0x04
        call strthread

        jmp lasers

;squares
thread6:
        cmp byte [printed + 5], 0x00
        jnz squares

        mov word [mincolor], 80
        mov word [maxcolor], 84

        mov si, str7
        mov di, 0x05
        call strthread

        jmp squares

;"wave"
thread7:
        cmp byte [printed + 6], 0x00
        jnz wave

        mov word [mincolor], 28
        mov word [maxcolor], 32

        mov si, str8
        mov di, 0x06
        call strthread

        jmp wave

;chaos
thread8:
        cmp byte [printed + 7], 0x00
        jnz chaos

        mov word [mincolor], 1
        mov word [maxcolor], 16

        mov si, str9
        mov di, 0x07
        call strthread

        jmp chaos

;lines
thread9:
        cmp byte [printed + 8], 0x00
        jnz lines

        mov word [mincolor], 98
        mov word [maxcolor], 102

        mov si, str10
        mov di, 0x08
        call strthread

        jmp lines

;scrollxor
thread10:
        cmp byte [printed + 9], 0x00
        jnz scrollxor

        mov word [mincolor], 0x47
        mov word [maxcolor], 0x4A

        mov si, str11
        mov di, 0x09
        call strthread

        jmp scrollxor

;edge
thread11:
        cmp byte [printed + 10], 0x00
        jnz edge

        mov word [pxmaxcolor], 31
        mov word [pxmincolor], 25

        mov word [mincolor], 28
        mov word [maxcolor], 32

        mov word [addcol], 20

        mov si, str12
        mov di, 10
        call strthread

        jmp edge

;rainbow scroll
thread12:
        cmp byte [printed + 11], 0x00
        jnz rainbowscroll

        mov word [maxcolor], 56
        mov word [mincolor], 31

        mov word [addcol], 32
        mov word [delcol], 31

        mov si, str13
        mov di, 11
        call strthread

        jmp rainbowscroll

;roto
thread13:
        cmp byte [printed + 12], 0x00
        jnz roto

        mov bx, 0x00
        call setvgapalette

        mov word [mincolor], 52
        mov word [maxcolor], 54

        mov si, str14
        mov di, 12
        call strthread

        jmp roto

;--------------------------------------------------------------

;This section contains every strings for each payload

str1:  db "       Welcome to my Purgatorium!       ", 0x00 ;noise
str2:  db "This river of feelings is my own hell...", 0x00 ;scroll
str3:  db "     Seeking meaning till my death.     ", 0x00 ;plasma
str4:  db "     Walking alone at the darkness.     ", 0x00 ;tunnel
str5:  db "Shadows and light intertwining together.", 0x00 ;overlap
str6:  db " Having my brain melted into nothing... ", 0x00 ;lasers
str7:  db " Repeating the same thing again forever ", 0x00 ;squares
str8:  db "I guess that I'll not find any answers..", 0x00 ;waves
str9:  db "   Complete chaos... Full disorder...   ", 0x00 ;chaos
str10: db "Everything is destroyed, no turning back", 0x00 ;lines
str11: db "       Chained here for eternity.       ", 0x00 ;scrollxor
str12: db "         Condemned to suffering         ", 0x00 ;edge
str13: db "      Beyond the veil of illusions      ", 0x00 ;rainbow scroll
str14: db "      Living on the vortex of life      ", 0x00 ;roto

;This variable manages the state of each print

printed: times 13 dw 0x00

;This is the most important variable, since it
;will be useful to our full threading system.

time: dw 0
