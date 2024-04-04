
// lexer, then parser, then assembler
#include <language.h>

#define CHAR_TO_INT(c) ((c) - '0')

enum token_type
{
    tk_invalid,
    tk_op,
    tk_reg,
    tk_lit,
    tk_terminate,
    tk_num
};

typedef enum token_type token_type;

global char* token_type_str[tk_num] = 
{
    "INVALID", "OP","REGISTER", "LITERAL"
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

#include <math.h>
#include <ctype.h>

void print_tokens(struct lexer* lexi)
{
    for(i32 i = 0; i < lexi->num_tokens; i ++)
    {
        printf("%d %s %s\n", i, token_type_str[lexi->tokens[i].type], lexi->tokens[i].lexeme);
    }
}

void lex_tokens(char* data, struct lexer* lexi, struct Arena* arena)
{
    char* current = &data[0];

    struct token* tokens = push_array(arena, struct token, 10);
    u32 num_tokens = 0;

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
                    tokens[num_tokens].lexeme[i] = *peek; 
                    peek++;
                }

                tokens[num_tokens].type = tk_op;  
                current += 4;                 
                
                num_tokens ++;
            }break;
            case 'r':
            {
                tokens[num_tokens].type = tk_reg;
                tokens[num_tokens].lexeme[0] = 'r';

                char* peek = current + 1;
                tokens[num_tokens].lexeme[1] = *peek;

                current +=2; 
                num_tokens++;
            }break;
            // fall through
            case '\n':
            case ' ':
            {

                current++;
            }break;

            default:
            {
                if(isdigit(*current))
                {
                    //ToDo(facts): hexadecimal support. check for 0x
                    tokens[num_tokens].type = tk_lit;
                    
                    char* peek = current;
                    i32 len = 0;

                    while(true)
                    {
                        tokens[num_tokens].lexeme[len] = *peek;
                        len ++;

                        if(!isdigit(*(++peek)))
                        {
                            break;
                        }
                    }
                    num_tokens++;
                    
                    
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
    tokens[num_tokens].type = tk_terminate;
    num_tokens++;

    lexi->tokens = tokens;
    lexi->num_tokens = num_tokens;

    //print_tokens(lexi);
}

enum NODE_TYPE
{
    NODE_INVALID,
    NODE_INSTR,
    NODE_LITERAL,
    NODE_REGISTER,
};

typedef enum NODE_TYPE NODE_TYPE;

global const char* node_type_str[] = 
{
    "invalid", "instruction", "literal", "register"
};

struct Node;

struct InstrNode
{
    struct token opcode;
    struct Node* param1;
    struct Node* param2;
};

struct Node
{
    NODE_TYPE type;
    union
    {
        struct InstrNode instrNode;
        u8 literal;
        struct token reg;
    };
};

struct parser
{
    struct Node nodes[20];
    i32 num_nodes;
};

void print_node(struct Node* node)
{
    switch(node->type)
    {
        case NODE_INVALID:
        {
            printl("invalid node");
        }break;
        case NODE_INSTR:
        {

            printl("Opcode: %s %s", token_type_str[node->instrNode.opcode.type], 
            node->instrNode.opcode.lexeme);

            printf("Arg1:");
            print_node(node->instrNode.param1);

            printf("Arg2:");
            print_node(node->instrNode.param2);
            printf("\n");

        }break;
        case NODE_REGISTER:
        {
            printl("%s", node->reg.lexeme);
        }break;
        case NODE_LITERAL:
        {
            printl("%d", node->literal);
        }break;

        default:
        {
            printl("ooga booga why is control here");
        }
    }
}

void print_nodes(struct parser* parser)
{
    for(i32 i = 0; i < parser->num_nodes; i ++)
    {
        print_node(&parser->nodes[i]);
    }
}

void parse_tokens(struct parser* parser, struct lexer* lexi)
{

    struct Node nodes[20];
    u32 num_nodes = 0;
    struct token* _token = lexi->tokens;
    
    while(true)
    {
        switch (_token->type)
        {
            //todo(facts): op have variable args.
            case tk_op:
            {
                struct Node* instr = &parser->nodes[num_nodes];
                instr->type = NODE_INSTR;
                instr->instrNode.opcode = *_token; 
                _token++;
                num_nodes ++;
       
                struct Node* param1 = &parser->nodes[num_nodes];
                param1->type = NODE_REGISTER;
                param1->reg = *_token;
                
                instr->instrNode.param1 = param1;
                _token++;
                num_nodes++;

                struct Node *param2 = &parser->nodes[num_nodes];
                param2->type = NODE_LITERAL;
                param2->literal = atoi(_token->lexeme);

                instr->instrNode.param2 = param2;
                _token++;
                num_nodes++;
              
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
    parser->num_nodes = num_nodes;

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
   
    //ass->bin = 
}