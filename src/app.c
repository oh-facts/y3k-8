#include <app.h>

void app_innit(struct App *app)
{
    size_t mem_size = Megabytes(16);
    app->memory_size = mem_size;
    arena_innit(&app->memory, mem_size, malloc(mem_size));
}

void app_free(struct App *app)
{
}
