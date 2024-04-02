#include <computer.h>

void app_innit(struct Computer *self, u8* base)
{
    self->ram = base;
}

void app_load_program(struct Computer* self, const u8* program, u32 num)
{
    memcpy(self->ram,program,sizeof(u8) * num);
}

void app_free(struct Computer *self)
{
}
