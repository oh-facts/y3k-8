#include <platform.h>

#include <meta.h>
#include <computer.h>

#include <gen/str_enums.h>

#include "types.h"
#include "assembler.c"
#include "lexer.c"
#include "parser.c"

#include <yk_file.h>

int main(int argc, char *argv[])
{
    AssertM(argc == 3, "Usage: ./out \"input filename\" \"output filename\" ");
    
    printl("Input : %s\n",argv[1]);
    printl("Output: %s\n",argv[2]);
    
    size_t mem_size = Megabytes(1);
    struct Arena arena;
    arena_innit(&arena, mem_size, calloc(mem_size,sizeof(u8)));

    char* data =  yk_read_text_file(argv[1],&arena);
    
    struct token* tokens = lex_tokens(data, &arena);
    
    struct Node* nodes = parse_tokens(tokens, &arena);
    
    u8* bin = assemble(nodes, &arena);
    
    if(!yk_write_binary_file(argv[2], bin,100))
    {
        printf("Failed to output binary %s", argv[2]);
    }

}