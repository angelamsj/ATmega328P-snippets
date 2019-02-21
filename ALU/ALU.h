/*
    ALU.h
    
    Arithmetic logic unit interface
    Functions included: not, and, nand, or, nor, xor, xnor, and add.
*/ 

typedef unsigned char (*functionALU) (
    unsigned char,
    unsigned char
    );

unsigned char not (
    unsigned char A,
    unsigned char B
    );

unsigned char and (
    unsigned char A,
    unsigned char B
    );

unsigned char nand (
    unsigned char A,
    unsigned char B
    );

unsigned char or (
    unsigned char A,
    unsigned char B
    );

unsigned char nor (
    unsigned char A,
    unsigned char B
    );

unsigned char xor (
    unsigned char A,
    unsigned char B
    );

unsigned char xnor (
    unsigned char A,
    unsigned char B
    );

unsigned char add (
    unsigned char A,
    unsigned char B
    );