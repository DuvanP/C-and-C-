

#include<p18lf26k22.h>
#include<delays.h>


void temperatura14 (unsigned char T_1,unsigned char T_2);
void conversorhumedad12 (unsigned char H_1 , unsigned char H_2);

unsigned int TEMPERATURA;
unsigned int HUMEDAD;
float F_TEMP;
unsigned int CONVERSION;
unsigned int TEMP1;
unsigned char DECENAS,UNIDADES,DECIMAS,CENTECIMAS;




	void temperatura14 (unsigned char T_1,unsigned char T_2)

{


		  TEMPERATURA = T_1;
		  TEMPERATURA = TEMPERATURA <<8;		
		  TEMPERATURA = TEMPERATURA | T_2;
		  TEMPERATURA = TEMPERATURA >>2;
		  F_TEMP = (0.01075097 * TEMPERATURA);
		  F_TEMP = F_TEMP - 46.85;
		  CONVERSION = F_TEMP * 100;
		  DECENAS = CONVERSION /1000;	
		  TEMP1 = CONVERSION%1000;
		  UNIDADES = TEMP1/100;
		  TEMP1 = TEMP1%100;
		  DECIMAS = TEMP1/10;
		  CENTECIMAS = TEMP1%10;

		  TXREG2 = (DECENAS + 48);
		  while(TXSTA2bits.TRMT ==0){}
		
		  TXREG2 = (UNIDADES + 48);
		  while(TXSTA2bits.TRMT ==0){}

		  TXREG2 = ('.');
		  while(TXSTA2bits.TRMT ==0){}


		  TXREG2 = (DECIMAS + 48);
		  while(TXSTA2bits.TRMT ==0){}

		  TXREG2 = (CENTECIMAS + 48);
		  while(TXSTA2bits.TRMT ==0){}
}

	void conversorhumedad12 (unsigned char H_1 , unsigned char H_2)
{
		  HUMEDAD = H_1;
		  HUMEDAD = HUMEDAD <<8;		
		  HUMEDAD = HUMEDAD | H_2;
		  HUMEDAD = HUMEDAD >>4;
		  F_TEMP = (0.030517578 * HUMEDAD);
		  F_TEMP = F_TEMP - 6;
		  CONVERSION = F_TEMP * 100;
		  DECENAS = CONVERSION /1000;	
		  TEMP1 = CONVERSION%1000;
		  UNIDADES = TEMP1/100;
		  TEMP1 = TEMP1%100;
		  DECIMAS = TEMP1/10;
		  CENTECIMAS = TEMP1%10;

		  TXREG2 = (DECENAS + 48);
		  while(TXSTA2bits.TRMT ==0){}
		
		  TXREG2 = (UNIDADES + 48);
		  while(TXSTA2bits.TRMT ==0){}

		  TXREG2 = ('.');
		  while(TXSTA2bits.TRMT ==0){}


		  TXREG2 = (DECIMAS + 48);
		  while(TXSTA2bits.TRMT ==0){}

		  TXREG2 = (CENTECIMAS + 48);
		  while(TXSTA2bits.TRMT ==0){}
}



