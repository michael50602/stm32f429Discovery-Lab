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


#define RCC_AHB1ENR		 (*((volatile unsigned long *) (0x40023800 + 0x30)))
#define GPIOG_MODER		 (*((volatile unsigned long *) (0x40021800 + 0x00)))
#define GPIOG_OTYPER  	(*((volatile unsigned long *) (0x40021800 + 0x04)))
#define GPIOG_OSPEEDR 	(*((volatile unsigned long *) (0x40021800 + 0x08)))
#define GPIOG_BSRR	 	(*((volatile unsigned long *) (0x40021800 + 0x18)))

asm(".word 0x20001000");
asm(".word main");
int main()
{
	unsigned int c=0;
	RCC_AHB1ENR = (1 << 6);
	GPIOG_MODER = 0x14000000;
	//GPIOG_OTYPER &= ~(1 << 13);	//GPIOG_OTYPER is default push-pull
	GPIOG_OSPEEDR = 0x14000000;
	while(1){
		GPIOG_BSRR = 0x40002000;	//Only PG13 ON
		for(c=0;c<100000;c++);
		GPIOG_BSRR = 0x20004000;	//Only PG14 ON
		for(c=0;c<100000;c++);
	}
}
