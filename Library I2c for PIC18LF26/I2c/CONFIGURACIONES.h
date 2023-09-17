

#include<p18lf26k22.h>
#include<delays.h>


void CONF_OSC(void);
void CONF_PUERTOS(void);
void CONF_USART(void);
void CONF_MSSP (void);





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

	TRISB = 0b11000111; // RB1 = SCL2  y RB2 = SDA2 ; RB0 = INTO
	LATB  = 0;
	ANSELB = 0b00000000;

	TRISC = 0b11011000; // RC3 = SCL1  y RC4 = SDA1 , RC6=TX1 y RC7=RX1 =1
	ANSELC = 0b00000000;

	LATC  = 0;

}	

//----------------------------------------------------------------------


void CONF_USART(void)
{

	SPBRGH2 = 0;					// Parte para configurar la velocidad del baudio
	SPBRG2  = 34;				// Para configurar la velocidad del baudio en 115.200
	
	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones
//               76543210
	TXSTA2 =   0b00100110;
	RCSTA2 =   0b10010000;
	BAUDCON2 = 0b00001000;

	SPBRGH1 = 0;					// Parte para configurar la velocidad del baudio
	SPBRG1  = 34;				// Para configurar la velocidad del baudio en 115.200
	
	
//               76543210
	TXSTA1 =   0b00100110;
	RCSTA1 =   0b10010000;
	BAUDCON1 = 0b00001000;

	PIR3bits.RC2IF = 0;
	PIR1bits.RC1IF = 0;


}

//----------------------------------------------------------------------------------



void CONF_MSSP (void)
{

//	OpenI2C2(MASTER, SLEW_OFF);// Initialize I2C module
// 	SSP2ADD = 39; //400kHz Baud clock(9) @16MHz
//				//100kHz Baud clock(39) @16MHz
//
//	OpenI2C1(MASTER, SLEW_OFF);// Initialize I2C module
// 	SSP1ADD = 39; //400kHz Baud clock(9) @16MHz
//				//100kHz Baud clock(39) @16MHz

			   //76543210
	SSP2STAT = 0b10000000;
	SSP2CON1 = 0b00101000;
	SSP2CON2 = 0b00000000;
	SSP2CON3 = 0b00000000;
	SSP2ADD  = 39;			// 100.000 KHz

	SSP1STAT = 0b10000000;
	SSP1CON1 = 0b00101000;
	SSP1CON2 = 0b00000000;
	SSP1CON3 = 0b00000000;
	SSP1ADD  = 39;			// 100.000 KHz


}


