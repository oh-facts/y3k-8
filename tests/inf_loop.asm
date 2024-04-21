; 1 char logger
; 3 uint logger

; 

    mov r1, 0       ; r1 = 0
L1:
    add  r1, 1      ; r1 += 1
    use  3, r1      ; 
    use  1, 10      ; new line
    jmp  L1         ;