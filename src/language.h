#ifndef LANGUAGE_H
#define LANGUAGE_H

gen_string_from_enum
enum register_type
{
    invalid_register_type = 0x00,
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
    invalid_op = 0x00,
    movv,
    movr,
    addv,
    addr,
    jmp,
    jmpx,
    opcode_num
};

typedef enum opcode_type opcode_type;

#endif