/* 
 * File:   key.c
 * Author: Козырев С.А.
 *  22.06.15 d:\bp
 * pic16f584 блок управления БП
 * написание под MPLAB X8C на 
 * PICkit2
 * 
 * 
 * 
 * V1.0 22.06.15
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <xc.h> 					// include standard header file


// set Config bits
//#pragma config FOSC=INTOSCIO,  WDTE=OFF, MCLRE=ON  //PLLEN=OFF,
//#pragma config BOREN=OFF,CP=OFF, CPD=OFF  //CLKOUTEN=OFF, IESO=OFF, FCMEN=OFF,
//#pragma config PWRTE=OFF   //,STVREN=ON,BORV=LO,LVP=OFF


#define ON     				0x01 
#define OFF     			0x0

unsigned char RB0_NEW,RB1_NEW,RB2_NEW,RB3_NEW;
unsigned char RB0_OLD,RB1_OLD,RB2_OLD,RB3_OLD;
unsigned char flag_RB0,flag_RB1,flag_RB2,flag_RB3;
unsigned char RB0_A,RB1_A,RB2_A,RB3_A;
unsigned char sek, first,pb;
unsigned char sek_1,sek_2,flag_sek_1,flag_sek_2,flag_t2;
unsigned char flag2=0;
unsigned char flag3 = 0;

	void interrupt Interrupt() {
			if (RBIF  == 1 )  //////////////////// ВТОРОЙ ТАЙМЕР
				{
				
					pb = PORTB;
					  RB0_NEW = RB0;
					  RB1_NEW = RB1;
					  RB2_NEW = RB2;
					  RB3_NEW = RB3;
					  TMR2ON = 1;	
					  RBIE = 0;
					RBIF  = 0;	
				}	
			if (TMR2IF  == 1 )  //////////////////// ВТОРОЙ ТАЙМЕР
				{
				TMR2ON = 0;	
				TMR2 = 0;
				RBIE = 1;
				flag_t2 =1;
				TMR2IF  = 0;	
				}	
			if (TMR1IF  == 1 )  //////////////////// ВТОРОЙ ТАЙМЕР
				{
					sek++;
					//RA0 =~RA0;
					if ((sek >= 200) & (flag_sek_1))   //20
						{sek_1 = ON;
							sek = 0;
							TMR1ON = 0;
							TMR1H = 0;
							TMR1L =  0;
							
						}
					if ((sek >= 10) & (flag_sek_2))
					{
						sek_2 = ON;
						sek = 0;
						TMR1ON = 0;
						TMR1H = 0;
						TMR1L =  0;
					}
				TMR1IF  = 0;	
				}	
			if (C1IF  == 1 )  //////////////////// ПЕРВЫЙ КОМПАРАТОР
				{
					asm("nop");
					C1IF  = 0;	
				}		
}

	void otkl(void)
	{
		RBIE = 0;
		RA1 = 1;
		TMR1ON = 1;
		flag_sek_2 = ON;
		while (!sek_2);
				flag_sek_2 = OFF;
		sek_2 = OFF;
		first = OFF;
		RA1 = 0;
		RBIE = 1;
	}
	
	void vkl(void)
	{
		RBIE = 0;
		RA0 = 1;
		TMR1ON = 1;
		flag_sek_2 = ON;
		while (!sek_2);
					flag_sek_2 = OFF;
		sek_2 = OFF;
		first = 1;
		RA0 = 0;
		RBIE = 1;
	}
	void kuku(void)
	{								//RB3_A
		if (RB3_NEW==1)
			{
				if (RB3_OLD==1)
					{
						asm("nop");
					}
				else
					{
						RB3_A = 1;
					}	
			}
		else
			{
				if (RB3_OLD==1)
					{
						RB3_A = 0;
					}
				else
					{
						asm("nop");
					}		
			}
		if (RB2_NEW==1)
			{
				if (RB2_OLD==1)
					{
						asm("nop");
					}
				else
					{
						RB2_A = 1;
					}	
			}
		else
			{
				if (RB2_OLD==1)
					{
						RB2_A = 0;
					}
				else
					{
						asm("nop");
					}		
			}	
			if (RB1_NEW==1)
			{
				if (RB1_OLD==1)
					{
						asm("nop");
					}
				else
					{
						RB1_A = 1;
					}	
			}
		else
			{
				if (RB1_OLD==1)
					{
						RB1_A = 0;
					}
				else
					{
						asm("nop");
					}		
			}
			if (RB0_NEW==1)
			{
				if (RB0_OLD==1)
					{
						asm("nop");
					}
				else
					{
						RB0_A = 1;
					}	
			}
		else
			{
				if (RB0_OLD==1)
					{
						RB0_A = 0;
					}
				else
					{
						asm("nop");
					}		
			}
	}
	void video(void)
	{
		if (RB0_A == 3)
			{asm("nop");}
		else if (RB0_A == 1)				// &&&&&&& клавиша звук отпущена &&&&&&&
		  	{	RB0_A =3;
			RB0_OLD = RB0_NEW;
			 // stop_u = 0;
			}
		else if (RB0_A == 0)				// ::::::: нажата как минимум клавиша звук ::::::::::
			{ 
			RB0_A = 3;
			RB0_OLD = RB0_NEW;
			if (!flag_RB0)
				flag_RB0 = ON;
			
			//stop_u = 1;
			}
		//////////////////////////////////////////////////////////////////////////////////////////	
		if (RB1_A == 3)
			{asm("nop");}
		else if (RB1_A == 1)				// &&&&&&& клавиша удар отпущена &&&&&&&
		  	{	RB1_A =3;
			RB1_OLD = RB1_NEW;
			 // stop_u = 0;
			}
		else if (RB1_A == 0)				// ::::::: нажата как минимум клавиша удар ::::::::::
			{ 
			RB1_A = 3;
			RB1_OLD = RB1_NEW;
			if (!flag_RB1)
				flag_RB1 = ON;
		
			//stop_u = 1;
			}
		///////////////////////////////////////////////////////////////////////////////////////////		
		if (RB2_A == 3)
			{asm("nop");}
		else if (RB2_A == 1)				// &&&&&&& клавиша откл отпущена &&&&&&&
		  	{	RB2_A =3;
				RB2_OLD = RB2_NEW;
			 // stop_u = 0;
			}
		
		else if (RB2_A == 0)				// ::::::: нажата как минимум клавиша откл ::::::::::
			{ 
			RB2_A = 3;
			RB2_OLD = RB2_NEW;
			if (!flag_RB2)
				flag_RB2 = ON;
			
			//otkl();//stop_u = 1;
			}
		///////////////////////////////////////////////////////////////////////////////////////////		
		if (RB3_A == 3)
			{asm("nop");}
		else if (RB3_A == 1)				// &&&&&&& клавиша вкл отпущена &&&&&&&
		  	{	RB3_A =3;
				RB3_OLD = RB3_NEW;
			 // stop_u = 0;
			}
		else if (RB3_A == 0)				// ::::::: нажата как минимум клавиша вкл ::::::::::
			{ 
			RB3_A = 3;
			RB3_OLD = RB3_NEW;
			if (!flag_RB3)
				flag_RB3 = ON;
			//vkl();
			//stop_u = 1;
			}	
	}

int main(int argc, char** argv) {

		SCS = 1;
		IRCF2 = 0x1; //OSCCONbits.IRCF2 = 0x1;  // bits.IRCF
		IRCF1 = 0x1;//OSCCONbits.IRCF1 = 0x1;
		IRCF0 = 0x0;//OSCCONbits.IRCF0 = 0x0;
	//	C1ON =0;
	//	C2ON = 0;
		PORTB  = 0;
//WPUB = 0XF;
	//	CMCON0 = 0x07;
		ANSELH  = 0;
		//ANS0 = 1;
		TRISB0 = 1;
		TRISB1 = 1;
		TRISB2 = 1;
		TRISB3 = 1;
		TRISB6 = 0;
		TRISB7 = 0;
		IOCB0 = 1;
		IOCB1 = 1;
		IOCB2 = 1;
		IOCB3 = 1;
		PORTC  = 0;
	//	TRISC = 0;
	//	TRISC1 = 0;
	
		PORTA=0;
		ANSEL =0;
		TRISA0 = 0;
		TRISA1 = 0;
		TRISA7 = 0;
		TRISA5 = 0;
		
		PORTC = 0;
		TRISC4 = 0;   // электромагнит
		TRISC6 = 0;   // электромагнит
		TRISC0 = 0; 
		TRISC1 = 0; 
		TRISC2 = 0; 
		TRISC4 = 0; 
		//  ----------------------------------
		// REF настройка 
		//
		/*
		VR0 = 1;
		VR1 = 1;
		VR2 =  0;
		VR3 = 0;
		
		VRSS = 0;
		VRR = 1;
		VROE = 0;
		VREN =1;  */
	  //DELAY  !!!!!!
	//	---------------------------------------
	
	//  ---------------------------------------
	//  коипаратор
	//
	/*
		C1ON = 1;
	  C1OE = 0;   // ВНУТРЕННИЙ ВЫХОД
	  C1R = 1; 
	  C1CH0 = 0;  //AN0  C12IN0
	  C1CH1 = 0;
	  C1OUT = 	0;
	  C1POL = 1;
	*/
	
	
	//  ---------------------------------------
	
	
		//RA0 = 0;
		//RA0 = 1;
		//RA0 = 0;
		//	RA1 = 0;
		//RA1 = 1;
		//RA1 = 0;
		sek = 0;
		flag_sek_1 = OFF;
		flag_sek_2 = OFF;
		RB0_NEW = ON;
		RB1_NEW = ON;
		RB2_NEW = ON;
		RB3_NEW = ON;
		
		RB0_OLD = ON;
		RB1_OLD = ON;
		RB2_OLD = ON;
		RB3_OLD = ON;
		RB0_A = 3;
		RB1_A = 3;
		RB2_A = 3;
		RB3_A = 3;
		flag_RB0 = OFF;
		flag_RB1 = OFF;
		flag_RB2 = OFF;
		flag_RB3 = OFF;
		flag_t2 =0;
		flag2=0;
		flag3 = 0;
		T1CKPS0 = 0;
		T1CKPS1 = 0;
		TMR1CS  = 0;
		TMR2ON = 0;
		TMR1ON = 0;
		TMR1H = 0;
		TMR1L =  0;
		TMR2 = 0;
	
		T2CKPS0  =1;
		T2CKPS1=1;  
		TOUTPS3 =1;	
		TOUTPS0  =1;
			TOUTPS1  =0;
			TOUTPS2  =1;
		RBIE = 0;
		GIE  = 1;
		// C1IE = 1;  //
		TMR1IE = 1;
		TMR2IE = 1;
		PEIE = 1;
//	while (1);
/*
		while (1)
		{
			TMR2ON = 1;	
							flag_t2 =0;
		while (flag_t2 ==0);
			RA0 =~RA0;	
		}	
	*//*
				TMR1ON = 1;
				flag_sek_1 = ON;	
		while (!sek_1);
					flag_sek_1 = OFF;
					sek_1 = OFF;
				    TMR1ON = 1;
					RBIE = 1;	
					*/
				//	while(1);
		while (1)
			{   	RBIE = 0;
				kuku();
				video();
					RBIE = 1;
				if (flag_RB2)
				{
					vkl();
					flag_RB2 = OFF;
					first = ON;
				}
				if (flag_RB3)
				{
					otkl();
					flag_RB3 = OFF;
					first = OFF;
				}
				//if (first)
				//{
				if (((flag_RB0) | (flag_RB1))&(first==1)&(!flag2))
					{
						if (!flag2)
							{
								TMR1ON = 1;
								flag_sek_1 = ON;
								flag2=1;
								flag3 = 1;
							}
										//while (!sek_1);
										//flag_sek_1 = OFF;
														//sek_1 = OFF;
														//TMR1ON = 1;
					}
					if ((sek_1)&(flag3==1))
						{
							TMR1ON = OFF;
							TMR1H = 0;
							TMR1L =  0;
							flag_sek_1 = OFF;
							sek_1 = OFF;
							if((flag_RB0) & (flag_RB1))
								{
									otkl();
									first = OFF;	flag2=1;
									flag_RB0 = OFF;
									flag_RB1 = OFF;
								}
							else
								{
									flag_RB0 = OFF;
									flag_RB1 = OFF;
								}
							flag2=0;
							flag3 = 0;
							
							
								
						}
					//}
				//}
			}
}