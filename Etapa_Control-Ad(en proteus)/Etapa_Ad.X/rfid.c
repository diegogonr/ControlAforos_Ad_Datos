/*
 * **********************ETAPA CONTROL-ADQUISI�N DE DATOS*********************** 
 * **********************Simulado en Proteus*********************** 
 * Descripci�n: Se tiene un sensor RFID el cu�l se simular� en Proteus, este sensor
 * para enviar datos al microcontrolador se realiza por medio de un bot�n  (Lectura
 * de tarjeta), el microcontrolador lo recibe y va mostrando en un display 7 seg
 * la cantidad de veces que se detecto una lectura (si se ha presiona el bot�n)  
 * 
 * RB0 = Recepci�n de informaci�n. 
 * AUTOR: DIEGO MANUEL GONZALES RODRIGUEZ
 */


#include <xc.h>
#include "Conf.h"
#include "stdio.h"            

#define Total_Personas 5

char i;                                     //cantidad de personas

void InitPort(void){

ADCON1=0X0F;              // TODO DIGITAL

TRISC=0;                  
TRISA=0;
TRISBbits.RB0=1;        

/*piloto de inicializaci�n*/
LATCbits.LATC2=1;
__delay_ms(500);
 
}

void main(void) 

{
   
    InitPort();              
    
    while (1)
        
    {         
        /*si hay lectura de un TAG*/
          if( PORTBbits.RB0==1 && i<Total_Personas)             // si detecta tarjeta      
          {            
              i++;
              LATA=i;
              __delay_ms(1000);      
                 
          }    
    }// fin while
}
  