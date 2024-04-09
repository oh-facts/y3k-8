
// function to write to file

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

internal b32 yk_write_to_file(const char* filename, char* data)
{
    FILE* file;
    fopen_s(&file, filename, "wb");
    
    // create file if it doesn't exist
    if(!file)
    {
        printl("File [%s] does not exist. Creating ..",filename);
        fopen_s(&file, filename, "wb+");
        if(!file)
        {
            printl("Could not create file");
            return false;
        }
    }

    size_t len = fwrite(data,sizeof(u8),strlen(data),file);

    if(len!=strlen(data))
    {
        printl("Writing was interrupted for file %s", filename);
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}