
/*********************************************
 USART1 TX on STM32 is at pin A9, RX is at pin
 A10
==========STM32===========CP210x==============
           GND------------GND pin
   pin A9  TX-------------RX  pin
   pin A10 RX-------------TX  pin
 *********************************************/
 
////////////////////// INCLUDES //////////////////////////////
#include "stm32f10x.h"                  // Device header
#include "printMsg.h"										//aka serial mornitor
////////////////////// END INCLUDES //////////////////////////


////////////////////// DEFINES //////////////////////////////

#define delay 	for(int i =0;i<500000;i++);

////////////////////// END DEFINES  /////////////////////////


int i;								//global variable i
char buffer [255];		//buffer for messages

int main(void)
{
	//////////////////// SETUP ////////////////////////
	
	//gpio A clock enabled //enabling  USART1
	

	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;		

	
	//pin konfiguration for uart rx/tx
	
	//PA9 TX pin Alternative push pull 50MHz output  -> 1011
	
	GPIOA->CRH |=GPIO_CRH_MODE9 |GPIO_CRH_CNF9_1;
	GPIOA->CRH &=~GPIO_CRH_CNF9_0;      
	
	//PA10 RX pin floating input  -> 0100 //default state of GPIO
	
	
	//badurate setting 9600 Kbps
	
	//     --------   BUSCLOCK/(16*DESIRE_USART_SPEED) -> 72MHZ/(16*9600) ->468.75
	
	//468->1D4   dec->hex
	//0.75 * 16 = 12-> C
	//468.75=0x14DC
	
	USART1->BRR=0x1D4C;


	//enable RX enable TX UART enable in CR1 register
	
	USART1->CR1 |=USART_CR1_RE| USART_CR1_TE | USART_CR1_UE; 

	
	
	//////////////////// END SETUP ////////////////////

//////////////////// LOOP ////////////////////
	while(1)
	{
		i++;
		println("hallo %d  -  %X \n", i, i);    //print message with arguments
		delay;
	
	}

//////////////////// END LOOP ////////////////////
}
