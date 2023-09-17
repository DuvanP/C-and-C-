
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


void CONF_INTER(void);
void CONF_RTC (void);
void HDELRELOJ (void); 
void OTP_FUNCTION (void);




//----VAriables Globales





//-------------------------------------------------

void main (void)

{

	CONF_OSC();
	CONF_PUERTOS();
	CONF_USART();
	CONF_MSSP();
	CONF_INTER();
	OSCILADOR_10_PULSOS();
	OTP_FUNCTION();
	Delay10KTCYx(250);
	CONF_RTC();
	Delay10KTCYx(250);



	while(1)
	{
	OSCILADOR_10_PULSOS();

	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	Delay10KTCYx(200);
	HDELRELOJ();	
	OSCCONbits.IDLEN=0;
	LATBbits.LATB4 = 0;
	Sleep();
	OSCCON = 0b01111110;

		
	}



}






//----------------------------------
// Rutina que configura la INTERRUP
// por flanco ascendente
void CONF_INTER(void)
{
	// Deshabilita prioridades
	RCONbits.IPEN = 0;
	
	// Habilita la Int por flanco en RB0
			 //76543210
	INTCON = 0b10010000;

	// Establece flanco de Subida
	INTCON2bits.INTEDG0 = 0;
	
	INTCONbits.GIE = 1;		// Habilita de manera global todas las interrupciones
}	

////----------------------------------
//
//// Inicio del manejo de interrupciones en la
//// Posicion de memoria 0x08
//
//#pragma code VECTOR_INTER_ALTA = 0x08 // Indica la dirección de la ROM donde esta el vector ALTO
////#pragma interrupt VECTOR_INTER_ALTA   // Le indica al compilador que es una funcion para atender 
//									  // una interrupción y salva el contexto
//void VECTOR_INTER_ALTA(void)
//{ 
//  _asm
//    goto ISR //Salte al manejador de interrupciones
//  _endasm
//}
//
////----------------------------------
//
//#pragma code 			// retorna a la sección anterior en la ROM
//#pragma interrupt ISR	// Le indica al compilador que es una funcion para atender 
//						// una interrupción y salva el contexto
//
////----------------------------------
//void ISR (void)
//{
//	
//	OSCCONbits.SCS0=1;
//	OSCCONbits.SCS1=0;
//	
//	OSCCONbits.IRCF1=1;
//	OSCCONbits.IRCF2=1;
//	OSCCONbits.IRCF0=1;
//	main();
//
//	INTCONbits.INT0IF = 0;
//	
//
//
////if (INTCONbits.TMR0IF)
//    {                                   //check for TMR0 overflow
////      INTCONbits.TMR0IF = 0;            //clear interrupt flag
////      Flags.Bit.Timeout = 1;            //indicate timeout
////      LATBbits.LATB0 = !LATBbits.LATB0; //toggle LED on RB0
//    }
//}


void CONF_RTC (void)

{
	unsigned char n=1;

	STARTI2C1();
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0xA2);			// Direccion del RTC 
	Delay100TCYx(n);			// 75us
		
	ESCRIBIRI2C1(0x10);			// direccion del registro WDTF
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0x02);			// DH WDTF 
	Delay100TCYx(n);			// 75us
	STOPI2C1();					// STOP
	Delay100TCYx(n);			// 75us

	STARTI2C1();
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0xA2);			// Direccion del RTC 
	Delay100TCYx(n);			// 75us
		
	ESCRIBIRI2C1(0x00);			// direccion primer registro 00h
	Delay100TCYx(n);			// 75us


	//XXXXXXXXXXX    CONF TODOS LOS REGISTROS  XXXXXXXXXXX
	
	ESCRIBIRI2C1(0x20);			// CONF CONTROL_1
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0x00);			// CONF CONTROL_2 DH interrupciones de alarma
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0xE0);			// CONF CONTROL_3
	Delay100TCYx(n);			// 75us

	//XXXXXXXXXXX    CONF DE HORA Y FECHA     XXXXXXXXXXX 

// 01:01:01 del dia 1
// lUNES, ENERO , del año 1
	

	ESCRIBIRI2C1(0x01);			// 1 SEGUNDO
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 1 MINUTO
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 1 HORA
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 1 DIA
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// LUNES
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// ENERO
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// AÑO 1
	Delay100TCYx(n);			// 

	//XXXXXXXXXXX    CONF DE LA ALARMA  XXXXXXXXXXX

// Cada minuto 5 del ciclo
// de minutos, la alarma se
// activara

	ESCRIBIRI2C1(0x20);			// Alarma SEG Habilitada a 20 seg
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x81);			// Alarma MIN DH
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x81);			// Alarma HORA DH
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x81);			// Alarma DIA DH
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x81);			// Alarma WEEKDAY DH
	Delay100TCYx(n);			// 
	

	//XXXXXXXXXXX    CONF DE CLKOUT  XXXXXXXXXXX

	ESCRIBIRI2C1(0x07);			// Alarma SEG DH
	Delay100TCYx(n);			// 
	

	//XXXXXXXXXXX    CONF DE WDTF  XXXXXXXXXXX

	
	ESCRIBIRI2C1(0x02);			// DH WDTF
	Delay100TCYx(n);			// 	
	ESCRIBIRI2C1(0x01);			// CONF periodo WDTF
	Delay100TCYx(n);			// 


	//XXXXXXXXXXX    CONF DE TIMESTAMP  XXXXXXXXXXX

	ESCRIBIRI2C1(0x40);			// DH TIMESPTAMP F
	Delay100TCYx(n);			// 		

	ESCRIBIRI2C1(0x01);			// 13h
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 14h
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 15h
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 16h
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 17h
	Delay100TCYx(n);			// 
	ESCRIBIRI2C1(0x01);			// 18h
	Delay100TCYx(n);			// 


	//XXXXXXXXXXX    CONF DE AGING_OFSET  XXXXXXXXXXX

	
	ESCRIBIRI2C1(0x08);			// SIN coRReccion 
	Delay100TCYx(n);			// 
	STOPI2C1();					// STOP
	Delay100TCYx(n);			// 75us



}



void HDELRELOJ (void)

{
	unsigned char n=3;
	STARTI2C1();
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0xA2);			// Direccion del RTC 
	Delay100TCYx(n);			// 75us
		
	ESCRIBIRI2C1(0x00);			// direccion del registro CONTROL_1
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0x00);			// Habilita el STOP
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0x02);			// Habilita el INT por alarma
	Delay100TCYx(n);			// 75us

	STOPI2C1();					// STOP
	Delay100TCYx(n);			// 75us
}


//--------------------------------------------------

void OTP_FUNCTION (void)

{


	unsigned char n=3;

	STARTI2C1();
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0xA2);			// Direccion del RTC 
	Delay100TCYx(n);			// 75us
		
	ESCRIBIRI2C1(0x0F);			// direccion del registro CLkout
	Delay100TCYx(n);			// 75us
	ESCRIBIRI2C1(0x27);			// OTP active 
	Delay100TCYx(n);			// 75us
	STOPI2C1();					// STOP
	Delay100TCYx(n);			// 75us

}

