/* Mastring Embedded System Diploma 
   Unit2 - Lesson4 - Lab1
   Sturtup.c file
   Eng: Kareem Abdelkader
*/

#include<stdint.h>

void Reset_Handler();
extern int main();

void Defualt_Handler(){
	Reset_Handler();
}
void NMI_Handler()          __attribute__ ((weak, alias ("Defualt_Handler"))); ;
void H_Fault_Handler()      __attribute__ ((weak, alias ("Defualt_Handler"))); ;
void MM_Fault_Handler()     __attribute__ ((weak, alias ("Defualt_Handler"))); ;
void Bus_Fault()            __attribute__ ((weak, alias ("Defualt_Handler"))); ;
void Usage_Fault_Handler()  __attribute__ ((weak, alias ("Defualt_Handler"))); ;

//Booking 1024B located by .bss through unintialized array of int (256*4=1024)
static unsigned long Stack_top[256];

//Vectors section is an array of pointers to function
void (* const G_P_Fn_Vectors[])() __attribute__((section(".vectors"))) = {
	 (void (*)()) ((unsigned long) Stack_top + sizeof(Stack_top)),
         &Reset_Handler,
	 &NMI_Handler,
	 &H_Fault_Handler,
	 &MM_Fault_Handler,
	 &Bus_Fault,
	 &Usage_Fault_Handler
};



extern unsigned int _E_text;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;


void Reset_Handler() 
{
	//Copy data section from flas to RAM
	unsigned int Data_Size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
	unsigned char* P_src   = (unsigned char*)&_E_text;
	unsigned char* P_dst   = (unsigned char*)&_S_DATA;
	for(int i = 0; i < Data_Size; i++){
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++);
	}
	
	//Init .bss section in RAM 
	unsigned int bss_Size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_dst   = (unsigned char*)&_S_bss;
	for(int i = 0; i < bss_Size; i++){
		*((unsigned char*)P_dst++) = (unsigned char)0;
	}
	
	//Jumb main
	main();
}