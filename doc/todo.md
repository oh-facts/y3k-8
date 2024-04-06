<!--
So I don't forget later - 

Immediate
1. Parse numbers properly so I can do signed and unsigned math
2. Fix max tokens limit
3. atm file is compiled and then executes. Make commands like this - 
    ./app -c  "input" -o "output"
    ./app -r  "input"

Long term
1. simd instructions. These will be part of special instructions and will use special registers
2. movv r1 69*23-31*19. Be able to do calculations like these at compile time. ofc if its too big to fit in u8, it will overflow.
3. register pairs so you can do upto u16
-->