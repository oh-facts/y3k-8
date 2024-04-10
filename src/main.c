#include "common.h"

// meta
#include "meta/str_enum_device_state.h"
#include "meta/str_enum_device_type.h"
#include "meta/str_enum_NODE_TYPE.h"
#include "meta/str_enum_opcode_type.h"
#include "meta/str_enum_register_type.h"
#include "meta/str_enum_token_type.h"
//

// ---
#include "meta.h"
#include "language.h"
#include "computer.c"
#include "assembler.c"
#include "platform.c"





int main(int argc, char *argv[])
{
    AssertM(argc == 2, "Usage: ./out \"filename\" ");
    printf("beep boop beep\n");
    
    printf("%s\n",argv[1]);
    
    size_t mem_size = Megabytes(1);
    struct Arena arena;
    arena_innit(&arena, mem_size, calloc(mem_size,sizeof(u8)));
    char* data =  yk_read_text_file(argv[1],&arena);
    
    struct lexer lexi = {0};
    lex_tokens(data, &lexi, &arena);
    
    struct parser parser = {0};
    parse_tokens(&parser, &lexi, &arena);
    
    u8* bin = assemble(&parser, &arena);
    
    struct Computer comp = {0};
    comp.ram = bin;
    
    execute(&comp);
    
    print_registers(&comp);
    
    printf("exited\n");
    
}
