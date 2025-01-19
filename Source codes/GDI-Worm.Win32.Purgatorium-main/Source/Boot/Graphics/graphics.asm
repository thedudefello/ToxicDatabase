[BITS    16]

reset:	
        ;Start all over again
        xor cx, cx
        mov dx, 0x08
        
        ;TIME++
        inc word [time]

        ;ANGLE2 += 0.1
        fld  dword [alpha]
        fadd dword [angle2]
        fstp dword [angle2]

        setpixel:
                ;X > W
                cmp cx, WSCREEN
                jae nextline
                        
                ;Y > H
                cmp dx, HSCREEN
                jae reset

                ;Set pixel
                int 0x10

                inc cx

                jmp payloads
                            
                ret

nextline:
        xor cx, cx
        inc dx

        jmp payloads