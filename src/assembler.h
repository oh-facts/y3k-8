#define CHAR_TO_INT(c) ((c) - '0')

enum token_type
{
    tk_invalid,
    tk_whitespace,
    tk_op,
    tk_reg,
    tk_num
};

typedef enum token_type token_type;

global char* token_type_str[tk_num] = 
{
    "INVALID","WHITESPACE","OP","REGISTER"
};

struct token
{
    token_type type;
    char lexeme[5];
};

void lex_tokens(char* data)
{
    char* current = &data[0];
    u32 num_tokens = 0;
    struct token tokens[10] = {0};

    while(true)
    {
        switch(*current)
        {
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
            case ' ':
            {
                tokens[num_tokens].type = tk_whitespace;
                tokens[num_tokens].lexeme[0] = ' ';  
                current++;
                num_tokens++;
            }break;

            default:
            {
                goto exit;

            }break;
            
            
        }
    }
    exit:

    for(i32 i = 0; i < num_tokens; i ++)
    {
        printf("%d %s %s\n", i, token_type_str[tokens[i].type], tokens[i].lexeme);
    }

}