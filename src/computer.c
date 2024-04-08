enum device_type
{
    dt_invalid,
    dt_logger,
    dt_num
};

typedef enum device_type device_type;

enum device_state
{
    ds_off,
    ds_on
};

typedef enum device_state device_state;

struct Device
{
    device_type type;
    device_state state;
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
            printf("%c",in);
        }break;
        default:
        {
            printl("Control shouldn't be here");
        }
    }
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
        printl("%s : 0x%02x",register_str[i], self->reg[i]);
        //printl("%s : %d",register_str[i], self->reg[i]);
    }
    printl("---------------");
    
}