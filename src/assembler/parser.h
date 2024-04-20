#ifndef PARSER_H
#define PARSER_H

gen_string_from_enum
enum NODE_TYPE
{
  NODE_INVALID,
  
  // statements
  NODE_INSTR_XX,
  NODE_INSTR_L,
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
  i32 temp;
};

struct LitNode
{
  u8 num;
};

struct RegNode
{
  i32 temp;
};

struct LabelDeclNode
{
  u8 id;
};

struct LabelNode
{
  struct Node* origin;
};

struct Node;

struct InstrNode
{
  struct Node* opcode;
  struct Node* param1;
  struct Node* param2;
};

// todo(facts): I just realized I am using L for both literals and ints. Fix this.
struct InstrNodeL
{
  struct Node* opcode;
  struct Node* label;
};

struct Node
{
  struct token token;
  struct Node *next;
  
  NODE_TYPE type;
  union
  {
    // statements
    struct InstrNode instr_node;
    struct InstrNodeL instr_node_l;
    struct LabelDeclNode label_decl_node;
    
    // types
    struct OpNode op_node;
    struct LitNode lit_node;
    struct RegNode reg_node;
    struct LabelNode label_node;
  };
};

struct parser
{
  struct token *tokens;
  
  struct Node *memory;
  
  struct Node *first;
  u32 num_nodes;
  
  struct Node **label_decls;
  u32 num_label_decls;
  
  struct Node **label_calls;
  u32 num_label_calls;
};

#endif