#include <y3k8.h>
#include <gen/str_enums.h>

#include "types.h"
#include "assembler.c"
#include "lexer.c"
#include "parser.c"


int main(int argc, char *argv[])
{
    AssertM(argc == 3, "Usage: ./out \"input filename\" \"output filename\" ");
    
    printl("%s\n",argv[1]);
    
    size_t mem_size = Megabytes(1);
    struct Arena arena;
    arena_innit(&arena, mem_size, calloc(mem_size,sizeof(u8)));
    char* data =  yk_read_text_file(argv[1],&arena);
    
    struct lexer lexi = {0};
    lex_tokens(data, &lexi, &arena);
    
    struct parser parser = {0};
    parse_tokens(&parser, &lexi, &arena);
    
    u8* bin = assemble(&parser, &arena);
    
    if(!yk_write_binary_file(argv[2], bin,100))
    {
        printf("Failed to output binary %s", argv[2]);
    }

}