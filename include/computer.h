#ifndef LANGUAGE_H
#define LANGUAGE_H

gen_string_from_enum
enum register_type
{
    register_dummy,
    r1 = 0x01,
    r2 = 0x02,
    r3 = 0x03,
    r4 = 0x04,
    r5 = 0x05,
    r6 = 0x06,
    r7 = 0x07,
    r8 = 0x08,
    acc,
    ip,
    register_num
};

typedef enum register_type register_type;

gen_string_from_enum
enum opcode_type
{
    opcode_dummy,
    movv = 1,
    movr,
    addv,
    addr,
    jmp,
    jmpx,
    use,
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

#endif