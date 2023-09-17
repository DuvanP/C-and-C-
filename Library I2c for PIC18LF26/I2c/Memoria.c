
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

void WMEMORY (void);




//----VAriables Globales

unsigned char AA [10] = {'H','O','L','A',32,'M','U','N','D','O'};
unsigned char BB [10] = {'H','O','L','A',32,'P','A','S','T','A'};






//-------------------------------------------------

void main (void)

{

	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();
	CONF_MSSP();
	OSCILADOR_10_PULSOS();
	WMEMORY();
	
		while(1)
		{

		}




}
	
	

//------------------------------------------------------------------------------------------------------------

void WMEMORY (void)

{
	unsigned char n=3;
	unsigned char j=0;

	STARTI2C2();
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C2(0xA0);			// Direccion de la memoria 
	Delay100TCYx(n);			// 75us
		
	ESCRIBIRI2C2(0x00);			// direccion parte alta
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C2(0x64);			// direccion parte baja  = direccion 100
	Delay100TCYx(n);			// 75us


	for (j=0;j<10;j++)
	
		{

	ESCRIBIRI2C2(AA[j]);		// transmición datos
	Delay100TCYx(n);			// 75us
			
		}


	STOPI2C2();					// STOP
	Delay100TCYx(n);			// 75us





}




