.MODEL SMALL
.STACK 200h

.DATA
    menuTitle    db 'C A L C U L A T O R$'
    menuLine1    db '1. Add$'
    menuLine2    db '2. Subtract$'
    menuLine3    db '3. Multiply$'
    menuLine4    db '4. Divide$'
    menuLine5    db '0. Exit$'
    choiceMsg    db 'Choose an option: $'
    firstMsg     db 'First number:  $'
    secondMsg    db 'Second number: $'
    resultMsg    db 'Result: $'
    quotMsg      db 'Quotient:  $'
    remMsg       db 'Remainder: $'
    divZeroMsg   db 'Cannot divide by zero$'
    overMsg      db 'Result too large for 16 bits$'
    badNumMsg    db 'Not a valid number, try again$'
    badChoiceMsg db 'Unknown option, try again$'
    pauseMsg     db 'Press any key to continue...$'
    byeMsg       db 'Goodbye$'
    newline      db 0Dh, 0Ah, '$'

    inBuf        db 12
    inLen        db ?
    inChars      db 12 dup(?)
    numSign      db ?
    firstNum     dw ?
    secondNum    dw ?
    result       dw ?
    remainder    dw ?

.CODE
main PROC FAR
    mov ax, @data
    mov ds, ax

menuLoop:
    call clearScreen
    call drawMenu
    call readChoice
    cmp al, '0'
    je  quit
    cmp al, '1'
    je  doAdd
    cmp al, '2'
    je  doSub
    cmp al, '3'
    je  doMul
    cmp al, '4'
    je  doDiv
    call printBadChoice
    jmp pauseAndMenu

doAdd:
    call getTwoNumbers
    mov ax, firstNum
    add ax, secondNum
    jo  overflowLine
    mov result, ax
    call showResult
    jmp pauseAndMenu

doSub:
    call getTwoNumbers
    mov ax, firstNum
    sub ax, secondNum
    jo  overflowLine
    mov result, ax
    call showResult
    jmp pauseAndMenu

doMul:
    call getTwoNumbers
    mov ax, firstNum
    imul secondNum
    mov cx, dx
    cwd
    cmp cx, dx
    jne overflowLine
    mov result, ax
    call showResult
    jmp pauseAndMenu

doDiv:
    call getTwoNumbers
    cmp secondNum, 0
    je  divZeroLine
    mov ax, firstNum
    cwd
    idiv secondNum
    mov result, ax
    mov remainder, dx
    call showDivResult
    jmp pauseAndMenu

divZeroLine:
    call printNewline
    mov dx, offset divZeroMsg
    call printString
    call printNewline
    jmp pauseAndMenu

overflowLine:
    call printNewline
    mov dx, offset overMsg
    call printString
    call printNewline

pauseAndMenu:
    call printNewline
    mov dx, offset pauseMsg
    call printString
    mov ah, 01h
    int 21h
    jmp menuLoop

quit:
    call clearScreen
    mov dx, offset byeMsg
    call printString
    call printNewline
    mov ax, 4C00h
    int 21h
main ENDP

clearScreen PROC NEAR
    push ax
    push bx
    push cx
    mov ah, 06h
    mov al, 0
    xor cx, cx
    mov dh, 24
    mov dl, 79
    mov bh, 07h
    int 10h
    pop cx
    pop bx
    pop ax
    ret
clearScreen ENDP

printString PROC NEAR
    push ax
    push dx
    mov ah, 09h
    int 21h
    pop dx
    pop ax
    ret
printString ENDP

printNewline PROC NEAR
    push ax
    push dx
    mov dx, offset newline
    mov ah, 09h
    int 21h
    pop dx
    pop ax
    ret
printNewline ENDP

drawMenu PROC NEAR
    mov dx, offset menuTitle
    call printString
    call printNewline
    call printNewline
    mov dx, offset menuLine1
    call printString
    call printNewline
    mov dx, offset menuLine2
    call printString
    call printNewline
    mov dx, offset menuLine3
    call printString
    call printNewline
    mov dx, offset menuLine4
    call printString
    call printNewline
    mov dx, offset menuLine5
    call printString
    call printNewline
    call printNewline
    ret
drawMenu ENDP

readChoice PROC NEAR
    mov dx, offset choiceMsg
    call printString
    mov ah, 01h
    int 21h
    call printNewline
    ret
readChoice ENDP

getTwoNumbers PROC NEAR
    mov dx, offset firstMsg
    call printString
    call readNumber
    mov firstNum, ax
    mov dx, offset secondMsg
    call printString
    call readNumber
    mov secondNum, ax
    ret
getTwoNumbers ENDP

readNumber PROC NEAR
    push cx
    push dx
    push si
rnAgain:
    mov dx, offset inBuf
    mov ah, 0Ah
    int 21h
    call printNewline
    mov numSign, 0
    xor si, si
    mov cl, inLen
    mov ch, 0
    jcxz rnBad
    mov al, inChars
    cmp al, '-'
    jne rnNotNeg
    mov numSign, 1
    inc si
    dec cx
    jmp rnFirst
rnNotNeg:
    cmp al, '+'
    jne rnFirst
    inc si
    dec cx
rnFirst:
    jcxz rnBad
    xor ax, ax
rnLoop:
    mov bl, inChars[si]
    cmp bl, '0'
    jb  rnBad
    cmp bl, '9'
    ja  rnBad
    sub bl, '0'
    mov bh, 0
    mov dx, 10
    mul dx
    or  dx, dx
    jnz rnBad
    add ax, bx
    jo  rnBad
    inc si
    loop rnLoop
    cmp numSign, 1
    jne rnDone
    neg ax
rnDone:
    jmp rnEnd
rnBad:
    mov dx, offset badNumMsg
    call printString
    call printNewline
    jmp rnAgain
rnEnd:
    pop si
    pop dx
    pop cx
    ret
readNumber ENDP

printNumber PROC NEAR
    push ax
    push bx
    push cx
    push dx
    push si
    cmp ax, 0
    jge pnPos
    push ax
    mov dl, '-'
    mov ah, 02h
    int 21h
    pop ax
    neg ax
pnPos:
    xor si, si
    mov bx, 10
pnLoop:
    xor dx, dx
    div bx
    push dx
    inc si
    cmp ax, 0
    jne pnLoop
pnPrint:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    dec si
    jnz pnPrint
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
printNumber ENDP

showResult PROC NEAR
    call printNewline
    mov dx, offset resultMsg
    call printString
    mov ax, result
    call printNumber
    call printNewline
    ret
showResult ENDP

showDivResult PROC NEAR
    call printNewline
    mov dx, offset quotMsg
    call printString
    mov ax, result
    call printNumber
    call printNewline
    mov dx, offset remMsg
    call printString
    mov ax, remainder
    call printNumber
    call printNewline
    ret
showDivResult ENDP

printBadChoice PROC NEAR
    call printNewline
    mov dx, offset badChoiceMsg
    call printString
    call printNewline
    ret
printBadChoice ENDP

END main
