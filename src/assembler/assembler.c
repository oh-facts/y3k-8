// lexer, then parser, then assembler

// todo(facts): Stick to some coding convention (not doing)

u8* assemble(struct parser* parser, struct Arena* arena)
{
  u8* bin = push_array(arena, u8, 100);
  u32 bindex = 0;
  
  struct Node* node = parser->first;
  node = node->next;
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
        bin[80] = bindex; 
      }break;
      
      case NODE_INSTR_L:
      {
        bin[bindex++] = node->instr_node_l.opcode->op_node.type;
        bin[bindex++] = bin[80];
      }break;
      case NODE_INSTR_LL:
      {
        bin[bindex++] = node->instr_node_ll.opcode->op_node.type;
        bin[bindex++] = bin[80];
        bin[bindex] = node->instr_node_ll.lit->lit_node.num;
      }break;
      default:
      {
        INVALID_CODE_PATH();
      }
    }
    
    node = node->next;
    
  }   
  
  return bin;
  
}