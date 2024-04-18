		jmp L2
L1:
		addv r1, 1
    jmp  L4
		addv r1, 1		; skipped

L2: 
		movv r2, 2
		jmp L1

L3:
		movv r3, 3		; skipped

L4: 
		movv r4, 4
    jmp L5

L5:

; comment out stuff and put more jmps.
; todo
; make a std library
; allow including other files