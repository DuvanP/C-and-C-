

#include<p18lf26k22.h>
#include<delays.h>




void OSCILADOR_10_PULSOS(void);
void retardo(void);



//----------------------------------




void retardo(void)

{	
	unsigned char p;

	for(p=0;p<10;p++)
	{
	 	Delay10KTCYx(20);
	}

}
void OSCILADOR_10_PULSOS (void)

{
	unsigned char l=0;

		for(l=0;l<10;l++)
	{
		LATBbits.LATB4 = 1;
			retardo();
		LATBbits.LATB4 = 0;
			retardo();
	}

}

