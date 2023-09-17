

#include<p18lf26k22.h>
#include<delays.h>


	void RETARDO(void);
	
	void RETARDO(void)

{	
	unsigned char p;

	for(p=0;p<10;p++)
	{
	 	Delay10KTCYx(20);
	}
}
