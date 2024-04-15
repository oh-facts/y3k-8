#define BIN_MAX_SIZE 1000

// todo(facts): make a memory layout.

u8* assemble(struct Node* node, struct assembler* ass)
{
    u8* bin = push_array(&ass->arena, u8, BIN_MAX_SIZE);
    u32 bindex = 0;
    
    node = node->next;

    u32 labels[10] = {0};

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
                labels[node->label_decl_node.id] = bindex;
            }break;

            case NODE_INSTR_L:
            {
                bin[bindex++] = node->instr_node_l.opcode->op_node.type;
                bin[bindex++] = labels[node->instr_node_l.label->label_node.origin->label_decl_node.id];
            }break;
            case NODE_INSTR_LL:
            {
                bin[bindex++] = node->instr_node_ll.opcode->op_node.type;
                bin[bindex++] = labels[node->instr_node_l.label->label_node.origin->label_decl_node.id];
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

void assembler_run(struct platform* pf, i32 argc, char* argv[])
{
    AssertM(argc == 3, "Usage: ./out \"input filename\" \"output filename\" ");
    
    printl("Input : %s\n",argv[1]);
    printl("Output: %s\n",argv[2]);
    
    struct assembler assembler = {0};
    arena_innit(&assembler.arena, pf->mem_size, pf->memory);
    arena_innit(&assembler.scratch, pf->scratch_size,pf->scratch);
    
    char* data =  pf->read_text_file(argv[1],&assembler.arena);
    
    struct token* tokens = lex_tokens(data, &assembler);
    
    struct Node* nodes = parse_tokens(tokens, &assembler);
    
    u8* bin = assemble(nodes, &assembler);
    
    if(!pf->write_bin_file(argv[2], bin, BIN_MAX_SIZE))
    {
        printf("Failed to output binary %s", argv[2]);
    }
}