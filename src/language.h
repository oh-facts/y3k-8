#ifndef LANGUAGE_H
#define LANGUAGE_H


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
};


#endif