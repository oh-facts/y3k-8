// todo(facts): Maybe make an int offset that adds an offset when printing so they look better

internal void print_node(struct Node* node)
{
  switch(node->type)
  {
    case NODE_INVALID:
    {
      printl("invalid node");
    }break;
    case NODE_INSTR_RR:
    case NODE_INSTR_RV:
    {
      print_node(node->instr_node.opcode);
      
      printf("Arg1:");
      print_node(node->instr_node.param1);
      
      printf("Arg2:");
      print_node(node->instr_node.param2);
      printn();
      
    }break;
    case NODE_OP:
    {
      printl("Opcode: %s", node->token.lexeme);
    }break;
    case NODE_REGISTER:
    {
      printl("Register %s", node->token.lexeme);
    }break;
    case NODE_LITERAL:
    {
      printl("Literal %s", node->token.lexeme);
    }break;
    case NODE_LABEL:
    {
      printl("Label %s", node->token.lexeme);
      printl("Label origin addr %p", node->label_node.origin);
      printl("Label origin id %d", node->label_node.origin->label_decl_node.id);
      
    }break;
    case NODE_INSTR_L:
    {
      print_node(node->instr_node_l.opcode);
      print_node(node->instr_node_l.label);
      printn();
    }break;
    case NODE_LABEL_DECL:
    {
      printl("Label Decl %s", node->token.lexeme);
      printl("Label addr %p", node);
      printl("Label id %d", node->label_decl_node.id);
      printn();
    }break;
    
    default:
    {
      INVALID_CODE_PATH();
    }
  }
}

internal void print_nodes(struct parser* parser)
{
  printn();
  printl("Parser Output");
  printl("---------------");
  
  struct Node* curr = parser->first;
  u32 count = 0;
  while(curr)
  {
    printl("Statement %d",count);
    print_node(curr);
    curr = curr->next;
    count ++;
  }
  printl("---------------");
  printn();
}

internal void resolve_labels(struct parser* parser)
{
  for(u32 i = 0; i < parser->num_label_decls; i ++)
  {
    struct Node* label_decl = parser->label_decls[i];
    for(u32 j = 0; j < parser->num_label_calls; j ++)
    {
      struct Node* label_call = parser->label_calls[j];
      if(strcmp(label_decl->token.lexeme, label_call->token.lexeme) == 0)
      {
        label_call->label_node.origin = label_decl; 
      }
    }
  }
}

internal struct Node *make_op_node(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_OP;
  out->token = *parser->tokens;
  
  //consume
  parser->tokens++;
  
  return out;
}

internal struct Node *make_lit_node(struct parser* parser, struct Arena* arena)
{
  struct Node* out  = push_struct(arena,struct Node);
  out->type = NODE_LITERAL;
  out->token = *parser->tokens;
  out->lit_node.num = atoi(parser->tokens->lexeme);
  
  //consume
  parser->tokens++;
  
  return out;
}

internal struct Node *make_reg_node(struct parser* parser, struct Arena* arena)
{
  struct Node* out  = push_struct(arena,struct Node);
  out->type = NODE_REGISTER;
  out->token = *parser->tokens;
  
  //consume
  parser->tokens++;
  
  return out;
}

internal struct Node *make_label_node(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_LABEL;
  out->token = *parser->tokens;
  
  // labels are resolved after all tokens are parsed
  //out->label_node.origin = 0;
  
  parser->label_calls[parser->num_label_calls++] = out;
  parser->tokens++;
  return out;
}

// Parsing Statements

internal struct Node *make_instr_rr(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_INSTR_RR;
  out->token = *parser->tokens;
  
  out->instr_node.opcode = make_op_node(parser, arena);
  
  out->instr_node.param1 = make_reg_node(parser, arena);
  
  // consume ","
  parser->tokens++;
  
  out->instr_node.param2 = make_reg_node(parser,arena);
  
  return out;
}

internal struct Node *make_instr_rv(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_INSTR_RV;
  out->token = *parser->tokens;
  
  out->instr_node.opcode = make_op_node(parser, arena);
  
  out->instr_node.param1 = make_reg_node(parser, arena);
  
  // consume ","
  parser->tokens++;
  
  out->instr_node.param2 = make_lit_node(parser,arena);
  
  return out;
}

internal struct Node *make_instr_l(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_INSTR_L;
  out->token = *parser->tokens;
  
  out->instr_node_l.opcode = make_op_node(parser, arena);
  
  out->instr_node_l.label = make_label_node(parser, arena);
  
  return out;
}

internal struct Node* make_label_decl_node(struct parser* parser, struct Arena* arena)
{
  struct Node* out = push_struct(arena, struct Node);
  out->type = NODE_LABEL_DECL;
  out->token = *parser->tokens;
  out->label_decl_node.id = parser->num_label_decls;
  
  parser->label_decls[parser->num_label_decls] = out;
  
  parser->num_label_decls ++;
  
  // self and colon
  parser->tokens +=2;
  return out;
}

internal void parse_tokens(struct parser* parser, struct lexer* lexi, struct Arena* arena)
{
  parser->memory = push_array(arena, struct Node, 1024);
  parser->label_decls = push_array(arena, struct Node*, 1024);
  parser->label_calls = push_array(arena, struct Node*, 1024);
  
  parser->first  = &parser->memory[0];
  parser->tokens = lexi->tokens;
  
  struct Node* curr = parser->first; 
  while(parser->tokens->type != tk_terminate)
  {
    switch (parser->tokens->type)
    {
      case tk_movv:
      case tk_addv:
      {
        curr->next = make_instr_rv(parser,arena);
      }break;
      
      case tk_movr:
      case tk_addr:
      case tk_use:
      case tk_cmp:
      case tk_icmp:
      {
        curr->next = make_instr_rr(parser,arena);
      }break;
      
      case tk_jmp:
      case tk_jg:
      case tk_jl:
      case tk_je:
      {
        curr->next = make_instr_l(parser, arena);
      }break;
      case tk_iden:
      {
        // label decl
        if((parser->tokens + 1)->type == tk_colon)
        {
          curr->next = make_label_decl_node(parser,arena);
        }
        else
        {
          INVALID_CODE_PATH();
        }
      }break;
      default:
      {
        INVALID_CODE_PATH();
      }
    }
    
    curr = curr->next;
  }    
  
  resolve_labels(parser);
  print_nodes(parser);
}
