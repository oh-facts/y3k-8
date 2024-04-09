// lexer, then parser, then assembler

// IdEAA PHATTEE: When parsing tokens, if something is a string, I can just check the next token and based on that go back and change the previous one.
// For labels, that works wonderfully. For instructions and parameters, I will have to think how I want it to work. (working on this)

// Store hashed lexemes alongside lexemes? (no)
// idea: Why don't I just store exact opcode or register as a token? (doing)
// todo(facts): Stick to some coding convention (not doing)
// make token nodes more useful. store tokens anyways, but also store other useful info
// Make an enum to string generator (doing)

#include "meta.h"

#define CHAR_TO_INT(c) ((c) - '0')

gen_string_from_enum
enum token_type
{
    tk_invalid,
    
    tk_r1,
    tk_r2,
    tk_r3,
    tk_r4,
    tk_r5,
    tk_r6,
    tk_r7,
    tk_r8,
    
    tk_movv,
    tk_movr,
    tk_addv,
    tk_addr,
    
    tk_iden,
    tk_lit,
    tk_comma,
    tk_colon,
    tk_terminate,
    tk_num
};

typedef enum token_type token_type;

#define token_type_op_offset (tk_movv - 1)
#define token_type_reg_offset (tk_r1 - 1)

global char* token_type_str[tk_num] = 
{
    "INVALID", "r1", "r2", "r3", "r4", "r5", "r6", "r7""REGISTER", "LITERAL", "COMMA", "TERMINATE"
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

internal inline b32 is_alpha(char a)
{
    return ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'));
}

internal void print_tokens(struct lexer* lexi)
{
    printn();
    printl("Lexer Output");
    printl("---------------");
    
    for(i32 i = 0; i < lexi->num_tokens; i ++)
    {
        printf("%d %s %s\n", i, token_type_str[lexi->tokens[i].type], lexi->tokens[i].lexeme);
    }
    
    printl("---------------");
    printn();
}

#include <string.h>

internal void lex_tokens(char* data, struct lexer* lexi, struct Arena* arena)
{
    //todo(facts): fix me
    const u32 max_tokens = 1024;
    
    lexi->tokens = push_array(arena, struct token, max_tokens);
    char* end = data;
    
    // Need a better name for this
#define new_token lexi->tokens[lexi->num_tokens] 
    
    char* current = &data[0];
    
    while(true)
    {
        
        switch(*current)
        {
            case ',':
            {
                new_token.type = tk_comma;
                new_token.lexeme[0] = ',';
                
                current ++; 
                lexi->num_tokens++;
                
            }break;
            case ':':
            {
                new_token.type = tk_colon;
                new_token.lexeme[0] = ':';
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
            case '\t':
            case '\n':
            case ' ':
            {
                
                current++;
            }break;
            case '\0':
            {
                goto exit;
            }break;
            default:
            {
                // if it starts with a number, its always a literal
                if(is_digit(*current))
                {
                    //ToDo(facts): hexadecimal support. check for 0x
                    new_token.type = tk_lit;
                    
                    char* peek = current;
                    i32 len = 0;
                    
                    while(true)
                    {
                        new_token.lexeme[len] = *peek;
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
                
                // either a keyword or an identifier
                else if(is_alpha(*current))
                {
                    char* peek = current;
                    u32 lexeme_len = 0;
                    
                    while(is_alpha(*peek) || is_digit(*peek))
                    {
                        new_token.lexeme[lexeme_len] = *peek; 
                        
                        lexeme_len++;
                        peek++;
                    }
                    
                    // is reg?
                    if(new_token.lexeme[0] == 'r' && is_digit(new_token.lexeme[1]))
                    {
                        i32 reg_num = CHAR_TO_INT(new_token.lexeme[1]);
                        new_token.type = reg_num + token_type_reg_offset;
                        goto found;
                    }
                    
                    // is opcode?
                    for(i32 i = movv; i <opcode_num; i ++)
                    {
                        if(strcmp(new_token.lexeme,opcode_str[i]) == 0)
                        {
                            new_token.type = token_type_op_offset + i;
                            goto found;
                        }
                    }
                    
                    // is identifier!
                    new_token.type = tk_iden;
                    
                    found:
                    lexi->num_tokens ++;
                    current += lexeme_len;
                    
                }
                else
                {
                    INVALID_CODE_PATH();
                }
                
            }break;
            
            
        }
    }
    
    exit:
    new_token.type = tk_terminate;
    lexi->num_tokens++;
    
    AssertM(lexi->num_tokens <= max_tokens, "too many tokens");
    
    print_tokens(lexi);
}

enum NODE_TYPE
{
    NODE_INVALID,
    
    // statements
    NODE_INSTR_RR,
    NODE_INSTR_RV,

    // types
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
    "invalid", "instruction_RR","instruction_RV" , "opcode" ,"literal", "register"
};

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

struct Node;

typedef struct InstrNode
{
    struct Node* opcode;
    struct Node* param1;
    struct Node* param2;
}InstrNodeRR, InstrNodeRV;

struct Node
{
    struct token token;
    struct Node* next;

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
    struct Node* memory;
    u32 num_nodes;

    struct Node* first;
    struct token* tokens;
};

// todo(facts): Maybe make an int offset that adds an offset when printing so they look
// better
/*
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
    
    for(i32 i = 0; i < parser->num_instr; i ++)
    {
        printl("Instruction %d",i);
        print_node(&parser->instr[i]);
    }
    printl("---------------");
    printn();
}
*/
internal struct Node*  make_lit_node(struct token* token, struct Arena* arena)
{
    struct Node* out  = push_struct(arena,struct Node);
    out->type = NODE_LITERAL;
    out->token = *token;
    out->lit_node.num = atoi(token->lexeme);
    return out;
}

internal struct Node*  make_reg_node(struct token* token, struct Arena* arena)
{
    struct Node* out  = push_struct(arena,struct Node);
    out->type = NODE_REGISTER;
    out->token = *token;
    out->reg_node.type = token->type - token_type_reg_offset;
    return out;
}

/*
    Write now the trees are purely made up of nodes or tokens.
    I normally represet literals and other symbols with primitives
    but I think I prefer them as tokens. Maybe I can have another
    step where I convert them to primitives from tokens? Or maybe that
    is a job for my assembler?
*/
internal void parse_tokens(struct parser* parser, struct lexer* lexi, struct Arena* arena)
{
    parser->memory = push_array(arena, struct Node, 1024);
    parser->first  = &parser->memory[0];
    struct token* _token = lexi->tokens;

    struct Node* curr = parser->first; 
    
    while(_token->type != tk_terminate)
    {
        switch (_token->type)
        {
            case tk_movv:
            case tk_addv:
            {

            }break;
            case tk_movr:
            case tk_addr:
            {

            }break;
            default:
            {
                _token++;
            }
        }

        curr = curr->next;
    }    
    
    //print_nodes(parser);
    
}

u8* assemble(struct parser* parser, struct Arena* arena)
{
    u8* bin = push_array(arena, u8, 100);
    u32 bindex = 0;
    
    struct Node* node = parser->first;
    while(node)
    {
       
        switch(node->type)
        {
            // How is this any better than movv addv, movr, addr? RV, RR makes no sense. worst idea.
            // opcode node, reg node.
        
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
            default:
            {
                INVALID_CODE_PATH();
            }
        }
        
        node = node->next;
        
    }   
    
    
    return bin;
    
}