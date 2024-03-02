#ifndef APP_H
#define APP_H

#include <defines.h>
#include <arena.h>

struct App
{
    struct Arena memory;
    size_t memory_size;
};

void app_innit(struct App* app);

void app_free(struct App* app);

#endif