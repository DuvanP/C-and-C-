
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
	CONF_USART();
	ENTER();





		A= 0b01000001;
		h= 0b01000010;


		
//------------------------------------- COmo dice el Data

//	SPBRGH1 = 0;					// Parte para configurar la velocidad del baudio
//	SPBRG1  = 34;				// Para configurar la velocidad del baudio en 57.600
//
//	TRISCbits.RC6 = 1;		// Configura el pin RC6/TX como pin de entrada
//	TRISCbits.RC7 = 1;		// Configura el pin RC7/RX como pin de entrada
//
//	ANSELC = 0; 			// COnfigura El Puerto C como pines I/o digitales
//
//	TXSTA1bits.SYNC = 0;    // configura el modo ASINCRONO en la EUSART
//
//	RCSTA1bits.SPEN = 1;	// Habilita los pines del puerto serial
//
//	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones
//
//	INTCONbits.PEIE = 0;	// Deshabilita las interrupciones perifericas
//	
//	PIE1bits.RC1IE = 0;		// DEsabilita las interrupciones en modo recepcion 
//
//	RCSTA1bits.CREN = 1; 	// Habilita la recepcion
//	
//	DATO_RECEPCION=RCSTA1;	// Lee el puerto para que la bandera RC1IF se ponga en 0	
//
//		
//while(1)
//{
//
//	ESPERAR_LA_BANDERA();	// rutina que espera el la bandera de recepcion
//	
//	
//	LEER_REGISTRO = RCSTA1;	// Lee las banderas para mirar si hubo errores 
//
//	DATO_RECEPCION =RCSTA1;	// Lee el registro de la recepcion con el dato ya recivido 
//							// y tambien con esto genera que la bandera RC1IF se ponda en 0
//
//	
//	if ( RCSTA1bits.OERR == 1)
//	{
//		RCSTA1bits.CREN = 0;	// si ocurrio un desborde en la recepcion de los datos
//								// se debe borrar el CREN para que el OERR se borre
//
//		RCSTA1bits.CREN = 1;	// vuelve a activar la recepcion.
//	}
//
//				if ( DATO_RECEPCION == A)	
//				{
//					 DATO_RECEPCION = 0;
//				 	 LATBbits.LATB4 = 1;
//					 TXSTA1bits.TXEN = 1;	
//					 TXREG1 = 0b01100001;
//					 retardo();	
//					 TXSTA1bits.TXEN = 0;
//				}
//
//}	
//	

	

	while(1)
	{TRANSMISION();}
	




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

	TRISB = 0b11000000; //se configuran RB6=TX2 y RB7=RX2 en 1 como lo indica el datasheet
	LATB  = 0;

	TRISC = 0b11000001; //Se configuran RC6=TX1 y RC7=RX1 en 1 como lo indica el datasheet

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

	SPBRGH1 = 0;					// Parte para configurar la velocidad del baudio
	SPBRG1  = 34;				// Para configurar la velocidad del baudio en 57.600
	
	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones
//               76543210
	TXSTA1 =   0b00010110;
	RCSTA1 =   0b10000000;
	BAUDCON1 = 0b00001010;



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

	void RECEPCION(void)
{
	
	unsigned char n=0,DATO_RECEPCION,h,a;
	

	PIR1bits.RC1IF = 1; // Borrar la bandera de recepcion
	RCSTA1bits.CREN = 0; 
	n = RCREG1;
	h= 0b01000010;
	a= 0b01000011;
	

	if(PIR1bits.RC1IF = 1)

	{	
		DATO_RECEPCION = RCREG1;
		
		if( DATO_RECEPCION == a)
			{ 	LATBbits.LATB4 = 1;}
		if( DATO_RECEPCION == h)

			{ 
				LATBbits.LATB4 = 1;

				Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote

				LATBbits.LATB4 = 0;

				Delay10KTCYx(1000000);		// Retardo de 200 miliSeg para que pase el rebote
			}
	}	

	else 
		{RECEPCION(); }
	

	
}

//-------------------------------------------------------------------------

	void retardo(void)

{	
	unsigned char p;

	for(p=0;p<2;p++)
	{
	 	Delay10KTCYx;
	}

}


//-------------------------------------------------------------------------

	void ESPERAR_LA_BANDERA(void)

	{
		if(PIR1bits.RC1IF == 0)
			{ ESPERAR_LA_BANDERA();}

	}