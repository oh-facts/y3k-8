; cmp is for unsigned comparision
; icmp is for signed

; imagine these were variables
movv r3, 1     ; char logger
movv r4, 2     ; 2 for int, 3 for uint (logger)
    
movv r5, 60    ; '<'
movv r6, 61    ; '='
movv r7, 62    ; '>'
    
movv r8, 32    ; ' '
 
movv r1, -25	 ; the numbers we are comparing
movv r2, 23   

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