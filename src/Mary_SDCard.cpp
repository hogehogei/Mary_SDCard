/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>
#include "initialize.hpp"
#include "drv/timer32.h"
#include "drv/led.h"
#include "drv/uart.h"
#include "drv/sdcard/SD_Card.hpp"
#include "drv/sdcard/SDC_Drv_SPI.hpp"

// 変数を実体化するだけ
#define GLOBAL_VALUE_DEFINITION
#include "global.hpp"



// TODO: insert other include files here

// TODO: insert other definitions and declarations here
void TimerCallback();
void LED_Blink();

int g_LED_BlinkTimer = 0;
int g_LED_Blink = 0;

SDC_Drv_SPI g_SDCDriver;
SD_Card g_SDC;

int main(void) {

    // TODO: insert code here

	Initialize_CPU();
	Initialize_Peripheral();
	Call_Static_Initializers();

	Timer32B1_SetCallback( TimerCallback );

	UART_Print( "SDCard Initialize start." );
	if( g_SDC.Initialize(&g_SDCDriver) ){
		UART_Print( "SDCard Initialized completed!" );
	}
	else {
		UART_Print( "Failed Initialize SDCard." );
	}

	Init_SPI_Fast();

	TurnOnLED( LED_COLOR_BLUE );

    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	LED_Blink();
    }

    return 0 ;
}

void TimerCallback()
{
	++g_LED_BlinkTimer;
}

void LED_Blink()
{
	if( g_LED_BlinkTimer >= 500 ){
		g_LED_BlinkTimer = 0;
		++g_LED_Blink;
		if( (g_LED_Blink & 0x01) == 0x01 ){
			TurnOnLED( LED_COLOR_BLUE );
		}
		else {
			TurnOffLED( LED_COLOR_BLUE );
		}
	}
}
