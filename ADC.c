#include "ADC.h"
void Delay(uint32_t ulTime)
{
	uint32_t i;
	i=0;
	while(ulTime--)
	{
		for(i=0;i<5000;i++);
	}
}
void ADC_Init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->R_PIO0_11 &= ~0xBF;
	LPC_IOCON->R_PIO0_11 |= 0x02;
	LPC_SYSCON->PDRUNCFG &=~(0x01<<13);
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x01<<13);
	LPC_ADC->CR=(0x01<<0)|
	            ((SystemCoreClock/1000000-1)<<8)|
	            (0<<16)|
	            (0<<17)|  
	            (0<<24)|      
	            (0<<27);     	
}
void UART_Init(void)
{
	uint16_t usFdiv;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_6 &= ~0x07;
	LPC_IOCON->PIO1_6 |=(1<<0);
	LPC_IOCON->PIO1_7 &= ~0x07;
	LPC_IOCON->PIO1_7 |=(1<<0);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV =0x01;
	
	LPC_UART->LCR =0x83;
	usFdiv=(SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	LPC_UART->DLM = usFdiv/256;
	LPC_UART->DLL = usFdiv%256;
	LPC_UART->LCR = 0X03;
	LPC_UART->FCR = 0X07;
}
void UART_SendByte(uint8_t ucDat)
{
	LPC_UART->THR =  ucDat;
	while((LPC_UART->LSR&0x40)==0);
}
void UART_SendStr(char *pucStr)
{
	while(1)
	{
		if(*pucStr == '\0')break;
		UART_SendByte(*pucStr++);
	}
}
void LED_Init()
{
		LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	  LPC_IOCON->PIO1_6 &= 0xF8;
		LPC_GPIO2->DIR |=~(1<<0);
		LPC_GPIO2->DIR |=~(1<<1);
		LPC_GPIO2->DIR |=~(1<<2);
		LPC_GPIO2->DIR |=~(1<<3);
		LPC_GPIO2->DIR |=~(1<<4);
		LPC_GPIO2->DIR |=~(1<<5);
		LPC_GPIO2->DIR |=~(1<<6);
		LPC_GPIO2->DIR |=~(1<<7);

	
}