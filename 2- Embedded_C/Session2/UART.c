#include"UART.h"

#define UART0DR  *((volatile unsigned int*)(0x101f1000))

void uart_send(unsigned char* ptr_txt){
	while(*ptr_txt != '\0'){
		UART0DR = (unsigned int)(*ptr_txt);
		ptr_txt++;
	}
} 