/*
seting up uart for basic communication. 
No remaping RX / TX line -> PA10/PA9.

*/


#include "stm32f10x.h"                  // Device header
#include "string.h"


char data[11];

int main(void)
{
	//gpio C clock and pin 13 output
	
	RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;		//clock Port C

	// declare as Output pin 13
	GPIOC->CRH |=GPIO_CRH_MODE13;
	GPIOA->CRH &=~GPIO_CRH_CNF13;
	
	//enabling GPIO and USART1
	RCC->APB2ENR |=RCC_APB2ENR_IOPAEN;   //portA clock enable
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


	// enable rE
	
	//USART1->CR1 |=USART_CR1_RXNEIE; 		//RXNE Interrupt Enable 
	//USART1->CR1 |=USART_CR1_TXEIE;      //TX interrupt enable

	//enable RX enable TX UART enbale in CR1 register
	
	USART1->CR1 |=USART_CR1_RE; 				//RX enable, receive data enabled
	USART1 ->CR1 |=USART_CR1_TE;				//TX, enabled,  transmite data enabled
	USART1->CR1 |=USART_CR1_UE;					//USART enabled
//Nested Vectored Interrupt Controller  IRQ za USART1 je 37
// NVIC_EnableIRQ(USART1_IRQn); 
	
	while(1)
	{
		

				for(int i=0; i<=strlen(data);i++)
				{
				data[i] = USART1->DR;			//read it and store in data var
				
				
				//USART1->DR=data[i];			//send it back
				
					//	while(!(USART1->SR & USART_SR_TC));
					
			while(!(USART1->SR &	USART_SR_RXNE));
				}	
			if(data[9]=='a') GPIOC->BSRR=(1<<(29));
			if(data[10]=='b') GPIOC->BSRR=(1<<13);


	}
}



//interrupt rutina mora imati ovo ime!!!!!
//void USART1_IRQHandler(void)	
//{
//check incoming data
		

			
	
//}	
