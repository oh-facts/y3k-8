internal void print_tokens(struct lexer* lexi)
{
    printn();
    printl("Lexer Output");
    printl("---------------");
    
    for(i32 i = 0; i < lexi->num_tokens; i ++)
    {
        printf("%d %s %s\n", i, str_enum_token_type[lexi->tokens[i].type], lexi->tokens[i].lexeme);
    }
    
    printl("---------------");
    printn();
}

internal void lex_tokens(char* data, struct lexer* lexi, struct Arena* arena)
{
    //todo(facts): fix me
    const u32 max_tokens = 1024;
    
    lexi->tokens = push_array(arena, struct token, max_tokens);
    char* end = data;
    
    // Need a better name for this
#define new_token lexi->tokens[lexi->num_tokens] 
    
    char* current = &data[0];
    
    while(*current != '\0')
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
                    if(*current == '\0')
                    {
                        break;
                    }
                }
            }break;
            // fall through
            case '\t':
            case '\n':
            case ' ':
            {
                
                current++;
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
                        if(strcmp(new_token.lexeme,str_enum_opcode_type[i]) == 0)
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
    
    new_token.type = tk_terminate;
    new_token.lexeme[0] = 'a';
    lexi->num_tokens++;
    
    AssertM(lexi->num_tokens <= max_tokens, "too many tokens");
    
    print_tokens(lexi);
}



