#include <computer.h>
#include <assembler.h>
#if defined(__unix__) || defined(__APPLE__)
#define fopen_s(pFile, filepath, mode) ((*(pFile)) = fopen((filepath), (mode))) == NULL
#endif

internal char *yk_read_text_file(const char *filepath, struct Arena *arena)
{
    FILE *file;
    fopen_s(&file, filepath, "r");
    
    AssertM(file, "Unable to open the file %s\n", filepath);
    
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    AssertM(length > 0, "File %s is empty", filepath);
    
    char *string = push_array(arena, char, length + 1);
    
    char c;
    int i = 0;
    
    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    
    fclose(file);
    
    return string;
}

internal u8 *yk_read_binary_file(const char *filename, struct Arena *arena)
{
    FILE *file;
    fopen_s(&file, filename, "rb");
    
    AssertM(file,"Failed to open file %s",filename);
    
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    u8 *buffer = push_array(arena, u8, fileSize);
    
    if (fread(buffer, 1, fileSize, file) != fileSize)
    {
        AssertM(0,"Failed to read file %s",filename);
    }
    
    fclose(file);
    
    return buffer;
}

int main(int argc, char *argv[])
{
  printf("beep boop beep\n");

  struct Computer comp = {0};

  size_t mem_size = Megabytes(16);
  struct Arena arena;
  arena_innit(&arena, mem_size, calloc(mem_size,sizeof(u8)));
  char* data =  yk_read_text_file("eep.fasm",&arena);
  
  lex_tokens(data);
  /*
  app_innit(&comp, push_array(&arena, u8, 256));
  
  u8 code[256] = {
    movv, r1 , 0x11,
    movv, r2 , 0x22,
    addr, r1 , r2,
    hlt
  };

  code[255] = 0x69;

  app_load_program(&comp, code,256);

  execute(&comp);

  print_registers(&comp);

  printf("exited\n");
  */
}
