/*
seting up uart for basic communication. 
No remaping RX / TX line -> PA10/PA9.
aka println function

*/

////////////////////// INCLUDES //////////////////////////////
#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdint.h>
#include "string.h"											//string lib
#include "stdlib.h"											//standarad functions lib
#include "stdarg.h"											//standard arguments lib
///////////////////////////////////////////////////////////

////////////////////// DEFINES //////////////////////////////

#define delay 	for(int i =0;i<500000;i++);

///////////////////////////////////////////////////////////

///////////////////// PROTOTYPES ///////////////////////////

static void println(char *msg, ...);

///////////////////////////////////////////////////////////


char data;

long int i;

int main(void)
{
	//gpio A clock enabled
	
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;		//clock Port A

	
	//enabling  USART1
	
	RCC->APB2ENR |=RCC_APB2ENR_USART1EN; //USART1 enable
	
	
	//pin konfiguration for uart rx/tx
	//PA9 TX pin Alternative push pull 50MHz output  -> 1011
	
	GPIOA->CRH |=GPIO_CRH_MODE9;				//0x00000030 -> 0011
	GPIOA ->CRH |= GPIO_CRH_CNF9_1;			//0x00000080 -> 1000
	GPIOA->CRH &=~GPIO_CRH_CNF9_0;      //0x00000040 -> 0100
	
	//PA10 RX pin floating input  -> 0100 //default state of GPIO
	
	
	//badurate setting 9600 Kbps
	
	//     --------   BUSCLOCK/(16*DESIRE_USART_SPEED) -> 72MHZ/(16*9600) ->468.75
	
	//468->1D4   dec->hex
	//0.75 * 16 = 12-> C
	//468.75=0x14DC
	
	USART1->BRR=0x1D4C;


	//enable RX enable TX UART enbale in CR1 register
	
	USART1->CR1 |=USART_CR1_RE; 				//RX enable, receive data enabled
	USART1 ->CR1 |=USART_CR1_TE;				//TX, enabled,  transmite data enabled
	USART1->CR1 |=USART_CR1_UE;					//USART enabled
	
	// turn off led C13
  GPIOC->BSRR=(1<<13);
	
	while(1)
	{
			i++;
		println("zdravo svijete po %i puta! \n", i);

		delay;
	
	}
	
}
static void println(char *msg, ...)
{

		char buffer[100];					//make a 100 byte buffer
	
	va_list args; 							// get the list of arguments
	va_start(args,msg);					// extract argumest from message, reformating the message
	vsprintf(buffer,msg,args);	//formating message acording to passed arguments
	
	//fill the buffer
	
	for(int i=0; i<strlen(buffer); i++)
	{
		USART1->DR=buffer[i];									//byte by byte filing saljem podatake sa TX
		
		while(!(USART1->SR & USART_SR_TXE)); //fill the array until the TX registar is empty
		
	}
}
