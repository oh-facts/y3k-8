; r1, r2 ... r8 are general purpose registers. I don't remember why there are eight

movv r1, 10     ; r1 = 10
movv r2, 9      ; r2 = 9
addr r1, r2     ; r1 = r1 + r2;

; output
; r1: 0x13
; r2: 0x09
; ip: 0x09