
#include<p18lf26k22.h>
#include<delays.h>
#include<stdio.h>


void CONF_XBEE (void);


void CONF_XBEE (void)

{
	unsigned char l,p;

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
