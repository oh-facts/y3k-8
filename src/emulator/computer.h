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
  rt_num
};

typedef enum register_type register_type;

gen_string_from_enum
enum opcode_type
{
  op_nop = 0x00,
  op_movv,
  op_movr,
  op_addv,
  op_addr,
  op_jmp,
  op_use,
  op_cmp,
  opcode_num
};

typedef enum opcode_type opcode_type;

gen_string_from_enum
enum device_type
{
  dt_invalid,
  dt_logger,
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
