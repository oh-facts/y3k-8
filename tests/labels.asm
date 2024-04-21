		jmp L2
L1:
		add r1, 1
    jmp  L4
		add r1, 1		; skipped

L2: 
		mov r2, 2
		jmp L1

L3:
		mov r3, 3		; skipped

L4: 
		mov r4, 4
    jmp L5

L5:
L6:
L7:
   mov r5, 5
L8:
L9:

; register view: 1,2,0,4,5

; I put extra labels for fun. I thought not having a nop would crash it if I ;jumped to a label like that

; labels can be called anything but currently I don't have a string library
; so I am using arrays of size 5. So you could do stuff like "here" or "main" 
; if you want to. Best just use L<number> and comment their purposes until I 
; make a string library

; todo
; make a std library
; allow including other files
