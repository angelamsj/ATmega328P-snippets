/*  Comparator of two magnitudes
    Compares magnitudes represented in hexadecimal. 
    Values from 0 - 255
*/

#include <mega328P.h>

void main (void)
{
    unsigned char Entrada1;
    unsigned char Entrada2;
    
    DDRC = 0x03; // Setting two LSB as outputs (1), port C as rrrrrrww 
    PORTC = 0x00; // Setting all bits on port C to 0    

    while (1) {
        Entrada1 = PINB; // Getting input from all bits of port B   
        Entrada2 = PIND; // Getting input from all bits of port D
        if (Entrada1 == Entrada2) { // Same value write 0x01
            PORTC.0 = 1;
            PORTC.1 = 0;

        } else if (Entrada1 > Entrada2 ) { // Input 1 greater value write 0x02
            PORTC.0 = 0;
            PORTC.1 = 1;

        } else { // Input 2 greater value write 0x03
           PORTC.0 = 0;
           PORTC.1 = 0;

        }          
    }
}