
#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>
#include<i2c.h>


void CONF_OSC(void);
void CONF_PUERTOS(void);
void ENTER(void);
void retardo(void);
void CONF_USART(void);


unsigned char arraywr[] = {'H','O','L','A','M','U','N','D','O'};
unsigned char arrayrd[20];


//-------------------------------------------------

void main (void)

{

unsigned char DATO_ENVIAR,DATO_LEER,DATO_RECEPCION;
unsigned char D_1,D_2,D_3,i;

	D_1 = 0;
	D_2 = 0;	
	D_3 = 0;
	

	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();
	OpenI2C2(MASTER, SLEW_ON);// Initialize I2C module
 	SSP2ADD = 9; //400kHz Baud clock(9) @16MHz
				//100kHz Baud clock(39) @16MHz
//	SSP1BUF = 0;


		for(i=0;i<10;i++)
	{
		LATBbits.LATB4 = 0;
			retardo();
		LATBbits.LATB4 = 1;
			retardo();
	}				

		i = 'N';	

		LATBbits.LATB4 = 0;
		retardo();
	
//	StartI2C2();
//	WriteI2C2(0xA0);
//	WriteI2C2(0x00);
//	WriteI2C2(0x32);
//	WriteI2C2(0xF0);
//	StopI2C2();
	
//-----------------------------------------------------Rutina para el SHT21
		
	retardo();						//tiempo necesario para que el sensor se prenda y este listo para la operacion


	SSP2CON2bits.SEN = 1;
	while(SSP2CON2bits.SEN == 0){}	    //COndicion de STAR

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3
 
//---------- Envió la condicion STAR ---


	WriteI2C2(0x03);				// Se escribe la direccion del SHT21 y el bit 0 en 0 para escritura

	while(SSP2CON2bits.ACKSTAT) {}	// espera el ACK

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3


	retardo(); 						// espero que termine la medicion 

	SSP2CON2bits.RCEN = 1;			// HABILITA LA RECEPCION

	while (PIR3bits.SSP2IF == 0){}	// Espera a que el sensor envie la informacion testeando la badndera del buffer
	
	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3 - ACA ESTUVO EL ERROR

//----------- Habilita la recepcion y espera que la recepcion finalice

	SSP2BUF = D_1; 					// Lee el dato MSB de la medición del Buffer

	

//----------- Envió El Byte de direccion para Escritura--

	WriteI2C2(0xE5);				// escribe Un comando de medicion de humedad  en modo HOLD MASTER
	
	while(SSP2CON2bits.ACKSTAT){} 	// espera el ACK
	
	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//----------- Envió El Byte de Comando---

	SSP2CON2bits.RSEN = 1;
	while(SSP2CON2bits.RSEN){}	    // vuelve  a enviar la COndicion de reSTAR

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//----------- Envió Condicion de RESTART

	WriteI2C2(0x81);				// escribe La direccion de SHT21 y el bit en 0 en 1 para lectura

	while(SSP2CON2bits.ACKSTAT){} 	// espera el ACK

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//----------- Envió El byte de direccion para lectura

	retardo();

	SSP2CON2bits.RCEN = 1;			// HABILITA LA RECEPCION

	while (PIR3bits.SSP2IF == 0){}	// Espera a que el sensor envie la informacion testeando la badndera del buffer
	
	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3 - ACA ESTUVO EL ERROR

//----------- Habilita la recepcion y espera que la recepcion finalice

	SSP2BUF = D_1; 					// Lee el dato MSB de la medición del Buffer

//----------- Lee lo que esta en el buffer y lo guarda

	SSP2CON2bits.ACKDT = 0;
	SSP2CON2bits.ACKEN = 1;			// inicia  la condicion de ACK hacia el SHT21

	while ( PIR3bits.SSP2IF == 0){}

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//-----------
	retardo();

	SSP2CON2bits.RCEN = 1;			// HABILITA LA RECEPCION

	while (PIR3bits.SSP2IF == 0){}	// Espera a que el sensor envie la informacion testeando la badndera del buffer
	
	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3 - ACA ESTUVO EL ERROR

//-----------

	SSP2BUF = D_2; 					// Lee el dato LSB de la medición del Buffer

//-----------

	SSP2CON2bits.ACKDT = 0;
	SSP2CON2bits.ACKEN = 1;			// inicia  la condicion de ACK hacia el SHT21

	while ( PIR3bits.SSP2IF == 0){}

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//-----------

	retardo();
	SSP2CON2bits.RCEN = 1;			// HABILITA LA RECEPCION

	while (PIR3bits.SSP2IF == 0){}	// Espera a que el sensor envie la informacion testeando la badndera del buffer
	
	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3 - ACA ESTUVO EL ERROR

//-----------

	SSP2BUF = D_1; 					// Lee el dato Checksum del Buffer

//-----------

	SSP2CON2bits.ACKDT = 1;
	SSP2CON2bits.ACKEN = 1;			// inicia  la condicion de NOTACK hacia el SHT21

	while ( PIR3bits.SSP2IF == 0){}

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

//-----------

	SSP2CON2bits.PEN = 1;

	while(SSP2CON2bits.PEN){}		// Inicia la condicion de STOP

	PIR3bits.SSP2IF = 0;			// borra la bandera IF del PIR3

	TXREG2 = 'P';
	TXREG2 = D_1;
	TXREG2 = D_2;
	TXREG2 = D_3;
	TXREG2 = 'Q';

	












		while(1)
		{

		}




}
	
	
//----------------------------------------------------------------------------------

void CONF_OSC(void)
{
// Frecuencia del oscilador interno = 8MHZ

	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	OSCCONbits.IRCF0=1;
} 

//----------------------------------

void CONF_PUERTOS(void)

{
			//76543210

	INTCONbits.GIE = 0;		// Deshabilita de manera global todas las interrupciones

	TRISB = 0b11000110; // RB1 = SCL2  y RB2 = SDA2
	LATB  = 0;
	ANSELB = 0b00000000;

	TRISC = 0b00011000; // RC3 = SCL1  y RC4 = SDA1
	ANSELC = 0b00000000;

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


	
//-------------------------------------------------------------------------

	void retardo(void)

{	
	unsigned char p;

	for(p=0;p<10;p++)
	{
	 	Delay10KTCYx(20);
	}

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



}