#include <string.h>

#include "common.h"
#include "platform.c"

// output file can look like
// // This file has been generated by meta.c
// For now, recreate it everytime you run

// todo
// clean up strings and print them
// write them to a file

#include <string.h>

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

#define enum_gen "gen_string_from_enum"
u32 enum_gen_size = strlen(enum_gen);

void extract(char* start)
{
    // verify
    char* peek = start + enum_gen_size;
    ++peek;
    if(match_word(peek, "enum", strlen("enum")))
    {
        // skip enum keyword
        peek += strlen("enum");
        
        /*
            capture name
        */
        
        // skip whitespace
        // make a function to do this and also skip \t and \n
        while(*(++peek) == ' ')
        {
        
        }
        char* name_start = peek;
        u32 name_size = 0;
        while(*(++peek) != '{')
        {
            name_size++;
        }
        
        {
            char buffer[128] = {0};
            memcpy(buffer, name_start, name_size);
            printl("const char* %s[]={", buffer);
        }
                

        // remove {
        ++peek;
        
        i32 len = 0;
        char* beg = peek;
        
        while(*(++peek) != '}')
        {
            if(*peek == ' ' || *peek == '\n' || *peek == '\t')
            {
                beg = peek;
                continue;
            }
            len++;
            if(*peek == ',')
            {
                // remove starting ' '
                beg++;

                // remove comma
                len--;
                
                char buffer[128] = {0};
                memcpy(buffer, beg, len);
                printf("\"%s\",\n", buffer);
                
                beg = peek;
                len = 0;
            }
        }
        printl("};");
    }
    
}

int main(int argc, char* argv[])
{
    struct Arena arena;
    arena_innit(&arena, Megabytes(1), calloc(Megabytes(1),sizeof(u8)));
    char* data = yk_read_text_file("../src/assembler.c", &arena);
    
    //printf("%s",data);
    
    char* peek = data;
    
    
    while(*(++peek) != '\0')
    {
        // g...
        if(*peek == 'g')
        {
            if(match_word(peek, enum_gen, enum_gen_size ))
            {
                extract(peek);
                //printf("%s",peek);
                //break;
            }
        }
    }

   // yk_write_to_file("../src/meta/enum_strings.h", hi);
    return 0;
}