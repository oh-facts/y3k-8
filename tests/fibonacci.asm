; 3  uint logger
; 1 char logger
; 10 new line ascii

mov r1, 0
mov r2, 1

use 3, r1				; print r1
use 1, 10        ; print new line

use 3, r2
use 1, 10

mov r4, 2

L1:
		mov r3, r2
    add r3, r1
	  
    mov r1, r2
    mov r2, r3

    use  3, r3
    use  1, 10
    add r4, 1
    
    cmp r4, 14
    jl L1


; make bigger registers?
; even 16 bit is fine