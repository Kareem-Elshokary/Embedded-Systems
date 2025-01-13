/*
 * Toggle Led
 *
 *  Eng: Kareem Abdelkader
 *    
 */

#include <stdio.h>
#include <stdint.h>

//The registers Base address
#define RCC_BASE     0x40021000
#define GPIOA_BASE   0x40010800

//The register offset address
#define RCC_APB2ENR   *((volatile int *)(RCC_BASE + 0x18))
#define GPIO_CRH      *((volatile int *)(GPIOA_BASE + 0x04))
#define GPIO_ODR      *((volatile int *)(GPIOA_BASE + 0x0c))

int main(){
	RCC_APB2ENR |= (1<<2);  //APB2ENR Register
	GPIO_CRH &= 0xffff0fff;
	GPIO_CRH |= 0x00000200; //Mode pin13 = 2

	while(1){
	GPIO_ODR |= (1<<13); //on
	for(int i=0; i<5000; i++); //delay
	GPIO_ODR &= ~(1<<13); //off
	for(int i=0; i<5000; i++); //delay
	}

	return 0;
}
