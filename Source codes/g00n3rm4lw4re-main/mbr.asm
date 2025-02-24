[BITS 16]
[ORG 0x7C00]

; Set video mode (320x200x256)
mov ah, 0x00
mov al, 0x13
int 0x10

; Load the image data
mov si, image_data
mov di, 0xA000    ; Video memory start address

; Copy image data to video memory
mov cx, 32000      ; Size of image data (320x200 bytes)
rep movsb

; Hang the system (infinite loop)
hang:
    jmp hang

; Define the image data (replace with your raw image data)
image_data:
    ; (Your raw image data here)
    ; Example: db 0x00, 0x01, 0x02, ...
