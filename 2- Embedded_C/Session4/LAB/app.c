/*
Master Embedded System Diploma
Unit3_Lesson4_Lab1
Toggle led by cortex-m4 MC
Eng. Kareem Abdelkader
*/

//Registers
#define SYSCTL_RCG2_R_BASE    0x400fe000
#define GPIO_PORTF_R_BASE     0x40025000

#define SYSCTL_RCG2_R         *((volatile unsigned long*)(SYSCTL_RCG2_R_BASE+0x108))
#define GPIO_PORTF_DIR_R      *((volatile unsigned long*)(GPIO_PORTF_R_BASE+0x3fc))
#define GPIO_PORTF_DEN_R      *((volatile unsigned long*)(GPIO_PORTF_R_BASE+0x400))
#define GPIO_PORTF_DATA_R     *((volatile unsigned long*)(GPIO_PORTF_R_BASE+0x51c))


int main()
{
	//Enable the GPIO port
	SYSCTL_RCG2_R = 0x00000020;
	//Set (PF3) the direction as output
	GPIO_PORTF_DIR_R |= (1<<3);
	//Enable the GPIO pin
	GPIO_PORTF_DEN_R |= (1<<3);
	
	volatile unsigned long Delay_Count;

	while(1){
	
	//On
	GPIO_PORTF_DATA_R |= (1<<3);
	//Delay
	for(Delay_Count =0; Delay_Count<200000; Delay_Count++);
	//Off
	GPIO_PORTF_DATA_R &= ~(1<<3);
	//Delay
	for(Delay_Count =0; Delay_Count<200000; Delay_Count++);
	
	}


	return 0;
}
