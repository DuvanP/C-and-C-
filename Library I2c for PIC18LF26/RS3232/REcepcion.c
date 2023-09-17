
#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>


void CONF_OSC(void);
void CONF_PUERTOS(void);
void ENTER(void);
void CONF_USART(void);
void TRANSMISION(void); 
void RECEPCION(void);
void retardo(void);
void ESPERAR_LA_BANDERA(void);


//-------------------------------------------------

void main (void)

{

unsigned char DATO_ENVIAR,DATO_LEER,DATO_RECEPCION,n,f,h,A,LEER_REGISTRO;

unsigned char AA [6] = {'H','o','L','a',13};
unsigned char BB [6] = {'C','h','a','o',13};

unsigned char i;

	CONF_OSC();
	CONF_PUERTOS();
	PIR1bits.RC1IF = 0;
	CONF_USART();




	LATBbits.LATB4 =0;

	while(1)
	{
		RECEPCION();

	}	




}
	
	
//----------------------------------------------------------------------------------

void CONF_OSC(void)
{
// Frecuencia del oscilador interno = 8MHZ

	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	OSCCONbits.IRCF0=0;
} 

//----------------------------------

void CONF_PUERTOS(void)

{
			//76543210

	TRISB = 0b00000000; //se configuran RB6=TX2 y RB7=RX2 en 1 como lo indica el datasheet
	LATB  = 0;

			  //76543210
	ANSELC 	= 0b01111110;
	TRISC 	= 0b10000001; //Se configuran RC6=TX1 y RC7=RX1 en 1 como lo indica el datasheet
	LATC  = 0;

}	

//------------------------------------

void ENTER(void)

{
unsigned char TEMP_ENTER;

	

	while(PORTCbits.RC0)	// Espera a que presione el enter
	{

	}

	Delay10KTCYx(1);		// Retardo de 200 miliSeg para que pase el rebote

	while(~PORTCbits.RC0)	// Espera a que suelte
	{		


	}

}

//----------------------------------------------------------------------------------

void CONF_USART(void)
{

	SPBRGH1 = 3;					// Parte para configurar la velocidad del baudio
	SPBRG1  = 64;				// Para configurar la velocidad del baudio en 57.600
	
	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones
//               76543210
	TXSTA1 =   0b00100110;
	RCSTA1 =   0b10010000;
	BAUDCON1 = 0b00001000;



}

//---------------------------------------------------------------------------

	
	
	void TRANSMISION(void)

{

		TXSTA1bits.TXEN = 1; // habilitar la trasnmision 
		PIR1bits.TX1IF = 1; // Borrar la bandera de transmision 
			//76543210
		 					
		TXREG1= 0b01000010;
		
	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote
	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote
	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote

		TXREG1= 0b01110101;

	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote
	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote
	Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote

}	


//---------------------------------------------------------------------------


	void retardo(void)

{	
	unsigned char p;

	for(p=0;p<2;p++)
	{
	 	Delay10KTCYx;
	}

}


//--------------------------------------------------------------------------

	void RECEPCION(void)

	{

		unsigned char T;

		if(PIR1bits.RC1IF)
		{
		
			T= RCREG1;
			LATBbits.LATB4 = ~LATBbits.LATB4 ;
			TXREG1= T;
			retardo();			

		}


	}

