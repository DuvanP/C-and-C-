


#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>
#include"10PULSOS.h"



void CONF_OSC(void);
void CONF_PUERTOS(void);
void CONF_USART(void);
void RESET_USART(void);
void RUTINA_ATND (void);
void RUTINA_ENVIAR_DATO (void);
void CONF_XBEE (void);
void DEFINIR_VARIABLES (void);
void RUTINA_NADA (void);



unsigned char DATO[245];
unsigned char AA[6]= {'h','o','l','a',13};
unsigned char k,ZZ;
unsigned char WWW,STOP,NADA;



void main (void)

{
	
	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();








	while(PORTCbits.RC0)
	
	{

	OSCILADOR_10_PULSOS();

	TXREG2= 'A';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'T';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'N';	// +	

	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'D';	// +


	

	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);	

	
	TXREG2= 0X2B;	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 0X2B;	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 0X2B;	// +
//
//
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
//	Delay10KTCYx(200);
//
//	TXREG2= 'A';	// +
//	Delay1KTCYx(40);	// 10ms
//	
//	TXREG2= 'T';	// +
	Delay1KTCYx(40);	// 10ms
//	
//	TXREG2= 'N';	// +	
//
	Delay1KTCYx(40);	// 10ms
//	
//	TXREG2= 'D';	// +
//

	Delay1KTCYx(40);	// 10ms
	
//	TXREG2= 0X0D;	// +

	DEFINIR_VARIABLES();


	TXREG2= 'A';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'T';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'N';	// +	

	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'D';	// +

	Delay10KTCYx(40);	// 10ms

	TXREG2= 0X0D;	// +

	RUTINA_ATND();



	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);



		TXREG2= 'A';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'T';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'C';	// +	

	Delay10KTCYx(40);	// 10ms
	
	TXREG2= 'N';	// +

	Delay10KTCYx(40);	// 10ms

	TXREG2= 0X0D;	// +


	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);



//	RUTINA_ATND();
//	Delay10KTCYx(40);	// 10ms
//	LATBbits.LATB4 = 1;


	RUTINA_ENVIAR_DATO();

	}	



	Delay10KTCYx(1);		// Retardo de 200 miliSeg para que pase el rebote

	while(~PORTCbits.RC0)	// Espera a que suelte
	{		


	}

	CONF_XBEE();	
	
	
}



void CONF_OSC(void)
{
// Frecuencia del oscilador interno = 16MHZ

	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	OSCCONbits.IRCF0=1;
} 

//----------------------------------

void CONF_PUERTOS(void)

{
			//76543210

	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones

	TRISB =  0b11000111; // RB1 = SCL2  y RB2 = SDA2 ; RB0 = INTO
	LATB  = 0;
	ANSELB = 0b00000000;

	TRISC = 0b11011001; // RC3 = SCL1  y RC4 = SDA1 , RC6=TX1 y RC7=RX1 =1
	ANSELC = 0b00000000;

	LATC  = 0;

}	

//----------------------------------------------------------------------


void CONF_USART(void)
{

	SPBRGH2 = 0b00000001;					// Parte para configurar la velocidad del baudio
	SPBRG2  = 0b10100000;				// Para configurar la velocidad del baudio en 9600
	
	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones
//               76543210
	TXSTA2 =   0b00100110;
	RCSTA2 =   0b10010000;
	BAUDCON2 = 0b00001000;

	SPBRGH1 = 0b00000001;					// Parte para configurar la velocidad del baudio
	SPBRG1 =  0b10100000;				// Para configurar la velocidad del baudio en 9600
	
	
//               76543210
	TXSTA1 =   0b00100110;
	RCSTA1 =   0b10010000;
	BAUDCON1 = 0b00001000;

	PIR3bits.RC2IF = 0;
	PIR1bits.RC1IF = 0;


}


//---------------------------------------------------------------------------------------

void RESET_USART(void)

{

	TXSTA2bits.TXEN = 0;		//DH la transmision	
	RCSTA2bits.SPEN = 0;		//DH los puertos
	RCSTA2bits.CREN = 0;		//DH la recepcion
	TXSTA1bits.TXEN = 0;		//DH la transmision	
	RCSTA1bits.SPEN = 0;		//DH los puertos
	RCSTA1bits.CREN = 0;		//DH la recepcion	

	TXSTA2bits.TXEN = 1;		//DH la transmision	
	RCSTA2bits.SPEN = 1;		//DH los puertos
	RCSTA2bits.CREN = 1;		//DH la recepcion
	TXSTA1bits.TXEN = 1;		//DH la transmision	
	RCSTA1bits.SPEN = 1;		//DH los puertos
	RCSTA1bits.CREN = 1;		//DH la recepcion	

}

//------------------------------------------------------------

void RUTINA_ATND (void)
{

	k= RCREG2; 
	k=0;

while (STOP)

	{

	
		if(RCSTA2bits.OERR)
		{RCSTA2bits.CREN = 0;
		 RCSTA2bits.CREN = 1;}

		if(PIR3bits.RC2IF)
		{
			DATO[k] = RCREG2;
			if ( DATO[k] == 0x0D)
			{
				if(WWW == 2)
				{
					STOP = 0;
					k = k+1;
				}
				if(WWW == 1)
				{
					WWW = 2;
					k = k+1;
				}
				if(WWW == 0)
				{
				
					WWW = 1;
					k = k+1;
				}

			}
			else
			{
				k = k+1;
				WWW=0;
			}
		}
	}
}


//-----------------------------------------------------


	void RUTINA_ENVIAR_DATO (void)
{

	STOP =1;
	ZZ=k;
	k=0;


	while(STOP)

	{

	
		for(k=0;k<ZZ;k++)
		{
			TXREG1 = DATO[k];
			Delay10KTCYx(40);
		}
		STOP = 0;

		if ( DATO[0] == 0x0D)
		{ RUTINA_NADA();}
		
	}

}	



///////----------------------------------------------------------------




void CONF_XBEE (void)

{

	unsigned char l,p;


 while(1){

			if(PIR1bits.RC1IF)
			{
				l=RCREG1;
				LATBbits.LATB4 = ~LATBbits.LATB4;
				TXREG2= l;

			}

			if(PIR3bits.RC2IF)

			{
				p=RCREG2;
				LATBbits.LATB4 = ~LATBbits.LATB4 ;
				TXREG1 = p;

			}
		}		
}



//-------------------------------------------

	void DEFINIR_VARIABLES (void)


{

	STOP=1;
	WWW=0;
	DATO[245]=0;
	k= RCREG2; 
	k=0;
	NADA=0;

}


//--------------------------------------------


	void RUTINA_NADA (void)

{

	TXREG1= 'N';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG1= 'o';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG1= 32;	// +	

	Delay10KTCYx(40);	// 10ms
	
	TXREG1= 'D';	// +
	Delay10KTCYx(40);	// 10ms

	TXREG1= 'A';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG1= 'T';	// +
	Delay10KTCYx(40);	// 10ms
	
	TXREG1= '0';	// +	

	Delay10KTCYx(40);	// 10ms
	
	TXREG1= 13;	// +
}

