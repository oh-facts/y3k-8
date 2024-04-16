#include <base/base_inc.h>
#include <gen/str_enums.h>

#include <emulator/computer.h>
#include <assembler/types.h>
#include <assembler/assembler.c>
#include <assembler/lexer.c>
#include <assembler/parser.c>

#include <emulator/computer.h>
#include <emulator/computer.c>

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        printl("beep boop beep");
    
        printl("%s\n",argv[1]);
        
        size_t mem_size = Megabytes(1);
        struct Arena arena;
        arena_innit(&arena, mem_size, calloc(mem_size,sizeof(u8)));
        u8* data =  yk_read_binary_file(argv[1],&arena);
    
        
        struct Computer comp = {0};
        comp.ram = data;
        
        execute(&comp);
        
        print_registers(&comp);
        
        printn();
        printn();
        printf("exited\n");
    }

    else if(argc == 3)
    {
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
}