// todo(facts): Maybe make an int offset that adds an offset when printing so they look
// better

internal void print_node(struct Node* node)
{
    switch(node->type)
    {

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
        }break;
        case NODE_INSTR_L:
        {
            print_node(node->instr_node_l.opcode);
            print_node(node->instr_node_l.label);
            printn();
        }break;
        case NODE_INSTR_LL:
        {

        }break;
        case NODE_LABEL_DECL:
        {
            printl("Label Decl %s",node->token.lexeme);
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
    
    // first node is header
    struct Node* curr = parser->first->next;
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

/*
    Iterates through nodes and returns parent label
*/
internal struct Node* get_origin_label_decl_node(struct parser* parser, struct Node* node)
{
    struct Node* curr = parser->first;
    while(curr)
    {
        if(curr->type == NODE_LABEL_DECL)
        {
            if(strcmp(curr->token.lexeme, node->token.lexeme) == 0)
            {
                return curr;
            }
        }
        curr = curr->next;
    }

    // Assert
    return 0;
}

internal struct Node* make_op_node(struct parser* parser, struct Arena* arena)
{
    struct Node* out = push_struct(arena, struct Node);
    out->type = NODE_OP;
    out->token = *parser->tokens;
    out->op_node.type = parser->tokens->type - token_type_op_offset;
    
    //consume
    parser->tokens++;
    
    return out;
}

internal struct Node*  make_lit_node(struct parser* parser, struct Arena* arena)
{
    struct Node* out  = push_struct(arena,struct Node);
    out->type = NODE_LITERAL;
    out->token = *parser->tokens;
    out->lit_node.num = atoi(parser->tokens->lexeme);
    
    //consume
    parser->tokens++;
    
    return out;
}

internal struct Node*  make_reg_node(struct parser* parser, struct Arena* arena)
{
    struct Node* out  = push_struct(arena,struct Node);
    out->type = NODE_REGISTER;
    out->token = *parser->tokens;
    out->reg_node.type = parser->tokens->type - token_type_reg_offset;
    
    //consume
    parser->tokens++;
    
    return out;
}

internal struct Node* make_label_node(struct parser* parser, struct Arena* arena)
{
    struct Node* out = push_struct(arena, struct Node);
    out->type = NODE_LABEL;
    out->token = *parser->tokens;
    out->label_node.origin = get_origin_label_decl_node(parser, out);
    parser->tokens++;
    return out;
}

// Parsing Statements

internal struct Node* make_instr_rr(struct parser* parser, struct Arena* arena)
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

internal struct Node* make_instr_rv(struct parser* parser, struct Arena* arena)
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

internal struct Node* make_instr_l(struct parser* parser, struct Arena* arena)
{
    struct Node* out = push_struct(arena, struct Node);
    out->type = NODE_INSTR_L;
    out->token = *parser->tokens;
    
    out->instr_node_l.opcode = make_op_node(parser, arena);
    
    out->instr_node_l.label = make_label_node(parser, arena);
    
    return out;
}

internal struct Node* make_instr_ll(struct parser* parser, struct Arena* arena)
{
    struct Node* out = push_struct(arena, struct Node);
    out->type = NODE_INSTR_LL;
    out->token = *parser->tokens;

    out->instr_node_ll.opcode = make_op_node(parser, arena);
    out->instr_node_ll.label = make_label_node(parser, arena);

    parser->tokens++;

    out->instr_node_ll.lit = make_lit_node(parser, arena);

    return out;
}

internal struct Node* make_label_decl_node(struct parser* parser, struct Arena* arena)
{
    struct Node* out = push_struct(arena, struct Node);
    out->type = NODE_LABEL_DECL;
    out->token = *parser->tokens;
    out->label_decl_node.temp = 1;

    // self and colon
    parser->tokens +=2;
    return out;
}

internal void parse_tokens(struct parser* parser, struct lexer* lexi, struct Arena* arena)
{
    parser->memory = push_array(arena, struct Node, 1024);
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
            {
                curr->next = make_instr_rr(parser,arena);
            }break;
            case tk_jmpx:
            {
                curr->next = make_instr_ll(parser, arena);
            }break;
            case tk_jmp:
            {
                curr->next = make_instr_l(parser, arena);
            }break;
            case tk_iden:
            {
                if((parser->tokens + 1)->type == tk_colon)
                {
                    curr->next = make_label_decl_node(parser,arena);
                }
            }break;
            default:
            {
                INVALID_CODE_PATH();
            }
        }
        
        curr = curr->next;
    }    
    
    print_nodes(parser);
    
}
