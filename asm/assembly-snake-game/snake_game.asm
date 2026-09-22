.MODEL SMALL
.STACK 200h

SCREEN_W    EQU 80
SCREEN_H    EQU 25
PLAY_X0     EQU 1
PLAY_X1     EQU 78
PLAY_Y0     EQU 2
PLAY_Y1     EQU 23
PLAY_W      EQU 78
PLAY_H      EQU 22
MAXLEN      EQU 120
DELAY_OUT   EQU 6
DELAY_IN    EQU 12000
BLANK_CELL  EQU 0720h

HEAD_ATTR   EQU 0Eh
BODY_ATTR   EQU 0Ah
FOOD_ATTR   EQU 0Ch
BORDER_ATTR EQU 1Fh
SPACE_ATTR  EQU 07h

SC_UP       EQU 48h
SC_DOWN     EQU 50h
SC_LEFT     EQU 4Bh
SC_RIGHT    EQU 4Dh
SC_ESC      EQU 01h

.DATA
    snakeX      db MAXLEN dup(?)
    snakeY      db MAXLEN dup(?)
    snakeLen    dw ?
    dirX        db ?
    dirY        db ?
    pendDirX    db ?
    pendDirY    db ?
    newHeadX    db ?
    newHeadY    db ?
    oldTailX    db ?
    oldTailY    db ?
    foodX       db ?
    foodY       db ?
    eating      db ?
    gameOver    db ?
    score       dw ?
    seed        dw ?
    textAttr    db 0Fh
    numbuf      db 6 dup(?)
    numLen      dw ?

    titleMsg    db 'S N A K E$'
    helpMsg     db 'Arrows: Move    Esc: Quit$'
    scoreLabel  db 'SCORE: $'
    overMsg     db 'G A M E   O V E R$'
    finalMsg    db 'Final Score: $'
    restartMsg  db 'Press R to play again, any other key to exit$'

.CODE
main PROC FAR
    mov ax, @data
    mov ds, ax

    mov ax, 0003h
    int 10h

    mov ax, 0040h
    mov es, ax
    mov ax, es:[006Ch]
    mov seed, ax

restartAll:
    mov gameOver, 0
    mov score, 0
    mov dirX, 1
    mov dirY, 0
    mov pendDirX, 1
    mov pendDirY, 0

    call clearScreen
    call drawBorder
    call drawStatus
    call initSnake
    call drawSnake
    call placeFood
    call drawFood
    call drawScore

gameLoop:
    call delay

    cmp gameOver, 1
    je  endGame

    mov al, pendDirX
    mov dirX, al
    mov al, pendDirY
    mov dirY, al

    mov al, snakeX
    add al, dirX
    mov newHeadX, al
    mov al, snakeY
    add al, dirY
    mov newHeadY, al

    mov eating, 0
    mov al, newHeadX
    cmp al, foodX
    jne notEat
    mov al, newHeadY
    cmp al, foodY
    jne notEat
    mov eating, 1
notEat:

    call checkCollide
    cmp gameOver, 1
    je  endGame

    call moveSnake

    cmp eating, 1
    jne gameLoop
    inc score
    call drawScore
    call placeFood
    call drawFood
    jmp gameLoop

endGame:
    call showGameOver
    call waitForRestart
    cmp ax, 1
    je  restartAll

    mov ax, 0003h
    int 10h
    mov ax, 4C00h
    int 21h
main ENDP

plot PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push di
    push es

    mov ch, 0
    mov cl, dl
    mov al, dh
    mov ah, 0
    mov dx, SCREEN_W
    mul dx
    add ax, cx
    add ax, ax
    mov di, ax

    mov ax, 0B800h
    mov es, ax
    mov ax, bx
    mov es:[di], ax

    pop es
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret
plot ENDP

drawText PROC NEAR
    push ax
    push bx
    push dx
    push si
dtLoop:
    mov al, [si]
    cmp al, '$'
    je  dtEnd
    mov bl, al
    mov bh, textAttr
    call plot
    inc dl
    inc si
    jmp dtLoop
dtEnd:
    pop si
    pop dx
    pop bx
    pop ax
    ret
drawText ENDP

clearScreen PROC NEAR
    push ax
    push cx
    push di
    push es
    mov ax, 0B800h
    mov es, ax
    xor di, di
    mov ax, BLANK_CELL
    mov cx, SCREEN_W * SCREEN_H
csLoop:
    mov es:[di], ax
    add di, 2
    loop csLoop
    pop es
    pop di
    pop cx
    pop ax
    ret
clearScreen ENDP

drawBorder PROC NEAR
    push ax
    push bx
    push dx
    mov bl, '#'
    mov bh, BORDER_ATTR

    mov dh, PLAY_Y0 - 1
    mov dl, 0
topLoop:
    call plot
    inc dl
    cmp dl, SCREEN_W
    jb  topLoop

    mov dh, PLAY_Y1 + 1
    mov dl, 0
botLoop:
    call plot
    inc dl
    cmp dl, SCREEN_W
    jb  botLoop

    mov dl, 0
    mov dh, PLAY_Y0 - 1
leftLoop:
    call plot
    inc dh
    cmp dh, PLAY_Y1 + 2
    jb  leftLoop

    mov dl, SCREEN_W - 1
    mov dh, PLAY_Y0 - 1
rightLoop:
    call plot
    inc dh
    cmp dh, PLAY_Y1 + 2
    jb  rightLoop

    pop dx
    pop bx
    pop ax
    ret
drawBorder ENDP

drawStatus PROC NEAR
    mov textAttr, 0Fh
    mov dh, 0
    mov dl, 2
    mov si, offset titleMsg
    call drawText
    mov dh, 0
    mov dl, 30
    mov si, offset helpMsg
    call drawText
    ret
drawStatus ENDP

initSnake PROC NEAR
    push ax
    push si
    mov snakeLen, 4
    xor si, si
initLoop:
    mov ax, 10
    sub ax, si
    mov snakeX[si], al
    mov snakeY[si], 12
    inc si
    cmp si, 4
    jb  initLoop
    pop si
    pop ax
    ret
initSnake ENDP

drawSnake PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si
    mov ax, snakeLen
    xor si, si
dsLoop:
    cmp si, 0
    jne bodySeg
    mov bl, '@'
    mov bh, HEAD_ATTR
    jmp plotSeg
bodySeg:
    mov bl, 'o'
    mov bh, BODY_ATTR
plotSeg:
    mov dh, snakeY[si]
    mov dl, snakeX[si]
    call plot
    inc si
    cmp si, ax
    jb  dsLoop
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
drawSnake ENDP

moveSnake PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si

    mov si, snakeLen
    dec si
    mov al, snakeX[si]
    mov oldTailX, al
    mov al, snakeY[si]
    mov oldTailY, al

    cmp eating, 1
    jne noGrow
    mov ax, snakeLen
    cmp ax, MAXLEN
    jae noGrow
    inc ax
    mov snakeLen, ax
noGrow:

    mov si, snakeLen
    dec si
shiftLoop:
    cmp si, 0
    je  shiftDone
    mov bx, si
    dec bx
    mov al, snakeX[bx]
    mov snakeX[si], al
    mov al, snakeY[bx]
    mov snakeY[si], al
    dec si
    jmp shiftLoop
shiftDone:

    mov al, newHeadX
    mov snakeX, al
    mov al, newHeadY
    mov snakeY, al

    cmp eating, 1
    je  skipErase
    mov dh, oldTailY
    mov dl, oldTailX
    mov bl, ' '
    mov bh, SPACE_ATTR
    call plot
skipErase:

    mov cx, snakeLen
    cmp cx, 2
    jb  drawHeadOnly
    mov dh, snakeY[1]
    mov dl, snakeX[1]
    mov bl, 'o'
    mov bh, BODY_ATTR
    call plot
drawHeadOnly:

    mov dh, newHeadY
    mov dl, newHeadX
    mov bl, '@'
    mov bh, HEAD_ATTR
    call plot

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
moveSnake ENDP

checkCollide PROC NEAR
    push ax
    push cx
    push si

    cmp newHeadX, PLAY_X0
    jb  collide
    cmp newHeadX, PLAY_X1
    ja  collide
    cmp newHeadY, PLAY_Y0
    jb  collide
    cmp newHeadY, PLAY_Y1
    ja  collide

    mov cx, snakeLen
    cmp eating, 1
    je  selfAll
    dec cx
selfAll:
    xor si, si
selfLoop:
    mov al, snakeX[si]
    cmp al, newHeadX
    jne selfNext
    mov al, snakeY[si]
    cmp al, newHeadY
    je  collide
selfNext:
    inc si
    loop selfLoop
    jmp collideDone
collide:
    mov gameOver, 1
collideDone:
    pop si
    pop cx
    pop ax
    ret
checkCollide ENDP

rand PROC NEAR
    push cx
    push dx
    mov ax, seed
    mov cx, 25173
    mul cx
    add ax, 13849
    mov seed, ax
    pop dx
    pop cx
    ret
rand ENDP

placeFood PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si
retryFood:
    call rand
    mov cx, PLAY_W
    xor dx, dx
    div cx
    add dx, PLAY_X0
    mov bx, dx
    mov foodX, bl

    call rand
    mov cx, PLAY_H
    xor dx, dx
    div cx
    add dx, PLAY_Y0
    mov foodY, dl

    xor si, si
    mov cx, snakeLen
chkFood:
    mov al, snakeX[si]
    cmp al, foodX
    jne nextFood
    mov al, snakeY[si]
    cmp al, foodY
    je  retryFood
nextFood:
    inc si
    loop chkFood

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
placeFood ENDP

drawFood PROC NEAR
    mov dh, foodY
    mov dl, foodX
    mov bl, '*'
    mov bh, FOOD_ATTR
    call plot
    ret
drawFood ENDP

itoa PROC NEAR
    push bx
    push cx
    push dx
    push di
    push si
    xor si, si
    mov bx, 10
convLoop:
    xor dx, dx
    div bx
    push dx
    inc si
    cmp ax, 0
    jne convLoop
    mov cx, si
    mov numLen, si
    mov di, offset numbuf
storeLoop:
    pop ax
    add al, '0'
    mov [di], al
    inc di
    loop storeLoop
    pop si
    pop di
    pop dx
    pop cx
    pop bx
    ret
itoa ENDP

drawScore PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si
    mov textAttr, 0Fh
    mov dh, 0
    mov dl, 62
    mov si, offset scoreLabel
    call drawText
    mov ax, score
    call itoa
    mov dh, 0
    mov dl, 69
    mov si, offset numbuf
    mov cx, numLen
scLoop:
    mov al, [si]
    mov bl, al
    mov bh, 0Fh
    call plot
    inc dl
    inc si
    loop scLoop
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
drawScore ENDP

handleInput PROC NEAR
    push ax
    push dx
    mov ah, 01h
    int 16h
    jz  noKey
    mov ah, 00h
    int 16h

    cmp ah, SC_ESC
    je  quitNow
    cmp ah, SC_UP
    je  tryUp
    cmp ah, SC_DOWN
    je  tryDown
    cmp ah, SC_LEFT
    je  tryLeft
    cmp ah, SC_RIGHT
    je  tryRight
    jmp noKey
quitNow:
    mov gameOver, 1
    jmp noKey
tryUp:
    cmp dirY, 1
    je  noKey
    mov pendDirX, 0
    mov pendDirY, -1
    jmp noKey
tryDown:
    cmp dirY, -1
    je  noKey
    mov pendDirX, 0
    mov pendDirY, 1
    jmp noKey
tryLeft:
    cmp dirX, 1
    je  noKey
    mov pendDirX, -1
    mov pendDirY, 0
    jmp noKey
tryRight:
    cmp dirX, -1
    je  noKey
    mov pendDirX, 1
    mov pendDirY, 0
noKey:
    pop dx
    pop ax
    ret
handleInput ENDP

delay PROC NEAR
    push ax
    push cx
    push dx
    mov dx, DELAY_OUT
dOuter:
    call handleInput
    cmp gameOver, 1
    je  dDone
    mov cx, DELAY_IN
dInner:
    loop dInner
    dec dx
    jnz dOuter
dDone:
    pop dx
    pop cx
    pop ax
    ret
delay ENDP

showGameOver PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si
    mov textAttr, 0Ch
    mov dh, 12
    mov dl, 31
    mov si, offset overMsg
    call drawText
    mov textAttr, 0Fh
    mov dh, 13
    mov dl, 34
    mov si, offset finalMsg
    call drawText
    mov ax, score
    call itoa
    mov dh, 13
    mov dl, 47
    mov si, offset numbuf
    mov cx, numLen
goLoop:
    mov al, [si]
    mov bl, al
    mov bh, 0Fh
    call plot
    inc dl
    inc si
    loop goLoop
    mov textAttr, 0Eh
    mov dh, 15
    mov dl, 18
    mov si, offset restartMsg
    call drawText
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
showGameOver ENDP

waitForRestart PROC NEAR
    mov ah, 00h
    int 16h
    cmp al, 'r'
    je  wrYes
    cmp al, 'R'
    je  wrYes
    cmp al, 0Dh
    je  wrYes
    xor ax, ax
    ret
wrYes:
    mov ax, 1
    ret
waitForRestart ENDP

END main
