

#include<p18lf26k22.h>


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  LIBRERIA I2C Por DUvan PUerto xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


// Declaracion de funciones 

 
void STARTI2C2	 (void);
void STOPI2C2  	 (void);
void ESCRIBIRI2C2 (unsigned char);
void RSTARTI2C2 	 (void);
unsigned char RECIBIRI2C2 (void);
void ACKI2C2 	 (void);
void NOTACKI2C2 	 (void);

void STARTI2C1	 (void);
void STOPI2C1  	 (void);
void ESCRIBIRI2C1 (unsigned char);
void RSTARTI2C1 	 (void);
unsigned char RECIBIRI2C1 (void);
void ACKI2C1 	 (void);
void NOTACKI2C1 	 (void);



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXX    LIBRERIA I2C   XXXXXX  DUVAN PUERTO  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

 void STARTI2C2 (void)
{PIR3bits.SSP2IF = 0; SSP2CON2bits.SEN = 1; while(PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*
void STOPI2C2 (void)
{ 	PIR3bits.SSP2IF = 0; SSP2CON2bits.PEN = 1;while (PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 void ESCRIBIRI2C2 (unsigned char DATO)
{PIR3bits.SSP2IF = 0; SSP2BUF = DATO; while(PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 void RSTARTI2C2 (void)
{PIR3bits.SSP2IF = 0; SSP2CON2bits.RSEN = 1; while(PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 unsigned char RECIBIRI2C2 (void)
{	unsigned char DATO_RECEP = 0;
	PIR3bits.SSP2IF = 0; SSP2CON2bits.RCEN = 1;// HABILITA LA RECEPCION
	while (PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0; DATO_RECEP = SSP2BUF;
	return DATO_RECEP;}
//*--------------------------------------------------------------------------------------------------*
 void ACKI2C2 (void)
{	PIR3bits.SSP2IF = 0; SSP2CON2bits.ACKDT = 0; SSP2CON2bits.ACKEN = 1;
	while (PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*
void NOTACKI2C2 (void)
{   PIR3bits.SSP2IF = 0; SSP2CON2bits.ACKDT = 1; SSP2CON2bits.ACKEN = 1;
	while (PIR3bits.SSP2IF == 0){} PIR3bits.SSP2IF = 0;}
//*--------------------------------------------------------------------------------------------------*




//*****************************************************************************************************
//*************************** MODULO 1*****************************************************************
//*****************************************************************************************************


 void STARTI2C1 (void)
{PIR1bits.SSP1IF = 0; SSP1CON2bits.SEN = 1; while(PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*
void STOPI2C1 (void)
{ 	PIR1bits.SSP1IF = 0; SSP1CON2bits.PEN = 1;while (PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 void ESCRIBIRI2C1 (unsigned char DATO)
{PIR1bits.SSP1IF = 0; SSP1BUF = DATO; while(PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 void RSTARTI2C1 (void)
{PIR1bits.SSP1IF = 0; SSP1CON2bits.RSEN = 1; while(PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*
 unsigned char RECIBIRI2C1 (void)
{	unsigned char DATO_RECEP = 0;
	PIR1bits.SSP1IF = 0; SSP1CON2bits.RCEN = 1;// HABILITA LA RECEPCION
	while (PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0; DATO_RECEP = SSP1BUF;
	return DATO_RECEP;}
//*--------------------------------------------------------------------------------------------------*
 void ACKI2C1 (void)
{	PIR1bits.SSP1IF = 0; SSP1CON2bits.ACKDT = 0; SSP1CON2bits.ACKEN = 1;
	while (PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*
void NOTACKI2C1 (void)
{   PIR1bits.SSP1IF = 0; SSP1CON2bits.ACKDT = 1; SSP1CON2bits.ACKEN = 1;
	while (PIR1bits.SSP1IF == 0){} PIR1bits.SSP1IF = 0;}
//*--------------------------------------------------------------------------------------------------*

