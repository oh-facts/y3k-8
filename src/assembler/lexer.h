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
    tk_jmpx,
    tk_use,
    
    // keywords
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

#define token_type_op_offset (tk_movv - 1)
#define token_type_reg_offset (tk_r1 - 1)


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