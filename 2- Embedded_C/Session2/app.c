#include"UART.h"

unsigned char string[100] = "Learn-in-depth : Kareem";

void main(){

uart_send(string);

}
