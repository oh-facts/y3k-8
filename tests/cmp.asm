; cmp is for unsigned comparision
; icmp is for signed

; imagine these were variables
mov r3, 1     ; char logger
mov r4, 2     ; 2 for int, 3 for uint (logger)
    
mov r5, 60    ; '<'
mov r6, 61    ; '='
mov r7, 62    ; '>'
    
mov r8, 32    ; ' '
 
mov r1, 25	 ; the numbers we are comparing
mov r2, -29   

use r4, r1
use r3, r8

icmp r1, r2
jl less

icmp r1, r2
jg more

use r3, r6
jmp end

less:
use r3, r5    ; print '<'
jmp end

more:
use r3, r7

end:
use r3, r8    ; print '\n'
use r4, r2