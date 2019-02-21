/* 
    Multiplexor.c

    Semaphore
*/

#include <mega328P.h>
#include <delay.h>

#define RojoPeaton  PORTD.3
#define VerdePeaton PORTD.4
#define RojoAuto    PORTD.5
#define AmbarAuto   PORTD.6
#define VerdeAuto   PORTD.7

#define Dig1        PORTD.1
#define Dig2        PORTD.2

unsigned char seg;
bit seleccionDigito = 0;
bit peaton = 0;
int i;

unsigned char SieteSeg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x98};

interrupt[EXT_INT0] void ext_int0_isr(void)                    
{
    peaton = 1;
}
interrupt[TIM0_COMPA] void timer0_compa_isr(void)
{
    int decenas;
    
    seleccionDigito =! seleccionDigito;
    if(seleccionDigito == 0)
    {                       
        Dig1 = 1;
        Dig2 = 1;
        decenas = seg/10;
        PORTC = SieteSeg[decenas];
        Dig1 = 0;
    }            
    else
    {
        Dig1 = 1;
        Dig2 = 1;
        decenas = seg%10;
        PORTC = SieteSeg[decenas];
        Dig2 = 0;
    }
}

void main() 
{
    DDRC = 0x07;
    DDRB.1 =1;
    DDRD = 0xFB; //PD2 entradqa y los demas de salida.
    PORTD.2 = 1;
    
    TCCR0A = 0x02;
    TCCR0B = 0x03;
    OCR0A = 77;
    
    TCCR1A = 0x40;
    //TCCR1B = 0x09;
    OCR1AH = 1135/256;
    OCR1AL = 1135%256;
    
    EICRA = 0x02;
    EIMSK = 0x01;
    EIFR = 0x01;
    PCICR = 0x00;
    
    TIMSK0 = 0x02;
    
    #asm("sei")
    
    while(1)
    {
        RojoPeaton = 1;
        VerdePeaton = 0;
        VerdeAuto = 1;
        AmbarAuto = 0;
        RojoAuto = 0;
        while(!peaton); //Espera que el peaton presione boton
        VerdeAuto = 0;
        AmbarAuto = 1;
        delay_ms(2000);
        RojoPeaton = 0;
        VerdePeaton = 1;
        AmbarAuto = 0;
        RojoAuto = 1;   
        seg = 20; 
        for (i=1;i<81;i++)
        {
            delay_ms(250);
            if((i%4) == 0)
            {
                seg--;
                TCCR1B = 0;
            }
            if((i%4) == 3)
            {
                TCCR1B = 0x09;
            }
        }
        peaton = 0;
        RojoPeaton = 1;
        VerdePeaton = 0;
        VerdeAuto = 1;
        AmbarAuto = 0;
        RojoAuto = 0;
        delay_ms(20000);
    }        
}