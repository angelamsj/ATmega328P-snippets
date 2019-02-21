/* 
	PWM_sintimer.c
	
	PWM using delay
	tiempo1 = 0x00 -> DC = 0 %
	tiempo1 = 0x0F -> DC = (15/16) * 100 %
*/

#include <mega328P.h>
#include <delay.h>

unsigned char tiempo1;

void main ()
{

    DDRB.1 = 1; // Pin B1 as output

    while (1) {
        tiempo1 = PIND & 0x0F; // Getting 4 LSB of Port D as input 
        PORTB.1 = 0; // Low state
        delay_ms(16-tiempo1); 
        PORTB.1 = 1; // High state
        delay_ms(tiempo1);
    }

}