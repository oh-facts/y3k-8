<!--
	
//
4/21 scratch
ok here is the plan.

binary conversions will happen inside the assembler
but the instruction types (RR, RV, etc.) will still happen in the parser.

based on the next token, it will do a different thing


this plan utterly flopped because i would have to keep track of a lot of tokens

i thinks it better to have an X XX XXX instruction types

then my assemlber can check the token type and just convert it to whatever.

we are doing it this way for the sole purpose to 


i think i am overcomplicating this


case mov

if(next tokens are register and register)
binary = movr

something like this

but do i store the binary here? I think I will do that inside the assembler.

I can also do this other thing where I encode some extra bytes that tell which
path to go down.

if(tk_mov)
{
  encode mov_code
 
  while(arguments)
  {
  	if(next token is register)
  	{
    	encode register_type
  	  encode register_code
    }
  	.....
  }
  
}



---------
I am being stupid. I should try adding some instructions and see how much harder it is
------------

------------
all I need to do is this

1. change token type to use mov, add

2. check what the parameters are.

if they are reg, reg

make an rr node

if they are reg, val

make an rv node

for now, do the binary conversion inside parser.

this is a good pass.

we can(will) change it after we get this working

one thing that comes to mind is

1. have mods be separate 8 bits (to make converting easier)
2. then my instructions would look saner too

 MOV    RV    r2    5

0x01  0x02  0x02  0x05
	
this is so much saner, I am going to start with this.

MOVR    r2    r3
0x01  0x02  0x03

MOVV    r2    r3
0x02  0x02  0x03

-----------

i did the above essentially. i need to add one more modifier - vv

then I will clean up code and add a stack.

then i will add some more modifiers

PP RP PR PP PV ...

RPVG
(reg, pointer, value, global)

4*4

I will lose my m if i have to maintain like that.

i think i should try and encode type after every arg??

i will get to that when i get to that

ok i covered vr and vv

now i will work on refactor
then i will work on a stack + mem addresses


add rbp, [ ] and a starting address for the stack

i need to study and woo cloé so I am not writing code anymore

//



So I don't forget later - 

Immediate
2. Fix max tokens limit

Long term
1. simd instructions. These will be part of special instructions and will use special registers
2. movv r1 69*23-31*19. Be able to do calculations like these at compile time. ofc if its too big to fit in u8, it will overflow.
3. register pairs so you can do upto u16

// Writing this here for a different project or will forget
v3 . v3 : v3_dot_v3

v3 * v3 : v3_mul_v3

v3 X v3 : v3_cross_v3

v3 * lit  : v3_mul_f32
			v3_num_lit

#define GenerateMath(expr)

v3 a = {1,2,3};
v3 b = {8,2,9};

GenerateMath(
a * b;

a + b;
)

./metaprogram

v3 a = {1,2,3};
v3 b = {8,2,9};
v3 c = {2,0,-2};

GenerateMath(v3 d = a * b + c / 3)

// Generated code >>>>
v3 d;
{
	v3 temp  = v3_mul_v3(a,b);
	v3 temp2 = v3_div_f32(c,3);
	d = v3_add_v3(temp,temp2);
}
// <<<< Generated code
-->