#include <platform.h>

#include <meta.h>
#include <computer.h>

#include <gen/str_enums.h>

#include "types.h"
#include "lexer.c"
#include "parser.c"
#include "assembler.c"

#include <yk_file.h>

int main(int argc, char *argv[])
{
    struct platform pf = {0};
    pf.mem_size = Megabytes(1);
    pf.scratch_size = Megabytes(1);
    pf.memory = calloc(pf.mem_size,sizeof(u8));
    pf.scratch = calloc(pf.mem_size,sizeof(u8));

    pf.read_text_file = yk_read_text_file;
    pf.read_bin_file = yk_read_binary_file;
    pf.write_bin_file = yk_write_binary_file;

    assembler_run(&pf, argc, argv);
}