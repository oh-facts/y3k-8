#include <arena.h>

void arena_innit(struct Arena* arena, size_t size, void* base)
{
	arena->size = size;
	arena->base = (u8*)base;
	arena->used = 0;
}

void yk_memory_arena_clean_reset(struct Arena* arena)
{
	memset(arena->base, 0, arena->used);
	arena->used = 0;
}

struct Arena yk_memory_sub_arena(struct Arena* arena, size_t size)
{
	AssertM(arena->size >= arena->used + size, "out of space");
	struct Arena out = {0};
	out.base = (u8*)arena->base + arena->used;
	arena->used += size;
	out.size = size;

	return out;
}

void* _arena_alloc(struct Arena* arena, size_t size)
{
	Assert(arena->used + size <= arena->size);
	arena->used += size;
	void* out = arena->base + arena->used;
	return out;
}