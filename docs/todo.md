<!--
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