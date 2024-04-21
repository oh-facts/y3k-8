#ifndef LANGUAGE_H
#define LANGUAGE_H

#define watch_your_mouth

gen_string_from_enum
enum keywords
{
  ke_inv,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,
  r8,
  
  mov,
  add,
  sub,
  mul,
  dave,
  
  jmp,
  jg,
  jl,
  je,
  
  cmp,
  icmp,
  
  use,
  
  kw_num,
};

// todo(you lazy fuck)
typedef enum keywords keyword;



#endif