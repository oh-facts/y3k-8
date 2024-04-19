movv r1, 1
movv r2, 2

cmp r1, r2
jg L1
jmp L2

L1: 
movv r3, 1
jmp L3

L2:
movv r4, 1

L3:

; if r1 > r2, then r3 = 1
; otherwise r4 = 1