#include <common.h>
#include <platform.h>
#include <yk_string.h>
// todo
// will require people testing it to come up with a good api.

// I think I have fixed all edge cases?
// Only need to clean it up and abuse file writing lesser

// Another meta tool I need.
// I write down enums inside of a .facts file
// then I can generate them insde another enum
// something like
/*
@type
enum alpha
{
    a,b,c,d
};

@type
enum num
{
    25,68,39
};

@expand
enum alpha_fruit_num
{
    @alpha, apple, orange, (n)_@num
}

// generated code
enum alpha_fruit_num
{
    a,b,c,d,apple,orange, n_25, n_68, n_39
}
*/
struct token
{
    char* lexeme;
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

#define enum_gen "gen_string_from_enum"
u32 enum_gen_size = strlen(enum_gen);

void extract(char* data, struct Arena* arena)
{
    char* curr = data;
    
    while(*(++curr) != '\0')
    {
        while(is_white_space(curr))
        {
            ++curr;
        }
        
        // g...
        if(*curr == 'g')
        {
            if(match_word(curr, enum_gen, enum_gen_size ))
            {
                // verify
                curr += enum_gen_size;
                
                while(is_white_space(curr))
                {
                    ++curr;
                }
                
                if(match_word(curr, "enum", strlen("enum")))
                {
                    // skip enum keyword
                    curr += strlen("enum");
                    
                    /*
                        capture name
                    */
                    
                    while(is_white_space(curr))
                    {
                        ++curr;
                    }
                    
                    // extract name
                    char* name_start = curr;
                    u32 name_size = 0;
                    while(*(++curr) != '{')
                    {
                        if(!is_white_space(curr))
                        {
                            name_size++;
                        }
                    }
                    
                    
                    char name[128] = {0};
                    memcpy(name, name_start, name_size+1);
                                        
                    struct token *tokens = push_array(arena,struct token, 256);
                    u32 token_num = 0;
                    while(*curr != '}')
                    {
                        switch(*curr)
                        {
                            case '/':
                            {
                                curr = skip_comments(curr);
                            }break;

                            case ' ':
                            case '\n':
                            case '\t':
                            case ',':
                            {
                                ++curr;
                            }break;

                            case '=':
                            {
                                while(*(++curr) != ',')
                                {

                                }
                            }break;

                            default:
                            {
                                if(is_alpha(*curr))
                                {
                                    char* peek = curr;
                                    u32 lexeme_len = 0;
                                    
                                    while(is_alpha(*peek) || is_digit(*peek) || *peek == '_')
                                    {    
                                        lexeme_len++;
                                        peek++;
                                    }
                                    tokens[token_num].lexeme = push_array(arena, char*, lexeme_len);
                                    memcpy(tokens[token_num].lexeme, curr,lexeme_len);
                                    token_num ++;
                                    curr += lexeme_len;

                                }
                                else
                                {
                                    curr++;
                                }
                            }

                        }
                    }

                    // I hate how I am writing so many times instead of one write.
                    // But this will have to do for now.

                    FILE *file;
                    char file_name[] = "../include/gen/str_enum_";
                    char ext[] = ".h";
                    
                    strcat_s(file_name, 256 ,name);
                    strcat_s(file_name, 256 ,ext);

                    fopen_s(&file, file_name, "w+");

                    fprintf(file,"//This file was not written by a human\n\n");

                    printl("global const char* %s[]={", name);
                    fprintf(file, "global const char* str_enum_%s[] =\n{\n",name);
                    for(i32 i = 0; i < token_num; i ++)
                    {
                        printl("\"%s\",",tokens[i].lexeme);
                        fprintf(file, "\t\"%s\",\n", tokens[i].lexeme);
                    }
                    printl("};");
                    fprintf(file, "};");

                    fclose(file);
                
                    

  
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    struct Arena arena;
    arena_innit(&arena, Megabytes(1), calloc(Megabytes(1),sizeof(u8)));

    char* files[] = 
    {
        "../assembler/types.h",
        "../include/computer.h"
    };

    for(i32 i = 0; i < 2; i ++)
    {
        char* data = yk_read_text_file(files[i], &arena);
        extract(data,&arena);

        arena.used = 0;
        memset(arena.base,0, arena.size);
    }
    
    return 0;
}