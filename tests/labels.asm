		jmp L2
L1:
		addv r1, 1
    jmp  L4
 
L2: 
		movv r2, 2
		jmp L1

L3:
		movv r3, 3		;completely skipped

L4: 
		movv r4, 4