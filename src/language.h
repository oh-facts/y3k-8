#ifndef LANGUAGE_H
#define LANGUAGE_H

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

global const char* register_str[register_num] = 
{
    "INVALID REGISTER",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "acc",
    "ip",
};

enum opcode_type
{
    invalid_op = 0x00,
    movv,
    movr,
    addv,
    addr,
    jmp,
    opcode_num
};

global const char* opcode_str[opcode_num] = 
{
    "INVALID OP",
    "movv",
    "movr",
    "addv",
    "addr",
    "jmp",
};


#endif