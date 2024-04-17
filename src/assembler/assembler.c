
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
  u8* bin = push_array(arena, u8, 100);
  u32 bindex = 0;
  
  struct Node* node = parser->first;
  node = node->next;
  
  struct defn defn = {0};
  struct calls calls = {0};
  
  while(node)
  {
    
    switch(node->type)
    {
      case NODE_INSTR_RV:
      {
        bin[bindex++] = node->instr_node.opcode->op_node.type;  
        
        bin[bindex++] = node->instr_node.param1->reg_node.type;  
        
        bin[bindex++] = node->instr_node.param2->lit_node.num;
        
      }break;
      
      case NODE_INSTR_RR:
      {
        bin[bindex++] = node->instr_node.opcode->op_node.type;  
        
        bin[bindex++] = node->instr_node.param1->reg_node.type;  
        
        bin[bindex++] = node->instr_node.param2->reg_node.type;
        
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
        break;
      }
    }
    
  }
  
  return bin;
  
}