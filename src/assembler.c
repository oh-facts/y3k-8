
// lexer, then parser, then assembler
// todo(facts): Stick to some coding convention
#define CHAR_TO_INT(c) ((c) - '0')

enum token_type
{
    tk_invalid,
    tk_op,
    tk_reg,
    tk_lit,
    tk_comma,
    tk_terminate,
    tk_num
};

typedef enum token_type token_type;

global char* token_type_str[tk_num] = 
{
    "INVALID", "OP","REGISTER", "LITERAL", "COMMA", "TERMINATE"
};

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

internal inline b32 is_digit(char a)
{
    return (a >= '0' && a <= '9');
}

internal void print_tokens(struct lexer* lexi)
{
    printn();
    for(i32 i = 0; i < lexi->num_tokens; i ++)
    {
        printf("%d %s %s\n", i, token_type_str[lexi->tokens[i].type], lexi->tokens[i].lexeme);
    }
    ;
    printn();
}



internal void lex_tokens(char* data, struct lexer* lexi, struct Arena* arena)
{
    const u32 max_tokens = 20;

    lexi->tokens = push_array(arena, struct token, max_tokens);

    // Need a better name for this
    #define new_token(lexer) (lexer->tokens[lexer->num_tokens])

    char* current = &data[0];
    
    while(true)
    {
        
        switch(*current)
        {
            // add<x>, mov<x>
            // i want to get the assembler up and running, so I won't be doing
            // much validation. If your opcode starts with the same letter as 
            // something that already exists, its valid. If its bigger or smaller
            // than 4 letters, severe problems can happen. That is for future me
            // to care about.
            case 'a':
            case 'm':
            {
                // >:) I know that my opcodes are 4 characters at best
                char* peek = current;
                for(i32 i = 0; i < 4; i ++)
                {
                    new_token(lexi).lexeme[i] = *peek; 
                    peek++;
                }

                new_token(lexi).type = tk_op;  
                current += 4;                 
                
                lexi->num_tokens ++;
            }break;
            case 'r':
            {
                new_token(lexi).type = tk_reg;
                new_token(lexi).lexeme[0] = 'r';

                char* peek = current + 1;
                new_token(lexi).lexeme[1] = *peek;

                current +=2; 
                lexi->num_tokens++;
            }break;
            case ',':
            {
                new_token(lexi).type = tk_comma;
                new_token(lexi).lexeme[0] = ',';

                current ++; 
                lexi->num_tokens++;

            }break;
            
            // skip comments until it finds a new line
            case ';':
            {
                while(*(++current) != '\n')
                {
                    //printf("%c",*current);
                    // :)
                }
            }break;

            // fall through
            case '\n':
            case ' ':
            {

                current++;
            }break;

            default:
            {
                if(is_digit(*current))
                {
                    //ToDo(facts): hexadecimal support. check for 0x
                    new_token(lexi).type = tk_lit;
                    
                    char* peek = current;
                    i32 len = 0;

                    while(true)
                    {
                        new_token(lexi).lexeme[len] = *peek;
                        len ++;

                        if(!is_digit(*(++peek)))
                        {
                            break;
                        }
                    }
                    lexi->num_tokens++;
                    
                    
                    //printf("%d\n",num);
                    current += len;
                }
                else
                {
                    goto exit;
                }

            }break;
            
            
        }
    }

    exit:
    new_token(lexi).type = tk_terminate;
    lexi->num_tokens++;

    AssertM(lexi->num_tokens <= max_tokens, "too many tokens");

    //print_tokens(lexi);
}

enum NODE_TYPE
{
    NODE_INVALID,
    NODE_INSTR,
    NODE_OP,
    NODE_LITERAL,
    NODE_REGISTER,
};

typedef enum NODE_TYPE NODE_TYPE;

// Note(facts): I am not using this anywhere currently. I will only use this
// for debug purposes. Its a pain to maintain these. I must phase these out.
// or generate them programatically. A switch case would be neater but these
// are elegant to look at. Maybe I will generate them at some point.
global const char* node_type_str[] = 
{
    "invalid", "instruction", "opcode" ,"literal", "register"
};

struct OpNode
{
    struct token token;
};

struct LitNode
{
    struct token token;
};

struct RegNode
{
    struct token token;
};

struct Node;

struct InstrNode
{
    struct Node* opcode;
    struct Node* param1;
    struct Node* param2;
};

struct Node
{
    NODE_TYPE type;
    union
    {
        struct InstrNode instr_node;
        struct OpNode op_node;
        struct LitNode lit_node;
        struct RegNode reg_node;
    };
};

struct parser
{
    // for now my asm is just a set of instructions
    struct Node* instr;
    i32 num_instr;
};

// todo(facts): Maybe make an int offset that adds an offset when printing so they look
// better
internal void print_node(struct Node* node)
{
    switch(node->type)
    {
        case NODE_INVALID:
        {
            printl("invalid node");
        }break;
        case NODE_INSTR:
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
            printl("Opcode: %s", node->op_node.token.lexeme);
        }break;
        case NODE_REGISTER:
        {
            printl("Register %s", node->reg_node.token.lexeme);
        }break;
        case NODE_LITERAL:
        {
            printl("Literal %s", node->lit_node.token.lexeme);
        }break;

        default:
        {
            printl("ooga booga why is control here");
        }
    }
}

internal void print_nodes(struct parser* parser)
{
    printn();
    for(i32 i = 0; i < parser->num_instr; i ++)
    {
        printl("Instruction %d",i);
        print_node(&parser->instr[i]);
    }
    printn();
}

internal void parse_param_token(struct Node* param, const struct token* token)
{
    if(token->type == tk_lit)
    {
        param->type = NODE_LITERAL;
        param->lit_node.token = *token;
    }
    else if(token->type == tk_reg)
    {
        param->type = NODE_REGISTER;
        param->reg_node.token = *token;
    }
    else
    {
        AssertM(3>4,"control shouldn't come here");
    }
}

internal void parse_tokens(struct parser* parser, struct lexer* lexi, struct Arena* arena)
{
    u32 num_nodes = 0;
    struct token* _token = lexi->tokens;
    
    parser->instr = push_array(arena, struct Node, 20);
    parser->num_instr = 0;

    while(true)
    {
        switch (_token->type)
        {
            //todo(facts):
            case tk_op:
            {
                struct Node* instr = &parser->instr[parser->num_instr];
                instr->type = NODE_INSTR;
                // Note(facts): Unsure about this. Should I just make
                // my opcode node an OpNode or leave it as a generic Node*
                instr->instr_node.opcode = push_struct(arena,struct Node);
                instr->instr_node.opcode->op_node.token = *_token; 
                instr->instr_node.opcode->type = NODE_OP;
                _token++;
                parser->num_instr++;
            
                struct Node* param1 = push_struct(arena,struct Node);
                parse_param_token(param1,_token);
                instr->instr_node.param1 = param1;
                _token++;            

                if(_token->type == tk_comma)
                {
                    // after comma
                    _token++;       

                    // I am not writing a function to save 2 loc
                    struct Node* param2 = push_struct(arena,struct Node);
                    parse_param_token(param2,_token);
                    instr->instr_node.param2 = param2;
                    _token++;                     
                }
                    
                print_node(instr);
              
            }break;
            case tk_terminate:
            {
                goto exit;
            }break;
            default:
            {
                _token++;
            }
        }
    }

    exit:

    print_nodes(parser);

    printl("bai bai");
}

struct assembler
{
    i32 temp;
    u8 bin[100];
};

void assemble()
{
    volatile int i = 0;
    volatile int a = 0;
    //ass->bin = 
}