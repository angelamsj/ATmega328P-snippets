/*  Analog to digital converter
    Reads analog input from adc_input and converts it to digital.
    Maps digital output to C degrees and displays it in the LCD.     
*/

#include <mega328P.h>
#include <delay.h>
#include <stdio.h>
#include "display.h"

#define ADC_VREF_TYPE 0xC0 // Internal 1.1V ref with external capacitor at AREF pin

char cadena[15];
float temperatura;
unsigned int tempDigital;

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{

  ADMUX = adc_input | (ADC_VREF_TYPE & 0xff); // Selecting channel and voltage reference
  delay_us(10); // Delay needed for the stabilization of the ADC input voltage in micro seconds
  ADCSRA |= 0x40; // Start the AD conversion
  while ((ADCSRA & 0x10) == 0); // Wait for the AD conversion to complete (ADC = (Vin * 1024) / Vref)
  ADCSRA |= 0x10; // Clearing ADC interrupt flag
  return ADCW; // Return conversion result

}
  
void main (void) 
{
  // ADC Auto Trigger Source: ADC Stopped    
  DIDR0 = 0x20; // Digital input buffers on ADC0, ADC1, ADC2, ADC3, and ADC4 On, ADC5: Off
  ADMUX = ADC_VREF_TYPE & 0xff; // ADC Voltage Reference: Int., cap. on AREF
  ADCSRA = 0x83; //Enabeling ADC and setting the input clock to the ADC at: 125.000 kHz

  ConfiguraLCD();

  while(1)
  {
  
    BorrarLCD(); // Clear LCD  
    tempDigital = read_adc(5); // Reading analog input from pin 5
    temperatura = tempDigital * 110.0/1024.0; // Mapping temperature to C degrees. 
    sprintf(cadena, "%3.1f %cC", temperatura, 0xDF); // Copy temperature into cadena
      
    MoverCursor(4,0); // Place cursor in starting position
    StringLCD("Temperatura:"); // Write to LCD
    MoverCursor(6,1); // Move cursor
    StringLCDVar(cadena); // Write temperature
    delay_ms(1000); // Wait 1 sec                                            
  
  }
} 
