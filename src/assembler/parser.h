

gen_string_from_enum
enum NODE_TYPE
{
  NODE_INVALID,
  
  // statements
  NODE_INSTR_RR,
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

struct parser
{
  struct Node* memory;
  u32 num_nodes;
  
  struct Node* first;
  struct token* tokens;
};