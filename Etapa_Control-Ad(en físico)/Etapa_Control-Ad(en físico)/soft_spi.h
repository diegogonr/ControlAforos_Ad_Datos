
/*librería de protocolo SPI para la comunicación entre modulo RC522 y uC*/

void Soft_SPI_Init()
{
   //configura pines a usar como spi;
   SoftSPI_SDO_Direction=0;      
   SoftSPI_CLK_Direction=0;
   SoftSPI_SDI_Direction=0;
   SoftSPI_SDI_Direction=1;

      SoftSPI_CLK =0;
      MFRC522_CS  =0;
      SoftSPI_SDO =0;
}


unsigned char  Soft_SPI_Read()
{
  unsigned char cont_s= 0;
  unsigned char dato_ = 0;

  for(cont_s= 0; cont_s < 8; cont_s++)
  {
      dato_ <<= 1;
      SoftSPI_CLK = 1;                      //clck en 1 para enviar dato
      __delay_us(10);                       //retardo de lectura

      if(SoftSPI_SDI != 0)
      {
        dato_ |= 1;
      }
      SoftSPI_CLK = 0;
      __delay_us(10);
  }
  return dato_;
}

void Soft_SPI_Write(unsigned char dato_)
{
  unsigned char cont_s= 0;

  for(cont_s = 0;cont_s < 8; cont_s++)
  {

    if((dato_ & 0x80) != 0) SoftSPI_SDO = 1;  //sino termina rotación coloca un uno sino un cero
    else    SoftSPI_SDO = 0;
    dato_ <<= 1;                              //vota el dato
    //genera un pulso del reloj
    SoftSPI_CLK = 1;
    __delay_us(10);
    SoftSPI_CLK = 0;
    __delay_us(10);
  }
}






