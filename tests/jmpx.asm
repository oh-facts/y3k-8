    movv r1, 0
L1:
    addv r1, 1
    jmpx L1, 3

; r1 = 0;
; for(i32 i = 0; i <= 5; i ++)
; {
;     r1 += 1;
; }