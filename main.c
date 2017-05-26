#include "LPC11xx.h"                    // Device header
#include "ADC.h"
int main (void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	UART_Init();
	ADC_Init();
	LED_Init();
	while(1)
	{
		ulADCData=0;
		for(i=0;i<10;i++)
		{
			LPC_ADC->CR |=(1<<24);
			while((LPC_ADC->DR[0]&0x80000000)==0);
			LPC_ADC->CR |=(1<<24);
			while((LPC_ADC->DR[0]&0x80000000)==0);
			ulADCBuf = LPC_ADC->DR[0];
			ulADCBuf = (ulADCBuf>>6)&0x3ff;
			ulADCData += ulADCBuf;
			
		}
			ulADCData = ulADCData/10;
			ulADCData = (	ulADCData*3300)/1024;
		  sprintf(GcRcvBuf,"VINO = %4d MV\r\n",	ulADCData);
		  UART_SendStr(GcRcvBuf);
		  Delay(200);
		if(ulADCData<400) LPC_GPIO2->DATA =0xFE;
		if(ulADCData>400&&ulADCData<800) LPC_GPIO2->DATA =0xFC;
		if(ulADCData>800&&ulADCData<1200) LPC_GPIO2->DATA =0xF8;
		if(ulADCData>1200&&ulADCData<1600) LPC_GPIO2->DATA =0xF0;
		if(ulADCData>1600&&ulADCData<2000) LPC_GPIO2->DATA =0xE0;
		if(ulADCData>2000&&ulADCData<2400) LPC_GPIO2->DATA =0xC0;
		if(ulADCData>2400&&ulADCData<2800) LPC_GPIO2->DATA =0x80;
		if(ulADCData>2800&&ulADCData<3200) LPC_GPIO2->DATA =0x00;
	}
	
}