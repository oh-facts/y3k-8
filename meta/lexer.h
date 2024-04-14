#define enum_gen "gen_string_from_enum"
u32 enum_gen_size = strlen(enum_gen);

struct token
{
    char* lexeme;
};

enum token_type
{
    tk_ident,
    tk_lit,

    tk_comma,
    tk_semicolon,
    tk_equals,
    
    tk_lbrack,
    tk_rbrack,
};

typedef enum token_type token_type;

struct lexer
{
    i32 temp;   
};

struct output_enum_string
{
    // big chunk of whole thing separated with commas
    char* string;
    
    char* enum_name;
};

b32 match_word(char* start, const char* match, u32 size)
{
    if(memcmp(start, match, size) == 0)
    {
        return true;
    }
    
    return false;
}

b32 is_white_space(char* curr)
{
    if(*curr == ' ' || *curr == '\n' || *curr == '\t')
    {
        return true;
    }
    else
    {
        return false;
    }
}

char* skip_comments(char* curr)
{
    if(*curr == '/' && *(curr + 1) == '/' )
    {
        while(*(++curr) != '\n')
        {
            
        }
        
    }
    
    return curr;
}