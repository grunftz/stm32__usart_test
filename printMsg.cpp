#include "stm32f10x.h"                  		// Device header

#include "printMsg.h"

#include <stdio.h>													
#include <stdint.h>
#include "string.h"													//string lib
#include "stdlib.h"													//standarad functions lib
#include "stdarg.h"													//standard arguments lib


void println (char *msg, ...)
{
	va_list args; 														//get the list of arguments
	va_start(args,msg);												//extract argumets from message, reformat message
	vsprintf(buffer,msg,args);								//formating message acording to passed arguments

	//fill the buffer
	
	for(int i=0; i<strlen(buffer); i++)
	{
		USART1->DR=buffer[i];										//byte by byte filing sending data via TX
		
		while(!(USART1->SR & USART_SR_TXE)); 		//fill the array until the TX registar is empty
		
	}
	
	
}
