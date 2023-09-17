
#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>
#include"LIBRERIAI2C.h"
#include"ENTER.h"
#include"10PULSOS.h"
#include"RETARDO.h"
#include"CONFIGURACIONES.h"
#include"XCTU.h"
#include"CONVERSORES.h"


//----FUNCIONES QUe Se USARan ----

void SHT21 (void);



//----VAriables Globales


unsigned char D_1=0;  
unsigned char D_2=0;
unsigned char F_1=0;
unsigned char F_2=0;

//-------------------------------------------------

void main (void)

{

	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();
	CONF_MSSP();
	OSCILADOR_10_PULSOS();

	
		while(1)
		{

		SHT21();



		  TXREG2 = ('H');
		  while(TXSTA2bits.TRMT ==0){}

		  TXREG2 = (0x20);
		  while(TXSTA2bits.TRMT ==0){}

		conversorhumedad12(F_1,F_2);

		  TXREG2 = (0x20);
		  while(TXSTA2bits.TRMT ==0){}


		  TXREG2 = ('T');
		  while(TXSTA2bits.TRMT ==0){}

		temperatura14(D_1,D_2);


		  TXREG2 = 13;
		  while(TXSTA2bits.TRMT ==0){}

		
		}




}
	
	

//------------------------------------------------------------------------------------------------------------

void SHT21 (void)

{
//-----------------------------------------------------Rutina para el SHT21
//---------- Envió la condicion START ---

	Delay10KTCYx(36);				// Tiempo necesario (90ms) para que el sensor se prenda y este listo para la operacion						
	STARTI2C2 ();
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0x80);
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0xE3);

//---------- Envió Condicion de RESTART

	RSTARTI2C2 ();
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0x81);

//----------- RECEPCION DATO 1 -----

	Delay10KTCYx(36);				// espera 90ms para el proceso de la medicion
	D_1 = RECIBIRI2C2 ();
	ACKI2C2 ();

//----------- RECEPCION DATO 2 -----

	Delay100TCYx(10);				// espera 250ms para el envio del siguiente byte	
	D_2 = RECIBIRI2C2 ();
	NOTACKI2C2 ();
	Delay100TCYx(10);				// espera 250ms para que SHT21 reconozca el NOTACK
	STOPI2C2 ();

//---------- Envió la condicion START ---

	Delay10KTCYx(36);				// Tiempo necesario (90ms) para que el sensor se prenda y este listo para la operacion						
	STARTI2C2 ();
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0x80);
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0xE5);

//---------- Envió Condicion de RESTART

	RSTARTI2C2 ();
	Delay100TCYx(3);				// 75us
	ESCRIBIRI2C2 (0x81);

//----------- RECEPCION DATO 1 -----

	Delay10KTCYx(36);				// espera 90ms para el proceso de la medicion
	F_1 = RECIBIRI2C2 ();
	ACKI2C2 ();

//----------- RECEPCION DATO 2 -----

	Delay100TCYx(10);				// espera 250ms para el envio del siguiente byte	
	F_2 = RECIBIRI2C2 ();
	NOTACKI2C2 ();
	Delay100TCYx(10);				// espera 250ms para que SHT21 reconozca el NOTACK
	STOPI2C2 ();

}





