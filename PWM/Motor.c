/* PWM using timer 1
   PIND = 0x00 -> Duty cycle = 0 %
   PIND = 0xFF -> Duty cycle = 100 %
*/
#include <mega328P.h>

void main()
{
    DDRB.1 = 1; // Pin B1 as output   
    TCCR1A = 0x81; // PWM no invertido, PWM 
    TCCR1B = 0x09; // PWM, no prescalating
    
    while (1) {
        OCR1AH = 0;     
        OCR1AL = PIND;  // Getting pulse width from port D  
    }

}