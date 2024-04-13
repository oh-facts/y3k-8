#include <y3k8.h>
#include <gen/str_enums.h>

#include "computer.c"

int main(int argc, char *argv[])
{
    AssertM(argc == 2, "Usage: ./out \"filename\" ");
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
