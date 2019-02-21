/* 
	Fecha.c
	
	Day finder
	Given a date, returns the corresponding day of the week
*/

#include <mega328p.h>
#include <stdio.h>

void main(void)
{
    
    char dias[7][10] = {"sabado","domingo","lunes","martes","miercoles","jueves","viernes"}; 
    char separador1 , separador2;
    unsigned int dia , mes, anio, diasemana; 
    
    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity   
    UCSR0A = 0x02; // U2X0 = 1, double tranfer rate for asynchronos communication
    UCSR0B = 0x18; // RXEN0 = 1, enable USART receiver, RXEN0 = 1, enable USART transmitter 
    UCSR0C = 0x06; // Asynchronous mode, parity mode disable, character size 8 bit
    UBRR0H = 0x00;  
    UBRR0L = 0x0C; // USART Baud Rate: 9600 (Double Speed Mode)

    while (1)
    { 

        printf ("Dame la fecha en formato dd-mm-yyyy"); // Ask for date
        scanf ("%i%c%i%c%i",&dia,&separador1,&mes,&separador2,&anio); // Get date from input 
        if ((separador1 == '-') && (separador2 == '-')) { // Validate format
            if ((dia >= 1)&&(dia <= 31)&&(mes >= 1)&&(mes <= 12)) {
                if (mes <= 2) {       
                    mes = mes + 12;
                    anio--;    
                }
                
                diasemana = (dia + ((26 * (mes + 1)) / 10) + anio + anio / 4 + 6 * (anio / 100) + anio/400) % 7;   
                printf("El dia de la semana es %i",&diasemana); // Print week day
            
            } else { // Invalid format
                printf("Formato invalio/n/r");       
            }

        } else { // Invalid format
            printf("Formato invalio/n/r");       
        }  
    }

}