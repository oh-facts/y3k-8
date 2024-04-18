#ifndef LANGUAGE_H
#define LANGUAGE_H

// todo(facts): Make a language enum that holds everything relevant to the language
// you can put that inside assembler
// make a computer.h that holds computer related stuff
// the assemlber can have a backends/fcpu that holds translations to relevant addresses

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
  
  nop,
  movv,
  movr,
  addv,
  addr,
  jmp,
  use,
  cmp,
  kw_num,
};

// todo(you lazy fuck)
typedef enum keywords keyword;



#endif