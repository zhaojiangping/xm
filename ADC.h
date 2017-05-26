#include "LPC11xx.h"                    // Device header
#include <stdio.h>
#include <string.h>
#define UART_BPS 9600
char GcRcvBuf[20];
#ifndef __ADC_H 
#define __ADC_H
void Delay(uint32_t ulTime);
void ADC_Init(void);
void UART_Init(void);
void UART_SendByte(uint8_t ucDat);
void UART_SendStr(char *pucStr);
void LED_Init();
#endif
