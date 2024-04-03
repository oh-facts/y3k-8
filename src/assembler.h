
// lexer, then parser, then assembler

#define CHAR_TO_INT(c) ((c) - '0')

enum token_type
{
    tk_invalid,
    tk_op,
    tk_reg,
    tk_lit,
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
            // add<x>, mov<x>, halt
            // i want to get the assembler up and running, so I won't be doing
            // much validation. If your opcode starts with the same letter as 
            // something that already exists, its valid. If its bigger or smaller
            // than 4 letters, severe problems can happen. That is for future me
            // to care about.
            case 'a':
            case 'm':
            case 'h':
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

    lexi->tokens = tokens;
    lexi->num_tokens = num_tokens;

    //print_tokens(lexi);
}

struct parser
{
    i32 temp;
};

void parse_tokens(struct parser* parser, struct lexer* lexi)
{

}

struct assembler
{
    i32 temp;
    u8 bin[100];
};

void assemble()
{
    u8 code[256] = {
    movv, r1 , 0x11,
    movv, r2 , 0x22,
    addr, r1 , r2,
    halt
    };
     FILE *file;
    file = fopen("data.bin", "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return;
    }

    // Write data to the file
    fwrite(code, sizeof(u8), sizeof(code) / sizeof(u8), file);

    // Close the file
    fclose(file);

    //ass->bin = 
}