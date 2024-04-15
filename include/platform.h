#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define printl(...) printf(__VA_ARGS__); printf("\n")
#define printn()	printf("\n")

#define DEBUG 1

#define _Assert_helper(expr, format, ...)            \
do                                               \
{                                                \
if (!(expr))                                 \
{                                            \
printf(format, ##__VA_ARGS__);           \
volatile int *ptr = 0;                   \
*ptr = 0;                                \
}                                            \
} while (0)

#if DEBUG
#define Assert(expr) _Assert_helper(expr, "Assert failed")
#define AssertM(expr, format, ...) _Assert_helper(expr,format,##__VA_ARGS__)
#else
#define Assert(expr)
#define AssertM(expr, format, ...)
#endif

#define INVALID_CODE_PATH() AssertM(1 > 2, "Invalid code path. Control should never reach here. Yet it did. Are you stupid? (Y or N)")

#define Kilobytes(Value) ((uint64_t)(Value) * 1024)
#define Megabytes(Value) (Kilobytes(Value) * 1024)
#define Gigabytes(Value) (Megabytes(Value) * 1024)
#define Terabytes(Value) (Gigabytes(Value) * 1024)

#define internal static
#define global static
#define local_persist static

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

/*
Meant to be used as booleans
*/
typedef int32_t b32;

#define true 1
#define false 0


#define CHAR_TO_INT(c) ((c) - '0')

internal inline b32 is_digit(char a)
{
    return (a >= '0' && a <= '9');
}

internal inline b32 is_alpha(char a)
{
    return ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'));
}

struct Arena
{
	size_t size;
	u8* base;
	size_t used;
};

internal void* _arena_alloc(struct Arena* arena, size_t size)
{
	Assert(arena->used + size <= arena->size);
	
    void* out = arena->base + arena->used;
	arena->used += size;
	return out;
}

#define push_struct(arena, type) _arena_alloc(arena, sizeof(type))

#define push_array(arena,type,count) _arena_alloc(arena, sizeof(type) * count)

internal void arena_innit(struct Arena* arena, size_t size, void* base)
{
	arena->size = size;
	arena->base = (u8*)base;
	arena->used = 0;
}

#if defined _WIN32
#define YK_API __declspec(dllexport)
#else
#define YK_API
#endif

struct platform
{
    void* memory;
    void* scratch;

    size_t mem_size;
    size_t scratch_size;

    char*  (*read_text_file)(const char* filename, struct Arena* arena);
    u8*  (*read_bin_file)(const char* filename, struct Arena* arena);
    b32 (*write_bin_file)(const char *filepath, const u8 *data, size_t size);
};