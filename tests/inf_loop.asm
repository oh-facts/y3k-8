; logger stuff
    movv r5, 1     ; device type

; 

    movv r1, 0      ; r1 = 0
L1:
    addv r1, 1      ; r1 += 1
    use  r5, r1     ; use (device, input)
    jmp  L1         ; 
    
    ;  haven't added comparisons, so this will have to do it like this