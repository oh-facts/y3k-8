# Instruction set v0.2.0

| op   | does             |
| ---- | ---------------- |
| movv | R  = V           |
| movr | R  = R           |
| addv | R  = R + V       |
| addr | R  = R + R       |
| jmp  | IP = L           |
| use  | check devices    |
| cmp  | sets S/Z/C to 1  |
| icmp | sets S/Z/C to 1  |
| jg   | if(C) { IP = L } |
| jl   | if(S) { IP = L } |
| je   | if(Z) { IP = L } |

R:  Register (r1 - r8)
V:  value    (8 bit literal)
L:  Label
IP: instruction pointer
S:  Sign flag
Z:  Zero flag
C:  Carry flag

8 general purpose registers : r1 - r8
Labels starts with a character
numbers need to be in the decimal system

## devices

Very unsure about the api. Will change. Atm, there "are" two loggers.

`use a, b`

 - a: Register 
	 - print codes: 
		 - char : 1 
		 - i8   : 2 
		 - u8   : 3
 - b: Register 
	 - Prints whatever value is inside it.