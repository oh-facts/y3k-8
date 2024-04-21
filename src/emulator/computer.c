
// insanity. need to get rid of this

// I am strongly considering to remove this because
// my award winning debugger can't resolve this (no debugger can,
// but I hoped raddbg could)

#define SET_FLAGS_EQUAL(self, reg1, reg2) \
if ((reg1) == (reg2)) \
{\
(self)->reg[rt_flags] |= ft_zero; \
}\
else if ((reg1) < (reg2))\
{\
(self)->reg[rt_flags] |= ft_sign; \
}\
else\
{\
(self)->reg[rt_flags] |= ft_carry; \
}

#define EXEC_CMP(self, type) \
self->reg[rt_flags] = 0; \
next(self);\
\
type args[2] = {0};\
\
for(u32 i = 0; i < 2; i ++)\
{\
arg_type arg_type = fetch(self);\
next(self);\
\
if(arg_type == arg_v)\
{\
args[i] = fetch(self);\
}\
else if(arg_type == arg_r)\
{\
args[i] = self->reg[fetch(self)];\
}\
else\
{\
INVALID_CODE_PATH();\
}\
next(self);\
}\
SET_FLAGS_EQUAL(self, args[0], args[1]);

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
    
    case dt_logger_char:
    {
      printf("%c",in);
    }break;
    
    case dt_logger_int:
    {
      printf("%hhd" ,in);
    }break;
    
    case dt_logger_uint:
    {
      printf("%hhu",in);
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

// dst stored in upper 8 bit, src stored in lower 8 bit
// idk why I am not passing it as &params
internal u16 exec_arith_get_src_dst(struct Computer *self)
{
  next(self);
  
  // dst mod is meaningless for now
  next(self);
  
  u8 dst = fetch(self);
  next(self);
  
  arg_type src_type = fetch(self);
  next(self);
  
  u8 src;
  
  if(src_type == arg_v)
  {
    src = fetch(self);
  }
  else if(src_type == arg_r)
  {
    src = self->reg[fetch(self)];
  }
  else
  {
    INVALID_CODE_PATH();
  }
  next(self);
  
  return ((u16)dst << 8) | src;
}

internal void execute(struct Computer *self)
{
  while(1)
  {
    switch (fetch(self))
    {
      case op_mov:
      {
        u16 res = exec_arith_get_src_dst(self);
        
        self->reg[(u8)(res >> 8)] = (u8)res;
        
      }break;
      
      case op_add:
      {
        u16 res = exec_arith_get_src_dst(self);
        
        self->reg[(u8)(res >> 8)] += (u8)res;
        
      }break;
      
      case op_sub:
      {
        u16 res = exec_arith_get_src_dst(self);
        
        self->reg[(u8)(res >> 8)] -= (u8)res;
        
      }break;
      
      case op_mul:
      {
        u16 res = exec_arith_get_src_dst(self);
        
        self->reg[(u8)(res >> 8)] *= (u8)res;
        
      }break;
      
      case op_div:
      {
        u16 res = exec_arith_get_src_dst(self);
        
        self->reg[(u8)(res >> 8)] /= (u8)res;
        
      }break;
      //note(facts): I hate this usage. think of better api when you work on devices properly. even i don't remember how it works, i copy paste my old asm
      case op_use:
      {
        next(self);
        
        // 0 is dst, 1 is src
        u8 args[2] = {0};
        
        for(u32 i = 0; i < 2; i ++)
        {
          arg_type type = fetch(self);
          next(self);
          
          if(type == arg_v)
          {
            args[i] = fetch(self);
          }
          else if(type == arg_r)
          {
            args[i] = self->reg[fetch(self)];
          }
          else
          {
            INVALID_CODE_PATH();
          }
          next(self);
        }
        
        use_device(args[0], args[1]);
        
      }break;
      
      case op_jmp:
      {
        next(self);
        
        self->reg[rt_ip] = fetch(self);            
        
      }break;
      
      case op_cmp:
      {
        EXEC_CMP(self,u8);
      }break;
      case op_icmp:
      {
        EXEC_CMP(self,i8);
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
  printl("\n\nRegister View");
  printl("---------------");
  for(i32 i = rt_r1; i < rt_num; i ++)
  {
    printl("%s : 0x%02x", str_enum_register_type[i], self->reg[i]);
    //printl("%s : %d",register_str[i], self->reg[i]);
  }
  printl("---------------");
  
}