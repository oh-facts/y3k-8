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
    
    tk_label,
    
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
                    
                    // anything starting with r is reserved for registers
                    switch(new_token.lexeme[0])
                    {
                        case 'r':
                        {
                            if(is_digit(new_token.lexeme[1]))
                            {
                                i32 reg_num = CHAR_TO_INT(new_token.lexeme[1]);
                                new_token.type = reg_num + token_type_reg_offset;
                            }
                            else
                            {
                                INVALID_CODE_PATH();
                            }
                            
                        }break;
                        
                    }
                    
                    for(i32 i = movv; i <opcode_num; i ++)
                    {
                        if(strcmp(new_token.lexeme,opcode_str[i]) == 0)
                        {
                            new_token.type = token_type_op_offset + i;
                            break;
                        }
                    }
                    
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
    NODE_INSTR_RR,
    NODE_INSTR_RV,
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

typedef struct InstrNode
{
    struct Node* opcode;
    struct Node* param1;
    struct Node* param2;
}InstrNodeRR, InstrNodeRV;

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

internal void parse_param_token(struct Node* param, const struct token* token)
{
    if(token->type == tk_lit)
    {
        param->type = NODE_LITERAL;
        param->lit_node.token = *token;
    }
    else if(token->type >= tk_r1 && token->type <=tk_r8)
    {
        param->type = NODE_REGISTER;
        param->reg_node.token = *token;
    }
    else
    {
        INVALID_CODE_PATH();
    }
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
    struct token* _token = lexi->tokens;
    
    parser->instr = push_array(arena, struct Node, 1024);
    parser->num_instr = 0;
    
    while(true)
    {
        switch (_token->type)
        {
            //todo(facts):
            case tk_addv:
            case tk_movv:
            {
                struct Node* instr = &parser->instr[parser->num_instr];
                instr->type = NODE_INSTR_RV;
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
                
                if(_token->type != tk_comma)
                {
                    printf("%s expects two arguments. One received", _token->lexeme);
                }
                _token++;
                
                struct Node* param2 = push_struct(arena,struct Node);
                parse_param_token(param2,_token);
                instr->instr_node.param2 = param2;
                _token++;                     
            }break;
            case tk_addr:
            case tk_movr:
            {
                struct Node* instr = &parser->instr[parser->num_instr];
                instr->type = NODE_INSTR_RR;
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
                
                if(_token->type != tk_comma)
                {
                    printf("%s expects two arguments. One received", _token->lexeme);
                }
                _token++;
                
                struct Node* param2 = push_struct(arena,struct Node);
                parse_param_token(param2,_token);
                instr->instr_node.param2 = param2;
                _token++;   
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
    
}

u8* assemble(struct parser* parser, struct Arena* arena)
{
    u8* bin = push_array(arena, u8, 100);
    u32 bindex = 0;
    
    
    
    for(i32 i = 0; i < parser->num_instr; i ++)
    {
        struct Node* instr = &parser->instr[i];
        struct InstrNode* instr_node = &instr->instr_node;
        
        switch(instr->type)
        {
            case NODE_INSTR_RV:
            {
                bin[bindex++] = instr_node->opcode->op_node.token.type - token_type_op_offset;
                bin[bindex++] = instr_node->param1->reg_node.token.type - token_type_reg_offset;
                
                // store literal values inside of the node
                bin[bindex++] = atoi(instr_node->param2->lit_node.token.lexeme);
                
            }break;
            
            case NODE_INSTR_RR:
            {
                bin[bindex++] = instr_node->opcode->op_node.token.type - token_type_op_offset;
                bin[bindex++] = instr_node->param1->reg_node.token.type - token_type_reg_offset;
                
                bin[bindex++] = instr_node->param2->reg_node.token.type - token_type_reg_offset;
                
            }break;
            default:
            {
                INVALID_CODE_PATH();
            }
        }
        
        
    }   
    
    
    return bin;
    
}