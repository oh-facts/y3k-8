; logger stuff
    movv r5, 1     ; char code
    movv r6, 3     ; uint code
    movv r7, 10    ; new line
; 

    movv r1, 0      ; r1 = 0
L1:
    addv r1, 1      ; r1 += 1
    use  r6, r1     ;
    use  r5, r7     ;
    jmp  L1         ; 
    
    ;  haven't added comparisons, so this will have to do it like this