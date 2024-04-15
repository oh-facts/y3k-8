struct assembler
{
    struct Arena arena;
    struct Arena scratch;
};

gen_string_from_enum
enum token_type 
{  
    tk_dummy,
    // registers
    tk_r1 = 1,
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
// make a str library to use arbitrarily sized strings
struct token
{
    token_type type;
    char lexeme[5];
};

gen_string_from_enum
enum NODE_TYPE
{   
    NODE_DUMMY,
    // statements
    NODE_INSTR_RR = 1,
    NODE_INSTR_RV,
    NODE_INSTR_L,
    NODE_INSTR_LL,
    NODE_LABEL_DECL,
    NODE_USE,

    // types
    NODE_OP,
    NODE_LITERAL,
    NODE_REGISTER,
    NODE_LABEL,
};

typedef enum NODE_TYPE NODE_TYPE;

struct OpNode
{
    opcode_type type;
};

struct LitNode
{
    u8 num;
};

struct RegNode
{
    register_type type;
};

struct LabelDeclNode
{
    u8 temp;
};

struct LabelNode
{
    struct Node* origin;
};

struct Node;

typedef struct InstrNode
{
    struct Node* opcode;
    struct Node* param1;
    struct Node* param2;
}InstrNodeRR, InstrNodeRV;

// todo(facts): I just realized I am using L for both literals and ints. Fix this.
struct InstrNodeL
{
    struct Node* opcode;
    struct Node* label;
};

struct InstrNodeLL
{
    struct Node* opcode;
    struct Node* label;
    struct Node* lit;
};

struct Node
{
    struct token token;
    struct Node* next;
    
    NODE_TYPE type;
    union
    {
        // statements
        struct InstrNode instr_node;
        struct InstrNodeL instr_node_l;
        struct InstrNodeLL instr_node_ll;
        struct LabelDeclNode label_decl_node;
        
        // types
        struct OpNode op_node;
        struct LitNode lit_node;
        struct RegNode reg_node;
        struct LabelNode label_node;
    };
};