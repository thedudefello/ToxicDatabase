[BITS    16]

playsound:
        pusha
                ;Counter
                mov al, 0xB6
                out 0x43, al

                ;Frequency
                mov ax, 300
                shr al, 6
                out 0x42, al

                ;Enable PC Speaker
                in al, 0x61
                or al, 3
                out 0x61, al
        popa

        ret

stopsound:
        pusha
                ;Disable PC Speaker
                in al, 0x61
                and al, 0xFC
                out 0x61, al
        popa

        ret