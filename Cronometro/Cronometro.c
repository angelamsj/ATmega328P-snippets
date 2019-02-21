/* Cronometer
   Cronometer with a Pacman on display 
*/

#include <MEGA328P.h> 
#include <delay.h> 
#include <stdio.h>
#include "display.h"         
               
unsigned char decSeg, seg, min, Start;
char cadena[10];
char car0[8] = {0x02, 0x04, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00}; // Defining array to display ó
char car1[8] = {0x0E, 0x1D, 0x1F, 0x1E, 0x1F, 0x1F, 0x0E, 0x00}; // Defining array to display Pacman close mouth
char car2[8] = {0x0E, 0x1D, 0x1E, 0x1C, 0x1E, 0x1F, 0x0E, 0x00}; // Defining array to display Pacman open mouth

void main()
{
    
    decSeg = 0;
    seg = 0;
    min = 0;
    Start = 1;
    PORTD.0 = 1; // Pull-up on PD0, start button
    PORTD.1 = 1; // Pull-up on PD1, reset button 
    ConfiguraLCD(); 
    CreaCaracter(0,car0); 
    CreaCaracter(1,car1);
    CreaCaracter(2,car2);  
       
    while(1)
    {
        MoverCursor(5,0);
        StringLCD("Cron");
        LetraLCD(0);    
        StringLCD("metro"); 
        
        while(1)
        {    
	        if(PIND.0 == 0) // Start button pressed 
            {
                Start = (Start + 1) & 0x01; // Toggle start variable 
                delay_ms(50); // Wait for push-button bounce
            }  
            
            sprintf(cadena, "%02i:%02i.%i" ,min,seg,decSeg); // Copy min, sec, and dsec into cadena
            MoverCursor(6,1);
            StringLCDVar(cadena); // Display time on the LCD   
            delay_ms(52); // Delay to complete the 100ms for each cycle
            
            if(Start == 0)
            {
                PORTD.6 = 1; // Turn on speaker
                delay_ms(10); // Wait 10 ms
                PORTD.6 = 0; // Turn off speaker    
                decSeg++; // Increase dsec 
                if(decSeg == 10) 
                {
                    decSeg = 0; // Clear dsec 
                    seg++; // Increase sec
                    if(seg == 60)
                    {
                        seg = 0; // Clear sec	
                        min++; // Increase minutes
                        if(min == 60)
                        {
                            min = 0; // Clear minuts
                        }
                    }
                }
            } 
            
            if(PIND.1 == 0) // Clear variables when Reset boton is pressed
            {
                decSeg = 0;
                seg = 0;
                min = 0;
            }
            
            if(decSeg == 0) // Display a Pac-Man changing its state every 5 d sec
            {
                MoverCursor(9,3);
                LetraLCD(1); // Pac-Man state 1
            }
            if (decSeg == 5)
            {
                MoverCursor(9,3);
                LetraLCD(2); // Pac-Man state 2
            }     
        }       
    }         

}
