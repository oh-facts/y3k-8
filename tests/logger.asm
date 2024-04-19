; initialize logger
    movv r5, 1     ; device type
    movv r6, 0     ; device mode
    use  r5, r6    ; (device, input)

; 

    movv r1, 0      ; r1 = 0
L1:
    addv r1, 1      ; r1 += 1
    use  r5, r1     ; use (device, input)
    jmpx L1, 3      ; (like a for loop that loops 3 times)
    
    ;  haven't added comparisons, so this will have to do it like this
    ;  jmpx has since been removed since i have added comparisions. i need to 
    ;  update this example