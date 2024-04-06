#include "common.h"
#include "language.h"
struct Computer
{
    u8 reg[register_num];
    u8 *ram;
};

internal inline u8 fetch(struct Computer *self)
{
    return self->ram[self->reg[ip]];
}

internal inline void next(struct Computer *self)
{
    self->reg[ip] ++;
}

internal void execute(struct Computer *self)
{
    while(1)
    {
        switch (fetch(self))
        {
            case movv:
            {
                next(self);
                u8 dst = fetch(self);
                next(self);
                u8 src = fetch(self);
                next(self);
                self->reg[dst] = src;
                
                

            }break;
            
            case movr:
            {   
                next(self);
                u8 dst = fetch(self);
                next(self);
                u8 src = fetch(self);
                next(self);
                self->reg[dst] = self->reg[src];
                
                

            }break;

            case addv:
            {
                next(self);
                u8 dst = fetch(self);
                next(self);
                u8 src = fetch(self);
                next(self);
                self->reg[dst] += src;
                
            }break;

            case addr:
            {
                next(self);
                u8 dst = fetch(self);
                next(self);
                u8 src = fetch(self);
                next(self);
                self->reg[dst] += self->reg[src];
                
            }break;

            default:
                return;
            }
    }
    
}

internal void print_registers(struct Computer* self)
{   
    for(i32 i = 0; i < register_num; i ++)
    {
        printl("%s : 0x%02x",registers_str[i], self->reg[i]);
    }
}