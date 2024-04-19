
struct Device
{
  u8 device_slot;
  device_type type;
  device_state state;
};

// the idea was that use does both input and output,
// use device input &ouput
// but i am unsure about this design, so for now, the
// return value is unused by the callers
// then i changed it to this. i am still unhappy with it, but I don;t
// care since I don;t have enough devices to understand what would
// be optimal
void use_device(device_type type, i8 in)
{
  switch (type)
  {
    case dt_invalid:
    {
      printl("device type not initialized. This is a bug");
    }break;
    
    case dt_logger_int:
    {
      printf("%hhu",in);
    }break;
    
    case dt_logger_char:
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
  u8 reg[rt_num];
  u8 *ram;
  struct Device devices[256];
};

internal u8 fetch(struct Computer *self)
{
  return self->ram[self->reg[rt_ip]];
}

internal void next(struct Computer *self)
{
  self->reg[rt_ip] ++;
}

internal void exec_jmp_instr(struct Computer *self, flag_type flag)
{
  next(self);
  if(self->reg[rt_flags] & flag)
  {
    self->reg[rt_ip] = fetch(self);
  }
  else
  {
    next(self);
  }
}

internal void execute(struct Computer *self)
{
  while(1)
  {
    switch (fetch(self))
    {
      case op_movv:
      {
        next(self);
        u8 dst = fetch(self);
        next(self);
        u8 src = fetch(self);
        next(self);
        self->reg[dst] = src;
        
        
        
      }break;
      
      case op_movr:
      {   
        next(self);
        u8 dst = fetch(self);
        next(self);
        u8 src = fetch(self);
        next(self);
        self->reg[dst] = self->reg[src];
        
        
        
      }break;
      
      case op_addv:
      {
        next(self);
        u8 dst = fetch(self);
        next(self);
        u8 src = fetch(self);
        next(self);
        self->reg[dst] += src;                
      }break;
      
      case op_addr:
      {
        next(self);
        u8 dst = fetch(self);
        next(self);
        u8 src = fetch(self);
        next(self);
        self->reg[dst] += self->reg[src];
        
      }break;
      //note(facts): I hate this usage. think of better api when you work on devices properly. even i don't remember how it works, i copy paste my old asm
      case op_use:
      {
        next(self);
        
        device_type type = self->reg[fetch(self)];
        next(self);
        
        u8 in = fetch(self);
        next(self);
        
        use_device(type, self->reg[in]);
      }break;
      
      case op_jmp:
      {
        next(self);
        
        self->reg[rt_ip] = fetch(self);            
        
      }break;
      
      case op_cmp:
      {
        self->reg[rt_flags] = 0;
        
        next(self);
        
        u8 reg1 = self->reg[fetch(self)];
        next(self);
        
        u8 reg2 = self->reg[fetch(self)];
        next(self);
        
        // i am one sneaky boy. i hope no one bullies me for this silly
        i16 diff = (i16)reg1 - reg2;
        
#define sign_16 (1 << 15)
        
        if(diff == 0)
        {
          self->reg[rt_flags] |= ft_zero;
        }
        else if(diff & sign_16)
        {
          self->reg[rt_flags] |= ft_sign;
        }
        else
        {
          self->reg[rt_flags] |= ft_carry;
        }
        
        
      }break;
      case op_je:
      {
        exec_jmp_instr(self, ft_zero);
      }break;
      
      case op_jl:
      {
        exec_jmp_instr(self, ft_sign);
      }break;
      
      case op_jg:
      {
        exec_jmp_instr(self, ft_carry);
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
  for(i32 i = rt_r1; i < rt_num; i ++)
  {
    printl("%s : 0x%02x", str_enum_register_type[i], self->reg[i]);
    //printl("%s : %d",register_str[i], self->reg[i]);
  }
  printl("---------------");
  
}