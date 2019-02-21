/*  
	MainALU.c
	
	Entry point of the Arithmetic Logic Unit.
*/

#include <mega328P.h>
#include "ALU.h"

void main ()
{
    unsigned char Entrada;
    unsigned char Operacion;
    unsigned char PalabraA;
    unsigned char PalabraB;
    unsigned char Resultado = 0;
    functionALU currentFunction = 0;     
    functionALU functionsArray[8] = {
        &not,
        &and,
        &nand,
        &or,
        &nor,
        &xor,
        &xnor,
        &add
    };
        
    DDRD = 0x0F; // Setting the 4 LSB in port D as output
    
    while(1)
    {
        
        PORTD = Resultado; // Output result, initial value 0;
        Entrada = PINB; // Getting input from PINB
        Operacion = PINC; // Selecting 1 of 8 operations using 3 LSB from PINC     
        PalabraA = Entrada & 0x0F; // Setting PalabraA as the 4 LSB from Entrada
        PalabraB = Entrada >> 4; // Setting PalabraB as the 4 MSB from Entrada using Bitwise Right Shift opperator
        currentFunction = functionsArray[Operacion & 0x07]; // Selecting operacion from array
        Resultado = currentFunction(PalabraA, PalabraB); // Applying operation to operands

    } 
}