; imagine these were variables
    movv r6, 3     ; uint logger
    movv r7, 1     ; char logger
    movv r8, 10    ; new line ascii

movv r1, 0
movv r2, 1

use r6, r1				; print r1
use r7, r8        ; print new line

use r6, r2
use r7, r8

movv r4, 2
movv r5, 14				; more than that and it overflows

L1:
		movr r3, r2
    addr r3, r1
	  
    movr r1, r2
    movr r2, r3

    use  r6, r3
    use  r7, r8
    addv r4, 1
    
    cmp r4, r5
    jl L1


; make bigger registers?
; even 16 bit is fine