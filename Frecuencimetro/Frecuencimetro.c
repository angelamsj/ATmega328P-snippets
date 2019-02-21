/* Frequencimeter
   Measure the frequency of a squared wave using the microcontroller internal clock
*/
#include <mega328P.h>

#define PULSOS_POR_SEGUNDO 3906

void main ()
{   

    unsigned char UsarFlanco;            
    unsigned int ContadorH;
    unsigned int ContadorL;
    unsigned char FlancoAnterior;
    unsigned int Frecuencia;
    unsigned int FrecuenciaAnterior; 
    unsigned char Centenas;
    unsigned char Decenas;
    unsigned char Unidades;
    unsigned int Contador;
    
    DDRB = 0xFF; // Puerto B as output
    DDRC = 0x0F; // PC0 to PC3 as output
    // PORTB = 0x00;
    // PORTC = 0x00;
    TCCR1B = 0x04; // Timer 1 Prescalate 64 
    UsarFlanco = 0;
    FlancoAnterior = PIND.5;
    Frecuencia = 0;
    FrecuenciaAnterior = 0;
    ContadorH = 0;
    ContadorL = 0;
    Contador = 0;
    TCNT1H = 0;
    TCNT1L = 0;
    
    while (1) { 
        if (FlancoAnterior != PIND.5) { // There is a toggle
            if (FlancoAnterior == 0) { // Previous state was low
                if (UsarFlanco) { // Using rise to count
                    ContadorL = TCNT1L; // Accesing timer/counter data 
                    ContadorH = TCNT1H; // Accesing timer/counter data
                    TCNT1H = 0; // Resetting timer/counter
                    TCNT1L = 0; // Resetting timer/counter
                    Contador = (ContadorH << 8) | (ContadorL & 0x00FF); // Joining timer MSB and LSB                    
                    Frecuencia = ((PULSOS_POR_SEGUNDO / Contador) + FrecuenciaAnterior) / 2; // Calculating frequency                                                
                    Centenas = Frecuencia / 100;
                    Decenas = (Frecuencia % 100) / 10;
                    Unidades = (Frecuencia % 10);
                    PORTB = (Decenas << 4) | (Centenas & 0x0F); // Output frquency part 1 
                    PORTC = Unidades & 0x0F; // Ouput frequency part 2
                    FrecuenciaAnterior = Frecuencia; // Updating previous frequency 
                
                } else { 
                    TCNT1H = 0;
                    TCNT1L = 0;
                }                
                
                UsarFlanco = (UsarFlanco == 0) ? 1 : 0; // Toggle UsarFlanco
            }
            
            FlancoAnterior = PIND.5; // Read PIND.5
        }  
    }

}