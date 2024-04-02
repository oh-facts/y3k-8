#ifndef COMPUTER_H
#define COMPUTER_H

#include <common.h>

enum registers
{
    ip = 0x00,
    r1 = 0x01,
    r2 = 0x02,
    r3 = 0x03,
    r4 = 0x04,
    r5 = 0x05,
    r6 = 0x06,
    r7 = 0x07,
    r8 = 0x08,
    acc = 0x09,
    register_num
};

global const char* registers_str[register_num] = 
{
    "ip",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "acc"
};

enum opcode
{
    movv = 0x00,
    movr,
    addv,
    addr,
    hlt
};

struct Platform
{
    void* main;
    void* scratch;

    size_t mem_size;
    size_t scratch_size;

    u8*  (*read_file)(const char* filename, struct Arena* arena);
};

struct Computer
{
    u8 reg[register_num];
    u8 *ram;
};

inline u8 fetch(struct Computer *self)
{
    return self->ram[self->reg[ip]];
}

inline void next(struct Computer *self)
{
    self->reg[ip] +=1;
}

inline void set(struct Computer* self, u8 reg, u8 value)
{
    
}

inline void execute(struct Computer *self)
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

            case hlt:
            {
                return;
            }break;

            default:
                printf("ooga booga why is control here");
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

void app_innit(struct Computer *self, u8 *base);

void app_load_program(struct Computer* self, const u8* program, u32 num);

void app_free(struct Computer *self);

#endif