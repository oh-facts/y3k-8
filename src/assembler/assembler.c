
// todo(facts): Stick to some coding convention (not doing)

struct defn
{
  u32 id[100];
  u32 addr[100];
  u32 num;
};

struct calls
{
  u8 dst[100];
  u8 src[100];
  u32 num;
};

u8* assemble(struct parser* parser, struct Arena* arena)
{
  u8* bin = push_array(arena, u8, 300);
  u32 bindex = 0;
  
  struct Node* node = parser->first;
  node = node->next;
  
  struct defn defn = {0};
  struct calls calls = {0};
  
  while(node)
  {
    
    switch(node->type)
    {
      case NODE_INSTR_XX:
      {
        bin[bindex++] = node->instr_node.opcode->op_node.type;  
        for(u32 i = 0; i < 2; i ++)
        {
          if(node->instr_node.types[i] == arg_v)
          {
            bin[bindex++] = arg_v;
            bin[bindex++] = node->instr_node.params[i]->lit_node.num;
          }
          else if(node->instr_node.types[i] == arg_r)
          {
            bin[bindex++] = arg_r;
            bin[bindex++] = node->instr_node.params[i]->reg_node.type;  
          }
          else
          {
            INVALID_CODE_PATH();
          }
          
        }
        
      }break;
      
      case NODE_LABEL_DECL:
      {
        defn.id[defn.num] = node->label_decl_node.id;
        defn.addr[defn.num] = bindex;
        defn.num++;
      }break;
      
      case NODE_INSTR_L:
      {
        bin[bindex++] = node->instr_node_l.opcode->op_node.type;
        
        calls.dst[calls.num] = node->instr_node_l.label->label_node.origin->label_decl_node.id;
        calls.src[calls.num] = bindex++;
        
        calls.num++;
      }break;
      
      default:
      {
        INVALID_CODE_PATH();
      }
    }
    
    node = node->next;
    
  }   
  
  // linking
  for(u32 i = 0; i < defn.num; i ++)
  {
    for(u32 j = 0; j < calls.num; j ++)
    {
      if(calls.dst[j] == defn.id[i])
      {
        bin[calls.src[j]] = defn.addr[i]; 
        
        // I added a break here before.
        // stupid move on my part. It stops from
        // multiple calls to the same defn
      }
    }
    
  }
  
  return bin;
  
}