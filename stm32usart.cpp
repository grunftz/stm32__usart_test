/*
seting up uart for basic communication. 
No remaping RX / TX line -> PA10/PA9.

*/


#include "stm32f10x.h"                  // Device header
#include "string.h"

char data[8];
int i;
int main(void)
{
	//gpio C clock and pin 13 output
	
	RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;		//clock Port C
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;		//clock Port A

	// declare as Output pin 13
	GPIOC->CRH |=GPIO_CRH_MODE13;
	GPIOC->CRH &=~GPIO_CRH_CNF13;
	
	// declare as Output port a pin 0-7
	GPIOA->CRL |=GPIO_CRL_MODE;
	GPIOA->CRL &=~GPIO_CRL_CNF;
	
	//enabling GPIO and USART1

	RCC->APB2ENR |=RCC_APB2ENR_USART1EN; //USART1 enable 1<<14
	
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
	//468.75=0x1D4C
	
	USART1->BRR=0x1D4C; //9600 


	//enable RX enable TX UART enbale in CR1 register
	
	USART1->CR1 |=USART_CR1_RE; 				//RX enable, receive data enabled
	USART1 ->CR1 |=USART_CR1_TE;				//TX, enabled,  transmite data enabled
	USART1->CR1 |=USART_CR1_UE;					//USART enabled
	
	GPIOC->BSRR=(1<<13);
	
	
	while(1)
	{
		//check incoming data
		
		if(USART1->SR &	USART_SR_RXNE) 		//check if data is received
			{
				//for (i=0;i<=10;i++)
				//{
				data[i] = USART1->DR;			//read it and store in data var
				
				
				USART1->DR=data[i];			//send it back
		
					i++;	
				}
				while(!(USART1->SR & USART_SR_TC)){if(i >=8) i=0;};
			
	
			if(data[0]=='0') GPIOA->BSRR=(1<<16);
			if(data[0]=='1') GPIOA->BSRR=(1<<0);
				
			if(data[1]=='0') GPIOA->BSRR=(1<<17);
			if(data[1]=='1') GPIOA->BSRR=(1<<1);
				
			if(data[2]=='0') GPIOA->BSRR=(1<<18);
			if(data[2]=='1') GPIOA->BSRR=(1<<2);
				
			if(data[3]=='0') GPIOA->BSRR=(1<<19);
			if(data[3]=='1') GPIOA->BSRR=(1<<3);
				
			if(data[4]=='0') GPIOA->BSRR=(1<<20);
			if(data[4]=='1') GPIOA->BSRR=(1<<4);
				
			if(data[5]=='0') GPIOA->BSRR=(1<<21);
			if(data[5]=='1') GPIOA->BSRR=(1<<5);
				
			if(data[6]=='0') GPIOA->BSRR=(1<<22);
			if(data[6]=='1') GPIOA->BSRR=(1<<6);
				
			if(data[7]=='0') GPIOA->BSRR=(1<<23);
			if(data[7]=='1') GPIOA->BSRR=(1<<7);

				
			
	}

}

