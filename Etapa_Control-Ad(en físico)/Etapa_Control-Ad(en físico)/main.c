/*
 * **********************ETAPA CONTROL-ADQUISIÓN DE DATOS*********************** 
 * **********************Simulado en Proteus*********************** 
 * Descripción: Se tiene un sensor RFID el cuál se implementará en un protoboard, 
 * este sensor utiliza el protocolo I2C para comunicarse con el PIC.
 * Se mostrará en una pantalla LCD 16X2 el código UID (identificador único de 
 * cada TAG o llavero)de 4 bytes en formato hexadecimal.  
 * 
 */


#define MFRC522_CS   LATA0          // SDA    SS
#define MFRC522_Rst  LATA1          // RST
#define SoftSPI_SDO  LATA2          //MOSI
#define SoftSPI_CLK  LATA3          //SCK
#define SoftSPI_SDI  RA4            //MISO

#define MFRC522_CS_Direction   TRISA0
#define MFRC522_Rst_Direction  TRISA1
#define SoftSPI_SDO_Direction  TRISA2
#define SoftSPI_CLK_Direction  TRISA3
#define SoftSPI_SDI_Direction  TRISA4

#include <xc.h>
#include "Conf.h"
#include "soft_spi.h"
#include "stdio.h"              //sprintf
#include "RC522.h"
#include "MiLCD.h"



char codigo_RFID[2]; 
char UID[4];                        // almacena el buffer del codigo de rfid
unsigned int TagType;               // almacena el tipo de tag
char i;
char a;


void InitPort(void){

ADCON1=0X0F;              // TODO DIGITAL
TRISC=0;                  //Puerto C = salida

/*piloto de inicialización*/
LATCbits.LATC2=1;
__delay_ms(500);
LATCbits.LATC2=0;
__delay_ms(500);
 
}

void main(void) 

{
   
    LCD_Init();              //incializa el LCD
    InitPort();              //inicializa los puertos
    
    LCD_gotoXY(0,0);
    LCD_Cadena("*Lectura de TAG*");
    __delay_ms(200);
    LCD_gotoXY(1,0);
    LCD_Cadena("RFID: ");
    __delay_ms(200);
  
    Soft_SPI_Init();    //Inicia protoclo SPI
    MFRC522_Init();     //inicializa la tarjeta
    __delay_ms(200);
    
    while (1)
        
    {         
        /*si hay lectura de un TAG*/
          if( MFRC522_isCard( &TagType ) )             // si detecta tarjeta      
          {
            i=0; 
            a=6;
            Clear_Linea (1,6);
              if( MFRC522_ReadCardSerial( &UID ) )     // si se puede leer tarjeta
                 {            
                    for (i; i < 4; i++)
                    {      
                     if(UID[i]>16){sprintf(codigo_RFID,"%x",UID[i]);}     
                     else {sprintf(codigo_RFID,"0%x",UID[i]);}           
                          
                        LCD_gotoXY(1,a);                    
                        LCD_Cadena (codigo_RFID);
                        __delay_ms(200);
                        a=a+2;
                    }    
                 __delay_ms(2000);      
                } 
          }    
    }// fin while
}
  