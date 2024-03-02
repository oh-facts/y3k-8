#ifndef ARENA_H
#define ARENA_H

#include <defines.h>

struct Arena
{
	size_t size;
	u8* base;
	size_t used;
};


void* _arena_alloc(struct Arena* arena, size_t size);

#define push_struct(arena, type) _arena_alloc(arena, sizeof(type))

#define push_array(arena,type,count) _arena_alloc(arena, sizeof(type) * count)

void arena_innit(struct Arena* arena, size_t size, void* base);

#endif