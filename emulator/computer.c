#include "meta.h"

struct logger
{
    device_logger_state state;
};

struct Device
{
    u8 device_slot;
    device_type type;
    device_state state;

    union
    {
        struct logger logger;
    };
};

i8 use_device(struct Device* device, i8 in)
{
    switch (device->type)
    {
        case dt_invalid:
        {
            printl("device type not initialized. This is a bug");
        }break;
        case dt_logger:
        {
            if(device->state == ds_off)
            {
                //printl("logger connected with mode %s",str_enum_device_logger_state[in]);
                device->logger.state = in;
                device->state = ds_on;
                return 1;
            }
            else
            {
                if(device->logger.state == dls_int)
                printf("%d",in);
                return in;
            }
            
        }break;
        default:
        {
            printl("Control shouldn't be here");
        }
    }
    
    return -1;
}

struct Computer
{
    u8 reg[register_num];
    u8 *ram;
    struct Device devices[dt_num];
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

            case use:
            {
                static struct Device dc = {0};
                next(self);
                
                dc.type = self->reg[fetch(self)];
                next(self);

                u8 in = fetch(self);
                next(self);

                use_device(&dc, self->reg[in]);
            }break;

            case jmp:
            {
                next(self);
                
                self->reg[ip] = fetch(self);            

            }break;

            case jmpx:
            {
                next(self);
                static i32 num = 0;
                i32 addr = fetch(self);

                next(self);
                i32 times = fetch(self);
                if(num < times)
                {
                    num ++;
                    self->reg[ip] = addr;
                }
                else
                {
                    next(self);
                }

            }break;
            
            default:
            return;
        }
    }
    
}

internal void print_registers(struct Computer* self)
{   
    printl("Register View");
    printl("---------------");
    for(i32 i = r1; i < register_num; i ++)
    {
        printl("%s : 0x%02x", str_enum_register_type[i], self->reg[i]);
        //printl("%s : %d",register_str[i], self->reg[i]);
    }
    printl("---------------");
    
}