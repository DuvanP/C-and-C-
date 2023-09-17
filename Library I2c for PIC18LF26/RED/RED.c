


#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>



void CONF_OSC(void);
void CONF_PUERTOS(void);
void CONF_USART(void);
void RESET_USART(void);
void RUTINA_ATND (void);
void RUTINA_ENVIAR_DATO (void);


unsigned char i,j,x1,x2,x3;
unsigned char DATO[245];
unsigned char k,ZZ;
unsigned char WWW,STOP;
unsigned char ATND[5]={'A','T','N','D',0x0D};


void main (void)

{
	
	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();

	i=0;
	j=0;
	k=0;
	STOP=1;
	WWW=0;
	x1=0;
	x2=0;
	x3=0;
	DATO[245]= 0;

		PORTCbits.RC0 = 1;

	while(1)
	{
	while(PORTCbits.RC0)
	{

			


		if(PIR1bits.RC1IF)
			{
				i=RCREG1;
				LATBbits.LATB4 = ~LATBbits.LATB4;
				TXREG2= i;

			}

		if(PIR3bits.RC2IF)

			{
				j=RCREG2;
				LATBbits.LATB4 = ~LATBbits.LATB4 ;
				TXREG1 = j;
		//		retardo();

			}


	}

		Delay10KTCYx(1);		// Retardo de 200 miliSeg para que pase el rebote

	while(~PORTCbits.RC0)	// Espera a que suelte
	{}
		
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);	

	
	TXREG2= 0X2B;	// +
	Delay1KTCYx(1);	// 10ms
	
	TXREG2= 0X2B;	// +
	Delay1KTCYx(1);	// 10ms
	
	TXREG2= 0X2B;	// +

	Delay1KTCYx(1);	// 10ms	
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);	



//	x1 = RCREG2;
//	while(PIR3bits.RC2IF ==0){}
//	x2 = RCREG2;
//	while(PIR3bits.RC2IF ==0){}
//	x3 = RCREG2;
//	while(PIR3bits.RC2IF ==0){}

	Delay1KTCYx(40);	// 10ms


//	TXREG1= x1;	// +
//	Delay1KTCYx(40);	// 10ms
//	
//	TXREG1= x2;	// +
//	Delay1KTCYx(40);	// 10ms
//	
//	TXREG1= x3;	// +


	TXREG2= 'A';	// +
	Delay1KTCYx(40);	// 10ms
	
	TXREG2= 'T';	// +
	Delay1KTCYx(40);	// 10ms
	
	TXREG2= 'N';	// +	

	Delay1KTCYx(40);	// 10ms
	
	TXREG2= 'D';	// +


	Delay1KTCYx(40);	// 10ms
	
	TXREG2= 0X0D;	// +

	

	RUTINA_ATND();


	RESET_USART();

	RUTINA_ENVIAR_DATO();

	

	


	}		
	
	
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

	TRISC = 0b11011000; // RC3 = SCL1  y RC4 = SDA1 , RC6=TX1 y RC7=RX1 =1
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

	STOP=1;

while (STOP)

	{
		if(PIR3bits.RC2IF)
		{
			DATO[k] = RCREG2;
			if ( DATO[k] == 0x0D)
			{
				if(WWW == 2)
				{
					STOP = 0;
				}
				if(WWW == 1)
				{
					WWW = 2;
				}
				if(WWW == 0)
				{
					WWW = 1;
				}
				k++;
			}
			else
			{
				k++;
				W=0;
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
		if(k == ZZ)
		{	
			STOP = 0;
		}
		else
		{
			TXREG1 = DATO[k];
			k++;
		}

	}

}	