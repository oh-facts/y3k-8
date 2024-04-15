; DOES NOT WORK ATM.

L3:
    jmp L2

    movv r1, 0      ; r1 = 0
L1:
    addv r1, 1      ; r1 += 1
    use  r5, r1     ; use (device, input)
    jmpx L1, 3      ; (like a for loop that loops 3 times)
    jmp L4
    ;  haven't added comparisons, so this will have to do it like this


    ; initialize logger
L2:
    movv r5, 1     ; device type
    movv r6, 0     ; device mode
    use  r5, r6    ; (device, input)
    jmp L3

L4:
    movv r8, 3