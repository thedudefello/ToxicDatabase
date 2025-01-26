;---------------------------------------------------
; Sorry Ass (remake of PC-DOS DONKEY) -- VileR 2016
;              FASM.EXE sorryass.asm
;---------------------------------------------------
use16

COM equ   1               ;0: boot sector :: 1: DOS version

IF COM
    org   100h
ELSE
    org   7c00h
    jmp   short segfix
segfix:                   
    jmp   0:start         ;enforce correct CS:IP
start:                    ;enforce good init values (TRUST NO ONE)
    clc
    cld
    push  cs              ;DX, BP, ES = don't care
    pop   ss
    push  cs
    pop   ds
    xor   ax,ax
    xor   bx,bx
    mov   cx,0FFh
    mov   si,start
    mov   sp,0FFFEh
    mov   di,sp
END IF

    ;set up video:
    inc   ax              ;gotta have color on composite systems ;)
    int   10h             ;go 40x25
    mov   ax,0B800h       ;init video seg (not all dos versions obey AX=0!)
    mov   es,ax           ;es=B800h ;di=sp=FFFEh (-2) on init (good enough)

    ;draw background:
    xchg  ax, cx          ;ax:= cx@init = 00FFh;cx:=B800h
    mov   ah,2Eh          ;ah:= attr, al:= FFh (char)
    rep   stosw           ;writing b800h words will try to stomp over memory
                          ;in >c000 too, but that's ROM-land so we don't mind
    push  si              ;program start

    ;prepare score labels:
    mov   si, text
    mov   dx,0105h        ;row, col
    call  wrtword         ;print them;CF clear = print 2 words

    ;get system time:
    xchg  ax, cx          ;CX==0 => AX:=0
    int   1Ah             ;get system time
    push  dx              ;store low word of system time as random seed

    ;init vars:
    mov   bp,3030h        ;BP = scores (ascii)- HIGH: donkey, LOW: driver
newturn: 
    mov   dx,1c11h        ;DX = car position-     DH: X-pos,   DL: Y-pos
newass:
    mov   bx,1c00h        ;BX = donkey position-  BH: X-pos,   BL: Y-pos

    ;randomize donkey's lane
    pop   cx              ;retrieve stored seed...
    pop   si              ;...and modifier location
    lodsw                 ;grab modifier + advance si
    add   ax,cx           ;fiddle with it
    jp    hold            ;do we switch?
    mov   bh,28h          ;yep
hold:
    push  si              ;store new modifier location...
    push  ax              ;...and post-fiddle seed value
    xor   cx,cx           ;ensure CH:=0 for later
    call  showpts         ;print scores
newstep:
    call  drwroad         ;clear road, draw lane marks

    ;draw car:
    inc   dx              ;bottom half: increment DL by 2 rows
    inc   dx
    call  drawcar
    dec   dx              ;top half: restore original y-pos
    dec   dx
    call  drawcar

    ;draw donkey:
    xchg  bx,dx           ;donkey location <-> car location
    mov   cl,4
    call  drawass         ;si now has offset of donkey
    call  sound
    xchg  bx,dx           ;switch them back

    hlt                   ;wait ~1/18 sec

    ;collision check:
    cmp   bh,dh           ;same lane?
    jne   no_hit          ;nope
    push  dx              ;save car pos
    sub   dl,bl           ;check diff
flipme:
    neg   dl              ;for abs val
    js    flipme          ;flip sign if negative
    cmp   dl,3            ; -3 <= (car_Y - donkey_Y) <= 3 ?
    pop   dx              ;restore car pos- flags unaffected
    jg    no_hit          ;no collision

    ;collision:
IF COM
    mov   si,100h         ;program start (code as explosion data)
    add   bp,si           ;increase donkey score too
ELSE
    mov   si, start
    add   bp, 100h        ;increase donkey score
END IF
    mov   cl, 38          ;# of animation "frames"
explode:
    push  cx
    mov   cl, 4           ;draw 4 rows
    call  drawass         ;reuse donkey code w/ explosion 'data'
    call  sound
    sub   si,37           ;odd number for more varied explosion
    pop   cx
    loop  explode         ;next iteration
    cmp   bp, 3A00h       ;did donkey win?
    jl    newturn         ;nope, start over
    stc                   ;yep, donkey victory
    jmp   endgame

no_hit:
    jmp   go_on           ;advance donkey & check keypress
switch:
    xor   dh, 034h        ;non-esc pressed? switch lanes

tests:
    cmp   bl, 32          ;donkey gone?
    jne   newstep         ;- nope, continue
    dec   dx              ;- yep, move car up
    cmp   dl, 7           ;did player score?
    jg    newass          ;- not yet, spawn new donkey
    inc   bp              ;- yes - player scored
    xchg  ax,bp
    cmp   al,3Ah          ;did player win?
    xchg  ax,bp
    jl    newturn         ;nope, start over
    clc                   ;yep, player victory

endgame: 
    mov   si, text+6      ;prepare victor announcement
    mov   dx,0305h        ;cursor pos for donkey
    jc    youlost
    mov   dl,30           ;cursor pos for player
youlost:
    xor   bx,bx           ;int 10h needs you baby
    stc
    call  wrtword         ;print them;CF set = print 2 words
    xor   ax,ax           ;wait for keypress
    int   16h
die:
IF COM
    mov   ax,3
    int   10h
    int   20h             ;can't RET, stack is soiled
ELSE
    jmp   0:start         ;be kind, rewind
END IF

;-------------------------------------------------------
go_on:
    inc   bx              ;advance donkey
    mov   ah,1            ;check for keypress
    int   16h
    jz    tests           ;nothing pressed
    xor   ah, ah          ;clear buffer
    int   16h
    cmp   al,1Bh          ;ESC pressed?
    je    die             ;quit (DOS) or restart (booter)
    jmp   switch          ;THERE IS NO ESCAPE!

    ;draw sprites:
drawcar:
    mov   si, sprites
    mov   cl,2            ;2 rows
drawass:
    mov   al,dh           ;X-pos
    cbw                   ;AH:=0
    xchg  di,ax           ;di = num_cols
    mov   al,80
    imul  dl              ;ax= num_rows*80 bytes/row
    add   di,ax           ;di: = screen position for drawing
drawlin:
    times 5 movsw         ;1b shorter than messing with CX
    add   di,70           ;next line
    loop  drawlin
    ret

    ;draw road:
drwroad:
    mov   cl,26           ;25 rows + one for the road
    mov   di,cx           ;starting screen position
    mov   ax,74DFh        ;char:= upper half block, grey/red
    test  bl,1            ;odd step? (test by donkey's y_pos)
    jnz   roadrow         ;yep, keep this char
    mov   al,0DCh         ;nope, change to lower half block
roadrow:
    stosw                 ;left edge
    push  cx
    stc                   ;for shorter loop
drwlane:
    mov   ah,0            ;attr:= invisible
    mov   cl,5            ;lane width
    rep   stosw
    jnc   nextrow         ;will only be taken the 2nd time
    mov   ah,0Fh          ;attr:= white on black
    stosw
    cmc
    jmp   drwlane
nextrow:
    mov   ah,74h
    stosw                 ;right edge
    add   di,54           ;next row
    pop   cx
    loop  roadrow
    ;ret = C3h = 1st byte of sprite data below

    ;data:
sprites:
    db 0C3h,000h,0DEh,004h,07Ch,04Eh,0DDh,004h,020h,007h ;car/2
    db 0B2h,008h,0C1h,00Ch,01Eh,04Bh,0C1h,00Ch,0B2h,008h
    db 020h,007h,020h,007h,020h,007h,020h,007h,020h,007h ;donkey
    db 020h,000h,020h,000h,05Ch,007h,0DCh,007h,02Fh,007h
    db 0FBh,007h,0DBh,007h,07Eh,070h,022h,074h,040h,007h
    db 020h,007h,0B3h,070h,020h,008h,0B3h,070h,020h,008h
text:
    db 'SSAUOYNOW'

    ;print text/hide cursor
wrtword:
    mov   ah,2            ;no lahf.. compatibility
    int   10h             ;set cursor position;bh (active page)=0
    mov   cl,3            ;loop x3
chrloop:
    lodsb                 ;load char into AL
    mov   ah, 0Ah         ;bios - write char
    int   10h
    loop  chrloop
    mov   dl,30           ;new column
    cmc                   ;do x2
    jc    wrtword
    mov   dx,1A0Fh        ;row 26, col 15
    mov   ah,2
    int   10h             ;hide cursor;AH=already 2
    ret

    ;print scores
showpts:
    xchg  bp, ax          ;get them
    mov   di, 0FCh
    xchg  ah, al          ;donkey first..
    stosb
    add   di, 49
    xchg  al, ah          ;driver second
    stosb
    xchg  bp, ax          ;put them back
    ret

    ;play sound, based on current sprite's Y-position
sound:
    push  dx              ;save positions
    mov   al,0b6h         ;command byte
    out   43h,al          ;tell timer 2 to expect value

    ;change pitch
    mov   al,dl
    out   42h,al          ;low counter byte
    shr   al,1
    out   42h,al          ;hi counter byte

    ;speaker on:
    in    al,61h          ;read current value
    or    al,3            ;turn speaker on
    out   61h,al

    ;tiny wait:
    mov   dh,09h          ;dl is insignificant
    call  readpit         ;ax:=current counter
    sub   ax,dx           ;ax:=counter target
    xchg  ax,dx           ;dx:=counter target
waitloop:
    call  readpit         ;ax:=current counter
    cmp   ax,dx           ;reached target? ; add carry check?
    jg    waitloop        ;nope, try again
    
    ;speaker off:
    in    al,61h          ;read current value
    and   al,252          ;turn speaker off
    out   61h,al
    call  wait_vs         ;wait for retrace for nice effect
    pop   dx              ;get positions back
    ret

readpit:
    xor   ax,ax           ;command byte
    out   43h,al          ;latch counter for channel 0 (system time)
    in    al,40h          ;al:=low counter byte
    xchg  ah, al          ;ah:=low counter byte
    in    al,40h          ;al:=hi counter byte
    xchg  ah, al
    ret

wait_vs:
    mov   dx,03DAh
wax_on:
    in    al,dx
    test  al,8
    jz    wax_on
wax_off:
    in    al,dx
    test  al,8
    jnz   wax_off
    ret

IF ~COM
    times 510-($-$$) db 0 ;pad to sector size
    dw    0AA55h          ;magic marker
END IF
