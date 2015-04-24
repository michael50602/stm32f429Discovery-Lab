/*
 *	This program turns on/off LEDs on STM32F429 Discovery Board
 *  
 *  You can see the reference from embedded2015.hackpad.com/Week-7-8--ID8HJ3uW0MO
 *
 *	If you have any question, please Email to me
 *
 *	John Chou <luckyjoou@gmail.com>
 *
 */

#define RCC_CR			 (*((volatile unsigned long *) (0x40023800)))
#define RCC_CFGR		 (*((volatile unsigned long *) (0x40023800 + 0x08)))
#define RCC_AHB1ENR		 (*((volatile unsigned long *) (0x40023800 + 0x30)))
#define GPIOG_MODER		 (*((volatile unsigned long *) (0x40021800 + 0x00)))
#define GPIOG_OTYPER   	(*((volatile unsigned long *) (0x40021800 + 0x04)))
#define GPIOG_OSPEEDR 	(*((volatile unsigned long *) (0x40021800 + 0x08)))
#define GPIOG_BSRR	 	(*((volatile unsigned long *) (0x40021800 + 0x18)))
#define STK_CTRL		 (*((volatile unsigned long*) (0xE000E010))) 
#define STK_LOAD		 (*((volatile unsigned long*) (0xE000E010 + 0x04))) 
#define STK_VAL			 (*((volatile unsigned long*) (0xE000E010 + 0x08))) 


asm(".word 0x20001000");
asm(".word main");

int systick_init(){
	RCC_CR = (1 << 16);			//Enable HSE clock
	while(!(RCC_CR & (1<<17)));	//Wait HSE Clock ready
	RCC_CFGR &= ~(1 << 7);		//AHB clock not divided 
	STK_LOAD = 1000000 - 1;		//1second once
	STK_VAL = 0;
//	STK_CTRL &= ~(1 << 1);
	STK_CTRL = 0x01;			// AHB/8 Counter enabled
}

int main()
{
	/* config gpio for led  */
	RCC_AHB1ENR = (1 << 6);
	GPIOG_MODER = 0x14000000;
	//GPIOG_OTYPER &= ~(1 << 13);	//GPIOG_OTYPER is default push-pull
	GPIOG_OSPEEDR = 0x14000000;

	systick_init();

	unsigned char flag = 0;
	unsigned int temp;
	while(1){
		do{
			temp = STK_CTRL;
		}while((temp&0x01)&&(!(temp&(1<<16))));
		if(flag){
			GPIOG_BSRR = 0x00002000;	//PG13 ON
			flag = 0;
		}else{
			GPIOG_BSRR = 0x20000000;	//PG13 OFF
			flag = 1;
		}
	}
}
