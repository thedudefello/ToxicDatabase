[BITS    16]
[ORG 0x7C00]

WSCREEN equ 320
HSCREEN equ 200

call setup
call palette


setup:

    mov ah, 0x00
    mov al, 0x13
    int 0x10

    push 0xA000
    pop es
    mov ah, 0x0C

    xor al, al   ; AL = Color
    xor bx, bx   ; BX = Page
    xor cx, cx   ; CX = X
    mov dx, 0x08 ; DX = Y

    fninit


    ret

		
		
reset:	
	
	xor cx, cx
	mov dx, 0x08
	
	;COLOR++
	inc word [color]
		
	palette:
		;Store CX and DX to use it later
		;using FPU instructions
		mov word [x], cx
		mov word [y], dx
		
		;Payload's execution system
		cmp word [color], 2048
		ja crash
				
		cmp word [color], 1792
		ja circles
				
		cmp word [color], 936
		ja sierpinski
		
		cmp word [color], 680
		ja squares
		
		cmp word [color], 512
		ja parabola
		
		cmp word [color], 430
		ja hearts
				
		cmp word [color], 700
		ja stars
				
		cmp word [color], 256
		ja xorfractal
				
		cmp word [color], 60
		ja scroll
		jb statics
				
		setpixel:
			
			cmp cx, WSCREEN
			jae nextline
					
			
			cmp dx, HSCREEN
			jae reset

			int 0x10

			inc cx
			jmp palette
						
			ret





statics:	
   mov bx, cx   
    xor bx, dx  

  
    mov al, bl   
    shr al, 7  

  
    add al, [color] 
    shr al, 4     

 
    mov ah, 0x0C  
    int 0x10      

    jmp HSV         
 

scroll: 
   
 mov bx, cx   ; Store X position for things
    xor bx, dx   

    mov al, bl   
    shr al, 3    
 
    add al, [color] 
    shr al, 3       
   
    mov ah, 0x0C   
    int 0x10      

    jmp HSV       
xorfractal:

 mov bx, cx          
    not bx              
    
    and bx, dx         
    
    add bl, [color]
    mov al, bl
    shr al, 4            
    
    not al              
    
    jmp HSV
 
stars:
  mov bx, cx   
    xor bx, dx   

    
    mov al, bl  
    shr al, 5   

  
    add al, [color] 
    shr al, 7     


    mov ah, 0x0C  
    int 0x10       

    jmp HSV 
		
hearts:
  mov bx, cx   
    xor bx, dx  
 
    mov al, bl   
    shr al, 1    

 
    add al, [color] 
    shr al, 3     

    ; Set the pixel color
    mov ah, 0x0C   
    int 0x10      
    jmp HSV 
		
parabola:
         
		
squares:

 
		
sierpinski:
	 mov bx, cx   ; Store X position for things
    xor bx, dx   

    mov al, bl   
    shr al, 2   
 
    add al, [color] 
    shr al, 1       
   
    mov ah, 0x0C   
    int 0x10      

    jmp HSV
		
circles:
	
		
crash:
	mov ax, 0x03
	int 0x19
			
		
HSV:
	cmp al, 55
        ja delhsv
        
        cmp al, 32
        jb addhsv
		
	jmp setpixel

delhsv:
        sub al, 16
        jmp HSV
        
addhsv:
        add al, 32
        jmp HSV

                
nextline:
        xor cx, cx
        inc dx

        jmp palette 





color: dw 0
x: dw 0
y: dw 0

zx: dd 1.0
zy: dd 0.0

a: dd 0.0
b: dd 0.0
; MBR Signature
times 510 - ($ - $$) db 0
dw 0xAA55
