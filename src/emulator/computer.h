/* date = April 18th 2024 0:54 pm */

#ifndef COMPUTER_H
#define COMPUTER_H


gen_string_from_enum
enum register_type
{
  invalid_register_type = 0x00,
  rt_r1 = 0x01,
  rt_r2 = 0x02,
  rt_r3 = 0x03,
  rt_r4 = 0x04,
  rt_r5 = 0x05,
  rt_r6 = 0x06,
  rt_r7 = 0x07,
  rt_r8 = 0x08,
  rt_acc,
  rt_ip,
  rt_flags,
  rt_num
};

typedef enum register_type register_type;

gen_string_from_enum
enum flag_type
{
  ft_zero = (1 << 0),
  ft_sign = (1 << 1),
  ft_carry = (1 << 2),
  ft_num,
};

typedef enum flag_type flag_type;

gen_string_from_enum
enum opcode_type
{
  invalid_op = 0x00,
  op_mov,
  op_add,
  op_jmp,
  op_use,
  op_cmp,
  op_icmp,
  op_jg,
  op_jl,
  op_je,
  opcode_num
};

typedef enum opcode_type opcode_type;

gen_string_from_enum
enum arg_type
{
  invalid_at,
  at_rv,
  at_rr,
  at_num
};

typedef enum arg_type arg_type;

gen_string_from_enum
enum device_type
{
  dt_invalid,
  dt_logger_char,
  dt_logger_int,
  dt_logger_uint,
  
  dt_num
};

typedef enum device_type device_type;

gen_string_from_enum
enum device_state
{
  ds_off,
  ds_on
};

typedef enum device_state device_state;

gen_string_from_enum
enum device_logger_state
{
  dls_int,
  dls_char
};

typedef enum device_logger_state device_logger_state;




#endif //COMPUTER_H
