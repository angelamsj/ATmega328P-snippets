#include "ALU.h"

unsigned char not (
    unsigned char A,
    unsigned char B
    )
{
    return (~A);    
}

unsigned char and (
    unsigned char A,
    unsigned char B
    )
{
    return (A & B);    
}

unsigned char nand (
    unsigned char A,
    unsigned char B
    )
{
    return (~(A & B));    
}

unsigned char or (
    unsigned char A,
    unsigned char B
    )
{
    return (A | B);    
}

unsigned char nor (
    unsigned char A,
    unsigned char B
    )
{
    return (~(A | B));    
}

unsigned char xor (
    unsigned char A,
    unsigned char B 
    )
{
    return (A ^ B);    
}

unsigned char xnor (
    unsigned char A,
    unsigned char B 
    )
{
    return (~(A ^ B));    
}

unsigned char add (
    unsigned char A,
    unsigned char B
    )
{
    return (A + B);    
}