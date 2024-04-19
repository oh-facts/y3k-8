#ifndef LEXER_H
#define LEXER_H

// todo(facts): generate the op/reg in token type using language.h

gen_string_from_enum
enum token_type 
{
  tk_invalid,
  
  // registers
  tk_r1,
  tk_r2,
  tk_r3,
  tk_r4,
  tk_r5,
  tk_r6,
  tk_r7,
  tk_r8,
  
  // op
  tk_movv,
  tk_movr,
  tk_addv,
  tk_addr,
  tk_jmp,
  tk_use,
  tk_cmp,
  tk_jg,
  tk_jl,
  tk_je,
  
  
  tk_iden,
  tk_lit,
  
  // punctuators
  tk_comma,
  tk_colon,
  
  // misc
  tk_terminate,
  tk_num
};

typedef enum token_type token_type;

// todo(facts): store row# and col#
struct token
{
  token_type type;
  char lexeme[5];
};

struct lexer
{
  struct token* tokens;
  u32 num_tokens;
};

#endif