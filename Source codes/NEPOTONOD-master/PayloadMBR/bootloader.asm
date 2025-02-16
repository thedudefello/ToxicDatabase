;==================================================================;
;                         Ultrasonic OS
;                   The best OS in the planet!
;                       code by Ultrasonic
;           bootloader.asm
;           The bootloader. The first sector of the floppy drive.
;           It jumps to the kernel
;==================================================================;
; WARNING:
; Most code from this bootloader is taken from Chris's one.
; It is almost an exact copy, so plz, don't remember it to me.

    bits 16                     ; make it 16 bit. Maybe i will do it 32 in the future.
    org 7c00h                   ; load in memory at 0x7c00

kernel_segment      equ 1000h
kernel_size         equ 3
kernel_start        equ 1

load:
    cli
    mov     sp, 9000h
    mov     ss, sp
    mov     sp, 0ffffh
    sti                         ;enable interrupts

    push    word kernel_segment
    pop     es

    mov     al, kernel_size
    mov     cl, kernel_start+1
    mov     dl, 00h             ; drive 0 (A:)
    mov     dh, 00h             ; head 0
    mov     ch, 00h             ; cylinder 0
    mov     ah, 02h             ; read
    int     13h                 ; BIOS disk interruption
    jc $                        ; loop if cf set
    jmp kernel_segment : 00h    ; if not, jump into kernel.

times 510 -($ - $$) db 0        ; bootloader has to be 512 bytes long, so we pad the resting space with zeros
dw 0aa55h                       ; add 16 bit bootloader signature
